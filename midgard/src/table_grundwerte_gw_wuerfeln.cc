// $Id: table_grundwerte_gw_wuerfeln.cc,v 1.24 2002/11/19 12:37:51 thoma Exp $
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
#include <Misc/Trace.h>

gint table_grundwerte::on_button_grundwerte_button_release_event(GdkEventButton *ev)
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  hauptfenster->set_status("");
  if(radiobutton_eigenschaften_standard->get_active())
     Eigenschaften_variante(1);
  else if(radiobutton_eigenschaften_zuweisen->get_active())
     Eigenschaften_variante(2);
  else if(radiobutton_eigenschaften_69->get_active())
     Eigenschaften_variante(3);
  hauptfenster->undosave("Grundwerte gewürfelt");
}

void table_grundwerte::Eigenschaften_variante(int i)
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  button_abg_werte->set_sensitive(true);
  combo_typ->set_sensitive(true);
  combo_typ2->set_sensitive(true);
  combo_typ->grab_focus();
  if (i==1) 
   { gw_wuerfeln_2x();
     frame_wuerfelvariante->hide();
     check_350();
   }
  else 
   { cH_Spezies spez=hauptfenster->getWerte().Spezies();
//std::cout << spez->Name() << '\n';
     Veigenschaften.clear();
     Veigenschaften.push_back(st_eigen(est,"die Stärke","St",spez->St()));
     Veigenschaften.push_back(st_eigen(egs,"die Geschicklichkeit","Gs",spez->Gs()));
     Veigenschaften.push_back(st_eigen(egw,"die Gewandheit","Gw",spez->Gw()));
     Veigenschaften.push_back(st_eigen(eko,"die Konstitution","Ko",spez->Ko()));
     Veigenschaften.push_back(st_eigen(ein,"die Intelligenz","In",spez->In()));
     Veigenschaften.push_back(st_eigen(ezt,"das Zaubertalent","Zt",spez->Zt()));
     actual_eigen=Veigenschaften.begin();

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
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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
   {  hauptfenster->set_status("Summe der Eigenschaftswerte "+itos(sum)+" kleiner als 350. Es darf (muß aber nicht) noch einmal gewürfelt werden.",false);
      button_grundwerte->set_sensitive(true);
   }
  zeige_werte(false);
  fill_typauswahl();
  fill_typauswahl_2();
}



//////////////////////////////////////////////////////////////////////////

void table_grundwerte::gw_wuerfeln_2x()
{   
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 if      (constraint==0) return hauptfenster->random.integer(1,100);
 else if (constraint<0)  return hauptfenster->random.integer(1,-constraint); 
 else 			          return hauptfenster->random.integer(constraint,100);
}

int table_grundwerte::wuerfeln_best_of_two()
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 int ran  = hauptfenster->random.integer(1,100);
 int ran2 = hauptfenster->random.integer(1,100);
 (ran > ran2) ? : ran=ran2;
 return ran;
}

///////////////////////////////////////////////////////////////

struct spezies_mod_comp
{	bool operator()(const table_grundwerte::st_eigen &a,const table_grundwerte::st_eigen &b)
	{  return a.spezies_mod>b.spezies_mod;
	}
};

#if 0
ostream &operator<<(ostream &o,const table_grundwerte::st_eigen &a)
{  o << '{' << int(a.eigenschaft) << ',' << a.lang << ',' << a.kurz
	<< ',' << a.spezies_mod << '}';
   return o;
}
#endif

void table_grundwerte::Schwachpunkt_wuerfeln()
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  for (std::vector<st_eigen>::iterator i=Veigenschaften.begin();i!=Veigenschaften.end();)
   {  if (i->spezies_mod<0)
      {   set_Grundwerte(i->eigenschaft,constraint_gw(i->spezies_mod));
          i=Veigenschaften.erase(i);
      }
      else ++i;
   }
   actual_eigen=Veigenschaften.begin();
   
   std::sort(Veigenschaften.begin(),Veigenschaften.end(),spezies_mod_comp());
//   std::copy(Veigenschaften.begin(),Veigenschaften.end(),std::ostream_iterator<st_eigen>(std::cout,"\n"));
}

void table_grundwerte::gw_variante_2()
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  Schwachpunkt_wuerfeln();
  frame_wuerfelvariante->remove();  
  Gtk::Table *tab = manage(new class Gtk::Table(3, 6, false));
  Gtk::Label *lab = manage(new class Gtk::Label(itos(Veigenschaften.size())+"x gewürfelt, jetzt die Werte zuordnen."));
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

#if 0
enum table_grundwerte::e_eigen &operator++(enum table_grundwerte::e_eigen &s)
{  ++(int&)s;
   return s;
}
#endif

void table_grundwerte::on_button_variante_2_clicked(Gtk::Button *button,e_eigen eigenschaft)
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  button->set_sensitive(false);
  set_Grundwerte(eigenschaft,actual_wurf);
  gw_variante_2_next();
}


void table_grundwerte::gw_variante_2_next()
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(!label) return;
  std::vector<int> V;
  for(int j=0;j<2;++j) V.push_back(hauptfenster->random.integer(1,100)) ;
  sort(V.rbegin(),V.rend());
  std::string W=itos(V[0])+"("+itos(V[1])+")";
  label->set_text("Wurf: "+W+"   Für welche Eigenschaft soll dieser Wurf verwendet werden?");  
  actual_wurf=V[0];
}

///////////////////////////////////////////////////////////////////////////

void table_grundwerte::gw_variante_3()
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  Schwachpunkt_wuerfeln();
  int anz_wuerfe=3+Veigenschaften.size();
  frame_wuerfelvariante->remove();  
  std::vector<int> V;
  for(int i=0;i<anz_wuerfe;++i) V.push_back(hauptfenster->random.integer(1,100)) ;
  sort(V.rbegin(),V.rend());
            
  Gtk::Table *tab = manage(new class Gtk::Table(3, 6, false));
  Gtk::Label *lab = manage(new class Gtk::Label(itos(anz_wuerfe)+"x gewürfelt, jetzt die Werte den Eigenschaften zuordnen."));  
  tab->attach(*lab, 0, 9, 0, 1, GTK_FILL, 0, 0, 0);
  int count=0;
  for(std::vector<int>::const_iterator i=V.begin();i!=V.end();++i)
   {
     Gtk::Button *b = manage(new class Gtk::Button(itos(*i)));
     tab->attach(*b, count, count+1, 2, 3, GTK_FILL, 0, 0, 0);
     b->clicked.connect(SigC::bind(SigC::slot(static_cast<class table_grundwerte*>(this), &table_grundwerte::on_button_variante_3_clicked),b,*i));
     if(count>=anz_wuerfe-3) b->set_sensitive(false);
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
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(label)
     label->set_text("Welcher Wert soll für "+actual_eigen->lang+" ("+actual_eigen->kurz+") verwendet werden?");  
}

void table_grundwerte::on_button_variante_3_clicked(Gtk::Button *button,int wert)
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  button->set_sensitive(false);
  set_Grundwerte(actual_eigen->eigenschaft,wert);
  gw_variante_3_next();
}

//#include<gtk--/table.h>

void table_grundwerte::set_Grundwerte(e_eigen eigenschaft,int wert)
{
  ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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
  if (!tab) return; // no children 
  bool all_insensitive=true;
//  Gtk::Table_Helpers::TableList &ch=tab->children();
//  for(Gtk::Table_Helpers::TableList::iterator i=ch.begin();i!=ch.end();++i)
  for(GList *liste=GTK_TABLE(tab->gtkobj())->children;liste;liste=liste->next)
   {
     Gtk::Widget *x=Gtk::wrap(((GtkTableChild*)(liste->data))->widget);
     if(Gtk::Button::isA(x) && x->is_sensitive()) { all_insensitive=false; break; }
   }
  if(all_insensitive)
   { 
    check_350();
    frame_wuerfelvariante->hide();
    frame_wuerfelvariante->remove();
    label=0;
   }
}
