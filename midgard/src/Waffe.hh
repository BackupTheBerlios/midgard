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

#ifndef _WAFFE_HH
#  define _WAFFE_HH
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Grundwerte.hh"

class cH_Waffe;
class WaffeBesitz;
class Abenteurer;

class Waffe : public MidgardBasicElement
{
   protected:
     Waffe():MidgardBasicElement("xxx"){} //wg. WaffeBesitz :-(
   public:
     struct st_alias { std::string name; std::string region; 
         std::string schaden;int schaden_bonus; int angriffs_mod;
      st_alias( std::string n,std::string r,std::string s,int b, int a)
        :name(n),region(r),schaden(s),schaden_bonus(b),angriffs_mod(a){}
      };
   private:
     std::string grundkenntnisse, art, art2;
     std::string schaden;
     std::string waffenrang, wm_abwehr_leicht, wm_abwehr_schwer,
         voraussetzung;
     int schwierigkeit,st,gw,gs,reichweite_0,reichweite_n,
         reichweite_m,reichweite_f;
     int lern_land,lern_stadt, anfangswert;
     int schaden_bonus,schaden_bonus2;
     std::list<st_alias> list_alias;
     std::vector<std::string> vec_voraussetzung_W, vec_voraussetzung_F;

     void get_Waffe();
     void get_Alias();
     int St() const {return st;}
     int Gw() const {return gw;}
     int Gs() const {return gs;}
  public:
     Waffe(const Tag *t)
      :MidgardBasicElement(t,t->getAttr("Name")),lern_land(0),lern_stadt(0)
     {get_Waffe(); get_Alias(); get_map_typ();get_Steigern_Kosten_map();
      EP_steigern("Waffen"); }

     enum MBEE What() const {return MidgardBasicElement::WAFFE;}
     std::string What_str() const {return "Waffe";}

     const std::list<st_alias>& Alias() const {return list_alias;}     
     std::string Grundkenntnis() const {return grundkenntnisse;}
     int LernLand() const {return lern_land;}
     int LernStadt() const {return lern_stadt;}
     std::string Region(const std::string& name) const ;

     std::string Art() const {return art;}
     std::string Art2() const {return art2;}
     std::string Schaden(const std::string& name) const;
     int Schaden_Bonus(const std::string& name) const;
     int Schaden_Bonus2(const std::string& name) const;
     std::string Waffenrang() const {return waffenrang;}
     std::string WM_Abwehr() const;
     int WM_Angriff(const std::string& name) const;
     std::string Reichweite() const ;

     int Schwierigkeit() const {return schwierigkeit;}
     std::string Schwierigkeit_str() const;
     int Anfangswert() const {return anfangswert;}
     std::string Voraussetzung() const {return voraussetzung;}
     bool Voraussetzung(const Abenteurer &A,bool anzeigen=true) const;
     bool Verteidigung() const {if(Art()=="Verteidigung") return true; else return false;}

     bool Grundkenntnis_vorhanden(const std::list<MBEmlt>&) const;
     int Maxwert(const std::vector<cH_Typen>& Typ) const;
     int MaxErfolgswert(const Abenteurer &A) const; 


     static std::map<std::string,std::string> fill_map_alias_waffe();
     static std::string Waffe::get_Verteidigungswaffe(int ohne_waffe,
         const std::list<MBEmlt>& list_Waffen,
         const std::list<WaffeBesitz>& list_Waffen_besitz,
         const Abenteurer &A);
     static void setSpezialWaffe(const std::string& name, std::list<MBEmlt>& list_Waffen_gelernt);
};

class cH_Waffe : public Handle<const Waffe>
{
    typedef CacheStatic<std::string,cH_Waffe> cache_t;
    static cache_t cache;
    cH_Waffe() {};
    friend class std::map<std::string,cH_Waffe>;
 public:
    cH_Waffe(const Waffe *s) : Handle<const Waffe>(s) {};
    cH_Waffe(const std::string& n,bool create=false);
    cH_Waffe(const Tag *tag);

    cH_Waffe(const cH_MidgardBasicElement &x) : Handle<const Waffe>
      (dynamic_cast<const Waffe *>(&*x)){}

};

class Waffe_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Waffe_All();
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
class WaffeBesitzLernen
{
   int Ewaffe,Awaffe;
   bool magisch;

 public:
   WaffeBesitzLernen() :  Ewaffe(0),Awaffe(0),magisch(false) {}

   void set_EWaffe(int i)  {Ewaffe=i;}
   void set_AWaffe(int i)  {Awaffe=i;}
   void add_EWaffe(int i)  {Ewaffe+=i;}
   void add_AWaffe(int i)  {Awaffe+=i;}
   int EWaffe() const {return Ewaffe;}
   int AWaffe() const {return Awaffe;}

   void setMagisch(bool b) {magisch=b;}
   bool getMagisch() const {return magisch;}
};


class WaffeBesitz : public MidgardBasicElement_mutable
{
     std::string alias_name;
     int av_bonus,sl_bonus;
     std::string magisch,region;

  public:
     WaffeBesitz(const cH_Waffe& w,std::string b,
                  int a,int s,const std::string &m,const std::string &r)
      : MidgardBasicElement_mutable(&*w),
            alias_name(b),av_bonus(a),sl_bonus(s),magisch(m),region(r)
            {}

     enum MidgardBasicElement::MBEE What() const {return MidgardBasicElement::WAFFEBESITZ;}
     std::string What_str() const {return "WaffeBesitz";}

     cH_Waffe Waffe() const {return cH_Waffe(&*getMBE());}
     std::string AliasName() const {return alias_name;}
     int av_Bonus() const {return av_bonus;}
     int sl_Bonus() const {return sl_bonus;}
     std::string Bonus() const;
     std::string Magisch() const {return magisch;}
     std::string Schaden(const Grundwerte& Werte,const std::string& name) const;
     std::string Region() const {return region;}
      
     void set_av_Bonus(int a) {av_bonus=a;}
     void set_sl_Bonus(int a) {sl_bonus=a;}
     void set_Magisch(std::string a) {magisch=a;}

     bool operator == (const WaffeBesitz& b) const
         {return (*this)->Name()==b->Name()
           && Bonus()==b.Bonus() && Magisch()==b.Magisch();}

};


class WaffenBesitz_sort_magbonus
{ public : bool operator() (WaffeBesitz x, WaffeBesitz y) const
      { return x.av_Bonus() > y.av_Bonus()  || 
              (x.av_Bonus() == y.av_Bonus() && x.sl_Bonus() > y.sl_Bonus())||
              (x.av_Bonus() == y.av_Bonus() && x.sl_Bonus()== y.sl_Bonus() &&
               x.Magisch() > y.Magisch() );}}; 
class WaffenBesitz_sort_name
{ public : bool operator() (WaffeBesitz x, WaffeBesitz y) const
      { return x->Name() < y->Name();}};

#endif
