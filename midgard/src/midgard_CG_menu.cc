/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
#include <gtk--/box.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/midgard_logo_tiny.xpm"
#include "../pixmaps/Regio_Hausregel_small.xpm"

void midgard_CG::menu_init()
{
  if (menu) { menu->destroy(); menu=0; haus_menuitem=0; }
  menu=manage(new Gtk::Menu());

  Gtk::MenuItem *save = manage(new class Gtk::MenuItem("Charakter speichern"));
  menu->append(*save);
#ifndef USE_XML
  save->activate.connect(SigC::slot(this,&midgard_CG::on_speichern_clicked));
#else
  save->activate.connect(SigC::slot(this,&midgard_CG::xml_export_auswahl));
#endif

  Gtk::MenuItem *close = manage(new class Gtk::MenuItem("MCG Beenden"));
  menu->append(*close);
  close->activate.connect(SigC::slot(this,&midgard_CG::on_schliessen_CG_clicked));

//Drucken ///////////////////////////////////////////////////////////////////
  Gtk::Menu *drucken_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *drucken = manage(new class Gtk::MenuItem("Drucken")); 
  drucken->set_submenu(*drucken_menu);

  Gtk::MenuItem *latex = manage(new class Gtk::MenuItem("Charakter drucken (LaTeX)"));
  drucken_menu->append(*latex);
  latex->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),true));

  Gtk::MenuItem *latex_beschreibung = manage(new class Gtk::MenuItem("Charakterbeschreibung drucken"));
  drucken_menu->append(*latex_beschreibung);
  latex_beschreibung->activate.connect(SigC::slot(this,&midgard_CG::latex_beschreibung_drucken));

  Gtk::MenuItem *latex_ausruestung = manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Alles)"));
  drucken_menu->append(*latex_ausruestung);
  latex_ausruestung->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_ausruestung_druck),true));
  Gtk::MenuItem *latex_ausruestung2 = manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Nur sichtbare Gegenstände)"));
  drucken_menu->append(*latex_ausruestung2);
  latex_ausruestung2->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_ausruestung_druck),false));

  Gtk::MenuItem *latex_empty = manage(new class Gtk::MenuItem("Leeres Charakterdokument drucken"));
  drucken_menu->append(*latex_empty);
  latex_empty->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),false));

  menu->append(*drucken);

//Regionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *regionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *regionen = manage(new class Gtk::MenuItem("Regionen")); 
  regionen->set_submenu(*regionen_menu);

  
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     Gtk::CheckMenuItem *_mi=manage(new Gtk::CheckMenuItem());         

     std::string labeltext=(*i)->Name();
     if (labeltext.size()>11)
     {  string::size_type pos=0;
        while ((pos=labeltext.find(' ',pos))!=string::npos)
        {  labeltext.replace(pos,1,'\n');
        }
     }
     Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
     int row=1;
     if((*i)->Offiziell()) 
       {
        Gtk::Pixmap *_o=manage(new Gtk::Pixmap(midgard_logo_tiny_xpm));
        _tab->attach(*_o,1,2,1,2,0,0,0,0);
        row=2;
       }
     Gtk::Label *_l=manage (new Gtk::Label(labeltext,0,0));
     _tab->attach(*_l,1,2,0,1,0,0,0,0);
     _tab->attach(*RegionenPic::Pic((*i)->Pic()),0,1,0,row,0,0,0,0);
     _tab->set_col_spacings(10);

     _mi->add(*_tab);
     regionen_menu->append(*_mi);
     _mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),_mi,*i));
     _mi->set_active((*i)->Active());
//     if(!OptionBool.Original && (*i)->Offiziell() )
     if(!OptionenCheck(Original).active && (*i)->Offiziell() )
        _mi->set_sensitive(false);
   }
  menu->append(*regionen);


//Optionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *optionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *optionen = manage(new class Gtk::MenuItem("Optionen")); 
  optionen->set_submenu(*optionen_menu);

  for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   {
    Gtk::Label *_l=manage (new Gtk::Label(i->text));
    Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
    _tab->attach(*_l,0,1,0,1,GTK_FILL,0,0,0);
    if(i->bild) 
     {
      Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
      _tab->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
     }
    i->menuitem=manage(new Gtk::CheckMenuItem());
    i->menuitem->add(*_tab);    
    i->menuitem->activate.connect(SigC::bind(SigC::slot(this,i->funktion),*i));
    i->menuitem->set_active(i->active);
    optionen_menu->append(*(i->menuitem));
   } 
/*
  OptionMenu.menu_original=manage(new Gtk::CheckMenuItem());
  Gtk::Label *_l=manage (new Gtk::Label("Originalregeln"));
  Gtk::Pixmap *_o=manage(new Gtk::Pixmap(midgard_logo_tiny_xpm));
  Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
  _tab->attach(*_l,0,1,0,1,GTK_FILL,0,0,0);
  _tab->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
  OptionMenu.menu_original->add(*_tab);

  optionen_menu->append(*OptionMenu.menu_original);
  OptionMenu.menu_original->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_original_menu));
  OptionMenu.menu_original->set_active(OptionBool.Original);

  OptionMenu.menu_info=manage(new Gtk::CheckMenuItem("Info Fenster anzeigen"));
  optionen_menu->append(*OptionMenu.menu_info);
  OptionMenu.menu_info->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_info_fenster_menu));
  OptionMenu.menu_info->set_active(OptionBool.Info);

  OptionMenu.menu_pics=manage(new Gtk::CheckMenuItem("Bilder anzeigen"));
  optionen_menu->append(*OptionMenu.menu_pics);
  OptionMenu.menu_pics->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_pics_menu));
  OptionMenu.menu_pics->set_active(OptionBool.Pics);

  OptionMenu.menu_sensitive=manage(new Gtk::MenuItem("Lernschema auswählbar machen"));
  optionen_menu->append(*OptionMenu.menu_sensitive);
  OptionMenu.menu_sensitive->activate.connect(SigC::slot(this,&midgard_CG::on_lernschema_sensitive_menu));

  OptionMenu.menu_version=manage(new Gtk::CheckMenuItem("Versionen automatisch erzeugen\n(Deaktivierung löscht den Eintrag in 'Version')"));
  optionen_menu->append(*OptionMenu.menu_version);
  OptionMenu.menu_version->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_version_menu));
  OptionMenu.menu_version->set_active(OptionBool.version);
*/
  menu->append(*optionen);

//Hausregeln////////////////////////////////////////////////////////////////
  Gtk::Menu *haus_menu = manage(new class Gtk::Menu());
//  if(haus_menuitem) {haus_menuitem->destroy();haus_menuitem=0;}
// heh, das ist managed!!! das gibt es schon gar nicht mehr!
  haus_menuitem = manage(new class Gtk::MenuItem());

  Gtk::Label *_lhaus = manage(new class Gtk::Label("Hausregeln"));
  Gtk::Table *_tabhaus=manage(new Gtk::Table(0,0,false));
  _tabhaus->attach(*_lhaus,0,1,0,1,0,0,0,0);
  Gtk::Pixmap *pix_haus=manage(new Gtk::Pixmap(Regio_Hausregel_small_xpm));
  _tabhaus->attach(*pix_haus,1,2,0,1,0,0,0,0);

  haus_menuitem->set_submenu(*haus_menu);

  for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     i->menu = manage(new class Gtk::CheckMenuItem(i->text));
     haus_menu->append(*(i->menu));
     i->menu->set_active(i->active);
     i->menu->activate.connect(SigC::slot(this,&midgard_CG::Hausregeln_setzen_from_menu));
   }  

  haus_menuitem->add(*_tabhaus);
  menu->append(*haus_menuitem);
  if(OptionenCheck(Original).active) haus_menuitem->set_sensitive(false);
///////////////////////////////////////////////////////////////////////////////
//Import/Export////////////////////////////////////////////////////////////////
  Gtk::Menu *im_ex_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *im_ex = manage(new class Gtk::MenuItem("Import/Export"));
  im_ex->set_submenu(*im_ex_menu);
/*
  Gtk::MenuItem *xml_import = manage(new class Gtk::MenuItem("xml Import"));
  im_ex_menu->append(*xml_import);
  xml_import->activate.connect(SigC::slot(this,&midgard_CG::xml_import_auswahl));

  Gtk::MenuItem *xml_export = manage(new class Gtk::MenuItem("xml Export"));
  im_ex_menu->append(*xml_export);
  xml_export->activate.connect(SigC::slot(this,&midgard_CG::xml_export_auswahl));
*/
  Gtk::MenuItem *Elsa_export = manage(new class Gtk::MenuItem("Export im Format für gedruckte Abenteuer"));
  im_ex_menu->append(*Elsa_export);
  Elsa_export->activate.connect(SigC::slot(this,&midgard_CG::spielleiter_export));
  Elsa_export->show();
  
  menu->append(*im_ex);
///////////////////////////////////////////////////////////////////////////////

  menu->show_all();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
#include "../pixmaps/Anpass-trans-50.xpm"
#include "../pixmaps/Dice-2W6-trans-50.xpm"
#include "../pixmaps/Armor-trans-50.xpm"
#include "../pixmaps/wizzard-trans-50.xpm"
#include "../pixmaps/Resistenz-trans-32.xpm"
#include "../pixmaps/Red-Dice-trans-50.xpm"

/* so ginge das ...
struct midgard_CG::st_gradanstieg{const std::string label; const char** pix; void (midgard_CG::*f)();
      const std::string l; const char** p; void (midgard_CG::*funk)();
      : label(l),pix(p),funk(f) {} };
*/

struct SteigernMenueEintrag
{    std::string text;
     const char * const *bild;
     void (midgard_CG::* funktion)();

     SteigernMenueEintrag(const std::string &t, const char * const * const b,
     		void (midgard_CG::* const f)())
     	: text(t), bild(b), funktion(f) {}
};

void midgard_CG::menu_gradanstieg_init()
{
  if (menu_gradanstieg) {menu_gradanstieg->destroy();menu_gradanstieg=0;}
  menu_gradanstieg=manage(new Gtk::Menu());

  std::vector<SteigernMenueEintrag> labelpic;
  labelpic.push_back(SteigernMenueEintrag("Grad anpassen",Anpass_trans_50_xpm,
  		&midgard_CG::on_button_grad_clicked));
  labelpic.push_back(SteigernMenueEintrag("Ausdauer würfeln",Dice_2W6_trans_50_xpm,
  		&midgard_CG::on_button_grad_ausdauer_clicked));
  labelpic.push_back(SteigernMenueEintrag("Abwehr",Armor_trans_50_xpm,
  		&midgard_CG::on_button_grad_abwehr_clicked));
  labelpic.push_back(SteigernMenueEintrag("Zaubern",wizzard_trans_50_xpm,
  		&midgard_CG::on_button_grad_zaubern_clicked));
  labelpic.push_back(SteigernMenueEintrag("Resistenz",Resistenz_trans_32_xpm,
  		&midgard_CG::on_button_grad_resistenz_clicked));
  labelpic.push_back(SteigernMenueEintrag("Basiswerte",Red_Dice_trans_50_xpm,
  		&midgard_CG::on_button_grad_basiswerte_clicked));

  for(std::vector<SteigernMenueEintrag>::const_iterator i=labelpic.begin();i!=labelpic.end();++i)
   {
     Gtk::MenuItem *mi=manage(new Gtk::MenuItem());
     Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
     Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
     _tab->attach(*_o,0,1,0,1,0,0,0,0);
     Gtk::Label *_l=manage (new Gtk::Label(i->text,0,0));
     _tab->attach(*_l,1,2,0,1,0,0,0,0);
     _tab->set_col_spacings(10);
     mi->add(*_tab);
     mi->activate.connect(SigC::slot(this,i->funktion));
     menu_gradanstieg->append(*mi);
   }
  menu_gradanstieg->show_all();
}


//#include "../pixmaps/midgard_logo_tiny.xpm"

void midgard_CG::Optionen_init()
{
  Gtk::CheckMenuItem *menu_original;
  list_Optionen.push_back(st_Optionen(Original,menu_original,
                           "Originalregeln",
                           true,midgard_logo_tiny_xpm,
                           &midgard_CG::on_checkbutton_optionen_menu));
  Gtk::CheckMenuItem *menu_info;
  list_Optionen.push_back(st_Optionen(Info,menu_info,
                           "Info Fenster anzeigen",true,0,
                           &midgard_CG::on_checkbutton_optionen_menu));
  Gtk::CheckMenuItem *menu_pics;
  list_Optionen.push_back(st_Optionen(showPics,menu_pics,
                           "Bilder anzeigen",true,0,
                           &midgard_CG::on_checkbutton_optionen_menu));
  Gtk::CheckMenuItem *menu_lernschema_sensitive;
  list_Optionen.push_back(st_Optionen(LernschemaSensitive,
                           menu_lernschema_sensitive,
                           "Lernschema auswählbar machen",true,0,
                           &midgard_CG::on_checkbutton_optionen_menu));
}


void midgard_CG::Hausregeln_init()
{
 list_Hausregeln.clear();
 Gtk::CheckMenuItem *gold; 
// list_Hausregeln.push_back(st_Haus(Gold,Gtk::CheckMenuItem *gold,"1 GS entspricht 1 GFP"));
 list_Hausregeln.push_back(st_Haus(Gold,gold,"1 GS entspricht 1 GFP",false));
// Gtk::CheckMenuItem *ep_steigern; 
// list_Hausregeln.push_back(st_Haus(EPsteigern,ep_steigern,"Steigern mit Erfahrungspunkten",true));
}

