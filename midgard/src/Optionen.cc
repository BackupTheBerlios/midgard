// $Id: Optionen.cc,v 1.1 2002/04/13 07:49:27 thoma Exp $
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
#include "MidgardBasicElement.hh" // nur für NotFound
#include <fstream>
#include "TagStream.hh"
#include "export_common.h"


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
       i->checkmenuitem->set_active(i->active);
       return; 
     }
 throw NotFound();
}
 
void Midgard_Optionen::setHausregeln(std::string hs,bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
    if(i->text==hs)  
      { i->active=b; 
        i->menu->set_active(i->active);
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
    






void Midgard_Optionen::Optionen_init()
{
  Gtk::CheckMenuItem *menu_original;
  list_Optionen.push_back(st_Optionen(Original,menu_original,
                           "Originalregeln",
                           true,midgard_logo_tiny_xpm));
  Gtk::CheckMenuItem *menu_nsc_only;
  list_Optionen.push_back(st_Optionen(NSC_only,menu_nsc_only,
                           "NSCs zulassen",
                           false,0));  
  Gtk::CheckMenuItem *menu_gw_wuerfeln;
  list_Optionen.push_back(st_Optionen(gw_wuerfeln,menu_gw_wuerfeln,
                           "Grundwerte nur mit einer Maustaste auswürfelbar machen",
                           false,Cyan_Dice_trans_50_xpm));
  Gtk::CheckMenuItem *menu_pics;
  list_Optionen.push_back(st_Optionen(showPics,menu_pics,
                           "Bilder anzeigen",true,0));
  Gtk::CheckMenuItem *menu_wizallways;
  list_Optionen.push_back(st_Optionen(Wizard_immer_starten,menu_wizallways, 
                           "Wizard bei jedem Programmstart zeigen",true,0));

  Gtk::MenuItem *menu_lernschema_sensitive;
  list_OptionenM.push_back(st_OptionenM(LernschemaSensitive,
                           menu_lernschema_sensitive,
                           "Lernschema/Steigern auswählbar machen",0));
  Gtk::MenuItem *menu_show_info_window;
  list_OptionenM.push_back(st_OptionenM(show_InfoWindow,
                           menu_show_info_window,
                           "Info Fenster zeigen",0));
  Gtk::MenuItem *menu_wizard_starten;
  list_OptionenM.push_back(st_OptionenM(WizardStarten,
                           menu_wizard_starten, 
                           "Wizard starten",0));
  Gtk::MenuItem *menu_lernschema_fertzusaetze_loeschen;
  list_OptionenM.push_back(st_OptionenM(LernschemaZusaetzeLoeschen,
                           menu_lernschema_fertzusaetze_loeschen,
                           "Fertigkeiten mit Zusätzen im Lernschema wieder anzeigen",0));
}




void Midgard_Optionen::pdfViewer_init()
{
  Gtk::RadioMenuItem *menu_xpdf;
  list_pdfViewer.push_back(st_pdfViewer(xpdf,menu_xpdf,
                           "pdf Dokument mit 'xpdf' betrachten",
                           false));
  Gtk::RadioMenuItem *menu_acroread;
  list_pdfViewer.push_back(st_pdfViewer(acroread,menu_acroread,
                           "pdf Dokument mit 'acroread' betrachten",
                           true));
  Gtk::RadioMenuItem *menu_gv;
  list_pdfViewer.push_back(st_pdfViewer(gv,menu_gv,
                           "pdf Dokument mit 'gv' betrachten",
                           false));
}

void Midgard_Optionen::Hausregeln_init()
{
 list_Hausregeln.clear();  
 Gtk::CheckMenuItem *gold; 
 list_Hausregeln.push_back(st_Haus(Gold,gold,"1 GS entspricht 1 GFP",false));
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
// muß von der Klasse midgard_CG aufgrerufen werden:
//  menu_init();
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
     write_string_attrib(datei, "pdfViewer" ,i->text);
     write_bool_attrib(datei, "Wert", i->active);
     datei << "/>\n";
   }
 datei << "</MAGUS-optionen>\n";
}
                                                   
