// $Id: magus_paths.cc,v 1.13 2003/11/24 16:21:42 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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
#include "Windows_Linux.hh"
#include <vector>
#include <unistd.h>
#include "magustrace.h"
#include <Misc/Trace.h>
#include <config.h> // PACKAGE_DATA_DIR
#include <sys/stat.h>
#include <cassert>
#include "Ausgabe.hh"

#ifdef __MINGW32__
#include "registry.h"
#endif

std::vector<std::string> magus_paths::paths;
std::string magus_paths::argv0;
std::string magus_paths::magus_verzeichnis;

void magus_paths::init(const std::string &_argv0,const std::string &_magus_verzeichnis)
{  
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,_argv0,_magus_verzeichnis);
   assert(paths.empty());
   argv0=_argv0;
   magus_verzeichnis=_magus_verzeichnis;
   if (magus_verzeichnis.empty())
   {
#ifdef __MINGW32__ // Standard Dokumentenverzeichnis
      char buf[1024];
      reg_key r1(HKEY_CURRENT_USER, KEY_READ, "Software", "Microsoft", "Windows",
      	"CurrentVersion", "Explorer", "User Shell Folders", NULL); // "AppData");?
      if (r1.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) 
      {  magus_verzeichnis=buf;
         Ausgabe(Ausgabe::Debug, magus_verzeichnis+ " from HKEY_CURRENT_USER");
      }
      else
      {  reg_key r2(HKEY_USERS, KEY_READ, ".Default", "Software", "Microsoft", "Windows",
      	"CurrentVersion", "Explorer", "User Shell Folders", NULL);
         if (r2.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) 
         {	magus_verzeichnis=buf;
            Ausgabe(Ausgabe::Debug,magus_verzeichnis + " from HKEY_USERS");
         }
         else
         {  reg_key r3(HKEY_LOCAL_MACHINE, KEY_READ, "Software", "Microsoft", "Windows",
         		"CurrentVersion", "Explorer", "User Shell Folders", NULL);
            if (r3.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) 
            {  magus_verzeichnis=buf;
               Ausgabe(Ausgabe::Debug,magus_verzeichnis+" from HKEY_LOCAL_MACHINE");
            }

            // %USERPROFILE%\Anwendungsdaten\Magus ???
            else 
            {  magus_verzeichnis="C:\\Eigene Dateien";
               Ausgabe(Ausgabe::Debug,magus_verzeichnis+ " by hand");
            }
         }
      }
      magus_verzeichnis+="\\Magus";
      ManuProC::Trace(LibMagus::trace_channel,"magus_verzeichnis=",magus_verzeichnis);
#else
      magus_verzeichnis=std::string(getenv("HOME"))+"/.magus";
#endif
   }

   const char *envpath=getenv("MAGUSPATH");
   if (envpath)
   {  // evtl zerteilen ...
      append_dir(std::string(envpath)+WinLux::dirsep);
   }
   if(access(magus_verzeichnis.c_str(),R_OK)) 
      if(mkdir(magus_verzeichnis.c_str() NUR_LINUX(,0777) ))
      { 
#ifndef __MINGW32__      
         Ausgabe(Ausgabe::Fatal, "Heimatverzeichnis nicht schreibbar"); exit(1);
#else
	 // eigentlich ist es krank den ganzen Baum zu erzeugen, 
	 // aber wir haben keine Wahl außer aufgeben
	 for (std::string::size_type i=magus_verzeichnis.find(WinLux::dirsep);
	 	i!=std::string::npos;i=magus_verzeichnis.find(WinLux::dirsep,i+1))
	 {  if (i && access(magus_verzeichnis.substr(0,i).c_str(),R_OK))
	    {  if (mkdir(magus_verzeichnis.substr(0,i).c_str()))
	       {  magus_verzeichnis="C:"; // last ressort
	          break;
	       }
	    }
	 }
	 mkdir(magus_verzeichnis.c_str() NUR_LINUX(,0777));
#endif         
      }
   magus_verzeichnis+=WinLux::dirsep;

   // normalize argv0 (prepend current dir if relative)
   if (argv0[0]!=WinLux::dirsep 
#ifdef __MINGW32__
			&& argv0.find(':')==std::string::npos
#endif
								)
   {  char buf[10240];
      *buf=0;
      getcwd(buf,sizeof buf);
      Ausgabe(Ausgabe::Debug,"cwd: "+ std::string(buf));
      argv0=buf+std::string(1,WinLux::dirsep)+argv0;
      Ausgabe(Ausgabe::Debug,"argv0: " +argv0);
   }

#ifndef __MINGW32__ // IMHO macht das unter Win32 keinen Sinn
  char currentwd[10240];
  *currentwd=0;
  getcwd(currentwd,sizeof currentwd);
  append_dir(std::string(currentwd)+"/");
#endif  
  append_dir(magus_verzeichnis);
#ifndef __MINGW32__
  append_dir(std::string(currentwd)+"/../xml/");
  if (BinaryVerzeichnis().find("/libmagus/.libs")!=std::string::npos)
     append_dir(BinaryVerzeichnis()+"../../src/");
  else if (BinaryVerzeichnis().find("/libmagus")!=std::string::npos)
     append_dir(BinaryVerzeichnis()+"../src/");
//  append_dir(std::string(currentwd)+"/../docs/");
  append_dir(PACKAGE_DATA_DIR);
//  append_dir(std::string(PACKAGE_DATA_DIR)+"/docs/");
#else
  append_dir(BinaryVerzeichnis());
  append_dir(BinaryVerzeichnis()+"Daten\\");
//  append_dir(BinaryVerzeichnis()+"Hilfe\\");
#endif  
    
}


std::string magus_paths::with_path(const std::string &name,bool path_only,bool noexit)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,name,path_only,noexit);
  if (argv0.empty()) Ausgabe(Ausgabe::Error, "magus_paths::with_path without init");
  for(std::vector<std::string>::const_iterator i=paths.begin();i!=paths.end();++i)
   {
     std::string n=*i+name;
//cout <<"Suche nach "<< n<<'\n';
     if(!access(n.c_str(),R_OK)) 
      { if(path_only) return *i;
        else return n;
      }
   }
  std::string path;
  for(std::vector<std::string>::const_iterator i=paths.begin();i!=paths.end();++i)
     path=path+*i+":";
  Ausgabe(Ausgabe::Warning, "File "+name+" not found in "+path);
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
