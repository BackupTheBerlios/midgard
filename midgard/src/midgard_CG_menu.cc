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

void midgard_CG::menu_init()
{
  if (menu) {menu->destroy();menu=0;}
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

  Gtk::MenuItem *latex_ausruestung = manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken"));
  drucken_menu->append(*latex_ausruestung);
  latex_ausruestung->activate.connect(SigC::slot(this,&midgard_CG::on_button_ausruestung_druck_clicked));

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
     _mi->remove();

     std::string labeltext=(*i)->Name();
     if (labeltext.size()>11)
     {  string::size_type pos=0;
        while ((pos=labeltext.find(' ',pos))!=string::npos)
        {  labeltext.replace(pos,1,'\n');
        }
     }
     Gtk::Label *_l=manage (new Gtk::Label(labeltext,0,0));
     Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
     Gtk::Pixmap *_o=manage(new Gtk::Pixmap(midgard_logo_tiny_xpm));
     int row=1;
     if((*i)->Offiziell()) 
       {
        _tab->attach(*_o,1,2,1,2,0,0,0,0);
        row=2;
       }
     _tab->attach(*_l,1,2,0,1,0,0,0,0);
     _tab->attach(*RegionenPic::Pic((*i)->Pic()),0,1,0,row,0,0,0,0);
     _tab->set_col_spacings(10);

     _mi->add(*_tab);
     regionen_menu->append(*_mi);
     _mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),_mi,*i));
     _mi->set_active((*i)->Active());
     if(!OptionBool.Original && (*i)->Offiziell() )
        _mi->set_sensitive(false);
   }
  menu->append(*regionen);


//Optionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *optionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *optionen = manage(new class Gtk::MenuItem("Optionen")); 
  optionen->set_submenu(*optionen_menu);
 
//  OptionMenu.menu_original=manage(new Gtk::CheckMenuItem("Originalregeln"));
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

  menu->append(*optionen);

//Import/Export////////////////////////////////////////////////////////////////
  Gtk::Menu *im_ex_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *im_ex = manage(new class Gtk::MenuItem("Import/Export"));
  im_ex->set_submenu(*im_ex_menu);

  Gtk::MenuItem *xml_import = manage(new class Gtk::MenuItem("xml Import"));
  im_ex_menu->append(*xml_import);
  xml_import->activate.connect(SigC::slot(this,&midgard_CG::xml_import_auswahl));

  Gtk::MenuItem *xml_export = manage(new class Gtk::MenuItem("xml Export"));
  im_ex_menu->append(*xml_export);
  xml_export->activate.connect(SigC::slot(this,&midgard_CG::xml_export_auswahl));

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

