// $Id: export_common.h,v 1.30 2003/09/01 06:47:59 christof Exp $
/*  Midgard Roleplaying Character Generator
 *  Copyright (C) 2001-2002 Christof Petig
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <string>
#include <Misc/FetchIStream.h>
#include <iostream>
#include <Misc/Tag.h>

#ifdef MIDGARD3
#define MIDGARD3_4(x,y) x
#else
#define MIDGARD3_4(x,y) y
#define MIDGARD4
#endif

extern std::string region;

std::string toSQL(const std::string &s);

int fetch_int(FetchIStream &is,int standard=0);
int fetch_and_set_int_attrib(FetchIStream &is,Tag &o,const std::string &wert,int standard=0);

double fetch_float(FetchIStream &is,double standard=0);
double fetch_and_set_float_attrib(FetchIStream &is,Tag &o,const std::string &wert,double standard=0);

std::string fetch_string(FetchIStream &is,const std::string &standard="");
std::string fetch_and_set_string_attrib(FetchIStream &is,Tag &o,const std::string &wert,const std::string &standard="");

bool fetch_bool(FetchIStream &is,const bool &standard=false);
bool fetch_and_set_bool_attrib(FetchIStream &is,Tag &o,const std::string &wert,bool standard=false);

void grund_standard_ausnahme(Tag &o, 
	const std::string &table, const std::string &name,
	const std::string &condition="", bool nur_region=false);
void lernschema(Tag &o, const std::string &art, const std::string &name,
	bool nur_region=false);
void ausnahmen(Tag &o, const std::string &art, const std::string &name,
	bool nur_region=false);

std::string RegionErgaenzungQuery(const std::string &attribute, 
	const std::string &typtable, const std::string &lernsch_art,
	const std::string &ausnahmen_art);
std::string Herkunft(bool invert=false);
void region_tags(Tag &t, const std::string &region, const std::string &version);
void kaufpreis(Tag &t, const std::string &art, const std::string &name);

void arkanum_speichern(Tag &t);
void land_speichern(Tag &t);
void fert_speichern(Tag &t);
void zusaetze_speichern(Tag &t);
void waffen_speichern(Tag &t);
void kido_speichern(Tag &t);
void ki_speichern(Tag &o);
