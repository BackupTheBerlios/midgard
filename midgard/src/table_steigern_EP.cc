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

#include "midgard_CG.hh"
#include "table_steigern.hh"
//#include "Window_Erfahrungspunkte.hh"
#include <gtk--/adjustment.h>
#include <Misc/itos.h>

gint table_steigern::vscale_value_changed(GdkEventButton *ev)
{
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  int Av=(int)A->get_value();
  hauptfenster->getWerte().set_Steigern_EP_Prozent(100-Av);
  steigern_gtk();
  return false;
}

void table_steigern::steigern_gtk()
{
  label_EP->set_text(itos(hauptfenster->getWerte().get_Steigern_EP_Prozent())+"%");
  label_Gold->set_text(itos(100-hauptfenster->getWerte().get_Steigern_EP_Prozent())+"%");
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  A->set_value(100-hauptfenster->getWerte().get_Steigern_EP_Prozent());
  if (steigern_mit_EP_bool) checkbutton_EP_Geld->set_active(true);
  else                      checkbutton_EP_Geld->set_active(false);
}

void table_steigern::on_checkbutton_EP_Geld_toggled()
{
   if (checkbutton_EP_Geld->get_active()) 
      { steigern_mit_EP_bool=true;
      }
   else 
      { steigern_mit_EP_bool=false;
      }
}

void table_steigern::on_button_EP_toggled()
{
 show_EPeingabe(button_EP->get_active());  
 spinbutton_aep->grab_focus();
}

void table_steigern::show_EPeingabe(bool b)
{
  if(b)
   {
     spinbutton_aep->set_value(hauptfenster->getWerte().AEP());
     spinbutton_kep->set_value(hauptfenster->getWerte().KEP());
     spinbutton_zep->set_value(hauptfenster->getWerte().ZEP());
     spinbutton_aep->show();
     spinbutton_kep->show();
     spinbutton_zep->show();
     label_aep->hide();
     label_kep->hide();
     label_zep->hide();
   }
  else
   {
     spinbutton_aep->hide();
     spinbutton_kep->hide();
     spinbutton_zep->hide();
     label_aep->set_text(itos(hauptfenster->getWerte().AEP()));
     label_kep->set_text(itos(hauptfenster->getWerte().KEP()));
     label_zep->set_text(itos(hauptfenster->getWerte().ZEP()));
     label_aep->show();
     label_kep->show();
     label_zep->show();
   }
}


 

void table_steigern::desteigern(unsigned int kosten)
{
  int gold_k=0,ep_k=0;
  if(radiobutton_praxis->get_active())
   {
     ep_k = kosten ;
   }
  else 
   {
     gold_k = hauptfenster->getWerte().gold_kosten(kosten);
     ep_k = hauptfenster->getWerte().ep_kosten(kosten);
   }
  if( !hauptfenster->getOptionen()->HausregelCheck(Midgard_Optionen::Gold).active ) gold_k*=10;
  set_lernzeit(-ep_k,Nichts);
  hauptfenster->getWerte().addGold(gold_k);
  hauptfenster->getWerte().addAEP(ep_k);
  zeige_werte();
}

void table_steigern::set_lernzeit(int kosten,e_was_steigern was,bool no_pp=false)
{
  if(was==Ausdauer) 
   { hauptfenster->getWerte().addSteigertage(Grad_anstieg::AP_Maximum_Tage);
     return;
   }
  if(radiobutton_unterweisung->get_active())
      hauptfenster->getWerte().addSteigertage(kosten/10);
  else if(radiobutton_selbst->get_active())
      hauptfenster->getWerte().addSteigertage(kosten/5.);
  else if(radiobutton_praxis->get_active() )
   {
     if(!no_pp) hauptfenster->getWerte().addSteigertage(kosten/500.);
     else  hauptfenster->getWerte().addSteigertage(kosten/5.);
   }
}

bool table_steigern::steigern_usp(int &kosten,MidgardBasicElement_mutable *MBE,int &stufen, e_was_steigern was)
{
  if (!steigern_mit_EP_bool) // Steigern OHNE EP/Gold/PP
      { set_lernzeit(kosten,was);
        return true; 
      }

  // genug GELD
  int gold_k=genug_geld(kosten);
  if(gold_k==-1) return false; // nicht genug Geld

  // EP
  bool bkep=false,bzep=false;
  steigern_mit(bkep,bzep,MBE,was);

  int ep_k = EP_kosten(kosten);
  int pp   = PP_vorrat(MBE,was);

 if(radiobutton_praxis->get_active())
  {
   if(pp==0) {hauptfenster->set_status("Keine PP vorhanden"); return false;}
   int rest_aep=0,use_pp=0;
   if(radiobutton_pp_hoch_wie_geht->get_active())
    {
      if(!MBE) {hauptfenster->set_status("Nur eine Stufe auf einmal möglich"); return false;}
      use_pp=pp;
      int ppkosten=0,aep=40*pp;
      stufen=stufen_auf_einmal_steigern_fuer_aep(*MBE,ppkosten,aep);
      rest_aep=aep;
      kosten=ppkosten;
      if(togglebutton_pp_verfallen->get_active() && rest_aep!=0)
       { 
         --use_pp;
//         ep_k = 0;
//         kosten=rest_aep;
//         rest_aep=0;
//cout << use_pp<<' '<<kosten<<' '<<rest_aep<<' '<<ep_k<<'\n';
//cout << "Abziehen = "<<MBE->Steigern(hauptfenster->getChar().getWerte(),hauptfenster->getChar().getVTyp())<<'\n';
hauptfenster->set_status("Nicht implementiert");
return false;
       }
    }
   else // genau EINE Stufe steigern
    {
      stufen=1;
      rest_aep = ep_k%40;
      use_pp   = ep_k/40;
      if(togglebutton_pp_verfallen->get_active())
       {
         use_pp=1;
         ep_k = 0;
         kosten=rest_aep;
         rest_aep=0;
       }
    }

   if(togglebutton_pp_aep_fuellen->get_active())
    {
      if(pp>=use_pp)  ep_k = rest_aep; 
      else ep_k = rest_aep + 40*(use_pp-pp);
    }
   else
    {
      if(pp<use_pp )  {hauptfenster->set_status("Nicht genug PP zum steigern vorhanden"); return false; }
      if(rest_aep!=0) {hauptfenster->set_status("Es müßten "+itos(rest_aep)+" EP verwendet werden um "+itos(stufen)+" Stufe(n) zu steigern"); return false; }
      ep_k=0;
    }
   pp=use_pp;
  }

  int aep0=0,kep0=0,zep0=0;
  bool ok=genug_EP(ep_k,bkep,bzep,aep0,kep0,zep0);
  if(!ok) return false;

  // jetzt darf gesteigert werden ...
  hauptfenster->getWerte().addGold(-gold_k);  
  
  if(radiobutton_praxis->get_active())
   {
     if(togglebutton_pp_verfallen->get_active())
       set_lernzeit(kosten,was); 
     else   
      { set_lernzeit(kosten-ep_k,was); set_lernzeit(ep_k,was,true); }
   }
  else set_lernzeit(kosten,was);

  if(pp)
   {
     if     (MBE&&(*MBE)->What()!=MidgardBasicElement::ZAUBER) modify(PP,*MBE,"",MBE->Praxispunkte()-pp) ;
     else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBER) hauptfenster->getWerte().addSpezialPP(-pp) ;
     else if(was==Resistenz)  hauptfenster->getWerte().addResistenzPP(-pp) ;
     else if(was==Abwehr)     hauptfenster->getWerte().addAbwehrPP(-pp) ;
     else if(was==Zaubern)    hauptfenster->getWerte().addZaubernPP(-pp) ;
     else if(was==Ausdauer)   ;
     else assert(!"Fehler in steigern_EP.cc");
   }
  if(bkep)
   { if (ep_k<=hauptfenster->getWerte().KEP()) {hauptfenster->getWerte().addKEP(-ep_k);ep_k =0  ;}
     else                   {ep_k-=hauptfenster->getWerte().KEP(); hauptfenster->getWerte().setKEP(0);} 
   }
  if(bzep)
   { if (ep_k<=hauptfenster->getWerte().ZEP()) {hauptfenster->getWerte().addZEP(-ep_k);ep_k =0 ;}
     else                   {  ep_k-=hauptfenster->getWerte().ZEP(); hauptfenster->getWerte().setZEP(0);  } 
   }
  hauptfenster->getWerte().addAEP(-ep_k);
  zeige_werte();
  return true;  
}

int table_steigern::stufen_auf_einmal_steigern_fuer_aep(MidgardBasicElement_mutable& MBE,int &kosten,int &aep)
{
  int steiger_kosten = MBE.Steigern(hauptfenster->getChar().getAbenteurer());
  int stufen=0;
  int erfolgswert_mem=MBE.Erfolgswert();
  while(steiger_kosten<=aep)
   {   
     kosten+=steiger_kosten;
     ++stufen;
     aep-=steiger_kosten;
     MBE.addErfolgswert(1);
     steiger_kosten = MBE.Steigern(hauptfenster->getChar().getAbenteurer());
   }      
  if(aep>0)
   {
     ++stufen;
     kosten+=steiger_kosten;
     aep-=steiger_kosten;  
     aep*=-1;
   }
     
  MBE.setErfolgswert(erfolgswert_mem);
  return stufen;
}



bool table_steigern::genug_EP(const int ep_k,const bool bkep,const bool bzep, int &aep0,int &kep0,int &zep0)
{
  int aep=hauptfenster->getWerte().AEP();  
  std::string sw;
  if (bkep) {aep += hauptfenster->getWerte().KEP() ;sw  =",KEP";}
  if (bzep) {aep += hauptfenster->getWerte().ZEP() ;sw +=",ZEP";}
  if (ep_k > aep) 
    { 
      hauptfenster->set_status("Zu wenig EP um zu steigern, es fehlen "+itos(ep_k-aep)+" Erfahrungspunkte (AEP"+sw+")."); 
      return false;
    }
  return true;
}


int table_steigern::PP_vorrat(const MidgardBasicElement_mutable *MBE,e_was_steigern was)
{
  guint pp=0;
  if(radiobutton_praxis->get_active())
   { 
     if     (MBE && (*MBE)->What()!=MidgardBasicElement::ZAUBER) pp=(*MBE).Praxispunkte();
     else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBER) pp=hauptfenster->getWerte().SpezialPP();
     else if(was==Resistenz) pp=hauptfenster->getWerte().ResistenzPP() ;
     else if(was==Abwehr)    pp=hauptfenster->getWerte().AbwehrPP() ;
     else if(was==Zaubern)   pp=hauptfenster->getWerte().ZaubernPP() ;
     else if(was==Ausdauer)  {hauptfenster->set_status("Ausdauer kann nicht mit Praxispunkten gesteigert werden.");return false;}
     else assert(!"Fehler in steigern_EP.cc");
   }
 return pp;
}


int table_steigern::EP_kosten(const int kosten)
{
  int ep_k;
  if(radiobutton_unterweisung->get_active())
      ep_k = hauptfenster->getWerte().ep_kosten(kosten);
  else
      ep_k = (int)(kosten);
  return ep_k;
}



void table_steigern::steigern_mit(bool &bkep,bool &bzep,const cH_MidgardBasicElement *MBE,e_was_steigern was)
{
  int womit;
  if     (MBE && (*MBE)->What()==MidgardBasicElement::WAFFE) womit = 1;
  else if(MBE && (*MBE)->What()==MidgardBasicElement::WAFFEGRUND) womit = 1;
  else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBER) womit = 2;
  else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBERWERK) womit = 2;
  else if(MBE && (*MBE)->What()==MidgardBasicElement::KIDO) womit = 3;
  else if(MBE) womit = (*MBE)->Steigern_mit_EP();
  else if (was==Ausdauer) womit=3; 
  else if (was==Zaubern) womit=2;  
  else if (was==Resistenz) womit=2;
  else if (was==Abwehr) womit=1;
  else assert(!"Fehler in steigern_EP.cc:steigern_usp");
//cout << (*MBE)->Name()<<'\t'<<womit<<'\n';
  if(womit==1 || womit==3) bkep=true;
  if(womit==2 || womit==3) bzep=true;
}


int table_steigern::genug_geld(const int kosten)
{
  if(!radiobutton_unterweisung->get_active())
     return 0; // keine Untreweisung => kein Geld nötig
  int gold_k = hauptfenster->getWerte().gold_kosten(kosten);
  if( !hauptfenster->getOptionen()->HausregelCheck(Midgard_Optionen::Gold).active ) gold_k*=10;
  if (gold_k > hauptfenster->getWerte().Gold()) 
    { hauptfenster->set_status("Zu wenig Gold um zu steigern, es fehlt "+itos(gold_k-hauptfenster->getWerte().Gold())+" Gold."); 
      return -1;
    }
  else 
   return gold_k;
}


void table_steigern::on_togglebutton_pp_verfallen_toggled()
{
  if(togglebutton_pp_verfallen->get_active())
   togglebutton_pp_aep_fuellen->set_active(false);  
}

void table_steigern::on_togglebutton_pp_aep_fuellen_toggled()
{
  if(togglebutton_pp_aep_fuellen->get_active())
   togglebutton_pp_verfallen->set_active(false);  
}

        