#  PyGiNaC Copyright (C) 2004 Jonathan Brandmeyer
#
#  These tests were adapted from check/check_lsolve.cpp as found in GiNaC
#  version 1.3.0, under the GNU General Public License.
#
#  GiNaC Copyright (C) 1999-2004 Johannes Gutenberg University Mainz, Germany
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

from ginac import *
from genex import dense_univariate_poly
from random import randrange

def check_matrix_solve(m, n, p, degree):
    """
    >>> # solve some numeric linear systems
    >>> result = 0
    >>> for n in range(1, 14):
    ...     result += check_matrix_solve(n, n, 1, 0)
    ... 
    >>> if result:
    ...    print "Numeric system checks failed."
    ... else:
    ...     print "Numeric system checks passed."
    ...
    Numeric system checks passed.
    
    >>> # solve some underdetermined numeric systems
    >>> result = 0
    >>> for n in range(1, 14):
    ...     result += check_matrix_solve(n+1, n, 1, 0)
    ...
    >>> if result:
    ...    print "Underdetermined system checks failed."
    ... else:
    ...     print "Underdetermined system checks passed."
    ...
    Underdetermined system checks passed.
    
    >>> result = 0
    >>> # solve some overdetermined numeric systems
    >>> for n in range(1, 14):
    ...     result += check_matrix_solve(n, n+1, 1, 0)
    ...
    >>> if result:
    ...     print "Overdetermined system checks failed."
    ... else:
    ...     print "Overdetermined system checks passed."
    ...
    Overdetermined system checks passed.
    
    >>> # solve some multiple numeric systems
    >>> result = 0
    >>> for n in range(1, 14):
    ...     result += check_matrix_solve(n, n, n/3+1, 0)
    ... 
    >>> if result:
    ...     print "Multiple numeric systems checks failed."
    ... else:
    ...     print "Multiple numeric systems checks passed."
    ... 
    Multiple numeric systems checks passed.
    
    >>> # solve some symbolic linear systems
    >>> result = 0
    >>> for n in range(1, 8):
    ...     result += check_matrix_solve(n, n, 1, 2)
    ... 
    >>> if result:
    ...     print "Symbolic linear systems checks failed."
    ... else:
    ...     print "Symbolic linear systems checks passed."
    ...
    Symbolic linear systems checks passed.
    """
    a = symbol('a')
    A = matrix(m, n)
    B = matrix(m, p)
    for ro in range( min(m, n)):
        for co in range(n):
            A[ro,co] = dense_univariate_poly(a, degree)
        for co in range(p):
            B[ro,co] = dense_univariate_poly(a, degree)
    for ro in range(n, m):
        for co in range(n):
            A[ro, co] = A[ro-1,co]
        for co in range(p):
            B[ro,co] = B[ro-1,co]
    # Create a vector of n*p symbols all named "xrc" where r and c are ints
    X = matrix(n,p)
    for i in range(n):
        for j in range(p):
            X[i,j] = symbol("x" + str(i) + str(j))
    soln = matrix(n, p)
    # Solve the system A*X == B
    sol = A.solve(X, B)
    # Check the result with the original matrix
    error = False
    for ro in range(m):
        for pco in range(p):
            e = numeric(0)
            for co in range(n):
                e += A[ro,co]*sol[co,pco]
            if (e-B[ro,pco]).normal() != 0:
                error = True
    if error:
        print "Our solve method claims that A*X == B with matricies:"
        print "A ==", A
        print "X ==", X
        print "B ==", B
        print "X (the solution) == ", sol
    return error

def check_inifcns_lsolve(n):
    """
    >>> result = 0
    >>> for n in range( 2, 6):
    ...     result += check_inifcns_lsolve(n)
    ...
    >>> if result:
    ...    print "Matrix lsolve checks failed."
    ... else:
    ...    print "Matrix lsolve checks passed."
    ...
    Matrix lsolve checks passed.
    """
    result = 0
    for repetition in range(220):
        # Create two size n lists of symbols, one for the coefficients
        # a[0]-a[n], another for the indetermines x[0]...x[n]
        a = []
        x = []
        for i in range(n):
            a.append( symbol('a' + str(i)))
            x.append( symbol('x' + str(i)))
        eqns = [] # Equation list
        vars = [] # Variable list
        # Create a random linear system
        for i in range(n):
            lhs = randrange(-100, 101)
            rhs = randrange(-100, 101)
            for j in range(n):
                lhs += a[j]*randrange(-10, 10)
                rhs += x[j]*randrange(-10, 10)
            eqns.append( lhs == rhs)
            vars.append( x[i])
        soln = lsolve( eqns, vars)
        if not len(soln):
            # No solution was found.  Is the coefficient matrix truly
            # degenerate?
            coeffmat = matrix(n, n)
            for ro in range(n):
                for co in range(n):
                    coeffmat[ro, co] = eqns[co].rhs.coeff(a[co],1)
            if coeffmat.determinant() != 0:
                result += 1
                print "solution of the system", [ str(eqn) for eqn in eqns],\
                    "for", [str(var) for var in vars], "was not found."
        else:
            error = False
            for i in range(n):
                if not eqns[i].subs(soln):
                    error = True
            if error:
                result += 1
                print "solution of the system", [ str(eqn) for eqn in eqns], \
                    "for", [str(var) for var in vars], \
                    "erroneously returned: ", [str(sol) for sol in soln]
    return result

if __name__ == "__main__":
    import doctest, sys
    doctest.testmod( sys.modules.get( __name__), verbose=True)

