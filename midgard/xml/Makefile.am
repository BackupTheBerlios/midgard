# $Id: Makefile.am,v 1.37 2002/09/25 20:47:38 thoma Exp $

EXTRA_PROGRAMS = all_exp arkanum_exp 

#MIDGARD3=$(shell if test `hostname` = "puck" ; then echo -DMIDGARD3 ; fi)

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ $(MIDGARD3) -DREGION

BUILT_SOURCES=TagStream.hh Tag.hh

TagStream.cc: ../src/TagStream.cc ; ln -sf ../src/$@ .
Tag.cc: ../src/Tag.cc ; ln -sf ../src/$@ .
TagStream.hh: ../src/TagStream.hh ; ln -sf ../src/$@ .
Tag.hh: ../src/Tag.hh ; ln -sf ../src/$@ .

common_sources = export_common.cc common_exp.cc zauber_exp.cc \
	Tag.cc TagStream.cc ki_speichern.cc
arkanum_exp_SOURCES= arkanum_exp.cc $(common_sources)
all_exp_SOURCES=all_exp.cc $(common_sources) \
	kido_exp.cc fertigk_exp.cc land_sprache_exp.cc waffen_exp.cc

LDFLAGS = @KOMPONENTEN_LDFLAGS@
CLEANFILES = *~ $(BUILT_SOURCES) 
LIBS=@LIBS@ @COMMONXX_LIBS@

XMLDIR=.

export: all_exp arkanum_exp
	./all_exp A >$(XMLDIR)/Alba.xml
	./all_exp   >$(XMLDIR)/Regelwerk4.xml
	./arkanum_exp >$(XMLDIR)/Arkanum.xml
	./all_exp MdS >$(XMLDIR)/MeisterDerSphaeren.xml
	./all_exp K >$(XMLDIR)/KanThaiPan.xml
	./all_exp R >$(XMLDIR)/Rawindra.xml
	./all_exp E >$(XMLDIR)/Eschar.xml
	./all_exp N >$(XMLDIR)/Nahuatlan.xml
	./all_exp W >$(XMLDIR)/Waeland.xml
	./all_exp KS >$(XMLDIR)/Kuestenstaaten.xml
	./all_exp M >$(XMLDIR)/Minangpahit.xml
	./all_exp X >$(XMLDIR)/AbenteuerBaende.xml
	./all_exp "H&D" >$(XMLDIR)/HexenzauberDruidenkraft.xml
	./all_exp "H&Df" >$(XMLDIR)/HexenzauberDruidenkraftFinster.xml
	./all_exp TuT >$(XMLDIR)/Kompendium.xml
	./all_exp G >$(XMLDIR)/Gildenbrief.xml
	./all_exp 3 >$(XMLDIR)/Regelwerk3.xml
	./all_exp "B&R" >$(XMLDIR)/BarbarenWutRitterEhre.xml
#	./all_exp 2 >$(XMLDIR)/Regelwerk2.xml
