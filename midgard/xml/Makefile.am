# $Id: Makefile.am,v 1.13 2001/11/30 17:20:27 christof Exp $

noinst_PROGRAMS = all_exp 
EXTRA_PROGRAMS = arkanum_exp kido_exp fertigk_exp land_sprache_exp waffen_exp

%_nm.o: %_exp.cc ; $(COMPILE.cc) -DXML_NO_MAIN $(OUTPUT_OPTION) $<
%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

arkanum_exp_SOURCES= arkanum_exp.cc export_common.cc
kido_exp_SOURCES= kido_exp.cc export_common.cc
fertigk_exp_SOURCES= fertigk_exp.cc export_common.cc
land_sprache_exp_SOURCES= land_sprache_exp.cc export_common.cc
waffen_exp_SOURCES=waffen_exp.cc export_common.cc
all_exp_SOURCES=all_exp.cc export_common.cc

all_exp_LDADD=arkanum_nm.o kido_nm.o fertigk_nm.o land_sprache_nm.o \
	waffen_nm.o
all_exp_DEPENDENCIES=$(all_exp_LDADD)

BUILT_SOURCES=arkanum_exp.cc kido_exp.cc fertigk_exp.cc land_sprache_exp.cc \
	waffen_exp.cc

LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ $(BUILT_SOURCES) 
LIBS=@LIBS@ @COMMONXX_LIBS@

export: $(noinst_PROGRAMS)
#	./arkanum_exp >../../midgard-xml/Arkanum.xml
#	./kido_exp >../../midgard-xml/KiDo.xml
#	./fertigk_exp >../../midgard-xml/Fertigkeiten.xml
#	./land_sprache_exp >../../midgard-xml/Land_Sprache.xml
#	./waffen_exp >../../midgard-xml/Waffen.xml
	./all_exp >../src/midgard.xml
