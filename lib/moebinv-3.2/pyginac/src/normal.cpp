/*
 *  PyGiNaC Copyright (C) 2004-2005 Jonathan Brandmeyer and Matti Peltomäki
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

#include <boost/python/def.hpp>
#include <boost/python/overloads.hpp>

#include <string>

#include "pyginac.hpp"

namespace pyginac {
namespace {

GiNaC::ex
do_sqrfree1(GiNaC::ex a) { return sqrfree(a); }

GiNaC::ex
do_sqrfree2( GiNaC::ex a, boost::python::object l)
{
  GiNaC::lst gl;
  lst_from_py_list(gl,l);
  return sqrfree(a, gl);
}

GiNaC::ex
do_divide(const GiNaC::ex &a, const GiNaC::ex &b, bool check_args=true)
{
  GiNaC::ex q;
  if(GiNaC::divide(a, b, q, check_args)) {
    return q;
  } else {
    throw std::invalid_argument("Exact division over the rationals not possible.");
  }
}

GiNaC::ex
do_gcd(const GiNaC::ex &a, const GiNaC::ex &b, bool check_args=true)
{
  return GiNaC::gcd(a, b, NULL, NULL, check_args);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(quo_overloads, quo, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(rem_overloads, rem, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(prem_overloads, prem, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(sprem_overloads, sprem, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(divide_overloads, do_divide, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(lcm_overloads, lcm, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(gcd_overloads, gcd, 2, 3)

} // !namespace (unnamed)

void
wrap_normal(void)
{
	using namespace boost::python;
	using namespace GiNaC;

	def("quo", quo, 
	    quo_overloads("Quotient q(x) of polynomials a(x) and b(x) in Q[x], so that a(x)=b(x)*q(x)+r(x)"));
	def("rem", rem, 
	    rem_overloads("Remainder r(x) of polynomials a(x) and b(x) in Q[x], so that a(x)=b(x)*q(x)+r(x)"));
	def("decomp_rational", decomp_rational, 
	    "Decompose rational function a(x)=N(x)/D(x) into Q(x)+R(x)/D(x)");
	def("prem", prem, 
	    prem_overloads("Pseudo-remainder of polynomials a(x) and b(x) in Q[x]"));
	def("sprem", sprem, 
	    sprem_overloads("Sparse pseudo-remainder of polynomials a(x) and b(x) in Q[x]"));
	def("divide", do_divide, 
	    divide_overloads("Exact polynomial division of a(X) by b(X) in Q[X]"));
	def("sqrfree", do_sqrfree1, "Square-free factorization of a polynomial a(x)");
	def("sqrfree", do_sqrfree2, "Square-free factorization of a polynomial a(x)");
	def("sqrfree_parfrac", sqrfree_parfrac,
	    "Square-free partial fraction decomposition of a rational function a(x)");
	def("collect_common_factors", collect_common_factors,
	    "Collect common factors in sums.");
	def("resultant", resultant, 
	    "Resultant of two polynomials e1,e2 with respect to symbol s");

	ex (*p_lcm)(const ex &, const ex &, bool) = &lcm;
	def("lcm", p_lcm, lcm_overloads("docstring"));

	ex (*p_gcd)(const ex &, const ex &, ex *, ex *, bool, unsigned int) = &gcd;

	def("gcd", p_gcd, gcd_overloads("Polynomial GCD in Z[x]"));
}

} // !namespace pyginac
