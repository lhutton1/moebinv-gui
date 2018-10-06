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
#include <boost/python/operators.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/def.hpp>

namespace pyginac {

void
wrap_constant(void)
{
	using namespace boost::python;
	using GiNaC::constant;
	using GiNaC::basic;
	using GiNaC::evalffunctype;
	using GiNaC::numeric;
	using GiNaC::ex;
	using GiNaC::symbol;
	
	class_<constant, bases<basic> >( "constant", "A symbol with specific value.",
		init< const std::string&, double>())
		// Wrapping ex::operator() fails.
		// .def( init< const std::string&, 
		// 	optional<
		// 		evalffunctype, 
		// 		const std::string&> >())
		.def( init< const std::string&,
			optional<
				const numeric&,
				const std::string&> >())
		.def( init< const std::string&, int>())
        .def( init< const constant&>())
		;
		
	implicitly_convertible< constant, GiNaC::ex>();
}

} // !namespace pyginac
