// $Id: arkanum_exp.cc,v 1.25 2004/11/29 13:54:25 christof Exp $
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
#include <Misc/TagStream.h>

int main(int argc, char *argv[])
{  
   try{
      ManuProC::Connection conn;
      conn.setDbase("midgard");
      ManuProC::dbconnect(conn);
      Query("set names 'utf-8'");
      
      std::string revision="$Revi""sion$";
      std::string file="/dev/stdout";

   if (argc>1) region=argv[1];
   if (argc>2) file=argv[2];
   
   TagStream::host_encoding="UTF-8";
   
   try
   {  TagStream in(file);
      revision=in.getContent().getAttr("CVS","$Revi""sion$");
   }
   catch (std::exception) { }

      TagStream ts;
//      ts.setEncoding("UTF-8");
      Tag &data=ts.push_back(Tag("MAGUS-data"));
      region_tags(data,region.empty()?std::string("Arkanum"):region,revision);
      arkanum_speichern(data);
   {  std::ofstream of(file.c_str());
      ts.write(of);
   }
   ManuProC::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
