// $Id: Abenteurer_besitz.cc,v 1.10 2003/01/23 15:28:25 thoma Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#include "Abenteurer.hh"
#include "dtos1.h"

void rekursiv(const std::list<AusruestungBaum> &AB, double &last,double &GG)
{
  for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
   {
     double G=i->getAusruestung().Gewicht();
     if(!i->getAusruestung().RuestungOhneGewicht())
      {
        if(GG<0) { GG+=G; if(GG>0) G=GG; else G=0;}
        if (G>0) last+=G*i->getAusruestung().Anzahl();
      }
     std::list<AusruestungBaum> L=i->getChildren();
     GG+=G;
     rekursiv(L,last,GG);
   }
}

std::map<std::string,double> Abenteurer::getBelastung() const
{
  std::map<std::string,double> MG;
//  double last=0;
  for(AusruestungBaum::const_iterator i=getBesitz().begin();i!=getBesitz().end();++i)
   {
//     if(i->getAusruestung().Name()!="Körper") continue;
     
     double G=i->getAusruestung().Gewicht();
     if(G>0) MG[i->getAusruestung().Name()]+=G*i->getAusruestung().Anzahl();
     std::list<AusruestungBaum> L=i->getChildren();
     ::rekursiv(L,MG[i->getAusruestung().Name()],G);
   }
  return MG;
//  return last;
}

double Abenteurer::getBelastung(const std::string &s) const
{
  std::map<std::string,double> MG=getBelastung();
  return MG[s];
}


AusruestungBaum* Abenteurer::rekursiv(std::list<AusruestungBaum> &AB,const std::string &name)
{
//std::cout << "S2: "<<AB.size()<<'\n';
  AusruestungBaum *ab=&getBesitz();
  for(std::list<AusruestungBaum>::iterator i=AB.begin();i!=AB.end();++i)
   {
//std::cout <<' '<< name<<'\t'<<i->getAusruestung().Name()<<'\t'<<(name==i->getAusruestung().Name())<<'\n';
     if(name==i->getAusruestung().Name()) return ab=&*i;
     else ab = rekursiv(i->getChildren(),name);
   }
 return ab;
}

AusruestungBaum& Abenteurer::getAusruestung_as_parent(const std::string &name)
{
  AusruestungBaum *ab=&getBesitz();
  for(AusruestungBaum::iterator i=getBesitz().begin();i!=getBesitz().end();++i)
   {
std::cout << name<<'\t'<<i->getAusruestung().Name()<<'\t'<<(name==i->getAusruestung().Name())<<'\n';
     if(name==i->getAusruestung().Name()) return *i;
     else ab=rekursiv(i->getChildren(),name);
   }
 return *ab;
}


void Abenteurer::setStandardAusruestung()
{
  if(!getBesitz().empty()) return;

  AusruestungBaum *Koerper = &besitz.push_back(Ausruestung("KÃ¶rper"));
  Koerper->setParent(&besitz);
  AusruestungBaum *Hose=&Koerper->push_back(Ausruestung("Hose"));
  Hose->setParent(Koerper);
  AusruestungBaum *Hemd=&Koerper->push_back(Ausruestung("Hemd"));
  Hemd->setParent(Koerper);
  AusruestungBaum *Guertel=&Koerper->push_back(Ausruestung("GÃ¼rtel"));
  Guertel->setParent(Koerper);
  AusruestungBaum *Schuhe=&Koerper->push_back(Ausruestung("Schuhe"));
  Schuhe->setParent(Koerper);
  AusruestungBaum *Rucksack=&Koerper->push_back(Ausruestung(1,"Rucksack",0,"Leder","",true,false,""));
  Rucksack->setParent(Koerper);
  AusruestungBaum *Decke=&Rucksack->push_back(Ausruestung(1,"Decke",0,"warm","",false,false,""));
  Decke->setParent(Rucksack);
  AusruestungBaum *Lederbeutel=&Rucksack->push_back(Ausruestung("Lederbeutel"));
  Lederbeutel->setParent(Guertel);
  AusruestungBaum *Geld=&Rucksack->push_back(Ausruestung(1,"Geld",0,"","",false,false,""));
  Geld->setParent(Lederbeutel);

//  return *Rucksack;
//  setFertigkeitenAusruestung(Rucksack);
}

int Abenteurer::getNormallast() const
{
   int s=getWerte().St();
   if     (s<=10)          return  3;
   else if(11<=s && s<=30) return  6;
   else if(31<=s && s<=60) return 10;
   else if(61<=s && s<=80) return 15;
   else if(81<=s && s<=95) return 20;
   else if(96<=s && s<=99) return 25;
   return 30; // s>=100
}
int Abenteurer::getHoechstlast() const 
{
   int s=getWerte().St();
   if     (s<=10)          return 40;
   else if(11<=s && s<=30) return 50;
   else if(31<=s && s<=60) return 60;
   else if(61<=s && s<=80) return 65;
   else if(81<=s && s<=95) return 75;
   else if(96<=s && s<=99) return 80;
   return 90; // s>=100
}
int Abenteurer::getSchublast() const
{
   int s=getWerte().St();
   if     (s<=10)          return 50;
   else if(11<=s && s<=30) return 70;
   else if(31<=s && s<=60) return 120;
   else if(61<=s && s<=80) return 140;
   else if(81<=s && s<=95) return 150;
   else if(96<=s && s<=99) return 170;
   return 200; // s>=100
}

double Abenteurer::getUeberlast() const
{
  double u=getBelastung("Körper")-getNormallast();
  if (u<0) return  0;
  else     return  u;
}

