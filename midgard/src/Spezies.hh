// $Id: Spezies.hh,v 1.11 2002/03/02 16:24:38 thoma Exp $               
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

#ifndef _SPEZIES_HH
#  define _SPEZIES_HH

#include <gtk--/progressbar.h>
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <string>
#include "xml.h"
#include <list>

class Grundwerte;
class cH_MidgardBasicElement;

class Spezies : public HandleContent
{
  std::string name;
  int nr;
  int hand_bonus;
  int st,gw,gs,ko,in,zt,sb,au,lp,ap_bonus,ap_grad_fak,
       psy,psy100,phs,phs100,phk,phk100,
       alter_fak, groesse_wanz,groesse_wuerfel,groesse_bonus, 
       gewicht_wanz, gewicht_bonus, 
       b_wanz,b_bonus,raufen;
  bool land,only_nsc;

protected:   
  struct st_spez {std::string typen;int maxgrad;
         st_spez(std::string t,int m) : typen(t),maxgrad(m) {};
      };
  struct st_angebfert {std::string art;std::string name;int erfolgswert;int lp;
         st_angebfert(std::string a, std::string n,int e,int l) 
            : art(a),name(n),erfolgswert(e),lp(l) {};
      };
private:
  std::vector<st_spez> vec_typen;
  std::vector<st_angebfert> vec_angebfert;

public:
   Spezies()
     :hand_bonus(0),st(0),gw(0),gs(0),ko(0),in(0),zt(0),sb(0),au(0),
       lp(0),ap_bonus(0),ap_grad_fak(0),
       psy(0),psy100(0),phs(0),phs100(0),phk(0),phk100(0),
       alter_fak(0),groesse_wanz(1),groesse_wuerfel(0),groesse_bonus(0),
       gewicht_wanz(0), gewicht_bonus(0),
       b_wanz(0),b_bonus(0),raufen(0) {}
   Spezies(const Tag *tag);

   std::string Name() const {return name;}
   int HandBonus() const {return hand_bonus;}
   int Nr() const {return nr;}
   int St() const {return st;}
   int Gw() const {return gw;}
   int Gs() const {return gs;}
   int Ko() const {return ko;}
   int In() const {return in;}
   int Zt() const {return zt;}
   int Sb() const {return sb;}
   int Au() const {return au;}
   int LP_Bonus() const {return lp;}
   int AP_GradFak() const {return ap_grad_fak;}
   int AP_Bonus() const {return ap_bonus;}
   int Psy(const Grundwerte &W) const;
   int Phs(const Grundwerte &W) const;
   int Phk(const Grundwerte &W) const;
   int AlterFaktor() const {return alter_fak;}
   int Groesse_Bonus() const {return groesse_bonus;}
   int Groesse_Wuerfel() const {return groesse_wuerfel;}
   int Groesse_Wanz() const {return groesse_wanz;}
   int Gewicht_Bonus() const {return gewicht_bonus;}
   int Gewicht_Wanz() const {return gewicht_wanz;}
   int B_Wanz() const {return b_wanz;}
   int B_Bonus() const {return b_bonus;}
   int Raufen() const {return raufen;}
   bool Typ_erlaubt(std::string typ) const;
   bool Land() const {return land;}
   bool onlyNSC() const {return only_nsc;}

   std::list<cH_MidgardBasicElement> getZauber() const;
   std::list<cH_MidgardBasicElement> getAngFertigkeiten() const;
   std::list<cH_MidgardBasicElement> getFertigkeiten(int &lp,const Grundwerte &Werte) const;
   std::list<cH_MidgardBasicElement> getFreiwilligeFertigkeiten(const Grundwerte &Werte) const;
   std::list<pair<std::string,int> > getSinne() const;

   bool istVerboten(const cH_MidgardBasicElement &mbe) const;
   bool istVerbotenSpielbegin(const cH_MidgardBasicElement &mbe) const;

   bool operator==(const Spezies &b) const
   {  return Name()==b.Name(); }
};

class cH_Spezies : public Handle<const Spezies>
{
    typedef CacheStatic<std::string,cH_Spezies> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Spezies>; 
    cH_Spezies(){};
  public:
//   cH_Spezies() {*this=new Spezies();}
   cH_Spezies(const std::string& name IF_XML(,bool create=false));
#ifdef USE_XML
   cH_Spezies(const Tag *tag);
#endif
    cH_Spezies(const Spezies *s) : Handle<const Spezies>(s) {};
};


class Spezies_All
{
      std::vector<cH_Spezies> list_All;
   public:
      Spezies_All(Gtk::ProgressBar *progressbar);
      std::vector<cH_Spezies> get_All() const {return list_All;}
};

bool operator==(gpointer data, const cH_Spezies &s);

#endif
