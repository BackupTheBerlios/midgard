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
class MidgardBasicElement_mutable;
class Abenteurer;

class NotFound : public std::exception
{public:
	virtual const char* what() const throw() { return "NotFound"; }
};

class MidgardBasicElement : public HandleContentCopyable
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
      mutable int anfangswert;
      eZusatz enum_zusatz;
//      int mutable praxispunkte,erfolgswert,lernpunkte;
//      enum zusatz;      
//      mutable std::string zusatz; // Für Zusäte bei Fertigkeiten (z.B. Abrichten, Sprache, Geheimzeichen...)
                                  // und Zauber (Tiersprache)
      std::vector<std::string> Vzusatz;
      vector<st_ausnahmen> VAusnahmen;
//      mutable bool gelernt; // Fürs Lernschema
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
            : tag(0), name(n), kosten(0),anfangswert(0),enum_zusatz(ZNone)
              ,nsc_only(false),steigern_mit_EP(0) {}
      MidgardBasicElement(const Tag *t,const std::string &n) 
		: tag(t), name(n), kosten(0),anfangswert(0),enum_zusatz(ZNone)
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
      int Anfangswert() const {return anfangswert;}
      void setAnfangswert(int i) const {anfangswert=i;}
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
      virtual int FErfolgswert(const Abenteurer &abenteurer,const MidgardBasicElement_mutable &mbem) const;


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
      bool standard_one_G(const vector<std::string>& s) const ;
      bool standard_all_S(const vector<std::string>& s) const ;
      bool operator == (const MidgardBasicElement& b) const 
         {return What()==b.What() && Name()==b.Name();}
      bool operator < (const MidgardBasicElement& b) const 
         {return  Name()<b.Name() ||
                 (Name()==b.Name() && What()<=b.What());  
         }


      static void show_list_in_tree(
            const std::list<MidgardBasicElement_mutable>& BasicList,
            SimpleTree *Tree, const midgard_CG *hauptfenster,
            bool clear_me=true);

      static void move_element(std::list<MidgardBasicElement_mutable>& von,
                               std::list<MidgardBasicElement_mutable>& nach,
                               const MidgardBasicElement_mutable& MBE);

      static void saveElementliste(ostream &datei,
      				const std::list<MidgardBasicElement_mutable>& b,
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


};

class MidgardBasicElement_mutable : public cH_MidgardBasicElement
{
 private:
      int praxispunkte,erfolgswert,lernpunkte;
      std::string zusatz; // Für Zusätze bei Fertigkeiten 
                              // (z.B. Abrichten, Sprache, Geheimzeichen...)
                              // und Zauber (Tiersprache)
      bool gelernt; // Fürs Lernschema
      bool pflicht;
      std::string lernart; // Fach- Allgemeinwissen, ungew. Fert.
      
   
 public: 

      MidgardBasicElement_mutable(const cH_MidgardBasicElement  &mbe)
         : cH_MidgardBasicElement(mbe),praxispunkte(0),erfolgswert(0),
            lernpunkte(0),gelernt(false),pflicht(false) 
           {setErfolgswert(mbe->Anfangswert());}

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

     std::string LernArt() const {return lernart;}
     void setLernArt(std::string z)  {lernart=z;}   
     
     bool Pflicht() const {return pflicht;}
     void setPflicht(bool p) {pflicht=p;}
     std::string Pflicht_str() const; 

     bool ist_gelernt(const std::list<MidgardBasicElement_mutable>& L) const;
      int Steigern(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const; 
      int Reduzieren(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const;
      int Verlernen(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const; 
               

   class sort {
      public:
         enum esort {LERNPUNKTE,NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(esort _es):es(_es) {}
         bool operator() (MidgardBasicElement_mutable x,MidgardBasicElement_mutable y) const
           { switch(es) {
               case(LERNPUNKTE) : return x.Lernpunkte() < y.Lernpunkte()  ;
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x.Erfolgswert() > y.Erfolgswert();
           }}
    };

};


#endif
