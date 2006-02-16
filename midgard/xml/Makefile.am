# $Id: Makefile.am,v 1.47 2006/02/16 18:39:09 christof Exp $

EXTRA_PROGRAMS = all_exp arkanum_exp 

pkgdata_DATA = Alba.xml Arkanum.xml MeisterDerSphaeren.xml KanThaiPan.xml \
	Rawindra.xml Eschar.xml Ikengabecken.xml Nahuatlan.xml Waeland.xml \
	Kuestenstaaten.xml Minangpahit.xml AbenteuerBaende.xml \
	HexenzauberDruidenkraft.xml HexenzauberDruidenkraftFinster.xml \
	Kompendium.xml Gildenbrief.xml Regelwerk3.xml Regelwerk4.xml \
	BarbarenWutRitterEhre.xml midgard.xml

#MIDGARD3=$(shell if test `hostname` = "puck" ; then echo -DMIDGARD3 ; fi)

AM_CXXFLAGS = @CXXFLAGS@ @COMMONXX_INCLUDES@ $(MIDGARD3) -DREGION

common_sources = export_common.cc common_exp.cc zauber_exp.cc \
	ki_speichern.cc
arkanum_exp_SOURCES= arkanum_exp.cc $(common_sources)
all_exp_SOURCES=all_exp.cc $(common_sources) \
	kido_exp.cc fertigk_exp.cc land_sprache_exp.cc waffen_exp.cc

AM_LDFLAGS = @COMMONXX_LDFLAGS@
CLEANFILES = *~ 
LIBS=@LIBS@ @COMMONXX_LIBS@

XMLDIR=.

export: all_exp arkanum_exp
	./all_exp A $(XMLDIR)/Alba.xml
	./all_exp     ""  $(XMLDIR)/Regelwerk4.xml
	./arkanum_exp "" $(XMLDIR)/Arkanum.xml
	./all_exp MdS $(XMLDIR)/MeisterDerSphaeren.xml
	./all_exp K $(XMLDIR)/KanThaiPan.xml
	./all_exp R $(XMLDIR)/Rawindra.xml
	./all_exp E $(XMLDIR)/Eschar.xml
	./all_exp I $(XMLDIR)/Ikengabecken.xml
	./all_exp N $(XMLDIR)/Nahuatlan.xml
	./all_exp W $(XMLDIR)/Waeland.xml
	./all_exp KS $(XMLDIR)/Kuestenstaaten.xml
	./all_exp M $(XMLDIR)/Minangpahit.xml
	./all_exp X $(XMLDIR)/AbenteuerBaende.xml
	./all_exp "H&D" $(XMLDIR)/HexenzauberDruidenkraft.xml
	./all_exp "H&Df" $(XMLDIR)/HexenzauberDruidenkraftFinster.xml
	./all_exp TuT $(XMLDIR)/Kompendium.xml
	./all_exp G $(XMLDIR)/Gildenbrief.xml
	./all_exp 3 $(XMLDIR)/Regelwerk3.xml
	./all_exp "B&R" $(XMLDIR)/BarbarenWutRitterEhre.xml
#	./all_exp 2 $(XMLDIR)/Regelwerk2.xml
