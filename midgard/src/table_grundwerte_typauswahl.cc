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
#include "Window_doppelcharaktere.hh"
#include <Gtk_OStream.h>
#include <SelectMatching.h>

static bool block;

void table_grundwerte::fill_typauswahl()
{
  if(!hauptfenster) return;
  fill_typauswahl_fill(1);
//  typauswahl->get_menu()->deactivate.connect(SigC::slot(this, &table_grundwerte::typauswahl_button));
  if (!hauptfenster->getCChar().getVTyp().empty()) 
   {
//     Gtk::Menu_Helpers::SelectMatching(*typauswahl,hauptfenster->getCChar().CTyp1());
     combo_typ->get_entry()->set_text(hauptfenster->getCChar().CTyp1()->Name(hauptfenster->getCWerte().Geschlecht()));
   }
}

void table_grundwerte::fill_typauswahl_2()
{
  if(!hauptfenster) return;
  fill_typauswahl_fill(2);
//  typauswahl_2->get_menu()->deactivate.connect(SigC::slot(this, &table_grundwerte::typauswahl_2_button));
//  if (hauptfenster->getCChar().getVTyp().size()>1) Gtk::Menu_Helpers::SelectMatching(*typauswahl_2,hauptfenster->getCChar().CTyp2());
  combo_typ2->get_entry()->set_text(hauptfenster->getCChar().CTyp2()->Name(hauptfenster->getCWerte().Geschlecht()));
}

void table_grundwerte::fill_typauswahl_fill(int typ_1_2)
{
//  Gtk::OStream t_((typ_1_2==1) ? typauswahl : typauswahl_2 ); 
  const std::vector<cH_Typen> T=hauptfenster->getCDatabase().Typen;
//  t_<<"Typauswahl\n";
  std::list<std::string> L;
//  L.push_back("Typ wählen");
  for(std::vector<cH_Typen>::const_iterator i=T.begin();i!=T.end();++i)
   {
     if (hauptfenster->getCWerte().Spezies()->Name()=="Mensch" || hauptfenster->getCWerte().Spezies()->Typ_erlaubt((*i)->Short()))
       if (hauptfenster->region_check((*i)->Region()) && hauptfenster->nsc_check((*i)->NSC_only()))
         {
/*
           if((*i)->Mindestwerte(hauptfenster->getCWerte())) 
                  t_ << (*i)->Name(hauptfenster->getCWerte().Geschlecht());
           else   t_ << "("<<(*i)->Name(hauptfenster->getCWerte().Geschlecht())<<")";
           t_.flush((*i)->ref(),&HandleContent::unref);
*/         
           if((*i)->Mindestwerte(hauptfenster->getCWerte())) 
              L.push_back((*i)->Name(hauptfenster->getCWerte().Geschlecht()));
           else
              L.push_back("("+(*i)->Name(hauptfenster->getCWerte().Geschlecht())+")");
         }
   }
 block=true;
 if(typ_1_2==1) combo_typ->set_popdown_strings(L);
 else           combo_typ2->set_popdown_strings(L);
 block=false;
}

void table_grundwerte::on_combo_typ_activate()
{
  button_abg_werte->grab_focus();
//  typauswahl_button();
}

gint table_grundwerte::on_combo_typ__focus_out_event(GdkEventFocus *ev)
{
  typauswahl_button();
  return false;
}

void table_grundwerte::typauswahl_button()
{
 std::string typ=combo_typ->get_entry()->get_text();
 if(!Typen::get_Typ_from_long(hauptfenster->getCDatabase().Typen,typ))
   return;
 hauptfenster->Char.reset();
 hauptfenster->clear_gtk();

 if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::TYP);
// cH_Typen ptr = static_cast<Typen*>(typauswahl->get_menu()->get_active()->get_user_data());

// cH_Typen ptr = cH_Typen(Typen::get_Typ_from_long(hauptfenster->getCDatabase().Typen,combo_typ->get_entry()->get_text()));
 hauptfenster->getChar().setTyp1(cH_Typen(typ));

// if (Typ[0]->Short()=="dBe" || Typ[0]->Short()=="eBe") angeborene_zauber();

 if(hauptfenster->getCWerte().Spezies()->Land()) 
   {
     radiobutton_land->set_active(true);
     radiobutton_stadt->set_sensitive(false);
     radiobutton_land->set_sensitive(true);
   }
 else if(!hauptfenster->getCChar().CTyp1()->Stadt())
   {
     radiobutton_land->set_active(true);
     radiobutton_land->set_sensitive(true);
     radiobutton_stadt->set_sensitive(false);
   }
 else if(!hauptfenster->getCChar().CTyp1()->Land())
   {
     radiobutton_stadt->set_active(true);
     radiobutton_stadt->set_sensitive(true);
     radiobutton_land->set_sensitive(false);
   }
 else
   {
     radiobutton_stadt->set_sensitive(true);
     radiobutton_land->set_sensitive(true);
   }
// if(radiobutton_stadt->sensitive() && radiobutton_land->sensitive())
//      radiobutton_stadt->grab_focus();
// else 
//  button_abg_werte->grab_focus();
}


void table_grundwerte::on_combo_typ2_activate()
{
  button_abg_werte->grab_focus();
//  typauswahl_2_button();
}

gint table_grundwerte::on_combo_typ2_focus_out_event(GdkEventFocus *ev)
{
  typauswahl_2_button();
  return false;
}

void table_grundwerte::typauswahl_2_button()
{
 std::string typ=combo_typ2->get_entry()->get_text();
 if(!Typen::get_Typ_from_long(hauptfenster->getCDatabase().Typen,typ))
   return;
// cH_Typen ptr = static_cast<Typen*>(typauswahl_2->get_menu()->get_active()->get_user_data());
// hauptfenster->getChar().setTyp2(ptr);
 hauptfenster->getChar().setTyp2(cH_Typen(typ));

// hauptfenster->show_gtk();
// if (Typ[1]->Short()=="dBe" || Typ[1]->Short()=="eBe") angeborene_zauber();
}


void table_grundwerte::fill_spezies()
{
  std::vector<std::string> L;
//  { Gtk::OStream t_(optionmenu_spezies);
    for(vector<cH_Spezies>::const_iterator i=hauptfenster->getDatabase().Spezies.begin();i!=hauptfenster->getDatabase().Spezies.end();++i)
     {
       if (!hauptfenster->nsc_check((*i)->NSC_only())) continue;
//       t_ << (*i)->Name();
//       t_.flush((*i)->ref(),&HandleContent::unref);
       L.push_back((*i)->Name());
     }
//  }
//  optionmenu_spezies->get_menu()->deactivate.connect(SigC::slot(static_cast<class table_grundwerte*>(this), &table_grundwerte::spezieswahl_button));
//  Gtk::Menu_Helpers::SelectMatching(*optionmenu_spezies,hauptfenster->getCWerte().Spezies());
//  combo_typ2->hide();

  combo_spezies->set_popdown_strings(L);

}

void table_grundwerte::on_combo_spezies_activate()
{
 button_grundwerte->grab_focus();
}

gint table_grundwerte::on_combo_spezies_focus_out_event(GdkEventFocus *ev)
{
  spezieswahl_button();
  return false;
}



void table_grundwerte::spezieswahl_button()
{
 std::string spezies=combo_spezies->get_entry()->get_text();
 bool ok=false;
 for(vector<cH_Spezies>::const_iterator i=hauptfenster->getDatabase().Spezies.begin();i!=hauptfenster->getDatabase().Spezies.end();++i)
   {
     if((*i)->Name()==spezies)
      {
        ok=true;
        hauptfenster->getWerte().clear();
        hauptfenster->getWerte().setSpezies(*i);
      }
   }
 if(!ok) return;
// hauptfenster->getWerte().clear();
// hauptfenster->zeige_werte();
// cH_Spezies ptr = static_cast<Spezies*>(optionmenu_spezies->get_menu()->get_active()->get_user_data());
// hauptfenster->getWerte().setSpezies(ptr);

 fill_typauswahl();
 typauswahl_button();

 if (hauptfenster->getCWerte().Spezies()->Name()=="Elf")
   manage (new Window_doppelcharaktere(this));

// typauswahl_2->hide();
// combo_typ2->hide();
// hauptfenster->getChar().setTyp2(cH_Typen());
 if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::SPEZIES);
}

void table_grundwerte::on_radiobutton_stadt_land_toggled()
{
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::STADTLAND);

  if(radiobutton_stadt->get_active()) hauptfenster->getWerte().setStadt_Land("Stadt");   
  else                                hauptfenster->getWerte().setStadt_Land("Land");   
}


void table_grundwerte::doppelcharaktere()
{
   if(!hauptfenster) return;
   fill_typauswahl_2();
//   typauswahl_2->show();
   combo_typ2->show();
//   typauswahl_2_button();
//   magie_bool=true;
}

void table_grundwerte::on_radiobutton_frau_toggled()
{ on_radiobutton_mann_toggled(); }
void table_grundwerte::on_radiobutton_mann_toggled()
{
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::GESCHLECHT);
  std::string oldG=hauptfenster->getCWerte().Geschlecht();
  if (radiobutton_mann->get_active()) hauptfenster->getWerte().setGeschlecht("m");
  else hauptfenster->getWerte().setGeschlecht("w");
  if(oldG!=hauptfenster->getCWerte().Geschlecht() && hauptfenster->getCWerte().Groesse() && hauptfenster->getCWerte().Spezies()->Name()=="Mensch")
   {
     if( hauptfenster->getCWerte().Geschlecht()=="w") hauptfenster->getWerte().setGroesse(hauptfenster->getCWerte().Groesse()-10);
     if( hauptfenster->getCWerte().Geschlecht()=="m") hauptfenster->getWerte().setGroesse(hauptfenster->getCWerte().Groesse()+10);
   }
  if(oldG!=hauptfenster->getCWerte().Geschlecht() && hauptfenster->getCWerte().Gewicht() && hauptfenster->getCWerte().Spezies()->Name()=="Mensch")
   {
     if( hauptfenster->getCWerte().Geschlecht()=="w") hauptfenster->getWerte().setGewicht(hauptfenster->getCWerte().Gewicht()-4);
     if( hauptfenster->getCWerte().Geschlecht()=="m") hauptfenster->getWerte().setGewicht(hauptfenster->getCWerte().Gewicht()+4);
   }
  fill_typauswahl();
  fill_typauswahl_2();
  hauptfenster->zeige_werte();
}

void table_grundwerte::kaempfer_lernt_zaubern()
{
  if(!hauptfenster) return;
  doppelcharaktere();
  hauptfenster->InfoFenster->AppendShow("Jetzt unter 'Grundwerte' die zweite Charkakterklasse wählen\n",WindowInfo::None);
  if (hauptfenster->getCWerte().Zaubern_wert()==2) 
      hauptfenster->getWerte().setZaubern_wert(10);
  //   cH_MidgardBasicElement MBE=new Fertigkeit(*cH_Fertigkeit("Zaubern"));
  //  MidgardBasicElement::move_element(list_Fertigkeit_neu,list_Fertigkeit,MBE);
  //  fertigkeiten_zeigen();
}
         
         
