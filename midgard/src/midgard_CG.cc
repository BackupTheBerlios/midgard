// $Id: midgard_CG.cc,v 1.33 2001/06/06 19:06:42 thoma Exp $
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

// generated 2001/2/2 11:29:18 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to midgard_CG.cc_glade

// This file is for your program, I won't touch it again!

#include "midgard_CG.hh"
#include "Window_charakter_beschreibung.hh"
#include "Sprache_auswahl.hh"
#include "Window_herkunft.hh"
#include "Window_hilfe.hh"
#include "Window_Geld_eingeben.hh"
#include "Window_ruestung.hh"
#include "Window_waffe.hh"
#include "Window_Waffenbesitz.hh"
#include "Midgard_Info.hh"

midgard_CG::midgard_CG()
{
  on_neuer_charakter_clicked();
}

void midgard_CG::on_radiobutton_frau_toggled()
{   
  if (radiobutton_frau->get_active()) werte.geschlecht="w";
   else werte.geschlecht="m";
  midgard_CG::fill_typauswahl();
  midgard_CG::fill_typauswahl_2();
  typauswahl->set_history(get_typ_nr());
  typauswahl_2->set_history(get_typ_nr(2)-100);
}

void midgard_CG::on_radiobutton_mann_toggled()
{
  if (radiobutton_mann->get_active()) werte.geschlecht="m";
   else werte.geschlecht="w";
  midgard_CG::fill_typauswahl();
  midgard_CG::fill_typauswahl_2();
  typauswahl->set_history(get_typ_nr());
  typauswahl_2->set_history(get_typ_nr(2)-100);
}

void midgard_CG::show_gtk(int tnr,int typ_1_2)
{
//cout << "show_gtk "<<tnr<<"\t"<<typ_1_2<<"\n";
 if (typ_1_2==1) 
   { typauswahl->set_history(tnr); // Charakterklasse
     if (typen_2_vector.size()==0) typauswahl_2->hide();
   }
 if (typ_1_2==2) 
   { typauswahl_2->show(); 
     typauswahl_2->set_history(tnr-100);
   }
 fertig_typ->set_text(typ.l);     // Charakterklasse im Lernfenster
 if (typ_2.l!="") fertig_typ->set_text(typ.l+"/"+typ_2.l);
 steigern_typ->set_text(typ.l);     // Charakterklasse im Lernfenster
 if (typ_2.l!="") steigern_typ->set_text(typ.l+"/"+typ_2.l);
 
   midgard_CG::zeige_werte(werte,"alle");
   midgard_CG::show_berufe();
   midgard_CG::show_fertigkeiten();
   midgard_CG::show_waffen();
   midgard_CG::show_zauber();


 // Spezialwaffe anzeigen?
 if (typ.z=="n" || typ.s == "Ord") label_spezialwaffe->set_text("Spezialwaffe durch \nselektieren auswählen");
 else label_spezialwaffe->set_text("");

 // Magie anzeigen?
 if (typ.z=="j" || typ.z == "z" || magie_bool) 
   { if (typ.s=="Ma" || typ.s == "eBe") magier_spezialgebiet("show");
     else magier_spezialgebiet("hide");
     table_magier_lernen->show();
     table_magier_steigern->show();
   }
 else 
   { table_magier_lernen->hide();
     table_magier_steigern->hide();
   }
 // KiDo anzeigen?
// if (typ.s=="Kd" || typ.s == "Ny" ) 
 if (kido_bool) 
   { optionmenu_KiDo_Stile->show();
     table_kido_lernen->show();
     table_kido_steigern->show();
   }
 else 
   { optionmenu_KiDo_Stile->hide();
     table_kido_lernen->hide();
     table_kido_steigern->hide();
   }
 // KiDo Stil setzen
 int kido_stil_nr=0;
 if (werte.spezialisierung=="Harte Techniken") kido_stil_nr = 1;
 if (werte.spezialisierung=="Sanfte Techniken") kido_stil_nr = 2;
 if (werte.spezialisierung=="Gemischte Techniken") kido_stil_nr = 3;
 if (kido_stil_nr!=0)
  {   
    optionmenu_KiDo_Stile->set_history(kido_stil_nr);
    checkbutton_KanThaiPan->set_active(true);
    KanThaiPanbool=true;
  }
}

void midgard_CG::on_herkunftsland_clicked()
{
   manage (new Window_herkunft(this));
}
void midgard_CG::herkunft_uebernehmen(const string& s)
{
   werte.herkunft = s;
   midgard_CG::zeige_werte(werte,"alle");
   midgard_CG::get_Ausnahmen();
}


void midgard_CG::on_muttersprache_clicked()
{   
   manage (new Sprache_auswahl(this,"Sprache"));
}



void midgard_CG::on_charakter_beschreibung_clicked()
{   
  manage(new Window_charakter_beschreibung(this,werte.beschreibung)); 
}   
void midgard_CG::charakter_beschreibung_uebernehmen(const string& b)
{
  werte.beschreibung=b;  
  on_speichern_clicked();
}
void midgard_CG::charakter_beschreibung_drucken(const string& b)
{
  werte.beschreibung=b;  
  on_speichern_clicked();
  midgard_CG::latex_beschreibung_drucken();
}

void midgard_CG::on_button_hilfe_clicked()
{
  manage(new Window_hilfe()); 
}
void midgard_CG::on_button_info_clicked()
{   
  manage(new Midgard_Info());
}


void midgard_CG::on_button_geld_s_clicked()
{
  manage (new  Window_Geld_eingeben(this, werte));
}
void midgard_CG::on_button_ruestung_s_clicked()
{
  manage (new Window_ruestung(werte,this));
}
void midgard_CG::on_button_waffen_s_clicked()
{
  manage (new Window_Waffenbesitz(this,vec_waffen,waffe_besitz,werte));
}



/*****************************************************************/

void midgard_CG::on_neuer_charakter_clicked()
{
   button_abg_werte->set_sensitive(false);
   button_herkunft->set_sensitive(false);
   button_sprache->set_sensitive(false);
   button_beschreibung->set_sensitive(false);
//   frame_steigern->set_sensitive(false);
//   frame_lernschema->set_sensitive(false);
   frame_steigern->hide();//set_sensitive(false);
   frame_lernschema->hide();//set_sensitive(false);

   button_geld_waffen->set_sensitive(false);
   button_ruestung->set_sensitive(false);

   hbox_beruf->set_sensitive(false);
   table_beruf->set_sensitive(false);
   hbox_fertigkeit->set_sensitive(false);
   table_fertigkeit->set_sensitive(false);
   hbox_waffen->set_sensitive(false);
   table_waffen->set_sensitive(false);
   hbox_zauber->set_sensitive(false);
   table_magier_lernen->set_sensitive(false);
   hbox_kido->set_sensitive(false);
   table_kido_lernen->set_sensitive(false);


   button_beruf_erfolgswert->set_sensitive(false);
   button_fertigkeiten->set_sensitive(false);
   button_kido_auswahl->set_sensitive(false);       

   vec_fertigkeiten.clear();
   vec_an_fertigkeit.clear();
   vec_waffen.clear();
   waffe_besitz.clear();
   vec_zauber.clear();
   vec_zaubermittel.clear();
   vec_kido.clear();
   vec_beruf.clear();
   vec_sprachen.clear();
   vec_schriften.clear();
   zauber.clear();
   werte.clear();
   lernpunkte.clear();
   typ.clear();
   typ_2.clear();
   typen_vector.clear();
   typen_2_vector.clear();
   waffen_grundkenntnisse.clear();
   midgard_CG::zeige_lernpunkte();
   midgard_CG::zeige_werte(werte,"alle");
   berufe_clist->clear();
   waffen_clist->clear();
   fertigkeiten_clist->clear();
   zauber_clist->clear();
   clist_kido->clear();
   steigern_fert_clist_alt->clear();
   steigern_fert_clist_neu->clear();
   steigern_waffen_clist_alt->clear();
   steigern_waffen_clist_neu->clear();
   grundkenntnisse_clist_alt->clear();
   grundkenntnisse_clist_neu->clear();
   steigern_zauber_clist_alt->clear();
   steigern_zauber_clist_neu->clear();
   clist_zaubermittel_alt->clear();
   clist_zaubermittel_neu->clear();
   steigern_kido_clist_alt->clear();
   steigern_kido_clist_neu->clear();
   clist_steigern_sprachen_alt->clear();
   clist_steigern_sprachen_neu->clear();
   clist_steigern_schrift_alt->clear();
   clist_steigern_schrift_neu->clear();
   
 kido_bool=false;
 magie_bool=false;
 werte.version="Erschaffung";
 midgard_CG::fill_typauswahl();
 midgard_CG::fill_spezies();
 midgard_CG::spezieswahl_button();
 midgard_CG::typauswahl_button(-1);
 show_gtk(get_typ_nr());
}



void midgard_CG::on_schliessen_CG_clicked()
{
  system("rm midgard_tmp_*");
  Gtk::Main::instance()->quit();
}

