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
#include <boost/python/def.hpp>

namespace pyginac {

namespace {
GiNaC::ex
get_power_basis( const GiNaC::power& This)
{
    return This.op(0);
}

void
set_power_basis( GiNaC::power& This, const GiNaC::ex& op)
{
    This[0] = op;
}

GiNaC::ex
get_power_exponent( const GiNaC::power& This)
{
    return This.op(1);
}

void
set_power_exponent( GiNaC::power& This, const GiNaC::ex& op)
{
    This[1] = op;
}

GiNaC::ex
sqrt_noninline(const GiNaC::ex& e)
{
  return sqrt(e);
}


} // !namespace (unnamed)

void
wrap_power(void)
{
    using namespace boost::python;
    using GiNaC::power;

    class_<power, bases<GiNaC::basic> >( "power", "Exponentiation expressions",
        init<const GiNaC::ex&, const GiNaC::ex&>())
        .def( init<const power&>())
        .add_property( "basis", get_power_basis)
        .add_property( "exponent", get_power_exponent)
        ;

    implicitly_convertible<power, GiNaC::ex>();

	def("sqrt", sqrt_noninline);
}


} // !namespace pyginac
