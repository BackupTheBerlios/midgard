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

// generated 2001/3/7 7:55:50 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Sprache_auswahl.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Sprache_auswahl.hh"
#include "midgard_CG.hh"
#include <Gtk_OStream.h>
#include "Schrift.hh"
#include "Sprache.hh"
#include "Fertigkeiten.hh"
#include "WindowInfo.hh"

void Sprache_auswahl::on_clist_sp_sc_select_row(gint row, gint column, GdkEvent *event)
{   
  if (mod == LAND)
   {
     cH_Land *s=static_cast<cH_Land*>(clist_sp_sc->selection().begin()->get_data());
     cH_MidgardBasicElement F(new Fertigkeit("Landeskunde"));
     cH_Fertigkeit(F)->setZusatz((*s)->Name());     
     F->set_Erfolgswert(wert);
//     std::list<cH_MidgardBasicElement> FL;
//     FL.push_back(static_cast<cH_MidgardBasicElement&>(F));
     hauptfenster->MidgardBasicElement_uebernehmen(F);
   }
  else 
   {
     cH_MidgardBasicElement *s=static_cast<cH_MidgardBasicElement*>(clist_sp_sc->selection().begin()->get_data());
     if((*s)->What()==MidgardBasicElement::SPRACHE)
        cH_Sprache(*s)->set_Erfolgswert(wert);
     else if((*s)->What()==MidgardBasicElement::SCHRIFT)
        cH_Schrift(*s)->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(*s);
   }
  destroy();
}


Sprache_auswahl::Sprache_auswahl(midgard_CG* h, const midgard_CG::st_Database& Database, 
   const modus _mod,int _wert,const std::list<cH_MidgardBasicElement> *Sp,
                             const std::list<cH_MidgardBasicElement> &Sc,
                             const std::list<cH_MidgardBasicElement> &L)
 : mod(_mod),hauptfenster(h),wert(_wert)
{
  {
   Gtk::OStream os(clist_sp_sc);
   if (mod == LAND)
      {
         sp_sc_label->set_text("Land wählen");
         for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
          { 
            os << (*i)->Name()<<'\t'<<wert<<'\n';
            os.flush(&const_cast<cH_Land&>(*i));
          }
      }
   if (mod == SPRACHE)
      {
         sp_sc_label->set_text("Sprache wählen");
         for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Sprache.begin();i!=Database.Sprache.end();++i)
          { 
            if((*i)->ist_gelernt(*Sp)) continue;
            cH_Sprache s(*i);
            os << s->Name()<<'\t'<<wert<<'\n';
            os.flush(&const_cast<cH_MidgardBasicElement&>(*i));
          }
      }
   if (mod == SCHRIFT)
      {
         sp_sc_label->set_text("Schrift wählen");
         for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Schrift.begin();i!=Database.Schrift.end();++i)
          { 
            if((*i)->ist_gelernt(Sc)) continue;
            cH_Schrift s(*i);
            if(s->kann_Sprache(*Sp))
             {
               os << s->Name()<<'\t'<<s->Art_der_Schrift()<<'\n';
               os.flush(&const_cast<cH_MidgardBasicElement&>(*i));
             }
          }
         if(!clist_sp_sc->rows().size())
            manage (new WindowInfo("Keine Sprache gewählt, deren Schrift zu lernen wäre.\n"));
      }
   for (unsigned int i=0;i<clist_sp_sc->columns().size();++i)
      clist_sp_sc->set_column_auto_resize(i,true);
  }
 // Leere Liste wieder zerstören
 if(!clist_sp_sc->rows().size()) destroy();
}
