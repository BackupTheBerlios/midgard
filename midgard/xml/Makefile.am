# $Id: Makefile.am,v 1.24 2002/01/19 11:21:37 christof Exp $

EXTRA_PROGRAMS = all_exp arkanum_exp 

#MIDGARD3=$(shell if test `hostname` = "puck" ; then echo -DMIDGARD3 ; fi)

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ $(MIDGARD3) -DREGION

common_sources = export_common.cc common_exp.cc zauber_exp.cc 
arkanum_exp_SOURCES= arkanum_exp.cc $(common_sources)
all_exp_SOURCES=all_exp.cc $(common_sources) \
	kido_exp.cc fertigk_exp.cc land_sprache_exp.cc waffen_exp.cc

LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ $(BUILT_SOURCES) 
LIBS=@LIBS@ @COMMONXX_LIBS@

XMLDIR=../../midgard-xml

export: all_exp arkanum_exp
	./arkanum_exp >$(XMLDIR)/Arkanum.xml
	./all_exp K >$(XMLDIR)/KanThaiPan.xml
	./all_exp R >$(XMLDIR)/Rawindra.xml
	./all_exp A >$(XMLDIR)/Alba.xml
	./all_exp E >$(XMLDIR)/Eschar.xml
	./all_exp "B&R" >$(XMLDIR)/BarbarenWutRitterEhre.xml
	./all_exp "H&D" >$(XMLDIR)/HexenzauberDruidenkraft.xml
	./all_exp G >$(XMLDIR)/Gildenbrief.xml
	./all_exp   >$(XMLDIR)/Regelwerk4.xml
	./all_exp 3 >$(XMLDIR)/Regelwerk3.xml
#	./all_exp 2 >$(XMLDIR)/Regelwerk2.xml
