// generated 2001/2/2 11:29:18 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to midgard_CG.hh_glade

// you might replace
//    class Foo : public Foo_glade { ... };
// by
//    typedef Foo_glade Foo;
// if you didn't make any modifications to the widget

#ifndef _MIDGARD_CG_HH
#  include "midgard_CG_glade.hh"
#  define _MIDGARD_CG_HH
#include "glademm_support.hh"
#include "WindowInfo.hh"

#include <fstream>
#include <string>
#include <stdio.h>
#include <gtk--/main.h>
#include <gtk--/menu.h>
#include <gtk--/menuitem.h>
#include <vector>
#include <map>
#include "itos.h"
//string itos(int i);

struct st_werte{int st; int ge;int ko;int in;int zt;
             int au;int pa;int sb;int rw;int hgw;
             int b;int lp;int ap;int abwehr_wert; string zaubern_wert;
             int psyZR_wert; int phsZR_wert; int phkZR_wert; int gift_wert;
             int bo_au_typ; int bo_au; int bo_sc; int bo_an; int bo_ab; int bo_za;
             int bo_psy; int bo_phs; int bo_phk; int bo_gi;
             int kaw; int wlw; int lpbasis;
             int alter;string gestalt;
             int gewicht;int groesse;int grad;
             string spezialisierung;string spezial; string stand;string herkunft;
             string glaube; string name_charakter; string name_spieler;
             int gfp;string version; string beschreibung; string ruestung;
             int gold; int silber; int kupfer;
      st_werte() : st(0),ge(0),ko(0),in(0),zt(0),au(0),pa(0),sb(0), rw(0),
             hgw(0),b(0),lp(0),ap(0),abwehr_wert(0),
             psyZR_wert(0),phsZR_wert(0),phkZR_wert(0),gift_wert(0),
             bo_au_typ(0),bo_au(0),bo_sc(0),bo_an(0),bo_ab(0),bo_za(0),
             bo_psy(0),bo_phs(0),bo_phk(0),bo_gi(0),kaw(0),wlw(0),lpbasis(0),
             alter(0),gewicht(0),groesse(0),grad(1),spezialisierung(""),
             stand(""),herkunft(""),glaube(""),name_charakter(""), gfp(0),version("Erschaffung"),
             ruestung("OR"), gold(0), silber(0), kupfer(0) {}
      void clear() {*this=st_werte();}}; 
struct st_lernpunkte{int beruf; int fertigkeiten; int waffen; int zauber;
      st_lernpunkte() : beruf(0),fertigkeiten(0),waffen(0),zauber(0) {}
      void clear(){*this=st_lernpunkte();} };
struct styp{int nr;string l;string s;string z; string ausdauer; int stand;
      int sb;
   styp() : nr(0),stand(0) {} 
   void clear() {*this=styp();} };
struct st_ausgewaehlte_fertigkeiten {string name; int erfolgswert; string attribut;
      st_ausgewaehlte_fertigkeiten(const string n,int e, const string a)
      : name(n),erfolgswert(e), attribut(a) {} };
struct st_angeborene_fertigkeit {string name; int erfolgswert;
      st_angeborene_fertigkeit(const string n,int e )
      : name(n),erfolgswert(e) {} };
struct st_ausgewaehlte_waffen {string name; int erfolgswert; 
      st_ausgewaehlte_waffen(const string n,int e)
      : name(n),erfolgswert(e) {} };
struct st_waffen_besitz {string name; int av_bonus; int sl_bonus;
   st_waffen_besitz(string n, int a, int s) : name(n), av_bonus(a),sl_bonus(s)
      {}
   st_waffen_besitz() : name(""), av_bonus(0), sl_bonus(0) {} };
struct st_ausgewaehlte_zauber {string name; string ap; 
      st_ausgewaehlte_zauber(const string n, const string a)
      : name(n), ap(a) {} };
struct st_ausgewaehlte_berufe {string name; string vorteile; int erfolgswert; 
      st_ausgewaehlte_berufe(const string n, const string v, int e)
      : name(n), vorteile(v), erfolgswert(e) {} };
struct st_zauber{string ap; string name; string erfolgswert;string art; string stufe;
              string zauberdauer; string reichweite; string wirkungsziel;
              string wirkungsbereich; string wirkungsdauer; string ursprung;
              string material; string agens; string prozess; string reagens; 
              string beschreibung; int kosten;
       st_zauber (const string a1, const string n, const string er, const string a, 
            const string s,
            const string zd, const string r, const string zi,
            const string ber, const string wd, const string u,
            const string mat, const string age, const string pro, 
            const string rea, const string bes, int ko) 
      : ap(a1), name(n), erfolgswert(er), art(a), stufe(s), zauberdauer(zd), 
         reichweite(r),
         wirkungsziel(zi), wirkungsbereich(ber), wirkungsdauer(wd), 
         ursprung(u), material(mat), agens(age), prozess(pro), reagens(rea),
         beschreibung(bes), kosten(ko) {} };

struct st_sprachen {string name; int wert;string schrift;
      st_sprachen(string n, int w, string s) : name(n),wert(w),schrift(s) {} };
struct st_schriften {string urschrift; string typ;
      st_schriften(string u, string t) : urschrift(u),typ(t) {}};


extern bool Infobool;
extern bool Escharbool;
extern bool Rawindrabool;
extern bool KanThaiPanbool;
extern bool Nahuatlanbool;
extern bool Waelandbool;
extern bool Albabool;


class midgard_CG : public midgard_CG_glade
{   
        friend class midgard_CG_glade;
        vector<string> typen_vector;
        vector<st_ausgewaehlte_fertigkeiten> vec_fertigkeiten;
        vector<st_angeborene_fertigkeit> vec_an_fertigkeit;
        vector<st_ausgewaehlte_waffen> vec_waffen;
        vector<st_waffen_besitz> waffe_besitz;
        vector<st_ausgewaehlte_zauber> vec_zauber;
        vector<st_ausgewaehlte_berufe> vec_beruf;
        vector<st_zauber> zauber;
        vector<st_sprachen> vec_sprachen;
        vector<st_schriften> vec_schriften;
        map<string,string> waffen_grundkenntnisse;
        styp typ;
        st_lernpunkte lernpunkte;

        void regnot(string sadd);
        void fill_typauswahl();
        void typauswahl_button();
        void on_herkunftsland_clicked();
        void on_muttersprache_clicked();
        void gw_wuerfeln();
        void werte_editieren();
        void on_abge_werte_setzen_clicked();
        void grundwerte_boni_setzen();
        void on_neuer_charakter_clicked();
        void on_button_hilfe_clicked();
        void on_charakter_beschreibung_clicked();
        void midgard_CG::charakter_db_anlegen();
        void on_laden_clicked();
        void load_charakter();
        void on_latex_clicked();
        void latex_beschreibung_drucken();
        void on_button_info_clicked();
        void LaTeX_zauber_main();
        void LaTeX_zauber();
        string LaTeX_string(int i);
        void on_schliessen_CG_clicked();
        void on_lernpunkte_wuerfeln_clicked();
        void on_lernpunkte_editieren_clicked();
        void on_button_ruestung_clicked();
        void on_button_geld_waffen_clicked();
        void on_button_geld_s_clicked();
        void on_button_ruestung_s_clicked();
        void on_button_waffen_s_clicked();
        void get_typ(styp& typ);
        string ruestung(string mod);
        void on_waffen_clist_select_row(gint row, gint column, GdkEvent *event);   
        void on_waffen_clist_unselect_row(gint row, gint column, GdkEvent *event);
        void on_fertigkeiten_wahl_clicked();
        void on_waffen_wahl_clicked();
        void spezialgebiet_button();
        void on_zauber_wahl_clicked();
        void on_berufe_wahl_clicked();
        string  get_erfolgswert_zaubern(styp typ,string name);
        int get_spezial_zauber(string typ,string name);
        void show_berufe();
        void show_waffen();
        void show_zauber();
        void zeige_lernpunkte();
        void Zauber_get_daten(vector<st_zauber>& zauber);
        void on_beruf_erfolgswert_clicked();
        gint on_angeborene_fertigkeit_button_release_event(GdkEventButton *ev);
        void on_angeborene_fertigkeit_clicked();
        void on_angeborene_fertigkeit_right_clicked();
        void on_spezialwaffe_clicked();
        void on_checkbutton_info_fenster_toggled();
        void on_checkbutton_Eschar_toggled();
        void on_checkbutton_Rawindra_toggled();
        void on_checkbutton_KanThaiPan_toggled();
        void on_checkbutton_Nahuatlan_toggled();
        void on_checkbutton_Waeland_toggled();
        void on_checkbutton_Alba_toggled();

        void on_grad_anstieg_clicked();
        void get_grad(int gfp);
        void get_ausdauer(int grad);
        void get_abwehr_resistenz_wert(int grad);
        void get_zauber(int grad);
        void get_grundwerte();
         
        void on_fertigkeiten_laden_clicked();
        void on_steigern_fert_clist_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_steigern_fert_clist_neu_select_row(gint row, gint column, GdkEvent *event);
        void show_alte_fertigkeiten();
        void show_neue_fertigkeiten();
        void on_radio_fert_steigern_toggled();
        void on_radio_fert_reduzieren_toggled();
        void on_radio_fert_verlernen_toggled();
        void on_togglebutton_praxispunkte_fertigkeiten_toggled();
        void on_radiobutton_praxis_wuerfeln_fertigkeiten_toggled();
        void on_radiobutton_praxis_auto_fertigkeiten_toggled();
        int praxispunkte_wuerfeln(string fert,int alter_wert, string art,bool wuerfeln);
        int midgard_CG::attribut_check(string atr);

        void on_waffen_laden_clicked();
        void show_alte_grund();
        void show_neue_grund();
        void show_alte_waffen();
        void show_neue_waffen();
        void on_grundkenntnisse_clist_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_grundkenntnisse_clist_neu_select_row(gint row, gint column, GdkEvent *event);
        void on_steigern_waffen_clist_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_steigern_waffen_clist_neu_select_row(gint row, gint column, GdkEvent *event);
        void on_radio_waffen_steigern_toggled();
        void on_radio_waffen_reduzieren_toggled();
        void on_togglebutton_praxispunkte_waffen_toggled();
        void on_radiobutton_praxis_wuerfeln_waffen_toggled();
        void on_radiobutton_praxis_auto_waffen_toggled();
        string get_Verteidigungswaffe(int ohne_waffe);


        void on_zauber_laden_clicked();
        void on_spruchrolle_toggled();
        int midgard_CG::spruchrolle_wuerfeln(int istufe, string art, string zauber);
        void on_steigern_zauber_clist_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_steigern_zauber_clist_neu_select_row(gint row, gint column, GdkEvent *event);
        void show_alte_zauber();
        void show_neue_zauber();

        void on_sprache_laden_clicked();
        void on_steigern_sprache_clist_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_steigern_sprache_clist_neu_select_row(gint row, gint column, GdkEvent *event);
        void on_radio_sprache_steigern_toggled();
        void on_radio_sprache_reduzieren_toggled();
        void on_radio_sprache_verlernen_toggled();
        void on_clist_steigern_schrift_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_steigern_schrift_neu_select_row(gint row, gint column, GdkEvent *event);
        void show_alte_schriften();
        void show_neue_schriften();
        void show_alte_sprachen();
        void show_neue_sprachen();
        void sprachen_schrift();

   public:
         midgard_CG();
         st_werte werte;
         void on_speichern_clicked();
         void charakter_beschreibung_uebernehmen(string b);
         void charakter_beschreibung_drucken(string b);
         void select_charakter(string name, string version);
         void zeige_werte(const st_werte& w, const string welche);
         void setze_lernpunkte(st_lernpunkte& lernpunkte);
         void fertigkeiten_uebernehmen(vector<st_ausgewaehlte_fertigkeiten>& saf);
         void show_fertigkeiten();
         void waffen_uebernehmen(vector<st_ausgewaehlte_waffen>& saw,map<string,string> wg);
         void waffe_besitz_uebernehmen(vector<st_waffen_besitz>& wbu);
         void zauber_uebernehmen(vector<st_ausgewaehlte_zauber>& saz);
         void berufe_uebernehmen(vector<st_ausgewaehlte_berufe>& sab);
         double get_standard_zauber(string typ, string zauber);
         double get_standard_waffen(string typ,string waffe);
         double get_standard_fertigkeit(string typ, string fertigkeit);
         void sprache_uebernehmen(string s, int wert);
         void schrift_uebernehmen(string s, string t);
         void herkunft_uebernehmen(string s);
         string waffe_werte(const st_waffen_besitz& waffe,st_werte& werte, string mod);
         vector<string> Berufs_Vorteile();
         bool Fertigkeiten_Voraussetzung(const string fertigkeit);
         bool Waffen_Voraussetzung(const string waffe);
         bool region_check(string region);
};
#endif
