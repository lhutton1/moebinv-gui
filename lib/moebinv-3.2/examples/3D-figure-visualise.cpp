/* For the numerical value \(R=\frac{\sqrt{3}}{2}\), the program found      */
/* \(16\) different solutions which satisfy to [[is_real_cycle]] and        */
/* [[only_reals]] conditions. If we omit these conditions then additional   */
/* \(16\) imaginary spheres will be producing (\(32\) in total).            */
/*                                                                          */
/* For the symbolic radii \(R\) again \(32\) different spheres are          */
/* found. The condition [[only_reals]] leaves only two obvious spheres,     */
/* discussed at the beginning of the subsection. This happens because for   */
/* some value of \(R\) coefficient of other spheres may turn to be          */
/* complex. Finally, if we use the condition [[is_real_cycle]], then no     */
/* sphere passes it---the square of its radius may become negative for      */
/* some \(R\).                                                              */
/*                                                                          */
/*                                                                          */
/* For visualisation we can partially re-use the previous code.             */
/*                                                                          */
/* <3D-figure-visualise.cpp>=                                               */
/* The following two chunks are shared with the next example.               */
/*                                                                          */
/* <3D-figure-example-common>=                                              */
/* \section{License}                                                        */
/* \label{sec:license}                                                      */
/* This programme is distributed under GNU GPLv3~\cite{GNUGPL}.             */
/*                                                                          */
/* <license>=                                                               */
// The library for ensembles of interrelated cycles in non-Euclidean geometry
//
//  Copyright (C) 2014-2016 Vladimir V. Kisil
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

#include "figure.h"
/* To save keystrokes, we use the following [[namespace]]s.                 */
/*                                                                          */
/* <using all namespaces>=                                                  */
using namespace std;
using namespace GiNaC;
using namespace MoebInv;
int main(){
        ex e3D = clifford_unit(varidx(symbol("lam"), 3), diag_matrix(lst{-1,-1,-1})); // Metric for 3D space
        possymbol R("R");
        figure F(e3D);

/* Then we put four given spheres to the figure. They are defined by        */
/* their centres and square of radii.                                       */
/*                                                                          */
/* <3D-figure-example-common>=                                              */
        /* Numerical radii */
        /*      ex P1=F.add_cycle(cycle(lst{1,1,1}, e3D, numeric(3,4)), "P1");
        ex P2=F.add_cycle(cycle(lst{-1,-1,1}, e3D, numeric(3,4)), "P2");
        ex P3=F.add_cycle(cycle(lst{1,-1,-1}, e3D, numeric(3,4)), "P3");
        ex P4=F.add_cycle(cycle(lst{-1,1,-1}, e3D, numeric(3,4)), "P4");
        */
        ex P1=F.add_cycle(cycle(lst{1,1,1}, e3D, pow(R,2)), "P1");
        ex P2=F.add_cycle(cycle(lst{-1,-1,1}, e3D, pow(R,2)), "P2");
        ex P3=F.add_cycle(cycle(lst{1,-1,-1}, e3D, pow(R,2)), "P3");
        ex P4=F.add_cycle(cycle(lst{-1,1,-1}, e3D, pow(R,2)), "P4");


/* To simplify the structure we eliminate spheres which are different       */
/* only up to the rotational symmetry of the initial set-up. To this end    */
/* we explicitly specify inner or outer tangency for different spheres.     */
/*                                                                          */
/* <3D-figure-visualise.cpp>=                                               */
        realsymbol N0("N0"), N1("N1"), N2("N2"), N3("N3"),  N4("N4");
        F.add_cycle_rel(lst{is_tangent_o(P1), is_tangent_o(P2), is_tangent_o(P3),is_tangent_o(P4),
                                is_real_cycle(N0), only_reals(N0)}, N0);
        F.add_cycle_rel(lst{is_tangent_o(P1), is_tangent_o(P2), is_tangent_o(P3),is_tangent_i(P4),
                                is_real_cycle(N1), only_reals(N1)}, N1);
        F.add_cycle_rel(lst{is_tangent_o(P1), is_tangent_o(P2), is_tangent_i(P3),is_tangent_i(P4),
                                is_real_cycle(N2), only_reals(N2)}, N2);
        F.add_cycle_rel(lst{is_tangent_o(P1), is_tangent_i(P2), is_tangent_i(P3),is_tangent_i(P4),
                                is_real_cycle(N3), only_reals(N3)}, N3);

/* Now we save the arrangement for the numerical value \(R^2=\frac{3}{4}\). */
/*                                                                          */
/* <3D-figure-visualise.cpp>=                                               */
        F.subs(R==sqrt(ex_to<numeric>(3))/2).arrangement_write("appolonius");
        return 0;
}
