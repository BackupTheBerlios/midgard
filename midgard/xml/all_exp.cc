// $Id: all_exp.cc,v 1.22 2003/03/10 13:19:33 christof Exp $
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
#include <Misc/dbconnect.h>
#include <export_common.h>
#include <Misc/exception.h>
#include <Misc/FetchIStream.h>
#include <Misc/Transaction.h>
#include <Misc/TagStream.h>

int main(int argc, char *argv[])
{  ManuProC::PrintUncaughtExceptions();
   try{
      ManuProC::Connection conn;
      conn.setDbase("midgard");
      ManuProC::dbconnect(conn);
      
      std::string revision="$Revi""sion$";
      std::string file="/dev/stdout";

   if (argc>1) region=argv[1];
   if (argc>2) file=argv[2];
   
   try
   {  TagStream in(file);
      revision=in.getContent().getAttr("CVS","$Revi""sion$");
   }
   catch (std::exception) { }
   
      TagStream ts;
      ts.setEncoding("ISO-8859-1");
      Tag &data=ts.push_back(Tag("MAGUS-data"));
      region_tags(data,region,revision);
   land_speichern(data);
   fert_speichern(data);
   waffen_speichern(data);
   if (region.empty()) ki_speichern(data);
   // Arkanum ist ein extra Package
   if (!region.empty()) arkanum_speichern(data);
   kido_speichern(data);
   {  std::ofstream of(file.c_str());
      ts.write(of);
   }
   ManuProC::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
