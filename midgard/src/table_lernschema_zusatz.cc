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
#include "LernListen.hh"
#include <typeinfo> // for bad_cast
static SigC::Connection connection;
#include <libmagus/Ausgabe.hh>
#include <gdk/gdk.h>

// der R�ckgabewert ist f�r das idle signal (immer false)
bool table_lernschema::lernen_zusatz(MidgardBasicElement::eZusatz was,MBEmlt MBE)
{
  checkbutton_einschraenkungen_zusatz->set_active(false);
  // Weil Fertigkeiten mehrmals gelernt werden dürfen werde sie hier nicht 
  // in die Liste geschrieben.
  // eine Ausnamhe ist 'Landeskunde (Heimat)', das passiert unten
// list_FertigkeitZusaetze.push_back((*MBE)->Name());
  if(MBE->Lernpunkte()==0 &&  // Sprache/Schrift für '0' Lernpunkte nur einmal lernen
     !((*MBE)->Name()=="Muttersprache") && !((*MBE)->Name()=="Gastlandsprache"))
    list_FertigkeitZusaetze.push_back((*MBE)->Name());
  if((*MBE)->Name()=="Schreiben: Muttersprache(+4)" ||
     (*MBE)->Name()=="Schreiben: Muttersprache(+9)" ||
     (*MBE)->Name()=="Schreiben: Muttersprache(+12)") 
    {
      list_FertigkeitZusaetze.push_back("Schreiben: Muttersprache(+4)");
      list_FertigkeitZusaetze.push_back("Schreiben: Muttersprache(+9)");
      list_FertigkeitZusaetze.push_back("Schreiben: Muttersprache(+12)");
      MBE->setLernArt(MBE->LernArt()+"_Schreiben_Muttersprache");
    }
  lernen_zusatz_titel(was,MBE);
  datavec_zusatz.clear();
  connection.disconnect();

  switch(was)
   {
     case MidgardBasicElement::ZHerkunft:
      {
       std::vector<std::pair<cH_Land,bool> > L=LernListen::getHerkunft(hauptfenster->getAben());
       for(std::vector<std::pair<cH_Land,bool> >::const_iterator i=L.begin();i!=L.end();++i)
          datavec_zusatz.push_back(new Data_Herkunft(i->first,i->second,MBE));
       connection = Tree_Lernschema_Zusatz->signal_leaf_selected()
       	.connect(SigC::slot(*this, &table_lernschema::on_herkunft_leaf_selected));
       scrolledwindow_lernen->hide();
       break;
      }
     case MidgardBasicElement::ZUeberleben:
      {
       std::vector<MidgardBasicElement::st_zusatz> V=LernListen::getUeberlebenZusatz();
       for(std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=V.begin();i!=V.end();++i)
          datavec_zusatz.push_back(new Data_Zusatz(hauptfenster->getAben().Ueberleben(),*i));
       connection = Tree_Lernschema_Zusatz->signal_leaf_selected().connect(SigC::slot(*this, &table_lernschema::on_herkunft_ueberleben_leaf_selected));
       scrolledwindow_lernen->hide();
       break;
      }
     case MidgardBasicElement::ZLand:
      {
       if((*MBE)->Name()=="Landeskunde (Heimat)")
         {
           list_FertigkeitZusaetze.push_back((*MBE)->Name());
           cH_MidgardBasicElement MBE_=&*cH_Fertigkeit("Landeskunde");
           MBEmlt M(&*MBE_);
           M->setLernArt(MBE->LernArt()+"_Heimat");
           M->setZusatz(hauptfenster->getAben().Herkunft()->Name());
           M->setErfolgswert(MBE->Erfolgswert());
           M->setLernpunkte(MBE->Lernpunkte());
           hauptfenster->getAben().List_Fertigkeit().push_back(M);
           return false;
         }
       else
         {
           std::vector<MidgardBasicElement::st_zusatz> V=LernListen::getLandZusatz();
           for(std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=V.begin();i!=V.end();++i)
              datavec_zusatz.push_back(new Data_Zusatz(MBE,*i));
         }
       connection = Tree_Lernschema_Zusatz->signal_leaf_selected().connect(SigC::slot(*this, &table_lernschema::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZSprache:
      {
// Das passiert schon oben bei '0' Lernpunkten
       if((*MBE)->Name()=="Muttersprache" || (*MBE)->Name()=="Gastlandsprache" || (*MBE)->Name()=="Sprechen: Alte Sprache") 
        {  
           MBE->setLernArt((*MBE)->Name());
           list_FertigkeitZusaetze.push_back(MBE->LernArt());
        }
       std::vector<MidgardBasicElement::st_zusatz>  V=LernListen
            ::getSprachenZusatz(MBE,hauptfenster->getAben(),button_allgemeinwissen->get_active());
       for(std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=V.begin();i!=V.end();++i)
          datavec_zusatz.push_back(new Data_Zusatz(MBE,*i));
       connection = Tree_Lernschema_Zusatz->signal_leaf_selected().connect(SigC::slot(*this, &table_lernschema::on_zusatz_leaf_sprache_selected));
       break;
      }
     case MidgardBasicElement::ZSchrift:
      {
       std::vector<MidgardBasicElement::st_zusatz> V=LernListen::getSchriftenZusatz(MBE,hauptfenster->getAben());
       for(std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=V.begin();i!=V.end();++i)
          datavec_zusatz.push_back(new Data_Zusatz(MBE,*i));
       if(datavec_zusatz.empty()) 
         { Ausgabe(Ausgabe::Error,"Keine Schrift lernbar (entweder keine Sprache gelernt oder es werden alle lernbaren Schriften schon beherrscht.)");
           list_FertigkeitZusaetze.remove((*MBE)->Name());
           if(MBE->LernArt()=="Fach")      vabenteurer->getLernpunkte().getLernpunkte().addFach( MBE->Lernpunkte());
           else if(MBE->LernArt()=="Allg") vabenteurer->getLernpunkte().getLernpunkte().addAllgemein( MBE->Lernpunkte());
           else if(MBE->LernArt()=="Unge") vabenteurer->getLernpunkte().getLernpunkte().addUnge( MBE->Lernpunkte());
           else if(MBE->LernArt()=="Allg_Schreiben_Muttersprache")
             { vabenteurer->getLernpunkte().getLernpunkte().addAllgemein( MBE->Lernpunkte());
               list_FertigkeitZusaetze.remove("Schreiben: Muttersprache(+4)");
               list_FertigkeitZusaetze.remove("Schreiben: Muttersprache(+9)");
               list_FertigkeitZusaetze.remove("Schreiben: Muttersprache(+12)");
             }
           else Ausgabe(Ausgabe::Error,"Fehler beim Lernpunkte zurückstellen");
           return false;}
       connection = Tree_Lernschema_Zusatz->signal_leaf_selected().connect(SigC::slot(*this, &table_lernschema::on_zusatz_leaf_schrift_selected));
       break;
      }
     case MidgardBasicElement::ZWaffe:
      {
       std::vector<MidgardBasicElement::st_zusatz> V=LernListen::getWaffenZusatz(hauptfenster->getAben().List_Waffen());
       for(std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=V.begin();i!=V.end();++i)
           datavec_zusatz.push_back(new Data_Zusatz(MBE,*i));
       if(datavec_zusatz.empty()) 
         { Ausgabe(Ausgabe::Error,"Noch keine Fernkampfwaffe gewählt.");
           hauptfenster->getAben().List_Fertigkeit().remove(MBE);
           list_FertigkeitZusaetze.remove((*MBE)->Name());
           if(MBE->LernArt()=="Fach")      vabenteurer->getLernpunkte().getLernpunkte().addFach( MBE->Lernpunkte());
           else if(MBE->LernArt()=="Allg") vabenteurer->getLernpunkte().getLernpunkte().addAllgemein( MBE->Lernpunkte());
           else if(MBE->LernArt()=="Unge") vabenteurer->getLernpunkte().getLernpunkte().addUnge( MBE->Lernpunkte());
           else Ausgabe(Ausgabe::Error,"Fehler beim Lernpunkte zurückstellen");
           return false;}
       connection = Tree_Lernschema_Zusatz->signal_leaf_selected().connect(SigC::slot(*this, &table_lernschema::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZTabelle:
      {
       std::vector<MidgardBasicElement::st_zusatz> VG=LernListen::getMBEZusatz(hauptfenster->getAben(),MBE);
       for (std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=VG.begin();i!=VG.end();++i)
          datavec_zusatz.push_back(new Data_Zusatz(MBE,*i));
       connection = Tree_Lernschema_Zusatz->signal_leaf_selected().connect(SigC::slot(*static_cast<class table_lernschema*>(this), &table_lernschema::on_zusatz_leaf_selected));
       break;
      }
     case MidgardBasicElement::ZNone : break;
   }
 show_datavec_zusatz();
 set_zusatz_sensitive(true);
 list_FertigkeitZusaetze.sort();
 list_FertigkeitZusaetze.unique();

// Tree_Lernschema_Zusatz->grab_focus();
/*
 Gdk_Window W_to=frame_lernschema_zusatz->get_window();
 GdkEventMask eventmask = gdk_window_get_events(W_to);
 GdkCursor *cursor=0;
 GdkWindow *Wto(Gdk_Window);
 gdk_pointer_grab(Wto,0,eventmask,Wto,cursor,0);
*/
// fra->pointer_grab();
  return false;
}


void table_lernschema::show_datavec_zusatz()
{
  std::vector<cH_RowDataBase> datavec;
  for(std::vector<cH_RowDataBase>::const_iterator i=datavec_zusatz.begin();i!=datavec_zusatz.end();++i)
   {
        Handle<const Data_Zusatz> dt=i->cast_dynamic<const Data_Zusatz>();
        if(!!dt) 
        {  if(checkbutton_einschraenkungen_zusatz->get_active() 
        	|| dt->Erlaubt())
              datavec.push_back(*i);
        }
        else
        {  Handle<const Data_Herkunft>dt2=i->cast_dynamic<const Data_Herkunft>();
           if(checkbutton_einschraenkungen_zusatz->get_active() 
           	|| dt2->Erlaubt())
              datavec.push_back(*i);
        }
   }
  Tree_Lernschema_Zusatz->setDataVec(datavec);
}


void table_lernschema::lernen_zusatz_titel(MidgardBasicElement::eZusatz was,const MBEmlt& MBE)
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
     case MidgardBasicElement::ZUeberleben :
      {
       frame_lernschema_zusatz->set_label("In welcher Gegend beherrscht dieser Abenteurer 'Überleben' als Universelle Fertigkeit");
       vs.push_back((*MBE)->Name());
       vs.push_back("");
       vs.push_back("");
       break;
      }
     case MidgardBasicElement::ZWaffe :
      {
       frame_lernschema_zusatz->set_label("Fernkampfwaffe auswählen");
       vs.push_back((*MBE)->Name());
       vs.push_back("");
       vs.push_back("");
       break;
      }
     case MidgardBasicElement::ZTabelle :
      {
       frame_lernschema_zusatz->set_label("Zusatz auswählen");
       vs.push_back((*MBE)->Name());
       vs.push_back("");
       vs.push_back("Region");
       break;
      }
     case MidgardBasicElement::ZSchrift :
      {
       frame_lernschema_zusatz->set_label("Schrift auswählen");
       vs.push_back((*MBE)->Name());
       vs.push_back("");
       vs.push_back("");
       break;
      }
     case MidgardBasicElement::ZSprache :
      {
       if((*MBE)->Name()=="Muttersprache")
        {
          std::vector<std::string> V=hauptfenster->getAben().Herkunft()->Sprachen();
          std::vector<std::string> W;
          for(std::vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
            if(!cH_Sprache(*i)->Alte_Sprache()) W.push_back(*i) ;
          std::string s,label;
          for(std::vector<std::string>::const_iterator i=W.begin();i!=W.end();)
              { s+=*i; if(++i!=W.end()) s+=", ";}
          if(W.size()==1)  label ="Muttersprache ("+s+") wählen" ;
          else label = "Eine Muttersprache wählen\n("+s+")" ;
          frame_lernschema_zusatz->set_label(label);
        }
       else frame_lernschema_zusatz->set_label("Sprache auswählen");
       vs.push_back((*MBE)->Name());
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
  Handle<const Data_Herkunft> dt=d.cast_dynamic<const Data_Herkunft>();
  hauptfenster->getChar().getWizard().done(Wizard::HERKUNFT,hauptfenster->getAben());
  hauptfenster->getAben().setHerkunft(dt->getLand());
  // Region anschalten
  if (!dt->getLand()->Region().empty())
      hauptfenster->getAben().getRegion(cH_Region::getRegionfromAbk(dt->getLand()->Region()))=true;
  set_zusatz_sensitive(false);
  zeige_werte();  
  if(!hauptfenster->getAben().getOptionen().OptionenCheck(Optionen::NSC_only).active)
     button_herkunft->set_sensitive(false);
  MBEmlt M(cH_Fertigkeit("Muttersprache"));
  Sprache::setErfolgswertMuttersprache(M,hauptfenster->getAben().In(),
           cH_Fertigkeit(M->getMBE())->AttributBonus(hauptfenster->getAben()));
  Glib::signal_idle().connect(SigC::bind(
  	SigC::slot(*this,&table_lernschema::lernen_zusatz),MidgardBasicElement::ZSprache,M));
//#error lernen_zusatz in idle connectieren!
//  lernen_zusatz(MidgardBasicElement::ZSprache,M);
}

void table_lernschema::on_herkunft_ueberleben_leaf_selected(cH_RowDataBase d)
{
  hauptfenster->getChar().getWizard().done(Wizard::UEBERLEBEN,hauptfenster->getAben());
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);

  MBEmlt M(&*cH_Fertigkeit(dt->getZusatz().name));
  hauptfenster->getAben().setUeberleben(M);

  button_angeborene_fert->set_sensitive(true);
  set_zusatz_sensitive(false);
  zeige_werte();  
  show_gelerntes();
}

void table_lernschema::on_zusatz_leaf_selected(cH_RowDataBase d)
{
  if(tree_lernschema)
     tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);
  MBEmlt MBE=dt->getMBE();

  MBE->setZusatz(dt->getZusatz());
  if((*MBE).What()==MidgardBasicElement::FERTIGKEIT)
   {
     if(hauptfenster->getAben().Herkunft()->Name()==MBE->Zusatz())
      {
        MBE->setErfolgswert(10+cH_Fertigkeit(MBE->getMBE())->AttributBonus(hauptfenster->getAben())); 
      }
     hauptfenster->getAben().List_Fertigkeit().push_back(MBE);
   }
  else if((*MBE).What()==MidgardBasicElement::ZAUBER)
     hauptfenster->getAben().List_Zauber().push_back(MBE);

  set_zusatz_sensitive(false);
  zeige_werte();  
  show_gelerntes();
}

void table_lernschema::on_zusatz_leaf_schrift_selected(cH_RowDataBase d)
{
  if(tree_lernschema) tree_lernschema->set_sensitive(true);
  const Data_Zusatz *dt=dynamic_cast<const Data_Zusatz*>(&*d);

  MBEmlt schrift(&*cH_Schrift(dt->getZusatz().name));
  schrift->setErfolgswert(dt->getMBE()->Erfolgswert());
  schrift->setLernpunkte(dt->getMBE()->Lernpunkte());
  schrift->setLernArt(dt->getMBE()->LernArt());

  hauptfenster->getAben().List_Schrift().push_back(schrift);
  set_zusatz_sensitive(false);
  zeige_werte();  
  show_gelerntes();
}

void table_lernschema::on_zusatz_leaf_sprache_selected(cH_RowDataBase d)
{
  if(tree_lernschema) tree_lernschema->set_sensitive(true);
  Handle<const Data_Zusatz> dt=d.cast_dynamic<const Data_Zusatz>();
  if (!dt) { Ausgabe(Ausgabe::Error,"on_zusatz_leaf_sprache_selected: kein Data_Zusatz"); return; }

  MBEmlt sprache(cH_Sprache(dt->getZusatz().name));
  sprache->setErfolgswert(dt->getMBE()->Erfolgswert());
  sprache->setLernpunkte(dt->getMBE()->Lernpunkte());
  sprache->setLernArt(dt->getMBE()->LernArt());

  hauptfenster->getAben().List_Sprache().push_back(sprache);
  set_zusatz_sensitive(false);
  zeige_werte();  
  show_gelerntes();
  if((*dt->getMBE())->Name()=="Muttersprache")
   {
//#error in idle selectieren     
//     lernen_zusatz(MidgardBasicElement::ZUeberleben,dummy);
     hauptfenster->getAben().setMuttersprache((*sprache)->Name());
     
     MBEmlt dummy=hauptfenster->getAben().Ueberleben();
     Glib::signal_idle().connect(SigC::bind(
  	SigC::slot(*this,&table_lernschema::lernen_zusatz),
  		MidgardBasicElement::ZUeberleben,dummy));
   }
}

bool table_lernschema::on_eventbox_zusatz_leave_notify_event(GdkEventCrossing *ev)
{
  Ausgabe(Ausgabe::Debug,"leave out");
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
