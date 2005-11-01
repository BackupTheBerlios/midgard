/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2005 Christof Petig
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
#include <libmagus/Ausgabe.hh>
#include <libmagus/LernListen.hh>
#include <Misc/create_parse.h>

void table_steigern::waffen_zeigen()
{  if (notebook_lernen->get_current_page()!=PAGE_WAFFEN) return;
   alte_waffen_zeigen();
   neue_waffen_zeigen();
   waffengrund_zeigen();
   zeige_werte();
}

void table_steigern::neue_waffen_zeigen()
{
   Abenteurer &A=hauptfenster->getAben();
   list_Waffen_neu=LernListen::get_steigern_MBEm(A,MidgardBasicElement::WAFFE);
   MidgardBasicTree::show_list_in_tree(list_Waffen_neu,neue_waffen_tree,hauptfenster->getChar().actualIterator());
}

void table_steigern::waffengrund_zeigen()
{
  Abenteurer &A=hauptfenster->getAben();
  list_WaffenGrund_neu=LernListen::get_steigern_MBEm(A,MidgardBasicElement::WAFFEGRUND);
  MidgardBasicTree::show_list_in_tree(list_WaffenGrund_neu,neue_grund_tree,hauptfenster->getChar().actualIterator());
  MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_WaffenGrund()    ,alte_grund_tree,hauptfenster->getChar().actualIterator());
}

void table_steigern::alte_waffen_zeigen()
{
   MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Waffen()    ,alte_waffen_tree,hauptfenster->getChar().actualIterator());
}



void table_steigern::on_leaf_selected_neue_grund(cH_RowDataBase d)
{  
}


void table_steigern::on_leaf_selected_neue_waffen(cH_RowDataBase d)
{  
}
 
void table_steigern::on_leaf_selected_alte_grund(cH_RowDataBase d)
{  

}

void table_steigern::on_leaf_selected_alte_waffen(cH_RowDataBase d)
{  
//  if(!spinbutton_pp_eingeben->is_visible())
//     alte_waffen_tree->get_selection()->unselect_all(); 
}

void table_steigern::on_alte_waffen_reorder()
{
  std::deque<guint> seq = alte_waffen_tree->get_seq();
  switch((Data_SimpleTree::Spalten_LONG_ALT)seq[0]) {
      case Data_SimpleTree::WERTa : hauptfenster->getAben().List_Waffen().sort(MBEmlt::sort(MBEmlt::sort::ERFOLGSWERT)); ;break;
      case Data_SimpleTree::NAMEa : hauptfenster->getAben().List_Waffen().sort(MBEmlt::sort(MBEmlt::sort::NAME)); ;break;
      default : Ausgabe(Ausgabe::Error,"Sortieren nach diesem Parameter ist nicht möglich");
   }
}

void table_steigern::on_alte_waffen_clicked(cH_RowDataBase row,bool &handled)
{ if (button_was_tun->get_index()!=Button_PP_eingeben)
  { 
    if (MidgardBasicElement_leaf_alt(row))
    // notwendig?
     {
       dynamic_cast<const Data_SimpleTree*>(&*row)->redisplay(alte_waffen_tree);
       neue_waffen_zeigen();
//       zeige_werte();
       if(hauptfenster->getAben().reduzieren) alte_waffen_zeigen();
     }
    handled=true;
  }
}

void table_steigern::on_neue_waffen_clicked(cH_RowDataBase row,bool &handled)
{ if (button_was_tun->get_index()!=Button_PP_eingeben)
  { MidgardBasicElement_leaf_neu(row);
    handled=true;
  }
//  neue_waffen_zeigen();
//  waffengrund_zeigen();
}

void table_steigern::on_alte_grund_clicked(cH_RowDataBase row,bool &handled)
{ if (button_was_tun->get_index()!=Button_PP_eingeben)
  { if(hauptfenster->getAben().reduzieren)
     {
       Ausgabe(Ausgabe::Warning,"WARNUNG: Beim verlernen von Grundkenntnissen werden die\n"
          "bereits gelernten Waffen, die zu dieser\n"
          "Grundkenntnis gehöhren, NICHT verlernt");
       MidgardBasicElement_leaf_alt(row);
       neue_waffen_zeigen();
       waffengrund_zeigen();
       handled=true;
     }
  }
}

void table_steigern::on_neue_grund_clicked(cH_RowDataBase row,bool &handled)
{ if (button_was_tun->get_index()!=Button_PP_eingeben)
  { MidgardBasicElement_leaf_neu(row);
    neue_waffen_zeigen();
    handled=true;
  }
//  waffengrund_zeigen();
}
