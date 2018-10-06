// 	$Id: figure.cpp,v 1.15 2015/02/12 16:54:47 kisilv Exp kisilv $	
/*
 *  PyDual_Number Copyright (C) 2006 Vladimir Kisil
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

#include "figure.h"
#include "pyginac.hpp"

#include <boost/python/class.hpp>
#include <boost/python/def.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/str.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/list.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/make_constructor.hpp>

#include <boost/python/return_internal_reference.hpp>
#include <boost/python/default_call_policies.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/object/function.hpp>
#include <boost/function_types/function_type.hpp>

namespace pyfigure {
using namespace MoebInv;
using namespace std;
using namespace GiNaC;

PyObject*
py_list_from_lst(GiNaC::ex L) {
	lst obj=ex_to<lst>(L);
	boost::python::list ret;
	GiNaC::lst::const_iterator i = obj.begin();
	GiNaC::lst::const_iterator i_end = obj.end();
	while (i != i_end) {
		ret.append( boost::python::object(*i));
		++i;
	}

	Py_INCREF(ret.ptr());
	return ret.ptr();
}

static boost::shared_ptr<figure>
do_init_with_llist_figure(boost::python::list bpl)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return boost::shared_ptr<figure>( new figure(l1));
}

class figure
subs_lst( const figure& This, boost::python::list lhs, unsigned options = 0)
{
    using namespace boost::python;
    std::map<ex, ex, GiNaC::ex_is_less> exmap;

    int end = pyginac::length(lhs);
    for (int i = 0; i != end; ++i) {
        GiNaC::relational equality = extract<GiNaC::relational>(lhs[i]);
        exmap[equality.op(0)] = equality.op(1);
		}
    return ex_to<figure>(ex(This).subs(exmap,options));
}

class figure
subs_dict( const figure& This, boost::python::dict rules, unsigned options = 0)
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
	return ex_to<figure>(ex(This).subs( exmap, options));
}

ex
add_cycle_rel_symb(figure & F, boost::python::list rel, const ex & key)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,rel);
	return F.add_cycle_rel(l1, key);
}

ex
add_cycle_rel_str(figure & F, boost::python::list rel, const string name)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,rel);
	return F.add_cycle_rel(l1, name);
}

ex
add_cycle_rel_str2(figure & F, boost::python::list rel, const string name, string TeXname)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,rel);
	return F.add_cycle_rel(l1, name, TeXname);
}

ex
add_cycle_rel1_symb(figure & F, cycle_relation rel, const ex & key)
{
	return F.add_cycle_rel(rel, key);
}

ex
add_cycle_rel1_str(figure & F, cycle_relation rel, const string name)
{
	return F.add_cycle_rel(rel, name);
}

ex
add_cycle_rel1_str2(figure & F, cycle_relation  rel, const string name, string TeXname)
{
	return F.add_cycle_rel(rel, name, TeXname);
}

cycle_relation
sl2_transform_bpl(const ex & key, bool cmetric, boost::python::list L)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return sl2_transform(key, cmetric, l1);
}

cycle_relation
moebius_transform_bpl(const ex & key, bool cmetric, boost::python::list L)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return moebius_transform(key, cmetric, l1);
}

void
do_asy_draw(const figure & F, ostream & ost =std::cout, ostream & err=std::cerr, const string picture="",
              const ex & xmin = -5, const ex & xmax = 5,
              const ex & ymin = -5, const ex & ymax = 5,
              bool with_realline=true, bool with_header = true, int points_per_arc = 0, const string imaginary_options="rgb(0,.9,0)+4pt")
{
    F.asy_draw( ost,  err,  picture, xmin, xmax, ymin,  ymax,
				default_asy, default_label,
				with_realline, with_header, points_per_arc, imaginary_options);
}

void
do_asy_print(const figure & F, const string name="figure_temp", const string picture="",
              const ex & xmin = -5, const ex & xmax = 5,
              const ex & ymin = -5, const ex & ymax = 5,
              bool with_realline=true, bool with_header = true, int points_per_arc = 0, const string imaginary_options="rgb(0,.9,0)+4pt")
{
	string filename=name+".asy";
	ofstream out(filename);
	F.asy_draw(out, std::cerr,  picture, xmin, xmax, ymin,  ymax,
			   default_asy, default_label,
			   with_realline, with_header, points_per_arc, imaginary_options);
}

void
do_asy_write(const figure & F, int size=300,
			  const ex & xmin = -5, const ex & xmax = 5,
			  const ex & ymin = -5, const ex & ymax = 5,
			  string name="figure-view-tmp", string format="eps",
			 bool with_realline=true, bool with_header = true, int points_per_arc = 0, const string imaginary_options="rgb(0,.9,0)+4pt", bool  rm_asy_file=true)
{
	F.asy_write(size, xmin, xmax, ymin,  ymax, name, format,
				default_asy, default_label, with_realline, with_header, points_per_arc, imaginary_options, rm_asy_file);
}

void
do_asy_animate(const figure & F, boost::python::list val, int size=300,
			   const ex & xmin = -5, const ex & xmax = 5,
			   const ex & ymin = -5, const ex & ymax = 5,
			   string name="figure-animate-tmp", string format="pdf",
			   bool with_realline=true, bool with_header = true, int points_per_arc = 0,
			   const string imaginary_options="rgb(0,.9,0)+4pt", const string values_position="bl",
			   bool rm_asy_file=true)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,val);
	F.asy_animate(l1, size, xmin, xmax, ymin,  ymax, name, format,
				  default_asy, default_label, with_realline, with_header, points_per_arc,
				  imaginary_options, values_position, rm_asy_file);
}

void
do_arrangement_visualise(const figure & F, int first_gen=0)
{
	F.arrangement_write("3D-visualise-tmp",first_gen);
	system("cycle3D-visualiser 3D-visualise-tmp.txt");
}

void
do_move_cycle(figure & F, const ex & key, const cycle & C) {
	F.move_cycle(key,C);
}

PyObject*
do_get_cycle(figure & F, const ex & key, bool use_point_metric=true) {
	lst	obj=ex_to<lst>(F.get_cycle(key,use_point_metric));
	boost::python::list ret;
	GiNaC::lst::const_iterator i = obj.begin();
	GiNaC::lst::const_iterator i_end = obj.end();
	while (i != i_end) {
		ret.append( boost::python::object(ex_to<cycle>(*i)));
		++i;
	}
	Py_INCREF(ret.ptr());
	return ret.ptr();
}
	
//ex
PyObject*
do_check_rel(figure & F, const ex & key1, const ex & key2, string rel,
			 bool use_cm=true, bool corresponding=true) {
	PCR rel_ptr;
	if (rel == "cycle_orthogonal")
		rel_ptr=cycle_orthogonal;
	else if (rel == "cycle_f_orthogonal")
		rel_ptr=cycle_f_orthogonal;
	else if (rel == "cycle_different")
		rel_ptr=cycle_different;
	else if (rel == "cycle_adifferent")
		rel_ptr=cycle_adifferent;
	else if (rel == "check_tangent")
		rel_ptr=check_tangent;
	else if (rel == "cycle_tangent")
		rel_ptr=cycle_tangent;
	else if (rel == "cycle_tangent_i")
		rel_ptr=cycle_tangent_i;
	else if (rel == "cycle_tangent_o")
		rel_ptr=cycle_tangent_o;
	else
		return py_list_from_lst(lst{numeric(1)==numeric(0)});

	//	return F.check_rel(key1, key2, rel_ptr, use_cm).op(0);
	return py_list_from_lst(F.check_rel(key1, key2, rel_ptr, use_cm, corresponding));
}

string
figure_to_string(const figure & F)
{
	std::ostringstream drawing;
	drawing << F;
	return drawing.str().c_str();
}

ex
add_point0(figure & F, boost::python::list bpl, const ex &k)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return F.add_point(l1, k);
}

ex
add_point3(figure & F, boost::python::list bpl, string name)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return F.add_point(l1, name);
}

ex
add_point4(figure & F, boost::python::list bpl, string name, string TeXname)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	return F.add_point(l1, name, TeXname);
}

void
move_point0(figure & F, const ex &k, boost::python::list bpl)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,bpl);
	F.move_point(k, l1);
}

ex
add_cycle0(figure & F, const ex & C, const ex &k )
{
	return F.add_cycle(C, k);
}

ex
add_cycle2(figure & F, const ex & C, string name)
{
	return F.add_cycle(C, name);
}

ex
add_cycle3(figure & F, const ex & C, string name, string TeXname)
{
	return F.add_cycle(C, name, TeXname);
}

ex
add_cycle4(figure & F, const cycle & C, const ex &k )
{
	return F.add_cycle(C, k);
}

ex
add_cycle5(figure & F, const cycle & C, string name)
{
	return F.add_cycle(C, name);
}

ex
add_cycle6(figure & F, const cycle & C, string name, string TeXname)
{
	return F.add_cycle(C, name, TeXname);
}

ex
add_subfigure0(figure & F, const figure & SF, boost::python::list L, const ex &k )
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(SF, l1, k);
}

ex
add_subfigure1(figure & F, const basic & SF, boost::python::list L, const ex &k )
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(ex_to<figure>(SF), l1, k);
}

ex
add_subfigure2(figure & F, const basic & SF, boost::python::list L, string name )
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(ex_to<figure>(SF), l1, name);
}

ex
add_subfigure3(figure & F, const  figure & SF, boost::python::list L, string name)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(SF, l1, name);
}

ex
add_subfigure4(figure & F, const  figure & SF, boost::python::list L, string name, string TeXname)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(SF, l1, name, TeXname);
}

ex
add_subfigure5(figure & F, const ex & SF, boost::python::list L, const ex &k )
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(SF, l1, k);
}

ex
add_subfigure6(figure & F, const  ex & SF, boost::python::list L, string name)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(SF, l1, name);
}

ex
add_subfigure7(figure & F, const  ex & SF, boost::python::list L, string name, string TeXname)
{
	GiNaC::lst l1;
	pyginac::lst_from_py_list(l1,L);
	return F.add_subfigure(SF, l1, name, TeXname);
}

figure
do_midpoint()
{
    return ex_to<figure>(midpoint_constructor());
}

figure
do_evalf(figure F, int level=0) {
	return ex_to<figure>(F.evalf(level));
}

//overloads for class figure

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(subs_overloads, subs, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_metric_overloads, set_metric, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(save_overloads, save, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(check_rel_overloads,check_rel,3,5)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(arrangement_write_overloads, arrangement_write, 1, 2)

BOOST_PYTHON_FUNCTION_OVERLOADS(subs_lst_overloads, subs_lst, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(subs_dict_overloads, subs_dict, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_get_cycle_overloads,do_get_cycle,2,3)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_check_rel_overloads,do_check_rel,4,6)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_asy_draw_overloads, do_asy_draw, 1, 12)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_asy_print_overloads, do_asy_print, 1, 10)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_asy_write_overloads, do_asy_write, 1, 13)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_arrangement_visualise_overloads, do_arrangement_visualise, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_orthogonal_overloads, is_orthogonal, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_f_orthogonal_overloads, is_f_orthogonal, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_different_overloads, is_different, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_adifferent_overloads, is_adifferent, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_tangent_overloads, is_tangent, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_tangent_i_overloads, is_tangent_i, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_tangent_o_overloads, is_tangent_o, 1, 2)
BOOST_PYTHON_FUNCTION_OVERLOADS(is_real_cycle_overloads, is_real_cycle, 1, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(only_reals_overloads, only_reals, 1, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(product_nonpositive_overloads, product_nonpositive, 1, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_evalf_overloads,do_evalf,1,2)
BOOST_PYTHON_FUNCTION_OVERLOADS(do_asy_animate_overloads,do_asy_animate,2,15)

void
wrap_figure(void)
{
  using namespace boost::python;
  //using namespace GiNaC;
  using GiNaC::basic;
  using GiNaC::ex;
  using GiNaC::lst;
  using GiNaC::matrix;
  using GiNaC::numeric;

//difficult overloads for figure
figure (figure::*subs0)(const ex &, unsigned) const = &figure::subs;
ex (figure::*subs1)(const exmap &, unsigned) const = &figure::subs;

  class_<figure, bases<basic> >
	  ("figure",
	   "The class describing ensembles of cycles",
	   no_init)

	  .add_property("real_line", &figure::get_real_line)
	  .def("get_real_line", &figure::get_real_line)
	  .add_property("infinity", &figure::get_infinity)
	  .def("get_infinity", &figure::get_infinity)
	  .def(init<>())
	  .def(init<const ex &, optional<const ex &> >())
	  .def(init<const char* >())
	  .def(init<const char* , optional<string> >())
	  .def("__init__", make_constructor(do_init_with_llist_figure),"Inititialise a figure from a Python list of metric's diagonal elemets")
	  .def("save", &figure::save, save_overloads("Save the figure into a file"))
	  .def("subs", subs_lst, subs_lst_overloads("Make a substitution in the figure"))
	  .def("subs", subs_dict, subs_dict_overloads("Make a substitution in the figure"))
	  .def("subs", subs0, subs_overloads("Make a substitution in the figure"))
	  .def("subs", subs1, subs_overloads("Make a substitution in the figure"))
	  .def("add_point", add_point0, "Add a pre-definec point to generation-0")
	  .def("add_point", add_point3, "Add a pre-definec point to generation-0")
	  .def("add_point", add_point4, "Add a pre-definec point to generation-0")
	  .def("add_cycle", add_cycle0, "Add a pre-definec cycle to generation-0")
	  .def("add_cycle", add_cycle2, "Add a pre-definec cycle to generation-0")
	  .def("add_cycle", add_cycle3, "Add a pre-definec cycle to generation-0")
	  .def("add_cycle", add_cycle4, "Add a pre-definec cycle to generation-0")
	  .def("add_cycle", add_cycle5, "Add a pre-definec cycle to generation-0")
	  .def("add_cycle", add_cycle6, "Add a pre-definec cycle to generation-0")
	  .def("add_subfigure", add_subfigure0, "Add a cycle defined trhrough a subfigure")
	  .def("add_subfigure", add_subfigure1, "Add a cycle defined trhrough a subfigure")
	  .def("add_subfigure", add_subfigure2, "Add a cycle defined trhrough a subfigure")
	  .def("add_subfigure", add_subfigure3, "Add a cycle defined trhrough a subfigure")
	  .def("add_subfigure", add_subfigure4, "Add a cycle defined trhrough a subfigure")
	  .def("add_subfigure", add_subfigure5, "Add a cycle defined trhrough a subfigure")
	  .def("add_subfigure", add_subfigure6, "Add a cycle defined trhrough a subfigure")
	  .def("add_subfigure", add_subfigure7, "Add a cycle defined trhrough a subfigure")
	  // Does not work need to learn how to create signatures of functions
	  //.def("add_cycle_rel1", make_function(&figure::add_cycle_rel,  default_call_policies(),
	  //								   (boost::python::arg("srel"), boost::python::arg("name"),
	  //									boost::python::arg("TeXname")=""),
	  //								   boost::function_types::function_type< boost::mpl::vector<ex,const ex &, string, string> >::type),
	  //	   "Add a cycle by certain relations to previous ones")
	  .def("add_cycle_rel", add_cycle_rel1_symb, "Add a cycle by single relation to previous ones")
	  .def("add_cycle_rel", add_cycle_rel1_str, "Add a cycle by a relation to previous ones")
	  .def("add_cycle_rel", add_cycle_rel1_str2, "Add a cycle by a relation to previous ones")
	  .def("add_cycle_rel", add_cycle_rel_symb, "Add a cycle by certain relations to previous ones")
	  .def("add_cycle_rel", add_cycle_rel_str, "Add a cycle by certain relations to previous ones")
	  .def("add_cycle_rel", add_cycle_rel_str2, "Add a cycle by certain relations to previous ones")
	  .def("set_metric", &figure::set_metric, set_metric_overloads("Set metric for the figure and re-calculate all cycles"))
	  .def("move_point", move_point0, "Move a point to new location")
	  .def("move_cycle", do_move_cycle, "Change data of a cycle at zero-level")
	  .def("remove_cycle_node", &figure::remove_cycle_node, "Remove a cycle described by a key")
	  .def("get_cycle_label", &figure::get_cycle_label, "Return a key for the cycle described by a string")
	  .def("get_cycle", do_get_cycle, do_get_cycle_overloads("Return the cycle node for a given key"))
	  .def("get_real_line", &figure::get_real_line, "Return a key for the real line")
	  .def("get_infinity", &figure::get_infinity, "Return a key for the infinity")
	  .def("get_point_metric", &figure::get_point_metric, "Return the metric of the point space")
	  .def("get_cycle_metric", &figure::get_cycle_metric, "Return the metric of the cycle space")
	  .def("reset_figure", &figure::reset_figure, "Delete all info from the figure")
	  .def("get_all_keys", make_function(&figure::get_all_keys,  default_call_policies(),
										 (boost::python::arg("mingen")=GHOST_GEN+1,
										  boost::python::arg("maxgen")=GHOST_GEN)),"Obtain all keys to cycles in the chosen range of generations")
	  .def("get_all_keys_sorted", make_function(&figure::get_all_keys_sorted,  default_call_policies(),
										 (boost::python::arg("mingen")=GHOST_GEN+1,
										  boost::python::arg("maxgen")=GHOST_GEN)),"Obtain all keys to cycles in the chosen range of generations"
		   " sorted by the generation number")
	  .def("asy_draw", do_asy_draw,  do_asy_draw_overloads("Produce a string with Asymptote command to draw the figure"))
	  .def("asy_print", do_asy_print,  do_asy_print_overloads("Print a string with Asymptote command to draw the figure"))
	  .def("asy_write", do_asy_write,  do_asy_write_overloads("Write a PS or PDF representation of the figure"))
	  .def("set_asy_style", &figure::set_asy_style, "Set an Asymptote option string for a particular cycle")
	  .def("get_asy_style", &figure::get_asy_style, "Obtain the Asymptote option string for a particular cycle")
	  .def("evalf", do_evalf, do_evalf_overloads("Float evaluation of the figure"))
	  .def("string", figure_to_string, "Output cycle as a string")
	  .def("check_rel", &figure::check_rel,check_rel_overloads("Make a chek of a relation between two cycles in the figure"))
	  .def("check_rel",do_check_rel, do_check_rel_overloads("Make a chek of a relation between two cycles in the figure"))
	  .def("asy_animate",do_asy_animate, do_asy_animate_overloads("Animate the figure with a list of parameter's values"))
	  .def("arrangement_write",&figure::arrangement_write,arrangement_write_overloads("Write file for visualisation of a 3D arrangement"))
	  .def("arrangement_visualise", do_arrangement_visualise, do_arrangement_visualise_overloads("Make a visualisation of a 3D arrangement"))
	  .def("get_dim",&figure::get_dim, "Return the dimensionality of the figure")
	  .def("freeze",&figure::freeze, "Prevent cycle in nodes from evaluation")
	  .def("unfreeze",&figure::unfreeze, "Allow cycle in nodes to be evaluated")
	  .def("set_float_eval",&figure::set_float_eval, "Force float evaluation of cycles parameters")
	  .def("set_exact_eval",&figure::set_exact_eval, "Use exact arithmetics for evaluation of cycles parameters")
;

  class_<cycle_relation, bases<basic> >
	  ("cycle_relation",
	   "The class describing relations of cycles",
	   no_init)

	  .def(init<>())
	  ;

	  //  def("figure",do_init_with_llist_figure,"Inititialise a figure from a Python list of metric's diagonal elemets");
  def("is_orthogonal", &is_orthogonal, is_orthogonal_overloads("Make cycle relation to be orthogonal"));
  def("is_f_orthogonal", &is_f_orthogonal, is_f_orthogonal_overloads("Make cycle relation to be focal orthogonal"));
  def("is_different", &is_different, is_different_overloads("Make cycle relation to be different"));
  def("is_adifferent", &is_adifferent, is_adifferent_overloads("Make cycle relation to be almost different"));
  def("is_tangent", &is_tangent, is_tangent_overloads("Make cycle relation to be tangent"));
  def("is_tangent_i", &is_tangent_i, is_tangent_i_overloads("Make cycle relation to be tangent"));
  def("is_tangent_o", &is_tangent_o, is_tangent_o_overloads("Make cycle relation to be tangent"));
  def("is_real_cycle", &is_real_cycle, is_real_cycle_overloads("Make the circle to be real"));
  def("only_reals", &only_reals, only_reals_overloads("Check that all coefficients are reals"));
  def("product_nonpositive", &product_nonpositive, product_nonpositive_overloads("Make the cycle product with another cycle (ot itself) to be nonpositive (or nonnegative)"));
  def("make_angle", &make_angle, "Cycle relation to make the given intersection angle");
  def("cycle_power", &cycle_power, "Cycle relation to have given Steiner power");
  def("tangential_distance", &tangential_distance, "Cycle relation to have given tangential distance");
  def("cross_t_distance", &cross_t_distance, "Cycle relation to have given tangential distance");
  def("moebius_transform", moebius_transform_bpl, "Cycle relation to make the given intersection angle");
  def("sl2_transform", sl2_transform_bpl, "Cycle relation to make the given intersection angle");
  def("midpoint_constructor", do_midpoint, "Creates a figure, defining the midpoint of variable000 and variable001 with respect to infinity at variable002");
  def("cycle_orthogonal", &cycle_orthogonal, "The expression to for orthogonality of cycles");
  def("figure_debug_on", &figure_debug_on, "Swith debug output on");
  def("figure_debug_off", &figure_debug_off, "Swith debug output off");
  def("figure_ask_debug_status", &figure_ask_debug_status, "Ask if debug output is on");
  def("show_asy_on", show_asy_on, "Switch on visualisation of Asymptote output");
  def("show_asy_off", show_asy_off, "Switch off visualisation of Asymptote output");

} // !figure_wrap()

} // !namespace pyginac

// The pyGiNaC wrapper for ensembles of interrelated cycles in non-Euclidean geometry
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
