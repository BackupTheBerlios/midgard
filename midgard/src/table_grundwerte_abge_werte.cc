// $Id: table_grundwerte_abge_werte.cc,v 1.3 2002/05/22 17:00:45 thoma Exp $
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
#include "table_grundwerte.hh"

void table_grundwerte::on_abge_werte_setzen_clicked()
{
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::ABGELEITETEWERTE);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active) 
      button_abg_werte->set_sensitive(false);
  hauptfenster->getWerte().setGrad(1);
//  Werte.setAu( constraint_aw(Werte.Spezies()->Au()) );
//  Werte.setpA( random.integer(1,100)-30 + 3*(Werte.In()/10 + Werte.Au()/10) );
  { //Bewegungsweite
    int b = hauptfenster->getCWerte().Spezies()->B_Bonus();
    for (int i=0;i<hauptfenster->getCWerte().Spezies()->B_Wanz();++i) b+=hauptfenster->random.integer(1,3);
    hauptfenster->getWerte().setB(b);
  }
  hauptfenster->getWerte().setWk(hauptfenster->random.integer(1,100)-40 
         + 3*(hauptfenster->getCWerte().In()/10 + hauptfenster->getCWerte().Ko()/10) );
  {
    int sb = hauptfenster->random.integer(1,100) + 3*(hauptfenster->getCWerte().In()/10 
                                       + hauptfenster->getCWerte().Wk()/10) - 30;
    // Boni für Selbstbeherrschung: Assassine, Beschwörer & Druide
    sb += hauptfenster->Char.CTyp1()->Sb() + hauptfenster->Char.CTyp2()->Sb();
    // Saddhu
    if (hauptfenster->Char.CTyp1()->Short() == "Sa") sb = 80+hauptfenster->random.integer(1,20);
    hauptfenster->getWerte().setSb(sb);
  }

  ////////////////////////////////////////////////////////////////////////
  // Ausdauer
  {
    int bo_au_typ;  
    if      (hauptfenster->Char.CTyp1()->Ausdauer() == "k" || hauptfenster->Char.CTyp2()->Ausdauer() == "k" ) bo_au_typ = 4 ;
    else if (hauptfenster->Char.CTyp1()->Ausdauer() == "ak"|| hauptfenster->Char.CTyp2()->Ausdauer() == "ak" ) bo_au_typ = 3 ;
    else bo_au_typ = 2 ;
    int ap = hauptfenster->random.integer(1,6)+hauptfenster->getCWerte().bo_Au()+bo_au_typ 
            + hauptfenster->getCWerte().Spezies()->AP_Bonus() ;
    if (ap<4) ap=4;
    hauptfenster->getWerte().setAP(ap);
  }
  hauptfenster->getWerte().setLP(hauptfenster->random.integer(1,6)
      +hauptfenster->getCWerte().Ko()/10+4 + hauptfenster->getCWerte().Spezies()->LP_Bonus());

  /////////////////////////////////////////////////////////////////////////
  // Körper und Stand
  {
    int groesse = hauptfenster->getCWerte().Spezies()->Groesse_Bonus() 
                +  hauptfenster->getCWerte().St()/10 ;
    for (int i=0;i<hauptfenster->getCWerte().Spezies()->Groesse_Wanz();++i) 
       groesse += hauptfenster->random.integer(1,hauptfenster->getCWerte().Spezies()->Groesse_Wuerfel()) ;
    if (hauptfenster->getCWerte().Spezies()->Name()=="Mensch" && 
         hauptfenster->getCWerte().Geschlecht()=="w")
       groesse-=10;   
    hauptfenster->getWerte().setGroesse(groesse);
  }
  {
    int gewicht = hauptfenster->getCWerte().Spezies()->Gewicht_Bonus() 
                  + hauptfenster->getCWerte().St()/10 
                  + hauptfenster->getCWerte().Groesse();
    for (int i=0;i<hauptfenster->getCWerte().Spezies()->Gewicht_Wanz();++i) 
       gewicht += hauptfenster->random.integer(1,6) ;
    if (hauptfenster->getCWerte().Spezies()->Name()=="Mensch" && hauptfenster->getCWerte().Geschlecht()=="w")
       gewicht-=4;   
    hauptfenster->getWerte().setGewicht(gewicht);
  }

  {
    int ihand=hauptfenster->random.integer(1,20)+hauptfenster->getCWerte().Spezies()->HandBonus();
    std::string h;
    if(ihand<=15) h=Vhand[0];
    else if (16<=ihand && ihand<=19) h=Vhand[1];
    else h=Vhand[2];
    hauptfenster->getWerte().setHand(h);
  }
  {
    int istand=hauptfenster->random.integer(1,100);
    int typstand1 = hauptfenster->Char.CTyp1()->Stand();
    int typstand2 = hauptfenster->Char.CTyp2()->Stand();
    if(typstand1*typstand2 <= 0 ) istand += typstand1 + typstand2 ;
    else  // gleiches Vorzeichen
     { int t= (abs(typstand1)>abs(typstand2)) ? abs(typstand1) : abs(typstand2);
       if (typstand1<0) t*=-1;
       istand += t;
     }
//std::cout << "typstand\t"<<typstand<<"\n";
    std::string stand;  
    if(hauptfenster->getCWerte().Spezies()->Name()=="Mensch")
     {
       if (istand<=10) stand = Vstand[1];
       if (11<=istand&&istand<=50) stand =  Vstand[2];
       if (51<=istand&&istand<=90) stand =  Vstand[3];
       if (istand>=91) stand =  Vstand[4];;
     }
    else if(hauptfenster->getCWerte().Spezies()->Name()=="Halbling" ||
            hauptfenster->getCWerte().Spezies()->Name()=="Waldgnom" ||
            hauptfenster->getCWerte().Spezies()->Name()=="Berggnom")
     {
       if (istand<=50) stand =  Vstand[2];
       if (51<=istand) stand =  Vstand[3];
     }
    else
     {
       if (            istand<=50) stand =  Vstand[2];
       if (51<=istand&&istand<=90) stand =  Vstand[3];
       if (istand>=91) stand =  Vstand[4];
     }
    hauptfenster->getWerte().setStand(stand);
   }
  hauptfenster->getWerte().setGrad1Werte(hauptfenster->getCChar().getVTyp());

  zeige_werte();
  hauptfenster->table_lernschema->button_herkunft->set_sensitive(true);
  hauptfenster->frame_lernschema->set_sensitive(true);
}


