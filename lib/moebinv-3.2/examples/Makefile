#
# generic Makefile 
# (add it to, or add to it, whatever you like)
#
#======================================================================

CFLAGS=-ggdb3  -Wall -I./ -I/usr/local/include -L./ -c
LDLIBS = -lcln -lginac -lcycle  -lfigure
CPPFLAGS =  -ggdb3 -Wall -std=gnu++11  -I./ -I../include -I/usr/local/include  -fdiagnostics-color
LDFLAGS =  -L./  -L/usr/lib  -L/usr/local/lib -L../src

MLIB = -lm
RM = rm
RMFLAGS = -v -f
LATEX = latex

GXX = g++
CC=gcc
#======================================================================

.SUFFIXES: .cpp

default:
	make hello-cycle
	@echo
	@echo 'The example is compiled. Make sure that  libraries libcycle.so and libfigure.so'
	@echo 'are within LD_LIBRARY_PATH, e.g. you may need to execute'
	@echo '$$ export LD_LIBRARY_PATH=../src:$$LD_LIBRARY_PATH'
	@echo 'and then try to run'
	@echo '$$ ./hello-cycle'

