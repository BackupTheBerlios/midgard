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
#include "table_steigern.hh"
#include "class_SimpleTree.hh"
#include <Gtk_OStream.h>
#include "Fertigkeiten.hh"
#include "Waffe.hh"       


void table_steigern::on_fertigkeiten_laden_clicked()
{
  list_Fertigkeit_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getCDatabase().Fertigkeit.begin();i!=hauptfenster->getCDatabase().Fertigkeit.end();++i)
   { cH_Fertigkeit f(*i);
     if ((*i)->ist_gelernt(hauptfenster->getCChar().CList_Fertigkeit()) && cH_Fertigkeit(*i)->ZusatzEnum(hauptfenster->getCChar().getVTyp())==MidgardBasicElement::ZNone) continue ;
     if (f->Name()=="Sprache" || f->Name()=="Schreiben" || f->Name()=="KiDo-Technik") continue;
//     if (hauptfenster->getCDatabase().pflicht.istVerboten(hauptfenster->getCWerte().Spezies()->Name(),hauptfenster->getCChar().getVTyp(),f->Name())) continue;
     if(hauptfenster->getCWerte().Spezies()->istVerboten(*i)) continue;
     if (f->Name()=="Zaubern" && hauptfenster->getCChar().is_mage() ) continue;
     if (!(*i)->ist_lernbar(hauptfenster->getCChar().getVTyp(),f->get_MapTyp())) continue;
     if (!hauptfenster->region_check(f->Region()) ) continue;
     if (f->Voraussetzungen(hauptfenster->getCWerte(),hauptfenster->getCChar().CList_Fertigkeit())) 
       {
         f->setErfolgswert(f->Anfangswert());
         list_Fertigkeit_neu.push_back(*i);
//Kopie            list_Fertigkeit_neu.push_back(new Fertigkeit(*f));
         }
   }
 fertigkeiten_zeigen();
}

void table_steigern::fertigkeiten_zeigen()
{
 zeige_werte();
 MidgardBasicElement::show_list_in_tree(list_Fertigkeit_neu,neue_fert_tree,hauptfenster);
 MidgardBasicElement::show_list_in_tree(hauptfenster->getCChar().CList_Fertigkeit()    ,alte_fert_tree,hauptfenster);
}


void table_steigern::on_leaf_selected_alte_fert(cH_RowDataBase d)
{  
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_Fertigkeit F(cH_Fertigkeit(dt->getMBE()));
 if( radiobutton_unterweisung->get_active() && 
     F->Erfolgswert() >= F->MaxUnterweisung())
   {
     hauptfenster->set_status("Weitere Steigerung des Erfolgswertes ist NICHT mit Unterweisung m�glich.");
     return ;
   }
 if (MidgardBasicElement_leaf_alt(d))
  {
   on_fertigkeiten_laden_clicked();
//    fertigkeiten_zeigen();
  }
}

void table_steigern::on_alte_fert_reorder()
{
  std::deque<guint> seq = alte_fert_tree->get_seq();
  switch((Data_SimpleTree::Spalten_LONG_ALT)seq[0]) {
      case Data_SimpleTree::NAMEa : hauptfenster->getChar().List_Fertigkeit().sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME)); ;break;
      case Data_SimpleTree::WERTa : hauptfenster->getChar().List_Fertigkeit().sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::ERFOLGSWERT)); ;break;
      default : hauptfenster->set_status("Sortieren nach diesem Parameter\n ist nicht m�glich");
   }
}



void table_steigern::on_leaf_selected_neue_fert(cH_RowDataBase d)
{  
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if (MBE->Name()=="KiDo") 
    { zeige_werte();
      hauptfenster->InfoFenster->AppendShow("Jetzt mu� ein Stil unter 'Lernschema' -> 'KiDo' gew�hlt werden !!!",WindowInfo::None);
      hauptfenster->load_for_mainpage(midgard_CG::PAGE_LERNEN);
      MidgardBasicElement_leaf_neu(d);      
    }
  else if (MBE->Name()=="Zaubern") 
    {  
     hauptfenster->InfoFenster->AppendShow("Sicher, da� dieser K�mpfer Zaubern lernen soll?\nDiese Entscheidung kann nicht mehr R�ckg�ngig gemacht werden.",WindowInfo::ZaubernLernen,MBE);
    }
  else 
     MidgardBasicElement_leaf_neu(d);
   on_fertigkeiten_laden_clicked();
}
