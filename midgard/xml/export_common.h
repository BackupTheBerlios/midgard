// $Id: export_common.h,v 1.1 2001/11/02 12:52:20 christof Exp $
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

static int fetch_and_write_int(FetchIStream &is,std::ostream &o,const std::string &wert,int indent=0)
{  int val;
   
   is >> FetchIStream::MapNull<int>(val,0);
   if (!val) return val;
   for (int i=0;i<indent;++i) o << ' ';
   o << '<' << wert << '>' << val << "</" << wert << ">\n";
   return val;
}

static int fetch_and_write_int_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,int standard=0)
{  int val;
   
   is >> FetchIStream::MapNull<int>(val,standard);
   if (val==standard) return val;
   o << ' ' << wert << "=\"" << val << '\"';
   return val;
}

static void fetch_and_write_string(FetchIStream &is,std::ostream &o,const std::string &wert,int indent=0)
{  std::string val;
   
   is >> FetchIStream::MapNull<string>(val,""); 
   if (!val.size()) return;
   // val in XML wandeln ...
   for (int i=0;i<indent;++i) o << ' ';
   o << '<' << wert << '>' << val << "</" << wert << ">\n";
}

static std::string fetch_and_write_string_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const std::string &standard="")
{  std::string val;
   
   is >> FetchIStream::MapNull<string>(val,standard); 
   if (val==standard) return val;
   // val in XML wandeln ...
   o << ' ' << wert << "=\"" << val << '\"';
   return val;
}

static bool fetch_and_write_bool_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const bool &standard=false)
{  bool val;
   
   is >> FetchIStream::MapNull<bool>(val,standard); 
   if (val==standard) return val;
   // val in XML wandeln ...
   o << ' ' << wert << "=\"" << (val?"True":"False") << '\"';
   return val;
}

