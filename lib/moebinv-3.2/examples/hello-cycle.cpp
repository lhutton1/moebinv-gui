/* \subsection{Hello, Cycle!}                                               */
/* \label{sec:hello-cycle}                                                  */
/*                                                                          */
/* This is a minimalist example showing how to obtain a simple drawing of   */
/* cycles in non-Euclidean geometry. Of course, we are starting from the    */
/* library header file.                                                     */
/*                                                                          */
/* <hello-cycle.cpp>=                                                       */
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

/* We declare the figure [[F]] which will be constructed with the           */
/* default elliptic metric in two dimensions.                               */
/*                                                                          */
/* <hello-cycle.cpp>=                                                       */
        figure F;
/* Next we define a couple of points [[A]] and [[B]]. Every point is        */
/* added to [[F]] by giving its explicit coordinates as a [[lst]] and a     */
/* string, which will be used to label the point. The returned value is a   */
/* \GiNaC\ expression of [[symbol]] class, which will be used as a key      */
/* of the respective point. All points are added to the zero generation.    */
/*                                                                          */
/* <hello-cycle.cpp>=                                                       */
        ex A=F.add_point(lst{-1,.5},"A");
        ex B=F.add_point(lst{1,1.5},"B");
/* Now we add a ``line'' in the Lobachevsky half-plane. It passes both      */
/* points [[A]] and [[B]] and is orthogonal to the real line. The real      */
/* line and the point at infinity were automatically added to [[F]] at      */
/* its initialisation. The real line is accessible as                       */
/* [[F.get_real_line()]] method in [[figure]] class. A cycle                */
/* passes a point if it is orthogonal to the cycle defined by this          */
/* point. Thus, the line is defined through a list of three                 */
/* orthogonalities~\citelist{\cite{Kisil06a} \cite{Kisil12a}*{Defn.~6.1}}   */
/* (other pre-defined relations between cycles are listed in                */
/* Section~\ref{sec:publ-meth-cycl}). We also supply a string to label      */
/* this cycle. The returned valued is a [[symbol]], which is a key for this */
/* cycle.                                                                   */
/*                                                                          */
/* <hello-cycle.cpp>=                                                       */
        ex a=F.add_cycle_rel(lst{is_orthogonal(A),is_orthogonal(B),is_orthogonal(F.get_real_line())},"a");
/* Now, we draw our figure to a file. Its format (e.g. EPS, PDF, PNG,       */
/* etc.) is determined by your default \Asymptote settings. This can be     */
/* overwritten if a format is explicitly requested, see examples below.     */
/* The output is shown at Figure~\ref{fig:lobachevky-line}.                 */
/*                                                                          */
/* <hello-cycle.cpp>=                                                       */
        F.asy_write(300,-3,3,-3,3,"lobachevsky-line");
        return 0;
}
