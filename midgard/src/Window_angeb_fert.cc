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

#include "config.h"
#include "Window_angeb_fert.hh"
#include "midgard_CG.hh"
#include <Gtk_OStream.h>
#include "Fertigkeiten_angeboren.hh"
#include <Aux/itos.h>

void Window_angeb_fert::fertigkeiten_zeigen()
{
 show_alte_afert();
 show_neue_afert();
}

void Window_angeb_fert::on_clist_ang_fert_alt_select_row(gint row, gint column, GdkEvent *event)
{   
  cH_MidgardBasicElement MBE=static_cast<MidgardBasicElement*>(clist_ang_fert_alt->selection().begin()->get_data());
  MidgardBasicElement::move_element(list_Fertigkeit_ang,list_Fertigkeit_ang_neu,MBE);
  show_alte_afert();
  show_neue_afert();
}

void Window_angeb_fert::on_clist_ang_fert_neu_select_row(gint row, gint column, GdkEvent *event)
{   
  cH_MidgardBasicElement MBE=static_cast<MidgardBasicElement*>(clist_ang_fert_neu->selection().begin()->get_data());
cout << "Befor Move: "<<list_Fertigkeit_ang_neu.size()<<' '<<list_Fertigkeit_ang.size()<<'\n';
  if(!Sinn(cH_Fertigkeit_angeborene(MBE)->Min(),MBE->Erfolgswert()))
     MidgardBasicElement::move_element(list_Fertigkeit_ang_neu,list_Fertigkeit_ang,MBE);
  else list_Fertigkeit_ang_neu.remove(MBE);
  if (wurf==100) { on_button_close_clicked(); return;}
cout << "After Move: "<<list_Fertigkeit_ang_neu.size()<<' '<<list_Fertigkeit_ang.size()<<'\n';
  show_alte_afert();
  show_neue_afert();
}

void Window_angeb_fert::show_alte_afert()
{
  clist_ang_fert_alt->clear();
  Gtk::OStream os(clist_ang_fert_alt);
cout <<"Show: "<< list_Fertigkeit_ang_neu.size()<<' '<<list_Fertigkeit_ang.size()<<'\n';

  std::map<std::string,int> SM=Werte.Sinne();
  for(std::map<std::string,int>::const_iterator i=SM.begin();i!=SM.end();++i)
   {
     os<<i->first<<'\t'<<i->second<<'\n';
   }
  os <<'\n';
  for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit_ang.begin();i!=list_Fertigkeit_ang.end();++i)
   { 
     os << (*i)->Name()<<'\t'<<(*i)->Erfolgswert()<<'\n'; 
     os.flush((*i)->ref(),&HandleContent::unref);
   }
  for (unsigned int i=0;i<clist_ang_fert_alt->columns().size();++i)
     clist_ang_fert_alt->set_column_auto_resize(i,true);
}

void Window_angeb_fert::show_neue_afert() 
{   
  clist_ang_fert_neu->clear();
  Gtk::OStream os(clist_ang_fert_neu);
  for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit_ang_neu.begin();
         i!=list_Fertigkeit_ang_neu.end();++i)
   { cH_Fertigkeit_angeborene f(*i);
     os << f->Min() <<'-'<<f->Max()<<'\t'<<f->Name()<<'\t'
        <<f->Erfolgswert()<<'\n'; 
     os.flush((*i)->ref(),&HandleContent::unref);
   }
  for (unsigned int i=0;i<clist_ang_fert_neu->columns().size();++i)
     clist_ang_fert_neu->set_column_auto_resize(i,true);
}

Window_angeb_fert::Window_angeb_fert(midgard_CG* h, 
   const Datenbank& Database,
   std::list<cH_MidgardBasicElement>& vaf, 
   Grundwerte& W,int wu)
: list_Fertigkeit_ang(vaf),Werte(W),wurf(wu)
{
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit_ang.begin();i!=Database.Fertigkeit_ang.end();++i)
   {
     if((*i)->ist_gelernt(list_Fertigkeit_ang)) continue;
     list_Fertigkeit_ang_neu.push_back(*i);
   }
 hauptfenster=h;
 if (wurf==100) 
   { label_ang_fert->set_text("100 gew�rfelt --> Fertigkeit ausw�hlen");
     show_alte_afert();
     show_neue_afert(); 
     std::string strinfo="F�r die Angeborene Fertigkeit\n wurde eine "
         +itos(wurf)+" gew�rfelt.\nangeborene Fertigkeit mit RECHTER "+
         +"Maustaste ausw�hlen.\n";
     hauptfenster->InfoFenster->AppendShow(strinfo,WindowInfo::None);
   }
 if (wurf==-1) 
   { label_ang_fert->set_text("Fertigkeit(en) ausw�hlen");
     show_alte_afert();
     show_neue_afert(); 
   }
 else gewuerfelt();
}

void Window_angeb_fert::on_button_close_clicked()
{   
//  hauptfenster->zeige_werte(Werte);
  destroy();
}

void Window_angeb_fert::gewuerfelt()
{
  for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit_ang_neu.begin();i!=list_Fertigkeit_ang_neu.end();++i)
   {
     if (cH_Fertigkeit_angeborene(*i)->Min()<=wurf && wurf<=cH_Fertigkeit_angeborene(*i)->Max()) 
      {
         name=(*i)->Name();
         if(!Sinn(wurf,(*i)->Erfolgswert()))
            MidgardBasicElement::move_element(list_Fertigkeit_ang_neu,list_Fertigkeit_ang,*i);
         break;
      }
   }  
  on_button_close_clicked();
}

bool Window_angeb_fert::Sinn(int wurf,int wert)
{
  if     ( 1<=wurf && wurf<= 2) Werte.setSinnCheck("Sehen",wert);
  else if( 3<=wurf && wurf<= 4) Werte.setSinnCheck("H�ren",wert);
  else if( 5<=wurf && wurf<= 6) Werte.setSinnCheck("Riechen",wert);
  else if( 7<=wurf && wurf<= 8) Werte.setSinnCheck("Schmecken",wert);
  else if( 9<=wurf && wurf<=10) Werte.setSinnCheck("Tasten",wert);
  else if(11<=wurf && wurf<=20) Werte.setSinn("Sehen",wert);
  else if(21<=wurf && wurf<=30) Werte.setSinn("H�ren",wert);
  else if(31<=wurf && wurf<=40) Werte.setSinn("Riechen",wert);
  else if(41<=wurf && wurf<=50) Werte.setSinn("Schmecken",wert);
  else if(51<=wurf && wurf<=60) Werte.setSinn("Tasten",wert);
  else if(61<=wurf && wurf<=65) Werte.setSinn("Sechster Sinn",wert);
  else return false;
/*
cout << "Sehen = "<<Werte.Sinne()["Sehen"]<<'\n';
cout << "H�ren = "<<Werte.Sinne()["H�ren"]<<'\n';
cout << "Riechen = "<<Werte.Sinne()["Riechen"]<<'\n';
cout << "Schmecken = "<<Werte.Sinne()["Schmecken"]<<'\n';
cout << "Tasten = "<<Werte.Sinne()["Tasten"]<<'\n';
cout << "Sechster Sinn = "<<Werte.Sinne()["Sechster Sinn"]<<'\n';
*/
  return true;
}

