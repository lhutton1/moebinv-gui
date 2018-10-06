#  Regression tests for PyGiNaC (C) 2005 Matti Peltomaki

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/exam_paranoia.cpp as found in 
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

def exam_paranoia1():
    """
    According to the GiNaC people, these were bugs in power.cpp in 1999.
    
    >>> exam_paranoia1()
    0
    >>>
    """

    result = 0

    x = symbol('x')
    y = symbol('y')
    z = symbol('z')

    e = z*y*x
    f = y*z
    g = e / f

    # In the first one expand did not do any job at all
    if not g.expand().is_equal(x):
        print "e=x*y*x; f=y*x; (e/f).expand() erroneously returned ", g.expand()
        result += 1

    # This somehow used to return 0
    e = pow(x+1,1)
    if not e.expand().is_equal(e):
        print "pow(x+1,1).expand() erroneously returned ", e.expand()
        result += 1

    return result

def exam_paranoia2():
    """
    From GiNaC:
    And here the second oops which showed up until May 17th 1999.  It had to do
    with lexicographic canonicalization and thus showed up only if the variables
    had the names as given here:

    >>> exam_paranoia2()
    0
    >>>
    """

    result = 0

    x = symbol('x')
    y = symbol('y')
    z = symbol('z')

    e = x + x*z;
    f = e*y;
    g = f - e*y;

    # After .expand(), g should be zero
    if not g.expand().is_zero():
        print "e=x + x*z; f = e*y; (f - e*y).expand() erroneously returned", g.expand()
        result += 1

    # After .eval(), g should be zero
    if not g.eval().is_zero():
        print "e=x + x*z; f = e*y; (f - e*y).eval() erroneously returned", g.eval()
        result += 1

    # After both of them, g should also be zero
    if not g.expand().eval().is_zero():
        print "e=x + x*z; f = e*y; (f - e*y).expand().eval() erroneously returned"
        print g.expand().eval()
        result += 1

    return result

def exam_paranoia3():
    """
    GiNaC:
    The third bug was introduced on May 18th 1999, discovered on May 19 and
    fixed that same day.  It worked when x was substituted by 1 but not with
    other numbers:

    >>> exam_paranoia3()
    0
    >>>
    """

    result = 0

    x = symbol('x')
    y = symbol('y')

    e = x*y - y
    f = e.subs(x == 2)
    
    if not f.is_equal(y):
        print "e = x*y - y; f = e.subs(x == 2) erroneously returned", f
        result += 1

    if not f.eval().is_equal(y):
        print "e = x*y - y; f = e.subs(x == 2) erroneously returned", f.eval()
        result += 1

    if not f.expand().is_equal(y):
        print "e = x*y - y; expand(e.subs(x == 2)) erroneously returned", f.expand()
        result += 1

    return result

def exam_paranoia4():
    """
    GiNaC:
    The fourth bug was also discovered on May 19th 1999 and fixed immediately:

    >>> exam_paranoia4()
    0
    >>>
    """

    result = 0

    x = symbol('x')
    e = pow(x, 2) + x + 1
    f = pow(x, 2) + x + 1
    g = e - f

    if not g.is_zero():
        print "e = pow(x,2) + x + 1; f = e; g = e-f; g erroneously returned ", g
        result += 1

    if not g.eval().is_zero():
        print "e = pow(x,2) + x + 1; f = e; g = e-f; eval(g) erroneously returned ", g.eval()
        result += 1

    return result

def exam_paranoia5():
    """
    GiNaC:
    The fifth oops was discovered on May 20th 1999 and fixed a day later
    >>> exam_paranoia5()
    0
    >>>
    """

    result = 0

    x = symbol('x')
    y = symbol('y')

    e = pow(x*y + 1, 2)
    f = pow(x*y,2) + 2*x*y + 1
    
    if not (e-f).expand().is_zero():
        print "(x*y+1)**2-(x*y)**2-2*x*y-1 erroneously not zero but", (e-f).expand()
        result += 1

    return result

def exam_paranoia6():
    """
    GiNaC:
    This one was discovered on Jun 1st 1999 and fixed the same day:
    
    >>> exam_paranoia6()
    0
    >>>
    """

    result = 0

    x = symbol('x')
    e = pow(x, -5)
    f = e.denom()
    if f != pow(x,5):
        print "the denominator of pow(x, -5) is erroneously ", f
        result += 1

    return result

def exam_paranoia7():
    """
    GiNaC:
    This one was introduced on June 1st 1999 by some aggressive manual
    optimization. Discovered and fixed on June 2nd.

    >>> exam_paranoia7()
    0
    >>>
    """

    result = 0

    x = symbol('x')
    y = symbol('y')

    e = y + y*x + 2
    f = expand(pow(e,2) - (e*y*(x+1)))
    if f.nops() > 3:
        print "e =  y + y*x + 2; f = expand(pow(e,2) - (e*y*(x+1))); f.nops() != 3"
        result += 1

    return result

def exam_paranoia8():
    """
    GiNaC:
    This one was a result of the rewrite of mul::max_coefficient when we
    introduced the overall_coefficient field in expairseq objects on Oct 1st
    1999. Fixed on Oct 4th.

    >>> exam_paranoia8()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    e = -x/(x+1)

    try:
        f = e.normal()
        if f != e:
            print "normal(-x/(x+1)) erroneously returned ", f
            result += 1
    except Exception(e):
        print "normal(-x/(x+1)) erroneously raises ", e
        result += 1

    return result

def exam_paranoia9():
    """
    GiNaC:
    This one was a result of a modification to frac_cancel() & Co. to avoid
    expanding the numerator and denominator when bringing them from Q[X] to
    Z[X]. multiply_lcm() forgot to multiply the x-linear term with the LCM of
    the coefficient's denominators (2 in this case).  Introduced on Jan 25th
    2000 and fixed on Jan 31th.

    >>> exam_paranoia9()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    e = (exp(-x)-2*x*exp(-x)+pow(x,2)/2*exp(-x))/exp(-x)
    f = e.normal()

    if f != 1-2*x+pow(x,2)/2:
        print "normal(",e,") returns ", f, " instead of ", (1-2*x+pow(x,2)/2)
        result += 1

    return result

def exam_paranoia10():
    """
    GiNaC:
    I have no idea when this broke.  It has been working long ago, before 0.4.0
    and on Feb 13th 2000 I found out that things like 2^(3/2) throw an exception
    "power::eval(): pow(0,0) is undefined" instead of simplifying to 2*2^(1/2).
    It was fixed that same day.

    >>> exam_paranoia10()
    0
    >>>
    """
    result = 0

    b = numeric(2)
    e = numeric(3, 2)

    try:
        r = pow(b, e).eval()
        if not (r-2*sqrt(2)).is_zero():
            print "2^(3/2) erroneously returned ", r, " instead of 2*sqrt(2)"
            result += 1
    except Exception(e):
        print "eval(2^(3/2)) raises ", e
        result += 1

    return result

def exam_paranoia11():
    """
    GiNaC:
    After the rewriting of basic::normal() & Co. to return {num, den} lists,
    add::normal() forgot to multiply the denominator of the overall_coeff of
    its expanded and normalized children with the denominator of the expanded
    child (did you get this? Well, never mind...). Fixed on Feb 21th 2000.

    >>> exam_paranoia11()
    0
    >>>
    """
    result = 0
    
    x = symbol('x')
    e = ((-5-2*x)-((2-5*x)/(-2+x))*(3+2*x))/(5-4*x)
    f = e.normal()
    d = (4+10*x+8*pow(x,2))/(x-2)/(5-4*x)

    if (f-d).expand() != 0:
        print "normal(", e, ") returns ", f, " instead of ", d
        result += 1

    return result

def exam_paranoia12():
    """
    GiNaC:
    This one returned 0 because add::normal() incorrectly assumed that if the
    common denominator is 1, all the denominators would be 1 (they can in fact
    be +/-1). Fixed on Aug 2nd 2000.

    >>> exam_paranoia12()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    e = 2-2*(1+x)/(-1-x)
    f = e.normal()
    d = numeric(4)

    if (f-d).expand() != 0:
        print "normal(",e,") returned ", f, " instead of ", d
        result += 1

    return result

def exam_paranoia13():
    """
    GiNaC:
    This one caused a division by 0 because heur_gcd() didn't check its
    input polynomials against 0. Fixed on Aug 4th 2000.

    >>> exam_paranoia13()
    0
    >>>
    """
    result = 0

    a = symbol('a')
    b = symbol('b')
    c = symbol('c')

    e = (b*a-c*a)/(4-a)
    d = (c*a-b*a)/(a-4)

    try:
        f = e.normal()
        if (f-d).expand() != 0:
            print "normal(",e,") returned ",f," instead of ", d
            result += 1
    except Exception(e):
        print "normal(",e,") raises ", e
        result += 1

    return result

def exam_paranoia14():
    """
    GiNaC:
    A bug introduced on July 19, 2001. quo() and rem() would sometimes call
    vector::reserve() with a negative argument. Fixed on Dec 20, 2001.

    >>> exam_paranoia14()
    0
    >>> 
    """
    result = 0

    x = symbol('x')

    q = quo(1, pow(x,3), x)
    if q != 0:
        print "quo(1,x^3,x) erroneously returned ", q, " instead of 0"
        result += 1

    return result

def exam_paranoia15():
    """
    GiNaC:
    Under certain conditions, power::expand_add_2() could produce non-canonical
    numeric expairs. Fixed on Oct 24, 2002.

    >>> exam_paranoia15()
    0
    >>>
    """
    result = 0

    q = pow(pow(2, numeric(1, 2))*2+1, 2).expand()
    # this used to produce "1+4*sqrt(2)+4*2" which would never evaluate
    # to "9+4*sqrt(2)"
    if q-9-4*sqrt(2) != 0:
        print "expand((sqrt(2)*2+1)^2) erroneously returned ", q, " instead of 9+4*sqrt(2)"
        result += 1

    return result

def exam_paranoia16():
    """
    GiNaC:
    Expanding products containing powers of sums could return results that
    were not fully expanded. Fixed on Dec 10, 2003.

    >>> exam_paranoia16()
    0
    >>>
    """
    result = 0

    a = symbol('a')
    b = symbol('b')
    c = symbol('c')
    d = symbol('d')
    e = symbol('e')

    e1 = pow(1+a*sqrt(b+c), 2)
    e2 = e1.expand()
    if e2.has(pow(a, 2)*(b+c)):
        print "expand(", e1, ") did not fully expand"
        result += 1

    e1 = (d*sqrt(a+b)+a*sqrt(c+d))*(b*sqrt(a+b)+a*sqrt(c+d))
    e2 = e1.expand()
    if e2.has(pow(a, 2)*(c+d)):
        print "expand(", e1, ") did not fully expand"
        result += 1

    e1 = (a+sqrt(b+c))*sqrt(b+c)*(d+sqrt(b+c))
    e2 = e1.expand()
    if e2.has(a*(b+c)):
        print "expand(", e1, ") did not fully expand"
        result += 1

    e1 = pow(sqrt(a+b)+sqrt(c+d), 3)
    e2 = e1.expand()
    if e2.has(3*(a+b)*sqrt(c+d)) or e2.has(3*(c+d)*sqrt(a+b)):
        print "expand(", e1, ") did not fully expand"
        result += 1

    e1 = a*(b+c*(d+e))
    e2 = e1.expand()
    if e2.has(c*(d+e)):
        print "expand(", e1, ") did not fully expand"
        result += 1

    e1 = 2*pow(1+a, 2)/a
    e2 = e1.expand()
    if e2.has(pow(a, 2)):
        print "expand(", e1, ") did not fully expand"
        result += 1

    e1 = a*(a+b)
    e2 = pow( pow(e1, -1), -1)
    if e2.has(a*b):
        print "double reciprocal expanded where it should not have"
        result += 1

    return result

if __name__ == "__main__":
    import doctest, sys
 
    doctest.testmod( sys.modules.get( __name__), verbose=True)  
