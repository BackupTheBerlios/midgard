// $Id: midgard_CG_lernen.cc,v 1.101 2002/04/11 14:11:41 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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
#include "Window_waffe.hh"
#include <Aux/itos.h>
#include "class_SimpleTree.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
//#include "Zauber.hh"
#include "Fertigkeiten.hh"
//#include "Sprache_auswahl.hh"
#include "Window_Waffenbesitz.hh"
#include "Window_Geld_eingeben.hh"
#include "Window_ruestung.hh"

void midgard_CG::on_herkunftsland_clicked()
{
  cH_MidgardBasicElement Dummy=new Fertigkeit(*cH_Fertigkeit("",true));
  lernen_zusatz(MidgardBasicElement::ZHerkunft,Dummy);
}

void midgard_CG::on_lernpunkte_wuerfeln_clicked()
{
  //Speziesspezifische Fertigkeiten
  int lpspezies=0;
  list_Fertigkeit=Werte.Spezies()->getFertigkeiten(lpspezies,Werte);
  show_gelerntes();

  int fachlern=random.integer(1,6)+random.integer(1,6);
  if(!list_Fertigkeit.empty())
    regnot("Die Lernpunkte ("+itos(lpspezies)+") für die Pflichtfertigkeiten\n"
      "für die Spezies "+Werte.Spezies()->Name()+" wurden von den erfürfelten\n"
      "Lernpunkten ("+itos(fachlern)+") abgezogen.");
  lernpunkte.setFach(fachlern - lpspezies);
  lernpunkte.setAllgemein(random.integer(1,6)+1);
  lernpunkte.setUnge(random.integer(1,6));
  if (Typ[1]->Short()=="") lernpunkte.setWaffen(random.integer(1,6)+random.integer(1,6));
  else                     lernpunkte.setWaffen(random.integer(1,6)+1); // Doppelcharakter
  if (Typ[0]->is_mage() && Typ[1]->Short()=="") 
      lernpunkte.setZauber(random.integer(1,6)+random.integer(1,6));
  if (Typ[1]->is_mage() && Typ[1]->Short()!="") 
      lernpunkte.setZauber(random.integer(1,6)+1);

  int age = (lernpunkte.Allgemein() + lernpunkte.Unge() 
             + lernpunkte.Fach()
             + lernpunkte.Waffen() + lernpunkte.Zauber())/4+16;

  Werte.setAlter( age * Werte.Spezies()->AlterFaktor());
  spinbutton_alter->set_value(Werte.Alter());
  zeige_lernpunkte();

  button_lernpunkte->set_sensitive(false);
  button_fachkenntnisse->set_sensitive(true);    
  button_allgemeinwissen->set_sensitive(true);   
  button_untyp_fertigkeiten->set_sensitive(true);
  button_waffen->set_sensitive(true);
  if(Typ[1]->is_mage() || Typ[1]->is_mage() || magie_bool) 
      button_zauber->set_sensitive(true);
  button_lernschema_geld->set_sensitive(true);
  button_lernschema_waffen->set_sensitive(true);
  button_ruestung->set_sensitive(true);

  on_lernliste_wahl_toggled();
}


void midgard_CG::on_button_fach_trans_clicked()
{
 if(lernpunkte.Fach()>0) 
   {
     lernpunkte.addFach(-1);
     lernpunkte.addUnge(+1);
   }
 zeige_lernpunkte();
}

void midgard_CG::on_button_waffe_trans_clicked()
{
 if(lernpunkte.Waffen()>0) 
   {
     lernpunkte.addWaffen(-1);
     lernpunkte.addUnge(+1);
   }
 zeige_lernpunkte();
}

void midgard_CG::on_togglebutton_lernpunkte_edit_toggled()
{
  edit_lernpunkte(togglebutton_lernpunkte_edit->get_active());
//  zeige_notebook();
}

void midgard_CG::edit_lernpunkte(bool b)
{
 spinbutton_fach->set_sensitive(b);
 spinbutton_allgemein->set_sensitive(b);
 spinbutton_unge->set_sensitive(b);
 spinbutton_waffen->set_sensitive(b);
 spinbutton_zauber->set_sensitive(b);
 spinbutton_beruf->set_sensitive(b);
}


gint midgard_CG::on_spinbutton_fach_focus_out_event(GdkEventFocus *ev)
{ set_lernpunkte();  return false;}
gint midgard_CG::on_spinbutton_allgemein_focus_out_event(GdkEventFocus *ev)
{ set_lernpunkte();  return false;}
gint midgard_CG::on_spinbutton_unge_focus_out_event(GdkEventFocus *ev)
{ set_lernpunkte();  return false;}
gint midgard_CG::on_spinbutton_waffen_focus_out_event(GdkEventFocus *ev)
{ set_lernpunkte();  return false;}
gint midgard_CG::on_spinbutton_zaubern_focus_out_event(GdkEventFocus *ev)
{ set_lernpunkte();  return false;}

void midgard_CG::on_spinbutton_fach_activate()
{ set_lernpunkte(); spinbutton_allgemein->grab_focus();}
void midgard_CG::on_spinbutton_allgemein_activate()
{ set_lernpunkte(); spinbutton_unge->grab_focus();}
void midgard_CG::on_spinbutton_unge_activate()
{ set_lernpunkte(); spinbutton_waffen->grab_focus();}
void midgard_CG::on_spinbutton_waffen_activate()
{ set_lernpunkte(); spinbutton_zauber->grab_focus();}
void midgard_CG::on_spinbutton_zaubern_activate()
{ set_lernpunkte(); togglebutton_lernpunkte_edit->set_active(false);}

void midgard_CG::set_lernpunkte()
{
  gtk_spin_button_update(spinbutton_unge->gtkobj());
  lernpunkte.setUnge(spinbutton_unge->get_value_as_int());
  gtk_spin_button_update(spinbutton_fach->gtkobj());
  lernpunkte.setFach(spinbutton_fach->get_value_as_int());
  gtk_spin_button_update(spinbutton_allgemein->gtkobj());
  lernpunkte.setAllgemein(spinbutton_allgemein->get_value_as_int());
  gtk_spin_button_update(spinbutton_waffen->gtkobj());
  lernpunkte.setWaffen(spinbutton_waffen->get_value_as_int());
  gtk_spin_button_update(spinbutton_zauber->gtkobj());
  lernpunkte.setZauber(spinbutton_zauber->get_value_as_int());
  on_lernliste_wahl_toggled();
  zeige_werte();
}

void midgard_CG::zeige_lernpunkte()
{
 spinbutton_fach->set_value(lernpunkte.Fach());
 spinbutton_allgemein->set_value(lernpunkte.Allgemein());
 spinbutton_unge->set_value(lernpunkte.Unge());
 spinbutton_waffen->set_value(lernpunkte.Waffen());
 spinbutton_zauber->set_value(lernpunkte.Zauber());
 zeige_werte();

 if(lernpunkte.Fach()==0 && lernpunkte.Allgemein()==0 &&
    lernpunkte.Unge()==0 && lernpunkte.Waffen()==0 &&
    lernpunkte.Zauber()==0 )
 table_berufswahl->set_sensitive(true);
}


gint midgard_CG::on_button_lernschema_waffen_button_release_event(GdkEventButton *ev)
{   
  button_lernschema_waffen->set_sensitive(false);
  if  (ev->button==1)
   {
     int wurf = random.integer(1,100);
     manage (new Window_waffe(wurf,this,Werte,Typ,Database,list_Waffen));
   }
  else if (ev->button==3) 
     manage (new Window_Waffenbesitz(this,list_Waffen,list_Waffen_besitz));
  return 0;
}

gint midgard_CG::on_button_lernschema_geld_button_release_event(GdkEventButton *ev)
{
  button_lernschema_geld->set_sensitive(false);
  Werte.setGeld(0,0,0);
  if      (ev->button==1)  lernschema_geld_wuerfeln();
  else if (ev->button==3)  manage (new Window_Geld_eingeben(this,Werte));;
  return 0;
}

void midgard_CG::lernschema_geld_wuerfeln()
{
 int igold=0;  
 vector<int> V;
 for(int i=0;i<3;++i) V.push_back(random.integer(1,6));
 igold=V[0]+V[1]+V[2];
 if      (Typ[0]->Geld() == 1) igold-=3;
 else if (Typ[0]->Geld() == 2) igold+=0;
 else if (Typ[0]->Geld() == 3) igold+=6;
 else if (Typ[0]->Geld() == 4) igold+=3;

 if(Werte.Stand()=="Adel" ) igold*=2;  
 if(Werte.Stand()=="Unfrei" ) igold/=2;
 if(V[0]==V[1] && V[1]==V[2]) igold += 100;

 std::string strinfo ="Beim Auswürfeln von Geld wurden \n"
   +itos(V[0])+"  "+itos(V[1])+"  "+itos(V[2])+"\n gewürfelt\n"
   "das ergibt "+itos(igold)+" Gold\n";
 InfoFenster->AppendShow(strinfo);
 Werte.addGold(igold);
 Geld_uebernehmen();
}


gint midgard_CG::on_button_ruestung_button_release_event(GdkEventButton *ev)
{
  button_ruestung->set_sensitive(false);
  if      (ev->button==1)  on_button_ruestung_clicked();
  else if (ev->button==3)  manage (new Window_ruestung(Werte,this,Database));
  return 0;
}


void midgard_CG::on_button_ruestung_clicked()
{
  std::string rue;
  int wurf = random.integer(1,100);
  if (Typ[0]->Ruestung() == 1)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "TR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "LR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "LR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "LR" ;
      if (96 <= wurf && wurf  <= 100) rue = "LR" ;
   }    
  if (Typ[0]->Ruestung()== 2)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "LR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "LR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "KR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "KR" ;
      if (96 <= wurf && wurf  <= 100) rue = "KR" ;
   }    
  if (Typ[0]->Ruestung()== 3)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "LR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "KR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "KR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "KR" ;
      if (96 <= wurf && wurf  <= 100) rue = "PR" ;
   }    
  if (Typ[0]->Ruestung()== 4)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "OR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "OR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "TR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "TR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "LR" ;
      if (96 <= wurf && wurf  <= 100) rue = "LR" ;
   }    
  Werte.setRuestung(cH_Ruestung(rue));
  std::string strinfo ="Beim Auswürfeln der Rüstung wurde eine\n"+itos(wurf)+" gewürfelt\n";
  strinfo += "---> " + Werte.Ruestung()->Long();
  InfoFenster->AppendShow(strinfo);
  zeige_werte();
}


void midgard_CG::on_lernliste_wahl_toggled()
{
  if(button_zauber->get_active())
   {
     if (Werte.Spezialgebiet()->Spezial2()=="" && Typ[0]->Short()=="eBe")
      {
         std::string strinfo="Erst Primär- und Sekundärelement wählen\n";
         InfoFenster->AppendShow(strinfo);
         return;
      }
   }
 show_lernschema();
}

void midgard_CG::on_button_waffen_clicked()
{
 button_lernschema_waffen->set_sensitive(true);
}



void midgard_CG::on_tree_gelerntes_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if(togglebutton_spezialwaffe->get_active() && MBE->What()!= MidgardBasicElement::WAFFE)
      {
        togglebutton_spezialwaffe->set_active(false); return ; 
      }
  switch(MBE->What()) {
     case MidgardBasicElement::WAFFE : 
         { 
           if(togglebutton_spezialwaffe->get_active() )
            { 
              if(cH_Waffe(MBE)->Verteidigung())
               regnot("Eine Verteidingungswaffe kann keine Spezialwaffe werden.");
             else
              {
               Werte.setSpezialisierung(MBE->Name());
               Waffe::setSpezialWaffe(Werte.Spezialisierung(),list_Waffen);
              }
            }
           else
            {
              list_Waffen.remove(MBE);
              lernpunkte.addWaffen(MBE->Lernpunkte());
            }
           break;
         }
     case MidgardBasicElement::ZAUBER : 
         { list_Zauber.remove(MBE);
           lernpunkte.addZauber(MBE->Lernpunkte());
           break;
         }
     case MidgardBasicElement::FERTIGKEIT_ANG : 
         { list_Fertigkeit_ang.remove(MBE);
           break;
         }
     case MidgardBasicElement::FERTIGKEIT : 
         { list_Fertigkeit.remove(MBE);
           if(cH_Fertigkeit(MBE)->LernArt()=="Fach")      lernpunkte.addFach( MBE->Lernpunkte());
           else if(cH_Fertigkeit(MBE)->LernArt()=="Allg") lernpunkte.addAllgemein( MBE->Lernpunkte());
           else if(cH_Fertigkeit(MBE)->LernArt()=="Unge") lernpunkte.addUnge( MBE->Lernpunkte());
           break;
         }
     case MidgardBasicElement::SPRACHE : 
           list_Sprache.remove(MBE);
     case MidgardBasicElement::SCHRIFT : 
           list_Schrift.remove(MBE);

           if(button_fachkenntnisse->get_active())
                lernpunkte.addFach(MBE->Lernpunkte());
           else if(button_allgemeinwissen->get_active())
                lernpunkte.addAllgemein(MBE->Lernpunkte());
           else if(button_untyp_fertigkeiten->get_active())
                lernpunkte.addUnge(MBE->Lernpunkte());
           else regnot("Da kein Fertigkeiten-Auswahl-Knopf gewählt wurde konnten die Lernpunkte ("
                  +itos(MBE->Lernpunkte())+") für das Verlernen dieser Sprache nicht gut geschrieben werden.");
           break;

     default : break;
   }
  show_lernschema(); // Lernschema setzt die Erfolgswerte zurück
//  Waffe::setSpezialWaffe(Werte.Spezialisierung(),list_Waffen);
  show_gelerntes();
}

void midgard_CG::on_tree_lernschema_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if(MBE->Gelernt()) 
   { 
     regnot ("Diese Fertigkeit ist schon gelernt");
     tree_lernschema->unselect_all();
     return;
   }
  switch(MBE->What()) {
    case MidgardBasicElement::WAFFE: 
      { 
        if(MBE->Lernpunkte()>lernpunkte.Waffen()) 
          { regnot ("Nicht genug Lernpunkte"); 
            tree_lernschema->unselect_all();
            return;
          }
        list_Waffen.push_back(MBE); 
        list_WaffenGrund.push_back(&*cH_WaffeGrund(cH_Waffe(MBE)->Grundkenntnis()));
        list_WaffenGrund.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
        list_WaffenGrund.unique();
        lernpunkte.addWaffen(- MBE->Lernpunkte());
        break; }
    case MidgardBasicElement::ZAUBER: 
      { 
        if(MBE->Lernpunkte()>lernpunkte.Zauber()) 
          { regnot ("Nicht genug Lernpunkte"); 
            tree_lernschema->unselect_all();
            return;
          }
        list_Zauber.push_back(MBE); 
        if(MBE->ZusatzEnum(Typ)) lernen_zusatz(MBE->ZusatzEnum(Typ),MBE);
        lernpunkte.addZauber(- MBE->Lernpunkte());
        break; }
    case MidgardBasicElement::FERTIGKEIT: 
      { 
        if( (cH_Fertigkeit(MBE)->LernArt()=="Fach" && 
             MBE->Lernpunkte() > lernpunkte.Fach()) ||
             (cH_Fertigkeit(MBE)->LernArt()=="Allg" && 
             MBE->Lernpunkte() > lernpunkte.Allgemein()) ||
             (cH_Fertigkeit(MBE)->LernArt()=="Unge" && 
             MBE->Lernpunkte() > lernpunkte.Unge()) ) 
          { regnot ("Nicht genug Lernpunkte"); 
            tree_lernschema->unselect_all();
            return;
          }
        // Das hat hier keinen Sinn, da der Erfolgswert bein Anzeigen des
        // Lernschemas nocheinmal nocheinmal gesetzt wird.
        // MBE->set_Erfolgswert(cH_Fertigkeit(MBE)->FErfolgswert(Werte)+cH_Fertigkeit(MBE)->AttributBonus(Werte));
        if(!SpracheSchrift(MBE)) 
          { if(MBE->Name()!="Landeskunde (Heimat)") // Das macht 'lernen_zusatz' automatisch
               list_Fertigkeit.push_back(MBE); 
          }
        else 
          { // Damit Sprachen und Schriften nicht doppelt angezeigt werden
            list_FertigkeitZusaetze.push_back(MBE->Name());
          }
        if(MBE->ZusatzEnum(Typ)) lernen_zusatz(MBE->ZusatzEnum(Typ),MBE);

        if(cH_Fertigkeit(MBE)->LernArt()=="Fach")
           lernpunkte.addFach(-MBE->Lernpunkte());
        else if(cH_Fertigkeit(MBE)->LernArt()=="Allg")
           lernpunkte.addAllgemein(- MBE->Lernpunkte());
        else if(cH_Fertigkeit(MBE)->LernArt()=="Unge")
           lernpunkte.addUnge(- MBE->Lernpunkte());
        break; }
    default : break;
   }
  show_lernschema();
  show_gelerntes();
}

void midgard_CG::show_gelerntes()
{
  modify_bool=true; // Zum Abspeichern
  zeige_lernpunkte();
  
  std::list<cH_MidgardBasicElement> FL;
  std::list<std::list<cH_MidgardBasicElement> > LL;
  LL.push_back(list_Fertigkeit_ang);
  LL.push_back(list_Fertigkeit);
  LL.push_back(list_Waffen);
  LL.push_back(list_Zauber);
  LL.push_back(list_Zauberwerk);
  LL.push_back(list_Kido);
  LL.push_back(list_WaffenGrund);
  LL.push_back(list_Waffen_besitz);
  LL.push_back(list_Sprache);
  LL.push_back(list_Schrift);
  LL.push_back(list_Beruf);
  LL.push_back(Werte.Sinne());

  for(std::list<std::list<cH_MidgardBasicElement> >::const_iterator i=LL.begin();i!=LL.end();++i)
    for (std::list<cH_MidgardBasicElement>::const_iterator j=i->begin();j!=i->end();++j)
      FL.push_back(*j);
  MidgardBasicElement::show_list_in_tree(FL,tree_gelerntes,this);
  tree_gelerntes->Expand_recursively();
}

void midgard_CG::show_lernschema()
{
  MidgardBasicElement::MBEE what;
  std::string fert;
  if(button_waffen->get_active())
    {  what=MidgardBasicElement::WAFFE;
       label_lernschma_titel->set_text("Waffen");
    }
  else if(button_zauber->get_active())
    {  what=MidgardBasicElement::ZAUBER;
       label_lernschma_titel->set_text("Zauber");
    }
  else 
    {  what=MidgardBasicElement::FERTIGKEIT;
       if(button_fachkenntnisse->get_active())
         {  fert="Fach";
            label_lernschma_titel->set_text("Fachkenntnisse");
         }
        else if(button_untyp_fertigkeiten->get_active())
         {  fert="Unge";
            label_lernschma_titel->set_text("Ungewöhnliche Fertigkeiten");
         }
        else 
         {  fert="Allg";
            label_lernschma_titel->set_text("Allgemeinwissen");
         }
   }

  std::list<cH_MidgardBasicElement> newlist;
  std::list<cH_MidgardBasicElement> LW;
  if(fert=="Unge" || fert=="Allg"/* || fert=="Fach"*/) // 'Fach' wg. Spezies
   {
    for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
     {
      cH_Fertigkeit f(*i);
      int lp=0;
      f->setLernArt(fert);
      if(fert=="Allg")
       {
         if     (Werte.Stadt_Land()=="Land"  ) lp=f->LernLand();
         else if(Werte.Stadt_Land()=="Stadt" ) lp=f->LernStadt();
         else {regnot("Stadt oder Land wählen"); return;}
         if(!togglebutton_teure_anzeigen->get_active() && lp>lernpunkte.Allgemein())
            continue;
       }
      else if(fert=="Unge") 
        {
          lp = f->LernUnge();
          if(!togglebutton_teure_anzeigen->get_active() && lp>lernpunkte.Unge())
            continue;
        }
      if(lp == 99  ) continue;

      if     (f->Name()=="Muttersprache"   && 30<Werte.In()&&Werte.In()<=60) f->set_Erfolgswert(14);
      else if(f->Name()=="Muttersprache"   && Werte.In()>60) f->set_Erfolgswert(18+f->AttributBonus(Werte));
      else if(f->Name()=="Gastlandsprache" && Werte.In()>30) f->set_Erfolgswert(12);
      else f->set_Erfolgswert(f->Anfangswert()+f->AttributBonus(Werte));
      f->set_Lernpunkte(lp);

      if(!region_check((*i)->Region())) continue;
      if(!f->Voraussetzungen(Werte)) continue;
      if ((*i)->ist_gelernt(list_Fertigkeit)) 
        {
         if (!togglebutton_gelernte_anzeigen->get_active()) continue;
         else (*i)->setGelernt(true); 
        }
      if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) (*i)->setGelernt(true); //continue ;
      if(Werte.Spezies()->istVerbotenSpielbegin(*i)) continue;
      newlist.push_back(*i);
     }
   }
  if(fert=="Fach") // Freiwillige Speziesfertigkeiten
   {
     std::list<cH_MidgardBasicElement> LW=Werte.Spezies()->getFreiwilligeFertigkeiten(Werte);
     for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
      {
       cH_Fertigkeit(*i)->setLernArt("Fach");
       bool gelernt=false;
       if ((*i)->ist_gelernt(list_Fertigkeit)) gelernt=true;
       if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) gelernt=true;
       newlist.push_back(*i);
     }
   }
  if(fert!="Unge" && fert!="Allg" )
    {
      if(what==MidgardBasicElement::WAFFE)
         LW=Database.lernschema.get_List("Waffenfertigkeiten",Typ,list_Waffen);
      if(what==MidgardBasicElement::ZAUBER)
         LW=Database.lernschema.get_List("Zauberkünste",Typ,list_Zauber);
      if(what==MidgardBasicElement::FERTIGKEIT)
         LW=Database.lernschema.get_List("Fachkenntnisse",Typ,list_Fertigkeit);
      for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
        {
          bool gelernt=false;
          if((*i)->What()==MidgardBasicElement::FERTIGKEIT) 
               cH_Fertigkeit(*i)->setLernArt("Fach");
          if(Werte.Spezies()->istVerbotenSpielbegin(*i)) continue;
          if(what==MidgardBasicElement::WAFFE)  
               if (!region_check(cH_Waffe(*i)->Region((*i)->Name()))) continue;
          else if (!region_check((*i)->Region())) continue;

          if((*i)->Lernpunkte() == 99  ) continue;

          std::vector<Lernschema::st_index> VI;
          if(what==MidgardBasicElement::WAFFE)  
           {
             if ((*i)->ist_gelernt(list_Waffen)) gelernt=true; 
             if (!cH_Waffe(*i)->SG_Voraussetzung(Werte)) continue ;
             VI=Lernschema::getIndex(Typ,"Waffenfertigkeiten",(*i)->Name());
            }
           else if(what==MidgardBasicElement::ZAUBER)
            {
             if ((*i)->ist_gelernt(list_Zauber) )  gelernt=true;
             if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) gelernt=true;
             VI=Lernschema::getIndex(Typ,"Zauberkünste",(*i)->Name());
            }
           else if(what==MidgardBasicElement::FERTIGKEIT)
            {
             if ((*i)->ist_gelernt(newlist)) continue ; // Speziesfertigkeiten 
             if (!cH_Fertigkeit(*i)->Voraussetzungen(Werte)) continue ;
             if(Werte.Spezies()->istVerbotenSpielbegin(*i)) continue;
//             if(Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name(),true)) continue;
             if ((*i)->ist_gelernt(list_Fertigkeit)) gelernt=true;
             if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) gelernt=true;
             VI=Lernschema::getIndex(Typ,"Fachkenntnisse",(*i)->Name());
             cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert0()+cH_Fertigkeit(*i)->AttributBonus(Werte));
             cH_Fertigkeit(*i)->setPflicht(Database.lernschema.get_Pflicht(VI));
           }
        (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(VI));

        bool zuteuer=false;
         if(what==MidgardBasicElement::WAFFE)  
          { if((*i)->Lernpunkte() > lernpunkte.Waffen() ) zuteuer=true;}
         else if(what==MidgardBasicElement::ZAUBER)
          { if((*i)->Lernpunkte() > lernpunkte.Zauber() ) zuteuer=true; }
         else if(what==MidgardBasicElement::FERTIGKEIT)
          { if((*i)->Lernpunkte() > lernpunkte.Fach() ) zuteuer=true; }

         if(zuteuer && !togglebutton_teure_anzeigen->get_active()) continue;
         if(gelernt && !togglebutton_gelernte_anzeigen->get_active()) continue;
         if(gelernt) (*i)->setGelernt(true); 

         newlist.push_back(*i);
        }
     }
  MidgardBasicElement::show_list_in_tree(newlist,tree_lernschema,this);
  setTitels_for_Lernschema(what,fert);
  tree_lernschema->Expand_recursively();
  scrolledwindow_beruf->hide();
  scrolledwindow_lernschema->show();
  scrolledwindow_ange_fert->hide();
}

void midgard_CG::setTitels_for_Lernschema(const MidgardBasicElement::MBEE& what,const std::string& fert)
{
 vector<std::string> vs;
 vs.push_back("LP");
 switch (what) {
   case MidgardBasicElement::WAFFE:
     {
       vs.push_back("Grundkenntnnis"); // PFLICHTg
       vs.push_back("Waffe");
       vs.push_back("Wert");  
       vs.push_back(""); // EIGENSCHAFTg
       vs.push_back("Voraussetzung");
       vs.push_back("Schwierigkeit");    
       break;
     }
   case MidgardBasicElement::FERTIGKEIT:
     {
       vs.push_back("Pflicht");
       vs.push_back("Fertigkeit");
       vs.push_back("Wert");  
       vs.push_back("L.E.");
       vs.push_back("Voraussetzung");
       vs.push_back("Kosten");    
       break;
     }
   case MidgardBasicElement::ZAUBER:
     {
       vs.push_back("");
       vs.push_back("Zauber");
       vs.push_back("AP"); // WERTg
       vs.push_back("");
       vs.push_back("");
       vs.push_back("Kosten");    
       break;
     }
   default: break;
   }
 vs.push_back("Art");
 vs.push_back("Gelernt");
 tree_lernschema->setTitles(vs);                                   

 switch (what) {
   case MidgardBasicElement::WAFFE:
     {
       tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::KOSTENg,true);
       break;
     }
   case MidgardBasicElement::FERTIGKEIT:
     {
       if(fert=="Fach") tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,true);
       else tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::KOSTENg,true);
       break;
     }
   case MidgardBasicElement::ZAUBER:
     {
       tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::KOSTENg,true);
       break;
     }
    default : break;
   }
}

bool midgard_CG::SpracheSchrift(const cH_MidgardBasicElement& MBE)
{
 bool launch=false;
 std::string fert=MBE->Name();

 if(fert=="Schreiben: Muttersprache(+12)" ||
         fert=="Schreiben: Muttersprache(+9)" ||        
         fert=="Schreiben: Muttersprache(+4)" ||
         fert=="Schreiben: Alte Sprache(+12)" ||
         fert=="Schreiben" )
    { launch=true;   }
 else if(fert=="Muttersprache")
    { launch=true; }
 else if(fert=="Gastlandsprache" ||
         fert=="Sprechen: Sprache(+4)" ||
         fert=="Sprechen: Sprache(+9)" ||
         fert=="Sprechen: Sprache(+12)")
    { launch=true;  }
 else if(fert=="Sprechen: Alte Sprache")
    { launch=true; }
 return launch;
}


void midgard_CG::on_togglebutton_gelernte_anzeigen_toggled()
{
  on_lernliste_wahl_toggled();
}
void midgard_CG::on_togglebutton_teure_anzeigen_toggled()
{
 on_lernliste_wahl_toggled();
}
