# $Id: Makefile.am,v 1.20 2002/01/02 15:21:43 christof Exp $

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

export: $(EXTRA_PROGRAMS)
	./arkanum_exp >../../midgard-xml/Arkanum.xml
	./all_exp K >../../midgard-xml/KanThaiPan.xml
	./all_exp R >../../midgard-xml/Rawindra.xml
	./all_exp A >../../midgard-xml/Alba.xml
	./all_exp "B&R" >../../midgard-xml/BarbarenWutRitterEhre.xml
	./all_exp "H&D" >../../midgard-xml/HexenzauberDruidenkraft.xml
	./all_exp G >../../midgard-xml/Gildenbrief.xml
	./all_exp   >../../midgard-xml/Regelwerk4.xml
	./all_exp 3 >../../midgard-xml/Regelwerk3.xml
#	./all_exp 2 >../../midgard-xml/Regelwerk2.xml
