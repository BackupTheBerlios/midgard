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
     cH_MidgardBasicElement *ptr = static_cast<cH_MidgardBasicElement*>(i->get_data());
     technik.push_back(*ptr);
   }
  hauptfenster->MidgardBasicElement_uebernehmen(technik);
  destroy();
}


KiDo_auswahl::KiDo_auswahl(midgard_CG* h, int m, const Grundwerte& Werte,
   const midgard_CG::st_Database& Database,
   const vector<cH_Typen>& Typ)
: maxkido(m)
{
//   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
   hauptfenster=h;
   label_kido_techniken->set_text("Noch "+itos(maxkido)+" Techniken auswählen");

/*
   exec sql begin declare section;
    char db_name_orig[50];
    char query[1024];
   exec sql end declare section;
   std::string squery;
   squery = "select name_orig from kido where stufe='Schüler' ";
   if (Werte.Spezialisierung() != "Gemischte Techniken")
      squery += "and (stil = 'beide' or stil = '"+Werte.Spezialisierung() +"') ";
   squery +=  " order by 1";
   strncpy(query,squery.c_str(),sizeof(query));
   Transaction tr;
   exec sql prepare ein_ from :query;
   exec sql declare ein cursor for ein_;
   exec sql open ein;
   SQLerror::test(__FILELINE__);
   while (true)
     {
      exec sql fetch ein into :db_name_orig;
      SQLerror::test(__FILELINE__,100);  
      if (sqlca.sqlcode) break;
      cH_MidgardBasicElement kido(new KiDo(db_name_orig));
      kido_technik.push_back(kido);
     }
   exec sql close ein;
*/
   for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Kido.begin();i!=Database.Kido.end();++i)
    {
      cH_KiDo kd(*i);
      if(kd->Stufe()!="Schüler") continue;
      if (Werte.Spezialisierung()=="Harte Techniken")
           if(kd->Stil()=="Sanfte Techniken") continue; 
      if (Werte.Spezialisierung()=="Sanfte Techniken")
           if(kd->Stil()=="Harte Techniken") continue;   
      kido_technik.push_back(*i);
    }
   Gtk::OStream os(clist_kido_auswahl);
   clist_kido_auswahl->freeze();
   for (std::list<cH_MidgardBasicElement>::iterator i=kido_technik.begin();i!=kido_technik.end();++i)
    {
      cH_KiDo kd(*i);
      os << kd->Hoho() <<"\t"<<kd->Name()<<"\t"<<kd->Ap()<<"\t"<<kd->Kosten(Typ,Database.ausnahmen)<<"\n";
      os.flush(&*i);
    }
   for (unsigned int i=0;i<clist_kido_auswahl->columns().size();++i)
      clist_kido_auswahl->set_column_auto_resize(i,true);
   clist_kido_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
   clist_kido_auswahl->set_reorderable(true);
   clist_kido_auswahl->thaw();
}

