# $Id: Makefile.am,v 1.2 2001/11/02 13:33:21 christof Exp $

bin_PROGRAMS = arkanum_exp

%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

arkanum_exp_SOURCES= $(BUILT_SOURCES)

#arkanum_exp_LDADD = @LIBS@ @COMMONXX_LIBS@

BUILT_SOURCES=arkanum_exp.cc
LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old
LIBS=@LIBS@ @COMMONXX_LIBS@
