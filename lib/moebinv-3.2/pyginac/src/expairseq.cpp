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
#include <boost/python/list.hpp>
#include <boost/python/make_constructor.hpp>

#include "pyginac.hpp"

namespace pyginac {
	
namespace {
	
GiNaC::add *
init_add_from_list(boost::python::list l)
{
  GiNaC::exvector cpp_ev;
  exvector_from_py_list(cpp_ev, l);
  return new GiNaC::add(cpp_ev);
}

GiNaC::mul *
init_mul_from_list(boost::python::list l)
{
  GiNaC::exvector cpp_ev;
  exvector_from_py_list(cpp_ev, l);
  return new GiNaC::mul(cpp_ev);
}

} // !namespace anonymous

void
wrap_expairseq(void)
{
	using namespace boost::python;
	using GiNaC::basic;
	using GiNaC::expairseq;
	using GiNaC::add;
	using GiNaC::mul;
	using GiNaC::ex;
	using GiNaC::exvector;
	using GiNaC::epvector;
	
	class_<expairseq, bases<basic> >( "expairseq", "A sequence of expair.", no_init)
		;
	
	class_<add, bases< expairseq, basic> >( "add", 
		"The symbolic sum of two expressions.", init<const ex&, const ex&>())
		.def( init<const add&>())
		.def( init<const exvector&>())
		.def( init<const epvector&>())
		.def( init<const epvector&, const ex&>())
	        .def("__init__", make_constructor(init_add_from_list));
		;
		
	class_<mul, bases<expairseq, basic> >("mul", 
		"The symbolic product of two expressions.", init<const ex&, const ex&>())
		.def( init<const exvector&>())
		.def( init<const epvector&>())
		.def( init<const epvector&, const ex&>())
		.def( init<const ex&, const ex&, const ex&>())
		.def( init<const mul&>())
		.def( "algebraic_subs_mul", &mul::algebraic_subs_mul)
	        .def("__init__", make_constructor(init_mul_from_list))
		;
		
	implicitly_convertible<mul, GiNaC::ex>();
	implicitly_convertible<add, GiNaC::ex>();
	implicitly_convertible<expairseq, GiNaC::ex>();

}
	
} // !namespace pyginac
