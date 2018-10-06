#  PyGiNaC  Copyright (C) 2004 Jonathan Brandmeyer
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; version 2.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

# This program will run all of the tests currently available for PyGiNaC,
# and mostly just serves as a convenience over running the tests individually.

import doctest, sys
import check_inifcns, check_lsolve, check_matricies, check_numeric
import exam_diff, exam_lsolve, exam_matrices, exam_normalization
import exam_misc, exam_paranoia, exam_polygcd
import exam_powerlaws, exam_pseries, regressions

# Since the check_* test suites introduce a random number of new symbols,
# and the serial numbers of the symbols affect canonical ordering in GiNaC,
# the check_* suites have to be run after the exam_* ones, some of which
# rely on a particular canonical ordering.

for mod in [exam_diff, exam_lsolve, exam_matrices, exam_misc, exam_normalization,
	    exam_paranoia, exam_polygcd, exam_powerlaws, exam_pseries,
	    regressions,
	    check_inifcns, check_lsolve, check_matricies, check_numeric]:
        fails, attempts = doctest.testmod( mod)
        if fails == 0:
            print "All tests passed in bin/%s.py" % mod.__name__
        # else:
        #   doctest.testmod() displayed the errors.
