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

//bool steigern;

gint midgard_CG::vscale_value_changed(GdkEventButton *ev)
{
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  int Av=(int)A->get_value();
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
  if (steigern_mit_EP_bool) checkbutton_EP_Geld->set_active(true);
  else                      checkbutton_EP_Geld->set_active(false);
}

void midgard_CG::on_checkbutton_EP_Geld_toggled()
{
   if (checkbutton_EP_Geld->get_active()) 
      { steigern_mit_EP_bool=true;
//        frame_lernen_mit->set_sensitive(true);
      }
   else 
      { steigern_mit_EP_bool=false;
//        frame_lernen_mit->set_sensitive(false);
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
  int gold_k=0,ep_k=0;
  if(radiobutton_praxis->get_active())
   {
     ep_k = kosten ;
   }
  else 
   {
     gold_k = (int)(0.5+kosten 
               * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
     ep_k = (int)(0.5+kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
   }
  if( !MOptionen->HausregelCheck(Midgard_Optionen::Gold).active ) gold_k*=10;
  set_lernzeit(-ep_k);
  Werte.addGold(gold_k);
  Werte.addAEP(ep_k);
  Geld_uebernehmen();
  EP_uebernehmen();
}

void midgard_CG::set_lernzeit(int kosten)
{
  if(radiobutton_unterweisung->get_active())
      Werte.addSteigertage(kosten/10);
  else if(radiobutton_selbst->get_active())
      Werte.addSteigertage(kosten/5.);
  else if(radiobutton_praxis->get_active())
      Werte.addSteigertage(kosten/500.);
}

bool midgard_CG::steigern_usp(int kosten,cH_MidgardBasicElement* MBE, e_was_steigern was)
{
  if (!steigern_mit_EP_bool) // Steigern OHNE EP/Gold/PP
      { set_lernzeit(kosten);
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

  // Kosten geringer als ein Praxispunkt wert ist
  if(pp>0 && ep_k<40)
   {
     if(MBE)
      {
        int kosten=0;
        int aep=40;
        int stufen=stufen_auf_einmal_steigern_fuer_aep(true,*MBE,kosten,aep);
        int kosten_max=0;
        int aep_max=40*pp;
        int stufen_max=stufen_auf_einmal_steigern_fuer_aep(true,*MBE,kosten_max,aep_max);
        std::string anzahl="drei";
        if(pp>1) anzahl="fünf";
        std::string str ="\nACHTUNG: Kosten ("+itos(ep_k)+") geringer als ein Praxispunkt wert (40GFP) ist.\n"
            "Nun gibt es "+anzahl+" Möglichkeiten:\n"
            " 1. Es wird nicht gesteigert.\n"
            " 2. Es wird mit einem PP um "+itos(stufen)+" Stufen gesteigert.\n"
            "    Die restlichen Punkte ("+itos(aep)+") verfallen\n"
            " 3. Es wird mit einem PP und "+itos(kosten-aep)+" AEP um "+itos(stufen+1)+" Stufen gesteigert\n"
            "    (Damit verfallen dann keine Punkte. Die Lernzeit für die verwendeten AEP\n."
            "     wird wie bei 'Selbststudium' angenommen)\n";
         if(pp>1)
         str+= 
            " 4. Es werden alle ("+itos(pp)+") PP verwendet um "+itos(stufen_max)+" Stufen zu steigern.\n"
            "    Die restlichen Punkte ("+itos(aep_max)+") verfallen\n"
            " 5. Es werden alle ("+itos(pp)+") PP und "+itos(kosten_max-aep_max)+" AEP verwendet um "+itos(stufen_max+1)+" Stufen zu steigern,\n"
            "(sollten die AEP (bei 3. und 5.) nicht ausreichen um fehlende FP zu bezahlen,\n"
            " so verfallen die restlichen FP der PP.)";
         if(pp>1)
              InfoFenster->AppendShow(str,WindowInfo::PraxisPunkteMBE,*MBE,5);
         else InfoFenster->AppendShow(str,WindowInfo::PraxisPunkteMBE,*MBE,3);
         return false;
      }
   }
  // Dafür sorgen, daß FP für Praxispunkte nicht verschenkt werden
  while (pp>0 && pp*40 > ep_k ) --pp;
  // Nun von den Kosten 40*pp subtrahieren
  ep_k -= pp*40;

  
  int aep0=0,kep0=0,zep0=0;
  bool ok=genug_EP(ep_k,bkep,bzep,aep0,kep0,zep0);
  if(!ok) return false;


  // jetzt darf gesteigert werden ...
  Werte.addGold(-gold_k);  
  set_lernzeit(kosten);
  if     (MBE&&(*MBE)->What()!=MidgardBasicElement::ZAUBER) (*MBE)->addPraxispunkte(-pp) ;
  else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBER) Werte.addSpezialPP(-pp) ;
  else if(was==Resistenz)  Werte.addResistenzPP(-pp) ;
  else if(was==Abwehr)     Werte.addAbwehrPP(-pp) ;
  else if(was==Zaubern)    Werte.addZaubernPP(-pp) ;
  else if(was==Ausdauer)   ;
  else assert(!"Fehler in steigern_EP.cc");

  if(bkep)
   { if (ep_k<=Werte.KEP()) {Werte.addKEP(-ep_k);ep_k =0  ;}
     else                   {ep_k-=Werte.KEP(); Werte.setKEP(0);} 
   }
  if(bzep)
   { if (ep_k<=Werte.ZEP()) {Werte.addZEP(-ep_k);ep_k =0 ;}
     else                   {  ep_k-=Werte.ZEP(); Werte.setZEP(0);  } 
   }
  Werte.addAEP(-ep_k);
  Geld_uebernehmen();
  EP_uebernehmen();
  return true;  
}

bool midgard_CG::genug_EP(const int ep_k,const bool bkep,const bool bzep, int &aep0,int &kep0,int &zep0)
{
  int aep=Werte.AEP();  
  std::string sw;
  if (bkep) {aep += Werte.KEP() ;sw  =",KEP";}
  if (bzep) {aep += Werte.ZEP() ;sw +=",ZEP";}
  if (ep_k > aep) 
    { 
      set_status("Zu wenig EP um zu steigern, es fehlen "+itos(ep_k-aep)+" Erfahrungspunkte (AEP"+sw+")."); 
      return false;
    }
  return true;
}


int midgard_CG::PP_vorrat(const cH_MidgardBasicElement *MBE,e_was_steigern was)
{
  guint pp=0;
  if(radiobutton_praxis->get_active())
   { 
     if     (MBE && (*MBE)->What()!=MidgardBasicElement::ZAUBER) pp=(*MBE)->Praxispunkte();
     else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBER) pp=Werte.SpezialPP();
     else if(was==Resistenz) pp=Werte.ResistenzPP() ;
     else if(was==Abwehr)    pp=Werte.AbwehrPP() ;
     else if(was==Zaubern)   pp=Werte.ZaubernPP() ;
     else if(was==Ausdauer)  {set_status("Ausdauer kann nicht mit Praxispunkten gesteigert werden.");return false;}
     else assert(!"Fehler in steigern_EP.cc");
   }
 return pp;
}


int midgard_CG::EP_kosten(const int kosten)
{
  int ep_k;
  if(radiobutton_unterweisung->get_active()) //+0.5 zum runden
      ep_k = (int)(0.5 + kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
  else
      ep_k = (int)(kosten);
  return ep_k;
}



void midgard_CG::steigern_mit(bool &bkep,bool &bzep,const cH_MidgardBasicElement *MBE,e_was_steigern was)
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


int midgard_CG::genug_geld(const int kosten)
{
  if(!radiobutton_unterweisung->get_active())
     return 0; // keine Untreweisung => kein Geld nötig
  // +0.5 zum runden
  int gold_k = (int)(0.5 + kosten * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
  if( !MOptionen->HausregelCheck(Midgard_Optionen::Gold).active ) gold_k*=10;
  if (gold_k > Werte.Gold()) 
    { set_status("Zu wenig Gold um zu steigern, es fehlt "+itos(gold_k-Werte.Gold())+" Gold."); 
      return -1;
    }
  else 
   return gold_k;
}


void midgard_CG::PraxisPunkt_to_AEP(cH_MidgardBasicElement& MBE,bool verfallen,bool alle_pp)
{
  int aep=40;
  if(alle_pp) 
     { aep=40*MBE->Praxispunkte();
       MBE->setPraxispunkte(0);
     }
  else 
       MBE->addPraxispunkte(-1);
     
  int kosten=0;
  stufen_auf_einmal_steigern_fuer_aep(false,MBE,kosten,aep);
  // Die übrigbleibenden Punkte in AEP umwandeln
  if(!verfallen && aep>0)
   {
     int steiger_kosten = MBE->Steigern(Werte,Typ);
     int aep_kosten = steiger_kosten-aep;
     if(aep_kosten>Werte.AEP())
      {
        set_status("Zu wenig AEP, die restlichen Punkte verfallen.");
      }
     else
      {
        Werte.addAEP(-aep_kosten);
        EP_uebernehmen();
        Werte.addGFP(steiger_kosten);
        MBE->addErfolgswert(1);

        set_lernzeit(steiger_kosten-aep_kosten); // Lernzeit für PP
        radiobutton_selbst->set_active(true);
        set_lernzeit(aep_kosten); // Lernzeit für Selbststudium
        radiobutton_praxis->set_active(true);
      }  
   }
  load_for_page(notebook_lernen->get_current_page_num());
}

int midgard_CG::stufen_auf_einmal_steigern_fuer_aep(bool info,cH_MidgardBasicElement& MBE,int &kosten,int &aep)
{
  int steiger_kosten = MBE->Steigern(Werte,Typ);
  int stufen=0;
  int erfolgswert_mem=MBE->Erfolgswert();
  while(steiger_kosten<=aep)
   {   
     kosten+=steiger_kosten;
     ++stufen;
     aep-=steiger_kosten;
     MBE->addErfolgswert(1);
     steiger_kosten = MBE->Steigern(Werte,Typ);
   }      
  if(info)
   {
     kosten=MBE->Steigern(Werte,Typ) ; // kosten für die nächste Stufe
     MBE->setErfolgswert(erfolgswert_mem);
   }
  else
   {
     Werte.addGFP(kosten);
     set_lernzeit(kosten);
   }
  return stufen;
}


