#line 5614 "cycle.nw"
// The library to operate cycles in non-Euclidean geometry
//
//  Copyright (C) 2004-2018 Vladimir V. Kisil
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

#line 3359 "cycle.nw"
#include <cycle.h>
namespace MoebInv {
using namespace std;
using namespace GiNaC;

#define PRINT_CYCLE  c.s << "("; \
 k.print(c, level); \
 c.s << ", "; \
 l.print(c, level); \
 c.s << ", "; \
 m.print(c, level); \
 c.s << ")";

#line 3374 "cycle.nw"
 GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle, basic,
           print_func<print_dflt>(&cycle::do_print).
									  //           print_func<print_python>(&cycle::do_print_python).
           print_func<print_latex>(&cycle::do_print_latex))

 GINAC_IMPLEMENT_REGISTERED_CLASS(cycle2D, cycle)
//,    print_func<print_dflt>(&cycle2D::do_print)

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(paravector, basic,
										 print_func<print_dflt>(&paravector::do_print).
										 print_func<print_latex>(&paravector::do_print_latex))

#line 3388 "cycle.nw"
return_type_t cycle::return_type_tinfo() const
{
	if (is_a<numeric>(get_dim()))
		switch (ex_to<numeric>(get_dim()).to_int()) {
		case 2:
			return make_return_type_t<cycle2D>();
		default:
		return make_return_type_t<cycle>();
		}
	else
		return make_return_type_t<cycle>();
}

cycle::cycle() : unit(), k(), l(), m()
{
}

#line 3411 "cycle.nw"
cycle::cycle(const ex & k1, const ex & l1, const ex & m1, const ex & metr) // Main constructor
 : k(k1), m(m1)
{
	ex D, metric;

#line 3419 "cycle.nw"
	  if (is_a<indexed>(l1.simplify_indexed())) {
		  l = ex_to<indexed>(l1.simplify_indexed());
		  if (ex_to<indexed>(l).get_indices().size() == 1) {
			  D = ex_to<varidx>(ex_to<indexed>(l).get_indices()[0]).get_dim();
		  } else
			  throw(std::invalid_argument("cycle::cycle(): the second parameter should be an indexed object"
										  "with one varindex"));
	  } else if (is_a<matrix>(l1) && (min(ex_to<matrix>(l1).rows(), ex_to<matrix>(l1).cols()) ==1)) {
		  D = max(ex_to<matrix>(l1).rows(), ex_to<matrix>(l1).cols());
		  l = indexed(l1, varidx((new symbol)->setflag(status_flags::dynallocated), D));
	  } else if (l1.info(info_flags::list) && (l1.nops() > 0)) {
		  D = l1.nops();
		  l = indexed(matrix(1, l1.nops(), ex_to<lst>(l1)),
					  varidx((new symbol)->setflag(status_flags::dynallocated), D));

#line 3437 "cycle.nw"
	} else if (not l1.simplify_indexed().is_zero()) {
		  throw(std::invalid_argument("cycle::cycle(): the second parameter should be an indexed object, "
									  "matrix or list"));
	  }

#line 3445 "cycle.nw"
	if (is_a<clifford>(metr)) {
		if (D.is_zero())
			D = ex_to<varidx>(metr.op(1)).get_dim();
		unit =metr;
	} else {
		if (D.is_zero()) {
			if (is_a<indexed>(metr))
				D = ex_to<varidx>(metr.op(1)).get_dim();
			else if (is_a<matrix>(metr))
				D = ex_to<matrix>(metr).rows();
			else {
				exvector indices = metr.get_free_indices();
				if (indices.size() == 2)
					D = ex_to<varidx>(indices[0]).get_dim();
			}
		}

#line 3464 "cycle.nw"
	if (D.is_zero())
		throw(std::invalid_argument("cycle::cycle(): the metric should be either tensor, "
									"matrix, Clifford unit or indexed by two indices. "
									"Otherwise supply the through the second parameter."));

#line 3472 "cycle.nw"
	try {
		unit = clifford_unit(varidx((new symbol)->setflag(status_flags::dynallocated), D), metr);
	} catch (std::exception &p) {
		try {
			unit = clifford_unit(varidx((new symbol)->setflag(status_flags::dynallocated), D-1), metr);
		} catch (std::exception &p1) {
			throw(std::invalid_argument("cycle::cycle(): the metricis not suitable for both vector "
										"and paravector formalism"));
		}
	}
}
}

#line 3492 "cycle.nw"
cycle::cycle(const lst & l, const ex & metr, const ex & r_squared, const ex & e, const ex & sign)
{
	symbol m_temp;
	cycle C(numeric(1), l, m_temp, metr);
	(*this) = C.subject_to(lst{C.radius_sq(e, sign) == r_squared}, lst{m_temp});
}

#line 3502 "cycle.nw"
cycle::cycle(const cycle & C, const ex & metr)
{
	(*this) = metr.is_zero()? C : cycle(C.get_k(), C.get_l(), C.get_m(), metr);
}

#line 3510 "cycle.nw"
cycle::cycle(const matrix & M, const ex & metr, const ex & e, const ex & sign, const ex & dim)
{
	
#line 3615 "cycle.nw"
ex e1, D=dim;
if (e.is_zero()) {
	if (is_a<clifford>(metr)) {
		D=ex_to<varidx>(metr.op(1)).get_dim();
		e1=metr;
	} else {
		ex metr1;
		if (is_a<matrix>(metr)) {
			D = ex_to<matrix>(metr).cols();
			metr1 = metr;
		} else if (is_a<indexed>(metr)) {
			D = ex_to<varidx>(ex_to<indexed>(metr).get_indices()[0]).get_dim();
			metr1 = metr;
		} else
			throw(std::invalid_argument("cycle(): Could not determine the dimensionality of point space "
										"from the supplied metric or Clifford unit"));

		e1 = clifford_unit(varidx((new symbol)->setflag(status_flags::dynallocated), D), metr1);
	}
} else {
	if (! is_a<clifford>(e))
		throw(std::invalid_argument("cycle(): if e is supplied, it shall be a Clifford unit"));
	e1 = e;
	D = ex_to<varidx>(e.op(1)).get_dim();
 }

#line 3513 "cycle.nw"
	ex M1=M;
	bool is_vector=(dim==0 || dim==D);
	ex Dsp=is_vector?D:dim;

	// Expensive checks, if this conditions are not satisfied,
	// corresponding errors will be generated later by the constructor
	/*
	if (is_vector &&
		not (M.rows() == 2 && M.cols() == 2 && (M.op(0)+M.op(3)).normal().is_zero()))
		throw(std::invalid_argument("cycle::cycle(): in vector formalism the second argument should be "
		"square 2x2 matrix with M(1,1)=-M(2,2)"));

	if (not is_vector &&
		not (M.rows() == 2 && M.cols() == 2 && (M.op(0)+clifford_bar(M.op(3))).normal().is_zero()))
		throw(std::invalid_argument("cycle::cycle(): in paravector formalism the second argument should"
		" be square 2x2 matrix with M(1,1)=-bar(M)(2,2)")); */

#line 3533 "cycle.nw"
if (sign.is_zero()) {
	try {
		lst l0=ex_to<lst>(clifford_to_lst(M.op(0), e1));
		
#line 3540 "cycle.nw"
		if (l0.nops()<Dsp) {
			lst l1=lst{0};
			for (auto & x: l0)
				l1.append(x);
			l0=l1;
		}


#line 3550 "cycle.nw"
		(*this) = cycle(remove_dirac_ONE(M.op(2)), l0, (is_vector?1:-1)*remove_dirac_ONE(M.op(1)), metr);
	} catch  (std::exception &p) {
		lst l0=ex_to<lst>(clifford_to_lst(M.op(0)*clifford_inverse(M.op(2)), e1));
		
#line 3540 "cycle.nw"
		if (l0.nops()<Dsp) {
			lst l1=lst{0};
			for (auto & x: l0)
				l1.append(x);
			l0=l1;
		}

#line 3554 "cycle.nw"
		(*this) = cycle(numeric(1), l0,
						(is_vector?1:-1)*canonicalize_clifford(M.op(1)*clifford_inverse(M.op(2))), metr);
	}
} else {
	varidx i0((new symbol)->setflag(status_flags::dynallocated), Dsp),
		i1((new symbol)->setflag(status_flags::dynallocated), Dsp, true);

	ex sign_m, conv;
	sign_m = sign.evalm();

#line 3566 "cycle.nw"
	if (is_a<tensor>(sign_m))
		conv = indexed(ex_to<tensor>(sign_m), i0, i1);
	else if (is_a<clifford>(sign_m)) {
		if (ex_to<varidx>(sign_m.op(1)).get_dim() == Dsp)
			conv = ex_to<clifford>(sign_m).get_metric(i0, i1);
		else
			throw(std::invalid_argument("cycle::cycle(): the sign should be a Clifford unit with "
										"the dimensionality matching to the second parameter"));
	} else if (is_a<indexed>(sign_m)) {
		exvector ind = ex_to<indexed>(sign_m).get_indices();
		if ((ind.size() == 2) && (ex_to<varidx>(ind[0]).get_dim() == Dsp) && (ex_to<varidx>(ind[1]).get_dim() == Dsp))
			conv = sign_m.subs(lst{ind[0] == i0, ind[1] == i1});
		else
			throw(std::invalid_argument("cycle::cycle(): the sign should be an indexed object "
										"with two indices and their dimensionality matching to "
										"the second parameter"));

#line 3585 "cycle.nw"
	} else if (is_a<matrix>(sign_m)) {
		if ((ex_to<matrix>(sign_m).cols() == Dsp) && (ex_to<matrix>(sign_m).rows() == Dsp))
			conv = indexed(ex_to<matrix>(sign_m), i0, i1);
		else
			throw(std::invalid_argument("cycle::cycle(): the sign should be a square matrix with the "
										"dimensionality matching to the second parameter"));
	} else
		throw(std::invalid_argument("cycle::cycle(): the sign should be either tensor, indexed, matrix "
									"or Clifford unit"));

#line 3598 "cycle.nw"
	try {
		lst l0=ex_to<lst>(clifford_to_lst(M.op(0), e1));
		
#line 3540 "cycle.nw"
		if (l0.nops()<Dsp) {
			lst l1=lst{0};
			for (auto & x: l0)
				l1.append(x);
			l0=l1;
		}

#line 3601 "cycle.nw"
		(*this) = cycle(remove_dirac_ONE(M.op(2)), indexed(matrix(1, ex_to<numeric>(Dsp).to_int(),
																   l0), i0.toggle_variance())*conv, (is_vector?1:-1)*remove_dirac_ONE(M.op(1)), metr);
	} catch  (std::exception &p) {
		lst l0=ex_to<lst>(clifford_to_lst(M.op(0)*clifford_inverse(M.op(2)), e1));
		
#line 3540 "cycle.nw"
		if (l0.nops()<Dsp) {
			lst l1=lst{0};
			for (auto & x: l0)
				l1.append(x);
			l0=l1;
		}

#line 3606 "cycle.nw"
		(*this) = cycle(numeric(1), indexed(matrix(1, ex_to<numeric>(Dsp).to_int(), l0), i0.toggle_variance())*conv,
						(is_vector?1:-1)*canonicalize_clifford(M.op(1)*clifford_inverse(M.op(2))), metr);
	}
}
}

#line 3647 "cycle.nw"
ex expand_paravector_metric(const ex & unit) {
	int D=ex_to<numeric>(ex_to<idx>(unit.get_free_indices()[0]).get_dim()).to_int();
	matrix M=ex_to<matrix>(unit_matrix(D+1));
	M(0,0)=numeric(-1);
	for (int i=0; i<D; ++i)
		for (int j=0; j<D; ++j)
			M(i+1,j+1)=ex_to<clifford>(unit).get_metric(i,j);
	return indexed(M, varidx((new symbol)->setflag(status_flags::dynallocated), D+1),
				   varidx((new symbol)->setflag(status_flags::dynallocated), D+1));
}

#line 3660 "cycle.nw"
ex cycle::get_metric() const {
	if (ex_to<idx>(unit.op(1)).get_dim() == get_dim())
		return ex_to<clifford>(unit).get_metric();
	else if (is_a<numeric>(get_dim())) {
		return expand_paravector_metric(unit);
	} else
		throw(std::runtime_error("cycle::get_metric(): cannot return metric for paravector formalism "
								 "with symbolic dimensions"));
}

#line 3672 "cycle.nw"
ex cycle::get_metric(const ex &i0, const ex &i1) const {
	if (ex_to<idx>(unit.op(1)).get_dim() == get_dim())
		return ex_to<clifford>(unit).get_metric(i0, i1);

#line 3679 "cycle.nw"
	else if (is_a<idx>(i0) && ex_to<idx>(i0).is_numeric() &&
			 is_a<idx>(i1) && ex_to<idx>(i1).is_numeric()) {
		int j0= ex_to<numeric>(ex_to<idx>(i0).get_value()).to_int(),
			j1= ex_to<numeric>(ex_to<idx>(i1).get_value()).to_int();
		if ( j0 > 0 && j1 > 0)
			return ex_to<clifford>(unit).get_metric(varidx(j0-1,get_dim()-1), varidx(j1-1,get_dim()-1));
		else if ( j0 == 0 && j1 == 0)
			return -numeric(1);
		else
			return 0;
	} else if (is_a<numeric>(get_dim())) {
		ex metr=expand_paravector_metric(unit);
		return metr.subs(lst{metr.op(1)==i0,metr.op(2)==i1});
	} else
		throw(std::runtime_error("cycle::get_metric(): cannot return metric for paravector formalism "
								 "with symbolic dimensions"));
 }

#line 3699 "cycle.nw"
ex cycle::op(size_t i) const
{
 GINAC_ASSERT(i<nops());

 switch (i) {
 case 0:
  return k;
 case 1:
  return l;
 case 2:
  return m;
 case 3:
  return unit;
 default:
  throw(std::invalid_argument("cycle::op(): requested operand out of the range (4)"));
 }
}

#line 3719 "cycle.nw"
ex & cycle::let_op(size_t i)
{
 GINAC_ASSERT(i<nops());

 ensure_if_modifiable();
 switch (i) {
 case 0:
  return k;
 case 1:
  return l;
 case 2:
  return m;
 case 3:
  return unit;
 default:
  throw(std::invalid_argument("cycle::let_op(): requested operand out of the range (4)"));
 }
}

#line 3740 "cycle.nw"
cycle cycle::subs(const ex & e, unsigned options) const
{
	exmap em;
	if (e.info(info_flags::list)) {
		lst l = ex_to<lst>(e);
		for (const auto & i : l)
			em.insert(std::make_pair(i.op(0), i.op(1)));
	} else if (is_a<relational>(e))
		em.insert(std::make_pair(e.op(0), e.op(1)));
	else
		throw(std::invalid_argument("cycle::subs(): the parameter should be a relational or a lst"));
	return cycle(k.subs(em, options),l.subs(em, options),m.subs(em, options),unit.subs(em, options));
}


#line 3763 "cycle.nw"
void cycle::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("k-param", k);
	n.add_ex("l-param", l);
	n.add_ex("m-param", m);
	n.add_ex("unit", unit);
}

#line 3774 "cycle.nw"
void cycle::read_archive(const archive_node &n, lst &sym_lst)
{
	inherited::read_archive(n, sym_lst);
	n.find_ex("k-param", k, sym_lst);
	n.find_ex("l-param", l, sym_lst);
	n.find_ex("m-param", m, sym_lst);
	n.find_ex("unit", unit, sym_lst);
}
GINAC_BIND_UNARCHIVER(cycle);

//const char *cycle::get_class_name() { return "cycle"; }

#line 3788 "cycle.nw"
int cycle::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle>(other));
	   return inherited::compare_same_type(other);
/*
	const cycle &o = static_cast<const cycle &>(other);
	if ((unit == o.unit) && (l*o.get_k() - o.get_l()*k).is_zero() && (m*o.get_k() - o.get_m()*k).is_zero())
		return 0;
	else if ((unit < o.unit)
			 || (l*o.get_k() < o.get_l()*k) || (m*o.get_k() < o.get_m()*k))
		return -1;
	else
		return 1;*/
}

#line 3805 "cycle.nw"
bool cycle::is_equal(const basic & other, bool projectively, bool ignore_unit) const
{
	if (not is_a<cycle>(other))
		return false;
	const cycle o = ex_to<cycle>(other);
	ex factor=0, ofactor=0;

	if (not (ignore_unit || unit.is_equal(o.unit)))
		return false;

	if (projectively) {
		// Check that coefficients are scalar multiples of other
		if (not (m*o.get_k()-o.get_m()*k).normal().is_zero())
			return false;
		// Set up coefficients for proportionality
		if (get_k().normal().is_zero()) {
			factor=get_m();
			ofactor=o.get_m();
		} else {
			factor=get_k();
			ofactor=o.get_k();
		}

	} else
		// Check the exact equality of coefficients
		if (not ((get_k()-o.get_k()).normal().is_zero() && (get_m()-o.get_m()).normal().is_zero()))
			return false;


#line 3836 "cycle.nw"
	if (is_a<numeric>(get_dim())) {
		int D = ex_to<numeric>(get_dim()).to_int();
		if (! (is_a<numeric>(o.get_dim()) && D ==ex_to<numeric>(o.get_dim()).to_int()))
			return false;

		for (int i=0; i<D; i++)
			if (projectively) {
				// search the the first non-zero coefficient
				if (factor.is_zero()) {
					factor=get_l(i);
					ofactor=o.get_l(i);
				} else
					if (! (get_l(i)*ofactor-o.get_l(i)*factor).normal().is_zero())
						return false;
			} else
				if (! (get_l(i)-o.get_l(i)).normal().is_zero())
					return false;

		return true;
	} else
		return (l*ofactor-o.get_l()*factor).normal().is_zero();
}

#line 3863 "cycle.nw"
ex cycle::the_same_as(const basic & other) const
{
 if (! (is_a<cycle>(other) && (get_dim() == ex_to<cycle>(other).get_dim())))
	 return lst{1==0};
 ex f=1, f1=1;
 lst res;

#line 3872 "cycle.nw"
 if (not k.is_zero()) {
  f = k;
  f1 = ex_to<cycle>(other).get_k();
  res.append(f1*m ==f*ex_to<cycle>(other).get_m());

#line 3879 "cycle.nw"
 } else if (not m.is_zero()) {
  f = m;
  f1 = ex_to<cycle>(other).get_m();
 }

#line 3886 "cycle.nw"
 if (ex_to<varidx>(unit.op(1)).is_numeric()) {
  int D = ex_to<numeric>(get_dim()).to_int();
  for (int i=0; i < D; ++i)
   res.append(f1*get_l(i)==f*ex_to<cycle>(other).get_l(i));
 } else
  res.append(f1*l==f*ex_to<cycle>(other).get_l());
 return res;
}


#line 3898 "cycle.nw"
bool cycle::is_zero() const
{
 return (k.is_zero() && l.is_zero() && m.is_zero());
}

#line 3905 "cycle.nw"
ex cycle::real_part() const
{
	return cycle(k.real_part(),indexed(l.op(0).real_part(),l.op(1)),m.real_part(),unit);
}

ex cycle::imag_part() const
{
	return cycle(k.imag_part(),indexed(l.op(0).imag_part(),l.op(1)),m.imag_part(),unit);
}

#line 3917 "cycle.nw"
void cycle::do_print(const print_dflt & c, unsigned level) const
{
 PRINT_CYCLE
}

/*void cycle::do_print_python(const print_dflt & c, unsigned level) const
{
 PRINT_CYCLE
 }*/

void cycle::do_print_latex(const print_latex & c, unsigned level) const
{
 PRINT_CYCLE
}

#line 3937 "cycle.nw"
cycle cycle::add(const cycle & rh) const
{
	if (get_dim() != rh.get_dim())
		throw(std::invalid_argument("cycle::add(): cannot add two cycles from diferent dimensions"));

	ex ln=indexed(((get_l().is_zero()?0:get_l().op(0))+(rh.get_l().is_zero()?0:rh.get_l().op(0))).evalm(),
				  varidx((new symbol)->setflag(status_flags::dynallocated), get_dim()));
	return cycle(get_k()+rh.get_k(), ln, get_m()+rh.get_m(), unit);
}
cycle cycle::sub(const cycle & rh) const
{
	if (get_dim() != rh.get_dim())
		throw(std::invalid_argument("cycle::add(): cannot subtract two cycles from diferent dimensions"));

	ex ln=indexed(((get_l().is_zero()?0:get_l().op(0))-(rh.get_l().is_zero()?0:rh.get_l().op(0))).evalm(),
				  varidx((new symbol)->setflag(status_flags::dynallocated), get_dim()));
	return cycle(get_k()-rh.get_k(), ln, get_m()-rh.get_m(), unit);
}
cycle cycle::exmul(const ex & rh) const
{
	return cycle(get_k()*rh, indexed(get_l().is_zero() ? 0 : (get_l().op(0)*rh).evalm(),
									 varidx((new symbol)->setflag(status_flags::dynallocated), get_dim())),
				 get_m()*rh, unit);
}
cycle cycle::div(const ex & rh) const
{
	return exmul(pow(rh, numeric(-1)));
}

#line 3968 "cycle.nw"
const cycle operator+(const cycle & lh, const cycle & rh)
{
 return lh.add(rh);
}
const cycle operator-(const cycle & lh, const cycle & rh)
{
 return lh.sub(rh);
}
const cycle operator*(const cycle & lh, const ex & rh)
{
 return lh.exmul(rh);
}
const cycle operator*(const ex & lh, const cycle & rh)
{
 return rh.exmul(lh);
}
const cycle operator/(const cycle & lh, const ex & rh)
{
 return lh.div(rh);
}
const ex operator*(const cycle & lh, const cycle & rh)
{
 return lh.mul(rh);
}

#line 3995 "cycle.nw"
const cycle2D operator+(const cycle2D & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(lh.add(rh));
}
const cycle2D operator-(const cycle2D & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(lh.sub(rh));
}
const cycle2D operator*(const cycle2D & lh, const ex & rh)
{
 return ex_to<cycle2D>(lh.exmul(rh));
}
const cycle2D operator*(const ex & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(rh.exmul(lh));
}
const cycle2D operator/(const cycle2D & lh, const ex & rh)
{
 return ex_to<cycle2D>(lh.div(rh));
}
const ex operator*(const cycle2D & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(lh.mul(rh));
}

#line 4028 "cycle.nw"
cycle cycle::normalize(const ex & k_new, const ex & e) const
{
	ex ratio = 0;
	if (k_new.is_zero()) // Make the determinant equal 1
		ratio = sqrt(radius_sq(e));
	else { // First non-zero coefficient among k, m, l_0, l_1, ... is set to k_new
		if (!k.is_zero())
			ratio = k/k_new;
		else if (!m.is_zero())
			ratio = m/k_new;
		else {
			int D = ex_to<numeric>(get_dim()).to_int();
			for (int i=0; i<D; i++)
				if (!l.subs(l.op(1) == i).is_zero()) {
					ratio = l.subs(l.op(1) == i)/k_new;
					break;
				}
		}
	}
	if (ratio.is_zero()) // No normalisation is possible
		return (*this);

	return cycle((k/ratio).normal(), indexed((l.op(0)/ratio).evalm().normal(), l.op(1)), (m/ratio).normal(), unit);
}

#line 4057 "cycle.nw"
cycle cycle::normalize_det(const ex & e, const ex & sign, const ex & D, bool fix_paravector) const
{
	ex d = det(e, sign, 0, fix_paravector);
	if (d.is_zero())
		return *this;

	ex ratio=sqrt(((-d/D).info(info_flags::nonnegative)? -1: 1)*d/D);
	return cycle((k/ratio).normal(), indexed((l.op(0)/ratio).evalm().normal(), l.op(1)), (m/ratio).normal(), unit);
}


#line 4071 "cycle.nw"
ex cycle::center(const ex & metr, bool return_matrix) const
{
	if (is_a<numeric>(get_dim())) {
		ex e1, M, D = get_dim();
		if (metr.is_zero())
			e1 = unit;
		else {
			if (is_a<clifford>(metr))
				e1=metr;

#line 4083 "cycle.nw"
			else
				try {
					e1 = clifford_unit(varidx(0, D), metr);
				} catch (exception &p) {
					throw(std::invalid_argument("cycle::center(): supplied metric"
												" is not suitable for Clifford unit"));
				}
		}

#line 4094 "cycle.nw"
		if (D==ex_to<idx>(e1.op(1)).get_dim())
			M=ex_to<clifford>(e1).get_metric();
		else
			M=expand_paravector_metric(e1);
		exvector f_ind=M.get_free_indices();

#line 4106 "cycle.nw"
		lst c;
		for(int i=0; i<D; i++)
			if (k.is_zero())
				c.append(get_l(i));
			else
				//c.append(jump_fnct(-ex_to<clifford>(e1).get_metric(varidx(i, D), varidx(i, D)))*get_l(i)/k);
				c.append(-M.subs(lst{f_ind[0]==i, f_ind[1]==i})*get_l(i)/k);
		return (return_matrix? (ex)matrix(ex_to<numeric>(D).to_int(), 1, c) : (ex)c);
	} else {
		return l/k;
	}
}

#line 4129 "cycle.nw"
cycle cycle::subject_to(const ex & condition, const ex & vars) const
{
 lst vars1;
 if (vars.info(info_flags::list) &&(vars.nops() != 0))
	 vars1 = ex_to<lst>(vars);
 else if (is_a<symbol>(vars))
	 vars1 = lst{vars};
 else if ((vars == 0) || (vars.nops() == 0)) {
	 if (is_a<symbol>(m))
   vars1.append(m);
	 if (is_a<numeric>(get_dim()))
		 for (int i = 0; i < ex_to<numeric>(get_dim()).to_double(); i++)
			 if (is_a<symbol>(get_l(i)))
				 vars1.append(get_l(i));
	 if (is_a<symbol>(k))
   vars1.append(k);
	 if (vars1.nops() == 0)
		 throw(std::invalid_argument("cycle::subject_to(): could not construct the default list of "
									 "parameters"));
 } else
	 throw(std::invalid_argument("cycle::subject_to(): second parameter should be a list of symbols"
								 " or a single symbol"));

 return subs(lsolve(condition.info(info_flags::relation_equal)? lst{condition} : condition,
								 vars1), subs_options::algebraic | subs_options::no_pattern);
}

#line 4160 "cycle.nw"
ex make_clifford_unit(const ex & e, const ex & D, const ex & unit) {
	varidx i1((new symbol)->setflag(status_flags::dynallocated), D),
		i1s((new symbol)->setflag(status_flags::dynallocated), D-1);

#line 4167 "cycle.nw"
	if (e.is_zero()) {
		if (ex_to<idx>(unit.op(1)).get_dim()==D)
			return unit.subs(unit.op(1) == i1);
		else
			return unit.subs(unit.op(1) == i1s);

#line 4176 "cycle.nw"
	} else if (is_a<clifford>(e)) {
		if (ex_to<idx>(e.op(1)).get_dim()==D)
			return e.subs(e.op(1) == i1);
		else if (ex_to<idx>(e.op(1)).get_dim()==D-1)
			return e.subs(e.op(1) == i1s);
		else
			throw(std::invalid_argument("make_clifford_unit(): "
										"Clifford unit has unsuitable dimensionality"));

#line 4187 "cycle.nw"
	} else if (is_a<indexed>(e)) {
		if (ex_to<idx>(e.op(1)).get_dim()==D)
			return clifford_unit(i1, e);
		else if (ex_to<idx>(e.op(1)).get_dim()==D-1)
			return clifford_unit(i1s, e);
		else
			throw(std::invalid_argument("make_clifford_unit(): "
										"indexed object has unsuitable dimensionality"));

#line 4198 "cycle.nw"
	} else if (is_a<tensor>(e)) {
		return clifford_unit(i1, e);
	} else if (is_a<matrix>(e)) {
		int C=ex_to<matrix>(e).cols();
		if (C==D)
			return clifford_unit(i1, e);
		else if (C==D-1)
			return clifford_unit(i1s, e);
		else
			throw(std::invalid_argument("make_clifford_unit(): matrix has unsuitable size"));

#line 4211 "cycle.nw"
	} else
		throw(std::invalid_argument("make_clifford_unit(): expect a clifford number, matrix, tensor or "
									"indexed as the first parameter"));
}

#line 4225 "cycle.nw"
matrix cycle::to_matrix(const ex & e, const ex & sign, bool conjugate) const
{
	ex conv, // Indexed object for convolution with l
		D = get_dim();

	ex es = make_clifford_unit(e, D, unit); // The Clifford unit to be used in the matrix
	ex one = dirac_ONE(ex_to<clifford>(es).get_representation_label());

	varidx i0((new symbol)->setflag(status_flags::dynallocated), D),
		i1((new symbol)->setflag(status_flags::dynallocated), D);

#line 4238 "cycle.nw"
	ex sign_m = sign.evalm();

	if (is_a<tensor>(sign_m))
		conv = indexed(ex_to<tensor>(sign_m), i0, i1.toggle_variance());
	else if (is_a<clifford>(sign_m)) {
		if (ex_to<varidx>(sign_m.op(1)).get_dim() == D)
			conv = ex_to<clifford>(sign_m).get_metric(i0, i1.toggle_variance());
		else
			throw(std::invalid_argument("cycle::to_matrix(): the sign should be a Clifford unit with the "
										"dimensionality matching to the second parameter"));
	} else if (is_a<indexed>(sign_m)) {
		exvector ind = ex_to<indexed>(sign_m).get_indices();
		if ((ind.size() == 2) && (ex_to<varidx>(ind[0]).get_dim() == D) && (ex_to<varidx>(ind[1]).get_dim() == D))
			conv = sign_m.subs(lst{ind[0] == i0, ind[1] == i1.toggle_variance()});
		else
			throw(std::invalid_argument("cycle::to_matrix(): the sign should be an indexed object with two "
										"indices and their dimensionality matching to the second parameter"));
	} else if (is_a<matrix>(sign_m)) {
		if ((ex_to<matrix>(sign_m).cols() == D) && (ex_to<matrix>(sign_m).rows() == D))
			conv = indexed(ex_to<matrix>(sign_m), i0, i1.toggle_variance());
		else
			throw(std::invalid_argument("cycle::to_matrix(): the sign should be a square matrix with the "
										"dimensionality matching to the second parameter"));
	} else
		throw(std::invalid_argument("cycle::to_matrix(): the sign should be either tensor, indexed, "
									"matrix or Clifford unit"));

#line 4269 "cycle.nw"
	if ( ex_to<idx>(es.op(1)).get_dim() == D) {
		ex a00 = expand_dummy_sum(l.subs(ex_to<indexed>(l).get_indices()[0] == i0.toggle_variance())
								  * conv * es.subs(es.op(1)==i1));
		return matrix(2, 2, lst{a00, m * one, k * one, -a00});

#line 4276 "cycle.nw"
	} else {
		ex lconv=simplify_indexed(l.subs(ex_to<indexed>(l).get_indices()[0] == i0.toggle_variance()) * conv);
		if (is_a<indexed>(lconv)) {
			ex scalar_p = expand_dummy_sum(lconv.subs(ex_to<indexed>(lconv).get_indices()[0] == 0)*one),
				vector_p = expand_dummy_sum(indexed(paravector(lconv.op(0)),
													ex_to<varidx>(es.op(1)).toggle_variance())* es);
			return matrix(2, 2, lst{scalar_p+ (conjugate?-1:1)*vector_p, -m * one, k * one, -scalar_p+(conjugate?-1:1)*vector_p});

#line 4286 "cycle.nw"
		} else
			throw(std::runtime_error("cycle::to_matrix(): after convolution with sign the indexed "
									 "objext disappered"));
	}
}

#line 4300 "cycle.nw"
ex cycle::val(const ex & y, const ex & x) const
{
	ex y0, D = get_dim();
	varidx i0, i1;
	if (is_a<indexed>(y)) {
		i0 = ex_to<varidx>(ex_to<indexed>(y).get_indices()[0]);
		if ((ex_to<indexed>(y).get_indices().size() == 1) && (i0.get_dim() == D)) {
			y0 = ex_to<indexed>(y);
			i1 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		} else
			throw(std::invalid_argument("cycle::val(): the second parameter should be "
										"an indexed object with one varindex"));

#line 4315 "cycle.nw"
	} else if (y.info(info_flags::list) && (y.nops() == D)) {
		i0 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		i1 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		y0 = indexed(matrix(1, y.nops(), ex_to<lst>(y)), i0);
	} else if (is_a<matrix>(y) && (min(ex_to<matrix>(y).rows(), ex_to<matrix>(y).cols()) ==1)
			   && (D == max(ex_to<matrix>(y).rows(), ex_to<matrix>(y).cols()))) {
		i0 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		i1 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		y0 = indexed(y, i0);
	} else
		throw(std::invalid_argument("cycle::val(): the second parameter should be a indexed object, "
									"matrix or list"));

		return expand_dummy_sum(-k*y0*y0.subs(i0 == i1)*get_metric(i0.toggle_variance(), i1.toggle_variance())
							- numeric(2)*x* l*y0.subs(i0 == ex_to<varidx>(ex_to<indexed>(l).get_indices()[0]).toggle_variance())
								+m*pow(x,2));
}

#line 4346 "cycle.nw"
ex cycle::det(const ex & e, const ex & sign, const ex & k_norm, bool fix_paravector) const
{
	ex es = make_clifford_unit(e, get_dim(), unit); // The Clifford unit to be used in the matrix
	return (fix_paravector && (ex_to<idx>(es.op(1)).get_dim() != get_dim())? -1 : 1)*
		remove_dirac_ONE((k_norm.is_zero()?*this:normalize(k_norm))
							.to_matrix(es, sign).determinant());
}
#line 4358 "cycle.nw"
ex cycle::cycle_product(const cycle & C, const ex & e, const ex & sign) const {
	ex es = make_clifford_unit(e, get_dim(), unit); // The Clifford unit to be used in the matrix
	bool is_paravect = (ex_to<idx>(es.op(1)).get_dim() == get_dim());
	return (is_paravect? 1 : -1)*
		scalar_part(ex_to<matrix>(mul(ex_to<cycle>(C).to_matrix(es, sign,true), es, sign)).trace());
}
#line 4369 "cycle.nw"
ex cycle::mul(const ex & C, const ex & e, const ex & sign, const ex & sign1) const
{
	if (is_a<cycle>(C)) {
		return canonicalize_clifford(to_matrix(e, sign).mul(
				ex_to<cycle>(C).to_matrix(e.is_zero()?unit:e, sign1.is_zero()?sign:sign1)));
	} else if (is_a<matrix>(C) && (ex_to<matrix>(C).rows() == 2)  && (ex_to<matrix>(C).cols() == 2)) {
		return canonicalize_clifford(to_matrix(e, sign).mul(ex_to<matrix>(C)));
	} else
		throw(std::invalid_argument("cycle::mul(): cannot multiply a cycle by anything but a cycle "
									"or 2x2 matrix"));
}

#line 4392 "cycle.nw"
cycle cycle::matrix_similarity(const ex & M, const ex & e, const ex & sign, bool not_inverse,
							   const ex & sign_inv) const
{
	if (not (is_a<matrix>(M) && ex_to<matrix>(M).rows()==2 && ex_to<matrix>(M).cols()==2))
		throw(std::invalid_argument("cycle::matrix_similarity(): the first parameter sgould be "
									"a 2x2 matrix"));
	return matrix_similarity(M.op(0), M.op(1), M.op(2), M.op(3), e, sign, not_inverse, sign_inv);
}

#line 4404 "cycle.nw"
cycle cycle::matrix_similarity(const ex & a, const ex & b, const ex & c, const ex & d, const ex & e,
          const ex & sign, bool not_inverse, const ex & sign_inv) const
{
	ex es = make_clifford_unit(e, get_dim(), unit); // The Clifford unit to be used in the matrix
	matrix R=ex_to<matrix>(canonicalize_clifford(matrix(2,2,not_inverse?lst{a, b, c, d}:lst{clifford_star(d), -clifford_star(b), -clifford_star(c), clifford_star(a)})
												 .mul(ex_to<matrix>(mul(matrix(2,2,not_inverse?lst{clifford_star(d), -clifford_star(b), -clifford_star(c), clifford_star(a)}:lst{a, b, c, d}), es, sign)))
												 .evalm()).normal());


#line 4417 "cycle.nw"
			/*			if (ex_to<idx>(es.op(1)).get_dim() == get_dim())
				return cycle(matrix(2,2,lst{(R.op(0)-R.op(3))/numeric(2),R.op(1),
								R.op(2),(-R.op(0)+R.op(3))/numeric(2)}), unit, es, sign_inv, get_dim());
			else
				return cycle(matrix(2,2,lst{(R.op(0)-clifford_bar(R.op(3)))/numeric(2),R.op(1),R.op(2),
								(-clifford_bar(R.op(0))+R.op(3))/numeric(2)}), unit, es, sign_inv, get_dim());
			*/
			return cycle(R, unit, es, sign_inv, get_dim());
}

#line 4430 "cycle.nw"
cycle cycle::sl2_similarity(const ex & a, const ex & b, const ex & c, const ex & d, const ex & e,
							const ex & sign, bool not_inverse, const ex & sign_inv) const
{
//	ex sign_inv=is_a<matrix>(sign)?pow(sign,-1):sign;
	relational sl2_rel = (c*b == (d*a-1));

#line 4439 "cycle.nw"
	ex det=(a*d-b*c).eval();
	ex es=e.is_zero()?unit:e;
	if (is_a<numeric>(det) && (ex_to<numeric>(det).evalf() !=1))
		sl2_rel = (c*b==c*b);

#line 4446 "cycle.nw"
	matrix R=ex_to<matrix>(canonicalize_clifford(
							   sl2_clifford(a, b, c, d, es, not_inverse)
							   .mul(ex_to<matrix>(mul(sl2_clifford(a, b, c, d, es, !not_inverse), es, sign_inv)))
							   .evalm().subs(sl2_rel, subs_options::algebraic | subs_options::no_pattern)).normal());

#line 4454 "cycle.nw"
	/*if (ex_to<idx>(es.op(1)).get_dim()==get_dim())
	  return cycle(matrix(2,2,lst{(R.op(0)-R.op(3))/numeric(2),R.op(1),R.op(2),
	  (-R.op(0)+R.op(3))/numeric(2)}), unit, e, sign, get_dim());
	  else
	  return cycle(matrix(2,2,lst{(R.op(0)-clifford_bar(R).op(3))/numeric(2),R.op(1),
	  R.op(2),(-clifford_bar(R).op(0)+R.op(3))/numeric(2)}), unit, e, sign, get_dim());*/
		return cycle(R, unit, e, sign, get_dim());
}

#line 4465 "cycle.nw"
cycle cycle::sl2_similarity(const ex & M, const ex & e, const ex & sign, bool not_inverse,
							const ex & sign_inv) const
{
	if (is_a<matrix>(M) || M.info(info_flags::list))
		return sl2_similarity(M.op(0), M.op(1), M.op(2), M.op(3), e, sign, not_inverse, sign_inv);
	else
		throw(std::invalid_argument("sl2_similarity(): expect a list or matrix as the first parameter"));
}

#line 4479 "cycle.nw"
cycle cycle::cycle_similarity(const cycle & C, const ex & e, const ex & sign, const ex & sign1,
							  const ex & sign_inv) const
{
//	ex sign_inv=is_a<matrix>(sign)?pow(sign,-1):sign;
	ex es = make_clifford_unit(e, get_dim(), unit); // The Clifford unit to be used in the matrix
	if (ex_to<idx>(es.op(1)).get_dim() == get_dim()) {// Vector formalism
        return cycle(ex_to<matrix>(canonicalize_clifford(C.mul(mul(C, es, sign,sign1.is_zero()?sign:sign1),
															   es, sign1.is_zero()?sign:sign1))),
					 unit, es, sign_inv, get_dim());
	} else { // Paravector formalism
		matrix M=ex_to<matrix>(to_matrix(es,sign,true)),
			M1=ex_to<matrix>(C.to_matrix(es,sign1.is_zero()?sign:sign1));
		return cycle(ex_to<matrix>(canonicalize_clifford((-M1*M*M1).evalm())),
					 unit, es, sign_inv, get_dim());
	}
}

#line 4498 "cycle.nw"
ex cycle::moebius_map(const ex & P, const ex & e, const ex & sign) const {
	return clifford_moebius_map(to_matrix(e, sign), P, (e.is_zero()?unit:e));
}
#line 4505 "cycle.nw"
ex cycle::is_f_orthogonal(const cycle & C, const ex & e, const ex & sign, const ex & sign1,
						  const ex & sign_inv) const
{
	ex es=make_clifford_unit(e, get_dim(), unit);
	ex signc=sign1.is_zero()?sign:sign1;

	matrix M=ex_to<matrix>(to_matrix(es,sign,true)),
		M1=ex_to<matrix>(C.to_matrix(es,sign1.is_zero()?sign:sign1)),
		P= ex_to<matrix>(canonicalize_clifford((M*M1*M).evalm()));
	/*	if (ex_to<idx>(es.op(1)).get_dim() == get_dim()) { // Vector formalism
		P = ex_to<matrix>(canonicalize_clifford((M*M1*M).evalm()));
	} else { // Paravector formalism
		//		P = ex_to<matrix>(canonicalize_clifford((clifford_bar(M)*M1*clifford_bar(M)).evalm()));
		P = ex_to<matrix>(canonicalize_clifford(((M)*M1*(M)).evalm()));
		}*/

	return (cycle(P, es, es, sign_inv, get_dim()).get_l(get_dim()-1).normal() == 0);
//	return (C.cycle_similarity(*this, e, sign, sign1).get_l(get_dim()-1).normal() == 0);
}

#line 4532 "cycle.nw"
cycle2D::cycle2D() : inherited()
{
}

#line 4538 "cycle.nw"
cycle2D::cycle2D(const ex & k1, const ex & l1, const ex & m1, const ex & metr)
 : inherited(k1, l1, m1, metr)
{
 if (get_dim() != 2)
  throw(std::invalid_argument("cycle2D::cycle2D(): class cycle2D is defined in two dimensions"));
}

#line 4547 "cycle.nw"
cycle2D::cycle2D(const lst & l, const ex & r_squared, const ex & metr, const ex & e, const ex & sign)
 : inherited(l, r_squared, metr, e, sign)
{
 if (get_dim() != 2)
  throw(std::invalid_argument("cycle2D::cycle2D(): class cycle2D is defined in two dimensions"));
}

#line 4556 "cycle.nw"
cycle2D::cycle2D(const matrix & M, const ex & metr, const ex & e, const ex & sign)
	: inherited(M, metr, e, sign, 2)
{
 if (get_dim() != 2)
  throw(std::invalid_argument("cycle2D::cycle2D(): class cycle2D is defined in two dimensions"));
}

#line 4565 "cycle.nw"
cycle2D::cycle2D(const cycle & C, const ex & metr)
{
 (*this) = cycle2D(C.get_k(), C.get_l(), C.get_m(), (metr.is_zero()? C.get_unit(): metr));
}

#line 4572 "cycle.nw"
void cycle2D::archive(archive_node &n) const
{
	inherited::archive(n);
}

//cycle2D::cycle2D(const archive_node &n, lst &sym_lst) : inherited(n, sym_lst) {; }

void cycle2D::read_archive(const archive_node &n, lst &sym_lst)
{
	inherited::read_archive(n, sym_lst);
}
GINAC_BIND_UNARCHIVER(cycle2D);

int cycle2D::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle2D>(other));
	return inherited::compare_same_type(other);
}

//const char *cycle2D::get_class_name() { return "cycle2D"; }

#line 4595 "cycle.nw"
ex cycle2D::real_part() const
{
	return cycle2D(k.real_part(),lst{get_l(0).real_part(),get_l(1).real_part()},m.real_part(),unit);
}

ex cycle2D::imag_part() const
{
	return cycle2D(k.imag_part(),lst{get_l(0).imag_part(),get_l(1).imag_part()},m.imag_part(),unit);
}

#line 4616 "cycle.nw"
ex cycle2D::focus(const ex & e, bool return_matrix) const
{
	lst f=lst{//jump_fnct(-get_metric(varidx(0, 2), varidx(0, 2)))*
		get_l(0)/k,
		(-det(e, (new tensdelta)->setflag(status_flags::dynallocated), 0, true)/(numeric(2)*get_l(1)*k)).normal()};
	return (return_matrix? (ex)matrix(2, 1, f) : (ex)f);
}

#line 4626 "cycle.nw"
lst cycle2D::roots(const ex & y, bool first) const
{
	ex D = get_dim();
	lst k_sign = lst{-k*get_metric(varidx(0, D), varidx(0, D)), -k*get_metric(varidx(1, D), varidx(1, D))};
	int i0 = (first?0:1), i1 = (first?1:0);
	ex c = k_sign.op(i1)*pow(y, 2) - numeric(2)*get_l(i1)*y+m;
	if (k_sign.op(i0).is_zero())
		return (get_l(i0).is_zero() ? lst{} : lst{c/get_l(i0)/numeric(2)});
	else {
		ex disc = sqrt(pow(get_l(i0), 2) - k_sign.op(i0)*c);
		return lst{(get_l(i0)-disc)/k_sign.op(i0), (get_l(i0)+disc)/k_sign.op(i0)};
	}
}

#line 4642 "cycle.nw"
lst cycle2D::line_intersect(const ex & a, const ex & b) const
{
	ex D = get_dim();
	ex pm = -k*get_metric(varidx(1, D), varidx(1, D));
	return cycle2D(k*(numeric(1)+pm*pow(a,2)).normal(),
				   lst{(get_l(0)+get_l(1)*a-pm*a*b).normal(), 0},
				   (m-numeric(2)*get_l(1)*b+pm*pow(b,2)).normal()).roots();
 }

#line 4653 "cycle.nw"
cycle2D cycle2D::sl2_similarity(const ex & M1, const ex & M2, const ex & e,
								const ex & sign, bool not_inverse, const ex & sign_inv) const {
	if ((is_a<matrix>(M1) || M1.info(info_flags::list)) && (is_a<matrix>(M2) || M2.info(info_flags::list)))
		return sl2_similarity(M1.op(0), M1.op(1), M1.op(2), M1.op(3),
							  M2.op(0), M2.op(1), M2.op(2), M2.op(3),e, sign, not_inverse, sign_inv);
	else
		throw(std::invalid_argument("cycle2D::sl2_similarity(): expect a lsts or matrices as "
									"the first parameter"));
;
 }

#line 4666 "cycle.nw"
cycle2D cycle2D::sl2_similarity(const ex & a1, const ex & b1, const ex & c1, const ex & d1,
								const ex & a2, const ex & b2, const ex & c2, const ex & d2,
								const ex & e, const ex & sign, bool not_inverse, const ex & sign_inv) const {
	ex es=e.is_zero()?unit:e;
	matrix R=ex_to<matrix>(canonicalize_clifford(
												 sl2_clifford(a1, b1, c1, d1, a2, b2, c2, d2, es, not_inverse)
												 .mul(ex_to<matrix>(mul(sl2_clifford(a1, b1, c1, d1,
																					 a2, b2, c2, d2, es, !not_inverse), es, sign_inv)))
												 .evalm()).normal());
	return cycle(R, unit, e, sign, get_dim());
 }

#line 4680 "cycle.nw"
cycle2D cycle2D::sl2_similarity(const ex & M, const ex & e) const {
	if (is_a<matrix>(e))
		return sl2_similarity(M, e, unit, (new tensdelta)->setflag(status_flags::dynallocated), true,
							  (new tensdelta)->setflag(status_flags::dynallocated));
	else
		return sl2_similarity(M, e, (new tensdelta)->setflag(status_flags::dynallocated), true,
							  (new tensdelta)->setflag(status_flags::dynallocated));
 }

#line 4691 "cycle.nw"
cycle2D cycle2D::sl2_similarity(const ex & M, const ex & e, const ex & sign) const {
	if (is_a<matrix>(e))
		return sl2_similarity(M, e, sign, (new tensdelta)->setflag(status_flags::dynallocated), true,
							  (new tensdelta)->setflag(status_flags::dynallocated));
	else
		return sl2_similarity(M, e, sign, true, (new tensdelta)->setflag(status_flags::dynallocated));
 }

#line 4705 "cycle.nw"
inline ex max(const ex &a, const ex &b) {return ex_to<numeric>((a-b).evalf()).is_positive()?a:b;}
inline ex min(const ex &a, const ex &b) {return ex_to<numeric>((a-b).evalf()).is_positive()?b:a;}

#line 4710 "cycle.nw"
#define DRAW_ARC(X, S)   u = X; \
    v = ex_to<numeric>(Cf.roots(X, !not_swapped).op(zero_or_one).evalf()).to_double(); \
    du = dir*(-k_d*signv*v+lv);    \
    dv = dir*(k_d*signu*u-lu);        \
    if (not_swapped)            \
     ost << S <<  u << "," << v << "){" << du << "," << dv << "}"; \
    else                \
     ost << S <<  v << "," << u << "){" << (sign == 0? dv : -dv) << "," << (sign == 0? du : -du) << "}";

#line 4721 "cycle.nw"
bool is_almost_zero(const ex & x)
{
	if (is_a<numeric>(x))
		return (abs(ex_to<numeric>(x).to_double()) < 0.0000000001);
	else
		return x.is_zero();
}

#line 4731 "cycle.nw"
bool is_almost_negative(const ex & x)
{
	if (is_a<numeric>(x))
		return (ex_to<numeric>(x.evalf()).to_double() < 0.0000000001);
	else
		return x.is_zero();
}

#line 4741 "cycle.nw"
void cycle2D::metapost_draw(ostream & ost, const ex & xmin, const ex & xmax,
							const ex & ymin, const ex & ymax,
							const lst & color, const string more_options, bool with_header,
							int points_per_arc, bool asymptote, const string picture, bool only_path,
							bool is_continuation, const string imaginary_options) const
{
 ostringstream draw_start, draw_options;
 string already_drawn =(is_continuation? "^^(" : "(" ); // Was any arc already drawn?
draw_start << "draw" << (asymptote ? "(" : " ") << picture << (picture.size()==0? "" : ",") << "(";
 ios_base::fmtflags keep_flags = ost.flags(); // Keep stream's flags to be restored on the exit
 draw_options.flags(keep_flags); // Synchronise flags between the streams
 draw_options.precision(ost.precision()); // Synchronise flags between the streams

#line 4757 "cycle.nw"
 ost << fixed;
 draw_options << fixed;
 if (color.nops() == 3) {
  if (asymptote)
   draw_options  << ",rgb("
       << ex_to<numeric>(color.op(0)).to_double() << ","
       << ex_to<numeric>(color.op(1)).to_double() <<","
       << ex_to<numeric>(color.op(2)).to_double() << ")";
  else
   draw_options  << showpos << " withcolor "
       << ex_to<numeric>(color.op(0)).to_double() << "*red"
       << ex_to<numeric>(color.op(1)).to_double() <<"*green"
       << ex_to<numeric>(color.op(2)).to_double() << "*blue ";
 }
 if (more_options != "") {
	 if (color.nops() == 3)
		 draw_options << "+";
	 else
		 draw_options << ",";
	 draw_options << more_options;
 }
 draw_options << (asymptote ? ");" : ";") << endl;

#line 4783 "cycle.nw"
if (with_header) {
  ost << (asymptote ? "// Asymptote" : "% Metapost") << " data in [" << xmin << ","
   << xmax << "]x[" << ymin << ","
	  << ymax << "] for ";

 ostringstream equat;
 equat << (ex)passing(lst{symbol("u"), symbol("v")});
 if (equat.str().length()< 256)
	 ost << equat.str();
 else
	 ost << " [approx.] " << ex_to<cycle2D>(evalf()).passing(lst{symbol("u"), symbol("v")});
 }

 if (k.is_zero() && l.subs(l.op(1) == 0).is_zero() && l.subs(l.op(1) == 1).is_zero() && \
m.is_zero()) {
  ost << " zero cycle, (whole plane) " << endl;
  ost.flags(keep_flags);
  return;
 }

#line 4807 "cycle.nw"
	cycle2D Cf=ex_to<cycle2D>(evalf()).normalize();
	double  xc = ex_to<numeric>(Cf.center().op(0)).to_double(),
		yc = ex_to<numeric>(Cf.center().op(1)).to_double(); // the center of cycle
	double sign0 = ex_to<numeric>(-get_metric(varidx(0, 2), varidx(0, 2)).evalf()).to_double(),
	sign1 = ex_to<numeric>(-get_metric(varidx(1, 2), varidx(1, 2)).evalf()).to_double(),
	sign = sign0 * sign1;
	double determinant = ex_to<numeric>(Cf.radius_sq()).to_double(),
		r=ex_to<numeric>(GiNaC::sqrt(GiNaC::abs(determinant))).to_double();
	double epsilon=0.0000000001;
	bool not_swapped = (sign>0 || sign1==0 || ((sign <0) && (determinant < epsilon)));
	double signu = (not_swapped?sign0:sign1), signv = (not_swapped?sign1:sign0);
	int iu = (not_swapped?0:1), iv = (not_swapped?1:0);
	double umin =  ex_to<numeric>((not_swapped ? xmin : ymin).evalf()).to_double(),
		umax =  ex_to<numeric>((not_swapped ? xmax : ymax).evalf()).to_double(),
		vmin =  ex_to<numeric>((not_swapped ? ymin:  xmin).evalf()).to_double(),
		vmax =  ex_to<numeric>((not_swapped ? ymax : xmax).evalf()).to_double(),
		uc =  (not_swapped ? xc:  yc), vc =  (not_swapped ? yc : xc);
	lst b_roots = ex_to<lst>(Cf.roots(vmin, not_swapped).evalf()),
		t_roots = ex_to<lst>(Cf.roots(vmax, not_swapped).evalf());

#line 4831 "cycle.nw"
	
#line 4924 "cycle.nw"
	if (! (Cf.get_k().imag_part().is_zero() && Cf.get_l(0).imag_part().is_zero()
		   && Cf.get_l(1).imag_part().is_zero() && Cf.get_m().imag_part().is_zero())) {
		if (imaginary_options == "invisible")
			return;
		realsymbol x1("x1"), y1("y1");
		cycle2D CI=ex_to<cycle2D>(Cf.imag_part());
		lst sol=ex_to<lst>(lsolve(lst{CI.val(lst{x1,y1})==0}, lst{x1,y1}));

#line 4934 "cycle.nw"
		CI=ex_to<cycle2D>(Cf.normalize().real_part());
		ex eq=(CI.val(lst{x1,y1}).subs(sol)).normal();
		ex t=(eq.has(x1)?x1:y1),  s=(eq.has(x1)?y1:x1);
		double A, B, C, D;
		A=ex_to<numeric>(eq.coeff(ex_to<symbol>(t),2)).to_double();
		B=ex_to<numeric>(eq.coeff(ex_to<symbol>(t),1)).to_double();
		C=ex_to<numeric>(eq.coeff(ex_to<symbol>(t),0)).to_double();
		D=B*B-4*A*C;

#line 4945 "cycle.nw"
		if (abs(A)<epsilon || D>=0){
			if (with_header)
				ost << endl << "// imaginary coefficients, the intersection with the real plane is dots only";

#line 4951 "cycle.nw"
			for(int i=-1; i<2; i+=2) {
				double t1;
				if (abs(A)<epsilon) {
					i=1; // No need for second pass
					if (abs(B)<epsilon)
						return; // trivial identity
					else
						t1=-C/B;
				} else
					t1= ex_to<numeric>((-B+i*sqrt((numeric)D))/2.0/A).to_double();
				exmap em;
				em.insert(std::make_pair(t, t1));
				ex s1=s.subs(sol.subs(em));
				uc=ex_to<numeric>(eq.has(x1)? t1 : s1).to_double();
				vc=ex_to<numeric>(eq.has(x1)? s1 : t1).to_double();

#line 4970 "cycle.nw"
				if (abs(ex_to<numeric>(Cf.val(lst{uc,vc}).evalf()).to_double()) < epsilon) {
					if (asymptote)
						draw_options.str(","+imaginary_options+");");
					else
						draw_options.str(" "+imaginary_options+";");
					ost << endl;
					{
#line 5089 "cycle.nw"
	double U=ex_to<numeric>(uc).to_double();
	double V=ex_to<numeric>(vc).to_double();
	if ((umin <=U) && (umax>=U) && (vmin<=V) && (vmax>=V)) {
		ost << (asymptote ? (only_path ? already_drawn : "dot(") : "draw " )
			<< picture << (picture.size()==0? "" : ",")
			<< (only_path ? "" : "(")
			<< uc << "," << vc << ")" << (only_path ? "" : draw_options.str());
	already_drawn="^^(";

#line 5100 "cycle.nw"
	} else
		if (with_header)
			ost << "// the vertex is out of range" << endl;

#line 4976 "cycle.nw"
                     }
				} else {
					std::cerr << "Calculation of dots in imaginary cycle is inaccurate" << std::endl;
				}
			}

#line 4984 "cycle.nw"
	} else
		if (with_header)
			ost << endl << "// imaginary coefficients, no intersection with the real plane" << endl;
	ost << endl;
	return;
}

#line 4832 "cycle.nw"
	
#line 4846 "cycle.nw"
if (b_roots.nops() != 2) { // a linear object
	if (Cf.get_k().is_zero() && Cf.get_l(0).is_zero() && Cf.get_l(1).is_zero()) {
		if (with_header)
			ost << " the zero-radius cycle at infinity" << endl;
		return;
	}
	if (with_header)
		ost << " (straight line)" << endl;
	double u1, u2, v1, v2;
	if (b_roots.nops() == 1){ // a "non-horisontal" line
		u1 = std::max(std::min(ex_to<numeric>(b_roots.op(0)).to_double(), umax), umin);
		u2 = std::min(std::max(ex_to<numeric>(t_roots.op(0)).to_double(), umin), umax);
	} else { // a "horisontal" line
		u1 = umin;
		u2 = umax;
	}

#line 4865 "cycle.nw"
if (Cf.get_l(iv).is_zero()) { // a vertical line
	if (ex_to<numeric>(b_roots.op(0)- umin).to_double() > -epsilon
		&& ex_to<numeric>(umax-b_roots.op(0)).to_double() > -epsilon ) {
		v1 =  vmin;
		v2 =  vmax;
	} else { // out of scope
		ost.flags(keep_flags);
		return;
	}

#line 4877 "cycle.nw"
} else {
	v1 = ex_to<numeric>(Cf.roots(u1, !not_swapped).op(0)).to_double();
	v2 = ex_to<numeric>(Cf.roots(u2, !not_swapped).op(0)).to_double();
	if ((std::max(v1, v2)-vmax > epsilon) || (std::min(v1, v2) -vmin < -epsilon )) {
		ost.flags(keep_flags);
		return; //out of scope
	}
}

#line 4888 "cycle.nw"
	ost <<  (only_path ? already_drawn : draw_start.str())
		<< (not_swapped? u1: v1) << "," << (not_swapped ? v1: u1)
		<< ")--(" << (not_swapped ? u2: v2) << "," << (not_swapped ? v2: u2) << ")"
		<< (only_path ? "" : draw_options.str());
already_drawn="^^(";
if (with_header)
	ost << endl;
ost.flags(keep_flags);
return;
}

#line 4833 "cycle.nw"
	
#line 4902 "cycle.nw"
double left[2] = {std::max(std::min(uc, umax), umin),
				   std::max(std::min(uc, umax), umin)},
	right[2] = {std::max(std::min(uc, umax), umin),
				std::max(std::min(uc, umax), umin)};

	if (ex_to<numeric>(b_roots.op(0).evalf()).is_real()) {
		if (ex_to<numeric>((b_roots.op(0)-b_roots.op(1)).evalf()).is_positive())
			b_roots = lst{b_roots.op(1), b_roots.op(0)}; // rearrange to have minimum value first
		left[0] = std::min(std::max(ex_to<numeric>(b_roots.op(0)).to_double(), umin), umax);
		right[0] = std::max(std::min(ex_to<numeric>(b_roots.op(1)).to_double(), umax), umin);
	}
	if (ex_to<numeric>(t_roots.op(0).evalf()).is_real()) {
		if (ex_to<numeric>((t_roots.op(0)-t_roots.op(1)).evalf()).is_positive())
			t_roots = lst{t_roots.op(1), t_roots.op(0)}; // rearrange to have minimum value first
		left[1] = std::min(std::max(ex_to<numeric>(t_roots.op(0)).to_double(), umin), umax);
		right[1] = std::max(std::min(ex_to<numeric>(t_roots.op(1)).to_double(), umax), umin);
	}

#line 4834 "cycle.nw"
	if (sign > 0) { // elliptic metric
		
#line 4997 "cycle.nw"
if (determinant > epsilon) {
 double u[2][4], v[2][4];
 if (with_header)
  ost << " /circle of radius " << r  << endl;
 if (uc+r < umin || uc-r > umax || vc+r< vmin || vc-r > vmax ||
	 pow(std::max(umax-uc,uc-umin),2.0)+pow(std::max(vmax-vc,vc-vmin),2.0)<determinant) {
	  if (with_header)
		  ost << "   // out of the window " << endl;
 } else {

#line 5010 "cycle.nw"
	if ( vc-vmax > epsilon) {
		u[0][2] = left[1]; u[0][3] = right[1];
		u[1][2] = left[0]; u[1][3] = right[0];
		u[0][0] = u[1][0] = uc;
		u[0][1] = u[1][1] = uc;

#line 5018 "cycle.nw"
	} else if (vc-vmin > epsilon) {
		u[0][0] = left[1]; u[0][1] = right[1];
		u[0][2] = right[0]; u[0][3] = left[0];

		if (uc-r-umin > epsilon)
			u[1][0] = u[1][3] = uc-r;
		else
			u[1][0] = u[1][3] = umin;

		if (umax-uc-r > epsilon)
			u[1][1] = u[1][2] = uc+r;
		else
			u[1][1] = u[1][2] = umax;

#line 5034 "cycle.nw"
 } else {
  u[0][0] = left[1]; u[0][1] = right[1];
  u[1][0] = left[0]; u[1][1] = right[0];
  u[0][2] = u[1][2] = uc;
  u[0][3] = u[1][3] = uc;
 }

#line 5044 "cycle.nw"
 lst y_roots;
 for (int j=0; j<2; j++)
  for (int i=0; i<4; i++)
   if (abs(u[j][i]-uc) < epsilon) // Touch the horizontal boundary?
    v[j][i] = (i==0 || i ==1? vc+r : vc-r);
   else if (abs(u[j][i]-uc-r)<epsilon || abs(u[j][i]-uc+r)<epsilon) // Touch the vertical boundary?
    v[j][i] = vc;
   else {
    y_roots = Cf.roots(u[j][i], false);
    if (ex_to<numeric>(y_roots.op(0)).is_real()) { // does circle intersect the boundary?
     if (i<2)
		 v[j][i] = std::min(ex_to<numeric>(std::max(y_roots.op(0), y_roots.op(1))).to_double(), vmax);
     else
		 v[j][i] = std::max(ex_to<numeric>(std::min(y_roots.op(0), y_roots.op(1))).to_double(), vmin);
    } else
     v[j][i] = vc;
   }

#line 5066 "cycle.nw"
 for (int i=0; i<4; i++) {// actual drawing of four arcs
  int s = (i==0 || i ==2? -1:1);
  if ((u[0][i] != u[1][i]) || (v[0][i] != v[1][i])) {// do not draw empty arc
   ost << "  " << (only_path ? already_drawn : draw_start.str()) << u[0][i] <<","
	   << v[0][i] << "){" << s*(v[0][i]-vc) << "," << s*(uc-u[0][i])
	   << (asymptote ? "}::{" : "}...{")
	   << s*(v[1][i]-vc) << "," << s*(uc-u[1][i]) << "}(" << u[1][i] <<"," << v[1][i] << ")"
	   << (only_path ? "" : draw_options.str());
   already_drawn="^^(";
  }
 }
 }

#line 5082 "cycle.nw"
} else if (is_almost_zero(determinant)) {
	if (with_header)
		ost << " /circle of zero-radius" << endl;
	
#line 5089 "cycle.nw"
	double U=ex_to<numeric>(uc).to_double();
	double V=ex_to<numeric>(vc).to_double();
	if ((umin <=U) && (umax>=U) && (vmin<=V) && (vmax>=V)) {
		ost << (asymptote ? (only_path ? already_drawn : "dot(") : "draw " )
			<< picture << (picture.size()==0? "" : ",")
			<< (only_path ? "" : "(")
			<< uc << "," << vc << ")" << (only_path ? "" : draw_options.str());
	already_drawn="^^(";

#line 5100 "cycle.nw"
	} else
		if (with_header)
			ost << "// the vertex is out of range" << endl;


#line 5106 "cycle.nw"
} else
	if (with_header)
		ost << " /circle of imaginary radius--not drawing" << endl;

#line 4836 "cycle.nw"
			} else { // parabolic or hyperbolic  metric
		
#line 5113 "cycle.nw"
double u, v, du, dv, k_d = ex_to<numeric>(Cf.get_k()).to_double(),
                 lu = ex_to<numeric>(Cf.get_l(iu)).to_double(),
                 lv = ex_to<numeric>(Cf.get_l(iv)).to_double();

bool change_branch = (sign != 0); // either to do a swap of branches
int zero_or_one = (sign == 0 || k_d*signv > 0 ? 0 : 1); // for parabola and positive k take first

if (sign == 0) {
 
#line 5130 "cycle.nw"
if (sign0 == 0 && Cf.get_l(0).is_zero()) {
	if (with_header)
		ost << " /parabola degenerated into two horizontal lines" << endl;
	cycle2D(0, lst{0, 1}, 2*b_roots.op(0), unit).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, is_continuation);
	cycle2D(0, lst{0, 1}, 2*b_roots.op(1), unit).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, true);
	if (with_header)
		ost << endl;
	ost.flags(keep_flags);
	return;

#line 5144 "cycle.nw"
} else if (sign1 == 0 && Cf.get_l(1).is_zero()) {
	if (with_header)
		ost << " /parabola degenerated into two vertical lines" << endl;
	cycle2D(0, lst{1, 0}, 2*b_roots.op(0), unit).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, is_continuation);
	cycle2D(0, lst{1, 0}, 2*b_roots.op(1), unit).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, true);
	if (with_header)
		ost << endl;
	ost.flags(keep_flags);
	return;
}

#line 5160 "cycle.nw"
if (with_header)
	ost << " /parabola" << endl;
 if (right[0]-left[0] > epsilon && right[1]-left[1] > epsilon) {
	if (k_d*(signu*lv+signv*lu) > 0) { //rearrange intervals
		double e = left[1]; left[1] = right[0]; right[0] = left[0]; left[0] =e;
	} else {
		double e = left[1]; left[1] = right[1]; right[1] = right[0]; right[0] =e;
	}
 }

#line 5179 "cycle.nw"
for (int i =0; i < 2; i++) {
	if (right[i]-left[i] > epsilon) { // a proper branch of a parabola
		double cp[8];
		if (not_swapped) {
			cp[0] = left[i];
			cp[1] = ex_to<numeric>(Cf.val(lst{cp[0],0})/2.0/Cf.get_l(1)).to_double();
			cp[6] = right[i];
			cp[7] = ex_to<numeric>(Cf.val(lst{cp[6],0})/2.0/Cf.get_l(1)).to_double();
			cp[2] = 2.0/3.0*cp[0]+1.0/3.0*cp[6];
			cp[3] = ex_to<numeric>((numeric(1,6)*cp[0]*cp[0]*Cf.get_k() + 1.0/3.0*cp[0]*cp[6]*Cf.get_k()
									- 2.0/3.0*cp[0]*Cf.get_l(0)- 1.0/3.0*Cf.get_l(0)*cp[6]+Cf.get_m()/2.0)/Cf.get_l(1)).to_double();
			cp[4] = 1.0/3.0*cp[0]+2.0/3.0*cp[6];
			cp[5] = ex_to<numeric>((1.0/3.0*cp[0]*Cf.get_k()*cp[6]-1.0/3.0*cp[0]*Cf.get_l(0)
									-2.0/3.0*Cf.get_l(0)*cp[6]+numeric(1,6)*Cf.get_k()*cp[6]*cp[6]
									+Cf.get_m()/2.0)/Cf.get_l(1)).to_double();

#line 5197 "cycle.nw"
  } else {
			cp[1] = left[i];
			cp[0] = ex_to<numeric>(Cf.val(lst{0,cp[1]})/2.0/Cf.get_l(0)).to_double();
			cp[7] = right[i];
			cp[6] = ex_to<numeric>(Cf.val(lst{0,cp[7]})/2.0/Cf.get_l(0)).to_double();
			cp[3] = 2.0/3.0*cp[1]+1.0/3.0*cp[7];
			cp[2] = ex_to<numeric>((numeric(1,6)*cp[1]*cp[1]*Cf.get_k() + 1.0/3.0*cp[1]*cp[7]*Cf.get_k()
									- 2.0/3.0*cp[1]*Cf.get_l(1)- 1.0/3.0*Cf.get_l(1)*cp[7]+Cf.get_m()/2.0)/Cf.get_l(0)).to_double();
			cp[5] = 1.0/3.0*cp[1]+2.0/3.0*cp[7];
			cp[4] = ex_to<numeric>((1.0/3.0*cp[1]*Cf.get_k()*cp[7]-1.0/3.0*cp[1]*Cf.get_l(1)
									-2.0/3.0*Cf.get_l(1)*cp[7]+numeric(1,6)*Cf.get_k()*cp[7]*cp[7]
									+Cf.get_m()/2.0)/Cf.get_l(0)).to_double();
  }

#line 5213 "cycle.nw"
	ost <<  (only_path ? already_drawn : draw_start.str()) << cp[0] << "," << cp[1] << ") .. controls (";
if (asymptote)
	ost <<  cp[2] << "," << cp[3] << ") and (" <<  cp[4] << "," << cp[5] << ") .. (";
else
	ost <<  "(" << cp[2] << "," << cp[3] << ")) and ((" <<  cp[4] << "," << cp[5] << ")) .. (";
ost <<  cp[6] << "," << cp[7] << ")" << (only_path ? "" : draw_options.str());
already_drawn="^^(";
	}
}

#line 5122 "cycle.nw"
} else {
 
#line 5226 "cycle.nw"
if (abs(determinant)<epsilon) {
	if (with_header)
		ost << " / a light cone at (" << xc << "," << yc <<")" << endl;
	cycle2D(0, lst{1, 1}, 2*(uc+vc), unit).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																 false, 0, asymptote, picture, only_path, is_continuation);
	cycle2D(0, lst{1, -1}, 2*(uc-vc), unit).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																  false, 0, asymptote, picture, only_path, true);

#line 5236 "cycle.nw"
	if (! only_path) {
		
#line 5089 "cycle.nw"
	double U=ex_to<numeric>(uc).to_double();
	double V=ex_to<numeric>(vc).to_double();
	if ((umin <=U) && (umax>=U) && (vmin<=V) && (vmax>=V)) {
		ost << (asymptote ? (only_path ? already_drawn : "dot(") : "draw " )
			<< picture << (picture.size()==0? "" : ",")
			<< (only_path ? "" : "(")
			<< uc << "," << vc << ")" << (only_path ? "" : draw_options.str());
	already_drawn="^^(";

#line 5100 "cycle.nw"
	} else
		if (with_header)
			ost << "// the vertex is out of range" << endl;

#line 5238 "cycle.nw"
		if (with_header)
			ost << endl;
	}
	ost.flags(keep_flags);
	return;

#line 5246 "cycle.nw"
} else {
	if (with_header)
		ost << " /hyperbola" << endl;
	if (vmin-vc > epsilon) {
		double e = left[1]; left[1] = right[0]; right[0] = left[0]; left[0] =e;
		change_branch = false;
		zero_or_one = (k_d*signv > 0 ? 1 : 0);
	}
	if (vc-vmax > epsilon) {
		double e = left[1]; left[1] = right[1]; right[1] = right[0]; right[0] =e;
		change_branch = false;
		zero_or_one = (k_d*signv > 0 ? 0 : 1);
	}
}

#line 5263 "cycle.nw"
int points = (points_per_arc == 0? 7 : points_per_arc);
for (int i =0; i < 2; i++) {
	double dir = ex_to<numeric>(csgn(signv*(2*zero_or_one-1))).to_double(); //direction of the tangent vectors
	//double dir = ((sign == 0? lv : signv*(2*zero_or_one-1))<0?-1:1); direction of the tangent vectors (second alternative)
	if (right[i]-left[i] > epsilon ) { // a proper branch of the hyperbola

#line 5272 "cycle.nw"
		double f_left=ex_to<numeric>(asinh((left[i]-uc)/r)).to_double(),
					 f_right=ex_to<numeric>(asinh((right[i]-uc)/r)).to_double();
		DRAW_ARC(ex_to<numeric>(sinh(f_left)*r+uc).to_double(), (only_path ? already_drawn : draw_start.str()));
		for (int j=1; j<points; j++) {
			DRAW_ARC(ex_to<numeric>(sinh(f_left*(1.0-j/(points-1.0))+f_right*j/(points-1.0))*r+uc).to_double(),
					 (asymptote ? "::(" : "...(") );
		}
		ost << (only_path ? "" : draw_options.str());
		already_drawn="^^(";
	}
	if (change_branch)
		zero_or_one = 1 - zero_or_one; // make a swap for the next branch of hyperbola
 }

#line 5124 "cycle.nw"
}

#line 4838 "cycle.nw"
			}
ost << endl;
ost.flags(keep_flags);
return;
}

#line 5292 "cycle.nw"
paravector::paravector() : vector() {
#if GINAC_VERSION_ATLEAST(1,7,1)
#else
	std::cerr << "GiNaC version is prior 1.7.1, the paravector formalism will not work properly!!!" << std::endl;
#endif
}

paravector::paravector(const ex & b) {
#if GINAC_VERSION_ATLEAST(1,7,1)
#else
	std::cerr << "GiNaC version is prior 1.7.1, the paravector formalism will not work properly!!!" << std::endl;
#endif
	vector=ex_to<basic>(b);
}

void paravector::archive(archive_node &n) const {
	inherited::archive(n);
	n.add_ex("vector", vector);
}

void paravector::read_archive(const archive_node &n, lst &sym_lst) {
	inherited::read_archive(n, sym_lst);
	n.find_ex("vector", vector, sym_lst);
}
GINAC_BIND_UNARCHIVER(paravector);

#line 5320 "cycle.nw"
ex paravector::eval_indexed(const basic & i) const {
	GINAC_ASSERT(i.nops() == 2 && is_a<idx>(i.op(1)));

	idx mu;

#line 5327 "cycle.nw"
	if (is_a<varidx>(i.op(1))) {
		if (ex_to<varidx>(i.op(1)).is_contravariant()) {
			mu=varidx(ex_to<varidx>(i.op(1)).get_value()+1, ex_to<varidx>(i.op(1)).get_dim()+1,false);
		} else {
			mu=varidx(ex_to<varidx>(i.op(1)).get_value()+1, ex_to<varidx>(i.op(1)).get_dim()+1,true);
		}
	} else if(is_a<idx>(i.op(1)))
		mu=idx(ex_to<varidx>(i.op(1)).get_value()+1, ex_to<varidx>(i.op(1)).get_dim()+1);
	else
		throw(std::invalid_argument("paravector::eval_indexed(): second argument shall be an index"));

#line 5340 "cycle.nw"
	ex e=indexed(vector, mu);

	if (is_a<indexed>(e) && e.op(1).is_equal(mu))
		return i.hold();
	else
		return e;
}

#line 5350 "cycle.nw"
void paravector::do_print(const print_dflt & c, unsigned level) const {
	c.s << vector;
}

void paravector::do_print_latex(const print_latex & c, unsigned level) const {
	c.s << vector;
}

#line 5360 "cycle.nw"
ex paravector::subs(const ex & e, unsigned options) const {
	return paravector(vector.subs(e,options));
}

ex paravector::subs(const exmap & m, unsigned options) const {
	return paravector(vector.subs(m,options));
}

#line 5370 "cycle.nw"
return_type_t paravector::return_type_tinfo() const {
	return make_return_type_t<paravector>();
}

int paravector::compare_same_type(const basic &other) const {
	GINAC_ASSERT(is_a<paravector>(other));
	return inherited::compare_same_type(other);
}

#line 5381 "cycle.nw"
ex paravector::op(size_t i) const {
	GINAC_ASSERT(i==0);
	return vector;
}

ex & paravector::let_op(size_t i) {
	GINAC_ASSERT(i==0);
	return vector;
}

#line 5401 "cycle.nw"
//////////
// Jump function
//////////

static ex jump_fnct_evalf(const ex & arg) {
	if (is_exactly_a<numeric>(arg)) {
		if ((ex_to<numeric>(arg).is_real() && ex_to<numeric>(arg).is_positive())
			|| ex_to<numeric>(arg).is_zero())
			return numeric(1);
		else
			return numeric(-1);
	}

	return jump_fnct(arg).hold();
}

#line 5419 "cycle.nw"
static ex jump_fnct_eval(const ex & arg) {
	if (is_exactly_a<numeric>(arg)) {
		if ((ex_to<numeric>(arg).is_real() && ex_to<numeric>(arg).is_positive())
			|| ex_to<numeric>(arg).is_zero())
			return numeric(1);
		else
			return numeric(-1);
	} else if (is_exactly_a<mul>(arg) &&
			   is_exactly_a<numeric>(arg.op(arg.nops()-1))) {
		numeric oc = ex_to<numeric>(arg.op(arg.nops()-1));
		if (oc.is_real()) {
			if (oc > 0)
				// jump_fnct(42*x) -> jump_fnct(x)
				return jump_fnct(arg/oc).hold();
			else
				// jump_fnct(-42*x) -> jump_fnct(-x)
				return jump_fnct(-arg/oc).hold();
		}
	}
	return jump_fnct(arg).hold();
}

#line 5443 "cycle.nw"
static ex jump_fnct_conjugate(const ex & arg) {
	return jump_fnct(arg);
}

#line 5449 "cycle.nw"
static ex jump_fnct_power(const ex & arg, const ex & exp) {
	if (is_a<numeric>(exp) && ex_to<numeric>(exp).is_integer()) {
		if (ex_to<numeric>(exp).is_even())
			return numeric(1);
		else
			return jump_fnct(arg);
	}
	if (is_a<numeric>(exp) && ex_to<numeric>(-exp).is_positive())
		return ex_to<basic>(pow(jump_fnct(arg), -exp)).hold();
	return ex_to<basic>(pow(jump_fnct(arg), exp)).hold();
}

#line 5463 "cycle.nw"
static void jump_fnct_print_dflt_text(const ex & x, const print_context & c) {
	c.s << "H("; x.print(c); c.s << ")";
}

static void jump_fnct_print_latex(const ex & x, const print_context & c) {
	c.s << "\\chi("; x.print(c); c.s << ")";
}

#line 5473 "cycle.nw"
REGISTER_FUNCTION(jump_fnct, eval_func(jump_fnct_eval).
      evalf_func(jump_fnct_evalf).
      latex_name("\\chi").
      //text_name("H").
      print_func<print_dflt>(jump_fnct_print_dflt_text).
      print_func<print_latex>(jump_fnct_print_latex).
      //derivative_func(2*delta).
      power_func(jump_fnct_power).
      conjugate_func(jump_fnct_conjugate));

#line 5485 "cycle.nw"
const string equality(const ex & E) {
	if (E.normal().is_zero())
		return "-equal-";
	else
		return "DIFFERENT!!!";
}

#line 5494 "cycle.nw"
const string eph_case(const numeric & sign) {
	if (numeric(sign-(-1)).is_zero())
		return "Elliptic case (sign = -1)";
	if (numeric(sign).is_zero())
		return "Parabolic case (sign = 0)";
	if (numeric(sign-1).is_zero())
		return "Hyperbolic case (sign = 1)";
	return "Unknown case!!!!";
}

#line 5506 "cycle.nw"
ex scalar_part(const ex & e) {
	ex given=canonicalize_clifford(e.expand()),
		out=0, term;
	if (is_a<add>(given)){
		for (size_t i=0; i<given.nops(); i++) {
			try {
				term=remove_dirac_ONE(given.op(i));
			} catch (exception &p) {
				term=0;
			}
			out+=term;
		}
		return out.normal();
	} else{
		try {
			return remove_dirac_ONE(given);
		} catch (exception &p) {
			return 0;
		}
	}
}

#line 5531 "cycle.nw"
matrix sl2_clifford(const ex & M, const ex & e, bool not_inverse) {
	if (is_a<matrix>(M) || M.info(info_flags::list))
		return sl2_clifford(M.op(0), M.op(1), M.op(2), M.op(3), e, not_inverse);
	else
		throw(std::invalid_argument("sl2_clifford(): expect a list or matrix as the first parameter"));
}

#line 5540 "cycle.nw"
matrix sl2_clifford(const ex & a, const ex & b, const ex & c, const ex & d, const ex & e, bool not_inverse) {
	if (is_a<clifford>(e)) {
		ex e0,
			one = dirac_ONE(ex_to<clifford>(e).get_representation_label());
		if (ex_to<idx>(e.op(1)).get_dim()==2)
			e0 = e.subs(e.op(1) == 0);
		else
			e0 = one;
		if (not_inverse)
			return matrix(2, 2,
						  lst{a * one, b * e0,
								  c * pow(e0, 3), d * one});
		else
			return matrix(2, 2,
						  lst{d * one, -b * e0,
								  -c * pow(e0, 3), a * one});
	} else
		throw(std::invalid_argument("sl2_clifford(): expect a clifford numeber as a parameter"));
}

#line 5562 "cycle.nw"
matrix sl2_clifford(const ex & M1, const ex & M2, const ex & e, bool not_inverse) {
	if ((is_a<matrix>(M1) || M1.info(info_flags::list)) && (is_a<matrix>(M2) || M2.info(info_flags::list)))
		return sl2_clifford(M1.op(0), M1.op(1), M1.op(2), M1.op(3), M2.op(0), M2.op(1), M2.op(2), M2.op(3),
							e, not_inverse);
	else
		throw(std::invalid_argument("sl2_clifford(): expect a list or matrix as the first parameter"));
}

#line 5572 "cycle.nw"
matrix sl2_clifford(const ex & a1, const ex & b1, const ex & c1, const ex & d1,
					const ex & a2, const ex & b2, const ex & c2, const ex & d2,
					const ex & e, bool not_inverse) {
	if (is_a<clifford>(e)) {
		ex one = dirac_ONE(ex_to<clifford>(e).get_representation_label());
		if (ex_to<idx>(e.op(1)).get_dim()==2) {
			ex e0 = e.subs(e.op(1) == 0);
			ex e1 = e.subs(e.op(1) == 1);
			ex e01=e0*e1;
			if (not_inverse)
				return matrix(2, 2,
							  lst{a1*one+a2*e01, b1*e0+b2*e1,
									  -c1*e0+c2*e1, d1*one-d2*e01});
			else
				return matrix(2, 2,
							  lst{d1*one+d2*e01, -b1*e0-b2*e1,
									  c1*e0-c2*e1, a1*one-a2*e01});

#line 5592 "cycle.nw"
		} else {
			ex e0 = e.subs(e.op(1) == 0);
			if (not_inverse)
				return matrix(2, 2,
							  lst{a1*one+a2*e0, b1*one+b2*e0,
									  c1*one+c2*e0, d1*one+d2*e0});
			else
				return matrix(2, 2,
							  lst{d1*one+d2*e0, -b1*one-b2*e0,
									  -c1*one-c2*e0, a1*one+a2*e0});
		}
	} else
		throw(std::invalid_argument("sl2_clifford(): expect a clifford numeber as a parameter"));
}

} // namespace MoebInv

