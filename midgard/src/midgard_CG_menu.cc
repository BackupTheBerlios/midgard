/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2004-2005 Christof Petig
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
#include <libmagus/magustrace.h>
#include <Misc/Trace.h>
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

#if 0
static void prop_adaptor(GtkWindow*o)
{  create_prop_editor(G_OBJECT(o),0);
} 
#endif

static Gtk::MenuItem *AddItem(Gtk::Menu *m,const Glib::ustring &name,const SigC::Slot0<void> &sl)
{ m->items().push_back(Gtk::Menu_Helpers::MenuElem(name,sl));
  Gtk::MenuItem *mi = (Gtk::MenuItem *)&m->items().back();
//  mi->signal_activate().connect(sl);
  mi->show();
  return mi;
}

static Gtk::MenuItem *AddItem(Gtk::Menu *m,Gtk::Widget &widg,const SigC::Slot0<void> &sl)
{ Gtk::MenuItem *mi = Gtk::manage(new Gtk::MenuItem(widg));
  m->add(*mi);
  mi->signal_activate().connect(sl);
  mi->show();
  return mi;
}

static Gtk::MenuItem *AddItem(Gtk::Menu *m,const Glib::RefPtr<Gdk::Pixbuf> &image,
  const std::string &name,const SigC::Slot0<void> &sl)
{ Gtk::Image *i=Gtk::manage(new Gtk::Image(image));
  i->show();
  m->items().push_back(Gtk::Menu_Helpers::ImageMenuElem(name,*i,sl));
  Gtk::MenuItem *mi = (Gtk::MenuItem *)&m->items().back();
  mi->show();
  return mi;
}

static bool_CheckMenuItem *AddItem(Gtk::Menu *m,Gtk::Widget &widg, const Model_ref<bool> &model)
{ bool_CheckMenuItem *_M=Gtk::manage(new bool_CheckMenuItem(model,widg));
  m->append(*_M);
  _M->show();
  return _M;
}

static bool_CheckMenuItem *AddItem(Gtk::Menu *m,const Glib::ustring &text, const Model_ref<bool> &model)
{ Gtk::Label *l=Gtk::manage(new Gtk::Label(text));
  l->show();
  return AddItem(m,*l,model);
}

static void AddLine(Gtk::Menu *m)
{ m->items().push_back(Gtk::Menu_Helpers::SeparatorElem());
  Gtk::MenuItem *trennlinie = (Gtk::MenuItem *)&m->items().back();
  trennlinie->show();
}

static Gtk::Menu *AddMenu(Gtk::Menu *m,const Glib::ustring &name)
{ Gtk::Menu *M = Gtk::manage(new class Gtk::Menu());
  Gtk::MenuItem *MI = Gtk::manage(new class Gtk::MenuItem(name)); 
  MI->set_submenu(*M);
  m->append(*MI);
  MI->show();
  return M;
}

static Gtk::Table *make_tab(const Glib::ustring &name,
                            const Glib::RefPtr<Gdk::Pixbuf> &image=Glib::RefPtr<Gdk::Pixbuf>(),
                            bool offiziell=false)
{ Gtk::Table *_tab=Gtk::manage(new Gtk::Table(1,1,false));
  int row=1;
  if(offiziell) 
  { Gtk::Image *_o=Gtk::manage(new Gtk::Image(MagusImage("midgard_logo_tiny.xpm")));
    _tab->attach(*_o,1,2,1,2,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
    row=2;
    _o->show();
  }
  Gtk::Label *_l=Gtk::manage (new Gtk::Label(name,0,0));
  _tab->attach(*_l,1,2,0,1,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
  _l->show();
  if (image)
  { Gtk::Image *_pix=Gtk::manage(new Gtk::Image(image));
    _tab->attach(*_pix,0,1,0,row,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
    _pix->show();
  }
  _tab->set_col_spacings(10);
  _tab->show();
  return _tab;
}

#if 0
static void print(std::string x)
{ std::cerr << x << '\n';
}
#endif

void midgard_CG::menu_init()
{
  ManuProC::Trace _t(LibMagus::trace_vector,__FUNCTION__,menu_kontext);
  menu_kontext=Gtk::manage(new Gtk::Menu());

//Schummel-Menü/////////////////////////////////////////////////////////////////////
  Gtk::Menu *schummel_menu = AddMenu(menu_kontext,"Original-Regel-Menü");
  AddItem(schummel_menu,MagusImage("NSC-Mode-26.xpm"),"alle Regeln abschalten",
    SigC::slot(*this,&midgard_CG::Schummeln));
  AddLine(schummel_menu);
  AddItem(schummel_menu,make_gtk_box(MagusImage("midgard_logo_tiny.xpm"),
      "Originalregeln "),
    Model_ref<bool>(getChar().proxies.checks[Optionen::Original]));
  AddItem(schummel_menu,"Lernschema- und Steigern-Fenster aktivieren",
    SigC::bind(SigC::slot(*this,&midgard_CG::OptionenExecute_setzen_from_menu),
      Magus_Optionen::LernschemaSensitive));
  AddItem(schummel_menu,"Werte editieren",SigC::Slot0<void>())->set_sensitive(false);
  AddItem(schummel_menu,"Mit EP/PP steigern",SigC::Slot0<void>())->set_sensitive(false);
  AddItem(schummel_menu,"NSC-Modus",Model_ref<bool>(getChar().proxies.checks[Optionen::NSC_only]));

//Drucken ///////////////////////////////////////////////////////////////////
  Gtk::Menu *drucken_menu = AddMenu(menu_kontext,"Drucken");
  AddItem(drucken_menu,"Abenteurer drucken (LaTeX)",
        SigC::slot(*this,&midgard_CG::on_abenteurerdokument_drucken));
  AddItem(drucken_menu,"Abenteurerbeschreibung drucken",
        SigC::slot(*this,&midgard_CG::on_beschreibung_drucken));
  AddItem(drucken_menu,"Ausrüstungsdokument drucken (Alles)",
        SigC::slot(*this,&midgard_CG::on_auch_unsichtbares_drucken));
  AddItem(drucken_menu,"Ausrüstungsdokument drucken (Nur sichtbare GegenstÃ€nde)",
        SigC::slot(*this,&midgard_CG::on_nur_sichtbares_drucken));
  AddItem(drucken_menu,"Leeres Abenteurerdokument drucken",
        SigC::slot(*this,&midgard_CG::on_leeres_abenteurerdokument_drucken));

// Abent. Optionen (Original, NSC, ...)
 {Gtk::Menu *char_opt_menu = AddMenu(menu_kontext,"Abent.-Einst.");
   std::list<Optionen::st_OptionenCheck> &L2=getAben().getOptionen().getOptionenCheck();
   for(std::list<Optionen::st_OptionenCheck>::iterator i=L2.begin();i!=L2.end();++i)
    {
     Gtk::Table *_tab=make_tab(i->text,Optionen_GUI::Check_bild(i->index));
     AddItem(char_opt_menu,*_tab,Model_ref<bool>(getChar().proxies.checks[i->index]));
#warning undosave?
   }
 }

//Regionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *regionen_menu = AddMenu(menu_kontext,"Regionen");
  for(std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();i!=Datenbank.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     Gtk::Table *_tab=make_tab((*i)->Name(),RegionenPic::PicModel((*i)->Pic()),
                         (*i)->Offiziell());
     bool_CheckMenuItem *mi=AddItem(regionen_menu,*_tab,Model_ref<bool>(getChar().proxies.regionen[*i]));
     if(!(*i)->Offiziell())
         mi->setSensitive(getChar().proxies.checks[Optionen::Original],true);
   }
  AddLine(regionen_menu);
  AddItem(regionen_menu,"Ausgewählte Regionen zum Standard machen",
            SigC::slot(*this,&midgard_CG::SetStandardRegionen));
#if 0
  standard_regionen->signal_activate().connect(
     SigC::bind(SigC::slot(Programmoptionen->
      &Magus_Optionen::setStandardRegionen),getAben()));
#endif

//Optionen/////////////////////////////////////////////////////////////////////
 {Gtk::Menu *optionen_menu = AddMenu(menu_kontext,"Ansicht & Fenster");

  std::list<Magus_Optionen::st_OptionenExecute> &OLM=Programmoptionen->getOptionenExecute();
  for(std::list<Magus_Optionen::st_OptionenExecute>::iterator i=OLM.begin();i!=OLM.end();++i)
   {
     Gtk::Table *_tab=make_tab(i->text,Optionen_GUI::Execute_bild(i->index));
     AddItem(optionen_menu,*_tab,SigC::bind(SigC::slot(*this,&midgard_CG::OptionenExecute_setzen_from_menu),i->index));
//    mi->signal_activate().connect(SigC::bind(SigC::slot(*this,&midgard_CG::OptionenExecute_setzen_from_menu),i->index));
//    optionen_menu->append(*mi);
   } 
 }
///////////////////////////////////////////////////////////////////////////////
#if 0
  { Gtk::MenuItem *mi=new Gtk::MenuItem("widget properties");
    menu_kontext->append(*mi);
    mi->show();
    mi->signal_activate().connect(SigC::bind(SigC::slot(&prop_adaptor),gobj()));
  }
#endif
///////////
  menu_kontext->show_all();
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
  ManuProC::Trace _t(LibMagus::trace_vector,__FUNCTION__);
  // Ansicht
  Gtk::Menu *ansicht_menu = Gtk::manage(new class Gtk::Menu());
  main_menubar->items().insert(--main_menubar->items().end(),Gtk::Menu_Helpers::MenuElem("Ansicht & _Fenster", Gtk:: GTKMM22(Menu_Helpers::)AccelKey("<Control>F"), *ansicht_menu));

  Gtk::Menu *menu1 = AddMenu(ansicht_menu,"Ansicht & Fenster");
  Gtk::Menu *menu2 = AddMenu(ansicht_menu,"Gestaltung");

  AddItem(ansicht_menu,"Optionen",SigC::slot(*this,&midgard_CG::menu_einstellungen_aendern));

  std::list<Magus_Optionen::st_OptionenExecute> &OLM=Programmoptionen->getOptionenExecute();
  for(std::list<Magus_Optionen::st_OptionenExecute>::iterator i=OLM.begin();i!=OLM.end();++i)
   {
    Gtk::Table *_tab=make_tab(i->text,Optionen_GUI::Execute_bild(i->index));
    AddItem(menu1,*_tab,SigC::bind(SigC::slot(*this,&midgard_CG::OptionenExecute_setzen_from_menu),i->index));
   } 
  for(std::list<Magus_Optionen::st_Ober>::iterator i=Programmoptionen->getOber().begin();i!=Programmoptionen->getOber().end();++i)
   {
    if(!i->show) continue;
    AddItem(menu2,i->text,Model_ref<bool>(i->active));
   } 
  ansicht_menu->show_all();   

  // Regionen
  Gtk::Menu *regionen_menu = Gtk::manage(new class Gtk::Menu());
  main_menubar->items().insert(--main_menubar->items().end(),Gtk::Menu_Helpers::MenuElem("_Regionen",Gtk:: GTKMM22(Menu_Helpers::)AccelKey("<Control>R"), *regionen_menu));

  for(std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();i!=Datenbank.Regionen.end();++i)
   {
     if((*i)->Nr()<=0) continue;
     Gtk::Table *_tab=make_tab((*i)->Name(),RegionenPic::PicModel((*i)->Pic()),(*i)->Offiziell());
     bool_CheckMenuItem *mi =AddItem(regionen_menu,*_tab,Model_ref<bool>(getChar().proxies.regionen[*i]));
     if(!(*i)->Offiziell())
        mi->setSensitive(getChar().proxies.checks[Optionen::Original],true);
   }

  AddLine(regionen_menu);
  AddItem(regionen_menu,"Ausgewählte Regionen zum Standard machen",
          SigC::slot(*this,&midgard_CG::SetStandardRegionen));

 regionen_menu->show_all();

  // Optionen: deutsch Erweiterungen?
 {Gtk::Menu *options_menu = Gtk::manage(new class Gtk::Menu());
  main_menubar->items().insert(--main_menubar->items().end(),Gtk::Menu_Helpers::MenuElem("Er_weiterungen", *options_menu));

  std::list<Optionen::st_OptionenCheck> &L2=getAben().getOptionen().getOptionenCheck();
  for(std::list<Optionen::st_OptionenCheck>::iterator i=L2.begin();i!=L2.end();++i)
  { Gtk::Table *_tab=make_tab(i->text,Optionen_GUI::Check_bild(i->index));
    AddItem(options_menu,*_tab,Model_ref<bool>(getChar().proxies.checks[i->index]));
  }
  AddLine(options_menu);
  
  std::list<Optionen::st_Haus> &L3=getAben().getOptionen().getHausregeln();
  for(std::list<Optionen::st_Haus>::iterator i=L3.begin();i!=L3.end();++i)
  { Gtk::Table *_tab=make_tab(i->text,Optionen_GUI::Haus_bild(i->index));
    AddItem(options_menu,*_tab,Model_ref<bool>(getChar().proxies.hausregeln[i->index]));
  }
  options_menu->show_all();
 }
 
 menu_history_init(-1);
}



void midgard_CG::menu_history_init(int oldsize)
// oldsize is not used ...
{
  ManuProC::Trace _t(LibMagus::trace_vector,__FUNCTION__);
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
