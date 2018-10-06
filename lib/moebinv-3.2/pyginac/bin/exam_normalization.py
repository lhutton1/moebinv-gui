#  Regression tests for PyGiNaC (C) 2005 Matti Peltomaki

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/exam_normalization.cpp as found in 
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

from ginac import *

def check_normal(e, d):
    en = e.normal()
    if(en != d):
        print "normal form of ", e, " returned ", en , " while it should be ", d
        return 1
    return 0   

def exam_normal1():
    """
    >>> exam_normal1()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')

    # Expansion
    e = pow(x,2) - (x-1)*(x+1) - 1
    result += check_normal(e, 0)
    
    # Expansion inside functions
    e = sin(x*(x+1)-x) + 1
    d = sin(pow(x, 2)) + 1
    result += check_normal(e, d)

    # Fraction addition
    e = 2/x + y/3
    d = (x*y + 6)/(x*3)
    result += check_normal(e, d)

    e = pow(x,-1) + x/(x+1)
    d = (pow(x,2) + x + 1)/(x*(x+1))
    result += check_normal(e, d)

    return result

def exam_normal2():
    """
    >>> exam_normal2()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')
    z = symbol('z')
    w = symbol('w')

    # Fraction cancellation
    e = numeric(1)/2 * z * (2*x + 2*y)
    d = z*(x+y)
    result += check_normal(e, d)

    e = numeric(1)/6 * z * (3*x + 3*y) * (2*x + 2*w)
    d = z * (x + y) * (x + w)
    result += check_normal(e, d)

    e = (3*x + 3*y) * (w/3 + z/3)
    d = (x + y) * (w + z)
    result += check_normal(e, d)

    e = (pow(x, 2) - pow(y, 2)) / pow(x-y, 3)
    d = (y + x) / pow(x - y, 2)
    result += check_normal(e, d)
 
    e = (pow(x, -1) + x) / (pow(x , 2) * 2 + 2)
    d = pow(x * 2, -1)
    result += check_normal(e, d)

    # Fraction cancellation with rational coefficient
    e = (pow(x, 2) - pow(y, 2)) / pow(x/2 - y/2, 3)
    d = (8*x + 8*y) / pow(x - y, 2)
    result += check_normal(e, d)

    e = z/5 * (x/7 + y/10) / (x/14 + y/20)
    d = 2*z/5
    result += check_normal(e, d)

    return result

def exam_normal3():
    """
    >>> exam_normal3()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')

    # Distribution of powers
    e = pow(x/y, 2)
    d = pow(x, 2) / pow(y, 2)
    result += check_normal(e, d)

    # Distribution of powers (integer, distribute) and fraction addition
    e = pow(pow(x, -1) + x, 2)
    d = pow(pow(x, 2) + 1, 2) / pow(x, 2)
    result += check_normal(e, d)

    # Distribution of powers (non-integer, don't distribute) and fraction addition
    e = pow(pow(x, -1) + x, numeric(1)/2)
    d = pow((pow(x, 2) + 1) / x, numeric(1)/2)
    result += check_normal(e, d)

    return result 

def exam_normal4():
    """
    >>> exam_normal4()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')
    z = symbol('z')

    # Replacement of functions with temporary symbols and fraction cancellation
    e = pow(sin(x), 2) - pow(cos(x), 2)
    e /= sin(x) + cos(x)
    d = sin(x) - cos(x)
    result += check_normal(e, d)

    # Replacement of non-integer powers with temporary symbols
    e = (pow(numeric(2), numeric(1)/2) * x + x) / x
    d = pow(numeric(2), numeric(1)/2) + 1
    result += check_normal(e, d)

    # Replacement of complex numbers with temporary symbols
    e = (x + y + x*I + y*I) / (x + y)
    d = 1 + I
    result += check_normal(e, d)

    e = (pow(x, 2) + pow(y, 2)) / (x + y*I)
    d = e
    result += check_normal(e, d)

    # More complex rational function
    e = (pow(x-y*2,4)/pow(pow(x,2)-pow(y,2)*4,2)+1)*(x+y*2)*(y+z)/(pow(x,2)+pow(y,2)*4)
    d = (y*2 + z*2) / (x + y*2)
    result += check_normal(e, d)

    return result

def check_content(e, x, ic, c, pp):
    result = 0

    r_ic = e.integer_content()
    if(r_ic != ic):
        print "the integer content of ", e, " returned ", r_ic, " instead of ", ic
        result += 1

    r_c = e.content(x)
    if(r_c != c):
        print "the content part of ", e, " returned ", r_c, " instead of ", c
        result += 1

    r_pp = e.primpart(x)
    if(r_pp != pp):
        print "the primitive polynomial of ", e, " returned ", r_pp, " instead of ", pp
        result += 1

    r = r_c*r_pp*e.unit(x)
    if((r-e).normal() != 0):
        print "product of unit, content, and primitive part of ", e
        print "returned ", r, " instead of ", e
        result += 1
    
    return result

def exam_content():
    """
    >>> exam_content()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')

    result += check_content(numeric(-3)/4, x, numeric(3)/4, numeric(3)/4, 1)
    result += check_content(-x/4, x, numeric(1)/4, numeric(1)/4, x)
    result += check_content(5*x-15, x, 5, 5, x-3)
    result += check_content(5*x*y-15*y*y, x, 5, 5*y, x-3*y)
    result += check_content(-15*x/2+numeric(25)/3, x, numeric(5)/6, numeric(5)/6, 9*x-10)
    result += check_content(-x*y, x, 1, y, x)

    return result
    
if __name__ == "__main__":  
    import doctest, sys 
 
    doctest.testmod( sys.modules.get( __name__), verbose=True)  
