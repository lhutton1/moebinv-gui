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

#include "pyginac.hpp"

namespace GiNaC {
	class constant;
}

namespace pyginac {

GiNaC::numeric
numeric_from_py_object(PyObject * n)
{
        using namespace boost::python; 
        using GiNaC::numeric;

        if (PyInt_CheckExact(n)) {
	        return numeric(PyInt_AsLong(n));
        }
        else if (PyLong_CheckExact(n)) {
                object num = object( handle<>( borrowed(n)));
                std::string repr = extract<std::string>(num.attr("__repr__")());
                return numeric( repr.substr(0, repr.size()-1).c_str());
        }
        else if (PyFloat_CheckExact(n)) {
                return numeric( PyFloat_AsDouble(n));
        }
        else if (PyComplex_CheckExact(n)) {
                numeric real( PyComplex_RealAsDouble(n));
                numeric imag( PyComplex_ImagAsDouble(n));
                return numeric( real.add(imag.mul(GiNaC::I)));
        }
        else throw std::invalid_argument("");
}

// Perform implicit conversions from the supported numeric types to a 
// GiNaC::ex - wrapped GiNaC::numeric.
struct numeric_from_number
{
	numeric_from_number()
	{
		boost::python::converter::registry::push_back( 
			&convertible,
			&construct,
			boost::python::type_id<GiNaC::numeric>());
	}
	
	static void* convertible( PyObject* obj)
	{
		if (PyInt_CheckExact(obj) 
			|| PyFloat_CheckExact(obj) 
			|| PyComplex_CheckExact(obj)
			|| PyLong_CheckExact(obj))
			return obj;
		return 0;
	}

	static void construct( 
		PyObject* obj, 
		boost::python::converter::rvalue_from_python_stage1_data* data)
	{
		using namespace boost::python;
		using GiNaC::numeric;

		void* storage = (
			(boost::python::converter::rvalue_from_python_storage<numeric>*)
			data)->storage.bytes;
		
		try {
		        new (storage) numeric(numeric_from_py_object(obj));
		data->convertible = storage;
		} catch (std::invalid_argument) {
		        assert(false == true);
		}
	}
};

GiNaC::numeric
do_rdiv( const GiNaC::numeric& rhs, const GiNaC::numeric lhs)
{
    return lhs / rhs; 
}

GiNaC::numeric
do_rsub( const GiNaC::numeric& rhs, const GiNaC::numeric lhs)
{
    return lhs.sub( rhs);
}

void
wrap_numeric(void)
{
	using namespace boost::python;
	using GiNaC::basic;
	using GiNaC::numeric;
	
	class_<numeric, bases<basic> >( "numeric", 
	"A polymorphic representation of numbers.  numeric may represent integers, "
	"floating point numbers, rational numbers, complex floats, complex "
	"integers, and complex rationals, all to arbitrary precision.", 
        init<long, long>( (args( "numer"), "denom")))
		.def( init<const char*>())
        .def( init<const numeric&>())
		.def( "inverse", &numeric::inverse, "inverse of a number")
		.def( "csgn", &numeric::csgn, "Returns the complex half-plane (left or "
			"right) on which the number lies.")
		.def( "is_zero", &numeric::is_zero, "True if this object is zero")
		.def( "is_positive", &numeric::is_positive)
		.def( "is_negative", &numeric::is_negative)
		.def( "is_integer", &numeric::is_integer)
		.def( "is_pos_integer", &numeric::is_pos_integer)
		.def( "is_nonneg_integer", &numeric::is_nonneg_integer)
		.def( "is_even", &numeric::is_even)
		.def( "is_odd", &numeric::is_odd)
		.def( "is_prime", &numeric::is_prime, "True if this is an exact integer"
			" and a probabalistic prime.")
		.def( "is_rational", &numeric::is_rational)
		.def( "is_real", &numeric::is_real)
		.def( "is_cinteger", &numeric::is_cinteger, 
			"True if object is element of the domain of integers extended"
			" by I, i.e. it is of the form a+b*I, where a and b are "
			"integers.")
		.def( "is_crational", &numeric::is_crational, 
			"True if object is an exact rational number, may even be complex "
			"(denominator may be unity).")
		.def( "to_int", &numeric::to_int)
		.def( "to_float", &numeric::to_double)
		.def( "real", &numeric::real, "Real part of complex numbers.")
		.def( "imag", &numeric::imag, "Imaginary part of complex numbers.")
		.def( "numer", &numeric::numer, "Numerator of rational numbers.")
		.def( "denom", &numeric::denom, "Denominator of rational numbers.")
		;
		
	def( "isqrt", &GiNaC::isqrt, "Integer numeric square root.");
	
	const numeric (*py_lcm)(const numeric&, const numeric&) = &GiNaC::lcm;
	def( "lcm", py_lcm, 
		"Least common multiple if the operands are integers, the product of the"
		" operands if they are not.");
	
	const numeric (*py_gcd)(const numeric&, const numeric&) = &GiNaC::gcd;
	def( "gcd", py_gcd, "Greatest Common Divisor if both are integers, "
		"numeric(1) if they are not.");
	
	int (*py_csgn)(const numeric&) = &GiNaC::csgn;
	def( "csgn", py_csgn);
	
	const numeric (*py_irem)(const numeric&, const numeric&) = &GiNaC::irem;
	def("irem", py_irem, "Numeric integer remainder");

	const numeric (*py_iquo)(const numeric&, const numeric&) = &GiNaC::iquo;
	def("iquo", py_iquo, "Numeric integer quotient");

	implicitly_convertible<numeric, GiNaC::ex>();
	numeric_from_number();
}

} // !namespace pyginac
