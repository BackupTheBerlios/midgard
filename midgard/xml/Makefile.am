# $Id: Makefile.am,v 1.1 2001/11/02 12:52:20 christof Exp $

bin_PROGRAMS = arkanum_exp

%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

arkanum_exp_SOURCE= $(BUILT_SOURCES)

#arkanum_exp_LDADD = @LIBS@ @COMMONXX_LIBS@

BUILT_SOURCES=arkanum_exp.cc
LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old
LIBS=@LIBS@ @COMMONXX_LIBS@
