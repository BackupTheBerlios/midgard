// $Id: export_common.cc,v 1.21 2002/11/22 08:13:01 thoma Exp $
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

#include "export_common.h"
#include <Misc/itos.h>

std::string region;

#if defined( __MINGW32__) || defined(USE_XML)
#define NO_SQL
#endif

#ifndef NO_SQL
std::string toSQL(const std::string &s)
{  std::string res;
   for (std::string::const_iterator i=s.begin();i!=s.end();++i)
   {  if (*i=='\'') res+="''";
      else res+=*i;
//      else res+=std::string("\")+Formatiere(*i,0,3,"0");
   }
   return "'"+res+"'";
}

int fetch_int(FetchIStream &is,int standard=0)
{  int val;
   
   is >> FetchIStream::MapNull<int>(val,standard);
   return val;
}

int fetch_and_set_int_attrib(FetchIStream &is,Tag &o,const std::string &wert,int standard=0)
{  int val=fetch_int(is,standard);
   if (val!=standard) o.setIntAttr(wert,val);
   return val;
}

double fetch_float(FetchIStream &is,double standard=0)
{  float val;
   
   is >> FetchIStream::MapNull<float>(val,standard);
   return val;
}

 std::string fetch_string(FetchIStream &is,const std::string &standard="")
{  std::string val;
   
   is >> FetchIStream::MapNull<string>(val,standard); 
   return val;
}

 std::string fetch_and_set_string_attrib(FetchIStream &is,Tag &o,const std::string &wert,const std::string &standard)
{  std::string val=fetch_string(is,standard);
   if (val!=standard) o.setAttr(wert,val);
   return val;
}

bool fetch_and_set_bool_attrib(FetchIStream &is,Tag &o,const std::string &wert,bool standard=0)
{  bool val=fetch_bool(is,standard);
   if (val!=standard) o.setBoolAttr(wert,val);
   return val;
}

double fetch_and_set_float_attrib(FetchIStream &is,Tag &o,const std::string &wert,double standard=0)
{  double val=fetch_float(is,standard);
   if (val!=standard) o.setAttr(wert,dtos(val));
   return val;
}

 bool fetch_bool(FetchIStream &is,const bool &standard)
{  bool val;
   
   is >> FetchIStream::MapNull<bool>(val,standard); 
   return val;
}

#endif

