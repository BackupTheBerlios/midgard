// $Id: Sprache.hh,v 1.28 2002/08/20 06:12:44 thoma Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002 Christof Petig
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

#ifndef SPRACHECLASS
#define SPRACHECLASS
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Fertigkeiten.hh"
#include <gtk--/progressbar.h>
class cH_Sprache;
class VAbenteurer;
class midgard_CG;

/*
class Sprache_und_Schrift
{
   public:
      struct st_sus{std::string schrift; int wert;
             st_sus(std::string s,int w) :schrift(s),wert(w) {}};
   private:
      MidgardBasicElement_mutable sprache;
      std::vector<st_sus> schriften;
   public:
      Sprache_und_Schrift(const MidgardBasicElement_mutable& M)
         : sprache(M) {}

      MidgardBasicElement_mutable getSprache() const {return sprache;}
      std::vector<st_sus> getSchriften() const {return schriften;}
};
*/

class Sprache : public MidgardBasicElement
{
  public:
         struct st_sprachen_schrift{MidgardBasicElement_mutable sprache;
               std::vector<pair<std::string,int> > vs;
               st_sprachen_schrift(const MidgardBasicElement_mutable &s,
                               const std::vector<pair<std::string,int> > &v)
                    :sprache(s),vs(v) {}   
               st_sprachen_schrift(const MidgardBasicElement_mutable &s)
                    :sprache(s) {}
               };

  private:
     std::vector<std::string> VSchrift;
     bool alte_sprache,minderheit,muttersprache;
     int maxwert;
     std::vector<int> V_sprachgruppe;

     void get_Sprache();
     int Grundkosten() const {return kosten;}
     bool Sprachgruppe(const std::vector<int>& V2) const;
     std::vector<int> getVSprachgruppe() const {return V_sprachgruppe;}

  
  public:
   Sprache(const Tag *t) : MidgardBasicElement(t,t->getAttr("Name"))
      {get_Sprache();get_map_typ();get_Steigern_Kosten_map();
         EP_steigern("Sprache");}
   enum MBEE What() const {return MidgardBasicElement::SPRACHE;}
   std::string What_str() const {return "Sprache";}

   std::string Schriften() const;
   const std::vector<std::string> &Schrift() const  {return VSchrift; }
   const std::vector<pair<std::string,int> > SchriftWert(const std::list<MidgardBasicElement_mutable>& list_Schrift) const;

   bool Alte_Sprache() const {return alte_sprache;}    
   bool Minderheit() const {return minderheit;}    
   bool Muttersprache() const {return muttersprache;}    
   int MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const;
   int Kosten(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const;
//private:
   std::list<MidgardBasicElement_mutable> VerwandteSprachen(const int erfolgswert,const std::list<MidgardBasicElement_mutable>& gelernte_listSprache,const std::list<cH_MidgardBasicElement>& listSprache) const;
   static std::list<MidgardBasicElement_mutable> cleanVerwandteSprachen(std::list<MidgardBasicElement_mutable> L);
public:
   static std::list<MidgardBasicElement_mutable> getVerwandteSprachen(const std::list<MidgardBasicElement_mutable>& gekonnteSprachen,const std::list<cH_MidgardBasicElement>& alleSprachen);

   bool ist_erlaubt(const VAbenteurer& A,bool nachbarland=false) const;
   int getHoeherenErfolgswert(const std::list<MidgardBasicElement_mutable>& gelernte_listSprache,
                              const std::list<cH_MidgardBasicElement>& listSprache) const;

   void setMuttersprache(bool b) {muttersprache=b;}
   

   static void setErfolgswertMuttersprache(MidgardBasicElement_mutable &M,int in,int bonus) 
      {setErfolgswertMutterGastlandsprache(M,"Muttersprache",in,bonus);}
   static void setErfolgswertGastlandsprache(MidgardBasicElement_mutable &M,int in) 
      {setErfolgswertMutterGastlandsprache(M,"Gastlandsprache",in,0);}
private:
   static void setErfolgswertMutterGastlandsprache(MidgardBasicElement_mutable &M,std::string mode,int in,int bonus);
};


class cH_Sprache : public Handle<const Sprache>
{
    typedef CacheStatic<std::string,cH_Sprache> cache_t;
    static cache_t cache;
    cH_Sprache(const Sprache *s) : Handle<const Sprache>(s) {};
    friend class std::map<std::string,cH_Sprache>;
    cH_Sprache(){};
  public:
   cH_Sprache(const std::string& name ,bool create=false);
   cH_Sprache(const Tag *tag);

   cH_Sprache(const cH_MidgardBasicElement &x) : Handle<const Sprache>
      (dynamic_cast<const Sprache *>(&*x)){}

};

class Sprachen_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Sprachen_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};
#endif
