// $Id: Abenteurer_steigern.cc,v 1.9 2002/10/31 15:37:58 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#include "Abenteurer.hh"
#include "Zauber.hh"
#include <Misc/itos.h>
#include "zufall.h"

bool Abenteurer::steigere(MBEmlt &MBE,std::string &info,const e_wie_steigern wie,
                          const st_bool_steigern &bool_steigern)
{
  if ( MBE->Erfolgswert() >= (*MBE)->MaxErfolgswert(*this))
      { info+= "Maximal möglicher Erfolgswert erreicht";
        return false; }
  if(wie==Enums::eUnterweisung)
    {  
     if( ((*MBE).What()==MidgardBasicElement::FERTIGKEIT &&
            MBE->Erfolgswert() >= cH_Fertigkeit(MBE->getMBE())->MaxUnterweisung()) ||
           ((*MBE).What()==MidgardBasicElement::SPRACHE &&
            MBE->Erfolgswert() >= cH_Fertigkeit("Sprache")->MaxUnterweisung()) ||
           ((*MBE).What()==MidgardBasicElement::SCHRIFT &&
            MBE->Erfolgswert() >= cH_Fertigkeit("Schreiben")->MaxUnterweisung())
          )
         { info+= "Weitere Steigerung des Erfolgswertes ist NICHT mit Unterweisung möglich.";
           return false; }
     }      
  int stufen=1;
  int steigerkosten=MBE->Steigern(*this);
  if(!steigern_usp(wie,steigerkosten,MBE,stufen,Enums::eMBEm,info,bool_steigern)) 
         return false;
  getWerte().addGFP(steigerkosten); 

  std::list<MBEmlt> &MyList=get_known_list(MBE);
  for (std::list<MBEmlt>::iterator i=MyList.begin();i!= MyList.end();++i )
{
//cout << (*MBE)->Name()<<' '<<(*i)->Name()<<' '<<stufen<<'\n';
     if ( (*i) == MBE) { (*i)->addErfolgswert(stufen) ; break;}
}
  return true;
}


void Abenteurer::reduziere(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
  if (bool_steigern.mitEP) desteigern(MBE->Reduzieren(*this),wie,bool_steigern);
      getWerte().addGFP(-MBE->Reduzieren(*this));

  std::list<MBEmlt> &MyList=get_known_list(MBE);

  for (std::list<MBEmlt>::iterator i=MyList.begin();i!= MyList.end();++i )
       if ( (*i) == MBE) { (*i)->addErfolgswert(-1) ; break;}

//  MBE->addErfolgswert(-1) ;
}

void Abenteurer::verlerne(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
  guint verlernen = MBE->Verlernen(*this);
  if( (*MBE).What()==MidgardBasicElement::ZAUBER && 
      bool_steigern.Spruchrolle)    verlernen/=5  ;
  if (bool_steigern.mitEP) desteigern(verlernen,wie,bool_steigern);  
      getWerte().addGFP(-verlernen);

}

bool Abenteurer::neu_lernen(MBEmlt &MBE,std::string &info,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
 if(((*MBE).What()==MidgardBasicElement::FERTIGKEIT ||  (*MBE).What()==MidgardBasicElement::WAFFE)
      && !(*MBE)->Voraussetzung(*this,false))
  {
    info+="Erst muß "+(*MBE)->Voraussetzung()+" gelernt werden";
    return false;
  }

 // Neue Dinge können nur durch Unterweisung gelernt werden
 // es sei denn es handelt sich um Zaubersprüche
 if((*MBE).What()!=MidgardBasicElement::ZAUBER)   
  { if (wie!=Enums::eUnterweisung)
     { info+="Neue Fertigkeiten, Waffen, Sprachen und Schriften können nur durch 'Unterweisung' gelernt werden";
       return false;
     }
  }   
 else // ==> (*MBE).What()==MidgardBasicElement::ZAUBER
  {
/* 
    if(radiobutton_selbst->get_active() )
      { hauptfenster->set_status("Neue Zauber können nicht durch 'Selbststudium' gelernt werden");
        return false;
      }
*/
    // Nicht alle Abenteurerklassen können Zauber auch mit Praxispunkten lernen
    if(wie==Enums::ePraxis)
      { if(!Typ1()->SpruecheMitPP() && !Typ2()->SpruecheMitPP() )
           { info+="Neue Zaubersprüche können von "+Typ1()->Name(getWerte().Geschlecht())
                     +" nicht durch Praxispunkte gelernt werden";
             return false;
           }
        else if((*MBE)->Standard__(*this)!="G")
           { info +="Nur Grundzauber können von "+Typ1()->Name(getWerte().Geschlecht())
                     +" mit Praxispunkten gelernt werden";
             return false;
           }
      }
  }
 int kosten=(*MBE)->Kosten(*this);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( (*MBE).What()==MidgardBasicElement::ZAUBER && bool_steigern.Spruchrolle ) 
      kosten/=10;
 /////////////////////////////////////////////////////////////////////////
 // Lernern neuer Sprache mit PP: /////////////////////////////////////// 
 bool neue_sprache_mit_pp=false;
 if((*MBE).What()==MidgardBasicElement::SPRACHE &&bool_steigern.neue_sprache_pp)
   { neue_sprache_mit_pp=true;  kosten=40;}
 /////////////////////////////////////////////////////////////////////////
 
 int dummy=1;
 if(neue_sprache_mit_pp)
   { set_lernzeit(wie,kosten,Enums::eMBEm);
     if((*MBE)->Grundfertigkeit(*this))
          MBE->setErfolgswert(9);
     else MBE->setErfolgswert(7);
   }
 else if (!steigern_usp(wie,kosten,MBE,dummy,Enums::eMBEm,info,bool_steigern)) return false;


 getWerte().addGFP(kosten);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if     ((*MBE).What()==MidgardBasicElement::ZAUBER && bool_steigern.Spruchrolle &&  
     bool_steigern.SpruchrolleAuto)    getWerte().addGFP(kosten);
 else if((*MBE).What()==MidgardBasicElement::ZAUBER && bool_steigern.Spruchrolle &&
     !bool_steigern.SpruchrolleAuto)
   {
     bool x=cH_Zauber(MBE->getMBE())->spruchrolle_wuerfeln(*this,info);
     if(!x) return false;
     else getWerte().addGFP(kosten);
   } 
 return true;
}


bool Abenteurer::steigern_usp(const e_wie_steigern wie,
                              int &kosten,MBEmlt MBE,int &stufen, 
                              const e_was_steigern was,
                              std::string &info,
                              const st_bool_steigern &bool_steigern)
{
 if (!bool_steigern.mitEP) // Steigern OHNE EP/Gold/PP
   { set_lernzeit(wie,kosten,was);
     return true;
   }

  // genug GELD
  int gold_k=genug_geld(kosten,wie,bool_steigern.HausG1,info);
  if(gold_k==-1) return false; // nicht genug Geld

  // EP
  bool bkep=false,bzep=false;
  steigern_mit(bkep,bzep,MBE,was);

  int ep_k = EP_kosten(kosten,wie);
  int pp   = PP_vorrat(MBE,was,info,wie);
  if(pp==-1) return false;

 if(wie==Enums::ePraxis)
  {
   if(pp==0) {info+="Keine PP vorhanden"; return false;}
   int rest_aep=0,use_pp=0;
   if(bool_steigern.hoch_wie_geht)
    {
      if(was!=Enums::eMBEm) { info+="Nur eine Stufe auf einmal möglich"; return false;}
      use_pp=pp;
      int ppkosten=0,aep=40*pp;
      stufen=stufen_auf_einmal_steigern_fuer_aep(MBE,ppkosten,aep);
      rest_aep=aep;
      kosten=ppkosten;
      if(bool_steigern.pp_verfallen && rest_aep!=0)
       { 
//         --use_pp;
//         ep_k = 0;
//         kosten=rest_aep;
//         rest_aep=0;
//cout << use_pp<<' '<<kosten<<' '<<rest_aep<<' '<<ep_k<<'\n';
         info+="Nicht implementiert";
         return false;
       }
    }   
   else // genau EINE Stufe steigern
    {
      stufen=1;
      rest_aep = ep_k%40;
      use_pp   = ep_k/40;
      if(bool_steigern.pp_verfallen)
       {
         use_pp=1;
         ep_k = 0;
         kosten=rest_aep;
         rest_aep=0;
       }
    }

   if(bool_steigern.aep_fuellen)
    {
      if(pp>=use_pp)  ep_k = rest_aep; 
      else ep_k = rest_aep + 40*(use_pp-pp);
    }  
   else
    {  
      if(pp<use_pp )  {info+="Nicht genug PP zum steigern vorhanden"; return false; }
      if(rest_aep!=0) {info+= "Es müßten "+itos(rest_aep)+" EP verwendet werden um "+itos(stufen)+" Stufe(n) zu steigern"; return false;}
      ep_k=0;
    }
   pp=use_pp;
  }
   
  int aep0=0,kep0=0,zep0=0;
  bool ok=genug_EP(ep_k,bkep,bzep,aep0,kep0,zep0,info);
  if(!ok) return false;

  // jetzt darf gesteigert werden ...
  getWerte().addGold(-gold_k);
  
  if(wie==Enums::ePraxis)
   {
     if(bool_steigern.pp_verfallen)  set_lernzeit(wie,kosten,was); 
     else   
      { set_lernzeit(wie,kosten-ep_k,was); set_lernzeit(wie,ep_k,was,true); }
   }
  else set_lernzeit(wie,kosten,was);

  if(pp)
   {
     if     (was==Enums::eMBEm && (*MBE).What()!=MidgardBasicElement::ZAUBER) modify(PPmodus,MBE,MidgardBasicElement::st_zusatz(),MBE->Praxispunkte()-pp) ;
     else if(was==Enums::eMBEm && (*MBE).What()==MidgardBasicElement::ZAUBER) getWerte().addSpezialPP(-pp) ;
     else if(was==Enums::eResistenz)  getWerte().addResistenzPP(-pp) ;
     else if(was==Enums::eAbwehr)     getWerte().addAbwehrPP(-pp) ;   
     else if(was==Enums::eZaubern)    getWerte().addZaubernPP(-pp) ;  
     else if(was==Enums::eAusdauer)   ;
     else assert(!"Fehler in steigern_EP.cc");
   }
  if(bkep)
   { if (ep_k<=getWerte().KEP()) {getWerte().addKEP(-ep_k);ep_k =0  ;}
     else  {ep_k-=getWerte().KEP(); getWerte().setKEP(0);}
   }
  if(bzep)
   { if (ep_k<=getWerte().ZEP()) {getWerte().addZEP(-ep_k);ep_k =0 ;}
     else {  ep_k-=getWerte().ZEP(); getWerte().setZEP(0);  }
   }
  getWerte().addAEP(-ep_k);
  return true;  
}


void Abenteurer::set_lernzeit(const e_wie_steigern wie,const int kosten,
                              const e_was_steigern was,const bool no_pp)
{
  if(was==Enums::eAusdauer)
   { getWerte().addSteigertage(Grad_anstieg::AP_Maximum_Tage);
     return;
   }
  if     (wie==Enums::eUnterweisung) getWerte().addSteigertage(kosten/10);
  else if(wie==Enums::eSelbststudium) getWerte().addSteigertage(kosten/5.);
  else if(wie==Enums::ePraxis)       
   {
     if(!no_pp) getWerte().addSteigertage(kosten/500.);
     else       getWerte().addSteigertage(kosten/5.);
   }
}   

void Abenteurer::steigern_mit(bool &bkep,bool &bzep,const MBEmlt MBE,e_was_steigern was)
{
  int womit;
  if(was==Enums::eMBEm)
   {
     if     (MBE->getMBE()->What()==MidgardBasicElement::WAFFE) womit = 1;
     else if(MBE->getMBE()->What()==MidgardBasicElement::WAFFEGRUND) womit = 1;
     else if(MBE->getMBE()->What()==MidgardBasicElement::ZAUBER) womit = 2;
     else if(MBE->getMBE()->What()==MidgardBasicElement::ZAUBERWERK) womit = 2;
     else if(MBE->getMBE()->What()==MidgardBasicElement::KIDO) womit = 3;
     else womit = MBE->getMBE()->Steigern_mit_EP();
   }
  else if (was==Enums::eAusdauer) womit=3; 
  else if (was==Enums::eZaubern) womit=2;  
  else if (was==Enums::eResistenz) womit=2;
  else if (was==Enums::eAbwehr) womit=1;   
  else assert(!"Fehler in steigern_EP.cc:steigern_usp");
//cout << (MBE)->Name()<<'\t'<<womit<<'\n';
  if(womit==1 || womit==3) bkep=true;
  if(womit==2 || womit==3) bzep=true;
}



int Abenteurer::genug_geld(const int kosten,const e_wie_steigern wie,
                           const bool HausG1, std::string &info)
{
  if(wie!=Enums::eUnterweisung) return 0; // keine Unterweisung => kein Geld nötig
  int gold_k = getWerte().gold_kosten(kosten);
  if( !HausG1 ) gold_k*=10;
  if (gold_k > getWerte().Gold())
    { info+= "Zu wenig Gold um zu steigern, es fehlt "+itos(gold_k-getWerte().Gold())+" Gold.";
      return -1;
    }
  else
   return gold_k;
}

bool Abenteurer::genug_EP(const int ep_k,const bool bkep,const bool bzep, int &aep0,int &kep0,int &zep0,std::string &info)
{
  int aep=getWerte().AEP();
  std::string sw;
  if (bkep) {aep += getWerte().KEP() ;sw  =",KEP";}
  if (bzep) {aep += getWerte().ZEP() ;sw +=",ZEP";}
  if (ep_k > aep) 
    { 
      info+= "Zu wenig EP um zu steigern, es fehlen "+itos(ep_k-aep)+" Erfahrungspunkte (AEP"+sw+").";
      return false;
    }
  return true;
}


int Abenteurer::EP_kosten(const int kosten,const e_wie_steigern wie)
{
  int ep_k;
  if(wie==Enums::eUnterweisung) ep_k = getWerte().ep_kosten(kosten);
  else                   ep_k = (int)(kosten);
  return ep_k;
}

int Abenteurer::PP_vorrat(const MBEmlt &MBE,const e_was_steigern was,
                          std::string &info,const e_wie_steigern wie)
{
  guint pp=0;
  if(wie==Enums::ePraxis)
   {
     if     (was==Enums::eMBEm && (*MBE).What()!=MidgardBasicElement::ZAUBER) pp=MBE->Praxispunkte();
     else if(was==Enums::eMBEm && (*MBE).What()==MidgardBasicElement::ZAUBER) pp=getWerte().SpezialPP();
     else if(was==Enums::eResistenz) pp=getWerte().ResistenzPP() ;
     else if(was==Enums::eAbwehr)    pp=getWerte().AbwehrPP() ;
     else if(was==Enums::eZaubern)   pp=getWerte().ZaubernPP() ;
     else if(was==Enums::eAusdauer)  {info+= "Ausdauer kann nicht mit Praxispunkten gesteigert werden.";return -1;}
     else assert(!"Fehler in steigern_EP.cc");
   }
 return pp;
}

int Abenteurer::stufen_auf_einmal_steigern_fuer_aep(MBEmlt& MBE,int &kosten,int &aep)
{
  int steiger_kosten = MBE->Steigern(*this);
  int stufen=0;
  int erfolgswert_mem=MBE->Erfolgswert();
  while(steiger_kosten<=aep)
   {   
     kosten+=steiger_kosten;
     ++stufen;
     aep-=steiger_kosten;
     MBE->addErfolgswert(1);
     steiger_kosten = MBE->Steigern(*this);
   }      
  if(aep>0)
   {
     ++stufen;
     kosten+=steiger_kosten;
     aep-=steiger_kosten;   
     aep*=-1;
   }
    
  MBE->setErfolgswert(erfolgswert_mem);
  return stufen;
}

void Abenteurer::modify(modi_modus modus,const MBEmlt &M,const MidgardBasicElement::st_zusatz &zusatz,int praxispunkte)
{
  bool found=false;
  int c=0;
  while(true)
   {
     std::list<MBEmlt> *L;
     if(c==0) L=&List_Fertigkeit();
     else if(c==1) L=&List_Zauber();
     else if(c==2) L=&List_Waffen();
     else if(c==3) L=&List_Sprache();
     else if(c==4) L=&List_Schrift();
     else assert(!"never get here\n");
     for(std::list<MBEmlt>::iterator i=L->begin();i!=L->end();++i)
      {
        if( (*i)->Zusatz().empty() && (*(*i))->Name() == (*M)->Name())
         {
           found=true;
           if(modus==PPmodus)
             (*i)->setPraxispunkte(praxispunkte);
           else if(modus==Zusatzmodus)
            {
              (*i)->setZusatz(zusatz);
              if(zusatz.name==getWerte().Herkunft()->Name())
                (*i)->setErfolgswert(9);
            }
         }   
      }      
    if(found) break;
    else ++c;
   }
}   
    
void Abenteurer::desteigern(unsigned int kosten,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
  int gold_k=0,ep_k=0;
  if(wie==Enums::ePraxis) ep_k = kosten ;
  else
   {  
     gold_k = getWerte().gold_kosten(kosten);
     ep_k = getWerte().ep_kosten(kosten);
   }
//  if( !hauptfenster->getOptionen()->HausregelCheck(Midgard_Optionen::Gold).active ) gold_k*=10;
  if( !bool_steigern.HausG1 ) gold_k*=10;
  set_lernzeit(wie,-ep_k,Enums::eMBEm);
  getWerte().addGold(gold_k);
  getWerte().addAEP(ep_k);   
}


int Abenteurer::get_ausdauer(int grad, const Datenbank &Database,std::string &info,
                              const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
   Random random;
   int bonus_K, bonus_aK, bonus_Z;
   int kosten = Database.GradAnstieg.get_AP_Kosten(grad);
   if (grad == 1)  { bonus_K =  4, bonus_aK =  3; bonus_Z =  2; }
   else if (grad == 2)  { bonus_K =  6, bonus_aK =  4; bonus_Z =  2; }
   else if (grad == 3)  { bonus_K =  9, bonus_aK =  6; bonus_Z =  3; }
   else if (grad == 4)  { bonus_K = 12, bonus_aK =  8; bonus_Z =  4; }
   else if (grad == 5)  { bonus_K = 15, bonus_aK = 10; bonus_Z =  5; }
   else if (grad == 6)  { bonus_K = 18, bonus_aK = 12; bonus_Z =  6; }
   else if (grad == 7)  { bonus_K = 21, bonus_aK = 14; bonus_Z =  7; }
   else if (grad == 8)  { bonus_K = 24, bonus_aK = 16; bonus_Z =  8; }
   else if (grad == 9)  { bonus_K = 27, bonus_aK = 18; bonus_Z =  9; }
   else if (grad ==10)  { bonus_K = 30, bonus_aK = 20; bonus_Z = 10; }
   else if (grad >=11)  { bonus_K = 30, bonus_aK = 20; bonus_Z = 10; }
//   int dummy=1;
   if (!steigern_usp(wie,kosten,Enums::eAusdauer,info,bool_steigern)) return 0;
//   if (!steigern_usp(kosten,0,dummy,eAusdauer)) return 0;
   getWerte().addGFP(kosten);
   int ap=0;
   for (int i=0;i<grad;++i) ap += random.integer(1,6);

  int nab, nap;
  if      (Typ1()->Ausdauer() == "k" || Typ2()->Ausdauer() == "k")  nab = bonus_K ;
  else if (Typ1()->Ausdauer() == "ak"|| Typ2()->Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  nap = ap + nab + getWerte().bo_Au() ;
  int nspez = getWerte().Grad()*getWerte().Spezies()->AP_GradFak();
  nap += nspez;
  info+="Ausdauerpunkte für Grad "+itos(getWerte().Grad())+": "
   "Gewürfelt("+itos(ap)+") + Bonus für Typ("+itos(nab)
   +") + Persönlichen Bonus("+itos(getWerte().bo_Au())
   +") + Spezies-Bonus("+itos(nspez)+") = "+itos(nap)+" AP";
   // Für alle ist die AP-anzahel mind. = Grad
  if (getWerte().AP()<getWerte().Grad()) getWerte().setAP(getWerte().Grad());
   // Neue AP höher als alte?
  if (nap>getWerte().AP())  getWerte().setAP(nap)  ;
  return kosten;
}
 
int Abenteurer::get_ab_re_za(const e_was_steigern was,const e_wie_steigern &wie,
                              const bool bsteigern,const Datenbank &Database,
                              std::string &info,const st_bool_steigern &bool_steigern)
{
  int alter_wert, max_wert;
  int kosten;
  int grad=getWerte().Grad();
  if(!bsteigern) grad=--grad;
//  if(!radiobutton_steigern->get_active()) grad=--grad;
  if(grad==0) grad=1;
  if      (was==Enums::eAbwehr)
    { 
      max_wert = Database.GradAnstieg.get_MaxAbwehr(grad);
      alter_wert = getWerte().Abwehr_wert(); 
      kosten   = Database.GradAnstieg.get_Abwehr_Kosten(alter_wert+1);
    } 
  else if (was==Enums::eResistenz)
    { 
      max_wert = Database.GradAnstieg.get_MaxResistenz(grad);
      alter_wert = getWerte().Resistenz(); 
      kosten   = Database.GradAnstieg.get_Resistenz_Kosten(alter_wert+1);
    } 
  else if (was==Enums::eZaubern)
    { 
      if (is_mage())
       { 
         max_wert = Database.GradAnstieg.get_MaxZauber(grad);
         alter_wert = getWerte().Zaubern_wert(); 
         kosten   = Database.GradAnstieg.get_Zauber_Kosten(alter_wert+1);
       } 
      else return 0;
    }
  else assert(!"never get here");
  if (alter_wert >= max_wert && bsteigern)
      { info+="Für Grad "+itos(getWerte().Grad())+" ist der Maximalwert erreicht!" ;
        return 0;}

  if(bsteigern)
   {
//     int dummy=1;
     if (!steigern_usp(wie,kosten,Enums::eAusdauer,info,bool_steigern)) return 0;
//     if(!steigern_usp(kosten,0,dummy,was) ) return 0;
     getWerte().addGFP(kosten);
     if      (was==Enums::eAbwehr)    getWerte().setAbwehr_wert(alter_wert+1);
     else if (was==Enums::eResistenz) getWerte().setResistenz(alter_wert+1);  
     else if (was==Enums::eZaubern)   getWerte().setZaubern_wert(alter_wert+1);
   }
  else
   {  
     if (bool_steigern.mitEP) desteigern(kosten,wie,bool_steigern);
     set_lernzeit(wie,-kosten,was);
     getWerte().addGFP(-kosten);
     if      (was==Enums::eAbwehr)    getWerte().setAbwehr_wert(alter_wert-1);
     else if (was==Enums::eResistenz) getWerte().setResistenz(alter_wert-1);  
     else if (was==Enums::eZaubern)   getWerte().setZaubern_wert(alter_wert-1);
   }
 return kosten;
}

void Abenteurer::eigenschaften_steigern(std::string &info,const Datenbank &Database,int wurf)
{
  if(getWerte().Grad() <= getWerte().get_Grad_Basiswerte())
   {info+="Für Grad "+itos(getWerte().get_Grad_Basiswerte())+" wurde schon gewürfelt";
    return;
   }
  // Erhöhen der Schicksalsgunst
  { int n=Database.GradAnstieg.get_Schicksalsgunst(getWerte().Grad());
    if(getWerte().Spezies()->Name()=="Halbling") n=n+2;
    getWerte().add_SG(n);
  }

  Random random;
  if(wurf==-1) wurf=random.integer(1,100);

  int z=wurf;  
  info+="Beim Würfeln zur Erhöhung einer Eigenschaft für Grad "
      + itos(getWerte().get_Grad_Basiswerte()+1) + " wurde eine ";
  info += itos(wurf);
  info +=" gewürfelt ==> ";
  std::string was = "keine Erhöhung";

  int erh = random.integer(1,6)+1;
  int awko= getWerte().Ko(); //alter_wert;
  int aapb = getWerte().bo_Au(); // alter Wert
  if( 76<=z && z>=78 ) { was="Stärke";           getWerte().add_St(erh); }
  if( 79<=z && z>=81 ) { was="Geschicklichkeit"; getWerte().add_Gs(erh); }
  if( 82<=z && z>=84 ) { was="Gewandheit"; getWerte().add_Gw(erh); }
  if( 85<=z && z>=87 ) { was="Konstitution"; getWerte().add_Ko(erh); }
  if( 88<=z && z>=90 ) { was="Intelligenz"; getWerte().add_In(erh); }
  if( 91<=z && z>=93 ) { was="Zaubertalent"; getWerte().add_Zt(erh); }
  if( 94<=z && z>=95 ) { was="Selbstbeherrschung"; getWerte().add_Sb(erh); }
  if( 96<=z && z>=97 ) { was="Willenskraft"; getWerte().add_Wk(erh); }
  if( 99<=z && z>=99 ) { was="persönliche Ausstrahlung"; getWerte().add_pA(erh); }
  if (z==100)          { was="Aussehn"; getWerte().add_Au(erh); }

  {
   //Setzen von abgeleiteten Werten, die durch eine Steigerung 
   //bertoffen sein könnten:
   getWerte().setSinn("Sechster Sinn",getWerte().Zt()/25);
//   getWerte().setRaufen((getWerte().St()+getWerte().Gw())/20+getWerte().bo_An() );
   if(was=="Konstitution" && (awko/10 != getWerte().Ko()/10))
         getWerte().setLP(getWerte().LP()-awko/10+getWerte().Ko()/10);
   if( aapb!=getWerte().bo_Au() ) 
      getWerte().setAP(getWerte().AP()-aapb+getWerte().bo_Au());
  }

  info += was;
  if (was != "keine Erhöhung" )
    {
       info += " um "+itos(erh)+" erhöht.";
    }
  getWerte().set_Grad_Basiswerte(1+getWerte().get_Grad_Basiswerte());
}


void Abenteurer::Steigertage2Alter()
{
  float tage=getWerte().Steigertage();
  int alter=getWerte().Alter();
  int tage_pro_jahr=360;
  while(tage>tage_pro_jahr)
   {
     alter+=1;
     tage-=tage_pro_jahr;
   }
  getWerte().setAlter(alter);
  getWerte().setSteigertage(tage);
}

