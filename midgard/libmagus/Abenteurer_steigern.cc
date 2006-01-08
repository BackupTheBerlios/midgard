// $Id: Abenteurer_steigern.cc,v 1.20 2006/01/08 08:46:58 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2003-2004 Christof Petig
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
#include "magustrace.h"
#include <Misc/Trace.h>

bool Abenteurer::ZauberSpruecheMitPP() const
{
   return Typ1()->SpruecheMitPP() || Typ2()->SpruecheMitPP() ;
}

// dies ist die eigentliche Steigern Funktion
bool Abenteurer::steigern_usp(int &kosten,MBEmlt MBE,int &stufen)
{
 if (!fpanteil && !goldanteil) // Steigern OHNE EP/Gold/PP
 { if (wie_steigern==ws_Spruchrolle) 
     kosten=cH_Zauber(MBE->getMBE())->iStufe();
   set_lernzeit(kosten,MBE);
   return true;
 }

  // genug GELD
  int gold_k=genug_geld(kosten);
  if (gold_k==-1) return false; // nicht genug Geld

  // EP
  MidgardBasicElement::EP_t ep_t=steigern_mit(MBE);

  int ep_k = EP_kosten(kosten);

  if(wie_steigern==ws_Praxispunkte)
  { int pp = PP_vorrat(MBE);
    if(pp==-1) return false;
    if(pp==0) 
    { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Keine PP vorhanden"); 
      return false;
    }
    if (wie_steigern==ws_Praxispunkte 
          && wie_steigern_variante==wsv_NurPraxispunkte
          && pp*40<ep_k)
    { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Mindestens "+itos((ep_k+39)/40)
        + " Praxispunkte erforderlich (oder EP aufwenden)");
      return false;
    }
    else if(ep_k > pp*(40/2))
    { Ausgabe(Ausgabe::Error,"Höchstens die Hälfte der GFP darf beim "
          "'Steigern mit PP' durch EP bestritten werden"); 
      Ausgabe(Ausgabe::Error,"Es fehlen "+itos((ep_k+79)/80 - pp)+"PP");
      return false;
    }

    unsigned use_pp=0; // soviel PP werden verwendet
    
    if (MBE->What()==MidgardBasicElement::RESISTENZ_UND_CO)  // || immer genau EINE Stufe steigern
    { stufen=1;
      use_pp = ep_k/40;
      ep_k  %= 40;
      if (wie_steigern_variante==wsv_NurPraxispunkte && ep_k)
      { ++use_pp;
        ep_k=0;
      }
    }
    else 
    { kosten = 0;
      ep_k = 40*pp;
      stufen=stufen_auf_einmal_steigern_fuer_aep(MBE,kosten,ep_k);
      if (!ep_k) use_pp=(kosten+39)/40;
      else use_pp=kosten/40;
    }

    if (use_pp>pp)
    { ep_k+=40*(use_pp-pp);
      use_pp=pp;
    }   

    if(!genug_EP(ep_k,ep_t)) return false;
   
    set_lernzeit(kosten,MBE); 
    PP_aufwenden(use_pp,MBE);
    EP_aufwenden(ep_t,ep_k);
    return true;
  }

   
  if(!genug_EP(ep_k,ep_t)) return false;

  // jetzt darf gesteigert werden ...
  addGold(-gold_k);
  if(wie_steigern==ws_Spruchrolle) 
    kosten=cH_Zauber(MBE->getMBE())->iStufe(); // ???
  set_lernzeit(kosten,MBE);
  EP_aufwenden(ep_t,ep_k);
  return true;  
}

void Abenteurer::EP_aufwenden(MidgardBasicElement::EP_t ep_t,unsigned ep_k)
{ if(ep_t&MidgardBasicElement::KEP)
  { int kep=std::min<unsigned>(ep_k,KEP());
    addKEP(-kep);
    ep_k-=kep;
  }
  if(ep_t&MidgardBasicElement::ZEP)
  { int zep=std::min<unsigned>(ep_k,ZEP());
    addZEP(-zep);
    ep_k-=zep;
  }
  addAEP(-ep_k);
}

void Abenteurer::move_neues_element(MBEmlt &MBE,std::list<MBEmlt> *MyList_neu_)
{
 move_element(*MyList_neu_,getList((*MBE).What()),MBE);
}

void Abenteurer::set_lernzeit(int kosten, const MBEmlt &was)
{
  if(!!was && was->What()==MidgardBasicElement::RESISTENZ_UND_CO
     && was->getHandle<ResistenzUndCo>()->WasIstEs()==ResistenzUndCo::eAusdauer)
  { addSteigertage(Grad_anstieg::AP_Maximum_Tage);
    return;
  }
  switch (wie_steigern)
  { case ws_Spruchrolle:
      addSteigertage(kosten*3);
      break;
    case ws_Selbststudium:
      addSteigertage(kosten/5.);
      break;
    case ws_Unterweisung:
      addSteigertage(kosten/10.);
      break;
    case ws_Praxispunkte:
      addSteigertage(kosten/500.);
      break;
  }
}   

#warning das gehört in MBE!!!
MidgardBasicElement::EP_t Abenteurer::steigern_mit(const MBEmlt &MBE) const
{ switch (MBE->getMBE()->What())
  { case MidgardBasicElement::WAFFE: 
    case MidgardBasicElement::WAFFEGRUND:
      return MidgardBasicElement::KEP;
    case MidgardBasicElement::ZAUBER:
    case MidgardBasicElement::ZAUBERWERK:
      return MidgardBasicElement::ZEP;
    case MidgardBasicElement::KIDO:
      return MidgardBasicElement::Beides;
    case MidgardBasicElement::RESISTENZ_UND_CO:
      switch (MBE->getHandle<ResistenzUndCo>()->WasIstEs())
      { case ResistenzUndCo::eAusdauer: 
          return MidgardBasicElement::Beides;
        case ResistenzUndCo::eZaubern:
        case ResistenzUndCo::eResistenz: 
          return MidgardBasicElement::ZEP;
        case ResistenzUndCo::eAbwehr:
          return MidgardBasicElement::KEP;
      }
      break;
    default:
      return MBE->getMBE()->Steigern_mit_EP();
  }
  abort();
}

// Rückgabewert: Kosten in GS oder -1 wenn es nicht reicht
int Abenteurer::genug_geld(const int kosten) const
{
  if (wie_steigern!=ws_Unterweisung) return 0; // keine Unterweisung => kein Geld nötig
  int gold_k = gold_kosten(kosten);
  if (!optionen.HausregelCheck(Optionen::Gold).active) gold_k*=10;

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

bool Abenteurer::genug_EP(int ep_k,MidgardBasicElement::EP_t mit) const
{ int aep=AEP();
  std::string sw;
  if (mit&MidgardBasicElement::KEP) { aep += KEP(); sw =",KEP"; }
  if (mit&MidgardBasicElement::ZEP) { aep += ZEP(); sw +=",ZEP"; }
  if (ep_k > aep) 
  { Ausgabe(Ausgabe::Error,"Zu wenig EP um zu steigern, es fehlen "+itos(ep_k-aep)+" Erfahrungspunkte (AEP"+sw+").");
    return false;
  }
  return true;
}

int Abenteurer::EP_kosten(int kosten) const
{ if(wie_steigern==ws_Unterweisung || wie_steigern==ws_Selbststudium) 
    return ep_kosten(kosten);
  else return kosten;
}

int Abenteurer::PP_vorrat(const MBEmlt &MBE) const
{
  if(wie_steigern!=ws_Praxispunkte)
    return 0;
  if(MBE->What()!=MidgardBasicElement::RESISTENZ_UND_CO)
  { if ((*MBE).What()!=MidgardBasicElement::ZAUBER) return MBE->Praxispunkte();
    return SpezialPP();
  }
  switch (MBE->getHandle<ResistenzUndCo>()->WasIstEs())
  { case ResistenzUndCo::eResistenz: return ResistenzPP() ;
    case ResistenzUndCo::eAbwehr: return AbwehrPP() ;
    case ResistenzUndCo::eZaubern: return ZaubernPP() ;
    case ResistenzUndCo::eAusdauer: 
      Ausgabe(Ausgabe::Error,"Ausdauer kann nicht mit Praxispunkten gesteigert werden.");
      return -1;
    default: assert(!"Fehler in steigern_EP.cc");
  }
  abort();
}

void Abenteurer::PP_aufwenden(unsigned pp, const MBEmlt &MBE)
{ 
  if(MBE->What()!=MidgardBasicElement::RESISTENZ_UND_CO)
  { if ((*MBE).What()!=MidgardBasicElement::ZAUBER)
      MBE->setPraxispunkte(MBE->Praxispunkte()-pp);
//      modify(PPmodus,MBE,MidgardBasicElement::st_zusatz(),MBE->Praxispunkte()-pp);
    else addSpezialPP(-pp);
    return;
  }
  switch (MBE->getHandle<ResistenzUndCo>()->WasIstEs())
  { case ResistenzUndCo::eResistenz: addResistenzPP(-pp); break;
    case ResistenzUndCo::eAbwehr: addAbwehrPP(-pp); break;
    case ResistenzUndCo::eZaubern: addZaubernPP(-pp); break;
    default: assert(!"Fehler in PP_aufwenden");
  }
}

// kosten: out: Kosten an GFP
// aep: in: Verfügbare FP von PP
// aep: out: Benötigte EP
// result: steigerbare Stufen
int Abenteurer::stufen_auf_einmal_steigern_fuer_aep(const MBEmlt& _MBE,int &kosten,int &aep) const
{ kosten=0; // out parameter
  MBEmlt MBE(_MBE);
  int stufen=0;
  int steiger_kosten = MBE->Steigern(*this);
  int ew=MBE->Erfolgswert();
  if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
    ew=(*MBE)->FErfolgswert(*this,MBE);
  while (steiger_kosten<=aep && ew<(*MBE)->MaxErfolgswert(*this))
  { kosten+=steiger_kosten;
    ++stufen;
    aep-=steiger_kosten;

    MBE->addErfolgswert(1);
    ew=MBE->Erfolgswert();
    if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
      ew=(*MBE)->FErfolgswert(*this,MBE);
    steiger_kosten = MBE->Steigern(*this);
    ManuProC::Trace(LibMagus::trace_channel,__FUNCTION__,steiger_kosten,
               kosten,stufen,aep,ew,(*MBE)->MaxErfolgswert(*this));
  }      
  if((steiger_kosten/2)<aep && wie_steigern==ws_Praxispunkte
            && wie_steigern_variante==wsv_PraxispunkteFP 
            && ew<(*MBE)->MaxErfolgswert(*this))
  { ++stufen;
    kosten+=steiger_kosten;
    aep=steiger_kosten-aep; // noch notwendige 
  }
  else aep=0;
  return stufen;
}

int Abenteurer::get_ausdauer(int grad)
{
   int bonus_K=0, bonus_aK=0, bonus_Z=0;
   int kosten = Datenbank.GradAnstieg.get_AP_Kosten(grad);
   switch (grad)
   { case  1: bonus_K =  4, bonus_aK =  3; bonus_Z =  2; break;
     default: if (2 <= grad && grad <= 10)
       { bonus_K = 3*grad, bonus_aK = 2*grad; bonus_Z = grad;  }
       else if (grad >=11)  
       { bonus_K = 30, bonus_aK = 20; bonus_Z = 10;  }
       break;
   }
   if (!steigern_usp(kosten,ResistenzUndCo::eAusdauer)) return 0;
   addGFP(kosten);
   int ap=0;
   for (int i=0;i<grad;++i) ap += Random::W6();

  int nab=0;
  if      (Typ1()->Ausdauer() == "k" || Typ2()->Ausdauer() == "k")  nab = bonus_K ;
  else if (Typ1()->Ausdauer() == "ak"|| Typ2()->Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  int nap = ap + nab + bo_Au() ;
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

// was bedeutet denn das? 
// get_Abwehr_Resistenz_Zaubern
// steigert und gibt Kosten zurück
int Abenteurer::get_ab_re_za(const ResistenzUndCo::was_t was)
{
  int alter_wert, max_wert;
  int kosten;
  int grad=Grad();
  // diese Anweisung finde ich gewagt!
  if(reduzieren) grad=--grad;

  if(grad==0) kosten=0;
  else switch (was)
  { case ResistenzUndCo::eAbwehr:
      max_wert = Datenbank.GradAnstieg.get_MaxAbwehr(grad);
      alter_wert = Abwehr_wert(); 
      kosten   = Datenbank.GradAnstieg.get_Abwehr_Kosten(alter_wert+1);
      if(reduzieren) kosten = Datenbank.GradAnstieg.get_Abwehr_Kosten(alter_wert);
      break;
    case ResistenzUndCo::eResistenz:
      max_wert = Datenbank.GradAnstieg.get_MaxResistenz(grad);
      alter_wert = Resistenz(); 
      kosten   = Datenbank.GradAnstieg.get_Resistenz_Kosten(alter_wert+1);
      if(reduzieren) kosten = Datenbank.GradAnstieg.get_Resistenz_Kosten(alter_wert);
      break;
    case ResistenzUndCo::eZaubern:
      if (is_mage())
       { 
         max_wert = Datenbank.GradAnstieg.get_MaxZauber(grad);
         alter_wert = Zaubern_wert(); 
         kosten   = Datenbank.GradAnstieg.get_Zauber_Kosten(alter_wert+1);
         if(reduzieren) kosten = Datenbank.GradAnstieg.get_Zauber_Kosten(alter_wert);
       } 
      else return 0;
      break;
    default: assert(!"never get here");
  }
  if(!kosten) 
  { Ausgabe(Ausgabe::Error,"Minimaler Erfogswert erreicht");
    return 0;
  }

  if (alter_wert >= max_wert && !reduzieren)
  { Ausgabe(Ausgabe::Error,"Für Grad "+itos(Grad())+" ist der Maximalwert erreicht!") ;
    return 0;
  }

  else if(!reduzieren)
   { // hier stand eAusdauer ... was ist sinnvoller - oder?
     if (!steigern_usp(kosten,was)) return 0;
     addGFP(kosten);
     if      (was==ResistenzUndCo::eAbwehr)    setAbwehr_wert(alter_wert+1);
     else if (was==ResistenzUndCo::eResistenz) setResistenz(alter_wert+1);  
     else if (was==ResistenzUndCo::eZaubern)   setZaubern_wert(alter_wert+1);
   }
  else
   {  
     desteigern(kosten);
     if      (was==ResistenzUndCo::eAbwehr)    setAbwehr_wert(alter_wert-1);
     else if (was==ResistenzUndCo::eResistenz) setResistenz(alter_wert-1);  
     else if (was==ResistenzUndCo::eZaubern)   setZaubern_wert(alter_wert-1);
   }
  return kosten;
}

int Abenteurer::get_ab_re_za(const MBEmlt &MBE)
{ assert (MBE->What()==MidgardBasicElement::RESISTENZ_UND_CO);
  return get_ab_re_za(MBE->getHandle<ResistenzUndCo>()->WasIstEs());
}

bool Abenteurer::eigenschaften_steigern_erlaubt() const
{ return (Grad() > get_Grad_Basiswerte());
}

void Abenteurer::eigenschaften_steigern(int wurf)
{
  if(!eigenschaften_steigern_erlaubt())
   {Ausgabe(Ausgabe::Error,"Für Grad "+itos(get_Grad_Basiswerte())+" wurde schon gewürfelt");
    return;
   }
  // Erhöhen der Schicksalsgunst
  { int n=Datenbank.GradAnstieg.get_Schicksalsgunst(Grad());
    if(Spezies()->Name()=="Halbling") n+=2;
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
  else if( z==100) { was="Aussehen"; add_Au(erh); }

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

bool Abenteurer::steigere(MBEmlt &MBE)
{
  if ( MBE->Erfolgswert() >= (*MBE)->MaxErfolgswert(*this))
  { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Maximal möglicher Erfolgswert ("+itos((*MBE)->MaxErfolgswert(*this))+") erreicht");
    return false; }
  if(wie_steigern==ws_Unterweisung)
  { if( ((*MBE).What()==MidgardBasicElement::FERTIGKEIT &&
            MBE->Erfolgswert() >= cH_Fertigkeit(MBE->getMBE())->MaxUnterweisung()) ||
           ((*MBE).What()==MidgardBasicElement::SPRACHE &&
            MBE->Erfolgswert() >= cH_Fertigkeit("Sprache")->MaxUnterweisung()) ||
           ((*MBE).What()==MidgardBasicElement::SCHRIFT &&
            MBE->Erfolgswert() >= cH_Fertigkeit("Schreiben")->MaxUnterweisung())
          )
    { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Weitere Steigerung des Erfolgswertes ist NICHT mit Unterweisung möglich.");
      return false;
    }
  }      
  int stufen=1;
  int steigerkosten=MBE->Steigern(*this);
  if (!steigern_usp(steigerkosten,MBE,stufen)) return false;
  addGFP(steigerkosten); 
  MBE->addErfolgswert(stufen);
  return true;
}


void Abenteurer::reduziere(MBEmlt &MBE)
{ desteigern(MBE->Reduzieren(*this));
  MBE->addErfolgswert(-1);
}

// 2do: Aus Liste löschen?
void Abenteurer::verlerne(MBEmlt &MBE)
{ desteigern(MBE->Verlernen(*this));  
}

bool Abenteurer::neu_lernen(MBEmlt &MBE, int bonus)
{
 if(((*MBE).What()==MidgardBasicElement::FERTIGKEIT 
   ||  (*MBE).What()==MidgardBasicElement::WAFFE)
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
  { if (wie_steigern!=ws_Unterweisung)
     { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Neue Fertigkeiten, Waffen, Sprachen und Schriften können nur durch 'Unterweisung' gelernt werden");
       return false;
     }
  }   
 else // ==> (*MBE).What()==MidgardBasicElement::ZAUBER
  {
    // Nicht alle Abenteurerklassen können Zauber auch mit Praxispunkten lernen
    if(wie_steigern==ws_Praxispunkte)
      { if(!Typ1()->SpruecheMitPP() && !Typ2()->SpruecheMitPP() )
           { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Neue Zaubersprüche können von "+Typ1()->Name(Geschlecht())
                     +" nicht durch Praxispunkte gelernt werden");
             return false;
           }
        if((*MBE)->Standard__(*this)!="G")
           { Ausgabe(Ausgabe::Error,(*MBE)->Name()+": Nur Grundzauber können von "+Typ1()->Name(Geschlecht())
                     +" mit Praxispunkten gelernt werden");
             return false;
           }
      }
  }
 int kosten=(*MBE)->Kosten(*this);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( (*MBE).What()==MidgardBasicElement::ZAUBER && wie_steigern==ws_Spruchrolle) 
      kosten/=10;
 /////////////////////////////////////////////////////////////////////////
 
 int dummy=1;
 // Lernern neuer Sprache mit PP
 if((*MBE).What()==MidgardBasicElement::SPRACHE 
       && wie_steigern==ws_Praxispunkte)
 { set_lernzeit(40,MBE); // tatsächlich???
   // hmmm
   if((*MBE)->Grundfertigkeit(*this))
     MBE->setErfolgswert(9);
   else MBE->setErfolgswert(7);
   return true;
 }
 if (!steigern_usp(kosten,MBE,dummy)) return false;

 addGFP(kosten);
     
  // Lernen mit Spruchrolle: ///////////////////////////////////////////////
  if((*MBE).What()==MidgardBasicElement::ZAUBER && wie_steigern==ws_Spruchrolle)
  {  if(wie_steigern_variante!=wsv_SpruchrolleAlways &&
         !cH_Zauber(MBE->getMBE())->spruchrolle_wuerfeln(*this,bonus))
       return false;
     addGFP(kosten);
     list_Gelernt_von_Spruchrolle.push_back(MBE->getMBE()->Name());
  }
  return true;
}

void Abenteurer::desteigern(unsigned kosten)
{ int gold_k=0,ep_k=0;
  if (fpanteil) switch (wie_steigern)
  { case ws_Praxispunkte: 
      ep_k=kosten;
      break;
    case ws_Selbststudium:
      ep_k=kosten*1.33;
      break;
    case ws_Spruchrolle:
      ep_k=kosten/10;
      break;
    case ws_Unterweisung:
      gold_k = gold_kosten(kosten);
      ep_k = ep_kosten(kosten);
      break;
    default: assert(!"desteigern: wie denn das?");
  }
  if(!optionen.HausregelCheck(Optionen::Gold).active) gold_k*=10;
  set_lernzeit(-ep_k,MBEmlt(0));
  addGold(gold_k);
  addAEP(ep_k);   
  addGFP(-kosten);
}

bool Abenteurer::steigern_usp(int &kosten, ResistenzUndCo::was_t was)
{ int d=1; 
  MBEmlt mbe=MBEmlt(&*ResistenzUndCo::getMBE(was));
  // EW setzen?
  return steigern_usp(kosten,mbe,d);
}
