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
#include <Misc/itos.h>
#include <MVC_boolMenu_Widget.hh>
#include "../pixmaps/NSC-Mode-26.xpm"

Gtk::Box &midgard_CG::make_gtk_box(const gchar * const *data,const std::string &label,const bool text_vor_bild,const bool hbox)
{
  Gtk::Pixmap *_p=manage(new Gtk::Pixmap(data));
  Gtk::Label *_l=manage(new Gtk::Label(label));
  Gtk::Box *_v;
  if(hbox) _v=manage(new Gtk::HBox());
  else     _v=manage(new Gtk::VBox());
  if(text_vor_bild)  { _v->pack_start(*_l,false,false);
                       _v->pack_start(*_p,false,false); }
  else               { _v->pack_start(*_p,false,false);
                       _v->pack_start(*_l,false,false); }
  return *_v;
}
 

void midgard_CG::menu_init()
{
  menu_kontext=manage(new Gtk::Menu());

//Schummel-Menü/////////////////////////////////////////////////////////////////////
  Gtk::Menu *schummel_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *schummel = manage(new class Gtk::MenuItem("Original-Regel-Menü")); 
  schummel->set_submenu(*schummel_menu);

  {MVC_boolMenu_Widget *_M=manage(new MVC_boolMenu_Widget(schummeln,make_gtk_box(NSC_Mode_26_xpm,"alle Regeln abschalten")));
  schummel_menu->append(*_M);
  _M->activate.connect_after(SigC::slot(this,&midgard_CG::Schummeln));}

  {MVC_boolMenu_Widget *_M=manage(new MVC_boolMenu_Widget(MOptionen->OptionenCheck(Midgard_Optionen::Original).active,make_gtk_box(midgard_logo_tiny_xpm,"Originalregeln ")));
  schummel_menu->append(*_M);}

  {Gtk::MenuItem *_M = manage(new Gtk::MenuItem("Lernschema- und Steigern-Fenster aktivieren"));
  schummel_menu->append(*_M);
  _M->activate.connect_after(SigC::bind(SigC::slot(this,&midgard_CG::OptionenExecute_setzen_from_menu),Midgard_Optionen::LernschemaSensitive));}

  {MVC_boolMenu_Widget *_M=manage(new MVC_boolMenu_Widget(table_grundwerte->edit_werte,"Werte editieren"));
  schummel_menu->append(*_M);}

  {MVC_boolMenu_Widget *_M=manage(new MVC_boolMenu_Widget(table_steigern->steigern_mit_EP_bool,"Mit EP/PP steigern"));
  schummel_menu->append(*_M);}

  {MVC_boolMenu_Widget *_M=manage(new MVC_boolMenu_Widget(MOptionen->OptionenCheck(Midgard_Optionen::NSC_only).active,"NSC-Modus"));
  schummel_menu->append(*_M);}

  menu_kontext->append(*schummel);

//Drucken ///////////////////////////////////////////////////////////////////
  Gtk::Menu *drucken_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *drucken = manage(new class Gtk::MenuItem("Drucken")); 
  drucken->set_submenu(*drucken_menu);

  Gtk::MenuItem *latex = manage(new class Gtk::MenuItem("Abenteurer drucken (LaTeX)"));
  drucken_menu->append(*latex);
  latex->activate.connect(SigC::slot(this,&midgard_CG::on_abenteurerdokument_drucken));

  Gtk::MenuItem *latex_beschreibung = manage(new class Gtk::MenuItem("Abenteurerbeschreibung drucken"));
  drucken_menu->append(*latex_beschreibung);
  latex_beschreibung->activate.connect(SigC::slot(this,&midgard_CG::on_beschreibung_drucken));

  Gtk::MenuItem *latex_ausruestung = manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Alles)"));
  drucken_menu->append(*latex_ausruestung);
  latex_ausruestung->activate.connect(SigC::slot(this,&midgard_CG::on_auch_unsichtbares_drucken));
  Gtk::MenuItem *latex_ausruestung2 = manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Nur sichtbare Gegenstände)"));
  drucken_menu->append(*latex_ausruestung2);
  latex_ausruestung2->activate.connect(SigC::slot(this,&midgard_CG::on_nur_sichtbares_drucken));

  Gtk::MenuItem *latex_empty = manage(new class Gtk::MenuItem("Leeres Abenteurerdokument drucken"));
  drucken_menu->append(*latex_empty);
  latex_empty->activate.connect(SigC::slot(this,&midgard_CG::on_leeres_abenteurerdokument_drucken));

  menu_kontext->append(*drucken);
//Regionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *regionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *regionen = manage(new class Gtk::MenuItem("Regionen")); 
  regionen->set_submenu(*regionen_menu);
  Midgard_Optionen::IconIndex II=MOptionen->getIconIndex();

  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     std::string labeltext=(*i)->Name();
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
     _tab->attach(*RegionenPic::Pic((*i)->Pic(),II),0,1,0,row,0,0,0,0);
     _tab->set_col_spacings(10);

     MVC_boolMenu_Widget *mi = manage(new MVC_boolMenu_Widget((*i)->Active(),*_tab));
     regionen_menu->append(*mi);
     (*i)->Active().changed.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),*i));
     if(!(*i)->Offiziell())
         mi->setSensitive(MOptionen->OptionenCheck(Midgard_Optionen::Original).active,true);
   }
  menu_kontext->append(*regionen);
  

//Optionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *optionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *optionen = manage(new class Gtk::MenuItem("Ansicht & Fenster")); 
  optionen->set_submenu(*optionen_menu);

  std::list<Midgard_Optionen::st_OptionenExecute> OLM=MOptionen->getOptionenExecute();
  for(std::list<Midgard_Optionen::st_OptionenExecute>::iterator i=OLM.begin();i!=OLM.end();++i)
   {
    Gtk::Label *_l=manage (new Gtk::Label(i->text));
    Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
    _tab->attach(*_l,0,1,0,1,GTK_FILL,0,0,0);
    if(i->bild) 
     {
      Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
      _tab->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
     }
    Gtk::MenuItem *mi=manage(new Gtk::MenuItem());
    mi->add(*_tab);    
    mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::OptionenExecute_setzen_from_menu),i->index));
    optionen_menu->append(*mi);
   } 
  menu_kontext->append(*optionen);
///////////////////////////////////////////////////////////////////////////////
  menu_kontext->show_all();

///////////
}


/*
static void wert_changed(gpointer gp)
{ 
  std::cout << "MENÜ: WC: "<<  *(bool*)(gp)<<'\n';
} 
*/ 

void midgard_CG::menubar_init()
{

//  const Gtk::MenuShell::MenuList *Gtk_ML;
//  main_menubar->items().back();
//  main_menubar->items().pop_back();
//  main_menubar->items().push_back(Gtk_ML);

  // Ansicht
  Gtk::Menu *ansicht_menu = manage(new class Gtk::Menu());
//  main_menubar->items().push_back(Gtk::Menu_Helpers::MenuElem("Ansicht & _Fenster","<Control>F", *ansicht_menu));
  main_menubar->items().insert(--main_menubar->items().end(),Gtk::Menu_Helpers::MenuElem("Ansicht & _Fenster","<Control>F", *ansicht_menu));

  Gtk::Menu *menu1 = manage(new class Gtk::Menu());
  Gtk::Menu *menu2 = manage(new class Gtk::Menu());

  Gtk::MenuItem *mi0 = manage(new class Gtk::MenuItem("Optionen"));
  mi0->activate.connect(SigC::slot(this,&midgard_CG::menu_einstellungen_aendern));
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi0));

  Gtk::MenuItem *mi1 = manage(new class Gtk::MenuItem("Ansicht & Fenster"));
  Gtk::MenuItem *mi2 = manage(new class Gtk::MenuItem("Gestaltung"));
  
  std::list<Midgard_Optionen::st_OptionenExecute> OLM=MOptionen->getOptionenExecute();
  for(std::list<Midgard_Optionen::st_OptionenExecute>::iterator i=OLM.begin();i!=OLM.end();++i)
   {
    Gtk::Label *_l=manage (new Gtk::Label(i->text));
    Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
    _tab->attach(*_l,0,1,0,1,GTK_FILL,0,0,0);
    if(i->bild) 
     {
      Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
      _tab->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
     }
    Gtk::MenuItem *mi=manage(new Gtk::MenuItem());
    mi->add(*_tab);    
    mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::OptionenExecute_setzen_from_menu),i->index));
    menu1->append(*mi);
   } 
  for(std::list<Midgard_Optionen::st_Ober>::iterator i=MOptionen->getOber().begin();i!=MOptionen->getOber().end();++i)
   {
    if(!i->show) continue;
    MVC_boolMenu_Widget *mi = manage(new MVC_boolMenu_Widget(i->active,i->text,0,0.5));
    i->active.changed.connect(SigC::bind(SigC::slot(this,&midgard_CG::Ober_element_activate),i->index));
    menu2->append(*mi);
   } 
  mi1->set_submenu(*menu1);
  mi2->set_submenu(*menu2);
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi1));
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi2));
  ansicht_menu->show_all();   


  // Regionen
  Gtk::Menu *regionen_menu = manage(new class Gtk::Menu());
//  main_menubar->items().push_back(Gtk::Menu_Helpers::MenuElem("_Regionen","<Control>R", *regionen_menu));
  main_menubar->items().insert(--main_menubar->items().end(),Gtk::Menu_Helpers::MenuElem("_Regionen","<Control>R", *regionen_menu));
  Midgard_Optionen::IconIndex II=MOptionen->getIconIndex();

  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     std::string labeltext=(*i)->Name();
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
     _tab->attach(*RegionenPic::Pic((*i)->Pic(),II),0,1,0,row,0,0,0,0);
     _tab->set_col_spacings(10);

     MVC_boolMenu_Widget *mi = manage(new MVC_boolMenu_Widget((*i)->Active(),*_tab));
     regionen_menu->items().push_back(Gtk::Menu_Helpers::CheckMenuElem(*mi));
     (*i)->Active().changed.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),*i));
     if(!(*i)->Offiziell())
        mi->setSensitive(MOptionen->OptionenCheck(Midgard_Optionen::Original).active,true);
   }
 regionen_menu->show_all();


}



void midgard_CG::menu_history_init(int oldsize)
{
  Gtk::Menu *M=main_menubar->items()[0]->get_submenu();
  Gtk::Menu::MenuList L=M->items();
  for(int i=0;i<oldsize;++i) L.pop_back();
  int x=1;
  for(std::list<std::string>::const_iterator i=LDateien.begin();i!=LDateien.end();++i)
   {
     L.push_back(Gtk::Menu_Helpers::MenuElem(*i, "<Control>"+itos(x)));
     Gtk::MenuItem *mi=(Gtk::MenuItem *)L.back();
     mi->activate.connect(SigC::bind(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::xml_import_history),*i));
     ++x;
   }
}

void midgard_CG::push_back_LDateien(std::string s)
{
  int oldsize=LDateien.size();
  std::list<std::string>::iterator i=find(LDateien.begin(),LDateien.end(),s);

  if (i!=LDateien.end()) LDateien.remove(*i);
  else 
   { if(oldsize>MOptionen->DateiHistory()) LDateien.pop_back(); 
   }

  LDateien.push_front(s);
  menu_history_init(oldsize);
}
