#include "midgard_CG.hh"
#include "zufall.h"
#include "WindowInfo.hh"

void midgard_CG::on_grad_anstieg_clicked()
{
   int old_grad      = werte.grad;
   get_grad(werte.gfp);
   get_ausdauer(werte.grad);
   get_abwehr_resistenz_wert(werte.grad);
   get_zauber(werte.grad);
   if (old_grad<werte.grad) get_grundwerte();
   midgard_CG::zeige_werte(werte,"alle");
}

void midgard_CG::get_grundwerte()
{
  Random random;
  int z=random.integer(1,100);
  string stinfo="Beim Würfeln zur Erhöhung einer Eigenschaft\nbeim Gradanstieg wurde eine ";
  stinfo += itos(z);
  stinfo +=" gewürfelt --> ";
//  cout << "Beim Würfeln zur Erhöhung einer Eigenschaft beim Gradanstieg\n"
//       << " wurde eine "<<z<<" gewürfelt --> ";
  string was = "keine Erhöhung";

  int erh = random.integer(1,6)+1;
  if( 81<=z && z>=83 ) { was="Stärke";           werte.st+=erh; }
  if( 84<=z && z>=86 ) { was="Geschicklichkeit"; werte.ge+=erh; }
  if( 87<=z && z>=89 ) { was="Konstitution"; werte.ko+=erh; }
  if( 90<=z && z>=92 ) { was="Intelligenz"; werte.in+=erh; }
  if( 93<=z && z>=95 ) { was="Zaubertalent"; werte.zt+=erh; }
  if (z==96)   { was="Aussehn"; werte.au+=erh; }
  if (z==97)   { was="persönliche Ausstrahlung"; werte.pa+=erh; }
  if (z==98)   { was="Selbstbeherrschung"; werte.sb+=erh; }
  if (z==99)   { was="Reaktionswert"; werte.rw+=erh; }
  if (z==100)  { was="Hanggemengewert"; werte.hgw+=erh; }

//  cout << was;
  stinfo += was;
  if (was != "keine Erhöhung" )
    {
//       cout <<" um " <<erh<<" erhöht.\n";
       stinfo += " um "; stinfo += itos(erh); stinfo+=" erhöht.\n";
       midgard_CG::grundwerte_boni_setzen();
    }
//  cout << ".\n";
  manage(new WindowInfo(stinfo));
}

void midgard_CG::get_zauber(int grad)
{
 if (typ.z == "z" || typ.z == "j" )
  {  
   int kosten=0;
   if (grad == 1)  { werte.zaubern_wert = 10 ;}
   if (grad == 2)  { werte.zaubern_wert = 11 ; kosten =   10;}
   if (grad == 3)  { werte.zaubern_wert = 12 ; kosten =   10;}
   if (grad == 4)  { werte.zaubern_wert = 13 ; kosten =   20;}
   if (grad == 5)  { werte.zaubern_wert = 14 ; kosten =   30;}
   if (grad == 6)  { werte.zaubern_wert = 15 ; kosten =   70;}
   if (grad == 7)  { werte.zaubern_wert = 16 ; kosten =  150;}
   if (grad == 8)  { werte.zaubern_wert = 17 ; kosten =  300;}
   if (grad == 9)  { werte.zaubern_wert = 18 ; kosten =  600;}
   if (grad == 10) { werte.zaubern_wert = 19 ; kosten =  800;}
   werte.gfp += kosten;
  }
}


void midgard_CG::get_abwehr_resistenz_wert(int grad)
{
   int kosten=0;
   if (grad == 1)  { werte.abwehr_wert = 11; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=10; }
   if (grad == 2)  { werte.abwehr_wert = 12; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=11; kosten =   10; }
   if (grad == 4)  { werte.abwehr_wert = 13; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=12; kosten =   20; }
   if (grad == 6)  { werte.abwehr_wert = 14; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=13; kosten =   80; }
   if (grad == 8)  { werte.abwehr_wert = 15; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=14; kosten =  300; }
   if (grad == 10) { werte.abwehr_wert = 16; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=15; kosten =  700; }
   if (grad == 12) { werte.abwehr_wert = 17; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=16; kosten = 1000; }
   if (grad == 14) { werte.abwehr_wert = 18; werte.psyZR_wert=werte.phsZR_wert=werte.phkZR_wert=17; kosten = 1500; }
   werte.gfp += kosten;
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
   werte.gfp += kosten;
   int ap=0;
   Random random;
   for (int i=0;i<grad;++i) ap += random.integer(1,6);

  int nab, nap;
  if (typ.ausdauer == "k")  nab = bonus_K ;
  if (typ.ausdauer == "ak") nab = bonus_aK ;
  if (typ.ausdauer == "z")  nab = bonus_Z ;
  nap = ap + nab + werte.bo_au;
//  cout << "Ausdauerpunkte: "<<ap<<" + " <<nab<<" + "<<werte.bo_au<<" = "<<nap<<"\n";
  string stinfo="Ausdauerpunkte: Gewürfelt + Bonus für Typ + Persönlichen Bonus\n";
   stinfo+=itos(ap);stinfo+="+";stinfo+=itos(nab);
   stinfo+="+";stinfo+=itos(werte.bo_au);stinfo+="=";stinfo+=itos(nap);
  manage(new WindowInfo(stinfo));
  (nap>werte.ap)?werte.ap=nap:0 ;
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
   werte.grad = new_grad;
}
