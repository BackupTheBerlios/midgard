# $Id: Makefile,v 1.1 2001/04/03 12:27:24 christof Exp $

INSTALLED_TABLES=$(shell psql -t -q -c "select tablename from pg_tables where \
		tablename not like 'pg_%' and tablename not like 'pga_%';" midgard)
SYSTEM_TABLES=angeborene_fertigkeiten arkanum_zauber berufe_stand \
	berufe_voraussetzung berufe_vorteile  \
	fertigkeiten fertigkeiten_voraussetzung lernschema pflicht_lernen \
	praxispunkte ruestung schrift sprachen steigern_fertigkeiten \
	steigern_fertigkeiten_werte typen waffen waffen_grund waffen_region_name \
	waffen_standard waffen_steigern
USER_TABLES=charaktere charaktere_fertigkeiten
TABLES=$(SYSTEM_TABLES) $(USER_TABLES)

VERSION=0.3beta0
PACKAGE=midgard-postgres
DIST_FILES=Makefile $(TABLES)

PGDUMP_FLAGS=-c -n -O -R

all:
	@echo $(PACKAGE) Version $(VERSION)
	@echo "make dump: make a dump of your database (without user data)"
	@echo "make dist: make a .tar.gz"
	@echo "make install: install tables (preserving user data)"
	@echo
	@echo "make fulldump: dump with user data (not for dist or cvs, please)"
	@echo "make fullinstall: overwrite user data - DO YOU REALLY WANT THIS?"

# extract all tables with all data
fulldump:
	@for i in $(INSTALLED_TABLES) ; \
	do \
	  echo "dumping $$i with data" ; \
	  pg_dump $(PGDUMP_FLAGS) -t "$$i" midgard >"$$i" ; \
	done

# extract tables for dist or cvs (user tables without data)
dump: fulldump
	@for i in $(USER_TABLES) ; \
	do \
	  echo "dumping empty $$i schema" ; \
	  pg_dump $(PGDUMP_FLAGS) -s -t "$$i" midgard >"$$i" ; \
	done

# make distribution tar archive
dist: $(DIST_FILES)
	mkdir $(PACKAGE)-$(VERSION)
	cp $(DIST_FILES) $(PACKAGE)-$(VERSION)
	tar cvzf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	rm -r $(PACKAGE)-$(VERSION)

# install system tables unconditionally, user tables if missing
install:
	@for i in $(SYSTEM_TABLES) ; \
	do \
	  echo "loading $$i" ; \
	  psql midgard <"$$i" ; \
	done
	@for i in $(USER_TABLES) ; \
	do \
	  export QU="'" ; \
	  if psql -t -q -c "select tablename from pg_tables where tablename=$$QU$$i$$QU;" midgard | fgrep -q "$$i" ;  \
	  then \
	    echo "$$i is already there" ; \
	  else \
	    echo "loading $$i" ; \
	    psql midgard <"$$i" ; \
	  fi ; \
	done

# install all tables unconditionally - use with care!
fullinstall:
	@for i in $(TABLES) ; \
	do \
	  echo "loading $$i" ; \
	  psql midgard <"$$i" ; \
	done

clean:
	rm *~
