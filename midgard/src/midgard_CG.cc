// $Id: midgard_CG.cc,v 1.51 2001/08/13 20:08:24 thoma Exp $
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
#include "class_Ausnahmen.hh"

midgard_CG::midgard_CG()
{
  on_neuer_charakter_clicked();
  set_tree_titles();
}

void midgard_CG::set_tree_titles()
{
 std::vector<string> alte_fert;
 alte_fert.push_back("Fertigkeit");
 alte_fert.push_back("Wert");
 alte_fert.push_back("Steigern\n(nächste Stufe)");
 alte_fert.push_back("Reduzieren\n(eine Stufe)");
 alte_fert.push_back("Verlernen");
 alte_fert_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 alte_fert_tree->setTitles(alte_fert);
 std::vector<string> neue_fert;
 neue_fert.push_back("Fertigkeit");
 neue_fert.push_back("Wert");
 neue_fert.push_back("Lernkosten");
 neue_fert.push_back("Art");
 neue_fert.push_back("Vorraussetzungen");
 neue_fert_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_fert_tree->setTitles(neue_fert);

 std::vector<string> alte_waffen;
 alte_waffen.push_back("Waffe");
 alte_waffen.push_back("Wert");
 alte_waffen.push_back("Steigern\n(nächste Stufe)");
 alte_waffen.push_back("Reduzieren\n(eine Stufe)");
 alte_waffen_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 alte_waffen_tree->setTitles(alte_waffen);
 std::vector<string> neue_waffen;
 neue_waffen.push_back("Waffe");
 neue_waffen.push_back("Wert");
 neue_waffen.push_back("Vorraussetzung");
 neue_waffen_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_waffen_tree->setTitles(neue_waffen);

 std::vector<string> alte_grund;
 alte_grund.push_back("Grundkenntnisse");
 alte_grund_tree->setTitles(alte_grund);
 alte_grund_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 std::vector<string> neue_grund;
 neue_grund.push_back("Grundkenntnisse");
 neue_grund.push_back("Kosten");
 neue_grund_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_grund_tree->setTitles(neue_grund);
 
 std::vector<string> alte_zauber;
 alte_zauber.push_back("Name");
 alte_zauber.push_back("Stufe");
 alte_zauber.push_back("Ursprung");
 alte_zauber.push_back("Lernkosten");
 alte_zauber_tree->setTitles(alte_zauber);
 alte_zauber_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 std::vector<string> neue_zauber;
 neue_zauber.push_back("Name");
 neue_zauber.push_back("Stufe");
 neue_zauber.push_back("Ursprung");
 neue_zauber.push_back("Lernkosten");
 neue_zauber.push_back("Art");
 neue_zauber_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_zauber_tree->setTitles(neue_zauber);

 std::vector<string> alte_zaubermittel;
 alte_zaubermittel.push_back("Stufe");
 alte_zaubermittel.push_back("Name");
 alte_zaubermittel.push_back("Art");
 alte_zaubermittel.push_back("Kosten");
 alte_zaubermittel_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 alte_zaubermittel_tree->setTitles(alte_zaubermittel); 
 std::vector<string> neue_zaubermittel;
 neue_zaubermittel.push_back("Stufe");
 neue_zaubermittel.push_back("Name");
 neue_zaubermittel.push_back("Art");
 neue_zaubermittel.push_back("Kosten");
 neue_zaubermittel.push_back("Preis");
 neue_zaubermittel.push_back("Zeitaufwand");
 neue_zaubermittel_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_zaubermittel_tree->setTitles(neue_zaubermittel); 

 std::vector<string> kido;
 kido.push_back("HoHo");
 kido.push_back("Technik");
 kido.push_back("Stufe");
 kido.push_back("AP");
 kido.push_back("Kosten");
 kido.push_back("Stil");
 alte_kido_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 alte_kido_tree->setTitles(kido);
 neue_kido_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_kido_tree->setTitles(kido);

 std::vector<string> alte_sprachen;
 alte_sprachen.push_back("Sprache");
 alte_sprachen.push_back("Wert");
 alte_sprachen.push_back("Steigern\n(nächste Stufe)");
 alte_sprachen.push_back("Reduzieren\n(eine Stufe)");
 alte_sprachen.push_back("Verlernen");
 alte_sprache_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 alte_sprache_tree->setTitles(alte_sprachen);
 std::vector<string> neue_sprachen;
 neue_sprachen.push_back("Sprache");
 neue_sprachen.push_back("Urschrift");
 neue_sprachen.push_back("Lernkosten");
 neue_sprache_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_sprache_tree->setTitles(neue_sprachen);

 std::vector<string> schrift;
 schrift.push_back("Urschrift");
 schrift.push_back("Art der Schrift");
 schrift.push_back("Kosten");
 alte_schrift_tree->set_value_data(reinterpret_cast<gpointer>('A'));
 alte_schrift_tree->setTitles(schrift);
 neue_schrift_tree->set_value_data(reinterpret_cast<gpointer>('N'));
 neue_schrift_tree->setTitles(schrift);

}

void midgard_CG::on_radiobutton_frau_toggled()
{   
  if (radiobutton_frau->get_active()) Werte.Geschlecht()="w";
   else Werte.set_Geschlecht("m");
  midgard_CG::fill_typauswahl();
  midgard_CG::fill_typauswahl_2();
  typauswahl->set_history(Typ.Nr_Optionmenu());
  typauswahl_2->set_history(Typ2.Nr_Optionmenu());
}

void midgard_CG::on_radiobutton_mann_toggled()
{
  if (radiobutton_mann->get_active()) Werte.Geschlecht()="m";
   else Werte.set_Geschlecht("w");
  midgard_CG::fill_typauswahl();
  midgard_CG::fill_typauswahl_2();
  typauswahl->set_history(Typ.Nr_Optionmenu());
  typauswahl_2->set_history(Typ2.Nr_Optionmenu());
}

//void midgard_CG::show_gtk(int tnr,int typ_1_2)
void midgard_CG::show_gtk()
{
  typauswahl->set_history(Typ.Nr_Optionmenu());
  if (Typ2.Short()=="") typauswahl_2->hide();
  else
   { typauswahl_2->show(); 
     typauswahl_2->set_history(Typ2.Nr_Optionmenu());
   }
 fertig_typ->set_text(Typ.Name());     // Charakterklasse im Lernfenster
 if (Typ2.Name()!="") fertig_typ->set_text(Typ.Name()+"/"+Typ2.Name());
 steigern_typ->set_text(Typ.Name());     // Charakterklasse im Lernfenster
 if (Typ2.Name()!="") steigern_typ->set_text(Typ.Name()+"/"+Typ2.Name());
 
   midgard_CG::zeige_werte(Werte);
   midgard_CG::show_berufe();
   midgard_CG::show_fertigkeiten();
   midgard_CG::show_waffen();
   midgard_CG::show_zauber();


 // Spezialwaffe anzeigen?
 if (Typ.Zaubern()=="n" || Typ.Short() == "Ord") label_spezialwaffe->set_text("Spezialwaffe durch \nselektieren auswählen");
 else label_spezialwaffe->set_text("");

 // Magie anzeigen?
 if (Typ.Zaubern()=="j" || Typ.Zaubern() == "z" || magie_bool) 
   { if (Typ.Short()=="Ma" || Typ.Short() == "eBe") magier_spezialgebiet("show");
     else magier_spezialgebiet("hide");
     table_magier_lernen->show();
     table_magier_steigern->show();
   }
 else 
   { table_magier_lernen->hide();
     table_magier_steigern->hide();
   }
 // KiDo anzeigen?
// if (Typ.Short()=="Kd" || Typ.Short() == "Ny" ) 
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
 if (Werte.Spezialisierung()=="Harte Techniken") kido_stil_nr = 1;
 if (Werte.Spezialisierung()=="Sanfte Techniken") kido_stil_nr = 2;
 if (Werte.Spezialisierung()=="Gemischte Techniken") kido_stil_nr = 3;
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
void midgard_CG::herkunft_uebernehmen(const std::string& s)
{
   Werte.set_Herkunft(s);
   zeige_werte(Werte);
   clear_Ausnahmen();
}


void midgard_CG::on_muttersprache_clicked()
{   
   manage (new Sprache_auswahl(this,"Sprache"));
}



void midgard_CG::on_charakter_beschreibung_clicked()
{   
  manage(new Window_charakter_beschreibung(this,Werte.Beschreibung())); 
}   
void midgard_CG::charakter_beschreibung_uebernehmen(const std::string& b)
{
  Werte.set_Beschreibung(b);
  on_speichern_clicked();
}
void midgard_CG::charakter_beschreibung_drucken(const std::string& b)
{
  Werte.set_Beschreibung(b);
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
  manage (new  Window_Geld_eingeben(this, Werte));
}
void midgard_CG::on_button_ruestung_s_clicked()
{
  manage (new Window_ruestung(Werte,this));
}
void midgard_CG::on_button_waffen_s_clicked()
{
  manage (new Window_Waffenbesitz(this,vec_Waffen,vec_Waffen_besitz,Werte));
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

   vec_Fertigkeiten.clear();
   vec_an_Fertigkeit.clear();
   vec_Waffen.clear();
   vec_Waffen_besitz.clear();
   vec_Kido.clear();
   vec_Beruf.clear();
   vec_Sprachen.clear();
   vec_Schriften.clear();
   vec_Zauber.clear();
   vec_Zaubermittel.clear();
   Werte.clear();
   lernpunkte.clear();
   Typ.clear();
   Typ2.clear();
   vec_Typen.clear();
   vec_Typen_2.clear();
   waffen_grundkenntnisse.clear();
   zeige_lernpunkte();
   zeige_werte(Werte);
   berufe_clist->clear();
   waffen_clist->clear();
   fertigkeiten_clist->clear();
   zauber_clist->clear();
   clist_kido->clear();
   alte_fert_tree->clear();
   neue_fert_tree->clear();
   alte_waffen_tree->clear();
   neue_waffen_tree->clear();
   alte_grund_tree->clear();
   neue_grund_tree->clear();
   alte_zauber_tree->clear();
   neue_zauber_tree->clear();
   alte_zaubermittel_tree->clear();
   neue_zaubermittel_tree->clear();
   alte_kido_tree->clear();
   neue_kido_tree->clear();
   alte_sprache_tree->clear();
   neue_sprache_tree->clear();
   alte_schrift_tree->clear();
   neue_schrift_tree->clear();
   
   Originalbool=true;  checkbutton_original->set_active(true);
   Infobool=true;      checkbutton_original->set_active(true);
   Albabool=false;      checkbutton_Alba->set_active(false);
   Escharbool=false;      checkbutton_Eschar->set_active(false);
   Rawindrabool=false;      checkbutton_Rawindra->set_active(false);
   KanThaiPanbool=false;      checkbutton_KanThaiPan->set_active(false);
   Waelandbool=false;      checkbutton_Waeland->set_active(false);
   Nahuatlanbool=false;      checkbutton_Nahuatlan->set_active(false);
   HDbool=false;             checkbutton_HD->set_active(false);
   BRbool=false;             checkbutton_BR->set_active(false);

 on_checkbutton_original_toggled();
 kido_bool=false;
 magie_bool=false;
 Werte.set_Namen("","","Erschaffung");
 midgard_CG::fill_typauswahl();
 midgard_CG::fill_spezies();
 midgard_CG::spezieswahl_button();
 midgard_CG::typauswahl_button();
 show_gtk();

 // Verschwindet irgendwann
 checkbutton_Kuestenstaaten->set_sensitive(false);
 checkbutton_Nahuatlan->set_sensitive(false);
 checkbutton_Waeland->set_sensitive(false);

}

void midgard_CG::clear_Ausnahmen()
{
//  Ausnahmen A(werte,Typ,Typ2,vec_Beruf);
  Ausnahmen::clear();

//  vec_Ausnahmen=A.get_Ausnahmen(werte,Typ,Typ2,vec_Beruf); 
}

void midgard_CG::on_schliessen_CG_clicked()
{
  system("rm midgard_tmp_*");
  Gtk::Main::instance()->quit();
}

