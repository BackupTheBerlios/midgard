// $Id: Grundwerte.hh,v 1.13 2004/12/22 08:10:31 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#ifndef CLASS_GRUND
#define CLASS_GRUND
#include "Land.hh"
#include "Ruestung.hh"
#include "Spezies.hh"
#include "Spezialgebiet.hh"
#include "Typen.hh"
#include "MidgardBasicElement.hh"
#include "Fertigkeiten.hh"
#include <BaseObjects/Model.h>
#include <Misc/compiler_ports.h>

class Grundwerte
{
   struct st_grund{int st;int gw;int gs;int ko;int in;int zt;
          st_grund() :st(),gw(),gs(),ko(),in(),zt() {}
          st_grund(int _st,int _gw,int _gs,int _ko,int _in,int _zt)
             :  st(_st),gw(_gw),gs(_gs),ko(_ko),in(_in),zt(_zt) {}
         };         
   st_grund grund;
   std::list<MBEmlt> list_Sinne;
   MBEmlt Ueberleben_angeboren;
   int raufen;

   int au,pa,sb,wk,b,lp,ap;
   int gg,sg;
   int abwehr_wert,abwehr_pp,zaubern_wert,zauber_pp,pp_spezialzauber;
   int resistenz,resistenz_pp;
   int alter;
   Enums::geschlecht geschlecht;
   int gewicht,groesse,grad;
   std::string stand,spezialisierung,hand,
      glaube,name_abenteurer,name_spieler,version,bezeichnung;
   struct st_beschreibung{std::string text;std::string file;int size;
            st_beschreibung():size(8){} };
   st_beschreibung beschreibung;
   std::string merkmale;
   int gfp;
   float steigertage;
   int gold,silber,kupfer,aep,kep,zep;
   cH_Land herkunft;
   std::vector<cH_Ruestung> ruestung;
   cH_Spezies spezies;
   cH_Spezialgebiet spezialgebiet;
   Enums::StadtLand stadt_land;

//   int steigern_EP_prozent;  
   int grad_basiswerte; 

   std::vector<cH_Typen> Typ;
   std::string muttersprache;

public: // access these Models if you like ... ;-)
   enum wie_steigern_t { 
           ws_Unterweisung, // FP+GS
//           ws_none=ws_Unterweisung, // FP werden nicht verändert (*anteil=0)
           ws_Selbststudium, // 4/3*FP (goldanteil=0, fpanteil=133)
           ws_Praxispunkte, // PP(+FP) (goldanteil=0)
           ws_Spruchrolle // FP/10, GFP+=2*FP, Fehlschlag: GFP+=FP
        };
   enum wie_steigern_variante_t {
           wsv_NurPraxispunkte, // PP (GFP Rest kann verfallen) unsinnig? besser warten
           wsv_PraxispunkteFP, // PP+FP (mit FP bis zur nächsten Stufe auffüllen)
           // nur eine Stufe?
           
           wsv_SpruchrolleAlways=0,
           wsv_SpruchrolleRoll
        };

   Model_copyable<wie_steigern_t> wie_steigern;
   Model_copyable<wie_steigern_variante_t> wie_steigern_variante;
   Model_copyable<int> goldanteil; // 33-67 (oder weniger wenn Auftraggeber Kosten bezahlt)
   Model_copyable<int> fpanteil; // 0, 33-67 (oder 133 wenn Selbststudium)
   Model_copyable<bool> reduzieren; // reduzieren/verlernen statt steigern

public:
   Grundwerte(bool initialize=false);

   void reset();
   void resetSinne() ;
   void setSt(int i) {grund.st=i;}
   void setGw(int i) {grund.gw=i;}
   void setGs(int i) {grund.gs=i;}
   void setKo(int i) {grund.ko=i;}
   void setIn(int i) {grund.in=i;}
   void setZt(int i) {grund.zt=i;}
   int St() const {return grund.st;}
   int Gw() const {return grund.gw;}
   int Gs() const {return grund.gs;}
   int Ko() const {return grund.ko;}
   int In() const {return grund.in;}
   int Zt() const {return grund.zt;}
   int Au() const {return au;}
   int pA() const {return pa;}
   int Sb() const {return sb;}
   int Wk() const {return wk;}
   int B() const {return b;}
   int LP() const {return lp;}
   int AP() const {return ap;}
   const std::list<MBEmlt> &Sinne() const {return list_Sinne;}
   const MBEmlt &Ueberleben() const {return Ueberleben_angeboren;};
   int Raufen() const;
   std::string RaufenSchaden() const;
   int Abwehr_wert() const {return abwehr_wert;}
   int AbwehrPP() const {return abwehr_pp;}
   int Zaubern_wert() const { return zaubern_wert;}
   int ZaubernPP() const { return zauber_pp;}
   int SpezialPP() const { return pp_spezialzauber;}
   int Resistenz() const {return resistenz;}
   const std::string Resistenzen_alle() const;
   int ResistenzPP() const {return resistenz_pp;}
   int bo_Au() const;
   int bo_Sc() const;
   int bo_An() const; 
   int bo_Ab() const;
   int bo_Za() const;
   int bo_Psy() const;
   int bo_Phs() const;
   int bo_Phk() const;
   int KAW() const {return St()/10;}
   int WLW() const {return 40+Ko()/2;}
   int Geistesblitz() const {return In()/10;}
   int Gift() const {if(Ko()) return 30 + Ko()/2; else return 0;}
   int Alter() const {return alter;}
   std::string Gestalt() const ;
   Enums::geschlecht Geschlecht() const {return geschlecht;}
   std::string Geschlecht_str() const;
   const std::string &Hand() const {return hand;}
   int Gewicht() const {return gewicht;}
   int Groesse() const {return groesse;}
   std::string GroesseBez() const ;
   int Grad() const {return grad;}
   int SG() const {return sg;}
   int GG() const {return gg;}
   cH_Spezialgebiet Spezialgebiet() const {return spezialgebiet;}
   const std::string &Spezialisierung() const {return spezialisierung;}
//   std::string Spezial2() const {return spezial2;}
   const std::string &Stand() const {return stand;}
   cH_Ruestung Ruestung(unsigned int i=0) const;
   cH_Land Herkunft() const {return herkunft;}
   cH_Spezies Spezies() const {return spezies;}
   const std::string &Glaube() const {return glaube;}
   const std::string &Name_Abenteurer() const {return name_abenteurer;}
   const std::string &Name_Spieler() const {return name_spieler;}
   std::string Version() const;
   const std::string &Bezeichnung() const {return bezeichnung;}
   const std::string &Beschreibung() const {return beschreibung.text;}
   const std::string &BeschreibungPix() const {return beschreibung.file;}
   int BeschreibungPixSize() const {return beschreibung.size;}
   const std::string &Merkmale() const {return merkmale;}
   Enums::StadtLand Stadt_Land() const {return stadt_land;}
   std::string Stadt_Land_str() const ;
//   cH_Ruestung Ruestung(unsigned int i=0) const;
   int GFP() const {return gfp;}
   float Steigertage() const {return steigertage;}
   int Gold() const {return gold;}
   int Silber() const {return silber;}
   int Kupfer() const {return kupfer;}
   int AEP() const {return aep;}
   int KEP() const {return kep;}
   int ZEP() const {return zep;}

   void add_St(int i) {grund.st+=i;}
   void add_Gw(int i) {grund.gw+=i;}
   void add_Gs(int i) {grund.gs+=i;}
   void add_Ko(int i) {grund.ko+=i;}
   void add_In(int i) {grund.in+=i;}
   void add_Zt(int i) {grund.zt+=i;}
   void add_Au(int i) {au+=i;}
   void add_pA(int i) {pa+=i;}
   void add_Sb(int i) {sb+=i;}
   void add_Wk(int i) {wk+=i;}

   void setLP(int i) {lp=i;}
   void setBasiswerte(int st,int gw,int gs,int ko,int in, int zt)
         {grund=st_grund(st,gw,gs,ko,in,zt);}
   void setGewicht(int i) {gewicht=i;}
   void setGroesse(int i) {groesse=i;}
   void setHand(const std::string &s) {hand=s;}
   void setStand(const std::string &s) {stand=s;}
   void setAu(int i) {au=i;}
   void setpA(int i) {pa=i;}
   void setSb(int i) {sb=i;}
   void setWk(int i) {wk=i;}
   void setB(int i) {b=i;}
   void setAbgeleitetewerte_small(int _au,int _pa,int _sb,int _wk)
      { au=_au ;pa=_pa ;sb=_sb; wk=_wk; }

   void setSinn(const std::string &name,int wert) ;
   void setSinnCheck(const std::string &name,int wert); // wg. Speziessinnen
   int getSinn(const std::string &name) const;

   void setUeberleben(const MBEmlt &m) {Ueberleben_angeboren=m;}


   int Sehen() const {return getSinn("Sehen");}
   int Hoeren() const {return getSinn("Hören");}
   int Riechen() const {return getSinn("Riechen");}
   int Schmecken() const {return getSinn("Schmecken");}
   int Tasten() const {return getSinn("Tasten");}
   int SechsterSinn() const {return getSinn("Sechster Sinn");}

   void setGrad1Werte();

   void setZaubern_wert(int i){zaubern_wert=i;}
   void setAbwehr_wert(int i){abwehr_wert=i;}
   void setResistenz(int i){resistenz=i;}
   void addZaubern_wert(int i){zaubern_wert+=i;}
   void addAbwehr_wert(int i){abwehr_wert+=i;}
   void addResistenz(int i){resistenz+=i;}
   void setZaubernPP(int i){zauber_pp=i;}
   void setSpezialPP(int i){pp_spezialzauber=i;}
   void setAbwehrPP(int i){abwehr_pp=i;}
   void setResistenzPP(int i){resistenz_pp=i;}
   void addZaubernPP(int i){zauber_pp+=i;}
   void addSpezialPP(int i){pp_spezialzauber+=i;}
   void addAbwehrPP(int i){abwehr_pp+=i;}
   void addResistenzPP(int i){resistenz_pp+=i;}
   void setGrad(int i){grad=i;}
   void setAP(int i){ap=i;}
   void setSG(int i){sg=i;}
   void add_SG(int i){sg+=i;}
   void setGG(int i){gg=i;}
   void setAlter(int _alter){alter=_alter;}
   void setGeschlecht(const Enums::geschlecht& _geschlecht){geschlecht=_geschlecht;}
   void setGeschlecht(const std::string& _geschlecht);
   void setSpezialisierung(const std::string& _spezialisierung){spezialisierung=_spezialisierung;}   
   void setSpezialgebiet(const cH_Spezialgebiet& s) {spezialgebiet=s;}
//   void setSpezial(const std::string& _spezial,std::string _spezial2){spezial=_spezial;spezial2=_spezial2;}
   void setHerkunft(const cH_Land& _herkunft){herkunft=_herkunft;}
   void setSpezies(const cH_Spezies& _spezies){spezies=_spezies;}
   void setGlaube(const std::string& _glaube){glaube=_glaube;}
   void setAbenteurername(const std::string& s) {name_abenteurer=s;}
   void setNamen(const std::string& _name_abenteurer,const std::string &_name_spieler, const std::string &_version)
      {name_abenteurer=_name_abenteurer;name_spieler=_name_spieler;version=_version;}
   void setBezeichnung(const std::string& s) {bezeichnung=s;}
   void setMerkmale(const std::string& m) {merkmale=m;}
   void setNameC(const std::string& s) {name_abenteurer=s;}
   void setNameS(const std::string& s) { name_spieler=s;}
   void setVersion(const std::string& s) { version=s;}

   void setBeschreibung(const std::string& _b){beschreibung.text=_b;}
   void setBeschreibungPix(const std::string& _b){beschreibung.file=_b;}
   void setBeschreibungPixSize(int i){beschreibung.size=i;}
   void setStadtLand(const Enums::StadtLand& sl) {stadt_land=sl;}
   void setStadtLand(const std::string& sl);
   void setGFP(int _gfp){gfp=_gfp;}
   void addGFP(int _gfp){gfp += _gfp;}
   void setSteigertage(float i){steigertage=i;}
   void addSteigertage(float i){steigertage+=i;}
   void setGeld(int g,int s,int k){gold=g;silber=s;kupfer=k;}
   void addGold(int g)  {gold+=g;}
   void addSilber(int s) {silber+=s;}
   void addKupfer(int k) {kupfer+=k;}
   void setGold(int g)  {gold=g;}
   void setSilber(int s) {silber=s;}
   void setKupfer(int k) {kupfer=k;}
   void setEP(int a, int k, int z) {aep=a;kep=k;zep=z;}
   void addAEP(int a) {aep+=a;}
   void addKEP(int a) {kep+=a;}
   void addZEP(int a) {zep+=a;}
   void setAEP(int a) {aep=a;}
   void setKEP(int a) {kep=a;}
   void setZEP(int a) {zep=a;}
   
   const cH_Typen &Typ1() const {return Typ[0];}
   const cH_Typen &Typ2() const {return Typ[1];}
   std::string STyp() const ;
   void setTyp1(cH_Typen t) {Typ[0]=t;}
   void setTyp2(cH_Typen t) {Typ[1]=t;}
   const std::vector<cH_Typen> &getVTyp() const {return Typ;}
   bool is_mage() const ;

   std::string Muttersprache() const {return muttersprache;}
   void setMuttersprache(std::string s) {muttersprache=s;}

   int get_Steigern_EP_Prozent() const {return fpanteil;}
   int gold_kosten(int kosten) const;
   int ep_kosten(int kosten) const;
   int get_Grad_Basiswerte() const {return grad_basiswerte;}
   __deprecated void set_Grad_Anstieg(int p,int b)
              { fpanteil=p; goldanteil=100-p; grad_basiswerte=b; }
   __deprecated void set_Steigern_EP_Prozent(int i) {fpanteil=i; goldanteil=100-i;}
   void set_Grad_Basiswerte(int i) {grad_basiswerte=i;}

   void setRuestung1(const std::string &r,bool force=false)
       {ruestung[0]=cH_Ruestung(r,force);}
   void setRuestung2(const std::string &r,bool force=false)
       {ruestung[1]=cH_Ruestung(r,force);}
                     

   // LaTeX code für die Rüstung
   std::string Ruestung_RW_Verlust() const ;
//   std::string Ruestung_B_Verlust() const ;
   std::string Ruestung_Abwehr_Verlust(const std::list<MBEmlt>& list_Fertigkeit) const;
   std::string Ruestung_Angriff_Verlust(const std::list<MBEmlt>& list_Fertigkeit) const;

   // ================= aus table_grundwerte.hh ======================
   	void abge_werte_setzen();
   	
//        void grundwerte_wuerfeln();
//        void Eigenschaften_variante(int i);
        bool check_350(const std::vector<int>& a = std::vector<int>()) const;
        void gw_wuerfeln_2x();
        void Au_pA_wuerfeln();
private:        
        int  constraint_gw(int constraint);
        int  constraint_aw(int constraint);
        int  wuerfeln_best_of_two();
public:
//        void midgard_check_werte100();

        static std::vector<std::string> Vstand, Vhand;
};
#endif
