// $Id: xml.cc,v 1.16 2003/07/01 10:49:10 christof Exp $
/*  Midgard Roleplaying Character Generator
 *  Copyright (C) 2001-2003 Christof Petig
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

#include "xml.h"
#include <iostream>
#include "magus_paths.h"
#include <Misc/TagStream.h>
#include <Misc/compiler_ports.h>
#include "Datenbank.hh"
#include <fstream>
#include <NotFound.h>

void xml_init(SigC::Slot1<void,double> progress,SigC::Slot1<void,const std::string&> meldungen, Datenbank &db)
{  std::string filename=magus_paths::with_path("midgard.xml");
   std::ifstream ifs(filename.c_str());
   TagStream ts=TagStream(ifs);
   try
   {  Tag &main_file=ts.getContent();
   
   double anzdateien=1;
   FOR_EACH_CONST_TAG(i,main_file)
   {  if (i->Type()!="MAGUS-include" && i->Type()!="MCG-include") continue;
      if (!i->getBoolAttr("inactive",false)) 
         ++anzdateien;
   }
   int count=0;
    FOR_EACH_TAG(i,main_file)
    {  if (i->Type()!="MAGUS-include" && i->Type()!="MCG-include") continue;
       std::string file=magus_paths::with_path(i->getAttr("File"),false,true);
       if (i->getBoolAttr("inactive",false))
          continue;
       progress(++count/anzdateien);
       
       std::ifstream in2(file.c_str());
       // wenn nicht, URL holen?
       if (in2.good()) 
       {  TagStream ts2(in2);
          try
          {  Tag &data=ts2.getContent();
             if (data.Type()!="MAGUS-data")
             {  std::cerr << file << " ist keine Magus Datei\n";
             }
             else try
             {  db.load_region(data,file);
                db.load_list(data);
             }
             catch (NotFound &e)
             {  std::cerr << file << ": " << e.what() << ": " << e.Name() << '\n';
             }
             catch (std::exception &e)
             {  std::cerr << file << ": " << e.what() << '\n';
             }
          } catch (std::exception &e)
          {  std::cerr << file << " ist keine g�ltige XML Datei\n";
          }
       }
       else std::cerr << "Kann Datei '" << file << "' nicht öffnen\n";
    }
  }
  catch (...)
  {  std::cerr << "Ladefehler XML Datei " << filename << "\n";
      exit(2);
  }
}

void xml_free()
{  
}
