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
 midgard_CG::fill_typauswahl();
 midgard_CG::fill_spezies();
 midgard_CG::typauswahl_button();
 werte.version="Erschaffung";
}

void midgard_CG::spezieswahl_button()
{
 int ityp = int(optionmenu_spezies->get_menu()->get_active()->get_user_data());
 werte.spezies = spezies_vector[ityp];
}

void midgard_CG::typauswahl_button()
{
//cout << typ.nr<<"\n";
 get_typ(typ);
//cout << typ.nr<<"\n";
 fertig_typ->set_text(typ.l);

 // Spezialwaffe anzeigen?
 if (typ.z=="n" || typ.s == "Ord") label_spezialwaffe->set_text("Spezialwaffe durch \nselektieren auswählen");
 else label_spezialwaffe->set_text("");

 // Magie anzeigen?
 if (typ.z=="j" || typ.z == "z") 
   { if (typ.s=="Ma") option_magier_spezialgebiet->show();
     else option_magier_spezialgebiet->hide();
     table_magier_lernen->show();
     table_magier_steigern->show();
   }
 else 
   { table_magier_lernen->hide();
     table_magier_steigern->hide();
   }

 // KiDo anzeigen?
 if (typ.s=="Kd" || typ.s == "Ny") 
   { optionmenu_KiDo_Stile->show();
     table_kido_lernen->show();
     table_kido_steigern->show();
   }
 else 
   { optionmenu_KiDo_Stile->hide();
     table_kido_lernen->hide();
     table_kido_steigern->hide();
   }

}

void midgard_CG::on_herkunftsland_clicked()
{
   manage (new Window_herkunft(this));
}
void midgard_CG::herkunft_uebernehmen(string s)
{
   werte.herkunft = s;
   midgard_CG::zeige_werte(werte,"alle");
}


void midgard_CG::on_muttersprache_clicked()
{   
   manage (new Sprache_auswahl(this,"Sprache"));
}



void midgard_CG::on_charakter_beschreibung_clicked()
{   
  manage(new Window_charakter_beschreibung(this,werte.beschreibung)); 
}   
void midgard_CG::charakter_beschreibung_uebernehmen(string b)
{
  werte.beschreibung=b;  
}
void midgard_CG::charakter_beschreibung_drucken(string b)
{
  werte.beschreibung=b;  
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
   vec_fertigkeiten.clear();
   vec_an_fertigkeit.clear();
   vec_waffen.clear();
   waffe_besitz.clear();
   vec_zauber.clear();
   vec_kido.clear();
   vec_beruf.clear();
   vec_sprachen.clear();
   vec_schriften.clear();
   zauber.clear();
   werte.clear();
   lernpunkte.clear();
   typ.clear();
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
   steigern_kido_clist_alt->clear();
   steigern_kido_clist_neu->clear();
   clist_steigern_sprachen_alt->clear();
   clist_steigern_sprachen_neu->clear();
   clist_steigern_schrift_alt->clear();
   clist_steigern_schrift_neu->clear();

   midgard_CG::typauswahl_button();
   werte.version="Erschaffung";
   optionmenu_spezies->get_menu()->set_active(0);
   optionmenu_spezies->get_menu()->deactivate();

}



void midgard_CG::on_schliessen_CG_clicked()
{
  system("rm midgard_tmp_*");
  Gtk::Main::instance()->quit();
}

