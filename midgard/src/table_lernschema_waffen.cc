// $Id: table_lernschema_waffen.cc,v 1.6 2002/06/08 06:35:03 thoma Exp $
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
//#include "Fertigkeiten.hh"
//#include "class_Beruf_Data.hh"
//#include "Beruf.hh"
#include <Aux/itos.h>
//#include "Window_Waffenbesitz.hh"
#include "class_SimpleTree.hh"
#include "midgard_CG.hh"

gint table_lernschema::on_button_lernschema_waffen_button_release_event(GdkEventButton *ev)
{
  hauptfenster->getChar().List_Waffen_besitz().clear();
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::WAFFEN);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
     button_lernschema_waffen->set_sensitive(false);
  if  (ev->button==1)
   {
     table_waffen_lernschema_eingabe->hide();
     int wurf = hauptfenster->random.integer(1,100);
     WaffenBesitz_lernschema_wuerfeln(wurf);     
   }
  else if (ev->button==3)
   {
     gwr_auswahl=EWaffen;
     set_gwr_eingabe();
   }
  return 0;
}

gint table_lernschema::on_spinbutton_waffen_lernschema_focus_in_event(GdkEventFocus *ev)
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
     { VGeldwurf.clear();
       VGeldwurf.push_back(spinbutton_waffen_lernschema->get_value_as_int());
       gwr_auswahl=EGeld2;
       set_gwr_eingabe();       
     }
  else if(gwr_auswahl==EGeld2)
     { 
       VGeldwurf.push_back(spinbutton_waffen_lernschema->get_value_as_int());
       gwr_auswahl=EGeld3;
       set_gwr_eingabe();       
     }
  else if(gwr_auswahl==EGeld3)
     { 
       VGeldwurf.push_back(spinbutton_waffen_lernschema->get_value_as_int());
       gwr_auswahl=ENone;
       lernschema_geld_wuerfeln(VGeldwurf);
       table_waffen_lernschema_eingabe->hide();
       gwr_auswahl=ENone;  
     }
}


void table_lernschema::show_WaffenBesitz_lernschema()
{
  clean_lernschema_trees();

  tree_waffen_lernschema = manage(new MidgardBasicTree(MidgardBasicTree::WAFFE_LERNSCHEMA));
  tree_waffen_lernschema->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_waffen_lernschema_tree_leaf_selected));
  label_lernschma_titel->set_text("Waffenbesitz wählen");

  std::list<MidgardBasicElement_mutable> L;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getDatabase().Waffe.begin();i!=hauptfenster->getDatabase().Waffe.end();++i)
   {
     if(hauptfenster->getCWerte().Spezies()->istVerbotenSpielbegin(*i)) continue;
     const cH_Waffe w(*i);
     if (w->Grundkenntnis() == "Kampf ohne Waffen") continue;
     if (!MidgardBasicElement_mutable(&*w).ist_gelernt(hauptfenster->getCChar().CList_Waffen())) continue;
//     L.push_back(new WaffeBesitz(w,w->Name(),0,0,""));
     L.push_back(WaffeBesitz(w,-2,w->Name(),0,0,""));
   }
  MidgardBasicElement::show_list_in_tree(L,tree_waffen_lernschema,hauptfenster);
  tree_waffen_lernschema->show();
  tree_waffen_lernschema->Expand_recursively();
  Gtk::Table *table=manage(new Gtk::Table(0,0,false));
  Gtk::Label *lE = manage(new Gtk::Label(itos(waffebesitzlernen.EWaffe())+" Einhandwaffen, Verteidigungswaffen oder Wurfwaffen",0));
  Gtk::Label *lA = manage(new Gtk::Label(itos(waffebesitzlernen.AWaffe())+" beliebige Waffen (einschließlich Zweihand- und Schußwaffen)",0));
  

  table->attach(*lE,0,1,0,1,GTK_FILL,0,0,0);
  table->attach(*lA,0,1,1,2,GTK_FILL,0,0,0);
  table->attach(*tree_waffen_lernschema,0,1,2,3,GTK_FILL,0,0,0);
  if(waffebesitzlernen.getMagisch())
   {
     Gtk::Label *lM = manage(new Gtk::Label("Die erste gewählte Einhandwaffe ist magisch",0));
     table->attach(*lM,0,1,3,4,GTK_FILL,0,0,0);
   }
  viewport_lernen->add(*table);  
  scrolledwindow_lernen->show_all();
}

void table_lernschema::on_waffen_lernschema_tree_leaf_selected(cH_RowDataBase d)
{
 try{
   const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
   MidgardBasicElement_mutable MBE = dt->getMBE();
//   std::string art=cH_WaffeBesitz(MBE)->Waffe()->Art2();
   std::string art=WaffeBesitz(MBE).Waffe()->Art2();
   if( (art=="E" || art=="W" || art=="V") && waffebesitzlernen.EWaffe()>0)
    {
      waffebesitzlernen.add_EWaffe(-1);
      if(waffebesitzlernen.getMagisch())
        {
//          cH_WaffeBesitz(MBE).set_av_Bonus(1);
          WaffeBesitz(MBE).set_av_Bonus(1);
          waffebesitzlernen.setMagisch(false);
        }
    }
   else if(waffebesitzlernen.AWaffe()>0)
     waffebesitzlernen.add_AWaffe(-1);
   else return;

   hauptfenster->getChar().List_Waffen_besitz().push_back(MBE);

   show_gelerntes();
   show_WaffenBesitz_lernschema();
 }catch(std::exception &e) {cerr << e.what()<<'\n';}
}

void table_lernschema::WaffenBesitz_lernschema_wuerfeln(int wurf)
{
  std::string strinfo = "Für die Waffenauswahl wurde eine "+itos(wurf)
      +" gewürfelt, die Abenteurerklasse ist "
      +hauptfenster->getChar().CTyp1()->Name(hauptfenster->getCWerte().Geschlecht())+" ==> ";
 int E=0,A=0;
 bool M=false;
 if (hauptfenster->getChar().CTyp1()->Geld() == 1)
  { if      ( 1<=wurf&&wurf<=10 ) { E=3;      }
    else if (11<=wurf&&wurf<=20 ) { E=3; A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=2; A=2; }
    else if (31<=wurf&&wurf<=60 ) { E=3; A=2; }
    else if (61<=wurf&&wurf<=80 ) { E=2; A=3; }
    else if (81<=wurf&&wurf<=95 ) {      A=5; }
    else if (96<=wurf&&wurf<=100) { E=1; A=4; M=true; }
  }  
 if (hauptfenster->getChar().CTyp1()->Geld() == 2)
  { if      ( 1<=wurf&&wurf<=10 ) { E=2;      }
    else if (11<=wurf&&wurf<=20 ) { E=1; A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=2; A=1; }
    else if (31<=wurf&&wurf<=60 ) { E=3; A=1; }
    else if (61<=wurf&&wurf<=80 ) { E=2; A=2; }
    else if (81<=wurf&&wurf<=95 ) {      A=4; }
    else if (96<=wurf&&wurf<=100) { E=1; A=3; M=true; }
  }  
 if (hauptfenster->getChar().CTyp1()->Geld() == 3) 
  { if      ( 1<=wurf&&wurf<=10 ) { E=1;      }
    else if (11<=wurf&&wurf<=20 ) {      A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=2;      }
    else if (31<=wurf&&wurf<=60 ) { E=1; A=1; }
    else if (61<=wurf&&wurf<=80 ) { E=1; A=1; }
    else if (81<=wurf&&wurf<=95 ) {      A=2; }
    else if (96<=wurf&&wurf<=100) { E=1; A=1; M=true; }
  }  
 if (hauptfenster->getChar().CTyp1()->Geld() == 4) 
  { if      ( 1<=wurf&&wurf<=10 ) { E=2;      }
    else if (11<=wurf&&wurf<=20 ) { E=1; A=1; }
    else if (21<=wurf&&wurf<=30 ) { E=3;      }
    else if (31<=wurf&&wurf<=60 ) { E=2; A=1; }
    else if (61<=wurf&&wurf<=80 ) { E=1; A=2; }
    else if (81<=wurf&&wurf<=95 ) {      A=3; }
    else if (96<=wurf&&wurf<=100) { E=1; A=2; M=true; }
  }  
 strinfo += itos(E)+" Einhand- und "+itos(A)+" beliebige Waffen";
 hauptfenster->set_status(strinfo);
 waffebesitzlernen.setMagisch(M);
 waffebesitzlernen.set_EWaffe(E);
 waffebesitzlernen.set_AWaffe(A);
 show_WaffenBesitz_lernschema();
}

