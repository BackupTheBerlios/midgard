// generated 2002/5/23 18:30:41 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_steigern.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _TABLE_STEIGERN_HH
#  include "table_steigern_glade.hh"
#  define _TABLE_STEIGERN_HH
class midgard_CG;
#include "MidgardBasicElement.hh"
#include <list>
class LernListen;
#include "Enums.hh"
#include <MVC.h>

class table_steigern : public table_steigern_glade
{  
        
        friend class table_steigern_glade;
        friend class midgard_CG;
        friend class Midgard_Optionen; // Zum Speichern der Handle-Fenster Positionen
        midgard_CG *hauptfenster;
        LernListen *LL;        

        std::list<MBEmlt> list_Fertigkeit_neu;
        std::list<MBEmlt> list_WaffenGrund_neu;
        std::list<MBEmlt> list_Waffen_neu;
        std::list<MBEmlt> list_Zauber_neu;
        std::list<MBEmlt> list_Zauberwerk_neu;
        std::list<MBEmlt> list_Kido_neu;
        std::list<MBEmlt> list_Sprache_neu;
        std::list<MBEmlt> list_Schrift_neu;

        MVC<bool> steigern_mit_EP_bool;
        enum enum_notebook_lernen{PAGE_FERTIGKEITEN,PAGE_WAFFEN,PAGE_ZAUBER,
                                  PAGE_KIDO,PAGE_SPRACHE,PAGE_BESITZ};
                                  
//        enum modi_modus{Zusatz,PP};
//        void modify(modi_modus modus,const MBEmlt &M,const MidgardBasicElement::st_zusatz &zusatz,int praxispunkte);
//        void modify(modi_modus modus,const MBEmlt &M,const std::string &s,int praxispunkte)
//          {modify(modus,M,MidgardBasicElement::st_zusatz(s),praxispunkte);}
public:
        
        table_steigern(GlademmData *_data) 
         : table_steigern_glade(_data),hauptfenster(0),LL(0),
            steigern_mit_EP_bool(true) {}
        void init(midgard_CG *hauptfenster);

private:
        const MBEmlt &getSelectedNotebookLernen() throw(TreeBase::noRowSelected); 
        void load_for_page(guint pagenr);
        void zeige_werte();
        void neuer_charakter();

        // Main
        void fillClistZusatz(MBEmlt &MBE);
        void set_zusatz_sensitive(bool an);
        void on_radio_steigern_all();
        std::string SpruecheMitPP();
        void on_radiobutton_pp_all_toggled();
        bool MidgardBasicElement_leaf_alt(const cH_RowDataBase &d);
        void MidgardBasicElement_leaf_neu(const cH_RowDataBase &d);
        void show_goldeingabe(bool b,int button=0);
        void show_EPeingabe(bool b,int button=0);
        
        // Grad anstieg
private:
        const Enums::e_wie_steigern get_wie_steigern();
        const Enums::st_bool_steigern get_bool_steigern();

        void get_grundwerte(int wurf);
        void get_ab_re_za(Enums::e_was_steigern was);//,bool verschenke_pp=false);


        // EP
        void steigern_gtk();

        // Fertigkeiten
        void fertigkeiten_zeigen();
        void alte_fertigkeiten_zeigen();
        void neue_fertigkeiten_zeigen();
        
        // Waffen
        void on_waffen_laden_clicked();
        void neue_waffen_zeigen();
        void alte_waffen_zeigen();
        void waffen_zeigen();
        void waffengrund_zeigen();

        // Zauber
        void on_zauber_laden_clicked();
        void zauber_zeigen();
        void zauberwerk_laden();
        void zauberwerk_zeigen();

        // Sprache
       void schriften_zeigen();
       void sprachen_zeigen();
       void alte_sprache_zeigen();
       void alte_schrift_zeigen();
       void neue_sprache_zeigen();
       void neue_schrift_zeigen();
        void neue_schrift_wegen_sprache();
        int andereSprache_gleicheSchriftart(std::string art);


        // KiDo
        bool kido_steigern_check(int wert);
        void on_kido_laden_clicked();
        void kido_zeigen();

        // Besitz
        void fill_ruestung();
        void show_label();
        void init_waffenbesitz();
        void lade_waffenbesitz();
        void show_alte_waffen();


         // Ab hier die automatischen Methoden von glade erzeugt
private:
        void on_steigern_zusatz_leaf_selected(cH_RowDataBase d);
        void on_leaf_selected_alte_fert(cH_RowDataBase d);
        void on_alte_fert_reorder();
        void on_leaf_selected_neue_fert(cH_RowDataBase d);
        void on_leaf_selected_alte_waffen(cH_RowDataBase d);
        void on_alte_waffen_reorder();
        void on_leaf_selected_neue_waffen(cH_RowDataBase d);
        void on_leaf_selected_alte_grund(cH_RowDataBase d);
        void on_leaf_selected_neue_grund(cH_RowDataBase d);
        void on_leaf_selected_alte_zauber(cH_RowDataBase d);
        void on_alte_zauber_reorder();
        void on_leaf_selected_neue_zauber(cH_RowDataBase d);
        void on_leaf_selected_alte_zauberwerk(cH_RowDataBase d);
        void on_alte_zaubermittel_reorder();
        void on_leaf_selected_neue_zauberwerk(cH_RowDataBase d);
        void on_leaf_selected_alte_kido(cH_RowDataBase d);
        void on_alte_kido_reorder();
        void on_leaf_selected_neue_kido(cH_RowDataBase d);
        void on_leaf_selected_alte_sprache(cH_RowDataBase d);
        void on_alte_sprache_reorder();
        void on_leaf_selected_neue_sprache(cH_RowDataBase d);
        void on_leaf_selected_alte_schrift(cH_RowDataBase d);
        void on_leaf_selected_neue_schrift(cH_RowDataBase d);
        void on_notebook_lernen_switch_page(Gtk::Notebook_Helpers::Page *p0, guint p1);
        gint vscale_value_changed(GdkEventButton *ev);
        void on_checkbutton_EP_Geld_toggled();
        void on_radio_selbst_toggled();
        void on_radio_praxis_toggled();
        void on_radio_unterweisung_toggled();
        void on_spruchrolle_toggled();
        void on_togglebutton_alle_zauber_toggled();
        void on_togglebutton_zaubersalze_toggled();
        void on_radio_reduzieren_toggled();
        void on_radio_verlernen_toggled();
        void on_radio_steigern_toggled();
        void on_spinbutton_pp_eingeben_activate();
        void on_togglebutton_praxispunkte_toggled();
        void on_radiobutton_pp_fertigkeit_toggled();
        void on_radiobutton_pp_abwehr_toggled();
        void on_radiobutton_pp_zauber_toggled();
        void on_radiobutton_pp_spezial_toggled();
        void on_radiobutton_pp_resistenz_toggled();
        void on_clist_landauswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_button_grad_clicked();
        void on_button_grad_ausdauer_clicked();
        void on_button_grad_abwehr_clicked();
        void on_button_grad_zaubern_clicked();
        void on_button_grad_resistenz_clicked();
        void on_grad_anstieg_clicked();
        void on_button_grad_basiswerte_clicked();
        gint on_button_grad_basiswerte_button_release_event(GdkEventButton *ev);
        void on_spinbutton_eigenschaften_grad_anstieg_activate();
        void on_button_alter_clicked();
        void on_LabelSpin_gfp_activate();
        void on_LabelSpin_gold_activate();
        void on_LabelSpin_silber_activate();
        void on_LabelSpin_kupfer_activate();
        void on_LabelSpin_aep_activate();
        void on_LabelSpin_kep_activate();
        void on_LabelSpin_zep_activate();
        gint on_checkbutton_gfp_button_release_event(GdkEventButton *ev);
        gint on_button_gold_eingeben_button_release_event(GdkEventButton *ev);
        gint on_button_EP_eingeben_button_release_event(GdkEventButton *ev);
        void on_clist_ruestung_select_row(gint row, gint column, GdkEvent *event);
        void on_button_ruestung_1_toggled();
        void on_button_ruestung_2_toggled();
        void on_leaf_waffenbesitz_selected_alt(cH_RowDataBase d);
        void on_leaf_waffenbesitz_selected_neu(cH_RowDataBase d);
        void on_checkbutton_mag_waffenbonus_toggled();
        void on_alte_waffenbesitz_reorder();
        void on_spinbutton_av_bonus_activate();
        void on_spinbutton_sl_bonus_activate();
        void on_entry_magisch_activate();
        void on_togglebutton_pp_verfallen_toggled();
        void on_togglebutton_pp_aep_fuellen_toggled();

};
#endif
