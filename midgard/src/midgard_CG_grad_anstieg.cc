// $Id: midgard_CG_grad_anstieg.cc,v 1.21 2001/08/21 12:03:03 thoma Exp $
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
   int old_grad      = Werte.Grad();
   get_grad(Werte.GFP());
   get_ausdauer(Werte.Grad());
   get_abwehr_wert(Werte.Grad());
   get_resistenz_wert(Werte.Grad());
   get_zauber(Werte.Grad());
   if (old_grad<Werte.Grad()) get_grundwerte();
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

void midgard_CG::on_button_grad_basiswerte_clicked()
{   
  get_grundwerte();
  zeige_werte(Werte);
}

void midgard_CG::on_button_grad_azr_clicked()
{   
 get_abwehr_wert(Werte.Grad());
 get_zauber(Werte.Grad());
 get_resistenz_wert(Werte.Grad());
  zeige_werte(Werte);
}


void midgard_CG::get_grundwerte()
{
  if(Werte.Grad() <= grad_basiswerte) 
   {
      std::string strinfo = "Für diesen Grad wurde schon gewürfelt";
      manage(new WindowInfo(strinfo));
      return;
   }
  Random random;
  int z=random.integer(1,100);
  std::string stinfo="Beim Würfeln zur Erhöhung einer Eigenschaft\nbeim Gradanstieg wurde eine ";
  stinfo += itos(z);
  stinfo +=" gewürfelt --> ";
//  std::cout << "Beim Würfeln zur Erhöhung einer Eigenschaft beim Gradanstieg\n"
//       << " wurde eine "<<z<<" gewürfelt --> ";
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
  grad_basiswerte=Werte.Grad();
}

void midgard_CG::get_zauber(int grad)
{
 if (Typ.Zaubern() == "z" || Typ.Zaubern() == "j" || Typ2.Zaubern() == "z" || Typ2.Zaubern() == "j")
  {  
   int kosten=0;
   int a;
   if (grad == 1)  { a=10 ;}
   if (grad == 2)  { a=11 ; kosten =   10;}
   if (grad == 3)  { a=12 ; kosten =   10;}
   if (grad == 4)  { a=13 ; kosten =   20;}
   if (grad == 5)  { a=14 ; kosten =   30;}
   if (grad == 6)  { a=15 ; kosten =   70;}
   if (grad == 7)  { a=16 ; kosten =  150;}
   if (grad == 8)  { a=17 ; kosten =  300;}
   if (grad == 9)  { a=18 ; kosten =  600;}
   if (grad == 10) { a=19 ; kosten =  800;}
   if (!steigern(kosten,"Zauber")) 
      { std::string strinfo ="Zu wenig EP um 'Zaubern' zu steigern";
        manage(new WindowInfo(strinfo));
        return;
      }
   Werte.add_GFP(kosten);
   Werte.set_Zaubern_wert(a);
  }
}


void midgard_CG::get_abwehr_wert(int grad)
{
   int kosten=0;
   int a;
   if (grad == 1)  { a=11; }
   if (grad == 2)  { a=12; kosten =   10; }
   if (grad == 4)  { a=13; kosten =   20; }
   if (grad == 6)  { a=14; kosten =   80; }
   if (grad == 8)  { a=15; kosten =  300; }
   if (grad == 10) { a=16; kosten =  700; }
   if (grad == 12) { a=17; kosten = 1000; }
   if (grad == 14) { a=18; kosten = 1500; }
   if (!steigern(kosten,"Abwehr"))
      { std::string strinfo ="Zu wenig EP um die 'Abwehr' zu steigern";
        manage(new WindowInfo(strinfo));
        return;
      }
   Werte.add_GFP(kosten);  
   Werte.set_Abwehr_wert(a);
}

void midgard_CG::get_resistenz_wert(int grad)
{
   int kosten=0;
   int r;
   if (grad == 1)  { r=10; }
   if (grad == 2)  { r=11; kosten =   10; }
   if (grad == 4)  { r=12; kosten =   20; }
   if (grad == 6)  { r=13; kosten =   80; }
   if (grad == 8)  { r=14; kosten =  300; }
   if (grad == 10) { r=15; kosten =  700; }
   if (grad == 12) { r=16; kosten = 1000; }
   if (grad == 14) { r=17; kosten = 1500; }
   if (!steigern(kosten,"Resistenz"))
      { std::string strinfo ="Zu wenig EP um die 'Resistenz' zu steigern";
        manage(new WindowInfo(strinfo));
        return;
      }
   Werte.add_GFP(kosten);  
   Werte.set_Resistenz(r);
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


void midgard_CG::get_grad(int gfp)
{
   int new_grad;
   if (gfp <   200 )                new_grad = 1;
   if (   200<=gfp && gfp <   500 ) new_grad = 2;
   if (   500<=gfp && gfp <  1000 ) new_grad = 3;
   if (  1000<=gfp && gfp <  2000 ) new_grad = 4;
   if (  2000<=gfp && gfp <  4000 ) new_grad = 5;
   if (  4000<=gfp && gfp <  7000 ) new_grad = 6;
   if (  7000<=gfp && gfp < 15000 ) new_grad = 7;
   if ( 15000<=gfp && gfp < 25000 ) new_grad = 8;
   if ( 25000<=gfp && gfp < 50000 ) new_grad = 9;
   if ( 50000<=gfp && gfp < 70000 ) new_grad = 10;
   if ( 70000<=gfp && gfp < 90000 ) new_grad = 11;
   if (110000<=gfp && gfp <110000 ) new_grad = 12;
   if (130000<=gfp && gfp <130000 ) new_grad = 13;
   if (150000<=gfp && gfp <150000 ) new_grad = 14;
   if (150000<=gfp )                new_grad = 15;
   Werte.set_Grad(new_grad);
}
