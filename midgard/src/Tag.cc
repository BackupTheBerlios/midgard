// $Id: Tag.cc,v 1.14 2001/01/31 12:13:51 christof Exp $
/*  glade--: C++ frontend for glade (Gtk+ User Interface Builder)
 *  Copyright (C) 1998  Christof Petig
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

#include "Tag.hh"
#include <algo.h>

const Tag *Tag::find(const string &tp) const
{  const_iterator i=find(begin(),tp);
   if (i==end()) return 0;
   return &*i;
}

Tag *Tag::find(const string &tp)
{  iterator i=find(begin(),tp);
   if (i==end()) return 0;
   return &*i;
}

void Tag::debug(int recursion_depth,int indent) const
{  cout.write("                                                       ",indent);
   cout << '"' << Type() << '"';
   if (Value()[0]) cout << "=\"" << Value() << '"';
   else cout << " @" << this;
   cout << "\n";
   if (recursion_depth>2 || (recursion_depth>0 && Type()!="widget"))
      for (const_iterator i=begin();i!=end();++i)
         (*i).debug(recursion_depth-1,indent+2);
}

bool Tag::hasTag(const string &typ) const throw()
{  return find(begin(),typ)!=end();
}

bool Tag::parse_bool_value() const
{  if (!strcasecmp(Value().c_str(),"true")) return true;
   if (!strcasecmp(Value().c_str(),"false")) return false;
   cerr << "strange bool value: <" << Type() << "> \"" << Value() << "\"\n";
   return parse_int_value();
}

int Tag::parse_int_value() const
{  // 2do: check
   return atoi(Value().c_str());
}

long Tag::parse_long_value() const
{  return atol(Value().c_str());
} 

float Tag::parse_float_value() const
{  // 2do: check
   return atof(Value().c_str());
}

double Tag::parse_double_value() const
{  return atof(Value().c_str());
}

const string Tag::getString(const string &typ,const string &def) const throw()
{  const_iterator t=find(begin(),typ);
// XXX parse &gt; &auml; etc.
   if (t!=end()) return t->Value();
   return def;
}

bool Tag::getBool(const string &typ,bool def) const throw()
{  const_iterator t=find(begin(),typ);
   if (t==end()) return def;
   return t->parse_bool_value();
}

int Tag::getInt(const string &typ,int def) const throw()
{  const_iterator t=find(begin(),typ);
   if (t==end()) return def;
   return t->parse_int_value();
}

float Tag::getFloat(const string &typ,float def) const throw()
{  const_iterator t=find(begin(),typ);
   if (t==end()) return def;
   return t->parse_float_value();
}

void Tag::mark(const string &tg,const string &value) throw()
{  iterator t=find(begin(),tg);
   if (t==end()) push_back(Tag(tg,value));
   else (*t).Value(value);
}

