/* \subsection{Animated cycle}                                              */
/* \label{sec:animated-cycle}                                               */
/*                                                                          */
/* We use the similar construction to make an animation.                    */
/*                                                                          */
/* <hello-cycle-anim.cpp>=                                                  */
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

/* It is preferable to [[freeze]] a figure with a symbolic parameter in     */
/* order to avoid useless but expensive symbolic computations. It will be   */
/* automatically [[unfreeze]] by [[asy_animate]] method below.              */
/*                                                                          */
/* <hello-cycle-anim.cpp>=                                                  */
        figure F=figure().freeze();
        symbol t("t");
/* This time the point [[A]] on the figure depends from the above parameter */
/* [[t]] and the point [[B]] is fixed as before.                            */
/*                                                                          */
/* <hello-cycle-anim.cpp>=                                                  */
        ex A=F.add_point(lst{-1*t,.5*t+.5},"A");
        ex B=F.add_point(lst{1,1.5},"B");

/* The Lobachevsky line [[a]] is defined exactly as in the previous         */
/* example but is implicitly (through [[A]]) depending on [[t]] now.        */
/*                                                                          */
/* <hello-cycle-anim.cpp>=                                                  */
        ex a=F.add_cycle_rel(lst{is_orthogonal(A),is_orthogonal(B),is_orthogonal(F.get_real_line())},"a");

/* The new straight line [[b]] is defined as a cycle passing                */
/* (orthogonal to) the point at infinity. It is accessible by               */
/* [[get_infinity]] method.                                                 */
/*                                                                          */
/* <hello-cycle-anim.cpp>=                                                  */
        ex b=F.add_cycle_rel(lst{is_orthogonal(A),is_orthogonal(B),is_orthogonal(F.get_infinity())},"b");
/* Now we define the set of values for the parameter [[t]] which will       */
/* be used for substitution into the figure.                                */
/*                                                                          */
/* <hello-cycle-anim.cpp>=                                                  */
        lst val;
        for (int i=0; i<40; ++i)
                val.append(t==numeric(i+2,30));

/* Finally animations in different formats are created similarly to the     */
/* static picture from the previous example.                                */
/*                                                                          */
/* <hello-cycle-anim.cpp>=                                                  */
        F.asy_animate(val,500,-2.2,3,-2,2,"lobachevsky-anim","mng");
        F.asy_animate(val,300,-2.2,3,-2,2,"lobachevsky-anim","pdf");
        return 0;
}
