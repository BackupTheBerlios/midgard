// $Id: Ausgabe.cc,v 1.6 2004/06/04 09:27:39 christof Exp $
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

// copied from TagStream.cc
static void utf82iso(std::string &s)
{  for (unsigned i = 0; i+1<s.size() ; ++i)
   {  unsigned char x=s[i];
      if ((x&0xe0)==0xc0) 
      {  unsigned char y=s[i+1];
         unsigned char r=(x<<6)|(y&0x3f);
         s.replace(i,2u,1u,char(r));
      }
      else if (x>=0x80)
         std::cout << "UTF8 decoding error " << x << '\n';
   }
}

const char * const Verbose[Ausgabe::MaxLevel]=
{  0,"Meldung",/*.Ausgabe::Warning=*/"Warnung", "Bitte Handeln",
   "Fehler", "Darf nicht sein"
};

static Ausgabe::Level LogLevel=Ausgabe::Warning;

void Ausgabe::setLogLevel(Level l)
{  LogLevel=l;
}

static void StandardAusgabe(Ausgabe::Level l,const std::string &_text)
{  if (l>Ausgabe::MaxLevel) l=Ausgabe::Fatal;
   if (l<LogLevel) return;
   std::string text(_text);
   utf82iso(text);
   std::cerr << (Verbose[l]?Verbose[l]:"") << (Verbose[l]?":":"") << text << '\n';
}

static Ausgabe::Ausgabe_cb *aktuelle_implementierung=&StandardAusgabe;

void Ausgabe::set(Ausgabe::Ausgabe_cb *cb)
{  if (!cb) aktuelle_implementierung=&StandardAusgabe;
   else aktuelle_implementierung=cb;
}

Ausgabe::Ausgabe(Level l,const std::string &text)
{  (*aktuelle_implementierung)(l,text);
}

Ausgabe::Ausgabe(Level l,const NotFound &NF)
{  (*aktuelle_implementierung)(l,NF.Name()+" NotFound");
}

