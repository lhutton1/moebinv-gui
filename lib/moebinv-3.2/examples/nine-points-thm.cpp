/* \subsection{The nine-points theorem---conformal version}                 */
/* \label{sec:example:-nine-points}                                         */
/*                                                                          */
/* Here we present further usage of the library by an aesthetically         */
/* attractive example, see Section~\ref{sec:mathematical-results}.          */
/*                                                                          */
/*                                                                          */
/* The start of our file is minimalistic, we definitely need to             */
/* include the header of [[figure]] library.                                */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
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
        /* We define exact coordinates of points which will be used for our picture. */
        /*                                                                          */
        /* <initial data for drawing>=                                              */
                numeric x1(-10,10), y1(0,1), x2(10,10), y2(0,1), x3(-1,5), y3(-3,2), x4(1,2), y4(-5,2);
                int sign=-1;
        /* We declare the figure [[F]] which will be constructed.                   */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                figure F(lst{-1,sign});
        /* We will need several ``midpoints'' in our constructions, the             */
        /* corresponding figure [[midpoint_constructor]] is readily available       */
        /* from the library.                                                        */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                figure SF=ex_to<figure>(midpoint_constructor());

        /* Next we define vertices of the ``triangle'' [[A]], [[B]], [[C]] and      */
        /* the point [[N]] which will be an image if infinity. Every point is       */
        /* added to [[F]] by giving its explicit coordinates and a string, which    */
        /* will used to label it. The returned value is a \GiNaC\ expression of     */
        /* [[symbol]] class which will be used as the key of a respective           */
        /* point. All points are added to the zero generation.                      */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex A=F.add_point(lst{x1,y1},"A");
                ex B=F.add_point(lst{x2, y2},"B");
                ex C=F.add_point(lst{x3,y3},"C");
        /* There is the special point in the construction, which play the role      */
        /* of infinity. We first put this as cycle at infinity to make picture simple. */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex N=F.add_cycle(cycle_data(0,lst{0,0},1),"N");
        /* This is an alternative selection of point with [[N]] being at the        */
        /* centre of the triangle.                                                  */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                //Fully symmetric data
                // ex A=F.add_point(lst{-numeric(10,10},numeric(0,1)),"A")
                // ex B=F.add_point(lst{numeric(10,10},numeric(0,1)),"B")
                // ex C=F.add_point(lst{numeric(0,4},-numeric(1732050807,1000000000)),"C")
                // ex N=F.add_point(lst{numeric(0,4},-numeric(577350269,1000000000)),"N")

        /* Now we add ``sides'' of the triangle, that is cycles passing two         */
        /* vertices and [[N]]. A cycle passes a point if it is orthogonal to the    */
        /* cycle defined by this point. Thus, each side is defined through a list   */
        /* of three orthogonalities~\citelist{\cite{Kisil06a}                       */
        /*   \cite{Kisil12a}*{Defn.~6.1}}. We also supply a string to label this    */
        /* side. The returned valued is a [[symbol]] which is a key for this cycle. */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex a=F.add_cycle_rel(lst{is_orthogonal(B),is_orthogonal(C),is_orthogonal(N)},"a");
                ex b=F.add_cycle_rel(lst{is_orthogonal(A),is_orthogonal(C),is_orthogonal(N)},"b");
                ex c=F.add_cycle_rel(lst{is_orthogonal(A),is_orthogonal(B),is_orthogonal(N)},"c");
        /* We define the custom \Asymptote~\cite{Asymptote} drawing style for       */
        /* sides of the triangle: the dark blue ([[rgb]] colour (0,0,0.8)) and line thickness 1pt. */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                F.set_asy_style(a,"rgb(0,0,.8)+1");
                F.set_asy_style(b,"rgb(0,0,.8)+1");
                F.set_asy_style(c,"rgb(0,0,.8)+1");
        /* Now we drop ``altitudes'' in our triangle, that is again                 */
        /* provided through three orthogonality relations. They will be draw as     */
        /* dashed lines.                                                            */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                   ex ha=F.add_cycle_rel(lst{is_orthogonal(A),is_orthogonal(N),is_orthogonal(a)},"h_a");
                F.set_asy_style(ha,"dashed");
                ex hb=F.add_cycle_rel(lst{is_orthogonal(B),is_orthogonal(N),is_orthogonal(b)},"h_b");
                F.set_asy_style(hb,"dashed");
                ex hc=F.add_cycle_rel(lst{is_orthogonal(C),is_orthogonal(N),is_orthogonal(c)},"h_c");
                F.set_asy_style(hc,"dashed");

        /* We need the base of altitude [[ha]], which is the intersection points    */
        /* of the side [[a]]  and respective altitude [[ha]]. A point can be can    */
        /* be characterised as a cycle which is orthogonal to                       */
        /* itself~\citelist{\cite{Kisil12a}*{Defn.~5.13} \cite{Kisil06a}}. To       */
        /* define a relation of a cycle to itself we first need to define a         */
        /* symbol [[A1]] and then add a cycle with the key [[A1]] and the           */
        /* relation [[is_orthogonal]] to [[A1]]. Finally, there are two such        */
        /* points: the base of altitude and [[N]]. To exclude the second one we     */
        /* add the relation [[is_adifferent]] (``almost different'') to [[N]].      */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex A1=symbol("A_h");
         F.add_cycle_rel(lst{is_orthogonal(a),is_orthogonal(ha),is_orthogonal(A1),is_adifferent(N)},A1);
        /* Two other bases of altitude are defined in a similar manner.             */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex B1=symbol("B_h");
         F.add_cycle_rel(lst{is_orthogonal(b),is_orthogonal(hb),is_adifferent(N),is_orthogonal(B1)},B1);
                ex C1=symbol("C_h");
                F.add_cycle_rel(lst{is_adifferent(N),is_orthogonal(c),is_orthogonal(hc),is_orthogonal(C1)},C1);

        /* We add the cycle passing all three bases of altitudes.                   */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex p=F.add_cycle_rel(lst{is_orthogonal(A1),is_orthogonal(B1),is_orthogonal(C1)},"p");
                F.set_asy_style(p,"rgb(0,.8,0)+1");

        /* We build ``midpoint'' of the arc of [[a]] between [[B]] and              */
        /* [[C]]. To this end we use subfigure [[SF]] and supply the list of        */
        /* parameters [[B]], [[C]] and [[N]] (``infinity'') which are required      */
        /* by [[SF]].                                                               */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex A2=F.add_subfigure(SF,lst{B,C,N},"A_m");
        /* Similarly we build other two ``midpoints'', they all will belong to      */
        /* the cycle [[p]].                                                         */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex B2=F.add_subfigure(SF,lst{C,A,N},"B_m");
                ex C2=F.add_subfigure(SF,lst{A,B,N},"C_m");

        /* [[O]] is the intersection point of altitudes [[ha]] and [[hb]],          */
        /* again it is defined as a cycle with key [[O]] orthogonal to itself.      */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex O=symbol("O");
         F.add_cycle_rel(lst{is_orthogonal(ha),is_orthogonal(hb),is_orthogonal(O),is_adifferent(N)},O);

        /* We build three more ``midpoints'' which belong to [[p]] as well.         */
        /*                                                                          */
        /* <build medioscribed cycle>=                                              */
                ex A3=F.add_subfigure(SF,lst{O,A,N},"A_d");
                ex B3=F.add_subfigure(SF,lst{B,O,N},"B_d");
                ex C3=F.add_subfigure(SF,lst{C,O,N},"C_d");

                /* Now we want to check that the six additional points all belong to        */
                /* the build cycle [[p]]. The list of pre-defined conditions which may be   */
                /* checked is listed in Section~\ref{sec:check-relat-betw}.                 */
                /*                                                                          */
                /* <check the theorem>=                                                     */
                        cout << "Midpoint BC belongs to the cycle: " <<  F.check_rel(p,A2,cycle_orthogonal) << endl;
                        cout << "Midpoint AC belongs to the cycle: " <<  F.check_rel(p,B2,cycle_orthogonal) << endl;
                        cout << "Midpoint AB belongs to the cycle: " <<  F.check_rel(p,C2,cycle_orthogonal) << endl;
                        cout << "Midpoint OA belongs to the cycle: " << F.check_rel(p,A3,cycle_orthogonal) << endl;
                        cout << "Midpoint OB belongs to the cycle: " <<  F.check_rel(p,B3,cycle_orthogonal) << endl;
                        cout << "Midpoint OC belongs to the cycle: " <<  F.check_rel(p,C3,cycle_orthogonal) << endl;


/* We inscribe the cycle [[va]] into the triangle through the relation      */
/* [[is_tangent_i]] (that is ``tangent from inside'') and [[is_tangent_]]   */
/* (that is ``tangent from outside'')to sides of the triangle. We also      */
/* provide custom \Asymptote\ drawing style: dar red colour and line        */
/* thickness 0.5pt.                                                         */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        ex va=F.add_cycle_rel(lst{is_tangent_o(a),is_tangent_i(b),is_tangent_i(c)},"v_a");
        F.set_asy_style(va,"rgb(0.8,0,0)+.5");
/* Similarly we define two other tangent cycles: touching two sides         */
/* from inside and  the third from outside (the relation                    */
/* [[is_tangent_o]]). We also define custom \Asymptote\ styles for the      */
/* new cycles.                                                              */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        ex vb=F.add_cycle_rel(lst{is_tangent_i(a),is_tangent_o(b),is_tangent_i(c)},"v_b");
        F.set_asy_style(vb,"rgb(0.8,0,0)+.5");
        ex vc=F.add_cycle_rel(lst{is_tangent_i(a),is_tangent_i(b),is_tangent_o(c)},"v_c");
        F.set_asy_style(vc,"rgb(0.8,0,0)+.5");
        /* We also want to check the touching property between cycles:              */
        /*                                                                          */
        /* <check that cycles are tangent>=                                         */
                cout << "p and va are tangent: " <<  F.check_rel(p,va,check_tangent).evalf() << endl;
                cout << "p and vb are tangent: " <<  F.check_rel(p,vb,check_tangent).evalf() << endl;
                cout << "p and vc are tangent: " <<  F.check_rel(p,vc,check_tangent).evalf() << endl;


/* Now, we draw our figure to the PDF and PNG files, it is shown at         */
/* Figure~\ref{fig:illustr-conf-nine}.                                      */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        F.asy_write(300,-3.1,2.4,-3.6,1.3,"nine-points-thm-plain", "pdf");
        F.asy_write(600,-3.1,2.4,-3.6,1.3,"nine-points-thm-plain", "png");
/* We also can modify a cycle at zero level by [[move_point]]. This         */
/* time we restore the initial value of [[N]] as a debug check: this is a   */
/* transition from a pre-defined [[cycle]] given above to a point           */
/* (which is a calculated object due to the internal representation).       */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        F.move_point(N,lst{numeric(1,2),-numeric(5,2)});
        cerr << F << endl;
        F.asy_draw(cout,cerr,"",-3.1,2.4,-3.6,1.3);

        F.asy_write(300,-3.1,2.4,-3.6,1.3,"nine-points-thm", "pdf");
        F.asy_write(600,-3.1,2.4,-3.6,1.3,"nine-points-thm", "png");
        /* Now we want to check that the six additional points all belong to        */
        /* the build cycle [[p]]. The list of pre-defined conditions which may be   */
        /* checked is listed in Section~\ref{sec:check-relat-betw}.                 */
        /*                                                                          */
        /* <check the theorem>=                                                     */
                cout << "Midpoint BC belongs to the cycle: " <<  F.check_rel(p,A2,cycle_orthogonal) << endl;
                cout << "Midpoint AC belongs to the cycle: " <<  F.check_rel(p,B2,cycle_orthogonal) << endl;
                cout << "Midpoint AB belongs to the cycle: " <<  F.check_rel(p,C2,cycle_orthogonal) << endl;
                cout << "Midpoint OA belongs to the cycle: " << F.check_rel(p,A3,cycle_orthogonal) << endl;
                cout << "Midpoint OB belongs to the cycle: " <<  F.check_rel(p,B3,cycle_orthogonal) << endl;
                cout << "Midpoint OC belongs to the cycle: " <<  F.check_rel(p,C3,cycle_orthogonal) << endl;
        /* We also want to check the touching property between cycles:              */
        /*                                                                          */
        /* <check that cycles are tangent>=                                         */
                cout << "p and va are tangent: " <<  F.check_rel(p,va,check_tangent).evalf() << endl;
                cout << "p and vb are tangent: " <<  F.check_rel(p,vb,check_tangent).evalf() << endl;
                cout << "p and vc are tangent: " <<  F.check_rel(p,vc,check_tangent).evalf() << endl;

/* And now we use [[move_point]] to change coordinates of the point         */
/* (without a change of its type).                                          */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        F.move_point(N,lst{numeric(4,2),-numeric(5,2)});
        F.asy_write(300,-3.1,2.4,-3.6,1.3,"nine-points-thm2");
        /* Now we want to check that the six additional points all belong to        */
        /* the build cycle [[p]]. The list of pre-defined conditions which may be   */
        /* checked is listed in Section~\ref{sec:check-relat-betw}.                 */
        /*                                                                          */
        /* <check the theorem>=                                                     */
                cout << "Midpoint BC belongs to the cycle: " <<  F.check_rel(p,A2,cycle_orthogonal) << endl;
                cout << "Midpoint AC belongs to the cycle: " <<  F.check_rel(p,B2,cycle_orthogonal) << endl;
                cout << "Midpoint AB belongs to the cycle: " <<  F.check_rel(p,C2,cycle_orthogonal) << endl;
                cout << "Midpoint OA belongs to the cycle: " << F.check_rel(p,A3,cycle_orthogonal) << endl;
                cout << "Midpoint OB belongs to the cycle: " <<  F.check_rel(p,B3,cycle_orthogonal) << endl;
                cout << "Midpoint OC belongs to the cycle: " <<  F.check_rel(p,C3,cycle_orthogonal) << endl;
        /* We also want to check the touching property between cycles:              */
        /*                                                                          */
        /* <check that cycles are tangent>=                                         */
                cout << "p and va are tangent: " <<  F.check_rel(p,va,check_tangent).evalf() << endl;
                cout << "p and vb are tangent: " <<  F.check_rel(p,vb,check_tangent).evalf() << endl;
                cout << "p and vc are tangent: " <<  F.check_rel(p,vc,check_tangent).evalf() << endl;


/* Then, we move the cycle [[N]] to represent the point at infinity [[(0,lst{0,0},1)]], */
/* thus the drawing becomes the classical Nine Points Theorem in            */
/* Euclidean geometry.                                                      */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        F.move_cycle(N, cycle_data(0,lst{0,0},1));
        F.asy_write(300,-3.1,2.4,-3.6,1.3,"nine-points-thm1");
        /* Now we want to check that the six additional points all belong to        */
        /* the build cycle [[p]]. The list of pre-defined conditions which may be   */
        /* checked is listed in Section~\ref{sec:check-relat-betw}.                 */
        /*                                                                          */
        /* <check the theorem>=                                                     */
                cout << "Midpoint BC belongs to the cycle: " <<  F.check_rel(p,A2,cycle_orthogonal) << endl;
                cout << "Midpoint AC belongs to the cycle: " <<  F.check_rel(p,B2,cycle_orthogonal) << endl;
                cout << "Midpoint AB belongs to the cycle: " <<  F.check_rel(p,C2,cycle_orthogonal) << endl;
                cout << "Midpoint OA belongs to the cycle: " << F.check_rel(p,A3,cycle_orthogonal) << endl;
                cout << "Midpoint OB belongs to the cycle: " <<  F.check_rel(p,B3,cycle_orthogonal) << endl;
                cout << "Midpoint OC belongs to the cycle: " <<  F.check_rel(p,C3,cycle_orthogonal) << endl;
        /* We also want to check the touching property between cycles:              */
        /*                                                                          */
        /* <check that cycles are tangent>=                                         */
                cout << "p and va are tangent: " <<  F.check_rel(p,va,check_tangent).evalf() << endl;
                cout << "p and vb are tangent: " <<  F.check_rel(p,vb,check_tangent).evalf() << endl;
                cout << "p and vc are tangent: " <<  F.check_rel(p,vc,check_tangent).evalf() << endl;

/* We can draw the same figures in the hyperbolic metric as well. The       */
/* checks show that the nine-point theorem is still valid!                  */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        F.move_cycle(N, cycle_data(0,lst{0,0},1));
        F.set_metric(diag_matrix(lst{-1,1}));
        F.asy_write(300,-3.1,2.4,-3.6,1.3,"nine-points-thm-plain-hyp");
        /* Now we want to check that the six additional points all belong to        */
        /* the build cycle [[p]]. The list of pre-defined conditions which may be   */
        /* checked is listed in Section~\ref{sec:check-relat-betw}.                 */
        /*                                                                          */
        /* <check the theorem>=                                                     */
                cout << "Midpoint BC belongs to the cycle: " <<  F.check_rel(p,A2,cycle_orthogonal) << endl;
                cout << "Midpoint AC belongs to the cycle: " <<  F.check_rel(p,B2,cycle_orthogonal) << endl;
                cout << "Midpoint AB belongs to the cycle: " <<  F.check_rel(p,C2,cycle_orthogonal) << endl;
                cout << "Midpoint OA belongs to the cycle: " << F.check_rel(p,A3,cycle_orthogonal) << endl;
                cout << "Midpoint OB belongs to the cycle: " <<  F.check_rel(p,B3,cycle_orthogonal) << endl;
                cout << "Midpoint OC belongs to the cycle: " <<  F.check_rel(p,C3,cycle_orthogonal) << endl;
        /* We also want to check the touching property between cycles:              */
        /*                                                                          */
        /* <check that cycles are tangent>=                                         */
                cout << "p and va are tangent: " <<  F.check_rel(p,va,check_tangent).evalf() << endl;
                cout << "p and vb are tangent: " <<  F.check_rel(p,vb,check_tangent).evalf() << endl;
                cout << "p and vc are tangent: " <<  F.check_rel(p,vc,check_tangent).evalf() << endl;

        F.move_point(N,lst{numeric(1,2),-numeric(5,2)});
        F.asy_write(300,-3.1,2.4,-3.6,1.3,"nine-points-thm-hyp", "pdf");
        F.asy_write(600,-3.1,2.4,-3.6,1.3,"nine-points-thm-hyp","png");
        /* Now we want to check that the six additional points all belong to        */
        /* the build cycle [[p]]. The list of pre-defined conditions which may be   */
        /* checked is listed in Section~\ref{sec:check-relat-betw}.                 */
        /*                                                                          */
        /* <check the theorem>=                                                     */
                cout << "Midpoint BC belongs to the cycle: " <<  F.check_rel(p,A2,cycle_orthogonal) << endl;
                cout << "Midpoint AC belongs to the cycle: " <<  F.check_rel(p,B2,cycle_orthogonal) << endl;
                cout << "Midpoint AB belongs to the cycle: " <<  F.check_rel(p,C2,cycle_orthogonal) << endl;
                cout << "Midpoint OA belongs to the cycle: " << F.check_rel(p,A3,cycle_orthogonal) << endl;
                cout << "Midpoint OB belongs to the cycle: " <<  F.check_rel(p,B3,cycle_orthogonal) << endl;
                cout << "Midpoint OC belongs to the cycle: " <<  F.check_rel(p,C3,cycle_orthogonal) << endl;
        /* We also want to check the touching property between cycles:              */
        /*                                                                          */
        /* <check that cycles are tangent>=                                         */
                cout << "p and va are tangent: " <<  F.check_rel(p,va,check_tangent).evalf() << endl;
                cout << "p and vb are tangent: " <<  F.check_rel(p,vb,check_tangent).evalf() << endl;
                cout << "p and vc are tangent: " <<  F.check_rel(p,vc,check_tangent).evalf() << endl;

        //F.set_metric(diag_matrix(lst{-1,0}));
        //F.asy_write(300,-3.1,2.4,-3.6,1.3,"nine-points-thm-par", "pdf");

/* Finally, we produce an animation, which illustrate the transition        */
/* from the traditional nine-point theorem to its conformal version. To     */
/* this end we return to the elliptic metric and freeze the figure. This    */
/* can be time-consuming and may be not performed by default.               */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
         if (true) {
                F.set_metric(diag_matrix(lst{-1,-1}));
                F.freeze();

/* We define a symbolic parameter [[t]] and make the point [[N]] depends on it. */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
                realsymbol t("t");
                F.move_point(N,lst{(1.0+t)/2.0,-(5.0+t)/2.0});

/* Then, the range of values [[val]] for the parameter [[t]] and then       */
/* produce an animation based on these values. The resulting animation is   */
/* presented on the Fig.~\ref{fig:nine-points-anim}.                        */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
                lst val;
                 int num=50;
                for (int i=0;i<=num;++i)
                        val.append(t==exp(pow(2.2*(num-i)/num,2.2))-1.0);
                F.asy_animate(val,300,-3.1,2.4,-3.6,1.3,"nine-points-anim", "pdf");
        }

/*  We produce an illustration of [[SF]] in the canonical position. Everything is done now. */
/*                                                                          */
/* <nine-points-thm.cpp>=                                                   */
        return 0;
}
