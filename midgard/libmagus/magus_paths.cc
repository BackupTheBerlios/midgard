// $Id: magus_paths.cc,v 1.4 2003/05/07 13:32:12 christof Exp $
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
#include <unistd.h>
#include "magustrace.h"
#include <Misc/Trace.h>

std::vector<std::string> magus_paths::paths;
std::string magus_paths::argv0;
std::string magus_paths::magus_verzeichnis;

void magus_paths::init(const std::string &_argv0,const std::string &_magus_verzeichnis)
{  assert(paths.empty());
   argv0=_argv0;
   magus_verzeichnis=_magus_verzeichnis;
#ifndef __MINGW32__ // IMHO macht das unter Win32 keinen Sinn
  char currentwd[10240];
  *currentwd=0;
  getcwd(currentwd,sizeof currentwd);
  append_dir(std::string(currentwd)+"/");
#endif  
  append_dir(magus_verzeichnis);
#ifndef __MINGW32__
  append_dir(std::string(currentwd)+"/../xml/");
  append_dir(std::string(currentwd)+"/../docs/");
#else
  append_dir(BinaryVerzeichnis());
  append_dir(BinaryVerzeichnis()+"Daten\\");
  append_dir(BinaryVerzeichnis()+"Hilfe\\");
#endif  
    
}

//  append_dir(PACKAGE_DATA_DIR);
//  append_dir(std::string(PACKAGE_DATA_DIR)+"/docs/");

std::string magus_paths::with_path(const std::string &name,bool path_only,bool noexit)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  for(std::vector<std::string>::const_iterator i=paths.begin();i!=paths.end();++i)
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

std::string magus_paths::BinaryVerzeichnis()
{  
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   if (argv0.rfind(WinLux::dirsep)!=std::string::npos) 
      return argv0.substr(0,argv0.rfind(WinLux::dirsep)+1);
   else return "";
}

void magus_paths::append_dir(const std::string &name)
{  paths.push_back(name);
}

void magus_paths::prepend_dir(const std::string &name)
{  paths.insert(paths.begin(),name);
}
