// $Id: table_grundwerte_abge_werte.cc,v 1.20 2003/09/05 06:32:27 christof Exp $
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
#include <Misc/Trace.h>
#include <libmagus/Random.hh>

void table_grundwerte::on_abge_werte_setzen_clicked()
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(!hauptfenster->getOptionen()->OptionenCheck(Optionen::NSC_only).active)
   {
     combo_typ->set_sensitive(false);
     combo_typ2->set_sensitive(false);
   }   
  hauptfenster->getChar().getWizard().done(Wizard::ABGELEITETEWERTE);
  if(!hauptfenster->getOptionen()->OptionenCheck(Optionen::NSC_only).active) 
      button_abg_werte->set_sensitive(false);
  hauptfenster->setGrad(1);
  { //Bewegungsweite
    int b = hauptfenster->Spezies()->B_Bonus();
    for (int i=0;i<hauptfenster->Spezies()->B_Wanz();++i) b+=Random::integer(1,3);
    hauptfenster->setB(b);
  }
  hauptfenster->setWk(Random::integer(1,100)-40 
         + 3*(hauptfenster->In()/10 + hauptfenster->Ko()/10) );
  {
    int sb = Random::integer(1,100) + 3*(hauptfenster->In()/10 
                                       + hauptfenster->Wk()/10) - 30;
    // Boni für Selbstbeherrschung: Assassine, Beschwörer & Druide
    sb += hauptfenster->getChar()->Typ1()->Sb() + hauptfenster->getChar()->Typ2()->Sb();
    // Saddhu
    if (hauptfenster->getChar()->Typ1()->Short() == "Sa") sb = 80+Random::integer(1,20);
    hauptfenster->setSb(sb);
  }

  ////////////////////////////////////////////////////////////////////////
  // Ausdauer
  {
    int bo_au_typ;  
    if      (hauptfenster->getChar()->Typ1()->Ausdauer() == "k" || hauptfenster->getChar()->Typ2()->Ausdauer() == "k" ) bo_au_typ = 4 ;
    else if (hauptfenster->getChar()->Typ1()->Ausdauer() == "ak"|| hauptfenster->getChar()->Typ2()->Ausdauer() == "ak" ) bo_au_typ = 3 ;
    else bo_au_typ = 2 ;
    int ap = Random::integer(1,6)+hauptfenster->bo_Au()+bo_au_typ 
            + hauptfenster->Spezies()->AP_Bonus() ;
    if (ap<4) ap=4;
    hauptfenster->setAP(ap);
  }
  hauptfenster->setLP(Random::integer(1,6)
      +hauptfenster->Ko()/10+4 + hauptfenster->Spezies()->LP_Bonus());

  /////////////////////////////////////////////////////////////////////////
  // Körper und Stand
  {
    int groesse = hauptfenster->Spezies()->Groesse_Bonus() 
                +  hauptfenster->St()/10 ;
    for (int i=0;i<hauptfenster->Spezies()->Groesse_Wanz();++i) 
       groesse += Random::integer(1,hauptfenster->Spezies()->Groesse_Wuerfel()) ;
    if (hauptfenster->Spezies()->Name()=="Mensch" && 
         hauptfenster->Geschlecht()==Enums::Frau)
       groesse-=10;   
    hauptfenster->setGroesse(groesse);
  }
  {
    int gewicht = hauptfenster->Spezies()->Gewicht_Bonus() 
                  + hauptfenster->St()/10 
                  + hauptfenster->Groesse();
    for (int i=0;i<hauptfenster->Spezies()->Gewicht_Wanz();++i) 
       gewicht += Random::integer(1,6) ;
    if (hauptfenster->Spezies()->Name()=="Mensch" && hauptfenster->Geschlecht()==Enums::Frau)
       gewicht-=4;   
    hauptfenster->setGewicht(gewicht);
  }

  {
    int ihand=Random::integer(1,20)+hauptfenster->Spezies()->HandBonus();
    std::string h;
    if(ihand<=15) h=Vhand[0];
    else if (16<=ihand && ihand<=19) h=Vhand[1];
    else h=Vhand[2];
    hauptfenster->setHand(h);
  }
  {
    int istand=Random::integer(1,100);
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
    if(hauptfenster->Spezies()->Name()=="Mensch")
     {
       if (istand<=10) stand = Vstand[1];
       if (11<=istand&&istand<=50) stand =  Vstand[2];
       if (51<=istand&&istand<=90) stand =  Vstand[3];
       if (istand>=91) stand =  Vstand[4];;
       if (hauptfenster->getChar()->Typ1()->Short()=="MMa") stand =  Vstand[3];
     }
    else if(hauptfenster->Spezies()->Name()=="Halbling" ||
            hauptfenster->Spezies()->Name()=="Waldgnom" ||
            hauptfenster->Spezies()->Name()=="Berggnom")
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
    hauptfenster->setStand(stand);
   }
  hauptfenster->setGrad1Werte(hauptfenster->getChar()->getVTyp());

  hauptfenster->table_lernschema->button_herkunft->set_sensitive(true);
  hauptfenster->frame_lernschema->set_sensitive(true);
  zeige_werte();
  hauptfenster->getChar().undosave("Abgeleitete Werte gewürfelt");
}


