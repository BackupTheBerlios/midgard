/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#ifndef ZAUBERWERKCLASS
#define ZAUBERWERKCLASS
class Grundwerte;
#include "MidgardBasicElement.hh"
#include "Typen.hh"
class cH_Zauberwerk;


class Zauberwerk : public MidgardBasicElement
{
   std::string stufe, art;
   std::string preis, zeitaufwand; 

   enum MBEE What() const {return MidgardBasicElement::ZAUBERWERK;}
   std::string What_str() const {return "Zauberwerk";}
   struct st_vor{std::string voraussetzung; std::string op;
          st_vor(){};
          st_vor(std::string v,std::string o) 
               : voraussetzung(v),op(o){} };
   std::vector<st_vor> vec_vor; // Zaubersprüche
   std::vector<st_vor> vec_vorF; // Fertigkeiten

   void getVoraussetzungen(const Tag &t);
   void getVoraussetzungenFert(const Tag &t);
   void get_Zauberwerk(const Tag &t);
 public:
   Zauberwerk(const Tag &t);
   void load(const Tag &t);

   virtual bool operator==(const MidgardBasicElement& b) const
      {return MidgardBasicElement::operator==(b) && 
              Art()==static_cast<const Zauberwerk&>(b).Art() &&
              Stufe()==static_cast<const Zauberwerk&>(b).Stufe() ;}
                                                     
   std::string Art() const { return art; }
   std::string Stufe() const {  return stufe; }
   int iStufe() const {  if (Stufe()=="groÃŸ") return 6; else return atoi(Stufe().c_str()); }
   std::string Zeitaufwand() const { return zeitaufwand;}
   std::string Preis() const { return preis; }

   bool Voraussetzungen(const std::list<MBEmlt>& listZauber) const;
   bool Voraussetzungen_Fertigkeit(const std::list<MBEmlt>& listFert) const;
   int MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion
};

class cH_Zauberwerk : public Handle<const Zauberwerk>
{
    struct st_index {std::string name;std::string art; std::string stufe;
           st_index(std::string n,std::string a,std::string s)
                    :name(n),art(a),stufe(s) {}
           bool operator<(const st_index& b) const {
               return name<b.name ||
                     (name==b.name && art<b.art) || 
                     (name==b.name && art==b.art && stufe<b.stufe) ;}
            };
    typedef CacheStatic<st_index,cH_Zauberwerk> cache_t;
    static cache_t cache;
    cH_Zauberwerk(const Zauberwerk *s) : Handle<const Zauberwerk>(s) {};
    friend class std::map<st_index,cH_Zauberwerk>;
    cH_Zauberwerk(){};
 public:
    cH_Zauberwerk(const std::string& name, const std::string& art,const std::string& stufe ,bool create=false);
    static cH_Zauberwerk load(const Tag &tag,bool &is_new);

    cH_Zauberwerk(const cH_MidgardBasicElement &x) : Handle<const Zauberwerk>
      (dynamic_cast<const Zauberwerk *>(&*x)){}

 class sort {
      public:
         enum esort {NAME,STUFE,ART};
      private:
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (MBEmlt _x,MBEmlt _y) const
           { 
            cH_Zauberwerk x(_x->getMBE());
            cH_Zauberwerk y(_y->getMBE());
            switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(STUFE): return x->Stufe() < y->Stufe();
               case(ART): return x->Art() < y->Art() ;  
           }}
    };

};


class Zauberwerk_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Zauberwerk_All();
   static void load(std::list<cH_MidgardBasicElement> &list,const Tag &t);
   const std::list<cH_MidgardBasicElement> &get_All() const {return list_All;}
};

#endif
