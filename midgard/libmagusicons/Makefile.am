# $Id: Makefile.am,v 1.3 2003/04/27 21:13:41 christof Exp $

noinst_PROGRAMS=embed

lib_LTLIBRARIES=libmagusicons.la

libmagusicons_la_SOURCES=magusicons.cc big_embedding_file.cc

embed_SOURCES=embed.cc

embed_LDADD = @COMMONXX_LIBS@

CPPFLAGS = @CPPFLAGS@ @KOMPONENTEN2_INCLUDES@ -DUSE_XML $(WIN_INCLUDES) -I..

LDFLAGS = @KOMPONENTEN2_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~

big_embedding_file.cc: embed$(EXEEXT) iconlist iconlist.ulf
	./embed$(EXEEXT) >big_embedding_file.cc
