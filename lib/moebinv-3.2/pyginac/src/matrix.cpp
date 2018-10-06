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
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/list.hpp>
#include <boost/python/def.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/args.hpp>

#include "pyginac.hpp"

namespace pyginac { namespace {

GiNaC::ex
py_getitem( GiNaC::matrix& This, boost::python::tuple idx)
{
	using namespace boost::python;
	return This( extract<unsigned>(idx[0]), extract<unsigned>(idx[1]));
}

void
py_setitem( GiNaC::matrix& This, boost::python::tuple idx, GiNaC::ex item)
{
	using namespace boost::python;
	This( extract<unsigned>(idx[0]), extract<unsigned>(idx[1])) = item;
}

GiNaC::matrix*
init_from_seq( boost::python::object seq)
{
    using namespace boost::python;
    
    object row = seq[0];
    int n = length(seq);
    int m = length(row);
    GiNaC::matrix* ret = new GiNaC::matrix( n, m);
    for (int i = 0; i < n; ++i) {
        object row = seq[i];
        for (int j = 0; j < m; ++j) {
            (*ret)(i,j) = extract<GiNaC::ex>(row[j]);
        }
    }
    return ret;
}

GiNaC::ex
matrix_determinant( const GiNaC::matrix& This)
{
    return This.determinant();
}

GiNaC::ex
matrix_rncmul( const GiNaC::matrix& rhs, const GiNaC::matrix& lhs)
{
    return lhs * rhs;
}

GiNaC::ex
do_lsolve( boost::python::object eqns, boost::python::object vars, unsigned options)
{
    GiNaC::lst cpp_eqns, cpp_vars;
    lst_from_py_list( cpp_eqns, eqns);
    lst_from_py_list( cpp_vars, vars);
    return lsolve( cpp_eqns, cpp_vars, options);
}

GiNaC::ex
do_lsolve_default( boost::python::object eqns, boost::python::object vars)
{
    return do_lsolve(eqns, vars, GiNaC::solve_algo::automatic);
}

GiNaC::ex
do_diag_matrix( boost::python::object elems)
{
	GiNaC::lst cpp_elems;
	lst_from_py_list( cpp_elems, elems);
	return diag_matrix(cpp_elems);
}

} // !namespace (unnamed)

void
wrap_matrix(void)
{
	using GiNaC::matrix;
	using namespace boost::python;
#if GINAC_VERSION_ATLEAST(1,7,3)
    matrix (matrix::*inverse0)()const = &matrix::inverse;
#endif
	
	// TODO: Enable construction from a list of list of ex.
	class_<matrix, bases<GiNaC::basic> >( "matrix", "A symbolic matrix.", 
		init<unsigned, unsigned>())
        .def( init<const matrix&>())
        .def( "__init__", make_constructor(init_from_seq))
		.def( "__getitem__", py_getitem)
		.def( "__setitem__", py_setitem)
		.def( "transpose", &matrix::transpose)
		.def( "determinant", &matrix::determinant)
        .def( "determinant", matrix_determinant)
		.def( "trace", &matrix::trace)
#if GINAC_VERSION_ATLEAST(1,7,3)
		.def( "inverse", inverse0, "Inverse of a matrix")
#else
		.def( "inverse", &matrix::inverse)
#endif
		.def( "charpoly", &matrix::charpoly, 
            "Returns the characteristic polynomial of the matrix")
		.def( "solve", 
            (matrix (matrix:: *)(const matrix &vars, const matrix &rhs) const)
            &matrix::solve, (args("args"), "rhs"), "matrix.solve( args, rhs) -> matrix\n"
                "Solves the system self*args == rhs for args.")
		.def( "rank", &matrix::rank)
		;

    implicitly_convertible<matrix, GiNaC::ex>();
    
    def( "lsolve", do_lsolve, args( "eqns", "vars", "options"));
    def( "lsolve", do_lsolve_default, "Solve a system of equations "
        "(a wrapper around matrix.solve())", args("eqns", "vars"));

    GiNaC::ex (*unit_matrix_ol1)(unsigned) = &GiNaC::unit_matrix;
    GiNaC::ex (*unit_matrix_ol2)(unsigned, unsigned) = &GiNaC::unit_matrix;
   
    GiNaC::ex (*symbolic_matrix_ol3)
      (unsigned, unsigned, const std::string&) = &GiNaC::symbolic_matrix;
    GiNaC::ex (*symbolic_matrix_ol4)
      (unsigned, unsigned, const std::string&, const std::string&) 
      = &GiNaC::symbolic_matrix;
    
    def("diag_matrix", do_diag_matrix, "Build a diagonal matrix.");
    def("unit_matrix", unit_matrix_ol1, "Build a unit matrix of givensize.");
    def("unit_matrix", unit_matrix_ol2);
    def("symbolic_matrix", symbolic_matrix_ol3, "Build a symbolic matrix of given size");
    def("symbolic_matrix", symbolic_matrix_ol4);
}

} // !namespace pyginac
