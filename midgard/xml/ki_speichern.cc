// $Id: ki_speichern.cc,v 1.3 2003/09/01 06:47:59 christof Exp $
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

#include <fstream>
#include <Misc/Transaction.h>
#include <Misc/dbconnect.h>
#include "export_common.h"
#include <Misc/itos.h>

void ki_speichern(Tag &o)
{
  Tag &KI=o.push_back(Tag("KI"));

  Transaction tr;
  FetchIStream is;

  Query query("select name,fertigkeit,zauber,waffen,waffen_grund,zauberwerk,"
              "sprache,schrift,fert_spezialist,waff_spezialist,"
              "spra_spezialist,schr_spezialist from ki_prototyp order by name");
  while ((query>>is).good())
   {
     Tag &proto=KI.push_back(Tag("Prototyp"));
     fetch_and_set_string_attrib(is, proto, "Name");
     fetch_and_set_int_attrib(is, proto, "Fertigkeit");
     fetch_and_set_int_attrib(is, proto, "Zauber");
     fetch_and_set_int_attrib(is, proto, "Waffen");
     fetch_and_set_int_attrib(is, proto, "WaffenGrund");
     fetch_and_set_int_attrib(is, proto, "Zauberwerk");
     fetch_and_set_int_attrib(is, proto, "Sprache");
     fetch_and_set_int_attrib(is, proto, "Schrift");
     fetch_and_set_int_attrib(is, proto, "FertSpezialist");
     fetch_and_set_int_attrib(is, proto, "WaffSpezialist");
     fetch_and_set_int_attrib(is, proto, "SpraSpezialist");
     fetch_and_set_int_attrib(is, proto, "SchrSpezialist");
   }
}
