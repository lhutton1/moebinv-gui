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
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>
#include "pyginac.hpp"

namespace pyginac {
	
namespace {

  // The following six functions have to be rewrapped like below,
  // since their GiNaC versions are inline functions which cannot be 
  // given as function references to def()

GiNaC::function 
zeta_noninline1(const GiNaC::ex& e) 
{
  return zeta(e);
}

GiNaC::function
zeta_noninline2(const GiNaC::ex& e1, const GiNaC::ex& e2) 
{
  return zeta(e1, e2);
}

GiNaC::function
G_noninline2(const GiNaC::ex& e1, const GiNaC::ex& e2)
{
  return G(e1, e2);
}

GiNaC::function
G_noninline3(const GiNaC::ex& e1, const GiNaC::ex& e2, const GiNaC::ex& e3)
{
  return G(e1, e2, e3);
}

GiNaC::function
psi_noninline1(const GiNaC::ex& e)
{
  return psi(e);
}

GiNaC::function
psi_noninline2(const GiNaC::ex& e1, const GiNaC::ex& e2)
{
  return psi(e1, e2);
}

} // !namespace anonymous
	
#define PYGINAC_WRAP_FUNCTION( name) \
	const GiNaC::function (*name##_ex)(const GiNaC::ex&) = &GiNaC::name<>; \
	def( #name, name##_ex);
#define PYGINAC_WRAP_FUNCTION_2P( name) \
        const GiNaC::function (*name##_ex)(const GiNaC::ex&, const GiNaC::ex&) = &GiNaC::name<>; \
        def( #name, name##_ex);

#define PYGINAC_WRAP_FUNCTION_3P( name) \
        const GiNaC::function (*name##_ex)(const GiNaC::ex&, const GiNaC::ex&, const GiNaC::ex&) = &GiNaC::name<>; \
	def( #name, name##_ex);

void
wrap_exprseq(void)
{
	using namespace boost::python;
	using GiNaC::ex;
	using GiNaC::basic;
	using GiNaC::exprseq;
	using GiNaC::exvector;
	using GiNaC::function;
	using GiNaC::symbol;
	using GiNaC::constant;
	using GiNaC::fderivative;
	
	class_<exprseq, bases<basic> >( "exprseq", no_init)
		.def( "append", &exprseq::append, return_internal_reference<>())
		.def( "__iter__", iterator<const exprseq>())
		;
	
	ex (function::* thiscontainer)(const exvector&) const = 
		&function::thiscontainer;
	
	class_<function, bases<exprseq, basic> >( "function", 
		"A symbolic function.  This class is used to implement builtin functions"
		" like sin(), cos(), etc.", no_init)
		.def( "get_name", &function::get_name)
		.def( "get_serial", &function::get_serial)
		.def( "thiscontainer", thiscontainer)
		.add_property( "name", &function::get_name)
		.add_property( "serial", &function::get_serial)
		;
		
	class_<fderivative, bases<function, exprseq, basic> >("fderivative",
		"The (abstract) derivative of a function.", no_init)
		;
	
	PYGINAC_WRAP_FUNCTION(abs)
	PYGINAC_WRAP_FUNCTION(step)
	PYGINAC_WRAP_FUNCTION(csgn)
	PYGINAC_WRAP_FUNCTION(sin)
	PYGINAC_WRAP_FUNCTION(cos)
	PYGINAC_WRAP_FUNCTION(tan)
	PYGINAC_WRAP_FUNCTION(asin)
	PYGINAC_WRAP_FUNCTION(acos)
	PYGINAC_WRAP_FUNCTION(atan)
	PYGINAC_WRAP_FUNCTION(sinh)
	PYGINAC_WRAP_FUNCTION(cosh)
	PYGINAC_WRAP_FUNCTION(tanh)
	PYGINAC_WRAP_FUNCTION(asinh)
	PYGINAC_WRAP_FUNCTION(acosh)
	PYGINAC_WRAP_FUNCTION(atanh)
	PYGINAC_WRAP_FUNCTION(exp)
	PYGINAC_WRAP_FUNCTION(log)
	PYGINAC_WRAP_FUNCTION(Li2)
	PYGINAC_WRAP_FUNCTION(Li3)
	PYGINAC_WRAP_FUNCTION(tgamma)
	PYGINAC_WRAP_FUNCTION(lgamma)
	PYGINAC_WRAP_FUNCTION(factorial)
	PYGINAC_WRAP_FUNCTION(Order)
	
	PYGINAC_WRAP_FUNCTION_2P(atan2)
	PYGINAC_WRAP_FUNCTION_2P(Li)
	PYGINAC_WRAP_FUNCTION_2P(H)
	PYGINAC_WRAP_FUNCTION_2P(eta)
	PYGINAC_WRAP_FUNCTION_2P(zetaderiv)
	PYGINAC_WRAP_FUNCTION_2P(beta)
	PYGINAC_WRAP_FUNCTION_2P(binomial)

	PYGINAC_WRAP_FUNCTION_3P(S)

	
	def( "lsolve", &GiNaC::lsolve);
	GiNaC::ex (*py_pow)(const ex&, const ex&) = &GiNaC::pow;
	def( "pow", py_pow);
	
	// The (Riemann) zeta function needs to be handled 
	// differently from the others since in GiNaC it is 
	// originally handled differently. The case is the same
	// for G and psi, too. 
	def("zeta", zeta_noninline1);
	def("zeta", zeta_noninline2);
	
	def("G", G_noninline2);
	def("G", G_noninline3);

	def("psi", psi_noninline1);
	def("psi", psi_noninline2);

	implicitly_convertible< function, GiNaC::ex>();
	implicitly_convertible< exprseq, GiNaC::ex>();
    implicitly_convertible< fderivative, GiNaC::ex>();
}

} // !namespace pyginac
