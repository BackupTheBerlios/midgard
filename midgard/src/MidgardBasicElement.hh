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

class MidgardBasicElement_fixed : public HandleContentCopyable
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
      std::string name, region,region_zusatz;
      int kosten;
      eZusatz enum_zusatz;
//      int mutable praxispunkte,erfolgswert,lernpunkte;
//      enum zusatz;      
//      mutable std::string zusatz; // F�r Zus�te bei Fertigkeiten (z.B. Abrichten, Sprache, Geheimzeichen...)
                                  // und Zauber (Tiersprache)
      std::vector<std::string> Vzusatz;
      vector<st_ausnahmen> VAusnahmen;
//      mutable bool gelernt; // F�rs Lernschema
      bool nsc_only;
      enum EP_t { Nicht=0, KEP=1, ZEP=2, Beides=KEP|ZEP };
      /* EP_t (CP) */ int steigern_mit_EP;
      std::map<std::string,std::string> map_typ;
      std::map<int,int> map_erfolgswert_kosten;
      
      void get_map_typ();
      void get_Steigern_Kosten_map();
      int GrundKosten() const {  return kosten; }

   public:
      MidgardBasicElement_fixed(const std::string &n) 
            : tag(0), name(n), kosten(0),enum_zusatz(ZNone)
              ,nsc_only(false),steigern_mit_EP(0) {}
      MidgardBasicElement_fixed(const Tag *t,const std::string &n) 
		: tag(t), name(n), kosten(0),enum_zusatz(ZNone)
              ,nsc_only(false),steigern_mit_EP(0) {}

      enum MBEE {BERUF,FERTIGKEIT,FERTIGKEIT_ANG,WAFFEGRUND,WAFFE,WAFFEBESITZ,
                 ZAUBER,ZAUBERWERK,KIDO,SPRACHE,SCHRIFT,SINN} ;
      enum TREE {OLD,NEW};

      map<std::string,std::string> get_MapTyp() const {return map_typ;}
      
      std::vector<std::string> VZusatz() const {return Vzusatz;}
      virtual eZusatz ZusatzEnum(const vector<cH_Typen>& Typ) const {return enum_zusatz;}
 
      bool NSC_only() const {return nsc_only;}
      void EP_steigern(const std::string fert);
      virtual std::string Name() const {return name;}
      std::string Region() const {return region;}
      std::string RegionZusatz() const {return region_zusatz;}
      std::string RegionString(const Datenbank &D) const;
      int Steigern_mit_EP() const {return steigern_mit_EP;}
      virtual enum MBEE What() const=0;
      virtual std::string What_str() const=0; // zum speichern
      virtual std::string Stufe() const {return "";} 
      virtual int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const {return 0;};
      bool ist_lernbar(const vector<cH_Typen>& Typ,const map<std::string,std::string>& map_typ) const;
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
      bool operator == (const MidgardBasicElement_fixed& b) const 
         {return What()==b.What() && Name()==b.Name();}
      bool operator < (const MidgardBasicElement_fixed& b) const 
         {return  Name()<b.Name() ||
                 (Name()==b.Name() && What()<=b.What());  
         }


      static void show_list_in_tree(
            const std::list<cH_MidgardBasicElement>& BasicList,
            SimpleTree *Tree, const midgard_CG *hauptfenster,
            bool clear_me=true);

};


class cH_MidgardBasicElement_fixed : public Handle<const MidgardBasicElement_fixed>
{
      typedef CacheStatic<std::string,cH_MidgardBasicElement_fixed> cache_t;
      static cache_t cache;
      friend class std::map<std::string,cH_MidgardBasicElement_fixed>;
      cH_MidgardBasicElement_fixed(){}
   public:
      cH_MidgardBasicElement_fixed(const MidgardBasicElement_fixed *r) 
            : Handle<const MidgardBasicElement_fixed>(r){}


};

class MidgardBasicElement : public cH_MidgardBasicElement_fixed
{
 private:
      int praxispunkte,erfolgswert,lernpunkte;
      std::string zusatz; // F�r Zus�tze bei Fertigkeiten 
                              // (z.B. Abrichten, Sprache, Geheimzeichen...)
                              // und Zauber (Tiersprache)
      bool gelernt; // F�rs Lernschema

 public: 

      MidgardBasicElement(const cH_MidgardBasicElement_fixed  &mbe)
         : cH_MidgardBasicElement_fixed(mbe),praxispunkte(0),erfolgswert(0),
            lernpunkte(0),gelernt(false) {}

      int Lernpunkte() const {return lernpunkte;};
      void setLernpunkte(int l) {lernpunkte=l;}
      int Erfolgswert() const {return erfolgswert;};
      void setErfolgswert(int e) {erfolgswert=e;}
      void addErfolgswert(int e) {erfolgswert+=e;}
      int Praxispunkte() const {return praxispunkte;};
      void setPraxispunkte(int e)  {praxispunkte=e;}
      void addPraxispunkte(int e)  {praxispunkte+=e;}

      void setGelernt(bool b)  {gelernt=b;}
      bool Gelernt() const {return gelernt;}
  
      std::string Zusatz() const {return zusatz;}
      void setZusatz(std::string z) {zusatz=z;}

      bool ist_gelernt(const std::list<MidgardBasicElement>& L) const;

      static void move_element(std::list<MidgardBasicElement>& von,
                               std::list<MidgardBasicElement>& nach,
                               const MidgardBasicElement& MBE);

      static void saveElementliste(ostream &datei,
      				const std::list<MidgardBasicElement>& b,
                                   const Grundwerte& Werte,
                                   const vector<cH_Typen>& Typ);

   class sort {
      public:
         enum esort {LERNPUNKTE,NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(esort _es):es(_es) {}
         bool operator() (MidgardBasicElement x,MidgardBasicElement y) const
           { switch(es) {
               case(LERNPUNKTE) : return x.Lernpunkte() < y.Lernpunkte()  ;
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x.Erfolgswert() > y.Erfolgswert();
           }}
    };

};


#endif
