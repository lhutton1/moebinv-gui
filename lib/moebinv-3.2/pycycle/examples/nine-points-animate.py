#!/usr/bin/python
# This script produces an animated transtion from the 
# traditional nine-points theorem to its conformal version
from cginac import *
from ccycle import *
from cfigure import *
SF=midpoint_constructor()

# Initial figure is freezed
F=figure([-1,-1]).freeze()

# Three points defining the triangle
A=F.add_point([-numeric(10,10),numeric(0,1)],"A")
B=F.add_point([numeric(10,10),numeric(0,1)],"B")
C=F.add_point([-numeric(1,5),-numeric(3,2)],"C")

# The parameter t define a movement of N from infinity to the finite position
t=realsymbol("t")
N=F.add_point([(1.0+t)/2.0,-(5.0+t)/2.0],"N")

# Three sides of the triangle
a=F.add_cycle_rel([is_orthogonal(B),is_orthogonal(C),is_orthogonal(N)],"a")
b=F.add_cycle_rel([is_orthogonal(C),is_orthogonal(A),is_orthogonal(N)],"b")
c=F.add_cycle_rel([is_orthogonal(A),is_orthogonal(B),is_orthogonal(N)],"c")
F.set_asy_style(a,"rgb(0,0,.8)+1")
F.set_asy_style(b,"rgb(0,0,.8)+1")
F.set_asy_style(c,"rgb(0,0,.8)+1")

# Three altitudes 
ha=F.add_cycle_rel([is_orthogonal(A),is_orthogonal(N),is_orthogonal(a)],"h_a")
F.set_asy_style(ha,"dashed")
hb=F.add_cycle_rel([is_orthogonal(B),is_orthogonal(N),is_orthogonal(b)],"h_b")
F.set_asy_style(hb,"dashed")
hc=F.add_cycle_rel([is_orthogonal(C),is_orthogonal(N),is_orthogonal(c)],"h_c")
F.set_asy_style(hc,"dashed")

# The bases of the altitudes
A1=symbol("A_h")
B1=symbol("B_h")
C1=symbol("C_h")
F.add_cycle_rel([is_orthogonal(a),is_orthogonal(ha),is_orthogonal(A1),is_adifferent(N)],A1)
F.add_cycle_rel([is_orthogonal(b),is_orthogonal(hb),is_adifferent(N),is_orthogonal(B1)],B1)
F.add_cycle_rel([is_adifferent(N),is_orthogonal(c),is_orthogonal(hc),is_orthogonal(C1)],C1)

# The nin-point circle
p=F.add_cycle_rel([is_orthogonal(A1),is_orthogonal(B1),is_orthogonal(C1)],"p")
F.set_asy_style(p,"rgb(0,.8,0)+1")

# Outer tangent circles
Va=F.add_cycle_rel([is_tangent_i(a),is_tangent_i(b),is_tangent_o(c)],"v_a")
F.set_asy_style(Va,"rgb(0.8,0,0)+.5")
Vb=F.add_cycle_rel([is_tangent_i(a),is_tangent_o(b),is_tangent_i(c)],"v_b")
F.set_asy_style(Vb,"rgb(0.8,0,0)+.5")
Vc=F.add_cycle_rel([is_tangent_i(a),is_tangent_i(b),is_tangent_i(c)],"v_c")
F.set_asy_style(Vc,"rgb(0.8,0,0)+.5")

# The midpoints of the sides
A2=F.add_subfigure(SF,[B,C,N],"A_m")
B2=F.add_subfigure(SF,[C,A,N],"B_m")
C2=F.add_subfigure(SF,[A,B,N],"C_m")

# The intersection point of altitudes
O=symbol("O")
F.add_cycle_rel([is_orthogonal(ha),is_orthogonal(hb),is_orthogonal(O),is_adifferent(N)],O)

# Midpoints between O and the triangle's vertices
A3=F.add_subfigure(SF,[O,A,N],"A_d")
B3=F.add_subfigure(SF,[B,O,N],"B_d")
C3=F.add_subfigure(SF,[C,O,N],"C_d")

# The list of values for the parameter t
val=[]
num=15
for i in range(num,10,-1):
    val.append(t==exp(i*.13*i/num).evalf()-1.0)

# Animation is created!
F.subs(t==1).asy_write(600,-3.1,2.4,-3.6,1.3,"nine-points")
F.asy_animate(val,600,-3.1,2.4,-3.6,1.3,"nine-points-anim", "gif")
