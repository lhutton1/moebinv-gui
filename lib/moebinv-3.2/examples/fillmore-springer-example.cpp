/* \subsection{Numerical relations}                                         */
/* \label{sec:numerical-relations}                                          */
/*                                                                          */
/*                                                                          */
/* To illustrate the usage of relations with numerical parameters we are    */
/* solving the following problem                                            */
/* from~\cite{FillmoreSpringer00a}*{Problem~A}:                             */
/* \begin{quote}                                                            */
/*   Find the cycles having (all three conditions):                         */
/*   \begin{itemize}                                                        */
/*   \item tangential distance \(7\) from the circle                        */
/*     \begin{displaymath}                                                  */
/*       (u-7)^2+(v-1)^2=2^2;                                               */
/*     \end{displaymath}                                                    */
/*   \item angle \(\arccos \frac{4}{5}\) with the circle                    */
/*     \begin{displaymath}                                                  */
/*       (u-5)^2+(v-3)^2=5^2;                                               */
/*     \end{displaymath}                                                    */
/*   \item centres lying on the line                                        */
/*     \begin{displaymath}                                                  */
/*       \frac{5}{13} u + \frac{12}{13} v=0.                                */
/*     \end{displaymath}                                                    */
/*   \end{itemize}                                                          */
/* \end{quote}                                                              */
/* The statement of the problem uses orientation of cycles. Geometrically   */
/* it is given by the inward or outward direction of the normal. In our     */
/* library the orientation represented by the direction of the vector in    */
/* the projective space, it changes to the opposite if the vector is        */
/* multiplied by \(-1\).                                                    */
/*                                                                          */
/*                                                                          */
/* The start of of our code is similar to the previous one.                 */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
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
        ex sign=-numeric(1);
        varidx nu(symbol("nu", "\\nu"), 2);
        ex e = clifford_unit(nu, diag_matrix(lst{-numeric(1),sign}));
        figure F(e);

/* Now we define three circles given in the problem statement above.        */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
        ex A=F.add_cycle(cycle(lst{numeric(7),numeric(1)},e,numeric(4)),"A");
        ex B=F.add_cycle(cycle(lst{numeric(5),numeric(3)},e,numeric(25)),"B");
        ex C=F.add_cycle(cycle(numeric(0),lst{numeric(5,13),numeric(12,13)},0,e),"C");

/* All given data will be drawn in black inc.                               */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
        F.set_asy_style(A,"rgb(0,0,0)");
        F.set_asy_style(B,"rgb(0,0,0)");
        F.set_asy_style(C,"rgb(0,0,0)");

/* The solution [[D]] is a circle defined by the three above                */
/* conditions. The solution will be drawn in red.                           */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
        realsymbol D("D"), T("T");
 F.add_cycle_rel(lst{tangential_distance(A,true,numeric(7)), // The tangential distance to [[A]] is  7
                                                         make_angle(B,true,numeric(4,5)), // The angle with [[B]] is  arccos(4/5)
                                                         is_orthogonal(C), // If the centre is on [[C]], then [[C]] and [[D]] are orthogonal
                         is_real_cycle(D)}, D); // We require [[D]] be a real circle, as there are two imaginary solutions as well
        F.set_asy_style(D,"rgb(0.7,0,0)");
/* The output tells parameters of two solutions:                            */
/* \begin{verbatim}                                                         */
/*   Solutions: {(-1.0, [0,0]~D, 0.99999999999999999734),                   */
/* (-0.0069444444444444444444, [-0.089285714285714285705,0.037202380952380952383]~D, -1.0)} */
/* \end{verbatim}                                                           */
/* Here, as in [[cycle]] library, the set of four numbers \((k,[l,n],m)\)   */
/* represent the circle equation \(k(u^2+v^2)-2lu-2nv+m=0\).                */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
    cout << "Solutions: "<< F.get_cycles(D).evalf() << endl;

/* To visualise the tangential distances we may add the joint tangent       */
/* lines to the figure. Some solutions are lines with imaginary             */
/* coefficients, to avoid them we use [[only_reals]] condition. The         */
/* tangents will be drawn in blue inc.                                      */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
        F.add_cycle_rel(lst{is_tangent_i(D),is_tangent_i(A),is_orthogonal(F.get_infinity()),only_reals(T)},T);
        F.set_asy_style(T,"rgb(0,0,0.7)");
/* Finally we draw the picture, see                                         */
/* Fig.~\ref{fig:illustr-fillm-spring}, which shall be compared             */
/* with~\cite{FillmoreSpringer00a}*{Fig.~1}.                                */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
        F.asy_write(400,-4,20,-12.5,9,"fillmore-springer-example");

/* Out of curiosity we may want to know that is square of tangents          */
/* intervals which are separate circles [[A]], [[D]]. The output is:        */
/* \begin{verbatim}                                                         */
/* Sq. cross tangent distance: {41.000000000000000003,-7.571428571428571435} */
/* \end{verbatim}                                                           */
/* Thus one solution does have such tangents with length \(\sqrt{41}\),     */
/* and for the second solution such tangents are imaginary since the        */
/* square is negative. This happens because one solution [[D]] intersects [[A]]. */
/*                                                                          */
/* <fillmore-springer-example.cpp>=                                         */
        cout << "Sq. cross tangent distance: " << F.measure(D,A,sq_cross_t_distance_is).evalf() << endl;
   return 0;
}
