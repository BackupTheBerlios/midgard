// $Id: midgard_CG_kido.cc,v 1.36 2002/04/30 08:25:04 thoma Exp $
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
//#include "KiDo_auswahl.hh"
#include <Gtk_OStream.h>
#include "KiDo.hh"
#include "class_SimpleTree.hh"
#include <Aux/itos.h>

void midgard_CG::on_kido_wahl_clicked()
{
   if(!button_kido_auswahl->get_active()) return;
   if (Werte.Spezialisierung()!=Vkido[1] && 
       Werte.Spezialisierung()!=Vkido[2] &&
       Werte.Spezialisierung()!=Vkido[3])
    {
      set_status("Erst eine Technik wählen\n");
      return;
    }
   list_Kido.clear();
   fill_kido_lernschema();

//   manage(new KiDo_auswahl(this,maxkido,Werte,Database,Typ,Vkido));
}

void midgard_CG::fill_kido_lernschema()
{
  clean_lernschema_trees();
  viewport_lernen->remove();
  if(maxkido==0) return;
  else if(maxkido==1) label_lernschma_titel->set_text(itos(maxkido)+" KiDo-Technik auswählen");
  else label_lernschma_titel->set_text(itos(maxkido)+" KiDo-Techniken auswählen");
  tree_kido_lernschema = manage(new MidgardBasicTree(MidgardBasicTree::KIDO));
  tree_kido_lernschema->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_tree_kido_lernschema_leaf_selected));

  std::list<cH_MidgardBasicElement> newlist;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Kido.begin();i!=Database.Kido.end();++i)
   {
     cH_KiDo kd(*i);
     if(kd->Stufe()!="Schüler") continue;
     if (Werte.Spezialisierung()==Vkido[2])
         if(kd->Stil()==Vkido[1]) continue;
     if (Werte.Spezialisierung()==Vkido[1])
         if(kd->Stil()==Vkido[2]) continue;
     if ((*i)->ist_gelernt(list_Kido)) continue ;
     newlist.push_back(*i);                                     
   }

  MidgardBasicElement::show_list_in_tree(newlist,tree_kido_lernschema,this);
  scrolledwindow_lernen->show();
  tree_kido_lernschema->show();
  viewport_lernen->add(*tree_kido_lernschema);
}

void midgard_CG::on_tree_kido_lernschema_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  list_Kido.push_back(MBE);
  --maxkido;
  undosave(MBE->Name()+" gelernt");
  fill_kido_lernschema();
  show_gelerntes();      
}


/*
void midgard_CG::show_kido()
{
   clist_kido->clear();
   Gtk::OStream os(clist_kido);
   for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Kido.begin();i!=list_Kido.end();++i)
    {
      cH_KiDo kd(*i);
      os << kd->HoHo()<<"\t"<<kd->Deutsch()<<"\t"<<kd->Ap()<<"\t"<<kd->Kosten(Werte,Typ)<<"\n";
    }
   for (unsigned int i=0;i<clist_kido->columns().size();++i)
      clist_kido->set_column_auto_resize(i,true);
}
*/
void midgard_CG::stil_optionmenue()
{
//  static bool block=false;
//  if (block==true) return;
  int ityp = int(optionmenu_KiDo_Stile->get_menu()->get_active()->get_user_data());
  if (ityp==optionmenu_KiDo_Stile::sanft) Werte.setSpezialisierung(Vkido[1]);
  if (ityp==optionmenu_KiDo_Stile::hart) Werte.setSpezialisierung(Vkido[2]);
  if (ityp==optionmenu_KiDo_Stile::gemischt) Werte.setSpezialisierung(Vkido[3]);
  // NUR sensetiv setzen, wenn Abenteurerrschaffung also Grad=1
  if(Werte.Grad()==1) button_kido_auswahl->set_sensitive(true);
}
