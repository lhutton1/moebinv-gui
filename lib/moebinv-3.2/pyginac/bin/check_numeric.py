#  PyGiNaC  Copyright (C) 2004 Jonathan Brandmeyer
#  These tests were adapted from check/check_numeric.cpp as found in GiNaC
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
from random import randrange
import sys

def check_numeric1():
    """
    >>> check_numeric1()
    Basic consistency checks passed.
    """
    error = False
    # Check some numerator and denominator calcs
    for rep in range(200):
        re_q = randrange(1, sys.maxint)
        im_q = randrange(1, sys.maxint)
        r = numeric( randrange(-sys.maxint-1, sys.maxint), re_q)
        i = numeric( randrange(-sys.maxint-1, sys.maxint), im_q)
        z = r + I*i
        p = numer(z)
        q = denom(z)
        res = p/q
        if res != z:
            error = True
            print z, "erroneously transformed into ", p, "/", q, \
                "by numer() and denom()"
    if error:
        print "Basic consistency checks failed."
    else:
        print "Basic consistency checks passed."

def check_numeric2():
    """
    >>> check_numeric2()
    Basic consistency checks passed.
    """
    error = False
    # Check non-nested radicals (n/d)^(m/n) in ex wrapper class
    for i in range(200):
        for j in range( 2, 13):
            # construct an exponent 1/j...
            nm = numeric(1)/j
            nm += randrange( -10, 10)
            # a numerator
            i_num = randrange(1, sys.maxint)
            num = numeric(i_num)
            # and a denominator
            i_den = randrange(1, sys.maxint)
            den = numeric(i_den)
            # construct the radicals
            radical = (num/den)**nm
            if radical.__class__ == numeric:
                # This should be very unlikely, it is probably a power object.
                if radical**nm.inverse() == num/den:
                    # These aren't the numbers you're looking for.  Move along.
                    pass
                else:
                    print "(", num, "/", den, ")**(", nm, \
                        ") erroneously returned:", radical
                    print "when it should have returend a power or product"
                    error = True
            # Note: The remaining parts of this test as found in GiNaC are not repeatable
            # with PyGiNaC's interface - this is intentional.
    if error:
        print "Basic consistency checks failed."
    else:
        print "Basic consistency checks passed."

if __name__ == "__main__":
    import doctest, sys
    doctest.testmod( sys.modules.get( __name__), verbose=True)

