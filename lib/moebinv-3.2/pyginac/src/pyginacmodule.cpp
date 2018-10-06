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

#include <sstream>

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/exception_translator.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/errors.hpp>

namespace pyginac {

// Exception translation for GiNaC's only locally defined exception.
void
translate_pole_error( const GiNaC::pole_error& e)
{
	PyErr_SetString( PyExc_ZeroDivisionError, e.what());
}

void 
translate_std_out_of_range( const std::out_of_range& e)
{
	PyErr_SetString( PyExc_IndexError, e.what());
}


// Allow access to Digits from Python.  You cannot control Digits with assignment
// in the same way that you can in C++, this is a reasonable workaroud.
long
set_digits( long digits)
{
	long ret = GiNaC::Digits;
	GiNaC::Digits = digits;
	return ret;
}

// Declared in pyginac.hpp, and used locally within pyginac itself.  This is a
// thin wrapper around the builtin function len().
int 
length( boost::python::object seq)
{
	int ret = PySequence_Size( seq.ptr());
	if (ret == -1) {
		boost::python::throw_error_already_set();
	}
	return ret;
}

bool
supports_iteration( boost::python::object o)
{
	return PyObject_GetIter(o.ptr()) != NULL;
}

boost::python::object
extract_iterator( boost::python::object o)
{
	using namespace boost::python;
	return object( handle<>( PyObject_GetIter(o.ptr())));
}


// Forward declarations.
void wrap_basic();
void wrap_constant();
void wrap_numeric();
void wrap_expairseq();
void wrap_symbol();
void wrap_ex();
void wrap_exprseq();
void wrap_lst();
void wrap_relational();
void wrap_ncmul();
void wrap_idx();
void wrap_expair();
void wrap_map_function();
void wrap_matrix();
void wrap_ncmul();
void wrap_integral();
void wrap_power();
void wrap_info_flags();
void wrap_exmap();
void wrap_series();
void wrap_wildcard();
void wrap_normal();
void wrap_tensor();
void wrap_symmetry();
void wrap_clifford();

/** Verify that PyGiNaC is runtime linked against a build of GiNaC that is ABI 
 * compatable with the one that we were built against.
 */
static void 
verify_abi_compatible()
{
	const int build_version_major = GINACLIB_MAJOR_VERSION;
	const int build_version_minor = GINACLIB_MINOR_VERSION;
	
	if (build_version_major != GiNaC::version_major 
		|| build_version_minor != GiNaC::version_minor) {
		std::ostringstream err;
		err << "PyGiNaC was built against GiNaC version " 
			<< build_version_major << "." << build_version_minor 
			<< ", but the runtime linker found version "
			<< GiNaC::version_major << "." << GiNaC::version_minor << "."
			<< "  They are incompatable.";
		PyErr_SetString( PyExc_ImportError, err.str().c_str());
		boost::python::throw_error_already_set();
	}
}
	
} // !namespace pyginac

BOOST_PYTHON_MODULE( cginac)
{
	using namespace boost::python;
	using namespace pyginac;
	
	verify_abi_compatible();
	
	register_exception_translator<const GiNaC::pole_error&>( 
		&translate_pole_error);
	// By default, Boost.Python translates this into a plain RuntimeError.
	// To support the sequence protocol properly, something has to return IndexError
	// std::out_of_range seems the most appropriate.
	register_exception_translator<const std::out_of_range&>(
		&translate_std_out_of_range);
	
	// Wrap the base class for all GiNaC classes.
	wrap_basic();
	// Wraps class constant, and will also instantiate the three special constants.
	wrap_constant();
	// Wraps the numeric class and functions that operate only on numerics.
	wrap_numeric();
	// Wraps expairseq, add, and mul
	wrap_expairseq();
	// Wraps symbol
	wrap_symbol();
	// Wraps ex, 
	wrap_ex();
	// Wraps exprseq, function, fderivative, and the global predefined symbolic 
	// functions.
	wrap_exprseq();
	// Wraps the ginac lst aka std::list.
	wrap_lst();
	// Wraps the relational object.
	wrap_relational();
	// Wraps the ncmul and wildcard classes
	wrap_ncmul();
	// Wraps the idx, varidx, and spinidx classes.
	wrap_idx();
	// Wraps the expair class.  This doesn't appear to be needed in Python at
    // this time.
	// wrap_expair();
	// Wraps the many map_function functors
	wrap_map_function();
	wrap_matrix();
    wrap_integral();
    wrap_power();
    wrap_info_flags();
    wrap_exmap();
    wrap_series();
    wrap_wildcard();
    wrap_normal();
    wrap_tensor();
    wrap_symmetry();
    wrap_clifford();
	
	def( "set_digits", &pyginac::set_digits, 
		"Globally set the minimum precision of floating point evaluation in "
			"GiNaC.\n"
		"Returns the previous value for the global precision.");
	
    // def( "_get_version", &pyginac::get_version);
    scope().attr("version") = make_tuple( GiNaC::version_major, 
        GiNaC::version_minor,
        GiNaC::version_micro);
    scope().attr("Pi") = object( boost::python::ptr( &GiNaC::Pi));
    scope().attr("I") = object( boost::python::ptr( &GiNaC::I));
    scope().attr("Euler") = object( boost::python::ptr( &GiNaC::Euler));
    scope().attr("Catalan") = object( boost::python::ptr( &GiNaC::Catalan));
}
