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
//#include <gtk--/toolbar.h>
#include <gtk--/pixmap.h>
#include "class_SimpleTree.hh"
#include "class_SimpleTree_LernschemaZusatz.hh"

///////////////////////////////////////////////////////////
void table_steigern::on_radio_steigern_toggled()
{ on_radio_steigern_all();}
void table_steigern::on_radio_reduzieren_toggled()
{ on_radio_steigern_all();}
void table_steigern::on_radio_verlernen_toggled()
{ on_radio_steigern_all();}
void table_steigern::on_radio_steigern_all()
{
/*
  if (radiobutton_steigern->get_active())
     frame_lernen_mit->set_sensitive(true); 
  else
     frame_lernen_mit->set_sensitive(false); 
*/
}

void table_steigern::on_togglebutton_praxispunkte_toggled()
{
  if(togglebutton_praxispunkte->get_active())
   {
     radiobutton_pp_fertigkeit->set_active(true);
     vbox_praxispunkte->show();
     if(hauptfenster->getCChar().CTyp1()->is_mage() || hauptfenster->getCChar().CTyp2()->is_mage()) 
         radiobutton_pp_zauber->set_sensitive(true);//show();
     else
         radiobutton_pp_zauber->set_sensitive(true);//hide();
   }
  else
   {
     vbox_praxispunkte->hide();
     spinbutton_pp_eingeben->hide();
   }
}

std::string table_steigern::SpruecheMitPP()
{
  if(hauptfenster->getCChar().CTyp1()->SpruecheMitPP())
       return hauptfenster->getCChar().CTyp1()->SpruecheMitPP_Text();
  else if(hauptfenster->getCChar().CTyp2()->SpruecheMitPP())
       return hauptfenster->getCChar().CTyp2()->SpruecheMitPP_Text();
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
}

void table_steigern::on_radiobutton_pp_fertigkeit_toggled()
{on_radiobutton_pp_all_toggled();}
void table_steigern::on_radiobutton_pp_zauber_toggled()
{on_radiobutton_pp_all_toggled();}
void table_steigern::on_radiobutton_pp_abwehr_toggled()    
{on_radiobutton_pp_all_toggled();}
void table_steigern::on_radiobutton_pp_resistenz_toggled()
{on_radiobutton_pp_all_toggled();}
void table_steigern::on_radiobutton_pp_all_toggled()
{
  if(radiobutton_pp_fertigkeit->get_active())
    spinbutton_pp_eingeben->hide();
  else 
    spinbutton_pp_eingeben->show();
}
                                

void table_steigern::on_spinbutton_pp_eingeben_activate()
{
  spinbutton_pp_eingeben->update();
  int PPanz = spinbutton_pp_eingeben->get_value_as_int();

 if(!radiobutton_pp_fertigkeit->get_active())
  {
    if(radiobutton_pp_abwehr->get_active())
       hauptfenster->getChar().getWerte().setAbwehrPP(PPanz);
    else if(radiobutton_pp_zauber->get_active())
       hauptfenster->getChar().getWerte().setZaubernPP(PPanz);
    else if(radiobutton_pp_spezial->get_active())
       hauptfenster->getChar().getWerte().setSpezialPP(PPanz);
    else if(radiobutton_pp_resistenz->get_active())
       hauptfenster->getChar().getWerte().setResistenzPP(PPanz);
    spinbutton_pp_eingeben->hide();
    radiobutton_steigern->get_active();
    zeige_werte();
    return;
  }   
 
 guint pagenr = notebook_lernen->get_current_page_num();
 MidgardBasicElement_mutable M=getSelectedNotebookLernen();
 modify(PP,M,"",PPanz);

// const_cast<MidgardBasicElement_mutable&>(getSelectedNotebookLernen()).setPraxispunkte(PPanz);


  if(pagenr==PAGE_FERTIGKEITEN)
     MidgardBasicElement::show_list_in_tree(hauptfenster->getCChar().CList_Fertigkeit(),alte_fert_tree,hauptfenster); 
  if(pagenr==PAGE_WAFFEN)
     MidgardBasicElement::show_list_in_tree(hauptfenster->getCChar().CList_Waffen(),alte_waffen_tree,hauptfenster); 
  if(pagenr==PAGE_SPRACHE)
   {
     MidgardBasicElement::show_list_in_tree(hauptfenster->getCChar().CList_Sprache(),alte_sprache_tree,hauptfenster); 
     MidgardBasicElement::show_list_in_tree(hauptfenster->getCChar().CList_Schrift(),alte_schrift_tree,hauptfenster); 
   }
  spinbutton_pp_eingeben->hide();
}

const MidgardBasicElement_mutable &table_steigern::getSelectedNotebookLernen()
{
 const Data_SimpleTree *dt;
 guint pagenr = notebook_lernen->get_current_page_num();
 try{
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
          catch (std::exception &e) {}
      try {dt=dynamic_cast<const Data_SimpleTree*>(&*(alte_schrift_tree->getSelectedRowDataBase())); }
          catch (std::exception &e) {}
    }
  }catch(std::exception &e) {cerr << e.what()<<'\n'; assert(!"Fehler");}
 return dt->getMBE();
// cH_MidgardBasicElement MBE(dt->getMBE());
// return (const_cast<MidgardBasicElement*>(MBE));
}



void table_steigern::on_button_alter_clicked()
{
  float tage=hauptfenster->getCChar().getCWerte().Steigertage();
  int alter=hauptfenster->getCChar().getCWerte().Alter();
  int tage_pro_jahr=360;
  while(tage>tage_pro_jahr)
   {
     alter+=1;
     tage-=tage_pro_jahr;
   }
  hauptfenster->getChar().getWerte().setAlter(alter);
  hauptfenster->getChar().getWerte().setSteigertage(tage);
  zeige_werte();
}


void table_steigern::fillClistZusatz(MidgardBasicElement_mutable &MBE)
{
  std::vector<cH_RowDataBase> datavec;
  std::vector<std::string> title;
  switch (MBE->ZusatzEnum(hauptfenster->getCChar().getVTyp()))
   {
     case MidgardBasicElement::ZLand :
      {        
        title.push_back("Land auswählen");
        for (std::vector<cH_Land>::const_iterator i=hauptfenster->getCDatabase().Laender.begin();i!=hauptfenster->getCDatabase().Laender.end();++i)
         {
           datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
         }
        break;
      }
     case MidgardBasicElement::ZWaffe :
      {      
        title.push_back("Waffe auswählen");
        for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Waffen().begin();i!=hauptfenster->getCChar().CList_Waffen().end();++i)
         {
           if (cH_Waffe(*i)->Art()=="Schußwaffe" || cH_Waffe(*i)->Art()=="Wurfwaffe")
            {
              datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
            }
         }
        break;
      }
     case MidgardBasicElement::ZTabelle : 
      {
        title.push_back(MBE->Name()+" auswählen");
        std::vector<std::string> VZ=MBE->VZusatz();
        for (std::vector<std::string>::const_iterator i=VZ.begin();i!=VZ.end();++i)
           {
             datavec.push_back(new Data_Zusatz(MBE,(*i)));
           }
        break; 
       }
     default : assert("Never get here\n");
   }
  tree_steigern_zusatz->setTitles(title);
  tree_steigern_zusatz->setDataVec(datavec);
  scrolledwindow_landauswahl->show();
}



//#include <algorithm>
void table_steigern::on_steigern_zusatz_leaf_selected(cH_RowDataBase d)
{
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);

/*
  MidgardBasicElement_mutable M
      =const_cast<MidgardBasicElement_mutable&>(dt->getMBE());
*/
#warning: Christof, warum geht das nicht?
/*
  M.setZusatz(dt->getZusatz());
  // Erhöter Erfolgswert für Landeskunde Heimat:
  if(dt->getZusatz()==hauptfenster->getCWerte().Herkunft()->Name()) 
       M.setErfolgswert(9);
*/
  modify(Zusatz,dt->getMBE(),dt->getZusatz(),0);

  scrolledwindow_landauswahl->hide();
  on_fertigkeiten_laden_clicked();
  neue_fert_tree->set_sensitive(true);
}

void table_steigern::modify(modi_modus modus,const MidgardBasicElement_mutable &M,const std::string &zusatz,int praxispunkte)
{
  bool found=false;
  int c=0;
  while(true)
   {
     std::list<MidgardBasicElement_mutable> &L=hauptfenster->getChar().List_Fertigkeit();
     if(c==0) L=hauptfenster->getChar().List_Fertigkeit();
     else if(c==1) L=hauptfenster->getChar().List_Zauber();
     else assert(!"never get here\n");
     for(std::list<MidgardBasicElement_mutable>::iterator i=L.begin();i!=L.end();++i)
      {
        if( i->Zusatz().empty() && (*i)->Name() == M->Name())       
         {
           found=true;
           if(modus==PP)
             i->setPraxispunkte(praxispunkte);
           else if(modus==Zusatz)
            {
              i->setZusatz(zusatz);
              if(zusatz==hauptfenster->getCWerte().Herkunft()->Name()) 
                i->setErfolgswert(9);
            }
         }
      }
    if(found) break;
    else ++c;
   }
}
