// $Id: table_lernschema_waffen.cc,v 1.43 2004/08/31 16:58:28 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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
#include <Gtk_OStream.h>
#include <Misc/itos.h>
#include "class_SimpleTree.hh"
#include "midgard_CG.hh"
#include "LernListen.hh"
#include <libmagus/Random.hh>
#include <libmagus/Ausgabe.hh>

void table_lernschema::on_button_lernschema_waffen()
{
  if(hauptfenster->getAben().List_Waffen().empty()) 
   { Ausgabe(Ausgabe::Error,"Noch keine Waffen gewählt"); return ;}
  for(std::list<H_WaffeBesitz>::const_iterator i=hauptfenster->getAben().List_Waffen_besitz().begin();i!=hauptfenster->getAben().List_Waffen_besitz().end();++i)
   {
     AusruestungBaum &AB=hauptfenster->getAben().getAusruestung_as_parent((**i)->Name());
     AusruestungBaum *Parent = AB.getParent();
     if(Parent)  Parent->remove(AB); 
     else Ausgabe(Ausgabe::Error,"Keine Herkunftsnode gesetzt");
   }
  hauptfenster->getAben().List_Waffen_besitz().clear();
  hauptfenster->getChar().getWizard().done(Wizard::WAFFEN,hauptfenster->getAben());
  if(!hauptfenster->getAben().getOptionen().OptionenCheck(Optionen::NSC_only).active)
     button_lernschema_waffen->set_sensitive(false);

     table_waffen_lernschema_eingabe->hide();
     int wurf = Random::integer(1,100);
     WaffenBesitz_lernschema_wuerfeln(wurf);     
#if 0   
  else if (ev->button==3)
   {
     gwr_auswahl=EWaffen;
     set_gwr_eingabe();
   }
  return 0;
#endif  
}

bool table_lernschema::on_spinbutton_waffen_lernschema_focus_in_event(GdkEventFocus *ev)
{spinbutton_waffen->select_region(0,-1); return false;}

void table_lernschema::on_spinbutton_waffen_lernschema_activate()
{
  assert(gwr_auswahl!=ENone);
  spinbutton_waffen_lernschema->update();
  if(gwr_auswahl==EWaffen)
   {
     WaffenBesitz_lernschema_wuerfeln(spinbutton_waffen_lernschema->get_value_as_int());
     table_waffen_lernschema_eingabe->hide();
     gwr_auswahl=ENone;  
   }
  else if(gwr_auswahl==ERuestung)
   {
     on_button_ruestung_clicked(spinbutton_waffen_lernschema->get_value_as_int());
     table_waffen_lernschema_eingabe->hide();
     gwr_auswahl=ENone;  
   }
  else if(gwr_auswahl==EGeld1)
     { vabenteurer->getLernpunkte().getVGeldwurf().clear();
       vabenteurer->getLernpunkte().getVGeldwurf().push_back(spinbutton_waffen_lernschema->get_value_as_int());
       gwr_auswahl=EGeld2;
       set_gwr_eingabe();       
     }
  else if(gwr_auswahl==EGeld2)
     { 
       vabenteurer->getLernpunkte().getVGeldwurf().push_back(spinbutton_waffen_lernschema->get_value_as_int());
       gwr_auswahl=EGeld3;
       set_gwr_eingabe();       
     }
  else if(gwr_auswahl==EGeld3)
     { 
       vabenteurer->getLernpunkte().getVGeldwurf().push_back(spinbutton_waffen_lernschema->get_value_as_int());
       gwr_auswahl=ENone;
       lernschema_geld_wuerfeln(vabenteurer->getLernpunkte().getVGeldwurf());
       table_waffen_lernschema_eingabe->hide();
       gwr_auswahl=ENone;  
     }
}


void table_lernschema::show_WaffenBesitz_lernschema()
{
  clean_lernschema_trees();

  tree_waffen_lernschema = manage(new MidgardBasicTree(MidgardBasicTree::WAFFE_LERNSCHEMA));
  tree_waffen_lernschema->signal_leaf_selected().connect(SigC::slot(*static_cast<class table_lernschema*>(this), &table_lernschema::on_waffen_lernschema_tree_leaf_selected));
  label_lernschma_titel->set_text("Waffenbesitz wählen");
#warning TODO
  std::list<H_WaffeBesitz> L1=LernListen::getWaffenBesitz(hauptfenster->getAben());
  std::list<MBEmlt> L;
  for(std::list<H_WaffeBesitz>::iterator i=L1.begin();i!=L1.end();++i) 
      L.push_back(H_MidgardBasicElement_mutable(&**i));
  MidgardBasicTree::show_list_in_tree(L,tree_waffen_lernschema,hauptfenster->getChar().actualIterator());
  tree_waffen_lernschema->show();
  tree_waffen_lernschema->Expand_recursively();
  Gtk::Table *table=manage(new Gtk::Table(1,1,false));
  Gtk::Label *lE = manage(new Gtk::Label(itos(waffebesitzlernen.EWaffe())+" Einhandwaffen, Verteidigungswaffen oder Wurfwaffen",0));
  Gtk::Label *lA = manage(new Gtk::Label(itos(waffebesitzlernen.AWaffe())+" beliebige Waffen (einschließlich Zweihand- und Schußwaffen)",0));
  

  table->attach(*lE,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  table->attach(*lA,0,1,1,2,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  table->attach(*tree_waffen_lernschema,0,1,2,3,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  if(waffebesitzlernen.getMagisch())
   {
     Gtk::Label *lM = manage(new Gtk::Label("Die erste gewählte Einhandwaffe ist magisch",0));
     table->attach(*lM,0,1,3,4,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   }
  scrolledwindow_lernen->add(*table);  
  scrolledwindow_lernen->show_all();
}

void table_lernschema::on_waffen_lernschema_tree_leaf_selected(cH_RowDataBase d)
{
 try{
   const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
   MBEmlt MBE = dt->getMBE();
   cH_Waffe W(MBE->getMBE());
   std::string art=W->Art2();
   H_WaffeBesitz WB=new WaffeBesitz(W,(*MBE)->Name(),0,0,"","");
   if( (art=="E" || art=="W" || art=="V") && waffebesitzlernen.EWaffe()>0)
    {
      waffebesitzlernen.add_EWaffe(-1);
      if(waffebesitzlernen.getMagisch())
        {
          WB->set_av_Bonus(1);
          waffebesitzlernen.setMagisch(false);
        }
    }
   else if(waffebesitzlernen.AWaffe()>0)
     waffebesitzlernen.add_AWaffe(-1);
   else return;

   hauptfenster->getAben().List_Waffen_besitz().push_back(WB);
   {
    AusruestungBaum &wohin=hauptfenster->getAben().getAusruestung_as_parent("Gürtel");
    std::string g=WB->Waffe()->Grundkenntnis();
    if(g=="Kampf ohne Waffen")
     {
       if(g=="Zweihandschwert" || g=="Zweihandschlagwaffe" ||
          g=="Spießwaffe" || g=="Stangenwaffe" || g=="Bögen" ||
          g=="Armbrust"
         )
          wohin=hauptfenster->getAben().getBesitz();
       wohin.push_back(Ausruestung((*WB)->Name()));
     }
   }
   show_gelerntes();
   show_WaffenBesitz_lernschema();
 }catch(std::exception &e) {Ausgabe(Ausgabe::Error,e.what());}
}

void table_lernschema::WaffenBesitz_lernschema_wuerfeln(int wurf)
{
  std::string strinfo = "Für die Waffenauswahl wurde eine "+itos(wurf)
      +" gewürfelt, die Abenteurerklasse ist "
      +hauptfenster->getAben().Typ1()->Name(hauptfenster->getAben().Geschlecht())+" ==> ";
 waffebesitzlernen =Zufall::WaffenBesitz_wuerfeln(hauptfenster->getAben(),wurf);
 strinfo += itos(waffebesitzlernen.EWaffe())+" Einhand- und "+itos(waffebesitzlernen.AWaffe())+" beliebige Waffen";
 Ausgabe(Ausgabe::Log,strinfo);
 show_WaffenBesitz_lernschema();
}

void table_lernschema::on_togglebutton_spezialwaffe_toggled()
{  if (togglebutton_spezialwaffe->get_active()) scrolledwindow_lernen->hide();
   else 
     { scrolledwindow_lernen->show();
       hauptfenster->getChar().getWizard().done(Wizard::SPEZIALWAFFE,hauptfenster->getAben());
     }
}
