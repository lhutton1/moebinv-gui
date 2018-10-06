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
#include <boost/python/call_method.hpp>

namespace pyginac {

// this class is used as a helper for client code to traverse internal data
// structures and create new GiNaC algorithms in Python.
struct map_function_proxy : GiNaC::map_function
{
	PyObject* self;
	map_function_proxy(PyObject* _self) :self(_self) {}
	virtual ~map_function_proxy();
	
	virtual GiNaC::ex 
	operator()(const GiNaC::ex& arg)
	{
		assert(self != 0);
		return boost::python::call_method<GiNaC::ex>(self, "__call__", arg);
	}
};

map_function_proxy::~map_function_proxy()
{
}

void
wrap_map_function(void)
{
	using namespace boost::python;
	using GiNaC::map_function;
	
	class_<map_function, boost::noncopyable>( "map_function_base", 
		"Private base class used for internal purposes.", no_init);
	
	class_<map_function_proxy, bases<map_function>, boost::noncopyable>("map_function", 
		"Function object for map().\n"
		"Client code should inherit from this class and implement "
		"map_function.__call__().",
		no_init)
		.def( "__call__", &map_function_proxy::operator())
		;
}

} // !namespace pyginac
