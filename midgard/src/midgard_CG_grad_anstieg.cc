// $Id: midgard_CG_grad_anstieg.cc,v 1.52 2002/02/18 07:01:06 thoma Exp $
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
 int old_grad=Werte.Grad();
 Werte.setGrad(Database.GradAnstieg.get_Grad(Werte.GFP()));
 get_ausdauer(Werte.Grad());
 while(old_grad<=Werte.Grad())
  {
    get_ab_re_za(Abwehr);
    get_ab_re_za(Resistenz);
    get_ab_re_za(Zaubern);
    get_grundwerte();
    ++old_grad;
  }
 zeige_werte(Werte);
}

void midgard_CG::on_button_grad_clicked()
{   
  Werte.setGrad(Database.GradAnstieg.get_Grad(Werte.GFP()));
  zeige_werte(Werte);
}
void midgard_CG::on_button_grad_ausdauer_clicked()
{   
  get_ausdauer(Werte.Grad());
  zeige_werte(Werte);
}
void midgard_CG::on_button_grad_abwehr_clicked()
{   
 get_ab_re_za(Abwehr);
 zeige_werte(Werte);
}
void midgard_CG::on_button_grad_zaubern_clicked()
{   
 get_ab_re_za(Zaubern);
 zeige_werte(Werte);
}
void midgard_CG::on_button_grad_resistenz_clicked()
{   
 get_ab_re_za(Resistenz);
 zeige_werte(Werte);
}
void midgard_CG::on_button_grad_basiswerte_clicked()
{   
  get_grundwerte();
  zeige_werte(Werte);
}


void midgard_CG::get_grundwerte()
{
  if(Werte.Grad() <= Database.GradAnstieg.get_Grad_Basiswerte()) 
   {
      InfoFenster->AppendShow("Für Grad "+itos(Database.GradAnstieg.get_Grad_Basiswerte())+" wurde schon gewürfelt");
      return;
   }
  // Erhöhen der Schicksalsgunst
  { int n=Database.GradAnstieg.get_Schicksalsgunst(Werte.Grad());
    if(Werte.Spezies()->Name()=="Halbling") n=n+2;
    Werte.add_SG(n);
  }


  int z=random.integer(1,100);
  std::string stinfo="Beim Würfeln zur Erhöhung einer Eigenschaft\nfür Grad "
      + itos(Database.GradAnstieg.get_Grad_Basiswerte()+1) + " wurde eine ";
  stinfo += itos(z);
  stinfo +=" gewürfelt --> ";
  std::string was = "keine Erhöhung";

  int erh = random.integer(1,6)+1;
  int awko=Werte.Ko(); //alter_wert;
  int aapb = Werte.bo_Au(); // alter Wert
  if( 76<=z && z>=78 ) { was="Stärke";           Werte.add_St(erh); }
  if( 79<=z && z>=81 ) { was="Geschicklichkeit"; Werte.add_Gs(erh); }
  if( 82<=z && z>=84 ) { was="Gewandheit"; Werte.add_Gw(erh); }
  if( 85<=z && z>=87 ) { was="Konstitution"; Werte.add_Ko(erh); }
  if( 88<=z && z>=90 ) { was="Intelligenz"; Werte.add_In(erh); }
  if( 91<=z && z>=93 ) { was="Zaubertalent"; Werte.add_Zt(erh); }
  if( 94<=z && z>=95 ) { was="Selbstbeherrschung"; Werte.add_Sb(erh); }
  if( 96<=z && z>=97 ) { was="Willenskraft"; Werte.add_Wk(erh); }
  if( 99<=z && z>=99 ) { was="persönliche Ausstrahlung"; Werte.add_pA(erh); }
  if (z==100)          { was="Aussehn"; Werte.add_Au(erh); }

  {
   //Setzen von abgeleiteten Werten, die durch eine Steigerung 
   //bertoffen sein könnten:
   Werte.setSinn("Sechster Sinn",Werte.Zt()/25);
//   Werte.setRaufen((Werte.St()+Werte.Gw())/20+Werte.bo_An() );
   if(was=="Konstitution" && (awko/10 != Werte.Ko()/10))
         Werte.setLP(Werte.LP()-awko/10+Werte.Ko()/10);
   if( aapb!=Werte.bo_Au() ) 
      Werte.setAP(Werte.AP()-aapb+Werte.bo_Au());
  }


  stinfo += was;
  if (was != "keine Erhöhung" )
    {
       stinfo += " um "; stinfo += itos(erh); stinfo+=" erhöht.\n";
    }
  InfoFenster->AppendShow(stinfo,WindowInfo::None);
  Database.GradAnstieg.set_Grad_Basiswerte(1+Database.GradAnstieg.get_Grad_Basiswerte());
  zeige_werte(Werte);
}

void midgard_CG::get_ausdauer(int grad)
{
   int bonus_K, bonus_aK, bonus_Z;
   int kosten = Database.GradAnstieg.get_Resistenz_Kosten(grad);
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
   Werte.addGFP(kosten);
   int ap=0;
   for (int i=0;i<grad;++i) ap += random.integer(1,6);

  int nab, nap;
  if      (Typ[0]->Ausdauer() == "k" || Typ[1]->Ausdauer() == "k")  nab = bonus_K ;
  else if (Typ[0]->Ausdauer() == "ak"|| Typ[1]->Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  nap = ap + nab + Werte.bo_Au() ;
  int nspez = Werte.Grad()*Werte.Spezies()->AP_Grad();
  nap += nspez;
//  std::cout << "Ausdauerpunkte: "<<ap<<" + " <<nab<<" + "<<Werte.bo()_au<<" + "<<nspez<<" = "<<nap<<"\n";
  std::string stinfo="Für Grad "+itos(Werte.Grad())+":\n";
   stinfo+="Ausdauerpunkte: Gewürfelt + Bonus für Typ + Persönlichen Bonus + Spezies-Bonus\n";
   stinfo+=itos(ap);stinfo+="+";stinfo+=itos(nab);
   stinfo+="+";stinfo+=itos(Werte.bo_Au());stinfo+="=";stinfo+=itos(nap);
  InfoFenster->AppendShow(stinfo,WindowInfo::None);
   // Für alle ist die AP-anzahel mind. = Grad
  if (Werte.AP()<Werte.Grad()) Werte.setAP(Werte.Grad()); 
   // Neue AP höher als alte?
  if (nap>Werte.AP())  Werte.setAP(nap)  ;

  Werte.addSteigertage(28);
}

void midgard_CG::get_ab_re_za(e_was_steigern was)
{
  int alter_wert, max_wert;
  int kosten;
  int grad=Werte.Grad();
  if(!radiobutton_steigern->get_active()) grad=--grad;
  if      (was==Abwehr)
    { 
      max_wert = Database.GradAnstieg.get_Abwehr(grad); 
      kosten   = Database.GradAnstieg.get_Abwehr_Kosten(grad+1);
      alter_wert = Werte.Abwehr_wert(); 
    } 
  else if (was==Resistenz) 
    { 
      max_wert = Database.GradAnstieg.get_Resistenz(grad);
      kosten   = Database.GradAnstieg.get_Resistenz_Kosten(grad+1);
      alter_wert = Werte.Resistenz(); 
    } 
  else if (was==Zaubern) 
    { 
      if ( Typ[0]->Zaubern()  == "z" || Typ[0]->Zaubern()  == "j" ||
           Typ[1]->Zaubern() == "z" || Typ[1]->Zaubern() == "j" ) 
       { 
         max_wert = Database.GradAnstieg.get_Zauber(grad);
         kosten   = Database.GradAnstieg.get_Zauber_Kosten(grad+1);
         alter_wert = Werte.Zaubern_wert(); 
       } 
      else return; 
    }
  else abort();
  if (alter_wert >= max_wert && radiobutton_steigern->get_active())
      { InfoFenster->AppendShow("Für Grad "+itos(Werte.Grad())+" ist der Maximalwert erreicht!") ;
        return;}

  if(radiobutton_steigern->get_active())
   {
     steigern_usp(kosten,0,was); //Wg. Geld und Lerntagen 
     Werte.addGFP(kosten);
     if      (was==Abwehr)    Werte.setAbwehr_wert(alter_wert+1);
     else if (was==Resistenz) Werte.setResistenz(alter_wert+1); 
     else if (was==Zaubern)   Werte.setZaubern_wert(alter_wert+1); 
   }
  else
   {
     if (checkbutton_EP_Geld->get_active()) desteigern(kosten);
     set_lernzeit(-kosten);
//     steigern_usp(-kosten,0,was);
     Werte.addGFP(-kosten);
     if      (was==Abwehr)    Werte.setAbwehr_wert(alter_wert-1);
     else if (was==Resistenz) Werte.setResistenz(alter_wert-1); 
     else if (was==Zaubern)   Werte.setZaubern_wert(alter_wert-1); 
   }
}
