// $Id: Preise.hh,v 1.7 2003/09/18 07:32:12 christof Exp $
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

#ifndef PREISECLASS
#define PREISECLASS
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include<string>
#include<vector>
#include<list>
//#include "xml.h"
class Tag;
class Datenbank;

class Preise : public HandleContent
{
   std::string name,einheit,art,art2;
   std::string region;
   std::string beschreibung;
   double kosten,gewicht;
//   friend class Preise_All;
   bool unverkauflich;
   bool ruestung; // Ruestung wird bei der Belastung nicht mitgezählt

   void get_Preise(const Tag &t);
 public:
   Preise(const Tag &_tag);
   Preise(const std::string& _name, const std::string& _art, const Tag &_tag);
   void load(const Tag &t);

 std::string Art() const {  return art; }
 std::string Art2() const {  return art2; }
 std::string Name()  const {  return name; }
 std::string Region()  const {  return region; }
 std::string Beschreibung()  const {  return beschreibung; }

 bool Unverkauflich() const {return unverkauflich;}
 bool Ruestung() const {return ruestung;}
 double Kosten() const { return kosten ; }
 double Gewicht() const { return gewicht ; }
 std::string Einheit()  const {  return einheit; }
// bool ist_eigener_Artikel() const { return tag==&Tag_eigene_Artikel; }

// warum kein Preise &?
 static void saveArtikel(const std::string &Filename, 
     const std::string &art,const std::string &art2,
     const std::string &name,const double &preis, const std::string &einheit,
     const double &gewicht,const std::string &region,
     const std::string &beschreibung);
};

class cH_Preise : public Handle<const Preise>
{
    typedef CacheStatic<std::string,cH_Preise> cache_t;
    static cache_t cache;
    cH_Preise(const Preise *s) : Handle<const Preise>(s) {};
    friend class std::map<std::string,cH_Preise>;
    friend class Preise;
    cH_Preise(){};
 public:
    cH_Preise(const std::string& name ,bool create=false);
    static cH_Preise load(const Tag &t,bool &is_new);
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

namespace Preise_All 
{  void load(std::list<cH_Preise> &list, const Tag &t);
};

bool operator!=(const cH_Preise &a, const std::string &b);



///////////////////////////////////

// vielleicht wieder in PreiseMod zurückbenennen
class PreiseNewMod :  public HandleContent
{
   public: 
      struct st_preismod{std::string spezifikation; double preis_faktor;
             st_preismod() : preis_faktor(1) {};
             st_preismod(const std::string &s,const double &p) 
                  :spezifikation(s),preis_faktor(p) {} };

   private:
      std::string name;  // Kleidung, Waffen, ...

      // Farbe | Stand | Material | ...
      

      std::map<std::string,std::vector<st_preismod> > VS;  
   public:
      PreiseNewMod(const Tag &_tag);
      void load(const Tag &t);
      void getPNM(const Tag &t);
      
      const std::string &Name() const {return name;}
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
      static cH_PreiseNewMod load(const Tag &t,bool &is_new);
};

namespace PreiseNewMod_All
{  void load(std::vector<cH_PreiseNewMod> &list, const Tag &t);
};
           
#endif
