// $Id: gw_wuerfeln.cc,v 1.25 2001/12/21 22:46:15 thoma Exp $
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

// generated 2001/2/2 10:59:38 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to gw_wuerfeln.cc_glade

// This file is for your program, I won't touch it again!

#include "midgard_CG.hh"
#include <strstream>
#include <algorithm>
#include <gtk--/label.h>

gint midgard_CG::on_button_grundwerte_button_release_event(GdkEventButton *ev)
{
  if (ev->button==1) 
   { gw_wuerfeln_2x();
     table_werte_wuerfeln->hide();
   }
  else if (ev->button==2)
   {
     set_werte_label_2();
     werte_label_count=0;
     gw_setzen();
     button_wert_1->set_sensitive(true);
     button_wert_2->set_sensitive(true);
     button_wert_3->set_sensitive(true);
     button_wert_4->set_sensitive(true);
     button_wert_5->set_sensitive(true);
     button_wert_6->set_sensitive(true);
     button_wert_7->hide();
     button_wert_8->hide();
     button_wert_9->hide();
     table_werte_wuerfeln->show();
     table_bw_wurf->show();
   }
  else if (ev->button==3)
   {
     std::vector<int> V;
     for(int i=0;i<9;++i) V.push_back(random.integer(1,100)) ;
     sort(V.rbegin(),V.rend());
     button_wert_1->remove();
     button_wert_1->add_label(itos(V[0]));
     button_wert_2->remove();
     button_wert_2->add_label(itos(V[1]));
     button_wert_3->remove();
     button_wert_3->add_label(itos(V[2]));
     button_wert_4->remove();
     button_wert_4->add_label(itos(V[3]));
     button_wert_5->remove();
     button_wert_5->add_label(itos(V[4]));
     button_wert_6->remove();
     button_wert_6->add_label(itos(V[5]));
     button_wert_7->remove();
     button_wert_7->add_label(itos(V[6]));
     button_wert_8->remove();
     button_wert_8->add_label(itos(V[7]));
     button_wert_9->remove();
     button_wert_9->add_label(itos(V[8]));
     werte_label_count=0;
     set_werte_label_3();
     button_wert_1->set_sensitive(true);
     button_wert_2->set_sensitive(true);
     button_wert_3->set_sensitive(true);
     button_wert_4->set_sensitive(true);
     button_wert_5->set_sensitive(true);
     button_wert_6->set_sensitive(true);
     button_wert_7->set_sensitive(false);
     button_wert_8->set_sensitive(false);
     button_wert_9->set_sensitive(false);
     button_wert_7->show();
     button_wert_8->show();
     button_wert_9->show();
     table_werte_wuerfeln->show();
   }
  button_abg_werte->set_sensitive(true);
  return false;
}

//////////////////////////////////////////////////////////////////////////
void midgard_CG::gw_setzen(Gtk::Label *L,int button)
{
  if(L) 
   {
     int w=atoi(label_besserer_wurf->get_text().c_str());
     if(L->get_text()=="St") {Werte.setSt(w); st->set_text(itos(w));}
     else if(L->get_text()=="Gs") {Werte.setGs(w); gs->set_text(itos(w));}
     else if(L->get_text()=="Gw") {Werte.setGw(w); gw->set_text(itos(w));}
     else if(L->get_text()=="Ko") {Werte.setKo(w); ko->set_text(itos(w));}
     else if(L->get_text()=="In") {Werte.setIn(w); in->set_text(itos(w));}
     else if(L->get_text()=="Zt") {Werte.setZt(w); zt->set_text(itos(w));}
   }
  if(++werte_label_count==7)
   {
    table_werte_wuerfeln->hide();
    table_bw_wurf->hide();
    return;
   }

  vector<int> V;
  for(int j=0;j<2;++j) V.push_back(random.integer(1,100)) ;
  sort(V.rbegin(),V.rend());

  label_werte->set_text("Für welche Basiseigenschaft soll der Wurf verwendet werden?") ;
  label_besserer_wurf->set_text(itos(V[0]));
  label_schlechterer_wurf->set_text("("+itos(V[1])+")");
}


void midgard_CG::set_werte_label_2()
{
  button_wert_1->remove();
  button_wert_1->add_label("St");
  button_wert_2->remove();
  button_wert_2->add_label("Gs");
  button_wert_3->remove();
  button_wert_3->add_label("Gw");
  button_wert_4->remove();
  button_wert_4->add_label("Ko");
  button_wert_5->remove();
  button_wert_5->add_label("In");
  button_wert_6->remove();
  button_wert_6->add_label("Zt");
}

//////////////////////////////////////////////////////////////////////////

void midgard_CG::set_werte_label_3(Gtk::Label *L)
{
  if(werte_label_count==0)
     label_werte->set_text("Welcher Wert soll für die  Stärke (St) verwendet werden?") ;
  else
   {
     int w=atoi(L->get_text().c_str());
     switch(werte_label_count) {
      case 1 : 
            st->set_text(L->get_text());
            Werte.setSt(w);
            label_werte->set_text("Welcher Wert soll für die  Geschicklichkeit (Gs) verwendet werden?");
            break;
      case 2 :
            gs->set_text(L->get_text());
            Werte.setGs(w);
            label_werte->set_text("Welcher Wert soll für die  Gewandheit (Gw) verwendet werden?");
            break;
      case 3 : 
            gw->set_text(L->get_text());
            Werte.setGw(w);
            label_werte->set_text("Welcher Wert soll für die  Konstitution (Ko) verwendet werden?");
            break;
      case 4 : 
            ko->set_text(L->get_text());
            Werte.setKo(w);
            label_werte->set_text("Welcher Wert soll für die  Intelligenz (In) verwendet werden?");
            break;
      case 5 : 
            in->set_text(L->get_text());
            Werte.setIn(w);
            label_werte->set_text("Welcher Wert soll für das  Zaubertalent (Zt) verwendet werden?");
            break;
      default: 
            zt->set_text(L->get_text());
            Werte.setZt(w);
            table_werte_wuerfeln->hide();
            table_bw_wurf->hide();
        } 
   }
  ++werte_label_count;
}

//////////////////////////////////////////////////////////////////////////

void midgard_CG::on_button_wert_1_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_1->get_child());
  button_wert_1->set_sensitive(false);
  if(l->get_text()=="St") gw_setzen(l,1);
  else  set_werte_label_3(l);
}
void midgard_CG::on_button_wert_2_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_2->get_child());
  button_wert_2->set_sensitive(false);
  if(l->get_text()=="Gs") gw_setzen(l,2);
  else  set_werte_label_3(l);
}
void midgard_CG::on_button_wert_3_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_3->get_child());
  button_wert_3->set_sensitive(false);
  if(l->get_text()=="Gw") gw_setzen(l,3);
  else  set_werte_label_3(l);
}
void midgard_CG::on_button_wert_4_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_4->get_child());
  button_wert_4->set_sensitive(false);
  if(l->get_text()=="Ko") gw_setzen(l,4);
  else  set_werte_label_3(l);
}
void midgard_CG::on_button_wert_5_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_5->get_child());
  button_wert_5->set_sensitive(false);
  if(l->get_text()=="In") gw_setzen(l,5);
  else  set_werte_label_3(l);
}
void midgard_CG::on_button_wert_6_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_6->get_child());
  button_wert_6->set_sensitive(false);
  if(l->get_text()=="Zt") gw_setzen(l,6);
  else  set_werte_label_3(l);
}

//////////////////////////////////////////////////////////////////////////

void midgard_CG::gw_wuerfeln_2x()
{   
 Werte.set_Basiswerte(constraint_gw(random,Werte.Spezies()->St()),
     constraint_gw(random,Werte.Spezies()->Gw()),
     constraint_gw(random,Werte.Spezies()->Gs()),
     constraint_gw(random,Werte.Spezies()->Ko()),
     constraint_gw(random,Werte.Spezies()->In()),
     constraint_gw(random,Werte.Spezies()->Zt()));
 zeige_werte(Werte);
}

int midgard_CG::constraint_gw(Random& random,int constraint)
{
 int wert;
 if      (constraint==0) wert = wuerfeln_best_of_two(random);
 else if (constraint<0) 
   do wert = random.integer(1,100);
   while (wert > -constraint);
 else if (constraint > 0) 
   { wert = wuerfeln_best_of_two(random);
     while (wert < constraint) wert = random.integer(1,100);
   }
 return wert;
}

int midgard_CG::constraint_aw(Random& random,int constraint)
{
 int wert = random.integer(1,100);
 if      (constraint==0) return wert;
 else if (constraint<0) 
   while (wert > -constraint);
 else if (constraint > 0) 
   while (wert < constraint) wert = random.integer(1,100);
 return wert;
}

int midgard_CG::wuerfeln_best_of_two(Random& random)
{
 int ran  = random.integer(1,100);
 int ran2 = random.integer(1,100);
 (ran > ran2) ? : ran=ran2;
 return ran;
}
