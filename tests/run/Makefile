#
# (GNU) Makefile for UN*X-like systems
# This makefile shows how to make a different runner for each test
#

.PHONY: all clean

all: run

clean:
	rm -f *~ *.cpp *.o runner

CXXTESTDIR   = ../../../cxxtest
CXXTESTGEN   = $(CXXTESTDIR)/bin/cxxtestgen
CXXTESTFLAGS = --have-eh --abort-on-fail

ALP_DIR     = ../../main

TESTS = $(wildcard ../*Test.h)
OBJS  = runner.o $(TESTS:../%.h=%.o) 

run: runner
	./runner

runner: $(OBJS)
	c++ -o $@ $^

%.o: %.cpp
	c++ -c -o $@ -I $(CXXTESTDIR) -I .. -I $(ALP_DIR) $^

%.cpp: ../%.h
	$(CXXTESTGEN) $(CXXTESTFLAGS) --part -o $@ $^

runner.cpp:
	$(CXXTESTGEN) $(CXXTESTFLAGS) --root --error-printer -o $@

#
# Local Variables:
# compile-command: "make -fMakefile.unix"
# End:
#