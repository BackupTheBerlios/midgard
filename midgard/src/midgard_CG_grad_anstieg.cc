// $Id: midgard_CG_grad_anstieg.cc,v 1.25 2001/09/07 07:30:33 thoma Exp $
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
#include "WindowInfo.hh"
#include "zufall.h"

void midgard_CG::on_grad_anstieg_clicked()
{
 int old_grad=Werte.Grad();
 get_grad(Werte.GFP());
 get_ausdauer(Werte.Grad());
 get_ab_re_za("Abwehr");
 get_ab_re_za("Resistenz");
 get_ab_re_za("Zaubern");
 while(old_grad<Werte.Grad())
  { get_grundwerte();
    ++old_grad;
  }
 zeige_werte(Werte);
}

void midgard_CG::on_button_grad_clicked()
{   
  get_grad(Werte.GFP());
  zeige_werte(Werte);
}
void midgard_CG::on_button_grad_ausdauer_clicked()
{   
  get_ausdauer(Werte.Grad());
  zeige_werte(Werte);
}
void midgard_CG::on_button_grad_abwehr_clicked()
{   
 get_ab_re_za("Abwehr");
 zeige_werte(Werte);
}
void midgard_CG::on_button_grad_zaubern_clicked()
{   
 get_ab_re_za("Zaubern");
 zeige_werte(Werte);
}
void midgard_CG::on_button_grad_resistenz_clicked()
{   
 get_ab_re_za("Resistenz");
 zeige_werte(Werte);
}
void midgard_CG::on_button_grad_basiswerte_clicked()
{   
  get_grundwerte();
  zeige_werte(Werte);
}


void midgard_CG::get_grundwerte()
{
  if(Werte.Grad() <= Grad_Anstieg.get_Grad_Basiswerte()) 
   {
      std::string strinfo = "Für Grad "+itos(Grad_Anstieg.get_Grad_Basiswerte())+" wurde schon gewürfelt";
      manage(new WindowInfo(strinfo));
      return;
   }
  Random random;
  int z=random.integer(1,100);
  std::string stinfo="Beim Würfeln zur Erhöhung einer Eigenschaft\nfür Grad "
      + itos(Grad_Anstieg.get_Grad_Basiswerte()+1) + " wurde eine ";
  stinfo += itos(z);
  stinfo +=" gewürfelt --> ";
  std::string was = "keine Erhöhung";

  int erh = random.integer(1,6)+1;
  if( 81<=z && z>=83 ) { was="Stärke";           Werte.add_St(erh); }
  if( 84<=z && z>=86 ) { was="Geschicklichkeit"; Werte.add_Ge(erh); }
  if( 87<=z && z>=89 ) { was="Konstitution"; Werte.add_Ko(erh); }
  if( 90<=z && z>=92 ) { was="Intelligenz"; Werte.add_In(erh); }
  if( 93<=z && z>=95 ) { was="Zaubertalent"; Werte.add_Zt(erh); }
  if (z==96)   { was="Aussehn"; Werte.add_Au(erh); }
  if (z==97)   { was="persönliche Ausstrahlung"; Werte.add_pA(erh); }
  if (z==98)   { was="Selbstbeherrschung"; Werte.add_Sb(erh); }
  if (z==99)   { was="Reaktionswert"; Werte.add_RW(erh); }
  if (z==100)  { was="Handgemengewert"; Werte.add_HGW(erh); }

  stinfo += was;
  if (was != "keine Erhöhung" )
    {
       stinfo += " um "; stinfo += itos(erh); stinfo+=" erhöht.\n";
       midgard_CG::grundwerte_boni_setzen();
    }
  manage(new WindowInfo(stinfo,true));
  if (Originalbool) original_midgard_check() ;
  Grad_Anstieg.set_Grad_Basiswerte(1+Grad_Anstieg.get_Grad_Basiswerte());
}

void midgard_CG::get_ausdauer(int grad)
{
   int bonus_K, bonus_aK, bonus_Z, kosten=0;
   if (grad == 1)  { bonus_K =  4, bonus_aK =  3; bonus_Z =  2; kosten =    20;}
   if (grad == 2)  { bonus_K =  6, bonus_aK =  4; bonus_Z =  2; kosten =    20;}
   if (grad == 3)  { bonus_K =  9, bonus_aK =  6; bonus_Z =  3; kosten =    20;}
   if (grad == 4)  { bonus_K = 12, bonus_aK =  8; bonus_Z =  4; kosten =    40;}
   if (grad == 5)  { bonus_K = 15, bonus_aK = 10; bonus_Z =  5; kosten =    70;}
   if (grad == 6)  { bonus_K = 18, bonus_aK = 12; bonus_Z =  6; kosten =   150;}
   if (grad == 7)  { bonus_K = 21, bonus_aK = 14; bonus_Z =  7; kosten =   300;}
   if (grad == 8)  { bonus_K = 24, bonus_aK = 16; bonus_Z =  8; kosten =  1200;}
   if (grad == 9)  { bonus_K = 27, bonus_aK = 18; bonus_Z =  9; kosten =  1500;}
   if (grad >= 10) { bonus_K = 30, bonus_aK = 20; bonus_Z = 10; kosten =  2000;}
   if (!steigern(kosten,"Ausdauer")) return;
   Werte.add_GFP(kosten);
   int ap=0;
   Random random;
   for (int i=0;i<grad;++i) ap += random.integer(1,6);

  int nab, nap;
  if      (Typ.Ausdauer() == "k" || Typ2.Ausdauer() == "k")  nab = bonus_K ;
  else if (Typ.Ausdauer() == "ak"|| Typ2.Ausdauer() == "ak") nab = bonus_aK ;
  else  nab = bonus_Z ;
  nap = ap + nab + Werte.bo_Au() ;
  int nspez = Werte.Grad()*Spezies_constraint.AP_Grad();
  nap += nspez;
//  std::cout << "Ausdauerpunkte: "<<ap<<" + " <<nab<<" + "<<Werte.bo()_au<<" + "<<nspez<<" = "<<nap<<"\n";
  std::string stinfo="Ausdauerpunkte: Gewürfelt + Bonus für Typ + Persönlichen Bonus + Spezies-Bonus\n";
   stinfo+=itos(ap);stinfo+="+";stinfo+=itos(nab);
   stinfo+="+";stinfo+=itos(Werte.bo_Au());stinfo+="=";stinfo+=itos(nap);
  manage(new WindowInfo(stinfo,true));
   // Für alle ist die AP-anzahel mind. = Grad
  if (Werte.AP()<Werte.Grad()) Werte.set_AP(Werte.Grad()); 
   // Neue AP höher als alte?
  if (nap>Werte.AP())  Werte.set_AP(nap)  ;
}

