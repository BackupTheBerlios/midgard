// generated 2002/5/16 18:55:17 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_lernschema.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _TABLE_LERNSCHEMA_HH
#  include "table_lernschema_glade.hh"
#  define _TABLE_LERNSCHEMA_HH

#include "class_lernpunkte.hh"
#include "MidgardBasicElement.hh"
class midgard_CG;
class AusruestungBaum;
#include "Waffe.hh"
#include "Beruf.hh"

class table_lernschema : public table_lernschema_glade
{  
        friend class table_lernschema_glade;
        friend class table_grundwerte;
        friend class midgard_CG;  
        friend class Zufall;


        midgard_CG *hauptfenster; 
        Lernpunkte lernpunkte;
        std::list<std::string> list_FertigkeitZusaetze;
        WaffeBesitzLernen waffebesitzlernen;
        MidgardBasicTree *tree_lernschema;
        SimpleTree *Beruf_tree;
        MidgardBasicTree *tree_angeb_fert;
        MidgardBasicTree *tree_kido_lernschema;
        MidgardBasicTree *tree_waffen_lernschema;
        int maxkido;
        BerufsKategorie BKategorie;
        std::list<MBEmlt> list_Fertigkeit_ang_neu;                                        
        enum GWR_Auswahl {ENone,EGeld1,EGeld2,EGeld3,EWaffen,ERuestung};
        GWR_Auswahl gwr_auswahl;
        std::vector<int> VGeldwurf;
        std::vector<cH_RowDataBase> datavec_zusatz;
        
private:
       void show_datavec_zusatz();
       void lernen_zusatz(MidgardBasicElement::eZusatz was,MBEmlt& _MBE);
       void lernen_zusatz_titel(MidgardBasicElement::eZusatz was,const MBEmlt& MBE);

       void set_gwr_eingabe();
       void on_herkunft_leaf_selected(cH_RowDataBase d);
       void on_herkunft_ueberleben_leaf_selected(cH_RowDataBase d);
       void on_tree_lernschema_leaf_selected(cH_RowDataBase d);
       void on_zusatz_leaf_selected(cH_RowDataBase d);
       void on_zusatz_leaf_sprache_selected(cH_RowDataBase d);
       void on_zusatz_leaf_schrift_selected(cH_RowDataBase d);
       void set_zusatz_sensitive(bool an);
       void show_gelerntes();
       void show_lernschema();
       void zeige_lernpunkte();
       void set_lernpunkte();
       void button_sensitive(bool b);
       void edit_lernpunkte(bool b);
       void zeige_werte();
       void lernschema_geld_wuerfeln(const std::vector<int>& VGeldwurf);
       void geld_wuerfeln();
       void on_button_ruestung_clicked(int wurf);
       void setTitels_for_Lernschema(const MidgardBasicElement::MBEE& what,const std::string& fert);
       void clean_lernschema_trees();        

       // Beruf
       void deleteBerufsFertigekeit();
       void showBerufsLernList();
       void beruf_gewuerfelt(int wurf);
       void on_beruf_tree_leaf_selected(cH_RowDataBase d);

       // Fertigkeiten
       void on_angeborene_fertigkeit_clicked();
       void on_angeborene_fertigkeit_right_clicked();
       void on_ang_fert_leaf_selected(cH_RowDataBase d);
       std::string AngebFert_gewuerfelt(int wurf);
       void lernpflichten_info();
       
       // Waffen
       void show_WaffenBesitz_lernschema();
       void on_waffen_lernschema_tree_leaf_selected(cH_RowDataBase d);
       void WaffenBesitz_lernschema_wuerfeln(int wurf);
       void on_togglebutton_spezialwaffe_toggled();
       
       // Zauber
       void show_magier_spezialgebiet(bool show);
       void spezialgebiet_button_fill();
//       void spezialgebiet_button();
       
       // KiDo
       void fill_kido_lernschema();
       void on_tree_kido_lernschema_leaf_selected(cH_RowDataBase d);

       // Ausrüstung
//       void setStandardAusruestung();
//       void setFertigkeitenAusruestung(AusruestungBaum &Rucksack);
       void setFertigkeitenAusruestung();
       void InfoFensterAusruestung(const std::string &fert_name,
                        const std::string &gegen_name,int wurf,int noetig);
       
public:
        
        table_lernschema(GlademmData *_data) 
          : table_lernschema_glade(_data), hauptfenster(0),
          tree_lernschema(0),Beruf_tree(0),tree_angeb_fert(0),tree_kido_lernschema(0),
            tree_waffen_lernschema(0),maxkido(0) {}
        void init(midgard_CG *hauptfenster);

      // Ab hier die automatischen Methoden von glade erzeugt
private:
        void on_combo_kido_stil_activate();
        bool on_combo_kido_stil_focus_out_event(GdkEventFocus *ev);
        void on_combo_magier_spezialgebiet_activate();
        bool on_combo_magier_spezialgebiet_focus_out_event(GdkEventFocus *ev);
        void on_button_waffe_trans_clicked();
        void on_button_fach_trans_clicked();
        void on_spinbutton_fach_activate();
        bool on_spinbutton_fach_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_fach_focus_in_event(GdkEventFocus *ev);
        void on_lernliste_wahl_toggled();
        void on_spinbutton_allgemein_activate();
        bool on_spinbutton_allgemein_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_allgemein_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_waffen_activate();
        bool on_spinbutton_waffen_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_waffen_focus_in_event(GdkEventFocus *ev);
        void on_button_waffen_clicked();
        void on_spinbutton_zaubern_activate();
        bool on_spinbutton_zaubern_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_zaubern_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_unge_activate();
        bool on_spinbutton_unge_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_unge_focus_in_event(GdkEventFocus *ev);
        void on_kido_wahl_clicked();
        void on_tree_gelerntes_leaf_selected(cH_RowDataBase d);
        void on_herkunftsland_clicked();
        bool on_angeborene_fertigkeit_button_release_event(GdkEventButton *ev);
        void on_lernpunkte_wuerfeln_clicked();
        void on_togglebutton_lernpunkte_edit_toggled();
        bool on_button_beruf_release_event(GdkEventButton *ev);
        void on_spinbutton_beruf_activate();
        bool on_spinbutton_beruf_focus_in(GdkEventFocus *ev);
        void on_entry_berufsname_activate();
        bool on_button_lernschema_geld_button_release_event(GdkEventButton *ev);
        bool on_button_lernschema_waffen_button_release_event(GdkEventButton *ev);
        void on_spinbutton_waffen_lernschema_activate();
        bool on_spinbutton_waffen_lernschema_focus_in_event(GdkEventFocus *ev);
        bool on_button_ruestung_button_release_event(GdkEventButton *ev);
        bool on_button_ausruestung_button_release_event(GdkEventButton *ev);
        void ausruestung_setzen();
        void on_togglebutton_teure_anzeigen_toggled();
        void on_togglebutton_gelernte_anzeigen_toggled();
        void on_togglebutton_einschraenkungen_zusatz_anzeigen_toggled();
        bool on_eventbox_zusatz_leave_notify_event(GdkEventCrossing *ev);
        void on_combo_magier_changed();
        void on_combo_kido_stil_changed();
};
#endif
