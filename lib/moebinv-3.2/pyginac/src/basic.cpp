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
#include <ginac/flags.h>

#include <boost/python/class.hpp>
#include <boost/python/list.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/def.hpp>

#include "pyginac.hpp"

namespace pyginac {

bool pyginac_latex = false;
bool is_latex_on()
{
	return pyginac_latex;
}

void
inline latex_on()
{
	pyginac_latex = true;
}

void
inline latex_off()
{
	pyginac_latex = false;
}

namespace {
	
using GiNaC::ex;
using GiNaC::lst;
using GiNaC::basic;
using GiNaC::return_types;

ex
py_getitem( const basic& This, size_t index)
{
	return This[index];
}

void
py_setitem( const basic& This, size_t index, const GiNaC::basic& value)
{
    This[index] = value;
}

ex
py_getitem_ex( const basic& This, const ex& index)
{
	return This[index];
}

inline GiNaC::ex
do_add( const GiNaC::basic& lhs, const GiNaC::basic& rhs)
{
    return GiNaC::add( lhs, rhs);
}

inline GiNaC::ex
do_sub( const GiNaC::basic& lhs, const GiNaC::basic& rhs)
{
    return GiNaC::add( lhs, GiNaC::mul( GiNaC::numeric(-1), rhs));
}

inline GiNaC::ex
do_rsub( const GiNaC::basic& rhs, const GiNaC::basic& lhs)
{
    return GiNaC::add( lhs, GiNaC::mul( GiNaC::numeric(-1), rhs));
}


GiNaC::ex
do_mul( const GiNaC::basic& lhs, const GiNaC::basic& rhs)
{
    // Check if we are constructing a mul object or a ncmul object.
    if (rhs.return_type()==return_types::commutative ||
        lhs.return_type()==return_types::commutative)
        return GiNaC::mul(lhs,rhs);
    else
        return GiNaC::ncmul(lhs,rhs);
}

inline GiNaC::ex
do_pow( const GiNaC::basic& lhs, const GiNaC::basic& rhs)
{
    return GiNaC::power( lhs, rhs);
}

inline GiNaC::ex
do_neg( const GiNaC::basic& lhs)
{
    return GiNaC::mul( lhs, GiNaC::numeric(-1));
}

inline GiNaC::ex
do_div( const GiNaC::basic& lhs, const GiNaC::basic& rhs)
{
    return GiNaC::mul( lhs, GiNaC::power( rhs, GiNaC::numeric(-1)));
}

inline GiNaC::ex
do_rdiv( const GiNaC::basic& rhs, const GiNaC::basic& lhs)
{
    return do_div( lhs, rhs);
}

inline GiNaC::ex
do_nadd( const GiNaC::basic& lhs, const GiNaC::numeric& rhs)
{
    return GiNaC::add( lhs, rhs);
}

inline GiNaC::ex
do_nsub( const GiNaC::basic& lhs, const GiNaC::numeric& rhs)
{
    return GiNaC::add( lhs, GiNaC::mul( GiNaC::numeric(-1), rhs));
}

inline GiNaC::ex
do_nrsub( const GiNaC::basic& rhs, const GiNaC::numeric& lhs)
{
    return GiNaC::add( lhs, GiNaC::mul( GiNaC::numeric(-1), rhs));
}

inline GiNaC::ex
do_nmul( const GiNaC::basic& lhs, const GiNaC::numeric& rhs)
{
    return GiNaC::mul( lhs, rhs);
}

inline GiNaC::ex
do_npow( const GiNaC::basic& lhs, const GiNaC::numeric& rhs)
{
    return GiNaC::power( lhs, rhs);
}

inline GiNaC::ex
do_nrpow( const GiNaC::basic& rhs, const GiNaC::numeric& lhs)
{
    return GiNaC::power( lhs, rhs);
}

inline GiNaC::ex
do_ndiv( const GiNaC::basic& lhs, const GiNaC::numeric& rhs)
{
    return GiNaC::mul( lhs, GiNaC::power( rhs, GiNaC::numeric(-1)));
}

inline GiNaC::ex
do_nrdiv( const GiNaC::basic& rhs, const GiNaC::numeric& lhs)
{
    return do_div( lhs, rhs);
}

GiNaC::ex
do_normal(const GiNaC::basic& lhs, int level = 0)
{
    GiNaC::ex holder(lhs);
#if GINAC_VERSION_ATLEAST(1,7,0)
    return holder.normal();
#else
    return holder.normal( level);
#endif
}

GiNaC::ex
do_factor(const GiNaC::ex& poly, unsigned options = 0)
{
    return factor(poly, options);
}

GiNaC::ex
do_numer( const GiNaC::basic& This)
{
    GiNaC::ex holder( This);
    return holder.numer();
}

GiNaC::ex
do_denom( const GiNaC::basic& This)
{
    return GiNaC::ex(This).denom();
}

boost::python::tuple
do_numer_denom( const GiNaC::basic& This)
{
    GiNaC::ex ret( GiNaC::ex(This).numer_denom());
    return boost::python::make_tuple( ret[0], ret[1]);
}

ex
collect_lst( const basic& This, boost::python::list var_list, bool distributed = false)
{
	GiNaC::lst vars;
	lst_from_py_list(vars, var_list);

    return This.collect(vars, distributed);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(normal, do_normal, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(factor, do_factor, 1, 2)

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(expand, expand, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(coeff, coeff, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(collect, collect, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(collect2, collect_lst, 2, 3)
#if GINAC_VERSION_ATLEAST(1,7,0)
#else
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(eval, eval, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(evalf, evalf, 0, 1)
#endif
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(series, series, 2, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(diff, diff, 1, 2)

/*ex
do_eval_noarg( const GiNaC::basic& lhs)
{
    return lhs.eval();
}*/

ex
subs_ex( const basic& This, const GiNaC::relational& other)
{
    std::map<ex, ex, GiNaC::ex_is_less> exmap;
    exmap[other.op(0)] = other.op(1);
    return This.subs( exmap);
}

ex
subs_ex_opts( const basic & This, const GiNaC::relational& other, unsigned opts)
{
    std::map<ex, ex, GiNaC::ex_is_less> exmap;
    exmap[other.op(0)] = other.op(1);
    return This.subs( exmap, opts);
}

ex
subs_lsts( const basic& This, boost::python::object lhs, boost::python::object rhs)
{
    using namespace boost::python;

    if (length(lhs) != length(rhs))
        throw std::out_of_range( "expression lists must have the same length");

    std::map<ex, ex, GiNaC::ex_is_less> exmap;
    int end = length(lhs);
    for (int i = 0; i != end; ++i) {
        exmap[extract<ex>(lhs[i])] = extract<ex>(rhs[i]);
    }
    return This.subs( exmap);
}

ex
subs_lst( const basic& This, boost::python::object lhs)
{
    using namespace boost::python;

    std::map<ex, ex, GiNaC::ex_is_less> exmap;

    int end = length(lhs);
    for (int i = 0; i != end; ++i) {
        GiNaC::relational equality = extract<GiNaC::relational>(lhs[i]);
        exmap[equality.op(0)] = equality.op(1);
    }
    return This.subs( exmap);
}


ex
subs_dict( const basic& This, boost::python::dict rules)
{
    using namespace boost::python;
    object iter = rules.attr( "iteritems")();
    std::map<ex, ex, GiNaC::ex_is_less> exmap;

    while (true) {
        try {
            object item = iter.attr("next")();
            exmap[ extract<ex>(item[0])] = extract<ex>(item[1]);
        }
        catch (boost::python::error_already_set& ) {
            PyErr_Clear();
            break;
        }
    }
    return This.subs( exmap);
}

GiNaC::relational
eq( const GiNaC::basic& lhs, const GiNaC::ex& rhs)
{
    return GiNaC::relational( lhs, rhs, GiNaC::relational::equal);
}

GiNaC::relational
neq( const GiNaC::basic& lhs, const GiNaC::ex& rhs)
{
    return GiNaC::relational( lhs, rhs, GiNaC::relational::not_equal);
}

GiNaC::relational
gt( const GiNaC::basic& lhs, const GiNaC::ex& rhs)
{
    return GiNaC::relational( lhs, rhs, GiNaC::relational::greater);
}

GiNaC::relational
gteq( const GiNaC::basic& lhs, const GiNaC::ex& rhs)
{
    return GiNaC::relational( lhs, rhs, GiNaC::relational::greater_or_equal);
}

GiNaC::relational
lt( const GiNaC::basic& lhs, const GiNaC::ex& rhs)
{
    return GiNaC::relational( lhs, rhs, GiNaC::relational::less);
}

GiNaC::relational
lteq( const GiNaC::basic& lhs, const GiNaC::ex& rhs)
{
    return GiNaC::relational( lhs, rhs, GiNaC::relational::less_or_equal);
}

bool
do_is_zero( const GiNaC::basic& This)
{
    GiNaC::ex expr = This;
    expr = expr.eval();
    return expr.is_zero();
}

bool
do_is_zero_matrix( const GiNaC::basic& This)
{
    GiNaC::ex expr = This;
    expr = expr.eval();
    return expr.is_zero_matrix();
}

boost::python::tuple
do_match( const GiNaC::basic& This, const GiNaC::basic& pattern)
{
    namespace py = boost::python;

    std::map<ex, ex, GiNaC::ex_is_less> matches;
    GiNaC::ex wrapper(This);
    bool ret0 = wrapper.match( pattern, matches);
    py::dict ret1;
    GiNaC::exmap::const_iterator i = matches.begin();
    GiNaC::exmap::const_iterator end = matches.end();
    while (i != end) {
             ret1[i->first] = i->second;
             ++i;
    }
    return py::make_tuple(ret0, ret1);
}

bool
do_has( const GiNaC::basic& This, const GiNaC::basic& pattern)
{
    return GiNaC::ex(This).has(pattern);
}

GiNaC::lst
do_find( const GiNaC::basic& This, const GiNaC::basic& pattern)
{
    std::set<ex, GiNaC::ex_is_less> matches;
    GiNaC::ex(This).find( pattern, matches);
    GiNaC::lst ret;
    GiNaC::exset::const_iterator i = matches.begin();
    GiNaC::exset::const_iterator end = matches.end();
    while (i != end) {
        ret.append(*i);
        ++i;
    }
    return ret;
}

GiNaC::ex
do_content(const GiNaC::basic& This, const GiNaC::basic& x)
{
  return GiNaC::ex(This).content(x);
}

GiNaC::ex
do_unit(const GiNaC::basic& This, const GiNaC::basic& x)
{
  return GiNaC::ex(This).unit(x);
}

GiNaC::ex
do_primpart(const GiNaC::basic& This, const GiNaC::basic& x)
{
  return GiNaC::ex(This).primpart(x);
}

GiNaC::ex
do_primpart2(const GiNaC::basic& This, const GiNaC::basic& x, const GiNaC::basic& c)
{
  return GiNaC::ex(This).primpart(x, c);
}

GiNaC::ex
do_simplify_indexed(const GiNaC::basic& This)
{
  return GiNaC::ex(This).simplify_indexed();
}

GiNaC::ex
do_simplify_indexed_sp(const GiNaC::basic& This, const GiNaC::scalar_products& sp)
{
  return GiNaC::ex(This).simplify_indexed(sp);
}

GiNaC::ex
do_symmetrize(const GiNaC::basic& This)
{
  return GiNaC::ex(This).symmetrize();
}

GiNaC::ex
do_antisymmetrize(const GiNaC::basic& This)
{
  return GiNaC::ex(This).antisymmetrize();
}

GiNaC::ex
do_symmetrize_cyclic(const GiNaC::basic& This)
{
  return GiNaC::ex(This).symmetrize_cyclic();
}

// TODO: Use the pickling system for this instead.
// TODO: Learn how pickling works :)
boost::python::object
parse_string( std::string str, boost::python::object vars)
{
	GiNaC::lst cpp_vars;
	lst_from_py_list( cpp_vars, vars);
	return boost::python::object( GiNaC::ex( str, cpp_vars));
}

/** Python hash values are 32-bit signed integers, wheras GiNaC computes
 * hash values that are 32 bit unsigned integers.  This function makes a
 * straight conversion from one to the other.
 */
int
wrap_hash(const GiNaC::basic& This)
{
	/** TODO: Make sure that this is the Right Thing on a 64bit platform. */
    union {
        unsigned int given_hash;
        signed int returned_hash;
    } converter;

    converter.given_hash = This.gethash();
    return converter.returned_hash;
}

} // !namespace anonymous

BOOST_PYTHON_FUNCTION_OVERLOADS(expand_dummy_sum_overload, GiNaC::expand_dummy_sum, 1, 2)

void
wrap_basic(void)
{
	using namespace boost::python;
	using GiNaC::basic;
	using GiNaC::ex;
		
	class_<basic>( "basic", "The common base class for most classes in GiNaC.",
		no_init)
        // Access as a number-like object.
        .def( "__add__", do_add)
        .def( "__sub__", do_sub)
        .def( "__mul__", do_mul)
        .def( "__pow__", do_pow)
        .def( "__neg__", do_neg)
        .def( "__div__", do_div)
        // Repeats of the above to coax out some more implicit conversions from
        // built-in numeric types.
        .def( "__add__", do_nadd)
        .def( "__sub__", do_nsub)
        .def( "__mul__", do_nmul)
        .def( "__radd__", do_nadd)
        .def( "__rsub__", do_nrsub)
        .def( "__rmul__", do_nmul)
        .def( "__pow__", do_npow)
        .def( "__rpow__", do_nrpow)
        .def( "__div__", do_ndiv)
        .def( "__rdiv__", do_nrdiv)
        // Relational operators
        .def( "__eq__", eq)
        .def( "__ne__", neq)
        .def( "__gt__", gt)
        .def( "__ge__", gteq)
        .def( "__lt__", lt)
        .def( "__le__", lteq)

		.def( "precedence", &basic::precedence,
			"Return relative operator precendence (for formatting output).")
		.def( "info", &basic::info, "Information about the object.  "
            "See also info_flags")

        // The sequence protocol and element access.
		.def( "nops", &basic::nops, "The number of operands or members.")
        .def( "__len__", &basic::nops)
		.def( "op", &basic::op, "Returns the operand at the specified position.")
		.def( "__getitem__", py_getitem)
        .def( "__setitem__", py_setitem)
		.def( "__getitem__", py_getitem_ex)
		.def( "map", &basic::map, "Construct new expression by applying "
			"the specified function to all sub-expressions (one level only, "
			"not recursively).")

        // Operations on polynomials
		.def( "degree", &basic::degree, "Returns degree of highest power in an "
			"object")
		.def( "ldegree", &basic::ldegree, "Returns degree of lowest power in an"
			" object")
		.def( "coeff", &basic::coeff, coeff("Returns the coefficiant of degree n in s"))
		.def( "collect", &basic::collect, collect("Sort expanded expression in terms of "
												  "powers of some object(s)"))
		.def( "collect", &collect_lst, collect2("Sort expanded expression in terms of "
			"powers of some list of objects"))
        .def( "expand", &basic::expand, expand( "Expand the expression, i.e., "
            "multiply it out and return the result as a new expression."))
        .def( "numer", do_numer, "Return the numerator of a polynomial in normal form.")
        .def( "denom", do_denom, "Return the denominator of a polynomial in normal form.")
        .def( "numer_denom", do_numer_denom, "basic.numer_denom()->(numer, denom)\n"
            "Split a polynomial in normal form into its numerator and denominator"
            " faster than calling .numer() and .denom() separately.")

        // Evaluations
#if GINAC_VERSION_ATLEAST(1,7,0)
		.def( "eval", &basic::eval, "Perform automatic non-interruptive term "
			"rewriting rules.")
		.def( "evalf", &basic::evalf, "Evaluate object numerically.")
#else
		.def( "eval", &basic::eval, eval("Perform automatic non-interruptive term "
			"rewriting rules."))
		.def( "evalf", &basic::evalf, evalf("Evaluate object numerically."))
#endif
		.def( "evalm", &basic::evalm, "Evaluate sums, products and integer "
			"powers of matrices.")
        .def( "eval_integ", &basic::eval_integ, "Evaluate integral expressions symbolically.")
        // Searching
        .def( "match", do_match, "Check whether the expression matches a "
            "given pattern.  Returns (bool, dict), where bool is true if a match"
            " was found, and dict contains the mapping of wildcards to the "
            "expressions that they matched.")
        .def( "has", do_has, "Test for occurance of a pattern")
        .def( "find", do_find,
            "Similar to has(), except that it returns a "
            "list of all expressions that were found.")

        // Polynomial ops
		.def( "series", &basic::series, series( "Default implementation of ex.series()."))
        .def( "normal", &do_normal, normal("Default implementation of ex.normal()."))
		.def( "to_rational", &basic::to_rational, "Default implementation of "
			"ex.to_rational().")
		.def( "to_polynomial", &basic::to_polynomial)
		.def( "integer_content", &basic::integer_content)
		.def( "smod", &basic::smod, "Apply symmetric modular homomorphism to an "
			"expanded multivariate polynomial.")
		.def( "max_coefficient", &basic::max_coefficient, "Implementation of "
			"ex.max_coefficient().")
		.def( "get_free_indices", &basic::get_free_indices, "Returns a vector "
			"containing the free indices of the expression.")
		.def( "eval_indexed", &basic::eval_indexed, "Perform automatic symbolic "
			"evaluations on indexed expression that contains this object as the "
			"base expression.")
		.def( "add_indexed", &basic::add_indexed, "Add two indexed expressions.")
		.def( "scalar_mul_indexed", &basic::scalar_mul_indexed, "Multiply an "
			"indexed expression with a scalar.")
		.def( "contract_with", &basic::contract_with, "Try to contract two "
			"indexed expressions that appear in the same product.")
		.def( "subs", subs_lsts)
        .def( "subs", subs_lst)
        .def( "subs", subs_dict)
        .def( "subs", subs_ex)
	.def( "subs", subs_ex_opts)
		.def( "diff", &basic::diff, diff("Default interface of nth derivative."))
        .def( "conjugate", &basic::conjugate, "Returns the complex conjugate of itself.")
        .def( "real_part", &basic::real_part, "Returns real part of itself.")
        .def( "imag_part", &basic::imag_part, "Returns imag part of itself.")
		.def( "is_equal", &basic::is_equal, "Test for syntactic equality.")
        .def( "is_zero", do_is_zero, "The common test for zero-ness.")

		.def( "dbgprint", &basic::dbgprint, "Print debug output.")
		.def( "dbgprinttree", &basic::dbgprinttree, "Print full debug tree output.")

        .def( "is_zero_matrix", do_is_zero_matrix, "The common test for zero matrix.")
	.def( "content", do_content, "The content part of a multivariate polynomial")
	.def( "unit", do_unit, "The unit part of a multivariate polynomial")
	.def( "primpart", do_primpart, "The primitive polynomial of a multivariate polynomial")
	.def( "primpart", do_primpart2,
		"The primitive polynomial of a multivariate polynomial")
	.def("simplify_indexed", do_simplify_indexed,
	     "Simplify an indexed expression")
	.def("simplify_indexed", do_simplify_indexed_sp,
	     "Simplify an indexed expression")
	.def("symmetrize", do_symmetrize, "Symmetrize an expression.")
	.def("antisymmetrize", do_antisymmetrize, "Antisymmetrize an expression.")
	.def("symmetrize_cyclic", do_symmetrize_cyclic,
	     "Symmetrize an expression by cyclic permutation.")

        // Overrides for special Python object behavior
		.def( "__str__", &print_to_string<basic>)
        .def( "__hash__", wrap_hash, "Compute a hash of an expression.")
		;

	def("expand_dummy_sum", &GiNaC::expand_dummy_sum,
		expand_dummy_sum_overload("Expand dummy summation into an explicit form"));
	def( "parse_string", &parse_string, (args( "string"), "variables"),
		"parse_string(string, variables)-> ginac.basic\n"
		"Parse an algebraic expression string into a tree of GiNaC expressions.  "
		"'variables' is a Sequence of ginac.symbol to use when parsing.");
	def( "is_latex_on", &is_latex_on,
	     "report true if GINaC expressions printed in LaTeX form");
	def("latex_on", &latex_on, "Switch ON LaTeX output for ALL expressions.");
	def("latex_off", &latex_off, "Switch OFF LaTeX output for ALL expressions.");
	def("factor",do_factor,factor("Factorise polynomial"));
}

} // !namespace pyginac
