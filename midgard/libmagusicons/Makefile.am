# $Id: Makefile.am,v 1.7 2003/10/13 14:19:00 christof Exp $

if WINDOWS
WIN_LDFLAGS=-no-undefined -export-symbols libmagusicons.def -L../libmagus
DLL_LDADD=@COMMONXX_LIBS@ @GTKMM2_LIBS@ @SIGC_LIBS@ -lmagus libmagusicons_res.lo
else
WIN_LDFLAGS=
DLL_LDADD=
endif

libmagusicons_res.lo: libmagusicons.rc
	WINDRES=i586-mingw32msvc-windres $(top_srcdir)/../ManuProC_Base/build/win32/lt-compile-resource $< $@

noinst_PROGRAMS=embed

lib_LTLIBRARIES=libmagusicons.la

libmagusicons_la_SOURCES=magusicons.cc big_embedding_file.cc
libmagusicons_la_LIBADD=$(DLL_LDADD)

embed_SOURCES=embed.cc

embed_LDADD = @COMMONXX_LIBS@

AM_CPPFLAGS = @KOMPONENTEN2_INCLUDES@ -DUSE_XML $(WIN_INCLUDES) -I.. \
	-Dlibmagusicons_COMPILATION

AM_LDFLAGS = @KOMPONENTEN2_LDFLAGS@ $(WIN_LDFLAGS)
# $(LINK_OPTIONS)

CLEANFILES = *~

big_embedding_file.cc: embed$(EXEEXT) iconlist iconlist.ulf ../pixmaps ../pixmaps/Ulf
	./embed$(EXEEXT) >big_embedding_file.cc
