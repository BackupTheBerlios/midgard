// $Id: Preise.hh,v 1.25 2002/11/19 09:55:17 thoma Exp $
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

#ifndef PREISECLASS
#define PREISECLASS
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include<string>
#include<vector>
#include<list>
#include "xml.h"

class Preise : public HandleContent
{
   std::string name,einheit,art,art2;
   std::string region;
   double kosten,gewicht;
   const Tag *tag;
   static Tag eigenerArtikel;
   bool unverkauflich;
   bool ruestung; // Ruestung wird bei der Belastung nicht mitgezählt

   void get_Preise();
 public:
   Preise(const Tag *_tag)
     : name(_tag->getAttr("Ware")), art(_tag->getAttr("Art")), tag(_tag)  
      ,unverkauflich(false)
     {get_Preise();}
   Preise(const std::string& _name, const std::string& _art, const Tag *_tag)
     : name(_name), art(_art), tag(_tag),unverkauflich(false)
     {get_Preise();}

 std::string Art() const {  return art; }
 std::string Art2() const {  return art2; }
 std::string Name()  const {  return name; }
 std::string Region()  const {  return region; }

 bool Unverkauflich() const {return unverkauflich;}
 bool Ruestung() const {return ruestung;}
 double Kosten() const { return kosten ; }
 double Gewicht() const { return gewicht ; }
 std::string Einheit()  const {  return einheit; }
 bool ist_eigener_Artikel() const { return tag==&eigenerArtikel; }

 static void saveArtikel(const std::string &Filename,midgard_CG *hauptfenster,
     const std::string &art,const std::string &art2,
     const std::string &name,const double &preis, const std::string &einheit,
     const double &gewicht,const std::string &region);
};

class cH_Preise : public Handle<const Preise>
{
    typedef CacheStatic<std::string,cH_Preise> cache_t;
    static cache_t cache;
    cH_Preise(const Preise *s) : Handle<const Preise>(s) {};
    friend class std::map<std::string,cH_Preise>;
    cH_Preise(){};
 public:
    cH_Preise(const std::string& name ,bool create=false);
    cH_Preise(const Tag *tag);
    cH_Preise(const std::string& name, const std::string& art, const Tag *tag);
    bool operator==(const std::string& name)
    {  return (*this)->Name()==name; }

 class sort {
      public:
         enum esort {NAME,ART};
      private: 
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Preise x,cH_Preise y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(ART)   : return x->Art() < y->Art() ;
           }}
    };
};

class Preise_All
{
   std::list<cH_Preise> list_All;
  public:
   Preise_All();
   std::list<cH_Preise> get_All() const {return list_All;}
};

bool operator!=(const cH_Preise &a, const std::string &b);



///////////////////////////////////

class PreiseNewMod :  public HandleContent
{
   public: 
      struct st_preismod{std::string spezifikation; double preis_faktor;
             st_preismod() : preis_faktor(1) {};
             st_preismod(std::string s,double p) 
                  :spezifikation(s),preis_faktor(p) {} };

   private:
      const Tag *tag;
      std::string name;  // Kleidung, Waffen, ...

      // Farbe | Stand | Material | ...
      

      std::map<std::string,std::vector<st_preismod> > VS;  
   public:
      PreiseNewMod(const Tag *_tag) : tag(_tag) { getPNM(); }
      
      void getPNM();
      
      std::string Name() const {return name;}
      const std::map<std::string,std::vector<st_preismod> > &VSpezifikation() const {return VS; }
               
};

class cH_PreiseNewMod : public Handle<const PreiseNewMod>
{
    typedef CacheStatic<std::string,cH_PreiseNewMod> cache_t;
    static cache_t cache;
    cH_PreiseNewMod(const PreiseNewMod *s) : Handle<const PreiseNewMod>(s) {};
    friend class std::map<std::string,cH_PreiseNewMod>;
    cH_PreiseNewMod(){}

   public:
      cH_PreiseNewMod(const std::string& name, bool create=false) ;
      cH_PreiseNewMod(const Tag *tag);

};

class PreiseNewMod_All
{
   std::vector<cH_PreiseNewMod> list_All;
 public:
   PreiseNewMod_All();
   std::vector<cH_PreiseNewMod> get_All() const {return list_All;}
};
           
           



class PreiseMod : public HandleContent
{
 public: 
   struct st_payload{std::string name; double faktor;
          st_payload() : faktor(0) {}
          st_payload(std::string n, double f) 
             : name(n), faktor(f) {}
          };
 private:
   const Tag *tag;
   std::string art,art2,typ;
   int nr;
   st_payload payload;
   void get_PreiseMod();
 public:
   PreiseMod(const Tag *_tag)
     : tag (_tag), nr(0) {get_PreiseMod();}

 std::string Art() const {  return art; }
 std::string Art2() const {  return art2; }
 std::string Typ() const {  return typ; }
 int Nr() const {  return nr; }
 st_payload Payload() const {return payload;}

// static saveGruppe(std::string art,int typ, std::string eigenschaft);
};

class cH_PreiseMod : public Handle<const PreiseMod>
{
   struct st_index{std::string art; std::string art2; std::string typ;int nr;
          st_index() :nr(0) {}
          st_index(std::string a,std::string a2,std::string t,int n) 
               : art(a),art2(a2),typ(t),nr(n) {}
          bool operator<(const st_index& b) const
            {return art<b.art || (art==b.art && art2<b.art2) ||
              ( art==b.art && art2==b.art2 && typ<b.typ)
                    || (art==b.art && art2==b.art2 &&typ==b.typ&&nr<b.nr) ;}          
         };

    typedef CacheStatic<st_index,cH_PreiseMod> cache_t;
    static cache_t cache;
    friend class std::map<st_index,cH_PreiseMod>;
    cH_PreiseMod(){};
 public:
    cH_PreiseMod(const std::string& art,const std::string& art2,const std::string typ,const int &nr);
    cH_PreiseMod(const Tag *tag);
    cH_PreiseMod(const PreiseMod *s) : Handle<const PreiseMod>(s) {};
};

class PreiseMod_All
{
   std::list<cH_PreiseMod> list_All;
  public:
   PreiseMod_All();
   std::list<cH_PreiseMod> get_All() const {return list_All;}
};




#endif
