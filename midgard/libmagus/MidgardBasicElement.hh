/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2003-2004 Christof Petig
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
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <string>
#include <vector>
#include <list>
//#include "NotFound.h"
//#include <Tag.h>
//#include "xml.h"
//#include "Enums.hh"

class cH_Typen;
class Grundwerte;
class H_Data_beruf;
class cH_MidgardBasicElement;
class SimpleTree;
//class Datenbank;
class MidgardBasicElement_mutable;
class Abenteurer;
class Tag;

class H_MidgardBasicElement_mutable;
  
typedef H_MidgardBasicElement_mutable MBEmlt;
  
// dies ist eine erlernbare Fertigkeit, d.h. losgelöst von einem Abenteurer
class MidgardBasicElement : public HandleContent
{
   protected:
      // WARNUNG: Beruf wird nicht verwendet
      struct st_ausnahmen{std::string herkunft;std::string spezies;
                          std::string typ;std::string beruf;std::string stand;
                          std::string standard;
             st_ausnahmen(std::string h,std::string s,std::string t,
                          std::string b,std::string st,std::string sta) 
                        :herkunft(h),spezies(s),typ(t),beruf(b),stand(st),
                         standard(sta) {} };
 public:
      enum eZusatz {ZNone,ZTabelle,ZLand,ZWaffe,
                    ZHerkunft,ZSprache,ZSchrift,ZUeberleben};
      struct st_zusatz{std::string name;bool erlaubt; std::string typ;std::string region; std::string region_zusatz;
                       std::string long_region;
             st_zusatz() {}
             st_zusatz(std::string n,bool e=true):name(n),erlaubt(e) {}
             st_zusatz(std::string n,std::string t,std::string r,std::string rz,std::string lr,bool e=true)
               :name(n),erlaubt(e),typ(t),region(r),region_zusatz(rz),long_region(lr) {}};
      enum EP_t { Nicht=0, KEP=1, ZEP=2, Beides=KEP|ZEP, EP_t_undefined };
   protected:
//	const Tag *tag; // später weg
      std::string name, region,region_zusatz;
      int kosten;
      mutable int anfangswert;
      eZusatz enum_zusatz;

      std::vector<st_zusatz> Vzusatz;
      std::vector<st_ausnahmen> VAusnahmen;
      bool nsc_only;
      EP_t steigern_mit_EP;
      std::map<std::string,std::string> map_typ;
      std::map<int,int> map_erfolgswert_kosten;
      
      static std::map<std::string,EP_t> verwendbareEP;
      static std::map<int,std::map<int,int> > waffen_steigern_nach_schwierigkeit;
      static std::map<std::string,std::map<int,int> > sonstige_steigern_kosten;
public:      
      static void load_waffen_steigern_nach_schwierigkeit(const Tag &t);
      static void load_steigern_kosten(const Tag &t);
      
protected:
      void get_map_typ();
      void get_map_typ(const Tag &t);
      void get_Steigern_Kosten_map(const Tag &t);
      const std::map<int,int> &get_Steigern_Kosten_map(); // anhand des Typs bestimmen
      int GrundKosten() const {  return kosten; }

   public:
      MidgardBasicElement(const std::string &n) 
            : name(n), kosten(),anfangswert(),enum_zusatz()
              ,nsc_only(),steigern_mit_EP() {}

      enum MBEE {BERUF,FERTIGKEIT,FERTIGKEIT_ANG,WAFFEGRUND,WAFFE,WAFFEBESITZ,
                 ZAUBER,ZAUBERWERK,KIDO,SPRACHE,SCHRIFT,SINN,RESISTENZ_UND_CO} ;

      const std::map<std::string,std::string> &get_MapTyp() const {return map_typ;}
      
      const std::vector<st_zusatz> &VZusatz() const {return Vzusatz;}
      virtual eZusatz ZusatzEnum(const std::vector<cH_Typen>& Typ) const {return enum_zusatz;}
 
      bool NSC_only() const {return nsc_only;}
      static void EP_steigern(const std::string &fert,EP_t e);
      static EP_t EP_steigern_load(const Tag &t);
      // initialisierung: steigern wie Fertigkeit ...
      EP_t EP_steigern(const std::string &fert);
      void EP_steigern(EP_t e) { steigern_mit_EP=e; }
      void EP_steigern(const Tag &t) { steigern_mit_EP=EP_steigern_load(t); }

      virtual std::string Name() const {return name;}
      int Anfangswert() const {return anfangswert;}
      void setAnfangswert(int i) const {anfangswert=i;}
      const std::string &Region() const {return region;}
      const std::string &RegionZusatz() const {return region_zusatz;}
      std::string RegionString() const;
      EP_t Steigern_mit_EP() const {return steigern_mit_EP;}
      virtual enum MBEE What() const=0;
      virtual std::string What_str() const=0; // zum speichern
      virtual std::string Stufe() const {return "";} 
      virtual int MaxErfolgswert(const Abenteurer &A) const {return 0;};
      virtual int LernLand() const {return -99;}
      virtual int LernStadt() const {return -99;}
      bool ist_lernbar(const std::vector<cH_Typen>& Typ,const std::map<std::string,std::string>& map_typ) const;
      bool ist_gelernt(const std::list<std::string>& L) const;
      virtual int FErfolgswert(const Abenteurer &abenteurer,const MBEmlt &mbem) const;
      virtual std::string Voraussetzung() const {return "B U G";}
      virtual bool Voraussetzung(const Abenteurer& A,bool anzeigen=true) const;

      int get_Steigern_Kosten(int erfolgswert) const;

      std::vector<std::string> Standard(const Abenteurer &A) const; 
      std::string Standard__(const Abenteurer &A) const;
      double Standard_Faktor(const Abenteurer &A) const ;
      bool Grundfertigkeit(const Abenteurer &A) const;
      bool Standardfertigkeit(const Abenteurer &A) const;
private:
      std::string AusnahmenString(const Grundwerte &Werte,const cH_Typen& Typ,const std::string s) const;
public:
      std::string Standard_Faktor(const Grundwerte &Werte,const std::vector<cH_Typen>& Typ,const std::string s) const;

      int Kosten(const Abenteurer &A) const ;
      bool standard_one_G(const std::vector<std::string>& s) const ;
      bool standard_all_S(const std::vector<std::string>& s) const ;
      virtual bool operator == (const MidgardBasicElement& b) const 
         {return What()==b.What() && Name()==b.Name();}
      bool operator < (const MidgardBasicElement& b) const 
         {return  What()<b.What() || (What()==b.What() 
			&& Name()<b.Name());
         }

      static void saveElementliste(Tag &datei,
      				const std::list<MBEmlt>& b,
                                   const Grundwerte& Werte,
                                   const std::vector<cH_Typen>& Typ);
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
      template <class T>
       cH_MidgardBasicElement(const Handle<T> &r)
       	    : Handle<const MidgardBasicElement>(r){}
};

// noch nicht genutzt
struct wie_erlernt
{ enum wie_t { angeboren, lernen, beruf, unterweisung, selbststudium, 
      spruchrolle, praxis };
  enum lernen_t { fachkenntnis, allgemeinwissen, ungewoehnlich };
  wie_t wie:4;
  int neuer_wert:6; // [-32..31]
  struct fp_t { int aep, zep, kep; };
  struct praxis_t { unsigned praxispunkte:4; fp_t fp; };
  struct lernen_det_t { lernen_t liste; int lp; };
  struct unterweisung_t { unsigned gs; fp_t fp; } ;
  union
  { praxis_t praxis_detail;
    lernen_det_t lernen_detail;
    unterweisung_t unterweisung_detail; // +selbststudium
    fp_t spruchrolle_detail;
  };
};

// dies ist eine erlernte "Fertigkeit" d.h. sie hat Erfolgswert usw.
class MidgardBasicElement_mutable : public HandleContent
{
 private:
      cH_MidgardBasicElement mbe;
      int praxispunkte,erfolgswert,lernpunkte;
      MidgardBasicElement::st_zusatz zusatz; // Für Zusätze bei Fertigkeiten 
                              // (z.B. Abrichten, Sprache, Geheimzeichen...)
                              // und Zauber (Tiersprache)
      bool gelernt:1; // Fürs Lernschema
      bool pflicht:1;
      bool erlaubt:1;
      std::string lernart; // Fach- Allgemeinwissen, ungew. Fert.
      
   
 public: 
      template <class T>
       MidgardBasicElement_mutable(const Handle<T> &_mbe)
         : mbe(_mbe),praxispunkte(),erfolgswert(),
            lernpunkte(),gelernt(),pflicht() 
           {setErfolgswert(mbe->Anfangswert());}
      // wegen der &* Unsitte ;-)
      MidgardBasicElement_mutable(const MidgardBasicElement *_mbe)
         : mbe(_mbe),praxispunkte(),erfolgswert(),
            lernpunkte(),gelernt(),pflicht() 
           {setErfolgswert(mbe->Anfangswert());}
      const MidgardBasicElement *operator->() const
         {return &*mbe;}
      bool operator == (const MidgardBasicElement_mutable& b) const 
         {return What()==b.What() && mbe==b.mbe && Zusatz()==b.Zusatz();}
      bool operator < (const MidgardBasicElement_mutable& b) const 
         {return What()<b.What() || (What()==b.What() 
                   && (mbe<b.mbe || (mbe==b.mbe 
                   && Zusatz()<b.Zusatz())));
         }
      const MidgardBasicElement *getMBE() const {return &*mbe;}
      template <typename T>
       Handle<const T> getHandle() const
//      { return mbe.cast_dynamic<const T>(); } // geht erst ab g++ 3.4
      { return Handle<const T>(dynamic_cast<const T*>(&*mbe)); }

      virtual enum MidgardBasicElement::MBEE What() const {return mbe->What();}
      virtual std::string What_str() const {return mbe->What_str();}
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
  
      const std::string &Zusatz() const {return zusatz.name;}
      void setZusatz(MidgardBasicElement::st_zusatz z) {zusatz=z;}

     const std::string &LernArt() const {return lernart;}
     void setLernArt(const std::string &z)  {lernart=z;}   
     
     bool Erlaubt() const {return erlaubt;}
     void setErlaubt(bool e) {erlaubt=e;}
     bool Pflicht() const {return pflicht;}
     void setPflicht(bool p) {pflicht=p;}
     std::string Pflicht_str() const; 

     bool ist_gelernt(const std::list<MBEmlt>& L) const;
     int Steigern(const Abenteurer &A) const; 
     int Reduzieren(const Abenteurer &A) const;
     int Verlernen(const Abenteurer &A) const; 

      MidgardBasicElement_mutable *dup() const;
// wird die Klasse hier gebraucht?
   class sort {
      public:
         enum esort {LERNPUNKTEPFLICHT,NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(esort _es):es(_es) {}
         bool operator() (MidgardBasicElement_mutable x,MidgardBasicElement_mutable y) const;
    };

};

class H_MidgardBasicElement_mutable : public Handle<MidgardBasicElement_mutable>
{
      H_MidgardBasicElement_mutable(){}
   public:
      H_MidgardBasicElement_mutable(MidgardBasicElement_mutable *r) 
            : Handle<MidgardBasicElement_mutable>(r){}
      H_MidgardBasicElement_mutable(const cH_MidgardBasicElement  &_mbe)
         : Handle<MidgardBasicElement_mutable>(new MidgardBasicElement_mutable(_mbe))
               {}
      
      // duplizieren d.h. unabhängiges Element erzeugen
      H_MidgardBasicElement_mutable dup() const;

   class sort {
      public:
         enum esort {LERNPUNKTEPFLICHT,NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(esort _es):es(_es) {}
         bool operator() (H_MidgardBasicElement_mutable x,H_MidgardBasicElement_mutable y) const;
    };
};

void operator|=(MidgardBasicElement::EP_t &a, MidgardBasicElement::EP_t b);
bool operator&(MidgardBasicElement::EP_t a, MidgardBasicElement::EP_t b);

#endif
