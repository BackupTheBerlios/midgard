// $Id: Ausgabe.cc,v 1.1 2003/07/11 22:47:15 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2003 Christof Petig
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

#include "Ausgabe.hh"
#include <iostream>

static Ausgabe::Ausgabe_cb *aktuelle_implementierung;

extern std::string utf82iso(const std::string &s);
#if 0
{  std::string ret="";

   for (std::string::const_iterator i = s.begin(); i!=s.end() ; i++)
   {  if (((*i)&0xe0)==0xc0)
      {  unsigned char first=*i;
         unsigned char second=*++i;
         ret+=(unsigned char)((first<<6)|(second)&0x3f);
      }
      else if ((unsigned char)(*i)>=0x80)
         std::cout << "UTF8 error " << int(*i) << '\n';
      else ret+=*i;
   }
   return ret;
}
#endif

const char * const Verbose[Ausgabe::MaxLevel]=
{  0,/*.Ausgabe::Warning=*/"Warnung", "Bitte Handeln",
   "Fehler", "Darf nicht sein"
};

static Ausgabe::Level LogLevel=Ausgabe::Warning;

static void StandardAusgabe(Ausgabe::Level l,const std::string &text)
{  if (l>Ausgabe::MaxLevel) l=Ausgabe::Fatal;
   if (l<LogLevel) return;
   std::cerr << (Verbose[l]?Verbose[l]:"") << (Verbose[l]?":":"") << text << '\n';
}

void Ausgabe::set(Ausgabe::Ausgabe_cb *cb)
{  if (!cb) aktuelle_implementierung=&StandardAusgabe;
   else aktuelle_implementierung=cb;
}

Ausgabe::Ausgabe(Level l,const std::string &text)
{  (*aktuelle_implementierung)(l,text);
}
