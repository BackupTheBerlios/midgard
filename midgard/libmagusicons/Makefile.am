# $Id: Makefile.am,v 1.9 2004/12/15 09:17:30 christof Exp $

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

libmagusicons_la_SOURCES=big_embedding_file.cc magusicons.cc 
libmagusicons_la_LIBADD=$(DLL_LDADD)

embed_SOURCES=embed.cc

embed_LDADD = @COMMONXX_LIBS@

AM_CPPFLAGS = @KOMPONENTEN2_INCLUDES@ -DUSE_XML $(WIN_INCLUDES) -I.. \
	-Dlibmagusicons_COMPILATION

AM_LDFLAGS = @KOMPONENTEN2_LDFLAGS@ $(WIN_LDFLAGS)
# $(LINK_OPTIONS)

CLEANFILES = *~

big_embedding_file.cc: embed$(EXEEXT) iconlist iconlist.ulf ../pixmaps ../pixmaps/Ulf
	@NATIVE_BUILD@/libmagusicons/embed >big_embedding_file.cc
