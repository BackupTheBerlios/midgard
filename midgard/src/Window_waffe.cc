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

// generated 2001/3/12 22:18:09 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_waffe.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_waffe.hh"
#include <Gtk_OStream.h>
#include "itos.h"
#include "WindowInfo.hh"
#include "midgard_CG.hh"
#include "Window_Waffe_Geld.hh"

void Window_waffe::on_clist_waffe_select_row(gint row, gint column, GdkEvent *event)
{   
  oberfenster->get_waffe(clist_waffe->get_text(row,0));
  destroy();
}

Window_waffe::Window_waffe(int _wurf, 
      Window_Waffe_Geld* o, Grundwerte& W,const vector<cH_Typen>& T, 
      const midgard_CG::st_Database& _Database,
      const std::list<cH_MidgardBasicElement>& wa)
:Database(_Database),wurf(_wurf),list_Waffen(wa) ,Werte(W), Typ(T)
{
  oberfenster=o;
  wuerfeln();
}

void Window_waffe::wuerfeln()
{
 std::string strinfo = "Für die Waffenauswahl wurde eine "+itos(wurf)
            +" gewürfelt,\n der Stand ist "+Werte.Stand()+"\n ---> ";
 if ( 1<=wurf&&wurf<=10)
   {
       Werte.add_Kupfer(10);  strinfo+="10 Kupferstücke";
       manage(new WindowInfo(strinfo));      
       oberfenster->show_Geld();
       destroy();
       return;
   }
 Gtk::OStream os(clist_waffe);
 std::string aartE,aartS,aartW,aartZ,aartA;
 if (wurf!=-1) get_art(aartE,aartS,aartW,aartZ,aartA);
 if (wurf==-1) aartA="A";

 for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Waffe.begin();i!=Database.Waffe.end();++i)
  {  
    cH_Waffe w(*i);
    if (w->Name() == "waffenloser Kampf") continue;
    if ((*i)->ist_gelernt(list_Waffen))
//     if (w->ist_lernbar(Typ,w->get_MapTyp()))
       if  ((aartE =="E" && w->Art2()=="E") ||
            (aartW =="W" && w->Art2()=="W") ||
            (aartS =="S" && w->Art2()=="S") ||
            (aartZ =="Z" && w->Art2()=="Z") ||
            (aartA =="A") )
         os << w->Name() <<"\t"<<w->Grundkenntnis()
            <<"\t"<<w->Schaden(w->Name())+"+"
            +itos(w->Schaden_Bonus(w->Name()))<<"\n";
  }
 if (aartE=="E") strinfo += "Einhandwaffe ";
 if (aartS=="S") strinfo += "Schußwaffe " ;
 if (aartW=="W") strinfo += "Wurfwaffe " ;
 if (aartZ=="Z") strinfo += "Zweihandwaffe " ;
 if (aartA=="A") strinfo += "Beliebige Waffe" ;
 if (wurf !=-1) manage(new WindowInfo(strinfo));

 for (unsigned int i=0;i<clist_waffe->columns().size();++i)
   clist_waffe->set_column_auto_resize(i,true);  
}


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

void Window_waffe::magische_Waffe()
{
   std::string strinfo="100 gewürfelt!!! => magische Einhandwaffe\n";
      strinfo+= "bitte unter 'steigern'->'Besitztümer' einen Angriffsbonus von +1 einstellen.\n";
   manage(new WindowInfo(strinfo));   
}
