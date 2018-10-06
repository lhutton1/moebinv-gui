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

#include <boost/python/class.hpp>
#include <ginac/expair.h>

namespace pyginac {

void
wrap_expair(void)
{
	using namespace boost::python;
	using GiNaC::expair;
	using GiNaC::ex;
	
	class_<expair>("expair", "A pair of expressions", 
		init<const ex&, const ex&>())
		.def( init<>())
		.def( "is_equal", &expair::is_equal, 
			"Member-wise check for canonical ordering equality.")
		.def( "is_less", &expair::is_less,
			"Member-wise check for canonical ordering lessness.")
		.def( "compare", &expair::compare,
			"Member-wise check for cannocal ordering.")
		.def( "is_canonical_numeric", &expair::is_canonical_numeric,
			"True if this is of the form (numeric,ex(1))." )
		.def( "swap", &expair::swap, "Swap contents with other expair.")
		.def_readwrite( "rest", &expair::rest)
		.def_readwrite( "coeff", &expair::coeff)
		;
}

} // !namespace pyginac
