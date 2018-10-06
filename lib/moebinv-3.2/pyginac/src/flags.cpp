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

#include <boost/python/enum.hpp>

#include <ginac/ginac.h>
#include <ginac/flags.h>

#include "pyginac.hpp"

namespace pyginac {
namespace {
enum info_flags
{
    numeric = GiNaC::info_flags::numeric,
    real = GiNaC::info_flags::real,
    rational = GiNaC::info_flags::rational,
    integer = GiNaC::info_flags::integer,
    crational = GiNaC::info_flags::crational,
    cinteger = GiNaC::info_flags::cinteger,
    positive = GiNaC::info_flags::positive,
    negative = GiNaC::info_flags::negative,
    nonnegative = GiNaC::info_flags::nonnegative,
    posint = GiNaC::info_flags::posint,
    negint = GiNaC::info_flags::negint,
    nonnegint = GiNaC::info_flags::nonnegint,
    even = GiNaC::info_flags::even,
    odd = GiNaC::info_flags::odd,
    prime = GiNaC::info_flags::prime,
    relation_equal = GiNaC::info_flags::relation_equal,
    relation_not_equal = GiNaC::info_flags::relation_not_equal,
    relation_less = GiNaC::info_flags::relation_less,
    relation_less_or_equal = GiNaC::info_flags::relation_less_or_equal,
    relation_greater = GiNaC::info_flags::relation_greater,
    relation_greater_or_equal = GiNaC::info_flags::relation_greater_or_equal,
    list = GiNaC::info_flags::list,
    polynomial = GiNaC::info_flags::polynomial,
    integer_polynomial = GiNaC::info_flags::integer_polynomial,
    cinteger_polynomial = GiNaC::info_flags::cinteger_polynomial,
    rational_polynomial = GiNaC::info_flags::rational_polynomial,
    crational_polynomial = GiNaC::info_flags::crational_polynomial,
    rational_function = GiNaC::info_flags::rational_function,
#if GINAC_VERSION_ATLEAST(1,7,0)
#else
    algebraic = GiNaC::info_flags::algebraic,
#endif
    indexed = GiNaC::info_flags::indexed,
    has_indices = GiNaC::info_flags::has_indices
};

enum determinant_algo 
{
    automatic = GiNaC::determinant_algo::automatic,
    gauss = GiNaC::determinant_algo::gauss,
    divfree = GiNaC::determinant_algo::divfree,
    laplace = GiNaC::determinant_algo::laplace,
    bareiss = GiNaC::determinant_algo::bareiss
};

namespace solve_algo {
enum solve_algo
{
    automatic = GiNaC::solve_algo::automatic,
    gauss = GiNaC::solve_algo::gauss,
    divfree = GiNaC::solve_algo::divfree,
    bareiss = GiNaC::solve_algo::bareiss  
};
} // !namespace solve_algo

namespace subs_options {
enum subs_options 
{
  no_pattern = GiNaC::subs_options::no_pattern,
  subs_no_pattern = GiNaC::subs_options::subs_no_pattern,
  algebraic = GiNaC::subs_options::algebraic,
  subs_algebraic = GiNaC::subs_options::subs_algebraic
};
} // !namespace subs_options
    
namespace expand_options {
enum expand_options
{
  expand_indexed = GiNaC::expand_options::expand_indexed,
#if GINAC_VERSION_ATLEAST(1,6,3)
  expand_function_args = GiNaC::expand_options::expand_function_args,
  expand_transcendental = GiNaC::expand_options::expand_transcendental
#else
  expand_function_args = GiNaC::expand_options::expand_function_args
#endif
};
} // !namespace expand_options
    
} // !namespace (unnamed)

void
wrap_info_flags(void)
{ 
    using namespace boost::python;

    enum_<info_flags>( "info_flags")
        .value( "numeric", numeric)
        .value( "real", real)
        .value( "rational", rational)
        .value( "integer", integer)
        .value( "crational", crational)
        .value( "cinteger", cinteger)
        .value( "positive", positive)
        .value( "negative", negative)
        .value( "nonnegative", nonnegative)
        .value( "posint", posint)
        .value( "negint", negint)
        .value( "nonnegint", nonnegint)
        .value( "even", even)
        .value( "odd", odd)
        .value( "prime", prime)
        .value( "relation_equal", relation_equal)
        .value( "relation_not_equal", relation_not_equal)
        .value( "relation_less", relation_less)
        .value( "relation_less_or_equal", relation_less_or_equal)
        .value( "relation_greater", relation_greater)
        .value( "relation_greater_or_equal", relation_greater_or_equal)
        .value( "list", list)
        .value( "polynomial", polynomial)
        .value( "integer_polynomial", integer_polynomial)
        .value( "cinteger_polynomial", cinteger_polynomial)
        .value( "rational_poynomial", rational_polynomial)
        .value( "crational_polynomial", crational_polynomial)
        .value( "rational_function", rational_function)
#if GINAC_VERSION_ATLEAST(1,7,0)
#else
        .value( "algebraic", algebraic)
#endif
        .value( "indexed", indexed)
        .value( "has_indices", has_indices)
        ;

    enum_<determinant_algo>("determinant_algo")
        .value( "automatic", automatic)
        .value( "gauss", gauss)
        .value( "divfree", divfree)
        .value( "laplace", laplace)
        .value( "bareiss", bareiss)
        ;
    
    enum_<solve_algo::solve_algo>("solve_algo")
        .value( "automatic", solve_algo::automatic)
        .value( "gauss", solve_algo::gauss)
        .value( "divfree", solve_algo::divfree)
        .value( "bareiss", solve_algo::bareiss)
        ;

    enum_<subs_options::subs_options>("subs_options")
      .value( "no_pattern", subs_options::no_pattern)
      .value( "subs_no_pattern", subs_options::subs_no_pattern)
      .value( "algebraic", subs_options::algebraic)
      .value( "subs_algebraic", subs_options::subs_algebraic)
      ;

    enum_<expand_options::expand_options>("expand_options")
      .value( "expand_indexed", expand_options::expand_indexed)
      .value( "expand_function_args", expand_options::expand_function_args)
#if GINAC_VERSION_ATLEAST(1,6,3)
      .value( "expand_transcendental", expand_options::expand_transcendental)
#endif
      ;

}

} // !namespace pyginac
