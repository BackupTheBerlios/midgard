// $Id: midgard_CG.cc,v 1.293 2003/04/15 17:29:29 christof Exp $
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
#include "Midgard_Info.hh"
#include "BegruessungsWindow.hh"
#include "Fertigkeiten.hh"
#include <unistd.h>
//#include <stdlib.h>
#ifdef __MINGW32__
#include <time.h>
#endif
#include "Windows_Linux.hh"
#include <Misc/Trace.h>
#include <char_Pixmap.hh>
#include <gdkmm/pixbufloader.h>
#include <bool_ImageButton.hh>

static Glib::RefPtr<Gdk::Pixbuf> LoadImage(const unsigned char data[], unsigned size)
{  Glib::RefPtr<Gdk::PixbufLoader> loader=Gdk::PixbufLoader::create();
   loader->write(data, size);
   loader->close();
   return loader->get_pixbuf();
}

static Glib::RefPtr<Gdk::Pixbuf> LoadImage(const char * const *data)
{  return Gdk::Pixbuf::create_from_xpm_data(data);
}

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
}

midgard_CG::midgard_CG(const std::string &_argv0,const std::string &_magus_verzeichnis,
                       const std::string &datei)
: magus_paths(_argv0,_magus_verzeichnis),in_dtor(false),
	InfoFenster(0), news_columns(),
	MOptionen(0),wizard(0),menu_kontext(0),
	schummeln(false),tag_eigene_artikel(Tag("MAGUS-data"))
{ news_columns.attach_to(*list_news);
//  ManuProC::Tracer::Enable(table_grundwerte::trace_channel);
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  InfoFenster = manage(new WindowInfo(this));

  // Optionen laden
  fill_IconVec();
  MOptionen = new Midgard_Optionen(this); 
  table_optionen->set_Hauptfenster(this);
  MOptionen->load_options(with_path("magus_optionen.xml",false,true));
  // wait for Window to appear
  while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
  
  srand(time(0));
  Database.load(Midgard_Info,this);

  set_sensitive(true);

  if (!datei.empty()) xml_import(datei); // Charakter laden
  else if(MOptionen->OptionenCheck(Midgard_Optionen::Wizard_immer_starten).active) 
       on_wizard_starten_activate();
  else on_neuer_charakter_clicked();
  if(MOptionen->OptionenCheck(Midgard_Optionen::Notebook_start).wert!=-1) 
     notebook_main->set_current_page(MOptionen->OptionenCheck(Midgard_Optionen::Notebook_start).wert);


  menubar_init();
  table_optionen->init();
  menu_init();
  init_statusbar();

// ToolBar: StyleIcon
  button_neuer_charakter->add(LoadImage(StyleIcon(iNew).icon),"Neu mit Wizard",SigC::slot(*this,&midgard_CG::on_neuer_charakter_release_event));
  button_neuer_charakter->add(LoadImage(StyleIcon(iNew).icon),"Neu ohne Wizard",SigC::slot(*this,&midgard_CG::on_neuer_charakter_clicked));
  button_speichern->add(LoadImage(StyleIcon(iClose).icon),"Speichern",SigC::slot(*this,&midgard_CG::save_existing_filename));
  button_speichern->add(LoadImage(StyleIcon(iClose).icon),"Speichern unter",SigC::slot(*this,&midgard_CG::xml_export_auswahl));
  button_main_drucken->add(LoadImage(StyleIcon(iPrint).icon),"Drucken",SigC::slot(*this,&midgard_CG::on_latex_release_event));
  ImageLabelKnopf(button_undo,LoadImage(StyleIcon(iBack).icon),StyleIcon(iBack).text);
  ImageLabelKnopf(button_redo,LoadImage(StyleIcon(iForward).icon),StyleIcon(iForward).text);
  
// Statusbar MVC
  extern const unsigned char hand_roll_png_data[],auto_roll_png_data[];
  extern const unsigned hand_roll_png_size,auto_roll_png_size;
  Glib::RefPtr<Gdk::Pixbuf> hand_roll=LoadImage(hand_roll_png_data, hand_roll_png_size);
  Glib::RefPtr<Gdk::Pixbuf> auto_roll=LoadImage(auto_roll_png_data, auto_roll_png_size);
  bool_ImageButton *wuerfelt_butt = new bool_ImageButton(MOptionen->WerteEingebenModel(),hand_roll,auto_roll);
  hbox_status->pack_start(*wuerfelt_butt, Gtk::PACK_SHRINK, 0);
  
  // für die NEWS
  Gtk::OStream os(list_news);
  os << 
#include"NEWS.h" 
   <<'\n';

  if(MOptionen->OberCheck(Midgard_Optionen::BegruessungsFenster).active)
     manage(new BegruessungsWindow(this));
}

midgard_CG::~midgard_CG()
{  
//cout << "~midgard_CG()\n\n\n\n";
   in_dtor=true;
   delete MOptionen;
   if(wizard) delete wizard;
}

void midgard_CG::init_statusbar()
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
//  frame_regionen_status->remove();
  vec_region_status.clear();
  Gtk::HBox *hb_regionen_status=manage(new class Gtk::HBox(false, 0));
//  Midgard_Optionen::IconIndex II=MOptionen->getIconIndex();
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     char_Pixmap *_pix=manage(new char_Pixmap((*i)->RegionPixSmall()));
     hb_regionen_status->pack_start(*_pix);
     if((*i)->Active()) _pix->show();
     vec_region_status.push_back(st_reg_status((*i)->Pic(),_pix));
   }
  hb_regionen_status->show();
  frame_regionen_status->add(*hb_regionen_status);
}

void midgard_CG::set_region_statusbar(RegionenPic::epic pic,bool active)
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  for(std::vector<st_reg_status>::const_iterator i=vec_region_status.begin();i!=vec_region_status.end();++i)
   {
     if(i->name==pic)
      {
        if(active) i->pix->show();
        else i->pix->hide();
        return;
      }
   }
}


std::string magus_paths::with_path(const std::string &name,bool path_only,bool noexit) const
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  std::vector<std::string> V;
#ifndef __MINGW32__ // IMHO macht das unter Win32 keinen Sinn

  // vielleicht sollten wir das aktuelle Verzeichnis beim 
  // Programmstart einmal ermitteln und nicht immer
  char currentwd[10240];
  *currentwd=0;
  getcwd(currentwd,sizeof currentwd);
  
  V.push_back(std::string(currentwd)+"/");
#endif  
  V.push_back(magus_verzeichnis);
#ifndef __MINGW32__
  V.push_back(PACKAGE_DATA_DIR);
  V.push_back(std::string(PACKAGE_DATA_DIR)+"/docs/");
  V.push_back(std::string(currentwd)+"/../xml/");
  V.push_back(std::string(currentwd)+"/../docs/");
#else
  V.push_back(BinaryVerzeichnis());
  V.push_back(BinaryVerzeichnis()+"Daten\\");
  V.push_back(BinaryVerzeichnis()+"Hilfe\\");
#endif  
  std::string ntmp;
  for(std::vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
   {
     std::string n=*i+name;
//cout <<"Suche nach "<< n<<'\n';
     if(!access(n.c_str(),R_OK)) 
      { if(path_only) return *i;
        else return n;
      }
   }
  std::cout << "File "+name+" nowhere found\n";
  if(!noexit) exit(1);
  return("");
}

std::string magus_paths::BinaryVerzeichnis() const
{  
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
   if (argv0.rfind(WinLux::dirsep)!=std::string::npos) 
      return argv0.substr(0,argv0.rfind(WinLux::dirsep)+1);
   else return "";
}

void midgard_CG::fill_IconVec()
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  // InfoFenster
  IconVec.push_back(st_buttons(InfoFenster->button_bestaetigen,iJa));
  IconVec.push_back(st_buttons(InfoFenster->button_abbrechen,iNein));
  IconVec.push_back(st_buttons(InfoFenster->button_info_ok,iOK));
  IconVec.push_back(st_buttons(InfoFenster->button_erase,iErase));
  // Grundwerte
  IconVec.push_back(st_buttons(table_grundwerte->button_grundwerte,iEigenschaften));
  IconVec.push_back(st_buttons(table_grundwerte->button_abg_werte,iAbgeleitet));
  IconVec.push_back(st_buttons(table_lernschema->button_angeborene_fert,iAngeFert));
  IconVec.push_back(st_buttons(table_grundwerte->eventbox_werte_edit,iEditGrund));
  // Lernschema
  IconVec.push_back(st_buttons(table_lernschema->button_lernpunkte,iLernpunkte));
  IconVec.push_back(st_buttons(table_lernschema->togglebutton_lernpunkte_edit,iLernEdit));
  IconVec.push_back(st_buttons(table_lernschema->button_beruf,iBeruf));
  IconVec.push_back(st_buttons(table_lernschema->button_angeborene_fert,iAngeFert));
  IconVec.push_back(st_buttons(table_lernschema->button_lernschema_geld,iGeld));
  IconVec.push_back(st_buttons(table_lernschema->button_lernschema_waffen,iWaffen));
  IconVec.push_back(st_buttons(table_lernschema->button_ruestung,iRuestung));
  IconVec.push_back(st_buttons(table_lernschema->button_ausruestung,iAusruestung));
  // Steigern
  IconVec.push_back(st_buttons(table_steigern->button_grad_basiswerte,iEigenschaft));
//  IconVec.push_back(st_buttons(table_steigern->eventbox_eppp_steigern,???));
  IconVec.push_back(st_buttons(table_steigern->radiobutton_steigern,iButtonSteigern));
  IconVec.push_back(st_buttons(table_steigern->radiobutton_reduzieren,iButtonReduce));
  IconVec.push_back(st_buttons(table_steigern->radiobutton_verlernen,iButtonVerlernen));
  // Beschreibung
  IconVec.push_back(st_buttons(table_beschreibung->button_grafik,iBildeinfuegen));
  IconVec.push_back(st_buttons(table_beschreibung->button_beschreibung_drucken,iPrint));
  // Ausrüstung
  IconVec.push_back(st_buttons(table_ausruestung->button_ausruestung_loeschen,iDeleteAusr));

  IconVec.push_back(st_buttons(togglebutton_delete_abenteurer_aus_liste,iDeleteA));
  //////////////////////////////////////////////////////////////////////////
  IconVecBin.push_back(st_buttons(eventbox_wizard_aktiv,iStatusWizard));
  IconVecBin.push_back(st_buttons(eventbox_NSC_aktiv,iStatusNPC));
  //////////////////////////////////////////////////////////////////////////
  IconVec.push_back(st_buttons(eventbox_credits,iNotebookCredit));
  IconVec.push_back(st_buttons(eventbox_grundwerte,iNotebookGrundwerte));
  IconVec.push_back(st_buttons(eventbox_lernen,iNotebookLernen));
  IconVec.push_back(st_buttons(eventbox_steigern,iNotebookSteigern));
//future  IconVec.push_back(st_buttons(eventbox_beschreibung,iNotebookBeschreibung));
//future  IconVec.push_back(st_buttons(eventbox_ausruestung,iNotebookAusruestung));
  IconVec.push_back(st_buttons(eventbox_optionen,iNotebookOptionen));
  IconVec.push_back(st_buttons(eventbox_geschichte,iNotebookNEWS));
  IconVec.push_back(st_buttons(eventbox_zufall,iNotebookZufall));

}

