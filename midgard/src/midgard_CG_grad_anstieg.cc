// $Id: midgard_CG_grad_anstieg.cc,v 1.60 2002/05/22 17:00:45 thoma Exp $
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
#include <Aux/itos.h>

gint midgard_CG::on_button_kurz_steigern_release_event(GdkEventButton *event)
{
  if (event->button==1) 
   { menu_gradanstieg->popup(event->button,event->time);
     return true;
   }
  if (event->button==3) 
   {
    on_grad_anstieg_clicked();
    return false;
   }
 return false;
}


void midgard_CG::on_grad_anstieg_clicked()
{
 radiobutton_steigern->set_active(true);
 int old_grad=getCWerte().Grad();
 getWerte().setGrad(Database.GradAnstieg.get_Grad(getCWerte().GFP()));
 get_ausdauer(getCWerte().Grad());
 while(old_grad<=getCWerte().Grad())
  {
    get_ab_re_za(Abwehr);
    get_ab_re_za(Resistenz);
    get_ab_re_za(Zaubern);
    get_grundwerte();
    ++old_grad;
  }
 zeige_werte();
}

void midgard_CG::on_button_grad_clicked()
{   
  getWerte().setGrad(Database.GradAnstieg.get_Grad(getCWerte().GFP()));
  zeige_werte();
}
void midgard_CG::on_button_grad_ausdauer_clicked()
{   
  get_ausdauer(getCWerte().Grad());
  zeige_werte();
}
void midgard_CG::on_button_grad_abwehr_clicked()
{   
 get_ab_re_za(Abwehr);
 zeige_werte();
}
void midgard_CG::on_button_grad_zaubern_clicked()
{   
 get_ab_re_za(Zaubern);
 zeige_werte();
}
void midgard_CG::on_button_grad_resistenz_clicked()
{   
 get_ab_re_za(Resistenz);
 zeige_werte();
}
void midgard_CG::on_button_grad_basiswerte_clicked()
{   
  get_grundwerte();
  zeige_werte();
}


void midgard_CG::get_grundwerte()
{
  if(getCWerte().Grad() <= getCWerte().get_Grad_Basiswerte()) 
   {
      set_status("Für Grad "+itos(getCWerte().get_Grad_Basiswerte())+" wurde schon gewürfelt");
      return;
   }
  // Erhöhen der Schicksalsgunst
  { int n=Database.GradAnstieg.get_Schicksalsgunst(getCWerte().Grad());
    if(getCWerte().Spezies()->Name()=="Halbling") n=n+2;
    getWerte().add_SG(n);
  }


  int z=random.integer(1,100);
  std::string stinfo="Beim Würfeln zur Erhöhung einer Eigenschaft\nfür Grad "
      + itos(getCWerte().get_Grad_Basiswerte()+1) + " wurde eine ";
  stinfo += itos(z);
  stinfo +=" gewürfelt ==> ";
  std::string was = "keine Erhöhung";

  int erh = random.integer(1,6)+1;
  int awko=getCWerte().Ko(); //alter_wert;
  int aapb = getCWerte().bo_Au(); // alter Wert
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
   getWerte().setSinn("Sechster Sinn",getCWerte().Zt()/25);
//   getCWerte().setRaufen((getCWerte().St()+getCWerte().Gw())/20+getCWerte().bo_An() );
   if(was=="Konstitution" && (awko/10 != getCWerte().Ko()/10))
         getWerte().setLP(getCWerte().LP()-awko/10+getCWerte().Ko()/10);
   if( aapb!=getCWerte().bo_Au() ) 
      getWerte().setAP(getCWerte().AP()-aapb+getCWerte().bo_Au());
  }


  stinfo += was;
  if (was != "keine Erhöhung" )
    {
       stinfo += " um "+itos(erh)+" erhöht.";
    }
//  InfoFenster->AppendShow(stinfo,WindowInfo::None);
  set_status(stinfo);
  getWerte().set_Grad_Basiswerte(1+getCWerte().get_Grad_Basiswerte());
  zeige_werte();
}

void midgard_CG::get_ausdauer(int grad)
{
   int bonus_K, bonus_aK, bonus_Z;
   int kosten = Database.GradAnstieg.get_AP_Kosten(grad);
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
   getWerte().addGFP(kosten);
   int ap=0;
   for (int i=0;i<grad;++i) ap += random.integer(1,6);

  int nab, nap;
  if      (Char.CTyp1()->Ausdauer() == "k" || Char.CTyp2()->Ausdauer() == "k")  nab = bonus_K ;
  else if (Char.CTyp1()->Ausdauer() == "ak"|| Char.CTyp2()->Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  nap = ap + nab + getCWerte().bo_Au() ;
  int nspez = getCWerte().Grad()*getCWerte().Spezies()->AP_GradFak();
  nap += nspez;
  std::string stinfo="Ausdauerpunkte für Grad "+itos(getCWerte().Grad())+": "
   +"Gewürfelt("+itos(ap)+") + Bonus für Typ("+itos(nab)
   +") + Persönlichen Bonus("+itos(getCWerte().bo_Au())+") 
   + Spezies-Bonus("+itos(nspez)+")\n";
  set_status(stinfo);
//  InfoFenster->AppendShow(stinfo,WindowInfo::None);
   // Für alle ist die AP-anzahel mind. = Grad
  if (getCWerte().AP()<getCWerte().Grad()) getWerte().setAP(getCWerte().Grad()); 
   // Neue AP höher als alte?
  if (nap>getCWerte().AP())  getWerte().setAP(nap)  ;
  getWerte().addSteigertage(Grad_anstieg::AP_Maximum_Tage);
}

void midgard_CG::get_ab_re_za(e_was_steigern was)
{
  int alter_wert, max_wert;
  int kosten;
  int grad=getCWerte().Grad();
  if(!radiobutton_steigern->get_active()) grad=--grad;
  if      (was==Abwehr)
    { 
      max_wert = Database.GradAnstieg.get_MaxAbwehr(grad); 
      alter_wert = getCWerte().Abwehr_wert(); 
      kosten   = Database.GradAnstieg.get_Abwehr_Kosten(alter_wert+1);
    } 
  else if (was==Resistenz) 
    { 
      max_wert = Database.GradAnstieg.get_MaxResistenz(grad);
      alter_wert = getCWerte().Resistenz(); 
      kosten   = Database.GradAnstieg.get_Resistenz_Kosten(alter_wert+1);
    } 
  else if (was==Zaubern) 
    { 
      if ( Char.is_mage()) 
       { 
         max_wert = Database.GradAnstieg.get_MaxZauber(grad);
         alter_wert = getCWerte().Zaubern_wert(); 
         kosten   = Database.GradAnstieg.get_Zauber_Kosten(alter_wert+1);
       } 
      else return; 
    }
  else abort();
  if (alter_wert >= max_wert && radiobutton_steigern->get_active())
      { set_status("Für Grad "+itos(getCWerte().Grad())+" ist der Maximalwert erreicht!") ;
        return;}

  if(radiobutton_steigern->get_active())
   {
     steigern_usp(kosten,0,was); //Wg. Geld und Lerntagen 
     getWerte().addGFP(kosten);
     if      (was==Abwehr)    getWerte().setAbwehr_wert(alter_wert+1);
     else if (was==Resistenz) getWerte().setResistenz(alter_wert+1); 
     else if (was==Zaubern)   getWerte().setZaubern_wert(alter_wert+1); 
   }
  else
   {
     if (checkbutton_EP_Geld->get_active()) desteigern(kosten);
     set_lernzeit(-kosten);
//     steigern_usp(-kosten,0,was);
     getWerte().addGFP(-kosten);
     if      (was==Abwehr)    getWerte().setAbwehr_wert(alter_wert-1);
     else if (was==Resistenz) getWerte().setResistenz(alter_wert-1); 
     else if (was==Zaubern)   getWerte().setZaubern_wert(alter_wert-1); 
   }
}
