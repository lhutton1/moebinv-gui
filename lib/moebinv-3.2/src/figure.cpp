#line 7633 "figure.nw"
// The library for ensembles of interrelated cycles in non-Euclidean geometry
//
//  Copyright (C) 2014-2018 Vladimir V. Kisil <kisilv@maths.leeds.ac.uk>
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

#line 3919 "figure.nw"
#include <iostream>

#if __cplusplus >= 201703L
  #include <filesystem>
#endif

#include "figure.h"

namespace MoebInv {
using namespace std;
using namespace GiNaC;
#line 3354 "figure.nw"
const ex evaluation_assist = lst{power(cos(wild(0)),2)==1-power(sin(wild(0)),2),
		power(cosh(wild(1)),2)==1+power(sinh(wild(1)),2)};
#line 3688 "figure.nw"
const ex metric_e = clifford_unit(varidx(symbol("i"), numeric(2)), indexed(diag_matrix(lst{-1,-1}), sy_symm(),
																		   varidx(symbol("j"), numeric(2)), varidx(symbol("k"), numeric(2))));
const ex metric_p = clifford_unit(varidx(symbol("i"), numeric(2)), indexed(diag_matrix(lst{-1,0}), sy_symm(),
																		   varidx(symbol("j"), numeric(2)), varidx(symbol("k"), numeric(2))));
const ex metric_h = clifford_unit(varidx(symbol("i"), numeric(2)), indexed(diag_matrix(lst{-1,1}), sy_symm(),
varidx(symbol("j"), numeric(2)), varidx(symbol("k"), numeric(2))));
#line 3944 "figure.nw"
unsigned do_not_update_subfigure = 0x0100;

#line 3948 "figure.nw"
bool FIGURE_DEBUG=true;
#line 3953 "figure.nw"
bool show_asy_graphics=true;
#line 3958 "figure.nw"
GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle_data, basic,
									 print_func<print_dflt>(&cycle_data::do_print))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle_relation, basic,
									 print_func<print_dflt>(&cycle_relation::do_print).
print_func<print_tree>(&cycle_relation::do_print_tree))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(subfigure, basic,
									 print_func<print_dflt>(&subfigure::do_print))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle_node, basic,
									 print_func<print_dflt>(&cycle_node::do_print).
print_func<print_tree>(&cycle_relation::do_print_tree))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(figure, basic,
									 print_func<print_dflt>(&figure::do_print))

#line 3979 "figure.nw"
const ex epsilon=GiNaC::pow(10,-Digits/2);
#line 3984 "figure.nw"
bool is_less_than_epsilon(const ex & x)
{
		return ( x.is_zero() || abs(x).evalf() < epsilon ) ;
}
#line 7181 "figure.nw"
ex cycle_orthogonal(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{(ex)lst{ex_to<cycle>(C1).is_orthogonal(ex_to<cycle>(C2))}};
}
#line 7189 "figure.nw"
ex cycle_f_orthogonal(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{(ex)lst{ex_to<cycle>(C1).is_f_orthogonal(ex_to<cycle>(C2))}};
}
#line 7197 "figure.nw"
ex cycle_adifferent(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{(ex)lst{cycle_data(C1).is_almost_equal(ex_to<basic>(cycle_data(C2)),true)? 0: 1}};
}
#line 7210 "figure.nw"
ex check_tangent(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{(ex)lst{pow(ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2)),2)
				-ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))
				*ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2)) == 0}};
}
#line 7225 "figure.nw"
ex cycle_tangent(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))+numeric(1)==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
				   -sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0},
			   lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))-numeric(1)==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
				   -sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0},
			   lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))+numeric(1)==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
				   +sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0},
			   lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))-numeric(1)==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
				   +sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0}};
}
#line 7244 "figure.nw"
ex cycle_tangent_o(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))+numeric(1)==0,
				ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
				-sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0},
			lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))-numeric(1)==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
					-sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0}};
}
#line 7257 "figure.nw"
ex cycle_tangent_i(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))+numeric(1)==0,
				ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
				+sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0},
			lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))-numeric(1)==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2))
					+sqrt(abs(ex_to<cycle>(C2).cycle_product(ex_to<cycle>(C2))))==0}};
}
#line 7270 "figure.nw"
ex cycle_different(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{(ex)lst{ex_to<cycle>(C1).is_equal(ex_to<basic>(C2), true)? 0: 1}};
}
#line 7279 "figure.nw"
ex product_sign(const ex & C1, const ex & C2, const ex & pr)
{
	if (is_less_than_epsilon(ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1)).evalf().imag_part()))
		return lst{(ex)lst{pr*(ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1)).evalf().real_part() - epsilon) <0}};
	else
		return lst{(ex)lst{numeric(1) <0}};
}
#line 7293 "figure.nw"
ex cycle_angle(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2).normalize_norm())-pr==0,
				ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))+numeric(1)==0},
			lst{ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C2).normalize_norm())-pr==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))-numeric(1)==0}};
}
#line 7304 "figure.nw"
ex steiner_power(const ex & C1, const ex & C2, const ex & pr)
{
	cycle C=ex_to<cycle>(C2).normalize();
	return lst{lst{ex_to<cycle>(C1).cycle_product(C)+sqrt(abs(C.cycle_product(C)))
				-pr*ex_to<cycle>(C1).get_k()==0,
				ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))+numeric(1)==0},
			lst{ex_to<cycle>(C1).cycle_product(C)+sqrt(abs(C.cycle_product(C)))
						-pr*ex_to<cycle>(C1).get_k()==0,
					ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))-numeric(1)==0}};
}
#line 7318 "figure.nw"
ex cycle_cross_t_distance(const ex & C1, const ex & C2, const ex & pr)
{
	cycle C=ex_to<cycle>(C2).normalize();
	return lst{lst{ex_to<cycle>(C1).cycle_product(C)-sqrt(abs(C.cycle_product(C)))
				-pow(pr,2)*ex_to<cycle>(C1).get_k()==0,
				ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))+numeric(1)==0},
			lst{ex_to<cycle>(C1).cycle_product(C)-sqrt(abs(C.cycle_product(C)))
				-pow(pr,2)*ex_to<cycle>(C1).get_k()==0,
				ex_to<cycle>(C1).cycle_product(ex_to<cycle>(C1))-numeric(1)==0}};
}
#line 7332 "figure.nw"
ex coefficients_are_real(const ex & C1, const ex & C2, const ex & pr)
{
	cycle C=ex_to<cycle>(ex_to<cycle>(C1.evalf()).imag_part());
	if (! (is_less_than_epsilon(C.get_k()) && is_less_than_epsilon(C.get_m())))
		return lst{(ex)lst{0}};
	for (int i=0; i < ex_to<cycle>(C1).get_dim(); ++i)
		if (! is_less_than_epsilon(C.get_l(i)))
			return lst{(ex)lst{0}};

	return lst{(ex)lst{1}};
}
#line 7352 "figure.nw"
ex angle_is(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{(ex)lst{ex_to<cycle>(C1).normalize_norm().cycle_product(ex_to<cycle>(C2).normalize_norm())}};
}
#line 7361 "figure.nw"
ex power_is(const ex & C1, const ex & C2, const ex & pr)
{
	cycle Ca=ex_to<cycle>(C1).normalize(), Cb=ex_to<cycle>(C2).normalize();

	return lst{(ex)lst{Ca.cycle_product(Cb)+pr*sqrt(abs(Ca.cycle_product(Ca)*Cb.cycle_product(Cb)))}};
}
#line 7371 "figure.nw"
ex cycle_moebius(const ex & C1, const ex & C2, const ex & pr)
{
	return lst{(ex)lst{ex_to<cycle>(C2).matrix_similarity(pr.op(0),pr.op(1),pr.op(2),pr.op(3))}};
}
#line 7379 "figure.nw"
cycle_relation sl2_transform(const ex & key, bool cm, const ex & matrix) {
	if (is_a<lst>(matrix) && matrix.op(0).info(info_flags::real) && matrix.op(1).info(info_flags::real)
		&& matrix.op(2).info(info_flags::real) && matrix.op(3).info(info_flags::real))
			return cycle_relation(key, cycle_sl2, cm, matrix);
	else
		throw(std::invalid_argument("sl2_transform(): shall be applied only with a matrix having"
									" real entries"));
}
#line 7391 "figure.nw"
ex cycle_sl2(const ex & C1, const ex & C2, const ex & pr)
{
	if (ex_to<cycle>(C2).get_dim() == 2)
		return lst{(ex)lst{ex_to<cycle>(C2).sl2_similarity(pr.op(0),pr.op(1),pr.op(2),pr.op(3),
													   ex_to<cycle>(C2).get_unit())}};
	else
		throw(std::invalid_argument("cycle_sl2(): shall be applied only in two dimensions"));
}
#line 3997 "figure.nw"
cycle_data::cycle_data() : k_cd(), l_cd(), m_cd()
{
	;
}

#line 4004 "figure.nw"
cycle_data::cycle_data(const ex & C)
{
	if (is_a<cycle>(C)) {
		cycle C_new=ex_to<cycle>(C).normalize();
		
#line 4012 "figure.nw"
		k_cd=C_new.get_k();
		l_cd=C_new.get_l();
		m_cd=C_new.get_m();


#line 4018 "figure.nw"
	} else if (is_a<cycle_data>(C)) {
		cycle_data C_new=ex_to<cycle_data>(C);
		
#line 4012 "figure.nw"
		k_cd=C_new.get_k();
		l_cd=C_new.get_l();
		m_cd=C_new.get_m();

#line 4021 "figure.nw"
	} else
		throw(std::invalid_argument("cycle_data(): accept only cycle or cycle_data"
									" as the parameter"));
}

#line 4028 "figure.nw"
cycle_data::cycle_data(const ex & k1, const ex l1, const ex &m1, bool normalize)
{
	k_cd = k1;
	l_cd = l1;
	m_cd = m1;
	if (normalize) {
		ex ratio = 0;
		if (!k_cd.is_zero()) // First non-zero coefficient among k_cd, m_cd, l_0, l_1, ... is set to 1
			ratio = k_cd;
		else if (!m_cd.is_zero())
			ratio = m_cd;
		else {
			for (unsigned int i=0; i<get_dim(); i++)
				if (!l_cd.subs(l_cd.op(1) == i).is_zero()) {
					ratio = l_cd.subs(l_cd.op(1) == i);
					break;
				}
		}

		if (!ratio.is_zero()) {
			k_cd=(k_cd/ratio).normal();
			l_cd=indexed((l_cd.op(0)/ratio).evalm().normal(), l_cd.op(1));
			m_cd=(m_cd/ratio).normal();
		}
	}
}

#line 4057 "figure.nw"
return_type_t cycle_data::return_type_tinfo() const
{
	return make_return_type_t<cycle_data>();
}

#line 4064 "figure.nw"
int cycle_data::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle_data>(other));
	   return inherited::compare_same_type(other);
}


#line 4073 "figure.nw"
void cycle_data::do_print(const print_dflt & con, unsigned level) const
{
	con.s << "`";
	this->k_cd.print(con, level);
	con.s << ", ";
	this->l_cd.print(con, level);
	con.s << ", ";
	this->m_cd.print(con, level);
	con.s << "'";
}

#line 4086 "figure.nw"
void cycle_data::do_print_double(const print_dflt & con, unsigned level) const
{
	if (! is_a<numeric>(get_dim())) {
		do_print(con, level);
	} else {

#line 4094 "figure.nw"
		con.s << "(";
		if ((is_a<numeric>(k_cd) && ! ex_to<numeric>(k_cd).is_crational())
			|| is_a<numeric>(k_cd.evalf())) {
			ex f=k_cd.evalf();
			
#line 4102 "figure.nw"
			con.s << ex_to<numeric>(f).to_double(); // only real part is converted
			if (! ex_to<numeric>(f).is_real()) {
				double b=ex_to<numeric>(f.imag_part()).to_double();
				if (b>0)
					con.s << "+";
				con.s << b << "*I";
			}


#line 4112 "figure.nw"
		} else
			k_cd.print(con, level);
		con.s << ", [[";

#line 4118 "figure.nw"
		int D=ex_to<numeric>(get_dim()).to_int();
		for(int i=0; i< D; ++i) {
			if ((is_a<numeric>(l_cd.op(0).op(i)) && ! ex_to<numeric>(l_cd.op(0).op(i)).is_crational())
				|| is_a<numeric>(l_cd.op(0).op(i).evalf())) {
				ex f=ex_to<numeric>(l_cd.op(0).op(i)).evalf();
				
#line 4102 "figure.nw"
			con.s << ex_to<numeric>(f).to_double(); // only real part is converted
			if (! ex_to<numeric>(f).is_real()) {
				double b=ex_to<numeric>(f.imag_part()).to_double();
				if (b>0)
					con.s << "+";
				con.s << b << "*I";
			}

#line 4124 "figure.nw"
			} else
				l_cd.op(0).op(i).print(con, level);
			if (i<D-1)
				con.s << ",";
		}
		con.s << "]]";
		l_cd.op(1).print(con, level);

#line 4134 "figure.nw"
		con.s << ", ";
		if ((is_a<numeric>(m_cd) && ! ex_to<numeric>(m_cd).is_crational())
			|| is_a<numeric>(m_cd.evalf())) {
			ex f=m_cd.evalf();
			
#line 4102 "figure.nw"
			con.s << ex_to<numeric>(f).to_double(); // only real part is converted
			if (! ex_to<numeric>(f).is_real()) {
				double b=ex_to<numeric>(f.imag_part()).to_double();
				if (b>0)
					con.s << "+";
				con.s << b << "*I";
			}

#line 4139 "figure.nw"
		} else
			m_cd.print(con, level);
		con.s << ")";
	}
}

#line 4147 "figure.nw"
void cycle_data::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("k-val", k_cd);
	n.add_ex("l-val", l_cd);
	n.add_ex("m-val", m_cd);
}

#line 4157 "figure.nw"
void cycle_data::read_archive(const archive_node &n, lst &sym_lst)
{
	inherited::read_archive(n, sym_lst);
	n.find_ex("k-val", k_cd, sym_lst);
	n.find_ex("l-val", l_cd, sym_lst);
	n.find_ex("m-val", m_cd, sym_lst);
}

#line 4167 "figure.nw"
GINAC_BIND_UNARCHIVER(cycle_data);

#line 4171 "figure.nw"
ex cycle_data::op(size_t i) const
{
 GINAC_ASSERT(i<nops());
	switch(i) {
	case 0:
		return k_cd;
	case 1:
		return l_cd;
	case 2:
		return m_cd;
	default:
		throw(std::invalid_argument("cycle_data::op(): requested operand out of the range (3)"));
	}
}

#line 4188 "figure.nw"
ex & cycle_data::let_op(size_t i)
{
	ensure_if_modifiable();
	GINAC_ASSERT(i<nops());
	switch(i) {
	case 0:
		return k_cd;
	case 1:
		return l_cd;
	case 2:
		return m_cd;
	default:
		throw(std::invalid_argument("cycle_data::let_op(): requested operand out of the range (3)"));
	}
}

#line 4206 "figure.nw"
ex cycle_data::make_cycle(const ex & metr) const
{
	return cycle(k_cd, l_cd, m_cd, metr);
}

#line 4213 "figure.nw"
bool cycle_data::is_equal(const basic & other, bool projectively) const
{
	if (not is_a<cycle_data>(other))
		return false;
	const cycle_data o = ex_to<cycle_data>(other);
	ex factor=0, ofactor=0;

	if (projectively) {
		// Check that coefficients are scalar multiples of other
		if (not ((m_cd*o.get_k()-o.get_m()*k_cd).normal().is_zero()))
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
		if (not ((get_k()-o.get_k()).normal().is_zero()
				 && (get_m()-o.get_m()).normal().is_zero()))
			return false;


#line 4242 "figure.nw"
	for (unsigned int i=0; i<get_dim(); i++)
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
}

#line 4260 "figure.nw"
bool cycle_data::is_almost_equal(const basic & other, bool projectively) const
{
	if (not is_a<cycle_data>(other))
		return false;
	const cycle_data o = ex_to<cycle_data>(other);
	ex factor=0, ofactor=0;

	if (projectively) {
		// Check that coefficients are scalar multiples of other
		if (! (is_less_than_epsilon(m_cd*o.get_k()-o.get_m()*k_cd)))
			return false;
		// Set up coefficients for proportionality
		if (is_less_than_epsilon(get_k())) {
			factor=get_m();
			ofactor=o.get_m();
		} else {
			factor=get_k();
			ofactor=o.get_k();
		}

	} else
		// Check the exact equality of coefficients
		if (! (is_less_than_epsilon((get_k()-o.get_k()))
				 && is_less_than_epsilon(get_m()-o.get_m())))
			return false;


#line 4289 "figure.nw"
	for (unsigned int i=0; i<get_dim(); i++)
		if (projectively) {
			// search the the first non-zero coefficient
			if (factor.is_zero()) {
				factor=get_l(i);
				ofactor=o.get_l(i);
			} else
				if (! is_less_than_epsilon(get_l(i)*ofactor-o.get_l(i)*factor))
					return false;
		} else
			if (! is_less_than_epsilon(get_l(i)-o.get_l(i)))
				return false;

	return true;
}

#line 4307 "figure.nw"
cycle_data cycle_data::subs(const ex & e, unsigned options) const
{
	return cycle_data(k_cd.subs(e,options),l_cd.subs(e,options),m_cd.subs(e,options),false);
}
#line 4313 "figure.nw"
ex cycle_data::subs(const exmap & em, unsigned options) const
{
	return cycle_data(k_cd.subs(em,options),l_cd.subs(em,options),m_cd.subs(em,options),false);
}

#line 4320 "figure.nw"
ex cycle_data::num_normalize() const
{
	if (! (is_a<numeric>(k_cd) && is_a<numeric>(m_cd)
		   && is_a<numeric>(l_cd.op(0).op(0))  && is_a<numeric>(l_cd.op(0).op(1))))
		return cycle_data(k_cd,l_cd,m_cd,true);

	numeric k1=ex_to<numeric>(k_cd),
		m1=ex_to<numeric>(m_cd);
	numeric r=max(abs(k1),abs(m1));
	for (unsigned int i=0; i<get_dim(); ++i)
		r=max(r,abs(ex_to<numeric>(l_cd.op(0).op(i))));

	if (is_less_than_epsilon(r))
		return cycle_data(k_cd,l_cd,m_cd,true);
	k1/=r; k1=(is_less_than_epsilon(k1)?0:k1);
	m1/=r; m1=(is_less_than_epsilon(m1)?0:m1);
	lst l1;
	for (unsigned int i=0; i<get_dim(); ++i) {
		numeric li= ex_to<numeric>(l_cd.op(0).op(i))/r;
		l1.append(is_less_than_epsilon(li)?0:li);
	}

	return cycle_data(k1,indexed(matrix(1, get_dim(), l1), l_cd.op(1)),m1);
}

#line 4351 "figure.nw"
cycle_relation::cycle_relation() : parkey(), parameter()
{
  rel = cycle_orthogonal;
  use_cycle_metric = true;
}

#line 4359 "figure.nw"
cycle_relation::cycle_relation(const ex & ck, PCR r, bool cm, const ex & p) {
	parkey = ck;
	rel = r;
	use_cycle_metric = cm;
	parameter=p;
}

#line 4368 "figure.nw"
return_type_t cycle_relation::return_type_tinfo() const
{
	return make_return_type_t<cycle_relation>();
}

#line 4375 "figure.nw"
int cycle_relation::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle_relation>(other));
	   return inherited::compare_same_type(other);
	   /*
  const cycle_relation &o = static_cast<const cycle_relation &>(other);
	if ((parkey == o.parkey) && (&rel == &o.rel))
		return 0;
	else if ((parkey < o.parkey) || (&rel < &o.rel))
		return -1;
	else
	return 1;*/
}

#line 4393 "figure.nw"
void cycle_relation::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("cr-parkey", parkey);
	n.add_bool("use_cycle_metric", use_cycle_metric);
	n.add_ex("parameter", parameter);
	ex (*const* ptr)(const ex &, const ex &, const ex &)
		= rel.target<ex(*)(const ex&, const ex &,const ex&)>();
	if (ptr && *ptr == cycle_orthogonal)
		n.add_string("relation", "orthogonal");
	else if (ptr && *ptr == cycle_f_orthogonal)
		n.add_string("relation", "f_orthogonal");
	else if (ptr && *ptr == cycle_different)
		n.add_string("relation", "different");
	else if (ptr && *ptr == cycle_adifferent)
		n.add_string("relation", "adifferent");
	else if (ptr && *ptr == cycle_tangent)
		n.add_string("relation", "tangent");
	else if (ptr && *ptr == cycle_tangent_i)
		n.add_string("relation", "tangent_i");
	else if (ptr && *ptr == cycle_tangent_o)
		n.add_string("relation", "tangent_o");
	else if (ptr && *ptr == cycle_angle)
		n.add_string("relation", "angle");
	else if (ptr && *ptr == steiner_power)
		n.add_string("relation", "steiner_power");
	else if (ptr && *ptr == cycle_cross_t_distance)
		n.add_string("relation", "cross_distance");
	else if (ptr && *ptr == product_sign)
		n.add_string("relation", "product_sign");
	else if (ptr && *ptr == coefficients_are_real)
		n.add_string("relation", "are_real");
	else if (ptr && *ptr == cycle_moebius)
		n.add_string("relation", "moebius");
	else if (ptr && *ptr == cycle_sl2)
		n.add_string("relation", "sl2");
	else
		throw(std::invalid_argument("cycle_relation::archive(): archiving of this relation is not"
									" implemented"));
}

#line 4436 "figure.nw"
void cycle_relation::read_archive(const archive_node &n, lst &sym_lst)
{
	ex e;
	inherited::read_archive(n, sym_lst);
	n.find_ex("cr-parkey", e, sym_lst);
	if (is_a<symbol>(e))
		parkey=e;
	else
		throw(std::invalid_argument("cycle_relation::read_archive(): read a non-symbol as"
									" a parkey from the archive"));
	n.find_ex("parameter", parameter, sym_lst);
	n.find_bool("use_cycle_metric", use_cycle_metric);
	string relation;
	n.find_string("relation", relation);
	if (relation == "orthogonal")
		rel = cycle_orthogonal;
	else if (relation == "f_orthogonal")
		rel = cycle_f_orthogonal;
	else if (relation == "different")
		rel = cycle_different;
	else if (relation == "adifferent")
		rel = cycle_adifferent;
	else if (relation == "tangent")
		rel = cycle_tangent;
	else if (relation == "tangent_i")
		rel = cycle_tangent_i;
	else if (relation == "tangent_o")
		rel = cycle_tangent_o;
	else if (relation == "angle")
		rel = cycle_angle;
	else if (relation == "steiner_power")
		rel = steiner_power;
	else if (relation == "cross_distance")
		rel = cycle_cross_t_distance;
	else if (relation == "product_sign")
		rel = product_sign;
	else if (relation == "are_real")
		rel = coefficients_are_real;
	else if (relation == "moebius")
		rel = cycle_moebius;
	else if (relation == "sl2")
		rel = cycle_sl2;
	else
		throw(std::invalid_argument("cycle_relation::read_archive(): archive contains unknown"
									" relation"));
}

#line 4485 "figure.nw"
GINAC_BIND_UNARCHIVER(cycle_relation);

#line 4489 "figure.nw"
ex cycle_relation::rel_to_parent(const ex & C1, const ex & pmetric, const ex & cmetric,
								 const exhashmap<cycle_node> & N) const
{
       GINAC_ASSERT(is_a<cycle_data>(C1));

#line 4497 "figure.nw"
	exhashmap<cycle_node>::const_iterator  cnode=N.find(parkey);

#line 4501 "figure.nw"
	lst res,
		cycles=ex_to<lst>(cnode->second.make_cycles(use_cycle_metric? cmetric : pmetric));

	for (const auto& it : cycles) {
		lst calc=ex_to<lst>(rel(ex_to<cycle_data>(C1).make_cycle(use_cycle_metric? cmetric : pmetric),
								ex_to<cycle>(it), parameter));
		for (const auto& it1 : calc)
			res.append(it1);
	}
	return res;
}

#line 4515 "figure.nw"
void cycle_relation::do_print(const print_dflt & con, unsigned level) const
{
	con.s << parkey << (use_cycle_metric? "|" : "/");
	ex (*const* ptr)(const ex &, const ex &, const ex &)
		= rel.target<ex(*)(const ex&, const ex &, const ex &)>();
	if (ptr && *ptr == cycle_orthogonal)
		con.s << "o";
	else if (ptr && *ptr == cycle_f_orthogonal)
		con.s << "f";
	else if (ptr && *ptr == cycle_different)
		con.s << "d";
	else if (ptr && *ptr == cycle_adifferent)
		con.s << "ad";
	else if (ptr && *ptr == cycle_tangent)
		con.s << "t";
	else if (ptr && *ptr == cycle_tangent_i)
		con.s << "ti";
	else if (ptr && *ptr == cycle_tangent_o)
		con.s << "to";
	else if (ptr && *ptr == steiner_power)
		con.s << "s";
	else if (ptr && *ptr == cycle_angle)
		con.s << "a";
	else if (ptr && *ptr == cycle_cross_t_distance)
		con.s << "c";
	else if (ptr && *ptr == product_sign)
		con.s << "p";
	else if (ptr && *ptr == coefficients_are_real)
		con.s << "r";
	else if (ptr && *ptr == cycle_moebius)
		con.s << "m";
	else if (ptr && *ptr == cycle_sl2)
		con.s << "l";
	else
		con.s << "u"; // unknown type of relations
	if (! parameter.is_zero())
		con.s << "[" << parameter << "]";
}

#line 4556 "figure.nw"
void cycle_relation::do_print_tree(const print_tree & con, unsigned level) const
{
	//	inherited::do_print_tree(con,level);
	parkey.print(con,level+con.delta_indent);
	//	con.s <<  std::string(level+con.delta_indent, ' ') << (int)rel <<endl;
}

#line 4565 "figure.nw"
ex cycle_relation::op(size_t i) const
{
 GINAC_ASSERT(i<nops());
	switch(i) {
	case 0:
		return parkey;
	case 1:
		return parameter;
	default:
		throw(std::invalid_argument("cycle_relation::op(): requested operand out of the range (1)"));
	}
}

#line 4580 "figure.nw"
ex & cycle_relation::let_op(size_t i)
{
	ensure_if_modifiable();
	GINAC_ASSERT(i<nops());
	switch(i) {
	case 0:
		return parkey;
	case 1:
		return parameter;
	default:
		throw(std::invalid_argument("cycle_relation::let_op(): requested operand out of the range (1)"));
	}
}

#line 4601 "figure.nw"
subfigure::subfigure() : inherited()
{
}

#line 4607 "figure.nw"
subfigure::subfigure(const ex & F, const ex & l) {
	parlist = ex_to<lst>(l);
	subf = F;
}

#line 4614 "figure.nw"
return_type_t subfigure::return_type_tinfo() const
{
	return make_return_type_t<subfigure>();
}

#line 4621 "figure.nw"
int subfigure::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<subfigure>(other));
	   return inherited::compare_same_type(other);
}

#line 4632 "figure.nw"
void subfigure::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("parlist", ex_to<lst>(parlist));
	n.add_ex("subf", ex_to<figure>(subf));
}

#line 4641 "figure.nw"
void subfigure::read_archive(const archive_node &n, lst &sym_lst)
{
	ex e;
	inherited::read_archive(n, sym_lst);
	n.find_ex("parlist", e, sym_lst);
	if (is_a<lst>(e))
		parlist=ex_to<lst>(e);
	else
		throw(std::invalid_argument("subfigure::read_archive(): read a non-lst as a parlist from"
									" the archive"));
	n.find_ex("subf", e, sym_lst);
	if (is_a<figure>(e))
		subf=ex_to<figure>(e);
	else
		throw(std::invalid_argument("subfigure::read_archive(): read a non-figure as a subf from"
									" the archive"));
}

#line 4661 "figure.nw"
GINAC_BIND_UNARCHIVER(subfigure);

#line 4665 "figure.nw"
void subfigure::do_print(const print_dflt & con, unsigned level) const
{
	con.s << "subfig( " ;
        parlist.print(con, level+1);
		//        subf.print(con, level+1);
	con.s << ")" ;
}

#line 4675 "figure.nw"
inline ex subfigure::subs(const exmap & em, unsigned options) const {
	return subfigure(subf.subs(em,options | do_not_update_subfigure), parlist);
}

#line 4685 "figure.nw"
cycle_node::cycle_node()
{
	generation=0;
	custom_asy="";
}

#line 4693 "figure.nw"
cycle_node::cycle_node(const ex & C, int g)
{
	custom_asy="";
	generation=g;
	
#line 4702 "figure.nw"
	if (is_a<cycle_node>(C)) {
		cycles=ex_to<lst>(ex_to<cycle_node>(C).get_cycles_data());
		generation = ex_to<cycle_node>(C).get_generation();
		children = ex_to<cycle_node>(C).get_children();
		parents = ex_to<cycle_node>(C).get_parents();
	} else
		
#line 4722 "figure.nw"
 	if (is_a<lst>(C)) {
		for (const auto& it : ex_to<lst>(C))
			if ( is_a<cycle_data>(it) || is_a<cycle>(it))
				cycles.append(cycle_data(it));
			else
				throw(std::invalid_argument("cycle_node::cycle_node(): "
											"the parameter is list of something which is not"
											" cycle_data"));
	} else if (is_a<cycle_data>(C)) {
		cycles = lst{C};
	} else if (is_a<cycle>(C)) {
		cycles=lst{cycle_data(ex_to<cycle>(C).get_k(), ex_to<cycle>(C).get_l(),
							  ex_to<cycle>(C).get_m())};
	} else
		throw(std::invalid_argument("cycle_node::cycle_node(): "
									"the first parameters must be either cycle, cycle_data,"
									" cycle_node or list of cycle_data"));


#line 4698 "figure.nw"
}

#line 4712 "figure.nw"
cycle_node::cycle_node(const ex & C, int g, const lst & par)
{
	custom_asy="";
	generation=g;
	
#line 4722 "figure.nw"
 	if (is_a<lst>(C)) {
		for (const auto& it : ex_to<lst>(C))
			if ( is_a<cycle_data>(it) || is_a<cycle>(it))
				cycles.append(cycle_data(it));
			else
				throw(std::invalid_argument("cycle_node::cycle_node(): "
											"the parameter is list of something which is not"
											" cycle_data"));
	} else if (is_a<cycle_data>(C)) {
		cycles = lst{C};
	} else if (is_a<cycle>(C)) {
		cycles=lst{cycle_data(ex_to<cycle>(C).get_k(), ex_to<cycle>(C).get_l(),
							  ex_to<cycle>(C).get_m())};
	} else
		throw(std::invalid_argument("cycle_node::cycle_node(): "
									"the first parameters must be either cycle, cycle_data,"
									" cycle_node or list of cycle_data"));

#line 4717 "figure.nw"
	
#line 4742 "figure.nw"
	GINAC_ASSERT(is_a<lst>(par));
	parents = ex_to<lst>(par);

#line 4718 "figure.nw"
}

#line 4747 "figure.nw"
cycle_node::cycle_node(const ex & C, int g, const lst & par, const lst & ch)
{
	generation=g;
	children=ch;
	custom_asy="";
	
#line 4722 "figure.nw"
 	if (is_a<lst>(C)) {
		for (const auto& it : ex_to<lst>(C))
			if ( is_a<cycle_data>(it) || is_a<cycle>(it))
				cycles.append(cycle_data(it));
			else
				throw(std::invalid_argument("cycle_node::cycle_node(): "
											"the parameter is list of something which is not"
											" cycle_data"));
	} else if (is_a<cycle_data>(C)) {
		cycles = lst{C};
	} else if (is_a<cycle>(C)) {
		cycles=lst{cycle_data(ex_to<cycle>(C).get_k(), ex_to<cycle>(C).get_l(),
							  ex_to<cycle>(C).get_m())};
	} else
		throw(std::invalid_argument("cycle_node::cycle_node(): "
									"the first parameters must be either cycle, cycle_data,"
									" cycle_node or list of cycle_data"));

#line 4753 "figure.nw"
	
#line 4742 "figure.nw"
	GINAC_ASSERT(is_a<lst>(par));
	parents = ex_to<lst>(par);

#line 4754 "figure.nw"
}

#line 4758 "figure.nw"
cycle_node::cycle_node(const ex & C, int g, const lst & par, const lst & ch, string ca)
{
	generation=g;
	children=ch;
	custom_asy=ca;
	
#line 4722 "figure.nw"
 	if (is_a<lst>(C)) {
		for (const auto& it : ex_to<lst>(C))
			if ( is_a<cycle_data>(it) || is_a<cycle>(it))
				cycles.append(cycle_data(it));
			else
				throw(std::invalid_argument("cycle_node::cycle_node(): "
											"the parameter is list of something which is not"
											" cycle_data"));
	} else if (is_a<cycle_data>(C)) {
		cycles = lst{C};
	} else if (is_a<cycle>(C)) {
		cycles=lst{cycle_data(ex_to<cycle>(C).get_k(), ex_to<cycle>(C).get_l(),
							  ex_to<cycle>(C).get_m())};
	} else
		throw(std::invalid_argument("cycle_node::cycle_node(): "
									"the first parameters must be either cycle, cycle_data,"
									" cycle_node or list of cycle_data"));

#line 4764 "figure.nw"
	
#line 4742 "figure.nw"
	GINAC_ASSERT(is_a<lst>(par));
	parents = ex_to<lst>(par);

#line 4765 "figure.nw"
}

#line 4769 "figure.nw"
return_type_t cycle_node::return_type_tinfo() const
{
	return make_return_type_t<cycle_node>();
}

#line 4776 "figure.nw"
ex cycle_node::op(size_t i) const
{
	GINAC_ASSERT(i<nops());
	size_t ncyc=cycles.nops(), nchil=children.nops(), npar=parents.nops();
	if ( i < ncyc)
		return cycles.op(i);
	else if ( i < ncyc + nchil)
		return children.op(i-ncyc);
	else if ( i < ncyc + nchil + npar)
		return parents.op(i-ncyc-nchil);
	else
		throw(std::invalid_argument("cycle_node::op(): requested operand out of the range"));
}

#line 4792 "figure.nw"
ex & cycle_node::let_op(size_t i)
{
	ensure_if_modifiable();
	GINAC_ASSERT(i<nops());
	size_t ncyc=cycles.nops(), nchil=children.nops(), npar=parents.nops();
	if ( i < ncyc)
		return cycles.let_op(i);
	else if ( i < ncyc + nchil)
		return children.let_op(i-ncyc);
	else if ( i < ncyc + nchil + npar)
		return parents.let_op(i-ncyc-nchil);
	else
		throw(std::invalid_argument("cycle_node::let_op(): requested operand out of the range"));
}

#line 4809 "figure.nw"
int cycle_node::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle_node>(other));
	   return inherited::compare_same_type(other);
}

#line 4817 "figure.nw"
ex cycle_node::make_cycles(const ex & metr) const
{
	lst res;
	for (const auto&  it : cycles)
		res.append(ex_to<cycle_data>(it).make_cycle(metr));
	return res;
}

#line 4827 "figure.nw"
void cycle_node::set_cycles(const ex & C)
{
	cycles.remove_all();
	
#line 4722 "figure.nw"
 	if (is_a<lst>(C)) {
		for (const auto& it : ex_to<lst>(C))
			if ( is_a<cycle_data>(it) || is_a<cycle>(it))
				cycles.append(cycle_data(it));
			else
				throw(std::invalid_argument("cycle_node::cycle_node(): "
											"the parameter is list of something which is not"
											" cycle_data"));
	} else if (is_a<cycle_data>(C)) {
		cycles = lst{C};
	} else if (is_a<cycle>(C)) {
		cycles=lst{cycle_data(ex_to<cycle>(C).get_k(), ex_to<cycle>(C).get_l(),
							  ex_to<cycle>(C).get_m())};
	} else
		throw(std::invalid_argument("cycle_node::cycle_node(): "
									"the first parameters must be either cycle, cycle_data,"
									" cycle_node or list of cycle_data"));

#line 4831 "figure.nw"
}

#line 4835 "figure.nw"
void cycle_node::append_cycle(const ex & k, const ex & l, const ex & m)
{
	cycles.append(cycle_data(k,l,m));
}

#line 4842 "figure.nw"
void cycle_node::append_cycle(const ex & C)
{
	if (is_a<cycle>(C))
		cycles.append(cycle_data(ex_to<cycle>(C).get_k(), ex_to<cycle>(C).get_l(),
								   ex_to<cycle>(C).get_m()));
	else 	if (is_a<cycle_data>(C))
		cycles.append(ex_to<cycle_data>(C));
	else
		throw(std::invalid_argument("cycle_node::append_cycle(const ex &): the parameter must be"
									" either cycle or cycle_data"));
}

#line 4856 "figure.nw"
lst cycle_node::get_parents() const
{
	return parents;
}

#line 4863 "figure.nw"
lst cycle_node::get_parent_keys() const
{
	lst pkeys;
	if ( (parents.nops() == 1) && (is_a<subfigure>(parents.op(0)))) {
		pkeys=ex_to<lst>(ex_to<subfigure>(parents.op(0)).get_parlist());
	} else {
		for (const auto& it : parents)
			pkeys.append(ex_to<cycle_relation>(it).get_parkey());
	}
	return pkeys;
}

#line 4878 "figure.nw"
void cycle_node::do_print(const print_dflt & con, unsigned level) const
{
	
#line 4896 "figure.nw"
	con.s << '{';
	for (const auto& it : cycles) {

#line 4881 "figure.nw"
		ex_to<cycle_data>(it).do_print(con, level);
		
#line 4901 "figure.nw"
		con.s << ", ";
	}
	con.s << generation << '}' << " --> (";
	// list all children
	for (lst::const_iterator it = children.begin(); it != children.end();) {
		con.s << (*it);
		++it;
		if (it != children.end())
			con.s <<",";
	}

#line 4914 "figure.nw"
	con.s << ");  <-- (";
	if (generation > 0 || FIGURE_DEBUG)
		for (lst::const_iterator it = parents.begin(); it != parents.end();) {
			if (is_a<cycle_relation>(*it))
				ex_to<cycle_relation>(*it).do_print(con,level);
			else if (is_a<subfigure>(*it))
				ex_to<subfigure>(*it).do_print(con,level);
			++it;
			if (it != parents.end())
				con.s <<",";
		}
	con.s << ")";

#line 4929 "figure.nw"
	if (custom_asy != "")
		con.s<< " /" << custom_asy << "/";
	con.s << endl;

#line 4883 "figure.nw"
}

#line 4887 "figure.nw"
void cycle_node::do_print_double(const print_dflt & con, unsigned level) const
{
	
#line 4896 "figure.nw"
	con.s << '{';
	for (const auto& it : cycles) {

#line 4890 "figure.nw"
		ex_to<cycle_data>(it).do_print_double(con, level);
		
#line 4901 "figure.nw"
		con.s << ", ";
	}
	con.s << generation << '}' << " --> (";
	// list all children
	for (lst::const_iterator it = children.begin(); it != children.end();) {
		con.s << (*it);
		++it;
		if (it != children.end())
			con.s <<",";
	}

#line 4914 "figure.nw"
	con.s << ");  <-- (";
	if (generation > 0 || FIGURE_DEBUG)
		for (lst::const_iterator it = parents.begin(); it != parents.end();) {
			if (is_a<cycle_relation>(*it))
				ex_to<cycle_relation>(*it).do_print(con,level);
			else if (is_a<subfigure>(*it))
				ex_to<subfigure>(*it).do_print(con,level);
			++it;
			if (it != parents.end())
				con.s <<",";
		}
	con.s << ")";

#line 4929 "figure.nw"
	if (custom_asy != "")
		con.s<< " /" << custom_asy << "/";
	con.s << endl;

#line 4892 "figure.nw"
}

#line 4935 "figure.nw"
void cycle_node::do_print_tree(const print_tree & con, unsigned level) const
{
	for (const auto& it : cycles)
		it.print(con, level);
	con.s << std::string(level+con.delta_indent, ' ') << "generation: "<< generation << endl;
	con.s << std::string(level+con.delta_indent, ' ') << "children" <<endl;
	children.print(con,level+2*con.delta_indent);
	con.s << std::string(level+con.delta_indent, ' ') << "parents" <<endl;
	parents.print(con,level+2*con.delta_indent);
	con.s << std::string(level+con.delta_indent, ' ') << "custom_asy: " << custom_asy <<endl;
}

#line 4949 "figure.nw"
void cycle_node::remove_child(const ex & other)
{
	lst nchildren;
	for (const auto& it : children)
	    if (it != other)
			nchildren.append(it);
	children=nchildren;
}

#line 4960 "figure.nw"
cycle_node cycle_node::subs(const ex & e, unsigned options) const
{
	exmap em;
	if (e.info(info_flags::list)) {
		lst l = ex_to<lst>(e);
		for (const auto& i : l)
			em.insert(std::make_pair(i.op(0), i.op(1)));
	} else if (is_a<relational>(e)) {
		em.insert(std::make_pair(e.op(0), e.op(1)));
	} else
		throw(std::invalid_argument("cycle::subs(): the parameter should be a relational or a lst"));

	return ex_to<cycle_node>(subs(em, options));
}

#line 4977 "figure.nw"
ex cycle_node::subs(const exmap & em, unsigned options) const
{
	return cycle_node(cycles.subs(em, options), generation, ex_to<lst>(parents.subs(em, options)), children, custom_asy);
}

#line 4984 "figure.nw"
void cycle_node::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("cycles", cycles);
	n.add_unsigned("children_size", children.nops());
	if (children.nops()>0)
		for (const auto& it : children)
			n.add_ex("chil", it);

	n.add_unsigned("parent_size", parents.nops());
	if (parents.nops()>0) {
		n.add_bool("has_subfigure", false);
		for (const auto& it : parents)
			n.add_ex("par", ex_to<cycle_relation>(it));
	}

#line 5002 "figure.nw"
	bool neg_generation=(generation<0);
	n.add_bool("neg_generation", neg_generation);
	if (neg_generation)
		n.add_unsigned("abs_generation", -generation);
	else
		n.add_unsigned("abs_generation", generation);

#line 5011 "figure.nw"
	n.add_string("custom_asy", custom_asy);
}

#line 5016 "figure.nw"
void cycle_node::read_archive(const archive_node &n, lst &sym_lst)
{
	inherited::read_archive(n, sym_lst);
	ex e;
	n.find_ex("cycles", e, sym_lst);
	cycles=ex_to<lst>(e);
	ex ch, par;
	unsigned int c_size;
	n.find_unsigned("children_size", c_size);

	if (c_size>0) {
		archive_node::archive_node_cit first = n.find_first("chil");
		archive_node::archive_node_cit last = n.find_last("chil");
		++last;
		for (archive_node::archive_node_cit i=first; i != last; ++i) {
			ex e;
			n.find_ex_by_loc(i, e, sym_lst);
			children.append(e);
		}
	}

	unsigned int p_size;
	n.find_unsigned("parent_size", p_size);

	if (p_size>0) {
		archive_node::archive_node_cit first = n.find_first("par");
		archive_node::archive_node_cit last = n.find_last("par");
		++last;
		for (archive_node::archive_node_cit i=first; i != last; ++i) {
			ex e;
			n.find_ex_by_loc(i, e, sym_lst);
			parents.append(e);
		}
	}

#line 5053 "figure.nw"
	bool neg_generation;
	n.find_bool("neg_generation", neg_generation);
	unsigned int abs_generation;
	n.find_unsigned("abs_generation", abs_generation);
	if (neg_generation)
		generation = -abs_generation;
	else
		generation = abs_generation;

#line 5064 "figure.nw"
	n.find_string("custom_asy", custom_asy);
}

#line 5069 "figure.nw"
GINAC_BIND_UNARCHIVER(cycle_node);

#line 5085 "figure.nw"
figure::figure() : inherited(), k(realsymbol("k")), m(realsymbol("m")), l()
{
	l.append(realsymbol("l0"));
	l.append(realsymbol("l1"));
	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	point_metric = clifford_unit(varidx(real_line, 2), indexed(-(new tensdelta)->setflag(status_flags::dynallocated),
															   sy_symm(), varidx(symbol("i"), 2), varidx(symbol("j"), 2)));
	cycle_metric = clifford_unit(varidx(real_line, 2), indexed(-(new tensdelta)->setflag(status_flags::dynallocated),
															   sy_symm(), varidx(symbol("ic"), 2), varidx(symbol("jc"), 2)));
	
#line 5109 "figure.nw"
   
#line 5102 "figure.nw"
   unsigned int dim=ex_to<numeric>(get_dim()).to_int();
   lst l0;
   for(unsigned int i=0; i<dim; ++i)
	   l0.append(0);

#line 5110 "figure.nw"
   nodes[infinity] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
															  varidx(infinity, dim)),numeric(1)),INFINITY_GEN);

#line 5096 "figure.nw"
	
#line 5115 "figure.nw"
	l0.remove_last();
	l0.append(1);
	nodes[real_line] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
																	varidx(real_line, dim)),numeric(0)),REAL_LINE_GEN);

#line 5097 "figure.nw"
}
#line 5122 "figure.nw"
figure::figure(const ex & Mp, const ex & Mc) : inherited(), k(realsymbol("k")), m(realsymbol("m")), l()
{
	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	bool inf_missing=true, R_missing=true;
	
#line 5134 "figure.nw"
if (is_a<clifford>(Mp)) {
	point_metric = clifford_unit(varidx(real_line,
										ex_to<idx>(ex_to<clifford>(Mp).get_metric().op(1)).get_dim()),
								 ex_to<clifford>(Mp).get_metric());
 } else if (is_a<matrix>(Mp)) {
	ex D;
	if (ex_to<matrix>(Mp).rows() == ex_to<matrix>(Mp).cols())
		D=ex_to<matrix>(Mp).rows();
	else
		throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
									" only square matrices are admitted as point metric"));
	point_metric = clifford_unit(varidx(real_line, D), indexed(Mp, sy_symm(), varidx(symbol("i"), D), varidx(symbol("j"), D)));
 } else if (is_a<indexed>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, ex_to<idx>(Mp.op(1)).get_dim()), Mp);

#line 5152 "figure.nw"
	} else if (is_a<lst>(Mp)) {
		point_metric=clifford_unit(varidx(real_line, Mp.nops()), indexed(diag_matrix(ex_to<lst>(Mp)), sy_symm(),
																		 varidx(symbol("i"), Mp.nops()), varidx(symbol("j"), Mp.nops())));
	}


#line 5159 "figure.nw"
	else if (is_a<figure>(Mp)) {
		point_metric = ex_to<figure>(Mp).get_point_metric();
		cycle_metric = ex_to<figure>(Mp).get_cycle_metric();
		exhashmap<cycle_node> nnodes = ex_to<figure>(Mp).get_nodes();
		for (const auto& x: nnodes) {
			nodes[x.first]=x.second;
			
#line 5170 "figure.nw"
			if (x.second.get_generation() == REAL_LINE_GEN) {
				real_line = x.first;
				R_missing=false;
			}
			else if (x.second.get_generation() == INFINITY_GEN) {
				infinity = x.first;
				inf_missing=false;
			}

#line 5166 "figure.nw"
			}

#line 5181 "figure.nw"
	} else
			throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
										" the first parameter shall be a figure, a lst, "
										" a metric (can be either tensor, matrix,"
										" Clifford unit or indexed by two indices) "));
	
#line 5196 "figure.nw"
	if (Mc.is_zero()) {
		ex D=get_dim();
		if (is_a<numeric>(D)) {
			lst l0;
			for(int i=0; i< ex_to<numeric>(D).to_int(); ++i)
				l0.append(-jump_fnct(-ex_to<clifford>(point_metric).get_metric(idx(i,D),idx(i,D))));
			cycle_metric = clifford_unit(varidx(infinity, D), indexed(diag_matrix(l0), sy_symm(),
																	   varidx(symbol("ic"), D), varidx(symbol("jc"), D)));

#line 5207 "figure.nw"
		} else
			cycle_metric = clifford_unit(varidx(infinity, D), indexed(point_metric.op(0), sy_symm(),
																	   varidx(symbol("ic"), D), varidx(symbol("jc"), D)));

#line 5214 "figure.nw"
	} else if (is_a<clifford>(Mc)) {
		cycle_metric = clifford_unit(varidx(infinity,
											ex_to<idx>(ex_to<clifford>(Mc).get_metric().op(1)).get_dim()),
									 ex_to<clifford>(Mc).get_metric());
	} else if (is_a<matrix>(Mc)) {
		if (ex_to<matrix>(Mp).rows() != ex_to<matrix>(Mp).cols())
			throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
										" only square matrices are admitted as cycle metric"));

		cycle_metric = clifford_unit(varidx(infinity, get_dim()), indexed(Mc, sy_symm(), varidx(symbol("ic"),
																								 get_dim()), varidx(symbol("jc"), get_dim())));

#line 5228 "figure.nw"
	} else if (is_a<indexed>(Mc)) {
		cycle_metric = clifford_unit(varidx(infinity, ex_to<idx>(Mc.op(1)).get_dim()), Mc);
	} else if (is_a<lst>(Mc)) {
		cycle_metric=clifford_unit(varidx(infinity, Mc.nops()), indexed(diag_matrix(ex_to<lst>(Mc)), sy_symm(),
							varidx(symbol("ic"), Mc.nops()), varidx(symbol("jc"), Mc.nops())));
	}


#line 5237 "figure.nw"
	else
		throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
									" the second parameter"
									" shall be omitted, equal to zero "
									" or be a lst, a metric (can be either tensor, matrix,"
									" Clifford unit or indexed by two indices)"));

#line 5246 "figure.nw"
	if (! (get_dim()-ex_to<idx>(cycle_metric.op(1)).get_dim()).is_zero())
		throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
									"the point and cycle metrics shall have "
									"the same dimensions"));

#line 5254 "figure.nw"
	
#line 5259 "figure.nw"
	if (!(get_dim()-ex_to<varidx>(cycle_metric.op(1)).get_dim()).is_zero())
		throw(std::invalid_argument("Metrics for point and cycle spaces have"
									" different dimensionalities!"));

#line 5255 "figure.nw"
	
#line 5265 "figure.nw"
	int D;
	if (is_a<numeric>(get_dim())) {
		D=ex_to<numeric>(get_dim()).to_int();
		char name[6];
		for(int i=0; i<D; ++i) {
			sprintf(name, "l%d", i);
			l.append(realsymbol(name));
		}
	}


#line 5278 "figure.nw"
	
#line 5283 "figure.nw"
	if (inf_missing) {
		
#line 5109 "figure.nw"
   
#line 5102 "figure.nw"
   unsigned int dim=ex_to<numeric>(get_dim()).to_int();
   lst l0;
   for(unsigned int i=0; i<dim; ++i)
	   l0.append(0);

#line 5110 "figure.nw"
   nodes[infinity] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
															  varidx(infinity, dim)),numeric(1)),INFINITY_GEN);

#line 5285 "figure.nw"
	}
	if (R_missing) {
		
#line 5102 "figure.nw"
   unsigned int dim=ex_to<numeric>(get_dim()).to_int();
   lst l0;
   for(unsigned int i=0; i<dim; ++i)
	   l0.append(0);

#line 5288 "figure.nw"
		
#line 5115 "figure.nw"
	l0.remove_last();
	l0.append(1);
	nodes[real_line] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
																	varidx(real_line, dim)),numeric(0)),REAL_LINE_GEN);

#line 5289 "figure.nw"
	}

#line 5279 "figure.nw"
}

#line 5293 "figure.nw"
figure::figure(const ex & Mp, const ex & Mc, const exhashmap<cycle_node> & N):
			  inherited(), k(realsymbol("k")), m(realsymbol("m")), l()
{
	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	bool inf_missing=true, R_missing=true;
	if (is_a<clifford>(Mp) && is_a<clifford>(Mc)) {
		point_metric = Mp;
		cycle_metric = Mc;
	} else
		throw(std::invalid_argument("figure::figure(const ex &, const ex &, exhashmap<cycle_node>):"
									" the point_metric and cycle_metric should be clifford_unit. "));

#line 5308 "figure.nw"
	for (const auto& x: N) {
		nodes[x.first]=x.second;
		
#line 5170 "figure.nw"
			if (x.second.get_generation() == REAL_LINE_GEN) {
				real_line = x.first;
				R_missing=false;
			}
			else if (x.second.get_generation() == INFINITY_GEN) {
				infinity = x.first;
				inf_missing=false;
			}

#line 5311 "figure.nw"
	}
	
#line 5265 "figure.nw"
	int D;
	if (is_a<numeric>(get_dim())) {
		D=ex_to<numeric>(get_dim()).to_int();
		char name[6];
		for(int i=0; i<D; ++i) {
			sprintf(name, "l%d", i);
			l.append(realsymbol(name));
		}
	}

#line 5313 "figure.nw"
	
#line 5283 "figure.nw"
	if (inf_missing) {
		
#line 5109 "figure.nw"
   
#line 5102 "figure.nw"
   unsigned int dim=ex_to<numeric>(get_dim()).to_int();
   lst l0;
   for(unsigned int i=0; i<dim; ++i)
	   l0.append(0);

#line 5110 "figure.nw"
   nodes[infinity] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
															  varidx(infinity, dim)),numeric(1)),INFINITY_GEN);

#line 5285 "figure.nw"
	}
	if (R_missing) {
		
#line 5102 "figure.nw"
   unsigned int dim=ex_to<numeric>(get_dim()).to_int();
   lst l0;
   for(unsigned int i=0; i<dim; ++i)
	   l0.append(0);

#line 5288 "figure.nw"
		
#line 5115 "figure.nw"
	l0.remove_last();
	l0.append(1);
	nodes[real_line] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
																	varidx(real_line, dim)),numeric(0)),REAL_LINE_GEN);

#line 5289 "figure.nw"
	}

#line 5314 "figure.nw"
}

#line 5318 "figure.nw"
figure::figure(const char* file_name, string fig_name) : inherited(), k(realsymbol("k")), m(realsymbol("m")), l()
{
	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	
#line 5348 "figure.nw"
	string fn=file_name;
	size_t found = fn.find(".gar");
	if (found == std::string::npos)
		fn=fn+".gar";

	if (FIGURE_DEBUG)
		cerr << "use filename: " << fn << endl;

#line 5323 "figure.nw"
	GiNaC::archive A;
	std::ifstream ifs(fn.c_str(),  std::ifstream::in);

	ifs >> A;
	*this=ex_to<figure>(A.unarchive_ex(lst{infinity, real_line}, fig_name));
	string operation_name="read";
	
#line 5334 "figure.nw"
#if __cplusplus >= 201703L
	if (FIGURE_DEBUG) {
		std::filesystem::path file_path=std::filesystem::path(fn.c_str()),
			file_name=std::filesystem::path("raw-"+operation_name+"-");
		file_name+=file_path.filename();
		ofstream out1(file_path.replace_filename(file_name));
		A.printraw(out1);
		out1.close();
		out1.flush();
	}
#endif

#line 5330 "figure.nw"
}

#line 5359 "figure.nw"
void figure::save(const char* file_name, const char * fig_name) const
{
	
#line 5348 "figure.nw"
	string fn=file_name;
	size_t found = fn.find(".gar");
	if (found == std::string::npos)
		fn=fn+".gar";

	if (FIGURE_DEBUG)
		cerr << "use filename: " << fn << endl;

#line 5362 "figure.nw"
	GiNaC::archive A;
	A.archive_ex(*this, fig_name);
	ofstream out(fn.c_str());
	out << A;
	out.flush();
	out.close();
	string operation_name="save";
	
#line 5334 "figure.nw"
#if __cplusplus >= 201703L
	if (FIGURE_DEBUG) {
		std::filesystem::path file_path=std::filesystem::path(fn.c_str()),
			file_name=std::filesystem::path("raw-"+operation_name+"-");
		file_name+=file_path.filename();
		ofstream out1(file_path.replace_filename(file_name));
		A.printraw(out1);
		out1.close();
		out1.flush();
	}
#endif

#line 5370 "figure.nw"
}

#line 5378 "figure.nw"
ex figure::add_point(const ex & x, string name, string TeXname)
{
	
#line 5614 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 5381 "figure.nw"
	symbol key(name, TeXname_new);
	return add_point(x, key);
}
#line 5388 "figure.nw"
ex figure::add_point(const ex & x, const ex & key)
{
	if (not (is_a<lst>(x) and (x.nops() == get_dim())))
		throw(std::invalid_argument("figure::add_point(const ex &, const ex &): "
									"coordinates of a point shall be a lst of the right lenght"));

	if (not is_a<symbol>(key))
		throw(std::invalid_argument("figure::add_point(const ex &, const ex &): the third"
									" argument need to be a point"));
#line 5405 "figure.nw"
	int dim=x.nops();
	lst l0, rels;
	rels.append(cycle_relation(key,cycle_orthogonal,false));
	rels.append(cycle_relation(infinity,cycle_different));

	for(int i=0; i < dim; ++i)
		l0.append(numeric(0));

	for(int i=0; i < dim; ++i) {
		l0[i]=numeric(1);
		char name[8];
		sprintf(name, "-(%d)", i);
		symbol mother(ex_to<symbol>(key).get_name()+name);
		nodes[mother]=cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
															   varidx(mother, get_dim())),numeric(2)*x.op(i)),
								 GHOST_GEN, lst{}, lst{key});
		l0[i]=numeric(0);
		rels.append(cycle_relation(mother,cycle_orthogonal));
	}

#line 5430 "figure.nw"
	nodes[key]=cycle_node(cycle_data(), 0, rels);

#line 5434 "figure.nw"
	if (! info(status_flags::expanded))
		nodes[key].set_cycles(ex_to<lst>(update_cycle_node(key)));
	if (FIGURE_DEBUG)
		cerr << "Add the point: " << x << " as the cycle: " << nodes[key] << endl;
	return key;
}

#line 5443 "figure.nw"
ex figure::add_cycle(const ex & C, const ex & key)
{
	ex lC=ex_to<cycle>(C).get_l();
	if (is_a<indexed>(lC))
		nodes[key]=cycle_node(C.subs(lC.op(1)==key));
	else
		nodes[key]=cycle_node(C);
	if (FIGURE_DEBUG)
		cerr << "Add the cycle: " << nodes[key] << endl;
	return key;
}
#line 5458 "figure.nw"
ex figure::add_cycle(const ex & C, string name, string TeXname)
{
	
#line 5614 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 5461 "figure.nw"
	symbol key(name, TeXname_new);
	return add_cycle(C, key);
 }

#line 5467 "figure.nw"
void figure::set_cycle(const ex & key, const ex & C)
{
    if (nodes.find(key) == nodes.end())
        throw(std::invalid_argument("figure::set_cycle(): there is no node wi\
th the key given"));

    if (nodes[key].get_parents().nops() > 0)
        throw(std::invalid_argument("figure::set_cycle(): cannot modify data \
of a cycle with parents"));

    nodes[key].set_cycles(C);

    if (FIGURE_DEBUG)
        cerr << "Replace the cycle: " << nodes[key] << endl;
}
#line 5486 "figure.nw"
void figure::move_cycle(const ex & key, const ex & C)
{
	if (nodes.find(key) == nodes.end())
		throw(std::invalid_argument("figure::set_cycle(): there is no node with the key given"));

	if (nodes[key].get_generation() != 0)
		throw(std::invalid_argument("figure::set_cycle(): cannot modify data of a cycle in"
									" non-zero generation"));
#line 5500 "figure.nw"
	if (nodes[key].get_parents().nops() > 0) {
		lst par=nodes[key].get_parent_keys();
		for(const auto& it : par)
			if (nodes[it].get_generation() == GHOST_GEN)
				nodes.erase(it);
			else
				nodes[it].remove_child(key);
	}
	nodes[key].parents=lst{};

#line 5512 "figure.nw"
	nodes[key].set_cycles(C);
	update_node_lst(nodes[key].get_children());

	if (FIGURE_DEBUG)
		cerr << "Replace the cycle: " << nodes[key] << endl;
}

#line 5523 "figure.nw"
ex figure::add_cycle_rel(const ex & rel, const ex & key) {
	if (is_a<cycle_relation>(rel))
		return add_cycle_rel(lst{rel}, key);
	else
		throw(std::invalid_argument("figure::add_cycle_rel: a cycle shall be added "
									"by a single expression, which is a cycle_relation"));
}
#line 5536 "figure.nw"
ex figure::add_cycle_rel(const lst & rel, const ex & key)
{
	lst cond;
	int gen=0;

	for(const auto& it : rel) {
		if (ex_to<cycle_relation>(it).get_parkey() != key)
			gen=max(gen, nodes[ex_to<cycle_relation>(it).get_parkey()].get_generation());
		nodes[ex_to<cycle_relation>(it).get_parkey()].add_child(key);
	}

	nodes[key]=cycle_node(cycle_data(),gen+1,rel);

#line 5551 "figure.nw"
	if (! info(status_flags::expanded))
		nodes[key].set_cycles(ex_to<lst>(update_cycle_node(key)));

	if (FIGURE_DEBUG)
		cerr << "Add the cycle: " << nodes[key] << endl;

	return key;
}

#line 5563 "figure.nw"
ex figure::add_cycle_rel(const lst & rel, string name, string TeXname)
{
	
#line 5614 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 5566 "figure.nw"
	return add_cycle_rel(rel, symbol(name, TeXname_new));
}

#line 5571 "figure.nw"
ex figure::add_cycle_rel(const ex & rel, string name, string TeXname)
{
	if (is_a<cycle_relation>(rel)) {
		
#line 5614 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 5575 "figure.nw"
		return add_cycle_rel(lst{rel}, symbol(name, TeXname_new));
	} else
		throw(std::invalid_argument("figure::add_cycle_rel: a cycle shall be added "
									"by a single expression, which is a cycle_relation"));
}

#line 5585 "figure.nw"
ex figure::add_subfigure(const ex & F, const lst & L, const ex & key)
{
	GINAC_ASSERT(is_a<figure>(F));
	int gen=0;

	for(const auto& it : L) {
		if (! it.is_equal(key))
			gen=max(gen, nodes[it].get_generation());
		nodes[it].add_child(key);
	}
	nodes[key]=cycle_node(cycle_data(),gen+1,lst{subfigure(F,L)});
	if (! info(status_flags::expanded))
		nodes[key].set_cycles(ex_to<lst>(update_cycle_node(key)));

	return key;
}
#line 5606 "figure.nw"
ex figure::add_subfigure(const ex & F, const lst & l, string name, string TeXname)
{
	
#line 5614 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 5609 "figure.nw"
		return add_subfigure(F, l, symbol(name, TeXname_new));
}

#line 5631 "figure.nw"
void figure::move_point(const ex & key, const ex & x)
{
	if (not (is_a<lst>(x) and (x.nops() == get_dim())))
		throw(std::invalid_argument("figure::move_point(const ex &, const ex &): "
									"coordinates of a point shall be a lst of the right lenght"));

	if (nodes.find(key) == nodes.end())
		throw(std::invalid_argument("figure::move_point(): there is no node with the key given"));

	if (nodes[key].get_generation() != 0)
		throw(std::invalid_argument("figure::move_point(): cannot modify data of a cycle in"
									" non-zero generation"));

	if (FIGURE_DEBUG)
		cerr << "A cycle is moved : " << nodes[key] << endl;
#line 5651 "figure.nw"
	lst par=nodes[key].get_parent_keys();
	unsigned int dim=x.nops();
	lst l0;
	for(unsigned int i=0; i<dim; ++i)
		l0.append(numeric(0));

#line 5660 "figure.nw"
	char label[40];
	sprintf(label, "%s-(%%d)",ex_to<symbol>(key).get_name().c_str());
	if (par.nops() == dim+2 ) {
		for(const auto& it : par) {
			unsigned int i=dim;
			int res=sscanf(ex_to<symbol>(it).get_name().c_str(), label, &i);
			if (res>0 and i<dim) {
				l0[i]=numeric(1);
				nodes[it].set_cycles(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
																	varidx(it, dim)), numeric(2)*x.op(i)));
				l0[i]=numeric(0);
			}
		}

#line 5677 "figure.nw"
	} else if  (par.nops() == 0) {
		lst chil=nodes[key].get_children();
		
#line 5405 "figure.nw"
	int dim=x.nops();
	lst l0, rels;
	rels.append(cycle_relation(key,cycle_orthogonal,false));
	rels.append(cycle_relation(infinity,cycle_different));

	for(int i=0; i < dim; ++i)
		l0.append(numeric(0));

	for(int i=0; i < dim; ++i) {
		l0[i]=numeric(1);
		char name[8];
		sprintf(name, "-(%d)", i);
		symbol mother(ex_to<symbol>(key).get_name()+name);
		nodes[mother]=cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
															   varidx(mother, get_dim())),numeric(2)*x.op(i)),
								 GHOST_GEN, lst{}, lst{key});
		l0[i]=numeric(0);
		rels.append(cycle_relation(mother,cycle_orthogonal));
	}

#line 5430 "figure.nw"
	nodes[key]=cycle_node(cycle_data(), 0, rels);

#line 5680 "figure.nw"
		nodes[key].children=chil;
	} else
		throw(std::invalid_argument("figure::move_point(): strange number (neither 0 nor dim+2) of "
									"parents, which zero-generation node shall have!"));

	if (info(status_flags::expanded))
		return;

	nodes[key].set_cycles(ex_to<lst>(update_cycle_node(key)));
	update_node_lst(nodes[key].get_children());

#line 5694 "figure.nw"
	 update_node_lst(nodes[key].get_children());
	 if (FIGURE_DEBUG)
		cerr << "Moved to: " << x << endl;
}

#line 5702 "figure.nw"
void figure::remove_cycle_node(const ex & key)
{
	lst  branches=nodes[key].get_children();
	for (const auto& it : branches)
		remove_cycle_node(it);
#line 5711 "figure.nw"
	lst  par = nodes[key].get_parent_keys();
	for (const auto& it : par) {

#line 5718 "figure.nw"
		if (nodes[it].get_generation() == GHOST_GEN)
			nodes.erase(it);
		else
			nodes[it].remove_child(key);
	}

#line 5726 "figure.nw"
	nodes.erase(key);
	if (FIGURE_DEBUG)
		cerr << "The cycle is removed: " << key << endl ;
}

#line 5743 "figure.nw"
ex figure::evaluate_cycle(const ex & symbolic, const lst & cond) const
{
	//cerr << boolalpha << "symbolic: "; symbolic.dbgprint();
	//cerr << "condit: "; cond.dbgprint();
	bool first_solution=true, // whetehr the first solution is suitable
		second_solution=false, // whetehr the second solution is suitable
		is_homogeneous=true; // indicates whether all conditions are linear
#line 5754 "figure.nw"
	int D;
	if (is_a<numeric>(get_dim()))
		D=ex_to<numeric>(get_dim()).to_int();
	else
		throw logic_error("Could not resolve cycle relations if dimensionality is not numeric!");

#line 5762 "figure.nw"
	lst symbols, lin_cond, nonlin_cond;
	if (is_a<symbol>(ex_to<cycle_data>(symbolic).get_m()))
		symbols.append(ex_to<cycle_data>(symbolic).get_m());
	for (int i = 0; i < D; i++)
		if (is_a<symbol>(ex_to<cycle_data>(symbolic).get_l(i)))
			symbols.append(ex_to<cycle_data>(symbolic).get_l(i));
	if (is_a<symbol>(ex_to<cycle_data>(symbolic).get_k()))
		symbols.append(ex_to<cycle_data>(symbolic).get_k());

#line 5773 "figure.nw"
	if (symbols.nops() == 0)
		throw(std::invalid_argument("figure::evaluate_cycle(): could not construct the default list of "
								 "parameters"));
	//cerr << "symbols: "; symbols.dbgprint();

#line 5781 "figure.nw"
	lst rhs;
	for (size_t r=0; r<cond.nops(); r++) {
		lst sys;
		ex eq = (cond.op(r).op(0)-cond.op(r).op(1)).expand(); // lhs-rhs==0
		if (float_evaluation)
			eq=eq.evalf();
		//cerr << "eq: "; eq.dbgprint();
		ex linpart = eq;
		for (size_t c=0; c<symbols.nops(); c++) {
			const ex co = eq.coeff(ex_to<symbol>(symbols.op(c)),1);
			linpart -= co*symbols.op(c);
			sys.append(co);
		}
		linpart = linpart.expand();
		//cerr << "sys: "; sys.dbgprint();
		//cerr << "linpart: "; linpart.dbgprint();

#line 5800 "figure.nw"
		bool is_linear=true;
		for (size_t i=0; i<symbols.nops(); i++)
			if (sys.has(symbols.op(i)) || linpart.has(symbols.op(i)))
				is_linear = false;
		//cerr << "this equation linear? " << is_linear << endl;

#line 5809 "figure.nw"
		if (is_linear) {
			lin_cond.append(sys);
			rhs.append(linpart);
			is_homogeneous &= linpart.normal().is_zero();
		} else
			nonlin_cond.append(cond.op(r));
	}
	//cerr << "lin_cond: "; lin_cond.dbgprint();
	//cerr << "nonlin_cond: "; nonlin_cond.dbgprint();


#line 5822 "figure.nw"
	lst subs_lst1, // The main list of substitutions of found solutions
		subs_lst2, // The second solution lists for quadratic equations
		free_vars; // List of free variables being parameters of the solution
 	if (lin_cond.nops()>0) {
		matrix solution;
		try {
			solution=ex_to<matrix>(lst_to_matrix(lin_cond)).solve(matrix(symbols.nops(),1,symbols),
																  matrix(rhs.nops(),1,rhs));

#line 5834 "figure.nw"
        } catch (const std::runtime_error & e) {
			return lst{};
        }
        GINAC_ASSERT(solution.cols()==1);
        GINAC_ASSERT(solution.rows()==symbols.nops());

#line 5843 "figure.nw"
        for (size_t i=0; i<symbols.nops(); i++)
			if (symbols.op(i)==solution(i,0))
				free_vars.append(symbols.op(i));
			else
				subs_lst1.append(symbols.op(i)==solution(i,0));
	}
	//cerr << "Lin system is homogeneous: " << is_homogeneous << endl;

#line 5854 "figure.nw"
	cycle_data C_new, C1_new;
	if (nonlin_cond.nops() == 0) {
		C_new = ex_to<cycle_data>(symbolic.subs(subs_lst1)).normalize();
		//cerr << "C_new: "; C_new.dbgprint();

#line 5863 "figure.nw"
	ex norm=pow(ex_to<cycle_data>(symbolic).get_k(),2)+pow(ex_to<cycle_data>(symbolic).get_m(),2);
	for (int i = 0; i < D; i++)
		norm+=pow(ex_to<cycle_data>(symbolic).get_l(i),2);
	first_solution &= ! is_less_than_epsilon(norm.subs(subs_lst1,
													   subs_options::algebraic | subs_options::no_pattern));

#line 5872 "figure.nw"
	} else if (free_vars.nops() > 0) {
		lst nonlin_cond_new;
		//cerr << "free_vars: "; free_vars.dbgprint();
		//cerr << "subs_lst1: "; subs_lst1.dbgprint();

#line 5880 "figure.nw"
		ex quadratic_eq=nonlin_cond.op(0).subs(subs_lst1, subs_options::algebraic
											   | subs_options::no_pattern);
		ex quadratic=(quadratic_eq.op(0)-quadratic_eq.op(1)).expand().normal()
			.subs(evaluation_assist,subs_options::algebraic).normal();
		if (float_evaluation)
			quadratic=quadratic.evalf();
		//cerr << "quadratic: "; quadratic.dbgprint();

#line 5890 "figure.nw"
		lst quadratic_list;
		for (size_t i=0; i < free_vars.nops(); ++i)
			if (quadratic.has(free_vars.op(i)))
				quadratic_list.append(free_vars.op(i));
		free_vars=ex_to<lst>(quadratic_list);
		//cerr << "free_vars which are present: "; free_vars.dbgprint();

#line 5899 "figure.nw"
		if (is_homogeneous) {
			ex Q=quadratic;
			for (size_t i=1; i < free_vars.nops(); ++i)
				Q=Q.subs(free_vars.op(i)==free_vars.op(0));
			is_homogeneous &= (Q.degree(free_vars.op(0))==Q.ldegree(free_vars.op(0)));
		}
		//cerr << "Quadratic part is homogeneous: " << is_homogeneous << endl;

#line 5910 "figure.nw"
		bool is_quadratic=true;
		exmap flat_var_em, var1_em, var2_em;
		ex flat_var, var1, var2;

#line 5916 "figure.nw"
		size_t i=0;
		for (; i < free_vars.nops(); ++i) {
			//cerr << "degree: " << quadratic.degree(free_vars.op(i)) << endl;
			if (quadratic.degree(free_vars.op(i)) < 2) {
				is_quadratic=false;
				//cerr << "Equation is linear in "; free_vars.op(i).dbgprint();
				break;
			}
		}

#line 5929 "figure.nw"
		if (is_quadratic) {
			if (is_homogeneous && free_vars.nops() > 1) {
				exmap erase_var;
				erase_var.insert(std::make_pair(free_vars.op(free_vars.nops()-1), numeric(1)));
				subs_lst1=ex_to<lst>(subs_lst1.subs(erase_var,
													subs_options::algebraic | subs_options::no_pattern));
				subs_lst1.append(free_vars.op(free_vars.nops()-1) == numeric(1));
				quadratic=quadratic.subs(free_vars.op(free_vars.nops()-1) == numeric(1));
				free_vars.remove_last();
				//cerr << "Quadratic reduced by homogenuity: "; quadratic.dbgprint();
			}

#line 5944 "figure.nw"
			ex A, B, C, D, sqrtD;
			for(i=0; i < free_vars.nops(); ++i) {
				A=quadratic.coeff(free_vars.op(i),2).normal();
				//cerr << "A: "; A.dbgprint();
				B=quadratic.coeff(free_vars.op(i),1);
				C=quadratic.coeff(free_vars.op(i),0);
				D=(pow(B,2)-numeric(4)*A*C).normal();
				sqrtD=sqrt(D);
				//cerr << "D: "; D.dbgprint();

#line 5959 "figure.nw"
				if (//need_reals &&
					free_vars.nops()>1) {
					int another=0;
					if (i==0)
						another=1;

#line 5969 "figure.nw"
					if (not is_less_than_epsilon(D) && D.has(free_vars.op(another))) {
						ex A1=D.coeff(free_vars.op(another),2)
						.subs(evaluation_assist,subs_options::algebraic).normal(),
						B1=D.coeff(free_vars.op(another),1)
						.subs(evaluation_assist,subs_options::algebraic).normal(),
						C1=D.coeff(free_vars.op(another),0)
						.subs(evaluation_assist,subs_options::algebraic).normal(),
						D1=(pow(B1,2)-4*A1*C1).normal();
						//cerr << "Atempt to resolve square root for A1=" << A1;
						//cerr << ", B1=" << B1 << ", C1=" << C1 << ", D1=" << D1 << endl;

#line 5983 "figure.nw"
						if (is_less_than_epsilon(A1) && not is_less_than_epsilon(B1)) {
							ex y=realsymbol(),
							x=(pow(y,2)-C1)/B1;
							sqrtD=y;
							flat_var_em.insert(std::make_pair(free_vars.op(another), x));
							flat_var=(free_vars.op(another)==x);

#line 5993 "figure.nw"
						} else if (A1.evalf().info(info_flags::positive)) {

#line 5998 "figure.nw"
							if (D1.info(info_flags::negative)) {
								ex y=realsymbol(),
								x=(sinh(y)*sqrt(-D1)-B1)/2/A1;
								sqrtD=sqrt(C1-pow(B1,2)/4/A1)*cosh(y);
								flat_var_em.insert(std::make_pair(free_vars.op(another), x));
								flat_var=(free_vars.op(another)==x);
							} else if (D1.info(info_flags::positive)) {
								ex y=realsymbol(),
								x=(cosh(y)*sqrt(D1)-B1)/2/A1;
								sqrtD=sqrt(pow(B1,2)/4/A1-C1)*sinh(y);
								flat_var_em.insert(std::make_pair(free_vars.op(another), x));
								flat_var=(free_vars.op(another)==x);
							}

#line 6015 "figure.nw"
						} else if (A1.evalf().info(info_flags::negative)) {
							if (D1.info(info_flags::negative)) {
								ex y=realsymbol(),
								x=(sin(y)*sqrt(-D1)-B1)/2/A1;
								sqrtD=sqrt(-C1+pow(B1,2)/4/A1)*cos(y);
								flat_var_em.insert(std::make_pair(free_vars.op(another), x));
								flat_var=(free_vars.op(another)==x);

#line 6026 "figure.nw"
							} else if (D1.info(info_flags::positive)) {
								ex y=realsymbol(),
								x=(sinh(y)*I*sqrt(D1)-B1)/2/A1;
								sqrtD=I*sqrt(C1-pow(B1,2)/4/A1)*cosh(y);
								flat_var_em.insert(std::make_pair(free_vars.op(another), x));
								flat_var=(free_vars.op(another)==x);
							}
						}

#line 6037 "figure.nw"
					//cerr << "real_only sqrt(D): "; sqrtD.dbgprint();
					if (not (sqrtD-sqrt(D)).is_zero())
						break;
				}
			}
		}

#line 6046 "figure.nw"
		if (i == free_vars.nops())
			--i;

#line 6053 "figure.nw"
			if (is_less_than_epsilon(D) || ((! is_less_than_epsilon(B)) && is_less_than_epsilon(A/B))) {
				if (is_less_than_epsilon(D)) {
					//cerr << "zero determinant" << endl;
					var1=(-B/numeric(2)/A).subs(flat_var_em,subs_options::algebraic
												| subs_options::no_pattern).normal();
				} else {
					//cerr << "almost linear equation" << endl;
					var1=(-C/B).subs(flat_var_em,subs_options::algebraic
									 | subs_options::no_pattern).normal();
				}
				var1_em.insert(std::make_pair(free_vars.op(i), var1));
				subs_lst1=ex_to<lst>(subs_lst1
									 .subs(var1_em,subs_options::algebraic | subs_options::no_pattern));
				subs_lst1=ex_to<lst>(subs_lst1.append(free_vars.op(i) == var1)
									 .subs(flat_var_em,subs_options::algebraic | subs_options::no_pattern));
				if (flat_var.nops()>0)
					subs_lst1.append(flat_var);
				//cerr << "subs_lst1a: "; subs_lst1.dbgprint();

#line 6075 "figure.nw"
			} else {
				second_solution=true;
				subs_lst2=subs_lst1;
				var1=((-B+sqrtD)/numeric(2)/A).subs(flat_var_em,subs_options::algebraic
													| subs_options::no_pattern).normal();
				var1_em.insert(std::make_pair(free_vars.op(i), var1));
				var2=((-B-sqrtD)/numeric(2)/A).subs(flat_var_em,subs_options::algebraic
													| subs_options::no_pattern).normal();
				var2_em.insert(std::make_pair(free_vars.op(i), var2));
				subs_lst1=ex_to<lst>(subs_lst1
									 .subs(var1_em,subs_options::algebraic | subs_options::no_pattern));
				subs_lst1=ex_to<lst>(subs_lst1.append(free_vars.op(i) == var1)
									 .subs(flat_var_em,subs_options::algebraic | subs_options::no_pattern));

#line 6091 "figure.nw"
				subs_lst2=ex_to<lst>(subs_lst2
									 .subs(var2_em,subs_options::algebraic | subs_options::no_pattern));
				subs_lst2=ex_to<lst>(subs_lst2.append(free_vars.op(i) == var2)
									 .subs(flat_var_em,subs_options::algebraic | subs_options::no_pattern));

#line 6099 "figure.nw"
				if (flat_var.nops()>0) {
					subs_lst1.append(flat_var);
					subs_lst2.append(flat_var);
				}
				//cerr << "subs_lst1b: "; subs_lst1.dbgprint();
				//cerr << "subs_lst2b: "; subs_lst2.dbgprint();
			}
			// end of the quadratic case

#line 6111 "figure.nw"
		} else {
			//cerr << "The equation is not quadratic in a single variable"<<endl;
			//cerr << "free_vars: "; free_vars.dbgprint();
			var1=-(quadratic.coeff(free_vars.op(i),0)/quadratic.coeff(free_vars.op(i),1)).normal();
			var1_em.insert(std::make_pair(free_vars.op(i), var1));
			subs_lst1=ex_to<lst>(subs_lst1
								 .subs(var1_em,subs_options::algebraic | subs_options::no_pattern));
			subs_lst1.append(free_vars.op(i) == var1);
			//cerr << "non-quadratic subs_lst1: "; subs_lst1.dbgprint();
		}

#line 6125 "figure.nw"
			lst::const_iterator it1= nonlin_cond.begin();
			++it1;
			//cerr << "Subs list: "; subs_lst1.dbgprint();
			lst subs_f1=ex_to<lst>(subs_lst1.evalf()), subs_f2;
			//cerr << "Subs list float: "; subs_f1.dbgprint();
			if(second_solution)
				subs_f2=ex_to<lst>(subs_lst2.evalf());

#line 6137 "figure.nw"
			for (; it1 != nonlin_cond.end(); ++it1) {
				first_solution &= (is_less_than_epsilon((it1->op(0)-it1->op(1)).subs(subs_f1,
																		   subs_options::algebraic | subs_options::no_pattern))
						 || ((it1->op(0)-it1->op(1)).subs(subs_lst1,
														  subs_options::algebraic | subs_options::no_pattern)).normal().is_zero());

#line 6145 "figure.nw"
				if(second_solution)
					second_solution &= (is_less_than_epsilon((it1->op(0)-it1->op(1)).subs(subs_f2,
																			   subs_options::algebraic | subs_options::no_pattern))
							 || ((it1->op(0)-it1->op(1)).subs(subs_lst2,
															  subs_options::algebraic | subs_options::no_pattern)).normal().is_zero());
			}

#line 6154 "figure.nw"
			if (first_solution)
				C_new=symbolic.subs(subs_lst1, subs_options::algebraic
													| subs_options::no_pattern);

			//cerr << "C_new: "; C_new.dbgprint();
			if (second_solution)
				C1_new=symbolic.subs(subs_lst2, subs_options::algebraic
													 | subs_options::no_pattern);
			//cerr << "C1_new: "; C1_new.dbgprint();
		}

#line 6167 "figure.nw"
	lst repl;
	if (ex_to<cycle_data>(C_new).has(ex_to<cycle_data>(symbolic).get_k()))
		repl.append(ex_to<cycle_data>(symbolic).get_k()==realsymbol());
	if (ex_to<cycle_data>(C_new).has(ex_to<cycle_data>(symbolic).get_m()))
		repl.append(ex_to<cycle_data>(symbolic).get_m()==realsymbol());
	if (ex_to<cycle_data>(C_new).has(ex_to<cycle_data>(symbolic).get_l().op(0).op(0)))
		repl.append(ex_to<cycle_data>(symbolic).get_l().op(0).op(0)==realsymbol());
	if (ex_to<cycle_data>(C_new).has(ex_to<cycle_data>(symbolic).get_l().op(0).op(1)))
		repl.append(ex_to<cycle_data>(symbolic).get_l().op(0).op(1)==realsymbol());

#line 6179 "figure.nw"
	if (repl.nops()>0) {
		if (first_solution)
			C_new=C_new.subs(repl);
		if (second_solution)
			C1_new=C1_new.subs(repl);
	}

	//cerr << endl;

#line 6190 "figure.nw"
	lst res;
	if (first_solution)
		res.append(float_evaluation?C_new.num_normalize().evalf():C_new.num_normalize());
	if (second_solution)
		res.append(float_evaluation?C1_new.num_normalize().evalf():C1_new.num_normalize());

	return res;
}

#line 6204 "figure.nw"
ex figure::update_cycle_node(const ex & key, const lst & eq_cond, const lst & neq_cond, lst res, size_t level)
{
	//cerr << endl << "level: " << level << "; cycle: "; nodes[key].dbgprint();
	if (level == 0) {// set the iniail symbolic cycle for calculations
		
#line 6299 "figure.nw"
	if ( nodes[key].get_parents().nops() == 1 && is_a<subfigure>(nodes[key].get_parents().op(0))) {
		figure F=ex_to<figure>(ex_to<basic>(ex_to<subfigure>(nodes[key].get_parents().op(0)).get_subf())
							   .clearflag(status_flags::expanded));
		F=float_evaluation? F.set_float_eval(): F.set_exact_eval();

#line 6307 "figure.nw"
		lst parkeys=ex_to<lst>(ex_to<subfigure>(nodes[key].get_parents().op(0)).get_parlist());
		unsigned int var=0;
		char name[12];
		for (const auto& it : parkeys) {
			sprintf(name, "variable%03d", var);
			F.set_cycle(F.get_cycle_key(name), nodes[it].get_cycles_data());
			++var;
		}
		F.set_metric(point_metric,cycle_metric); // this calls automatic figure re-calculation
		return F.get_cycles(F.get_cycle_key("result"));

#line 6321 "figure.nw"
	} else
		nodes[key].set_cycles(cycle_data(k, indexed(matrix(1, ex_to<numeric>(get_dim()).to_int(), l), varidx(key, ex_to<numeric>(get_dim()).to_int())), m, false));


#line 6209 "figure.nw"
	}
#line 6215 "figure.nw"
	lst par = nodes[key].get_parents();
	lst::const_iterator it = par.begin();
	std::advance(it,level);

	lst new_cond=ex_to<lst>(ex_to<cycle_relation>(*it).rel_to_parent(nodes[key].get_cycles_data().op(0),
																	 point_metric, cycle_metric, nodes));

#line 6226 "figure.nw"
	for (const auto& it1 : new_cond) {
		lst store_cond=neq_cond;
		lst use_cond=eq_cond;
		lst step_cond=ex_to<lst>(it1);

#line 6233 "figure.nw"
		for (const auto& it2 : step_cond)
			if ((is_a<relational>(it2) && ex_to<relational>(it2).info(info_flags::relation_equal)))
				use_cond.append(it2);	// append the equation
			else if (is_a<cycle>(it2)) { // append a solution
				cycle Cnew=ex_to<cycle>(it2);
				res.append(cycle_data(Cnew.get_k(), Cnew.get_l().subs(Cnew.get_l().op(1)==key),
									  Cnew.get_m()));
			} else
				store_cond.append(*it); // store the pointer to parents producing inequality
		//cerr << "use_cond: "; use_cond.dbgprint();
		//cerr << "store_cond: "; store_cond.dbgprint();

#line 6249 "figure.nw"
		if(level == par.nops()-1) { //if the last one in the parents list
			lst cnew;
			if (use_cond.nops()>0)
				cnew=ex_to<lst>(evaluate_cycle(nodes[key].get_cycle_data(0), use_cond));
			for (const auto& sol : res)
				cnew.append(sol);
			res=lst{};

#line 6260 "figure.nw"
			//cerr<< "Store cond: "; store_cond.dbgprint();
			//cerr<< "Use cond: "; use_cond.dbgprint();
			for (const auto& inew: cnew) {
				bool to_add=true;
				for (const auto& icon: store_cond) {
					lst suits=ex_to<lst>(ex_to<cycle_relation>(icon).rel_to_parent(inew,
																				   point_metric, cycle_metric, nodes));
					//cerr<< "Suit: "; suits.dbgprint();
					for (const auto& is : suits)
						for (const auto& ic : is) {

#line 6274 "figure.nw"
							if  (is_a<relational>(ic)) {
								if (!(bool)ex_to<relational>(ic))
									to_add=false;
							} else if (is_less_than_epsilon(ic))
								to_add=false;
						}
					if (! to_add)
						break;
				}
				if (to_add)
					res.append(inew);
			}
		//cerr<< "Result: "; res.dbgprint();
		} else
			res=ex_to<lst>(update_cycle_node(key, use_cond, store_cond, res, level+1));
	}
	if (level ==0)
		return unique_cycle(res);
	else
		return res;
}

#line 6327 "figure.nw"
figure figure::update_cycles()
{
	if (info(status_flags::expanded))
		return *this;
	lst all_child;
	for (auto& x: nodes)
		if (ex_to<cycle_node>(x.second).get_generation() == 0) {
			if (ex_to<cycle_node>(x.second).get_parents().nops() > 0)
				nodes[x.first].set_cycles(ex_to<lst>(update_cycle_node(x.first)));
#line 6340 "figure.nw"
			lst ch=ex_to<cycle_node>(x.second).get_children();
			for (const auto& it1 : ch)
				all_child.append(it1);
		}
	all_child.sort();
	all_child.unique();
	update_node_lst(all_child);
	return *this;
}

#line 6357 "figure.nw"
void figure::set_metric(const ex & Mp, const ex & Mc)
{
	ex D=get_dim();
	
#line 5134 "figure.nw"
if (is_a<clifford>(Mp)) {
	point_metric = clifford_unit(varidx(real_line,
										ex_to<idx>(ex_to<clifford>(Mp).get_metric().op(1)).get_dim()),
								 ex_to<clifford>(Mp).get_metric());
 } else if (is_a<matrix>(Mp)) {
	ex D;
	if (ex_to<matrix>(Mp).rows() == ex_to<matrix>(Mp).cols())
		D=ex_to<matrix>(Mp).rows();
	else
		throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
									" only square matrices are admitted as point metric"));
	point_metric = clifford_unit(varidx(real_line, D), indexed(Mp, sy_symm(), varidx(symbol("i"), D), varidx(symbol("j"), D)));
 } else if (is_a<indexed>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, ex_to<idx>(Mp.op(1)).get_dim()), Mp);

#line 5152 "figure.nw"
	} else if (is_a<lst>(Mp)) {
		point_metric=clifford_unit(varidx(real_line, Mp.nops()), indexed(diag_matrix(ex_to<lst>(Mp)), sy_symm(),
																		 varidx(symbol("i"), Mp.nops()), varidx(symbol("j"), Mp.nops())));
	}

#line 6361 "figure.nw"
	
#line 5196 "figure.nw"
	if (Mc.is_zero()) {
		ex D=get_dim();
		if (is_a<numeric>(D)) {
			lst l0;
			for(int i=0; i< ex_to<numeric>(D).to_int(); ++i)
				l0.append(-jump_fnct(-ex_to<clifford>(point_metric).get_metric(idx(i,D),idx(i,D))));
			cycle_metric = clifford_unit(varidx(infinity, D), indexed(diag_matrix(l0), sy_symm(),
																	   varidx(symbol("ic"), D), varidx(symbol("jc"), D)));

#line 5207 "figure.nw"
		} else
			cycle_metric = clifford_unit(varidx(infinity, D), indexed(point_metric.op(0), sy_symm(),
																	   varidx(symbol("ic"), D), varidx(symbol("jc"), D)));

#line 5214 "figure.nw"
	} else if (is_a<clifford>(Mc)) {
		cycle_metric = clifford_unit(varidx(infinity,
											ex_to<idx>(ex_to<clifford>(Mc).get_metric().op(1)).get_dim()),
									 ex_to<clifford>(Mc).get_metric());
	} else if (is_a<matrix>(Mc)) {
		if (ex_to<matrix>(Mp).rows() != ex_to<matrix>(Mp).cols())
			throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
										" only square matrices are admitted as cycle metric"));

		cycle_metric = clifford_unit(varidx(infinity, get_dim()), indexed(Mc, sy_symm(), varidx(symbol("ic"),
																								 get_dim()), varidx(symbol("jc"), get_dim())));

#line 5228 "figure.nw"
	} else if (is_a<indexed>(Mc)) {
		cycle_metric = clifford_unit(varidx(infinity, ex_to<idx>(Mc.op(1)).get_dim()), Mc);
	} else if (is_a<lst>(Mc)) {
		cycle_metric=clifford_unit(varidx(infinity, Mc.nops()), indexed(diag_matrix(ex_to<lst>(Mc)), sy_symm(),
							varidx(symbol("ic"), Mc.nops()), varidx(symbol("jc"), Mc.nops())));
	}

#line 6362 "figure.nw"
	
#line 5259 "figure.nw"
	if (!(get_dim()-ex_to<varidx>(cycle_metric.op(1)).get_dim()).is_zero())
		throw(std::invalid_argument("Metrics for point and cycle spaces have"
									" different dimensionalities!"));

#line 6367 "figure.nw"
	if (! (D-get_dim()).is_zero())
		throw(std::invalid_argument("New metric has a different dimensionality!"));
	update_cycles();
}

#line 6375 "figure.nw"
ex figure::get_all_keys(const int mingen, const int maxgen) const {
	lst keys;
	for (const auto& x: nodes) {
		if (x.second.get_generation() >= mingen &&
			(maxgen == GHOST_GEN || x.second.get_generation() <= maxgen))
			keys.append(x.first);
	}
	return keys;
}
#line 6390 "figure.nw"
ex figure::get_all_keys_sorted(const int mingen, const int maxgen) const {
	lst keys;
	int mg=get_max_generation();
	if (maxgen != GHOST_GEN && maxgen < mg)
			mg =maxgen;
	for (int i=mingen; i <= mg; ++i)
		for (const auto& x: nodes) {
			if (x.second.get_generation() == i)
				keys.append(x.first);
	}
	return keys;
}
#line 6406 "figure.nw"
int figure::get_max_generation() const {
	int max_gen = REAL_LINE_GEN;
	for (const auto& x: nodes)
        if (x.second.get_generation() > max_gen)
			max_gen = x.second.get_generation();
	return max_gen;
}
#line 6418 "figure.nw"
ex figure::get_cycles(const ex & key, const ex & metric) const
{
	exhashmap<cycle_node>::const_iterator  cnode=nodes.find(key);
	if (cnode == nodes.end()) {
		if (FIGURE_DEBUG)
			cerr << "There is no key " << key << " in the figure." << endl;
		return lst{};
	} else
		return cnode->second.make_cycles(metric);
}
#line 6432 "figure.nw"
void figure::reset_figure()
{
	nodes.clear();
	
#line 5109 "figure.nw"
   
#line 5102 "figure.nw"
   unsigned int dim=ex_to<numeric>(get_dim()).to_int();
   lst l0;
   for(unsigned int i=0; i<dim; ++i)
	   l0.append(0);

#line 5110 "figure.nw"
   nodes[infinity] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
															  varidx(infinity, dim)),numeric(1)),INFINITY_GEN);

#line 6436 "figure.nw"
	
#line 5115 "figure.nw"
	l0.remove_last();
	l0.append(1);
	nodes[real_line] = cycle_node(cycle_data(numeric(0),indexed(matrix(1, dim, l0),
																	varidx(real_line, dim)),numeric(0)),REAL_LINE_GEN);

#line 6437 "figure.nw"
}
#line 6442 "figure.nw"
void figure::update_node_lst(const ex & inlist)
{
	if (info(status_flags::expanded))
		return;

	lst intake=ex_to<lst>(inlist);
	while (intake.nops() !=0) {
		int mingen=nodes[*intake.begin()].get_generation();
		for (const auto& it : intake)
			mingen=min(mingen, nodes[it].get_generation());
		lst current, future;
		for (const auto& it : intake)
			if (nodes[it].get_generation() == mingen)
				current.append(it);
			else
				future.append(it);
#line 6462 "figure.nw"
	for (const auto& it : current) {
		nodes[it].set_cycles(ex_to<lst>(update_cycle_node(it)));
		lst nchild=nodes[it].get_children();
		for (const auto& it1 : nchild)
			future.append(it1);
	}

#line 6471 "figure.nw"
		intake=future;
		intake.sort();
		intake.unique();
	}
}

#line 6479 "figure.nw"
ex figure::get_cycle_key(string name) const
{
	for (const auto& x: nodes)
		if (ex_to<symbol>(x.first).get_name() == name)
			return x.first;

	return 0;
}
#line 6496 "figure.nw"
void figure::asy_draw(ostream & ost, ostream & err, const string picture,
					  const ex & xmin, const ex & xmax, const ex & ymin, const ex & ymax,
					  asy_style style, label_string lstring, bool with_realline,
					  bool with_header, int points_per_arc, const string imaginary_options,
					  bool with_labels) const
{
	
#line 6507 "figure.nw"
	if (! (get_dim()-2).is_zero())
		throw logic_error("Drawing is possible for two-dimensional figures only!");

#line 6513 "figure.nw"
	stringstream preamble_stream, main_stream, labels_stream;
	string dots;
	std::regex re("dot\\(");

#line 6519 "figure.nw"
        int point_metric_signature=ex_to<numeric>(ex_to<clifford>(point_metric).get_metric(idx(0,2),idx(0,2))
												  *ex_to<clifford>(point_metric).get_metric(idx(1,2),idx(1,2)).eval()).to_int();

	for (const auto& x: nodes) {
		lst cycles=ex_to<lst>(x.second.make_cycles(point_metric));
		bool first_dot=true;

		for (const auto& it1 : cycles)
			try {
				if ( (x.second.get_generation() > REAL_LINE_GEN) ||
					 ((x.second.get_generation() == REAL_LINE_GEN) && with_realline)) {
					stringstream sstr;
					if (with_header)
						sstr << "// label: " << (x.first) << endl;

#line 6536 "figure.nw"
				lst colours=lst{0,0,0};
				string asy_opt;
				if (x.second.custom_asy=="") {
					asy_opt=style(x.first, (it1), colours);
				} else
					asy_opt=x.second.custom_asy;

#line 6546 "figure.nw"
			if (is_less_than_epsilon(ex_to<cycle>(it1).det())) {
				double x1=ex_to<numeric>(ex_to<cycle>(it1).center(cycle_metric).op(0)
										.evalf()).to_double(),
					y1=ex_to<numeric>(ex_to<cycle>(it1).center(cycle_metric).op(1)
										.evalf()).to_double();
				string var_name=regex_replace(ex_to<symbol>(x.first).get_name(), regex("[[:space:]]+"), "_");
				if (first_dot) {
					preamble_stream << "// label: " << (x.first) << endl
									<< "pair[] " << var_name << "={";
					first_dot = false;
				} else
					preamble_stream  << ", ";

				preamble_stream  << "(" << x1 << "," << y1 << ")";

#line 6563 "figure.nw"
				if (point_metric_signature > 0
					&& xmin <= x1 && x1<=xmax && ymin <= y1 && y1<=ymax) {
						sstr << "dot(" << var_name
							 << (asy_opt==""? "": ", ") << asy_opt
							 << ");" << endl;

#line 6571 "figure.nw"
				} else {
					ex_to<cycle2D>(it1).asy_draw(sstr, picture, xmin, xmax,
											 ymin, ymax, colours, asy_opt, with_header, points_per_arc, imaginary_options);

#line 6578 "figure.nw"
					if (FIGURE_DEBUG && point_metric_signature==0
						&& xmin <= x1 && x1<=xmax && ymin <= y1 && y1<=ymax)
						sstr << "dot(" << var_name << ", black+3pt);" << endl;
				}

#line 6585 "figure.nw"
			} else
				ex_to<cycle2D>(it1).asy_draw(sstr, picture, xmin, xmax,
											 ymin, ymax, colours, asy_opt, with_header, points_per_arc, imaginary_options);


#line 6592 "figure.nw"
				if (std::regex_search(sstr.str(), re))
					dots+=sstr.str();
				else
					main_stream << sstr.str();

#line 6599 "figure.nw"
				if (with_labels)
					labels_stream << lstring(x.first, (it1), sstr.str());
				}
			} catch (exception &p) {
				if (FIGURE_DEBUG)
					err << "Failed to draw " << x.first <<": " << x.second;
			}

#line 6609 "figure.nw"
		if (! first_dot)
			preamble_stream << "};" << endl;
	}
	//cerr << "Dots: " << dots;

#line 6617 "figure.nw"
	ost  << "/*" << endl
		<< std::regex_replace(info_text, std::regex("\\*/"), "* /") << endl
		<< "*/" << endl;

#line 6624 "figure.nw"
	if (preamble_stream.str() != "")
		ost << "// An auxiliary function" << endl
			<< "void label(string L, pair[] P, pair D) {" << endl
			<< "  for(pair k : P)" << endl
			<< "    label(L, k, D);" << endl
			<< "}" << endl
			<< preamble_stream.str();

#line 6634 "figure.nw"
	ost << main_stream.str()
		<< dots
		<< labels_stream.str();
}

#line 6641 "figure.nw"
void figure::asy_write(int size, const ex & xmin, const ex & xmax, const ex & ymin, const ex & ymax,
					  string name, string format,
					  asy_style style, label_string lstring, bool with_realline,
					  bool with_header, int points_per_arc, const string imaginary_options,
					  bool rm_asy_file, bool with_labels) const
{
	
#line 6507 "figure.nw"
	if (! (get_dim()-2).is_zero())
		throw logic_error("Drawing is possible for two-dimensional figures only!");

#line 6652 "figure.nw"
	string filename=name+".asy";
	ofstream out(filename);
	out << "size(" << size << ");" << endl;
	asy_draw(out, cerr, "", xmin, xmax, ymin, ymax,
			 style, lstring, with_realline, with_header, points_per_arc, imaginary_options, with_labels);
	if (name == "")
		out << "shipout();" << endl;
	else
		out << "shipout(\"" << name << "\");" << endl;
	out.flush();
	out.close();

#line 6666 "figure.nw"
	char command[256];
	strcpy(command, show_asy_graphics? "asy -V" : "asy");
	if (format != "") {
		strcat(command, " -f ");
		strcat(command, format.c_str());
	}
	strcat(command, " ");
	strcat(command, name.c_str());
	char * pcommand=command;
	system(pcommand);
	if (rm_asy_file)
		remove(filename.c_str());
}

#line 6682 "figure.nw"
void figure::asy_animate(const ex &val,
						 int size, const ex & xmin, const ex & xmax, const ex & ymin, const ex & ymax,
						 string name, string format, asy_style style, label_string lstring, bool with_realline,
						 bool with_header, int points_per_arc, const string imaginary_options,
						 const string values_position, bool rm_asy_file, bool with_labels) const
{
	
#line 6507 "figure.nw"
	if (! (get_dim()-2).is_zero())
		throw logic_error("Drawing is possible for two-dimensional figures only!");

#line 6689 "figure.nw"
	string filename=name+".asy";
	ofstream out(filename);
#line 6695 "figure.nw"
	if (format == "pdf")
		out << "settings.tex=\"pdflatex\";" << endl
			<< "settings.embed=true;" << endl
			<< "import animate;" << endl
			<< "size(" << size << ");" << endl
			<< "animation a=animation(\"" << name << "\");" << endl;
	else
		out << "import animate;" << endl
			<< "size(" << size << ");" << endl
			<< "animation a;" << endl;

#line 6709 "figure.nw"
	for (const auto& it : ex_to<lst>(val)) {
		out << "save();" << endl;
		unfreeze().subs(it).asy_draw(out, cerr, "", xmin, xmax, ymin, ymax,
									 style, lstring, with_realline, with_header, points_per_arc, imaginary_options, with_labels);

#line 6716 "figure.nw"
		std::regex deq ("==");
		stringstream sstr;
		sstr <<  (ex)it;
		string val_str=std::regex_replace(sstr.str(),deq,"=");

#line 6723 "figure.nw"
		if (values_position=="bl")
			out << "label(\"\\texttt{" << val_str << "}\",(" << xmin << "," << ymin << "), SE);";
		else if (values_position=="br")
			out << "label(\"\\texttt{" << val_str << "}\",(" << xmax << "," << ymin << "), SW);";
		else if (values_position=="tl")
			out << "label(\"\\texttt{" << val_str << "}\",(" << xmin << "," << ymax << "), NE);";
		else if (values_position=="tr")
			out << "label(\"\\texttt{" << val_str << "}\",(" << xmax << "," << ymax << "), NW);";

		out << "a.add();" << endl
			<< "restore();" << endl;
	}

#line 6739 "figure.nw"
	if (format == "pdf")
		out << "label(a.pdf(\"controls\",delay=250,keep=!settings.inlinetex));" << endl;
	else if ((format == "gif") ||  (format == "mp4") || (format == "mng"))
		out << "a.movie(loops=10,delay=250);" << endl;
	else
		out << format << endl;
	out.flush();
	out.close();

#line 6750 "figure.nw"
	char command[256];
	strcpy(command, show_asy_graphics? "asy -V " : "asy ");
	if ((format == "gif") || (format == "mp4") || (format == "mng")) {
		strcat(command, " -f ");
		strcat(command, format.c_str());
		strcat(command, " ");
	}
	strcat(command, name.c_str());
	char * pcommand=command;
	system(pcommand);
	if (rm_asy_file)
		remove(filename.c_str());
}

#line 6768 "figure.nw"
void figure::arrangement_write(string name, int first_gen) const
{
	if (! (get_dim()-3).is_zero())
		throw(std::invalid_argument("figure::arrangement_write(): the figure is not in 3D!"));

	string filename=name+".txt";
	ofstream out(filename);
#line 6780 "figure.nw"
	lst keys=ex_to<lst>(get_all_keys_sorted(first_gen));
	for (const auto& itk : keys) {
		ex gen=get_generation(itk);
		lst L=ex_to<lst>(get_cycles(itk));

#line 6788 "figure.nw"
	for (const auto& it : L) {
		cycle C=ex_to<cycle>(it);
		ex center = C.center();

#line 6795 "figure.nw"
		out <<  center.op(0).evalf() << " " << center.op(1).evalf() << " " << center.op(2).evalf()
			<< " " << sqrt(C.radius_sq()).evalf()
			<< " " << gen
			<< " " << itk
			<< endl;
		}
	}
	out.flush();
	out.close();
}

#line 6813 "figure.nw"
return_type_t figure::return_type_tinfo() const
{
	return make_return_type_t<figure>();
}

#line 6820 "figure.nw"
int figure::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<figure>(other));
	   return inherited::compare_same_type(other);
}

#line 6828 "figure.nw"
void figure::do_print(const print_dflt & con, unsigned level) const {
	lst keys=ex_to<lst>(get_all_keys_sorted(FIGURE_DEBUG?GHOST_GEN:INFINITY_GEN));
	int N_cycle=0;

	for (const auto& ck: keys) {
		N_cycle += get_cycles(ck).nops();
		con.s << ck <<": " << get_cycle_node(ck);
	}

	con.s << "Altogether " << N_cycle << " cycles in "
		  << keys.nops() << " cycle_nodes." << endl;
}

#line 6843 "figure.nw"
void figure::do_print_double(const print_dflt & con, unsigned level) const {
	for (const auto& x: nodes) {
		if (x.second.get_generation() > GHOST_GEN  || FIGURE_DEBUG) {
			con.s << x.first <<": ";
			ex_to<cycle_node>(x.second).do_print_double(con, level);
		}
	}
}

#line 6854 "figure.nw"
ex figure::op(size_t i) const
{
 GINAC_ASSERT(i<nops());
	switch(i) {
	case 0:
		return real_line;
	case 1:
		return infinity;
	case 2:
		return point_metric;
	case 3:
		return cycle_metric;
	default:
		exhashmap<cycle_node>::const_iterator it=nodes.begin();
		for (size_t n=4; n<i;++n)
			++it;
		return it->second;
	}
}

#line 6876 "figure.nw"
/*ex & figure::let_op(size_t i)
{
	ensure_if_modifiable();
	GINAC_ASSERT(i<nops());
	switch(i) {
	case 0:
		return real_line;
	case 1:
		return infinity;
	case 2:
		return point_metric;
	case 3:
		return cycle_metric;
	default:
		exhashmap<cycle_node>::iterator it=nodes.begin();
		for (size_t n=4; n<i;++n)
			++it;
		return nodes[it->first];
	}
}*/

#line 6899 "figure.nw"
figure figure::subs(const ex & e, unsigned options) const
{
	exmap m;
	if (e.info(info_flags::list)) {
		lst sl = ex_to<lst>(e);
		for (const auto& i : sl)
			m.insert(std::make_pair(i.op(0), i.op(1)));
	} else if (is_a<relational>(e)) {
		m.insert(std::make_pair(e.op(0), e.op(1)));
	} else
		throw(std::invalid_argument("cycle::subs(): the parameter should be a relational or a lst"));

	return ex_to<figure>(subs(m, options));
}

#line 6916 "figure.nw"
ex figure::subs(const exmap & m, unsigned options) const
{
	exhashmap<cycle_node> snodes;
	for (const auto& x: nodes)
		snodes[x.first]=ex_to<cycle_node>(x.second.subs(m, options));

	if (options & do_not_update_subfigure)
		return figure(point_metric.subs(m, options), cycle_metric.subs(m, options), snodes);
	else
		return figure(point_metric.subs(m, options), cycle_metric.subs(m, options), snodes).update_cycles();
}

#line 6930 "figure.nw"
ex figure::evalf(int level) const
{
	exhashmap<cycle_node> snodes;
	for (const auto& x: nodes)
#if GINAC_VERSION_ATLEAST(1,7,0)
		snodes[x.first]=ex_to<cycle_node>(x.second.evalf());

	return figure(point_metric.evalf(), cycle_metric.evalf(), snodes);
#else
		snodes[x.first]=ex_to<cycle_node>(x.second.evalf(level));

	return figure(point_metric.evalf(level), cycle_metric.evalf(level), snodes);
#endif
}

#line 6951 "figure.nw"
void figure::archive(archive_node &an) const
{
	inherited::archive(an);
	an.add_ex("real_line", real_line);
	an.add_ex("infinity", infinity);
	an.add_ex("point_metric", point_metric);
	an.add_ex("cycle_metric", cycle_metric);
	an.add_bool("float_evaluation", float_evaluation);

#line 6962 "figure.nw"
	lst keys, cnodes;
	for (const auto& x: nodes) {
		keys.append(x.first);
		cnodes.append(x.second);
	}
	an.add_ex("keys", keys);
	an.add_ex("cnodes", cnodes);
	an.add_string("info_text", info_text);
}

#line 6976 "figure.nw"
void figure::read_archive(const archive_node &an, lst &sym_lst)
{
	inherited::read_archive(an, sym_lst);
	an.find_ex("point_metric",  point_metric, sym_lst);
	an.find_ex("cycle_metric", cycle_metric, sym_lst);
	lst all_sym=sym_lst;
	ex keys, cnodes;
	an.find_ex("real_line", real_line, sym_lst);
	all_sym.append(real_line);
	an.find_ex("infinity", infinity, sym_lst);
	all_sym.append(infinity);
	an.find_bool("float_evaluation", float_evaluation);

#line 6991 "figure.nw"
	//an.find_ex("keys", keys, all_sym);
	an.find_ex("keys", keys, sym_lst);
	for (const auto& it : ex_to<lst>(keys))
		all_sym.append(it);
	all_sym.sort();
	all_sym.unique();
	an.find_ex("cnodes", cnodes, all_sym);
	lst::const_iterator it1 = ex_to<lst>(cnodes).begin();
	nodes.clear();
	for (const auto& it : ex_to<lst>(keys)) {
		nodes[it]=ex_to<cycle_node>(*it1);
		++it1;
	}
	an.find_string("info_text", info_text);
}

#line 7009 "figure.nw"
GINAC_BIND_UNARCHIVER(figure);

#line 7013 "figure.nw"
bool figure::info(unsigned inf) const
{
	switch (inf) {
	case status_flags::expanded:
		return (inf & flags);
	}
	return inherited::info(inf);
}

#line 7028 "figure.nw"
ex figure::check_rel(const ex & key1, const ex & key2, PCR rel, bool use_cycle_metric,
					 const ex & parameter, bool corresponds) const
{
	
#line 7039 "figure.nw"
	lst res,
		cycles1=ex_to<lst>(ex_to<cycle_node>(nodes.find(key1)->second)
						   .make_cycles(use_cycle_metric? cycle_metric : point_metric)),
		cycles2=ex_to<lst>(ex_to<cycle_node>(nodes.find(key2)->second)
						   .make_cycles(use_cycle_metric? cycle_metric : point_metric));

	if (corresponds && cycles1.nops() == cycles2.nops()) {
		auto it2=cycles2.begin();
		for (const auto& it1 : cycles1) {
			lst calc=ex_to<lst>(rel(it1,*(it2++),parameter));
			for (const auto& itr : calc)

#line 7032 "figure.nw"
	
#line 7055 "figure.nw"
			{
				ex e=(itr.op(0)).normal();
				if (is_a<relational>(e))
					res.append(e);
				else
					res.append(e==0);
			}

#line 7033 "figure.nw"
	
#line 7065 "figure.nw"
	  }
	} else {
		for (const auto& it1 : cycles1) {
			for (const auto& it2 : cycles2) {
				lst calc=ex_to<lst>(rel(it1,it2,parameter));
				for (const auto& itr : calc)

#line 7034 "figure.nw"
	
#line 7055 "figure.nw"
			{
				ex e=(itr.op(0)).normal();
				if (is_a<relational>(e))
					res.append(e);
				else
					res.append(e==0);
			}

#line 7074 "figure.nw"
			}
		}
	}
	return res;
}

#line 7083 "figure.nw"
ex figure::measure(const ex & key1, const ex & key2, PCR rel, bool use_cycle_metric,
				   const ex & parameter, bool corresponds) const
{
	
#line 7039 "figure.nw"
	lst res,
		cycles1=ex_to<lst>(ex_to<cycle_node>(nodes.find(key1)->second)
						   .make_cycles(use_cycle_metric? cycle_metric : point_metric)),
		cycles2=ex_to<lst>(ex_to<cycle_node>(nodes.find(key2)->second)
						   .make_cycles(use_cycle_metric? cycle_metric : point_metric));

	if (corresponds && cycles1.nops() == cycles2.nops()) {
		auto it2=cycles2.begin();
		for (const auto& it1 : cycles1) {
			lst calc=ex_to<lst>(rel(it1,*(it2++),parameter));
			for (const auto& itr : calc)

#line 7087 "figure.nw"
	res.append(itr.op(0));
	
#line 7065 "figure.nw"
	  }
	} else {
		for (const auto& it1 : cycles1) {
			for (const auto& it2 : cycles2) {
				lst calc=ex_to<lst>(rel(it1,it2,parameter));
				for (const auto& itr : calc)

#line 7089 "figure.nw"
	res.append(itr.op(0));
				}
			}
		}
	return res;
}
#line 7099 "figure.nw"
ex figure::apply(PEVAL func, bool use_cycle_metric, const ex & param) const
{
	lst res;
	for (const auto& x: nodes) {
		int i=0;
		lst cycles=ex_to<lst>(x.second.make_cycles(use_cycle_metric? cycle_metric : point_metric));
		for (const auto& itc : cycles) {
			res.append(lst{func(itc, param), x.first, i});
			++i;
		}
	}
	return res;
}
#line 7121 "figure.nw"
string asy_cycle_color(const ex & label, const ex & C, lst & color)
{
	string asy_options="";
	if (is_less_than_epsilon(ex_to<cycle>(C).det())) {// point
		color=lst{0.5,0,0};
		asy_options="dotted";
	} else if (is_less_than_epsilon(ex_to<cycle>(C).get_k())) // straight line
		color=lst{0,0.5,0};
	else  // a proper circle-hyperbola-parabola
		color=lst{0,0,0.5};

	return asy_options;
}
#line 7138 "figure.nw"
string label_pos(const ex & label, const ex & C, const string draw_str) {
	stringstream sstr;
	sstr << latex << label;

	string name=ex_to<symbol>(label).get_name(), new_TeXname;

	if (sstr.str() == name) {
		string TeXname;
		
#line 5614 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 7147 "figure.nw"
		if (TeXname_new =="")
			new_TeXname=name;
		else
			new_TeXname=TeXname_new;
	} else
		new_TeXname=sstr.str();
#line 7157 "figure.nw"
	std::regex draw("([.\\n\\r\\s]*)(draw)\\(([\\w]+,)?((?:\\(.+?\\)|\\{.+?\\}|[^-,0-9\\.])+),([.\\n\\r]*)");
	std::regex dot("([.\\n\\r\\s]*)(dot)\\(([\\w]*,)?((?:\\(.+?\\)|\\{.+?\\}|[^-,0-9\\.])+|[\\w]+),([.\\n\\r]*)");
	std::regex e1("symbolLaTeXname");

	if (std::regex_search(draw_str, dot)) {
			string labelstr=std::regex_replace (draw_str, dot,
								"label($3\"$symbolLaTeXname$\", $4, SE);\n",
								std::regex_constants::format_no_copy);
			return std::regex_replace (labelstr, e1, new_TeXname);
	} else if (std::regex_search(draw_str, draw)) {
			string labelstr=std::regex_replace (draw_str, draw,
								"label($3\"$symbolLaTeXname$\", point($4,0.1), SE);\n",
								std::regex_constants::format_no_copy | std::regex_constants::format_first_only);
			return std::regex_replace (labelstr, e1, new_TeXname);
	} else
		return "";
}

#line 7407 "figure.nw"
bool is_almost_equal(const ex & A, const ex & B)
{
	if ((not is_a<cycle>(A)) || (not is_a<cycle>(B)))
		return false;

	const cycle C1 = ex_to<cycle>(A),
        C2 = ex_to<cycle>(B);
	ex factor=0, ofactor=0;

	// Check that coefficients are scalar multiples of C2
	if (not is_less_than_epsilon((C1.get_m()*C2.get_k()-C2.get_m()*C1.get_k()).normal()))
		return false;
	// Set up coefficients for proportionality
	if (C1.get_k().normal().is_zero()) {
		factor=C1.get_m();
		ofactor=C2.get_m();
	} else {
		factor=C1.get_k();
		ofactor=C2.get_k();
	}
#line 7431 "figure.nw"
	   for (unsigned int i=0; i<C1.get_l().nops(); i++)
		// search the the first non-zero coefficient
		if (factor.is_zero()) {
			factor=C1.get_l(i);
			ofactor=C2.get_l(i);
		} else
			if (! is_less_than_epsilon((C1.get_l(i)*ofactor-C2.get_l(i)*factor).normal()))
				return false;
	return true;
}

#line 7444 "figure.nw"
ex midpoint_constructor()
{
 	figure SF=ex_to<figure>((new figure)->setflag(status_flags::expanded));

	ex v1=SF.add_cycle(cycle_data(),"variable000");
	ex v2=SF.add_cycle(cycle_data(),"variable001");
	ex v3=SF.add_cycle(cycle_data(),"variable002");
#line 7455 "figure.nw"
	ex v4=SF.add_cycle_rel(lst{cycle_relation(v1,cycle_orthogonal),
				cycle_relation(v2,cycle_orthogonal),
				cycle_relation(v3,cycle_orthogonal)},
		"v4");

#line 7462 "figure.nw"
	ex v5=SF.add_cycle_rel(lst{cycle_relation(v1,cycle_orthogonal),
				cycle_relation(v2,cycle_orthogonal),
				cycle_relation(v4,cycle_orthogonal)},
		"v5");

#line 7469 "figure.nw"
	ex v6=SF.add_cycle_rel(lst{cycle_relation(v3,cycle_orthogonal),
				cycle_relation(v4,cycle_orthogonal),
				cycle_relation(v5,cycle_orthogonal)},
		"v6");

#line 7476 "figure.nw"
	ex r=symbol("result");
 SF.add_cycle_rel(lst{cycle_relation(v4,cycle_orthogonal),
			 cycle_relation(v6,cycle_orthogonal),
			 cycle_relation(r,cycle_orthogonal,false),
			 cycle_relation(v3,cycle_adifferent)},
	 r);

	return SF;
}


#line 7490 "figure.nw"
ex unique_cycle(const ex & L)
{
	if(is_a<lst>(L) && (L.nops() > 1) ) {
		lst res;
		lst::const_iterator it = ex_to<lst>(L).begin();
		if (is_a<cycle_data>(*it)) {
			res.append(*it);
			++it;
			for (; it != ex_to<lst>(L).end(); ++it) {
				bool is_new=true;
				if (! is_a<cycle_data>(*it))
					break; // a non-cycle detected, get out

				for (const auto& it1 : res)
					if (ex_to<cycle_data>(*it).is_almost_equal(ex_to<basic>(it1),true)
						|| ex_to<cycle_data>(*it).is_equal(ex_to<basic>(it1),true)) {
						is_new=false; // is a duplicate
						break;
					}
				if (is_new)
					res.append(*it);
			}
			if (it == ex_to<lst>(L).end()) // all are processed, no non-cycle is detected
				return res;
		}
	}
	return L;
}
#line 7523 "figure.nw"
void figure_debug_on() { FIGURE_DEBUG = true; }
void figure_debug_off() { FIGURE_DEBUG = false; }
bool figure_ask_debug_status() { return FIGURE_DEBUG; }
#line 7531 "figure.nw"
void show_asy_on() { show_asy_graphics=true; }
void show_asy_off() { show_asy_graphics=false; }
#line 3940 "figure.nw"
} // namespace MoebInv

