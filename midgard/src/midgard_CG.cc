// $Id: midgard_CG.cc,v 1.247 2002/07/01 08:57:29 thoma Exp $
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

#include "midgard_CG.hh"
#include <gtk--/notebook.h>
#include "Midgard_Info.hh"
#include "Fertigkeiten.hh"
#include <unistd.h>
//#include <stdlib.h>
#ifdef __MINGW32__
#include <time.h>
#endif
#include "Windows_Linux.hh"

midgard_CG::midgard_CG(const string &_argv0,const string &_magus_verzeichnis,
                       const string &datei)
: argv0(_argv0),magus_verzeichnis(_magus_verzeichnis),InfoFenster(0),
    MOptionen(0),wizard(0),ansicht_menu(0),region_menu(0),menu(0)
{
  InfoFenster = manage(new WindowInfo(this));
  // Menüs initialisieren
  ansicht_menu = manage(new Gtk::MenuItem("Ansicht"));
  region_menu = manage(new Gtk::MenuItem("Regionen"));
  main_menubar->append(*ansicht_menu);
  main_menubar->append(*region_menu);
  ansicht_menu->show();
  region_menu->show();

  // Optionen laden
  MOptionen = new Midgard_Optionen(this); 
  table_optionen->set_Hauptfenster(this);
  MOptionen->load_options(with_path("magus_optionen.xml",false,true));
  setenv("TEXMFOUTPUT",MOptionen->getString(Midgard_Optionen::tmppfad).c_str(),1);

  srand(time(0));
  Database.load(Midgard_Info,with_path("midgard.xml"));

  set_sensitive(true);

  if (!datei.empty()) xml_import(datei); // Charakter laden
  else if(MOptionen->OptionenCheck(Midgard_Optionen::Wizard_immer_starten).active) 
       on_wizard_starten_activate();
  else on_neuer_charakter_clicked();

  // für die NEWS
  Gtk::OStream os(list_news);
  os << 
#include"NEWS.h" 
   <<'\n';
}

midgard_CG::~midgard_CG()
{  //cout << "~midgard_CG()\n\n\n\n";
   unsetenv("TEXMFOUTPUT");
   delete MOptionen;
//   if (menu) delete menu;
//   if (table_steigern->menu_gradanstieg) table_steigern->delete menu_gradanstieg;
//   InfoFenster->destroy(); 
   if(wizard) delete wizard;
}


std::string midgard_CG::with_path(const std::string &name,bool path_only,bool noexit) const
{
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
  V.push_back(Binary_Verzeichnis());
  V.push_back(Binary_Verzeichnis()+"\\Daten");
  V.push_back(Binary_Verzeichnis()+"\\Hilfe");
#endif  
  std::string ntmp;
  for(std::vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
   {
     std::string n=*i+name;
cout <<"Suche nach "<< n<<'\n';
     if(!access(n.c_str(),R_OK)) 
      { if(path_only) return *i;
        else return n;
      }
   }
  cout << "File "+name+" nowhere found\n";
  if(!noexit) exit(1);
  return("");
}

std::string midgard_CG::BinaryVerzeichnis() const
{  
   if (argv0.rfind(WinLux::dirsep())!=std::string::npos) 
      return argv0.substr(0,argv0.rfind(WinLux::dirsep())+1);
   else return "";
}
