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
//#include "midgard_CG.hh"
#include "MidgardBasicElement.hh"
#include <list>

class table_steigern : public table_steigern_glade
{  
        
        friend class table_steigern_glade;
        friend class midgard_CG;
        midgard_CG *hauptfenster;

        std::list<MidgardBasicElement_mutable> list_Fertigkeit_neu;
        std::list<MidgardBasicElement_mutable> list_WaffenGrund_neu;
        std::list<MidgardBasicElement_mutable> list_Waffen_neu;
        std::list<MidgardBasicElement_mutable> list_Zauber_neu;
        std::list<MidgardBasicElement_mutable> list_Zauberwerk_neu;
        std::list<MidgardBasicElement_mutable> list_Kido_neu;
        std::list<MidgardBasicElement_mutable> list_Sprache_neu;
        std::list<MidgardBasicElement_mutable> list_Schrift_neu;

        bool steigern_mit_EP_bool;
        enum enum_notebook_lernen{PAGE_FERTIGKEITEN,PAGE_WAFFEN,PAGE_ZAUBER,
                                  PAGE_KIDO,PAGE_SPRACHE,PAGE_BESITZ};
                                  
        enum modi_modus{Zusatz,PP};
        void modify(modi_modus modus,const MidgardBasicElement_mutable &M,const std::string &zusatz,int praxispunkte);
public:
        
        table_steigern(GlademmData *_data) 
         : table_steigern_glade(_data),hauptfenster(0) {}
        void init(midgard_CG *hauptfenster);

private:
        const MidgardBasicElement_mutable &getSelectedNotebookLernen() throw(TreeBase::noRowSelected); 
        void load_for_page(guint pagenr);
        void zeige_werte();
        void neuer_charakter();

        // Main
        void fillClistZusatz(MidgardBasicElement_mutable &MBE);
        void set_zusatz_sensitive(bool an);
        void on_radio_steigern_all();
        std::string SpruecheMitPP();
        void on_radiobutton_pp_all_toggled();
        bool MidgardBasicElement_leaf_alt(const cH_RowDataBase &d);
        void MidgardBasicElement_leaf_neu(const cH_RowDataBase &d);
        void show_goldeingabe(bool b);
        void show_EPeingabe(bool b);
        
        // Grad anstieg
public:
        enum e_was_steigern{Nichts,Ausdauer,Abwehr,Zaubern,Resistenz};
private:
        void get_grundwerte();
        void get_ausdauer(int grad);
        void get_ab_re_za(e_was_steigern was);//,bool verschenke_pp=false);
         
        // EP
        void steigern_gtk();
        int steigern_womit(const std::string& fert);
        void desteigern(unsigned int kosten);
        void set_lernzeit(int kosten,e_was_steigern was,bool no_pp=false);
        bool steigern_usp(int &kosten,MidgardBasicElement_mutable *MBE,int &stufen,e_was_steigern was=Nichts);
        int genug_geld(const int kosten);
        int EP_kosten(const int kosten);
        int PP_vorrat(const MidgardBasicElement_mutable *MBE,e_was_steigern was);
        bool genug_EP(const int ep_k,const bool bkep,const bool bzep,int &aep0,int &kep0,int &zep0);
        void steigern_mit(bool &bkep,bool &bzep,const cH_MidgardBasicElement *MBE,e_was_steigern was);
public:
//        void PraxisPunkt_to_AEP(MidgardBasicElement_mutable& MBE,bool verfallen,bool alle_pp);
//        void PraxisPunkt_fuer_Was(e_was_steigern was);
private:
         int stufen_auf_einmal_steigern_fuer_aep(MidgardBasicElement_mutable& MBE,int &kosten,int &aep);


        // Fertigkeiten
        void on_fertigkeiten_laden_clicked();
        void fertigkeiten_zeigen();
        void show_alte_fertigkeiten();
        void show_neue_fertigkeiten();
        
        // Waffen
        void on_waffen_laden_clicked();
        void on_waffengrund_laden_clicked();
        void waffen_zeigen();

        // Zauber
        void on_zauber_laden_clicked();
        void zauber_zeigen();
        bool spruchrolle_wuerfeln(const cH_MidgardBasicElement& zauber);
        void zauberwerk_laden();
        void zauberwerk_zeigen();

        // Sprache
        void on_sprache_laden_clicked();
        void on_schrift_laden_clicked();
        void schriften_zeigen();
        void sprachen_zeigen(); 
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
        void on_button_EP_toggled();
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
        void on_button_alter_clicked();
        void on_button_geld_s_toggled();
        void on_button_gfp_s_toggled();
        void on_spinbutton_gfp_activate();
        gint on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gfp_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gold_activate();
        gint on_spinbutton_gold_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gold_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_silber_activate();
        gint on_spinbutton_silber_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_silber_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_kupfer_activate();
        gint on_spinbutton_kupfer_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_kupfer_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_aep_activate();
        gint on_spinbutton_aep_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_aep_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_kep_activate();
        gint on_spinbutton_kep_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_kep_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_zep_activate();
        gint on_spinbutton_zep_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_zep_focus_in_event(GdkEventFocus *ev);
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

};
#endif
