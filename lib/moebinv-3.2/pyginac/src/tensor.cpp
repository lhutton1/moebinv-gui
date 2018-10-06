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
#include <boost/python/def.hpp>
#include <boost/python/overloads.hpp>

namespace pyginac {

namespace {

BOOST_PYTHON_FUNCTION_OVERLOADS(lorentz_g_ol, lorentz_g, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(lorentz_eps_ol, lorentz_eps, 4, 5)

} // !namespace (unnamed)

void
wrap_tensor(void)
{
    using namespace boost::python;
    using namespace GiNaC;
    
    class_<tensor, bases<basic> >
      ("tensor","This class holds one of GiNaC's predefined special tensors such as the"
       "delta and the metric tensors. They are represented without indices."
       "To attach indices to them, wrap them in an object of class indexed.");
			            
    def("delta_tensor", delta_tensor,
	"Create a delta tensor with specified indices. The indices must be of class"
	"idx or a subclass. The delta tensor is always symmetric and its trace is"
	"the dimension of the index space.");

    def("metric_tensor", metric_tensor,
	"Create a symmetric metric tensor with specified indices. The indices"
	"must be of class varidx or a subclass. A metric tensor with one"
	"covariant and one contravariant index is equivalent to the delta tensor.");

    def("lorentz_g", lorentz_g, 
	lorentz_g_ol("Create a Minkowski metric tensor with specified indices. The indices"
		     "must be of class varidx or a subclass. The Lorentz metric is a symmetric"
		     "tensor with a matrix representation of diag(1,-1,-1,...) (negative"
		     "signature, the default) or diag(-1,1,1,...) (positive signature)."));

    def("spinor_metric", spinor_metric,
	"Create a spinor metric tensor with specified indices. The indices must be"
	"of class spinidx or a subclass and have a dimension of 2. The spinor"
	"metric is an antisymmetric tensor with a matrix representation of"
	"[[ [[ 0, 1 ]], [[ -1, 0 ]] ]].");

    ex (*epsilon_tensor2)(const ex&, const ex&) = &epsilon_tensor;
    ex (*epsilon_tensor3)(const ex&, const ex&, const ex&) = &epsilon_tensor;
    
    def("epsilon_tensor", epsilon_tensor2,
	"Create an epsilon tensor in a Euclidean space with two indices. The"
	"indices must be of class idx or a subclass, and there must be as"
	"many (2 or 3) of them as their dimension is.");
    def("epsilon_tensor", epsilon_tensor3,
	"Create an epsilon tensor in a Euclidean space with two indices. The"
	"indices must be of class idx or a subclass, and there must be as"
	"many (2 or 3) of them as their dimension is.");
  
    def("lorentz_eps", lorentz_eps,
	lorentz_eps_ol("Create an epsilon tensor in a Minkowski space with four indices. The"
		       "indices must be of class varidx or a subclass, and have a dimension of 4."));

} 

} // !namespace pyginac
