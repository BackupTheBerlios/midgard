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
void midgard_CG::on_radiobutton_pp_eingeben_toggled()
{ on_radio_steigern_all();}
void midgard_CG::on_radio_steigern_all()
{
  if (radiobutton_steigern->get_active() && checkbutton_EP_Geld->get_active())
     frame_lernen_mit->set_sensitive(true); 
  else
     frame_lernen_mit->set_sensitive(false); 

  if(radiobutton_pp_eingeben->get_active())
     spinbutton_pp_eingeben->show();
  else
     spinbutton_pp_eingeben->hide();
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


void midgard_CG::on_spinbutton_pp_eingeben_activate()
{
 guint pagenr = notebook_lernen->get_current_page_num();
 cH_MidgardBasicElement *MBE;
 cH_RowDataBase *rdb;
 try{
   if(pagenr==PAGE_FERTIGKEITEN)
      rdb = &(alte_fert_tree->getSelectedRowDataBase()); 
   if(pagenr==PAGE_WAFFEN)
      rdb = &(alte_waffen_tree->getSelectedRowDataBase()); 
   if(pagenr==PAGE_SPRACHE)
    {
      try{ rdb = &(alte_sprache_tree->getSelectedRowDataBase()); }
          catch (std::exception &e) {}
      try {rdb = &(alte_schrift_tree->getSelectedRowDataBase()); }
          catch (std::exception &e) {}
    }
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&**rdb);
  MBE=&const_cast<cH_MidgardBasicElement&>(dt->getMBE());

  gtk_spin_button_update(spinbutton_pp_eingeben->gtkobj());
  (*MBE)->set_Praxispunkte(spinbutton_pp_eingeben->get_value_as_int());
  spinbutton_pp_eingeben->hide();
  MidgardBasicElement::show_list_in_tree(list_Fertigkeit,alte_fert_tree,Werte,Typ,Database.ausnahmen); 
  on_speichern_clicked();
  }catch(std::exception &e) {cerr << e.what()<<'\n';}
}

void midgard_CG::on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page *page,guint pagenr)
{
 if(pagenr==PAGE_STEIGERN)
   load_for_page(notebook_lernen->get_current_page_num());
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
     frame_fertigkeit->set_sensitive(false);
     frame_lernen_mit->set_sensitive(false);
     radiobutton_verlernen->set_active(true);
     if(pagenr==PAGE_ZAUBER) frame_zauber_zusatz->show();
     else                    frame_zauber_zusatz->hide();
   }
  else
   {
     frame_fertigkeit->set_sensitive(true);
     frame_lernen_mit->set_sensitive(true);
     radiobutton_steigern->set_active(true);
     frame_zauber_zusatz->hide();
   }
}

