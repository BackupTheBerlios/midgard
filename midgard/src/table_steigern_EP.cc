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
#include <Aux/itos.h>

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
  label_EP->set_text(itos(hauptfenster->getCWerte().get_Steigern_EP_Prozent())+"%");
  label_Gold->set_text(itos(100-hauptfenster->getCWerte().get_Steigern_EP_Prozent())+"%");
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  A->set_value(100-hauptfenster->getCWerte().get_Steigern_EP_Prozent());
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
     spinbutton_aep->set_value(hauptfenster->getCWerte().AEP());
     spinbutton_kep->set_value(hauptfenster->getCWerte().KEP());
     spinbutton_zep->set_value(hauptfenster->getCWerte().ZEP());
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
     label_aep->set_text(itos(hauptfenster->getCWerte().AEP()));
     label_kep->set_text(itos(hauptfenster->getCWerte().KEP()));
     label_zep->set_text(itos(hauptfenster->getCWerte().ZEP()));
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
     gold_k = (int)(0.5+kosten 
               * ((100-hauptfenster->getCWerte().get_Steigern_EP_Prozent())/100.));
     ep_k = (int)(0.5+kosten * (hauptfenster->getCWerte().get_Steigern_EP_Prozent()/100.));
   }
  if( !hauptfenster->getOptionen()->HausregelCheck(Midgard_Optionen::Gold).active ) gold_k*=10;
  set_lernzeit(-ep_k);
  hauptfenster->getWerte().addGold(gold_k);
  hauptfenster->getWerte().addAEP(ep_k);
  zeige_werte();
}

void table_steigern::set_lernzeit(int kosten)
{
  if(radiobutton_unterweisung->get_active())
      hauptfenster->getWerte().addSteigertage(kosten/10);
  else if(radiobutton_selbst->get_active())
      hauptfenster->getWerte().addSteigertage(kosten/5.);
  else if(radiobutton_praxis->get_active())
      hauptfenster->getWerte().addSteigertage(kosten/500.);
}

bool table_steigern::steigern_usp(int kosten,MidgardBasicElement_mutable *MBE, e_was_steigern was,bool verschenke_pp)
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
if(radiobutton_praxis->get_active())
{ hauptfenster->set_info("Wird gerade überarbeitet, nicht möglich, sorry\n"); 
return false;}

  // Kosten geringer als ein Praxispunkt wert ist
  if((pp>0 && ep_k<40) )//|| (was!=Nichts && ep_k%40!=0 && true))
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
              hauptfenster->InfoFenster->AppendShow(str,WindowInfo::PraxisPunkteMBE,MBE,5);
         else hauptfenster->InfoFenster->AppendShow(str,WindowInfo::PraxisPunkteMBE,MBE,3);
      }
     else if(!verschenke_pp)
      {
        std::string str ="\nACHTUNG: Kosten ("+itos(ep_k)+") geringer als ein Praxispunkt wert (40GFP) ist.\n"
            "Nun gibt es zwei Möglichkeiten:\n"
            " 1. Es wird nicht gesteigert.\n"
            " 2. Es wird mit einem PP gesteigert,\n"
            "    die restlichen Punkte verfallen\n";
        hauptfenster->InfoFenster->AppendShow(str,WindowInfo::PraxisPunkteMBE,was,2);
      }
     return false;
   }
  // Dafür sorgen, daß FP für Praxispunkte nicht verschenkt werden
  while (pp>0 && pp*40 > ep_k ) --pp;
  // Nun von den Kosten 40*pp subtrahieren
  ep_k -= pp*40;
  if(verschenke_pp)
    {
      pp = 1+ep_k/40;
      ep_k=0;
    }
cout <<"jbksfvbkjvb\t"<< pp<<'\n';
  
  int aep0=0,kep0=0,zep0=0;
  bool ok=genug_EP(ep_k,bkep,bzep,aep0,kep0,zep0);
  if(!ok) return false;

  // jetzt darf gesteigert werden ...
  hauptfenster->getWerte().addGold(-gold_k);  
  set_lernzeit(kosten);
  if     (MBE&&(*MBE)->What()!=MidgardBasicElement::ZAUBER) MBE->addPraxispunkte(-pp) ;
  else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBER) hauptfenster->getWerte().addSpezialPP(-pp) ;
  else if(was==Resistenz)  hauptfenster->getWerte().addResistenzPP(-pp) ;
  else if(was==Abwehr)     hauptfenster->getWerte().addAbwehrPP(-pp) ;
  else if(was==Zaubern)    hauptfenster->getWerte().addZaubernPP(-pp) ;
  else if(was==Ausdauer)   ;
  else assert(!"Fehler in steigern_EP.cc");

  if(bkep)
   { if (ep_k<=hauptfenster->getCWerte().KEP()) {hauptfenster->getWerte().addKEP(-ep_k);ep_k =0  ;}
     else                   {ep_k-=hauptfenster->getCWerte().KEP(); hauptfenster->getWerte().setKEP(0);} 
   }
  if(bzep)
   { if (ep_k<=hauptfenster->getCWerte().ZEP()) {hauptfenster->getWerte().addZEP(-ep_k);ep_k =0 ;}
     else                   {  ep_k-=hauptfenster->getCWerte().ZEP(); hauptfenster->getWerte().setZEP(0);  } 
   }
  hauptfenster->getWerte().addAEP(-ep_k);
  zeige_werte();
  return true;  
}

bool table_steigern::genug_EP(const int ep_k,const bool bkep,const bool bzep, int &aep0,int &kep0,int &zep0)
{
  int aep=hauptfenster->getCWerte().AEP();  
  std::string sw;
  if (bkep) {aep += hauptfenster->getCWerte().KEP() ;sw  =",KEP";}
  if (bzep) {aep += hauptfenster->getCWerte().ZEP() ;sw +=",ZEP";}
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
     else if(MBE && (*MBE)->What()==MidgardBasicElement::ZAUBER) pp=hauptfenster->getCWerte().SpezialPP();
     else if(was==Resistenz) pp=hauptfenster->getCWerte().ResistenzPP() ;
     else if(was==Abwehr)    pp=hauptfenster->getCWerte().AbwehrPP() ;
     else if(was==Zaubern)   pp=hauptfenster->getCWerte().ZaubernPP() ;
     else if(was==Ausdauer)  {hauptfenster->set_status("Ausdauer kann nicht mit Praxispunkten gesteigert werden.");return false;}
     else assert(!"Fehler in steigern_EP.cc");
   }
 return pp;
}


int table_steigern::EP_kosten(const int kosten)
{
  int ep_k;
  if(radiobutton_unterweisung->get_active()) //+0.5 zum runden
      ep_k = (int)(0.5 + kosten * (hauptfenster->getCWerte().get_Steigern_EP_Prozent()/100.));
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
  // +0.5 zum runden
  int gold_k = (int)(0.5 + kosten * ((100-hauptfenster->getCWerte().get_Steigern_EP_Prozent())/100.));
  if( !hauptfenster->getOptionen()->HausregelCheck(Midgard_Optionen::Gold).active ) gold_k*=10;
  if (gold_k > hauptfenster->getCWerte().Gold()) 
    { hauptfenster->set_status("Zu wenig Gold um zu steigern, es fehlt "+itos(gold_k-hauptfenster->getCWerte().Gold())+" Gold."); 
      return -1;
    }
  else 
   return gold_k;
}


void table_steigern::PraxisPunkt_to_AEP(MidgardBasicElement_mutable& MBE,bool verfallen,bool alle_pp)
{
  int aep=40;
  if(alle_pp) 
     { aep=40*MBE.Praxispunkte();
       MBE.setPraxispunkte(0);
     }
  else 
       MBE.addPraxispunkte(-1);
     
  int kosten=0;
  stufen_auf_einmal_steigern_fuer_aep(false,MBE,kosten,aep);
  // Die übrigbleibenden Punkte in AEP umwandeln
  if(!verfallen && aep>0)
   {
     int steiger_kosten = MBE.Steigern(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp());
     int aep_kosten = steiger_kosten-aep;
     if(aep_kosten>hauptfenster->getCWerte().AEP())
      {
        hauptfenster->set_status("Zu wenig AEP, die restlichen Punkte verfallen.");
      }
     else
      {
        hauptfenster->getWerte().addAEP(-aep_kosten);
        zeige_werte();
        hauptfenster->getWerte().addGFP(steiger_kosten);
        MBE.addErfolgswert(1);

        set_lernzeit(steiger_kosten-aep_kosten); // Lernzeit für PP
        radiobutton_selbst->set_active(true);
        set_lernzeit(aep_kosten); // Lernzeit für Selbststudium
        radiobutton_praxis->set_active(true);
      }  
   }
  load_for_page(notebook_lernen->get_current_page_num());
}

int table_steigern::stufen_auf_einmal_steigern_fuer_aep(bool info,MidgardBasicElement_mutable& MBE,int &kosten,int &aep)
{
  int steiger_kosten = MBE.Steigern(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp());
  int stufen=0;
  int erfolgswert_mem=MBE.Erfolgswert();
  while(steiger_kosten<=aep)
   {   
     kosten+=steiger_kosten;
     ++stufen;
     aep-=steiger_kosten;
     MBE.addErfolgswert(1);
     steiger_kosten = MBE.Steigern(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp());
   }      
  if(info)
   {
     kosten=MBE.Steigern(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()) ; // kosten für die nächste Stufe
     MBE.setErfolgswert(erfolgswert_mem);
   }
  else
   {
     hauptfenster->getWerte().addGFP(kosten);
     set_lernzeit(kosten);
   }
  return stufen;
}


void table_steigern::PraxisPunkt_fuer_Was(e_was_steigern was)
{
// get_ab_re_za(was,true);
 
}
