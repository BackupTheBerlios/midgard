// $Id: Abenteurer.hh,v 1.33 2006/01/08 08:46:42 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2003-2006 Christof Petig
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
#include "ResistenzUndCo.hh"
#include <map>
#include <Misc/compiler_ports.h>
#include <time.h>


// Vielleicht sollte AbenteurerLernpunkte hier noch rein ...
class Abenteurer : public Grundwerte
{
   time_t last_saved_time;
   AusruestungBaum besitz;

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
   
public:
   typedef std::map<cH_Region,Model_copyable<bool> > regionen_t;

private:
   regionen_t regionen; // aktive Regionen
   Optionen optionen; // aktive Optionen

public:
   Abenteurer(bool initialize=false);
   
   const std::string LastSavedAt() const;
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

   std::list<MBEmlt> &getList(MidgardBasicElement::MBEE was);
   std::list<MBEmlt> &get_known_list(const MidgardBasicElement::MBEE was);
   std::list<MBEmlt> &get_known_list(const MBEmlt &MBE);
   
   MBEmlt get_known(MidgardBasicElement::MBEE was, std::string const& name, std::string const& zusatz=std::string());
   MBEmlt get_unknown(MidgardBasicElement::MBEE was, std::string const& name, std::string const& zusatz=std::string());
   
   struct st_universell{MBEmlt mbe;bool voraussetzung;bool gelernt;
          st_universell(MBEmlt m) 
            : mbe(m),voraussetzung(true),gelernt(false) {}};
   const std::list<st_universell> List_Universell() const;

private:
      class sort_universell {
        public: sort_universell() {}
        bool operator()(const st_universell &x,const st_universell &y) const;
      };
public:

   // alter Name
   __deprecated void speicherstream(std::ostream &datei) const;
   __deprecated bool xml_import_stream(std::istream &datei);
   // neuer Name
   void speichern(std::ostream &datei) const;
   bool laden(std::istream &datei);
private:
   void grundwerte_speichern(Tag &) const;
   void save_ausruestung(Tag &datei,const std::list<AusruestungBaum> &AB) const;

   void load_ausruestung(const Tag *tag, AusruestungBaum *AB);
   void load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version);
   void load_regionen_optionen(const Tag *tag, int xml_version);

public:   
   Optionen &getOptionen() { return optionen; }
   const Optionen &getOptionen() const { return optionen; }
   Model_ref<bool> getRegion(const cH_Region &r) { return regionen[r]; }
   const regionen_t &getRegionen() const {return regionen;}
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

   // neues Interface
   // true geklappt
   bool Steigern(MBEmlt &MBE);
   // true: Besonderheiten ??
   bool Erlernen(MBEmlt &MBE);
   // false: Fehlgeschlagen
   bool ReduzierenVerlernen(MBEmlt &MBE, bool &verlernt);

   void reduziere(MBEmlt &MBE);
   void verlerne(MBEmlt &MBE);
   bool steigere(MBEmlt &MBE);
   bool neu_lernen(MBEmlt &MBE, int bonus=0);
   // (Kosten für) Ausdauer würfeln
   int get_ausdauer(int grad);
   // (Kosten für) Abwehr, Resistenz, Zaubern steigern
   __deprecated int get_ab_re_za(const ResistenzUndCo::was_t was);
   int get_ab_re_za(const MBEmlt &was);

   void move_neues_element(MBEmlt &MBE,std::list<MBEmlt> *MyList_neu);
private:   
   void EP_aufwenden(MidgardBasicElement::EP_t ep_t,unsigned ep_k);
   void PP_aufwenden(unsigned pp, const MBEmlt &MBE);

   // Kosten für reduzieren verrechnen?
   void desteigern(unsigned kosten);
   // Unterweisung, Selbststudium, Praxispunkte
   __deprecated bool steigern_usp(int &kosten,ResistenzUndCo::was_t was);
   bool steigern_usp(int &kosten,MBEmlt MBE,int &stufen);
   void set_lernzeit(int kosten,const MBEmlt &MBE);
   MidgardBasicElement::EP_t steigern_mit(const MBEmlt &MBE) const;
   bool genug_EP(int ep_k,MidgardBasicElement::EP_t mit) const;

   int genug_geld(int kosten) const;
   int EP_kosten(const int kosten) const;
   int PP_vorrat(const MBEmlt &MBE) const;

   // Beschreibung siehe .cc
   int stufen_auf_einmal_steigern_fuer_aep(const MBEmlt& MBE,int &kosten_out,int &aep) const;

public:
   void eigenschaften_steigern(int wurf=-1);
   bool eigenschaften_steigern_erlaubt() const;
  
   bool SpruchVonSpruchrolleGelernt(const std::string &zauber);
   bool ZauberSpruecheMitPP() const;
   
   unsigned VerfuegbareFP() const;
};

#endif
