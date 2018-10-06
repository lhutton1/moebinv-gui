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

namespace pyginac {

void
wrap_symmetry(void)
{
  using namespace boost::python;
  using GiNaC::basic;
  using GiNaC::ex;
  using GiNaC::symmetry;

  class_<symmetry, bases<basic> >("symmetry", 
				  "This class describes the symmetry of a group of indices." 
				  "These objects can be grouped into a tree to form complex "
				  "mixed symmetries.",
				  init<>())
    .def(init<unsigned>())
    .def(init<symmetry::symmetry_type, const symmetry&, const symmetry &>())
    .def("get_type", &symmetry::get_type, "Get symmetry type.")
    .def("set_type", &symmetry::set_type, "Set symmetry type.")
    .def("add", &symmetry::add, return_internal_reference<>(), 
	 "Add child node, check index sets for consistency.")
    .def("validate", &symmetry::validate, 
	 "Verify that all indices of this node are in the range [0..n-1]."
	 "This function throws an exception if the verification fails."
	 "If the top node has a type != none and no children, add all indices"
	 "in the range [0..n-1] as children.")
    .def("has_symmetry", &symmetry::has_symmetry,
	 "Check whether this node actually represents any kind of symmetry.")
    ;
		
  implicitly_convertible<symmetry, ex>();

  symmetry (*sy_none0)() = GiNaC::sy_none;
  symmetry (*sy_none2)(const symmetry&, const symmetry&) = GiNaC::sy_none;
  symmetry (*sy_none3)(const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_none;
  symmetry (*sy_none4)(const symmetry&, const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_none;

  def("sy_none", sy_none0);
  def("sy_none", sy_none2);
  def("sy_none", sy_none3);
  def("sy_none", sy_none4);

  symmetry (*sy_symm0)() = GiNaC::sy_symm;
  symmetry (*sy_symm2)(const symmetry&, const symmetry&) = GiNaC::sy_symm;
  symmetry (*sy_symm3)(const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_symm;
  symmetry (*sy_symm4)(const symmetry&, const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_symm;

  def("sy_symm", sy_symm0);
  def("sy_symm", sy_symm2);
  def("sy_symm", sy_symm3);
  def("sy_stmm", sy_symm4);

  symmetry (*sy_anti0)() = GiNaC::sy_anti;
  symmetry (*sy_anti2)(const symmetry&, const symmetry&) = GiNaC::sy_anti;
  symmetry (*sy_anti3)(const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_anti;
  symmetry (*sy_anti4)(const symmetry&, const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_anti;

  def("sy_anti", sy_anti0);
  def("sy_anti", sy_anti2);
  def("sy_anti", sy_anti3);
  def("sy_anti", sy_anti4);

  symmetry (*sy_cycl0)() = GiNaC::sy_cycl;
  symmetry (*sy_cycl2)(const symmetry&, const symmetry&) = GiNaC::sy_cycl;
  symmetry (*sy_cycl3)(const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_cycl;
  symmetry (*sy_cycl4)(const symmetry&, const symmetry&, const symmetry&, const symmetry&) = GiNaC::sy_cycl;

  def("sy_cycl", sy_cycl0);
  def("sy_cycl", sy_cycl2);
  def("sy_cycl", sy_cycl3);
  def("sy_cycl", sy_cycl4);

  implicitly_convertible<int, symmetry>();

  // TODO: Rest of the symmetry utilities, see src/symmetry.h in GiNaC.
} 

} // !namespace pyginac
