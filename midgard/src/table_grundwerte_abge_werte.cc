// $Id: table_grundwerte_abge_werte.cc,v 1.10 2002/09/23 06:34:08 thoma Exp $
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
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
   {
     combo_typ->set_sensitive(false);
     combo_typ2->set_sensitive(false);
   }   
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::ABGELEITETEWERTE);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active) 
      button_abg_werte->set_sensitive(false);
  hauptfenster->getWerte().setGrad(1);
  { //Bewegungsweite
    int b = hauptfenster->getWerte().Spezies()->B_Bonus();
    for (int i=0;i<hauptfenster->getWerte().Spezies()->B_Wanz();++i) b+=hauptfenster->random.integer(1,3);
    hauptfenster->getWerte().setB(b);
  }
  hauptfenster->getWerte().setWk(hauptfenster->random.integer(1,100)-40 
         + 3*(hauptfenster->getWerte().In()/10 + hauptfenster->getWerte().Ko()/10) );
  {
    int sb = hauptfenster->random.integer(1,100) + 3*(hauptfenster->getWerte().In()/10 
                                       + hauptfenster->getWerte().Wk()/10) - 30;
    // Boni für Selbstbeherrschung: Assassine, Beschwörer & Druide
    sb += hauptfenster->getChar()->Typ1()->Sb() + hauptfenster->getChar()->Typ2()->Sb();
    // Saddhu
    if (hauptfenster->getChar()->Typ1()->Short() == "Sa") sb = 80+hauptfenster->random.integer(1,20);
    hauptfenster->getWerte().setSb(sb);
  }

  ////////////////////////////////////////////////////////////////////////
  // Ausdauer
  {
    int bo_au_typ;  
    if      (hauptfenster->getChar()->Typ1()->Ausdauer() == "k" || hauptfenster->getChar()->Typ2()->Ausdauer() == "k" ) bo_au_typ = 4 ;
    else if (hauptfenster->getChar()->Typ1()->Ausdauer() == "ak"|| hauptfenster->getChar()->Typ2()->Ausdauer() == "ak" ) bo_au_typ = 3 ;
    else bo_au_typ = 2 ;
    int ap = hauptfenster->random.integer(1,6)+hauptfenster->getWerte().bo_Au()+bo_au_typ 
            + hauptfenster->getWerte().Spezies()->AP_Bonus() ;
    if (ap<4) ap=4;
    hauptfenster->getWerte().setAP(ap);
  }
  hauptfenster->getWerte().setLP(hauptfenster->random.integer(1,6)
      +hauptfenster->getWerte().Ko()/10+4 + hauptfenster->getWerte().Spezies()->LP_Bonus());

  /////////////////////////////////////////////////////////////////////////
  // Körper und Stand
  {
    int groesse = hauptfenster->getWerte().Spezies()->Groesse_Bonus() 
                +  hauptfenster->getWerte().St()/10 ;
    for (int i=0;i<hauptfenster->getWerte().Spezies()->Groesse_Wanz();++i) 
       groesse += hauptfenster->random.integer(1,hauptfenster->getWerte().Spezies()->Groesse_Wuerfel()) ;
    if (hauptfenster->getWerte().Spezies()->Name()=="Mensch" && 
         hauptfenster->getWerte().Geschlecht()==Enums::Frau)
       groesse-=10;   
    hauptfenster->getWerte().setGroesse(groesse);
  }
  {
    int gewicht = hauptfenster->getWerte().Spezies()->Gewicht_Bonus() 
                  + hauptfenster->getWerte().St()/10 
                  + hauptfenster->getWerte().Groesse();
    for (int i=0;i<hauptfenster->getWerte().Spezies()->Gewicht_Wanz();++i) 
       gewicht += hauptfenster->random.integer(1,6) ;
    if (hauptfenster->getWerte().Spezies()->Name()=="Mensch" && hauptfenster->getWerte().Geschlecht()==Enums::Frau)
       gewicht-=4;   
    hauptfenster->getWerte().setGewicht(gewicht);
  }

  {
    int ihand=hauptfenster->random.integer(1,20)+hauptfenster->getWerte().Spezies()->HandBonus();
    std::string h;
    if(ihand<=15) h=Vhand[0];
    else if (16<=ihand && ihand<=19) h=Vhand[1];
    else h=Vhand[2];
    hauptfenster->getWerte().setHand(h);
  }
  {
    int istand=hauptfenster->random.integer(1,100);
    int typstand1 = hauptfenster->getChar()->Typ1()->Stand();
    int typstand2 = hauptfenster->getChar()->Typ2()->Stand();
    if(typstand1*typstand2 <= 0 ) istand += typstand1 + typstand2 ;
    else  // gleiches Vorzeichen
     { int t= (abs(typstand1)>abs(typstand2)) ? abs(typstand1) : abs(typstand2);
       if (typstand1<0) t*=-1;
       istand += t;
     }
//std::cout << "typstand\t"<<typstand<<"\n";
    std::string stand;  
    if(hauptfenster->getWerte().Spezies()->Name()=="Mensch")
     {
       if (istand<=10) stand = Vstand[1];
       if (11<=istand&&istand<=50) stand =  Vstand[2];
       if (51<=istand&&istand<=90) stand =  Vstand[3];
       if (istand>=91) stand =  Vstand[4];;
     }
    else if(hauptfenster->getWerte().Spezies()->Name()=="Halbling" ||
            hauptfenster->getWerte().Spezies()->Name()=="Waldgnom" ||
            hauptfenster->getWerte().Spezies()->Name()=="Berggnom")
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
  hauptfenster->getWerte().setGrad1Werte(hauptfenster->getChar()->getVTyp());

  hauptfenster->table_lernschema->button_herkunft->set_sensitive(true);
  hauptfenster->frame_lernschema->set_sensitive(true);
  zeige_werte();
  hauptfenster->undosave("Abgeleitete Werte gewürfelt");
}


