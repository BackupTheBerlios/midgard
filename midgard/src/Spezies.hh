// $Id: Spezies.hh,v 1.8 2002/01/22 07:46:34 christof Exp $               
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

class Spezies : public HandleContent
{
  std::string name;
  int nr;
  int st,gw,gs,ko,in,zt,sb,au,lpbasis,ap_grad,m_abb,
       m_psy,m_phs,m_phk,alter, groesse_f,groesse_w, groesse_s, gestalt,
       b_f,b_s;
  bool land;

protected:   
  struct st_spez {std::string typen;int maxgrad;
         st_spez(std::string t,int m) : typen(t),maxgrad(m) {};
      };
private:
  std::vector<st_spez> vec_typen;

public:
   Spezies()
     :st(0),gw(0),gs(0),ko(0),in(0),zt(0),sb(0),au(0),
       lpbasis(0),ap_grad(0),m_abb(0),
       m_psy(0),m_phs(0),m_phk(0),alter(0), 
       groesse_f(0),groesse_w(0), groesse_s(0),
       gestalt(0),b_f(0),b_s(0)  {}
#ifndef USE_XML
   Spezies(const std::string& n); 
#else
   Spezies(const Tag *tag);
#endif

   std::string Name() const {return name;}
   int Nr() const {return nr;}
   int St() const {return st;}
   int Gw() const {return gw;}
   int Gs() const {return gs;}
   int Ko() const {return ko;}
   int In() const {return in;}
   int Zt() const {return zt;}
   int Sb() const {return sb;}
   int Au() const {return au;}
   int LPBasis() const {return lpbasis;}
   int AP_Grad() const {return ap_grad;}
   int Abb() const {return m_abb;}
   int Psy() const {return m_psy;}
   int Phs() const {return m_phs;}
   int Phk() const {return m_phk;}
   int Alter() const {return alter;}
   int Groesse_f() const {return groesse_f;}
   int Groesse_w() const {return groesse_w;}
   int Groesse_s() const {return groesse_s;}
   int Gestalt() const {return gestalt;}
   int B_f() const {return b_f;}
   int B_s() const {return b_s;}
//   std::vector<st_spez> get_Vec_Typen() const {return vec_typen;}
   bool Typ_erlaubt(std::string typ) const;
   bool Land() const {return land;}
   
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
    cH_Spezies(Spezies *s) : Handle<const Spezies>(s) {};
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
