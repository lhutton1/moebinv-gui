/* \subsection{An illustration of the modular group action}                 */
/* \label{sec:an-illustr-modul}                                             */
/*                                                                          */
/* The library allows to build figures out of cycles which are obtained     */
/* from each other by means of FLT. We are going to                         */
/* illustrate this by the action of the modular group                       */
/* \(\mathrm{SL}_2(\mathbb{Z})\) on a single                                */
/* circle~\cite{StewartTall02a}*{\S~14.4}. We repeatedly apply FLT \(T=     */
/* \begin{pmatrix}                                                          */
/*   1&1\\0&1                                                               */
/* \end{pmatrix}\)                                                          */
/* for translations and \(S=                                                */
/* \begin{pmatrix}                                                          */
/*   0&-1\\1&0                                                              */
/* \end{pmatrix}\) for the inversion in the unit circle.                    */
/*                                                                          */
/*                                                                          */
/* Here is the standard start of a programme with some additional           */
/* variables being initialised.                                             */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
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
        char buffer [50];
        int steps=3, trans=15;
        double epsilon=0.00001; // square of radius for a circle to be ignored
        figure F;

/* We will use the metric associated to the figure, it can be extracted     */
/* by [[get_point_metric]] method.                                          */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
        ex e=F.get_point_metric();

/* Firstly, we add to the figure an initial cycle and, then, add new        */
/* generations of its shifts and reflections.                               */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
        ex a=F.add_cycle(cycle2D(lst{0,numeric(3,2)},e,numeric(1,4)),"a");
        ex c=F.add_cycle(cycle2D(lst{0,numeric(11,6)},e,numeric(1,36)),"c");
        for (int i=0; i<steps;++i) {

/* We want to shift all cycles in the previous                              */
/* generation. Their key are grasped by [[get_all_keys]] method.            */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
                lst L=ex_to<lst>(F.get_all_keys(2*i,2*i));
                if (L.nops() == 0) {
                        cout << "Terminate on iteration " << i << endl;
                        break;
                }
/* Each cycle with the collected key is shifted horizontally by an          */
/* integer \(t\) in range [\(-\)[[trans]],[[trans]]{}]. This done by        */
/* [[moebius_transform]] relations and it is our responsibility to          */
/* produce proper Clifford-valued entries to the matrix,                    */
/* see~\cite{Kisil05a}*{\S~2.1} for an advise.                              */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
                for (const auto& ck: L) {
                        lst L1=ex_to<lst>(F.get_cycles(ck));
                        for (auto x: L1) {
                                for (int t=-trans; t<=trans;++t) {
                                        sprintf (buffer, "%s-%dt%d",ex_to<symbol>(ck).get_name().c_str(),i,t);

/* We shift initial cycles by zero in order to have their copies in the this generation. */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
                                        if ((t !=0 || i ==0)

/* To simplify the picture we are skipping circles whose radii would be     */
/* smaller than the threshold.                                              */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
                                                && ! ((ex_to<cycle>(x).det()-(pow(t,2)-1)*epsilon).evalf()<0)){
                                                ex b=F.add_cycle_rel(moebius_transform(ck,true,
                                                                                                                           lst{dirac_ONE(),t*e.subs(e.op(1).op(0)==0),0,dirac_ONE()}),buffer);
/* We want the colour of a cycle reflect its generation, smaller cycles     */
/* also need to be drawn by a finer pen. This can be set for each cycle     */
/* by [[set_asy_style]] method.                                             */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
                                                sprintf (buffer, "rgb(0,0,%.2f)+%.3f" ,1-1/(i+1.),1/(i+1.5));
                                                F.set_asy_style(b,buffer);
                                        }
                                }
                        }
                }
/* Similarly, we collect all key from the previous generation cycles        */
/* to make their reflection in the unit circle.                             */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
                if (i<steps-1)
                        L=ex_to<lst>(F.get_all_keys(2*i+1,2*i+1));
                else
                        L=lst{};
                for (const auto& ck: L) {
                        sprintf (buffer, "%ss",ex_to<symbol>(ck).get_name().c_str());

/* This time we keep things simple and are using [[sl2_transform]]          */
/* relation, all Clifford algebra adjustments are taken by the              */
/* library. The drawing style is setup accordingly.                         */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
                        ex b=F.add_cycle_rel(sl2_transform(ck,true,lst{0,-1,1,0}),buffer);
                        sprintf (buffer, "rgb(0,0.7,%.2f)+%.3f" ,1-1/(i+1.),1/(i+1.5));
                        F.set_asy_style(b,buffer);
                }
        }
/* Finally, we draw the picture. This time we do not want cycles label      */
/* to appear, thus the last parameter [[with_labels]] of [[asy_write]] is   */
/* [[false]]. We also want to reduce the size of \Asymptote\ file and       */
/* will not print headers of cycles, thus specifying                        */
/* [[with_header=true]]. The remaining parameters are explicitly assigned   */
/* their default values.                                                    */
/*                                                                          */
/* <modular-group.cpp>=                                                     */
        ex u=F.add_cycle(cycle2D(lst{0,0},e,numeric(1)),"u");
        F.asy_write(300,-2.17,2.17,0,2,"modular-group","pdf",default_asy,default_label,true,false,0,"rgb(0,.9,0)+4pt",true,false);
        return 0;
}
