/*  Copyright (C) 2001 Malte Thoma
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

#include "midgard_CG.hh"
//#include <gtk--/toolbar.h>
#include <gtk--/pixmap.h>
#include "class_SimpleTree.hh"

///////////////////////////////////////////////////////////
void midgard_CG::on_radio_steigern_toggled()
{ on_radio_steigern_all();}
void midgard_CG::on_radio_reduzieren_toggled()
{ on_radio_steigern_all();}
void midgard_CG::on_radio_verlernen_toggled()
{ on_radio_steigern_all();}
void midgard_CG::on_radio_steigern_all()
{
  if (radiobutton_steigern->get_active() && checkbutton_EP_Geld->get_active())
     frame_lernen_mit->set_sensitive(true); 
  else
     frame_lernen_mit->set_sensitive(false); 

}

void midgard_CG::on_togglebutton_praxispunkte_toggled()
{
  if(togglebutton_praxispunkte->get_active())
   {
     vbox_praxispunkte->show();
     if(Typ[0]->is_mage() || Typ[1]->is_mage()) 
         radiobutton_pp_zauber->set_sensitive(true);//show();
     else
         radiobutton_pp_zauber->set_sensitive(true);//hide();
   }
  else
     vbox_praxispunkte->hide();
}

/////////////////////////////////////////////////////////

void midgard_CG::on_radio_unterweisung_toggled()
{
 if(radiobutton_unterweisung->get_active())
  {
    steigern_gtk();
    vscale_EP_Gold->set_sensitive(true);
    label_EP->set_sensitive(true);
    label_Gold->set_sensitive(true);
  }
 else
  {
    label_EP->set_text("100%");
    label_Gold->set_text("0%");
    vscale_EP_Gold->set_sensitive(false);
    label_EP->set_sensitive(false);
    label_Gold->set_sensitive(false);
  }
}
void midgard_CG::on_radio_selbst_toggled()
{
}
void midgard_CG::on_radio_praxis_toggled()
{
}

void midgard_CG::on_radiobutton_pp_fertigkeit_toggled()
{on_radiobutton_pp_all_toggled();}
void midgard_CG::on_radiobutton_pp_zauber_toggled()
{on_radiobutton_pp_all_toggled();}
void midgard_CG::on_radiobutton_pp_abwehr_toggled()    
{on_radiobutton_pp_all_toggled();}
void midgard_CG::on_radiobutton_pp_resistenz_toggled()
{on_radiobutton_pp_all_toggled();}
void midgard_CG::on_radiobutton_pp_all_toggled()
{
  if(radiobutton_pp_fertigkeit->get_active())
    spinbutton_pp_eingeben->hide();
  else 
    spinbutton_pp_eingeben->show();
}
                                

void midgard_CG::on_spinbutton_pp_eingeben_activate()
{
  gtk_spin_button_update(spinbutton_pp_eingeben->gtkobj());
  int PPanz = spinbutton_pp_eingeben->get_value_as_int();

 if(!radiobutton_pp_fertigkeit->get_active())
  {
    if(radiobutton_pp_abwehr->get_active())
       Werte.setAbwehrPP(PPanz);
    else if(radiobutton_pp_zauber->get_active())
       Werte.setZaubernPP(PPanz);
    else if(radiobutton_pp_resistenz->get_active())
       Werte.setResistenzPP(PPanz);
    spinbutton_pp_eingeben->hide();
    radiobutton_steigern->get_active();
    zeige_werte();
    return;
  }   
 
 guint pagenr = notebook_lernen->get_current_page_num();
// cH_MidgardBasicElement MBE;
// cH_RowDataBase rdb;
 const Data_SimpleTree *dt;
 try{
   if(pagenr==PAGE_FERTIGKEITEN)
      dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_fert_tree->getSelectedRowDataBase())); 
   if(pagenr==PAGE_WAFFEN)
      dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_waffen_tree->getSelectedRowDataBase())); 
   if(pagenr==PAGE_SPRACHE)
    {
      try{ dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_sprache_tree->getSelectedRowDataBase())); }
          catch (std::exception &e) {}
      try {dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_schrift_tree->getSelectedRowDataBase())); }
          catch (std::exception &e) {}
    }
//  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&**rdb);
  cH_MidgardBasicElement MBE(dt->getMBE());
  const_cast<MidgardBasicElement&>(*MBE).set_Praxispunkte(PPanz);

  if(pagenr==PAGE_FERTIGKEITEN)
     MidgardBasicElement::show_list_in_tree(list_Fertigkeit,alte_fert_tree,this); 
  if(pagenr==PAGE_WAFFEN)
     MidgardBasicElement::show_list_in_tree(list_Waffen,alte_waffen_tree,this); 
  if(pagenr==PAGE_SPRACHE)
   {
     MidgardBasicElement::show_list_in_tree(list_Sprache,alte_sprache_tree,this); 
     MidgardBasicElement::show_list_in_tree(list_Schrift,alte_schrift_tree,this); 
   }

  }catch(std::exception &e) {cerr << e.what()<<'\n';}
  spinbutton_pp_eingeben->hide();
}


void midgard_CG::on_button_alter_clicked()
{
  float tage=Werte.Steigertage();
  int alter=Werte.Alter();
  int tage_pro_jahr=360;
  while(tage>tage_pro_jahr)
   {
     alter+=1;
     tage-=tage_pro_jahr;
   }
  Werte.setAlter(alter);
  Werte.setSteigertage(tage);
  zeige_werte();
}


gint midgard_CG::on_eventbox_ausruestung_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_AUSRUESTUNG); return false;}
gint midgard_CG::on_eventbox_steigern_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_STEIGERN); return false;}
gint midgard_CG::on_eventbox_lernen_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_LERNEN); return false;}
gint midgard_CG::on_eventbox_grundwerte_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_GRUNDWERTE); return false;}


void midgard_CG::on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page *page,guint pagenr)
{
 if(Typ[0]->is_mage() || Typ[1]->is_mage())
  {
    button_grad_zaubern->set_sensitive(true);
    frame_pp_zaubern->set_sensitive(true);
  }
 else 
  {
    button_grad_zaubern->set_sensitive(false);
    frame_pp_zaubern->set_sensitive(false);
  }
 if(pagenr==PAGE_STEIGERN)
  {
    menu_gradanstieg_init();
    load_for_page(notebook_lernen->get_current_page_num());
  }
 else if(pagenr==PAGE_AUSRUESTUNG)
    ausruestung_laden();
}

void midgard_CG::on_notebook_lernen_switch_page(Gtk::Notebook_Helpers::Page *page,guint pagenr)
{
  load_for_page(pagenr);
}

void midgard_CG::load_for_page(guint pagenr)
{
  if(pagenr==PAGE_FERTIGKEITEN)
     on_fertigkeiten_laden_clicked();
  if(pagenr==PAGE_WAFFEN)
     on_waffen_laden_clicked();
  if(pagenr==PAGE_ZAUBER)
     on_zauber_laden_clicked();
  if(pagenr==PAGE_KIDO)
     on_kido_laden_clicked();
  if(pagenr==PAGE_SPRACHE)
     on_sprache_laden_clicked();

  // Sensitive & Show
  if(pagenr==PAGE_ZAUBER || pagenr==PAGE_KIDO)
   {
//     frame_fertigkeit->set_sensitive(false);
     frame_fertigkeit->hide();
//     frame_lernen_mit->set_sensitive(false);
     radiobutton_verlernen->set_active(true);
     if(pagenr==PAGE_ZAUBER) frame_zauber_zusatz->show();
     if(Typ[0]->SpruecheMitPP() || Typ[1]->SpruecheMitPP())
        radiobutton_praxis->set_sensitive(true);
     else
     radiobutton_praxis->set_sensitive(false);
   }
  else
   {
//     frame_fertigkeit->set_sensitive(true);
     frame_fertigkeit->show();
//     frame_lernen_mit->set_sensitive(true);
     radiobutton_steigern->set_active(true);
     frame_zauber_zusatz->hide();
     radiobutton_praxis->set_sensitive(true);
   }
}

