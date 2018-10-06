#line 5660 "parab-ortho1.nw"
// The library to operate cycles in non-Euclidean geometry
//
//  Copyright (C) 2004-2016 Vladimir V. Kisil
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

#line 902 "parab-ortho1.nw"
#include <fstream>
#include <cycle.h>

#define par_matr diag_matrix(lst{-1, 0})
#define hyp_matr diag_matrix(lst{-1, 1})
using namespace MoebInv;
using namespace std;
using namespace GiNaC;

#line 914 "parab-ortho1.nw"
#define math_string << (output_latex?"$":"")
//$ (this is to balance dollar signs for LaTeX highlights in Xemacs)
#define wspaces (output_latex?"\\quad ":"  ")

#line 956 "parab-ortho1.nw"
const string eph_names="eph";
const numeric half(1,2);

const realsymbol a("a"), b("b"), c("c"), d("d"), x("x"), y("y"), z("z"), t("t"),
  k("k"), l("L","l"), m("m"), n("n"), // Cycles parameters
  k1("k1","\\tilde{k}"), l1("l1","\\tilde{l}"), m1("m1","\\tilde{m}"), n1("n1","\\tilde{n}"),
  u("u"), v("v"), u1("u1"), v1("v1"), // Coordinates of points in \(\Space{R}{2}\)
  epsilon("eps", "\\epsilon"); // The "infinitesimal" number

const varidx nu2(symbol("nu", "\\nu"), 2), mu2(symbol("mu", "\\mu"), 2);

#line 970 "parab-ortho1.nw"
const realsymbol sign("si", "\\sigma"), sign1("si1", "\\breve{\\sigma}"), //Signs of \(e_1^2\) of  \(\breve{e}_1^2\)
												 sign2("si2", "\\sigma_2"), sign3("si3", "\\sigma_3"),
												 sign4("si4", "\\mathring{\\sigma}"),
												 s("s"), s1("s1", "s_1"), s2("s2", "s_2");
int si, si1; // Values of \(e_1^2\) and \(\breve{e}_1^2\) for substitutions

 const matrix S2(2, 2, lst{1, 0, 0, jump_fnct(sign2)}),
	 S3(2, 2, lst{1, 0, 0, jump_fnct(sign3)}),
	 S4(2, 2, lst{1, 0, 0, jump_fnct(sign4)}); //Signs of [[l]] in the matrix representations of cycles

#line 982 "parab-ortho1.nw"
ex u2, v2, // Coordinates of the Moebius transform of [[(u, v)]]
            u3, v3, u4, v4, u5, v5,
            P, P1, // points on the plain
            K, L0, L1, // Parameters of cycles
            Len_c, // Expressions of Lengths
            p;

#line 992 "parab-ortho1.nw"
const ex M = diag_matrix(lst{-1, sign}), // Metrics of point spaces
	ev =  clifford_unit(mu2, M, 0), // Clifford algebra generators in the point space
	M1 = diag_matrix(lst{-1, sign1}), // Metrics of cycles spaces
	evs =  clifford_unit(nu2, M1, 1),  // Clifford algebra generators in the sphere space
	evh =  clifford_unit(nu2, S2, 1),  // Clifford algebra generators with Heviside function
	ev4 = clifford_unit(nu2, diag_matrix(lst{-1, sign4}), 2);

#line 1001 "parab-ortho1.nw"
#if GINAC_VERSION_ATLEAST(1,7,1)
const varidx nu1(symbol("nu", "\\nu"), 1), mu1(symbol("mu", "\\mu"), 1);
const ex ep =  clifford_unit(mu1, diag_matrix(lst{sign}), 0), // Clifford algebra generators in the point space
	eps =  clifford_unit(nu1, diag_matrix(lst{sign1}), 1),  // Clifford algebra generators in the sphere space
	eph =  clifford_unit(nu1, diag_matrix(lst{jump_fnct(sign2)}), 1),  // Clifford algebra generators in the sphere space
	ep4 = clifford_unit(nu1, diag_matrix(lst{sign4}), 2);

#line 1011 "parab-ortho1.nw"
#else
const varidx nu1=nu2, mu1=mu2;
const ex ep =  ev,
	eps =  evs,
	eph =  evh,
	ep4 = ev4;
#endif

#line 1023 "parab-ortho1.nw"
cycle2D C2, C3, C4, C5, C6, C7, C8, C9, C10, C11;

const cycle2D real_linev(0, lst{0, numeric(1)}, 0, ev), // the real line
            Cv(k, lst{l, n}, m, ev), Cv1(k1, lst{l1, n1}, m1, ev); // two generic cycles
const cycle2D Zvinf(0, lst{0, 0}, 1, ev), // the zero-radius cycle at infinity
            Zv(lst{u, v}, ev), Zv1(lst{u, v}, ev, 0, evs), // two generic cycles of zero-radius
            Zv2(lst{u, v}, ev, 0, evs, S2);

#line 1033 "parab-ortho1.nw"
const cycle2D real_linep(0, lst{0, numeric(1)}, 0, ep), // the real line
            Cp(k, lst{l, n}, m, ep), Cp1(k1, lst{l1, n1}, m1, ep); // two generic cycles
const cycle2D Zpinf(0, lst{0, 0}, 1, ep), // the zero-radius cycle at infinity
            Zp(lst{u, v}, ep), Zp1(lst{u, v}, ep, 0, eps), // two generic cycles of zero-radius
            Zp2(lst{u, v}, ep, 0, eps, S2);

#line 1042 "parab-ortho1.nw"
lst eqns, eqns1,
	vars=lst{k1, l1, m1, n1},
	solns, solns1, // Solutions of linear systems
		sign_val;

#line 1051 "parab-ortho1.nw"
const ex sl2_relation = (c*b == a*d-1), sl2_relation1 = (a == (1+b*c)/d); // since \(ad-bc\equiv 1\)
 const lst signs_cube = lst{pow(sign, 3) == sign, pow(sign1, 3) == sign1}; // \(s_{i}^3\equiv s_{i}\) since \(s_{i}=-1, 0, 1\)

const int debug = 0;
const bool output_latex = true;

#line 1060 "parab-ortho1.nw"
const matrix W(2,1, lst{u, v}), W1(2,1, lst{u1, v1}),
	Wbar(2,1, lst{u, -v}); // Needed for paravector formalism

#line 1065 "parab-ortho1.nw"
const matrix gW1=ex_to<matrix>(clifford_moebius_map(sl2_clifford(a, b, c, d, ev), W1, ev).subs(sl2_relation1,
   subs_options::algebraic | subs_options::no_pattern).normal());
#line 811 "parab-ortho1.nw"
const matrix gW=ex_to<matrix>(clifford_moebius_map(sl2_clifford(a, b, c, d, ev), W, ev).subs(sl2_relation1,
  subs_options::algebraic | subs_options::no_pattern).normal());


#line 1871 "parab-ortho1.nw"
ex sign5=sign4;

#line 1973 "parab-ortho1.nw"
possymbol vp("vp","v_p"); //the positive instance of symbol [[v]]
ex displ; //displacement of the focus

#line 2123 "parab-ortho1.nw"
	const matrix TCv(2,2, lst{dirac_ONE(), -ev.subs(mu2==1), sign1*ev.subs(mu2==1), dirac_ONE()}),
	 TCp(2,2, lst{dirac_ONE(), -ep.subs(mu1==0), sign1*ep.subs(mu1==0), dirac_ONE()});
// the inverse is TCI(2,2, lst{dirac_ONE(), e.subs(mu==1), -sign1*e.subs(mu==1), dirac_ONE()});

#line 1080 "parab-ortho1.nw"
	
#line 2132 "parab-ortho1.nw"
cycle2D cayley_parab(const cycle2D & C, const ex & sign = -1)
{
	return cycle2D(C.get_k()-2*sign*C.get_l(1), C.get_l(), C.get_m()-2*C.get_l(1), C.get_unit());
}


#line 1081 "parab-ortho1.nw"
	
#line 1770 "parab-ortho1.nw"
void check_conformality(const ex & Len_c, int si = 3) {
 
#line 1825 "parab-ortho1.nw"
ex Len_cD= ((Len_c.subs(lst{u == gW.op(0), v==gW.op(1), u1 == gW1.op(0),
					v1==gW1.op(1)}, subs_options::algebraic | subs_options::no_pattern)
		/Len_c).subs(lst{u1==u+t*x, v1==v+t*y}, subs_options::algebraic | subs_options::no_pattern)).normal();
ex Len_fD = Len_cD;


#line 1776 "parab-ortho1.nw"
if (si > 2)
 cout << wspaces << "This distance/length is conformal:" ;

#line 1781 "parab-ortho1.nw"
else
 cout << wspaces << "Conformity in a cycle space with metric:   E      P      H " << endl;

#line 1789 "parab-ortho1.nw"
do  {
 if (si > 1)
  si1 = 2;
 else {
  cout << wspaces << "Point space is " << eph_case(si) << ": ";
  si1 = -1;
 }

#line 1799 "parab-ortho1.nw"
 do {
  if (si < 2)

#line 1804 "parab-ortho1.nw"
Len_cD = Len_fD.subs(lst{sign == numeric(si), sign1 == numeric(si1)},
         subs_options::algebraic | subs_options::no_pattern).normal();

#line 1809 "parab-ortho1.nw"
  
#line 1833 "parab-ortho1.nw"
if (Len_cD.has(t))
 Len_cD = Len_cD.series(t==0,1).op(0).normal();

#line 1810 "parab-ortho1.nw"
  
#line 1839 "parab-ortho1.nw"
bool is_conformal = !(Len_cD.is_zero() || Len_cD.has(t)
     || Len_cD.has(x) || Len_cD.has(y));
cout << " " << is_conformal;
if (debug > 0 || (!is_conformal && (si > 2))) {
	cout << ". The factor is: " << endl << wspaces math_string << Len_cD.normal() math_string ;

}


#line 1814 "parab-ortho1.nw"
		si1++;
	} while (si1 < 2);
	cout  << endl;
	si+=2;
} while (si < 2);
}

#line 1082 "parab-ortho1.nw"
	
#line 1854 "parab-ortho1.nw"
void print_perpendicular(const cycle2D & C) {
 cout << wspaces << "Perpendicular to ((u,v); (u\',v\')) is: "
  math_string << (C.get_l(1)+sign*C.get_k()*v1).normal() math_string << "; "
  math_string << (C.get_l(0)-C.get_k()*u1).normal() math_string << endl << endl;
}

#line 1083 "parab-ortho1.nw"
	
#line 1931 "parab-ortho1.nw"
void focal_length_check(const ex & p, const cycle2D & C, const ex e, const ex es) {
	cout << "Length from *focus* check for " math_string << "p = " << p math_string << endl;
	cycle2D C11 = C.subject_to(lst{C.passing(W1), k==1, l == u, n == p});

#line 1938 "parab-ortho1.nw"
	  ex Len_c = C11.radius_sq(es).subs(pow(sign4,2)==1,subs_options::algebraic | subs_options::no_pattern).normal();
 cout << wspaces << "Length between (u,v) and (u\', v\') is equal to "
	  << (output_latex ?  "\\((\\mathring(\\sigma)-\\breve{\\sigma})p^2-2vp\\): ": "(s4-s1)*p^2-2vp: ")
	  << (Len_c - ((sign5-sign1)*pow(p, 2) - 2*v*p)).subs(signs_cube, subs_options::algebraic | subs_options::no_pattern)
	 .expand().subs(pow(sign4,2)==1,subs_options::algebraic | subs_options::no_pattern).normal().is_zero()
	  << endl;

#line 1948 "parab-ortho1.nw"
	cout << wspaces << "checks: C11 passes through (u\', v\'): " << C11.val(W1).normal().is_zero()
<< "; C11 focus is at (u, v): "
<< (C11.focus(diag_matrix(lst{-1,sign5}),true).subs(pow(sign4,2)==1,subs_options::algebraic)-matrix(2,1,lst{u,v}))
														 .evalm().normal().is_zero_matrix() << endl;
check_conformality(Len_c);

#line 1957 "parab-ortho1.nw"
	  cout << wspaces << "Perpendicular to ((u,v); (u\',v\')) is "
		   << (output_latex ? "\\((\\sigma v\'+p, u-u\')\\): " : "(s*v\'+p, u-u\'): ")
		   << ((C11.get_l(1)+sign*C11.get_k()*v1-(sign*v1+p)).normal().is_zero()
			   && (C11.get_l(0)-C11.get_k()*u1-(u-u1)).normal().is_zero())
		   << endl << endl;
}

#line 1084 "parab-ortho1.nw"
	
#line 2006 "parab-ortho1.nw"
void infinitesimal_calculations(const ex & nval, const cycle2D C, const ex e, const ex es, const ex e4,
								const cycle2D Cn, const ex en, const ex ens, const ex en4) {
	exmap smap;
	smap[v]=vp;

#line 2013 "parab-ortho1.nw"
	cycle2D C10 = cycle2D(1, lst{u, n},  pow(u,2)-pow(n,2)*sign1-pow(epsilon,2), e).subs(nval),
	  Cn10 = cycle2D(1, lst{u, n},  pow(u,2)-pow(n,2)*sign1-pow(epsilon,2), en).subs(nval);
	cout << wspaces << "Inf cycle is: " math_string << C10 math_string << endl;
	cout << wspaces << "For paravector is the same: " << C10.is_equal(Cn10,true,true) << endl;
	cout << wspaces << "Square of radius of the infinitesimal cycle is: "
		math_string << C10.radius_sq(es).subs(signs_cube, subs_options::algebraic
											  | subs_options::no_pattern).normal() math_string << endl
		 << wspaces << "For paravector is the same: " << C10.radius_sq(es).subs(signs_cube, subs_options::algebraic
																				| subs_options::no_pattern).normal()
		.is_equal(Cn10.radius_sq(es).subs(signs_cube, subs_options::algebraic
										  | subs_options::no_pattern).normal()) << endl;


#line 2029 "parab-ortho1.nw"
cout << wspaces << "Focus of infinitesimal cycle is: " math_string
	<< C10.focus(e4).subs(nval) math_string << endl
	<< wspaces << "For paravector is the same: "
	<< C10.focus(e4).subs(nval).is_equal(Cn10.focus(en4).subs(nval)) << endl
	<< wspaces << "Focal length is: " math_string
	<< C10.focal_length().series(epsilon==0,3).normal() math_string << endl
	<< wspaces << "For paravector is the same: "
	<< C10.focal_length().series(epsilon==0,3).normal().is_equal(
																 Cn10.focal_length().series(epsilon==0,3).normal())
	<< endl;

	cout << wspaces << "Infinitesimal cycle (vector) passing points" math_string
		 << "(u+" << epsilon*x <<", vp+"
		 << lsolve(C10.subs(sign==0).passing(lst{u+epsilon*x,vp+y}),y).series(epsilon==0,3).normal()
		 << "), " math_string << endl;

	cout << wspaces << "Infinitesimal cycle (paravector) passing points" math_string
		 << "(u+" << epsilon*x <<", vp+"
		 << lsolve(Cn10.subs(sign==0).passing(lst{u+epsilon*x,vp+y}),y).series(epsilon==0,3).normal()
		 << "), " math_string << endl;

#line 2057 "parab-ortho1.nw"
	cycle2D C11=C10.sl2_similarity(a, b, c, d, es),
	Cn11=Cn10.sl2_similarity(a, b, c, d, ens);
	cout << wspaces << "Image under SL2(R) of infinitesimal cycle has radius squared: " << endl
		math_string << C11.radius_sq(es).subs(sl2_relation1,
											  subs_options::algebraic | subs_options::no_pattern).subs(signs_cube,
																									   subs_options::algebraic | subs_options::no_pattern)
		.series(epsilon==0,3).normal()
		math_string << endl
		 << wspaces << "For paravector is the same: "
		 << C11.radius_sq(es).subs(sl2_relation1,
								   subs_options::algebraic | subs_options::no_pattern).subs(signs_cube,
																							subs_options::algebraic | subs_options::no_pattern)
		.series(epsilon==0,3).normal().is_equal(Cn11.radius_sq(ens).subs(sl2_relation1,
																		 subs_options::algebraic | subs_options::no_pattern).subs(signs_cube,
																																  subs_options::algebraic | subs_options::no_pattern)
												.series(epsilon==0,3).normal()) << endl;

#line 2076 "parab-ortho1.nw"
	cout << wspaces << "Image under cycle similarity of infinitesimal cycle has radius squared: "
		 << endl
		math_string << C10.cycle_similarity(C, es).radius_sq(es).subs(signs_cube, subs_options::algebraic
																	  | subs_options::no_pattern).series(epsilon==0,3).normal() math_string << endl
		<< wspaces << "For paravector is the same: "
		<< C10.cycle_similarity(C, es).radius_sq(es).subs(signs_cube, subs_options::algebraic
														  | subs_options::no_pattern).series(epsilon==0,3).normal()
		.is_equal(Cn10.cycle_similarity(Cn, es).radius_sq(ens).subs(signs_cube, subs_options::algebraic
																	| subs_options::no_pattern).series(epsilon==0,3).normal())
		 << endl;

#line 2090 "parab-ortho1.nw"
	ex displ = (C11.focus(e4, true).subs(nval) - gW.subs(smap, subs_options::no_pattern)).evalm();
	cout << wspaces << "Focus of the transormed cycle is from transformation of focus by: "
		math_string << displ.subs(sl2_relation, subs_options::algebraic
								  | subs_options::no_pattern).subs(lst{sign==0,a==(1+b*c)/d}).series(epsilon==0,2).normal()
		math_string << endl;

#line 2104 "parab-ortho1.nw"
	cout << wspaces << "Orthogonality (leading term) to infinitesimal cycle is:" << endl << wspaces
									 math_string << ex(C.is_orthogonal(C10, es)).series(epsilon==0,1).normal() math_string << endl;

#line 2112 "parab-ortho1.nw"
	  cout << wspaces << "f-orthogonality of other cycle to infinitesimal:" << endl << wspaces
	  math_string << C.is_f_orthogonal(C10, es).series(epsilon==0,1).normal() math_string << endl
		   << "f-orthogonality of infinitesimal cycle to other:" << endl << wspaces
	  math_string << C10.is_f_orthogonal(C, es).series(epsilon==0,3).normal() math_string << endl;

#line 2141 "parab-ortho1.nw"
	C11 = cayley_parab(C10, sign1);
	cout << wspaces <<  "Det of Cayley-transformed infinitesimal cycle: "
		math_string << C11.radius_sq(es).subs(lst{sign == 0},
											  subs_options::algebraic | subs_options::no_pattern).series(epsilon==0,3).normal()
		math_string << endl;

#line 2149 "parab-ortho1.nw"
	displ = (C11.focus(e4, true).subs(nval)
				 - clifford_moebius_map(TCv, matrix(2,1,lst{u,vp}), e)).evalm().normal();
	ex displn = (C11.focus(e4, true).subs(nval)
				 - clifford_moebius_map(TCp, matrix(2,1,lst{u,vp}), en)).evalm().normal();
	cout << wspaces << "Focus of the Cayley-transformed infinitesimal cycle displaced by: " math_string ;
 try{
	 cout << displ.subs(lst{sign == 0},
						subs_options::algebraic | subs_options::no_pattern).series(epsilon==0, 2).normal();
 } catch (exception &p) {
	 cout << "(" << displ.op(0).subs(lst{sign == 0},
									 subs_options::algebraic | subs_options::no_pattern).series(epsilon==0, 2).normal()
		  << ", " << displ.op(1).subs(lst{sign == 0},
									  subs_options::algebraic | subs_options::no_pattern).series(epsilon==0, 2).normal()
		  << ")";
}
cout  math_string << endl
<< wspaces << "For paravector is the same: " <<  displ.is_equal(displn) << endl;

#line 2169 "parab-ortho1.nw"
cout << wspaces << "f-orthogonality of Cayley transforms of infinitesimal cycle to other:" << endl << wspaces
	math_string << C11.is_f_orthogonal(cayley_parab(C,sign1), es).series(epsilon==0,3).normal()
	math_string << endl << endl;
}


#line 922 "parab-ortho1.nw"
int main(){
 cout << boolalpha;

 if (output_latex) cout << latex;

#line 930 "parab-ortho1.nw"
#if GINAC_VERSION_ATLEAST(1,7,1)
#else
cerr << "GiNaC version is not sufficiently large to handle paravector calculations." << endl
	<< "All false results for paravectors shall be ignored!" << endl;
#endif

#line 939 "parab-ortho1.nw"
	try {
		
#line 843 "parab-ortho1.nw"
  
#line 806 "parab-ortho1.nw"
	C2 = Cv.subject_to(lst{Cv.passing(W)});

#line 817 "parab-ortho1.nw"
cout << "Conjugation of a cycle comes through Moebius transformation for vectors: "
	 << C2.sl2_similarity(a, b, c, d, evs, S2, true, S2).val(gW).subs(sl2_relation1,
                subs_options::algebraic | subs_options::no_pattern).normal().is_zero()
 << endl << endl;

#line 1071 "parab-ortho1.nw"
	  C2 = Cp.subject_to(lst{Cp.passing(W)});
	  cout << "Conjugation of a cycle comes through Moebius transformation for paravectors: "
		   << C2.sl2_similarity(a, b, c, d, eps, S2, true, S2).val(gW).subs(sl2_relation1,
																			subs_options::algebraic | subs_options::no_pattern).normal().is_zero()
		   << endl << endl;

#line 844 "parab-ortho1.nw"
  
#line 1101 "parab-ortho1.nw"
auto K_inv = [](string S, const ex & e) {
cycle2D C2 = cycle2D(1, lst{0, (pow(t,-1)-sign*t)/2}, 1, e);
cout << "A K-orbit is preserved " << S << C2.sl2_similarity(cos(x), sin(x), -sin(x), cos(x), e).is_equal(C2)

#line 1107 "parab-ortho1.nw"
<< ", and  passing (0, t): " << (bool)ex_to<relational>(C2.passing(lst{0, t})) << endl; };

#line 1111 "parab-ortho1.nw"
	  K_inv("for vectors: ", ev);
	  K_inv("for paravectors: ", ep);

#line 845 "parab-ortho1.nw"
  
#line 1121 "parab-ortho1.nw"
cout << wspaces << "Determinant of zero-radius Z1 cycle in metric e is for vector: "
	math_string << canonicalize_clifford(Zv1.det(ev, S2)) math_string << endl;
 cout << wspaces << "The opposite value for paravector: "
	  << canonicalize_clifford(Zv1.det(ev, S2)+Zp1.det(ep, S2)).normal().is_zero()  << endl;

#line 1127 "parab-ortho1.nw"
cout << wspaces << "Focus of zero-radius cycle is (vector): " math_string
	 << Zv1.focus(ev) math_string << endl;
cout << wspaces << "The same value for paravector: "
	 << (Zv1.focus(ev,true)-Zp1.focus(ep,true)).evalm().is_zero()  << endl;
cout << wspaces << "Centre of zero-radius cycle is (vector): " math_string
	 << Zv1.center(ev) math_string << endl;
cout << wspaces << "The same value for paravector: "
	 << (Zv1.center(ev,true)-Zp1.center(ep,true)).evalm().is_zero()  << endl;
cout  << wspaces << "Focal length of zero-radius cycle is (vector): " math_string
	  << Zv1.focal_length() math_string << endl;
cout << wspaces << "The same value for paravector: "
	 << (Zv1.center(ev,true)-Zp1.center(ep,true)).evalm().is_zero()  << endl;

#line 1144 "parab-ortho1.nw"
auto Z_rad_tr=[](const cycle2D & Z1, const ex & e, const ex & es)
	{return canonicalize_clifford(Z1.sl2_similarity(a, b, c, d, e, S2).det(es, S2)).subs(sl2_relation1,
																						 subs_options::algebraic | subs_options::no_pattern); };

cout << "Image of the zero-radius cycle under Moebius transform has zero radius vector: "
	 << Z_rad_tr(Zv1,ev,evs).is_zero()
	 << " and paravector: " << Z_rad_tr(Zp1,ep,eps).is_zero() << endl;

#line 1154 "parab-ortho1.nw"
u2 = gW.op(0);
v2 = gW.op(1);

#line 1159 "parab-ortho1.nw"
auto Z_center=[](string S, const cycle2D & Z, const ex & e) {
	C2 = Z.sl2_similarity(a, b, c, d, e);
	K = C2.get_k();
	L0 = C2.get_l(0);
	L1 = C2.get_l(1).normal();

#line 1168 "parab-ortho1.nw"
cout <<"The centre of the Moebius transformed zero-radius cycle for " << S
 << equality((u2*K-L0).subs(sl2_relation, subs_options::algebraic | subs_options::no_pattern)) << ", "
 << equality((v2*K-L1).subs(sl2_relation, subs_options::algebraic | subs_options::no_pattern))
	<< endl; };

#line 1175 "parab-ortho1.nw"
 Z_center("vector: ", Zv, ev);
 Z_center("paravector: ", Zp, ep);

#line 846 "parab-ortho1.nw"
  
#line 1187 "parab-ortho1.nw"
auto Z_conjugated=[](const cycle2D & Z, const cycle2D & C, const ex & e) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);


#line 1197 "parab-ortho1.nw"
	matrix S1=ex_to<matrix>(diag_matrix(lst{1, s1})),  S2=ex_to<matrix>(diag_matrix(lst{1, s2}));
	lst square_sub=lst{pow(s1,2)==1, pow(s2,2)==1};
	cycle2D Zn = Z.cycle_similarity(C, e, S1, S2, pow(S1,-1).evalm());
	cout << "Image of the zero-radius cycle under cycle similarity has zero radius for "
	<< (is_vector? "" : "para") << "vector: " << canonicalize_clifford(Zn.det(e, S1)).subs(square_sub,
																						   subs_options::algebraic | subs_options::no_pattern).normal().is_zero()
	<< endl;

#line 1209 "parab-ortho1.nw"
lst Pc=ex_to<lst>(Zn.center(diag_matrix(lst{-1,-s2*s1})));
if (is_vector)
	P=C.moebius_map(Z.center(diag_matrix(lst{-1,-s2/s1})));
else
	P=C.moebius_map(Z.center(diag_matrix(lst{-1,s2/s1})));

cout <<"The centre of the conjugated zero-radius cycle coinsides with Moebius trans for "
	<< (is_vector? "" : "para") << "vector: " <<  equality((P.op(0)-Pc.op(0)).normal().subs(square_sub,
																							subs_options::algebraic))
	<< ", " << equality((P.op(1)-Pc.op(1)).normal().subs(square_sub,subs_options::algebraic))
	<< endl; };

#line 1223 "parab-ortho1.nw"
Z_conjugated(Zv, Cv, ev);
Z_conjugated(Zp, Cp, ep);

#line 847 "parab-ortho1.nw"
cout << endl;

#line 853 "parab-ortho1.nw"
  
#line 1239 "parab-ortho1.nw"
cout << wspaces << "The orthogonality in vectors is: " math_string
 << (ex)Cv.is_orthogonal(Cv1, evs, S2) math_string << endl
<< "for paravectors is the same: "
<< Cv.is_orthogonal(Cv1, evs, S2).is_equal(Cp.is_orthogonal(Cp1, eps, S2)) << endl;

#line 1246 "parab-ortho1.nw"
cout << wspaces << "The orthogonality of two lines is: " math_string
 << (ex)Cv.subs(k == 0).is_orthogonal(Cv1.subs(k1 == 0), evs, S2) math_string << endl;

#line 1253 "parab-ortho1.nw"
cout << wspaces << "The orthogonality to z-r-cycle is: " math_string
<< (ex)Cv.is_orthogonal(Zv, evs)  math_string << endl
	<< "for paravectors is the same: " <<
	Cv.is_orthogonal(Zv, evs).is_equal(Cp.is_orthogonal(Zp, eps)) << endl;

#line 1260 "parab-ortho1.nw"
cout << wspaces << "The orthogonality of two z-r-cycle is: " math_string
 <<  (ex)cycle2D(lst{u1, v1}, ev, 0, S2).is_orthogonal(Zv, evs) math_string << endl
	<< "for paravectors is the same: "
<< cycle2D(lst{u1, v1}, ev, 0, S2).is_orthogonal(Zv, evs).is_equal(
																   cycle2D(lst{u1, v1}, ep, 0, S2).is_orthogonal(Zp, eps)) << endl;

#line 854 "parab-ortho1.nw"
  
#line 1272 "parab-ortho1.nw"
	C2 = Cv1.subject_to(lst{Cv1.passing(W),
				Cv1.passing(W1),
				Cv1.is_orthogonal(Cv, evs)}, vars);

#line 1285 "parab-ortho1.nw"
if (debug > 0)
cout << "Cycle through two point is possible and unique if denominator is not zero: " << endl
 math_string << C2.get_k() math_string << endl << endl;

#line 855 "parab-ortho1.nw"
  
#line 1298 "parab-ortho1.nw"
auto Ortho_inv=[](const cycle2D & C, const cycle2D & C1, const ex & e, const ex & es) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1300 "parab-ortho1.nw"
	C2 = C1.subject_to(lst{C1.passing(W),
				C1.is_orthogonal(C, es)});

#line 1309 "parab-ortho1.nw"
	P = C.moebius_map(is_vector? W : Wbar, e, -M1);

	C3 = C1.subject_to(lst{C1.passing(P),
				C1.passing(W),
				C1.is_orthogonal(C, es)});

#line 1320 "parab-ortho1.nw"
cout << "Both orthogonal cycles (through one point and through its inverse)"
	" are the same for " << (is_vector? "" : "para") << "vector: "
	<< C2.is_equal(C3) << endl

#line 1326 "parab-ortho1.nw"
	<< "Orthogonal cycle passes through the transformed point "
	<< (is_vector? "" : "para") << "vector: "
	<< C2.val(P).normal().is_zero() << endl << endl;
};

#line 1333 "parab-ortho1.nw"
Ortho_inv(Cv, Cv1, ev, evs);
Ortho_inv(Cp, Cp1, ep, eps);

#line 856 "parab-ortho1.nw"
  
#line 1347 "parab-ortho1.nw"
auto Ortho_line=[](const cycle2D & C, const cycle2D & C1, const ex & e, const ex & es) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1349 "parab-ortho1.nw"
	C4 = C1.subject_to(lst{C1.passing(W), C1.passing(P), C1.is_linear()});
cout << "For " << (is_vector? "" : "para") << "vectors" << endl
	<< wspaces << "Line through point and its inverse is orthogonal: " << C4.cycle_product(C, es).is_zero()
	<< endl;

#line 1358 "parab-ortho1.nw"
u3 = C.center().op(0);
v3 = C4.roots(u3, false).op(0).normal();
cout << wspaces << "All lines come through the point " math_string
	<<"(" << u3 << ", " << v3 << ")" math_string << endl;

#line 1368 "parab-ortho1.nw"
if (is_vector)
	P1 = C.moebius_map(lst{u3+u, v3+v}, e, -M1);
else
	P1 = C.moebius_map(lst{u3+u, -v3-v}, e, -M1);
cout << wspaces << "Conjugated vector is parallel to (u,v): "
		<< ((P1.op(0)-u3)*v-(P1.op(1)-v3)*u).normal().is_zero() << endl;
if (debug > 1)
	cout << wspaces << "Conjugated vector to (u, v) is: " math_string
		 << "(" << (P1.op(0)-u3).normal() << ", "
		 << (P1.op(1)-v3).normal() << ")" math_string << endl; };

#line 1381 "parab-ortho1.nw"
Ortho_line(Cv, Cv1, ev, evs);
Ortho_line(Cp, Cp1, ep, eps);

#line 857 "parab-ortho1.nw"
  
#line 1397 "parab-ortho1.nw"
auto Ghost_cycle=[](const cycle2D & C, const cycle2D & C1, const ex & e, const ex & es) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1399 "parab-ortho1.nw"
	C5 = cycle2D(lst{u3, -v3*jump_fnct(sign)}, e, C.radius_sq(e, M1)).subs(signs_cube,
																		   subs_options::algebraic | subs_options::no_pattern);

#line 1404 "parab-ortho1.nw"
cout << "For " << (is_vector? "" : "para") << "vectors" << endl
	 << wspaces << "Ghost cycle has common roots with C : "
	  << (C5.val(lst{C.roots().op(0), 0}).normal().is_zero()
		  && C5.val(lst{C.roots().op(1), 0}).normal().is_zero()) << endl
	  << wspaces << "$\\chi(\\sigma)$-centre of ghist cycle is equal to "
	  "$\\breve{\\sigma}$-centre of C: "
	  << (C5.center(diag_matrix(lst{-1,jump_fnct(sign)}), true)-C.center(es, true)).normal().is_zero()
	  <<  endl;

#line 1416 "parab-ortho1.nw"
	P1 = C5.moebius_map(is_vector? W : Wbar, e, diag_matrix(lst{1, -jump_fnct(sign)}));
	P = C.moebius_map(is_vector? W : Wbar, e, -M1);

#line 1423 "parab-ortho1.nw"
cout << wspaces << "Inversion in (C-ghost, sign) coincides with inversion in (C, sign1): "
	  << (P1-P).subs(signs_cube, subs_options::algebraic | subs_options::no_pattern).normal().is_zero()
	   << endl; };

#line 1429 "parab-ortho1.nw"
Ghost_cycle(Cv, Cv1, ev, evs);
Ghost_cycle(Cp, Cp1, ep, eps);

#line 858 "parab-ortho1.nw"
  
#line 1445 "parab-ortho1.nw"
for (si=-1; si<2; si+=2) {
	auto Inv_RL=[](const cycle2D & C, const cycle2D & C1, const cycle2D & real_line,
				   const ex & e, const ex & es) {
		
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1449 "parab-ortho1.nw"
		C9 = cycle2D(k, lst{l, n+si*sqrt(C.hdet(es)*sign1)},m,es);
		cout << "For " << (is_vector? "" : "para") << "vectors" << endl
		<< wspaces << "Inversion to the real line (with " << (si==-1? "-" : "+") << " sign): " << endl
		<< wspaces << "Conjugation of the real line is the cycle C: "
		<< real_line.cycle_similarity(C9, es).subs(pow(sign1,2)==1, subs_options::algebraic).is_equal(C) << endl
		<< wspaces << "Conjugation of the cycle C is the real line: "
		<< C.cycle_similarity(C9, es).subs(pow(sign1,2)==1, subs_options::algebraic).is_equal(real_line) << endl


#line 1463 "parab-ortho1.nw"
		<< wspaces << "Inversion cycle has common roots with C: "
		<< (C9.val(lst{C.roots().op(0), 0}).numer().normal().is_zero()
			&& C9.val(lst{C.roots().op(1), 0}).numer().normal().is_zero()) << endl
		<< wspaces << "C passing the centre of inversion cycle: "
		<< cycle2D(C, es).val(C9.center()).numer().subs(sign1==sign, subs_options::no_pattern).normal()
		.subs(pow(sign,2)==1, subs_options::algebraic | subs_options::no_pattern).is_zero() << endl; };
	Inv_RL(Cv, Cv1, real_linev, ev, evs);
	Inv_RL(Cp, Cp1, real_linep, ep, eps);
}

#line 859 "parab-ortho1.nw"
  
#line 1485 "parab-ortho1.nw"
auto Yaglom_inv=[](const cycle2D & real_line, const ex & e) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1487 "parab-ortho1.nw"
	cout << "For " << (is_vector? "" : "para") << "vectors "
	<< "Yaglom inversion of the second kind is three reflections in the cycles: "
	<< (real_line.moebius_map(cycle2D(lst{l, 0}, e, -m/k).moebius_map(cycle2D(lst{l, 2*m}, e, -m/k)
																   .moebius_map(is_vector? W : Wbar))).subs(sign==0)
	 -matrix(2,1,lst{u, 2*(k*pow(u-l,2)+m)-v})).normal().is_zero() << endl; };

Yaglom_inv(real_linev, ev);
Yaglom_inv(real_linep, ep);

#line 860 "parab-ortho1.nw"
cout << endl;

#line 866 "parab-ortho1.nw"
  
#line 1509 "parab-ortho1.nw"
auto Focal_orth_cond=[](const cycle2D & real_line, const ex & e) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1511 "parab-ortho1.nw"
	cout << "For " << (is_vector? "" : "para") << "vectors"
	<< wspaces << "The real line is Moebius invariant: "
	<< real_line.is_equal(real_line.sl2_similarity(a, b, c, d, e)) << endl; };
Focal_orth_cond(real_linev,evs);
Focal_orth_cond(real_linep,eps);

#line 1519 "parab-ortho1.nw"
cout << "Reflection in the real line (vector): "
						 math_string << Zv.cycle_similarity(real_linev, evs).normalize()
						 math_string << endl
<< wspaces << "for paravector is the same: "
<< Zv.cycle_similarity(real_linev, evs).is_equal(Zp.cycle_similarity(real_linep, eps),true,true) << endl;

cout  << "Reflection of the real line in cycle C (vectors): " << endl
	math_string << real_linev.cycle_similarity(Cv, evs, S2, S3) math_string << endl
	  << wspaces << "for paravectors is the same: "
	  << real_linev.cycle_similarity(Cv, evs, S2, S3).is_equal(real_linep.cycle_similarity(Cp, eps, S2, S3),true,true)
	  << endl;

#line 1538 "parab-ortho1.nw"
cout  << "The f-orthogonality is (vectors): " math_string
<< (ex)Cv.is_f_orthogonal(Cv1, evs, S2) math_string << endl
<< wspaces << "for paravectors is the same: "
<< Cv.is_f_orthogonal(Cv1, evs, S2).is_equal(Cp.is_f_orthogonal(Cp1, eps, S2)) << endl;

#line 1545 "parab-ortho1.nw"
cout << wspaces << "The f-orthogonality of two lines is (vectors): " math_string
<< (ex)Cv.subs(k == 0).is_f_orthogonal(Cv1.subs(k1==0), evs, S2) math_string << endl
<< wspaces << "for paravectors is the same: "
<< Cv.subs(k == 0).is_f_orthogonal(Cv1.subs(k1==0), evs, S2).is_equal(
																	  Cp.subs(k == 0).is_f_orthogonal(Cp1.subs(k1==0), eps, S2)) << endl;

#line 1553 "parab-ortho1.nw"
cout << wspaces << "The f-orthogonality to z-r-cycle is first way (vectors): "  << endl
	math_string << (ex)Cv.is_f_orthogonal(Zv1, evs, S2) math_string << endl
<< wspaces << "for paravectors is the same: "
<< Cv.is_f_orthogonal(Zv1, evs, S2).is_equal(Cp.is_f_orthogonal(Zp1, eps, S2)) << endl;

#line 1563 "parab-ortho1.nw"
cout << wspaces << "The f-orthogonality to z-r-cycle in second way (vectors): " << endl
	math_string << (ex)Zv1.is_f_orthogonal(Cv, evs, S2) math_string << endl
<< wspaces << "for paravectors is the same: "
<< Zv1.is_f_orthogonal(Cv, evs, S2).is_equal(Zp1.is_f_orthogonal(Cp, eps, S2)) << endl;

#line 1570 "parab-ortho1.nw"
	//C9 = cycle2D(lst{u1, v1}, e);
cout << wspaces << "The f-orthogonality of two z-r-cycle is (vectors): " << endl
 math_string << (ex)Zv1.is_f_orthogonal(cycle2D(lst{u1, v1}, ev), evs, S2) math_string << endl
<< wspaces << "for paravectors is the same: "
<< Zv1.is_f_orthogonal(cycle2D(lst{u1, v1}, ev), evs, S2).is_equal(
																   Zp1.is_f_orthogonal(cycle2D(lst{u1, v1}, ep), eps, S2)) << endl;

#line 867 "parab-ortho1.nw"
  
#line 1584 "parab-ortho1.nw"
cycle2D Cv6 = Cv1.subject_to(lst{Cv1.passing(W), Cv.is_f_orthogonal(Cv1, evs)}),
	Cp6 = Cp1.subject_to(lst{Cp1.passing(W), Cp.is_f_orthogonal(Cp1, eps)});
 if (debug > 1)
	 cout << "Cycle f-orthogonal to (k, (l, n), m) is (vectors): " << endl
		 math_string << C6 math_string << endl
		  << wspaces << "for paravectors is the same: "
		  << Cv6.is_equal(Cp6,true, true);

#line 868 "parab-ortho1.nw"
  
#line 1595 "parab-ortho1.nw"
auto Focal_orth_line=[](const cycle2D & C6, const cycle2D & C, const ex & e) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1597 "parab-ortho1.nw"
	C7 = C6.subject_to(lst{C6.is_linear()});
	u4 = C.center().op(0);
	v4 = C7.roots(u4, false).op(0).normal();

#line 1604 "parab-ortho1.nw"
cout << wspaces << "For " << (is_vector? "" : "para")
	<< "vectors all lines come through the focus related $\\breve{e}$: "
	<< (C.focus(diag_matrix(lst{-1, -sign1}), true)-matrix(2, 1, lst{u4, v4})).normal().is_zero() << endl; };

 Focal_orth_line(Cv6, Cv, ev);
 Focal_orth_line(Cp6, Cp, ep);

#line 869 "parab-ortho1.nw"
  
#line 1619 "parab-ortho1.nw"
auto Focal_inversion=[](const cycle2D & C, const cycle2D & C6, const cycle2D & real_line,
						const ex & e, const ex & es) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1622 "parab-ortho1.nw"
	C8 = real_line.cycle_similarity(C, es, diag_matrix(lst{1, sign1}),
									diag_matrix(lst{1, jump_fnct(sign)}), diag_matrix(lst{1, sign1})).normalize(n*k);
	if (debug > 1)
		cout << "f-ghost cycleis : " math_string << C8 math_string << endl;

#line 1629 "parab-ortho1.nw"
	cout << "For " << (is_vector? "" : "para") << "vectors" << endl;
	cout << wspaces << "f-ghost cycle has common roots with C: "
		<< (C8.val(lst{C.roots().op(0), 0}).numer().normal().is_zero()
			&& C8.val(lst{C.roots().op(1), 0}).numer().normal().is_zero()) << endl;

#line 1636 "parab-ortho1.nw"
	cout  << wspaces << "$\\chi(\\sigma)$-center of f-ghost cycle coincides "
	"with $\\breve{\\sigma}$-focus of C : "
	<< (C8.center(diag_matrix(lst{-1,jump_fnct(sign)}), true)
		-C.focus(diag_matrix(lst{-1, -sign1}), true)).evalm().normal().is_zero_matrix()
	<< endl;

#line 1645 "parab-ortho1.nw"
	P1 = C8.moebius_map(is_vector? W : Wbar, e, diag_matrix(lst{1, -jump_fnct(sign)}))
	.subs(signs_cube, subs_options::algebraic | subs_options::no_pattern).normal();
	cout << wspaces << "f-inversion in C coincides with inversion in f-ghost cycle: "
	<< C6.val(P1).normal().subs(signs_cube, subs_options::algebraic | subs_options::no_pattern).normal().is_zero()
	<< endl; };

#line 1653 "parab-ortho1.nw"
Focal_inversion(Cv,Cv6,real_linev,ev,evs);
Focal_inversion(Cp,Cp6,real_linep,ep,eps);

#line 870 "parab-ortho1.nw"
cout << endl;

#line 875 "parab-ortho1.nw"
  
#line 1672 "parab-ortho1.nw"
auto Distance1=[](const cycle2D & C, const ex & e, const ex & es) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1674 "parab-ortho1.nw"
	cycle2D C10 = cycle2D(numeric(1), lst{l, n}, m, e);
	C10 = C10.subject_to(lst{C10.passing(W), C10.passing(W1)}, lst{m, n, l});
	if (debug > 0) cout << wspaces << "C10 is:   "  << C10 << endl;

#line 1682 "parab-ortho1.nw"
	ex D = 4*C10.radius_sq(es);
	Len_c = D.subs(lsolve(lst{D.diff(l) == 0}, lst{l})).normal();

#line 1691 "parab-ortho1.nw"
	cout << "For " << (is_vector? "" : "para") << "vectors" << endl;
	cout << wspaces << "Distance between (u,v) and (u\',v\') in elliptic and hyperbolic spaces is "
	<< endl;

if (output_latex) {
 ex dist = (sign1*(pow(u-u1,2)-sign*pow(v-v1,2))+4*(1-sign*sign1)*v*v1)*(pow(u-u1,2)
   -sign*pow(v-v1,2))/(pow(u-u1,2)*sign1-pow(v-v1,2));
 cout << "\\(\\displaystyle " << dist << "\\): " <<  (Len_c-dist).normal().is_zero() << endl;
} else
 cout << endl
  << "  s1*((u-u\')^2-s*(v-v\')^2)+4*(1-s*s1)*v*v\')*((u-u\')^2-s*(v-v\')^2)"
  << endl
  << "  ---------------------------------------------------------------      : "
  <<  (Len_c-(sign1*(pow(u-u1,2)-sign*pow(v-v1,2))+4*(1-sign*sign1)*v*v1)*(pow(u-u1,2)
   -sign*pow(v-v1,2))/(pow(u-u1,2)*sign1-pow(v-v1,2))).normal().is_zero() << endl
  <<"               (u-u\')^2*s1-(v-v\')^2" << endl << endl;

#line 1714 "parab-ortho1.nw"
	check_conformality(Len_c, -1);
	C11 = C10.subs(lsolve(lst{D.diff(l) == 0}, lst{l}));
	print_perpendicular(C11);

#line 1722 "parab-ortho1.nw"
	Len_c = D.subs(lst{sign ==0, l == (u+u1)*half}).normal();
	cout << wspaces << "Value at the middle point (parabolic point space):" << endl << wspaces
	math_string << Len_c math_string << endl;

#line 1728 "parab-ortho1.nw"
	check_conformality(Len_c, 0);
	C11 = C10.subs(lst{sign ==0, l == (u+u1)*half});
	print_perpendicular(C11); };

#line 1734 "parab-ortho1.nw"
Distance1(Cv, ev, evs);
Distance1(Cp, ep, eps);

#line 1742 "parab-ortho1.nw"
auto Distance2=[](const cycle2D & C, const ex & e, const ex & es) {
	cycle2D C10 = cycle2D(numeric(1), lst{l, n}, m, e);
	C10 = C10.subject_to(lst{C10.passing(W),
				C10.passing(lst{u1, v})});
	if (debug > 1)
		cout << wspaces  << C10 << endl;

#line 1751 "parab-ortho1.nw"
	ex D = 4*C10.radius_sq(es);
	return D.subs(lsolve(lst{D.diff(n) == 0}, lst{n})).normal(); };

ex Dv=Distance2(Cv, ev, evs);
	cout << "For vectors distance between (u,v) and (u\',v\') "
		 << "(value at critical point): " << endl
		 << wspaces math_string << Dv  math_string
		 << endl << endl
		 << wspaces << " for paravector is the same: "
		 <<Dv.is_equal(Distance2(Cp, ep, eps)) << endl;

#line 876 "parab-ortho1.nw"
  
#line 1876 "parab-ortho1.nw"
auto Length_checks=[](const cycle2D & C, const ex & e, const ex & es, const ex & e4) {
	
#line 1193 "parab-ortho1.nw"
	bool is_vector = (ex_to<idx>(e.op(1)).get_dim() == 2);

#line 1878 "parab-ortho1.nw"
	sign5=sign4;
	C11 = C.subject_to(lst{C.passing(W1), C.is_normalized()});
	C11 = C11.subject_to(lst{C11.center().op(0) == u, C11.center(e4).op(1)== v});

#line 1886 "parab-ortho1.nw"
	Len_c = C11.radius_sq(es).normal();
	cout << "For " << (is_vector? "" : "para") << "vectors" << endl;
	cout << wspaces << "Length from *center* between (u,v) and "
	math_string << "(u^\\prime,v^\\prime)" math_string << ":" << endl  << wspaces
	math_string << Len_c math_string << endl ;
	check_conformality(Len_c);
	print_perpendicular(C11);

#line 877 "parab-ortho1.nw"
  
#line 1909 "parab-ortho1.nw"
focal_length_check(sign5*(-(v1-v)+sqrt(sign5*pow((u1-u), 2)+pow((v1-v), 2) -sign5*sign*pow(v1, 2))), C, e, es);

#line 1914 "parab-ortho1.nw"
focal_length_check(sign5*(-(v1-v)-sqrt(sign5*pow(u1-u, 2)+pow((v1-v), 2) -sign5*sign*pow(v1, 2))), C, e, es);

#line 1919 "parab-ortho1.nw"
cout << "Shall be `false' for conformality below" << endl;
sign5=0;
focal_length_check((pow(u1-u,2)-sign*pow(v1,2))/(v1-v)/2, C, e, es); };

#line 1925 "parab-ortho1.nw"
Length_checks(Cv,ev,evs,ev4);
Length_checks(Cp,ep,eps,ep4);

#line 878 "parab-ortho1.nw"
  
#line 1991 "parab-ortho1.nw"
infinitesimal_calculations(n==(vp-sqrt(pow(vp,2)+pow(epsilon,2)*(sign4-sign1)))/(sign4-sign1),
						   Cv,ev,evs,ev4,Cp,ep,eps,ep4);
//infinitesimal_calculations(n==(vp-abs(pow(pow(vp,2)-pow(epsilon,2)*(sign4-sign1),half)))/(sign4-sign1),
// C,e,es,e4,is_vector);

#line 2001 "parab-ortho1.nw"
infinitesimal_calculations(lst{n==pow(epsilon,2)/2/vp, sign4==sign1},Cv,ev,evs,ev4,Cp,ep,eps,ep4);

#line 879 "parab-ortho1.nw"
cout << endl;

#line 941 "parab-ortho1.nw"
		} catch (exception &p) {
		cerr << "*****       Got a problem with symbolic calculations: " <<  p.what() << endl;
	}

#line 947 "parab-ortho1.nw"
	
#line 2192 "parab-ortho1.nw"
#if GINAC_VERSION_ATLEAST(1,7,1)
for (int is_vector=0; is_vector<2;++is_vector) {
#else
for (int is_vector=1; is_vector<2;++is_vector) {
#endif
	cycle2D C, C1, Z, Z1, real_line, Zinf;
	varidx mu;
	ex e, es;
	ofstream asymptote;
	relational mu_subs;
	if (is_vector==1) {
		C=Cv; C1=Cv1; Z=Zv; Z1=Zv1;
		real_line=real_linev; Zinf=Zvinf;
		e=ev; es=evs;
		asymptote=ofstream("parab-ortho1-v.asy");
		mu=mu2;
		mu_subs=(mu==1);
	} else {
		C=Cp; C1=Cp1; Z=Zp; Z1=Zp1;
		real_line=real_linep;  Zinf=Zpinf;
		e=ep; es=eps;
		asymptote=ofstream("parab-ortho1-p.asy");
		mu=mu1;
		mu_subs=(mu==0);
	}

	P = C.moebius_map(is_vector==1? W : Wbar, e, -M1);
	P1 = C.moebius_map(is_vector==1? lst{u3+u, v3+v} : lst{u3+u, -v3-v}, e, -M1);

	C2 = C1.subject_to(lst{C1.passing(W), C1.is_orthogonal(C, es)});
	C4 = C1.subject_to(lst{C1.passing(W), C1.passing(P), C1.is_linear()});
	u3 = C.center().op(0);
	v3 = C4.roots(u3, false).op(0).normal();
	C5 = cycle2D(lst{u3, -v3*jump_fnct(sign)}, e, C.radius_sq(e, M1)).subs(signs_cube,
                 subs_options::algebraic | subs_options::no_pattern);
	C6 = C1.subject_to(lst{C1.passing(W), C.is_f_orthogonal(C1, eps)});
	C7 = C6.subject_to(lst{C6.is_linear()});
	C8 = real_line.cycle_similarity(C, es, diag_matrix(lst{1, sign1}), diag_matrix(lst{1, jump_fnct(sign)}),
									diag_matrix(lst{1, sign1})).normalize(n*k);


	asymptote << setprecision(2);
	for (si = -1; si < 2; si++) {
		for (si1 = -1; si1 < 2; si1++) {
			sign_val = lst{sign == si, sign1 == si1};

#line 2246 "parab-ortho1.nw"
try {
	{
#line 2593 "parab-ortho1.nw"
numeric xmin(-11,4), xmax(5), ymin(-3), ymax = (si == 0?numeric(25, 4): 4);
lst cycle_val = lst{sign == numeric(si), sign1 == numeric(si1),
					k == numeric(2,3), l == numeric(2,3), n == (si == 1?numeric(-1):numeric(1,2)), m ==numeric(-2)};
cycle2D Cf = C.subs(cycle_val), Cg = C5.subs(cycle_val), Cq =C2;
lst U, V;

#line 2601 "parab-ortho1.nw"
switch (si) {
case -1: // points b, a, center, c, d
	U = {numeric(11,4), Cg.roots(half).op(0), Cf.center().op(0).subs(cycle_val), (l/k).subs(cycle_val)};
	V = {Cf.roots(U.op(0), false).op(1), half, Cf.center().op(1).subs(cycle_val),
		 C4.roots(l/k, false).op(0).normal().subs(cycle_val)};
	break;
case 0:
	U = {numeric(17,4), Cg.roots().op(0), Cf.center().op(0).subs(cycle_val), (l/k).subs(cycle_val)};
	V = {Cf.roots(U.op(0), false).op(0), numeric(3,2), Cf.roots(l/k, false).op(0).subs(cycle_val),
		 C4.roots(l/k, false).op(0).normal().subs(cycle_val)};
	break;
case 1:
	U = {numeric(12,4), Cg.roots(numeric(3,4)).op(0), Cf.center().op(0).subs(cycle_val), (l/k).subs(cycle_val)};
	V = {Cf.roots(U.op(0), false).op(0), numeric(3,4), Cf.center().op(1).subs(cycle_val),
		 C4.roots(l/k, false).op(0).normal().subs(cycle_val)};
	break;
}

#line 2621 "parab-ortho1.nw"
U.append(P.op(0).subs(cycle_val).subs(lst{u == U.op(0), v == V.op(0)}).normal());
V.append(P.op(1).subs(cycle_val).subs(lst{u == U.op(0), v == V.op(0)}).normal());

asymptote << endl <<  "erase();"  << endl <<  "size(175);"  << endl;
#line 2630 "parab-ortho1.nw"
for (int j = 0; j<2; j++)
	for (int i=0; i<(si==1?4:5); i++)
		Cq.subs(lst{k1 == (si == 0? numeric(3*i,2): numeric(i, 4)), n1 == half, u == U.op(j),
					v == V.op(j)}).subs(cycle_val).asy_draw(asymptote, xmin, xmax, ymin, ymax,
															lst{0.2, 0.2+j*(0.3+i/8.0), 0.2+(1-j)*(0.3+i/8.0)});

Cf.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0.8, 0, 0}, "1");
Cg.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 0, 0}, "0.3+dashed");
if (si == 0)
 C5.subs(lst{sign ==0, sign1==0}).subs(cycle_val).asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 0, 0},
                 "dotted");

#line 2644 "parab-ortho1.nw"
asymptote << "pair[] z={(" << ex_to<numeric>(U.op(0).evalf()).to_double() << ", "
 << ex_to<numeric>(V.op(0).evalf()).to_double() << ")";
 for (int j = 1; j<5; j++)
	 asymptote << ", (" << ex_to<numeric>(U.op(j).evalf()).to_double() << ", "
			   << ex_to<numeric>(V.op(j).evalf()).to_double() << ")" ;


asymptote << "};" << endl    << "  dot(z);" << endl
 << (si == 0? "  draw((z[2].x,0)--z[2], 0.3+dotted);" : "") << endl
 << (si == 0? "  draw((z[3].x,0)--z[3], 0.3+dotted);" : "") << endl
 << "  label(\"$a$\", z[1], NW);" << endl
   << "  label(\"$b$\", z[0], SE);" << endl
  << "  label(\"$c$\", z[3], E);" << endl
   << "  label" << "(\"$d$\", z[4], " << (si ==1?"NW);":"NE);") << endl;

#line 2669 "parab-ortho1.nw"
asymptote  << "  label(\"$\\sigma=" << si << ", \\breve{\\sigma}=" << si1
  << "$\", (0, " << ymin.to_double() << "), S);" << endl << "draw((1,-0.1)--(1,0.1));" << endl
  << "draw((-0.1,1)--(0.1,1));" << endl
  << "label(\"$1$\", (1,0), S);" << endl
  << "label(\"$1$\", (0,1), E);" << endl;

#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;


#line 2626 "parab-ortho1.nw"
asymptote << "shipout(\"first-ort-" << eph_names[si+1] << eph_names[si1+1] << "\");" << endl;

#line 2247 "parab-ortho1.nw"
                                 }
	{
#line 2683 "parab-ortho1.nw"
numeric xmin(-11,4), xmax(5), ymin(-13,4), ymax = (si == 0?numeric(6): numeric(15,4));
lst cycle_val = lst{sign == numeric(si), sign1 == numeric(si1), sign2 == numeric(1), //sign3 == jump_fnct(-si), //sign3 == (si > 0?numeric(-1):numeric(1)),
     k == numeric(2,3), l == numeric(2,3), n == (si == 1?numeric(-4,3):half), m ==(si == 1?numeric(-9,3):numeric(-2))};
cycle2D Cf = C.subs(cycle_val), Cg = C8.subs(cycle_val), Cq =C6;
lst U, V;

#line 2691 "parab-ortho1.nw"
switch (si) {
case -1: // points b, a, center, c, d
	U = {numeric(11,4), Cg.roots(half).op(0), Cf.focus().op(0).subs(cycle_val), (l/k).subs(cycle_val)};
	V = {Cf.roots(U.op(0), false).op(1), half, Cf.focus().op(1).subs(cycle_val),
		 C7.roots(l/k, false).op(0).normal().subs(cycle_val)};
	break;
case 0:
	U = {numeric(4), Cf.roots().op(0), Cf.focus().op(0).subs(cycle_val), (l/k).subs(cycle_val)};
	V = {Cf.roots(U.op(0), false).op(0), numeric(3,2), Cf.focus().op(0).subs(cycle_val),
		 C7.roots(l/k, false).op(0).normal().subs(cycle_val)};
	break;
case 1:
	U = {Cf.roots(numeric(1)).op(1), Cg.roots(numeric(6, 4)).op(1),
		 Cf.focus().op(0).subs(cycle_val), (l/k).subs(cycle_val)};
	V = {numeric(1), numeric(6, 4), Cf.focus().op(1).subs(cycle_val),
		 C7.roots(l/k, false).op(0).normal().subs(cycle_val)};
	break;
}

#line 2712 "parab-ortho1.nw"
U.append(P1.op(0).subs(cycle_val).subs(lst{u == U.op(0), v == V.op(0)}).normal()); // Moebius transform of [[U.op(0)]]
V.append(P1.op(1).subs(cycle_val).subs(lst{u == U.op(0), v == V.op(0)}).normal());

asymptote << endl << "erase();" << endl << "size(175);" << endl;
#line 2630 "parab-ortho1.nw"
for (int j = 0; j<2; j++)
	for (int i=0; i<(si==1?4:5); i++)
		Cq.subs(lst{k1 == (si == 0? numeric(3*i,2): numeric(i, 4)), n1 == half, u == U.op(j),
					v == V.op(j)}).subs(cycle_val).asy_draw(asymptote, xmin, xmax, ymin, ymax,
															lst{0.2, 0.2+j*(0.3+i/8.0), 0.2+(1-j)*(0.3+i/8.0)});

Cf.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0.8, 0, 0}, "1");
Cg.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 0, 0}, "0.3+dashed");
if (si == 0)
 C5.subs(lst{sign ==0, sign1==0}).subs(cycle_val).asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 0, 0},
                 "dotted");

#line 2644 "parab-ortho1.nw"
asymptote << "pair[] z={(" << ex_to<numeric>(U.op(0).evalf()).to_double() << ", "
 << ex_to<numeric>(V.op(0).evalf()).to_double() << ")";
 for (int j = 1; j<5; j++)
	 asymptote << ", (" << ex_to<numeric>(U.op(j).evalf()).to_double() << ", "
			   << ex_to<numeric>(V.op(j).evalf()).to_double() << ")" ;


asymptote << "};" << endl    << "  dot(z);" << endl
 << (si == 0? "  draw((z[2].x,0)--z[2], 0.3+dotted);" : "") << endl
 << (si == 0? "  draw((z[3].x,0)--z[3], 0.3+dotted);" : "") << endl
 << "  label(\"$a$\", z[1], NW);" << endl
   << "  label(\"$b$\", z[0], SE);" << endl
  << "  label(\"$c$\", z[3], E);" << endl
   << "  label" << "(\"$d$\", z[4], " << (si ==1?"NW);":"NE);") << endl;

#line 2669 "parab-ortho1.nw"
asymptote  << "  label(\"$\\sigma=" << si << ", \\breve{\\sigma}=" << si1
  << "$\", (0, " << ymin.to_double() << "), S);" << endl << "draw((1,-0.1)--(1,0.1));" << endl
  << "draw((-0.1,1)--(0.1,1));" << endl
  << "label(\"$1$\", (1,0), S);" << endl
  << "label(\"$1$\", (0,1), E);" << endl;

#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;


#line 2717 "parab-ortho1.nw"
asymptote << "shipout(\"sec-ort-" << eph_names[si+1] << eph_names[si1+1] << "\");" << endl;

#line 2248 "parab-ortho1.nw"
                                 }
} catch  (exception &p) {
	cerr << "*****       Got a problem with drawing " <<  p.what() << endl;
}
}
}

#line 2258 "parab-ortho1.nw"
try {
	
#line 2724 "parab-ortho1.nw"
 numeric xmin(-5), xmax(5), ymin(-13,4), ymax = numeric(6);
 
#line 2742 "parab-ortho1.nw"
asymptote << endl << "erase();" << endl << "size(250);" << endl;
cycle2D C1f, C2f;
asymptote << "pair[] z;";
for (int j = -1; j<2; j++) {
 C1f = cycle2D(1, lst{-2.5, 1}, 3.75, diag_matrix(lst{-1, j}));
 C2f = cycle2D(1, lst{2.75, 3}, 14.0625, diag_matrix(lst{-1, j}));
 C1f.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 1.0-0.4*(j+1), 0.4*(j+1)}, ".75", true, 7);
 C2f.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 1.0-0.4*(j+1), 0.4*(j+1)}, ".75", true, 7);
 asymptote << "z.push((" << C1f.center().op(0) << ", "  << C1f.center().op(1) << ")); z.push(("
     << C2f.center().op(0) << ", "  << C2f.center().op(1) << "));" << endl;
}
asymptote << "z.push((" << C1f.roots().op(0) << ", 0));  z.push((" << C1f.roots().op(1) << ", 0));" << endl
  << " dot(z);" << endl
  << "  for (int j = 0; j<2; ++j) {"
  << "    label(\"$c_e$\", z[j], E);" << endl
  << "    label(\"$c_p$\", z[j+2], SE);" << endl
  << "    label(\"$c_h$\", z[j+4], E);" << endl
  << "    label((j==0?\"$r_0$\":\"$r_1$\"), z[j+6], (j==0? SW: SE));" << endl
  << "    draw(z[j]--z[j+4], .3+dashed);" << endl
  << "  }" << endl;
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2763 "parab-ortho1.nw"
asymptote << "shipout(\"same-cycle\");" << endl;

#line 2726 "parab-ortho1.nw"
 
#line 2771 "parab-ortho1.nw"
asymptote << endl << "erase();" << endl << "size(250);" << endl;
C1f = cycle2D(1, lst{-1.5, 2}, 3.75, par_matr);
C2f = cycle2D(1, lst{2, 2}, -3.5, par_matr);
C1f.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 1.0-0.4, 0.4}, ".75", true, 7);
C2f.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 1.0-0.4, 0.4}, ".75", true, 7);

asymptote << "pair[] z= {(" << C1f.center(-unit_matrix(2)).op(0) << ", "  << C1f.center(-unit_matrix(2)).op(1)
 << "), (" << C2f.center(-unit_matrix(2)).op(0) << ", "  << C2f.center(-unit_matrix(2)).op(1) << "), ";
for (int j = -1; j<2; j++) {
 ex MS = diag_matrix(lst{-1, j});
 lst F1 =  ex_to<lst>(C1f.focus(MS)),   F2 = ex_to<lst>(C2f.focus(MS));
 asymptote << "   (" << F1.op(0) << ", "  << F1.op(1) << "), ("
     << F2.op(0) << ", "  << F2.op(1) << ")" << (j==1? "};" : "," ) << endl;
}
asymptote << " dot (z);" << endl
  << " draw(z[0]--z[1], dashed);" << endl;

asymptote << "for (int j=1; j<3; ++j) {" << endl
 << "  label(\"$c_e$\", z[j-1], N);" << endl
 << "  label(\"$f_e$\", z[j+1], E);" << endl
 << "  label(\"$f_p$\", z[j+3], E);" << endl
 << "  label(\"$f_h$\", z[j+5], E);" << endl
 << " draw(z[j+1]--z[j+5], dotted+0.5);" << endl
 << "}" << endl;
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2796 "parab-ortho1.nw"
asymptote << "shipout(\"parab-cent\");" << endl;

#line 2727 "parab-ortho1.nw"
 
#line 2805 "parab-ortho1.nw"
asymptote << endl << "erase();" << endl << "size(250);" << endl
 << "pair[] z;" << endl;
{
	numeric xmin(-5), xmax(15), ymin(-5), ymax(5);
	for (int i1=-1; i1<2; i1++) {
		for(int i2=-1; i2<2; i2++) {
			lst val=lst{sign==i1, sign1==i2, u==6*i1+4, v==1.7};
			Z1.subs(val).asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0.5+0.4*i1, .5-0.3*i2, 0.5+0.3*i2},"", true, 7);
			asymptote << "dot((" << ex_to<numeric>(Z1.focus(e).op(0).subs(val)).to_double()
					  << ", "<< ex_to<numeric>(Z1.focus(e).op(1).subs(val)).to_double()
					  << "), " << 0.4+0.4*i1 << "red+"
					  <<  .4-0.3*i2 << "green+"
					  << 0.6+0.3*i2 << "blue);" << endl;
		}
	}
	
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2821 "parab-ortho1.nw"
}
asymptote << "shipout(\"zero-cycles\");" << endl;


#line 2728 "parab-ortho1.nw"
 
#line 2831 "parab-ortho1.nw"
asymptote << endl << "erase();" << endl << "size(250);" << endl;
C10 = cycle2D(1, lst{(-4-1)/2.0, 0.5}, 4,par_matr);
C10.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0.1, 0, 0.6});
asymptote << "pair[] z = {(" << C10.roots().op(0) << ", 0), (" << C10.roots().op(1) << ", 0)};" << endl;
cycle2D(1, lst{5/2.0, 0.5}, 8,par_matr).asy_draw(asymptote, xmin, xmax, ymin, ymax,
                  lst{0.1, 0.6, 0}, "", true, 7);
C10 =cycle2D(-1, lst{-5/2.0, 0.5}, 8-5.0*5/2.0,par_matr);
C10.asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0.1, 0.6, 0},
"dashed ", true, 7);
asymptote << "z.push((" << C10.roots().op(1) << ", 0)); z.push((" << C10.roots().op(0) << ", 0));" << endl;
#line 2847 "parab-ortho1.nw"
asymptote  << "z.push((z[2].x,0)); z.push((z[3].x,0));" << endl
  << " dot(z);" << endl
  << " draw(z[2]--z[3], black+.3);" << endl
  << " draw(z[0]--z[1], black+1.2);" << endl
  << " draw(z[4]--z[5], black+1.2);" << endl
  << "  label(\"$z_1$\", z[0], NW);" << endl
  << "  label(\"$z_2$\", z[1], SE);" << endl
  << "  label(\"$z_3$\", z[2], SW);" << endl
  << "  label(\"$z_4$\", z[3], SE);" << endl;

#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2843 "parab-ortho1.nw"
asymptote << "shipout(\"parab-diam\");" << endl;

#line 2729 "parab-ortho1.nw"
 
#line 2867 "parab-ortho1.nw"
asymptote << endl << "erase();" << endl << "size(250);" << endl;
for (int j=-2; j < 3; j++) {
	ex_to<cycle2D>(C.subject_to(lst{C.passing(lst{xmin+1, ymax-5}), C.passing(lst{xmin+3, ymax-6.5}), k == 1,
					l == xmin+2+0.5*j}).subs(sign == -1)).asy_draw(asymptote, xmin, xmax, ymin, ymax,
																   lst{0, 0.4*abs(j), 1.0-0.4*abs(j)}, (j == 0 ? "1" : ".3"));
	ex_to<cycle2D>(C.subject_to(lst{C.passing(lst{xmax-4, ymax-5}), C.passing(lst{xmax-1, ymax-2}), k == 1,
					l == xmax-2.5-0.2*(j+2)}).subs(sign == 0)).asy_draw(asymptote, xmin, xmax, ymin, ymax,
																		lst{0.2*(j+2), 0, 1.0-0.2*(j+2)}, (j == -2 ? "1" : ".3"), true, 7);
}

#line 2879 "parab-ortho1.nw"
asymptote << "pair[] z ={ (" << xmin+1 << ", " << ymax-5 << "),  (" << xmin+3 << ", "
										 << ymax-6.5 << "),  (" << xmax-4 << ", " << ymax-5 << "),  (" << xmax-1
										 << ", " << ymax-2 << ")};" << endl;
#line 2847 "parab-ortho1.nw"
asymptote  << "z.push((z[2].x,0)); z.push((z[3].x,0));" << endl
  << " dot(z);" << endl
  << " draw(z[2]--z[3], black+.3);" << endl
  << " draw(z[0]--z[1], black+1.2);" << endl
  << " draw(z[4]--z[5], black+1.2);" << endl
  << "  label(\"$z_1$\", z[0], NW);" << endl
  << "  label(\"$z_2$\", z[1], SE);" << endl
  << "  label(\"$z_3$\", z[2], SW);" << endl
  << "  label(\"$z_4$\", z[3], SE);" << endl;

#line 2883 "parab-ortho1.nw"
asymptote << "  label(\"$d_e$\", .5z[0]+.5z[1], NE);" << endl
										 << "  label(\"$d_p$\", .5z[4]+.5z[5], S);" << endl;
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2886 "parab-ortho1.nw"
asymptote << "shipout(\"dist-extr\");" << endl;

#line 2730 "parab-ortho1.nw"
 
#line 2895 "parab-ortho1.nw"
asymptote << endl << "erase();" << endl  << "size(250);" << endl;
for (int j=1; j < 5; j++) {
 cycle2D(lst{-2.5, 4.5}, -unit_matrix(2), 16.0*GiNaC::pow(2, -2*j)).asy_draw(asymptote, xmin, xmax, ymin, ymax,
                     lst{0, 0.2*abs(j), 1.0-0.2*abs(j)}, ".3");
 cycle2D(lst{1, 1.25}, hyp_matr, 25*GiNaC::pow(1.8, -2*j)).asy_draw(asymptote, xmin, xmax, ymin, ymax/3,
                     lst{0.2*abs(j), 1.0-0.2*abs(j), 0}, ".3", true, 5+j);
 cycle2D(1, lst{2, GiNaC::pow(3,-j)}, 2*2+2.0*GiNaC::pow(3,-j)-GiNaC::pow(3,-2*j), par_matr)
	 .asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{1.0-0.17*j, 0, 0.17*j}, ".3", true, 7);
}
asymptote  << " draw((2,1)--(2," << ymax << "), blue+1);" << endl;
cycle2D(lst{1, 1.25}, hyp_matr).asy_draw(asymptote, xmin, xmax, ymin, ymax/3, lst{1, 0, 0}, "1");
asymptote  << " dot((-2.5,4.5));" << endl
  << " dot((2,1));" << endl;
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2909 "parab-ortho1.nw"
asymptote << "shipout(\"infinites\");" << endl;

#line 2731 "parab-ortho1.nw"
 
#line 2918 "parab-ortho1.nw"
xmin = -numeric(4,2); xmax=numeric(4,2); ymin=-numeric(7,2); ymax=numeric(3);
cycle2D C10f, UC;
C10f  = cycle2D(1, lst{0, sign2}, sign, e);
UC=real_line.cycle_similarity(C10f, es).normalize();

#line 2925 "parab-ortho1.nw"
for (si=-1; si<2; si++) {
 for (si1=-1; si1<2; si1++)
  if ((si ==0 ) || (si == si1)) {
   asymptote << endl << "erase();" << endl << "size(250);" << endl;
   for (int si2=-1; si2<2; si2=si2+2) {
    lst cycle_val = lst{sign == si, sign1 == si1, sign2==si2};

#line 2935 "parab-ortho1.nw"
    if (si != 0 ) {
     ex_to<cycle2D>(UC.subs(cycle_val, subs_options::algebraic | subs_options::no_pattern))
      .asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 0, 0.7}, "1.5", true, 7);
     C10f.subs(cycle_val, subs_options::algebraic | subs_options::no_pattern).normalize()
      .asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 0.7, 0}, (si2 ==si1 ? "1" : "Dotted "), true, 7);

#line 2943 "parab-ortho1.nw"
    } else
     ex_to<cycle2D>(cayley_parab(real_line,sign1).subs(cycle_val, subs_options::algebraic | subs_options::no_pattern))
      .asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{0, 0, 0.7}, "1.5", true, 7);
   }

#line 2950 "parab-ortho1.nw"
   
#line 2669 "parab-ortho1.nw"
asymptote  << "  label(\"$\\sigma=" << si << ", \\breve{\\sigma}=" << si1
  << "$\", (0, " << ymin.to_double() << "), S);" << endl << "draw((1,-0.1)--(1,0.1));" << endl
  << "draw((-0.1,1)--(0.1,1));" << endl
  << "label(\"$1$\", (1,0), S);" << endl
  << "label(\"$1$\", (0,1), E);" << endl;

#line 2951 "parab-ortho1.nw"
      
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2952 "parab-ortho1.nw"
   asymptote << "shipout(\"cayley-"<< eph_names[si+1] << eph_names[si1+1]<<"\");" << endl;
  }
}

#line 2732 "parab-ortho1.nw"
 
#line 2963 "parab-ortho1.nw"
xmin=-2; xmax=2; ymin=-2; ymax=2;
C2=cycle2D(lst{0,(1-abs(sign))/2},e, 1);
C3=cycle2D(0,lst{l,n},m,e);
asymptote << endl << "erase();" << endl << "size(250);" << endl;
for(double i=-4; i<=4; i+=.4) {
 C3.subs(lst{sign==-1, l==0, n==1, m==i}).asy_draw(
  asymptote, xmin, xmax, ymin, ymax, lst{0.5, .75, 0.5},"0.25pt", true, 7);
 C3.subs(lst{sign==-1, l==1, n==0, m==i}).asy_draw(
  asymptote, xmin, xmax, ymin, ymax, lst{0.5, .5, 0.75},"0.25pt", true, 7);
}
C2.subs(sign==-1).asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{1,0,0},".75pt", true, 7);
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2975 "parab-ortho1.nw"
asymptote << "shipout(\"pre-invers\");" << endl;

#line 2980 "parab-ortho1.nw"
C4=C3.cycle_similarity(C2);
for(int si=-1; si<2; si++) {
	asymptote << endl << "erase();" << endl << "size(250);" << endl;
	for(double i=-4; i<=4; i+=.4) {
		C4.subs(lst{sign==si, l==0, n==1, m==i}).asy_draw(
			asymptote, xmin, xmax, ymin, ymax, lst{0.5, .75, 0.5},"0.25pt", true, 9);
		C4.subs(lst{sign==si, l==1, n==0, m==i}).asy_draw(
			asymptote, xmin, xmax, ymin, ymax, lst{0.5, .5, 0.75},"0.25pt", true, 9);
	}
	C2.subs(sign==si).asy_draw(asymptote, xmin, xmax, ymin, ymax, lst{1,0,0},".75pt", true, 7);

#line 2993 "parab-ortho1.nw"
	ex_to<cycle2D>(Zinf.cycle_similarity(C2)).subs(sign==si).asy_draw(
		asymptote, xmin, xmax, ymin, ymax, lst{0,0,1}, (si==-1? "3pt": ".75pt"));
	
#line 2664 "parab-ortho1.nw"
asymptote << "  draw_axes((" << xmin.to_double() << ", " << ymin.to_double()
 << "), ( " << xmax.to_double() << ", " << ymax.to_double() << "));" << endl;

#line 2996 "parab-ortho1.nw"
	asymptote << "shipout(\"inversion-" << eph_names[si+1] << "\");" << endl;
}


#line 2733 "parab-ortho1.nw"
 
#line 3009 "parab-ortho1.nw"
const int frames=20, balls=10; // number of frames and balls
const double r1=.1, r2=1, tmin=-3, tmax=3, // limits of balls' filling and inversions
    step2=(r2-r1)/(balls-1); // steps between balls

#line 3015 "parab-ortho1.nw"
ofstream asymptote("ball-inv-d.asy");
asymptote << setprecision(2);
const numeric scale=2.5; //size of the picture
asymptote << "scale = " << scale << ";" << endl;

#line 3022 "parab-ortho1.nw"
	matrix T=matrix(2, 2, lst{dirac_ONE(), -t*e.subs(mu_subs), t*e.subs(mu_subs), dirac_ONE()});
	const cycle2D Hyp=cycle2D(lst{0,0},e, a).matrix_similarity(T);

#line 3028 "parab-ortho1.nw"
for (int j=0; j<=2*frames ;j++ ) {
 double tval=(j==0 && j==2*frames ? 0 :
     (j==frames ? 10000000 :
      ex_to<numeric>((j<frames ? exp(tmin+j*(tmax-tmin)/(frames-2)) :
					  -GiNaC::exp(tmin+(2*frames-j)*(tmax-tmin)/(frames-2))).evalf()).to_double()));

#line 3037 "parab-ortho1.nw"
 for (int i=0; i <balls; i++) {
	 Hyp.subs(lst{sign==1, a==GiNaC::pow(r1+i*step2,2), t==tval}).asy_draw(asymptote, "pa",
   -scale, scale, -scale, scale, lst{0.1+0.8*i/balls, 0, 0.9-0.8*i/balls});
	 Hyp.subs(lst{sign==1, a==GiNaC::pow(r1+i*step2,2), t==tval}).asy_draw(asymptote, "pb",
   -scale, scale, -scale, scale, lst{0.1+0.8*i/balls, 0, 0.9-0.8*i/balls});
 }

#line 3046 "parab-ortho1.nw"
 Hyp.subs(lst{sign==1, a==1, t==tval}).asy_draw(asymptote, "pa",
  -scale, scale, -scale, scale, lst{1,0,0},"2pt");
 Hyp.subs(lst{sign==1, a==1, t==tval}).asy_draw(asymptote, "pb",
  -scale, scale, -scale, scale, lst{1,0,0},"2pt");
 asymptote << "newpic();" << endl  << endl ;
}

#line 3055 "parab-ortho1.nw"
asymptote.close();



#line 2260 "parab-ortho1.nw"
} catch  (exception &p) {
	cerr << "*****       Got a problem with extra drawing " <<  p.what() << endl;
}
asymptote.close();
}

#line 948 "parab-ortho1.nw"
}

