#  Regression tests for PyGiNaC (C) 2005 Matti Peltomaki

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/exam_polygcd.cpp as found in 
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

max_variables = 3;
x = symbol('x')
z = symbol('z')
y = []
for i in range(max_variables):
    y.append(symbol())

def poly_gcd1():
    """
    GCD = 1

    >>> poly_gcd1()
    0
    >>> 
    """
    result = 0

    for v in range(1, max_variables+1):
        e1 = x
        e2 = pow(x, 2)
        for i in range(v):
            e1 += y[i]
            e2 += pow(y[i], 2)
        f = (e1+1)*(e2+2)
        g = e2 * (-pow(x, 2) * y[0] * 3 + pow(y[0], 2) - 1)
        r = gcd(f, g)
        if r != 1:
            print "case 1, gcd(",f,",",g,") = ",r," (should be 1)"
            result += 1

    return result

def poly_gcd2():
    """
    Linearly dense quartic inputs with quadratic GCDs

    >>> poly_gcd2()
    0
    >>>
    """
    
    result = 0

    for v in range(1, max_variables+1):
        e1 = x
        e2 = x
        for i in range(v):
            e1 += y[i]
            e2 -= y[i]
        d = pow(e1+1,2)
        f = d * pow(e2 - 2, 2)
        g = d * pow(e1 + 2, 2)
        r = gcd(f.expand(), g.expand())
        if not (r-d).expand().is_zero():
            print "case 2, gcd(",f,",",g,") = ",r," (should be ",d,")"
            result += 1

    return result

def poly_gcd3():
    """
    Sparse GCD and inputs where degree are proportional to the number of variables

    >>> poly_gcd3()
    0
    >>>
    """

    result = 0

    for v in range(1, max_variables+1):
        e1 = pow(x, v+1)
        for i in range(v):
            e1 += pow(y[i], v+1)
        d = e1 + 1
        f = d * (e1 - 2)
        g = d * (e1 + 2)
        r = gcd(f.expand(), g.expand())
        if not (r-d).expand().is_zero():
            print "case 3, gcd(",f,",",g,") = ",r," (should be ",d,")"
            result += 1

    return result

def poly_gcd3p():
    """
    Variation of case 3; major performance degradation with PRS
    
    >>> poly_gcd3p()
    0
    >>>
    """

    result = 0

    for v in range(1, max_variables+1):
        e1 = pow(x, v+1)
        e2 = pow(x, v)
        for i in range(v):
            e1 += pow(y[i], v+1)
            e2 += pow(y[i], v)
        d = e1 + 1
        f = d * (e1 - 2)
        g = d * (e1 + 2)
        r = gcd(f.expand(), g.expand())
        if not (r-d).expand().is_zero():
            print "case 3p, gcd(",f,",",g,") = ",r," (should be ",d,")"
            result += 1

    return result

def poly_gcd4():
    """
    Quadratic non-monic GCD; f and g have other quadratic factors

    >>> poly_gcd4()
    0
    >>>
    """

    result = 0

    for v in range(1, max_variables+1):
        e1 = pow(x, 2) * pow(y[0], 2)
        e2 = pow(x, 2) - pow(y[0], 2)
        e3 = x * y[0]
        for i in range(1, v):
            e1 += pow(y[i], 2)
            e2 += pow(y[i], 2)
            e3 += y[i]

        d = e1 + 1
        f = d * (e2 - 1)
        g = d * pow(e3 + 2, 2)
        r = gcd(f.expand(), g.expand())
        if not (r-d).expand().is_zero():
            print "case 4, gcd(",f,",",g,") = ",r," (should be ",d,")"
            result += 1
            
    return result

def poly_gcd5():
    """
    Completely dense non-monic quadratic inputs with dense non-monic linear GCDs

    >>> poly_gcd5()
    0
    >>>
    """

    result = 0

    for v in range(1, max_variables+1):
        e1 = x +1 
        e2 = x - 2
        e3 = x + 2
        for i in range(v):
            e1 *= y[i] + 1
            e2 *= y[i] - 2
            e3 *= y[i] + 2

        d = e1 - 3
        f = d * (e2 + 3)
        g = d * (e3 - 3)
        r = gcd(f.expand(), g.expand())
        if not (r-d).expand().is_zero():
            print "case 5, gcd(",f,",",g,") = ",r," (should be ",d,")"
            result += 1

    return result

def poly_gcd5p():
    """
    Sparse non-monic quadratic inputs with linear GCDs

    >>> poly_gcd5()
    0
    >>>
    """

    result = 0

    for v in range(1, max_variables+1):
        e1 = x
        for i in range(v):
            e1 *= y[i]

        d = e1 - 1;
        f = d * (e1 + 3)
        g = d * (e1 - 3)
        r = gcd(f.expand(), g.expand())
        if not (r-d).expand().is_zero():
            print "case 5p, gcd(",f,",",g,") = ",r," (should be ",d,")"
            result += 1

    return result

def poly_gcd6():
    """
    Trivariate inputs with increasing degrees

    >>> poly_gcd6()
    0
    >>> 
    """

    result = 0

    y = symbol('y')

    for j in range(1, max_variables+1):
        d = pow(x, j) * y * (z - 1)
        f = d * (pow(x, j) + pow(y, j + 1) * pow(z, j) + 1)
        g = d * (pow(x, j + 1) + pow(y, j) * pow(z, j + 1) - 7)
        r = gcd(f.expand(), g.expand())
        if not (r-d).expand().is_zero():
            print "case 6, gcd(",f,",",g,") = ",r," (should be ",d,")"
            result += 1

    return result

def poly_gcd7():
    """
    Trivariate polynomials whose GCD has common factors with its cofactors

    >>> poly_gcd7()
    0
    >>>
    """
    
    result = 0

    y = symbol('y')
    p = x - y * z + 1
    q = x - y + z * 3

    for j in range(1, max_variables+1):
        for k in range(j+1, 5):
            d = pow(p, j) * pow(q, j)
            f = pow(p, j) * pow(q, k)
            g = pow(p, k) * pow(q, j) 
            r = gcd(f, g)
            if not (r-d).expand().is_zero():
                print "case 7, gcd(",f,",",g,") = ",r," (should be ",d,")"
                result += 1

    return result

if __name__ == "__main__":  
    import doctest, sys 

    doctest.testmod( sys.modules.get( __name__), verbose=True)  
