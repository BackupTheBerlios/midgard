// $Id: midgard_CG_waffen.cc,v 1.31 2002/02/05 15:47:43 thoma Exp $
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
#include "Waffen_auswahl.hh"
#include <Gtk_OStream.h>
#include "Waffe.hh"

void midgard_CG::on_waffen_wahl_clicked()
{
  waffen_clist->clear();
//  manage(new Waffen_auswahl(this,Database,lernpunkte.Waffen(),Werte,Typ));
//  show_waffen();
  show_lernschema(MidgardBasicElement::WAFFE);
}

/*
void midgard_CG::show_waffen()
{
  list_Waffen_neu.clear();
  std::list<cH_MidgardBasicElement> LW=Database.lernschema.get_List("Waffenfertigkeiten",Typ);
  for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
     {
       cH_Waffe waffe(*i);
       if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
       if (!region_check(waffe->Region((*i)->Name()))) continue;
       if ((*i)->ist_gelernt(list_Waffen)) continue ;
       Lernschema::st_index I(Typ[0]->Short(),"Waffenfertigkeiten",(*i)->Name());
       (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I));
       list_Waffen_neu.push_back(*i);
     }
  MidgardBasicElement::show_list_in_tree(list_Waffen_neu,tree_lernschema,Werte,Typ,Database.ausnahmen);
  tree_lernschema.Expand_recursively();        

*/  
/*
   waffen_clist->clear();
   Gtk::OStream os(waffen_clist);
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Waffen.begin();
         i!=list_Waffen.end();++i)
      {
         os << (*i)->Name()<<"\t"<<(*i)->Erfolgswert()<<"\n";
//         os.flush(&*i);
         os.flush((*i)->ref(),&HandleContent::unref);
      }
   for (unsigned int i=0;i<waffen_clist->columns().size();++i)
      waffen_clist->set_column_auto_resize(i,true);
   waffen_clist->set_reorderable(true);
*/
//}

void midgard_CG::on_waffen_clist_select_row(gint row, gint column, GdkEvent *event)
{   
 /* Funktion f�r Spezialwaffe */
 if (Typ[0]->Zaubern()=="n" || Typ[0]->Short() == "Ord")
   {
    Gtk::CList::SelectionList::iterator i=waffen_clist->selection().begin();
    cH_MidgardBasicElement ptr = static_cast<MidgardBasicElement*>(i->get_data());           
    (ptr)->set_Erfolgswert((ptr)->Erfolgswert()+2);
    Werte.setSpezialisierung((ptr)->Name());

    static cH_MidgardBasicElement *ptr_mem=0;
    if(ptr_mem)
     {
      (*ptr_mem)->set_Erfolgswert((*ptr_mem)->Erfolgswert()-2);
     }
    ptr_mem=&ptr;
//   show_waffen();
   show_gelerntes();
   }
}

