// $Id: midgard_CG_lernen.cc,v 1.125 2002/05/16 07:39:02 thoma Exp $
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
//#include "Window_waffe.hh"
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
  if(wizard) wizard->next_step(Wizard::LERNPUNKTE);
  //Speziesspezifische Fertigkeiten
  int lpspezies=0;
  list_Fertigkeit=Werte.Spezies()->getFertigkeiten(lpspezies,Werte);
  show_gelerntes();

  int fachlern=random.integer(1,6)+random.integer(1,6);
  if(!list_Fertigkeit.empty())
    set_status("Die Lernpunkte ("+itos(lpspezies)+") für die Pflichtfertigkeiten"
      " für die Spezies "+Werte.Spezies()->Name()+" wurden von den erfürfelten"
      " Lernpunkten ("+itos(fachlern)+") abgezogen.");
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
//  spinbutton_alter->set_value(Werte.Alter());
  zeige_lernpunkte();

  button_lernpunkte->set_sensitive(false);
  button_fachkenntnisse->set_sensitive(true);    
  button_allgemeinwissen->set_sensitive(true);   
  button_untyp_fertigkeiten->set_sensitive(true);
  button_waffen->set_sensitive(true);
  if(Typ[1]->is_mage() || Typ[1]->is_mage() ) //|| magie_bool) 
      button_zauber->set_sensitive(true);
  button_beruf->set_sensitive(true);
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
// spinbutton_beruf->set_sensitive(b);
 if(b) 
    table_berufsprozent->show();
 else 
    table_berufsprozent->hide();
// frame_berufswahl->set_sensitive(true);
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

gint midgard_CG::on_spinbutton_fach_focus_in_event(GdkEventFocus *ev)
{ spinbutton_fach->select_region(0,-1);   return false;}
gint midgard_CG::on_spinbutton_allgemein_focus_in_event(GdkEventFocus *ev)
{ spinbutton_allgemein->select_region(0,-1);   return false;}
gint midgard_CG::on_spinbutton_unge_focus_in_event(GdkEventFocus *ev)
{ spinbutton_unge->select_region(0,-1);   return false;}
gint midgard_CG::on_spinbutton_waffen_focus_in_event(GdkEventFocus *ev)
{ spinbutton_waffen->select_region(0,-1);   return false;}
gint midgard_CG::on_spinbutton_zaubern_focus_in_event(GdkEventFocus *ev)
{ spinbutton_zauber->select_region(0,-1);   return false;}


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

/*
 if(lernpunkte.Fach()==0 && lernpunkte.Allgemein()==0 &&
    lernpunkte.Unge()==0 && lernpunkte.Waffen()==0 &&
    lernpunkte.Zauber()==0 )
*/
// frame_berufswahl->set_sensitive(true);
}


gint midgard_CG::on_button_lernschema_geld_button_release_event(GdkEventButton *ev)
{
  if(wizard) wizard->next_step(Wizard::GELD);
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

 std::string strinfo ="Beim Auswürfeln von Geld wurden "
   +itos(V[0])+"  "+itos(V[1])+"  "+itos(V[2])+" gewürfelt ==> "
   +itos(igold)+" Gold";
 set_status(strinfo);
 Werte.addGold(igold);
 Geld_uebernehmen();
}


gint midgard_CG::on_button_ruestung_button_release_event(GdkEventButton *ev)
{
  if(wizard) wizard->next_step(Wizard::RUESTUNG);
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
  Werte.clearRuestung();
  Werte.addRuestung(cH_Ruestung(rue));
  set_status("Beim Auswürfeln der Rüstung wurde eine "+itos(wurf)+" gewürfelt "
             "==> " + Werte.Ruestung()->Long());
  zeige_werte();
}


void midgard_CG::on_lernliste_wahl_toggled()
{
  if(button_zauber->get_active())
   {
     if (Werte.Spezialgebiet()->Spezial2()=="" && Typ[0]->Short()=="eBe")
      {
         set_status("Erst Primär- und Sekundärelement wählen");
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
        set_status(MBE->What_str()+" kann nicht als Spezialwaffe verwendet werden.");
        return;         
      }
  switch(MBE->What()) {
     case MidgardBasicElement::WAFFE : 
         { 
           if(togglebutton_spezialwaffe->get_active() )
            { 
              if(cH_Waffe(MBE)->Verteidigung())
               set_status("Eine Verteidingungswaffe kann keine Spezialwaffe werden.");
             else
              {
               Werte.setSpezialisierung(MBE->Name());
               Waffe::setSpezialWaffe(Werte.Spezialisierung(),list_Waffen);
               togglebutton_spezialwaffe->set_active(false);
               if(wizard) wizard->next_step(Wizard::SPEZIALWAFFE);
              }
            }
           else
            {
              list_Waffen.remove(MBE);
              lernpunkte.addWaffen(MBE->Lernpunkte());
            }
           break;
         }
     case MidgardBasicElement::WAFFEBESITZ : 
         { list_Waffen_besitz.remove(MBE);
           std::string art=cH_WaffeBesitz(MBE)->Waffe()->Art2();
           if(art=="E" || art=="W" || art=="V") waffebesitzlernen.add_EWaffe(1);
           else waffebesitzlernen.add_AWaffe(1);
           break;
         }
     case MidgardBasicElement::ZAUBER : 
         { list_Zauber.remove(MBE);
           lernpunkte.addZauber(MBE->Lernpunkte());
           break;
         }
     case MidgardBasicElement::KIDO : 
         { list_Kido.remove(MBE);
           ++maxkido;
           fill_kido_lernschema();
           break;
         }
     case MidgardBasicElement::FERTIGKEIT_ANG : 
         { list_Fertigkeit_ang.remove(MBE);
           break;
         }
     case MidgardBasicElement::FERTIGKEIT : 
         { list_Fertigkeit.remove(MBE);
           list_FertigkeitZusaetze.remove(MBE->Name());
           if(cH_Fertigkeit(MBE)->LernArt()=="Fach")      lernpunkte.addFach( MBE->Lernpunkte());
           else if(cH_Fertigkeit(MBE)->LernArt()=="Allg") lernpunkte.addAllgemein( MBE->Lernpunkte());
           else if(cH_Fertigkeit(MBE)->LernArt()=="Unge") lernpunkte.addUnge( MBE->Lernpunkte());
           else set_info("Fehler beim Lernpunkte zurückstellen");
           std::string::size_type st = MBE->Name().find("KiDo-Technik");
           if(st!=std::string::npos)  --maxkido;
           break;
         }
     case MidgardBasicElement::SPRACHE : 
           list_Sprache.remove(MBE);
           // KEIN break 
     case MidgardBasicElement::SCHRIFT : 
           list_Schrift.remove(MBE);

           if(button_fachkenntnisse->get_active())
                lernpunkte.addFach(MBE->Lernpunkte());
           else if(button_allgemeinwissen->get_active())
                lernpunkte.addAllgemein(MBE->Lernpunkte());
           else if(button_untyp_fertigkeiten->get_active())
                lernpunkte.addUnge(MBE->Lernpunkte());
           else set_info("Da kein Fertigkeiten-Auswahl-Knopf gewählt wurde konnten die Lernpunkte ("
                  +itos(MBE->Lernpunkte())+") für das Verlernen dieser Sprache nicht gut geschrieben werden.");
           break;

     default : break;
   }
  if(MBE->What()==MidgardBasicElement::WAFFEBESITZ)
    show_WaffenBesitz_lernschema();
  else 
     show_lernschema();
  show_gelerntes();
  if(MBE->What()==MidgardBasicElement::WAFFE && togglebutton_spezialwaffe->get_active())
     undosave("Spezialwaffe "+MBE->Name()+" gewählt");
  else
     undosave(MBE->Name()+" verlernt");
}

void midgard_CG::on_tree_lernschema_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if(MBE->Gelernt()) 
   { 
     set_status("Diese Fertigkeit ist schon gelernt");
     tree_lernschema->unselect_all();
     return;
   }
  switch(MBE->What()) {
    case MidgardBasicElement::WAFFE: 
      { 
        if(MBE->Lernpunkte()>lernpunkte.Waffen()) 
          { set_status("Nicht genug Lernpunkte"); 
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
          { set_status("Nicht genug Lernpunkte"); 
            tree_lernschema->unselect_all();
            return;
          }
        if(!MBE->ZusatzEnum(Typ)) // Das macht 'lernen_zusatz' automatisch
            list_Zauber.push_back(MBE); 
        else lernen_zusatz(MBE->ZusatzEnum(Typ),MBE);
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
          { set_status("Nicht genug Lernpunkte"); 
            tree_lernschema->unselect_all();
            return;
          }
        if(!SpracheSchrift(MBE)) 
          { 
            std::string::size_type st = MBE->Name().find("KiDo-Technik");
            if(st!=std::string::npos) 
               { ++maxkido; list_FertigkeitZusaetze.push_back(MBE->Name());}
            if(!MBE->ZusatzEnum(Typ) && st==std::string::npos)// Das macht 'lernen_zusatz' automatisch
                  list_Fertigkeit.push_back(MBE); 
            if(MBE->Name()=="KiDo" && Typ[0]->Short()=="Kd") maxkido+=2;
            if(maxkido>0 && cH_Fertigkeit("KiDo")->ist_gelernt(list_Fertigkeit)) 
               show_gtk();
         }
        else 
          { // Damit Sprachen und Schriften nicht doppelt angezeigt werden
            // später: nach einhelliger Meinung sollen sie das doch 
//            list_FertigkeitZusaetze.push_back(MBE->Name());
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
  undosave(MBE->Name()+" gelernt");
  show_lernschema();
  show_gelerntes();
  if(frame_lernschema_zusatz->is_visible()) scrolledwindow_lernen->set_sensitive(false);
//  if(MBE->ZusatzEnum(Typ)) scrolledwindow_lernen->set_sensitive(false);
}

void midgard_CG::show_gelerntes()
{
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
  scrolledwindow_lernen->set_sensitive(true);
}

void midgard_CG::show_lernschema()
{
  if(button_kido_auswahl->get_active()) return;
  clean_lernschema_trees();
  tree_lernschema = manage(new MidgardBasicTree(MidgardBasicTree::LERNSCHEMA));
  tree_lernschema->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_tree_lernschema_leaf_selected));
  
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
  if(fert=="Unge" || fert=="Allg") 
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
         else {set_status("Stadt oder Land wählen"); return;}
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

      
      if(!(*i)->ist_gelernt(list_Fertigkeit))
        {
         if     (f->Name()=="Muttersprache"   && 30<Werte.In()&&Werte.In()<=60) f->setErfolgswert(14);
         else if(f->Name()=="Muttersprache"   && Werte.In()>60) f->setErfolgswert(18+f->AttributBonus(Werte));
         else if(f->Name()=="Gastlandsprache" && Werte.In()>30) f->setErfolgswert(12);
         else f->setErfolgswert(f->Anfangswert()+f->AttributBonus(Werte));
         f->setLernpunkte(lp);
        }
      if(!region_check((*i)->Region())) continue;
      if(!f->Voraussetzungen(Werte,list_Fertigkeit)) continue;
      // Fertigkeiten mit Zusätzen dürfen wiederholt gelernt werden, daher 'false'
      // statt 'true'
      if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) (*i)->setGelernt(false);
      else {(*i)->setGelernt(false);(*i)->setZusatz("");}
      if((*i)->Name()=="Landeskunde (Heimat)" && (*i)->ist_gelernt(list_FertigkeitZusaetze)) (*i)->setGelernt(true);
      if ((*i)->ist_gelernt(list_Fertigkeit)) (*i)->setGelernt(true); 
      if((*i)->Gelernt()&&!togglebutton_gelernte_anzeigen->get_active()) continue;
      if(Werte.Spezies()->istVerbotenSpielbegin(*i)) continue;
//if((*i)->Gelernt())
//cout << "Was ist gelernt? "<<(*i)->Name()<<' '
//<<(*i)->ist_gelernt(list_FertigkeitZusaetze)<<' '
//<<(*i)->ist_gelernt(list_Fertigkeit)<<'\n';
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
             if (!cH_Waffe(*i)->SG_Voraussetzung(Werte,list_Fertigkeit,list_Waffen)) continue ;
             VI=Lernschema::getIndex(Typ,"Waffenfertigkeiten",(*i)->Name());
            }
           else if(what==MidgardBasicElement::ZAUBER)
            {
             if ((*i)->ist_gelernt(list_Zauber) )  gelernt=true;
//             if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) gelernt=true;
             VI=Lernschema::getIndex(Typ,"Zauberkünste",(*i)->Name());
            }
           else if(what==MidgardBasicElement::FERTIGKEIT)
            {
             if ((*i)->ist_gelernt(newlist)) continue ; // Speziesfertigkeiten 
             if (!cH_Fertigkeit(*i)->Voraussetzungen(Werte,list_Fertigkeit)) continue ;
             if(Werte.Spezies()->istVerbotenSpielbegin(*i)) continue;
             if ((*i)->ist_gelernt(list_Fertigkeit)) gelernt=true;
             if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) gelernt=true;
             VI=Lernschema::getIndex(Typ,"Fachkenntnisse",(*i)->Name());
             cH_Fertigkeit(*i)->setErfolgswert(cH_Fertigkeit(*i)->Anfangswert0()+cH_Fertigkeit(*i)->AttributBonus(Werte));
             cH_Fertigkeit(*i)->setPflicht(Database.lernschema.get_Pflicht(VI));
           }
        (*i)->setLernpunkte(Database.lernschema.get_Lernpunkte(VI));

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
  tree_lernschema->show();
  viewport_lernen->add(*tree_lernschema);

  setTitels_for_Lernschema(what,fert);
  tree_lernschema->Expand_recursively();

  scrolledwindow_lernen->show();
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

void midgard_CG::clean_lernschema_trees()
{
  if(tree_lernschema) {tree_lernschema->destroy(); tree_lernschema=0;}
  if(Beruf_tree) {Beruf_tree->destroy(); Beruf_tree=0;}
  if(tree_angeb_fert) {tree_angeb_fert->destroy(); tree_angeb_fert=0;}
  if(tree_kido_lernschema) {tree_kido_lernschema->destroy(); tree_kido_lernschema=0;}
  if(tree_waffen_lernschema) {tree_waffen_lernschema->destroy(); tree_waffen_lernschema=0;}
  viewport_lernen->remove();
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
