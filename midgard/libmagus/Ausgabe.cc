// $Id: Ausgabe.cc,v 1.8 2004/08/30 13:17:56 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2003-2004 Christof Petig
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
#include <Misc/TagStream.h>

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
   TagStream::utf82iso(text);
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

