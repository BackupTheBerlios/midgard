// $Id: Abenteurer_steigern.cc,v 1.10 2003/09/18 07:32:12 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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
#include "Sprache.hh"
#include <Misc/itos.h>
#include "Random.hh"
#include "Datenbank.hh"
#include "Ausgabe.hh"

bool Abenteurer::steigere(MBEmlt &MBE,const e_wie_steigern wie,
                          const st_bool_steigern &bool_steigern)
{
  if ( MBE->Erfolgswert() >= (*MBE)->MaxErfolgswert(*this))
      { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Maximal möglicher Erfolgswert ("+itos((*MBE)->MaxErfolgswert(*this))+") erreicht");
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
         { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Weitere Steigerung des Erfolgswertes ist NICHT mit Unterweisung möglich.");
           return false; }
     }      
  int stufen=1;
  int steigerkosten=MBE->Steigern(*this);
  if(!steigern_usp(wie,steigerkosten,MBE,stufen,Enums::eMBEm,bool_steigern)) 
         return false;
  addGFP(steigerkosten); 

  MBE->addErfolgswert(stufen);
  return true;
}


void Abenteurer::reduziere(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
  if (bool_steigern.mitEP) desteigern(MBE->Reduzieren(*this),wie,bool_steigern);
      addGFP(-MBE->Reduzieren(*this));
  MBE->addErfolgswert(-1);
}

void Abenteurer::verlerne(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
  unsigned verlernen = MBE->Verlernen(*this);
  if( (*MBE).What()==MidgardBasicElement::ZAUBER && 
      bool_steigern.Spruchrolle)    verlernen/=5  ;
  if (bool_steigern.mitEP) desteigern(verlernen,wie,bool_steigern);  
      addGFP(-verlernen);
}

bool Abenteurer::neu_lernen(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern,const int bonus)
{
 if(((*MBE).What()==MidgardBasicElement::FERTIGKEIT ||  (*MBE).What()==MidgardBasicElement::WAFFE)
      && !(*MBE)->Voraussetzung(*this,false))
  {
    if((*MBE)->Voraussetzung()=="schlank")
      Ausgabe(Ausgabe::Error,(*MBE)->Name()+" können nur schlanke Abenteurer lernen");
    else Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Erst muß "+(*MBE)->Voraussetzung()+" gelernt werden");
    return false;
  }
 // Neue Dinge können nur durch Unterweisung gelernt werden
 // es sei denn es handelt sich um Zaubersprüche
 if((*MBE).What()!=MidgardBasicElement::ZAUBER)   
  { if (wie!=Enums::eUnterweisung)
     { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Neue Fertigkeiten, Waffen, Sprachen und Schriften können nur durch 'Unterweisung' gelernt werden");
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
           { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Neue Zaubersprüche können von "+Typ1()->Name(Geschlecht())
                     +" nicht durch Praxispunkte gelernt werden");
             return false;
           }
        else if((*MBE)->Standard__(*this)!="G")
           { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Nur Grundzauber können von "+Typ1()->Name(Geschlecht())
                     +" mit Praxispunkten gelernt werden");
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
   { set_lernzeit(wie,kosten,Enums::eMBEm,bool_steigern);
     if((*MBE)->Grundfertigkeit(*this))
          MBE->setErfolgswert(9);
     else MBE->setErfolgswert(7);
   }
 else if (!steigern_usp(wie,kosten,MBE,dummy,Enums::eMBEm,bool_steigern)) return false;

 if(bool_steigern.Spruchrolle)
    addGFP((*MBE)->Kosten(*this)/10);
 else  addGFP(kosten);
     
     

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if     ((*MBE).What()==MidgardBasicElement::ZAUBER && bool_steigern.Spruchrolle   
     &&   bool_steigern.SpruchrolleAuto)   
      addGFP(kosten);
 else if((*MBE).What()==MidgardBasicElement::ZAUBER && bool_steigern.Spruchrolle &&
     !bool_steigern.SpruchrolleAuto)
   {
     bool x=cH_Zauber(MBE->getMBE())->spruchrolle_wuerfeln(*this,bonus);
     if(!x) return false;
     else addGFP(kosten);
   } 
 return true;
}


bool Abenteurer::steigern_usp(const e_wie_steigern wie,
                              int &kosten,MBEmlt MBE,int &stufen, 
                              const e_was_steigern was,
                              const st_bool_steigern &bool_steigern)
{
 if (!bool_steigern.mitEP) // Steigern OHNE EP/Gold/PP
   { 
     if(bool_steigern.Spruchrolle) kosten=cH_Zauber(MBE->getMBE())->iStufe();
     set_lernzeit(wie,kosten,was,bool_steigern);
     return true;
   }

  // genug GELD
  int gold_k=genug_geld(kosten,wie,bool_steigern);
  if(gold_k==-1) return false; // nicht genug Geld

  // EP
  bool bkep=false,bzep=false;
  steigern_mit(bkep,bzep,MBE,was);

  int ep_k = EP_kosten(kosten,wie);
  int pp   = PP_vorrat(MBE,was,wie);
  if(pp==-1) return false;

 if(wie==Enums::ePraxis && !bool_steigern.Spruchrolle)
  {
   if(pp==0) {Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Keine PP vorhanden"); return false;}
   int rest_aep=0,use_pp=0;
   if(bool_steigern.hoch_wie_geht)
    {
      if(was!=Enums::eMBEm) { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Nur eine Stufe auf einmal möglich"); return false;}
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
         Ausgabe(Ausgabe::Error,"Nicht implementiert");
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
      else            {ep_k = rest_aep + 40*(use_pp-pp); use_pp=pp;}
      if(ep_k > use_pp*40)
       {
         Ausgabe(Ausgabe::Error,"Höchstens die Hälfte der GFP darf beim 'Steigern mit PP' durch die Hälfte der GFP darf beim 'Steigern mit PP' durch EP bestritten werden"); 
         return false;
       }
    }  
   else
    {  
      if(pp<use_pp )  {Ausgabe(Ausgabe::Error,"Nicht genug PP zum steigern vorhanden"); return false; }
      if(rest_aep!=0) {Ausgabe(Ausgabe::Error,"Es müßten "+itos(rest_aep)+" EP verwendet werden um "+itos(stufen)+" Stufe(n) zu steigern"); return false;}
      ep_k=0;
    }
   pp=use_pp;
  }

   
  int aep0=0,kep0=0,zep0=0;
  bool ok=genug_EP(ep_k,bkep,bzep,aep0,kep0,zep0);
  if(!ok) return false;

  // jetzt darf gesteigert werden ...
  addGold(-gold_k);
  
  if(wie==Enums::ePraxis && !bool_steigern.Spruchrolle)
   {
     if(bool_steigern.pp_verfallen)  set_lernzeit(wie,kosten,was,bool_steigern); 
     else   
      { //set_lernzeit(wie,kosten-ep_k,was,bool_steigern); 
        //set_lernzeit(wie,ep_k,was,bool_steigern,true); 
        set_lernzeit(wie,kosten,was,bool_steigern);
      }
   }
  else 
   { if(bool_steigern.Spruchrolle) kosten=cH_Zauber(MBE->getMBE())->iStufe();
     set_lernzeit(wie,kosten,was,bool_steigern);
   }

  if(pp)
   {
     if     (was==Enums::eMBEm && (*MBE).What()!=MidgardBasicElement::ZAUBER) modify(PPmodus,MBE,MidgardBasicElement::st_zusatz(),MBE->Praxispunkte()-pp) ;
     else if(was==Enums::eMBEm && (*MBE).What()==MidgardBasicElement::ZAUBER) addSpezialPP(-pp) ;
     else if(was==Enums::eResistenz)  addResistenzPP(-pp) ;
     else if(was==Enums::eAbwehr)     addAbwehrPP(-pp) ;   
     else if(was==Enums::eZaubern)    addZaubernPP(-pp) ;
     else if(was==Enums::eAusdauer)   ;
     else assert(!"Fehler in steigern_EP.cc");
   }
  if(bkep)
   { if (ep_k<=KEP()) {addKEP(-ep_k);ep_k =0  ;}
     else  {ep_k-=KEP(); setKEP(0);}
   }
  if(bzep)
   { if (ep_k<=ZEP()) {addZEP(-ep_k);ep_k =0 ;}
     else {  ep_k-=ZEP(); setZEP(0);  }
   }
  addAEP(-ep_k);
  return true;  
}

void Abenteurer::move_neues_element(MBEmlt &MBE,std::list<MBEmlt> *MyList_neu_,const std::list<cH_MidgardBasicElement> *alleSprachen)
{
 std::list<MBEmlt> *MyList;//,*MyList_neu;
 if((*MBE).What()==MidgardBasicElement::FERTIGKEIT) 
  {
//???kido steigern und nicht neu lernen     if ((*MBE)->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return;
     MyList     = &List_Fertigkeit();
   }
 else if((*MBE).What()==MidgardBasicElement::WAFFE) MyList=&List_Waffen(); 
   
 else if((*MBE).What()==MidgardBasicElement::WAFFEGRUND) MyList=&List_WaffenGrund(); 
 else if((*MBE).What()==MidgardBasicElement::ZAUBER) MyList=&List_Zauber();
 else if((*MBE).What()==MidgardBasicElement::ZAUBERWERK) MyList=&List_Zauberwerk();
 else if((*MBE).What()==MidgardBasicElement::KIDO) MyList= &List_Kido(); 
 else if((*MBE).What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &List_Sprache();
     // eventuell höherer Erfolgswert weil die Sprache schon ungelernt beherrscht wird)
// das entspricht wohl nicht den Regeln , oder doch???
//     int ungelernterErfolgswert=cH_Sprache(MBE->getMBE())->getHoeherenErfolgswert(List_Sprache(),*alleSprachen/*hauptfenster->getCDatabase().Sprache*/);
//     if (ungelernterErfolgswert > MBE->Erfolgswert()) MBE->setErfolgswert(ungelernterErfolgswert);
     // bis hier
   }
 else if((*MBE).What()==MidgardBasicElement::SCHRIFT) MyList=&List_Schrift();
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");
 move_element(*MyList_neu_,*MyList,MBE);
}




void Abenteurer::set_lernzeit(const e_wie_steigern wie,const int kosten,
                              const e_was_steigern was,
                              const st_bool_steigern bool_steigern)
{
  if(was==Enums::eAusdauer)
   { addSteigertage(Grad_anstieg::AP_Maximum_Tage);
     return;
   }
  if(bool_steigern.Spruchrolle)
   { assert(wie==Enums::eSelbststudium);
     addSteigertage(kosten*3);
     return;
   }
  if(wie==Enums::eUnterweisung) addSteigertage(kosten/10);
  else if(wie==Enums::eSelbststudium) addSteigertage(kosten/5.);
  else if(wie==Enums::ePraxis)       
   {
     addSteigertage(kosten/500.);
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
                           const st_bool_steigern bool_steigern)
{
  if(wie!=Enums::eUnterweisung) return 0; // keine Unterweisung => kein Geld nötig
  if(bool_steigern.Spruchrolle) return 0;
  int gold_k = gold_kosten(kosten);
  if( !bool_steigern.HausG1 ) gold_k*=10;

  std::pair<int,bool> gestu=Erfolgswert("Geschäftstüchtigkeit");
  if(gestu.second)
   {
      int iw=Random::W20();
      int erg=gestu.first+iw;
      Ausgabe(Ausgabe::Log,"EW:Geschäftstüchtigkeit = "+itos(gestu.first)+"+"+itos(iw)
               +"="+itos(erg));
      int gold_gespart = int(gold_k*0.9);
      if(erg>=20) Ausgabe(Ausgabe::Log," => "+itos(gold_gespart)+" Gold gespart");
      gold_k-=gold_gespart;
   }

  if (gold_k > Gold())
    { Ausgabe(Ausgabe::Error,"Zu wenig Gold um zu steigern, es fehlt "+itos(gold_k-Gold())+" Gold.");
      return -1;
    }
  else
   return gold_k;
}

bool Abenteurer::genug_EP(const int ep_k,const bool bkep,const bool bzep, int &aep0,int &kep0,int &zep0)
{
  int aep=AEP();
  std::string sw;
  if (bkep) {aep += KEP() ;sw  =",KEP";}
  if (bzep) {aep += ZEP() ;sw +=",ZEP";}
  if (ep_k > aep) 
    { 
      Ausgabe(Ausgabe::Error,"Zu wenig EP um zu steigern, es fehlen "+itos(ep_k-aep)+" Erfahrungspunkte (AEP"+sw+").");
      return false;
    }
  return true;
}


int Abenteurer::EP_kosten(const int kosten,const e_wie_steigern wie)
{
  int ep_k;
  if(wie==Enums::eUnterweisung) ep_k = ep_kosten(kosten);
  else                   ep_k = (int)(kosten);
  return ep_k;
}

int Abenteurer::PP_vorrat(const MBEmlt &MBE,const e_was_steigern was,
                          const e_wie_steigern wie)
{
  unsigned pp=0;
  if(wie==Enums::ePraxis)
   {
     if     (was==Enums::eMBEm && (*MBE).What()!=MidgardBasicElement::ZAUBER) pp=MBE->Praxispunkte();
     else if(was==Enums::eMBEm && (*MBE).What()==MidgardBasicElement::ZAUBER) pp=SpezialPP();
     else if(was==Enums::eResistenz) pp=ResistenzPP() ;
     else if(was==Enums::eAbwehr)    pp=AbwehrPP() ;
     else if(was==Enums::eZaubern)   pp=ZaubernPP() ;
     else if(was==Enums::eAusdauer)  {Ausgabe(Ausgabe::Error,"Ausdauer kann nicht mit Praxispunkten gesteigert werden.");return -1;}
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
     int ew=MBE->Erfolgswert();
     if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
         ew=(*MBE)->FErfolgswert(*this,MBE);
//std::cout << steiger_kosten<<' '<<kosten<<' '<<stufen<<'\t'<<ew<<' '
//<<(*MBE)->MaxErfolgswert(*this)<<'\n';
     if((*MBE)->MaxErfolgswert(*this)-1==ew) break;
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
              if(zusatz.name==Herkunft()->Name())
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
  if(wie==Enums::ePraxis || wie==Enums::eSelbststudium) ep_k = kosten ;
  else
   {  
     gold_k = gold_kosten(kosten);
     ep_k = ep_kosten(kosten);
   }
//  if( !hauptfenster->getOptionen()->HausregelCheck(Magus_Optionen::Gold).active ) gold_k*=10;
  if( !bool_steigern.HausG1 ) gold_k*=10;
  set_lernzeit(wie,-ep_k,Enums::eMBEm,bool_steigern);
  addGold(gold_k);
  addAEP(ep_k);   
}


int Abenteurer::get_ausdauer(int grad,
                              const e_wie_steigern &wie,const st_bool_steigern &bool_steigern)
{
   int bonus_K, bonus_aK, bonus_Z;
   int kosten = Datenbank.GradAnstieg.get_AP_Kosten(grad);
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
   if (!steigern_usp(wie,kosten,Enums::eAusdauer,bool_steigern)) return 0;
   addGFP(kosten);
   int ap=0;
   for (int i=0;i<grad;++i) ap += Random::W6();

  int nab, nap;
  if      (Typ1()->Ausdauer() == "k" || Typ2()->Ausdauer() == "k")  nab = bonus_K ;
  else if (Typ1()->Ausdauer() == "ak"|| Typ2()->Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  nap = ap + nab + bo_Au() ;
  int nspez = Grad()*Spezies()->AP_GradFak();
  nap += nspez;
  Ausgabe(Ausgabe::Error,"Ausdauerpunkte für Grad "+itos(Grad())+": "
   "Gewürfelt("+itos(ap)+") + Bonus für Typ("+itos(nab)
   +") + Persönlichen Bonus("+itos(bo_Au())
   +") + Spezies-Bonus("+itos(nspez)+") = "+itos(nap)+" AP");
   // Für alle ist die AP-anzahel mind. = Grad
  if (AP()<Grad()) setAP(Grad());
   // Neue AP höher als alte?
  if (nap>AP())  setAP(nap)  ;
  return kosten;
}
 
int Abenteurer::get_ab_re_za(const e_was_steigern was,const e_wie_steigern &wie,
                              const bool bsteigern,
                              const st_bool_steigern &bool_steigern)
{
  int alter_wert, max_wert;
  int kosten;
  int grad=Grad();
  if(!bsteigern) grad=--grad;
  if(grad==0) kosten=0;
  else if (was==Enums::eAbwehr)
    { 
      max_wert = Datenbank.GradAnstieg.get_MaxAbwehr(grad);
      alter_wert = Abwehr_wert(); 
      kosten   = Datenbank.GradAnstieg.get_Abwehr_Kosten(alter_wert+1);
      if(!bsteigern) kosten = Datenbank.GradAnstieg.get_Abwehr_Kosten(alter_wert);
    } 
  else if (was==Enums::eResistenz)
    { 
      max_wert = Datenbank.GradAnstieg.get_MaxResistenz(grad);
      alter_wert = Resistenz(); 
      kosten   = Datenbank.GradAnstieg.get_Resistenz_Kosten(alter_wert+1);
      if(!bsteigern) kosten = Datenbank.GradAnstieg.get_Resistenz_Kosten(alter_wert);
    } 
  else if (was==Enums::eZaubern)
    { 
      if (is_mage())
       { 
         max_wert = Datenbank.GradAnstieg.get_MaxZauber(grad);
         alter_wert = Zaubern_wert(); 
         kosten   = Datenbank.GradAnstieg.get_Zauber_Kosten(alter_wert+1);
         if(!bsteigern) kosten = Datenbank.GradAnstieg.get_Zauber_Kosten(alter_wert);
       } 
      else return 0;
    }
  else assert(!"never get here");
  if (kosten!=0 && (alter_wert >= max_wert && bsteigern))
      { Ausgabe(Ausgabe::Error,"Für Grad "+itos(Grad())+" ist der Maximalwert erreicht!") ;
        return 0;}

  if(kosten!=0 && bsteigern)
   { // hier stand eAusdauer ... was ist sinnvoller - oder?
     if (!steigern_usp(wie,kosten,was,bool_steigern)) return 0;
     addGFP(kosten);
     if      (was==Enums::eAbwehr)    setAbwehr_wert(alter_wert+1);
     else if (was==Enums::eResistenz) setResistenz(alter_wert+1);  
     else if (was==Enums::eZaubern)   setZaubern_wert(alter_wert+1);
   }
  else
   {  
     if(kosten==0) 
      { 
        Ausgabe(Ausgabe::Error,"Minimaler Erfogswert erreicht");
        return 0;
      }
     if (bool_steigern.mitEP) desteigern(kosten,wie,bool_steigern);
     set_lernzeit(wie,-kosten,was,bool_steigern);
     addGFP(-kosten);
     if      (was==Enums::eAbwehr)    setAbwehr_wert(alter_wert-1);
     else if (was==Enums::eResistenz) setResistenz(alter_wert-1);  
     else if (was==Enums::eZaubern)   setZaubern_wert(alter_wert-1);
   }
 return kosten;
}

bool Abenteurer::eigenschaften_steigern_erlaubt() const
{
 if(Grad() > get_Grad_Basiswerte()) return true;
 return false;
}

void Abenteurer::eigenschaften_steigern(int wurf)
{
  if(!eigenschaften_steigern_erlaubt())
   {Ausgabe(Ausgabe::Error,"Für Grad "+itos(get_Grad_Basiswerte())+" wurde schon gewürfelt");
    return;
   }
  // Erhöhen der Schicksalsgunst
  { int n=Datenbank.GradAnstieg.get_Schicksalsgunst(Grad());
    if(Spezies()->Name()=="Halbling") n=n+2;
    add_SG(n);
  }

  if(wurf==-1) wurf=Random::W100();

  int z=wurf;  
  std::string info="Beim Würfeln zur Erhöhung einer Eigenschaft für Grad "
      + itos(get_Grad_Basiswerte()+1) + " wurde eine ";
  info += itos(wurf);
  info +=" gewürfelt ==> ";
  std::string was = "keine Erhöhung";

  int erh = Random::W6()+1;
  int awko= Ko(); //alter_wert;
  int aapb = bo_Au(); // alter Wert
  if     ( z<=76 ) ;//nichts steigern 
  else if( z<=78 ) { was="Stärke";           add_St(erh); }
  else if( z<=81 ) { was="Geschicklichkeit"; add_Gs(erh); }
  else if( z<=84 ) { was="Gewandheit"; add_Gw(erh); }
  else if( z<=87 ) { was="Konstitution"; add_Ko(erh); }
  else if( z<=90 ) { was="Intelligenz"; add_In(erh); }
  else if( z<=93 ) { was="Zaubertalent"; add_Zt(erh); }
  else if( z<=95 ) { was="Selbstbeherrschung"; add_Sb(erh); }
  else if( z<=97 ) { was="Willenskraft"; add_Wk(erh); }
  else if( z<=99 ) { was="persönliche Ausstrahlung"; add_pA(erh); }
  else if( z==100) { was="Aussehn"; add_Au(erh); }

  {
   //Setzen von abgeleiteten Werten, die durch eine Steigerung 
   //bertoffen sein könnten:
   setSinn("Sechster Sinn",Zt()/25);
//   setRaufen((St()+Gw())/20+bo_An() );
   if(was=="Konstitution" && (awko/10 != Ko()/10))
         setLP(LP()-awko/10+Ko()/10);
   if( aapb!=bo_Au() ) 
      setAP(AP()-aapb+bo_Au());
  }

  info += was;
  if (was != "keine Erhöhung" )  info += " um "+itos(erh)+" erhöht.";
  Ausgabe(Ausgabe::Log,info);
  set_Grad_Basiswerte(1+get_Grad_Basiswerte());
}


void Abenteurer::Steigertage2Alter()
{
  float tage=Steigertage();
  int alter=Alter();
  int tage_pro_jahr=360;
  while(tage>tage_pro_jahr)
   {
     alter+=1;
     tage-=tage_pro_jahr;
   }
  setAlter(alter);
  setSteigertage(tage);
}

