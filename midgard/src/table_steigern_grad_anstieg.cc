// $Id: table_steigern_grad_anstieg.cc,v 1.9 2002/09/25 06:33:02 thoma Exp $
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
#include <Misc/itos.h>

void table_steigern::on_grad_anstieg_clicked()
{
 radiobutton_steigern->set_active(true);
 int old_grad=hauptfenster->getWerte().Grad();
 hauptfenster->getWerte().setGrad(hauptfenster->getCDatabase().GradAnstieg.get_Grad(hauptfenster->getWerte().GFP()));
// get_ausdauer(hauptfenster->getWerte().Grad());

 std::string info;
 hauptfenster->getChar()->get_ausdauer(hauptfenster->getWerte().Grad(),hauptfenster->getCDatabase(),info,
                           get_wie_steigern(),get_bool_steigern());
 hauptfenster->set_status(info);
 while(old_grad<=hauptfenster->getWerte().Grad())
  {
    get_ab_re_za(Enums::eAbwehr);
    get_ab_re_za(Enums::eResistenz);
    get_ab_re_za(Enums::eZaubern);
    int wurf=hauptfenster->random.integer(1,100);
    get_grundwerte(wurf);
    ++old_grad;
  }
}

void table_steigern::on_button_grad_clicked()
{   
  hauptfenster->getWerte().setGrad(hauptfenster->getCDatabase().GradAnstieg.get_Grad(hauptfenster->getWerte().GFP()));
  zeige_werte();
}
void table_steigern::on_button_grad_ausdauer_clicked()
{   
 std::string info;
 hauptfenster->getChar()->get_ausdauer(hauptfenster->getWerte().Grad(),hauptfenster->getCDatabase(),info,get_wie_steigern(),get_bool_steigern());
 hauptfenster->set_status(info);
//  get_ausdauer(hauptfenster->getWerte().Grad());
  zeige_werte();
}
void table_steigern::on_button_grad_abwehr_clicked()
{   
 get_ab_re_za(Enums::eAbwehr);
}
void table_steigern::on_button_grad_zaubern_clicked()
{   
 get_ab_re_za(Enums::eZaubern);
}
void table_steigern::on_button_grad_resistenz_clicked()
{   
 get_ab_re_za(Enums::eResistenz);
}
void table_steigern::on_button_grad_basiswerte_clicked()
{   
  int wurf=hauptfenster->random.integer(1,100);
  get_grundwerte(wurf);
  zeige_werte();
}

gint table_steigern::on_button_grad_basiswerte_button_release_event(GdkEventButton *ev)
{
  if(hauptfenster->getWerte().Grad() <= hauptfenster->getWerte().get_Grad_Basiswerte()) 
   { hauptfenster->set_status("Für Grad "+itos(hauptfenster->getWerte().get_Grad_Basiswerte())+" wurde schon gewürfelt");
      return true;   }
  if (ev->button == 1) on_button_grad_basiswerte_clicked();
  if (ev->button == 3) 
   {
     spinbutton_eigenschaften_grad_anstieg->show();
     spinbutton_eigenschaften_grad_anstieg->grab_focus();
     spinbutton_eigenschaften_grad_anstieg->select_region(0,-1);
   }
  return true;
}

void table_steigern::on_spinbutton_eigenschaften_grad_anstieg_activate()
{
  spinbutton_eigenschaften_grad_anstieg->update();
  spinbutton_eigenschaften_grad_anstieg->hide();
  int wurf=spinbutton_eigenschaften_grad_anstieg->get_value_as_int();
  get_grundwerte(wurf);
  zeige_werte();
}


void table_steigern::get_grundwerte(int wurf)
{
  // Erhöhen der Schicksalsgunst
  { int n=hauptfenster->getCDatabase().GradAnstieg.get_Schicksalsgunst(hauptfenster->getWerte().Grad());
    if(hauptfenster->getWerte().Spezies()->Name()=="Halbling") n=n+2;
    hauptfenster->getWerte().add_SG(n);
  }


  int z=wurf;  std::string stinfo="Beim Würfeln zur Erhöhung einer Eigenschaft\nfür Grad "
      + itos(hauptfenster->getWerte().get_Grad_Basiswerte()+1) + " wurde eine ";
  stinfo += itos(wurf);
  stinfo +=" gewürfelt ==> ";
  std::string was = "keine Erhöhung";

  int erh = hauptfenster->random.integer(1,6)+1;
  int awko=hauptfenster->getWerte().Ko(); //alter_wert;
  int aapb = hauptfenster->getWerte().bo_Au(); // alter Wert
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
   hauptfenster->getWerte().setSinn("Sechster Sinn",hauptfenster->getWerte().Zt()/25);
//   hauptfenster->getWerte().setRaufen((hauptfenster->getWerte().St()+hauptfenster->getWerte().Gw())/20+hauptfenster->getWerte().bo_An() );
   if(was=="Konstitution" && (awko/10 != hauptfenster->getWerte().Ko()/10))
         hauptfenster->getWerte().setLP(hauptfenster->getWerte().LP()-awko/10+hauptfenster->getWerte().Ko()/10);
   if( aapb!=hauptfenster->getWerte().bo_Au() ) 
      hauptfenster->getWerte().setAP(hauptfenster->getWerte().AP()-aapb+hauptfenster->getWerte().bo_Au());
  }


  stinfo += was;
  if (was != "keine Erhöhung" )
    {
       stinfo += " um "+itos(erh)+" erhöht.";
    }
//  InfoFenster->AppendShow(stinfo,WindowInfo::None);
  hauptfenster->set_status(stinfo);
  hauptfenster->getWerte().set_Grad_Basiswerte(1+hauptfenster->getWerte().get_Grad_Basiswerte());
  zeige_werte();
}

#if 0
void table_steigern::get_ausdauer(int grad)
{
   int bonus_K, bonus_aK, bonus_Z;
   int kosten = hauptfenster->getCDatabase().GradAnstieg.get_AP_Kosten(grad);
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
   int dummy=1;
   if (!steigern_usp(kosten,0,dummy,Ausdauer)) return;
   hauptfenster->getWerte().addGFP(kosten);
   int ap=0;
   for (int i=0;i<grad;++i) ap += hauptfenster->random.integer(1,6);

  int nab, nap;
  if      (hauptfenster->getChar()->Typ1()->Ausdauer() == "k" || hauptfenster->getChar()->Typ2()->Ausdauer() == "k")  nab = bonus_K ;
  else if (hauptfenster->getChar()->Typ1()->Ausdauer() == "ak"|| hauptfenster->getChar()->Typ2()->Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  nap = ap + nab + hauptfenster->getWerte().bo_Au() ;
  int nspez = hauptfenster->getWerte().Grad()*hauptfenster->getWerte().Spezies()->AP_GradFak();
  nap += nspez;
  std::string stinfo="Ausdauerpunkte für Grad "+itos(hauptfenster->getWerte().Grad())+": "
   +"Gewürfelt("+itos(ap)+") + Bonus für Typ("+itos(nab)
   +") + Persönlichen Bonus("+itos(hauptfenster->getWerte().bo_Au())+") 
   + Spezies-Bonus("+itos(nspez)+")\n";
  hauptfenster->set_status(stinfo);
   // Für alle ist die AP-anzahel mind. = Grad
  if (hauptfenster->getWerte().AP()<hauptfenster->getWerte().Grad()) hauptfenster->getWerte().setAP(hauptfenster->getWerte().Grad()); 
   // Neue AP höher als alte?
  if (nap>hauptfenster->getWerte().AP())  hauptfenster->getWerte().setAP(nap)  ;
}
#endif

void table_steigern::get_ab_re_za(Enums::e_was_steigern was)
{
  std::string info;
  const bool bsteigern=radiobutton_steigern->get_active();
  hauptfenster->getChar()->get_ab_re_za(was,get_wie_steigern(),bsteigern,
                                        hauptfenster->getCDatabase(),info,get_bool_steigern());
  hauptfenster->set_status(info);
#if 0
  int alter_wert, max_wert;
  int kosten;
  int grad=hauptfenster->getWerte().Grad();
  if(!radiobutton_steigern->get_active()) grad=--grad;
  if(grad==0) grad=1;
  if      (was==Abwehr)
    { 
      max_wert = hauptfenster->getCDatabase().GradAnstieg.get_MaxAbwehr(grad); 
      alter_wert = hauptfenster->getWerte().Abwehr_wert(); 
      kosten   = hauptfenster->getCDatabase().GradAnstieg.get_Abwehr_Kosten(alter_wert+1);
    } 
  else if (was==Resistenz) 
    { 
      max_wert = hauptfenster->getCDatabase().GradAnstieg.get_MaxResistenz(grad);
      alter_wert = hauptfenster->getWerte().Resistenz(); 
      kosten   = hauptfenster->getCDatabase().GradAnstieg.get_Resistenz_Kosten(alter_wert+1);
    } 
  else if (was==Zaubern) 
    { 
      if ( hauptfenster->getChar()->is_mage()) 
       { 
         max_wert = hauptfenster->getCDatabase().GradAnstieg.get_MaxZauber(grad);
         alter_wert = hauptfenster->getWerte().Zaubern_wert(); 
         kosten   = hauptfenster->getCDatabase().GradAnstieg.get_Zauber_Kosten(alter_wert+1);
       } 
      else return; 
    }
  else assert(!"never get here");
  if (alter_wert >= max_wert && radiobutton_steigern->get_active())
      { hauptfenster->set_status("Für Grad "+itos(hauptfenster->getWerte().Grad())+" ist der Maximalwert erreicht!") ;
        return;}

  if(radiobutton_steigern->get_active())
   {
     int dummy=1;
     if(!steigern_usp(kosten,0,dummy,was) ) return; 
     hauptfenster->getWerte().addGFP(kosten);
     if      (was==Abwehr)    hauptfenster->getWerte().setAbwehr_wert(alter_wert+1);
     else if (was==Resistenz) hauptfenster->getWerte().setResistenz(alter_wert+1); 
     else if (was==Zaubern)   hauptfenster->getWerte().setZaubern_wert(alter_wert+1); 
   }
  else
   {
     if (checkbutton_EP_Geld->get_active()) desteigern(kosten);
     set_lernzeit(-kosten,was);
     hauptfenster->getWerte().addGFP(-kosten);
     if      (was==Abwehr)    hauptfenster->getWerte().setAbwehr_wert(alter_wert-1);
     else if (was==Resistenz) hauptfenster->getWerte().setResistenz(alter_wert-1); 
     else if (was==Zaubern)   hauptfenster->getWerte().setZaubern_wert(alter_wert-1); 
   }
#endif
 zeige_werte();
}
