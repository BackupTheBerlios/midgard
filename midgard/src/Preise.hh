// $Id: Preise.hh,v 1.14 2002/01/26 09:17:41 christof Exp $
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
#include <gtk--/progressbar.h>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include<string>
#include<vector>
#include<list>
#include "xml.h"

class Preise : public HandleContent
{
   std::string name,einheit,art,art2;
   double kosten,gewicht;
#ifdef USE_XML
   const Tag *tag;
   static Tag eigenerArtikel;
#endif

   void get_Preise();
 public:
#ifndef USE_XML 
   Preise(const std::string& n)
     :name(n) {get_Preise();}
#else     
   Preise(const Tag *_tag)
     : name(_tag->getAttr("Ware")), art(_tag->getAttr("Art")), tag(_tag)  
     {get_Preise();}
   Preise(const std::string& _name, const std::string& _art, const Tag *_tag)
     : name(_name), art(_art), tag(_tag)
     {get_Preise();}
#endif

 std::string Art() const {  return art; }
 std::string Art2() const {  return art2; }
 std::string Name()  const {  return name; }
 double Kosten() const { return kosten ; }
 double Gewicht() const { return gewicht ; }
 std::string Einheit()  const {  return einheit; }
#ifdef USE_XML
 bool ist_eigener_Artikel() const { return tag==&eigenerArtikel; }
#endif

 static void saveArtikel(std::string art,std::string art2,
      std::string name,double preis, std::string einheit,double gewicht);
};

class cH_Preise : public Handle<const Preise>
{
    typedef CacheStatic<std::string,cH_Preise> cache_t;
    static cache_t cache;
    cH_Preise(const Preise *s) : Handle<const Preise>(s) {};
    friend class std::map<std::string,cH_Preise>;
    cH_Preise(){};
 public:
    cH_Preise(const std::string& name IF_XML(,bool create=false));
#ifdef USE_XML
    cH_Preise(const Tag *tag);
    cH_Preise(const std::string& name, const std::string& art, const Tag *tag);
#endif    

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
   Preise_All(Gtk::ProgressBar *progressbar);
   std::list<cH_Preise> get_All() const {return list_All;}
};

///////////////////////////////////

class PreiseMod : public HandleContent
{
 public: 
   struct st_payload{std::string name; double faktor;
          st_payload() : faktor(0) {}
          st_payload(std::string n, double f) 
             : name(n), faktor(f) {}
          };
 private:
#ifdef USE_XML
   const Tag *tag;
#endif 
   std::string art,art2,typ;
   int nr;
   st_payload payload;
   void get_PreiseMod();
 public:
#ifndef USE_XML 
   PreiseMod(const std::string& a,const std::string& a2,const std::string& t,const int& n)
     :art(a),art2(a2),typ(t),nr(n) {get_PreiseMod();}
#else
   PreiseMod(const Tag *_tag)
     : tag (_tag), nr(0) {get_PreiseMod();}
#endif     

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
#ifdef USE_XML
    cH_PreiseMod(const Tag *tag);
#endif
    cH_PreiseMod(const PreiseMod *s) : Handle<const PreiseMod>(s) {};
};

class PreiseMod_All
{
   std::list<cH_PreiseMod> list_All;
  public:
   PreiseMod_All(Gtk::ProgressBar *progressbar);
   std::list<cH_PreiseMod> get_All() const {return list_All;}
};



#endif
