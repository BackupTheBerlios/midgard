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

#ifndef MIDGARDBASICELEMENT
#define MIDGARDBASICELEMENT
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <string>
#include <vector>
#include <list>
#include "xml.h"

class cH_Typen;
class Grundwerte;
class H_Data_beruf;
class cH_MidgardBasicElement;
class SimpleTree;
class Datenbank;
class midgard_CG;

#ifdef USE_XML
class NotFound : public std::exception
{public:
	virtual const char* what() const throw() { return "NotFound"; }
};
#endif

class MidgardBasicElement : public HandleContent
{
   private:
      // WARNUNG: Beruf wird nicht verwendet
      struct st_ausnahmen{std::string herkunft;std::string spezies;
                          std::string typ;std::string beruf;std::string stand;
                          std::string standard;
//             st_ausnahmen(){}
             st_ausnahmen(std::string h,std::string s,std::string t,
                          std::string b,std::string st,std::string sta) 
                        :herkunft(h),spezies(s),typ(t),beruf(b),stand(st),
                         standard(sta) {} };
   public:
      enum eZusatz {ZNone=0,ZTabelle=1,ZLand=2,ZWaffe=3,ZHerkunft=4,
                    ZSprache=5,ZSchrift=6};
   protected:
	const Tag *tag;
      std::string name, region;
      int kosten;
      int mutable praxispunkte,erfolgswert,lernpunkte;
      eZusatz enum_zusatz;
      mutable std::string zusatz; // F�r Zus�te bei Fertigkeiten (z.B. Abrichten, Sprache, Geheimzeichen...)
                                  // und Zauber (Tiersprache)
      std::vector<std::string> Vzusatz;
      vector<st_ausnahmen> VAusnahmen;
      mutable bool gelernt; // F�rs Lernschema
      bool nsc_only;
      enum EP_t { Nicht=0, KEP=1, ZEP=2, Beides=KEP|ZEP };
      /* EP_t (CP) */ int steigern_mit_EP;
      std::map<std::string,std::string> map_typ;
      std::map<int,int> map_erfolgswert_kosten;
      
      void get_map_typ();
      void get_Steigern_Kosten_map();
      int GrundKosten() const {  return kosten; }

   public:
      MidgardBasicElement(const std::string &n) 
            : tag(0), name(n), kosten(0),praxispunkte(0),
                              erfolgswert(0),lernpunkte(0),enum_zusatz(ZNone)
                              ,gelernt(false),nsc_only(false),steigern_mit_EP(0) {}
      MidgardBasicElement(const Tag *t,const std::string &n) 
		: tag(t), name(n), kosten(0),praxispunkte(0),
                               erfolgswert(0),lernpunkte(0),enum_zusatz(ZNone)
                              ,gelernt(false),steigern_mit_EP(0) {}

      MidgardBasicElement(const MidgardBasicElement &M);

      enum MBEE {BERUF,FERTIGKEIT,FERTIGKEIT_ANG,WAFFEGRUND,WAFFE,WAFFEBESITZ,
                 ZAUBER,ZAUBERWERK,KIDO,SPRACHE,SCHRIFT} ;
      enum TREE {OLD,NEW};

      map<std::string,std::string> get_MapTyp() const {return map_typ;}
      
      std::string Zusatz() const {return zusatz;}
      std::vector<std::string> VZusatz() const {return Vzusatz;}
      void setZusatz(std::string z) const {zusatz=z;}
      virtual eZusatz ZusatzEnum(const vector<cH_Typen>& Typ) const {return enum_zusatz;}
 
      void setGelernt(bool b) const {gelernt=b;}
      bool Gelernt() const {return gelernt;}
      bool NSC_only() const {return nsc_only;}
      void EP_steigern(const std::string fert);
      virtual std::string Name() const {return name;}
      std::string Region() const {return region;}
      std::string RegionString(const Datenbank &D) const;
      int Lernpunkte() const {return lernpunkte;};
      void set_Lernpunkte(int l) const {lernpunkte=l;}
      int Erfolgswert() const {return erfolgswert;};
      void set_Erfolgswert(int e) const {erfolgswert=e;}
      void add_Erfolgswert(int e) const {erfolgswert+=e;}
      int Praxispunkte() const {return praxispunkte;};
      void set_Praxispunkte(int e) const {praxispunkte=e;}
      void add_Praxispunkte(int e) const {praxispunkte+=e;}
      int Steigern_mit_EP() const {return steigern_mit_EP;}
      virtual enum MBEE What() const=0;
      virtual std::string What_str() const=0; // zum speichern
      virtual std::string Stufe() const {return "";} 
      virtual int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const {return 0;};
      bool ist_lernbar(const vector<cH_Typen>& Typ,const map<std::string,std::string>& map_typ) const;
      bool ist_gelernt(const std::list<cH_MidgardBasicElement>& L) const;
      bool ist_gelernt(const std::list<std::string>& L) const;
      int get_Steigern_Kosten(int erfolgswert) const;
      vector<std::string> Standard(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const; 
      std::string Standard__(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const;
      double Standard_Faktor(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const;
private:
      std::string AusnahmenString(const Grundwerte &Werte,const cH_Typen& Typ,const std::string s) const;
public:
      std::string Standard_Faktor(const Grundwerte &Werte,const vector<cH_Typen>& Typ,const std::string s) const;

      int Kosten(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const 
         {return (int)(Standard_Faktor(Werte,Typ)*GrundKosten());}
      int Steigern(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const; 
      int Reduzieren(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const;
      int Verlernen(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const; 
      bool standard_one_G(const vector<std::string>& s) const ;
      bool standard_all_S(const vector<std::string>& s) const ;
      bool operator == (const MidgardBasicElement& b) const 
         {return What()==b.What() && Name()==b.Name();}


      static void move_element(std::list<cH_MidgardBasicElement>& von,
                               std::list<cH_MidgardBasicElement>& nach,
                               const cH_MidgardBasicElement& MBE);
      static void show_list_in_tree(
            const std::list<cH_MidgardBasicElement>& BasicList,
            SimpleTree *Tree, const midgard_CG *hauptfenster,
            bool clear_me=true);
      static void saveElementliste(IF_XML(ostream &datei,)
      				const std::list<cH_MidgardBasicElement>& b,
                                   const Grundwerte& Werte,
                                   const vector<cH_Typen>& Typ);

};


class cH_MidgardBasicElement : public Handle<const MidgardBasicElement>
{
      typedef CacheStatic<std::string,cH_MidgardBasicElement> cache_t;
      static cache_t cache;
      friend class std::map<std::string,cH_MidgardBasicElement>;
      cH_MidgardBasicElement(){}
   public:
      cH_MidgardBasicElement(const MidgardBasicElement *r) 
            : Handle<const MidgardBasicElement>(r){}
//      bool operator== (const cH_MidgardBasicElement b) 
//         {return b==(*this);)

   class sort {
      public:
         enum esort {LERNPUNKTE,NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_MidgardBasicElement x,cH_MidgardBasicElement y) const
           { switch(es) {
               case(LERNPUNKTE) : return x->Lernpunkte() < y->Lernpunkte()  ;
//               case(LERN_L) : return cH_Fertigkeit(x)->LernLand() < cH_Fertigkeit(y)->LernLand()  ;
//               case(LERN_S) : return cH_Fertigkeit(x)->LernStadt() < cH_Fertigkeit(y)->LernStadt()  ;
//               case(LERN_U) : return x->Lernpunkte() < y->Lernpunkte()  ;
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x->Erfolgswert() > y->Erfolgswert();
           }}
    };

};

#endif
