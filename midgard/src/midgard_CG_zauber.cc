// $Id: midgard_CG_zauber.cc,v 1.47 2002/01/19 18:22:06 christof Exp $
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
#include "Zauber_auswahl.hh"
#include <Gtk_OStream.h>
#ifndef USE_XML
#include <Aux/SQLerror.h>
#endif
#include "Zauber.hh"

void midgard_CG::on_zauber_wahl_clicked()
{
  zauber_clist->clear();
  if (Werte.Spezialgebiet()->Spezial2()=="" && Typ[0]->Short()=="eBe")
   {
      std::string strinfo="Erst Primär- und Sekundärelement wählen\n";
      manage(new WindowInfo(strinfo));
      return;
   }
  manage(new Zauber_auswahl(this,Werte,Database,Typ,lernpunkte.Zauber()));
}

void midgard_CG::show_zauber()
{
   zauber_clist->clear();
   Gtk::OStream os(zauber_clist);
   for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Zauber.begin();i!=list_Zauber.end();++i)
      {
         cH_Zauber z(*i);
         os << z->Name()<<"\t"<<z->Erfolgswert_Z(Typ,Werte,Database.ausnahmen)<<"\n";
      }
   for (unsigned int i=0;i<zauber_clist->columns().size();++i)
      zauber_clist->set_column_auto_resize(i,true);
//   zauber_clist->set_reorderable(true);
}


void midgard_CG::angeborene_zauber()
{
#ifndef USE_XML
 try{
#endif
 if (Typ[0]->Short()=="eBe" || Typ[1]->Short()=="eBe" || Typ[0]->Short()=="dBe" || Typ[1]->Short()=="dBe" ) 
    list_Zauber.push_back(&*cH_Zauber("Lehrersuche"));
 if (Werte.Spezies()->Name()=="Elf") 
    list_Zauber.push_back(&*cH_Zauber("Erkennen der Aura"));
#ifndef USE_XML    
 }catch(SQLerror &e) {cerr << e <<'\n';}
#endif
}

void midgard_CG::magier_spezialgebiet(const std::string& whattodo)
{
 if (whattodo=="show")
   { spezialgebiet_button_fill();
     option_magier_spezialgebiet->show();
   }
 if (whattodo=="hide") option_magier_spezialgebiet->hide();
}

void midgard_CG::spezialgebiet_button_fill()
{
 {
  Gtk::OStream t_(option_magier_spezialgebiet);
  for(std::vector<cH_Spezialgebiet>::iterator i=Database.Spezialgebiet.begin();i!=Database.Spezialgebiet.end();++i)
   {
    if((*i)->Typ() != Typ[0]->Short() && (*i)->Typ() != Typ[1]->Short() ) continue;
    t_ << (*i)->Name();
cout << (*i)->Name()<<'\n';
cout << "\tvor "<<(*i)->ref()<<'\n';
    t_.flush((*i)->ref(),&HandleContent::unref);
cout << "\tnach "<<(*i)->ref()<<'\n';
//    t_.flush(gpointer(&*i));
   }  
 }
 option_magier_spezialgebiet->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::spezialgebiet_button));
cout <<"Menu: "<< option_magier_spezialgebiet->get_menu()<<'\n';
}

void midgard_CG::spezialgebiet_button()
{
cout << "Auswahl\n";
 gpointer user_data=optionmenu_spezies->get_menu()->get_active()->get_user_data();
cout <<"Menu: "<< option_magier_spezialgebiet->get_menu()<<'\n';
cout << "Ja\n";
cout << user_data<<' '<<&user_data<<'\n';
 cH_Spezialgebiet ptr = static_cast<Spezialgebiet*>(user_data);
cout << "aftercast\n";
// if (s=="Spezialgebiet" || s == "Primär- und Sekundärelement") return ;
cout <<"Spez="<<(ptr)->Name()<<'\n';
/*
 Werte.set_Spezialgebiet(ptr);

cout <<"Spez="<<(ptr)->Name()<<'\n';
// get_spezial_from_spezialgebiet();
//cout << Werte.Spezialisierung()<<"\t"<<Werte.Spezial()<<"\t"<<Werte.Spezial2(
*/
} 

              