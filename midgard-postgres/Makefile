# $Id: Makefile,v 1.24 2001/08/15 11:25:10 thoma Exp $
INSTALLED_TABLES=$(shell psql -t -q -c "select tablename from pg_tables where \
		tablename not like 'pg_%' and tablename not like 'pga_%';" midgard)
SYSTEM_TABLES=angeborene_fertigkeiten arkanum_zauber ausnahmen berufe_stand \
	berufe_voraussetzung berufe_vorteile  \
	fertigkeiten fertigkeiten_voraussetzung kido lernschema pflicht_lernen \
	praxispunkte spezies spezies_typen ruestung schrift sprachen \
	steigern_fertigkeiten \
	steigern_fertigkeiten_werte typen waffen waffen_grund waffen_region_name \
	waffen_standard waffen_steigern zauber_beschreibung zauberwerk \
	zauberwerk_voraussetzung spezialgebiete
USER_TABLES=charaktere charaktere_fertigkeiten
TABLES=$(SYSTEM_TABLES) $(USER_TABLES)

VERSION=0.7beta5
PACKAGE=midgard-postgres
DIST_FILES=Makefile $(TABLES)

PGDUMP_FLAGS=-c -O -R

all:
	@echo $(PACKAGE) Version $(VERSION)
	@echo "make dump: make a dump of your database (without user data)"
	@echo "make dist: make a .tar.gz"
	@echo "make install: install tables (preserving user data)"
	@echo "make diff: compare your tables with these files"
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
	psql midgard -c "vacuum analyze"

# install all tables unconditionally - use with care!
fullinstall:
	@for i in $(TABLES) ; \
	do \
	  echo "loading $$i" ; \
	  psql midgard <"$$i" ; \
	done
	psql midgard -c "vacuum analyze"

clean:
	rm *~

# compare your tables with these files
diff:
	@for i in $(SYSTEM_TABLES) ; \
	do \
	  pg_dump $(PGDUMP_FLAGS) -t "$$i" midgard | \
		diff -B -I '--.*' -u - "$$i" ; \
	done ; true
	@for i in $(USER_TABLES) ; \
	do \
	  pg_dump $(PGDUMP_FLAGS) -s -t "$$i" midgard | \
		diff -B -I '-- .*' -u - "$$i" ; \
	done ; true
