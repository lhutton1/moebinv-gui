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
#include <boost/python/overloads.hpp>

#include "pyginac.hpp"

namespace pyginac {

namespace {

GiNaC::ex
do_get_metric(const GiNaC::ex & e, const GiNaC::ex & i,  const GiNaC::ex & j, bool symmetrised = true)
{
	return GiNaC::ex_to<GiNaC::clifford>(e).get_metric(i, j, symmetrised);
}

GiNaC::ex
do_dirac_trace_list(const GiNaC::ex & e, boost::python::list rll, const GiNaC::ex & trONE = 4)
{
  GiNaC::lst l;
  lst_from_py_list(l, rll);
  return GiNaC::dirac_trace(e, l, trONE);
}

GiNaC::ex
do_dirac_trace(const GiNaC::ex & e, unsigned char rl = 0, const GiNaC::ex & trONE = 4)
{
  return GiNaC::dirac_trace(e, rl, trONE);
}

GiNaC::ex
do_lst_to_clifford(const GiNaC::ex & v, const GiNaC::ex & mu,
		   const GiNaC::ex & metr, unsigned char rl = 0)
{
  return GiNaC::lst_to_clifford(v, mu, metr, rl);
}

GiNaC::ex
do_lst_to_clifford_bpl(boost::python::list bpl, const GiNaC::ex & mu,
		   const GiNaC::ex & metr, unsigned char rl = 0)
{
  GiNaC::lst v;
  lst_from_py_list(v, bpl);
  return GiNaC::lst_to_clifford(v, mu, metr, rl);
}

GiNaC::ex
do_lst_to_clifford_bpl_e(boost::python::list bpl, const GiNaC::ex & e)
{
  GiNaC::lst v;
  lst_from_py_list(v, bpl);
  return GiNaC::lst_to_clifford(v, e);
}

GiNaC::ex
clifford_moebius_map4(const GiNaC::ex & M, const GiNaC::ex & P,
		   const GiNaC::ex & e, unsigned char rl = 0)
{
  return GiNaC::clifford_moebius_map(M, P, e, rl);
}
GiNaC::ex
clifford_moebius_map4_bpl(const GiNaC::ex & M, boost::python::list bpl,
		   const GiNaC::ex & e, unsigned char rl = 0)
{
  GiNaC::lst P;
  lst_from_py_list(P, bpl);
  return GiNaC::clifford_moebius_map(M, P, e, rl);
}

GiNaC::ex
clifford_moebius_map7(const GiNaC::ex & a, const GiNaC::ex & b, const GiNaC::ex & c,
		   const GiNaC::ex & d, const GiNaC::ex & P,
		   const GiNaC::ex & e, unsigned char rl = 0)
{
  return GiNaC::clifford_moebius_map(a, b, c, d, P, e, rl);
}

GiNaC::ex
clifford_moebius_map7_bpl(const GiNaC::ex & a, const GiNaC::ex & b, const GiNaC::ex & c,
		   const GiNaC::ex & d, boost::python::list bpl,
		   const GiNaC::ex & e, unsigned char rl = 0)
{
  GiNaC::lst P;
  lst_from_py_list(P, bpl);
  return GiNaC::clifford_moebius_map(a, b, c, d, P, e, rl);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(get_metric_overloads, do_get_metric, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(clifford_moebius_map4_overloads, clifford_moebius_map4, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(clifford_moebius_map4_bpl_overloads, clifford_moebius_map4_bpl, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(clifford_moebius_map7_overloads, clifford_moebius_map7, 6, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(clifford_moebius_map7_bpl_overloads, clifford_moebius_map7_bpl, 6, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(remove_dirac_ONE_overloads, GiNaC::remove_dirac_ONE, 1, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(clifford_max_label_overloads, GiNaC::clifford_max_label, 1, 2)

BOOST_PYTHON_FUNCTION_OVERLOADS(clifford_unit_overloads, GiNaC::clifford_unit, 2, 3)

BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_ONE_overloads, GiNaC::dirac_ONE, 0, 1)
BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_gamma_overloads, GiNaC::dirac_gamma, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_gamma5_overloads, GiNaC::dirac_gamma5, 0, 1)
BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_gammaL_overloads, GiNaC::dirac_gammaL, 0, 1)
BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_gammaR_overloads, GiNaC::dirac_gammaR, 0, 1)
BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_slash_overloads, GiNaC::dirac_slash, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_trace_list_overloads, do_dirac_trace_list, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(dirac_trace_overloads, do_dirac_trace, 1, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(lst_to_clifford_overloads, do_lst_to_clifford, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(lst_to_clifford_bpl_overloads, do_lst_to_clifford_bpl, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(clifford_to_lst_overloads, GiNaC::clifford_to_lst, 2, 3)

} // !namespace anonymous

void
wrap_clifford(void)
{
  using namespace boost::python;
  using GiNaC::basic;
  using GiNaC::ex;
  using GiNaC::indexed;
  using GiNaC::clifford;
  using GiNaC::diracone;
  using GiNaC::tensor;
  using GiNaC::cliffordunit;
  using GiNaC::diracgamma;
  using GiNaC::diracgamma5;
  using GiNaC::diracgammaL;
  using GiNaC::diracgammaR;

  class_<clifford, bases<indexed, basic> >
    ("clifford",
     "This class holds an object representing an element of the Clifford"
     "algebra (the Dirac gamma matrices). These objects only carry Lorentz"
     "indices. Spinor indices are hidden. A representation label (an unsigned"
     "8-bit integer) is used to distinguish elements from different Clifford"
     "algebras (objects with different labels commutate).",
     init<>())
    .def(init<const ex &>())
    .def(init<const ex &, unsigned char>())
    .def(init<const ex &, const ex&, const ex &>())
    .def(init<const ex &, const ex&, const ex &, unsigned char>())
    .def("get_representation_label", &clifford::get_representation_label)
    .def("same_metric", &clifford::same_metric)
    .def("get_metric", do_get_metric, get_metric_overloads("Get metric of the clifford unit"))
    ;

  class_<diracone, bases<tensor, basic> >
    ("diracone",
     "This class represents the Clifford algebra unity element.",
     init<>())
    ;

  class_<cliffordunit, bases<tensor, basic> >
    ("cliffordunit",
     "This class represents the Clifford algebra generators (units).",
    init<>())
    ;

  class_<diracgamma, bases<cliffordunit, tensor, basic> >
    ("diracgamma",
     "This class represents the Dirac gamma Lorentz vector.",
     init<>())
    ;

  class_<diracgamma5, bases<tensor, basic> >
    ("diracgamma5",
     "This class represents the Dirac gamma5 object which anticommutates with"
     "all other gammas.",
     init<>())
    ;

  class_<diracgammaL, bases<tensor, basic> >
    ("diracgammaL",
     "This class represents the Dirac gammaL object which behaves like"
     "1/2 (1-gamma5)",
     init<>())
    ;

  class_<diracgammaR, bases<tensor, basic> >
    ("diracgammaR",
     "This class represents the Dirac gammaR object which behaves like"
     "1/2 (1+gamma5)",
     init<>())
    ;

  ex (*lst_to_clifford2)(const ex &, const ex &) = &GiNaC::lst_to_clifford;

  def("dirac_ONE", &GiNaC::dirac_ONE, dirac_ONE_overloads("Create a Clifford unity object."));
  def("clifford_unit", &GiNaC::clifford_unit,
      clifford_unit_overloads("Create a Clifford unit object."));
  def("dirac_gamma", &GiNaC::dirac_gamma,
      dirac_gamma_overloads("Create a Dirac gamma object."));
  def("dirac_gamma5", &GiNaC::dirac_gamma5,
      dirac_gamma5_overloads("Create a Dirac gamma5 object."));
  def("dirac_gammaR", &GiNaC::dirac_gammaR,
      dirac_gammaR_overloads("Create a Dirac gammaR object."));
  def("dirac_gammaL", &GiNaC::dirac_gammaL,
      dirac_gammaL_overloads("Create a Dirac gammaL object."));
  def("dirac_slash", &GiNaC::dirac_slash,
      dirac_slash_overloads("Create a term of the form e_mu * gamma~mu with a unique index mu."));
  def("dirac_trace", do_dirac_trace_list, dirac_trace_list_overloads(
      "Calculate dirac traces over the specified list of representation labels."
      "The computed trace is a linear functional that is equal to the usual"
      "trace only in D = 4 dimensions. In particular, the functional is not"
      "always cyclic in D != 4 dimensions when gamma5 is involved."));
  def("dirac_trace", do_dirac_trace, dirac_trace_overloads());
  def("canonicalize_clifford", &GiNaC::canonicalize_clifford,
      "Bring all products of clifford objects in an expression into a canonical"
      "order. This is not necessarily the most simple form but it will allow"
      "to check two expressions for equality.");
  def("clifford_prime", &GiNaC::clifford_prime,
      "Automorphism of the Clifford algebra, simply changes signs of all"
      "clifford units.");
  def("clifford_bar", &GiNaC::clifford_bar,
      "Main anti-automorphism of the Clifford algebra: makes reversion"
      "and changes signs of all clifford units");
  def("clifford_star", &GiNaC::clifford_star,
      "Reversion of the Clifford algebra, coincides with the conjugate().");
  def("remove_dirac_ONE", &GiNaC::remove_dirac_ONE,
      remove_dirac_ONE_overloads(
      "Replaces all dirac_ONE's in e with 1 (effectively removing them)."));
  def("clifford_norm", &GiNaC::clifford_norm,
      "Calculation of the norm in the Clifford algebra.");
  def("clifford_inverse", &GiNaC::clifford_inverse,
      "Calculation of the inverse in the Clifford algebra.");
  def("lst_to_clifford", lst_to_clifford2);
  def("lst_to_clifford", do_lst_to_clifford_bpl_e);
  def("lst_to_clifford", do_lst_to_clifford,
      lst_to_clifford_overloads("List conversion into the Clifford vector."));
  def("lst_to_clifford", do_lst_to_clifford_bpl,
      lst_to_clifford_bpl_overloads("List conversion into the Clifford vector."));
  def("clifford_to_list", &GiNaC::clifford_to_lst,
      clifford_to_lst_overloads(
      "An inverse function to lst_to_clifford(). For given Clifford vector extracts"
      "its components with respect to given Clifford unit. Obtained components may"
      "contain Clifford units with a different metric. Extraction is based on"
      "the algebraic formula (e * c.i + c.i * e)/ pow(e.i, 2) for non-degenerate cases"
      "(i.e. neither pow(e.i, 2) = 0)."));
  def("clifford_moebius_map", clifford_moebius_map4,
      clifford_moebius_map4_overloads(
      "Calculations of Moebius transformations (conformal map) defined by a 2x2 Clifford matrix"
      "(a b\\c d) in linear spaces with arbitrary signature. The expression is "
      "(a * x + b)/(c * x + d), where x is a vector build from list v with metric G."
      "(see Jan Cnops. An introduction to {D}irac operators on manifolds, v.24 of"
      "Progress in Mathematical Physics. Birkhauser Boston Inc., Boston, MA, 2002.)"
      "The three-parameter form of Moebius transformations defined by a 2x2 Clifford matrix M"
      "This function takes the transformation matrix M as a single entity."));
  def("clifford_moebius_map", clifford_moebius_map4_bpl,
      clifford_moebius_map4_bpl_overloads(
      "Calculations of Moebius transformations (conformal map) defined by a 2x2 Clifford matrix"));
  def("clifford_moebius_map", clifford_moebius_map7,
      clifford_moebius_map7_overloads(
      "Calculations of Moebius transformations (conformal map) with matrix given by "
      "its four elements."));
  def("clifford_moebius_map", clifford_moebius_map7_bpl,
      clifford_moebius_map7_bpl_overloads(
      "Calculations of Moebius transformations (conformal map) with matrix given by "
      "its four elements. Takes boost::python::list"));
  def("clifford_max_label", GiNaC::clifford_max_label,
      clifford_max_label_overloads(
      "Returns the maximal representation label of a clifford object "
      "if e contains at least one, otherwise returns -1"));
}

} // !namespace pyginac
