// 	$Id: cycle.cpp,v 1.22 2014/08/10 15:35:27 kisilv Exp kisilv $	
/*
 *  PyCycle Copyright (C) 2006 Vladimir Kisil & Daniel Seidel
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

#include "cycle.h"
#include "pyginac.hpp"

#include <string>
#include <boost/python/class.hpp>
#include <boost/python/list.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/def.hpp>
#include <boost/python/make_constructor.hpp>

namespace pycycle {
using namespace MoebInv;
using namespace std;
using namespace GiNaC;

///////////wrappers for constructors of cycle and cycle2D - begin ///////////////
// this was necessary, because of the special handling for lists 							 //
// constructors without lists had to be wrapped, because they are not 				 //
// recognized by python while a global function named like the class exists		 //
/////////////////////////////////////////////////////////////////////////////////

//////////////	cycle	constructors	//////////////////////

//.def(init<const lst &, optional<const ex &, const ex &, const ex &, const ex &> >())
//
static boost::shared_ptr<cycle>
do_init_with_llist_cycle(const GiNaC::ex & k1, boost::python::list bpl, const GiNaC::ex & m1,
    const GiNaC::ex & metr)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return boost::shared_ptr<cycle>( new cycle(k1, matrix(1,pyginac::length(bpl),l1), m1, metr));
}

static boost::shared_ptr<cycle>
do_init_with_list_cycle(boost::python::list bpl, const GiNaC::ex & metr,
    const GiNaC::ex & r_squared, const GiNaC::ex & e, const GiNaC::ex & sign)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return boost::shared_ptr<cycle>( new cycle(l1, metr, r_squared, e,
											   sign.is_zero()?(new tensdelta)->setflag(status_flags::dynallocated):sign));
}

//.def(init<const ex &, const ex &, const ex &,optional< const ex &> >())
static boost::shared_ptr<cycle>
do_init_4ex_cycle(const GiNaC::ex & k1, const GiNaC::ex & l1, const GiNaC::ex & m1,
    const GiNaC::ex & metr)
{
	return boost::shared_ptr<cycle>( new cycle(k1,l1,m1,metr));
}

//.def(init<const matrix &, const ex &, optional<const ex &, const ex &> >())
static boost::shared_ptr<cycle>
do_init_matrix_cycle(const GiNaC::matrix & M, const GiNaC::ex & metr, const GiNaC::ex & e, const GiNaC::ex & sign, const GiNaC::ex & dim)
{
	return boost::shared_ptr<cycle>( new cycle(M,metr,e,sign,dim));
}

static boost::shared_ptr<cycle>
do_init_cycle_cycle(const cycle & C, const ex & metr)
{
	return boost::shared_ptr<cycle>( new cycle(C,metr));
}

/////////////// cycle2D constructors /////////////////////

//.def(init<const lst &, optional<const ex &, const ex &, const ex &, const ex &> >())
static boost::shared_ptr<cycle2D>
do_init_with_llist_cycle2D(const GiNaC::ex & k1, boost::python::list bpl, const GiNaC::ex & m1,
						   const GiNaC::ex & metr)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return boost::shared_ptr<cycle2D>( new cycle2D(k1, matrix(1,pyginac::length(bpl),l1), m1, metr));
}

static boost::shared_ptr<cycle2D>
do_init_with_list_cycle2D(boost::python::list bpl, const GiNaC::ex & metr,
						  const GiNaC::ex & r_squared, const GiNaC::ex & e,
						  const GiNaC::ex & sign)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return boost::shared_ptr<cycle2D>( new cycle2D(l1, metr, r_squared, e, sign));
}

//.def(init<const ex &, const ex &, const ex &, optional<const ex &> >())
static boost::shared_ptr<cycle2D>
do_init_4ex_cycle2D(const GiNaC::ex & k1, const GiNaC::ex & l1, const GiNaC::ex & m1, const GiNaC::ex & metr)
{
	return boost::shared_ptr<cycle2D>( new cycle2D(k1,l1,m1,metr));
}

//.def(init<const matrix &, const ex &, optional<const ex &, const ex &> >())
static boost::shared_ptr<cycle2D>
do_init_matrix_cycle2D(const GiNaC::matrix & M, const GiNaC::ex & metr, const GiNaC::ex & e, const GiNaC::ex & sign)
{
	return boost::shared_ptr<cycle2D>( new cycle2D(M,metr,e,sign));
}

//.def(init<const cycle &>())
static boost::shared_ptr<cycle2D>
do_init_cycle_cycle2D(const cycle & C, const ex & metr)
{
	return boost::shared_ptr<cycle2D>( new cycle2D(C,metr));
}

static boost::shared_ptr<cycle2D>
do_init_cycle_cycle2D_from_basic(const basic & C)
{
	if (is_a<cycle2D>(C))
		return boost::shared_ptr<cycle2D>( new cycle2D(ex_to<cycle2D>(C)));
	else 	
		return boost::shared_ptr<cycle2D>( new cycle2D(ex_to<cycle>(C)));
}

///////////wrappers for constructors of cycle and cycle2D - end   ///////////////

///////////// Linear operations on cycles ///////////////////
inline cycle
do_add( const cycle& lhs, const cycle& rhs)
{
    return  lhs.add(rhs);
}

inline cycle
do_sub( const cycle& lhs, const cycle& rhs)
{
    return lhs.sub(rhs);
}

inline cycle
do_mul1( const cycle& lhs, const GiNaC::ex& rhs)
{
    return lhs.exmul(rhs);
}

inline cycle
do_mul2( const GiNaC::ex& lhs, const cycle& rhs)
{
    return rhs.exmul(lhs);
}

inline cycle
do_div( const cycle& lhs, const GiNaC::ex& rhs)
{
    return lhs.div(rhs);
}

inline GiNaC::ex
do_mul3( const cycle& lhs, const cycle& rhs)
{
    return lhs.mul(rhs);
}

//////////// Linear operations on cycle2D  ///////////
inline cycle2D
do_add2D( const cycle2D& lhs, const cycle2D& rhs)
{
    return lhs.add(rhs);
}

inline cycle2D
do_sub2D( const cycle2D& lhs, const cycle2D& rhs)
{
    return lhs.sub(rhs);
}

inline cycle2D
do_mul12D( const cycle2D& lhs, const GiNaC::ex& rhs)
{
    return lhs.exmul(rhs);
}

inline cycle2D
do_mul22D(const GiNaC::ex& lhs, const cycle2D& rhs)
{
    return rhs.exmul(lhs);
}

inline cycle2D
do_div2D( const cycle2D& lhs, const GiNaC::ex& rhs)
{
    return lhs.div(rhs);
}

//////////// Linear operations on cycles - end ///////////

///////////wrappers for boost::python::list arguments  - begin ///////////////////
GiNaC::ex
val_to_bpl(const cycle & C, boost::python::list y, const GiNaC::ex & x=1)
{
       GiNaC::lst ly;
       pyginac::lst_from_py_list(ly,y);
       return(C.val(ly,x));
}
GiNaC::ex
passing_to_bpl(const cycle & C, boost::python::list y)
{
       GiNaC::lst ly;
       pyginac::lst_from_py_list(ly,y);
       return(C.passing(ly));
}

class cycle
subject_to_bpl_bpl(const cycle & C, boost::python::list condition, boost::python::list vars)
{
	GiNaC::lst lcondition, lvars;
	pyginac::lst_from_py_list(lcondition,condition);
	pyginac::lst_from_py_list(lvars,vars);
	return C.subject_to(lcondition, lvars);
}

class cycle
subject_to_bpl(const cycle & C, boost::python::list condition)
{
	GiNaC::lst lcondition;
	pyginac::lst_from_py_list(lcondition,condition);
	return C.subject_to(lcondition);
}

string asy_string(const cycle2D & C, const GiNaC::ex & xmin = -5, const GiNaC::ex & xmax = 5,
				  const GiNaC::ex & ymin = -5, const GiNaC::ex & ymax = 5,
				  boost::python::list color = boost::python::list(), const string more_options = "",
				  bool with_header = true, int points_per_arc = 0, const string imaginary_options="rgb(0,.9,0)+4pt")
{
	std::ostringstream drawing;
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,color);
	C.asy_draw(drawing, xmin, xmax, ymin, ymax, l1, more_options, with_header, points_per_arc, imaginary_options);
	return drawing.str().c_str();
}

string asy_string_picture(const cycle2D & C, const string & picture,
				   const GiNaC::ex & xmin = -5, const GiNaC::ex & xmax = 5,
				  const GiNaC::ex & ymin = -5, const GiNaC::ex & ymax = 5,
				  boost::python::list color = boost::python::list(), const string more_options = "",
						  bool with_header = true, int points_per_arc = 0, const string imaginary_options="rgb(0,.9,0)+4pt")
{
	std::ostringstream drawing;
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,color);
	C.asy_draw(drawing, picture, xmin, xmax, ymin, ymax, l1, more_options, with_header, points_per_arc, imaginary_options);
	return drawing.str().c_str();
}


string asy_path_string(const cycle2D & C, const GiNaC::ex & xmin = -5, const GiNaC::ex & xmax = 5,
				const GiNaC::ex & ymin = -5, const GiNaC::ex & ymax = 5, 
					   int points_per_arc = 0, bool  is_continuation = false)
{
	std::ostringstream drawing;
	C.asy_path(drawing, xmin, xmax, ymin, ymax, points_per_arc, is_continuation);
	return drawing.str().c_str();
}

string cycle_to_string(const cycle & C)
{
	std::ostringstream drawing;
	drawing << C;
	return drawing.str().c_str();
}

cycle
sl2_similarity_lst(const cycle & C, boost::python::list bpl, const GiNaC::ex & e = 0,
	const GiNaC::ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
	bool not_inverse=true,
	const GiNaC::ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated))
{
       GiNaC::lst M;
       pyginac::lst_from_py_list(M, bpl);
       return C.sl2_similarity(M, e, sign, not_inverse, sign_inv);
}

cycle2D
sl2_similarity_lst1(const cycle2D & C, boost::python::list bpl, const GiNaC::ex & e = 0,
	const GiNaC::ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
	bool not_inverse=true,
	const GiNaC::ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated))
{
       GiNaC::lst M;
       pyginac::lst_from_py_list(M, bpl);
       return C.sl2_similarity(M, e, sign, not_inverse, sign_inv);
}

cycle2D
sl2_similarity_lst2(const cycle2D & C, boost::python::list bpl1, boost::python::list bpl2,
	const GiNaC::ex & e = 0,
	const GiNaC::ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
	bool not_inverse=true,
	const GiNaC::ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated))
{
	GiNaC::lst M1, M2;
	pyginac::lst_from_py_list(M1, bpl1);
	pyginac::lst_from_py_list(M2, bpl2);
	return C.sl2_similarity(M1, M2, e, sign, not_inverse, sign_inv);
}

cycle2D
sl2_similarity_elements2(const cycle2D & C, const ex & a, const ex & b, const ex & c, const ex & d,
	const ex & e = 0,
	const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
	bool not_inverse=true,
	const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated))
{
		return ex_to<cycle2D>(C.inherited::sl2_similarity(a, b, c, d, e, sign, not_inverse, sign_inv));
}

cycle2D
sl2_similarity_elements3(const cycle2D & C, const ex & M1, const ex & M2, const ex & e,
	const ex & sign,
	bool not_inverse=true,
	const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated))
{
	return C.sl2_similarity(M1, M2, e, sign, not_inverse, sign_inv);
}

ex
moebius_map_lst(const cycle & C, boost::python::list bpl, const ex & e = 0,
		const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated))
{
       GiNaC::lst M;
       pyginac::lst_from_py_list(M, bpl);
       return C.moebius_map(M, e, sign);
}

GiNaC::matrix
sl2_clifford_lst(boost::python::list bpl, const GiNaC::ex & e, bool not_inverse=true)
{
	GiNaC::lst M;
       pyginac::lst_from_py_list(M, bpl);
       return sl2_clifford(M,e,not_inverse);
}

GiNaC::matrix
sl2_clifford_lst2(boost::python::list bpl1, boost::python::list bpl2, const GiNaC::ex & e, bool not_inverse=true)
{
	GiNaC::lst M1, M2;
       pyginac::lst_from_py_list(M1, bpl1);
       pyginac::lst_from_py_list(M2, bpl2);
       return sl2_clifford(M1,M2,e,not_inverse);
}

cycle
subs_lst( const cycle& This, boost::python::list lhs)
{
    using namespace boost::python;

    std::map<ex, ex, GiNaC::ex_is_less> exmap;

    int end = pyginac::length(lhs);
    for (int i = 0; i != end; ++i) {
        GiNaC::relational equality = extract<GiNaC::relational>(lhs[i]);
        exmap[equality.op(0)] = equality.op(1);
		}
    return ex_to<cycle>(ex(This).subs( exmap));
}

cycle
subs_dict( const cycle& This, boost::python::dict rules)
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
	return ex_to<cycle>(ex(This).subs( exmap));
}

inline cycle2D
subs_lst_2D( const cycle2D& This, boost::python::list lhs)
{
    return ex_to<cycle2D>(subs_lst(This, lhs));
}

cycle
do_real_part(const cycle C)
{
	return ex_to<cycle>(C.real_part());
}

cycle
do_imag_part(const cycle C)
{
	return ex_to<cycle>(C.imag_part());
}

cycle2D
do_real_part_2D(const cycle2D C)
{
	return ex_to<cycle2D>(C.real_part());
}

cycle2D
do_imag_part_2D(const cycle2D C)
{
	return ex_to<cycle2D>(C.imag_part());
}

inline cycle2D
subs_dict_2D( const cycle2D& This, boost::python::dict rules)
{
	return ex_to<cycle2D>(subs_dict(This, rules));
}

class cycle2D
subject_to_bpl_bpl_2D(const cycle2D & C, boost::python::list condition, boost::python::list vars)
{
	GiNaC::lst lcondition, lvars;
	pyginac::lst_from_py_list(lcondition,condition);
	pyginac::lst_from_py_list(lvars,vars);
	return C.subject_to(lcondition, lvars);
}

class cycle2D
subject_to_bpl_2D(const cycle2D & C, boost::python::list condition)
{
	GiNaC::lst lcondition;
	pyginac::lst_from_py_list(lcondition,condition);
	return C.subject_to(lcondition);
}

///////////wrappers for boost::python::list arguments  - end           ///////////////////


//wrapper for with macro declared function jump_fnct
GiNaC::ex
do_jump_fnct(const GiNaC::ex & e)
{
	return jump_fnct(e);
}

//overloads for class cycle

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(subs_overloads, subs, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(normalize_overloads, normalize, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(center_overloads, center, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(subject_to_overloads, subject_to, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(to_matrix_overloads, to_matrix, 0, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( det_overloads, det, 0, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(hdet_overloads, hdet, 0, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(radius_sq_overloads, radius_sq, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(mul_overloads, mul, 1, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(sl2_similarity_elements_overloads, sl2_similarity, 4, 8)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(sl2_similarity_matrix_overloads, sl2_similarity, 1, 5)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(matrix_similarity_elements_overloads, matrix_similarity, 4, 8)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(matrix_similarity_matrix_overloads, matrix_similarity, 1, 5)
//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(matrix_similarity_overloads, matrix_similarity, 4, 8)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(cycle_similarity_overloads, cycle_similarity, 1, 5)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(moebius_map_overloads, moebius_map, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(cycle_product_overloads, cycle_product, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(is_equal_overloads, is_equal, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(is_orthogonal_overloads, is_orthogonal, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(is_f_orthogonal_overloads, is_f_orthogonal, 1, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(normalize_det_overloads, normalize_det, 0, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(normalize_norm_overloads, normalize_norm, 0, 4)

//overloads for class cycle2D
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(subs_2D_overloads, subs, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(subject_to_2D_overloads, subject_to, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(normalize_2D_overloads, normalize, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(sl2_similarity_2D_elements_overloads1, sl2_similarity, 8, 12)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(focus_overloads, focus, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(roots_overloads, roots, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(metapost_draw_overloads, metapost_draw, 1, 14)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(asy_draw_picture_overloads, asy_draw, 2, 11)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(asy_draw_nopicture_overloads, asy_draw, 0, 10)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(asy_path_overloads, asy_path, 1, 7)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(normalize_det_2D_overloads, normalize_det, 0, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(normalize_norm_2D_overloads, normalize_norm, 0, 4)


//overloads for functions outside the classes
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_clifford_elements_overloads, sl2_clifford, 5, 6)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_clifford_elements_overloads2, sl2_clifford, 9, 10)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_clifford_matrix_overloads, sl2_clifford, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_clifford_matrix_overloads2, sl2_clifford, 3, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_clifford_lst_overloads, sl2_clifford_lst, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_clifford_lst_overloads2, sl2_clifford_lst2, 3, 4)

BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_similarity_lst_overloads, sl2_similarity_lst, 2, 5)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_similarity_lst_2D_overloads1, sl2_similarity_lst1, 2, 5)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_similarity_lst_2D_overloads2, sl2_similarity_lst2, 3, 6)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_similarity_2D_elements_overloads2, sl2_similarity_elements2, 5, 9)
BOOST_PYTHON_FUNCTION_OVERLOADS(sl2_similarity_2D_elements_overloads3, sl2_similarity_elements3, 5, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(matrix_similarity4_overloads, matrix_similarity4, 2, 6)
BOOST_PYTHON_FUNCTION_OVERLOADS(matrix_similarity7_overloads, matrix_similarity7, 5, 9)
BOOST_PYTHON_FUNCTION_OVERLOADS(moebius_map_lst_overloads, moebius_map_lst, 2, 4)
BOOST_PYTHON_FUNCTION_OVERLOADS(val_to_bpl_overloads, val_to_bpl, 2, 3)

//overloads for asymptote calls
BOOST_PYTHON_FUNCTION_OVERLOADS(asy_string_overloads, asy_string, 1, 9)
BOOST_PYTHON_FUNCTION_OVERLOADS(asy_string_picture_overloads, asy_string_picture, 2, 10)
BOOST_PYTHON_FUNCTION_OVERLOADS(asy_path_string_overloads, asy_path_string, 1, 7)

//} // !namespace anonymous

void
wrap_cycle(void)
{
  using namespace boost::python;
  using GiNaC::basic;
  using GiNaC::ex;
  using GiNaC::lst;
  using GiNaC::matrix;
  using GiNaC::numeric;

//difficult overloads for cycle
ex (cycle::*get_metric0)() const = &cycle::get_metric;
ex (cycle::*get_metric2)(const ex &, const ex &) const = &cycle::get_metric;
ex (cycle::*get_l0)() const = &cycle::get_l;
ex (cycle::*get_l1)(const ex &) const = &cycle::get_l;
cycle (cycle::*sl2_similarity_elements)(const ex &, const ex &, const ex &, const ex &, 
const ex &, const ex &, bool, const ex &)const = &cycle::sl2_similarity;
cycle (cycle::*sl2_similarity_matrix)(const ex &, const ex &, const ex &, bool, const ex &)const = &cycle::sl2_similarity;
cycle (cycle::*matrix_similarity_elements)(const ex &, const ex &, const ex &, const ex &, 
const ex &, const ex &, bool, const ex &)const = &cycle::matrix_similarity;
cycle (cycle::*matrix_similarity_matrix)(const ex &, const ex &, const ex &, bool, const ex &)const = &cycle::matrix_similarity;

	class_<cycle, bases<basic> >
		("cycle",
		 "The class describes loci of points x in R^n definded by kx^2-2<l,x>+m=0",
		 no_init)
		//the following constructor is wrapped in a function below (outside the class) because of lst
#if __cplusplus >= 201703L
		.def(init<const lst &>())
		.def(init<const lst &, const ex &>())
		.def(init<const lst &, const ex &, const ex &>())
		.def(init<const lst &, const ex &, const ex &, const ex &>())
		.def(init<const lst &, const ex &, const ex &, const ex &, const ex &>())
#else
		.def(init<const lst &, optional<const ex &, const ex &, const ex &, const ex &> >())
#endif
	 
#if __cplusplus >= 201703L
		.def(init<const ex &, const ex &, const ex &>())
		.def(init<const ex &, const ex &, const ex &, const ex &>())
#else
		.def(init<const ex &, const ex &, const ex &, optional<const ex &> >())
#endif

#if __cplusplus >= 201703L
		.def(init<const matrix &, const ex &>())
		.def(init<const matrix &, const ex &, const ex &>())
		.def(init<const matrix &, const ex &, const ex &, const ex &>())
#else
		.def(init<const matrix &, const ex &, optional<const ex &, const ex &> >())
#endif
		.def("__init__", make_constructor(do_init_with_llist_cycle,  default_call_policies(),
										  (boost::python::arg("k1"),boost::python::arg("bpl"),boost::python::arg("m1"),
										   boost::python::arg("metr")= -(new tensdelta)->setflag(status_flags::dynallocated))), "Inititialise a cycle from list of parameters")
		.def("__init__", make_constructor(do_init_with_list_cycle,default_call_policies(),
										  (boost::python::arg("bpl"),
										   boost::python::arg("metr")= ex(-(new tensdelta)->setflag(status_flags::dynallocated)),
										   boost::python::arg("r_squared") = 0,
										   boost::python::arg("e")=0,
										   boost::python::arg("sign")= 0)),
			 "Inititialise a cycle from list presenting centre and radius")
		.def("__init__", make_constructor(do_init_4ex_cycle,  default_call_policies(),
										  (boost::python::arg("k1"),boost::python::arg("l1"),boost::python::arg("m1"),
										   boost::python::arg("metr") = -(new tensdelta)->setflag(status_flags::dynallocated))),
			 "Inititialise a cycle from four expressions")
		.def("__init__", make_constructor(do_init_matrix_cycle,  default_call_policies(),
										  (boost::python::arg("M"), boost::python::arg("metr"),
										   boost::python::arg("e") = 0, boost::python::arg("sign") = 0)),
			 "Inititialise a cycle from a matrix and metric")
		.def("__init__", make_constructor(do_init_cycle_cycle), "Inititialise a cycle from a cycle")
		.def( "__add__", do_add)
		.def( "__sub__", do_sub)
		.def( "__mul__", do_mul1)
		.def( "__mul__", do_mul2)
		.def( "__mul__", do_mul3)
		.def( "__div__", do_div)
		.def( "add", &cycle::add)
		.def( "sub", &cycle::sub)
		.def( "mul", do_mul3)
		.def( "exmul", &cycle::exmul)
		.def( "div", &cycle::div)
		.def("get_dim", &cycle::get_dim)
		.def("get_metric", get_metric0, "Get metric of the cycle")
		.def("get_metric", get_metric2, "Get metric of the cycle")
		.def("get_k", &cycle::get_k)
		.def("get_l", get_l0)
		.def("get_l", get_l1)
		.def("get_m", &cycle::get_m)
		.def("get_unit", &cycle::get_unit)
		.def("nops", &cycle::nops)
		.def("op", &cycle::op)
		.def("let_op", &cycle::let_op, return_internal_reference<>())	//throws warning in compile time
		.def("normal", &cycle::normal, "returns cycle with normalized components")
		.def("expand", &cycle::expand, "returns cycle with expanded components")
		.def("is_equal", &cycle::is_equal, is_equal_overloads())
		.def("the_same_as", &cycle::the_same_as)
		.def("is_zero", &cycle::is_zero)

		.def("string", cycle_to_string, "Output cycle as a string")
		.def("subs", subs_lst)
		.def("subs", subs_dict)
		.def("subs", &cycle::subs, subs_overloads())
		.def("normalize", &cycle::normalize, normalize_overloads())
		.def("normalize_det",&cycle::normalize_det, normalize_det_overloads())
		.def("normalize_norm",&cycle::normalize_norm, normalize_norm_overloads())
		.def("center", &cycle::center, center_overloads())
		.def("val", &cycle::val)
		.def("val", val_to_bpl, val_to_bpl_overloads())
		.def("passing", passing_to_bpl)
		.def("passing", &cycle::passing)

		.def("subject_to", &cycle::subject_to, subject_to_overloads())
		.def("subject_to", subject_to_bpl_bpl, "Calculation of a cycle subject to given conditions")
		.def("subject_to", subject_to_bpl, "Calculation of a cycle subject to given conditions (default vars)")
		.def("to_matrix", &cycle::to_matrix, to_matrix_overloads())
		.def("det", &cycle::det, det_overloads())
		.def("radius_sq", &cycle::radius_sq, radius_sq_overloads())
		.def("mul", &cycle::mul, mul_overloads())
		.def("sl2_similarity", sl2_similarity_elements, sl2_similarity_elements_overloads())//ok
		.def("sl2_similarity", sl2_similarity_matrix, sl2_similarity_matrix_overloads())		//ok
//		.def("sl2_similarity", sl2_similarity_matrix, sl2_similarity_matrix_overloads())
                //ok
		.def("sl2_similarity", sl2_similarity_lst, sl2_similarity_lst_overloads())
//		.def("matrix_similarity", matrix_similarity4, matrix_similarity4_overloads())	//ok
//		.def("matrix_similarity", matrix_similarity7, matrix_similarity7_overloads())	//ok
		.def("matrix_similarity", matrix_similarity_elements, matrix_similarity_elements_overloads())//ok
		.def("matrix_similarity", matrix_similarity_matrix, matrix_similarity_matrix_overloads())		//ok
		.def("cycle_similarity", &cycle::cycle_similarity, cycle_similarity_overloads())		//ok
		.def("moebius_map", &cycle::moebius_map, moebius_map_overloads())
		.def("moebius_map", moebius_map_lst, moebius_map_lst_overloads())
		.def("cycle_product", &cycle::cycle_product, cycle_product_overloads())
		.def("is_orthogonal", &cycle::is_orthogonal, is_orthogonal_overloads())
		.def("is_f_orthogonal", &cycle::is_f_orthogonal, is_f_orthogonal_overloads())
		.def("is_linear", &cycle::is_linear)
		.def("evalf", &cycle::evalf, "Float evaluation of the cycle")
		.def("real_part", do_real_part, "the real part of cycle as a vector")
		.def("imag_part", do_imag_part, "the imaginary part of cycle as a vector")
		.def("is_normalized", &cycle::is_normalized)
		;

	//difficult overloads for cycle2D
	cycle2D (cycle2D::*sl2_similarity_matrix1)(const ex &)const = &cycle2D::sl2_similarity;
	cycle2D (cycle2D::*sl2_similarity_matrix2)(const ex &, const ex &)const = &cycle2D::sl2_similarity;
	cycle2D (cycle2D::*sl2_similarity_matrix3)(const ex &, const ex &, const ex &)const = &cycle2D::sl2_similarity;
	cycle2D (cycle2D::*sl2_similarity_elements1)(const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, bool, const ex &)const = &cycle2D::sl2_similarity;
	void (cycle2D::*asy_draw_picture)(ostream &, const std::string, const ex &, const ex &, const ex &, const ex &, const lst &, const string, bool, int, const string) const = &cycle2D::asy_draw;
	void (cycle2D::*asy_draw_nopicture)(ostream &, const ex &, const ex &, const ex &, const ex &, const lst &, const string, bool, int, const string) const = &cycle2D::asy_draw;
	void (cycle2D::*asy_path)(ostream &, const ex &, const ex &, const ex &, const ex &, int, bool) const = &cycle2D::asy_path;
	//in class cycle2D all ok
	class_<cycle2D, bases<cycle> >
		("cycle2D",
		 "derived from cycle, here are only very few specific methods for two dimensions, notably for the visualisation added.",
		 no_init)
		//the following constructors are wrapped in functions below (outside the class) because of lst
#if __cplusplus >= 201703L
		.def(init<const ex &, const ex &, const ex &>())
		.def(init<const ex &, const ex &, const ex &, const ex &>())
#else
		.def(init<const ex &, const ex &, const ex &, optional<const ex &> >())
#endif
#if __cplusplus >= 201703L
		.def(init<const lst &>())
		.def(init<const lst &, const ex &>())
		.def(init<const lst &, const ex &, const ex &>())
		.def(init<const lst &, const ex &, const ex &, const ex &>())
		.def(init<const lst &, const ex &, const ex &, const ex &, const ex &>())
#else
		.def(init<const lst &, optional<const ex &, const ex &, const ex &, const ex &> >())
#endif
		.def(init<const cycle &>())

		.def("__init__", make_constructor(do_init_with_llist_cycle2D,  default_call_policies(),
										  (boost::python::arg("k1"),boost::python::arg("bpl"),boost::python::arg("m1"),
										   boost::python::arg("metr") = GiNaC::diag_matrix(GiNaC::lst{-1, -1}))),
			 "Initialise cycle2D from a list of parameters")
		.def("__init__", make_constructor(do_init_with_list_cycle2D,  default_call_policies(),
										  (boost::python::arg("bpl"),
										   boost::python::arg("metr")=GiNaC::diag_matrix(GiNaC::lst{-1,-1}),
										   boost::python::arg("r_squared")=0,
										   boost::python::arg("e")=0,
										   boost::python::arg("sign") = GiNaC::diag_matrix(GiNaC::lst{1,1}))),
			 "Initialise cycle2D from a list defining its centre and radius")
		.def("__init__", make_constructor(do_init_4ex_cycle2D,  default_call_policies(),
										  (boost::python::arg("k1"),boost::python::arg("l1"),
										   boost::python::arg("m1"),
										   boost::python::arg("metr") = GiNaC::diag_matrix(GiNaC::lst{-1, -1}))),
			 "Initialise cycle2D from four expressions")
		.def("__init__", make_constructor(do_init_matrix_cycle2D,  default_call_policies(),
										  (boost::python::arg("M"),boost::python::arg("metr"),
										   boost::python::arg("e")=0,
										   boost::python::arg("sign")=0)),
			 "Initialise cycle2D from a matrix")
		.def("__init__", make_constructor(do_init_cycle_cycle2D,  default_call_policies(),
										  (boost::python::arg("C"),boost::python::arg("metr")=0)),
			 "Initialise cycle2D from a cycle")
		.def("__init__", make_constructor(do_init_cycle_cycle2D_from_basic),
			 "Initialise cycle2D from a Ginac::basic (yet cycle)")
		.def( "__add__", do_add2D)
		.def( "__sub__", do_sub2D)
		.def( "__mul__", do_mul12D)
		.def( "__mul__", do_mul22D)
		.def( "__div__", do_div2D)
		.def("sl2_similarity", sl2_similarity_elements1, sl2_similarity_2D_elements_overloads1("SL2 similarity by eight elements of two matrices"))//ok
		.def("sl2_similarity", sl2_similarity_elements2, sl2_similarity_2D_elements_overloads2("SL2 similarity vy fiur elements of one real matrix"))//ok
		.def("sl2_similarity", sl2_similarity_elements3, sl2_similarity_2D_elements_overloads3("SL2 similarity by two real matrices, Clifford unit and sign"))//ok
		.def("sl2_similarity", sl2_similarity_lst1, sl2_similarity_lst_2D_overloads1("SL2 similairity by a list representing one matrix"))		//ok
		.def("sl2_similarity", sl2_similarity_lst2, sl2_similarity_lst_2D_overloads2("SL2 similairity by a two lists representing two matrices"))		//ok
		.def("sl2_similarity", sl2_similarity_matrix1, "SL2 similarity with one real matrix")		//ok
		.def("sl2_similarity", sl2_similarity_matrix2, "SL2 similarity with two real matrices, or two one real matrix and a different unit")		//ok
		.def("sl2_similarity", sl2_similarity_matrix3, "SL2 similarity with two real matrices and a different unit")		//ok
		.def("sl2_similarity", sl2_similarity_lst, sl2_similarity_lst_overloads())
		.def("normal", &cycle2D::normal, "returns cycle2D with normalized components")
		.def("expand", &cycle2D::expand, "returns cycle2D with expanded components")
		.def("hdet", &cycle2D::hdet, hdet_overloads())
		.def("focus", &cycle2D::focus, focus_overloads("returns focus of the cycle"))
		.def("focal_length", &cycle2D::focal_length, "focal length of the cycle")
		.def("roots", &cycle2D::roots, roots_overloads("roots of a cycle"))
		.def("line_intersect", &cycle2D::line_intersect, "intersection points with the line ax+b")
		.def("metapost_draw",&cycle2D::metapost_draw, metapost_draw_overloads())
		.def("asy_draw", asy_draw_picture, asy_draw_picture_overloads())
		.def("asy_draw", asy_draw_nopicture, asy_draw_nopicture_overloads())
		.def("asy_path", asy_path, asy_path_overloads())
		.def("asy_string", asy_string, asy_string_overloads())
		.def("asy_string", asy_string_picture, asy_string_picture_overloads())
		.def("asy_path_string", asy_path_string, asy_path_string_overloads())
		.def("subject_to", subject_to_bpl_bpl_2D, "Calculation of a cycle subject to given conditions")
		.def("subject_to", subject_to_bpl_2D, "Calculation of a cycle subject to given conditions (default vars)")
		.def("subject_to", &cycle2D::subject_to, subject_to_2D_overloads())
		.def("subs", subs_lst_2D)
		.def("subs", subs_dict_2D)
		.def("subs", &cycle2D::subs, subs_2D_overloads("Substitution of values into cycle"))
		.def("real_part", do_real_part_2D, "the real part of cycle as a vector")
		.def("imag_part", do_imag_part_2D, "the imaginary part of cycle as a vector")
		.def("evalf", &cycle2D::evalf, "Float evaluation of the cycle")
		.def("normalize", &cycle2D::normalize, normalize_2D_overloads())
		.def("normalize_det",&cycle2D::normalize_det,normalize_det_2D_overloads())
		.def("normalize_norm",&cycle2D::normalize_norm,normalize_norm_2D_overloads())
		;

//difficult overloads for functions in no class
matrix (*sl2_clifford_elements)(const ex &, const ex &, const ex &, const ex &, const ex &, bool) = &sl2_clifford;
matrix (*sl2_clifford_matrix)(const ex &, const ex &, bool) = &sl2_clifford;
matrix (*sl2_clifford_elements2)(const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, const ex &, bool) = &sl2_clifford;
matrix (*sl2_clifford_matrix2)(const ex &, const ex &, const ex &, bool) = &sl2_clifford;

const string (*equality1)(const ex &) = &equality;
const string (*equality2)(const ex &, const ex &) = &equality;
const string (*equality3)(const ex &, const ex &, const ex &) = &equality;

//function which are in no class

	def("equality", equality1);	//ok
	def("equality", equality2);	//ok
	def("equality", equality3);	//ok
	def("eph_case", &eph_case, "Return the string describing the case (elliptic, parabolic or hyperbolic)");
	def("scalar_part", &scalar_part, "Return even (real) part of a Clifford number");		//ok
//	def("clifford_part", &clifford_part, "Return odd part of a Clifford number");							//ok
	def("sl2_clifford", sl2_clifford_elements, sl2_clifford_elements_overloads("Produces a Clifford matrix form of element of SL2"));	//ok
	def("sl2_clifford", sl2_clifford_matrix, sl2_clifford_matrix_overloads("Produces a Clifford matrix form of element of SL2"));			//ok
	def("sl2_clifford", sl2_clifford_lst, sl2_clifford_lst_overloads("Produces a Clifford matrix form of element of SL2"));
	def("sl2_clifford", sl2_clifford_elements2, sl2_clifford_elements_overloads2("Produces a Clifford matrix form of element of SL2"));	//ok
	def("sl2_clifford", sl2_clifford_matrix2, sl2_clifford_matrix_overloads2("Produces a Clifford matrix form of element of SL2"));			//ok
	def("sl2_clifford", sl2_clifford_lst2, sl2_clifford_lst_overloads2("Produces a Clifford matrix form of element of SL2"));
	def("jump_fnct", do_jump_fnct);

} // !cycle_wrap()

} // !namespace pyginac

// The pyGiNaC wrapper of cycle library for Lie sphere geometry.
//
//  Copyright (C) 2007-2018 Vladimir V. Kisil <kisilv@maths.leeds.ac.uk>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
