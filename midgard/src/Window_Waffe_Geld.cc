// $Id: Window_Waffe_Geld.cc,v 1.36 2002/01/14 10:29:27 thoma Exp $
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
#include "zufall.h"
#include "Waffe.hh"

void Window_Waffe_Geld::on_button_geld_clicked()
{   
   button_geld->set_sensitive(false);

   if (radio_auswaehlen->get_active()) 
       manage (new Window_Geld_eingeben(this,Werte));
   else    
       Geld() ;
}

void Window_Waffe_Geld::on_button_waffe_clicked()
{   
   button_waffe->set_sensitive(false);
   if (radio_auswaehlen->get_active()) 
      manage (new Window_waffe(-1,this,Werte,Typ,Database,list_Waffen));
   else
    {
      Random random;
      int wurf = random.integer(1,100);
      manage (new Window_waffe(wurf,this,Werte,Typ,Database,list_Waffen));
    }
}

void Window_Waffe_Geld::on_button_close_clicked()
{
  std::list<cH_MidgardBasicElement> waffe;
  for (unsigned int i=0;i<clist_gewaehlte_waffen->rows().size();++i)
   {
     std::string swaffe=clist_gewaehlte_waffen->get_text(i,0);
     waffe.push_back(new WaffeBesitz(cH_Waffe(swaffe),swaffe,"",0,0,""));
   }
  hauptfenster->waffe_besitz_uebernehmen(waffe);
  hauptfenster->Geld_uebernehmen();
  destroy();
}

Window_Waffe_Geld::Window_Waffe_Geld(midgard_CG* h, Grundwerte& w,
      const vector<cH_Typen>& T, 
      const Datenbank& _Database,
      const std::list<cH_MidgardBasicElement>& wa)
: Database(_Database),Werte(w), Typ(T), list_Waffen(wa)
{
   hauptfenster = h;
   button_geld->set_sensitive(true);
   button_waffe->set_sensitive(true);

// Midgard 3 Version:
  label_waffen_geld->hide();
}

void Window_Waffe_Geld::get_waffe(const vector<cH_MidgardBasicElement>& waffe)
{
  Gtk::OStream os(clist_gewaehlte_waffen);
  for(vector<cH_MidgardBasicElement>::const_iterator i=waffe.begin();i!=waffe.end();++i)
     os << (*i)->Name() <<"\n"; 
}

void Window_Waffe_Geld::show_Geld()
{
 gold->set_text(itos(Werte.Gold()));
 silber->set_text(itos(Werte.Silber()));
 kupfer->set_text(itos(Werte.Kupfer()));
}

void Window_Waffe_Geld::Geld()
{
 Random random;
 int igold=0;
 vector<int> V;
 for(int i=0;i<3;++i) V.push_back(random.integer(1,6));
 igold=V[0]+V[1]+V[2];
 if      (Typ[0]->Geld() == 1) igold-=3;
 else if (Typ[0]->Geld() == 2) igold+=0;
 else if (Typ[0]->Geld() == 3) igold+=6;
 else if (Typ[0]->Geld() == 4) igold+=3;
 if(V[0]==V[1] && V[1]==V[2]) igold += 100;

 if(Werte.Stand()=="Adel" ) igold*=3;
 if(Werte.Stand()=="Unfrei" ) igold/=2;

 std::string strinfo ="Beim Auswürfeln von Geld wurden \n"
   +itos(V[0])+"  "+itos(V[1])+"  "+itos(V[2])+"\n gewürfelt\n";
 manage (new WindowInfo(strinfo));
 Werte.addGold(igold);
 gold->set_text(itos(Werte.Gold()));
// silber->set_text(itos(Werte.Silber()));
// kupfer->set_text(itos(Werte.Kupfer()));
}

