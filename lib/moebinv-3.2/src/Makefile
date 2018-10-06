#
# generic Makefile 
# (add it to, or add to it, whatever you like)
#
#======================================================================

CFLAGS=-ggdb3  -Wall -I./ -I/usr/local/include -L./ -c
LDLIBS_cycle = -lcln -lginac
LDLIBS_figure = -lcln -lginac -lcycle
CPPFLAGS =  -ggdb3 -Wall -std=gnu++11  -I./ -I../include -I/usr/local/include  -fdiagnostics-color
LDFLAGS =  -L./  -L/usr/lib  -L/usr/local/lib 

GXX = g++
CC=gcc
#======================================================================

.SUFFIXES: .h .cpp

lib%.so: %.cpp
	$(GXX) $(CPPFLAGS) -c -fPIC  $*.cpp -o $*.o
	$(GXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS_$*) --verbose -shared -o $@ $*.o

default:
	make libcycle.so
	make libfigure.so
	@echo
	@echo "Libraries are build. Make sure that header files cycle.h and figure.h"
	@echo "are within INCLUDE scope and libraries libcycle.so and libfigure.so"
	@echo "are within LD_LIBRARY_PATH".

