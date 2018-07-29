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

#ifndef ____figure__
#define ____figure__

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <regex>
#include "cycle.h"

namespace MoebInv {
using namespace std;
using namespace GiNaC;
#define REAL_LINE_GEN -1
#define INFINITY_GEN -2
#define GHOST_GEN -3
using PEVAL = std::function<ex(const ex &, const ex &)>;

using PCR = std::function<ex(const ex &, const ex &, const ex &)>;
class cycle_data : public basic
{
GINAC_DECLARE_REGISTERED_CLASS(cycle_data, basic)
protected:
	ex k,
	l,
	m;

public:
	cycle_data(const ex & C);
 	cycle_data(const ex & k1, const ex l1, const ex &m1, bool normalize=false);
	ex get_cycle(const ex & metr) const;
	inline size_t nops() const { return 3; }
	ex op(size_t i) const;
	ex & let_op(size_t i);
	inline ex get_k() const { return k; }
	inline ex get_l() const { return l; }
	inline ex get_l(size_t i) const { return l.op(0).op(i); }
	inline ex get_m() const { return m;}
	inline long unsigned int get_dim() const { return l.op(0).nops(); }
	void do_print(const print_dflt & con, unsigned level) const;
	void archive(archive_node &n) const;
	inline ex normalize() const {return cycle_data(k,l,m,true);}
	ex num_normalize() const;
	void read_archive(const archive_node &n, lst &sym_lst);
	bool is_equal(const basic & other, bool projectively) const;
	bool is_almost_equal(const basic & other, bool projectively) const;
	cycle_data subs(const ex & e, unsigned options=0) const;
	ex subs(const exmap & em, unsigned options=0) const;
	inline bool has(const ex & x) const { return (k.has(x) ||  l.has(x) ||  m.has(x)); }

protected:
	return_type_t return_type_tinfo() const;
};
GINAC_DECLARE_UNARCHIVER(cycle_data);

class cycle_relation;

class cycle_node : public basic
{
GINAC_DECLARE_REGISTERED_CLASS(cycle_node, basic)
protected:
	lst cycles; // List of cycle data entries
	int generation;
	lst children; // List of keys to cycle_nodes
	lst parents; // List of cycle_relations or a list containing a single subfigure
	string custom_asy; // Custom string for Asymptote

public:
	cycle_node(const ex & C, int g=0);
	cycle_node(const ex & C, int g, const lst & par);
	cycle_node(const ex & C, int g, const lst & par, const lst & chil);
	cycle_node(const ex & C, int g, const lst & par, const lst & chil, string ca);
	cycle_node subs(const ex & e, unsigned options=0) const;
	ex subs(const exmap & m, unsigned options=0) const;

protected:
	inline void add_child(const ex & c) {children.append(c);}

	inline ex get_cycles() const {return cycles;}

	ex get_cycle(const ex & metr) const;
	inline ex get_cycle_data(int i) const {return cycles.op(i);}

	inline int get_generation() const {return generation;}

	inline lst get_children() const {return children;}

	void set_cycles(const ex & C);

	void append_cycle(const ex & C);
	void append_cycle(const ex & k, const ex & l, const ex & m);

	lst get_parents() const;

	lst get_parent_keys() const ;

	void remove_child(const ex & c);

	inline void set_asy_opt(const string opt)  {custom_asy=opt;}

	inline size_t nops() const { return cycles.nops()+children.nops()+parents.nops(); }
	ex op(size_t i) const;
	ex & let_op(size_t i);
	void do_print(const print_dflt & con, unsigned level) const;
	void do_print_tree(const print_tree & con, unsigned level) const;
protected:
	return_type_t return_type_tinfo() const;
	void archive(archive_node &n) const;
	void read_archive(const archive_node &n, lst &sym_lst);

friend class cycle_relation;
friend class figure;
};
GINAC_DECLARE_UNARCHIVER(cycle_node);

class cycle_relation : public basic
{
	GINAC_DECLARE_REGISTERED_CLASS(cycle_relation, basic)
protected:
	ex parkey; // A key to a parent cycle_node in figure
	PCR rel; // A pointer to function which produces the relation
	ex parameter; // The value, which is supplied to rel() as the third parameter
	bool use_cycle_metric; // If true uses the cycle space metric, otherwise the point space metric
public:
	cycle_relation(const ex & key, PCR rel, bool cm=true, const ex & p=0);
	inline ex get_parkey() const {return parkey;}
	inline PCR get_PCR() const {return rel;}
	inline ex get_parameter() const {return parameter;}
	inline bool cycle_metric_inuse() const {return use_cycle_metric;}
	inline ex subs(const exmap & em, unsigned options=0) const
	{return cycle_relation(parkey, rel, use_cycle_metric, parameter.subs(em,options));}

protected:
	ex rel_to_parent(const cycle_data & C1, const ex & pmetric, const ex & cmetric,
					 const exhashmap<cycle_node> & N) const;
	return_type_t return_type_tinfo() const;
	void do_print(const print_dflt & con, unsigned level) const;
	void do_print_tree(const print_tree & con, unsigned level) const;

	void archive(archive_node &n) const;
	void read_archive(const archive_node &n, lst &sym_lst);

	inline size_t nops() const { return 2; }
	ex op(size_t i) const;
	ex & let_op(size_t i);

friend class cycle_node;
friend class figure;
};
GINAC_DECLARE_UNARCHIVER(cycle_relation);

ex cycle_orthogonal(const ex & C1, const ex & C2, const ex & pr=0);
ex cycle_f_orthogonal(const ex & C1, const ex & C2, const ex & pr=0);
ex check_tangent(const ex & C1, const ex & C2, const ex & pr=0);
ex cycle_different(const ex & C1, const ex & C2, const ex & pr=0);
ex cycle_adifferent(const ex & C1, const ex & C2, const ex & pr=0);
ex product_sign(const ex & C1, const ex & C2, const ex & pr=1);
ex coefficients_are_real(const ex & C1, const ex & C2, const ex & pr=1);

ex cycle_tangent(const ex & C1, const ex & C2, const ex & pr=0);
ex cycle_tangent_i(const ex & C1, const ex & C2, const ex & pr=0);
ex cycle_tangent_o(const ex & C1, const ex & C2, const ex & pr=0);
ex cycle_angle(const ex & C1, const ex & C2, const ex & pr);
ex steiner_power(const ex & C1, const ex & C2, const ex & pr);
ex cycle_cross_t_distance(const ex & C1, const ex & C2, const ex & pr);
ex cycle_moebius(const ex & C1, const ex & C2, const ex & pr);
ex cycle_sl2(const ex & C1, const ex & C2, const ex & pr);
ex power_is(const ex & C1, const ex & C2, const ex & pr=1);
inline ex sq_t_distance_is(const ex & C1, const ex & C2, const ex & pr=1)
 {return power_is(C1,C2,1);}
inline ex sq_cross_t_distance_is(const ex & C1, const ex & C2, const ex & pr=-1)
 {return power_is(C1,C2,-1);}
ex angle_is(const ex & C1, const ex & C2, const ex & pr=0);
inline cycle_relation is_orthogonal(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_orthogonal, cm);}
inline cycle_relation is_f_orthogonal(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_f_orthogonal, cm);}
inline cycle_relation is_different(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_different, cm);}
inline cycle_relation is_adifferent(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_adifferent, cm);}
inline cycle_relation is_real_cycle(const ex & key, bool cm=false, const ex & pr=1)
 {return cycle_relation(key, product_sign, cm, pr);}
inline cycle_relation product_nonpositive(const ex & key, bool cm=true, const ex & pr=1)
 {return cycle_relation(key, product_sign, cm, pr);}
inline cycle_relation only_reals(const ex & key, bool cm=true, const ex & pr=0)
 {return cycle_relation(key, coefficients_are_real, cm, pr);}
inline cycle_relation is_tangent(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_tangent, cm);}
inline cycle_relation is_tangent_i(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_tangent_i, cm);}
inline cycle_relation is_tangent_o(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_tangent_o, cm);}
inline cycle_relation make_angle(const ex & key, bool cm=true, const ex & angle=0)
					{return cycle_relation(key, cycle_angle, cm, angle);}
inline cycle_relation cycle_power(const ex & key, bool cm=true, const ex & cpower=0)
					{return cycle_relation(key, steiner_power, cm, cpower);}
inline cycle_relation tangential_distance(const ex & key, bool cm=true, const ex & distance=0)
					{return cycle_relation(key, steiner_power, cm, pow(distance,2));}
inline cycle_relation cross_t_distance(const ex & key, bool cm=true, const ex & distance=0)
					{return cycle_relation(key, cycle_cross_t_distance, cm, distance);}
inline cycle_relation moebius_transform(const ex & key, bool cm=true,
										const ex & matrix=lst{numeric(1),0,0,numeric(1)})
					{return cycle_relation(key, cycle_moebius, cm, matrix);}
 cycle_relation sl2_transform(const ex & key, bool cm=true,
							  const ex & matrix=lst{numeric(1),0,0,numeric(1)});

ex metric_e = clifford_unit(varidx(symbol("i"), 2), indexed(diag_matrix(lst{-1,-1}), sy_symm(),
															varidx(symbol("j"), 2), varidx(symbol("k"), 2)));
ex metric_p = clifford_unit(varidx(symbol("i"), 2), indexed(diag_matrix(lst{-1,0}), sy_symm(),
															varidx(symbol("j"), 2), varidx(symbol("k"), 2)));
ex metric_h = clifford_unit(varidx(symbol("i"), 2), indexed(diag_matrix(lst{-1,1}), sy_symm(),
															varidx(symbol("j"), 2), varidx(symbol("k"), 2)));
inline ex cycle_orthogonal_e(const ex & C1, const ex & C2, const ex & pr=0) {
	return lst{(ex)lst{ex_to<cycle>(C1).is_orthogonal(ex_to<cycle>(C2), metric_e)}};}

inline ex cycle_orthogonal_p(const ex & C1, const ex & C2, const ex & pr=0) {
	return lst{(ex)lst{ex_to<cycle>(C1).is_orthogonal(ex_to<cycle>(C2), metric_p)}};}

inline ex cycle_orthogonal_h(const ex & C1, const ex & C2, const ex & pr=0) {
	return lst{(ex)lst{ex_to<cycle>(C1).is_orthogonal(ex_to<cycle>(C2), metric_h)}};}
using asy_style=std::function<string(const ex &, const ex &, lst &)>;
//typedef string (*asy_style)(const ex &, const ex &, lst &);
inline string no_color(const ex & label, const ex & C, lst & color) {color=lst{0,0,0}; return "";}
string asy_cycle_color(const ex & label, const ex & C, lst & color);
asy_style default_asy=asy_cycle_color;

using label_string=std::function<string(const ex &, const ex &, const string)>;
//typedef string (*label_string)(const ex &, const ex &, const string);
string label_pos(const ex & label, const ex & C, const string draw_str);
inline string no_label(const ex & label, const ex & C, const string draw_str) {return "";}
//label_string default_label=*no_label;
label_string default_label=label_pos;

class figure : public basic
{
GINAC_DECLARE_REGISTERED_CLASS(figure, basic)

protected:
 ex real_line, // the key for the real line
	  infinity; // the key for cycle at infinity
	ex point_metric; // The metric of the point space encoded as a clifford_unit object
	ex cycle_metric; // The metric of the cycle space encoded as a clifford_unit object
	exhashmap<cycle_node> nodes; // List of cycle_node, exhashmap<cycle_node> object
	bool float_evaluation=false;
	ex k, m; // realsymbols for symbolic calculations
	lst l;
protected:
	ex update_cycle_node(const ex & key, const lst & eq_cond=lst{},
						   const lst & neq_cond=lst{}, lst res=lst{}, size_t level=0);
	void set_cycle(const ex & key, const ex & C);
	ex evaluate_cycle(const ex & symbolic, const lst & cond) const;

public:
	figure(const ex & Mp, const ex & Mc=0);
	void set_metric(const ex & Mp, const ex & Mc=0);
	figure(const ex & Mp, const ex & Mc, const exhashmap<cycle_node> & N);
	void reset_figure();
	ex add_point(const ex & x, string name, string TeXname="");
	ex add_point(const ex & x, const ex & key);
	ex add_cycle(const ex & C, string name, string TeXname="");
	ex add_cycle(const ex & C, const ex & key);
	ex add_cycle_rel(const lst & rel, string name, string TeXname="");
	ex add_cycle_rel(const lst & rel, const ex & key);
	ex add_cycle_rel(const ex & rel, string name, string TeXname="");
	ex add_cycle_rel(const ex & rel, const ex & key);
	ex add_subfigure(const ex & F, const lst & L, string name, string TeXname="");
	ex add_subfigure(const ex & F, const lst & L, const ex & key);
	void move_point(const ex & key, const ex & x);
	void move_cycle(const ex & key, const ex & C);
	void remove_cycle_node(const ex & key);
	ex get_cycle_label(string name) const;
	ex get_all_keys(const int mingen = GHOST_GEN+1, const int maxgen = GHOST_GEN) const;
	ex check_rel(const ex & key1, const ex & key2, PCR rel, bool use_cycle_metric=true,
				 const ex & parameter=0, bool corresponds=true) const;
	ex measure(const ex & key1, const ex & key2, PCR rel, bool use_cycle_metric=true,
			   const ex & parameter=0, bool corresponds=true) const;
	inline ex get_point_metric() const { return point_metric; }
	inline ex get_cycle_metric() const { return cycle_metric; }
	inline ex get_dim() const { return ex_to<varidx>(point_metric.op(1)).get_dim(); }
	inline ex get_cycle(const ex & k, bool use_point_metric=true) const {
		return get_cycle(k,use_point_metric?point_metric:cycle_metric);}
	ex get_cycle(const ex & k, const ex & metric) const;
	inline ex get_generation(const ex & k) const {
		return ex_to<cycle_node>(get_cycle_node(k)).get_generation();}
	ex apply(PEVAL func, bool use_cycle_metric=true, const ex & param = 0) const;
	void asy_draw(ostream & ost =std::cout, ostream & err=std::cerr, const string picture="",
				  const ex & xmin = -5, const ex & xmax = 5,
				  const ex & ymin = -5, const ex & ymax = 5,
				  asy_style style=default_asy, label_string lstring=default_label,
				  bool with_realline=true, bool with_header=true,
				  int points_per_arc = 0, const string imaginary_options="rgb(0,.9,0)+4pt",
				  bool with_labels=true) const;
	void asy_write(int size=300, const ex & xmin = -5, const ex & xmax = 5,
				   const ex & ymin = -5, const ex & ymax = 5,
				   string name="figure-view-tmp", string format="",
				   asy_style style=default_asy, label_string lstring=default_label,
				   bool with_realline=true, bool with_header=true,
				   int points_per_arc=0, const string imaginary_options="rgb(0,.9,0)+4pt",
				   bool rm_asy_file=true, bool with_labels=true) const;
	void asy_animate(const ex & val,
					 int size=300, const ex & xmin = -5, const ex & xmax = 5,
					 const ex & ymin = -5, const ex & ymax = 5,
					 string name="figure-animatecf-tmp", string format="pdf",
					 asy_style style=default_asy, label_string lstring=default_label,
					 bool with_realline=true, bool with_header=true,
					 int points_per_arc = 0, const string imaginary_options="rgb(0,.9,0)+4pt",
					 const string values_position="bl", bool rm_asy_file=true,
					 bool with_labels=true) const;
	inline figure freeze() const {setflag(status_flags::expanded); return *this;}
	inline figure unfreeze() const {clearflag(status_flags::expanded); return *this;}
	inline figure set_float_eval() {float_evaluation=true; return *this;}
	inline figure set_exact_eval() {float_evaluation=false; return *this;}
	inline void set_asy_style(const ex & key, string opt) {nodes[key].set_asy_opt(opt);}
	void arrangement_write(string name, int first_gen=0) const;
	void save(const char* file_name, const char* fig_name="myfig") const;
	figure(const char* file_name, string fig_name="myfig");
		inline exhashmap<cycle_node> get_nodes() const {return nodes;}

		inline size_t nops() const {return 4+nodes.size();}
		ex op(size_t i) const;
		//ex & let_op(size_t i);
		ex evalf(int level=0) const;
		figure subs(const ex & e, unsigned options=0) const;
		ex subs(const exmap & m, unsigned options=0) const;
		void archive(archive_node &n) const;
		void read_archive(const archive_node &n, lst &sym_lst);
		bool info(unsigned inf) const;

	inline ex get_cycle_node(const ex & k) const {return nodes.find(k)->second;}
	inline ex get_real_line() const {return real_line;}
	inline ex get_infinity() const {return infinity;}
protected:
	void do_print(const print_dflt & con, unsigned level) const;
	return_type_t return_type_tinfo() const;

	void update_node_lst(const ex & inlist);
	figure update_cycles();
};
GINAC_DECLARE_UNARCHIVER(figure);
class subfigure : public basic
{
	GINAC_DECLARE_REGISTERED_CLASS(subfigure, basic)
protected:
	ex subf; // A figure to be inserted
	lst parlist; // A list of key to a parent cycle_node in figure
public:
	subfigure(const ex & F, const ex & L);
	inline ex subs(const exmap & em, unsigned options=0) const;
protected:
	inline ex get_parlist() const {return parlist;}
	inline ex get_subf() const {return subf;}
	return_type_t return_type_tinfo() const;
	void do_print(const print_dflt & con, unsigned level) const;
	void do_print_tree(const print_tree & con, unsigned level) const;

	void archive(archive_node &n) const;
	void read_archive(const archive_node &n, lst &sym_lst);

friend class cycle_node;
friend class figure;
};
GINAC_DECLARE_UNARCHIVER(subfigure);

	void show_asy_on();
	void show_asy_off();
ex midpoint_constructor();
ex unique_cycle(const ex & L);
void figure_debug_on();
void figure_debug_off();
bool figure_ask_debug_status();
ex evaluation_assist = lst{pow(cos(wild(0)),2)==1-pow(sin(wild(0)),2),
		pow(cosh(wild(1)),2)==1+pow(sinh(wild(1)),2)};
} // namespace MoebInv
#endif /* defined(____figure__) */

