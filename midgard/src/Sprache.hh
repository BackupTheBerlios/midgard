// $Id: Sprache.hh,v 1.19 2002/02/13 11:21:00 thoma Exp $               
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
#include "Ausnahmen.hh"
#include "Fertigkeiten.hh"
#include <gtk--/progressbar.h>
class cH_Sprache;

class Sprache : public MidgardBasicElement
{
     std::vector<std::string> VSchrift;
     bool alte_sprache,minderheit;
     int maxwert;
     std::vector<int> V_sprachgruppe;

     void get_Sprache();
     int Grundkosten() const {return kosten;}
     bool Sprachgruppe(const std::vector<int>& V2) const;
     std::vector<int> getVSprachgruppe() const {return V_sprachgruppe;}

  
  public:
#ifndef USE_XML
   Sprache(const std::string& n) : MidgardBasicElement(n)
      {get_Sprache();get_map_typ();get_Steigern_Kosten_map();
         EP_steigern("Sprache");}
#else
   Sprache(const Tag *t) : MidgardBasicElement(t,t->getAttr("Name"))
      {get_Sprache();get_map_typ();get_Steigern_Kosten_map();
         EP_steigern("Sprache");}
#endif
   enum MBEE What() const {return MidgardBasicElement::SPRACHE;}
   std::string What_str() const {return "Sprache";}

   std::string Schriften() const;
   const std::vector<std::string> &Schrift() const  {return VSchrift; }
   const std::vector<pair<std::string,int> > SchriftWert(const std::list<cH_MidgardBasicElement>& list_Schrift) const;

   bool Alte_Sprache() const {return alte_sprache;}    
   bool Minderheit() const {return minderheit;}    
   int MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const;
   int Kosten(const std::vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const;
   std::list<cH_MidgardBasicElement> VerwandteSprachen(const std::list<cH_MidgardBasicElement>& gelernte_listSprache,const std::list<cH_MidgardBasicElement>& listSprache) const;

   static std::list<cH_MidgardBasicElement> Sprache::cleanVerwandteSprachen(std::list<cH_MidgardBasicElement> L);

};


class cH_Sprache : public Handle<const Sprache>
{
    typedef CacheStatic<std::string,cH_Sprache> cache_t;
    static cache_t cache;
    cH_Sprache(const Sprache *s) : Handle<const Sprache>(s) {};
    friend class std::map<std::string,cH_Sprache>;
    cH_Sprache(){};
  public:
   cH_Sprache(const std::string& name IF_XML(,bool create=false));
#ifdef USE_XML
   cH_Sprache(const Tag *tag);
#endif

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
