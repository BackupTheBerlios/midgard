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
#include "Window_Erfahrungspunkte.hh"
#include <gtk--/adjustment.h>
#include <Aux/itos.h>

bool steigern;

gint midgard_CG::vscale_value_changed(GdkEventButton *ev)
{
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  int Av=(int)A->get_value();
//  steigern_EP_prozent = 100-Av;
  Database.GradAnstieg.set_Steigern_EP_Prozent(100-Av);
  steigern_gtk();
  return false;
}

void midgard_CG::steigern_gtk()
{
  label_EP->set_text(itos(Database.GradAnstieg.get_Steigern_EP_Prozent())+"%");
  label_Gold->set_text(itos(100-Database.GradAnstieg.get_Steigern_EP_Prozent())+"%");
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  A->set_value(100-Database.GradAnstieg.get_Steigern_EP_Prozent());
  if (steigern) checkbutton_EP_Geld->set_active(true);
  else               checkbutton_EP_Geld->set_active(false);
}

void midgard_CG::on_checkbutton_EP_Geld_toggled()
{
   if (checkbutton_EP_Geld->get_active()) 
      { steigern=true;
        frame_lernen_mit->set_sensitive(true);
      }
   else 
      { steigern=false;
        frame_lernen_mit->set_sensitive(false);
      }
}

void midgard_CG::on_button_EP_clicked()
{
  manage(new Window_Erfahrungspunkte(this,Werte));
}
 
void midgard_CG::EP_uebernehmen()
{
  label_aep->set_text(itos(Werte.AEP()));
  label_kep->set_text(itos(Werte.KEP()));
  label_zep->set_text(itos(Werte.ZEP()));
}
                  
void midgard_CG::Geld_uebernehmen()
{
  label_gold->set_text(itos(Werte.Gold()));
  label_silber->set_text(itos(Werte.Silber()));
  label_kupfer->set_text(itos(Werte.Kupfer()));
  // und für die Ausrüstung
  label_golda->set_text(itos(Werte.Gold()));
  label_silbera->set_text(itos(Werte.Silber()));
  label_kupfera->set_text(itos(Werte.Kupfer()));
}


void midgard_CG::desteigern(unsigned int kosten)
{
  guint gold_k=0,ep_k=0;
  if(radiobutton_praxis->get_active())
   {
     ep_k = kosten ;
   }
  else 
   {
     gold_k = (guint)(kosten 
               * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
     ep_k = (guint)(kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
   }
  Werte.addGold(gold_k);
  Werte.addAEP(ep_k);
  Geld_uebernehmen();
  EP_uebernehmen();
}

void midgard_CG::set_lernzeit(unsigned int kosten)
{
  if(radiobutton_unterweisung->get_active())
      Werte.addSteigertage(kosten/10);
  else if(radiobutton_selbst->get_active())
      Werte.addSteigertage(kosten/5.);
  else if(radiobutton_praxis->get_active())
      Werte.addSteigertage(kosten/500.);
}

bool midgard_CG::steigern_usp(unsigned int kosten,const cH_MidgardBasicElement* MBE, e_was_steigern was)
{
  if (!steigern) // Steigern OHNE EP/Gold/PP
      { set_lernzeit(kosten);
        return true; 
      }

  int gold_k=0,ep_k=0;
  if(radiobutton_unterweisung->get_active())
   {
     // genug Geld? 
     gold_k = (guint)(kosten * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
     if (gold_k > Werte.Gold()) 
         { regnot("Zu wenig Gold um zu steigern,\n es fehlen "+itos(gold_k-Werte.Gold())+" GS."); 
cout << "Zu wenig Gold\n";
           return false;
         }
   }  

  // genug EP?
  bool bkep=false,bzep=false;
  int womit;
  if(MBE) womit = (*MBE)->Steigern_mit_EP();
  else if (was==Ausdauer) womit=3;
  else if (was==Zaubern) womit=3;
  else if (was==Resistenz) womit=3;
  else if (was==Abwehr) womit=3;
  else assert(!"Fehler in steigern_EP.cc:steigern_usp");
  if(womit==1 || womit==3) bkep=true;
  if(womit==2 || womit==3) bzep=true;

  if(radiobutton_unterweisung->get_active()) 
      ep_k = (guint)(kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
  else
      ep_k = (guint)(kosten);
  guint aep=Werte.AEP();  
  guint kep=Werte.KEP();  
  guint zep=Werte.ZEP();  
  guint pp=0;
  if     (radiobutton_praxis->get_active())
   { 
     if(MBE)                 pp=(*MBE)->Praxispunkte() ;
     else if(was==Resistenz) pp=Werte.ResistenzPP() ;
     else if(was==Abwehr)    pp=Werte.AbwehrPP() ;
     else if(was==Zaubern)   pp=Werte.ZaubernPP() ;
     else if(was==Ausdauer)  {regnot ("Ausdauer kann nicht mit Praxispunkten gesteigert werden.");return false;}
     else assert(!"Fehler in steigern_EP.cc");
   }

  // Dafür sorgen, daß FP für Praxispunkte nicht verschenkt werden
  while (pp>0 && pp*40 > ep_k ) --pp;
  // Nun von den Kosten 40*pp subtrahieren
  ep_k -= pp*40;

  guint ep = aep;  
  std::string sw;
  if (bkep) {ep += kep;sw  =",KEP";}
  if (bzep) {ep += zep;sw +=",ZEP";}
  if (ep_k > ep) 
      { regnot("Zu wenig EP um zu steigern,\n es fehlen "+itos(ep_k-ep)+" Erfahrungspunkte (AEP"+sw+")."); 
cout << "Zu wenig EP\n";
        return false;
      }

  // jetzt darf gesteigert werden ...
  Werte.addGold(-gold_k);  
  set_lernzeit(kosten);
  if (MBE) (*MBE)->add_Praxispunkte(-pp) ;
  else if(was==Resistenz)  Werte.addResistenzPP(-pp) ;
  else if(was==Abwehr)  Werte.addAbwehrPP(-pp) ;
  else if(was==Zaubern)  Werte.addZaubernPP(-pp) ;
  else if(was==Ausdauer)  ;
  else assert(!"Fehler in steigern_EP.cc");

  if(bkep)
   { if (ep_k<=kep) {Werte.addKEP(-ep_k);ep_k =0 ;}
     else           {ep_k-=kep; Werte.setKEP(0);} 
   }
  if(bzep)
   { if (ep_k<=zep) {Werte.addZEP(-ep_k);ep_k =0 ;}
     else           {ep_k-=zep; Werte.setZEP(0);} 
   }
  Werte.addAEP(-ep_k);
  Geld_uebernehmen();
  EP_uebernehmen();
  return true;  
}


