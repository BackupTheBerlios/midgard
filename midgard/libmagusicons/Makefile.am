# $Id: Makefile.am,v 1.2 2003/04/23 14:01:03 christof Exp $

noinst_LIBRARIES=libmagusicons.a

libmagusicons_a_SOURCES=magusicons.cc

CPPFLAGS = @CPPFLAGS@ @KOMPONENTEN2_INCLUDES@ -DUSE_XML $(WIN_INCLUDES) -I..

LDFLAGS = @KOMPONENTEN2_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~
