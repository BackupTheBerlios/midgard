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

// generated 2001/2/11 14:16:06 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Zauber_auswahl.cc_new

// This file is for your program, I won't touch it again!

#include "Zauber_auswahl.hh"
#include "midgard_CG.hh"
#include <cstring>
#include <Gtk_OStream.h>

Zauber_auswahl::Zauber_auswahl(midgard_CG* h,const Grundwerte& Werte, 
   const midgard_CG::st_Database& Database,
   const std::vector<H_Data_beruf>& vec_Beruf,
   const vector<cH_Typen>& Typ, int lernpunkte)
{
  while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
  assert (Typ.size()==2);
  hauptfenster=h;
  maxpunkte = lernpunkte;
  zauber_auswahl_lernpunkte->set_text(itos(maxpunkte));
  std::list<cH_MidgardBasicElement> LW=Database.lernschema.get_List("Zauber",Typ);
  
    for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
      {
       Lernschema::st_index I(Typ[0]->Short(),"Zauber",(*i)->Name());
//       int v=0;
//       for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.
//            if ((*j)==(*i)->Name()) v=1;
       (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I));
       list_zauber.push_back(*i);
      }
    list_zauber.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
    Gtk::OStream os(zauber_clist_auswahl);
    zauber_clist_auswahl->freeze();
    for(std::list<cH_MidgardBasicElement>::iterator i=list_zauber.begin();i!=list_zauber.end();++i)
      {
         cH_Zauber z(*i);
         os << z->Lernpunkte() <<"\t"<< z->Name() <<"\t"
            <<z->Ap()<<"\t"<<z->Kosten(Typ,Database.ausnahmen)<<"\n";
         os.flush(&*i);
      }
    for (unsigned int i=0;i<zauber_clist_auswahl->columns().size();++i)
      zauber_clist_auswahl->set_column_auto_resize(i,true);

    zauber_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
    zauber_clist_auswahl->set_reorderable(true);
    zauber_clist_auswahl->thaw();
}


void Zauber_auswahl::on_zauber_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{   
   if (maxpunkte < atoi(zauber_clist_auswahl->get_text(row,0).c_str() ))
      {
         zauber_clist_auswahl->row(row).unselect();
      }
   maxpunkte -= atoi(zauber_clist_auswahl->get_text(row,0).c_str());
   zauber_auswahl_lernpunkte->set_text(itos(maxpunkte));
}

void Zauber_auswahl::on_zauber_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{   
   maxpunkte += atoi(zauber_clist_auswahl->get_text(row,0).c_str());
   zauber_auswahl_lernpunkte->set_text(itos(maxpunkte));
}

void Zauber_auswahl::on_close_zauber_clicked()
{   
   std::list<cH_MidgardBasicElement> saz;
   for (Gtk::CList::SelectionList::iterator i=zauber_clist_auswahl->selection().begin();
         i!=zauber_clist_auswahl->selection().end();++i)
     {  
         // ptr=&fert[i->get_row_num()];
//         H_Data_zauber *ptr = static_cast<H_Data_zauber*>(i->get_data());
         cH_MidgardBasicElement *ptr = static_cast<cH_MidgardBasicElement*>(i->get_data());
//       saz.push_back(new Data_zauber((*ptr)->Name()));
//       saz.push_back(cH_Zauber((*ptr)->Name(),Typ,Ausnahmen(Werte,Typ,vec_Beruf)));
       saz.push_back(*ptr);
     }
  hauptfenster->MidgardBasicElement_uebernehmen(saz);
  destroy();
}
