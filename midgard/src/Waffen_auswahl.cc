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

// generated 2001/2/10 15:15:14 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Waffen_auswahl.cc_new

// This file is for your program, I won't touch it again!

#include "Waffen_auswahl.hh"
#include <cstring>
#include <Gtk_OStream.h>


Waffen_auswahl::Waffen_auswahl(midgard_CG* h,const Datenbank& D,
   int lernpunkte, const Grundwerte& Werte,const vector<cH_Typen>& _Typ)
:Typ(_Typ)
{
  hauptfenster=h;
//  std::vector<string> vorteile=hauptfenster->Berufs_Vorteile();
  maxpunkte = lernpunkte;
  waffen_auswahl_lernpunkte->set_text(itos(maxpunkte));
  std::list<cH_MidgardBasicElement> LW=D.lernschema.get_List("Waffenfertigkeiten",Typ);

  for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
     {
       cH_Waffe waffe(*i);
       if (D.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
       if (!hauptfenster->region_check(waffe->Region((*i)->Name()))) continue;
       Lernschema::st_index I(Typ[0]->Short(),"Waffenfertigkeiten",(*i)->Name());
//       int v=0;
//       for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
//            if ((*j)==(*i)->Name()) v=1;
       (*i)->set_Lernpunkte(D.lernschema.get_Lernpunkte(I));
       list_Waffen.push_back(*i);
     }
    list_Waffen.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
    Gtk::OStream os(waffen_clist_auswahl);
    waffen_clist_auswahl->freeze();
    
    for(std::list<cH_MidgardBasicElement>::iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
      {
        cH_Waffe w(*i);
        if (w->SG_Voraussetzung(Werte))
         {
            os << w->Lernpunkte() <<"\t"<<w->Voraussetzung()<<"\t"
               << w->Name() <<"\t"
               << w->Erfolgswert() <<"\t"<<w->Grundkenntnis()<<"\n";
//            os.flush(&*i);
            os.flush(w->ref(),&HandleContent::unref);
         }
      }
    for (unsigned int i=0;i<waffen_clist_auswahl->columns().size();++i)
      waffen_clist_auswahl->set_column_auto_resize(i,true);

    waffen_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
    waffen_clist_auswahl->set_reorderable(true);
    waffen_clist_auswahl->thaw();
}

void Waffen_auswahl::on_waffen_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{   
   if (maxpunkte < atoi(waffen_clist_auswahl->get_text(row,0).c_str() ))
      {
         waffen_clist_auswahl->row(row).unselect();
      }
   maxpunkte -= atoi(waffen_clist_auswahl->get_text(row,0).c_str());
   waffen_auswahl_lernpunkte->set_text(itos(maxpunkte));
   std::string grund = waffen_clist_auswahl->get_text(row,4);
//   cH_MidgardBasicElement E(new WaffeGrund(grund));
//   list_WaffenGrund.push_back(E);
   list_WaffenGrund.push_back(new WaffeGrund(grund));
}

void Waffen_auswahl::on_waffen_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{   
   maxpunkte += atoi(waffen_clist_auswahl->get_text(row,0).c_str());
   waffen_auswahl_lernpunkte->set_text(itos(maxpunkte));
}

void Waffen_auswahl::on_close_waffen_clicked()
{   
   std::list<cH_MidgardBasicElement> saw;
   for (Gtk::CList::SelectionList::iterator i=waffen_clist_auswahl->selection().begin();
         i!=waffen_clist_auswahl->selection().end();++i)
     {  
       cH_MidgardBasicElement ptr = static_cast<MidgardBasicElement*>(i->get_data());
       saw.push_back(ptr);
     }
//  hauptfenster->waffen_uebernehmen(saw,list_WaffenGrund);
  hauptfenster->MidgardBasicElement_uebernehmen(saw,list_WaffenGrund);
  destroy();
}
