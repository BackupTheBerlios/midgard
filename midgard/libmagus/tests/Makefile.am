# $Id: Makefile.am,v 1.13 2006/03/09 08:01:24 christof Exp $

AM_CPPFLAGS=@COMMONXX_INCLUDES@ -I../..

AM_LDFLAGS=@COMMONXX_LDFLAGS@ @COMMONGTK2_LDFLAGS@ -L..

CLEANFILES = *~ test*.magus

EXTRA_PROGRAMS= test1 test2 test3 test4 test5 test6 test7 test8 \
	lernliste test9

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
test6_LDADD=$(test1_LDADD)
test6_SOURCES=test6.cc
test7_LDADD=$(test1_LDADD)
test7_SOURCES=test7.cc
test8_LDADD=$(test1_LDADD)
test8_SOURCES=test8.cc
test9_LDADD=$(test1_LDADD)
test9_SOURCES=test9.cc
lernliste_LDADD=$(test1_LDADD)
lernliste_SOURCES=lernliste.cc

diff: $(EXTRA_PROGRAMS)
	-chmod a+x original
	-rm diff
	for i in $(EXTRA_PROGRAMS) ; do ./$$i ; echo $$i >>diff \
		; diff `./original $$i.magus` $$i.magus >>diff; done ; true

check: diff
	diff diff soll
	@echo --- Test successful. ---
