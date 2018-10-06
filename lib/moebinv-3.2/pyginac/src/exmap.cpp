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

#include <boost/python/dict.hpp>
#include <boost/python/to_python_converter.hpp>

namespace pyginac {

// TODO: Implicit conversion from boost::python::dict 
//  -> std::map<ex, ex, ex_is_less>

// Implicit conversion from GiNaC::exmap -> dict { ex : ex }
namespace {
struct exmap_to_python
{
    static PyObject* convert( const GiNaC::exmap& obj)
    {
        boost::python::dict ret;
        GiNaC::exmap::const_iterator i = obj.begin();
        GiNaC::exmap::const_iterator i_end = obj.end();
        while (i != i_end) {
             ret[i->first] = i->second;
             ++i;
        }
        Py_INCREF(ret.ptr());
        return ret.ptr();
    }
};
} // !namespace anonymous

void
wrap_exmap(void)
{
    boost::python::to_python_converter<GiNaC::exmap, exmap_to_python>();
}

} // !namespace pyginac
