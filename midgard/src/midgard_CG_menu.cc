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

void midgard_CG::menu_init()
{
  table_optionen->init();
  menubar_init();

  if (menu_kontext) { menu_kontext->destroy(); menu_kontext=0; }
  menu_kontext=manage(new Gtk::Menu());


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
     Gtk::CheckMenuItem *_mi=manage(new Gtk::CheckMenuItem());         

     std::string labeltext=(*i)->Name();
/*
     if (labeltext.size()>11)
     {  std::string::size_type pos=0;
        while ((pos=labeltext.find(' ',pos))!=std::string::npos)
        {  labeltext.replace(pos,1,'\n');
        }
     }
*/
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

     _mi->add(*_tab);
     regionen_menu->append(*_mi);
     _mi->set_active((*i)->Active());
     _mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),_mi,*i));
     if(MOptionen->OptionenCheck(Midgard_Optionen::Original).active && 
         !(*i)->Offiziell() )
        _mi->set_sensitive(false);
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
}

//#include <gtk--/menushell.h>
void midgard_CG::menubar_init()
{
reloop:
  for(unsigned int i=3;i<main_menubar->items().size();++i)
    {  main_menubar->items().pop_back(); goto reloop;}

//  const Gtk::MenuShell::MenuList *Gtk_ML;
//  main_menubar->items().back();
//  main_menubar->items().pop_back();
//  main_menubar->items().push_back(Gtk_ML);

  // Ansicht
  Gtk::Menu *ansicht_menu = manage(new class Gtk::Menu());
  main_menubar->items().push_back(Gtk::Menu_Helpers::MenuElem("_Ansicht & Fenster","<Control>A", *ansicht_menu));

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
  std::list<Midgard_Optionen::st_Ober> L=MOptionen->getOber();
  for(std::list<Midgard_Optionen::st_Ober>::iterator i=L.begin();i!=L.end();++i)
   {
    if(!i->show) continue;
    Gtk::CheckMenuItem *mi=manage(new Gtk::CheckMenuItem(i->text));
    mi->set_active(i->active);
    mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::Ober_setzen_from_menu),mi,i->index));
    menu2->append(*mi);
   } 
  mi1->set_submenu(*menu1);
  mi2->set_submenu(*menu2);
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi1));
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi2));
  ansicht_menu->show_all();   

  ///////////////////////////////////////////////////////////////////
  // Regionen
  Gtk::Menu *regionen_menu = manage(new class Gtk::Menu());
  main_menubar->items().push_back(Gtk::Menu_Helpers::MenuElem("_Regionen","<Control>R", *regionen_menu));
  Midgard_Optionen::IconIndex II=MOptionen->getIconIndex();

  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     Gtk::CheckMenuItem *_mi=manage(new Gtk::CheckMenuItem());
     std::string labeltext=(*i)->Name();
/*
     if (labeltext.size()>11)
     {  std::string::size_type pos=0;
        while ((pos=labeltext.find(' ',pos))!=std::string::npos)
        {  labeltext.replace(pos,1,'\n');
        }
     }
*/
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

     _mi->add(*_tab);
     regionen_menu->items().push_back(Gtk::Menu_Helpers::CheckMenuElem(*_mi));
     _mi->set_active((*i)->Active());
     _mi->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),_mi,*i));
     if(MOptionen->OptionenCheck(Midgard_Optionen::Original).active && 
         !(*i)->Offiziell() )
        _mi->set_sensitive(false);
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
