// $Id: export_common.h,v 1.10 2001/12/12 10:30:01 christof Exp $
/*  Midgard Roleplaying Character Generator
 *  Copyright (C) 2001 Christof Petig
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
#include <Aux/FetchIStream.h>
#include <iostream>

#ifdef MIDGARD3
#define MIDGARD3_4(x,y) x
#else
#define MIDGARD3_4(x,y) y
#define MIDGARD4
#endif

#ifdef REGION
extern std::string region;
#define IF_REGION(x) x
#define IF_NOT_REGION(x) 
#else
#define IF_REGION(x)
#define IF_NOT_REGION(x) x
#endif

std::string toXML(const std::string &s);

int fetch_int(FetchIStream &is,int standard=0);
void write_int(std::ostream &o,const std::string &wert,int val, int indent=0);
void write_int_attrib(std::ostream &o,const std::string &wert,int val, int standard=0);
int fetch_and_write_int(FetchIStream &is,std::ostream &o,const std::string &wert,int indent=0);
int fetch_and_write_int_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,int standard=0);

std::string fetch_string(FetchIStream &is,const std::string &standard="");
void write_string(std::ostream &o,const std::string &wert,const std::string &val,int indent=0);
void write_string_attrib(std::ostream &o,const std::string &wert,const std::string &val,const std::string &standard="");
std::string fetch_and_write_string(FetchIStream &is,std::ostream &o,const std::string &wert,int indent=0);
std::string fetch_and_write_string_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const std::string &standard="");

bool fetch_bool(FetchIStream &is,const bool &standard=false);
void write_bool_attrib(std::ostream &o,const std::string &wert,bool val, bool standard=false);
bool fetch_and_write_bool_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const bool &standard=false);

std::string typ_standardisierung(const std::string &t);
std::string fetch_typ(FetchIStream &is,const std::string &standard="");
std::string fetch_and_write_typ_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const std::string &standard="");

// common routines for exporting from tables
void grund_standard_ausnahme(ostream &o, 
	const std::string &table, const std::string &name,
	const std::string &condition="", bool nur_region=false);
void lernschema(ostream &o, const std::string &art, const std::string &name,
	bool nur_region=false);
void ausnahmen(ostream &o, const std::string &art, const std::string &name,
	bool nur_region=false);
void pflicht_lernen(ostream &o, const std::string &name);
void verbot_lernen(ostream &o, const std::string &name);

std::string RegionErgaenzungQuery(const std::string &attribute, 
	const std::string &typtable, const std::string &lernsch_art,
	const std::string &ausnahmen_art);
std::string Herkunft(bool invert=false);
