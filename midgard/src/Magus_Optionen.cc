// $Id: Magus_Optionen.cc,v 1.1 2003/07/11 22:47:25 christof Exp $
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

#include "Magus_Optionen.hh"
#include <fstream>
#include <Misc/TagStream.h>
#ifdef __MINGW32__
#  include "registry.h"
#endif
#include "Windows_Linux.hh"

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

Magus_Optionen::Magus_Optionen(midgard_CG* h)
:hauptfenster(h)
{
   Optionen_init();
   Hausregeln_init();
   Ober_init();
   Icon_init();
   Strings_init();
   pdfViewer_init();
}

std::string Magus_Optionen::Viewer() const
{
#ifndef __MINGW32__
  if     (pdfViewerCheck(Magus_Optionen::gv).active)       return "gv";
  else if(pdfViewerCheck(Magus_Optionen::xpdf).active)     return "xpdf";
  else if(pdfViewerCheck(Magus_Optionen::acroread).active) return "acroread";
  else if(pdfViewerCheck(Magus_Optionen::anderer).active)  return getString(pdf_viewer);
  else assert(!"");
  abort();
#else
  return getString(pdf_viewer);
#endif  
}

std::string Magus_Optionen::getString(StringIndex index) const 
{
 for(std::list<st_strings>::const_iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->index==index) return i->name;    
 abort();//never get here
}

void Magus_Optionen::setString(StringIndex index,std::string n)
{
 for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->index==index) { i->name=n; return; }
}

Magus_Optionen::st_OptionenCheck &Magus_Optionen::OptionenCheck(OptionenCheckIndex oi) 
{
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->index==oi) 
     { //if(wert!=-1) const_cast<st_OptionenCheck&>(*i).wert=wert;
       return *i;
     }
 assert(!"OptionenCheck: nicht gefunden");
 abort();
}

Magus_Optionen::st_Haus &Magus_Optionen::HausregelCheck(HausIndex hi) 
{
 for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   if(i->index==hi) return *i;
 assert(!"HausregelCheck: nicht gefunden");
 abort();
}

Magus_Optionen::st_Ober &Magus_Optionen::OberCheck(OberIndex hi) 
{
 for(std::list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   if(i->index==hi) return *i;
 assert(!"OberCheck: nicht gefunden");
 abort();
}

Magus_Optionen::st_Icon &Magus_Optionen::IconCheck(IconIndex hi) 
{
 for(std::list<st_Icon>::iterator i=list_Icon.begin();i!=list_Icon.end();++i)
   if(i->index==hi) return *i;
 assert(!"IconCheck: nicht gefunden");
 abort();
}

Magus_Optionen::IconIndex Magus_Optionen::getIconIndex() const
{
 for(std::list<st_Icon>::const_iterator i=list_Icon.begin();i!=list_Icon.end();++i)
   if(i->active) return i->index;
 throw std::out_of_range("getIconIndex");
}

Magus_Optionen::st_pdfViewer Magus_Optionen::pdfViewerCheck(pdfViewerIndex pi) const 
{
 for(std::list<st_pdfViewer>::const_iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   if(i->index==pi) return *i;
 assert(!"pdfViewer: nicht gefunden");
 abort();
}
 
void Magus_Optionen::setOptionCheck(std::string os,bool b,int wert)
{
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->text==os) 
     {  
       i->active=b;
       if(wert!=-1) i->wert=wert;
       OptionenCheck_setzen_from_menu(i->index);
       return; 
     }
 std::cerr << "Option "<<os<<" unbekannt\n";
}

void Magus_Optionen::setString(std::string os,std::string b)
{
 for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->text==os) 
     { i->name=b;
       return; 
     }
 std::cerr << "Option "<<os<<" unbekannt\n";
}
 
void Magus_Optionen::setHausregeln(std::string hs,bool b)
{
  for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
    if(i->text==hs)  
      { 
        i->active=b;
        Hausregeln_setzen_from_menu(i->index);
        return;
      }
 std::cerr << "Option "<<hs<<" unbekannt\n";
}

void Magus_Optionen::setOber(std::string hs,bool b)
{
  for(std::list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   {
    if(i->text==hs)  
      { 
        i->active=b;
//cout << "setOber: "<<hs<<'\t'<<i->active<<'\n';
        Ober_setzen_from_menu(i->index);
        return;
      }
   }
 std::cerr << "Option "<<hs<<" unbekannt\n";
}

void Magus_Optionen::setIcon(std::string hs,bool b)
{
  for(std::list<st_Icon>::iterator i=list_Icon.begin();i!=list_Icon.end();++i)
   {
    if(i->text==hs)  
      { 
        i->active=b;
        Icon_setzen_from_menu(i->index);
        return;
      }
   }
 std::cerr << "Option "<<hs<<" unbekannt\n";
}

void Magus_Optionen::setpdfViewer(std::string is,bool b)
{
  for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->text==is) i->active=b;
     else i->active=!b;
   }
}


void Magus_Optionen::OptionenCheck_setzen_from_menu(OptionenCheckIndex index)
{
//  if(!hauptfenster->fire_enabled) return;
//  hauptfenster->fire_enabled=false;
  for(std::list<Magus_Optionen::st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   {
     if(i->index!=index) continue;
     else if(i->index==Wizard_immer_starten) hauptfenster->show_wizard_active(i->active);
     else if(i->index==Notebook_start)  
      { //i->wert=wert;
//        if(!i->spin) return;
//cout << "Option: "<<i->spin<<'\n';
//        if(i->active) i->spin->show();
//        else i->spin->hide();
      }
   }
//  hauptfenster->fire_enabled=true;
}
 
void Magus_Optionen::OptionenExecute_setzen_from_menu(OptionenExecuteIndex index)
{
  if(index==LernschemaSensitive) hauptfenster->lernschema_sensitive(true);
  if(index==show_InfoWindow) hauptfenster->InfoFenster->Show();
}

void Magus_Optionen::Ober_setzen_from_menu(OberIndex index)
{
  for(std::list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   {
     if(i->index==index) 
      { 
        if     (index==Bilder) hauptfenster->show_Pics(i->active);
        else if(index==AutoShrink) hauptfenster->autoshrink(i->active);
        else if(index==Menueleiste) hauptfenster->show_Menueleiste(i->active);
        else if(index==Knopfleiste) hauptfenster->show_Knopfleiste(i->active);
        else if(index==Status) hauptfenster->show_Statusleiste(i->active);
        else if(index==NoInfoFenster) ;
        else if(index==BegruessungsFenster) ;
        else if(index==Icons) 
         { if(!i->active && !OberCheck(Beschriftungen).active)
            {
              hauptfenster->set_status("Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
//              i->active=true;
            }
           else 
              hauptfenster->show_Icons(i->active);
         }
        else if(index==Beschriftungen) 
         { if(!i->active && !OberCheck(Icons).active)
            {
              hauptfenster->set_status("Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
//              i->active=true;
            }
           else 
              hauptfenster->show_Beschriftungen(i->active);
         }
        else if(index==Customize_Icons)
         {
           Gtk::CustomizeToolbars(hauptfenster->notebook_main,
                     i->active,OberCheck(Customize_Text).active,
                     OberCheck(Customize_Tab).active);
         }
        else if(index==Customize_Text)
         {
           Gtk::CustomizeToolbars(hauptfenster->notebook_main,
                     OberCheck(Customize_Icons).active,i->active,
                     OberCheck(Customize_Tab).active);
         }
        else if(index==Customize_Tab)
         {
           Gtk::CustomizeToolbars(hauptfenster->notebook_main,
                     OberCheck(Customize_Icons).active,
                     OberCheck(Customize_Text).active,i->active);
         }
//        hauptfenster->menu_init();
        return;
      }
   }
}   

void Magus_Optionen::Icon_setzen_from_menu(IconIndex index)
{
//  assert(b);
  static bool setbool=true;
  if(setbool==false) return;
  for(std::list<st_Icon>::iterator i=list_Icon.begin();i!=list_Icon.end();++i)
   {
     setbool=false;
     if(i->index!=index) i->active = false;
   }
  hauptfenster->Icons_setzen();
  setbool=true;
}   


    
void Magus_Optionen::pdfViewer_setzen_from_menu(pdfViewerIndex index)
{
  for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->index==index) i->active = true  ;
     else                i->active = false ;
   }
}   

void Magus_Optionen::Optionen_init()
{
  list_OptionenCheck.push_back(st_OptionenCheck(Notebook_start, 
                           "MAGUS mit bestimmter Seite starten",false,
                           Glib::RefPtr<Gdk::Pixbuf>(),1));

  list_OptionenCheck.push_back(st_OptionenCheck(Wizard_immer_starten, 
                           "Wizard bei jedem Programmstart starten",true,
                           Glib::RefPtr<Gdk::Pixbuf>()));


  list_OptionenExecute.push_back(st_OptionenExecute(show_InfoWindow,"Info Fenster zeigen",
  			Glib::RefPtr<Gdk::Pixbuf>()));
  list_OptionenExecute.push_back(st_OptionenExecute(LernschemaSensitive,
                           "Lernschema/Steigern auswählbar machen",
                           Glib::RefPtr<Gdk::Pixbuf>()));
}


void Magus_Optionen::Strings_init()
{
  datei_history=6;
#ifndef __MINGW32__
  list_Strings.push_back(st_strings(pdf_viewer,"PDF Viewer",""));
  list_Strings.push_back(st_strings(html_viewer,"HTML Viewer","mozilla"));
  list_Strings.push_back(st_strings(tmppfad,"TEMP-Pfad","/tmp/"));
  list_Strings.push_back(st_strings(speicherpfad,"Speicherverzeichnis",hauptfenster->MagusVerzeichnis()));
#else
  list_Strings.push_back(st_strings(pdf_viewer,"PDF Viewer",CommandByExtension(".pdf")));
  list_Strings.push_back(st_strings(html_viewer,"HTML Viewer",CommandByExtension(".htm")));
  char *tmp=getenv("TMPDIR");
  if (!tmp) tmp=getenv("TMP");
  if (!tmp) tmp=getenv("TEMP");
  if (!tmp) tmp="C:\\WINDOWS\\TEMP";
  list_Strings.push_back(st_strings(tmppfad,"TEMP-Pfad",std::string(tmp)+WinLux::dirsep));
  
  // %USERPROFILE%\Anwendungsdaten\Magus ???
  list_Strings.push_back(st_strings(speicherpfad,"Speicherverzeichnis",hauptfenster->MagusVerzeichnis()));
#endif
}


void Magus_Optionen::pdfViewer_init()
{
#ifndef __MINGW32__
  list_pdfViewer.push_back(st_pdfViewer(acroread,
                           "acroread",
                           true));
  list_pdfViewer.push_back(st_pdfViewer(gv,
                           "gv",
                           false));
  list_pdfViewer.push_back(st_pdfViewer(xpdf,
                           "xpdf",
                           false));
  list_pdfViewer.push_back(st_pdfViewer(anderer,
                           "anderer",
                           false));
#else
  list_pdfViewer.push_back(st_pdfViewer(anderer,
                           "PDF Programm",
                           true));
#endif
}


void Magus_Optionen::Ober_init()
{
 list_Ober.clear();  
 list_Ober.push_back(st_Ober(SaveFenster,"Fenstergröße und -position speichern",false));
 list_Ober.push_back(st_Ober(AutoShrink,"Fenster automatisch verkleinern",false));
 list_Ober.push_back(st_Ober(Bilder,"Bilder anzeigen",true));
 list_Ober.push_back(st_Ober(Menueleiste,"Menüleiste",true));
 list_Ober.push_back(st_Ober(Knopfleiste,"Knopfleiste",true));
 list_Ober.push_back(st_Ober(Customize_Icons,"Icons anzeigen",true));
 list_Ober.push_back(st_Ober(Customize_Text,"Text anzeigen",true));
 list_Ober.push_back(st_Ober(Customize_Tab,"Text der Reiter anzeigen",true));
 list_Ober.push_back(st_Ober(Icons,"Icons der Knopfleiste",true));
 list_Ober.push_back(st_Ober(Beschriftungen,"Beschriftungen der Knopfleiste",true));
 list_Ober.push_back(st_Ober(Status,"Statuszeile",true));
 list_Ober.push_back(st_Ober(NoInfoFenster,"Kein automatisches Öffnen des Infofensters",false,false));
 list_Ober.push_back(st_Ober(BegruessungsFenster,"Automatisches Öffnen des Begrüssungsfensters",true));
}


void Magus_Optionen::Icon_init()
{
 list_Icon.clear();  
 list_Icon.push_back(st_Icon(Self,"MAGUS-Stil",true));
 list_Icon.push_back(st_Icon(Ulf,"Win32-Stil",false));
 list_Icon.push_back(st_Icon(Gtk2,"Gtk2-Stil",false));
}

// Lines marked with 'compat' are to maintain compatibility
void Magus_Optionen::load_options(const std::string &filename)
{try {
  std::ifstream f(filename.c_str());
  if (!f.good()) std::cout << "Cannot open " << filename << '\n';
  TagStream ts(f);
  // we should use ts.getContent once compatibility is not needed !
  const Tag *data=ts.find("MAGUS-optionen"); // compat
  if (!data) data=ts.find("MAGUS-data");
  if(!data)    
    { std::cout << "Optionen konnten nicht geladen werden";
      ts.debug();
      return;
    }
  const Tag *options=data->find("Optionen");
  if (!options) options=data; // compat
  FOR_EACH_CONST_TAG_OF(i,*options,"Optionen") // compat
     setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"),i->getIntAttr("Page",hauptfenster->NOPAGE));
  FOR_EACH_CONST_TAG_OF(i,*options,"Option")
     setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"),i->getIntAttr("Page",hauptfenster->NOPAGE));
  FOR_EACH_CONST_TAG_OF(i,*options,"Ansicht")
     setOber(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"Icon")
     setIcon(i->getAttr("Name"),i->getBoolAttr("Wert"));
  if (IconCheck(Magus_Optionen::Self).active) MagusIcons::set_icon_style(MagusIcons::Alessandro);
  else if (IconCheck(Magus_Optionen::Ulf).active) MagusIcons::set_icon_style(MagusIcons::Ulf);
  else if (IconCheck(Magus_Optionen::Gtk2).active) MagusIcons::set_icon_style(MagusIcons::Gtk);
  else MagusIcons::set_icon_style(MagusIcons::Any);
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
     FOR_EACH_CONST_TAG_OF(i,*data2,"WindowPositions")
       {
         std::string name=i->getAttr("Name");
         int x=i->getIntAttr("X");
         int y=i->getIntAttr("Y");
         int breite=i->getIntAttr("Breite");
         int hoehe=i->getIntAttr("Höhe");
         Gtk::HandleBox *HB;
         if     (name=="handlebox_steigern_1")
            HB=hauptfenster->table_steigern->handlebox_steigern_1;
         else if(name=="handlebox_steigern_2")
            HB=hauptfenster->table_steigern->handlebox_steigern_2;
         else if(name=="handlebox_steigern_3")
            HB=hauptfenster->table_steigern->handlebox_steigern_3;
         else if(name=="handlebox_steigern_4")
            HB=hauptfenster->table_steigern->handlebox_steigern_4;
         else continue;
std::cout << "SETZEN: "<<name<<' '<<x<<' '<<y<<"\n\n\n\n";
         detachHB(*HB,x,y,breite,hoehe);
       }
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
//  hauptfenster->menu_init();
 } catch (std::exception &e) { std::cerr << e.what() << '\n'; }
}

                                                   
void Magus_Optionen::save_options(const std::string &filename)
{
  std::ofstream datei(filename.c_str());
  if (!datei.good())
   { 
    Ausgabe(Ausgabe::Error, "Kann die Optionen nicht speichern");
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
    Glib::RefPtr<Gdk::Window> fenster=hauptfenster->get_window();
    fenster->get_size(width,height);
    fenster->get_position(x,y);
    Tag &groesse=fenstert.push_back(Tag("Größe"));
    groesse.setIntAttr("Breite",width);
    groesse.setIntAttr("Höhe",height);
    Tag &position=fenstert.push_back(Tag("Position"));
    position.setIntAttr("X", x);
    position.setIntAttr("Y", y);

    // Handle-Windows
    std::vector<std::pair<std::string,Glib::RefPtr<Gdk::Window> > > VW;
    VW.push_back(std::pair<std::string,Glib::RefPtr<Gdk::Window> >("main",hauptfenster->get_window()));
    if(hauptfenster->table_steigern->handlebox_steigern_1->is_float_window_mapped())
       VW.push_back(std::pair<std::string,Glib::RefPtr<Gdk::Window> >("handlebox_steigern_1",hauptfenster->table_steigern->handlebox_steigern_1->get_float_window()));
    if(hauptfenster->table_steigern->handlebox_steigern_2->is_float_window_mapped())
       VW.push_back(std::pair<std::string,Glib::RefPtr<Gdk::Window> >("handlebox_steigern_2",hauptfenster->table_steigern->handlebox_steigern_2->get_float_window()));
    if(hauptfenster->table_steigern->handlebox_steigern_3->is_float_window_mapped())
       VW.push_back(std::pair<std::string,Glib::RefPtr<Gdk::Window> >("handlebox_steigern_3",hauptfenster->table_steigern->handlebox_steigern_3->get_float_window()));
    if(hauptfenster->table_steigern->handlebox_steigern_4->is_float_window_mapped())
       VW.push_back(std::pair<std::string,Glib::RefPtr<Gdk::Window> >("handlebox_steigern_4",hauptfenster->table_steigern->handlebox_steigern_4->get_float_window()));
    for(std::vector<std::pair<std::string,Glib::RefPtr<Gdk::Window> > >::iterator i=VW.begin();i!=VW.end();++i)    
     {
       Tag &T=fenstert.push_back(Tag("WindowPositions"));
       gint width,height,x,y;
       i->second->get_size(width,height);
       i->second->get_position(x,y);
       T.setAttr("Name",i->first);
       T.setIntAttr("Breite",width);
       T.setIntAttr("Höhe",height);
       T.setIntAttr("X", x);
       T.setIntAttr("Y", y);
     }
  }

 Tag &optionen=data.push_back(Tag("Optionen"));
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   { Tag &opt=optionen.push_back(Tag("Option"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
//geht so nicht    if(i->wert!=-1 && i->active)  opt.setIntAttr("Page",i->wert);
     if(i->index==Notebook_start && i->active) opt.setIntAttr("Page",i->wert);
   }
 for(std::list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   { Tag &opt=optionen.push_back(Tag("Ansicht"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
   }
 for(std::list<st_Icon>::iterator i=list_Icon.begin();i!=list_Icon.end();++i)
   { 
     if(!i->active) continue;
     Tag &opt=optionen.push_back(Tag("Icon"));
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
                                                   