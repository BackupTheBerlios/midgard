# $Id: Makefile.am,v 1.17 2002/04/03 06:37:08 christof Exp $

CLEANFILES = *~

INCLUDES = -I. -I$(top_srcdir)/searchcombo/src @GTKMM_CFLAGS@ 

lib_LIBRARIES = lib@LIBNAME@.a

noinst_LIBRARIES = libtemp.a

myinclude_HEADERS = Gtk_OStream.h Message.h Picture.h TCList.h \
		TCListRow.h SearchCombo.h \
		SearchComboContent.h Gtk2TeX.h TCListRow_ct.h TCList_ct.h \
		Picture2.h gtksearchcombo.h TCList_iterator.h \
		TeX.h SelectMatching.h

noinst_HEADERS = green_minus.xpm red_plus.xpm

libtemp_a_SOURCES = Gtk_OStream_clist.cc Gtk_OStream_label.cc \
		 Gtk_OStream_list.cc Gtk_OStream_optionmenu.cc Gtk_OStream_stream.cc Picture.cc \
		 SearchCombo.cc TCList.cc TCListRow.cc string_width.cc \
		 Gtk2TeX.cc TeX.cc \
		 Picture2.cc
#Rausgenommen damit es kompiliert MAT
#TCListRow_ct.cc TCList_ct.cc 

BUILT_SOURCES=SearchCombo.cc SearchCombo.h

libtemp_a_LIBADD = gtksearchcombo.o

EXTRA_DIST=SearchCombo.gen_h private/SearchCombo_p.h

SearchCombo.cc SearchCombo.h: SearchCombo.gen_h
	if [ ! -d private ] ; then mkdir private ; fi
	$(shell gtkmm-config --proc) --m4 $(shell gtkmm-config --procdir) -l SearchCombo ./ ./

gtksearchcombo.h: $(top_srcdir)/searchcombo/src/gtksearchcombo.h
	ln -s $(top_srcdir)/searchcombo/src/gtksearchcombo.h .

gtksearchcombo.o: $(top_srcdir)/searchcombo/src/gtksearchcombo.o
	cp $(top_srcdir)/searchcombo/src/gtksearchcombo.o .

lib@LIBNAME@.a: libtemp.a
	ln -f libtemp.a lib@LIBNAME@.a

lib_LIBNAME__a_SOURCES= 

if PETIG_HACK
myincludedir=$(includedir)
else
myincludedir=$(includedir)/@LIBNAME@
endif
