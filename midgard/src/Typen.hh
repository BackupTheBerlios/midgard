// $Id: Typen.hh,v 1.7 2002/01/12 08:12:25 thoma Exp $               
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

#ifndef CLASS_TYPEN_
#define CLASS_TYPEN_

#include<string>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>

class Typen : public HandleContent
{
   std::string typs;
   int typnr;
   std::string typl,typlw,typz;
   std::string zaubern,ausdauer,region,beruf;
   int stand,sb,ruestung,geld;
   mutable int opionmenu_nr;
   bool stadt,land;
   bool sprueche_mit_pp;

public:
   Typen(const std::string& n);
   Typen() : typnr(0),stand(0),sb(0),ruestung(0),geld(0),
         opionmenu_nr(0),stadt(true),land(true) {}
   
   int Nr() const {return opionmenu_nr;}
   void set_opionmenu_nr(int o) const {opionmenu_nr=o;}
   std::string Name(const std::string& geschlecht) const 
      {
//cout << "Geschlect im Typ = "<<geschlecht<<'\n';
if (geschlecht=="m") return typl; else return typlw;}
   std::string Short() const {return typs;}
   std::string Zaubern() const {return typz;}
   std::string Ausdauer() const {return ausdauer;}
   int Stand() const {return stand;}
   int Sb() const {return sb;}
   int Ruestung() const {return ruestung;}
   int Geld() const {return geld;}
   std::string Region() const {return region;}
   std::string Beruf() const {return beruf;}
   bool Land() const {return land;}
   bool Stadt() const {return stadt;}
   bool SpruecheMitPP() const {return sprueche_mit_pp;}

   bool is_mage() const 
    { if(Zaubern()=="z" || Zaubern()=="j") return true; else return false; } 
};

class cH_Typen : public Handle<const Typen>    
{
    typedef CacheStatic<std::string,cH_Typen> cache_t;
    static cache_t cache;
    cH_Typen(Typen *s) : Handle<const Typen>(s) {};
    friend class std::map<std::string,cH_Typen>;
///    cH_Typen(){};
  public:
   cH_Typen() {*this=new Typen();}
   cH_Typen(const std::string& name);
};
 
class Typen_All
{
      std::vector<cH_Typen> list_All;
   public:
      Typen_All(Gtk::ProgressBar *progressbar);
      std::vector<cH_Typen> get_All() const {return list_All;}
};
  

#endif
