// $Id: export_common.h,v 1.7 2001/11/20 22:18:06 christof Exp $
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
