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

void midgard_CG::menu_init()
{
  if (menu) {menu->destroy();menu=0;}
  menu=manage(new Gtk::Menu());

  Gtk::MenuItem *save = manage(new class Gtk::MenuItem("Charakter speichern"));
  menu->append(*save);
  save->activate.connect(SigC::slot(this,&midgard_CG::on_speichern_clicked));
  save->show();

  Gtk::MenuItem *close = manage(new class Gtk::MenuItem("MCG Beenden"));
  menu->append(*close);
  close->activate.connect(SigC::slot(this,&midgard_CG::on_schliessen_CG_clicked));
  close->show();

//Drucken ///////////////////////////////////////////////////////////////////
  Gtk::Menu *drucken_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *drucken = manage(new class Gtk::MenuItem("Drucken")); 
  drucken->set_submenu(*drucken_menu);

  Gtk::MenuItem *latex = manage(new class Gtk::MenuItem("Charakter drucken (LaTeX)"));
  drucken_menu->append(*latex);
  latex->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),true));
  latex->show();

  Gtk::MenuItem *latex_empty = manage(new class Gtk::MenuItem("Leeres Charakterdokument drucken"));
  drucken_menu->append(*latex_empty);
  latex_empty->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),false));
  latex_empty->show();

  menu->append(*drucken);
  drucken->show();

//Regionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *regionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *regionen = manage(new class Gtk::MenuItem("Regionen")); 
  regionen->set_submenu(*regionen_menu);

  
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     Gtk::CheckMenuItem *_mi=manage(new Gtk::CheckMenuItem((*i)->Name()));         
     _mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),_mi,*i));
     Gtk::HBox *_hb=manage(new class Gtk::HBox(false,0));

//     _hb->pack_start(*RegionenPic::Pic((*i)->Pic()));
     _hb->pack_start(*_mi);
     regionen_menu->append(*_mi);
     _mi->set_active((*i)->Active());
     if(!OptionBool.Original && ((*i)->Abkuerzung()=="H&D" ||(*i)->Abkuerzung()=="G"))
        _mi->set_sensitive(false);
     _mi->show();
     _hb->show();
   }
  menu->append(*regionen);
  regionen->show();


//Optionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *optionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *optionen = manage(new class Gtk::MenuItem("Optionen")); 
  optionen->set_submenu(*optionen_menu);
 
  OptionMenu.menu_original=manage(new Gtk::CheckMenuItem("Originalregeln"));
  optionen_menu->append(*OptionMenu.menu_original);
  OptionMenu.menu_original->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_original_menu));
  OptionMenu.menu_original->set_active(OptionBool.Original);
  OptionMenu.menu_original->show();

  OptionMenu.menu_info=manage(new Gtk::CheckMenuItem("Info Fenster anzeigen"));
  optionen_menu->append(*OptionMenu.menu_info);
  OptionMenu.menu_info->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_info_fenster_menu));
  OptionMenu.menu_info->set_active(OptionBool.Info);
  OptionMenu.menu_info->show();

  OptionMenu.menu_pics=manage(new Gtk::CheckMenuItem("Bilder anzeigen"));
  optionen_menu->append(*OptionMenu.menu_pics);
  OptionMenu.menu_pics->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_pics_menu));
  OptionMenu.menu_pics->set_active(OptionBool.Pics);
  OptionMenu.menu_pics->show();

  OptionMenu.menu_version=manage(new Gtk::CheckMenuItem("Versionen automatisch erzeugen\n(Deaktivierung löscht den Eintrag in 'Version')"));
  optionen_menu->append(*OptionMenu.menu_version);
  OptionMenu.menu_version->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_version_menu));
  OptionMenu.menu_version->set_active(OptionBool.version);
  OptionMenu.menu_version->show();

  menu->append(*optionen);
  optionen->show();

//Import/Export////////////////////////////////////////////////////////////////
  Gtk::Menu *im_ex_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *im_ex = manage(new class Gtk::MenuItem("Import/Export"));
  im_ex->set_submenu(*im_ex_menu);

  Gtk::MenuItem *xml_import = manage(new class Gtk::MenuItem("xml Import"));
  im_ex_menu->append(*xml_import);
  xml_import->activate.connect(SigC::slot(this,&midgard_CG::xml_import_auswahl));
  xml_import->show();

  Gtk::MenuItem *xml_export = manage(new class Gtk::MenuItem("xml Export"));
  im_ex_menu->append(*xml_export);
  xml_export->activate.connect(SigC::slot(this,&midgard_CG::xml_export_auswahl));
  xml_export->show();

  Gtk::MenuItem *Elsa_export = manage(new class Gtk::MenuItem("Export im Format für gedruckte Abenteuer"));
  im_ex_menu->append(*Elsa_export);
  Elsa_export->activate.connect(SigC::slot(this,&midgard_CG::spielleiter_export));
  Elsa_export->show();
  
  menu->append(*im_ex);
  im_ex->show();
///////////////////////////////////////////////////////////////////////////////

  menu->show();
}
