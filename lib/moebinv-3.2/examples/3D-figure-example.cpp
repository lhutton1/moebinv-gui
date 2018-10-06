/* \subsection{Three-dimensional examples}                                  */
/* \label{sec:an-example-calc}                                              */
/*                                                                          */
/*                                                                          */
/* The most of the library functionality (except graphical methods) is      */
/* literally preserved for quadrics in arbitrary dimensions. We             */
/* demonstrate this on the following stereometric problem of                */
/* \href{https://en.wikipedia.org/wiki/Problem_of_Apollonius}{Apollonius    */
/*   type}, cf.~\cite{FillmoreSpringer00a}*{\S~8}. Let four spheres of      */
/* equal radii \(R\) %\(\frac{\sqrt{3}}{2}\)                                */
/* have centres at four points \((1,1,1)\), \((-1,-1,1)\), \((-1,1,-1)\),   */
/* \((1,-1,-1)\). These points are vertices of a regular                    */
/* \href{https://en.wikipedia.org/wiki/Platonic_solid}{tetrahedron} and     */
/* are every other vertices of a cube with the diagonal \(2\sqrt{3}\).      */
/*                                                                          */
/* There are two obvious spheres with the centre at the                     */
/* origin \((0,0,0)\) touching all four given spheres, they have radii      */
/* \(R+\sqrt{3}\) and \(\sqrt{3}-R\). Are there any others?                 */
/*                                                                          */
/*                                                                          */
/* We start from the standard initiation and define the metric of three     */
/* dimensional Euclidean space.                                             */
/*                                                                          */
/* <3D-figure-example.cpp>=                                                 */
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


/* Then we introduce the unknown cycle by the four tangency                 */
/* conditions to given spheres. We also put two conditions to rule out      */
/* non-geometric solutions: [[is_real_cycle]] checks that the radius is     */
/* real, [[only_reals]] requires that all coefficients are real.            */
/*                                                                          */
/* <3D-figure-example.cpp>=                                                 */
        realsymbol N3("N3");
        F.add_cycle_rel(lst{is_tangent(P1), is_tangent(P2), is_tangent(P3),is_tangent(P4)
                                                /* Tests below forbid all spheres with symbolic parameters */
                                                //, only_reals(N3), is_real_cycle(N3)
                         }, N3);
/* Then we output the solutions and their radii.                            */
/*                                                                          */
/* <3D-figure-example.cpp>=                                                 */
        lst L=ex_to<lst>(F.get_cycles(N3));
        cout << L.nops() << " spheres found" << endl;
        for (auto x: L)
                cout << "Sphere: " << ex_to<cycle>(x).normal()
                 << ", radius sq: " << (ex_to<cycle>(x).det()).normal()
                 <<endl;
        return 0;
}

