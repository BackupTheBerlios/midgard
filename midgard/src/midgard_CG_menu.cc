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
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <Misc/itos.h>
#include <bool_CheckMenuItem.hh>
//#include <RefPtr_Pixmap.hh>
#include "Region_GUI.hh"
#include "Optionen_GUI.hh"
#include "WindowInfo.hh"
#include <libmagus/Datenbank.hh>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#if MPC_SIGC_VERSION > 0x120
#  include <sigc++/bind.h>
#endif
#include "prop-editor.h"

// nach reiflicher �berlegung bin ich zu dem Entschluss gekommen, dass
// make_gtk_box den R�ckgabewert bereits show't (Schlie�lich ist es eine Referenz)
// dies widerspricht zwar allen gtkmm Konventionen ... CP Jun 2004
Gtk::Box &midgard_CG::make_gtk_box(Glib::RefPtr<Gdk::Pixbuf> data,const std::string &label,const bool text_vor_bild,const bool hbox)
{
  Gtk::Image *_p=Gtk::manage(new Gtk::Image(data));
  Gtk::Label *_l=Gtk::manage(new Gtk::Label(label));
  Gtk::Box *_v;
  if(hbox) _v=Gtk::manage(new Gtk::HBox());
  else     _v=Gtk::manage(new Gtk::VBox());
  if(text_vor_bild)  { _v->pack_start(*_l,false,false);
                       _v->pack_start(*_p,false,false); }
  else               { _v->pack_start(*_p,false,false);
                       _v->pack_start(*_l,false,false); }
  _p->show();
  _l->show();
  _v->show();
  return *_v;
}

static void prop_adaptor(GtkWindow*o)
{  create_prop_editor(G_OBJECT(o),0);
} 

void midgard_CG::menu_init()
{
  menu_kontext=Gtk::manage(new Gtk::Menu());

//Schummel-Menü/////////////////////////////////////////////////////////////////////
  Gtk::Menu *schummel_menu = Gtk::manage(new class Gtk::Menu());
  Gtk::MenuItem *schummel = Gtk::manage(new class Gtk::MenuItem("Original-Regel-Menü"));
  schummel->set_submenu(*schummel_menu);

  {Gtk::MenuItem *_M=Gtk::manage(new Gtk::MenuItem(make_gtk_box(MagusImage("NSC-Mode-26.xpm"),"alle Regeln abschalten")));
  schummel_menu->append(*_M);
  _M->show();
  _M->signal_activate().connect(SigC::slot(*this,&midgard_CG::Schummeln),true);}

  Gtk::MenuItem *trennlinie = (Gtk::MenuItem *)&schummel_menu->items().back();
  trennlinie->show();

  {bool_CheckMenuItem *_M=Gtk::manage(new bool_CheckMenuItem(getChar().proxies.checks[Optionen::Original],make_gtk_box(MagusImage("midgard_logo_tiny.xpm"),"Originalregeln ")));
  schummel_menu->append(*_M);
  _M->show();}

  {Gtk::MenuItem *_M = Gtk::manage(new Gtk::MenuItem("Lernschema- und Steigern-Fenster aktivieren"));
  schummel_menu->append(*_M);
  _M->signal_activate().connect(SigC::bind(SigC::slot(*this,&midgard_CG::OptionenExecute_setzen_from_menu),Magus_Optionen::LernschemaSensitive),true);
  _M->show();}

  {bool_CheckMenuItem *_M=Gtk::manage(new bool_CheckMenuItem(table_grundwerte->edit_werte,"Werte editieren"));
  schummel_menu->append(*_M);
  _M->show();}

//  {bool_CheckMenuItem *_M=Gtk::manage(new bool_CheckMenuItem(table_steigern->steigern_mit_EP_bool,"Mit EP/PP steigern"));
//  schummel_menu->append(*_M);}
#warning Schummeln

  {bool_CheckMenuItem *_M=Gtk::manage(new bool_CheckMenuItem(getChar().proxies.checks[Optionen::NSC_only],"NSC-Modus"));
  schummel_menu->append(*_M); _M->show();}

  menu_kontext->append(*schummel);

//Drucken ///////////////////////////////////////////////////////////////////
  Gtk::Menu *drucken_menu = Gtk::manage(new class Gtk::Menu());
  Gtk::MenuItem *drucken = Gtk::manage(new class Gtk::MenuItem("Drucken")); 
  drucken->set_submenu(*drucken_menu);

  Gtk::MenuItem *latex = Gtk::manage(new class Gtk::MenuItem("Abenteurer drucken (LaTeX)"));
  drucken_menu->append(*latex);
  latex->signal_activate().connect(SigC::slot(*this,&midgard_CG::on_abenteurerdokument_drucken));

  Gtk::MenuItem *latex_beschreibung = Gtk::manage(new class Gtk::MenuItem("Abenteurerbeschreibung drucken"));
  drucken_menu->append(*latex_beschreibung);
  latex_beschreibung->signal_activate().connect(SigC::slot(*this,&midgard_CG::on_beschreibung_drucken));

  Gtk::MenuItem *latex_ausruestung = Gtk::manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Alles)"));
  drucken_menu->append(*latex_ausruestung);
  latex_ausruestung->signal_activate().connect(SigC::slot(*this,&midgard_CG::on_auch_unsichtbares_drucken));
  Gtk::MenuItem *latex_ausruestung2 = Gtk::manage(new class Gtk::MenuItem("Ausrüstungsdokument drucken (Nur sichtbare GegenstÃ€nde)"));
  drucken_menu->append(*latex_ausruestung2);
  latex_ausruestung2->signal_activate().connect(SigC::slot(*this,&midgard_CG::on_nur_sichtbares_drucken));

  Gtk::MenuItem *latex_empty = Gtk::manage(new class Gtk::MenuItem("Leeres Abenteurerdokument drucken"));
  drucken_menu->append(*latex_empty);
  latex_empty->signal_activate().connect(SigC::slot(*this,&midgard_CG::on_leeres_abenteurerdokument_drucken));

  menu_kontext->append(*drucken);
//Regionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *regionen_menu = Gtk::manage(new class Gtk::Menu());
  Gtk::MenuItem *regionen = Gtk::manage(new class Gtk::MenuItem("Regionen")); 
  regionen->set_submenu(*regionen_menu);
  for(std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();i!=Datenbank.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     std::string labeltext=(*i)->Name();
     Gtk::Table *_tab=Gtk::manage(new Gtk::Table(1,1,false));
     int row=1;
     if((*i)->Offiziell()) 
       {
        Gtk::Image *_o=Gtk::manage(new Gtk::Image(MagusImage("midgard_logo_tiny.xpm")));
        _tab->attach(*_o,1,2,1,2,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
        row=2;
       }
     Gtk::Label *_l=Gtk::manage (new Gtk::Label(labeltext,0,0));
     _tab->attach(*_l,1,2,0,1,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
     Gtk::Image *_pix=Gtk::manage(new Gtk::Image(RegionenPic::PicModel((*i)->Pic())));
     _tab->attach(*_pix,0,1,0,row,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
     _tab->set_col_spacings(10);

     bool_CheckMenuItem *mi = Gtk::manage(new bool_CheckMenuItem(getChar().proxies.regionen[*i],*_tab));
     regionen_menu->append(*mi);
//     getChar().proxies.regionen[*i].signal_changed().connect(SigC::bind(SigC::slot(*this,&midgard_CG::on_checkbutton_Regionen_menu),*i));
     if(!(*i)->Offiziell())
         mi->setSensitive(getChar().proxies.checks[Optionen::Original],true);
   }
  regionen_menu->items().push_back(Gtk::Menu_Helpers::SeparatorElem());  
  Gtk::MenuItem *standard_regionen = Gtk::manage(new class Gtk::MenuItem("Ausgewählte Regionen zum Standard machen"));
  regionen_menu->append(*standard_regionen);
#if 0
  standard_regionen->signal_activate().connect(
     SigC::bind(SigC::slot(Programmoptionen->
      &Magus_Optionen::setStandardRegionen),getAben()));
#else
   standard_regionen->signal_activate().connect(SigC::slot(*this,&midgard_CG::SetStandardRegionen));
#endif
  menu_kontext->append(*regionen);
  

//Optionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *optionen_menu = Gtk::manage(new class Gtk::Menu());
  Gtk::MenuItem *optionen = Gtk::manage(new class Gtk::MenuItem("Ansicht & Fenster")); 
  optionen->set_submenu(*optionen_menu);

  std::list<Magus_Optionen::st_OptionenExecute> OLM=Programmoptionen->getOptionenExecute();
  for(std::list<Magus_Optionen::st_OptionenExecute>::iterator i=OLM.begin();i!=OLM.end();++i)
   {
    Gtk::Label *_l=Gtk::manage (new Gtk::Label(i->text));
    Gtk::Table *_tab=Gtk::manage(new Gtk::Table(1,1,false));
    _tab->attach(*_l,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    if(Optionen_GUI::Execute_bild(i->index)) 
     {
      Gtk::Image *_o=Gtk::manage(new Gtk::Image(Optionen_GUI::Execute_bild(i->index)));
      _tab->attach(*_o,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     }
    Gtk::MenuItem *mi=Gtk::manage(new Gtk::MenuItem());
    mi->add(*_tab);    
    mi->signal_activate().connect(SigC::bind(SigC::slot(*this,&midgard_CG::OptionenExecute_setzen_from_menu),i->index));
    optionen_menu->append(*mi);
   } 
  menu_kontext->append(*optionen);
///////////////////////////////////////////////////////////////////////////////
  { Gtk::MenuItem *mi=new Gtk::MenuItem("widget properties");
    menu_kontext->append(*mi);
    mi->show();
    mi->signal_activate().connect(SigC::bind(SigC::slot(&prop_adaptor),gobj()));
  }
  menu_kontext->show_all();

///////////
}


/*
static void wert_changed(gpointer gp)
{ 
  std::cout << "MENÜ: WC: "<<  *(bool*)(gp)<<'\n';
} 
*/ 

#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION<=2
#  define GTKMM22(x) x
#else
#  define GTKMM22(x)
#endif

void midgard_CG::menubar_init()
{
  // Ansicht
  Gtk::Menu *ansicht_menu = Gtk::manage(new class Gtk::Menu());
  main_menubar->items().insert(--main_menubar->items().end(),Gtk::Menu_Helpers::MenuElem("Ansicht & _Fenster", Gtk:: GTKMM22(Menu_Helpers::)AccelKey("<Control>F"), *ansicht_menu));

  Gtk::Menu *menu1 = Gtk::manage(new class Gtk::Menu());
  Gtk::Menu *menu2 = Gtk::manage(new class Gtk::Menu());

  Gtk::MenuItem *mi0 = Gtk::manage(new class Gtk::MenuItem("Optionen"));
  mi0->signal_activate().connect(SigC::slot(*this,&midgard_CG::menu_einstellungen_aendern));
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi0));

  Gtk::MenuItem *mi1 = Gtk::manage(new class Gtk::MenuItem("Ansicht & Fenster"));
  Gtk::MenuItem *mi2 = Gtk::manage(new class Gtk::MenuItem("Gestaltung"));
  
  std::list<Magus_Optionen::st_OptionenExecute> OLM=Programmoptionen->getOptionenExecute();
  for(std::list<Magus_Optionen::st_OptionenExecute>::iterator i=OLM.begin();i!=OLM.end();++i)
   {
    Gtk::Label *_l=Gtk::manage (new Gtk::Label(i->text));
    Gtk::Table *_tab=Gtk::manage(new Gtk::Table(1,1,false));
    _tab->attach(*_l,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    if(Optionen_GUI::Execute_bild(i->index)) 
     {
      Gtk::Image *_o=Gtk::manage(new Gtk::Image(Optionen_GUI::Execute_bild(i->index)));
      _tab->attach(*_o,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     }
    Gtk::MenuItem *mi=Gtk::manage(new Gtk::MenuItem());
    mi->add(*_tab);    
    mi->signal_activate().connect(SigC::bind(SigC::slot(*this,&midgard_CG::OptionenExecute_setzen_from_menu),i->index));
    menu1->append(*mi);
   } 
  for(std::list<Magus_Optionen::st_Ober>::iterator i=Programmoptionen->getOber().begin();i!=Programmoptionen->getOber().end();++i)
   {
    if(!i->show) continue;
    bool_CheckMenuItem *mi = Gtk::manage(new bool_CheckMenuItem(i->active,i->text));
    i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&midgard_CG::Ober_setzen_from_menu),i->index));
    menu2->append(*mi);
   } 
  mi1->set_submenu(*menu1);
  mi2->set_submenu(*menu2);
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi1));
  ansicht_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*mi2));
  ansicht_menu->show_all();   


  // Regionen
  Gtk::Menu *regionen_menu = Gtk::manage(new class Gtk::Menu());
  main_menubar->items().insert(--main_menubar->items().end(),Gtk::Menu_Helpers::MenuElem("_Regionen",Gtk:: GTKMM22(Menu_Helpers::)AccelKey("<Control>R"), *regionen_menu));

  for(std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();i!=Datenbank.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     std::string labeltext=(*i)->Name();
     Gtk::Table *_tab=Gtk::manage(new Gtk::Table(1,1,false));
     int row=1;
     if((*i)->Offiziell()) 
       {
        Gtk::Image *_o=Gtk::manage(new Gtk::Image(MagusImage("midgard_logo_tiny.xpm")));
        _tab->attach(*_o,1,2,1,2,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
        row=2;
       }
     Gtk::Label *_l=Gtk::manage (new Gtk::Label(labeltext,0,0));
     _tab->attach(*_l,1,2,0,1,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
     Gtk::Image *_pix=Gtk::manage(new Gtk::Image(RegionenPic::PicModel((*i)->Pic())));
     _tab->attach(*_pix,0,1,0,row,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
     _tab->set_col_spacings(10);

     bool_CheckMenuItem *mi = (new bool_CheckMenuItem(getChar().proxies.regionen[*i],*_tab));
     regionen_menu->items().push_back(Gtk::Menu_Helpers::CheckMenuElem(*mi));
     // Gtk::manage(mi);
//     getChar().proxies.regionen[*i].signal_changed().connect(SigC::bind(SigC::slot(*this,&midgard_CG::on_checkbutton_Regionen_menu),*i));
     if(!(*i)->Offiziell())
        mi->setSensitive(getChar().proxies.checks[Optionen::Original],true);
   }

  regionen_menu->items().push_back(Gtk::Menu_Helpers::SeparatorElem());  
  Gtk::MenuItem *standard_regionen = Gtk::manage(new class Gtk::MenuItem("Ausgewählte Regionen zum Standard machen"));
  regionen_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(*standard_regionen));
  standard_regionen->signal_activate().connect(SigC::slot(*this,&midgard_CG::SetStandardRegionen));

 regionen_menu->show_all();
 menu_history_init(-1);
}



void midgard_CG::menu_history_init(int oldsize)
// oldsize is not used ...
{
  Gtk::Menu *M=manage(new Gtk::Menu); // main_menubar->items()[0].get_submenu();
  zuletzt_geladen_mi->set_submenu(*M);
  Gtk::Menu::MenuList L=M->items();
  int x=1;
  for(std::list<std::string>::const_iterator i=Programmoptionen->LetzteDateien().begin();
  		i!=Programmoptionen->LetzteDateien().end();++i)
   {
     if (x<10) L.push_back(Gtk::Menu_Helpers::MenuElem(*i, Gtk:: GTKMM22(Menu_Helpers::)AccelKey("<Control>"+itos(x))));
     else L.push_back(Gtk::Menu_Helpers::MenuElem(*i));
     Gtk::MenuItem *mi=(Gtk::MenuItem *)&L.back();
     mi->signal_activate().connect(SigC::bind(SigC::slot(*static_cast<class midgard_CG*>(this), &midgard_CG::xml_import_history),*i));
     mi->show();
     ++x;
   }
}

void midgard_CG::push_back_LDateien(std::string s)
{
  int oldsize=Programmoptionen->LetzteDateien().size();
  std::list<std::string>::iterator i=find(Programmoptionen->LetzteDateien().begin(),Programmoptionen->LetzteDateien().end(),s);

  if (i!=Programmoptionen->LetzteDateien().end()) Programmoptionen->LetzteDateien().remove(*i);
  else 
   { if(oldsize>Programmoptionen->DateiHistory()) Programmoptionen->LetzteDateien().pop_back(); 
   }

  Programmoptionen->LetzteDateien().push_front(s);
#warning MVC
  menu_history_init(oldsize);
}

void midgard_CG::OptionenExecute_setzen_from_menu(Magus_Optionen::OptionenExecuteIndex index)
{  if(index==Magus_Optionen::LernschemaSensitive) lernschema_sensitive(true);
   else if(index==Magus_Optionen::show_InfoWindow) InfoFenster->show();
}

void midgard_CG::SetStandardRegionen() const
{
   Programmoptionen->setStandardRegionen(getAben());
}
