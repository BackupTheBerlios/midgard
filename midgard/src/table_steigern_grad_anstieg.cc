// $Id: table_steigern_grad_anstieg.cc,v 1.2 2002/06/14 07:14:08 thoma Exp $
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
#include "table_steigern.hh"
#include <Aux/itos.h>

void table_steigern::on_grad_anstieg_clicked()
{
 radiobutton_steigern->set_active(true);
 int old_grad=hauptfenster->getCWerte().Grad();
 hauptfenster->getWerte().setGrad(hauptfenster->getCDatabase().GradAnstieg.get_Grad(hauptfenster->getCWerte().GFP()));
 get_ausdauer(hauptfenster->getCWerte().Grad());
 while(old_grad<=hauptfenster->getCWerte().Grad())
  {
    get_ab_re_za(Abwehr);
    get_ab_re_za(Resistenz);
    get_ab_re_za(Zaubern);
    get_grundwerte();
    ++old_grad;
  }
}

void table_steigern::on_button_grad_clicked()
{   
  hauptfenster->getWerte().setGrad(hauptfenster->getCDatabase().GradAnstieg.get_Grad(hauptfenster->getCWerte().GFP()));
  zeige_werte();
}
void table_steigern::on_button_grad_ausdauer_clicked()
{   
  get_ausdauer(hauptfenster->getCWerte().Grad());
  zeige_werte();
}
void table_steigern::on_button_grad_abwehr_clicked()
{   
 get_ab_re_za(Abwehr);
}
void table_steigern::on_button_grad_zaubern_clicked()
{   
 get_ab_re_za(Zaubern);
}
void table_steigern::on_button_grad_resistenz_clicked()
{   
 get_ab_re_za(Resistenz);
}
void table_steigern::on_button_grad_basiswerte_clicked()
{   
  get_grundwerte();
  zeige_werte();
}


void table_steigern::get_grundwerte()
{
  if(hauptfenster->getCWerte().Grad() <= hauptfenster->getCWerte().get_Grad_Basiswerte()) 
   {
      hauptfenster->set_status("Für Grad "+itos(hauptfenster->getCWerte().get_Grad_Basiswerte())+" wurde schon gewürfelt");
      return;
   }
  // Erhöhen der Schicksalsgunst
  { int n=hauptfenster->getCDatabase().GradAnstieg.get_Schicksalsgunst(hauptfenster->getCWerte().Grad());
    if(hauptfenster->getCWerte().Spezies()->Name()=="Halbling") n=n+2;
    hauptfenster->getWerte().add_SG(n);
  }


  int z=hauptfenster->random.integer(1,100);
  std::string stinfo="Beim Würfeln zur Erhöhung einer Eigenschaft\nfür Grad "
      + itos(hauptfenster->getCWerte().get_Grad_Basiswerte()+1) + " wurde eine ";
  stinfo += itos(z);
  stinfo +=" gewürfelt ==> ";
  std::string was = "keine Erhöhung";

  int erh = hauptfenster->random.integer(1,6)+1;
  int awko=hauptfenster->getCWerte().Ko(); //alter_wert;
  int aapb = hauptfenster->getCWerte().bo_Au(); // alter Wert
  if( 76<=z && z>=78 ) { was="Stärke";           hauptfenster->getWerte().add_St(erh); }
  if( 79<=z && z>=81 ) { was="Geschicklichkeit"; hauptfenster->getWerte().add_Gs(erh); }
  if( 82<=z && z>=84 ) { was="Gewandheit"; hauptfenster->getWerte().add_Gw(erh); }
  if( 85<=z && z>=87 ) { was="Konstitution"; hauptfenster->getWerte().add_Ko(erh); }
  if( 88<=z && z>=90 ) { was="Intelligenz"; hauptfenster->getWerte().add_In(erh); }
  if( 91<=z && z>=93 ) { was="Zaubertalent"; hauptfenster->getWerte().add_Zt(erh); }
  if( 94<=z && z>=95 ) { was="Selbstbeherrschung"; hauptfenster->getWerte().add_Sb(erh); }
  if( 96<=z && z>=97 ) { was="Willenskraft"; hauptfenster->getWerte().add_Wk(erh); }
  if( 99<=z && z>=99 ) { was="persönliche Ausstrahlung"; hauptfenster->getWerte().add_pA(erh); }
  if (z==100)          { was="Aussehn"; hauptfenster->getWerte().add_Au(erh); }

  {
   //Setzen von abgeleiteten Werten, die durch eine Steigerung 
   //bertoffen sein könnten:
   hauptfenster->getWerte().setSinn("Sechster Sinn",hauptfenster->getCWerte().Zt()/25);
//   hauptfenster->getCWerte().setRaufen((hauptfenster->getCWerte().St()+hauptfenster->getCWerte().Gw())/20+hauptfenster->getCWerte().bo_An() );
   if(was=="Konstitution" && (awko/10 != hauptfenster->getCWerte().Ko()/10))
         hauptfenster->getWerte().setLP(hauptfenster->getCWerte().LP()-awko/10+hauptfenster->getCWerte().Ko()/10);
   if( aapb!=hauptfenster->getCWerte().bo_Au() ) 
      hauptfenster->getWerte().setAP(hauptfenster->getCWerte().AP()-aapb+hauptfenster->getCWerte().bo_Au());
  }


  stinfo += was;
  if (was != "keine Erhöhung" )
    {
       stinfo += " um "+itos(erh)+" erhöht.";
    }
//  InfoFenster->AppendShow(stinfo,WindowInfo::None);
  hauptfenster->set_status(stinfo);
  hauptfenster->getWerte().set_Grad_Basiswerte(1+hauptfenster->getCWerte().get_Grad_Basiswerte());
  zeige_werte();
}

void table_steigern::get_ausdauer(int grad)
{
   int bonus_K, bonus_aK, bonus_Z;
   int kosten = hauptfenster->getCDatabase().GradAnstieg.get_AP_Kosten(grad);
   if (grad == 1)  { bonus_K =  4, bonus_aK =  3; bonus_Z =  2; }
   if (grad == 2)  { bonus_K =  6, bonus_aK =  4; bonus_Z =  2; }
   if (grad == 3)  { bonus_K =  9, bonus_aK =  6; bonus_Z =  3; }
   if (grad == 4)  { bonus_K = 12, bonus_aK =  8; bonus_Z =  4; }
   if (grad == 5)  { bonus_K = 15, bonus_aK = 10; bonus_Z =  5; }
   if (grad == 6)  { bonus_K = 18, bonus_aK = 12; bonus_Z =  6; }
   if (grad == 7)  { bonus_K = 21, bonus_aK = 14; bonus_Z =  7; }
   if (grad == 8)  { bonus_K = 24, bonus_aK = 16; bonus_Z =  8; }
   if (grad == 9)  { bonus_K = 27, bonus_aK = 18; bonus_Z =  9; }
   if (grad ==10)  { bonus_K = 30, bonus_aK = 20; bonus_Z = 10; }
   if (grad >=11)  { bonus_K = 30, bonus_aK = 20; bonus_Z = 10; }
   if (!steigern_usp(kosten,0,Ausdauer)) return;
   hauptfenster->getWerte().addGFP(kosten);
   int ap=0;
   for (int i=0;i<grad;++i) ap += hauptfenster->random.integer(1,6);

  int nab, nap;
  if      (hauptfenster->getCChar().CTyp1()->Ausdauer() == "k" || hauptfenster->getCChar().CTyp2()->Ausdauer() == "k")  nab = bonus_K ;
  else if (hauptfenster->getCChar().CTyp1()->Ausdauer() == "ak"|| hauptfenster->getCChar().CTyp2()->Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  nap = ap + nab + hauptfenster->getCWerte().bo_Au() ;
  int nspez = hauptfenster->getCWerte().Grad()*hauptfenster->getCWerte().Spezies()->AP_GradFak();
  nap += nspez;
  std::string stinfo="Ausdauerpunkte für Grad "+itos(hauptfenster->getCWerte().Grad())+": "
   +"Gewürfelt("+itos(ap)+") + Bonus für Typ("+itos(nab)
   +") + Persönlichen Bonus("+itos(hauptfenster->getCWerte().bo_Au())+") 
   + Spezies-Bonus("+itos(nspez)+")\n";
  hauptfenster->set_status(stinfo);
//  InfoFenster->AppendShow(stinfo,WindowInfo::None);
   // Für alle ist die AP-anzahel mind. = Grad
  if (hauptfenster->getCWerte().AP()<hauptfenster->getCWerte().Grad()) hauptfenster->getWerte().setAP(hauptfenster->getCWerte().Grad()); 
   // Neue AP höher als alte?
  if (nap>hauptfenster->getCWerte().AP())  hauptfenster->getWerte().setAP(nap)  ;
  hauptfenster->getWerte().addSteigertage(Grad_anstieg::AP_Maximum_Tage);
}

void table_steigern::get_ab_re_za(e_was_steigern was,bool verschenke_pp=false)
{
  int alter_wert, max_wert;
  int kosten;
  int grad=hauptfenster->getCWerte().Grad();
  if(!radiobutton_steigern->get_active()) grad=--grad;
  if      (was==Abwehr)
    { 
      max_wert = hauptfenster->getCDatabase().GradAnstieg.get_MaxAbwehr(grad); 
      alter_wert = hauptfenster->getCWerte().Abwehr_wert(); 
      kosten   = hauptfenster->getCDatabase().GradAnstieg.get_Abwehr_Kosten(alter_wert+1);
    } 
  else if (was==Resistenz) 
    { 
      max_wert = hauptfenster->getCDatabase().GradAnstieg.get_MaxResistenz(grad);
      alter_wert = hauptfenster->getCWerte().Resistenz(); 
      kosten   = hauptfenster->getCDatabase().GradAnstieg.get_Resistenz_Kosten(alter_wert+1);
    } 
  else if (was==Zaubern) 
    { 
      if ( hauptfenster->getCChar().is_mage()) 
       { 
         max_wert = hauptfenster->getCDatabase().GradAnstieg.get_MaxZauber(grad);
         alter_wert = hauptfenster->getCWerte().Zaubern_wert(); 
         kosten   = hauptfenster->getCDatabase().GradAnstieg.get_Zauber_Kosten(alter_wert+1);
       } 
      else return; 
    }
  else assert(!"never get here");
  if (alter_wert >= max_wert && radiobutton_steigern->get_active())
      { hauptfenster->set_status("Für Grad "+itos(hauptfenster->getCWerte().Grad())+" ist der Maximalwert erreicht!") ;
        return;}

  if(radiobutton_steigern->get_active())
   {
     if(!steigern_usp(kosten,0,was,verschenke_pp) && !verschenke_pp) return; 
     hauptfenster->getWerte().addGFP(kosten);
     if      (was==Abwehr)    hauptfenster->getWerte().setAbwehr_wert(alter_wert+1);
     else if (was==Resistenz) hauptfenster->getWerte().setResistenz(alter_wert+1); 
     else if (was==Zaubern)   hauptfenster->getWerte().setZaubern_wert(alter_wert+1); 
   }
  else
   {
     if (checkbutton_EP_Geld->get_active()) desteigern(kosten);
     set_lernzeit(-kosten);
     hauptfenster->getWerte().addGFP(-kosten);
     if      (was==Abwehr)    hauptfenster->getWerte().setAbwehr_wert(alter_wert-1);
     else if (was==Resistenz) hauptfenster->getWerte().setResistenz(alter_wert-1); 
     else if (was==Zaubern)   hauptfenster->getWerte().setZaubern_wert(alter_wert-1); 
   }
 zeige_werte();
}
