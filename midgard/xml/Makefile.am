# $Id: Makefile.am,v 1.21 2002/01/08 08:40:27 christof Exp $

EXTRA_PROGRAMS = all_exp arkanum_exp kido_exp fertigk_exp land_sprache_exp waffen_exp

%_nm.o: %_exp.cc ; $(COMPILE.cc) -DXML_NO_MAIN $(OUTPUT_OPTION) $<
%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

#MIDGARD3=$(shell if test `hostname` = "puck" ; then echo -DMIDGARD3 ; fi)

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\" $(MIDGARD3) \
           -DREGION

common_sources = export_common.cc common_exp.cc
arkanum_exp_SOURCES= arkanum_exp.cc $(common_sources)
kido_exp_SOURCES= kido_exp.cc $(common_sources)
fertigk_exp_SOURCES= fertigk_exp.cc $(common_sources)
land_sprache_exp_SOURCES= land_sprache_exp.cc $(common_sources)
waffen_exp_SOURCES=waffen_exp.cc $(common_sources)
all_exp_SOURCES=all_exp.cc $(common_sources)

all_exp_LDADD=arkanum_nm.o kido_nm.o fertigk_nm.o land_sprache_nm.o \
	waffen_nm.o
all_exp_DEPENDENCIES=$(all_exp_LDADD)

LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ $(BUILT_SOURCES) 
LIBS=@LIBS@ @COMMONXX_LIBS@

#export: $(EXTRA_PROGRAMS)
#	./all_exp >../src/midgard.xml
# upps, das ist von früher übrig geblieben

XMLDIR=../../midgard-xml

export: $(EXTRA_PROGRAMS)
	./arkanum_exp >$(XMLDIR)/Arkanum.xml
	./all_exp K >$(XMLDIR)/KanThaiPan.xml
	./all_exp R >$(XMLDIR)/Rawindra.xml
	./all_exp A >$(XMLDIR)/Alba.xml
	./all_exp "B&R" >$(XMLDIR)/BarbarenWutRitterEhre.xml
	./all_exp "H&D" >$(XMLDIR)/HexenzauberDruidenkraft.xml
	./all_exp G >$(XMLDIR)/Gildenbrief.xml
	./all_exp   >$(XMLDIR)/Regelwerk4.xml
	./all_exp 3 >$(XMLDIR)/Regelwerk3.xml
#	./all_exp 2 >$(XMLDIR)/Regelwerk2.xml
