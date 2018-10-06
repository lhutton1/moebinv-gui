/*
 *  PyGiNaC Copyright (C) 2004 Jonathan Brandmeyer
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <ginac/ginac.h>

#include <boost/python/class.hpp>
#include <boost/python/args.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/overloads.hpp>

#include "pyginac.hpp"

namespace pyginac {

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(convert_to_poly_overloads, convert_to_poly, 0, 1)

void
wrap_series()
{
	using namespace boost::python;
	using GiNaC::ex;
	using GiNaC::pseries;
	
	class_<	pseries, bases<GiNaC::basic> >("pseries", 
			"An extended, truncated power series.")
		.add_property( "var", &pseries::get_var)
		.add_property( "point", &pseries::get_point)
		.def( "is_compatable_to", &pseries::is_compatible_to, 
			"Check whether series is compatible to another series "
			"(expansion variable and point are the same.")
		.def( "is_terminating", &pseries::is_terminating,
			"Returns true if there is no order term")
		.def( "__add__", &pseries::add_series)
		.def( "__mul__", &pseries::mul_const)
		.def( "__mul__", &pseries::mul_series)
		.def( "power_const", &pseries::power_const, (args("n"), "p"),
			"series.power_const(n, p)->pseries\n"
			"Compute the p-th power of a series.")
		.def( "shift_exponents", &pseries::shift_exponents,
			"series.shift_exponents(deg) -> pseries\n"
			"Returns a new pseries object with the powers shifted by deg.")
	        .def( "convert_to_poly", &pseries::convert_to_poly,
                        convert_to_poly_overloads("Convert to ordinary polynomial."))
		;

	implicitly_convertible<pseries, ex>();
}
	
} // !namespace pyginac
