#include "midgard_CG.hh"
#include "zufall.h"

void midgard_CG::on_abge_werte_setzen_clicked()
{
  Random random;
  werte.grad=1;
  //////////////////////////////////////////////////////////////////////
  // Übrige Werte würfeln //////////////////////////////////////////////
  // Aussehn
  werte.au = random.integer(1,100);
  // pers. Ausstrahlung
  werte.pa = random.integer(1,100)-40 + werte.in/2. + werte.au/4. ;
  // Selbstbeherrschung
  werte.sb = random.integer(1,100);
  // Reaktionswert
  werte.rw = random.integer(1,20)+10 + werte.ge/2. + werte.in/4.;
  // Handgemengewert
  werte.hgw = random.integer(1,20)+10+ werte.st/2. + werte.ge/4.;
  // Bewegungsweite
  werte.b= random.integer(1,3)+random.integer(1,3)
         + random.integer(1,3)+random.integer(1,3)+16;
  //////////////////////////////////////////////////////////////////////
  // Boni 
  // Assassine, Beschwörer & Druide
  if (typ.sb == 20) werte.sb += random.integer(1,20); 
  // Spitzbube
  if (typ.sb == -20) werte.sb -= random.integer(1,20); 
//cout << typ.sb<<"\n";
  midgard_CG::grundwerte_boni_setzen();

  // Ausdauerbonus für Typen
  if (typ.ausdauer == "k" ) werte.bo_au_typ = 4 ;
  if (typ.ausdauer == "ak" ) werte.bo_au_typ = 3 ;
  if (typ.ausdauer == "z" ) werte.bo_au_typ = 2 ;
//cout << werte.bo_au_typ<<"\n";
  // Werte würfeln und setzen
  werte.lp = random.integer(1,6)+werte.lpbasis ;
  werte.ap = random.integer(1,6)+werte.bo_au+werte.bo_au_typ ;
  werte.abwehr_wert= 11 ;
  //Barde,Ordenskrieger,Zauberer
  if (typ.z == "j" || typ.z == "z") werte.zaubern_wert = "10" ;
   else werte.zaubern_wert=" ";
  werte.psyZR_wert = 10;
  werte.phsZR_wert = 10;
  werte.phkZR_wert = 10;
  werte.gift_wert = 3*werte.lp;
  // Körper und Stand
  werte.groesse = random.integer(1,20)+random.integer(1,20)+145+werte.st/10.;
  
  int ges=random.integer(1,6);
  int gin=werte.groesse-100;
  if (werte.st >= 81) ges++;
  if (werte.st >= 96) ges++;
  if (ges<=2) 
   { werte.gestalt = "schlank";
     werte.gewicht = gin-(int)(gin*0.1) ; }
  if (ges>=3&&ges<=4) werte.gestalt = "normal";
  if (ges>=5) 
   { werte.gestalt = "breit";
     werte.gewicht =  gin+(int)(gin*0.2) ; }
  int istand=random.integer(1,100);
  istand += typ.stand;
//cout << typ.stand<<"\n";
  if (istand<=10) werte.stand = "Unfreie";
  if (11<=istand&&istand<=50) werte.stand = "Volk";
  if (51<=istand&&istand<=90) werte.stand = "Mittelschicht";
  if (istand>=91) werte.stand = "Adel";

  midgard_CG::zeige_werte(werte,"alle");
}


void midgard_CG::grundwerte_boni_setzen()
{
  werte.bo_au=0;
  werte.bo_sc=0;
  werte.bo_an=0;
  werte.bo_ab=0;
  werte.bo_za=0;
  werte.bo_psy=0;
  werte.bo_phs=0;
  werte.bo_phk=0;
  werte.bo_gi=0;
  // Stärke
  int ist=werte.st;
  if (ist<=10) { werte.bo_sc-=2; werte.bo_au-=1;werte.kaw=0;}
  if (11<=ist&&ist<=30) { werte.bo_sc-=1; werte.kaw=0;}
  if (31<=ist&&ist<=60) { werte.kaw=2;}
  if (61<=ist&&ist<=80) { werte.bo_sc+=1; werte.kaw=4;}
  if (81<=ist&&ist<=90) { werte.bo_sc+=2; werte.kaw=6;}
  if (91<=ist&&ist<=95) { werte.bo_sc+=2; werte.bo_au+=1;werte.kaw=8;}
  if (96<=ist&&ist<=99) { werte.bo_sc+=3; werte.bo_au+=2;werte.kaw=10;}
  if (ist>=100) { werte.bo_sc+=4; werte.bo_au+=3;werte.kaw=15;}
  // Geschicklichkeit
  ist=werte.ge;
  if (ist<=1) { werte.bo_sc-=2; werte.bo_an-=2; werte.bo_phk-=2;}
  if (2<=ist&&ist<=10) { werte.bo_sc-=1; werte.bo_an-=1; werte.bo_phk-=1;}
  if (11<=ist&&ist<=20) { werte.bo_sc-=1; }
  if (81<=ist&&ist<=90) { werte.bo_ab+=1;}
  if (91<=ist&&ist<=95) { werte.bo_sc+=1; werte.bo_ab+=1; werte.bo_phk+=1;}
  if (96<=ist&&ist<=99) { werte.bo_sc+=1; werte.bo_an+=1; werte.bo_ab+=2; werte.bo_phk+=2;}
  if (ist>=100) { werte.bo_sc+=2; werte.bo_an+=2; werte.bo_ab+=2; werte.bo_phk+=2;}
  // Konsitution
  ist=werte.ko;
  if (ist<=1) { werte.bo_au-=4; werte.lpbasis=5; werte.wlw=25; werte.bo_gi-=10; }
  if (2<=ist&&ist<=10) { werte.bo_au-=3; werte.lpbasis=6; werte.wlw=30; werte.bo_gi-=10; }
  if (11<=ist&&ist<=20) {werte.bo_au-=2; werte.lpbasis=7; werte.wlw=30; werte.bo_gi-=5; }
  if (21<=ist&&ist<=30) {werte.bo_au-=1; werte.lpbasis=8; werte.wlw=40; }
  if (31<=ist&&ist<=60) {werte.bo_au-=0; werte.lpbasis=9; werte.wlw=50; }
  if (61<=ist&&ist<=80) {werte.bo_au+=1; werte.lpbasis=10; werte.wlw=60; werte.bo_gi+=5; }
  if (81<=ist&&ist<=90) {werte.bo_au+=2; werte.lpbasis=11; werte.wlw=70; werte.bo_gi+=5; }
  if (91<=ist&&ist<=95) {werte.bo_au+=3; werte.lpbasis=12; werte.wlw=80; werte.bo_gi+=5; }
  if (96<=ist&&ist<=99) {werte.bo_au+=4; werte.lpbasis=13; werte.wlw=90; werte.bo_gi+=10; }
  if (ist>=100) { werte.bo_au+=5; werte.lpbasis=15; werte.wlw=95; werte.bo_gi+=15; }
  // Intelligenz
  ist=werte.in;
  if (ist<=10) { werte.bo_psy-=2;}
  if (11<=ist&&ist<=20) {werte.bo_psy-=1;}
  if (91<=ist&&ist<=95) {werte.bo_psy+=1;}
  if (96<=ist&&ist<=99) {werte.bo_psy+=2;}
  if (ist>=100) { werte.bo_psy+=3;}
  // Zaubertalent
  ist=werte.zt;
  int ibo_psy2=0;
  if (ist<=10) { werte.bo_za-=3; ibo_psy2-=2; werte.bo_phs-=2; }
  if (11<=ist&&ist<=20) {werte.bo_za-=2; ibo_psy2-=1; werte.bo_phs-=1; }
  if (21<=ist&&ist<=30) {werte.bo_za-=1; }
  if (61<=ist&&ist<=80) {werte.bo_za+=1; }
  if (81<=ist&&ist<=95) {werte.bo_za+=2; ibo_psy2+=1; werte.bo_phs+=1; }
  if (96<=ist&&ist<=99) {werte.bo_za+=3; ibo_psy2+=2; werte.bo_phs+=2; }
  if (ist>=100)         {werte.bo_za+=4; ibo_psy2+=3; werte.bo_phs+=3; }

  // Höhere Resistenz zählt + Resistenzen für Kämpfer|Zauberer
  (werte.bo_psy >= ibo_psy2) ? : werte.bo_psy=ibo_psy2 ;
  if (typ.z=="z" ) 
      { werte.bo_phs+=3; werte.bo_psy+=3; werte.bo_phk+=3; }
  else
      { werte.bo_phs+=2; }


}