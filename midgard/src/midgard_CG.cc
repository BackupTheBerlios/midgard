// $Id: midgard_CG.cc,v 1.335 2004/02/02 07:28:30 christof Exp $
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

#include "midgard_CG.hh"
#include <gtkmm/notebook.h>
#include <gtkmm/main.h>
//#include "Midgard_Info.hh"
//#include "BegruessungsWindow.hh"
#include "Fertigkeiten.hh"
#include <unistd.h>
//#include <stdlib.h>
#ifdef __MINGW32__
#include <time.h>
#endif
#include "Windows_Linux.hh"
#include <Misc/Trace.h>
#include <bool_properties.hh>
#include <gdkmm/pixbufloader.h>
#include <bool_ImageButton.hh>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#include <Gtk_OStream.h>
#include "xml_fileselection.hh"
//#include "WindowInfo.hh"
#include <libmagus/Datenbank.hh>
#include "MagusDialog.hh"

static void ImageLabelKnopf(Gtk::Button *b, Glib::RefPtr<Gdk::Pixbuf> pb, const Glib::ustring &t)
{  Gtk::VBox *vbox=manage(new Gtk::VBox());
   b->add(*vbox);
   Gtk::Image *image=manage(new Gtk::Image(pb));
   vbox->add(*image);
   Gtk::Label *label=manage(new Gtk::Label(t));
   vbox->add(*label);
   image->show();
   label->show();
   vbox->show();
   b->set_relief(Gtk::RELIEF_NONE);
}

midgard_CG::midgard_CG(WindowInfo *info,VAbenteurer::iterator i)
: news_columns(), undo_menu(),menu_kontext(),
	InfoFenster(info), toolview(_tooltips)
{ news_columns.attach_to(*list_news);

  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);

  table_optionen->set_Hauptfenster(this);
  
  srand(time(0));
// ToolBar: StyleIcon
  button_neuer_charakter->add(MagusImage("NewChar-trans-50.xpm"),"Neu mit Wizard",SigC::slot(*this,&midgard_CG::on_neuer_charakter));
  button_neuer_charakter->add(MagusImage("NewChar-trans-50.xpm"),"Neu ohne Wizard",SigC::slot(*this,&midgard_CG::on_neuer_charakter_clicked));
  button_neuer_charakter->set_relief(Gtk::RELIEF_NONE);
  button_neuer_charakter->set_tooltips(&_tooltips);
  button_speichern->add(MagusImage("SaveChar-trans-50.xpm"),"Speichern",SigC::slot(*this,&midgard_CG::save_existing_filename));
  button_speichern->add(MagusImage("SaveChar-trans-50.xpm"),"Speichern unter",SigC::slot(*this,&midgard_CG::xml_export_auswahl));
  button_speichern->set_relief(Gtk::RELIEF_NONE);
  button_speichern->set_tooltips(&_tooltips);
  button_main_drucken->add(MagusImage("PrintChar-trans-50.xpm"),"Drucken",SigC::slot(*this,&midgard_CG::on_latex));
  button_main_drucken->set_relief(Gtk::RELIEF_NONE);
  button_main_drucken->set_tooltips(&_tooltips);
  ImageLabelKnopf(button_undo,MagusImage("Undo.xpm"),"Zurück");
  ImageLabelKnopf(button_redo,MagusImage("redo.xpm"),"Vorwärts");
  
// Statusbar MVC
  bool_ImageButton *wuerfelt_butt = new bool_ImageButton(aktiver.proxies.werte_eingeben,
  	MagusImage("hand_roll.png"),MagusImage("auto_roll.png"));
  toolview.Associate(*wuerfelt_butt,aktiver.proxies.werte_eingeben,
  		"Werte werden ausgewürfelt. (Hier klicken zum eingeben)",
  		"Werte werden eingegeben. (Hier klicken zum auswürfeln)");
  hbox_status->pack_start(*wuerfelt_butt, Gtk::PACK_SHRINK, 0);
  wuerfelt_butt->show();

  set_sensitive(true);

  menubar_init();
  table_optionen->init();
  menu_init();
  init_statusbar();

  if (!AbenteurerAuswahl::Chars.empty())
	aktiver.setAbenteurer(AbenteurerAuswahl::Chars.begin());
  else if(Programmoptionen.OptionenCheck(Magus_Optionen::Wizard_immer_starten).active) 
       on_wizard_starten_activate();
  else on_neuer_charakter_clicked();
  if(Programmoptionen.OptionenCheck(Magus_Optionen::Notebook_start).active.Value() &&
  	Programmoptionen.OptionenCheck(Magus_Optionen::Notebook_start).wert!=-1) 
     notebook_main->set_current_page(Programmoptionen.OptionenCheck(Magus_Optionen::Notebook_start).wert);
  else notebook_main->set_current_page(PAGE_GRUNDWERTE);
  
  // Optionen setzen:
  Ober_setzen_from_menu(0,Magus_Optionen::Customize_Icons);
  Ober_setzen_from_menu(0,Magus_Optionen::AutoShrink);

  // für die NEWS
  Gtk::OStream os(list_news);
  os << 
#include"NEWS.h" 
   <<'\n';
   
  table_grundwerte->init(this); 
  table_lernschema->init(this); // qq 
  table_steigern->init(this); // qq
  table_beschreibung->init(this); // qq
  table_ausruestung->init(this); // qq
  table_zufall->init(this); // qq
  
  aktiver.proxies.wizard.signal_changed().connect(SigC::slot(*this,&midgard_CG::wizard_changed));
  aktiver.proxies.undo_changed.connect(SigC::slot(*this,&midgard_CG::refresh));
  aktiver.signal_anderer_abenteurer().connect(SigC::slot(*this,&midgard_CG::refresh));
  AbenteurerAuswahl::Chars.signal_changed().connect(SigC::slot(*this,&midgard_CG::refresh_char_list));
//  refresh();
  aktiver.signal_anderer_abenteurer()();
  aktiver.proxies.wizard.signal_changed()(0);
  AbenteurerAuswahl::Chars.signal_changed()();
}

midgard_CG::~midgard_CG()
{  
//cout << "~midgard_CG()\n\n\n\n";
//   in_dtor=true;
   if (menu_kontext) delete menu_kontext;
   if (undo_menu) delete undo_menu;
}

void midgard_CG::init_statusbar()
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
//  vec_region_status.clear();
  Gtk::HBox *hb_regionen_status=manage(new class Gtk::HBox(false, 0));
  for(std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();i!=Datenbank.Regionen.end();++i)
   {
     Gtk::Image *_pix=manage(new Gtk::Image(RegionenPic::PicModel((*i)->Pic(),true)));
     hb_regionen_status->pack_start(*_pix);
     Gtk::AssociateVisibility(_pix,aktiver.proxies.regionen[*i]);
//     vec_region_status.push_back(st_reg_status((*i)->Pic(),_pix));
   }
  hb_regionen_status->show();
  frame_regionen_status->add(*hb_regionen_status);
}

void midgard_CG::WizardBeenden() { on_wizard_beenden_activate(); }
void midgard_CG::AndererAbenteurer() 
{  getChar().signal_anderer_abenteurer()(); 
   this->on_neuer_charakter_clicked();
   this->table_lernschema->init(this);
   this->table_steigern->init(this);
}

void midgard_CG::LernschemaSteigern(bool l,bool s)
{  this->frame_lernschema->set_sensitive(l);
   this->frame_steigern->set_sensitive(s);
}

void midgard_CG::on_exportieren_activate()
{
   (new xml_fileselection(this,xml_fileselection::Export));
}

void midgard_CG::on_kompletter_export_activate()
{
   (new xml_fileselection(this,xml_fileselection::ExportFull));
}

void midgard_CG::grundwerte_background_create()
{  assert (get_window());
   {  Glib::RefPtr<Gdk::Pixbuf> pb=MagusImage("Gross_dfr4.light");
      int w,h;
      get_window()->get_size(w,h);
      Glib::RefPtr<Gdk::Pixmap> pm=Gdk::Pixmap::create(get_window(),w,h,get_window()->get_depth());
      Glib::RefPtr<Gdk::GC> gc=Gdk::GC::create(pm);
      gfloat faktor_x=gfloat(w)/pb->get_width(),
      	faktor_y=gfloat(h)/pb->get_height();
      if (faktor_x>faktor_y) faktor_y=faktor_x;
      else faktor_x=faktor_y;
      int pbw=gint(faktor_x*pb->get_width()+.5),
      	  pbh=gint(faktor_y*pb->get_height()+.5);
      if (pbw<w) pbw=w; // make absolutely sure that it is bigger
      if (pbh<h) pbh=h;
      Glib::RefPtr<Gdk::Pixbuf> pb_scaled
      		=pb->scale_simple(pbw,pbh,Gdk::INTERP_HYPER);
//std::cout << w << ',' << h << ' ' << pbw << ',' << pbh << '\n';      		
      pm->draw_pixbuf(gc,pb_scaled,(pbw-w)/2,(pbh-h)/2,0,0,w,h,Gdk::RGB_DITHER_NORMAL,0,0);
      Glib::RefPtr<Gtk::Style> st=grundwerte_background->get_style()->copy();
      st->set_bg_pixmap(Gtk::STATE_NORMAL,pm);
      grundwerte_background->set_style(st);
   }
}

void midgard_CG::refresh()
{  set_title(getAben().Name_Abenteurer());
}

void midgard_CG::refresh_char_list()
{  // if (abent_menu) delete abent_menu;
   Gtk::Menu *abent_menu=manage(new Gtk::Menu);
   for (VAbenteurer::iterator i=AbenteurerAuswahl::Chars.begin();
		i!=AbenteurerAuswahl::Chars.end();++i)
   {  // vielleicht noch mit Typ(Grad) ?   z.B. Aneren Hl(8)
//      Gtk::MenuItem *mi=manage(new Gtk::MenuItem(i->getAbenteurer().Name_Abenteurer()));
      abent_menu->items().push_back(Gtk::Menu_Helpers::MenuElem(i->getAbenteurer().Name_Abenteurer()));
      Gtk::MenuItem &mi=abent_menu->items().back();
      mi.show();
      mi.signal_activate().connect(SigC::bind(SigC::slot(
      		getChar(),&AbenteurerAuswahl::setAbenteurer_sig),i));
   }
   abenteurer_mi->set_submenu(*abent_menu);
}

midgard_CG::enum_notebook_main midgard_CG::get_current_page() const
{  return enum_notebook_main(notebook_main->get_current_page());
}
