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
#include "table_steigern.hh"
#include "class_SimpleTree.hh"
#include "KiDo.hh"
#include <libmagus/Ausgabe.hh>

void table_steigern::on_kido_laden_clicked()
{   
  list_Kido_neu.clear();
  int erfolgswert_kido = KiDo::get_erfolgswert_kido(hauptfenster->getAben().List_Fertigkeit());
  KiDo_Stile kido_stil;
  if (!kido_stil.ist_gelernt(hauptfenster->getAben().Spezialisierung())) 
     {
       Ausgabe(Ausgabe::Error,"Erst einen KiDo-Stil wählen (unter 'Lernschema'->'KiDo')");
       return;
     }
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Kido.begin();i!=Datenbank.Kido.end();++i)
   { cH_KiDo kd(*i);
     if (MBEmlt(&*kd)->ist_gelernt(hauptfenster->getAben().List_Kido())) continue ;
     // Stufe
     if (hauptfenster->getAben().Grad()<4 || erfolgswert_kido+hauptfenster->getAben().bo_Za() <15)
      if(kd->Stufe()=="Eingeweihter") continue;
     if (hauptfenster->getAben().Grad()<6 || erfolgswert_kido+hauptfenster->getAben().bo_Za() <18)
      if(kd->Stufe()=="Meister") continue;
     // Stil
     if (kido_stil.ist_hart(hauptfenster->getAben().Spezialisierung()))
       if(kido_stil.ist_sanft(kd->Stil())) continue;
     if (kido_stil.ist_sanft(hauptfenster->getAben().Spezialisierung()))
       if(kido_stil.ist_hart(kd->Stil())) continue;
   
     // Anzahl
     bool gem_technik = (kido_stil.ist_gemischt(hauptfenster->getAben().Spezialisierung()));
     std::map<std::string,int> MK = KiDo::maxkidostil(hauptfenster->getAben().List_Kido());  
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

void table_steigern::kido_zeigen()
{
 zeige_werte();
 MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Kido()    ,alte_kido_tree,&hauptfenster->getAben());
 MidgardBasicTree::show_list_in_tree(list_Kido_neu,neue_kido_tree,&hauptfenster->getAben());
}

void table_steigern::on_leaf_selected_alte_kido(cH_RowDataBase d)
{  
  if(MidgardBasicElement_leaf_alt(d))
     on_kido_laden_clicked();
}

void table_steigern::on_leaf_selected_neue_kido(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  on_kido_laden_clicked();
}

bool table_steigern::kido_steigern_check(int wert)
{
  if (hauptfenster->getAben().Grad()+10 > wert) return false;
  else
   { Ausgabe(Ausgabe::Error,"KiDo darf nur auf maximal Grad+10 gesteigert werden.");
     return true;
   }
}

void table_steigern::on_alte_kido_reorder()
{
  std::deque<guint> seq = alte_kido_tree->get_seq();
  switch((Data_SimpleTree::Spalten_KIDO)seq[0]) {
      case Data_SimpleTree::HOHOa_K  : hauptfenster->getAben().List_Kido().sort(cH_KiDo::sort(cH_KiDo::sort::HOHO)) ;break;
      case Data_SimpleTree::NAMEa_K  : hauptfenster->getAben().List_Kido().sort(cH_KiDo::sort(cH_KiDo::sort::NAME)) ;break;
      case Data_SimpleTree::STUFEa_K : hauptfenster->getAben().List_Kido().sort(cH_KiDo::sort(cH_KiDo::sort::STUFE)) ;break;
      case Data_SimpleTree::APa_K    : hauptfenster->getAben().List_Kido().sort(cH_KiDo::sort(cH_KiDo::sort::AP)); break;
      case Data_SimpleTree::STILa_K  : hauptfenster->getAben().List_Kido().sort(cH_KiDo::sort(cH_KiDo::sort::STIL)) ;break;
      default : Ausgabe(Ausgabe::Error,"Sortieren nach diesem Parameter ist nicht möglich");
   }
}
