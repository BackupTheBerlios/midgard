// $Id: midgard_CG_lernen.cc,v 1.75 2002/02/19 08:46:05 thoma Exp $
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
#include "Window_Waffe_Geld.hh"
#include <Aux/itos.h>
#include "class_SimpleTree.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
//#include "Zauber.hh"
#include "Fertigkeiten.hh"
#include "Sprache_auswahl.hh"

void midgard_CG::on_herkunftsland_clicked()
{
  cH_MidgardBasicElement Dummy=new Fertigkeit(*cH_Fertigkeit("",true));
  lernen_zusatz(MidgardBasicElement::ZHerkunft,Dummy);
}

void midgard_CG::on_lernpunkte_wuerfeln_clicked()
{
  lernpunkte.setFach(random.integer(1,6)+random.integer(1,6));
  lernpunkte.setAllgemein(random.integer(1,6)+1);
  lernpunkte.setUnge(random.integer(1,6));
  if (Typ[1]->Short()=="") lernpunkte.setWaffen(random.integer(1,6)+random.integer(1,6));
  else                  lernpunkte.setWaffen(random.integer(1,6)+1); // Doppelcharakter
  if (Typ[0]->Zaubern()=="j" || Typ[0]->Zaubern() == "z" && Typ[1]->Short()=="") 
      lernpunkte.setZauber(random.integer(1,6)+random.integer(1,6));
  if (Typ[1]->Zaubern()=="j" || Typ[1]->Zaubern() == "z" && Typ[1]->Short()!="") 
      lernpunkte.setZauber(random.integer(1,6)+1);

  int age = (lernpunkte.Allgemein() + lernpunkte.Unge() 
             + lernpunkte.Fach()
             + lernpunkte.Waffen() + lernpunkte.Zauber())/4+16;

//     if (Typ[0]->Zaubern()=="z" ) age = age/4+19;
//     if (Typ[0]->Zaubern()=="n" || Typ[0]->Zaubern()=="j") age = age/4+16;
  Werte.setAlter( age * Werte.Spezies()->Alter());
  spinbutton_alter->set_value(Werte.Alter());
  zeige_lernpunkte();
//  zeige_notebook();

  button_fachkenntnisse->set_sensitive(true);    
  button_allgemeinwissen->set_sensitive(true);   
  button_untyp_fertigkeiten->set_sensitive(true);
  button_waffen->set_sensitive(true);
  if(Typ[0]->Zaubern()=="j" || Typ[0]->Zaubern() == "z" || magie_bool) 
      button_zauber->set_sensitive(true);
  vbox_berufsname->set_sensitive(true);               
  button_geld_waffen->set_sensitive(true);
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
  zeige_werte(Werte);
}

void midgard_CG::zeige_lernpunkte()
{
 spinbutton_fach->set_value(lernpunkte.Fach());
 spinbutton_allgemein->set_value(lernpunkte.Allgemein());
 spinbutton_unge->set_value(lernpunkte.Unge());
 spinbutton_waffen->set_value(lernpunkte.Waffen());
 spinbutton_zauber->set_value(lernpunkte.Zauber());
  zeige_werte(Werte);
}

void midgard_CG::on_button_geld_waffen_clicked()
{   
  Werte.setGeld(0,0,0);
  steigern_aktivieren();
  manage(new Window_Waffe_Geld(this,Werte,Typ,Database,list_Waffen));
}

void midgard_CG::waffe_besitz_uebernehmen(const std::list<cH_MidgardBasicElement>& wbu)
{
 list_Waffen_besitz = wbu;
 steigern_aktivieren();
 show_gelerntes();
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
  zeige_werte(Werte);
}


void midgard_CG::on_lernliste_wahl_toggled()
{
  if(button_fachkenntnisse->get_active())
     show_lernschema(MidgardBasicElement::FERTIGKEIT,"Fach");
  if(button_allgemeinwissen->get_active())
      show_lernschema(MidgardBasicElement::FERTIGKEIT,"Allg");
  if(button_untyp_fertigkeiten->get_active())
      show_lernschema(MidgardBasicElement::FERTIGKEIT,"Unge");
  if(button_waffen->get_active())
      show_lernschema(MidgardBasicElement::WAFFE);
  if(button_zauber->get_active())
   {
     if (Werte.Spezialgebiet()->Spezial2()=="" && Typ[0]->Short()=="eBe")
      {
         std::string strinfo="Erst Primär- und Sekundärelement wählen\n";
         InfoFenster->AppendShow(strinfo);
         return;
      }
    show_lernschema(MidgardBasicElement::ZAUBER);
   }
}



void midgard_CG::on_tree_gelerntes_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if(togglebutton_spezialwaffe->get_active() && MBE->What()!= MidgardBasicElement::WAFFE)
      {togglebutton_spezialwaffe->set_active(false); return ; }
  switch(MBE->What()) {
     case MidgardBasicElement::WAFFE : 
         { 
           if(togglebutton_spezialwaffe->get_active())
            {
             Werte.setSpezialisierung(MBE->Name());
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

//     default : break;
   }
  if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
         show_lernschema(MBE->What(),cH_Fertigkeit(MBE)->LernArt());
  else if(MBE->What()==MidgardBasicElement::SPRACHE ||
          MBE->What()==MidgardBasicElement::SCHRIFT )
         on_lernliste_wahl_toggled();
  else   show_lernschema(MBE->What());
  show_gelerntes();
}

void midgard_CG::on_tree_lernschema_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  switch(MBE->What()) {
    case MidgardBasicElement::WAFFE: 
      { list_Waffen.push_back(MBE); 
        list_WaffenGrund.push_back(&*cH_WaffeGrund(cH_Waffe(MBE)->Grundkenntnis()));
        list_WaffenGrund.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
        list_WaffenGrund.unique();
        lernpunkte.addWaffen(- MBE->Lernpunkte());
        break; }
    case MidgardBasicElement::ZAUBER: 
      { list_Zauber.push_back(MBE); 
        if(MBE->ZusatzEnum(Typ)) lernen_zusatz(MBE->ZusatzEnum(Typ),MBE);
        lernpunkte.addZauber(- MBE->Lernpunkte());
        break; }
    case MidgardBasicElement::FERTIGKEIT: 
      { 
        // Das hat hier keinen Sinn, da der Erfolgswert bein Anzeigen des
        // Lernschemas nocheinmal nocheinmal gesetzt wird.
        // MBE->set_Erfolgswert(cH_Fertigkeit(MBE)->FErfolgswert(Werte)+cH_Fertigkeit(MBE)->AttributBonus(Werte));
        if(!SpracheSchrift(MBE)) 
          { if(MBE->Name!="Landeskunde (Heimat)") // Das macht 'lernen_zusatz' automatisch
               list_Fertigkeit.push_back(MBE); 
          }
        else SpracheSchrift(MBE,MBE->Erfolgswert(),true);

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
#warning Aus irgendwelchen Gründen setzet 'show_lernschema' den Erfolgswert 
#warning NICHT auf den richtigen Wert, obwohl der dann eigentlich korrekt
#warning angezeigt wird. Daher dieser HAck mit dem Erfolgswert.
   int e=MBE->Erfolgswert();
//cout <<"1 " <<MBE->Name()<<'a '<<MBE->Erfolgswert()<<'\n';
  if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
         show_lernschema(MBE->What(),cH_Fertigkeit(MBE)->LernArt());
  else   show_lernschema(MBE->What());
//cout <<"2 " << MBE->Name()<<' '<<MBE->Erfolgswert()<<'\n';
  MBE->set_Erfolgswert(e);
  show_gelerntes();
}

void midgard_CG::show_gelerntes()
{
  modify_bool=true; // Zum Abspeichern
  show_sinne();
  zeige_lernpunkte();
  
  std::list<cH_MidgardBasicElement> FL;
  std::list<std::list<cH_MidgardBasicElement> > LL;
  LL.push_back(list_Fertigkeit_ang);
  LL.push_back(list_Fertigkeit);
  Waffe::setSpezialWaffe(Werte.Spezialisierung(),list_Waffen);
  LL.push_back(list_Waffen);
  LL.push_back(list_Zauber);
  LL.push_back(list_Zauberwerk);
  LL.push_back(list_Kido);
  LL.push_back(list_WaffenGrund);
  LL.push_back(list_Waffen_besitz);
  LL.push_back(list_Sprache);
  LL.push_back(list_Schrift);
  LL.push_back(list_Beruf);

  for(std::list<std::list<cH_MidgardBasicElement> >::const_iterator i=LL.begin();i!=LL.end();++i)
    for (std::list<cH_MidgardBasicElement>::const_iterator j=i->begin();j!=i->end();++j)
      FL.push_back(*j);
  MidgardBasicElement::show_list_in_tree(FL,tree_gelerntes,Werte,Typ,Database.ausnahmen);
  tree_gelerntes->Expand_recursively();
}

void midgard_CG::show_lernschema(const MidgardBasicElement::MBEE& what,const std::string& fert)
{
  if(what==MidgardBasicElement::WAFFE) label_lernschma_titel->set_text("Waffen");
  if(what==MidgardBasicElement::ZAUBER) label_lernschma_titel->set_text("Zauber");
  if(what==MidgardBasicElement::FERTIGKEIT)
   {
     if(fert=="Allg") label_lernschma_titel->set_text("Allgemeinwissen");
     if(fert=="Unge") label_lernschma_titel->set_text("Ungewöhnliche Fertigkeiten");
     if(fert=="Fach") label_lernschma_titel->set_text("Fachkenntnisse");
   }

  std::list<cH_MidgardBasicElement> newlist;
  std::list<cH_MidgardBasicElement> LW;
  if(fert=="Unge" || fert=="Allg" || fert=="Fach") // 'Fach' wg. Spezies
   {
    for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
     {
      cH_Fertigkeit f(*i);
      f->setLernArt(fert);
      if(fert=="Allg")
       {
         int lp=0;
         if     (Werte.Stadt_Land()=="Land"  ) lp=f->LernLand();
         else if(Werte.Stadt_Land()=="Stadt" ) lp=f->LernStadt();
         else {regnot("Stadt oder Land wählen"); return;}
         if(lp > lernpunkte.Allgemein() ) continue;
       }
      else if(fert=="Unge")
       {
         if(f->LernUnge() > lernpunkte.Unge() ) continue;
       }

      if(fert=="Unge")  
         { f->set_Lernpunkte(f->LernUnge());
           f->set_Erfolgswert(f->Anfangswert()+f->AttributBonus(Werte));
         }
      else if(fert=="Allg" && Werte.Stadt_Land()=="Land" ) 
         { f->set_Lernpunkte(f->LernLand());
           f->set_Erfolgswert(f->Anfangswert()+f->AttributBonus(Werte));
           if(f->Name()=="Muttersprache" && Werte.In()>30) f->set_Erfolgswert(14);
           if(f->Name()=="Muttersprache" && Werte.In()>60) f->set_Erfolgswert(18+f->AttributBonus(Werte));
           if(f->Name()=="Gastlandsprache" && Werte.In()>30) f->set_Erfolgswert(12);
         }
      else if(fert=="Allg" && Werte.Stadt_Land()=="Stadt" ) 
         { f->set_Lernpunkte(f->LernStadt());
           f->set_Erfolgswert(f->Anfangswert()+f->AttributBonus(Werte));
           if(f->Name()=="Muttersprache" && Werte.In()>30) f->set_Erfolgswert(14);
           if(f->Name()=="Muttersprache" && Werte.In()>60) f->set_Erfolgswert(18+f->AttributBonus(Werte));
           if(f->Name()=="Gastlandsprache" && Werte.In()>30) f->set_Erfolgswert(12);
         }
      else if(fert=="Fach") 
        {
         int lp=Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::LERNPUNKTE);
         if(!lp) continue;
         f->set_Lernpunkte(lp);
         int erf=Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::ERFOLGSWERT);
         f->set_Erfolgswert(erf+f->AttributBonus(Werte));
        }
      if(!region_check((*i)->Region())) continue;
      if(!f->Voraussetzungen(Werte)) continue;
      if ((*i)->ist_gelernt(list_Fertigkeit)) continue ;
      if(Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
      newlist.push_back(*i);
     }
   }
  if(fert!="Unge" && fert!="Allg" )
    {
      if(what==MidgardBasicElement::WAFFE)
         LW=Database.lernschema.get_List("Waffenfertigkeiten",Typ);
      if(what==MidgardBasicElement::ZAUBER)
         LW=Database.lernschema.get_List("Zauberkünste",Typ);
      if(what==MidgardBasicElement::FERTIGKEIT)
         LW=Database.lernschema.get_List("Fachkenntnisse",Typ);
      for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
        {
          if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
          if(what==MidgardBasicElement::WAFFE)  
               if (!region_check(cH_Waffe(*i)->Region((*i)->Name()))) continue;
          else if (!region_check((*i)->Region())) continue;

          Lernschema::st_index I;
          if(what==MidgardBasicElement::WAFFE)  
           {
             if((*i)->Lernpunkte()>lernpunkte.Waffen()) continue;
             if ((*i)->ist_gelernt(list_Waffen)) continue ;
             if (!cH_Waffe(*i)->SG_Voraussetzung(Werte)) continue ;
             I= Lernschema::st_index(Typ[0]->Short(),"Waffenfertigkeiten",(*i)->Name());
//cout << "Spezial "<<Werte.Spezialisierung()<<' '<<(*i)->Name()
//<<' '<<(*i)->Erfolgswert()<<'\t';
//             if(Werte.Spezialisierung()==(*i)->Name()) 
//                  (*i)->add_Erfolgswert(2);
//cout <<' '<<(*i)->Erfolgswert()<<'\n';
           }
          else if(what==MidgardBasicElement::ZAUBER)
           {
             if((*i)->Lernpunkte()>lernpunkte.Zauber()) continue;
             if ((*i)->ist_gelernt(list_Zauber)) continue ;
             if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) continue ;
             I=Lernschema::st_index(Typ[0]->Short(),"Zauberkünste",(*i)->Name());
           }
          else if(what==MidgardBasicElement::FERTIGKEIT)
           {
             if((*i)->Lernpunkte()>lernpunkte.Fach()) continue;
             if ((*i)->ist_gelernt(list_Fertigkeit)) continue ;
             if ((*i)->ist_gelernt(list_FertigkeitZusaetze)) continue ;
             if (!cH_Fertigkeit(*i)->Voraussetzungen(Werte)) continue ;
             if(Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name(),true)) continue;
             I=Lernschema::st_index(Typ[0]->Short(),"Fachkenntnisse",(*i)->Name());
             cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert0()+cH_Fertigkeit(*i)->AttributBonus(Werte));
             cH_Fertigkeit(*i)->setPflicht(Database.lernschema.get_Pflicht(I));
           }
          (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I));
          newlist.push_back(*i);
        }
     }
  MidgardBasicElement::show_list_in_tree(newlist,tree_lernschema,Werte,Typ,Database.ausnahmen);
  setTitels_for_Lernschema(what,fert);
  tree_lernschema->Expand_recursively();
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
 tree_lernschema->setTitles(vs);                                   

 switch (what) {
   case MidgardBasicElement::WAFFE:
     {
       tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,true);
       break;
     }
   case MidgardBasicElement::FERTIGKEIT:
     {
       if(fert=="Fach") tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,true);
       else tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,true);
       break;
     }
   case MidgardBasicElement::ZAUBER:
     {
       tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,false);
       break;
     }
    default : break;
   }
}

bool midgard_CG::SpracheSchrift(const cH_MidgardBasicElement& MBE,int wert,bool auswahl)
{
 bool launch=false;
 Sprache_auswahl::modus mod;
 std::string fert=MBE->Name();

// if      (fert=="Geheimzeichen") 
//    { launch=true;  mod=Sprache_auswahl::GEHEIMZEICHEN; }
// if (fert=="Abrichten") 
//    { launch=true;  mod=Sprache_auswahl::ABRICHTEN; }
// else if (fert=="Tiersprache") 
//    { launch=true;  mod=Sprache_auswahl::TIERSPRACHE; }
// else if (fert=="Musizieren") 
//    { launch=true;  mod=Sprache_auswahl::MUSIZIEREN; }
// if (fert=="Scharfschießen") 
//    { launch=true;  mod=Sprache_auswahl::SCHARFSCHIESSEN; }
// else if (fert=="Landeskunde") 
//    { launch=true;  mod=Sprache_auswahl::LAND; }
// else if (fert=="Landeskunde (Heimat)")
//    { launch=true;  mod=Sprache_auswahl::HEIMATLAND; }
 if(fert=="Schreiben: Muttersprache(+12)" ||
         fert=="Schreiben: Muttersprache(+9)" ||        
         fert=="Schreiben: Muttersprache(+4)" ||
         fert=="Schreiben: Alte Sprache(+12)" ||
         fert=="Schreiben" )
    { launch=true;  mod=Sprache_auswahl::SCHRIFT; }
 else if(fert=="Muttersprache")
    { launch=true;  mod=Sprache_auswahl::MUTTERSPRACHE; }
 else if(fert=="Gastlandsprache" ||
         fert=="Sprechen: Sprache(+4)" ||
         fert=="Sprechen: Sprache(+9)" ||
         fert=="Sprechen: Sprache(+12)")
    { launch=true;  mod=Sprache_auswahl::NEUESPRACHE; }
 else if(fert=="Sprechen: Alte Sprache")
    { launch=true;  mod=Sprache_auswahl::ALTESPRACHE; }

 // Als Fertigkeiten darf man auch eine alte Sprache wählen, 
 // wenn Sprache gewählt ist:
 if(mod==Sprache_auswahl::NEUESPRACHE) mod=Sprache_auswahl::SPRACHE;
   
 if(auswahl && launch)
     manage (new Sprache_auswahl(this,Database,Werte,MBE,mod,wert,
                                 list_Waffen,
                                 list_Sprache,list_Schrift,list_Fertigkeit));
 return launch;
}

