// $Id: Zauber.hh,v 1.47 2002/12/11 18:18:50 christof Exp $               
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

#ifndef ZAUBERCLASS
#define ZAUBERCLASS
#include "MidgardBasicElement.hh"
#include "Typen.hh"
class cH_Zauber;
class Random;

class Zauber : public MidgardBasicElement
{
   std::string ap;//, name;
   std::string  art, stufe, zauberdauer, reichweite,
      wirkungsziel, wirkungsbereich, wirkungsdauer, ursprung,
      material, agens, prozess, reagens, beschreibung,
      zauberart,element; 
   bool spruchrolle;
   mutable double spruchrolle_faktor;
   mutable std::map<cH_Typen,std::string> map_typ_agens;

   void get_Zauber();
 public: 
   Zauber(const Tag *t) 
      : MidgardBasicElement(t,t->getAttr("Name")),spruchrolle_faktor(1)
   { get_Zauber();get_map_typ();EP_steigern("Zauber");} 

   enum MBEE What() const {return MidgardBasicElement::ZAUBER;}
   std::string What_str() const {return "Zauber";}

   std::string Ap() const { return ap;}

   std::string Art() const { return art;}
   std::string Stufe() const {  return stufe; }
   int iStufe() const {  if (Stufe()=="groß") return 6; else return atoi(Stufe().c_str()); }
   std::string Zauberdauer() const { return zauberdauer;}
   std::string Zauberart() const { return zauberart;}
   std::string Reichweite() const {return reichweite;}   
   std::string Wirkungsziel() const {return wirkungsziel;}
   std::string Wirkungsdauer() const {return wirkungsdauer;}
   std::string Wirkungsbereich() const {return wirkungsbereich;}
   std::string Ursprung() const {return ursprung;}
   std::string Material() const { return material;}
   std::string Agens(const std::vector<cH_Typen> &Typ) const; 
   std::string Prozess() const { return prozess;}
   std::string Reagens() const { return reagens;}
   std::string Beschreibung() const { return beschreibung;}
   std::string Element() const {return element;}
   bool Spruchrolle() const {return spruchrolle;}
   double SpruchrolleFaktor() const {return spruchrolle_faktor;}
   void setSpruchrolleFaktor(double s) const {spruchrolle_faktor=s;}
   int Kosten_eBe(const std::string& pe,const std::string& se) const;
   int Erfolgswert_Z(const Abenteurer &A) const;
   int MaxErfolgswert(const Abenteurer &A) const 
         {return 0;} //wg. virtueller Funktion
   int get_spezial_zauber_for_magier(const Abenteurer &A,const std::string& standard) const;

   bool spruchrolle_wuerfeln(const Abenteurer &A,std::string &info) const;


//   static void set_Spruchrolle(std::list<cH_MidgardBasicElement>&,bool sp) const;
};


#include <Misc/germanstring.h>
class cH_Zauber : public Handle<const Zauber>
{
    typedef CacheStatic<std::string,cH_Zauber> cache_t;
    static cache_t cache;
    cH_Zauber(const Zauber *s) : Handle<const Zauber>(s) {};
    friend class std::map<std::string,cH_Zauber>;
    cH_Zauber(){}
 public:
   cH_Zauber(const std::string& name, bool create=false) ;
   cH_Zauber(const Tag *tag);

   cH_Zauber(const cH_MidgardBasicElement &x) : Handle<const Zauber> 
      (dynamic_cast<const Zauber *>(&*x)){}

 class sort {
      public:
         enum esort {NAME,STUFE,URSPRUNG};
      private: 
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
//         bool operator() (cH_Zauber x,cH_Zauber y) const
         bool operator() (MBEmlt _x,MBEmlt _y) const
           { 
            cH_Zauber x(_x->getMBE());
            cH_Zauber y(_y->getMBE());
            switch(es) {
               case(NAME) : return germanstring(x->Name()) < germanstring(y->Name())  ;
               case(STUFE): return x->Stufe() < y->Stufe();
               case(URSPRUNG): return germanstring(x->Ursprung()) < germanstring(y->Ursprung()) ;
           }}
    };

};


class Zauber_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Zauber_All();
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
