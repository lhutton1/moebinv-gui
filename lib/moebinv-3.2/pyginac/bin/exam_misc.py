#  Regression tests for PyGiNaC (C) 2005 Matti Peltomaki

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/exam_misc.cpp as found in 
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

def exam_expand_subs():
    """
    >>> exam_expand_subs()
    0
    >>>
    """
    result = 0
    vecsize = 30

    l = []
    e = 0
    for i in range(vecsize):
        newsymb = symbol("a" + str(i))
        l.append(newsymb)
        e = e + newsymb
    aux = -e + l[0] + l[1]
    e = pow(e, 2).expand().subs(l[0] == aux).expand()
    if(e != pow(l[1], 2)):
        print "Denny Fliegner's quick consistency check returned ", e
        result = 1

    return result

def exam_expand_subs2():
    """
    >>> exam_expand_subs2()
    0
    >>> 
    """
    result = 0
    
    a = symbol('a')
    b = symbol('b')
    e = pow(a+b,200).expand()
    f = e.subs(a == -b)
    if(f != 0):
        print "e = pow(a+b,200).expand(); f = e.subs(a == -b); erroneously returned", f
        result = 1

    return result

def exam_expand_power():
    """
    >>> exam_expand_power()
    0
    >>> 
    """
    result = 0

    x = symbol('x')
    a = symbol('a')
    b = symbol('b')

    e = pow(x,pow(a+b,2)-pow(a,2)-pow(b,2)-a*b*2).expand()
    if( e != 1):
        print "pow(x,pow(a+b,2)-pow(a,2)-pow(b,2)-a*b*2).expand() returned ", e
        result += 1

    return result

def exam_sqrfree():
    """
    >>> exam_sqrfree()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')

    e1 = (1+x)*pow((2+x),2)*pow((3+x),3)*pow((4+x),4);
    e2 = sqrfree(e1.expand(), [x]);
    if(e1 != e2):
        print "sqrfree(expand(",e1,")) erroneously returned ", e2;
        result += 1

    e1 = (x+y)*pow((x+2*y),2)*pow((x+3*y),3)*pow((x+4*y),4);
    e2 = sqrfree(e1.expand());
    if (e1 != e2):
        print "sqrfree(expand(", e1, ")) erroneously returned ", e2
        result += 1

    e2 = sqrfree(e1.expand(),[x])
    if (e1 != e2):
        print "sqrfree(expand(", e1, "),[x]) erroneously returned ", e2
        result += 1
        
    e2 = sqrfree(e1.expand(),[y])
    if (e1 != e2):
        print "sqrfree(expand(", e1, "),[y]) erroneously returned ", e2
        result += 1

    e2 = sqrfree(e1.expand(),[x,y])
    if (e1 != e2):
        print "sqrfree(expand(", e1, "),[x,y]) erroneously returned ", e2
        result += 1
        
    return result

def exam_subs():
    """
    >>> exam_subs()
    0
    >>> 
    """
    result = 0

    x = symbol('x')
    
    e1 = x+1
    e2 = e1.subs(x == x-1)
    if(e2 != x):
        print "(x+1).subs(x==x-1) erroneously returned ", e2, " instead of x"
        result += 1

    e1 = sin(1+sin(x));
    e2 = e1.subs(sin(wild()) == cos(wild()))
    if(e2 != cos(1+cos(x))):
        print "sin(1+sin(x)).subs(sin($1)==cos($1)) erroneously returned "
        print e2, " instead of cos(1+cos(x))"
        result += 1

    return result

def exam_joris():
    """
    >>> exam_joris()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    e = expand(pow(x,x-1) * x)
    if(e != pow(x,x)):
        print "x^(x-1)*x did not expand to x^x"
        result += 1

    return result

def exam_subs_algebraic():
    """
    >>> exam_subs_algebraic()
    0
    >>>
    """
    result = 0

    x = symbol('x')
    y = symbol('y')

    e = (x**3 * y**2).subs(x*y == 2, subs_options.algebraic)
    if(e != 4*x):
        print "(x**3 * y**2).subs(x*y == 2, subs_options.algebraic) returned ", e
        result += 1

    e = (x**5).subs(x*x == y, subs_options.algebraic)
    if(e != y**2 * x):
        print "(x**5).subs(x*x == y, subs_options.algebraic) returned", e
        result += 1

    return result

if __name__ == "__main__":  
    import doctest, sys 
 
    doctest.testmod( sys.modules.get( __name__), verbose=True)  
