// $Id: Abenteurer.hh,v 1.19 2002/06/20 19:06:17 thoma Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#ifndef CLASS_ABENTEURER
#define CLASS_ABENTEURER
#include "Ausruestung.hh"
#include "Grundwerte.hh"
#include "Typen.hh"
#include <vector>
#include "Datenbank.hh"
#include "Optionen.hh"
#include "Waffe.hh"


class Abenteurer
{
   AusruestungBaum besitz;
   Grundwerte Werte;
   std::vector<cH_Typen> Typ;

   std::list<MidgardBasicElement_mutable> list_Beruf;
   std::list<MidgardBasicElement_mutable> list_Fertigkeit_ang;
   std::list<MidgardBasicElement_mutable> list_Fertigkeit;
   std::list<MidgardBasicElement_mutable> list_WaffenGrund;
   std::list<MidgardBasicElement_mutable> list_Waffen;
   std::list<WaffeBesitz> list_Waffen_besitz;
   std::list<MidgardBasicElement_mutable> list_Zauber;
   std::list<MidgardBasicElement_mutable> list_Zauberwerk;
   std::list<MidgardBasicElement_mutable> list_Kido;
   std::list<MidgardBasicElement_mutable> list_Sprache; 
   std::list<MidgardBasicElement_mutable> list_Schrift;        
   
public:
   Abenteurer() {Typ.resize(2);}

   void reset(){  list_Beruf.clear();
             list_Fertigkeit_ang.clear();list_Fertigkeit.clear();
             list_WaffenGrund.clear();list_Waffen.clear();
             list_Waffen_besitz.clear();list_Zauber.clear();
             list_Zauberwerk.clear();list_Kido.clear();
             list_Sprache.clear();list_Schrift.clear(); 
             Typ.clear(); Typ.resize(2);
             }

   Grundwerte &getWerte() {return Werte;}
   const Grundwerte &getCWerte() const {return Werte;}
   
   AusruestungBaum &getBesitz() {return besitz;}
   const AusruestungBaum &getCBesitz() const {return besitz;}

   const cH_Typen &CTyp1() const {return Typ[0];}
   const cH_Typen &CTyp2() const {return Typ[1];}
   std::string STyp() const ;
   void setTyp1(cH_Typen t) {Typ[0]=t;}
   void setTyp2(cH_Typen t) {Typ[1]=t;}
   const vector<cH_Typen> &getVTyp() const {return Typ;}
   bool is_mage() const {if(CTyp1()->is_mage() || CTyp2()->is_mage()) return true;
                         else return false;}

   const std::string Beruf() const;
   const std::list<MidgardBasicElement_mutable>& CList_Beruf() const {return list_Beruf;}
   const std::list<MidgardBasicElement_mutable>& CList_Fertigkeit_ang() const {return list_Fertigkeit_ang;}
   const std::list<MidgardBasicElement_mutable>& CList_Fertigkeit() const {return list_Fertigkeit;}
   const std::list<MidgardBasicElement_mutable>& CList_WaffenGrund() const {return list_WaffenGrund;}
   const std::list<MidgardBasicElement_mutable>& CList_Waffen() const {return list_Waffen;}
   const std::list<WaffeBesitz>& CList_Waffen_besitz() const {return list_Waffen_besitz;}
   const std::list<MidgardBasicElement_mutable>& CList_Zauber() const {return list_Zauber;}
   const std::list<MidgardBasicElement_mutable>& CList_Zauberwerk() const {return list_Zauberwerk;}
   const std::list<MidgardBasicElement_mutable>& CList_Kido() const {return list_Kido;}
   const std::list<MidgardBasicElement_mutable>& CList_Sprache() const {return list_Sprache;} 
   const std::list<MidgardBasicElement_mutable>& CList_Schrift() const {return list_Schrift;}
   struct st_universell{MidgardBasicElement_mutable mbe;bool voraussetzung;bool gelernt;
          st_universell(MidgardBasicElement_mutable m) 
            : mbe(m),voraussetzung(true),gelernt(false) {}};
   const std::list<st_universell> CList_Universell( const Datenbank &Database) const;

private:
      class sort_universell {
        public: sort_universell() {}
        bool operator()(st_universell x,st_universell y) const
          { return x.mbe->Name() < y.mbe->Name() ;
          }
      };
public:

   std::list<MidgardBasicElement_mutable>& List_Beruf() {return list_Beruf;}
   std::list<MidgardBasicElement_mutable>& List_Fertigkeit_ang() {return list_Fertigkeit_ang;}
   std::list<MidgardBasicElement_mutable>& List_Fertigkeit()  {return list_Fertigkeit;}
   std::list<MidgardBasicElement_mutable>& List_WaffenGrund() {return list_WaffenGrund;}
   std::list<MidgardBasicElement_mutable>& List_Waffen()  {return list_Waffen;}
   std::list<WaffeBesitz>& List_Waffen_besitz() {return list_Waffen_besitz;}
   std::list<MidgardBasicElement_mutable>& List_Zauber()  {return list_Zauber;}
   std::list<MidgardBasicElement_mutable>& List_Zauberwerk()  {return list_Zauberwerk;}
   std::list<MidgardBasicElement_mutable>& List_Kido()  {return list_Kido;}
   std::list<MidgardBasicElement_mutable>& List_Sprache()  {return list_Sprache;} 
   std::list<MidgardBasicElement_mutable>& List_Schrift()  {return list_Schrift;}

   void speicherstream(ostream &datei, const Datenbank &Database,const Midgard_Optionen *Optionen);
   void grundwerte_speichern(Tag &);
   void save_ausruestung(Tag &datei,const list<AusruestungBaum> &AB);

   bool xml_import_stream(istream &datei, Datenbank &Database,Midgard_Optionen *Optionen);
   void load_ausruestung(const Tag *tag, AusruestungBaum *AB);
   void load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version,Datenbank &Database,Midgard_Optionen *Optionen);


   bool operator==(const Abenteurer& a) const
      {return getCWerte().Name_Abenteurer()==a.getCWerte().Name_Abenteurer() &&
              getCWerte().Version() == a.getCWerte().Version() ;}


   // (bool==true) => gelernt ; (bool==false) => universell(oder garnicht)
   const pair<int,bool> Erfolgswert(std::string name,const Datenbank &Database) const;
   const std::string SErfolgswert(std::string name,const Datenbank &Database) const;
};

class VAbenteurer
{
   public:
      struct st_abenteurer{Abenteurer abenteurer;std::string filename;
                           bool gespeichert;
             st_abenteurer(Abenteurer A,bool g) : abenteurer(A),gespeichert(g) {}
             st_abenteurer() : abenteurer(Abenteurer()),gespeichert(true){} 
             bool operator==(const st_abenteurer& a) const 
               {return abenteurer.getCWerte().Name_Abenteurer()==a.abenteurer.getCWerte().Name_Abenteurer() &&
                       abenteurer.getCWerte().Version() == a.abenteurer.getCWerte().Version() ;}
             };
   private:
      std::list<st_abenteurer> VA;
      std::list<st_abenteurer>::iterator ai;

      class sort {
        public: sort() {}
        bool operator()(st_abenteurer x,st_abenteurer y) const
          { return x.abenteurer.getCWerte().Gw() < y.abenteurer.getCWerte().Gw() ;
          }
      };

   public:
      VAbenteurer() {}
      
      const std::list<st_abenteurer> &getList() const {return VA;}
      std::list<st_abenteurer> &getList() {return VA;}
      const Abenteurer &getCAbenteurer() const {return ai->abenteurer;}
      Abenteurer &getAbenteurer() const {return ai->abenteurer;}
      void sort_gw() {VA.sort(sort());}
      void push_back(Abenteurer A);
      void set_Abenteurer(const Abenteurer& A);
      void modified() {ai->gespeichert=false;}
      void safed() {ai->gespeichert=true;}
      bool gespeichert() const {return ai->gespeichert;}
      void setFilename(std::string s) {ai->filename=s;}
      const std::string &getFilename() {return ai->filename;}


      bool unsaved_exist();
      bool empty() const {return VA.empty();}
      bool size() const {return VA.size();}
      void delete_empty();

      // Wrapper
private:
   void grundwerte_speichern(Tag &datei) {ai->abenteurer.grundwerte_speichern(datei);}
   void save_ausruestung(Tag &datei,const list<AusruestungBaum> &AB)
      {ai->abenteurer.save_ausruestung(datei,AB);}
   
   void load_ausruestung(const Tag *tag, AusruestungBaum *AB) {ai->abenteurer.load_ausruestung(tag,AB);}
   void load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version,Datenbank &Database,Midgard_Optionen *Optionen)
         {ai->abenteurer.load_fertigkeiten(tag,waffen_b,xml_version,Database,Optionen);}


public:
   void speicherstream(ostream &datei,const Datenbank &Database,const Midgard_Optionen *Optionen) 
         {ai->abenteurer.speicherstream(datei,Database,Optionen);}
   bool xml_import_stream(istream &datei,Datenbank &Database,Midgard_Optionen *Optionen) 
         {return ai->abenteurer.xml_import_stream(datei,Database,Optionen);}

   Grundwerte &getWerte() {return ai->abenteurer.getWerte();}
   const Grundwerte &getCWerte() const {return ai->abenteurer.getCWerte();}
   
   AusruestungBaum &getBesitz() {return ai->abenteurer.getBesitz();}
   const AusruestungBaum &getCBesitz() const {return ai->abenteurer.getCBesitz();}

   const cH_Typen &CTyp1() const {return ai->abenteurer.CTyp1();}
   const cH_Typen &CTyp2() const {return ai->abenteurer.CTyp2();}
   std::string STyp() const {return ai->abenteurer.STyp();}
   void setTyp1(cH_Typen t) {ai->abenteurer.setTyp1(t);}
   void setTyp2(cH_Typen t) {ai->abenteurer.setTyp2(t);}
   const vector<cH_Typen> &getVTyp() const {return ai->abenteurer.getVTyp();}
   bool is_mage() const {if(CTyp1()->is_mage() || CTyp2()->is_mage()) 
                         return true;
                         else return false;}

   const std::list<MidgardBasicElement_mutable>& CList_Beruf() const {return ai->abenteurer.CList_Beruf();}
   const std::list<MidgardBasicElement_mutable>& CList_Fertigkeit_ang() const {return ai->abenteurer.CList_Fertigkeit_ang();}
   const std::list<MidgardBasicElement_mutable>& CList_Fertigkeit() const {return ai->abenteurer.CList_Fertigkeit();}
   const std::list<MidgardBasicElement_mutable>& CList_WaffenGrund() const {return ai->abenteurer.CList_WaffenGrund();}
   const std::list<MidgardBasicElement_mutable>& CList_Waffen() const {return ai->abenteurer.CList_Waffen();}
   const std::list<WaffeBesitz>& CList_Waffen_besitz() const {return ai->abenteurer.CList_Waffen_besitz();}
   const std::list<MidgardBasicElement_mutable>& CList_Zauber() const {return ai->abenteurer.CList_Zauber();}
   const std::list<MidgardBasicElement_mutable>& CList_Zauberwerk() const {return ai->abenteurer.CList_Zauberwerk();}
   const std::list<MidgardBasicElement_mutable>& CList_Kido() const {return ai->abenteurer.CList_Kido();}
   const std::list<MidgardBasicElement_mutable>& CList_Sprache() const {return ai->abenteurer.CList_Sprache();} 
   const std::list<MidgardBasicElement_mutable>& CList_Schrift() const {return ai->abenteurer.CList_Schrift();}
   const std::list<Abenteurer::st_universell> CList_Universell( const Datenbank &Database) const {return ai->abenteurer.CList_Universell(Database);}

   std::list<MidgardBasicElement_mutable>& List_Beruf() {return ai->abenteurer.List_Beruf();}
   std::list<MidgardBasicElement_mutable>& List_Fertigkeit_ang() {return ai->abenteurer.List_Fertigkeit_ang();}
   std::list<MidgardBasicElement_mutable>& List_Fertigkeit()  {return ai->abenteurer.List_Fertigkeit();}
   std::list<MidgardBasicElement_mutable>& List_WaffenGrund() {return ai->abenteurer.List_WaffenGrund();}
   std::list<MidgardBasicElement_mutable>& List_Waffen()  {return ai->abenteurer.List_Waffen();}
   std::list<WaffeBesitz>& List_Waffen_besitz() {return ai->abenteurer.List_Waffen_besitz();}
   std::list<MidgardBasicElement_mutable>& List_Zauber()  {return ai->abenteurer.List_Zauber();}
   std::list<MidgardBasicElement_mutable>& List_Zauberwerk()  {return ai->abenteurer.List_Zauberwerk();}
   std::list<MidgardBasicElement_mutable>& List_Kido()  {return ai->abenteurer.List_Kido();}
   std::list<MidgardBasicElement_mutable>& List_Sprache()  {return ai->abenteurer.List_Sprache();} 
   std::list<MidgardBasicElement_mutable>& List_Schrift()  {return ai->abenteurer.List_Schrift();}

   const pair<int,bool> Erfolgswert(std::string name,const Datenbank &Database) const {return ai->abenteurer.Erfolgswert(name,Database);};
};


#endif
