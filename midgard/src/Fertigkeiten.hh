// $Id: Fertigkeiten.hh,v 1.31 2002/01/26 09:17:41 christof Exp $               
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

#ifndef _FERTIGKEITEN_HH
#  define _FERTIGKEITEN_HH
#include "MidgardBasicElement.hh"
#include "Typen.hh"
//#include "Ausnahmen.hh"
#include <gtk--/progressbar.h>


class Fertigkeit : public MidgardBasicElement
{
     std::string attribut;
     mutable std::string zusatz; // Für verschiedene Länder bei Landeskunde
     int lern_unge, lern_land,lern_stadt, anfangswert0, anfangswert,
         ungelernt,berufskategorie,maxerfolgswert,maxunterweisung;
     struct st_Voraussetzung {int st;int gw;int gs;int ko;int in;int zt;int au;int pa;
                           int sb;int rw;std::string fert;
         st_Voraussetzung()
            : st(0),gw(0),gs(0),ko(0),in(0),zt(0),au(0),pa(0),
              sb(0),rw(0) {} 
         st_Voraussetzung(int _st,int _gw,int _gs,int _ko,int _in,int _zt,int _au,int _pa,
                       int _sb,int _rw,std::string _fert)
            : st(_st),gw(_gw),gs(_gs),ko(_ko),in(_in),zt(_zt),au(_au),pa(_pa),
              sb(_sb),rw(_rw),fert(_fert) {} };
     st_Voraussetzung voraussetzung;
     mutable bool pflicht;
//     IF_XML(std::string steigern_wie;) ??

     void get_Fertigkeit();
//     void get_Steigern_Kosten_map();

  public:
#ifndef USE_XML  
     Fertigkeit(const std::string& n)
      : MidgardBasicElement(n),lern_unge(0),lern_land(0),lern_stadt(0),pflicht(false) 
      {get_Fertigkeit(); get_map_typ(); get_Steigern_Kosten_map();
       EP_steigern(Name());}
#else
     Fertigkeit(const Tag *t)
      :MidgardBasicElement(t,t->getAttr("Name")),lern_unge(0),lern_land(0),lern_stadt(0),pflicht(false) 
      {get_Fertigkeit(); get_map_typ(); get_Steigern_Kosten_map();
       EP_steigern(Name());}
#endif
     enum MBEE What() const {return MidgardBasicElement::FERTIGKEIT;}
     std::string What_str() const {return "Fertigkeit";}


     std::string Zusatz() const {return zusatz;}
     void setZusatz(std::string z) const {zusatz=z;}
     std::string Attribut() const {return attribut;}
     int FErfolgswert(const Grundwerte &Werte) const;
     int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const;
     int MaxUnterweisung() const {return maxunterweisung;}
     int LernUnge() const {return lern_unge;}
     int LernLand() const {return lern_land;}
     int LernStadt() const {return lern_stadt;}
     int Anfangswert0() const {return anfangswert0;}
     int Anfangswert() const {return anfangswert;}
     int Ungelernt() const {return ungelernt;}
     int Berufskategorie() const {return berufskategorie;}
     std::string Voraussetzung() const {return voraussetzung.fert;}
     bool Voraussetzungen(const Grundwerte& Werte) const;
     std::string Pflicht() const {if (pflicht) return "*"; return "";}
     int AttributBonus(const Grundwerte& Werte) const;
};

class cH_Fertigkeit : public Handle<const Fertigkeit>
{
/*
   struct st_index {std::string name; int lernpunkte; 
      bool operator == (const st_index& b) const
         {return (name==b.name && lernpunkte==b.lernpunkte);}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && lernpunkte<b.lernpunkte ); }
      st_index(std::string n, int l):name(n),lernpunkte(l){}
      st_index(){}
      };
*/
    typedef CacheStatic<std::string,cH_Fertigkeit> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Fertigkeit>;
    cH_Fertigkeit(){};
 public:
    cH_Fertigkeit(const Fertigkeit *s) : Handle<const Fertigkeit>(s) {};
    cH_Fertigkeit(const std::string& n IF_XML(,bool create=false));
#ifdef USE_XML    
    cH_Fertigkeit(const Tag *tag);
#endif

    cH_Fertigkeit(const cH_MidgardBasicElement &x) : Handle<const Fertigkeit>
      (dynamic_cast<const Fertigkeit *>(&*x)){}

   class sort {
      public:
         enum esort {LERN_L,LERN_S};
      private:
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Fertigkeit x,cH_Fertigkeit y) const
           { switch(es) {
               case(LERN_L) : return x->LernLand()  < y->LernLand()  ;
               case(LERN_S) : return x->LernStadt() < y->LernStadt()  ;
           }}
    };
};

class Fertigkeiten_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Fertigkeiten_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
