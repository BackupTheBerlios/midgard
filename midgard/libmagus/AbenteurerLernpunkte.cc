// $Id: AbenteurerLernpunkte.cc,v 1.4 2003/11/24 16:21:42 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#include "AbenteurerLernpunkte.hh"
#include "Abenteurer.hh"
#include <Misc/itos.h>
#include "Ausgabe.hh"
#include "Random.hh"
#include "Datenbank.hh"
#include "Fertigkeiten_angeboren.hh"

void AbenteurerLernpunkte::ruestung_auswaehlen(Abenteurer &a,int wprozent)
	// on_button_ruestung_clicked(int wurf)
{
  std::string rue;
  if (a.Typ1()->Ruestung() == 1)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "TR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "TR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "LR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "LR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "LR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "LR" ;
   }
  if (a.Typ1()->Ruestung()== 2)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "TR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "LR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "LR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "KR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "KR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "KR" ;
   }
  if (a.Typ1()->Ruestung()== 3)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "TR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "LR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "KR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "KR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "KR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "PR" ;
   }
  if (a.Typ1()->Ruestung()== 4)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "OR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "OR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "TR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "TR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "LR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "LR" ;
   }
  if(a.Typ1()->Short()=="Fi") rue="KR";
  a.setRuestung1(rue);
  Ausgabe(Ausgabe::Log, "Beim Auswürfeln der Rüstung wurde eine "+itos(wprozent)+" gewürfelt "
             "==> " + a.Ruestung()->Long());
}

void AbenteurerLernpunkte::beruf_gewuerfelt(Abenteurer &a,int wurf)
{
  std::string kat=BKategorie.wuerfeln(wurf);
  Ausgabe(Ausgabe::ActionNeeded, kat);
}

#if 0
void AbenteurerLernpunkte::on_beruf_tree_leaf_selected(Abenteurer &A, cH_Beruf b, const st_vorteil &v)
{
 try{
    cH_MidgardBasicElement cmbe(&*b);
    MBEmlt mbe(cmbe);
    a.List_Beruf().clear(); // es kann nur einen Beruf geben
    a.List_Beruf().push_back(mbe);

    bool zusatz = Beruf::Berufsfertigkeit(A,v);
    if(zusatz) 
     { cH_MidgardBasicElement cMBE(&*cH_Fertigkeit(v.name));
       MBEmlt MBE(cMBE);
       lernen_zusatz((*MBE)->ZusatzEnum(a.getVTyp()),MBE);
     }

    if (!BKategorie.kat_IV || (dt->getVorteil().kat==3 || dt->getVorteil().kat==4))
      {
      }
    else
      {
         BKategorie.kat_IV=false;
      }
 }catch(std::exception &e) {Ausgabe(Ausgabe::Error,e.what());}
}

#endif

void AbenteurerLernpunkte::geld_wuerfeln(Abenteurer &a)
{
     VGeldwurf.clear();
     for(int i=0;i<3;++i) VGeldwurf.push_back(Random::W6());
     lernschema_geld_wuerfeln(a,VGeldwurf);
}

void AbenteurerLernpunkte::lernschema_geld_wuerfeln(Abenteurer &a,const std::vector<int>& VGeldwurf)
{
 assert(VGeldwurf.size()==3);
 int igold=0;  
 igold=VGeldwurf[0]+VGeldwurf[1]+VGeldwurf[2];
 if      (a.Typ1()->Geld() == 1) igold-=3;
 else if (a.Typ1()->Geld() == 2) igold+=0;
 else if (a.Typ1()->Geld() == 3) igold+=6;
 else if (a.Typ1()->Geld() == 4) igold+=3;

 if(a.Stand()=="Adel" ) igold*=2;  
 if(a.Stand()=="Unfrei" ) igold/=2;
 if(VGeldwurf[0]==VGeldwurf[1] && VGeldwurf[1]==VGeldwurf[2]) igold += 100;

 Ausgabe(Ausgabe::Log,"Beim Auswürfeln von Geld wurden "
   +itos(VGeldwurf[0])+"  "+itos(VGeldwurf[1])+"  "+itos(VGeldwurf[2])+" gewürfelt ==> "
   +itos(igold)+" Gold");
 a.addGold(igold);  
}

void AbenteurerLernpunkte::ausruestung_setzen(Abenteurer &a)
{ a.setStandardAusruestung();
  setFertigkeitenAusruestung(a);
}

std::string AbenteurerLernpunkte::AngebFert_gewuerfelt(Abenteurer &a,int wurf)
{
  std::string name;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Fertigkeit_ang.begin();i!=Datenbank.Fertigkeit_ang.end();++i)
   {
     if (cH_Fertigkeit_angeborene(*i)->Min()<=wurf && wurf<=cH_Fertigkeit_angeborene(*i)->Max())
      {
         name=(*i)->Name();
         a.setAngebSinnFert(wurf,MBEmlt(*i));  
         break;
      }
   }
 return name;
}

void AbenteurerLernpunkte::setFertigkeitenAusruestung(Abenteurer &a)
{
  AusruestungBaum &koerper=a.getBesitz();
  AusruestungBaum &rucksack=a.getAusruestung_as_parent("Rucksack");
  for (std::list<MBEmlt>::const_iterator i=a.List_Fertigkeit().begin();i!=a.List_Fertigkeit().end();++i)
   {
     const std::vector<Fertigkeit::st_besitz> VB=cH_Fertigkeit((*i)->getMBE())->get_vec_Besitz();
     for(std::vector<Fertigkeit::st_besitz>::const_iterator j=VB.begin();j!=VB.end();++j)
      {
        int wurf=Random::W100();
        if(wurf>=j->min)
         {
           AusruestungBaum *A;
           if(j->position == Fertigkeit::Besitz)
            {
              A = &koerper.push_back(Ausruestung(j->name)); 
              A->setParent(&koerper);
            }
           else if(j->position == Fertigkeit::Rucksack)
            {
              A = &rucksack.push_back(Ausruestung(j->name));
              A->setParent(&rucksack); 
            }
         }
        InfoAusruestung((*(*i))->Name(),j->name,wurf,j->min);
      }
   }
}

void AbenteurerLernpunkte::InfoAusruestung(const std::string &fert_name,
               const std::string &gegen_name,int wurf,int noetig)
{
 std::string strinfo;
 strinfo="Für die Fertigkeit '"+fert_name+"' wurde für '"+gegen_name+
        "' eine "+itos(wurf)+" gewürfelt.\n";
 strinfo += "Nötig ist mindestens eine "+itos(noetig)+".\n";
 if(wurf>noetig) strinfo +="==> Das reicht.";
 else strinfo +="==> Das reicht NICHT.";
 Ausgabe(Ausgabe::Log,strinfo);
}
