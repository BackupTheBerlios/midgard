// $Id: Abenteurer.hh,v 1.32 2002/09/23 06:34:08 thoma Exp $               
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
#include "Enums.hh"


class Abenteurer
{
   AusruestungBaum besitz;
   Grundwerte Werte;
   std::vector<cH_Typen> Typ;
   std::string muttersprache;

   std::list<MBEmlt> list_Beruf;
   std::list<MBEmlt> list_Fertigkeit_ang;
   std::list<MBEmlt> list_Fertigkeit;
   std::list<MBEmlt> list_WaffenGrund;
   std::list<MBEmlt> list_Waffen;
   std::list<WaffeBesitz> list_Waffen_besitz;
//   std::list<MBEmlt> list_Waffen_besitz;
   std::list<MBEmlt> list_Zauber;
   std::list<MBEmlt> list_Zauberwerk;
   std::list<MBEmlt> list_Kido;
   std::list<MBEmlt> list_Sprache; 
   std::list<MBEmlt> list_Schrift;        

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

   bool Valid() const;

   Grundwerte &getWerte() {return Werte;}
   const Grundwerte &getWerte() const {return Werte;}
   
   AusruestungBaum &getBesitz() {return besitz;}
   const AusruestungBaum &getBesitz() const {return besitz;}

   const cH_Typen &Typ1() const {return Typ[0];}
   const cH_Typen &Typ2() const {return Typ[1];}
   std::string STyp() const ;
   void setTyp1(cH_Typen t) {Typ[0]=t;}
   void setTyp2(cH_Typen t) {Typ[1]=t;}
   const vector<cH_Typen> &getVTyp() const {return Typ;}
   bool is_mage() const ;
   std::string Muttersprache() const {return muttersprache;}
   void setMuttersprache(std::string s) {muttersprache=s;}

   const std::string Beruf() const;
   const std::list<MBEmlt>& List_Beruf() const {return list_Beruf;}
   const std::list<MBEmlt>& List_Fertigkeit_ang() const {return list_Fertigkeit_ang;}
   const std::list<MBEmlt>& List_Fertigkeit() const {return list_Fertigkeit;}
   const std::list<MBEmlt>& List_WaffenGrund() const {return list_WaffenGrund;}
   const std::list<MBEmlt>& List_Waffen() const {return list_Waffen;}
   const std::list<WaffeBesitz>& List_Waffen_besitz() const {return list_Waffen_besitz;}
//   const std::list<MBEmlt>& List_Waffen_besitz() const {return list_Waffen_besitz;}
   const std::list<MBEmlt>& List_Zauber() const {return list_Zauber;}
   const std::list<MBEmlt>& List_Zauberwerk() const {return list_Zauberwerk;}
   const std::list<MBEmlt>& List_Kido() const {return list_Kido;}
   const std::list<MBEmlt>& List_Sprache() const {return list_Sprache;} 
   const std::list<MBEmlt>& List_Schrift() const {return list_Schrift;}
   struct st_universell{MBEmlt mbe;bool voraussetzung;bool gelernt;
          st_universell(MBEmlt m) 
            : mbe(m),voraussetzung(true),gelernt(false) {}};
   const std::list<st_universell> List_Universell( const Datenbank &Database) const;

private:
      class sort_universell {
        public: sort_universell() {}
        bool operator()(st_universell x,st_universell y) const
          { return (x.mbe)->Name() < (y.mbe)->Name() ;
          }
      };
public:

   std::list<MBEmlt>& List_Beruf() {return list_Beruf;}
   std::list<MBEmlt>& List_Fertigkeit_ang() {return list_Fertigkeit_ang;}
   std::list<MBEmlt>& List_Fertigkeit()  {return list_Fertigkeit;}
   std::list<MBEmlt>& List_WaffenGrund() {return list_WaffenGrund;}
   std::list<MBEmlt>& List_Waffen()  {return list_Waffen;}
   std::list<WaffeBesitz>& List_Waffen_besitz() {return list_Waffen_besitz;}
//   std::list<MBEmlt>& List_Waffen_besitz() {return list_Waffen_besitz;}
   std::list<MBEmlt>& List_Zauber()  {return list_Zauber;}
   std::list<MBEmlt>& List_Zauberwerk()  {return list_Zauberwerk;}
   std::list<MBEmlt>& List_Kido()  {return list_Kido;}
   std::list<MBEmlt>& List_Sprache()  {return list_Sprache;} 
   std::list<MBEmlt>& List_Schrift()  {return list_Schrift;}

   void speicherstream(ostream &datei, const Datenbank &Database,const Midgard_Optionen *Optionen);
   void grundwerte_speichern(Tag &);
   void save_ausruestung(Tag &datei,const list<AusruestungBaum> &AB);

   bool xml_import_stream(istream &datei, Datenbank &Database,Midgard_Optionen *Optionen,midgard_CG *hauptfenster);
   void load_ausruestung(const Tag *tag, AusruestungBaum *AB);
   void load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version,Datenbank &Database,Midgard_Optionen *Optionen,midgard_CG *hauptfenster);


   bool operator==(const Abenteurer& a) const
      {return getWerte().Name_Abenteurer()==a.getWerte().Name_Abenteurer() &&
              getWerte().Version() == a.getWerte().Version() ;}


   // (bool==true) => gelernt ; (bool==false) => universell(oder garnicht)
   const pair<int,bool> Erfolgswert(std::string name,const Datenbank &Database) const;
   const std::string SErfolgswert(std::string name,const Datenbank &Database) const;

   void setAngebFert();
   bool setAngebSinnFert(int wurf,const MBEmlt &MBE);
   void remove_WaffenGrund() ;

   static void move_element(std::list<MBEmlt>& von,
                            std::list<MBEmlt>& nach,
                            const MBEmlt& MBE);
};


class VAbenteurer
{
   public:
      struct st_abenteurer{Abenteurer abenteurer;std::string filename;
                           bool gespeichert;
             st_abenteurer(const Abenteurer &A,bool g) : abenteurer(A),gespeichert(g) {}
             st_abenteurer() : abenteurer(Abenteurer()),gespeichert(true){} 
             bool operator==(const st_abenteurer& a) const 
               {return abenteurer.getWerte().Name_Abenteurer()==a.abenteurer.getWerte().Name_Abenteurer() &&
                       abenteurer.getWerte().Version() == a.abenteurer.getWerte().Version() ;}
             };
   private:
      std::list<st_abenteurer> VA;
      std::list<st_abenteurer>::iterator ai;

      class sort {
        public: sort() {}
        bool operator()(st_abenteurer x,st_abenteurer y) const
          { return x.abenteurer.getWerte().Gw() < y.abenteurer.getWerte().Gw() ;
          }
      };

   public:
      VAbenteurer() {}
      
      const std::list<st_abenteurer> &getList() const {return VA;}
      std::list<st_abenteurer> &getList() {return VA;}
      const Abenteurer &getCAbenteurer() const {return ai->abenteurer;}
      Abenteurer &getAbenteurer() const {return ai->abenteurer;}
      void sort_gw() {VA.sort(sort());}
      void push_back();
      void set_Abenteurer(const Abenteurer& A);

      void modified() {ai->gespeichert=false;}
      void saved() {ai->gespeichert=true;}
      bool gespeichert() const {return ai->gespeichert;}
      void setFilename(std::string s) {ai->filename=s;}
      const std::string &getFilename() {return ai->filename;}

      bool unsaved_exist();
      bool empty() const {return VA.empty();}
      guint size() const {return VA.size();}
      void delete_empty();

   const Abenteurer *operator->() const
   {  return &ai->abenteurer; }
   Abenteurer *operator->()
   {  return &ai->abenteurer; }

};


#endif
