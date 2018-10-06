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

#include <boost/python/args.hpp>
#include <boost/python/class.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/overloads.hpp>

namespace pyginac {

namespace {

BOOST_PYTHON_FUNCTION_OVERLOADS(wild_overload, GiNaC::wild, 0, 1)

} // !namespace (unnamed)

void
wrap_wildcard(void)
{
    using namespace boost::python;
    using GiNaC::wildcard;
    
    class_<wildcard, bases<GiNaC::basic> >( "wildcard", 
	"Wildcard for matching and substitution", 
        init<>())
        .def( init<unsigned>())
        .def( init<const wildcard&>())
	.add_property( "label", &wildcard::get_label)
	;

    implicitly_convertible<wildcard, GiNaC::ex>();

    def("wild", GiNaC::wild, 
	wild_overload(args("label"), "Generate a wildcard with the optionally given label"));

    def("haswild", GiNaC::haswild, "Check if the expression contains a wildcard");

}

} // !namespace pyginac
