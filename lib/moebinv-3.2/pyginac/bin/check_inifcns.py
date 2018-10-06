#  PyGiNaC  Copyright (C) 2004 Jonathan Brandmeyer
#  These tests were adapted from check/check_inifcns.cpp as found in GiNaC
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
from random import random

def inifcns_check_sin():
    """
    >>> inifcns_check_sin()
    Passed sine checks.
    """
    error = False
    # sin(n*Pi) == 0?
    for n in range(-10, 10):
        expr = sin(n*Pi).eval()
        if expr != 0 \
            or not expr.is_integer():
                error = True
                print "sin(n*Pi) with integer n does not always return exact 0"
    
    # sin((n+1/2)*Pi) == {+|-}1?
    for n in range( -10, 10):
        expr = sin((n+numeric(1,2))*Pi).eval()
        if not (expr == 1 or expr == -1) \
            or not expr.is_integer():
                error = True
                print "sin((n+1/2)*Pi) with integer n does not always return exact {+|-}1"
    # compare sin((q*Pi).evalf()) with sin(q*Pi).eval().evalf()
    epsilon = numeric(1.0e-8)
    for n in range( -340, 340):
        arg = n*Pi/60
        if abs( sin( evalf(arg)) - evalf( sin( arg))) > epsilon:
            error = True
            print "sin(", arg, ") returns ", sin(arg).evalf()
    if not error:
        print "Passed sine checks."
    else:
        print "Failed sine checks."

def inifcns_check_cos():
    """
    >>> inifcns_check_cos()
    Passed cosine checks.
    """
    error = False
    for n in range( -10, 10):
        expr = cos((n+numeric(1)/2) * Pi).eval()
        if expr != 0 or not expr.is_integer():
            error = True
            print "cos((n+1/2)*Pi) with integer n does not always return exact 0"
        expr = cos(n*Pi).eval()
        if not (expr == 1 or expr == -1) \
            or not expr.is_integer():
                error = True
                print "cos(n*Pi) with integer n does not always return exact {+|-}1"
    
    epsilon = numeric(1.0e-8)
    for n in range( -340, 340):
        arg = n*Pi/60
        if abs(cos(evalf(arg)) - cos(arg).evalf()) > epsilon:
            error = True
            print "cos(", arg, ") returns", cos(arg).evalf()
    if not error:
        print "Passed cosine checks."
    else:
        print "Failed cosine checks."

def inifcns_check_tan():
    """
    >>> inifcns_check_tan()
    Passed tangent checks.
    """
    error = False
    epsilon = numeric(1.0e-8)
    for n in range( -340, 340):
        if not n%30 and n%60: 
            # skip poles
            continue
        arg = n*Pi/60
        if abs(tan(evalf(arg)) - tan(arg).evalf()) > epsilon:
            error = True
            print "cos(", arg, ") returns", cos(arg).evalf()
    if not error:
        print "Passed tangent checks."
    else:
        print "Failed tangent checks."

def inifcns_check_Li2():
    """
    >>> inifcns_check_Li2()
    Passed dilogarithm checks.
    """
    error = False
    # check the relation Li2(z^2) == 2 * (Li2(z) + Li2(-z)) numerically, which
    # should hold in the entire complex plane:
    epsilon = numeric( 1.0e-16)
    for n in range( 200):
        # A number from -10 -> +10 in the complex plane.
        argument = numeric(20.0*random()-10.0) + numeric(20.0*random()-10.0)*I
        if abs(Li2(argument**2)-2*Li2(argument)-2*Li2(-argument)) > epsilon:
            print "Li2(z) at z==", argument, "failed to satisfy Li2(z^2)==2*(Li2(z)+Li2(-z))"
            error = True
    if not error:
        print "Passed dilogarithm checks."
    else:
        print "Failed dilogarithm checks."
    
if __name__ == "__main__":
    import doctest, sys
    doctest.testmod( sys.modules.get( __name__), verbose=True)
