// $Id: Optionen.cc,v 1.3 2002/04/14 15:32:14 thoma Exp $
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
//#include "MidgardBasicElement.hh" // nur f�r NotFound
#include <fstream>
#include "TagStream.hh"
#include "export_common.h"
#include "midgard_CG.hh"

Midgard_Optionen::Midgard_Optionen(midgard_CG* h)
:hauptfenster(h)
{
   Optionen_init();
   Hausregeln_init();
   pdfViewer_init();
}

std::string Midgard_Optionen::Viewer()
{
  if     (pdfViewerCheck(Midgard_Optionen::gv).active)       return "gv ";
  else if(pdfViewerCheck(Midgard_Optionen::xpdf).active)     return "xpdf ";
  else if(pdfViewerCheck(Midgard_Optionen::acroread).active) return "acroread  ";
  else if(pdfViewerCheck(Midgard_Optionen::anderer).active)  return viewer+" ";
  else assert(!"");
  abort();
}


Midgard_Optionen::st_Optionen Midgard_Optionen::OptionenCheck(OptionenIndex oi)
{
 for(std::list<st_Optionen>::const_iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
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
Midgard_Optionen::st_pdfViewer Midgard_Optionen::pdfViewerCheck(pdfViewerIndex pi)
{
 for(std::list<st_pdfViewer>::const_iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   if(i->index==pi) return *i;
 assert(!"pdfViewer: nicht gefunden");
 abort();
}
 
void Midgard_Optionen::setOption(std::string os,bool b)
{
 for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   if(i->text==os) 
     { i->active=b;
       return; 
     }
 throw NotFound();
}
 
void Midgard_Optionen::setHausregeln(std::string hs,bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
    if(i->text==hs)  
      { i->active=b; 
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
cout << i->text<<' '<<is<<' '<<(i->text==is)<<' '<<i->active<<'\n';
     if(i->text==is) i->active=b;
     else i->active=!b;
cout <<'\t'<< i->text<<' '<<(i->text==is)<<' '<<i->active<<'\n';
   }
}   
    

void Midgard_Optionen::Optionen_setzen_from_menu(OptionenIndex index)
{
//  if(!hauptfenster->fire_enabled) return;
//  hauptfenster->fire_enabled=false;
/*
  for(list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   {
     if(i->index!=index) continue;
     i->active = i->checkmenuitem->get_active();
     if(i->index==Original) { hauptfenster->checkbutton_original(i->active); hauptfenster->menu_init();}
     if(i->index==showPics) hauptfenster->Pics(i->active);
     if(i->index==gw_wuerfeln) hauptfenster->show_gw_wuerfeln(i->active);
     if(i->index==NSC_only) hauptfenster->on_radiobutton_mann_toggled(); // zum Neuaufbau des Typmen�s
   }
//  hauptfenster->fire_enabled=true;
*/
}
 
void Midgard_Optionen::OptionenM_setzen_from_menu(OptionenIndex index)
{
  if(index==LernschemaSensitive) hauptfenster->lernschema_sensitive(true);
  if(index==WizardStarten) hauptfenster->wizard_starten_clicked();
  if(index==LernschemaZusaetzeLoeschen) {hauptfenster->list_FertigkeitZusaetze.clear();
                                         hauptfenster->on_lernliste_wahl_toggled();}   
  if(index==show_InfoWindow) hauptfenster->InfoFenster->show();
}

void Midgard_Optionen::Hausregeln_setzen_from_menu(HausIndex index)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     if(i->index==index) 
      { i->active = true;
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
  list_Optionen.push_back(st_Optionen(Original,"Originalregeln",
                           true,midgard_logo_tiny_xpm));
  list_Optionen.push_back(st_Optionen(NSC_only,"NSCs zulassen",
                           false,0));  
  list_Optionen.push_back(st_Optionen(gw_wuerfeln,
                           "Grundwerte nur mit einer Maustaste ausw�rfelbar machen",
                           false,Cyan_Dice_trans_50_xpm));
  list_Optionen.push_back(st_Optionen(showPics,"Bilder anzeigen",true,0));
  list_Optionen.push_back(st_Optionen(Wizard_immer_starten, 
                           "Wizard bei jedem Programmstart zeigen",true,0));

  list_OptionenM.push_back(st_OptionenM(LernschemaSensitive,
                           "Lernschema/Steigern ausw�hlbar machen",0));
  list_OptionenM.push_back(st_OptionenM(show_InfoWindow,"Info Fenster zeigen",0));
  list_OptionenM.push_back(st_OptionenM(WizardStarten,"Wizard starten",0));
  list_OptionenM.push_back(st_OptionenM(LernschemaZusaetzeLoeschen,
                           "Fertigkeiten mit Zus�tzen im Lernschema wieder anzeigen",0));
}




void Midgard_Optionen::pdfViewer_init()
{
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
}

void Midgard_Optionen::Hausregeln_init()
{
 list_Hausregeln.clear();  
 list_Hausregeln.push_back(st_Haus(Gold,"1 GS entspricht 1 GFP",false));
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
     setOption(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*data,"Hausregel")
     setHausregeln(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*data,"pdfViewer")
     setpdfViewer(i->getAttr("Name"),i->getBoolAttr("Wert"));
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
 for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   {
     datei << "  <Optionen";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib_force(datei, "Wert", i->active);
     datei << "/>\n";
   }
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     datei << "  <Hausregel";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib_force(datei, "Wert", i->active);
     datei << "/>\n";
   }
  for(list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(!i->active) continue;
     datei << "  <pdfViewer";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib(datei, "Wert", i->active);
     datei << "/>\n";
   }
 datei << "</MAGUS-optionen>\n";
}
                                                   
