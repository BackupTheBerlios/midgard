/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2003      Christof Petig
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

#include "Ruestung.hh"
#include "NotFound.h"
#include "Grundwerte.hh"
#include <iostream>
#include <Misc/Tag.h>
#include "NotFound.h"

cH_Ruestung::cache_t cH_Ruestung::cache;

cH_Ruestung::cH_Ruestung(const std::string& name ,bool create)
{
 cH_Ruestung *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  std::cerr << "Rüstung '" << name << "' nicht im Cache\n";
  if (create)
  {  Tag t2("Rüstung"); 
     t2.setAttr("Abkürzung",name);
     t2.setAttr("Name",name);
     *this=new Ruestung(t2);
  }
  else throw NotFound();
  }
}

Ruestung::Ruestung(const Tag &tag) 
: name(tag.getAttr("Abkürzung"))
{
  longname=tag.getAttr("Name");
  region=tag.getAttr("Region");
  lp_verlust=tag.getIntAttr("schütztLP");
  min_staerke=tag.getIntAttr("minimaleStärke");
  const Tag *Verlust=tag.find("Verlust");
  if (Verlust)
  {  rw_verlust=Verlust->getIntAttr("RW");
     b_verlust=Verlust->getIntAttr("B");
     abwehr_bonus_verlust=Verlust->getIntAttr("Abwehrbonus");;
     angriffs_bonus_verlust=Verlust->getIntAttr("Angriffsbonus");
     vollruestungsabzug=Verlust->getIntAttr("Vollrüstung");
     behinderung_wie=Verlust->getAttr("BehinderungWie");
  }
  else
     rw_verlust=b_verlust=abwehr_bonus_verlust=angriffs_bonus_verlust=0;
}

int Ruestung::AbwehrBonus_Verlust(int abwehr_bonus) const
{
  if(abwehr_bonus_verlust<=abwehr_bonus) return abwehr_bonus_verlust;
  else return 0;
} 

int Ruestung::AngriffsBonus_Verlust(int angriffs_bonus) const
{
  if(angriffs_bonus_verlust<=angriffs_bonus) return angriffs_bonus_verlust;
  else return 0;
}


int Ruestung::B_Verlust(const double &ueberlast,const Grundwerte &Werte,bool &ew) const
{
   ew=false;
   int reduce;
   const int D=Werte.Spezies()->B_Durchschnitt();
   std::string BW=BehinderungWie();
   if     (BW=="KR") reduce = D/6;
   else if(BW=="PR") reduce = D/3;
   else if(BW=="VR") reduce = D/2;
   else if(BW=="RR") reduce = (D*2)/3;
   else reduce=0;

   if     (ueberlast<1) return reduce;
   else if(ueberlast<5) 
     {
      if(BW=="OR" || BW=="TR" || BW=="LR") reduce += D/6;
      else if(BW=="KR")  reduce += D/3;
      else if(BW=="PR") {reduce += D/2;       ew=true;}
      else if(BW=="VR") {reduce += (D*3)/4;   ew=true;}
      else              {reduce  = Werte.B(); ew=true;}
     }
   else if(ueberlast<9) 
     {
      if(BW=="OR" || BW=="TR" || BW=="LR") reduce += D/3;
      else if(BW=="KR") {reduce += D/2;      ew=true;}
      else if(BW=="PR") {reduce += (D*3)/4;  ew=true;}
      else              {reduce  = Werte.B();ew=true;}
     }
   else if(ueberlast<=20) 
     {
      ew=true;
      if(BW=="OR" || BW=="TR" || BW=="LR") reduce += D/2;
      else if(BW=="KR") reduce += (D*3)/4;   
      else              reduce  = Werte.B(); 
     }
   else reduce = Werte.B();
   return reduce;
}

cH_Ruestung cH_Ruestung::load(const Tag &t,bool &is_new)
{  cH_Ruestung *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
   {  cH_Ruestung r2=new Ruestung(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Ruestung_All::load(std::list<cH_Ruestung> &list,const Tag &t)
{  bool is_new=false;
   cH_Ruestung z=cH_Ruestung::load(t,is_new);
   if (is_new) list.push_back(z);
}

void Ruestung_All::load(std::vector<cH_Ruestung> &list,const Tag &t)
{  bool is_new=false;
   cH_Ruestung z=cH_Ruestung::load(t,is_new);
   if (is_new) list.push_back(z);
}

