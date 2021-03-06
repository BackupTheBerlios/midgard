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
#include "table_steigern.hh"
//#include <gtkmm/toolbar.h>
#include <gtkmm/image.h>
#include "class_SimpleTree.hh"
#include "class_SimpleTree_LernschemaZusatz.hh"
#include <libmagus/Ausgabe.hh>

///////////////////////////////////////////////////////////
void table_steigern::on_radio_steigern_toggled()
{ on_radio_steigern_all();}
void table_steigern::on_radio_reduzieren_toggled()
{ on_radio_steigern_all();}
void table_steigern::on_radio_verlernen_toggled()
{ on_radio_steigern_all();}
void table_steigern::on_radio_steigern_all()
{
}

void table_steigern::on_togglebutton_praxispunkte_toggled()
{
  if(togglebutton_praxispunkte->get_active())
   {
     vbox_praxispunkte->show();
     if(hauptfenster->getAben().Typ1()->is_mage() || hauptfenster->getAben().Typ2()->is_mage()) 
         radiobutton_pp_zauber->set_sensitive(true);
     else
         radiobutton_pp_zauber->set_sensitive(true);
     on_radiobutton_pp_all_toggled();
   }
  else
   {
     vbox_praxispunkte->hide();
     spinbutton_pp_eingeben->hide();
   }
}

std::string table_steigern::SpruecheMitPP()
{
  if(hauptfenster->getAben().Typ1()->SpruecheMitPP())
       return hauptfenster->getAben().Typ1()->SpruecheMitPP_Text();
  else if(hauptfenster->getAben().Typ2()->SpruecheMitPP())
       return hauptfenster->getAben().Typ2()->SpruecheMitPP_Text();
  else return "";
}


/////////////////////////////////////////////////////////

void table_steigern::on_radiobutton_pp_zauber_toggled()
{
 on_radiobutton_pp_all_toggled();
}
void table_steigern::on_radiobutton_pp_spezial_toggled()
{
 on_radiobutton_pp_all_toggled();
}
void table_steigern::on_radiobutton_pp_abwehr_toggled()    
{
 on_radiobutton_pp_all_toggled(); 
}
void table_steigern::on_radiobutton_pp_resistenz_toggled()
{ 
 on_radiobutton_pp_all_toggled();
}
void table_steigern::on_radiobutton_pp_all_toggled()
{
  if (radiobutton_pp_resistenz->get_active())
    spinbutton_pp_eingeben->set_value(hauptfenster->getAben().ResistenzPP());
  else if (radiobutton_pp_abwehr->get_active())
    spinbutton_pp_eingeben->set_value(hauptfenster->getAben().AbwehrPP());
  else if (radiobutton_pp_spezial->get_active())
    spinbutton_pp_eingeben->set_value(hauptfenster->getAben().SpezialPP());
  else if (radiobutton_pp_zauber->get_active())
    spinbutton_pp_eingeben->set_value(hauptfenster->getAben().ZaubernPP());

     spinbutton_pp_eingeben->show();
     spinbutton_pp_eingeben->grab_focus();
     spinbutton_pp_eingeben->select_region(0,-1);
}
                                

void table_steigern::on_spinbutton_pp_eingeben_activate()
{
  spinbutton_pp_eingeben->update();
  int PPanz = spinbutton_pp_eingeben->get_value_as_int();

    if(radiobutton_pp_abwehr->get_active())
       hauptfenster->getAben().setAbwehrPP(PPanz);
    else if(radiobutton_pp_zauber->get_active())
       hauptfenster->getAben().setZaubernPP(PPanz);
    else if(radiobutton_pp_spezial->get_active())
       hauptfenster->getAben().setSpezialPP(PPanz);
    else if(radiobutton_pp_resistenz->get_active())
       hauptfenster->getAben().setResistenzPP(PPanz);
//    spinbutton_pp_eingeben->hide();
//    radiobutton_steigern->get_active();
    zeige_werte();
    return;
}

const MBEmlt &table_steigern::getSelectedNotebookLernen() throw(SimpleTree::noRowSelected)
{
 cH_RowDataBase dt;
 guint pagenr = notebook_lernen->get_current_page();
 try {
   if(pagenr==PAGE_FERTIGKEITEN)
      dt=alte_fert_tree->getSelectedRowDataBase(); 
   if(pagenr==PAGE_WAFFEN)
      dt=alte_waffen_tree->getSelectedRowDataBase(); 
   if(pagenr==PAGE_ZAUBER)
      dt=alte_zauber_tree->getSelectedRowDataBase(); 
   if(pagenr==PAGE_KIDO)
      dt=alte_kido_tree->getSelectedRowDataBase(); 
   if(pagenr==PAGE_SPRACHE)
    {
      try{ dt=alte_sprache_tree->getSelectedRowDataBase(); }
      catch (std::exception &e)
       { dt=alte_schrift_tree->getSelectedRowDataBase(); }
    }
  } catch (SimpleTree::noRowSelected &e) // try cursor
  {if(pagenr==PAGE_FERTIGKEITEN)
      dt=alte_fert_tree->getCursorRowDataBase(); 
   if(pagenr==PAGE_WAFFEN)
      dt=alte_waffen_tree->getCursorRowDataBase(); 
   if(pagenr==PAGE_ZAUBER)
      dt=alte_zauber_tree->getCursorRowDataBase(); 
   if(pagenr==PAGE_KIDO)
      dt=alte_kido_tree->getCursorRowDataBase(); 
   if(pagenr==PAGE_SPRACHE)
    {
      try{ dt=alte_sprache_tree->getCursorRowDataBase(); }
      catch (std::exception &e)
       { dt=alte_schrift_tree->getCursorRowDataBase(); }
    }
  }
  return Handle<const Data_SimpleTree>::cast_dynamic(dt)->getMBE();
}



void table_steigern::on_button_alter_clicked()
{
  hauptfenster->getAben().Steigertage2Alter();
  zeige_werte();
}

#include "LernListen.hh"
void table_steigern::fillClistZusatz(MBEmlt &MBE)
{
  std::vector<cH_RowDataBase> datavec;
  std::vector<std::string> title;
  std::vector<MidgardBasicElement::st_zusatz> VZusatz;
  switch ((*MBE)->ZusatzEnum(hauptfenster->getAben().getVTyp()))
   {
     case MidgardBasicElement::ZLand :
      {        
        title.push_back("Land auswählen");
        VZusatz=LernListen::getLandZusatz();
        break;
      }
     case MidgardBasicElement::ZWaffe :
      {      
        title.push_back("Waffe auswählen");
        VZusatz=LernListen::getWaffenZusatz(hauptfenster->getAben().List_Waffen());
        break;
      }
     case MidgardBasicElement::ZTabelle : 
      {
        title.push_back((*MBE)->Name()+" auswählen");
        title.push_back("Typ");
        title.push_back("Region");
        VZusatz=LernListen::getMBEZusatz(hauptfenster->getAben(),MBE);
        break; 
       }
     default : assert("Never get here\n");
   }
  for(std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=VZusatz.begin();i!=VZusatz.end();++i)
        datavec.push_back(new Data_Zusatz(MBE,*i));
  if(!datavec.empty())
   {
     set_zusatz_sensitive(true);
     tree_steigern_zusatz->setTitles(title);
     tree_steigern_zusatz->setDataVec(datavec);
   }
}

void table_steigern::set_zusatz_sensitive(bool an)
{
 if(an)
  {
    table_handlebox1->set_sensitive(false);
    handlebox_steigern_3->set_sensitive(false);
    notebook_lernen->set_sensitive(false);
    scrolledwindow_landauswahl->show();
  }
 else
  {
    table_handlebox1->set_sensitive(true);
    handlebox_steigern_3->set_sensitive(true);
    notebook_lernen->set_sensitive(true);
    scrolledwindow_landauswahl->hide();
  }
}



void table_steigern::on_steigern_zusatz_leaf_selected(cH_RowDataBase d)
{
  Handle<const Data_Zusatz> dt=d.cast_dynamic<const Data_Zusatz>();
  dt->getMBE()->setZusatz(dt->getZusatz());
  if(dt->getZusatz().name==hauptfenster->getAben().Herkunft()->Name())
     dt->getMBE()->setErfolgswert(9);

  set_zusatz_sensitive(false);

  if(dt->getMBE()->What()==MidgardBasicElement::FERTIGKEIT) 
      fertigkeiten_zeigen();
  else if (dt->getMBE()->What()==MidgardBasicElement::ZAUBER)
      zauber_zeigen();
  neue_fert_tree->set_sensitive(true);
}

