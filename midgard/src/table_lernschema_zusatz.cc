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

#include <gdk/gdk.h>

void table_lernschema::lernen_zusatz(MidgardBasicElement::eZusatz was,MidgardBasicElement_mutable& MBE)
{
  // Weil Fertigkeiten mehrmals gelernt werden dürfen werde sie hier nicht 
  // in die LIste geschrieben.
  // eine Ausnamhe ist 'Landeskunde (Heimat)', das passiert unten
// list_FertigkeitZusaetze.push_back(MBE->Name());
  if(MBE.Lernpunkte()==0) // Sprache/Schrift für '0' Lernpunkte nur einmal lernen
    list_FertigkeitZusaetze.push_back(MBE->Name());
  if(MBE->Name()=="Schreiben: Muttersprache(+4)" ||
     MBE->Name()=="Schreiben: Muttersprache(+9)" ||
     MBE->Name()=="Schreiben: Muttersprache(+12)") 
    {
      list_FertigkeitZusaetze.push_back("Schreiben: Muttersprache(+4)");
      list_FertigkeitZusaetze.push_back("Schreiben: Muttersprache(+9)");
      list_FertigkeitZusaetze.push_back("Schreiben: Muttersprache(+12)");
    }
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
           cH_MidgardBasicElement MBE_=new Fertigkeit(*cH_Fertigkeit("Landeskunde"));
           MidgardBasicElement_mutable M(&*MBE_);
           M.setZusatz(hauptfenster->getCWerte().Herkunft()->Name());
           M.setErfolgswert(MBE.Erfolgswert());
           M.setLernpunkte(MBE.Lernpunkte());
           hauptfenster->getChar().List_Fertigkeit().push_back(M);
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
            if(MidgardBasicElement_mutable(&**i).ist_gelernt(hauptfenster->getCChar().CList_Sprache())) continue;
            datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
         }
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_sprache_selected));
       break;
      }
     case MidgardBasicElement::ZSchrift:
      {
       for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getDatabase().Schrift.begin();i!=hauptfenster->getDatabase().Schrift.end();++i)
         {
           if(MidgardBasicElement_mutable(&**i).ist_gelernt(hauptfenster->getCChar().CList_Schrift())) continue;
           if(!cH_Schrift(*i)->kann_Sprache(hauptfenster->getCChar().CList_Sprache())) continue;
           datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
         }
       if(datavec.empty()) 
         { hauptfenster->set_status("Keine Schrift lernbar (entweder keine Sprache gelernt oder es werden alle lernbaren Schriften schon beherrscht.)");
           list_FertigkeitZusaetze.remove(MBE->Name());
           if(MBE.LernArt()=="Fach")      lernpunkte.addFach( MBE.Lernpunkte());
           else if(MBE.LernArt()=="Allg") lernpunkte.addAllgemein( MBE.Lernpunkte());
           else if(MBE.LernArt()=="Unge") lernpunkte.addUnge( MBE.Lernpunkte());
           else hauptfenster->set_info("Fehler beim Lernpunkte zurückstellen");
           return;}
       connection = Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_schrift_selected));
       break;
      }
     case MidgardBasicElement::ZWaffe:
      {
       for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Waffen().begin();i!=hauptfenster->getCChar().CList_Waffen().end();++i)
        if (cH_Waffe(*i)->Art()=="Schußwaffe" || cH_Waffe(*i)->Art()=="Wurfwaffe")
          datavec.push_back(new Data_Zusatz(MBE,(*i)->Name()));
       if(datavec.empty()) 
         { hauptfenster->set_status("Noch keine Fernkampfwaffe gewählt.");
           hauptfenster->getChar().List_Fertigkeit().remove(MBE);
           list_FertigkeitZusaetze.remove(MBE->Name());
           if(MBE.LernArt()=="Fach")      lernpunkte.addFach( MBE.Lernpunkte());
           else if(MBE.LernArt()=="Allg") lernpunkte.addAllgemein( MBE.Lernpunkte());
           else if(MBE.LernArt()=="Unge") lernpunkte.addUnge( MBE.Lernpunkte());
           else hauptfenster->set_info("Fehler beim Lernpunkte zurückstellen");
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
 set_zusatz_sensitive(true);

// Tree_Lernschema_Zusatz->grab_focus();
/*
 Gdk_Window W_to=frame_lernschema_zusatz->get_window();
 GdkEventMask eventmask = gdk_window_get_events(W_to);
 GdkCursor *cursor=0;
 GdkWindow *Wto(Gdk_Window);
 gdk_pointer_grab(Wto,0,eventmask,Wto,cursor,0);
*/
// fra->pointer_grab();
}

void table_lernschema::lernen_zusatz_titel(MidgardBasicElement::eZusatz was,const MidgardBasicElement_mutable& MBE)
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
  set_zusatz_sensitive(false);
//  hauptfenster->notebook_main->set_sensitive(true);
  zeige_werte();  
  button_angeborene_fert->set_sensitive(true);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
     button_herkunft->set_sensitive(false);
}

void table_lernschema::on_zusatz_leaf_selected(cH_RowDataBase d)
{
  tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);
  MidgardBasicElement_mutable MBE=dt->getMBE();

  MBE.setZusatz(dt->getZusatz());
/*
  MBE.setErfolgswert(MBE->Erfolgswert());
  MBE.setLernpunkte(MBE->Lernpunkte());
*/
  if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
   {   
//     cH_MidgardBasicElement M=new Fertigkeit(*cH_Fertigkeit(MBE->Name()));
     hauptfenster->getChar().List_Fertigkeit().push_back(MBE);
   }
  else if(MBE->What()==MidgardBasicElement::ZAUBER)
   {   
//     cH_MidgardBasicElement M=new Zauber(*cH_Zauber(MBE->Name()));
     hauptfenster->getChar().List_Zauber().push_back(MBE);
   }

  set_zusatz_sensitive(false);
//  hauptfenster->notebook_main->set_sensitive(true);
  zeige_werte();  
  show_gelerntes();
}

void table_lernschema::on_zusatz_leaf_schrift_selected(cH_RowDataBase d)
{
  if(tree_lernschema) tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);

  MidgardBasicElement_mutable schrift(&*cH_Schrift(dt->getZusatz()));
  schrift.setErfolgswert(dt->getMBE().Erfolgswert());
  schrift.setLernpunkte(dt->getMBE().Lernpunkte());

//  MidgardBasicElement_mutable schrift=dt->getZusatz();
  hauptfenster->getChar().List_Schrift().push_back(schrift);
  set_zusatz_sensitive(false);
//  hauptfenster->notebook_main->set_sensitive(true);
  zeige_werte();  
  show_gelerntes();
}

void table_lernschema::on_zusatz_leaf_sprache_selected(cH_RowDataBase d)
{
  tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);

  MidgardBasicElement_mutable sprache(&*cH_Sprache(dt->getZusatz()));
  sprache.setErfolgswert(dt->getMBE().Erfolgswert());
  sprache.setLernpunkte(dt->getMBE().Lernpunkte());

  hauptfenster->getChar().List_Sprache().push_back(sprache);
  set_zusatz_sensitive(false);
//  hauptfenster->notebook_main->set_sensitive(true);
  zeige_werte();  
  show_gelerntes();
}

gint table_lernschema::on_eventbox_zusatz_leave_notify_event(GdkEventCrossing *ev)
{
  cout << "leave out\n";
  return false;
}

void table_lernschema::set_zusatz_sensitive(bool an)
{
 if(an)
  {
   handlebox_lernschema->set_sensitive(false);
   frame_lernpunkte->set_sensitive(false);
   tree_gelerntes->set_sensitive(false);
   scrolledwindow_lernen->set_sensitive(false);
   table_lernschema_121->set_sensitive(false);
   frame_lernschema_zusatz->show();
  }
 else
  {
   handlebox_lernschema->set_sensitive(true);
   frame_lernpunkte->set_sensitive(true);
   tree_gelerntes->set_sensitive(true);
   scrolledwindow_lernen->set_sensitive(true);
   table_lernschema_121->set_sensitive(true);
   frame_lernschema_zusatz->hide();
  }
}
