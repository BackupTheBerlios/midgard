// $Id: Magus_Optionen.cc,v 1.27 2004/05/18 13:26:57 christof Exp $
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

#include "Magus_Optionen.hh"
#include <fstream>
#include <Misc/TagStream.h>
#ifdef __MINGW32__
#  include "registry.h"
#endif
#include "Windows_Linux.hh"
#include <cassert>
#include <Ausgabe.hh>
#include <magus_paths.h>
//#include <libmagusicons/magusicons.h>
#include <Misc/Global_Settings.h>
#include <Region.hh>
#include "NotFound.h"

// HKEY_LOCAL_MACHINE\software\classes\http\shell\open\command ?

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
     Ausgabe(Ausgabe::Debug,"Found "+ext+" Viewer @"+path);
     return path;
   }
   return "";
}
#endif

void Magus_Optionen::init_all()
{
   Optionen_init();
   Ober_init();
   Icon_init();
   Strings_init();
   pdfViewer_init();
}

void Magus_Optionen::init()
{  assert(!Programmoptionen);
   Programmoptionen=new Magus_Optionen;
   Programmoptionen->init_all();
   Global_Settings::set_impl(&global_settings_load,&global_settings_save);
}

std::string Magus_Optionen::Viewer() const
{
#ifndef __MINGW32__
  if     (pdfViewerCheck(Magus_Optionen::gv).active)       return "gv";
  else if(pdfViewerCheck(Magus_Optionen::xpdf).active)     return "xpdf";
  else if(pdfViewerCheck(Magus_Optionen::acroread).active) return "acroread";
  else if(pdfViewerCheck(Magus_Optionen::anderer).active)  return getString(pdf_viewer);
  return("no_legal_pdf_viewer_selected");
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

Model_ref<std::string> Magus_Optionen::getString(StringIndex index)
{
 for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
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

Magus_Optionen::st_pdfViewer &Magus_Optionen::pdfViewerCheck(pdfViewerIndex pi)
{
 for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   if(i->index==pi) return *i;
 assert(!"pdfViewer: nicht gefunden");
 abort();
}
 
const Magus_Optionen::st_pdfViewer &Magus_Optionen::pdfViewerCheck(pdfViewerIndex pi) const
{
 return const_cast<Magus_Optionen*>(this)->pdfViewerCheck(pi);
}
 
void Magus_Optionen::setOptionCheck(std::string os,bool b,int wert)
{
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->text==os) 
     {  
       i->active=b;
       if(wert!=-1) i->wert=wert;
       return; 
     }
 Ausgabe(Ausgabe::Warning,"Option "+os+" unbekannt");
}

void Magus_Optionen::setString(std::string os,std::string b)
{
 for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->text==os) 
     { i->name=b;
       return; 
     }
 Ausgabe(Ausgabe::Warning,"Option "+os+" unbekannt");
}
 
void Magus_Optionen::setOber(std::string hs,bool b)
{
  for(std::list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   {
    if(i->text==hs)  
      { 
        i->active=b;
//cout << "setOber: "<<hs<<'\t'<<i->active<<'\n';
        return;
      }
   }
 Ausgabe(Ausgabe::Warning,"Option "+hs+" unbekannt");
}

void Magus_Optionen::setIcon(std::string hs,bool b)
{ bool found=false;
  for(std::list<st_Icon>::iterator i=list_Icon.begin();i!=list_Icon.end();++i)
   {
    if(i->text==hs)
      { 
        i->active=b;
        found=true;
//        return;
      }
    else if (b) i->active=false;
   }
 if (!found) Ausgabe(Ausgabe::Warning,"Option "+hs+" unbekannt");
}

void Magus_Optionen::setpdfViewer(std::string is,bool b)
{
  for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->text==is) i->active=b;
     else i->active=!b;
   }
}

void Magus_Optionen::Optionen_init()
{
  list_OptionenCheck.push_back(st_OptionenCheck(Notebook_start, 
                           "MAGUS mit bestimmter Seite starten",false,0));

  list_OptionenCheck.push_back(st_OptionenCheck(Wizard_immer_starten, 
                           "Wizard bei jedem Programmstart starten",true));

  list_OptionenExecute.push_back(st_OptionenExecute(show_InfoWindow,"Info Fenster zeigen"));
  list_OptionenExecute.push_back(st_OptionenExecute(LernschemaSensitive,
                           "Lernschema/Steigern auswählbar machen"));
}


void Magus_Optionen::Strings_init()
{
  datei_history=6;
#ifndef __MINGW32__
  list_Strings.push_back(st_strings(pdf_viewer,"PDF Viewer",""));
  list_Strings.push_back(st_strings(html_viewer,"HTML Viewer","mozilla"));
  list_Strings.push_back(st_strings(tmppfad,"TEMP-Pfad","/tmp/"));
  list_Strings.push_back(st_strings(speicherpfad,"Speicherverzeichnis",magus_paths::MagusVerzeichnis()));
#else
  list_Strings.push_back(st_strings(pdf_viewer,"PDF Viewer",CommandByExtension(".pdf")));
  // class "http"?
  list_Strings.push_back(st_strings(html_viewer,"HTML Viewer",CommandByExtension(".htm")));
  char *tmp=getenv("TMPDIR");
  if (!tmp) tmp=getenv("TMP");
  if (!tmp) tmp=getenv("TEMP");
  if (!tmp) tmp="C:\\WINDOWS\\TEMP";
  list_Strings.push_back(st_strings(tmppfad,"TEMP-Pfad",std::string(tmp)+WinLux::dirsep));
  
  // %USERPROFILE%\Anwendungsdaten\Magus ???
  list_Strings.push_back(st_strings(speicherpfad,"Speicherverzeichnis",magus_paths::MagusVerzeichnis()));
#endif
}


void Magus_Optionen::pdfViewer_init()
{
#ifndef __MINGW32__
  std::vector<Model_ref<bool> > v;
  list_pdfViewer.push_back(st_pdfViewer(acroread,
                           "acroread",
                           true));
  v.push_back(list_pdfViewer.back().active);
  list_pdfViewer.push_back(st_pdfViewer(gv,
                           "gv",
                           false));
  v.push_back(list_pdfViewer.back().active);
  list_pdfViewer.push_back(st_pdfViewer(xpdf,
                           "xpdf",
                           false));
  v.push_back(list_pdfViewer.back().active);
  list_pdfViewer.push_back(st_pdfViewer(anderer,
                           "anderer",
                           false));
  v.push_back(list_pdfViewer.back().active);
  ausschluesse.push_back(RadioModel(v));
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
  std::vector<Model_ref<bool> > v;
 list_Icon.push_back(st_Icon(Self,"MAGUS-Stil",true));
  v.push_back(list_Icon.back().active);
 list_Icon.push_back(st_Icon(Ulf,"Win32-Stil",false));
  v.push_back(list_Icon.back().active);
 list_Icon.push_back(st_Icon(Gtk2,"Gtk2-Stil",false));
  v.push_back(list_Icon.back().active);
  ausschluesse.push_back(RadioModel(v));
}

// Lines marked with 'compat' are to maintain compatibility
#include<iostream>
void Magus_Optionen::load_options(const std::string &filename)
{try {
  std::ifstream f(filename.c_str());
  if (!f.good()) 
  { Ausgabe(Ausgabe::Error,"Cannot open "+filename);
    return ;
  }
  TagStream ts(f);
  const Tag *data=&ts.getContent();
  if(data->Type()!="MAGUS-data")
    { Ausgabe(Ausgabe::Error,"Optionen: falscher Tag "+data->Type());
      ts.debug();
      return;
    }
  const Tag *options=data->find("Optionen");
  if (!options) options=data; // compat
  FOR_EACH_CONST_TAG_OF(i,*options,"Optionen") // compat
     setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"),i->getIntAttr("Page",NOPAGE));
  FOR_EACH_CONST_TAG_OF(i,*options,"Option")
  {  if (i->hasAttr("Programm"))
        my_global_settings[st_Global_Settings_key(i->getIntAttr("Benutzer",0),i->getAttr("Programm"),i->getAttr("Name"))]
     		= i->getAttr("Wert");
     else
        setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"),i->getIntAttr("Page",NOPAGE));
  }
  FOR_EACH_CONST_TAG_OF(i,*options,"Ansicht")
     setOber(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"Icon")
     setIcon(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"pdfViewer")
     setpdfViewer(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*options,"Einstellungen")
     setString(i->getAttr("Name"),i->getAttr("Wert"));

  const Tag *regionen=data->find("Regionen");
  if(regionen) FOR_EACH_CONST_TAG_OF(i,*regionen,"Region")
    standard_regionen[i->getAttr("Name")]=i->getBoolAttr("Wert");

  const Tag *data2=ts.find("MAGUS-fenster"); // compat
  if (!data2) data2=data->find("Fenster");
  if(data2)
   {
     FOR_EACH_CONST_TAG_OF(i,*data2,"WindowPositions")
       {
         std::string name=i->getAttr("Name");
         int x=i->getIntAttr("X");
         int y=i->getIntAttr("Y");
         int breite=i->getIntAttr("Breite");
         int hoehe=i->getIntAttr("Höhe");
         setWindowPosition(name,x,y,breite,hoehe);
       }
   }

  const Tag *data3=ts.find("MAGUS-history"); // compat
  if (!data3) data3=data->find("History");
  if(data3)
   {
     FOR_EACH_CONST_TAG_OF(i,*data3,"DateiHistory")
       setDateiHistory(i->getIntAttr("Anzahl"));
     FOR_EACH_CONST_TAG_OF(i,*data3,"Datei")
       LDateien.push_back(i->getAttr("Name"));
   }
//  hauptfenster->menu_init();
 } catch (std::exception &e) 
 {  Ausgabe(Ausgabe::Error,"Optionen konnten nicht geladen werden: "+ std::string(e.what()));
 }
 geaendert=false;
}

                                                   
//#include <iostream>
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
 for(std::list<std::string>::const_iterator i=LDateien.begin();i!=LDateien.end();++i)
  { hist.push_back(Tag("Datei")).setAttr("Name",*i);
  }

 if(OberCheck(SaveFenster).active)
  { Tag &fenstert=data.push_back(Tag("Fenster"));

    for(std::list<st_WindowPosition>::const_iterator i=list_Windows.begin();i!=list_Windows.end();++i)    
     {
       Tag &T=fenstert.push_back(Tag("WindowPositions"));
       T.setAttr("Name",i->name);
       T.setIntAttr("Breite",i->width);
       T.setIntAttr("Höhe",i->height);
       T.setIntAttr("X", i->x);
       T.setIntAttr("Y", i->y);
     }
  }

 Tag &optionen=data.push_back(Tag("Optionen"));
 for(std::list<st_OptionenCheck>::const_iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   { Tag &opt=optionen.push_back(Tag("Option"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
     if(i->wert!=-1 && i->active)  opt.setIntAttr("Page",i->wert);
//     if(i->index==Notebook_start && i->active) opt.setIntAttr("Page",i->wert);
   }
 for(std::map<st_Global_Settings_key,std::string>::const_iterator i=my_global_settings.begin();i!=my_global_settings.end();++i)
   { if (i->second.empty()) continue;
     Tag &opt=optionen.push_back(Tag("Option"));
     if (i->first.userid) opt.setIntAttr("Benutzer",i->first.userid);
     opt.setAttr("Programm",i->first.program);
     opt.setAttr("Name",i->first.name);
     opt.setAttr("Wert", i->second);
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
  for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(!i->active) continue;
     Tag &opt=optionen.push_back(Tag("pdfViewer"));
     opt.setAttr("Name",i->text);
     opt.setBoolAttr("Wert", i->active);
   }
  for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   {
     if(i->name.Value().empty()) continue;
     Tag &opt=optionen.push_back(Tag("Einstellungen"));
     opt.setAttr("Name",i->text);
     opt.setAttr("Wert", i->name);
   }
  Tag &reg=data.push_back(Tag("Regionen"));
  for(regionen_t::const_iterator i=standard_regionen.begin();i!=standard_regionen.end();++i)
    {
      Tag &r=reg.push_back(Tag("Region"));
      r.setAttr("Name",i->first);
      r.setBoolAttr("Wert",i->second);
    }
  ts.write(datei);
  geaendert=false;
}
                                                   
Magus_Optionen *Programmoptionen;

static bool operator==(const Magus_Optionen::st_WindowPosition &a, const std::string &b)
{  return a.name==b;
}

void Magus_Optionen::setWindowPosition(const std::string &name,int x,int y,unsigned w,unsigned h)
{  std::list<st_WindowPosition>::iterator i=
		std::find(list_Windows.begin(),list_Windows.end(),name);
   if (i!=list_Windows.end())
   {  i->x=x; i->y=y; i->width=w; i->height=h;
   }
   else list_Windows.push_back(st_WindowPosition(name,x,y,w,h));
}

#include "Abenteurer.hh"
void Magus_Optionen::setStandardRegionen(const Abenteurer &A)
{
   for(Abenteurer::regionen_t::const_iterator i=A.getRegionen().begin();i!=A.getRegionen().end();++i)
     standard_regionen[i->first->Name()] = i->second;    
}



void Magus_Optionen::global_settings_save(int userid,const std::string& program,
      		const std::string& name, const std::string& value)
{  Programmoptionen->my_global_settings[st_Global_Settings_key(userid,program,name)]=value;
   Programmoptionen->geaendert=true;
}
std::string Magus_Optionen::global_settings_load(int userid,const std::string& program,
      		const std::string& name)
{  return Programmoptionen->my_global_settings[st_Global_Settings_key(userid,program,name)];
}

Magus_Optionen::Magus_Optionen() 
	: datei_history(), geaendert() 
{}
