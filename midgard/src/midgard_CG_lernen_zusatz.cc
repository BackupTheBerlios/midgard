/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "class_SimpleTree_LernschemaZusatz.hh"
#include "midgard_CG.hh"
#include "Fertigkeiten.hh"
#include "Waffe.hh"

static SigC::Connection connection;


void midgard_CG::lernen_zusatz(MidgardBasicElement::eZusatz was,const cH_MidgardBasicElement& MBE)
{
  list_FertigkeitZusaetze.push_back(MBE->Name());
  lernen_zusatz_titel(was,MBE);
  std::vector<cH_RowDataBase> datavec;
  connection.disconnect();
  switch(was)
   {
     case MidgardBasicElement::ZHerkunft:
      {
       for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
         datavec.push_back(new Data_Herkunft(*i));
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_herkunft_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZLand:
      {
       if(MBE->Name()=="Landeskunde (Heimat)")
         {
           cH_MidgardBasicElement M=new Fertigkeit(*cH_Fertigkeit("Landeskunde"));
           M->setZusatz(Werte.Herkunft()->Name());
           list_Fertigkeit.push_back(M);
           return;
         }
       else
         for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
            datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZWaffe:
      {
       for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
        if (cH_Waffe(*i)->Art()=="Schußwaffe" || cH_Waffe(*i)->Art()=="Wurfwaffe")
          datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
       if(datavec.empty()) 
         { regnot("Noch keine Fernkampfwaffe gewählt.");
           list_Fertigkeit.remove(MBE);
           list_FertigkeitZusaetze.remove(MBE->Name());
           return;}
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZTabelle:
      {
       std::vector<std::string> VG=MBE->VZusatz();
       for (std::vector<std::string>::const_iterator i=VG.begin();i!=VG.end();++i)
           datavec.push_back(new Data_Zusatz(MBE,*i));
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZNone : break;
   }
 Tree_Lernschema_Zusatz->setDataVec(datavec);
 tree_lernschema->set_sensitive(false);
 frame_lernschema_zusatz->show();
}

void midgard_CG::lernen_zusatz_titel(MidgardBasicElement::eZusatz was,const cH_MidgardBasicElement& MBE)
{
  std::vector<std::string> vs;
  switch(was)
   {
     case MidgardBasicElement::ZHerkunft :
      {
       frame_lernschema_zusatz->set_label("Herkunftsland wählen");
       vs.push_back("Land");
       vs.push_back("Koninent");
       vs.push_back("Sprache(n)");
      }
     case MidgardBasicElement::ZTabelle :
      {
       frame_lernschema_zusatz->set_label("Zusatz auswählen");
       vs.push_back(MBE->Name());
       vs.push_back("");
       vs.push_back("");
      }
    default : break;
   }
 Tree_Lernschema_Zusatz->setTitles(vs);
}


void midgard_CG::on_herkunft_leaf_selected(cH_RowDataBase d)
{
  const Data_Herkunft *dt=dynamic_cast<const Data_Herkunft*>(&*d);
  if(wizard) 
   { wizard->next_step();
   }
  Werte.setHerkunft(dt->getLand());
  frame_lernschema_zusatz->hide();
  tree_lernschema->set_sensitive(true);
  zeige_werte(Werte);  
  button_angeborene_fert->set_sensitive(true);
  button_herkunft->set_sensitive(false);
}

void midgard_CG::on_zusatz_leaf_selected(cH_RowDataBase d)
{
  tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);
  cH_MidgardBasicElement MBE=dt->getMBE();
  MBE->setZusatz(dt->getZusatz());
  frame_lernschema_zusatz->hide();
  zeige_werte(Werte);  
  show_gelerntes();
}

