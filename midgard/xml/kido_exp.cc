// $Id: kido_exp.cc,v 1.7 2004/11/29 13:54:25 christof Exp $
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

#include <fstream>
#include <Misc/Transaction.h>
#include <Misc/dbconnect.h>
#include "export_common.h"

void kido_speichern(Tag &o)
{  
   Transaction t;
#ifdef REGION   
   if (region=="K")
#endif
  {Query query("select name_orig, name, stufe, stil, fp, ap, effekt"
   	" from kido"
   	" order by name_orig");
   FetchIStream is;
   Tag &liste=o.push_back(Tag("Kido-Fertigkeiten"));
  while ((query>>is).good())
  {Tag &kf=liste.push_back(Tag("KiDo"));
   fetch_and_set_string_attrib(is, kf, "Name");
   fetch_and_set_string_attrib(is, kf, "Übersetzung");
   fetch_and_set_string_attrib(is, kf, "Stufe");
   fetch_and_set_string_attrib(is, kf, "Stil");
   fetch_and_set_int_attrib(is, kf, "Lernkosten");
   fetch_and_set_string_attrib(is, kf, "AP");
   kf.Value(fetch_string(is));
  }
  }
}

