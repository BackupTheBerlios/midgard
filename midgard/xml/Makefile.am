# $Id: Makefile.am,v 1.3 2001/11/02 14:27:34 christof Exp $

bin_PROGRAMS = arkanum_exp kido_exp

%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

arkanum_exp_SOURCES= arkanum_exp.cc
kido_exp_SOURCES= kido_exp.cc

BUILT_SOURCES=arkanum_exp.cc kido_exp.cc

LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ $(BUILT_SOURCES) 
LIBS=@LIBS@ @COMMONXX_LIBS@
