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
#include <boost/python/iterator.hpp>
#include <boost/python/list.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/extract.hpp>

#include "pyginac.hpp"

namespace pyginac {

namespace {
#if 0
GiNaC::ex& 
checked_getitem( GiNaC::lst* This, size_t index)
{
	if (index < This->nops())
		throw std::out_of_range( "lst index out of range.");
	else return This->let_op( index);
}

void
checked_setitem( GiNaC::lst* This, size_t index, const GiNaC::ex& item)
{
	if (index < This->nops())
		throw std::out_of_range( "lst index out of range.");
	else This->let_op(index) = item;
}
#endif

struct lst_to_python
{
    static PyObject* convert( const GiNaC::lst& obj)
    {
        boost::python::list ret;
        GiNaC::lst::const_iterator i = obj.begin();
        GiNaC::lst::const_iterator i_end = obj.end();
        while (i != i_end) {
             ret.append( boost::python::object(*i));
             ++i;
        }
        Py_INCREF(ret.ptr());
        return ret.ptr();
    }
};

struct exvector_to_python
{
    static PyObject* convert( const GiNaC::exvector& obj)
    {
        boost::python::list ret;
        GiNaC::exvector::const_iterator i = obj.begin();
        GiNaC::exvector::const_iterator i_end = obj.end();
        while (i != i_end) {
             ret.append( boost::python::object(*i));
             ++i;
        }
        Py_INCREF(ret.ptr());
        return ret.ptr();
    }
};

} // !namespace pyginac::(unnamed)

void
lst_from_py_list( GiNaC::lst& ret, boost::python::object l)
{
	using namespace boost::python;
	
	int len = length(l);
	object iterator = extract_iterator( l);
	
	for (int i = 0; i < len; ++i) {
		object element = iterator.attr("next")();
		extract<const GiNaC::basic&> is_basic(element);
		if (is_basic.check()) {
			ret.append( is_basic());
			continue;
		}
		// Handle automagic conversions from GiNaC::numeric.
		extract<const GiNaC::numeric&> is_num(element);
		if (is_num.check()) {
			ret.append( is_num());
			continue;
		}
		try {
		        GiNaC::numeric n = numeric_from_py_object(element.ptr());
		        ret.append(n);
		        continue;
		} catch (std::invalid_argument) { ; }
		try {
		        GiNaC::lst l1;
		        pyginac::lst_from_py_list(l1,element);
		        ret.append(l1);
		        continue;
		} catch (std::invalid_argument) { ; }
		throw std::invalid_argument( "Python sequence contains one or more "
			"items that are not ginac objects or cannot be converted to ginac"
			" objects.");
	}
	return;
}

void
exvector_from_py_list( GiNaC::exvector& ret, boost::python::list l)
{
        using namespace boost::python;

        int len = length(l);
  	object iterator = extract_iterator( l);
	
	for (int i = 0; i < len; ++i) {
		object element = iterator.attr("next")();
		extract<const GiNaC::basic&> is_basic(element);
		if (is_basic.check()) {
			ret.push_back( is_basic());
			continue;
		}
		// Handle automagic conversions from GiNaC::numeric.
		extract<const GiNaC::numeric&> is_num(element);
		if (is_num.check()) {
			ret.push_back( is_num());
			continue;
		}
		try {
		        GiNaC::numeric n = numeric_from_py_object(element.ptr());
		        ret.push_back(n);
		        continue;
		} catch (std::invalid_argument) { ; }
		throw std::invalid_argument( "Python sequence contains one or more "
			"items that are not ginac objects or cannot be converted to ginac"
			" objects.");
	}
	return;
}

void
wrap_lst(void)
{
	using namespace boost::python;
#if 0
	using GiNaC::lst;
	using GiNaC::basic;
	using GiNaC::ex;
	
	class_<lst, bases<basic> >( "lst", "A iterable container of expressions.", 
		init<const ex&>())
		.def( init<const ex&, const ex&, optional<const ex&, const ex&, 
			const ex&, const ex&, const ex&, const ex&, const ex&, const ex&> >())
		.def( "__getitem__", &checked_getitem, return_internal_reference<>())
		.def( "__setitem__", &checked_setitem)
		.def( "let_op", &lst::let_op, return_internal_reference<>())
		.def( "append", &lst::append, return_internal_reference<>())
		.def( "prepend", &lst::prepend, return_internal_reference<>())
		.def( "sort", &lst::sort, return_internal_reference<>(), 
			"Sort the lst in-place.")
		.def( "unique", &lst::unique, return_internal_reference<>(), "Removes "
			"duplicate elements of the lst.  You should call self.sort() "
			"before this member function.")
		.def( "remove_first", &lst::remove_first, return_internal_reference<>(),
			"Remove the first element in the lst.")
		.def( "remove_last", &lst::remove_last, return_internal_reference<>(), 
			"Remove the last element in the list.")
		.def( "remove_all", &lst::remove_all, return_internal_reference<>(), 
			"Clear the list.")
		.def( "__iter__", iterator<const lst>())
		;
#endif

    to_python_converter<GiNaC::lst, lst_to_python>();
    // TODO: Implement implicit conversions from Python lists of expressions
    // to GiNaC::lst 's.

    to_python_converter<GiNaC::exvector, exvector_to_python>();
}

} // !namespace pyginac
