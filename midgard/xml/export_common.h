// $Id: export_common.h,v 1.2 2001/11/06 08:43:40 christof Exp $
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

static const char HEX[]="0123456789ABCDEF";

static std::string toXML(const std::string &s)
{  string res;
   for (string::const_iterator i=s.begin();i!=s.end();++i)
   {  if (isalnum(*i)) res+=*i;
      else if ((unsigned char)*i>=160) res+=*i;
      else if (strchr(" @^+-*/.,?!$'`|~[]{}()_:;",*i)) res+=*i;
      else if (*i=='&') res+="&amp;";
      else if (*i=='<') res+="&lt;";
      else if (*i=='>') res+="&gt;";
      else if (*i=='"') res+="&quot;";
      else res+=string("&#X")+HEX[(*i>>4)&0xf]+HEX[*i&0xf]+';';
   }
   return res;
}

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
   for (int i=0;i<indent;++i) o << ' ';
   o << '<' << wert << '>' << toXML(val) << "</" << wert << ">\n";
}

static std::string fetch_and_write_string_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const std::string &standard="")
{  std::string val;
   
   is >> FetchIStream::MapNull<string>(val,standard); 
   if (val==standard) return val;
   o << ' ' << wert << "=\"" << toXML(val) << '\"';
   return val;
}

static bool fetch_and_write_bool_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const bool &standard=false)
{  bool val;
   
   is >> FetchIStream::MapNull<bool>(val,standard); 
   if (val==standard) return val;
   o << ' ' << wert << "=\"" << (val?"True":"False") << '\"';
   return val;
}

