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
#include <boost/python/return_value_policy.hpp>
#include <boost/python/copy_const_reference.hpp>

#include "pyginac.hpp"

namespace pyginac {

// exprseq must be wrapped first.
void
wrap_ncmul(void)
{
	using namespace boost::python;
	using GiNaC::exprseq;
	using GiNaC::basic;
	using GiNaC::ncmul;
	using GiNaC::ex;
	using GiNaC::wildcard;
	
	class_<ncmul, bases<exprseq, basic> >("ncmul", 
		"Represents non-commutative products of expressions.",
		init< const ex&, const ex&, optional< const ex&, const ex&, const ex&> >())
        .def( init<const ncmul&>())
		.def( "get_factors", &ncmul::get_factors, return_value_policy<copy_const_reference>())
		;
    
    implicitly_convertible<ncmul, ex>();
}

} // !namespace ginac
