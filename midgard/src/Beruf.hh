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

#ifndef _BERUF_HH
#  define _BERUF_HH

#include <gtk--/progressbar.h>
#include "MidgardBasicElement.hh"


class Beruf : public MidgardBasicElement
{
      std::string geschlecht; 
      int klasse;
//      vector<std::string> stand;
      vector<std::string> vorteile;
      bool u,v,m,a,typ_k,typ_z,stadt,land;
      
/*
      struct st_Voraussetzung {int st;int gw;int gs;int ko;int in;int zt;int au;int pa;
                           int sb;std::string geschlecht;std::string typ;
         st_Voraussetzung()
            : st(0),gw(0),gs(0),ko(0),in(0),zt(0),au(0),pa(0),sb(0) {} 
         st_Voraussetzung(int _st,int _gw,int _gs,int _ko,int _in,int _zt,int _au,
                       int _pa, int _sb,std::string _geschlecht,
                       std::string _typ)
            : st(_st),gw(_gw),gs(_gs),ko(_ko),in(_in),zt(_zt),au(_au),pa(_pa),
              sb(_sb),geschlecht(_geschlecht),typ(_typ) {} };
     st_Voraussetzung voraussetzung; 
*/
     void get_Beruf();      
  public:
//      Beruf() {}
#ifndef USE_XML  
      Beruf(std::string n) : MidgardBasicElement(n)
          {get_Beruf();}
#else
      Beruf(const Tag *t) : MidgardBasicElement(t,t->getAttr("Name"))
          {get_Beruf();}
#endif

     enum MBEE What() const {return MidgardBasicElement::BERUF;}
     std::string What_str() const {return "Beruf";}

     bool Stand(const std::string& stand) const;
     bool Typ(const vector<cH_Typen>& Typ) const;
     bool Land() const {return land;}
     bool Stadt() const {return stadt;}
//     std::string Name() const {return name;}
//     std::string Region() const {return region;}
//     int Lernpunkte() const {return lernpunkte;}

//     bool Voraussetzungen(const Grundwerte& Werte,const vector<cH_Typen>& Typ) const;
     std::vector<string> Vorteile() const {return vorteile;}
     std::string Beruf::get_Vorteile() const;
     int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion

};


class cH_Beruf : public Handle<const Beruf>
{
    typedef CacheStatic<std::string,cH_Beruf> cache_t;
    static cache_t cache;
    cH_Beruf(const Beruf *s) : Handle<const Beruf>(s) {};
    friend class std::map<std::string,cH_Beruf>;
    cH_Beruf(){};
 public:
    cH_Beruf(const std::string& n IF_XML(,bool create=false));
#ifdef USE_XML    
    cH_Beruf(const Tag *tag);
#endif

    cH_Beruf(const cH_MidgardBasicElement &x) : Handle<const Beruf>
      (dynamic_cast<const Beruf *>(&*x)){}
};

class Beruf_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Beruf_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
