#  PyGiNaC  Copyright (C) 2004 Jonathan Brandmeyer
#  These tests were adapted from check/check_matricies.cpp as found in GiNaC
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
from genex import dense_univariate_poly, sparse_tree
from random import randrange

# determinants of some sparse symbolic matrices with coefficients in
# an integral domain.
def integdom_matrix_determinants():
    """
    >>> integdom_matrix_determinants()
    Matrix determinant test passed.
    """
    error = False
    a = symbol('a')
    # Feel like you have CPU time to burn?  
    # Raise the value of the upper bounds here...
    for size in range(3, 22):
        A = matrix( size, size)
        # Populate one element in each row
        for r in range( size-1):
            A[r, randrange(0,size)] = dense_univariate_poly(a, 5)
        # Set the last row to a linear combination of two others to
        # guarantee that the determinant should be zero
        for c in range(size):
            A[size-1, c] = A[0,c] - A[size-2,c]
        if A.determinant() != 0:
            error = True
            print "Determinant of", size, "x", size, "matrix", A
            print "was not found to vanish!"
    if error:
        print "Matrix determinant test failed."
    else:
        print "Matrix determinant test passed."    

# determinants of some sparse symbolic matrices with coefficients in
# the rational domain.
def rational_matrix_determinants():
    """
    >>> rational_matrix_determinants()
    Rational matrix determinants test passed.
    """
    error = False
    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    for size in range( 3, 9):
        A = matrix(size, size)
        for r in range(size-1):
            # Populate one or two elements in each row:
            for ec in range(2):
                numer = sparse_tree( a, b, c, randrange(1, 4), 
                    False, False, False)
                denom = numeric(0)
                while denom == 0:
                    denom = sparse_tree( a, b, c, randrange(2), 
                        False, False, False)
                A[r, randrange(size)] = numer/denom
        # set the last row to a linear combination of two other lines
        # to guarantee that the determinant is zero:        
        for co in range(size):
            A[size-1, co] = A[0,co] - A[size-2,co]
        if A.determinant() != 0:
            error = True
            print "Determinant of", size, "x", size," matrix ", A
            print "was not found to vanish!"
    if error:
        print "Rational matrix determinants test failed."
    else:
        print "Rational matrix determinants test passed."

# Throw some trigonimetric functions in the mix...
def funny_matrix_determinants():
    """
    >>> funny_matrix_determinants()
    'Funny' matrix determinant test passed.
    """
    error = False
    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    for size in range(3, 8):
        A = matrix(size, size)
        for co in range(size-1):
            # Populate one or two elements in each row
            for ec in range(0, 2):
                numer = sparse_tree(a, b, c, randrange(1, 4), True, True, False)
                denom = numeric(0)
                while denom == 0:
                    denom = sparse_tree(a, b, c, randrange(2), False, True, False)
                A[randrange(size), co] = numer/denom
            # Set the last column to a linear combination of two other columns to
            # guarantee that the determinant is zero
            for ro in range(size):
                A[ro, size-1] = A[ro, 0] - A[ro,size-2]
            if A.determinant() != 0:
                error = True
                print "Determinant of", size, "x", size, "matrix", A
                print "was not found to vanish!"
    if error:
        print "'Funny' matrix determinant test failed."
    else:
        print "'Funny' matrix determinant test passed."    

# Compare results from different determinant algorithms
def compare_matrix_determinants():
    """
    >>> compare_matrix_determinants()
    Matrix determinant comparison test passed.
    """
    error = False
    a = symbol('a')
    for size in range(2, 8):
        A = matrix(size, size)
        for co in range(size):
            for ro in range(size):
                if randrange(size/2) == 0:
                    A[ro, co] = sparse_tree(a, a, a, randrange(3), 
                        False, True, False)
        det_gauss = A.determinant( determinant_algo.gauss)
        det_laplace = A.determinant( determinant_algo.laplace)
        det_divfree = A.determinant( determinant_algo.divfree)
        det_bareiss = A.determinant( determinant_algo.bareiss)
        if not (det_gauss - det_laplace).normal().is_zero() \
            or not (det_bareiss - det_laplace).normal().is_zero() \
            or not (det_divfree - det_laplace).normal().is_zero():
                error = True
                print "Determinant of", size, "x", size, "matrix", A
                print "is inconsistent between different algorithms:"
                print "Gauss elimination:   ", det_gauss
                print "Minor elimination:   ", det_laplace
                print "Division-free elim.: ", det_divfree
                print "Fraction-free elim.: ", det_bareiss
    if error:
        print "Matrix determinant comparison test failed."
    else:
        print "Matrix determinant comparison test passed."

# Check the matrix inversion algorithm.
def symbolic_matrix_inverse():
    """
    >>> symbolic_matrix_inverse()
    Symbolic matrix inverse test passed.
    """
    error = False
    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    for size in range(2, 6):
        A = matrix(size, size)
        while A.determinant() == 0:
            for co in range(size):
                for ro in range(size):
                    if randrange(size/2) == 0:
                        A[ro, co] = sparse_tree(a, b, c, randrange(2), 
                            False, True, False)
        B = A.inverse()
        C = (A * B).evalm().normal()
        ok = True
        for ro in range(size):
            for co in range(size):
                elem = C[ro, co]
                if ro == co and elem != 1:
                    print "non-unity", "(", ro, ",", co, ")", elem
                    ok = False
                if ro != co and elem != 0:
                    print "nonzero", "(", ro, ",", co, ")", elem
                    ok = False
        if not ok:
            print "Inverse of ", size, "x", size, "matrix", A
            print "errooneously returned:", B
            print "Its determinant is: ", A.determinant()
            error = True
    if error:
        print "Symbolic matrix inverse test failed."
    else:
        print "Symbolic matrix inverse test passed."

if __name__ == "__main__":
    import doctest, sys
    doctest.testmod( sys.modules.get( __name__), verbose=True)
