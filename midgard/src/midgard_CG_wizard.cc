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
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, U
 */

#include "midgard_CG.hh"
#include <cstring>

void midgard_CG::set_wizard(std::string s)
{
  label_wizard->show();
  label_wizard->set_text(s);
}

void midgard_CG::on_neuer_abenteurer_mit_wizard_activate()
{
  on_wizard_starten_activate();
}

void midgard_CG::on_wizard_starten_activate()
{
 on_neuer_charakter_clicked();
 getChar().proxies.werte_eingeben=false;
 getChar().getWizard().restart(getAben());
}

void midgard_CG::on_wizard_beenden_activate()
{  label_wizard->hide();
// show_wizard_active(false);
}

static const char * wizard_beschreibung[Wizard::MAXSTEPS];
static int wizard_page[Wizard::MAXSTEPS];

static void fill_texte()
{  if (wizard_beschreibung[Wizard::SPEZIES]) return;
   wizard_beschreibung[Wizard::SPEZIES]=
      "Spezies auswählen (oder Eigenschaften auswürfeln)";
   wizard_beschreibung[Wizard::GRUNDWERTE]=
                          "Eigenschaften auswürfeln";
   wizard_beschreibung[Wizard::GESCHLECHT]=
                          "Geschlecht oder Abenteuertyp auswählen";
   wizard_beschreibung[Wizard::TYP]=
                          "Abenteurertyp wählen";
   wizard_beschreibung[Wizard::STADTLAND]=
                          "Stadt oder Land wählen (oder abgeleitete Werte wärfeln)";
   wizard_beschreibung[Wizard::ABGELEITETEWERTE]=
                          "Abgeleitete Werte wärfeln";
   wizard_beschreibung[Wizard::LERNSCHEMA_SEITE]=
                          "Auf die 'Lernschema'-Seite umblättern";
   wizard_beschreibung[Wizard::HERKUNFT]=
                          "Herkunftsland wählen";
   wizard_beschreibung[Wizard::UEBERLEBEN]=
                          "In welchem Geländetyp wird 'überleben' als universelle Fertigkeit beherrscht?";
   wizard_beschreibung[Wizard::ANGEBORENEFERTIGKEITEN]=
                          "Angeborene Fertigkeiten erwürfeln";
   wizard_beschreibung[Wizard::LERNPUNKTE]=
                          "Lernpunkte auswürfeln";
   wizard_beschreibung[Wizard::WAEHLEN]=
                          "Jetzt Fertigkeiten, Waffen und ev. Zauber in beliebiger"
                          " Reinfolge lernen (anklicken) bis alle Lernpunkte"
                          " verbraucht sind und anschließend den Beruf wählen.";
   wizard_beschreibung[Wizard::BERUF1]=
                          "Fertigkeit auswählen, die aufgrund der Berufswahl"
                          " gelernt werden kann, danach das Geld auswürfeln.";
   wizard_beschreibung[Wizard::BERUF]=
                          "Berufsfertigkeit aus Liste wählen";
   wizard_beschreibung[Wizard::GELD]=
                          "Geld auswürfeln";
   wizard_beschreibung[Wizard::WAFFEN]=
                          "Waffen auswürfeln";
   wizard_beschreibung[Wizard::RUESTUNG]=
                          "Rüstung auswürfeln";
   wizard_beschreibung[Wizard::AUSRUESTUNG]=
                          "Ausrüstung auswürfeln";
   wizard_beschreibung[Wizard::SPEZIALWAFFE]=
                          "Spezialwaffe wählen (anklicken)";
   wizard_beschreibung[Wizard::SPEZIALGEBIET]=
                          "Magier sollten ein Spezialgebiet wählen (das kann aber auch später geschehen)";
   wizard_beschreibung[Wizard::NAMEN]=
                          "Namen vergeben (Eingabe mit 'Enter' abschließen)";
   wizard_beschreibung[Wizard::SPEICHERN]=
                          "Bitte neu erwürfelten Abenteurer abspeichern";
   for (unsigned i=0;i<Wizard::MAXSTEPS;++i)
      wizard_page[i]=midgard_CG::NOPAGE;
   wizard_page[Wizard::SPEZIES]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::GRUNDWERTE]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::GESCHLECHT]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::TYP]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::STADTLAND]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::ABGELEITETEWERTE]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::LERNSCHEMA_SEITE]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::HERKUNFT]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::UEBERLEBEN]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::ANGEBORENEFERTIGKEITEN]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::LERNPUNKTE]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::WAEHLEN]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::BERUF1]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::BERUF]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::GELD]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::WAFFEN]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::RUESTUNG]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::AUSRUESTUNG]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::SPEZIALWAFFE]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::SPEZIALGEBIET]=midgard_CG::PAGE_LERNEN;
   wizard_page[Wizard::NAMEN]=midgard_CG::PAGE_GRUNDWERTE;
   wizard_page[Wizard::SPEICHERN]=midgard_CG::PAGE_GRUNDWERTE;
}

void midgard_CG::wizard_changed(gpointer x)
{  if (aktiver.proxies.wizard.matches(x))
   {  if (aktiver.getWizard().getMode().Value()==Wizard::Aus)
      {  label_wizard->hide();
         // alles sensitiv machen
      }
      else if (aktiver.getWizard().getMode().Value()>=Wizard::Hints)
      {  if (!wizard_beschreibung[Wizard::SPEZIES]) fill_texte();
         label_wizard->set_text(wizard_beschreibung[aktiver.proxies.wizard.Value()]
         		?wizard_beschreibung[aktiver.proxies.wizard.Value()]
         		:"");
         label_wizard->show();
      }
      // sensitiv?
      // aktiv mithelfen?
      if (aktiver.getWizard().getMode().Value()==Wizard::Aktiv)
      {  Wizard::esteps e=aktiver.proxies.wizard.Value();

	 if(e==Wizard::FERTIG)
	    on_wizard_beenden_activate();
#if 0	    
	 else if(e==Wizard::HERKUNFT)
	    table_lernschema->on_herkunftsland_clicked();
	 else if(e==Wizard::SPEZIALWAFFE)
            table_lernschema->togglebutton_spezialwaffe->set_active(true);
         else if(e==Wizard::SPEZIALGEBIET)
            table_lernschema->frame_lernpunkte->set_sensitive(true);
	 else if(e==Wizard::NAMEN)
         {  table_grundwerte->edit_werte=true;
            table_lernschema->frame_lernpunkte->set_sensitive(false);
//        table_grundwerte->entry_nameC->grab_focus();
      }
#endif
	 else if(e==Wizard::SPEICHERN) xml_export_auswahl();
      }
   }
}
