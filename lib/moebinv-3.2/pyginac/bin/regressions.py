"""
    The following expressions should not simplify automatically.

>>> assert isinstance(numeric(0) == numeric(0), relational) == True

>>> assert isinstance( numeric(0) <= numeric(0), relational) == True

>>> assert isinstance( numeric(0) != numeric(1), relational) == True

>>> assert isinstance( numeric(0) >= numeric(0), relational) == True

>>> assert isinstance( numeric(0) < numeric(1), relational) == True

>>> assert isinstance( numeric(0) > numeric(-1), relational) == True

    Trig functions (and others) are only implemented for expression arguments.
    Taking the cosine of an integer should not evaluate the expression right
    away.

>>> assert isinstance( cos(1), function) == True

"""


#  PyGiNaC  Copyright (C) 2004, 2005 Jonathan Brandmeyer

#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, version 2.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

# Some basic regression tests.

from ginac import *


if __name__ == "__main__":
    import doctest, sys
    doctest.testmod( sys.modules.get( __name__), verbose=True)

    