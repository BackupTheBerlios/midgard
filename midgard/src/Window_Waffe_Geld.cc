// $Id: Window_Waffe_Geld.cc,v 1.19 2001/06/06 19:06:42 thoma Exp $
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

// generated 2001/3/11 22:34:10 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Waffe_Geld.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_Waffe_Geld.hh"
#include "Window_Geld_eingeben.hh"
#include "itos.h"
#include "midgard_CG.hh"
#include "WindowInfo.hh"
#include "Window_waffe.hh"
#include <Gtk_OStream.h>

void Window_Waffe_Geld::on_button_wuerfeln_clicked()
{   
   static int count = 0;
   ++count;
   if (count>6) { string strinfo="Schon 6x gewürfelt\n"; 
      manage (new WindowInfo(strinfo)); return; }
   string s= itos(count)+"x von 6x für Waffen oder Geld gewürfelt";
   label_waffen_geld->set_text(s);
   Random random;
   int wurf = random.integer(1,100);
   if (radio_geld->get_active()) Window_Waffe_Geld::Geld(wurf);
   if (radio_waffe->get_active()) Window_Waffe_Geld::Waffe(wurf);
}

void Window_Waffe_Geld::on_button_auswaehlen_clicked()
{   
 if (radio_geld->get_active()) manage (new Window_Geld_eingeben::Window_Geld_eingeben(this,werte));
 if (radio_waffe->get_active()) Window_Waffe_Geld::Waffe();
}

void Window_Waffe_Geld::on_button_close_clicked()
{
  vector<st_waffen_besitz> waffe;
  for (unsigned int i=0;i<clist_gewaehlte_waffen->rows().size();++i)
   {
     string swaffe=clist_gewaehlte_waffen->get_text(i,0);
     waffe.push_back(st_waffen_besitz(swaffe,swaffe,"",0,0,""));
   }
  hauptfenster->waffe_besitz_uebernehmen(waffe);
  destroy();
}

Window_Waffe_Geld::Window_Waffe_Geld(midgard_CG* h, st_werte& w, vector<st_ausgewaehlte_waffen>& wa)
: werte(w), vec_waffen(wa)
{
   hauptfenster = h;
}

void Window_Waffe_Geld::Waffe(int wurf)
{
 manage (new Window_waffe(wurf,hauptfenster,this,werte,vec_waffen));
}
 
void Window_Waffe_Geld::Waffe()
{
 manage (new Window_waffe(-1,hauptfenster,this,werte,vec_waffen));
}

void Window_Waffe_Geld::get_waffe(const string& waffe)
{
  Gtk::OStream os(clist_gewaehlte_waffen);
  os << waffe<<"\n"; 
}


void Window_Waffe_Geld::Geld()
{
 gold->set_text(itos(werte.gold));
 silber->set_text(itos(werte.silber));
 kupfer->set_text(itos(werte.kupfer));
}


void Window_Waffe_Geld::Geld(int wurf)
{
 string stand = werte.stand;
 if (stand == "Unfrei")
     {
      if ( 1 <= wurf && wurf  <= 10 ) {werte.kupfer += 1;  }
      if (11 <= wurf && wurf  <= 20 ) {werte.silber += 5;  }
      if (21 <= wurf && wurf  <= 40 ) {werte.gold   += 1;  }
      if (41 <= wurf && wurf  <= 60 ) {werte.silber += 15;  }
      if (61 <= wurf && wurf  <= 80 ) {werte.gold   += 2;  }
      if (81 <= wurf && wurf  <= 90 ) {werte.silber += 25;  }
      if (91 <= wurf && wurf  <= 99 ) {werte.gold   += 3;  }
      if (99 <  wurf && wurf  <= 100 ){werte.gold   += 100;  }
     }
 if (stand == "Volk")
     {
      if ( 1 <= wurf && wurf  <= 10 ) {werte.silber += 1;  }
      if (11 <= wurf && wurf  <= 20 ) {werte.gold   += 1;  }
      if (21 <= wurf && wurf  <= 40 ) {werte.silber += 15;  }
      if (41 <= wurf && wurf  <= 60 ) {werte.gold   += 2;  }
      if (61 <= wurf && wurf  <= 80 ) {werte.silber += 25;  }
      if (81 <= wurf && wurf  <= 90 ) {werte.gold   += 3;  }
      if (91 <= wurf && wurf  <= 99 ) {werte.gold   += 5;  }
      if (99 <  wurf && wurf  <= 100 ){werte.gold   += 100;  }
     }
 if (stand == "Mittelschicht")
     {
      if ( 1 <= wurf && wurf  <= 10 ) {werte.silber += 5;  }
      if (11 <= wurf && wurf  <= 20 ) {werte.gold   += 1;  }
      if (21 <= wurf && wurf  <= 40 ) {werte.gold   += 2;  }
      if (41 <= wurf && wurf  <= 60 ) {werte.gold   += 3;  }
      if (61 <= wurf && wurf  <= 80 ) {werte.gold   += 4;  }
      if (81 <= wurf && wurf  <= 90 ) {werte.gold   += 5;  }
      if (91 <= wurf && wurf  <= 99 ) {werte.gold   += 8;  }
      if (99 <  wurf && wurf  <= 100 ){werte.gold   += 100;  }
     }
 if (stand == "Adel")
     {
      if ( 1 <= wurf && wurf  <= 10 ) {werte.silber += 5;  }
      if (11 <= wurf && wurf  <= 20 ) {werte.gold   += 1;  }
      if (21 <= wurf && wurf  <= 40 ) {werte.gold   += 3;  }
      if (41 <= wurf && wurf  <= 60 ) {werte.gold   += 5;  }
      if (61 <= wurf && wurf  <= 80 ) {werte.gold   += 7;  }
      if (81 <= wurf && wurf  <= 90 ) {werte.gold   += 10;  }
      if (91 <= wurf && wurf  <= 99 ) {werte.gold   += 10;  }
      if (99 <  wurf && wurf  <= 100 ){werte.gold   += 100;  }
     }
 string strinfo ="Beim Auswürfeln von Geld wurde eine \n"+itos(wurf)+" gewürfelt\n";
 manage (new WindowInfo(strinfo));
 gold->set_text(itos(werte.gold));
 silber->set_text(itos(werte.silber));
 kupfer->set_text(itos(werte.kupfer));
}

