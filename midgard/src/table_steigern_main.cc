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
     radiobutton_pp_fertigkeit->set_active(true);
     vbox_praxispunkte->show();
     if(hauptfenster->getAben().Typ1()->is_mage() || hauptfenster->getAben().Typ2()->is_mage()) 
         radiobutton_pp_zauber->set_sensitive(true);
     else
         radiobutton_pp_zauber->set_sensitive(true);

     try{
      MBEmlt M=getSelectedNotebookLernen();
      spinbutton_pp_eingeben->set_value(M->Praxispunkte());
      spinbutton_pp_eingeben->show();
     }catch(SimpleTree::noRowSelected &e) {/*std::cerr << e.what()<<'\n'; hauptfenster->set_status("Keine Zeile selektiert");*/}
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

void table_steigern::on_radio_unterweisung_toggled()
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
void table_steigern::on_radio_selbst_toggled()
{
}
void table_steigern::on_radio_praxis_toggled()
{
  if(radiobutton_praxis->get_active())
     table_pp_einstellungen->show();//set_sensitive(true);
  else
     table_pp_einstellungen->hide();//set_sensitive(false);
}

void table_steigern::on_radiobutton_pp_fertigkeit_toggled()
{ 
   spinbutton_pp_eingeben->hide();
// spinbutton_pp_eingeben->select_region(0,-1);
// on_radiobutton_pp_all_toggled();
}
void table_steigern::on_radiobutton_pp_zauber_toggled()
{
 spinbutton_pp_eingeben->set_value(hauptfenster->getAben().ZaubernPP());
 on_radiobutton_pp_all_toggled();
}
void table_steigern::on_radiobutton_pp_spezial_toggled()
{
 spinbutton_pp_eingeben->set_value(hauptfenster->getAben().SpezialPP());
 on_radiobutton_pp_all_toggled();
}
void table_steigern::on_radiobutton_pp_abwehr_toggled()    
{
 spinbutton_pp_eingeben->set_value(hauptfenster->getAben().AbwehrPP());
 on_radiobutton_pp_all_toggled(); 
}
void table_steigern::on_radiobutton_pp_resistenz_toggled()
{ 
 spinbutton_pp_eingeben->set_value(hauptfenster->getAben().ResistenzPP());
 on_radiobutton_pp_all_toggled();
}
void table_steigern::on_radiobutton_pp_all_toggled()
{
/*
  if(radiobutton_pp_fertigkeit->get_active())
    spinbutton_pp_eingeben->hide();
  else
*/
   {
     spinbutton_pp_eingeben->show();
     spinbutton_pp_eingeben->grab_focus();
     spinbutton_pp_eingeben->select_region(0,-1);
   }
}
                                

void table_steigern::on_spinbutton_pp_eingeben_activate()
{
  spinbutton_pp_eingeben->update();
  int PPanz = spinbutton_pp_eingeben->get_value_as_int();

 if(!radiobutton_pp_fertigkeit->get_active())
  {
    if(radiobutton_pp_abwehr->get_active())
       hauptfenster->getAben().setAbwehrPP(PPanz);
    else if(radiobutton_pp_zauber->get_active())
       hauptfenster->getAben().setZaubernPP(PPanz);
    else if(radiobutton_pp_spezial->get_active())
       hauptfenster->getAben().setSpezialPP(PPanz);
    else if(radiobutton_pp_resistenz->get_active())
       hauptfenster->getAben().setResistenzPP(PPanz);
    spinbutton_pp_eingeben->hide();
    radiobutton_steigern->get_active();
    zeige_werte();
    return;
  }   

 guint pagenr = notebook_lernen->get_current_page();
 try{
 const MBEmlt &M=getSelectedNotebookLernen();
// modify(PP,M,MidgardBasicElement::st_zusatz(""),PPanz);
 M->setPraxispunkte(PPanz);
 }catch(SimpleTree::noRowSelected &e) {Ausgabe(Ausgabe::Debug,e.what()); Ausgabe(Ausgabe::Error,"Keine Zeile selektiert");}

  if(pagenr==PAGE_FERTIGKEITEN)
     MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Fertigkeit(),alte_fert_tree,&hauptfenster->getAben()); 
  if(pagenr==PAGE_WAFFEN)
     MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Waffen(),alte_waffen_tree,&hauptfenster->getAben()); 
  if(pagenr==PAGE_SPRACHE)
   {
     MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Sprache(),alte_sprache_tree,&hauptfenster->getAben()); 
     MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Schrift(),alte_schrift_tree,&hauptfenster->getAben()); 
   }
  spinbutton_pp_eingeben->hide();
}

const MBEmlt &table_steigern::getSelectedNotebookLernen() throw(SimpleTree::noRowSelected)
{
 const Data_SimpleTree *dt;
 guint pagenr = notebook_lernen->get_current_page();
   if(pagenr==PAGE_FERTIGKEITEN)
      dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_fert_tree->getSelectedRowDataBase())); 
   if(pagenr==PAGE_WAFFEN)
      dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_waffen_tree->getSelectedRowDataBase())); 
   if(pagenr==PAGE_ZAUBER)
      dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_zauber_tree->getSelectedRowDataBase())); 
   if(pagenr==PAGE_KIDO)
      dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_kido_tree->getSelectedRowDataBase())); 
   if(pagenr==PAGE_SPRACHE)
    {
      try{ dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_sprache_tree->getSelectedRowDataBase())); }
      catch (std::exception &e)
       { dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_schrift_tree->getSelectedRowDataBase())); }
    }
  return dt->getMBE();
// cH_MidgardBasicElement MBE(dt->getMBE());
// return (const_cast<MidgardBasicElement*>(MBE));
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
  LernListen LL;
  switch ((*MBE)->ZusatzEnum(hauptfenster->getAben().getVTyp()))
   {
     case MidgardBasicElement::ZLand :
      {        
        title.push_back("Land auswählen");
        VZusatz=LL.getLandZusatz();
        break;
      }
     case MidgardBasicElement::ZWaffe :
      {      
        title.push_back("Waffe auswählen");
        VZusatz=LL.getWaffenZusatz(hauptfenster->getAben().List_Waffen());
        break;
      }
     case MidgardBasicElement::ZTabelle : 
      {
        title.push_back((*MBE)->Name()+" auswählen");
        title.push_back("Typ");
        title.push_back("Region");
        VZusatz=LL.getMBEZusatz(hauptfenster->getAben(),MBE);
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
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);
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

