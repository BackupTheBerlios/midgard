
// $Id: Optionen.cc,v 1.48 2002/06/12 06:59:31 christof Exp $
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

#include "Optionen.hh"
#include "../pixmaps/midgard_logo_tiny.xpm"
#include "../pixmaps/Cyan-Dice-trans-50.xpm"
//#include "MidgardBasicElement.hh" // nur für NotFound
#include <fstream>
#include "TagStream.hh"
#include "export_common.h"
#include "midgard_CG.hh"
#ifdef __MINGW32__
#  include "registry.h"
#endif

#ifdef __MINGW32__
static std::string CommandByExtension(const std::string &ext)
{ char extclass[1024];
    
  reg_key r1(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes",ext.c_str(),0);
  r1.get_string(0, extclass, sizeof extclass, "");
  if (*extclass)
  {  reg_key r2(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes", extclass,
  		"shell", "open", "command", 0);
     r2.get_string(0, extclass, sizeof extclass, "");
  
     std::string path=extclass;
     if (path.size()>3 && path.substr(path.size()-3)==" %1") 
        path=path.substr(0, path.size()-3);
     else if (path.size()>5 && path.substr(path.size()-5)==" \"%1\"") 
        path=path.substr(0, path.size()-5);
std::cout << "Found "<<ext<<" Viewer @" << path << '\n';
     return path;
   }
   return "";
}
#endif

#include <gdk--.h>

Midgard_Optionen::Midgard_Optionen(midgard_CG* h)
:hauptfenster(h)
{
   Optionen_init();
   Hausregeln_init();
   Ober_init();
   Strings_init();
   pdfViewer_init();
}

std::string Midgard_Optionen::Viewer() const
{
#ifndef __MINGW32__
  if     (pdfViewerCheck(Midgard_Optionen::gv).active)       return "gv";
  else if(pdfViewerCheck(Midgard_Optionen::xpdf).active)     return "xpdf";
  else if(pdfViewerCheck(Midgard_Optionen::acroread).active) return "acroread";
  else if(pdfViewerCheck(Midgard_Optionen::anderer).active)  return getString(pdf_viewer);
  else assert(!"");
  abort();
#else
  return getString(pdf_viewer);
#endif  
}

std::string Midgard_Optionen::getString(StringIndex index) const 
{
 for(std::list<st_strings>::const_iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->index==index) return i->name;    
 abort();//never get here
}

void Midgard_Optionen::setString(StringIndex index,std::string n)
{
 for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->index==index) { i->name=n; return; }
}

Midgard_Optionen::st_OptionenCheck Midgard_Optionen::OptionenCheck(OptionenCheckIndex oi) const
{
 for(std::list<st_OptionenCheck>::const_iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->index==oi) return *i;
 assert(!"OptionenCheck: nicht gefunden");
 abort();
}

Midgard_Optionen::st_Haus Midgard_Optionen::HausregelCheck(HausIndex hi) const
{
 for(std::list<st_Haus>::const_iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   if(i->index==hi) return *i;
 assert(!"HausregelCheck: nicht gefunden");
 abort();
}

Midgard_Optionen::st_Ober Midgard_Optionen::OberCheck(OberIndex hi) const
{
 for(std::list<st_Ober>::const_iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   if(i->index==hi) return *i;
 assert(!"OberCheck: nicht gefunden");
 abort();
}

Midgard_Optionen::st_pdfViewer Midgard_Optionen::pdfViewerCheck(pdfViewerIndex pi) const 
{
 for(std::list<st_pdfViewer>::const_iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   if(i->index==pi) return *i;
 assert(!"pdfViewer: nicht gefunden");
 abort();
}
 
void Midgard_Optionen::setOptionCheck(std::string os,bool b)
{
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->text==os) 
     { OptionenCheck_setzen_from_menu(i->index,b);
       return; 
     }
 throw NotFound();
}

void Midgard_Optionen::setString(std::string os,std::string b)
{
 for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->text==os) 
     { i->name=b;
       return; 
     }
 throw NotFound();
}
 
void Midgard_Optionen::setHausregeln(std::string hs,bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
    if(i->text==hs)  
      { Hausregeln_setzen_from_menu(i->index,b);
        return;
      }
 throw NotFound();
}

void Midgard_Optionen::setOber(std::string hs,bool b)
{
  for(list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
    if(i->text==hs)  
      { Ober_setzen_from_menu(i->index,b);
        return;
      }
 throw NotFound();
}

void Midgard_Optionen::setAllHausregeln(bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
     i->active=b;
}
 
void Midgard_Optionen::setpdfViewer(std::string is,bool b)
{
  for(list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->text==is) i->active=b;
     else i->active=!b;
   }
}   
    

void Midgard_Optionen::OptionenCheck_setzen_from_menu(OptionenCheckIndex index,bool b)
{
//  if(!hauptfenster->fire_enabled) return;
//  hauptfenster->fire_enabled=false;
  for(std::list<Midgard_Optionen::st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   {
     if(i->index!=index) continue;
     i->active = b;
     if     (i->index==Original) { hauptfenster->checkbutton_original(i->active); hauptfenster->menu_init();}
//     else if(i->index==showPics) hauptfenster->Pics(i->active);
     else if(i->index==gw_wuerfeln) hauptfenster->show_gw_wuerfeln(i->active);
     else if(i->index==NSC_only) {hauptfenster->table_grundwerte->fill_typauswahl();
                                  hauptfenster->table_grundwerte->fill_typauswahl_2();} // zum Neuaufbau des Typmenüs
   }
//  hauptfenster->fire_enabled=true;
}
 
void Midgard_Optionen::OptionenExecute_setzen_from_menu(OptionenExecuteIndex index)
{
  if(index==LernschemaSensitive) hauptfenster->lernschema_sensitive(true);
//  if(index==WizardStarten) hauptfenster->wizard_starten_clicked();
//  if(index==LernschemaZusaetzeLoeschen) {hauptfenster->list_FertigkeitZusaetze.clear();
//                                         hauptfenster->on_lernliste_wahl_toggled();}   
  if(index==show_InfoWindow) hauptfenster->InfoFenster->Show();
}

void Midgard_Optionen::Hausregeln_setzen_from_menu(HausIndex index,bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     if(i->index==index) 
      { i->active = b;
        return;
      }
   }
}   
    
void Midgard_Optionen::Ober_setzen_from_menu(OberIndex index,bool b)
{
  for(list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   {
     if(i->index==index) 
      { i->active = b;
        if     (index==Bilder) hauptfenster->show_Pics(i->active);
        else if(index==AutoShrink) hauptfenster->autoshrink(i->active);
        else if(index==Menueleiste) hauptfenster->show_Menueleiste(i->active);
        else if(index==Knopfleiste) hauptfenster->show_Knopfleiste(i->active);
        else if(index==Status) hauptfenster->show_Statusleiste(i->active);
        else if(index==Icons) 
         { if(!b && !OberCheck(Beschriftungen).active)
            {
              hauptfenster->set_status("Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
              i->active=true;
            }
           else 
              hauptfenster->show_Icons(i->active);
         }
        else if(index==Beschriftungen) 
         { if(!b && !OberCheck(Icons).active)
            {
              hauptfenster->set_status("Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
              i->active=true;
            }
           else 
              hauptfenster->show_Beschriftungen(i->active);
         }
        else if(index==NIcons) 
           hauptfenster->show_NIcons(i->active);
        else if(index==NBeschriftungen) 
           hauptfenster->show_NBeschriftungen(i->active);
        hauptfenster->menu_init();
        return;
      }
   }
}   
    
void Midgard_Optionen::pdfViewer_setzen_from_menu(pdfViewerIndex index)
{
  for(list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->index==index) i->active = true  ;
     else                i->active = false ;
   }
}   
 
void Midgard_Optionen::Optionen_init()
{
  list_OptionenCheck.push_back(st_OptionenCheck(Original,"Originalregeln",
                           true,midgard_logo_tiny_xpm));
  list_OptionenCheck.push_back(st_OptionenCheck(NSC_only,"NSCs zulassen",
                           false,0));  
  list_OptionenCheck.push_back(st_OptionenCheck(gw_wuerfeln,
                           "Grundwerte nur mit einer Maustaste auswürfelbar machen",
                           false,Cyan_Dice_trans_50_xpm));
//  list_OptionenCheck.push_back(st_OptionenCheck(showPics,"Bilder anzeigen",true,0));
  list_OptionenCheck.push_back(st_OptionenCheck(Wizard_immer_starten, 
                           "Wizard bei jedem Programmstart starten",true,0));

  list_OptionenExecute.push_back(st_OptionenExecute(show_InfoWindow,"Info Fenster zeigen",0));
//  list_OptionenExecute.push_back(st_OptionenExecute(WizardStarten,"Wizard starten",0));
  list_OptionenExecute.push_back(st_OptionenExecute(LernschemaSensitive,
                           "Lernschema/Steigern auswählbar machen",0));
//  list_OptionenExecute.push_back(st_OptionenExecute(LernschemaZusaetzeLoeschen,
//                           "Fertigkeiten mit Zusätzen im Lernschema wieder anzeigen",0));
}


void Midgard_Optionen::Strings_init()
{
  datei_history=6;
#ifndef __MINGW32__
  list_Strings.push_back(st_strings(pdf_viewer,"PDF Viewer",""));
  list_Strings.push_back(st_strings(html_viewer,"HTML Viewer","mozilla"));
  list_Strings.push_back(st_strings(tmppfad,"TEMP-Pfad","/tmp"));
  list_Strings.push_back(st_strings(speicherpfad,"Speicherverzeichnis","~/magus/"));
#else
  list_Strings.push_back(st_strings(pdf_viewer,"PDF Viewer",CommandByExtension(".pdf")));
  list_Strings.push_back(st_strings(html_viewer,"HTML Viewer",CommandByExtension(".htm")));
  char *tmp=getenv("TMPDIR");
  if (!tmp) tmp=getenv("TEMP");
  if (!tmp) tmp="C:\WINDOWS\TEMP";
  list_Strings.push_back(st_strings(tmppfad,"TEMP-Pfad",tmp));
  
 {std::string save_path;
  char buf[1024];
  reg_key r1(HKEY_CURRENT_USER, KEY_READ, "Software", "Microsoft", "Windows",
  	"CurrentVersion", "Explorer", "User Shell Folders", NULL); // "AppData");?
  if (r1.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) save_path=buf;
  else
  {  reg_key r2(HKEY_USERS, KEY_READ, ".Default", "Software", "Microsoft", "Windows",
  	"CurrentVersion", "Explorer", "User Shell Folders", NULL);
     if (r2.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) save_path=buf;
     else
     {  reg_key r3(HKEY_LOCAL_MACHINE, KEY_READ, "Software", "Microsoft", "Windows",
     		"CurrentVersion", "Explorer", "User Shell Folders", NULL);
        if (r3.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) save_path=buf;
        else save_path="C:\\Eigene Dateien"
     }
  }
  save_path+="\\Magus\\";
  // %USERPROFILE%\Anwendungsdaten\Magus ???
  list_Strings.push_back(st_strings(speicherpfad,"Speicherverzeichnis",save_path));
#endif
}


void Midgard_Optionen::pdfViewer_init()
{
#ifndef __MINGW32__
  list_pdfViewer.push_back(st_pdfViewer(acroread,
                           "pdf Dokument mit 'acroread' betrachten",
                           true));
  list_pdfViewer.push_back(st_pdfViewer(gv,
                           "pdf Dokument mit 'gv' betrachten",
                           false));
  list_pdfViewer.push_back(st_pdfViewer(xpdf,
                           "pdf Dokument mit 'xpdf' betrachten",
                           false));
  list_pdfViewer.push_back(st_pdfViewer(anderer,
                           "anderer Viewer (z.B. 'kghostview', 'ggv')",
                           false));
#else
  list_pdfViewer.push_back(st_pdfViewer(anderer,
                           "PDF Programm",
                           true));
#endif
}

void Midgard_Optionen::Hausregeln_init()
{
 list_Hausregeln.clear();  
 list_Hausregeln.push_back(st_Haus(Gold,"1 GS entspricht 1 GFP",false));
}

void Midgard_Optionen::Ober_init()
{
 list_Ober.clear();  
 list_Ober.push_back(st_Ober(SaveFenster,"Größe und Position Fensters speichern",false));
 list_Ober.push_back(st_Ober(AutoShrink,"Automatisches verkleinern des Fensters",false));
 list_Ober.push_back(st_Ober(Bilder,"Bilder anzeigen",true));
 list_Ober.push_back(st_Ober(Menueleiste,"Menüleiste",true));
 list_Ober.push_back(st_Ober(Knopfleiste,"Knopfleiste",true));
 list_Ober.push_back(st_Ober(Icons,"Icons",true));
 list_Ober.push_back(st_Ober(Beschriftungen,"Beschriftungen",true));
 list_Ober.push_back(st_Ober(NIcons,"Icons der Notebooks",true));
 list_Ober.push_back(st_Ober(NBeschriftungen,"Beschriftungen der Notebooks",true));
 list_Ober.push_back(st_Ober(Status,"Statuszeile",true));
}

// Lines marked with 'compat' are to maintain compatibility
void Midgard_Optionen::load_options()
{try {
  ifstream f("midgard_optionen.xml");
  if (!f.good()) cout << "Cannot open " << "midgard_optionen.xml" << '\n';
  TagStream ts(f);
  // we should use ts.getContent once compatibility is not needed !
  const Tag *data=ts.find("MAGUS-optionen"); // compat
  if (!data) data=ts.find("MAGUS-data");
  if(!data)    
    { cout << "Optionen konnten nicht geladen werden";
      ts.debug();
      return;
    }
  const Tag *options=data->find("Optionen");
  if (!options) options=data; // compat
  FOR_EACH_CONST_TAG_OF(i,*options,"Optionen") // compat
     setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"Option")
     setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"Ansicht")
     setOber(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"Hausregel")
     setHausregeln(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"pdfViewer")
     setpdfViewer(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"Einstellungen")
     setString(i->getAttr("Name"),i->getAttr("Wert"));

  const Tag *data2=ts.find("MAGUS-fenster"); // compat
  if (!data2) data2=data->find("Fenster");
  if(data2)
   {
     FOR_EACH_CONST_TAG_OF(i,*data2,"Position")
        hauptfenster->setWindowPosition(i->getIntAttr("X"),i->getIntAttr("Y"));
     FOR_EACH_CONST_TAG_OF(i,*data2,"Groesse") // compat
        hauptfenster->setWindowSize(i->getIntAttr("Width"),i->getIntAttr("Height"));
     FOR_EACH_CONST_TAG_OF(i,*data2,"Größe")
        hauptfenster->setWindowSize(i->getIntAttr("Breite"),i->getIntAttr("Höhe"));
   }
  const Tag *data3=ts.find("MAGUS-history"); // compat
  if (!data3) data3=data->find("History");
  if(data3)
   {
     FOR_EACH_CONST_TAG_OF(i,*data3,"DateiHistory")
       setDateiHistory(i->getIntAttr("Anzahl"));
     FOR_EACH_CONST_TAG_OF(i,*data3,"Datei")
       hauptfenster->push_back_LDateien(i->getAttr("Name"));
   }
  hauptfenster->menu_init();
 } catch (std::exception &e) { cerr << e.what() << '\n'; }
}

                                                   
void Midgard_Optionen::save_options(WindowInfo *InfoFenster)
{
  ofstream datei("midgard_optionen.xml");
  if (!datei.good())
   { 
    hauptfenster->set_status("Ich kann die Optionen nicht speichern");
    return;
   }
  TagStream ts;
  ts.setEncoding("ISO-8859-1");

 Tag &data=ts.push_back(Tag("MAGUS-data"));
 Tag &hist=data.push_back(Tag("History"));
 hist.push_back(Tag("DateiHistory")).setIntAttr("Anzahl",DateiHistory());
 for(std::list<std::string>::const_iterator i=hauptfenster->LDateien.begin();i!=hauptfenster->LDateien.end();++i)
  { hist.push_back(Tag("Datei")).setAttr("Name",*i);
  }

 if(OberCheck(SaveFenster).active)
  { Tag &fenstert=data.push_back(Tag("Fenster"));
    gint width,height,x,y;
    Gdk_Window fenster=hauptfenster->get_window();
    fenster.get_size(width,height);
    fenster.get_position(x,y);
    Tag &groesse=fenstert.push_back(Tag("Größe"));
    groesse.setIntAttr("Breite",width);
    groesse.setIntAttr("Höhe",height);
    Tag &position=fenstert.push_back(Tag("Position"));
    position.setIntAttr("X", x);
    position.setIntAttr("Y", y);
  }

 Tag &optionen=data.push_back(Tag("Optionen"));
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   { Tag &opt=optionen.push_back(Tag("Option"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
   }
 for(std::list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   { Tag &opt=optionen.push_back(Tag("Ansicht"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
   }
  for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   { Tag &opt=optionen.push_back(Tag("Hausregel"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
   }
  for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(!i->active) continue;
     Tag &opt=optionen.push_back(Tag("pdfViewer"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
   }
  for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   {
     if(i->name.empty()) continue;
     Tag &opt=optionen.push_back(Tag("Einstellungen"));
     opt.setAttr("Name",i->text);
     opt.setAttr("Wert", i->name);
   }
  ts.write(datei);
}
                                                   
