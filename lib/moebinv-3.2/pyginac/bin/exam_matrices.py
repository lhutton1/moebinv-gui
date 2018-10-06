#  Regression tests for PyGiNaC 

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/exam_matricies.cpp as found in 
#  GiNaC version 1.3.0, under the GNU General Public License.
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

from ginac import *;

def matrix_determinants():
    """
    >>> print matrix_determinants()
    0
    >>> 
    """

    result = 0
    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    d = symbol('d')
    e = symbol('e')
    f = symbol('f')
    g = symbol('g')
    h = symbol('h')
    i = symbol('i')

    # Check symbolic trivial matrix determinant
    m1 = matrix([[a]])
    det = m1.determinant()
    if(det != a):
        print "determinant of 1x1 matrix ", m1
        print "erroneously returned ", det
        result += 1

    # Check generic dense symbolic 2x2 matrix determinant
    m2 = matrix([[a,b],[c,d]])
    det = m2.determinant()
    if(det != a*d - b*c):
        print "determinant of 2x2 matrix ", m2
        print "erroneously returned ", det
        result += 1
    
    # Check generic dense symbolic 3x3 matrix determinant
    m3 = matrix([[a,b,c],[d,e,f],[g,h,i]])
    det = m3.determinant()
    if(det != a*e*i - a*f*h - d*b*i + d*c*h + g*b*f - g*c*e):
        print "determinant of 3x3 matrix ", m3
        print "erroneously returned ", det
        result += 1

    # Check dense numeric 3x3 matrix determinant
    m3 = matrix([[0,-1,3],[3,-2,2],[3,4,-2]])
    det = m3.determinant()
    if(det != 42):
        print "determinant of 3x3 matrix ", m3
        print "erroneously returned ", det
        result += 1

    # Check dense symbolic 2x2 matrix determinant
    m2 = matrix([[a/(a-b), 1], [b/(a-b), 1]])
    det = m2.determinant()
    if(det != 1):
        if(det.normal() == 1): # only half wrong
            print "determinant of 2x2 matrix ", m2
            print "was returned unnormalized as ", det
        else: # totally wrong
            print "determinant of 2x2 matrix ", m2
            print "erroneously returned ", det
        result += 1

    # Check sparse symbolic 4x4 matrix determinant
    m4 = matrix(4,4)
    m4[0,1] = a
    m4[1,0] = b
    m4[3,2] = c
    m4[2,3] = d
    det = m4.determinant()
    if(det != a*b*c*d):
        print "determinant of 4x4 matrix ", m4
        print "erronsously returned ", det
        result += 1

    # Check characteristic polynomial
    m3 = matrix([[a,-2,2],[3,a-1,2],[3,4,a-3]])
    p = m3.charpoly(a)
    if(p != 0):
        print "charpoly of 3x3 matrix ", m3
        print "erroneously returned ", p
        result += 1

    return result

def matrix_invert1():
    """
    >>> print matrix_invert1()
    0
    >>>
    """
    result = 0
    
    a = symbol('a')
    m = matrix([[a]])
    mi = m.inverse()
    if(mi[0,0] != pow(a,-1)):
        print "Inverse of the 1x1 matrix ", m
        print "erroneously returned", mi
        result = 1
    return result

def matrix_invert2():
    """
    >>> print matrix_invert2()
    0
    >>> 
    """
    result = 0

    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    d = symbol('d')
    m = matrix([[a,b],[c,d]])
    mi = m.inverse()
    det = m.determinant()
    if((mi[0,0]*det).normal() != d or
       (mi[0,1]*det).normal() != -b or
       (mi[1,0]*det).normal() != -c or
       (mi[1,1]*det).normal() != a):
        print "Inverse of 2x2 matrix ", m
        print "erroneously returned ", mi
        result = 1
    return result

def matrix_invert3():
    """
    >>> print matrix_invert3()
    0
    >>>
    """
    result = 0

    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    d = symbol('d')
    e = symbol('e')
    f = symbol('f')
    g = symbol('g')
    h = symbol('h')
    i = symbol('i')
    m = matrix([[a,b,c],[d,e,f],[g,h,i]])
    mi = m.inverse()
    det = m.determinant()
    if (((mi[0,0]*det).normal() != (e*i-f*h)) or
        ((mi[0,1]*det).normal() != (c*h-b*i)) or
        ((mi[0,2]*det).normal() != (b*f-c*e)) or
        ((mi[1,0]*det).normal() != (f*g-d*i)) or
        ((mi[1,1]*det).normal() != (a*i-c*g)) or
        ((mi[1,2]*det).normal() != (c*d-a*f)) or
        ((mi[2,0]*det).normal() != (d*h-e*g)) or
        ((mi[2,1]*det).normal() != (b*g-a*h)) or
        ((mi[2,2]*det).normal() != (a*e-b*d))):
        print "Inverse of 3x3 matrix ", m
        print "erroneously returned ", mi
        result = 1

    return result

def matrix_solve2():
    """
    check the solution of the multiple system A*X = B:
         [ 1  2 -1 ] [ x0 y0 ]   [ 4 0 ]
    	 [ 1  4 -2 ]*[ x1 y1 ] = [ 7 0 ]
    	 [ a -2  2 ] [ x2 y2 ]   [ a 4 ]  
    >>> print matrix_solve2()
    0
    >>> 
    """
    result = 0

    a = symbol('a')
    x0 = symbol('x0')
    y0 = symbol('y0')
    x1 = symbol('x1')
    y1 = symbol('y1')
    x2 = symbol('x2')
    y2 = symbol('y2')
    A = matrix([[1,2,-1], [1,4,-2], [a,-2,2]])
    X = matrix([[x0,y0], [x1,y1], [x2,y2]])
    B = matrix([[4,0],[7,0],[a,4]])
    
    # corr contains the correct answer
    corr = matrix([[1,0], [3,2], [3,4]])
    sol = A.solve(X, B)
    
    if(corr != sol):
        print "Solving ", A, " * ", X, " == ", B
        print "erroneously returned ", sol
        result = 1

    return result

def matrix_evalm():
    """
    >>> print matrix_evalm()
    0
    >>>
    """
    result = 0

    S = matrix([[1,2],[3,4]])
    T = matrix([[1,1],[2,-1]])
    R = matrix([[27,14],[36,26]])

    expr = (S + T) * (S + 2*T)
    expr2 = expr.evalm()
    if(expr2 != R):
        print "Evaluating ", expr, " erroneously returned ", expr2
        print "instead of ", R
        result = 1

    return result

def matrix_rank():
    """
    >>> print matrix_rank()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')

    # The zero matrix has rank 0
    m = matrix(3,3)
    if(m.rank() != 0):
        print "The rank of ", m, " was not computed correctly."
        result += 1

    # A trivial rank one example
    m = matrix([[1,0,0], [2,0,0], [3,0,0]])
    if(m.rank() != 1):
        print "The rank of ", m, " was not computed correctly."
        result += 1

    # An example from Maple's help with rank two
    m = matrix([[x,1,0], [0,0,1], [x*y,y,1]])
    if(m.rank() != 2):
        print "The rank of ", m, " was not computed correctly."
        result += 1

    # The 3x3 unit matrix has rank 3
    m = unit_matrix(3)
    if(m.rank() != 3):
        print "The rank of ", m, " was not computed correctly."
        result += 1

    return result

def matrix_misc():
    """
    >>> print matrix_misc()
    0
    >>>
    """
    result = 0
    
    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    d = symbol('d')
    e = symbol('e')
    f = symbol('f')

    # Check a simple trace
    m1 = matrix([[a,b],[c,d]])
    tr = m1.trace()
    if(tr != a+d):
        print "Trace of 2x2 matrix ", m1, " erroneously returned ", tr
        result += 1

    # Two checks of transposing matrices
    m2 = m1.transpose()
    if(m2 != matrix([[a,c],[b,d]])):
        print "Transpose of ", m1, " erroneously returned ", m2
        result += 1
        
    m3 = matrix([[a,b,c],[d,e,f]])
    m4 = m3.transpose().transpose()
    if(m4!= m3):
        print "Double transpose of ", m3, " erroneously returned ", m4
        result += 1

    # Produce an exception by trying to invert a singular matrix
    m5 = matrix(2,2)
    c = False 
    try:
        m5inv = m5.inverse()
    except:
        caught = True
    if(not caught):
        print "A singular matrix ", m5, " erroneously inverted to ", m5inv
        result += 1
    
    return result

if __name__ == "__main__": 
    import doctest, sys
 
    doctest.testmod( sys.modules.get( __name__), verbose=True) 
