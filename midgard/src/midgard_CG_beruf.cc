// $Id: midgard_CG_beruf.cc,v 1.43 2002/02/05 15:47:43 thoma Exp $
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
#include "Berufe_auswahl.hh"
#include <Gtk_OStream.h>
#ifndef USE_XML
#include <Aux/SQLerror.h>
#endif


gint midgard_CG::on_button_beruf_release_event(GdkEventButton *ev)
{
  if (ev->button==1) 
   {
     berufe_clist->clear();
//     list_Beruf.clear(); //macht MidgardBasicElement_uebernehmen(MBE)
     manage(new Berufe_auswahl(this,Database,Typ,Werte,list_Fertigkeit));
   }
  if (ev->button==3) 
   {
     vbox_berufsname->show();
     entry_berufsname->grab_focus();
   }
  return false;
}

void midgard_CG::on_entry_berufsname_activate()
{
  cH_MidgardBasicElement beruf(&*cH_Beruf(entry_berufsname->get_text(),true));
  MidgardBasicElement_uebernehmen(beruf);
  vbox_berufsname->hide();
}


/*
void midgard_CG::on_berufe_wahl_clicked()
{
  berufe_clist->clear();
  list_Beruf.clear();
//  list_Fertigkeit.clear();
#ifndef USE_XML
  try{ 
#endif
   manage(new Berufe_auswahl(this,Database,Typ,Werte,list_Fertigkeit));
#ifndef USE_XML
   }catch(SQLerror &e) {cerr<<e.what()<<'\n';}
#endif
  hbox_fertigkeit->set_sensitive(true);
  table_fertigkeit->set_sensitive(true);
}
*/

/*
void midgard_CG::show_berufe()
{
   berufe_clist->clear();
   Gtk::OStream os(berufe_clist);
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Beruf.begin();i!=list_Beruf.end();++i)
    {
      cH_Beruf b(*i);  
//      os << (*i)->Name()<<"\t"<<b->Vorteile()<<"\t"<<(*i)->Erfolgswert()<<"\n";
      os << (*i)->Name()<<"\n";//<<b->Vorteile()<<"\t"<<(*i)->Erfolgswert()<<"\n";
    }
   for (unsigned int i=0;i<berufe_clist->columns().size();++i)
      berufe_clist->set_column_auto_resize(i,true);
   berufe_clist->set_reorderable(true);
}
*/
gint midgard_CG::on_beruf_erfolgswert_release_event(GdkEventButton *ev)
{
/*
  hbox_fertigkeit->set_sensitive(true);
  table_fertigkeit->set_sensitive(true);
*/
  return false;
}
/*
void midgard_CG::beruf_erfolgswert_eingeben()
{
#warning 
#warning 
#warning Berufeserfolgswert setzen geht bisher nur für den letzen Beruf
#warning 
  for(std::list<cH_MidgardBasicElement>::iterator i=list_Beruf.begin();i!=list_Beruf.end();++i)
   {
     vbox_beruferfolgswert->show();
     label_beruf_ew->set_text((*i)->Name());   
   }
}
*/
void midgard_CG::on_spinbutton_beruferfolgesert_activate()
{
/*
  spinbutton_beruferfolgesert->update();
  int x=spinbutton_beruferfolgesert->get_value_as_int();
  std::string beruf=label_beruf_ew->get_text();
  for(std::list<cH_MidgardBasicElement>::iterator i=list_Beruf.begin();i!=list_Beruf.end();++i)
   {
     if((*i)->Name()==beruf) (*i)->set_Erfolgswert(x);
   }
  vbox_beruferfolgswert->hide();
  MidgardBasicElement_uebernehmen(list_Beruf);
*/
}
/*

void midgard_CG::on_beruf_erfolgswert_clicked()
{
// int erfahrungswert = (int)((lernpunkte.Waffen() + lernpunkte.Fertigkeiten())/5.);
 int inbo=0;
 if (atoi(in->get_text().c_str()) >= 81 ) ++inbo ;
 if (atoi(in->get_text().c_str()) >= 96 ) ++inbo ;

 for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Beruf.begin();i!=list_Beruf.end();++i)
   {
    int ausbildungswert = random.integer(1,3)+6;
//    if (i==list_Beruf.begin()) (*i)->set_Erfolgswert(ausbildungswert+erfahrungswert+inbo);
//    else (*i)->set_Erfolgswert(ausbildungswert+inbo);
   } 
  MidgardBasicElement_uebernehmen(list_Beruf);
}

std::vector<string> midgard_CG::Berufs_Vorteile()
{
  std::vector<string> V;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Beruf.begin();
           i!=list_Beruf.end();++i)
   {
     std::vector<string> v=cH_Beruf(*i)->Vorteile();
     for(std::vector<string>::const_iterator j=v.begin();j!=v.end();++j)
         V.push_back(*j);      
   }           
 return V;
}
*/