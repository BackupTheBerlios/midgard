#ifndef CLASS_GRUND
#define CLASS_GRUND
#include "itos.h"
#include "Land.hh"
#include "Ruestung.hh"
#include "Spezies.hh"
#include "Spezialgebiet.hh"

class Grundwerte
{
   struct st_grund{int st;int gw;int gs;int ko;int in;int zt;
          st_grund() :st(0),gw(0),gs(0),ko(0),in(0),zt(0) {}
          st_grund(int _st,int _gw,int _gs,int _ko,int _in,int _zt)
             :  st(_st),gw(_gw),gs(_gs),ko(_ko),in(_in),zt(_zt) {}
         };         
   struct st_sinne {int sehen;int hoeren;int riechen;
                    int schmecken;int tasten;int sechster_sinn;
          st_sinne() : sehen(8), hoeren(8), riechen(8), schmecken(8),
                tasten(8), sechster_sinn(0) {} 
//          st_sinne(int s1,int s2,int s3,int s4,int s5,int s6)
//            :sehen(s1), hoeren(s2), riechen(s3), schmecken(s4),
//               tasten(s5), sechster_sinn(5) {}
            };
   st_grund grund;
   st_sinne sinne;
   int raufen;

   int au,pa,sb,wk,rw,hgw,b,lp,ap;
   int abwehr_wert,zaubern_wert;
   int resistenz,bo_au,bo_sc,bo_an,bo_ab,bo_za,
      bo_psy,bo_phs,bo_phk, bo_gi,kaw,wlw,alter;
   std::string gestalt, geschlecht;
   int gewicht,groesse,grad;
   std::string stand,spezialisierung,hand,
      glaube,name_charakter,name_spieler,version,beschreibung;
   int gfp,gold,silber,kupfer,aep,kep,zep;
   cH_Land herkunft;
   cH_Ruestung ruestung; 
   cH_Spezies spezies;
   cH_Spezialgebiet spezialgebiet;

public:
   Grundwerte() : raufen(0),au(0),pa(0),sb(0), wk(0), rw(0),
             hgw(0),b(0),lp(0),ap(0),abwehr_wert(0),zaubern_wert(0),
             resistenz(0),
             bo_au(0),bo_sc(0),bo_an(0),bo_ab(0),bo_za(0),
             bo_psy(0),bo_phs(0),bo_phk(0),bo_gi(0),kaw(0),wlw(0),
             alter(0),geschlecht("m"),gewicht(0),groesse(0),grad(1),
             stand(""),glaube(""),name_charakter(""),version("Erschaffung"),
             gfp(0),gold(0), silber(0), kupfer(0),
             aep(0),kep(0),zep(0),ruestung("OR"),spezies("Mensch") {}
   void clear() {*this=Grundwerte();}

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
   int RW() const {return rw;}
   int HGW() const {return hgw;}
   int B() const {return b;}
   int LP() const {return lp;}
   int AP() const {return ap;}
   st_sinne Sinne() const {return sinne;}
   int Raufen() const {return raufen;}
   int Abwehr_wert() const {return abwehr_wert;}
   int Zaubern_wert() const { return zaubern_wert;}
   int Resistenz() const {return resistenz;}
   int bo_Au() const {return bo_au;}
   int bo_Sc() const {return bo_sc;}
   int bo_An() const {return bo_an;}
   int bo_Ab() const {return bo_ab;}
   int bo_Za() const {return bo_za;}
   int bo_Psy() const {return bo_psy;}
   int bo_Phs() const {return bo_phs;}
   int bo_Phk() const {return bo_phk;}
   int bo_Gift() const {return bo_gi;}
   int KAW() const {return kaw;}
   int WLW() const {return wlw;}
   int Alter() const {return alter;}
   std::string Gestalt() const {return gestalt;}
   std::string Geschlecht() const {return geschlecht;}
   std::string Hand() const {return hand;}
   int Gewicht() const {return gewicht;}
   int Groesse() const {return groesse;}
   int Grad() const {return grad;}
   cH_Spezialgebiet Spezialgebiet() const {return spezialgebiet;}
   std::string Spezialisierung() const {return spezialisierung;}
//   std::string Spezial2() const {return spezial2;}
   std::string Stand() const {return stand;}
//   std::string Herkunft() const {return herkunft;}
   cH_Land Herkunft() const {return herkunft;}
//   std::string &Spezies() {return spezies;}
   cH_Spezies Spezies() const {return spezies;}
   std::string Glaube() const {return glaube;}
   std::string Name_Charakter() const {return name_charakter;}
   std::string Name_Spieler() const {return name_spieler;}
   std::string Version() const {return version;}
   std::string Beschreibung() const {return beschreibung;}
   cH_Ruestung Ruestung() const {return ruestung;}
   int GFP() const {return gfp;}
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
   void add_RW(int i) {rw+=i;}
   void add_HGW(int i) {hgw+=i;}

   void set_Basiswerte(int st,int gw,int gs,int ko,int in, int zt)
         {grund=st_grund(st,gw,gs,ko,in,zt);}
   void set_Abgeleitetewerte(int _au,int _pa,int _sb,int _wk,int _rw,int _hgw,int _b,
         int _lp, int _ap, int _abwehr_wert,int _zaubern_wert,
         int _resistenz,
         std::string _gestalt, std::string _hand,
         int _gewicht,int _groesse,int _grad, std::string _stand)
      { au=_au ;pa=_pa ;sb=_sb;wk=_wk ;rw=_rw ;hgw=_hgw ;b=_b ;lp=_lp ;ap=_ap ;
         abwehr_wert=_abwehr_wert ;zaubern_wert=_zaubern_wert ;
         resistenz=_resistenz ;
         gestalt=_gestalt ; hand=_hand;
         gewicht=_gewicht ;groesse=_groesse ;grad=_grad ;stand=_stand;
      }
   void set_Abgeleitetewerte_small(int _au,int _pa,int _sb,int _wk,int _rw,int _hgw)
      { au=_au ;pa=_pa ;sb=_sb; wk=_wk;rw=_rw ;hgw=_hgw; }
   void set_Abgeleitetewerte_Boni(int _bo_au,int _bo_sc,int _bo_an,int _bo_ab,
         int _bo_za,int _bo_psy,int _bo_phs,int _bo_phk)
      { bo_au=_bo_au ; bo_sc=_bo_sc ;bo_an=_bo_an ;
         bo_ab=_bo_ab ;bo_za=_bo_za ; bo_psy=_bo_psy ;bo_phs=_bo_phs ;
         bo_phk=_bo_phk ;
      }

   void set_Sinne_Sehen(int s) {sinne.sehen=s;}
   void set_Sinne_Hoeren(int s) {sinne.hoeren=s;}
   void set_Sinne_Riechen(int s) {sinne.riechen=s;}
   void set_Sinne_Schmecken(int s) {sinne.schmecken=s;}
   void set_Sinne_Tasten(int s) {sinne.tasten=s;}
   void set_Sinne_SechserSinn(int s) {sinne.sechster_sinn=s;}
   void set_Raufen(int r) {raufen=r;}

   void set_magBoni(int psy,int phs,int phk) {bo_psy=psy;bo_phs=phs;bo_phk=phk;}
   void set_Zaubern_wert(int i){zaubern_wert=i;}
   void set_Abwehr_wert(int i){abwehr_wert=i;}
   void set_Resistenz(int i){resistenz=i;}
   void set_Grad(int i){grad=i;}
   void set_AP(int i){ap=i;}
   void set_Alter(int _alter){alter=_alter;}
   void set_Geschlecht(const std::string& _geschlecht){geschlecht=_geschlecht;}
   void set_Spezialisierung(const std::string& _spezialisierung){spezialisierung=_spezialisierung;}   
   void set_Spezialgebiet(const cH_Spezialgebiet& s) {spezialgebiet=s;}
//   void set_Spezial(const std::string& _spezial,std::string _spezial2){spezial=_spezial;spezial2=_spezial2;}
   void set_Herkunft(const cH_Land& _herkunft){herkunft=_herkunft;}
   void set_Spezies(const cH_Spezies& _spezies){spezies=_spezies;}
   void set_Glaube(const std::string& _glaube){glaube=_glaube;}
   void set_Namen(const std::string& _name_charakter,std::string _name_spieler, std::string _version)
      {name_charakter=_name_charakter;name_spieler=_name_spieler;version=_version;}
   void set_Beschreibung(const std::string& _beschreibung){beschreibung=_beschreibung;}
   void set_Ruestung(const cH_Ruestung _ruestung){ruestung=_ruestung;}
   void set_GFP(int _gfp){gfp=_gfp;}
   void add_GFP(int _gfp){gfp += _gfp;}
   void set_Geld(int g,int s,int k){gold=g;silber=s;kupfer=k;}
   void add_Gold(int g)  {gold+=g;}
   void add_Silber(int s) {silber+=s;}
   void add_Kupfer(int k) {kupfer+=k;}
   void set_EP(int a, int k, int z) {aep=a;kep=k;zep=z;}
   void add_AEP(int a) {aep+=a;}
   void add_KEP(int a) {kep+=a;}
   void add_ZEP(int a) {zep+=a;}
   void set_KEP(int a) {kep=a;}
   void set_ZEP(int a) {zep=a;}

};
/*
class H_Grundwerte : public Handle<Grundwerte>    
{
protected:
 H_Grundwerte() {}
public:
 H_Grundwerte(Grundwerte *r) : Handle<Grundwerte>(r){}
};
*/
#endif
