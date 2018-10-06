#  Regression tests for PyGiNaC 

#  This file may be redistributed under the terms of the GNU General Public
#  License as published by the Free Software Foundation, version 2.

#  These tests were adapted from check/exam_lsolve.cpp as found in 
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

def exam_lsolve1():
    """A trivial example.
    >>> print(exam_lsolve1())
    1
    >>> 
    """
    
    x = symbol('x'); 
    eq = (3*x+5 == numeric(8));
    solution = lsolve([eq], [x])
    return (solution[x] - 1).is_zero()

def exam_lsolve2a():
    """An example from the Maple online help.
    >>> print(exam_lsolve2a())
    1
    >>>
    """

    a = symbol('a');
    b = symbol('b');
    x = symbol('x');
    y = symbol('y');
    eqns = [a*x + b*y == 3, x-y==b];
    solution = lsolve(eqns, [x,y]);
    solx = solution[x];
    soly = solution[y];
    realx = (3+pow(b,2))/(a+b);
    realy = (3-a*b)/(a+b);
    return (solx-realx).normal().is_zero() and (soly-realy).normal().is_zero() 

def exam_lsolve2b():
    """A boring example from Mathematica's online help.
    >>> print(exam_lsolve2b())
    0
    >>>
    """
    result = 0
    x = symbol('x')
    y = symbol('y')
    eqns = [3*x+y==7, 2*x-5*y==8]
    solution = lsolve(eqns, [x,y])
    solx = solution[x]
    soly = solution[y]
    # It should have returned x==43/17 and y==-10/17
    if(solx != numeric(43,17) or soly != numeric(-10,17)):
        result = 1
        print "solution of the system ", [str(item) for item in eqns], " for [x,y] "
        print "erronously returned ", [str(item) for item in solution]
    return result;

def exam_lsolve2c():
    """A more interesting example from the Maple online help.
    >>> print(exam_lsolve2c())
    0
    >>>
    """
    result = 0
    x = symbol('x')
    y = symbol('y')
    eqns = [I*x+y == 1, I*x-y == 2]
    solution = lsolve(eqns, [x,y])
    solx = solution[x]
    soly = solution[y]
    # It should have returned x == -3/2*I and y == -1/2
    if(solx != numeric(-3,2)*I or soly != numeric(-1,2)):
        result = 1
        print "solution of the system ", [str(item) for item in eqns], " for [x,y] "
        print "erroneously returned ", [str (item) for item in solution]
    return result

def exam_lsolve2S():
    """A degenerate example that has gone wrong in GiNaC
    in the past.
    >>> print(exam_lsolve2S())
    0
    >>>
    """
    result = 0
    x = symbol('x')
    y = symbol('y')
    t = symbol('t')
    eqns = [0*x + 0*y == 0, 0*x + 1*y == t]
    solution = lsolve(eqns, [x,y])
    solx = solution[x]
    soly = solution[y]
    # It should have returned x==x, y==t
    if(solx != x or soly != t):
        result = 1
        print "solution of the system ", [str(item) for item in eqns], " for [x,y]"
        print "erroneously returned ", [str(item) for item in solution]
    return result

def exam_lsolve3S():
    """Another degenerate example that has gine wrong in GiNaC in the past.
    >>> print(exam_lsolve3S())
    0
    >>>
    """
    result = 0
    b = symbol('b')
    c = symbol('c')
    x = symbol('x')
    y = symbol('y')
    z = symbol('z')

    # Create the linear system [y+z==b, -y+z==b] with an additional row
    eqns = [numeric(0) == numeric(0), b == z + y, -y+z == c]
    # Solve it for [x,y,z]
    solution = lsolve(eqns, [x,y,z])
    solx = solution[x]
    soly = solution[y]
    solz = solution[z]
    
    if(solx != x or soly != (b-c)/2 or solz != (b+c)/2):
        result = 1
        print "solution of the system ", [str(item) for item in eqns], " for [x,y,z]"
        print "erroneously returned ", [str(item) for item in solution]
    return result

if __name__ == "__main__":
    import doctest, sys
    doctest.testmod( sys.modules.get( __name__), verbose=True)
