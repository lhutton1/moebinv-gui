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
#include <boost/python/args.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/implicit.hpp>

namespace pyginac {
namespace {

bool
as_bool( const GiNaC::relational& This)
{
    return This;
}

GiNaC::ex
get_lhs( const GiNaC::relational& This)
{
    return This.lhs();
}

GiNaC::ex
get_rhs( const GiNaC::relational& This)
{
    return This.rhs();
}

GiNaC::relational::operators
get_operator( const GiNaC::relational& This)
{
    using GiNaC::relational;
    using GiNaC::info_flags;
    
    if (This.info( info_flags::relation_equal))
        return relational::equal;
    else if (This.info( info_flags::relation_not_equal))
        return relational::not_equal;
    else if (This.info( info_flags::relation_less))
        return relational::less;
    else if (This.info( info_flags::relation_less_or_equal))
        return relational::less_or_equal;
    else if (This.info( info_flags::relation_greater))
        return relational::greater;
    else if (This.info( info_flags::relation_greater_or_equal))
        return relational::greater_or_equal;
    else
        throw std::invalid_argument( "PyGiNaC CRITICAL ERROR: "
            "A relational object did not have a relation!");
}

} // !namespace (unnamed)

void
wrap_relational(void)
{
	using namespace boost::python;
	using GiNaC::basic;
	using GiNaC::relational;
	using GiNaC::ex;
	
	enum_<relational::operators>( "relop")
		.value("eq", relational::equal)
		.value("ne", relational::not_equal)
		.value("lt", relational::less)
		.value("le", relational::less_or_equal)
		.value("gt", relational::greater)
		.value("ge", relational::greater_or_equal)
		.export_values()
		;
	
	class_<relational, bases<basic> >("relational", 
		"A relational comparison between two expressions.",
		init<ex, ex, optional< ::GiNaC::relational::operators> >(
            (arg("lhs"), "rhs", "relop")))
        .def( init<const relational&>())
        .add_property( "lhs", get_lhs)
        .add_property( "rhs", get_rhs)
        .add_property( "relop", get_operator)
        .def( "__nonzero__", &as_bool)
		;

	implicitly_convertible<relational, GiNaC::ex>();
}

} // !namespace pyginac
