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
//#include <gtk--/radiomenuitem.h>
#include "../pixmaps/midgard_logo_tiny.xpm"
#include "../pixmaps/Regio_Hausregel_small.xpm"

void midgard_CG::menu_init()
{
  bool memfire=fire_enabled;
  fire_enabled=false;
  if (menu) { menu->destroy(); menu=0; MOptionen->haus_menuitem=0; }
  menu=manage(new Gtk::Menu());

  Gtk::MenuItem *save = manage(new class Gtk::MenuItem("Abenteurer speichern"));
  menu->append(*save);
  save->activate.connect(SigC::slot(this,&midgard_CG::xml_export_auswahl));

  Gtk::MenuItem *close = manage(new class Gtk::MenuItem("MAGUS Beenden"));
  menu->append(*close);
  close->activate.connect(SigC::slot(this,&midgard_CG::on_schliessen_CG_clicked));

//Drucken ///////////////////////////////////////////////////////////////////
  Gtk::Menu *drucken_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *drucken = manage(new class Gtk::MenuItem("Drucken")); 
  drucken->set_submenu(*drucken_menu);

  Gtk::MenuItem *latex = manage(new class Gtk::MenuItem("Abenteurer drucken (LaTeX)"));
  drucken_menu->append(*latex);
  latex->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),true));

  Gtk::MenuItem *latex_beschreibung = manage(new class Gtk::MenuItem("Abenteurerbeschreibung drucken"));
  drucken_menu->append(*latex_beschreibung);
  latex_beschreibung->activate.connect(SigC::slot(this,&midgard_CG::latex_beschreibung_drucken));

  Gtk::MenuItem *latex_ausruestung = manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Alles)"));
  drucken_menu->append(*latex_ausruestung);
  latex_ausruestung->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_ausruestung_druck),true));
  Gtk::MenuItem *latex_ausruestung2 = manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Nur sichtbare Gegenstände)"));
  drucken_menu->append(*latex_ausruestung2);
  latex_ausruestung2->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_ausruestung_druck),false));

  Gtk::MenuItem *latex_empty = manage(new class Gtk::MenuItem("Leeres Abenteurerdokument drucken"));
  drucken_menu->append(*latex_empty);
  latex_empty->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),false));

  Gtk::RadioMenuItem::Group _RadioMGroup_pdfViewer;
  std::list<Midgard_Optionen::st_pdfViewer> LP=MOptionen->getPDF();
  for(std::list<Midgard_Optionen::st_pdfViewer>::iterator i=LP.begin();i!=LP.end();++i)
   {
     Gtk::Label *_l=manage (new Gtk::Label(i->text));
     Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
     _tab->attach(*_l,0,1,0,1,GTK_FILL,0,0,0);
     // hier könnte noch ein Icon dazukommen
     if(!i->radio_menu_item) continue;
     i->radio_menu_item = manage(new class Gtk::RadioMenuItem(_RadioMGroup_pdfViewer));
     i->radio_menu_item->add(*_tab);
     MOptionen->pdfViewer_setzen_from_menu(i->index);
     i->radio_menu_item->activate.connect(SigC::bind(SigC::slot(this,&Midgard_Optionen::pdfViewer_setzen_from_menu),i->index));
     drucken_menu->append(*(i->radio_menu_item));
   }
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
     _mi->set_active((*i)->Active());
     _mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),_mi,*i));
     if(MOptionen->OptionenCheck(Midgard_Optionen::Original).active && 
         !(*i)->Offiziell() )
        _mi->set_sensitive(false);
   }
  menu->append(*regionen);


//Optionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *optionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *optionen = manage(new class Gtk::MenuItem("Optionen")); 
  optionen->set_submenu(*optionen_menu);

  std::list<Midgard_Optionen::st_Optionen> OL=MOptionen->getOptionen();
  for(std::list<Midgard_Optionen::st_Optionen>::iterator i=OL.begin();i!=OL.end();++i)
   {
    Gtk::Label *_l=manage (new Gtk::Label(i->text));
    Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
    _tab->attach(*_l,0,1,0,1,GTK_FILL,0,0,0);
    if(i->bild) 
     {
      Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
      _tab->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
     }
    i->checkmenuitem=manage(new Gtk::CheckMenuItem());
    i->checkmenuitem->add(*_tab);    
    i->checkmenuitem->set_active(i->active);
    MOptionen->Optionen_setzen_from_menu(i->index);
    i->checkmenuitem->activate.connect(SigC::bind(SigC::slot(this,&Midgard_Optionen::Optionen_setzen_from_menu),i->index));
    optionen_menu->append(*(i->checkmenuitem));
   } 
  std::list<Midgard_Optionen::st_OptionenM> OLM=MOptionen->getOptionenM();
  for(std::list<Midgard_Optionen::st_OptionenM>::iterator i=OLM.begin();i!=OLM.end();++i)
   {
    Gtk::Label *_l=manage (new Gtk::Label(i->text));
    Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
    _tab->attach(*_l,0,1,0,1,GTK_FILL,0,0,0);
    if(i->bild) 
     {
      Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
      _tab->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
     }
    if(i->menuitem)
     {
       i->menuitem=manage(new Gtk::MenuItem());
       i->menuitem->add(*_tab);    
       i->menuitem->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::OptionenM_setzen_from_menu),i->index));
       optionen_menu->append(*(i->menuitem));
     }
   } 

  menu->append(*optionen);

//Hausregeln////////////////////////////////////////////////////////////////
  Gtk::Menu *haus_menu = manage(new class Gtk::Menu());
  haus_menuitem = manage(new class Gtk::MenuItem());

  Gtk::Label *_lhaus = manage(new class Gtk::Label("Hausregeln"));
  Gtk::Table *_tabhaus=manage(new Gtk::Table(0,0,false));
  _tabhaus->attach(*_lhaus,0,1,0,1,0,0,0,0);
  Gtk::Pixmap *pix_haus=manage(new Gtk::Pixmap(Regio_Hausregel_small_xpm));
  _tabhaus->attach(*pix_haus,1,2,0,1,0,0,0,0);

  haus_menuitem->set_submenu(*haus_menu);

  std::list<Midgard_Optionen::st_Haus> LH=MOptionen->getHausregeln();
  for(std::list<Midgard_Optionen::st_Haus>::iterator i=LH.begin();i!=LH.end();++i)
   {
     i->menu = manage(new class Gtk::CheckMenuItem(i->text));
     haus_menu->append(*(i->menu));
     i->menu->set_active(i->active);
     Hausregeln_setzen_from_menu(i->index);
     i->menu->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::Hausregeln_setzen_from_menu),i->index));
   }  

  haus_menuitem->add(*_tabhaus);
  menu->append(*haus_menuitem);
  if(OptionenCheck(Original).active) haus_menuitem->set_sensitive(false);
///////////////////////////////////////////////////////////////////////////////
//Import/Export////////////////////////////////////////////////////////////////
  Gtk::Menu *im_ex_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *im_ex = manage(new class Gtk::MenuItem("Import/Export"));
  im_ex->set_submenu(*im_ex_menu);

  Gtk::MenuItem *Elsa_export = manage(new class Gtk::MenuItem("Export im Format für gedruckte Abenteuer"));
  im_ex_menu->append(*Elsa_export);
  Elsa_export->activate.connect(SigC::slot(this,&midgard_CG::spielleiter_export));
  Elsa_export->show();
  
  menu->append(*im_ex);
///////////////////////////////////////////////////////////////////////////////

  menu->show_all();
  fire_enabled=memfire;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
#include "../pixmaps/Anpass-trans-50.xpm"
#include "../pixmaps/Dice-2W6-trans-50.xpm"
#include "../pixmaps/Armor-trans-50.xpm"
#include "../pixmaps/wizzard-trans-50.xpm"
#include "../pixmaps/Resistenz-trans-32.xpm"
#include "../pixmaps/Red-Dice-trans-50.xpm"

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
     if(i->text=="Zaubern"  && (!Typ[0]->is_mage() && !Typ[1]->is_mage() ))
      {
        mi->set_sensitive(false);
      }
   }
  menu_gradanstieg->show_all();
}

/*
//#include "../pixmaps/midgard_logo_tiny.xpm"
#include "../pixmaps/Cyan-Dice-trans-50.xpm"

void midgard_CG::Optionen_init()
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


void midgard_CG::Hausregeln_init()
{
 list_Hausregeln.clear();
 Gtk::CheckMenuItem *gold; 
 list_Hausregeln.push_back(st_Haus(Gold,gold,"1 GS entspricht 1 GFP",false));
}

void midgard_CG::pdfViewer_init()
{
  Gtk::RadioMenuItem *menu_xpdf;
  list_pdfViewer.push_back(Midgard_Optionen::st_pdfViewer(xpdf,menu_xpdf,
                           "pdf Dokument mit 'xpdf' betrachten",
                           false));
  Gtk::RadioMenuItem *menu_acroread;
  list_pdfViewer.push_back(Midgard_Optionen::st_pdfViewer(acroread,menu_acroread,
                           "pdf Dokument mit 'acroread' betrachten",
                           true));
  Gtk::RadioMenuItem *menu_gv;
  list_pdfViewer.push_back(Midgard_Optionen::st_pdfViewer(gv,menu_gv,
                           "pdf Dokument mit 'gv' betrachten",
                           false));
}
*/