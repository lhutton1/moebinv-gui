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
		figure F1;
		idx I0(0,2), I1(1,2);

		F1.set_metric(metric_p, metric_h);
		//F1.set_metric(matrix(2,2,lst{-1,0,0,0}), matrix(2,2,lst{-1,0,0,1}));
		F1.save("/tmp/empty-par-hyp");

		cout << ex_to<clifford>(F1.get_point_metric()).get_metric(I0,I0)*ex_to<clifford>(F1.get_point_metric()).get_metric(I1,I1) << endl;
		cout << ex_to<clifford>(F1.get_cycle_metric()).get_metric(I0,I0)*ex_to<clifford>(F1.get_cycle_metric()).get_metric(I1,I1) << endl;

		figure F2=figure("/tmp/empty-par-hyp");
		cout << ex_to<clifford>(F2.get_point_metric()).get_metric(I0,I0)*ex_to<clifford>(F2.get_point_metric()).get_metric(I1,I1) << endl;
		cout << ex_to<clifford>(F2.get_cycle_metric()).get_metric(I0,I0)*ex_to<clifford>(F2.get_cycle_metric()).get_metric(I1,I1) << endl;
		
        return 0;
}

