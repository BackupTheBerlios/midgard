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

// generated 2001/4/3 21:37:34 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to KiDo_auswahl.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "KiDo_auswahl.hh"
#include "midgard_CG.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include <KiDo.hh>

void KiDo_auswahl::on_clist_kido_auswahl_select_row(gint row, gint column, GdkEvent *event)
{   
   if (maxkido<=0) clist_kido_auswahl->row(row).unselect();
   label_kido_techniken->set_text("Noch "+itos(--maxkido)+" Techniken auswählen");
}

void KiDo_auswahl::on_clist_kido_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{   
   label_kido_techniken->set_text("Noch "+itos(++maxkido)+" Techniken auswählen");
}

void KiDo_auswahl::on_button_close_clicked()
{
  std::list<cH_MidgardBasicElement> technik;
  for(Gtk::CList::SelectionList::iterator i=clist_kido_auswahl->selection().begin();
      i!=clist_kido_auswahl->selection().end();++i)
   {
     cH_MidgardBasicElement ptr = static_cast<MidgardBasicElement*>(i->get_data());
     technik.push_back(ptr);
   }
  hauptfenster->MidgardBasicElement_uebernehmen(technik);
  destroy();
}


KiDo_auswahl::KiDo_auswahl(midgard_CG* h, int m, const Grundwerte& Werte,
   const Datenbank& Database,
   const vector<cH_Typen>& Typ,std::vector<std::string> Vkido)
: maxkido(m)
{
   hauptfenster=h;
   label_kido_techniken->set_text("Noch "+itos(maxkido)+" Techniken auswählen");

   for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Kido.begin();i!=Database.Kido.end();++i)
    {
      cH_KiDo kd(*i);
      if(kd->Stufe()!="Schüler") continue;
      if (Werte.Spezialisierung()==Vkido[2])
           if(kd->Stil()==Vkido[1]) continue; 
      if (Werte.Spezialisierung()==Vkido[1])
           if(kd->Stil()==Vkido[2]) continue;   
      kido_technik.push_back(*i);
    }
   Gtk::OStream os(clist_kido_auswahl);
   clist_kido_auswahl->freeze();
   for (std::list<cH_MidgardBasicElement>::iterator i=kido_technik.begin();i!=kido_technik.end();++i)
    {
      cH_KiDo kd(*i);
      os << kd->Hoho() <<"\t"<<kd->Name()<<"\t"<<kd->Ap()<<"\t"<<kd->Kosten(Typ,Database.ausnahmen)<<"\n";
//      os.flush(&*i);
      os.flush(kd->ref(),&HandleContent::unref);
    }
   for (unsigned int i=0;i<clist_kido_auswahl->columns().size();++i)
      clist_kido_auswahl->set_column_auto_resize(i,true);
   clist_kido_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
   clist_kido_auswahl->set_reorderable(true);
   clist_kido_auswahl->thaw();
}

