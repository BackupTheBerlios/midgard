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
#include "WaffeGrund.hh"
#include "class_SimpleTree.hh"
#include "Waffe.hh"
#include "LernListen.hh"

void table_steigern::waffen_zeigen()
{
   alte_waffen_zeigen();
   neue_waffen_zeigen();
   waffengrund_zeigen();
   zeige_werte();
}

void table_steigern::neue_waffen_zeigen()
{
   Abenteurer &A=hauptfenster->getAben();
   bool nsc=hauptfenster->MOptionen->OptionenCheck(Midgard_Optionen::NSC_only).active;
   list_Waffen_neu=LL->get_steigern_MBEm(A,Enums::sWaff,nsc);
   MidgardBasicElement::show_list_in_tree(list_Waffen_neu,neue_waffen_tree,hauptfenster);
}

void table_steigern::waffengrund_zeigen()
{
  Abenteurer &A=hauptfenster->getAben();
  bool nsc=hauptfenster->MOptionen->OptionenCheck(Midgard_Optionen::NSC_only).active;
  list_WaffenGrund_neu=LL->get_steigern_MBEm(A,Enums::sWGru,nsc);
  MidgardBasicElement::show_list_in_tree(list_WaffenGrund_neu,neue_grund_tree,hauptfenster);
  MidgardBasicElement::show_list_in_tree(hauptfenster->getChar()->List_WaffenGrund()    ,alte_grund_tree,hauptfenster);
}

void table_steigern::alte_waffen_zeigen()
{
   MidgardBasicElement::show_list_in_tree(hauptfenster->getChar()->List_Waffen()    ,alte_waffen_tree,hauptfenster);
}



void table_steigern::on_leaf_selected_neue_grund(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  neue_waffen_zeigen();
  waffengrund_zeigen();
}


void table_steigern::on_leaf_selected_neue_waffen(cH_RowDataBase d)
{  
   MidgardBasicElement_leaf_neu(d);
   waffen_zeigen();
}
 
void table_steigern::on_leaf_selected_alte_grund(cH_RowDataBase d)
{  
  if(radiobutton_verlernen->get_active())
   {
     std::string strinfo="WARNUNG: Beim verlernen von Grundkenntnissen werden die\n";
     strinfo +="bereits gelernten Waffen, die zu dieser\n";
     strinfo +="Grundkenntnis gehöhren, NICHT verlernt\n";
     hauptfenster->set_info(strinfo);
     MidgardBasicElement_leaf_alt(d);
     neue_waffen_zeigen();
     waffengrund_zeigen();
   }
}

void table_steigern::on_leaf_selected_alte_waffen(cH_RowDataBase d)
{  
  if (MidgardBasicElement_leaf_alt(d))
   {
     dynamic_cast<const Data_SimpleTree*>(&*d)->redisplay(alte_waffen_tree);
     neue_waffen_zeigen();
     if(radiobutton_verlernen->get_active()) alte_waffen_zeigen();
   }
  alte_waffen_tree->unselect_all(); 
}

void table_steigern::on_alte_waffen_reorder()
{
  std::deque<guint> seq = alte_waffen_tree->get_seq();
  switch((Data_SimpleTree::Spalten_LONG_ALT)seq[0]) {
      case Data_SimpleTree::WERTa : hauptfenster->getChar()->List_Waffen().sort(MBEmlt::sort(MBEmlt::sort::ERFOLGSWERT)); ;break;
      case Data_SimpleTree::NAMEa : hauptfenster->getChar()->List_Waffen().sort(MBEmlt::sort(MBEmlt::sort::NAME)); ;break;
      default : hauptfenster->set_status("Sortieren nach diesem Parameter\n ist nicht möglich");
   }
}
