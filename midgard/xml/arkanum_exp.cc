// $Id: arkanum_exp.cc,v 1.16 2002/06/27 07:37:18 christof Exp $
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
#include <Misc/dbconnect.h>
#include "export_common.h"
#include "TagStream.hh"

int main(int argc, char *argv[])
{  
   try{
      ManuProC::Connection conn;
      conn.setDbase("midgard");
      ManuProC::dbconnect(conn);
      
      if (argc>1) region=argv[1];

      TagStream ts;
      Tag &data=ts.push_back(Tag("MAGUS-data"));
      region_tags(data,region.empty()?std::string("Arkanum"):region);
      arkanum_speichern(data);
      ts.write(std::cout);
   ManuProC::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
