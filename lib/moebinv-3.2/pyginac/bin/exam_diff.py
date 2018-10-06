#  PyGiNaC  Copyright (C) 2004 Jonathan Brandmeyer

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/examp_differentiaiton.cpp as found in 
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

def check_diff( e, x, d, nth=1):
    ed = e.diff(x, nth)
    if not (ed - d) == 0:
        if nth == 0:
            msg = "zeroth"
            pass
        elif nth == 2:
            msg = "second"
        elif nth == 3:
            msg = "third"
        else:
            msg = "%dth" % nth
            
        print "%s derivative of %s by %s returned %s instead of %s" % msg, e, x, ed, d
        print "returned %s\n instead of %s" % ed, d
        return 1
    return 0

def exam_diff1():
    """
    >>> print exam_diff1()
    0
    >>> 
    """
    x = symbol('x')
    y = symbol('y')
    
    # The accumulated error.
    result = 0
    
    # The function to be differentiated
    e1 = x**-2 * 3 + x**-1 * 5 + 7 + x * 11 + x**2 * 13;
    e2 = y**-2 * 5 + y**-1 * 7 + 11 + y * 13 + y**2 * 17;
    e = (e1*e2).expand()
    
    # de/dx
    d = parse_string( "121-55/x^2-66/x^3-30/x^3/y^2-42/x^3/y-78/x^3*y-102/x^3*y^2-25/x^2/y^2-35/x^2/y-65/x^2*y-85/x^2*y^2+77/y+143*y+187*y^2+130*x/y^2+182/y*x+338*x*y+442*x*y^2+55/y^2+286*x",
        [x , y] )
    result += check_diff(e, x, d)
    
    # de/dy
    d = parse_string("91-30/x^2/y^3-21/x^2/y^2+39/x^2+102/x^2*y-50/x/y^3-35/x/y^2+65/x+170/x*y-77*x/y^2+143*x+374*x*y-130/y^3*x^2-91/y^2*x^2+169*x^2+442*x^2*y-110/y^3*x-70/y^3+238*y-49/y^2",
        [x, y]);
    result += check_diff(e, y, d)
    
    # d^2 e / dx^2:
    d = parse_string("286+90/x^4/y^2+126/x^4/y+234/x^4*y+306/x^4*y^2+50/x^3/y^2+70/x^3/y+130/x^3*y+170/x^3*y^2+130/y^2+182/y+338*y+442*y^2+198/x^4+110/x^3",
        [x, y])
    result += check_diff(e, x, d, 2)
    
    # d^2 e / dy^2:
    d = parse_string("238+90/x^2/y^4+42/x^2/y^3+102/x^2+150/x/y^4+70/x/y^3+170/x+330*x/y^4+154*x/y^3+374*x+390*x^2/y^4+182*x^2/y^3+442*x^2+210/y^4+98/y^3",
        [x, y])
    result += check_diff(e, y, d, 2)
    return result
    
def exam_diff2():
    """
    >>> print exam_diff2()
    0
    """
    result = 0
    x = symbol("x")
    y = symbol("y")
    a = symbol("a")
    b = symbol("b")
    
    # construct expression e to be diff'ed:
    e1 = y*x**2 + a*x + b
    e2 = sin(e1)
    e = b* e2**2 + y*e2 + a
    
    d = 2*b*e2*cos(e1)*(2*x*y + a) + y*cos(e1)*(2*x*y + a)
    result += check_diff(e, x, d)
    
    
    d = (2*b* cos(e1)**2 * (2*x*y + a)**2 + 4*b*y*e2*cos(e1) -
        2*b* e2**2 * (2*x*y + a)**2 - y*e2*(2*x*y + a)**2 +
        2*y**2*cos(e1))
    result += check_diff(e, x, d, 2);
    
    d = 2*b*e2*cos(e1)*x**2 + e2 + y*cos(e1)*x**2
    result += check_diff(e, y, d);

    d = (2*b*cos(e1)**2 * x**4 - 2*b * e2**2 * x**4
        + 2*cos(e1)*x**2 - y*e2*x**4)
    result += check_diff(e, y, d, 2);
    
    # construct expression e to be diff'ed:
    e2 = cos(e1);
    e = b*e2**2 + y*e2 + a
    
    d = -2*b*e2*sin(e1)*(2*x*y + a) - y*sin(e1)*(2*x*y + a)
    result += check_diff(e, x, d)
    
    d = (2*b*sin(e1)**2 * (2*y*x + a)**2 - 4*b*e2*sin(e1)*y 
        - 2*b*e2**2*(2*y*x + a)**2 - y*e2*(2*y*x + a)**2
        - 2*y**2*sin(e1))
    result += check_diff(e, x, d, 2)
    
    d = -2*b*e2*sin(e1)*x**2 + e2 - y*sin(e1)*x**2
    result += check_diff(e, y, d)
    
    d = (-2*b* e2**2 * x**4 + 2*b* sin(e1)**2 * x**4
        - 2*sin(e1)* x**2 - y*e2 * x**4)
    result += check_diff(e, y, d, 2);

    return result;

if __name__ == "__main__":
    import doctest, sys
    doctest.testmod( sys.modules.get( __name__), verbose=True)

    