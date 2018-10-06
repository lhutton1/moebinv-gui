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
#include <boost/python/operators.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/def.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/list.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/to_python_converter.hpp>


#include <string>
#include "pyginac.hpp"

namespace pyginac {

namespace {

using GiNaC::ex;
using GiNaC::lst;

boost::python::object
unwrap_ex( const GiNaC::ex& other)
{
    using boost::python::object;
    using namespace GiNaC;

	if (is_exactly_a<add>(other))
            return object( add( ex_to<add>(other)));
        else if (is_exactly_a<mul>(other))
            return object( mul( ex_to<mul>(other)));
        else if (is_exactly_a<power>(other))
            return object( power( ex_to<power>(other)));
        else if (is_exactly_a<lst>(other))
            return object( lst( ex_to<lst>(other)));
        else if (is_exactly_a<ncmul>(other))
            return object( ncmul( ex_to<ncmul>(other)));
        else if (is_exactly_a<relational>(other))
            return object( relational( ex_to<relational>(other)));
        else if (is_exactly_a<possymbol>(other))
            return object( possymbol( ex_to<possymbol>(other)));
        else if (is_exactly_a<realsymbol>(other))
            return object( realsymbol( ex_to<realsymbol>(other)));
        else if (is_exactly_a<symbol>(other))
            return object( symbol( ex_to<symbol>(other)));
        else if (is_exactly_a<constant>(other))
            return object( constant( ex_to<constant>(other)));
        else if (is_exactly_a<fderivative>(other))
            return object( fderivative( ex_to<fderivative>(other)));
        else if (is_exactly_a<matrix>(other))
            return object( matrix( ex_to<matrix>(other)));
        else if (is_exactly_a<fail>(other))
            return object( fail( ex_to<fail>(other)));
        else if (is_exactly_a<numeric>(other))
            return object( numeric( ex_to<numeric>(other)));
        else if (is_exactly_a<pseries>(other))
            return object( pseries( ex_to<pseries>(other)));
        else if (is_exactly_a<integral>(other))
            return object( integral( ex_to<integral>(other)));
        else if (is_exactly_a<varidx>(other))
            return object( varidx( ex_to<varidx>(other)));
        else if (is_exactly_a<spinidx>(other))
            return object( spinidx( ex_to<spinidx>(other)));
        else if (is_exactly_a<tensdelta>(other))
            return object( tensdelta( ex_to<tensdelta>(other)));
        else if (is_exactly_a<tensmetric>(other))
            return object( tensmetric( ex_to<tensmetric>(other)));
        else if (is_exactly_a<minkmetric>(other))
            return object( minkmetric( ex_to<minkmetric>(other)));
        else if (is_exactly_a<spinmetric>(other))
            return object( spinmetric( ex_to<spinmetric>(other)));
        else if (is_exactly_a<tensepsilon>(other))
            return object( tensepsilon( ex_to<tensepsilon>(other)));
#if 0
        // TODO: Figure out how to {un}wrap these beasties
        else if (is_exactly_a<structure>(other))
            return object( structure( ex_to<structure>(other)));
#endif
        else if (is_exactly_a<su3one>(other))
            return object( su3one( ex_to<su3one>(other)));
        else if (is_exactly_a<su3t>(other))
            return object( su3t( ex_to<su3t>(other)));
        else if (is_exactly_a<su3f>(other))
            return object( su3f( ex_to<su3f>(other)));
        else if (is_exactly_a<su3d>(other))
            return object( su3d( ex_to<su3d>(other)));
        else if (is_exactly_a<symmetry>(other))
            return object( symmetry( ex_to<symmetry>(other)));
        else if (is_exactly_a<diracone>(other))
            return object( diracone( ex_to<diracone>(other)));
        else if (is_exactly_a<diracgamma>(other))
            return object( diracgamma( ex_to<diracgamma>(other)));
        else if (is_exactly_a<diracgamma5>(other))
            return object( diracgamma5( ex_to<diracgamma5>(other)));
        else if (is_exactly_a<diracgammaL>(other))
            return object( diracgammaL( ex_to<diracgammaL>(other)));
        else if (is_exactly_a<diracgammaR>(other))
            return object( diracgammaR( ex_to<diracgammaR>(other)));
        else if (is_exactly_a<clifford>(other))
            return object( clifford( ex_to<clifford>(other)));
        else if (is_exactly_a<color>(other))
            return object( color( ex_to<color>(other)));
        else if (is_exactly_a<wildcard>(other))
            return object( wildcard( ex_to<wildcard>(other)));
        else if (is_exactly_a<cliffordunit>(other))
            return object( cliffordunit( ex_to<cliffordunit>(other)));
        else if (is_exactly_a<idx>(other))
            return object( idx( ex_to<idx>(other)));
        else if (is_exactly_a<tensor>(other))
            return object( tensor( ex_to<tensor>(other)));
        else if (is_exactly_a<indexed>(other))
            return object( indexed( ex_to<indexed>(other)));
        else if (is_exactly_a<function>(other))
            return object( function( ex_to<function>(other)));
	else if (is_exactly_a<expairseq>(other))
            return object( expairseq( ex_to<expairseq>(other)));
        else if (is_exactly_a<exprseq>(other))
            return object( exprseq( ex_to<exprseq>(other)));
        else if (is_exactly_a<basic>(other))
            return object( basic( ex_to<basic>(other)));
        else
            // TODO: This might not be the right answer...
            return object( basic( ex_to<basic>(other)));
            //throw std::invalid_argument( "Could not unwrap an ex of unknown type.");
}

struct ex_to_python
{
    static PyObject* convert( const GiNaC::ex& obj)
    {
        boost::python::object ret = unwrap_ex(obj);
        Py_INCREF(ret.ptr());
        return ret.ptr();
    }
};

} // !namespace unnamed

void
wrap_ex(void)
{
	using namespace boost::python;
	
    to_python_converter< GiNaC::ex, ex_to_python>();
	
	def( "lhs", &GiNaC::lhs);
	def( "rhs", &GiNaC::rhs);
}

} // !namespace pyginac
