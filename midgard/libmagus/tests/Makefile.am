# $Id: Makefile.am,v 1.7 2006/01/30 07:33:47 christof Exp $

AM_CPPFLAGS=@COMMONXX_INCLUDES@ -I../..

AM_LDFLAGS=@COMMONXX_LDFLAGS@ @COMMONGTK2_LDFLAGS@ -L..

CLEANFILES = *~ test*.magus

EXTRA_PROGRAMS= test1 test2 test3 test4 test5

test1_LDADD=@COMMONXX_LIBS@ -lmagus @COMMONGTK2_ONLY@
test1_SOURCES=test1.cc
test2_LDADD=$(test1_LDADD)
test2_SOURCES=test2.cc
test3_LDADD=$(test1_LDADD)
test3_SOURCES=test3.cc
test4_LDADD=$(test1_LDADD)
test4_SOURCES=test4.cc
test5_LDADD=$(test1_LDADD)
test5_SOURCES=test5.cc

diff: $(EXTRA_PROGRAMS)
	-chmod a+x original
	-rm diff
	for i in $(EXTRA_PROGRAMS) ; do ./$$i ; echo $$i >>diff \
		; diff `./original $$i.magus` $$i.magus >>diff; done

check: diff
	diff diff soll
