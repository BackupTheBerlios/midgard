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
#include "WindowInfo.hh"
//#include "class_kido.hh"
#include "class_SimpleTree.hh"
#include "KiDo.hh"

void midgard_CG::on_kido_laden_clicked()
{   
  list_Kido_neu.clear();
  int erfolgswert_kido = KiDo::get_erfolgswert_kido(list_Fertigkeit);
  if (Werte.Spezialisierung()!=Vkido[1] &&
      Werte.Spezialisierung()!=Vkido[2]&&
      Werte.Spezialisierung()!=Vkido[3] ) 
     {
       manage(new WindowInfo("Erst einen KiDo-Stil wählen\n(unter 'Lernschema'->'KiDo')"));
       return;
     }
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Kido.begin();i!=Database.Kido.end();++i)
   { cH_KiDo kd(*i);
     if ((*i)->ist_gelernt(list_Kido)) continue ;
     // Stufe
     if (Werte.Grad()<4 || erfolgswert_kido+Werte.bo_Za() <15)
      if(kd->Stufe()=="Eingeweihter") continue;
     if (Werte.Grad()<6 || erfolgswert_kido+Werte.bo_Za() <18)
      if(kd->Stufe()=="Meister") continue;
     // Stil
     if (Werte.Spezialisierung()==Vkido[2])
       if(kd->Stil()==Vkido[1]) continue;
     if (Werte.Spezialisierung()==Vkido[1])
       if(kd->Stil()==Vkido[2]) continue;
   
     // Anzahl
     bool gem_technik = (Werte.Spezialisierung()==Vkido[3]);
     std::map<std::string,int> MK = KiDo::maxkidostil(list_Kido);  
     int maxS = MK["Schüler"];
     int maxE = MK["Eingeweihter"];
     int maxM = MK["Meister"];
     if((kd->Stufe()=="Schüler"     && gem_technik && maxS <11)||
        (kd->Stufe()=="Schüler"     &&!gem_technik && maxS <12)||
        (kd->Stufe()=="Eingeweihter"&& gem_technik && maxE < 6)||
        (kd->Stufe()=="Eingeweihter"&&!gem_technik && maxE < 7)||
        (kd->Stufe()=="Meister"     && gem_technik && maxM < 2)||
        (kd->Stufe()=="Meister"     &&!gem_technik && maxM < 3) )
    list_Kido_neu.push_back(*i);
    }
 kido_zeigen();
}

void midgard_CG::kido_zeigen()
{
 zeige_werte(Werte);
#ifndef USE_XML
 on_speichern_clicked();
#else
   steigern_aktivieren();
#endif
 MidgardBasicElement::show_list_in_tree(list_Kido    ,alte_kido_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Kido_neu,neue_kido_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::on_leaf_selected_alte_kido(cH_RowDataBase d)
{  
  if(MidgardBasicElement_leaf_alt(d))
     on_kido_laden_clicked();
}

void midgard_CG::on_leaf_selected_neue_kido(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  on_kido_laden_clicked();
}

void midgard_CG::on_alte_kido_reorder()
{
   on_button_kido_sort_clicked();
}


void midgard_CG::on_button_kido_sort_clicked()
{
  std::deque<guint> seq = alte_kido_tree->get_seq();
  switch((Data_SimpleTree::Spalten_KIDO)seq[0]) {
      case Data_SimpleTree::HOHOa_K  : list_Kido.sort(cH_KiDo::sort(cH_KiDo::sort::HOHO)) ;break;
      case Data_SimpleTree::NAMEa_K  : list_Kido.sort(cH_KiDo::sort(cH_KiDo::sort::NAME)) ;break;
      case Data_SimpleTree::STUFEa_K : list_Kido.sort(cH_KiDo::sort(cH_KiDo::sort::STUFE)) ;break;
      case Data_SimpleTree::APa_K    : list_Kido.sort(cH_KiDo::sort(cH_KiDo::sort::AP)); break;
      case Data_SimpleTree::STILa_K  : list_Kido.sort(cH_KiDo::sort(cH_KiDo::sort::STIL)) ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}
