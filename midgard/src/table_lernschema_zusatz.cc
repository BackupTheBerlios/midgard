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
#include "Zauber.hh"
#include "Waffe.hh"
#include "Sprache.hh"
#include "Schrift.hh"

static SigC::Connection connection;


void table_lernschema::lernen_zusatz(MidgardBasicElement::eZusatz was,const cH_MidgardBasicElement& MBE)
{
  // Weil Fertigkeiten mehrmals gelernt werden dürfen werde sie hier nicht 
  // in die LIste geschrieben.
  // eine Ausnamhe ist 'Landeskunde (Heimat)', das passiert unten
// list_FertigkeitZusaetze.push_back(MBE->Name());
  if(MBE->Lernpunkte()==0) // Sprache/Schrift für '0' Lernpunkte nur einmal lernen
    list_FertigkeitZusaetze.push_back(MBE->Name());
  lernen_zusatz_titel(was,MBE);
  std::vector<cH_RowDataBase> datavec;
  connection.disconnect();
  switch(was)
   {
     case MidgardBasicElement::ZHerkunft:
      {
       for (std::vector<cH_Land>::const_iterator i=hauptfenster->getDatabase().Laender.begin();i!=hauptfenster->getDatabase().Laender.end();++i)
         datavec.push_back(new Data_Herkunft(*i));
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_herkunft_leaf_selected));
       scrolledwindow_lernen->hide();
       break;
      }
     case MidgardBasicElement::ZLand:
      {
       if(MBE->Name()=="Landeskunde (Heimat)")
         {
           list_FertigkeitZusaetze.push_back(MBE->Name());
           cH_MidgardBasicElement M=new Fertigkeit(*cH_Fertigkeit("Landeskunde"));
           M->setZusatz(hauptfenster->getCWerte().Herkunft()->Name());
           M->setErfolgswert(MBE->Erfolgswert());
           M->setLernpunkte(MBE->Lernpunkte());
           hauptfenster->list_Fertigkeit.push_back(M);
           return;
         }
       else
         for (std::vector<cH_Land>::const_iterator i=hauptfenster->getDatabase().Laender.begin();i!=hauptfenster->getDatabase().Laender.end();++i)
            datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZSprache:
      {
       for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getDatabase().Sprache.begin();i!=hauptfenster->getDatabase().Sprache.end();++i)
         {
            if(MBE->Name()=="Muttersprache" && cH_Sprache(*i)->Alte_Sprache()) 
              {
                list_FertigkeitZusaetze.push_back(MBE->Name());
                continue ;
              }
            if(MBE->Name()=="Sprechen: Alte Sprache" && !cH_Sprache(*i)->Alte_Sprache())
              {
                list_FertigkeitZusaetze.push_back(MBE->Name());
                continue ;
              }
            if((*i)->ist_gelernt(hauptfenster->list_Sprache)) continue;
            datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
         }
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_sprache_selected));
       break;
      }
     case MidgardBasicElement::ZSchrift:
      {
       for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getDatabase().Schrift.begin();i!=hauptfenster->getDatabase().Schrift.end();++i)
         {
           if((*i)->ist_gelernt(hauptfenster->list_Schrift)) continue;
           if(!cH_Schrift(*i)->kann_Sprache(hauptfenster->list_Sprache)) continue;
           datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
         }
       if(datavec.empty()) 
         { hauptfenster->set_status("Keine Schrift lernbar (entweder keine Sprache gelernt oder es werden alle lernbaren Schriften schon beherrscht.)");
           list_FertigkeitZusaetze.remove(MBE->Name());
           return;}
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_schrift_selected));
       break;
      }
     case MidgardBasicElement::ZWaffe:
      {
       for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->list_Waffen.begin();i!=hauptfenster->list_Waffen.end();++i)
        if (cH_Waffe(*i)->Art()=="Schußwaffe" || cH_Waffe(*i)->Art()=="Wurfwaffe")
          datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
       if(datavec.empty()) 
         { hauptfenster->set_status("Noch keine Fernkampfwaffe gewählt.");
           hauptfenster->list_Fertigkeit.remove(MBE);
           list_FertigkeitZusaetze.remove(MBE->Name());
           return;}
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZTabelle:
      {
       std::vector<std::string> VG=MBE->VZusatz();
       for (std::vector<std::string>::const_iterator i=VG.begin();i!=VG.end();++i)
           datavec.push_back(new Data_Zusatz(MBE,*i));
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZNone : break;
   }
 Tree_Lernschema_Zusatz->setDataVec(datavec);
 frame_lernschema_zusatz->show();
 Tree_Lernschema_Zusatz->grab_focus();
}

void table_lernschema::lernen_zusatz_titel(MidgardBasicElement::eZusatz was,const cH_MidgardBasicElement& MBE)
{
  std::vector<std::string> vs;
  Tree_Lernschema_Zusatz->set_column_visibility(1,false);
  Tree_Lernschema_Zusatz->set_column_visibility(2,false);
  switch(was)
   {
     case MidgardBasicElement::ZHerkunft :
      {
       frame_lernschema_zusatz->set_label("Herkunftsland wählen");
       vs.push_back("Land");
       vs.push_back("Kontinent");
       vs.push_back("Sprache(n)");
       Tree_Lernschema_Zusatz->set_column_visibility(1,true);
       Tree_Lernschema_Zusatz->set_column_visibility(2,true);
       break;
      }
     case MidgardBasicElement::ZWaffe :
      {
       frame_lernschema_zusatz->set_label("Fernkampfwaffe auswählen");
       vs.push_back(MBE->Name());
       vs.push_back("");
       vs.push_back("");
       break;
      }
     case MidgardBasicElement::ZTabelle :
      {
       frame_lernschema_zusatz->set_label("Zusatz auswählen");
       vs.push_back(MBE->Name());
       vs.push_back("");
       vs.push_back("");
       break;
      }
     case MidgardBasicElement::ZSchrift :
      {
       frame_lernschema_zusatz->set_label("Schrift auswählen");
       vs.push_back(MBE->Name());
       vs.push_back("");
       vs.push_back("");
       break;
      }
     case MidgardBasicElement::ZSprache :
      {
       if(MBE->Name()=="Muttersprache")
        {
          vector<std::string> V=hauptfenster->getCWerte().Herkunft()->Sprachen();
          vector<std::string> W;
          for(vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
            if(!cH_Sprache(*i)->Alte_Sprache()) W.push_back(*i) ;
          std::string s,label;
          for(vector<std::string>::const_iterator i=W.begin();i!=W.end();)
              { s+=*i; if(++i!=W.end()) s+=", ";}
          if(W.size()==1)  label ="Muttersprache ("+s+") wählen" ;
          else label = "Eine Muttersprache wählen\n("+s+")" ;
          frame_lernschema_zusatz->set_label(label);
        }
       else frame_lernschema_zusatz->set_label("Sprache auswählen");
       vs.push_back(MBE->Name());
       vs.push_back("");
       vs.push_back("");
       break;
      }
    default : break;
   }
 Tree_Lernschema_Zusatz->setTitles(vs);
}


void table_lernschema::on_herkunft_leaf_selected(cH_RowDataBase d)
{
  const Data_Herkunft *dt=dynamic_cast<const Data_Herkunft*>(&*d);
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::HERKUNFT);
  hauptfenster->getWerte().setHerkunft(dt->getLand());
  frame_lernschema_zusatz->hide();
  zeige_werte();  
  button_angeborene_fert->set_sensitive(true);
  button_herkunft->set_sensitive(false);
}

void table_lernschema::on_zusatz_leaf_selected(cH_RowDataBase d)
{
  tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);
  cH_MidgardBasicElement MBE=dt->getMBE();

  MBE->setZusatz(dt->getZusatz());
  MBE->setErfolgswert(MBE->Erfolgswert());
  MBE->setLernpunkte(MBE->Lernpunkte());

  if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
   {   
     cH_MidgardBasicElement M=new Fertigkeit(*cH_Fertigkeit(MBE->Name()));
     hauptfenster->list_Fertigkeit.push_back(M);
   }
  else if(MBE->What()==MidgardBasicElement::ZAUBER)
   {   
     cH_MidgardBasicElement M=new Zauber(*cH_Zauber(MBE->Name()));
     hauptfenster->list_Zauber.push_back(M);
   }

  frame_lernschema_zusatz->hide();
  zeige_werte();  
  show_gelerntes();
}

void table_lernschema::on_zusatz_leaf_schrift_selected(cH_RowDataBase d)
{
  if(tree_lernschema) tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);
  cH_MidgardBasicElement MBE=dt->getMBE();
  cH_MidgardBasicElement schrift(&*cH_Schrift(dt->getZusatz()));
  schrift->setErfolgswert(MBE->Erfolgswert());
  schrift->setLernpunkte(MBE->Lernpunkte());
  hauptfenster->list_Schrift.push_back(schrift);
  frame_lernschema_zusatz->hide();
  zeige_werte();  
  show_gelerntes();
}

void table_lernschema::on_zusatz_leaf_sprache_selected(cH_RowDataBase d)
{
  tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);
  cH_MidgardBasicElement MBE=dt->getMBE();
  cH_MidgardBasicElement sprache(&*cH_Sprache(dt->getZusatz()));
  sprache->setErfolgswert(MBE->Erfolgswert());
  sprache->setLernpunkte(MBE->Lernpunkte());
  hauptfenster->list_Sprache.push_back(sprache);
  frame_lernschema_zusatz->hide();
  zeige_werte();  
  show_gelerntes();
}

gint table_lernschema::on_Tree_Lernschema_Zusatz_leave_notify_event(GdkEventCrossing *ev)
{
  cout << "leave out\n";
  return false;
}
