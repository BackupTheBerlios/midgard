/*  Copyright (C) 2001 Malte Thoma
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
#include "WindowInfo.hh"
//#include "Ausnahmen.hh"
#include "class_SimpleTree.hh"
#include "Pflicht.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_fertigkeiten_laden_clicked()
{
  list_Fertigkeit_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   { cH_Fertigkeit f(*i);
     if ((*i)->ist_gelernt(list_Fertigkeit) && f->Name()!="Landeskunde") continue ;
     if (f->Name()=="Sprache" || f->Name()=="Schreiben" || f->Name()=="KiDo-Technik") continue;
     if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name())) continue;
     if ((*i)->ist_lernbar(Typ,f->get_MapTyp()))
       if (region_check(f->Region()) )
        if (f->Voraussetzungen(Werte)) 
         {
            f->set_Erfolgswert(f->Anfangswert());
//            list_Fertigkeit_neu.push_back(*i);
            list_Fertigkeit_neu.push_back(new Fertigkeit(*f));
         }
   }
 fertigkeiten_zeigen();
}

void midgard_CG::fertigkeiten_zeigen()
{
 zeige_werte(Werte);
 on_speichern_clicked();
 MidgardBasicElement::show_list_in_tree(list_Fertigkeit_neu,neue_fert_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Fertigkeit    ,alte_fert_tree,Werte,Typ,Database.ausnahmen);
}


void midgard_CG::on_leaf_selected_alte_fert(cH_RowDataBase d)
{  
 MidgardBasicElement_leaf_alt(d);
/*
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();
 if(radiobutton_pp_eingeben->get_active())
  {
   spinbutton_pp_eingeben->set_value(MBE->Praxispunkte());
   spinbutton_pp_eingeben->show();
   return;
  }

 if (MBE->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return;
 if (radiobutton_steigern->get_active() && MBE->Steigern(Typ,Database.ausnahmen))
    {
      if (!steigern_usp(MBE->Steigern(Typ,Database.ausnahmen),&MBE)) return;
      Werte.add_GFP(MBE->Steigern(Typ,Database.ausnahmen));
      for (std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!= list_Fertigkeit.end();++i )
         if ( cH_Fertigkeit(*i)->Name() == MBE->Name()) 
           cH_Fertigkeit(*i)->add_Erfolgswert(1); 
    }
   if (radiobutton_reduzieren->get_active() && MBE->Reduzieren(Typ,Database.ausnahmen))
    {
      if (steigern_bool) desteigern(MBE->Reduzieren(Typ,Database.ausnahmen));
      Werte.add_GFP(-MBE->Reduzieren(Typ,Database.ausnahmen));
      for (std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!= list_Fertigkeit.end();++i )
         if ( cH_Fertigkeit(*i)->Name() == MBE->Name()) 
           cH_Fertigkeit(*i)->add_Erfolgswert(-1); 
    }
   if (radiobutton_verlernen->get_active() && MBE->Verlernen(Typ,Database.ausnahmen))
    {
      if (steigern_bool) desteigern(MBE->Verlernen(Typ,Database.ausnahmen));
      Werte.add_GFP(-MBE->Verlernen(Typ,Database.ausnahmen));
      MidgardBasicElement::move_element(list_Fertigkeit,list_Fertigkeit_neu,MBE->Name());
    }
*/
   fertigkeiten_zeigen();
}

void midgard_CG::on_alte_fert_reorder()
{
cout << "REORDER\n";
  on_button_fertigkeiten_sort_clicked();
}

void midgard_CG::on_button_fertigkeiten_sort_clicked()
{
  std::deque<guint> seq = alte_fert_tree->get_seq();
  switch((Data_SimpleTree::Spalten_FA)seq[0]) {
      case Data_SimpleTree::NAMEa : list_Fertigkeit.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME)); ;break;
      case Data_SimpleTree::WERTa : list_Fertigkeit.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::ERFOLGSWERT)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}


bool midgard_CG::kido_steigern_check(int wert)
{
  if (Werte.Grad()+10 > wert) return false;
  else
   { std::string strinfo ="KiDo darf nur auf maximal Grad+10 gesteigert werden.\n";
     manage (new WindowInfo(strinfo));
     return true;
   }
}


void midgard_CG::on_leaf_selected_neue_fert(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);

  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();

/*
  if (!steigern_usp(MBE->Kosten(Typ,Database.ausnahmen),&MBE)) return;
  Werte.add_GFP(MBE->Kosten(Typ,Database.ausnahmen));
  if(MBE->Name()!="Landeskunde")
     fertigkeiten_zeigen();
  else fillClistLand(MBE);
  MidgardBasicElement::move_element(list_Fertigkeit_neu,list_Fertigkeit,MBE->Name());
*/

  if (MBE->Name()=="KiDo") {kido_bool=true;show_gtk();
      optionmenu_KiDo_Stile->set_sensitive(true);
      table_kido_lernen->set_sensitive(true);
      button_kido_auswahl->set_sensitive(false);
      std::string strinfo="Jetzt muß ein Stil unter 'Lernschema' -> 'KiDo' gewählt werden !!!";
      manage (new WindowInfo(strinfo,true)); }
  if (MBE->Name()=="Zaubern") 
      {  doppelcharaktere();
         std::string strinfo ="Jetzt unter 'Grundwerte' die zweite Charkakterklasse wählen\n";
         strinfo += " und anschließend 'Fertigkeiten neu laden' klicken\n";
         manage (new WindowInfo(strinfo,true));
         // Resistenzboni für Zauberer setzten:
         Werte.set_magBoni(Werte.bo_Psy()+3,Werte.bo_Phs()+1,Werte.bo_Phk()+3);
         if (Werte.Zaubern_wert()==0) Werte.set_Zaubern_wert(10);
      }
  fertigkeiten_zeigen();
}

void midgard_CG::fillClistLand(const cH_MidgardBasicElement &MBE)
{
  Gtk::OStream os(clist_landauswahl);
  for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
   {
     os <<(*i)->Name()<<'\n';
//     os.flush(const_cast<cH_MidgardBasicElement*>(&MBE));
     os.flush(MBE->ref(),&HandleContent::unref);
   }
  scrolledwindow_landauswahl->show();
}

void midgard_CG::on_clist_landauswahl_select_row(gint row, gint column, GdkEvent *event)
{
  std::string land = clist_landauswahl->get_text(row,0);
cout << "2 "<<land<<'\n';
  MidgardBasicElement *MBE=static_cast<MidgardBasicElement*>(clist_landauswahl->selection().begin()->get_data());
cout << (MBE)->What()<<'\n';

  cH_Fertigkeit(MBE)->setZusatz(land);
  scrolledwindow_landauswahl->hide();
  fertigkeiten_zeigen();
}

/*
void midgard_CG::on_radio_fert_reduzieren_toggled()
{
   if (radio_fert_reduzieren->get_active())
      togglebutton_praxispunkte_fertigkeiten->set_active(false);
}
void midgard_CG::on_radio_fert_verlernen_toggled()
{
   if (radio_fert_verlernen->get_active())
      togglebutton_praxispunkte_fertigkeiten->set_active(false);
}
*/
/*
void midgard_CG::on_togglebutton_praxispunkte_fertigkeiten_toggled()
{
    if (togglebutton_praxispunkte_fertigkeiten->get_active())
      radio_fert_steigern->set_active(true);
}

void midgard_CG::on_radiobutton_praxis_wuerfeln_fertigkeiten_toggled()
{
}

void midgard_CG::on_radiobutton_praxis_auto_fertigkeiten_toggled()
{
}
*/
