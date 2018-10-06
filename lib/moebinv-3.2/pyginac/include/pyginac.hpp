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

#ifndef PYGINAC_MODULE_HPP
#define PYGINAC_MODULE_HPP

#include <ostream>
#include <string>
#include <sstream>

#include <boost/python/list.hpp>
#include <boost/shared_ptr.hpp>

namespace pyginac {

// GinacExponentiatable must support exponentiation
template< typename GinacExponentiatable1, typename GinacExponentiatable2>
GiNaC::ex
pow( const GinacExponentiatable1* This, const GinacExponentiatable2& other)
{
	return GiNaC::pow<>( *This, other);
}

// This template provides a fake member function for python stringification.
// GinacPrintable must implement GinacPrintable.print( GiNaC::print_context);
bool is_latex_on();
template< typename GinacPrintable>
std::string
print_to_string( GinacPrintable* object)
{
	std::ostringstream output;
	if (is_latex_on())
	{
		GiNaC::print_latex context( output);
		object->print( context);
	}
	else
	{
		GiNaC::print_python context( output);
		object->print( context);
	}

	return output.str();
}

#define PYGINAC_WRAP_MATH_OPERATORS_NOASSIGN( type) \
	.def( self + other<type>()) \
    .def( other<type>() + self) \
	.def( self - other<type>()) \
    .def( other<type>() - self) \
	.def( self * other<type>()) \
    .def( other<type>() * self) \
	.def( self / other<type>()) \
    .def( other<type>() / self)

#define PYGINAC_WRAP_MATH_OPERATORS_ONLYASSIGN( type) \
	.def( self += other<type>()) \
	.def( self -= other<type>()) \
	.def( self *= other<type>()) \
	.def( self /= other<type>())


#define PYGINAC_WRAP_MATH_OPERATORS( type) \
	PYGINAC_WRAP_MATH_OPERATORS_NOASSIGN( type) \
	PYGINAC_WRAP_MATH_OPERATORS_ONLYASSIGN( type)

// A wrapper for the builtin-function "len".  It might throw error_already_set.
int length( boost::python::object obj);

// Convert a Python list into a GiNaC list.  This might throw error_already_set
// if the object is not a sequence, or its elements cannot be converted into
// GiNaC::ex.
void lst_from_py_list( GiNaC::lst&, boost::python::object);

// Convert a Python list into a GiNaC exvector.  This might throw error_already_set
// if the object is not a sequence, or its elements cannot be converted into
// GiNaC::ex.
void exvector_from_py_list( GiNaC::exvector&, boost::python::list);

// A wrapper around PyIter_Check().  This returns true iff the object supports
// the Python iteration protocol.
bool supports_iteration( boost::python::object);

// A wrapper around PyIter_Get().  This returns a Python iterator object, or
// throws error_already_set if the object does not support iteration.
boost::python::object extract_iterator( boost::python::object);

// Convert a Python object to a GiNaC::numeric. Throws
// std::invalid_argument in case a conversion is not possible.
GiNaC::numeric numeric_from_py_object(PyObject*);

} // !namespace pyginac

#define GINAC_VERSION_ATLEAST( major, minor, micro) \
	(GINACLIB_MAJOR_VERSION > major \
	|| (GINACLIB_MAJOR_VERSION == major && GINACLIB_MINOR_VERSION > minor) \
	|| (GINACLIB_MAJOR_VERSION == major && GINACLIB_MINOR_VERSION == minor && GINACLIB_MICRO_VERSION >= micro))

#endif // !defined PYGINAC_MODULE_HPP
