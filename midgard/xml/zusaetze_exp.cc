// $Id: zusaetze_exp.cc,v 1.1 2002/02/09 16:13:29 thoma Exp $
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
#include <Aux/Transaction.h>
#include <Aux/dbconnect.h>
#include "export_common.h"

void zusaetze_speichern(std::ostream &o)
{  
   Transaction t;
  {Query query("select name from zusaetze ");
   FetchIStream is;
   o << " <Fertigkeiten-Zusätze>\n";
  while ((query>>is).good())
  {o << "  <Zusatz";
   fetch_and_write_string_attrib(is, o, "Name");
   o << ">";
   o << "</Zusatz>\n";
  }
   o << " </Fertigkeiten-Zusätze>\n";
  }
}

