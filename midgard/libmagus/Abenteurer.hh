// $Id: Abenteurer.hh,v 1.21 2004/03/08 14:56:15 thoma Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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
#include <vector>
#include "Ausruestung.hh"
#include "Grundwerte.hh"
#include "Optionen.hh"
#include "Waffe.hh"
#include "Ruestung.hh"
#include "Enums.hh"
#include "Region.hh"
#include <map>
#include <Misc/compiler_ports.h>

// Vielleicht sollte AbenteurerLernpunkte hier noch rein ...
class Abenteurer : public Grundwerte
{
   AusruestungBaum besitz;
//   Grundwerte Werte;

   std::list<MBEmlt> list_Beruf;
   std::list<MBEmlt> list_Fertigkeit_ang;
   std::list<MBEmlt> list_Fertigkeit;
   std::list<MBEmlt> list_WaffenGrund;
   std::list<MBEmlt> list_Waffen;
   std::list<H_WaffeBesitz> list_Waffen_besitz; // oder MBEmlt
   std::list<MBEmlt> list_Zauber;
   std::list<MBEmlt> list_Zauberwerk;
   std::list<MBEmlt> list_Kido;
   std::list<MBEmlt> list_Sprache; 
   std::list<MBEmlt> list_Schrift;        

   std::list<std::string> list_Gelernt_von_Spruchrolle;


   typedef std::map<cH_Region,Model_copyable<bool> > regionen_t;
   regionen_t regionen; // aktive Regionen
   Optionen optionen; // aktive Optionen

public:

   Abenteurer();
   
   void reset();
   bool Valid() const;

   __deprecated Grundwerte &getWerte() {return *this;}
   __deprecated const Grundwerte &getWerte() const {return *this;}
   
   AusruestungBaum &getBesitz(){return besitz;}
   AusruestungBaum& getAusruestung_as_parent(const std::string &name);
   AusruestungBaum* rekursiv(std::list<AusruestungBaum> &AB,const std::string &name);
   const AusruestungBaum &getBesitz() const {return besitz;}
   void setStandardAusruestung();
private:
   std::map<std::string,double> getBelastung() const;
public:
   double getBelastung(const std::string &s) const;
   int getNormallast() const;
   int getHoechstlast() const;
   int getSchublast() const;
   double getUeberlast() const;
   std::string Ruestung_B_Verlust(bool ueberlast_beruecksichtigen=false) const;


   void Steigertage2Alter();


   const std::string Beruf() const;
   const std::list<MBEmlt>& List_Beruf() const {return list_Beruf;}
   const std::list<MBEmlt>& List_Fertigkeit_ang() const {return list_Fertigkeit_ang;}
   const std::list<MBEmlt>& List_Fertigkeit() const {return list_Fertigkeit;}
   const std::list<MBEmlt>& List_WaffenGrund() const {return list_WaffenGrund;}
   const std::list<MBEmlt>& List_Waffen() const {return list_Waffen;}
   const std::list<H_WaffeBesitz>& List_Waffen_besitz() const {return list_Waffen_besitz;}
   const std::list<MBEmlt>& List_Zauber() const {return list_Zauber;}
   const std::list<MBEmlt>& List_Zauberwerk() const {return list_Zauberwerk;}
   const std::list<MBEmlt>& List_Kido() const {return list_Kido;}
   const std::list<MBEmlt>& List_Sprache() const {return list_Sprache;} 
   const std::list<MBEmlt>& List_Schrift() const {return list_Schrift;}
   struct st_universell{MBEmlt mbe;bool voraussetzung;bool gelernt;
          st_universell(MBEmlt m) 
            : mbe(m),voraussetzung(true),gelernt(false) {}};
   const std::list<st_universell> List_Universell() const;

private:
      class sort_universell {
        public: sort_universell() {}
        bool operator()(st_universell x,st_universell y) const
//          { return (x.mbe)->Name() < (y.mbe)->Name() ;
          { return (*(x.mbe))->Name() < (*(y.mbe))->Name() ;
          }
      };
public:

   std::list<MBEmlt>& List_Beruf() {return list_Beruf;}
   std::list<MBEmlt>& List_Fertigkeit_ang() {return list_Fertigkeit_ang;}
   std::list<MBEmlt>& List_Fertigkeit()  {return list_Fertigkeit;}
   std::list<MBEmlt>& List_WaffenGrund() {return list_WaffenGrund;}
   std::list<MBEmlt>& List_Waffen()  {return list_Waffen;}
   std::list<H_WaffeBesitz>& List_Waffen_besitz() {return list_Waffen_besitz;}
   std::list<MBEmlt>& List_Zauber()  {return list_Zauber;}
   std::list<MBEmlt>& List_Zauberwerk()  {return list_Zauberwerk;}
   std::list<MBEmlt>& List_Kido()  {return list_Kido;}
   std::list<MBEmlt>& List_Sprache()  {return list_Sprache;} 
   std::list<MBEmlt>& List_Schrift()  {return list_Schrift;}

   void speicherstream(std::ostream &datei);
   void grundwerte_speichern(Tag &);
   void save_ausruestung(Tag &datei,const std::list<AusruestungBaum> &AB);

   bool xml_import_stream(std::istream &datei);
   void load_ausruestung(const Tag *tag, AusruestungBaum *AB);
   void load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version);
   void load_regionen_optionen(const Tag *tag, int xml_version);
   
   Optionen &getOptionen() { return optionen; }
   const Optionen &getOptionen() const { return optionen; }
   Model_ref<bool> getRegion(const cH_Region &r) { return regionen[r]; }
   bool getRegion(const cH_Region &r) const;

   bool operator==(const Abenteurer& a) const
      {return Name_Abenteurer()==a.Name_Abenteurer() &&
              Version() == a.Version() ;}

   // (bool==true) => gelernt ; (bool==false) => universell(oder garnicht)
   const std::pair<int,bool> Erfolgswert(std::string name) const;
   const std::string SErfolgswert(std::string name) const;

   void setAngebFert();
   bool setAngebSinnFert(int wurf,const MBEmlt &MBE);
   void remove_WaffenGrund() ;

   static void move_element(std::list<MBEmlt>& von,
                            std::list<MBEmlt>& nach,
                            const MBEmlt& MBE);

   // Zum Steigern eines MBEm
   typedef Enums::e_was_steigern e_was_steigern;
   typedef Enums::e_wie_steigern e_wie_steigern;
   enum modi_modus{Zusatzmodus,PPmodus};;
   typedef Enums::st_bool_steigern st_bool_steigern;
   void reduziere(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern);
   void verlerne(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern);
   bool steigere(MBEmlt &MBE,const e_wie_steigern wie,
                 const st_bool_steigern &bool_steigern);
   bool neu_lernen(MBEmlt &MBE,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern,const int bonus=0);
   void move_neues_element(MBEmlt &MBE,std::list<MBEmlt> *MyList_neu,const std::list<cH_MidgardBasicElement> *alleSprachen=0);

   void desteigern(unsigned int kosten,const e_wie_steigern &wie,const st_bool_steigern &bool_steigern);
   bool steigern_usp(const e_wie_steigern wie,int &kosten,
                     const e_was_steigern was,
                     const st_bool_steigern &bool_steigern)
       { int d=1; 
         MBEmlt mbe=MBEmlt(&*cH_Fertigkeit("",true));
         return steigern_usp(wie,kosten,mbe,d,was,bool_steigern);}
   bool steigern_usp(const e_wie_steigern wie,int &kosten,MBEmlt MBE,
                     int &stufen,const e_was_steigern was,
                     const st_bool_steigern &bool_steigern);
   void set_lernzeit(const e_wie_steigern wie,const int kosten,
                     const e_was_steigern was,const st_bool_steigern bool_steigern);
   int genug_geld(const int kosten,const e_wie_steigern wie,const st_bool_steigern bool_steigern);
   bool genug_EP(const int ep_k,const bool bkep,const bool bzep, int &aep0,int &kep0,int &zep0);
   int EP_kosten(const int kosten,const e_wie_steigern wie);
   int PP_vorrat(const MBEmlt &MBE,e_was_steigern was,const e_wie_steigern wie);
   void steigern_mit(bool &bkep,bool &bzep,const MBEmlt MBE,e_was_steigern was);
   int stufen_auf_einmal_steigern_fuer_aep(MBEmlt& MBE,int &kosten,int &aep);
   void modify(modi_modus modus,const MBEmlt &M,const MidgardBasicElement::st_zusatz &zusatz,int praxispunkte);


   int get_ausdauer(int grad,
                      const e_wie_steigern &wie,const st_bool_steigern &bool_steigern);
   int get_ab_re_za(const e_was_steigern was,const e_wie_steigern &wie,
                              const bool bsteigern,
                              const st_bool_steigern &bool_steigern);
   void eigenschaften_steigern(int wurf=-1);
   bool eigenschaften_steigern_erlaubt() const;
  
   std::list<MBEmlt> &get_known_list(const Enums::MBEListen was);
   std::list<MBEmlt> &get_known_list(const MBEmlt &MBE);

   bool SpruchVonSpruchrolleGelernt(const std::string &zauber)
      {return find(list_Gelernt_von_Spruchrolle.begin(),list_Gelernt_von_Spruchrolle.end(),zauber)!=list_Gelernt_von_Spruchrolle.end() ; }


   bool ZauberSpruecheMitPP() const;

};

#endif
