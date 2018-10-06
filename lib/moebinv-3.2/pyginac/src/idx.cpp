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
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/list.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/overloads.hpp>

#include "pyginac.hpp"

namespace pyginac {
	
namespace {

void 
do_add_vectors(GiNaC::scalar_products & This, boost::python::object l, 
	       const GiNaC::ex & dim)
{
  GiNaC::lst cpp_l;
  lst_from_py_list(cpp_l, l);
  This.add_vectors(cpp_l, dim);
}

void 
do_add_vectors(GiNaC::scalar_products & This, boost::python::object l)
{
  do_add_vectors(This, l, GiNaC::wild());
}

GiNaC::indexed * 
init_from_list(const GiNaC::ex & b, boost::python::list l)
{
  GiNaC::exvector cpp_ev;
  exvector_from_py_list(cpp_ev, l);
  return new GiNaC::indexed(b, cpp_ev);
}

GiNaC::indexed *
init_from_list_symm(const GiNaC::ex & b, const GiNaC::symmetry & symm, 
		    boost::python::list l)
{
  GiNaC::exvector cpp_ev;
  exvector_from_py_list(cpp_ev, l);
  return new GiNaC::indexed(b, symm, cpp_ev);
}

} // !namespace anonymous

void
wrap_idx(void)
{
	using namespace boost::python;
	using GiNaC::idx;
	using GiNaC::basic;
	using GiNaC::varidx;
	using GiNaC::spinidx;
	using GiNaC::ex;
	using GiNaC::indexed;
	using GiNaC::scalar_products;
	using GiNaC::symmetry;
	using GiNaC::exvector;
	
	class_<idx, bases<basic> >("idx", 
		"This class holds one index of an indexed object.\n"
		"They can theoretically be any symbolic expression, but are usually "
		"only a symbol or numeric(integer). Indices belong to a space "
		"with a certain numeric or symbolic dimension.", 
		init<const ex&, const ex&>())
		.def( "is_dummy_pair_same_type", &idx::is_dummy_pair_same_type)
		.def( "get_value", &idx::get_value, "Returns the value of the index.")
		.def( "is_numeric", &idx::is_numeric, "Check whether the index is numeric.")
		.def( "is_symbolic", &idx::is_symbolic, "Check whether the index is symbolic.")
		.def( "get_dim", &idx::get_dim, "Get the dimension of index space.")
		.def( "is_dim_numeric", &idx::is_dim_numeric, 
			"Check whether the dimension is numeric")
		.def( "is_dim_symbolic", &idx::is_dim_symbolic, 
			"Check whether the dimension is symbolic")
		.def( "replace_dim", &idx::replace_dim, 
			"Return a new idx with same value but a different dimension")
		.def( "minimal_dim", &idx::minimal_dim,
			"Return the minimum of the dimensions of this and another.")
		;
		
	class_<varidx, bases<idx, basic> >("varidx", 
		"This class holds an index with a variance (co- or contravariant).",
		init< const ex&, const ex&, optional<bool> >())
		.def( "is_covariant", &varidx::is_covariant,
			"Check whether the index is covariant." )
		.def( "is_contravariant", &varidx::is_contravariant,
			"Check whether the index is contravariant.")
		.def( "toggle_variance", &varidx::toggle_variance,
			"Make a new index with the same value but the opposite variance.")
		;
		
	class_<spinidx, bases<varidx, idx, basic> >("spinidx",
		"This class holds a spinor index that can be dotted or undotted"
		" and that also has a variance.",
		init<const ex&, optional<const ex&, bool, bool> >())
		.def( "is_dotted", &spinidx::is_dotted, 
			"Check whether the index is dotted.")
		.def( "is_undotted", &spinidx::is_undotted,
			"Check whether the index is not dotted.")
		.def( "toggle_dot", &spinidx::toggle_dot,
			"Make a new index with the same value and variance but the opposite"
			" dottedness. ")
		.def( "toggle_variance_dot", &spinidx::toggle_variance_dot,
			"Make a new index with the same value but opposite variance and "
			"dottedness.")
		;
		
	exvector (indexed::*get_dummy_indices0)() const = &indexed::get_dummy_indices;
	exvector (indexed::*get_dummy_indices1)(const indexed&) const = &indexed::get_dummy_indices;

        class_<indexed, bases<basic> >("indexed",
               "This class holds an indexed expression.\n"
               "It consists of a 'base' expression (the expression being indexed) "
               "which can be accessed as op(0), and n (n >= 0)"
               "indices (all of class idx), accessible as op(1)..op(n).",
	       init<const ex&>())
               .def( init<const ex&, const ex&>())
               .def( init<const ex&, const ex&, const ex&>())
	       .def( init<const ex&, const ex&, const ex&, const ex&>())
	       .def( init<const ex&, const ex&, const ex&, const ex&, const ex &>())
	       .def( init<const ex&, const symmetry&, const ex&, const ex &>())
	       .def( init<const ex&, const symmetry&, const ex&, const ex &, const ex &>())
	       .def( init<const ex&, const symmetry&, const ex&, const ex &, const ex &, const ex &>())
	       .def( "__init__", make_constructor(init_from_list))
	       .def( "__init__", make_constructor(init_from_list_symm))
	       .def("all_index_values_are", &indexed::all_index_values_are, 
		    "Check whether all index values have a certain property")
	       .def("get_indices", &indexed::get_indices,
		    "Return a vector containing all the object's indices")
	       .def("has_dummy_index_for", &indexed::has_dummy_index_for,
		    "Check whether the object has an index that forms a dummy index pair with the given index")
	       .def("get_symmetry", &indexed::get_symmetry,
		    "Return symmetry properties")
	       .def("get_dummy_indices", get_dummy_indices0, 
		    "Get the dummy indices of the object")
	       .def("get_dummy_indices", get_dummy_indices1,
		    "Get the dummy indices of the object")
               ;

       void (scalar_products::*add3)(const ex &, const ex &, const ex &) = &scalar_products::add;
       void (scalar_products::*add4)(const ex &, const ex &, const ex &, const ex &) 
	 = &scalar_products::add;

       void (*add_vectors1)(scalar_products &, object) = &do_add_vectors;
       void (*add_vectors2)(scalar_products &, object, const ex &) = &do_add_vectors;
      
       class_<scalar_products>("scalar_products",
	       "Helper class for storing information about known scalar products which\n"
	       "are to be automatically replaced by simplify_indexed().",
	       init<>())
	 .def("add", add3, "Register a scalar product")
	 .def("add", add4, "Register a scalar product")
	 .def("add_vectors", add_vectors1, "Register a list of vectors")
	 .def("add_vectors", add_vectors2, "Register a list of vectors")
	 .def("clear", &scalar_products::clear, "Clear all registered scalar products")
	 ;

	implicitly_convertible<idx, ex>();
	implicitly_convertible<varidx, ex>();
	implicitly_convertible<spinidx, ex>();
	implicitly_convertible<indexed, ex>();
}
	
} // !namespace pyginac
