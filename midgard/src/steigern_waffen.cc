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
#include "WaffeGrund.hh"
#include "class_SimpleTree.hh"
#include "Pflicht.hh"


void midgard_CG::on_waffen_laden_clicked()
{
 list_Waffen_neu.clear();
 for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Waffe.begin();i!=Database.Waffe.end();++i)
   { cH_Waffe w(*i);
     if (w->ist_gelernt(list_Waffen)) continue ;
     if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,w->Name())) continue;
     if (w->Grundkenntnis_vorhanden(list_WaffenGrund))
       if (w->ist_lernbar(Typ,w->get_MapTyp()))
         if (region_check(w->Region(w->Name())) )
           if (w->SG_Voraussetzung(Werte))
             {
              if(w->Art()=="Verteidigung") w->set_Erfolgswert(1);
              else w->set_Erfolgswert(4);
              list_Waffen_neu.push_back(*i);
             }
   }
  on_waffengrund_laden_clicked();
  waffen_zeigen();
}


void midgard_CG::waffen_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
   MidgardBasicElement::show_list_in_tree(list_WaffenGrund_neu,neue_grund_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_WaffenGrund    ,alte_grund_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Waffen_neu,neue_waffen_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Waffen    ,alte_waffen_tree,Werte,Typ,Database.ausnahmen);
}



void midgard_CG::on_leaf_selected_neue_grund(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  on_waffen_laden_clicked();
}


void midgard_CG::on_waffengrund_laden_clicked()
{
  list_WaffenGrund_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.WaffeGrund.begin();i!=Database.WaffeGrund.end();++i)
   { cH_WaffeGrund w(*i);
     if ((*i)->ist_gelernt(list_WaffenGrund)) continue ;
     if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,w->Name())) continue;
     if((*i)->ist_lernbar(Typ,(*i)->get_MapTyp()))
        if (region_check(w->Region()) )
         list_WaffenGrund_neu.push_back(*i);
   }
}

void midgard_CG::on_leaf_selected_neue_waffen(cH_RowDataBase d)
{  
   MidgardBasicElement_leaf_neu(d);
   waffen_zeigen();
}
 
void midgard_CG::on_leaf_selected_alte_grund(cH_RowDataBase d)
{  
  std::string strinfo="WARNUNG: Beim verlernen von Grundkenntnissen werden die\n";
  strinfo +="bereits gelernten Waffen, die zu dieser\n";
  strinfo +="Grundkenntnis gehöhren, NICHT verlernt\n";
  WindowInfo(strinfo,true);
  if (MidgardBasicElement_leaf_alt(d))
//     waffen_zeigen();
  on_waffen_laden_clicked();

}

void midgard_CG::on_leaf_selected_alte_waffen(cH_RowDataBase d)
{  
  if (MidgardBasicElement_leaf_alt(d))
    waffen_zeigen();
}

void midgard_CG::on_alte_waffen_reorder()
{
  on_button_waffen_sort_clicked();
}


void midgard_CG::on_button_waffen_sort_clicked()
{
  std::deque<guint> seq = alte_waffen_tree->get_seq();
  switch((Data_SimpleTree::Spalten_LONG_ALT)seq[0]) {
      case Data_SimpleTree::WERTa : list_Waffen.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::ERFOLGSWERT)); ;break;
      case Data_SimpleTree::NAMEa : list_Waffen.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}
