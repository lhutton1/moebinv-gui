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
#include <boost/python/implicit.hpp>
#include "pyginac.hpp"

namespace pyginac {
namespace {
int get_max_integration_level( const GiNaC::integral&)
{
    return GiNaC::integral::max_integration_level; 
}

void set_max_integration_level( const GiNaC::integral&, int level)
{
    GiNaC::integral::max_integration_level = level; 
}

GiNaC::ex get_relerr( const GiNaC::integral&)
{
    return GiNaC::integral::relative_integration_error;
}

void set_relerr( const GiNaC::integral&, const GiNaC::basic& err)
{
    GiNaC::integral::relative_integration_error = err;
}

} // !namespace unnamed


void
wrap_integral(void)
{
    using GiNaC::integral;
    using GiNaC::ex;
    using namespace boost::python;  
    
    class_<integral, bases<GiNaC::basic> >( "integral", "a symbolic definate integral.",
        init<const ex&, const ex&, const ex&, const ex&>(args("dx", "lower", "upper", "f" )))
        .def( init<const integral&>())
        .add_property( "max_integration_level", 
            get_max_integration_level, set_max_integration_level)
        .add_property( "relative_integration_error", get_relerr, set_relerr)
        ;

    implicitly_convertible<integral, ex>();
}

} // !namespace pyginac
