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
#include <boost/python/enum.hpp>

#include <string>

#include "pyginac.hpp"

namespace pyginac {
namespace {
enum domain
{
    complex = GiNaC::domain::complex,
    real = GiNaC::domain::real,
    possymbol = GiNaC::domain::positive
};
} // !namespace (unnamed)

void
wrap_symbol(void)
{
	using namespace boost::python;
	using GiNaC::symbol;
	using GiNaC::basic;
	using GiNaC::constant;
	using GiNaC::numeric;
	using GiNaC::ex;

    enum_<domain>("domain")
        .value( "complex", complex)
        .value( "real", real)
        .value( "possymbol", possymbol)
        ;
	
	class_<symbol, bases<basic> >("symbol", "An algebraic symbol.", init<std::string>())
		.def( init<std::string, std::string>())
		.def( init<const symbol&>())
		.def( init<>())
		.def( "set_name", &symbol::set_name, "Set the name of the symbol")
		.def( "set_TeX_name", &symbol::set_TeX_name, "Set the name of the symbol")
		.add_property( "name", &symbol::get_name, &symbol::set_name)
		.add_property( "TeX_name", &symbol::get_name, &symbol::set_name)
		;

    class_<GiNaC::realsymbol, bases<symbol, basic> >("realsymbol",
        "An algebraic symbol over the real domain.", init<std::string>())
        .def( init<std::string, std::string>())
        .def( init<const GiNaC::realsymbol&>())
        ;
		
    class_<GiNaC::possymbol, bases<GiNaC::realsymbol, symbol, basic> >("possymbol",
        "An algebraic symbol over the real domain.", init<std::string>())
        .def( init<std::string, std::string>())
        .def( init<const GiNaC::possymbol&>())
        ;

	implicitly_convertible<symbol, ex>();
    implicitly_convertible<GiNaC::realsymbol, ex>();
    implicitly_convertible<GiNaC::possymbol, ex>();
}

} // !namespace pyginac
