// $Id: table_grundwerte_gw_wuerfeln.cc,v 1.18 2002/10/24 07:58:34 thoma Exp $
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
#include <Misc/itos.h>
#include <SelectMatching.h>


gint table_grundwerte::on_button_grundwerte_button_release_event(GdkEventButton *ev)
{
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active) 
      button_grundwerte->set_sensitive(false);
  if (ev->button==1) grundwerte_wuerfeln();
  if (ev->button==2) Eigenschaften_variante(2);
  if (ev->button==3) Eigenschaften_variante(3);
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::GRUNDWERTE);

  if(!hauptfenster->MOptionen->OptionenCheck(Midgard_Optionen::NSC_only).active)
      combo_spezies->set_sensitive(false);
  return false;
}

void table_grundwerte::grundwerte_wuerfeln()
{
  hauptfenster->set_status("");
  if(radiobutton_eigenschaften_standard->get_active())
     Eigenschaften_variante(1);
  else if(radiobutton_eigenschaften_zuweisen->get_active())
     Eigenschaften_variante(2);
  else if(radiobutton_eigenschaften_69->get_active())
     Eigenschaften_variante(3);
  hauptfenster->undosave("Grundwerte gew�rfelt");
}

void table_grundwerte::Eigenschaften_variante(int i)
{
  button_abg_werte->set_sensitive(true);
  combo_typ->set_sensitive(true);
  combo_typ->grab_focus();
  if (i==1) 
   { gw_wuerfeln_2x();
     frame_wuerfelvariante->hide();
     check_350();
   }
  else 
   {
     Veigenschaften.clear();
     Veigenschaften.push_back(st_eigen(est,"die St�rke","St"));
     Veigenschaften.push_back(st_eigen(egs,"die Geschicklichkeit","Gs"));
     Veigenschaften.push_back(st_eigen(egw,"die Gewandheit","Gw"));
     Veigenschaften.push_back(st_eigen(eko,"die Konstitution","Ko"));
     Veigenschaften.push_back(st_eigen(ein,"die Intelligenz","In"));
     Veigenschaften.push_back(st_eigen(ezt,"das Zaubertalent","Zt"));
     actual_eigen=est;

     if      (i==2)  gw_variante_2();
     else if (i==3)  gw_variante_3();
     frame_wuerfelvariante->show();
   }
  hauptfenster->getWerte().setAu(constraint_aw(
                                 hauptfenster->getWerte().Spezies()->Au()) );
  hauptfenster->getWerte().setpA( hauptfenster->random.integer(1,100)-30 
                                 + 3*(hauptfenster->getWerte().In()/10 
                                      + hauptfenster->getWerte().Au()/10) );
  
}

void table_grundwerte::check_350(const std::vector<int>& a)
{
  int sum=0;
  if(a.empty())
   { sum  = hauptfenster->getWerte().St() + hauptfenster->getWerte().Gs() + hauptfenster->getWerte().Gw() 
          + hauptfenster->getWerte().Ko() + hauptfenster->getWerte().In() + hauptfenster->getWerte().Zt(); 
   }
  else
   {
     assert(a.size()==6);
     for (std::vector<int>::const_iterator i=a.begin();i!=a.end();++i)
       sum += *i;
   }   
  if(sum<350)
   {  hauptfenster->set_status("Summe der Eigenschaftswerte "+itos(sum)+" kleiner als 350. Es darf (mu� aber nicht) noch einmal gew�rfelt werden.",false);
      button_grundwerte->set_sensitive(true);
   }
  zeige_werte(false);
  fill_typauswahl();
  fill_typauswahl_2();
}



//////////////////////////////////////////////////////////////////////////

void table_grundwerte::gw_wuerfeln_2x()
{   
 hauptfenster->getWerte().setBasiswerte(constraint_gw(hauptfenster->getWerte().Spezies()->St()),
     constraint_gw(hauptfenster->getWerte().Spezies()->Gw()),
     constraint_gw(hauptfenster->getWerte().Spezies()->Gs()),
     constraint_gw(hauptfenster->getWerte().Spezies()->Ko()),
     constraint_gw(hauptfenster->getWerte().Spezies()->In()),
     constraint_gw(hauptfenster->getWerte().Spezies()->Zt()));
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

///////////////////////////////////////////////////////////////


void table_grundwerte::gw_variante_2()
{
  frame_wuerfelvariante->remove();  
  Gtk::Table *tab = manage(new class Gtk::Table(3, 6, false));
  Gtk::Label *lab = manage(new class Gtk::Label("6x gew�rfelt, jetzt die Werte zuordnen."));  
  tab->attach(*lab, 0, int(eMAX), 0, 1, GTK_FILL, 0, 0, 0);
  int count=0;
  for(std::vector<st_eigen>::const_iterator i=Veigenschaften.begin();i!=Veigenschaften.end();++i)
   {
     Gtk::Button *b = manage(new class Gtk::Button(i->kurz));
     tab->attach(*b, count, count+1, 2, 3, GTK_FILL, 0, 0, 0);
     b->clicked.connect(SigC::bind(SigC::slot(static_cast<class table_grundwerte*>(this), &table_grundwerte::on_button_variante_2_clicked),b,i->eigenschaft));
     ++count;     
   }
//  if(label) delete label;
  label = manage(new class Gtk::Label("XXX"));  
  tab->attach(*label, 0, int(eMAX), 1, 2, GTK_FILL, 0, 0, 0);
  frame_wuerfelvariante->add(*tab);
  frame_wuerfelvariante->show_all();
  gw_variante_2_next();
}

enum table_grundwerte::e_eigen &operator++(enum table_grundwerte::e_eigen &s)
{  return (enum table_grundwerte::e_eigen)(++(int&)s);
}


void table_grundwerte::on_button_variante_2_clicked(Gtk::Button *button,e_eigen eigenschaft)
{
  button->set_sensitive(false);
  set_Grundwerte(eigenschaft,actual_wurf);
  gw_variante_2_next();
}


void table_grundwerte::gw_variante_2_next()
{
  if(!label) return;
  std::vector<int> V;
  for(int j=0;j<2;++j) V.push_back(hauptfenster->random.integer(1,100)) ;
  sort(V.rbegin(),V.rend());
  std::string W=itos(V[0])+"("+itos(V[1])+")";
  label->set_text("Wurf: "+W+"   F�r welche Eigenschaft soll dieser Wurf verwendet werden?");  
  actual_wurf=V[0];
}

///////////////////////////////////////////////////////////////////////////

void table_grundwerte::gw_variante_3()
{
  frame_wuerfelvariante->remove();  
  std::vector<int> V;
  for(int i=0;i<9;++i) V.push_back(hauptfenster->random.integer(1,100)) ;
  sort(V.rbegin(),V.rend());
            
  Gtk::Table *tab = manage(new class Gtk::Table(3, 6, false));
  Gtk::Label *lab = manage(new class Gtk::Label("9x gew�rfelt, jetzt die Werte den Eigenschaften zuordnen."));  
  tab->attach(*lab, 0, 9, 0, 1, GTK_FILL, 0, 0, 0);
  int count=0;
  for(std::vector<int>::const_iterator i=V.begin();i!=V.end();++i)
   {
     Gtk::Button *b = manage(new class Gtk::Button(itos(*i)));
     tab->attach(*b, count, count+1, 2, 3, GTK_FILL, 0, 0, 0);
     b->clicked.connect(SigC::bind(SigC::slot(static_cast<class table_grundwerte*>(this), &table_grundwerte::on_button_variante_3_clicked),b,*i));
     if(count>5) b->set_sensitive(false);
     ++count;     
   }
//  if(label) delete label;
  label = manage(new class Gtk::Label("XXX"));  
  tab->attach(*label, 0, 9, 1, 2, GTK_FILL, 0, 0, 0);
  frame_wuerfelvariante->add(*tab);
  frame_wuerfelvariante->show_all();
  gw_variante_3_next();
}


void table_grundwerte::gw_variante_3_next()
{
  std::vector<st_eigen>::const_iterator i=find(Veigenschaften.begin(),Veigenschaften.end(),actual_eigen);
  if(label)
     label->set_text("Welcher Wert soll f�r "+i->lang+" ("+i->kurz+") verwendet werden?");  
}

void table_grundwerte::on_button_variante_3_clicked(Gtk::Button *button,int wert)
{
  button->set_sensitive(false);
  set_Grundwerte(actual_eigen,wert);
  gw_variante_3_next();
}

//#include<gtk--/table.h>

void table_grundwerte::set_Grundwerte(e_eigen eigenschaft,int wert)
{
  switch(eigenschaft) {
     case est : hauptfenster->getWerte().setSt(wert); break;
     case egw : hauptfenster->getWerte().setGw(wert); break;
     case egs : hauptfenster->getWerte().setGs(wert); break;
     case eko : hauptfenster->getWerte().setKo(wert); break;
     case ein : hauptfenster->getWerte().setIn(wert); break;
     case ezt : hauptfenster->getWerte().setZt(wert); break;
     case eMAX : assert(!"never get here");
   }
  ++actual_eigen;
  zeige_werte(false);

  Gtk::Table *tab = dynamic_cast<Gtk::Table*>(frame_wuerfelvariante->get_child());
  bool all_insensitive=true;
//  Gtk::Table_Helpers::TableList &ch=tab->children();
//  for(Gtk::Table_Helpers::TableList::iterator i=ch.begin();i!=ch.end();++i)
  for(GList *liste=GTK_TABLE(tab->gtkobj())->children;liste;liste=liste->next)
   {
     Gtk::Widget *x=Gtk::wrap(((GtkTableChild*)(liste->data))->widget);
     if(Gtk::Button::isA(x) && x->is_sensitive()) all_insensitive=false;
   }
  if(all_insensitive)
   { 
    check_350();
    frame_wuerfelvariante->hide();
    frame_wuerfelvariante->remove();
    label=0;
   }
}
