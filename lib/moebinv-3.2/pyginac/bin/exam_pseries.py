#  Regression tests for PyGiNaC (C) 2005 Matti Peltomaki

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/exam_pseries.cpp as found in 
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

def check_series(e, point, d, order = 8):
    es = e.series(point, order)
    ep = es.convert_to_poly()
    if (ep-d).expand() != 0:
        print "series expansion of ", e, " at ", point
        print "erroneously returned ", ep, " instead of ", d
        return 1
    return 0

def exam_pseries1():
    """
    >>> exam_pseries1()
    0
    >>>
    """
    result = 0

    a = symbol('a')
    b = symbol('b')
    x = symbol('x')

    e = pow(a+b, x)
    d = 1 + Order(pow(x,1))
    result += check_series(e, x==0, d, 1)

    e = sin(x)
    d = x - pow(x, 3) / 6 + pow(x, 5) / 120 - pow(x, 7) / 5040 + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = cos(x)
    d = 1 - pow(x, 2) / 2 + pow(x, 4) / 24 - pow(x, 6) / 720 + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = exp(x)
    d = 1 + x + pow(x, 2) / 2 + pow(x, 3) / 6 + pow(x, 4) / 24
    d += pow(x, 5) / 120 + pow(x, 6) / 720 + pow(x, 7) / 5040 + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = pow(1 - x, -1)
    d = 1 + x + pow(x, 2) + pow(x, 3) + pow(x, 4) + pow(x, 5) + pow(x, 6)
    d += pow(x, 7) + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = x + pow(x, -1)
    d = x + pow(x, -1)
    result += check_series(e, x==0, d)
	
    e = x + pow(x, -1)
    d = 2 + pow(x-1, 2) - pow(x-1, 3) + pow(x-1, 4) - pow(x-1, 5)
    d += pow(x-1, 6) - pow(x-1, 7) + Order(pow(x-1, 8))
    result += check_series(e, x==1, d)
	
    e = pow(x + pow(x, 3), -1)
    d = pow(x, -1) - x + pow(x, 3) - pow(x, 5) + pow(x, 7) + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = pow(pow(x, 2) + pow(x, 4), -1)
    d = pow(x, -2) - 1 + pow(x, 2) - pow(x, 4) + pow(x, 6) + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = pow(sin(x), -2)
    d = pow(x, -2) + numeric(1,3) + pow(x, 2) / 15 + pow(x, 4) * 2/189
    d += pow(x, 6) / 675  + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = sin(x) / cos(x)
    d = x + pow(x, 3) / 3 + pow(x, 5) * 2/15 + pow(x, 7) * 17/315 + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = cos(x) / sin(x);
    d = pow(x, -1) - x / 3 - pow(x, 3) / 45 - pow(x, 5) * 2/945
    d += - pow(x, 7) / 4725 + Order(pow(x, 8))
    result += check_series(e, x==0, d)
	
    e = pow(numeric(2), x);
    t = log(2) * x;
    d = 1 + t + pow(t, 2) / 2 + pow(t, 3) / 6 + pow(t, 4) / 24
    d += pow(t, 5) / 120 + pow(t, 6) / 720 + pow(t, 7) / 5040 + Order(pow(x, 8))
    result += check_series(e, x==0, d.expand())
	
    e = pow(Pi, x)
    t = log(Pi) * x
    d = 1 + t + pow(t, 2) / 2 + pow(t, 3) / 6 + pow(t, 4) / 24
    d += pow(t, 5) / 120 + pow(t, 6) / 720 + pow(t, 7) / 5040 + Order(pow(x, 8))
    result += check_series(e, x==0, d.expand())
	
    e = log(x)
    d = e
    result += check_series(e, x==0, d, 1)
    result += check_series(e, x==0, d, 2)
	
    e = pow(x, 8) * pow(pow(x,3)+ pow(x + pow(x,3), 2), -2)
    d = pow(x, 4) - 2*pow(x, 5) + Order(pow(x, 6))
    result += check_series(e, x==0, d, 6)
	
    e = cos(x) * pow(sin(x)*(pow(x, 5) + 4 * pow(x, 2)), -3)
    d = pow(x, -9) / 64 - 3 * pow(x, -6) / 256 - pow(x, -5) / 960
    d += 535 * pow(x, -3) / 96768 + pow(x, -2) / 1280 - pow(x, -1) / 14400
    d += - numeric(283, 129024) - 2143 * x / 5322240 + Order(pow(x, 2))
    result += check_series(e, x==0, d, 2)
	
    e = sqrt(1+x*x) * sqrt(1+2*x*x)
    d = 1 + Order(pow(x, 2))
    result += check_series(e, x==0, d, 2)

    e = pow(x, 4) * sin(a) + pow(x, 2)
    d = pow(x, 2) + Order(pow(x, 3))
    result += check_series(e, x==0, d, 3)

    e = log(a*x + b*x*x*log(x))
    d = log(a*x) + b/a*log(x)*x - pow(b/a, 2)/2*pow(log(x)*x, 2) + Order(pow(x, 3))
    result += check_series(e, x==0, d, 3)

    e = pow((x+a), b)
    d = pow(a, b) + (pow(a, b)*b/a)*x
    d += (pow(a, b)*b*b/a/a/2 - pow(a, b)*b/a/a/2)*pow(x, 2) + Order(pow(x, 3));
    result += check_series(e, x==0, d, 3)

    return result

def exam_pseries2():
    """
    Series addition

    >>> exam_pseries2()
    0
    >>>
    """
    result = 0

    x = symbol('x')

    e = pow(sin(x), -1).series(x==0, 8) + pow(sin(-x), -1).series(x==0, 12)
    d = Order(pow(x, 8))
    result += check_series(e, x==0, d)

    return result

def exam_pseries3():
    """
    Series multiplication

    >>> exam_pseries3()
    0
    >>>
    """
    result = 0

    x = symbol('x')

    e = sin(x).series(x==0, 8) * pow(sin(x), -1).series(x==0, 12)
    d = 1 + Order(pow(x, 7))
    result += check_series(e, x==0, d)

    return result

def exam_pseries4():
    """
    Series exponentation

    >>> exam_pseries4()
    0
    >>>
    """
    result = 0

    x = symbol('x')

    e = pow((2*cos(x)).series(x==0, 5), 2).series(x==0, 5)
    d = 4 - 4*pow(x, 2) + 4*pow(x, 4)/3 + Order(pow(x, 5))
    result += check_series(e, x==0, d)

    e = pow(tgamma(x), 2).series(x==0, 2)
    d = pow(x,-2) - 2*Euler/x + (pow(Pi,2)/6+2*pow(Euler,2)) 
    d += x*(-4*pow(Euler, 3)/3 -pow(Pi,2)*Euler/3 - 2*zeta(3)/3) + Order(pow(x, 2));
    result += check_series(e, x==0, d);

    return result 

def exam_pseries5():
    """
    Orer term handling

    >>> exam_pseries5()
    0
    >>>
    """
    result = 0

    x = symbol('x')

    e = 1 + x + pow(x, 2) + pow(x, 3)
    d = Order(1)
    result += check_series(e, x==0, d, 0)

    d = 1 + Order(x)
    result += check_series(e, x==0, d, 1)
    
    d = 1 + x + Order(pow(x, 2))
    result += check_series(e, x==0, d, 2)
    
    d = 1 + x + pow(x, 2) + Order(pow(x, 3))
    result += check_series(e, x==0, d, 3)
    
    d = 1 + x + pow(x, 2) + pow(x, 3)
    result += check_series(e, x==0, d, 4)
    
    return result

def exam_pseries6():
    """
    Series expansion of tgamma(-1)

    >>> exam_pseries6()
    0
    >>>
    """
    x = symbol('x')
    
    e = tgamma(2*x)
    factors = [numeric(1,4),
               numeric(3,4) - numeric(1,2)*Euler,
               numeric(7,4) -
               numeric(3,2)*Euler +
               numeric(1,2)*pow(Euler,2) +
               numeric(1,12)*pow(Pi,2),
               numeric(15,4) -
               numeric(7,2)*Euler -
               numeric(1,3)*pow(Euler,3) +
               numeric(1,4)*pow(Pi,2) +
               numeric(3,2)*pow(Euler,2) -
               numeric(1,6)*pow(Pi,2)*Euler -
               numeric(2,3)*zeta(3),
               numeric(31,4) - pow(Euler,3) -
               numeric(15,2)*Euler +
               numeric(1,6)*pow(Euler,4) +
               numeric(7,2)*pow(Euler,2) +
               numeric(7,12)*pow(Pi,2) -
               numeric(1,2)*pow(Pi,2)*Euler -
               numeric(2)*zeta(3) +
               numeric(1,6)*pow(Euler,2)*pow(Pi,2) +
               numeric(1,40)*pow(Pi,4) +
               numeric(4,3)*zeta(3)*Euler]

    ps = [pow(x+1,i) for i in range(-1,4)]
    d = sum([f*p for f,p in zip(factors, ps)]) + Order(pow(x+1,4))

    return check_series(e, x==-1, d, 4)

def exam_pseries7():
    """
    Series expansion of tan(x==Pi/2)

    >>> exam_pseries7()
    0
    >>>
    """
    x = symbol('x')

    e = tan(x*Pi/2)
    d = pow(x-1,-1)/Pi*(-2) + pow(x-1,1)*Pi/6 + pow(x-1,3)*pow(Pi,3)/360
    d += pow(x-1,5)*pow(Pi,5)/15120 + pow(x-1,7)*pow(Pi,7)/604800
    d += Order(pow(x-1,9))
    return check_series(e, x==1, d, 9)

def exam_pseries8():
    """
    Series expansion of log(sin(x==0))

    >>> exam_pseries8()
    0
    >>>
    """
    x = symbol('x')

    e = log(sin(x))
    d = log(x) - pow(x,2)/6 - pow(x,4)/180 - pow(x,6)/2835 - pow(x,8)/37800 + Order(pow(x,9))
    return check_series(e, x==0, d, 9)

def exam_pseries9():
    """
    Series expansion of Li2(sin(x==0))

    >>> exam_pseries9()
    0
    >>>
    """
    x = symbol('x')

    e = Li2(sin(x))
    d = x + pow(x,2)/4 - pow(x,3)/18 - pow(x,4)/48
    d += - 13*pow(x,5)/1800 - pow(x,6)/360 - 23*pow(x,7)/21168
    d += Order(pow(x,8))
    return check_series(e, x==0, d, 8)

def exam_pseries10():
    """
    Series expansion of Li2((x==2)^2), caring about branch-cut

    >>> exam_pseries10()
    0
    >>>
    """
    x = symbol('x')

    e = Li2(pow(x,2))
    d = Li2(4) + (-log(3) + I*Pi*csgn(I-I*pow(x,2))) * (x-2)
    d += (numeric(-2,3) + log(3)/4 - I*Pi/4*csgn(I-I*pow(x,2))) * pow(x-2,2)
    d += (numeric(11,27) - log(3)/12 + I*Pi/12*csgn(I-I*pow(x,2))) * pow(x-2,3)
    d += (numeric(-155,648) + log(3)/32 - I*Pi/32*csgn(I-I*pow(x,2))) * pow(x-2,4)
    d += Order(pow(x-2,5))
    return check_series(e, x==2, d, 5)

def exam_pseries11():
    """
    Series expansion of logarithms around branch points

    >>> exam_pseries11()
    0
    >>> 
    """
    result = 0

    a = symbol('a')
    x = symbol('x')

    e = log(x)
    d = log(x)
    result += check_series(e, x==0, d, 5)

    e = log(3/x)
    d = log(3)-log(x)
    result += check_series(e, x==0, d, 5)
    
    e = log(3*pow(x,2))
    d = log(3)+2*log(x)
    result += check_series(e, x==0, d, 5)

    # These ones must not be expanded because it would result in a branch cut
    # running in the wrong direction. (Other systems tend to get this wrong.)
    e = log(-x)
    d = e
    result += check_series(e, x==0, d, 5)

    e = log(I*(x-123))
    d = e
    result += check_series(e, x==123, d, 5)

    e = log(a*x)
    d = e  # we don't know anything about a!
    result += check_series(e, x==0, d, 5)

    e = log((1-x)/x)
    d = log(1-x) - (x-1) + pow(x-1,2)/2 - pow(x-1,3)/3  + pow(x-1,4)/4 + Order(pow(x-1,5))
    result += check_series(e, x==1, d, 5)

    return result

def exam_pseries12():
    """
    Series expansion of other functions areound branch points

    >>> exam_pseries12()
    0
    >>>
    """
    result = 0

    x = symbol('x')

    # NB: Mma and Maple give different results, but they agree if one
    # takes into account that by assumption |x|<1.
    e = atan(x)
    d = (I*log(2)/2-I*log(1+I*x)/2) + (x-I)/4 + I*pow(x-I,2)/16 + Order(pow(x-I,3))
    result += check_series(e, x==I, d, 3)

    # NB: here, at -I, Mathematica disagrees, but it is wrong -- they
    # pick up a complex phase by incorrectly expanding logarithms.
    e = atan(x)
    d = (-I*log(2)/2+I*log(1-I*x)/2) + (x+I)/4 - I*pow(x+I,2)/16 + Order(pow(x+I,3))
    result += check_series(e, x==-I, d, 3)

    # This is basically the same as above, the branch point is at +/-1:
    e = atanh(x)
    d = (-log(2)/2+log(x+1)/2) + (x+1)/4 + pow(x+1,2)/16 + Order(pow(x+1,3))
    result += check_series(e, x==-1, d, 3)

    return result

if __name__ == "__main__":  
    import doctest, sys 

    doctest.testmod( sys.modules.get( __name__), verbose=True)  
