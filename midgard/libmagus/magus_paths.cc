// $Id: magus_paths.cc,v 1.1 2003/05/07 10:57:50 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "magus_paths.h"
#include <iostream>
#include "Windows_Linux.hh"
#include <vector>

std::string magus_paths::with_path(const std::string &name,bool path_only,bool noexit) const
{
//  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  std::vector<std::string> V;
#ifndef __MINGW32__ // IMHO macht das unter Win32 keinen Sinn

  // vielleicht sollten wir das aktuelle Verzeichnis beim 
  // Programmstart einmal ermitteln und nicht immer
  char currentwd[10240];
  *currentwd=0;
  getcwd(currentwd,sizeof currentwd);
  
  V.push_back(std::string(currentwd)+"/");
#endif  
  V.push_back(magus_verzeichnis);
#ifndef __MINGW32__
  V.push_back(PACKAGE_DATA_DIR);
  V.push_back(std::string(PACKAGE_DATA_DIR)+"/docs/");
  V.push_back(std::string(currentwd)+"/../xml/");
  V.push_back(std::string(currentwd)+"/../docs/");
#else
  V.push_back(BinaryVerzeichnis());
  V.push_back(BinaryVerzeichnis()+"Daten\\");
  V.push_back(BinaryVerzeichnis()+"Hilfe\\");
#endif  
  std::string ntmp;
  for(std::vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
   {
     std::string n=*i+name;
//cout <<"Suche nach "<< n<<'\n';
     if(!access(n.c_str(),R_OK)) 
      { if(path_only) return *i;
        else return n;
      }
   }
  std::cout << "File "+name+" nowhere found\n";
  if(!noexit) exit(1);
  return("");
}

std::string magus_paths::BinaryVerzeichnis() const
{  
//  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
   if (argv0.rfind(WinLux::dirsep)!=std::string::npos) 
      return argv0.substr(0,argv0.rfind(WinLux::dirsep)+1);
   else return "";
}

