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

//  if(radiobutton_pp_eingeben->get_active())
     ;//spinbutton_pp_eingeben->show();
//  else
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
  try{
   guint pagenr = notebook_lernen->get_current_page_num();
   cH_MidgardBasicElement *MBE;
   if(pagenr==PAGE_FERTIGKEITEN)
    { cH_RowDataBase rdb=alte_fert_tree->getSelectedRowDataBase(); 
      const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*rdb);
      MBE=&const_cast<cH_MidgardBasicElement&>(dt->getMBE());
    }
   if(pagenr==PAGE_WAFFEN)
    { cH_RowDataBase rdb=alte_waffen_tree->getSelectedRowDataBase(); 
      const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*rdb);
      MBE=&const_cast<cH_MidgardBasicElement&>(dt->getMBE());
    }
/*
   if(pagenr==PAGE_ZAUBER)
    { cH_RowDataBase rdb=alte_zauber_tree->getSelectedRowDataBase(); 
      const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*rdb);
      MBE=&const_cast<cH_MidgardBasicElement&>(dt->getMBE());
    }
   if(pagenr==PAGE_KIDO)
    { cH_RowDataBase rdb=alte_kido_tree->getSelectedRowDataBase(); 
      const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*rdb);
      MBE=&const_cast<cH_MidgardBasicElement&>(dt->getMBE());
    }
*/
   if(pagenr==PAGE_SPRACHE)
    { try {cH_RowDataBase rdb=alte_sprache_tree->getSelectedRowDataBase(); }
       catch (std::exception &e) {}
      cH_RowDataBase rdb=alte_schrift_tree->getSelectedRowDataBase();
      const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*rdb);
      MBE=&const_cast<cH_MidgardBasicElement&>(dt->getMBE());
    }

   gtk_spin_button_update(spinbutton_pp_eingeben->gtkobj());
   (*MBE)->set_Praxispunkte(spinbutton_pp_eingeben->get_value_as_int());
   spinbutton_pp_eingeben->hide();
   MidgardBasicElement::show_list_in_tree(list_Fertigkeit    ,alte_fert_tree,Werte,Typ,Database.ausnahmen); 
   on_speichern_clicked();
  }catch(std::exception &e) {cerr << e.what()<<'\n';}
}


#include "../pixmaps/LoadSkills-trans-50.xpm"
#include "../pixmaps/Sort_Skill-trans-50.xpm"
#include "../pixmaps/LoadWeapon-trans-50.xpm"
#include "../pixmaps/Sort_Weapon-trans-50.xpm"
#include "../pixmaps/LoadZaub-trans-50.xpm"
#include "../pixmaps/Sort_Zauber-50.xpm"
#include "../pixmaps/Load-Kido-trans-50.xpm"
#include "../pixmaps/Sort_KiDo-trans-50.xpm"
#include "../pixmaps/LoadLang_u_Font-trans-50.xpm"
#include "../pixmaps/Sort_Lang-trans-50.xpm"


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
  toolbar_fert->tools().clear();
  std::string b1,b2,t;
  Gtk::Pixmap *p1,*p2;

  if(pagenr==PAGE_FERTIGKEITEN)
   { 
     on_fertigkeiten_laden_clicked();
//     b1= "Fertigkeiten\n laden";
     b2= "Fertigkeiten\nsortieren";
//     p1= manage(new Gtk::Pixmap(LoadSkills_trans_50_xpm));
     p2= manage(new Gtk::Pixmap(Sort_Skill_trans_50_xpm));
     t ="Die gelernten Fertigkeiten werden in der aktuellen Reinfolge für den Ausdruck sortiert";
   }
  if(pagenr==PAGE_WAFFEN)
   { 
     on_waffen_laden_clicked();
//     b1= "Waffen\n laden";
     b2= "Waffen\nsortieren";
//     p1= manage(new Gtk::Pixmap(LoadWeapon_trans_50_xpm));
     p2= manage(new Gtk::Pixmap(Sort_Weapon_trans_50_xpm));
     t ="Die gelernten Waffen werden in der aktuellen Reinfolge für den Ausdruck sortiert";
   }
  if(pagenr==PAGE_ZAUBER)
   { 
     on_zauber_laden_clicked();
//     b1= "Zauber\n laden";
     b2= "Zauber\nsortieren";
//     p1= manage(new Gtk::Pixmap(LoadZaub_trans_50_xpm));
     p2= manage(new Gtk::Pixmap(Sort_Zauber_50_xpm));
     t ="Die gelernten Zauber und Zaubermittel werden in der aktuellen Reinfolge für den Ausdruck sortiert";
   }
  if(pagenr==PAGE_KIDO)
   { 
     on_kido_laden_clicked();
//     b1= "Techniken laden";
     b2= "Techniken\nsortieren";
//     p1= manage(new Gtk::Pixmap(Load_Kido_trans_50_xpm));
     p2= manage(new Gtk::Pixmap(Sort_KiDo_trans_50_xpm));
     t ="Die gelernten Techniken werden in der aktuellen Reinfolge für den Ausdruck sortiert";
   }
  if(pagenr==PAGE_SPRACHE)
   {
     on_sprache_laden_clicked();
//     b1= "Sprachen & Schriften laden";
     b2= "Sprachen\nsortieren";
//     p1= manage(new Gtk::Pixmap(LoadLang_u_Font_trans_50_xpm));
     p2= manage(new Gtk::Pixmap(Sort_Lang_trans_50_xpm));
     t ="Die gelernten Sprachen werden in der aktuellen Reinfolge für den Ausdruck sortiert";
   }

//  button_fert_laden = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(
//     GTK_TOOLBAR(toolbar_fert->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, 
//     b1.c_str(), 0, 0, GTK_WIDGET(p1->gtkobj()), 0, 0));
//  toolbar_fert->tools().push_back(Gtk::Toolbar_Helpers::Space());
  button_fert_sort = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(
     GTK_TOOLBAR(toolbar_fert->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0,
     b2.c_str(), 0, 0, GTK_WIDGET(p2->gtkobj()), 0, 0));

  Gtk::Tooltips _tooltips;
  _tooltips.set_tip(*button_fert_sort,t);

  // Connect Funktionen für Buttons
  if(pagenr==PAGE_FERTIGKEITEN)
    button_fert_sort->clicked.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_button_fertigkeiten_sort_clicked));
  else if(pagenr==PAGE_WAFFEN)
    button_fert_sort->clicked.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_button_zauber_sort_clicked));
  else if(pagenr==PAGE_ZAUBER)
    button_fert_sort->clicked.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_button_waffen_sort_clicked));
  else if(pagenr==PAGE_KIDO)
    button_fert_sort->clicked.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_button_kido_sort_clicked));
  else if(pagenr==PAGE_SPRACHE)
    button_fert_sort->clicked.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_button_sprache_sort_clicked));
  else assert(0);

  // Sensitive & Show
  if(pagenr==PAGE_ZAUBER)
   {
     frame_fertigkeit->set_sensitive(false);
     frame_zauber_zusatz->show();
   }
  else
   {
     frame_fertigkeit->set_sensitive(true);
     frame_zauber_zusatz->hide();
   }
}

