// $Id: Optionen.cc,v 1.13 2002/04/19 06:42:05 christof Exp $
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

Midgard_Optionen::Midgard_Optionen(midgard_CG* h)
:hauptfenster(h)
{
   Optionen_init();
   Hausregeln_init();
   Ober_init();
   pdfViewer_init();
   Strings_init();
}

std::string Midgard_Optionen::Viewer()
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

std::string Midgard_Optionen::getString(StringIndex index)
{
 for(std::list<st_strings>::const_iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->index==index) return i->name;    
 abort();//never get here
}

void Midgard_Optionen::setString(StringIndex index,std::string n)
{
 for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   if(i->index==index) i->name=n;    
}

Midgard_Optionen::st_OptionenCheck Midgard_Optionen::OptionenCheck(OptionenCheckIndex oi)
{
 for(std::list<st_OptionenCheck>::const_iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->index==oi) return *i;
 assert(!"OptionenCheck: nicht gefunden");
 abort();
}

Midgard_Optionen::st_Haus Midgard_Optionen::HausregelCheck(HausIndex hi)
{
 for(std::list<st_Haus>::const_iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   if(i->index==hi) return *i;
 assert(!"HausregelCheck: nicht gefunden");
 abort();
}

Midgard_Optionen::st_Ober Midgard_Optionen::OberCheck(OberIndex hi)
{
 for(std::list<st_Ober>::const_iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   if(i->index==hi) return *i;
 assert(!"OberCheck: nicht gefunden");
 abort();
}

Midgard_Optionen::st_pdfViewer Midgard_Optionen::pdfViewerCheck(pdfViewerIndex pi)
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
     else if(i->index==showPics) hauptfenster->Pics(i->active);
     else if(i->index==gw_wuerfeln) hauptfenster->show_gw_wuerfeln(i->active);
     else if(i->index==NSC_only) hauptfenster->on_radiobutton_mann_toggled(); // zum Neuaufbau des Typmenüs
   }
//  hauptfenster->fire_enabled=true;
}
 
void Midgard_Optionen::OptionenExecute_setzen_from_menu(OptionenExecuteIndex index)
{
  if(index==LernschemaSensitive) hauptfenster->lernschema_sensitive(true);
  if(index==WizardStarten) hauptfenster->wizard_starten_clicked();
  if(index==LernschemaZusaetzeLoeschen) {hauptfenster->list_FertigkeitZusaetze.clear();
                                         hauptfenster->on_lernliste_wahl_toggled();}   
  if(index==show_InfoWindow) hauptfenster->InfoFenster->show();
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
  list_OptionenCheck.push_back(st_OptionenCheck(showPics,"Bilder anzeigen",true,0));
  list_OptionenCheck.push_back(st_OptionenCheck(Wizard_immer_starten, 
                           "Wizard bei jedem Programmstart zeigen",true,0));

  list_OptionenExecute.push_back(st_OptionenExecute(show_InfoWindow,"Info Fenster zeigen",0));
  list_OptionenExecute.push_back(st_OptionenExecute(WizardStarten,"Wizard starten",0));
  list_OptionenExecute.push_back(st_OptionenExecute(LernschemaSensitive,
                           "Lernschema/Steigern auswählbar machen",0));
  list_OptionenExecute.push_back(st_OptionenExecute(LernschemaZusaetzeLoeschen,
                           "Fertigkeiten mit Zusätzen im Lernschema wieder anzeigen",0));
}


void Midgard_Optionen::Strings_init()
{
  list_Strings.push_back(st_strings(pdf_viewer,"PDF Viewer",""));
  list_Strings.push_back(st_strings(html_viewer,"HTML Viewer","mozilla"));
  list_Strings.push_back(st_strings(tmppfad,"TEMP-Pfad","$TEMP"));
  list_Strings.push_back(st_strings(speicherpfad,"Speicherverzeichnis","$HOME/magus"));
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
                           "Programm",
                           true));

  char pdfclass[1024];
    
  reg_key r1(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes"); // ".pdf");
  r1.get_string(".pdf", pdfclass, sizeof pdfclass, "?");
  cout << pdfclass << '\n';
  reg_key r2(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes", pdfclass,
  		"shell", "open");
  r2.get_string("command", pdfclass, sizeof pdfclass, "?");
  cout << pdfclass << '\n';
  
  std::string path=pdfclass;
  if (path.substr(path.size()-3)==" %1")) 
     path=path.substr(0, path.size()-3);
  cout << path << '\n';

  setString(pdfViewer,path);
  
#if 0
[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\.pdf]
@="AcroExch.Document"
"Content Type"="application/pdf"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\AcroExch.Document\shell\open\command]
@="\"C:\\Programme\\Adobe\\Acrobat 4.0\\Reader\\AcroRd32.exe\" %1"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\AcroExch.Document\CLSID]
@="{B801CA65-A1FC-11D0-85AD-444553540000}"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{B801CA65-A1FC-11D0-85AD-444553540000
}\LocalServer]
@="C:\\Programme\\Adobe\\Acrobat 4.0\\Reader\\AcroRd32.exe"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Software\Adobe\Acrobat\Exe]
@="\"C:\\Programme\\Adobe\\Acrobat 4.0\\Reader\\AcroRd32.exe\""

[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\AcroRd32
.exe]
"Path"="C:\\Programme\\Adobe\\Acrobat 4.0\\Reader;C:\\Programme\\Adobe\\Acrobat 
4.0\\Resource\\Lib"
@="C:\\Programme\\Adobe\\Acrobat 4.0\\Reader\\AcroRd32.exe"

#endif
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
 list_Ober.push_back(st_Ober(Bilder,"Bilder anzeigen",true));
 list_Ober.push_back(st_Ober(Menueleiste,"Menüleiste",true));
 list_Ober.push_back(st_Ober(Knopfleiste,"Knopfleiste",true));
 list_Ober.push_back(st_Ober(Icons,"Icons",true));
 list_Ober.push_back(st_Ober(Beschriftungen,"Beschriftungen",true));
}

void Midgard_Optionen::load_options()
{ ifstream f("midgard_optionen.xml");
  if (!f.good()) cout << "Cannot open " << "midgard_optionen.xml" << '\n';
  TagStream ts(f);
  const Tag *data=ts.find("MAGUS-optionen");
  if(!data)    
    { cout << "Optionen konnten nicht geladen werden";
      ts.debug();
      return;
    }

  FOR_EACH_CONST_TAG_OF(i,*data,"Optionen")
     setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*data,"Hausregel")
     setHausregeln(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*data,"pdfViewer")
     setpdfViewer(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*data,"Einstellungen")
     setString(i->getAttr("Name"),i->getAttr("Wert"));
  hauptfenster->menu_init();
}

                                                   
void Midgard_Optionen::save_options(WindowInfo *InfoFenster)
{
  ofstream datei("midgard_optionen.xml");
  if (!datei.good())
   { 
    InfoFenster->AppendShow("Ich kann die Optionen nicht speichern");
    return;
   }
 datei << "<?xml";
 write_string_attrib(datei, "version", "1.0");
 write_string_attrib(datei, "encoding", TagStream::host_encoding);
 datei << "?>\n\n";
 datei << "<MAGUS-optionen>\n";
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   {
     datei << "  <Optionen";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib_force(datei, "Wert", i->active);
     datei << "/>\n";
   }
  for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     datei << "  <Hausregel";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib_force(datei, "Wert", i->active);
     datei << "/>\n";
   }
  for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(!i->active) continue;
     datei << "  <pdfViewer";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib(datei, "Wert", i->active);
     datei << "/>\n";
   }
  for(std::list<st_strings>::iterator i=list_Strings.begin();i!=list_Strings.end();++i)
   {
     if(i->name=="") continue;
     datei << "  <Einstellungen";
     write_string_attrib(datei, "Name" ,i->text);
     write_string_attrib(datei, "Wert", i->name);
     datei << "/>\n";
   }
 datei << "</MAGUS-optionen>\n";
}
                                                   
