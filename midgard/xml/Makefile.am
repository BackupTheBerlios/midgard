# $Id: Makefile.am,v 1.5 2001/11/13 08:35:12 christof Exp $

bin_PROGRAMS = arkanum_exp kido_exp fertigk_exp

%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

arkanum_exp_SOURCES= arkanum_exp.cc
kido_exp_SOURCES= kido_exp.cc
fertigk_exp_SOURCES= fertigk_exp.cc

BUILT_SOURCES=arkanum_exp.cc kido_exp.cc fertigk_exp.cc

LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ $(BUILT_SOURCES) 
LIBS=@LIBS@ @COMMONXX_LIBS@

export: arkanum_exp kido_exp fertigk_exp
	./arkanum_exp >../../midgard-xml/Arkanum.xml
	./kido_exp >../../midgard-xml/KiDo.xml
	./fertigk_exp >../../midgard-xml/Fertigkeiten.xml
