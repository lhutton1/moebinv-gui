#!/usr/bin/python
# This script shows a basic usage of figure library
from cginac import *
from ccycle import *
from cfigure import *

# Initial figure is freezed
F=figure()

# Add two points
A=F.add_point([1,.5],"A")
B=F.add_point([-1.2,1.4],"B")

# Add a straight line passing both points
a=F.add_cycle_rel([is_orthogonal(A),is_orthogonal(B),is_orthogonal(F.get_infinity())],"a")

# Add a Lobachevski line passing both points
b=F.add_cycle_rel([is_orthogonal(A),is_orthogonal(B),is_orthogonal(F.get_real_line())],"b")

# Output data from the figure
print F.string()

# Ask asymptote to draw the figure
F.asy_write(300,-2.5,3.3,-3,3,"lobachevsky-line")
