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
     if (f->Name()=="Zaubern" && Typ[0]->is_mage() || f->Name()=="Zaubern" && Typ[1]->is_mage() ) continue;
     if ((*i)->ist_lernbar(Typ,f->get_MapTyp()))
       if (region_check(f->Region()) )
        if (f->Voraussetzungen(Werte)) 
         {
            f->set_Erfolgswert(f->Anfangswert());
            list_Fertigkeit_neu.push_back(*i);
//Kopie            list_Fertigkeit_neu.push_back(new Fertigkeit(*f));
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
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_Fertigkeit F(cH_Fertigkeit(dt->getMBE()));
 if( radiobutton_unterweisung->get_active() && 
     F->Erfolgswert() >= F->MaxUnterweisung())
   {
     regnot("Weitere Steigerung des Erfolgswertes ist NICHT mit Unterweisung möglich.");
     return ;
   }
 if (MidgardBasicElement_leaf_alt(d))
    fertigkeiten_zeigen();
}

void midgard_CG::on_alte_fert_reorder()
{
  on_button_fertigkeiten_sort_clicked();
}

void midgard_CG::on_button_fertigkeiten_sort_clicked()
{
  std::deque<guint> seq = alte_fert_tree->get_seq();
  switch((Data_SimpleTree::Spalten_LONG_ALT)seq[0]) {
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

  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if (MBE->Name()=="KiDo") 
    { kido_bool=true;show_gtk();
      optionmenu_KiDo_Stile->set_sensitive(true);
      table_kido_lernen->set_sensitive(true);
      button_kido_auswahl->set_sensitive(false);
      std::string strinfo="Jetzt muß ein Stil unter 'Lernschema' -> 'KiDo' gewählt werden !!!";
      manage (new WindowInfo(strinfo,true)); 
      MidgardBasicElement_leaf_neu(d);      
    }
  else if (MBE->Name()=="Zaubern") 
      {  doppelcharaktere();
         std::string strinfo ="Jetzt unter 'Grundwerte' die zweite Charkakterklasse wählen\n";
         strinfo += " und anschließend 'Fertigkeiten neu laden' klicken\n";
         manage (new WindowInfo(strinfo,true));
         // Resistenzboni für Zauberer setzten:
//         Werte.set_magBoni(Werte.bo_Psy()+3,Werte.bo_Phs()+1,Werte.bo_Phk()+3);
         if (Werte.Zaubern_wert()==2) Werte.setZaubern_wert(10);
      }
  else 
     MidgardBasicElement_leaf_neu(d);
  fertigkeiten_zeigen();
}

void midgard_CG::fillClistLand(const cH_MidgardBasicElement &MBE)
{
  clist_landauswahl->clear();
  Gtk::OStream os(clist_landauswahl);
  for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
   {
     os <<(*i)->Name()<<'\n';
     os.flush(MBE->ref(),&HandleContent::unref);
   }
  scrolledwindow_landauswahl->show();
}

void midgard_CG::on_clist_landauswahl_select_row(gint row, gint column, GdkEvent *event)
{
  std::string land = clist_landauswahl->get_text(row,0);
  MidgardBasicElement *MBE=static_cast<MidgardBasicElement*>(clist_landauswahl->selection().begin()->get_data());
  cH_Fertigkeit(MBE)->setZusatz(land);
  if(land==Werte.Herkunft()->Name()) MBE->set_Erfolgswert(9);
  scrolledwindow_landauswahl->hide();
  on_fertigkeiten_laden_clicked();
}

