#!/usr/bin/python
# This script shows a basic usage of figure library
from cginac import *
from ccycle import *
from cfigure import *

# Initiate a figure
F=figure([-1,-1])

# Get access to the predefined real line and infinity
RL=F.get_real_line()
inf=F.get_infinity()

# Specify a cycle by its parameters
A=F.add_cycle(cycle(1,[3,2],12),"A")

# Add a point
B=F.add_point([0,1],"B")

# Add a cycle by its relations to the existing objects
# since it s orthogonal to the real line---it is a Lobachevsky line
d=F.add_cycle_rel([is_orthogonal(A),is_orthogonal(B),is_orthogonal(RL)],"d")

# Add a straight line
e=F.add_cycle_rel([is_orthogonal(A),is_orthogonal(B),is_orthogonal(inf)],"e")

# Output data from the figure
print F.string()

# Ask asymptote to draw the figure
F.asy_write(300,-1.5,5,-5,5,"figure-example")
