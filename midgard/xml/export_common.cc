// $Id: export_common.cc,v 1.3 2001/12/16 21:47:49 christof Exp $
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

#include "export_common.h"

#ifdef REGION
std::string region;
#endif

static const char HEX[]="0123456789ABCDEF";

 std::string toXML(const std::string &s)
{  string res;
   for (string::const_iterator i=s.begin();i!=s.end();++i)
   {  if (isalnum(*i)) res+=*i;
      else if ((unsigned char)*i>=160) res+=*i;
      else if (strchr("# @^+-*/.,?!$'`|~[]{}()_:;=",*i)) res+=*i;
      else if (*i=='&') res+="&amp;";
      else if (*i=='<') res+="&lt;";
      else if (*i=='>') res+="&gt;";
      else if (*i=='"') res+="&quot;";
      else res+=string("&#x")+HEX[(*i>>4)&0xf]+HEX[*i&0xf]+';';
   }
   return res;
}

 int fetch_int(FetchIStream &is,int standard=0)
{  int val;
   
   is >> FetchIStream::MapNull<int>(val,standard);
   return val;
}

 void write_int(std::ostream &o,const std::string &wert,int val, int indent=0)
{  if (!val) return;
   for (int i=0;i<indent;++i) o << ' ';
   o << '<' << wert << '>' << val << "</" << wert << ">\n";
}

 void write_int_attrib(std::ostream &o,const std::string &wert,int val, int standard=0)
{  if (val==standard) return;
   o << ' ' << wert << "=\"" << val << '\"';
}

 int fetch_and_write_int(FetchIStream &is,std::ostream &o,const std::string &wert,int indent=0)
{  int val=fetch_int(is);
   write_int(o,wert,val,indent);
   return val;
}

int fetch_and_write_int_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,int standard=0)
{  int val=fetch_int(is,standard);
   write_int_attrib(o,wert,val,standard);
   return val;
}

double fetch_float(FetchIStream &is,double standard=0)
{  double val;
   
   is >> FetchIStream::MapNull<double>(val,standard);
   return val;
}

void write_float(std::ostream &o,const std::string &wert,double val, int indent=0)
{  if (!val) return;
   for (double i=0;i<indent;++i) o << ' ';
   o << '<' << wert << '>' << val << "</" << wert << ">\n";
}

void write_float_attrib(std::ostream &o,const std::string &wert,double val, double standard=0)
{  if (val==standard) return;
   o << ' ' << wert << "=\"" << val << '\"';
}

double fetch_and_write_float(FetchIStream &is,std::ostream &o,const std::string &wert,int indent=0)
{  double val=fetch_float(is);
   write_float(o,wert,val,indent);
   return val;
}

double fetch_and_write_float_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,double standard=0)
{  double val=fetch_float(is,standard);
   write_float_attrib(o,wert,val,standard);
   return val;
}

 std::string fetch_string(FetchIStream &is,const std::string &standard="")
{  std::string val;
   
   is >> FetchIStream::MapNull<string>(val,standard); 
   return val;
}

 void write_string(std::ostream &o,const std::string &wert,const std::string &val,int indent=0)
{  if (!val.size()) return;
   for (int i=0;i<indent;++i) o << ' ';
   o << '<' << wert << '>' << toXML(val) << "</" << wert << ">\n";
}

 void write_string_attrib(std::ostream &o,const std::string &wert,const std::string &val,const std::string &standard="")
{  if (val==standard) return;
   o << ' ' << wert << "=\"" << toXML(val) << '\"';
}

 std::string fetch_and_write_string(FetchIStream &is,std::ostream &o,const std::string &wert,int indent=0)
{  std::string val=fetch_string(is);
   write_string(o,wert,val,indent);
   return val;
}

 std::string fetch_and_write_string_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const std::string &standard="")
{  std::string val=fetch_string(is,standard);
   write_string_attrib(o,wert,val,standard);
   return val;
}

 bool fetch_bool(FetchIStream &is,const bool &standard=false)
{  bool val;
   
   is >> FetchIStream::MapNull<bool>(val,standard); 
   return val;
}

 void write_bool_attrib(std::ostream &o,const std::string &wert,bool val, bool standard=false)
{  if (val==standard) return;
   o << ' ' << wert << "=\"" << (val?"True":"False") << '\"';
}

 bool fetch_and_write_bool_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const bool &standard=false)
{  bool val=fetch_bool(is,standard);
   write_bool_attrib(o,wert,val,standard);
   return val;
}

 std::string typ_standardisierung(const std::string &t)
{  if (t=="Ord") return "Or";
   else if (t=="Ass") return "As";
   else return t;
}

 std::string fetch_typ(FetchIStream &is,const std::string &standard="")
{  return typ_standardisierung(fetch_string(is,standard));
}

 std::string fetch_and_write_typ_attrib(FetchIStream &is,std::ostream &o,const std::string &wert,const std::string &standard="")
{  std::string val=fetch_typ(is,standard);
   write_string_attrib(o,wert,val,standard);
   return val;
}

