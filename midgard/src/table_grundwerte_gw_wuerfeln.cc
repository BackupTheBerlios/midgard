// $Id: table_grundwerte_gw_wuerfeln.cc,v 1.5 2002/05/27 20:36:46 thoma Exp $
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

#include "table_grundwerte.hh"
#include "midgard_CG.hh"
#include <strstream>
#include <algorithm>
#include <gtk--/label.h>
#include <Aux/itos.h>
#include <SelectMatching.h>


gint table_grundwerte::on_button_grundwerte_button_release_event(GdkEventButton *ev)
{
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active) 
      button_grundwerte->set_sensitive(false);
  if (ev->button==1) grundwerte_wuerfeln();
  if (ev->button==2) Eigenschaften_variante(2);
  if (ev->button==3) Eigenschaften_variante(3);
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::GRUNDWERTE);

  hauptfenster->getWerte().setAu(constraint_aw(
                                 hauptfenster->getCWerte().Spezies()->Au()) );
  hauptfenster->getWerte().setpA( hauptfenster->random.integer(1,100)-30 
                                 + 3*(hauptfenster->getCWerte().In()/10 
                                      + hauptfenster->getCWerte().Au()/10) );
  zeige_werte(false);
  fill_typauswahl();
  fill_typauswahl_2();
  return false;
}

void table_grundwerte::grundwerte_wuerfeln()
{
  if(radiobutton_eigenschaften_standard->get_active())
     Eigenschaften_variante(1);
  else if(radiobutton_eigenschaften_zuweisen->get_active())
     Eigenschaften_variante(2);
  else if(radiobutton_eigenschaften_69->get_active())
     Eigenschaften_variante(3);
}

void table_grundwerte::Eigenschaften_variante(int i)
{
  button_abg_werte->set_sensitive(true);
  std::vector<int> a350;
  if (i==1) 
   { gw_wuerfeln_2x();
     table_werte_wuerfeln->hide();
     std::vector<int> dummy;
     check_350(dummy);
   }
  else if (i==2)
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
  else if (i==3)
   {
     std::vector<int> V;
     for(int i=0;i<9;++i) V.push_back(hauptfenster->random.integer(1,100)) ;
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
     for(int i=0;i<6;++i) a350.push_back(V[i]) ;
   }
}

void table_grundwerte::check_350(const std::vector<int>& a)
{
  int sum=0;
  if(a.empty())
   { sum  = hauptfenster->getCWerte().St() + hauptfenster->getCWerte().Gs() + hauptfenster->getCWerte().Gw() 
          + hauptfenster->getCWerte().Ko() + hauptfenster->getCWerte().In() + hauptfenster->getCWerte().Zt(); 
   }
  else
   {
     assert(a.size()==6);
     for (std::vector<int>::const_iterator i=a.begin();i!=a.end();++i)
       sum += *i;
   }   
  if(sum<350)
   {  hauptfenster->set_status("Summe der Eigenschaftswerte "+itos(sum)+" kleiner als 350. Es darf (muß aber nicht) noch einmal gewürfelt werden.",false);
      button_grundwerte->set_sensitive(true);
//      button_abg_werte->set_sensitive(false);
//      Werte.clear();            
//      Gtk::Menu_Helpers::SelectMatching(*optionmenu_spezies,hauptfenster->getCWerte().Spezies());
   }
}



//////////////////////////////////////////////////////////////////////////
void table_grundwerte::gw_setzen(Gtk::Label *L,int button)
{
  if(L) 
   {
     int w=atoi(label_besserer_wurf->get_text().c_str());
     if(L->get_text()=="St") {hauptfenster->getWerte().setSt(w); spinbutton_st->set_value(w);}
     else if(L->get_text()=="Gs") {hauptfenster->getWerte().setGs(w); spinbutton_gs->set_value(w);}
     else if(L->get_text()=="Gw") {hauptfenster->getWerte().setGw(w); spinbutton_gw->set_value(w);}
     else if(L->get_text()=="Ko") {hauptfenster->getWerte().setKo(w); spinbutton_ko->set_value(w);}
     else if(L->get_text()=="In") {hauptfenster->getWerte().setIn(w); spinbutton_in->set_value(w);}
     else if(L->get_text()=="Zt") {hauptfenster->getWerte().setZt(w); spinbutton_zt->set_value(w);}
   }
  if(++werte_label_count==7)
   {
    table_werte_wuerfeln->hide();
    table_bw_wurf->hide();
    std::vector<int> dummy;
    check_350(dummy);
    return;
   }

  vector<int> V;
  for(int j=0;j<2;++j) V.push_back(hauptfenster->random.integer(1,100)) ;
  sort(V.rbegin(),V.rend());

  label_werte->set_text("Für welche Basiseigenschaft soll der Wurf verwendet werden?") ;
  label_besserer_wurf->set_text(itos(V[0]));
  label_schlechterer_wurf->set_text("("+itos(V[1])+")");
}


void table_grundwerte::set_werte_label_2()
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

void table_grundwerte::set_werte_label_3(Gtk::Label *L)
{
  if(werte_label_count==0)
     label_werte->set_text("Welcher Wert soll für die  Stärke (St) verwendet werden?") ;
  else
   {
     int w=atoi(L->get_text().c_str());
     switch(werte_label_count) {
      case 1 : 
            spinbutton_st->set_value(w);
            hauptfenster->getWerte().setSt(w);
            label_werte->set_text("Welcher Wert soll für die  Geschicklichkeit (Gs) verwendet werden?");
            break;
      case 2 :
            spinbutton_gs->set_value(w);
            hauptfenster->getWerte().setGs(w);
            label_werte->set_text("Welcher Wert soll für die  Gewandheit (Gw) verwendet werden?");
            break;
      case 3 : 
            spinbutton_gw->set_value(w);
            hauptfenster->getWerte().setGw(w);
            label_werte->set_text("Welcher Wert soll für die  Konstitution (Ko) verwendet werden?");
            break;
      case 4 : 
            spinbutton_ko->set_value(w);
            hauptfenster->getWerte().setKo(w);
            label_werte->set_text("Welcher Wert soll für die  Intelligenz (In) verwendet werden?");
            break;
      case 5 : 
            spinbutton_in->set_value(w);
            hauptfenster->getWerte().setIn(w);
            label_werte->set_text("Welcher Wert soll für das  Zaubertalent (Zt) verwendet werden?");
            break;
      default: 
            spinbutton_zt->set_value(w);
            hauptfenster->getWerte().setZt(w);
            table_werte_wuerfeln->hide();
            table_bw_wurf->hide();
        } 
   }
  ++werte_label_count;
}

//////////////////////////////////////////////////////////////////////////

void table_grundwerte::on_button_wert_1_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_1->get_child());
  button_wert_1->set_sensitive(false);
  if(l->get_text()=="St") gw_setzen(l,1);
  else  set_werte_label_3(l);
}
void table_grundwerte::on_button_wert_2_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_2->get_child());
  button_wert_2->set_sensitive(false);
  if(l->get_text()=="Gs") gw_setzen(l,2);
  else  set_werte_label_3(l);
}
void table_grundwerte::on_button_wert_3_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_3->get_child());
  button_wert_3->set_sensitive(false);
  if(l->get_text()=="Gw") gw_setzen(l,3);
  else  set_werte_label_3(l);
}
void table_grundwerte::on_button_wert_4_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_4->get_child());
  button_wert_4->set_sensitive(false);
  if(l->get_text()=="Ko") gw_setzen(l,4);
  else  set_werte_label_3(l);
}
void table_grundwerte::on_button_wert_5_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_5->get_child());
  button_wert_5->set_sensitive(false);
  if(l->get_text()=="In") gw_setzen(l,5);
  else  set_werte_label_3(l);
}
void table_grundwerte::on_button_wert_6_clicked()
{
  Gtk::Label *l=static_cast<Gtk::Label*>(button_wert_6->get_child());
  button_wert_6->set_sensitive(false);
  if(l->get_text()=="Zt") gw_setzen(l,6);
  else  set_werte_label_3(l);
}

//////////////////////////////////////////////////////////////////////////

void table_grundwerte::gw_wuerfeln_2x()
{   
 hauptfenster->getWerte().setBasiswerte(constraint_gw(hauptfenster->getCWerte().Spezies()->St()),
     constraint_gw(hauptfenster->getCWerte().Spezies()->Gw()),
     constraint_gw(hauptfenster->getCWerte().Spezies()->Gs()),
     constraint_gw(hauptfenster->getCWerte().Spezies()->Ko()),
     constraint_gw(hauptfenster->getCWerte().Spezies()->In()),
     constraint_gw(hauptfenster->getCWerte().Spezies()->Zt()));
// zeige_werte(false);
// hauptfenster->zeige_werte();
}

//static inline int max(int a,int b) { return a>b?a:b; }

int table_grundwerte::constraint_gw(int constraint)
{
 int wert;
 if      (constraint==0) wert = wuerfeln_best_of_two();
 else if (constraint<0) 
 {  do wert = hauptfenster->random.integer(1,100);
    while (wert > -constraint);
 }
 else if (constraint > 0) 
   { wert = wuerfeln_best_of_two();
     while (wert < constraint) wert = hauptfenster->random.integer(1,100);
   }
 return wert;
}

int table_grundwerte::constraint_aw(int constraint)
{
 if      (constraint==0) return hauptfenster->random.integer(1,100);
 else if (constraint<0)  return hauptfenster->random.integer(1,-constraint); 
 else 			          return hauptfenster->random.integer(constraint,100);
}

int table_grundwerte::wuerfeln_best_of_two()
{
 int ran  = hauptfenster->random.integer(1,100);
 int ran2 = hauptfenster->random.integer(1,100);
 (ran > ran2) ? : ran=ran2;
 return ran;
}
