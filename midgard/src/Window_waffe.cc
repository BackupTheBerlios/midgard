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
#include "Window_waffe.hh"
#include "Waffe.hh"
#include <Gtk_OStream.h>
#include <Aux/itos.h>
#include "midgard_CG.hh"
//#include "Window_Waffe_Geld.hh"


Window_waffe::Window_waffe(int _wurf, 
      midgard_CG* h, Grundwerte& W,const vector<cH_Typen>& T, 
      const Datenbank& _Database,
      const std::list<cH_MidgardBasicElement>& wa)
:Database(_Database),wurf(_wurf),list_Waffen(wa) ,Werte(W), Typ(T)
{
  hauptfenster=h;
  wuerfeln();
}

void Window_waffe::wuerfeln()
{
 std::string strinfo = "Für die Waffenauswahl wurde eine "+itos(wurf)
            +" gewürfelt,\n die Abenteurerklasse ist "+Typ[0]->Name(Werte.Geschlecht())+"\n ---> \n";

 Gtk::OStream os(clist_waffe);
// std::string aartE,aartS,aartW,aartZ,aartA;
// if (wurf!=-1) get_art(aartE,aartS,aartW,aartZ,aartA);
// if (wurf==-1) aartA="A";
 int E=0,A=0;
 bool M=false;
 if (Typ[0]->Geld() == 1) 
  { if      ( 1<=wurf&&wurf<=10 ) { E=3;      }
    else if (11<=wurf&&wurf<=20 ) { E=3; A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=2; A=2; }
    else if (31<=wurf&&wurf<=60 ) { E=3; A=2; }
    else if (61<=wurf&&wurf<=80 ) { E=2; A=3; }
    else if (81<=wurf&&wurf<=95 ) {      A=5; }
    else if (96<=wurf&&wurf<=100) { E=1; A=4; M=true; }
  }  
 if (Typ[0]->Geld() == 2) 
  { if      ( 1<=wurf&&wurf<=10 ) { E=2;      }
    else if (11<=wurf&&wurf<=20 ) { E=1; A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=2; A=1; }
    else if (31<=wurf&&wurf<=60 ) { E=3; A=1; }
    else if (61<=wurf&&wurf<=80 ) { E=2; A=2; }
    else if (81<=wurf&&wurf<=95 ) {      A=4; }
    else if (96<=wurf&&wurf<=100) { E=1; A=3; M=true; }
  }  
 if (Typ[0]->Geld() == 3) 
  { if      ( 1<=wurf&&wurf<=10 ) { E=1;      }
    else if (11<=wurf&&wurf<=20 ) {      A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=2;      }
    else if (31<=wurf&&wurf<=60 ) { E=1; A=1; }
    else if (61<=wurf&&wurf<=80 ) { E=1; A=1; }
    else if (81<=wurf&&wurf<=95 ) {      A=2; }
    else if (96<=wurf&&wurf<=100) { E=1; A=1; M=true; }
  }  
 if (Typ[0]->Geld() == 4) 
  { if      ( 1<=wurf&&wurf<=10 ) { E=2;      }
    else if (11<=wurf&&wurf<=20 ) { E=1; A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=3;      }
    else if (31<=wurf&&wurf<=60 ) { E=2; A=1; }
    else if (61<=wurf&&wurf<=80 ) { E=1; A=2; }
    else if (81<=wurf&&wurf<=95 ) {      A=3; }
    else if (96<=wurf&&wurf<=100) { E=1; A=2; M=true; }
  }  

 strinfo += "Es dürfen gewählt werden:\n"
            +itos(E)+" Einhandwaffen und "
            +itos(A)+" Beliebige Waffen und/oder Schilde\n";


 for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Waffe.begin();i!=Database.Waffe.end();++i)
  {  
    cH_Waffe w(*i);
//    cH_MidgardBasicElement WB= new WaffeBesitz(cH_Waffe(*i),"",w->Region(w->Name()),0,0,"");
    cH_MidgardBasicElement WB= new WaffeBesitz(cH_Waffe(*i),"",0,0,"");
    if (w->Name() == "waffenloser Kampf") continue;
    if ((*i)->ist_gelernt(list_Waffen))
      {
         os << w->Art2()<<'\t'<<w->Name() <<'\t'<<w->Grundkenntnis()
            <<'\t'<<w->Schaden(w->Name())+"+"
            +itos(w->Schaden_Bonus(w->Name()))<<"\n";
//         os.flush((*i)->ref(),&HandleContent::unref);
         os.flush(WB->ref(),&HandleContent::unref);
      }  
  }
 hauptfenster->InfoFenster->AppendShow(strinfo);
 label_anzahl_E->set_text(itos(E));
 label_anzahl_A->set_text(itos(A));

 for (unsigned int i=0;i<clist_waffe->columns().size();++i)
   clist_waffe->set_column_auto_resize(i,true);  
 clist_waffe->set_selection_mode(GTK_SELECTION_MULTIPLE);
}

void Window_waffe::on_clist_waffe_select_row(gint row, gint column, GdkEvent *event)
{   
  std::string art= clist_waffe->get_text(row,0);
  int E=atoi(label_anzahl_E->get_text().c_str());
  int A=atoi(label_anzahl_A->get_text().c_str());

  if( (art=="E" || art=="W" || art=="V") && E>0)
     label_anzahl_E->set_text(itos(--E));
  else if(A>0)
     label_anzahl_A->set_text(itos(--A));
  else 
     clist_waffe->row(row).unselect();   
}


void Window_waffe::on_button_close_clicked()
{
  std::list<cH_MidgardBasicElement> V;
  for (Gtk::CList::SelectionList::iterator i=clist_waffe->selection().begin();i!=clist_waffe->selection().end();++i)
   {
     cH_MidgardBasicElement mbe=static_cast<MidgardBasicElement*>(i->get_data());
     V.push_back(mbe);
   }
  hauptfenster->MidgardBasicElement_uebernehmen(V);
  destroy();
}


/*
void Window_waffe::get_art(std::string& aartE,std::string& aartS, std::string& aartW, std::string& aartZ, std::string& aartA)
{
        if (Werte.Stand() == "Unfrei")
         {
          if (11<=wurf&&wurf<=20){aartE="E";} 
          if (21<=wurf&&wurf<=40){aartE="E";} 
          if (41<=wurf&&wurf<=60){aartE="E";aartS="S";} 
          if (61<=wurf&&wurf<=80){aartE="E";aartW="W";aartS="S";} 
          if (81<=wurf&&wurf<=90){aartA="A";} 
          if (91<=wurf&&wurf<=99){aartA="A";} 
          if (wurf==100){aartE="E";magische_Waffe();} 
         }
        if (Werte.Stand() == "Volk")
         {
          if (11<=wurf&&wurf<=20){aartE="E";} 
          if (21<=wurf&&wurf<=40){aartE="E";} 
          if (41<=wurf&&wurf<=60){aartE="E";aartW="W";} 
          if (61<=wurf&&wurf<=80){aartE="E";aartW="W";aartS="S";} 
          if (81<=wurf&&wurf<=90){aartA="A";} 
          if (91<=wurf&&wurf<=99){aartA="A";} 
          if (wurf==100){aartE="E";magische_Waffe();} 
         }
        if (Werte.Stand() == "Mittelschicht")
         {
          if (11<=wurf&&wurf<=20){aartE="E";} 
          if (21<=wurf&&wurf<=40){aartE="E";} 
          if (41<=wurf&&wurf<=60){aartE="E";aartW="W";} 
          if (61<=wurf&&wurf<=80){aartE="E";aartW="W";aartS="S";} 
          if (81<=wurf&&wurf<=90){aartA="A";} 
          if (91<=wurf&&wurf<=99){aartA="A";} 
          if (wurf==100){aartE="E";magische_Waffe();} 
         }
        if (Werte.Stand() == "Adel")
         {
          if (11<=wurf&&wurf<=20){aartE="E";} 
          if (21<=wurf&&wurf<=40){aartE="E";} 
          if (41<=wurf&&wurf<=60){aartE="E";aartZ="Z";} 
          if (61<=wurf&&wurf<=80){aartE="E";aartZ="Z";} 
          if (81<=wurf&&wurf<=90){aartA="A";} 
          if (91<=wurf&&wurf<=99){aartA="A";} 
          if (wurf==100){aartE="E";magische_Waffe();} 
         }
}
*/

void Window_waffe::magische_Waffe()
{
   std::string strinfo="100 gewürfelt!!! => magische Einhandwaffe\n";
      strinfo+= "bitte unter 'steigern'->'Besitztümer' einen Angriffsbonus von +1 einstellen.\n";
   hauptfenster->InfoFenster->AppendShow(strinfo);   
}
