// generated 2002/5/14 9:41:31 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_grundwerte.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _TABLE_GRUNDWERTE_HH
#  include "table_grundwerte_glade.hh"
#  define _TABLE_GRUNDWERTE_HH

class midgard_CG;
#include <vector>

class table_grundwerte : public table_grundwerte_glade
{  
        
        friend class table_grundwerte_glade;
        friend class midgard_CG;
        midgard_CG *hauptfenster;
public:
        
        table_grundwerte(GlademmData *_data) 
            : table_grundwerte_glade(_data), hauptfenster(0) {}
        void init(midgard_CG *hauptfenster);
        void fill_typauswahl();  
        void fill_typauswahl_2();
        void kaempfer_lernt_zaubern();
        void neuer_charakter();
        void doppelcharaktere();

private:
        int werte_label_count;
        std::vector<std::string> Vstand, Vhand;

        void grundwerte_wuerfeln();
        void Eigenschaften_variante(int i);
        void check_350(const std::vector<int>& a);
        void gw_setzen(Gtk::Label *L=0,int button=0);
        void set_werte_label_2();
        void set_werte_label_3(Gtk::Label *L=0);
        void gw_wuerfeln_2x();
        int  constraint_gw(int constraint);
        int  constraint_aw(int constraint);
        int  wuerfeln_best_of_two();
        void original_midgard_check();

        void edit_sensitive(bool b);
        
        void fill_typauswahl_fill(int typ_1_2);
        void fill_spezies();
        void typauswahl_button();  
        void typauswahl_2_button();
        void spezieswahl_button();
        void zeige_werte();
        
        // Ab hier die automatischen Methoden von glade erzeugt        
   private:
        void on_button_wert_1_clicked();
        void on_button_wert_2_clicked();
        void on_button_wert_3_clicked();
        void on_button_wert_4_clicked();
        void on_button_wert_5_clicked();
        void on_button_wert_6_clicked();
        void on_button_grda1setzen_clicked();
        void on_spinbutton_b_activate();
        gint on_spinbutton_b_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_b_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_au_activate();
        gint on_spinbutton_au_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_au_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_pa_activate();
        gint on_spinbutton_pa_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_pa_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_sb_activate();
        gint on_spinbutton_sb_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_sb_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_wk_activate();
        gint on_spinbutton_wk_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_wk_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_st_activate();
        gint on_spinbutton_st_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_st_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gs_activate();
        gint on_spinbutton_gs_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gs_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gw_activate();
        gint on_spinbutton_gw_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gw_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_ko_activate();
        gint on_spinbutton_ko_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_ko_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_in_activate();
        gint on_spinbutton_in_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_in_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_zt_activate();
        gint on_spinbutton_zt_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_zt_focus_in_event(GdkEventFocus *ev);
        void on_entry_nameC_activate();
        gint on_entry_nameC_focus_out_event(GdkEventFocus *ev);
        gint on_entry_nameC_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_ap_activate();
        gint on_spinbutton_ap_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_ap_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_lp_activate();
        gint on_spinbutton_lp_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_lp_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_grad_activate();
        gint on_spinbutton_grad_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_grad_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_alter_activate();
        gint on_spinbutton_alter_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_alter_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_Cgewicht_activate();
        gint on_spinbutton_Cgewicht_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_Cgewicht_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_groesse_activate();
        gint on_spinbutton_groesse_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_groesse_focus_in_event(GdkEventFocus *ev);
        void on_entry_nameS_activate();
        gint on_entry_nameS_focus_out_event(GdkEventFocus *ev);
        gint on_entry_nameS_focus_in_event(GdkEventFocus *ev);
        void on_entry_version_activate();
        gint on_entry_version_focus_out_event(GdkEventFocus *ev);
        gint on_entry_version_focus_in_event(GdkEventFocus *ev);
        void on_entry_herkunft_activate();
        gint on_entry_herkunft_focus_out_event(GdkEventFocus *ev);
        gint on_entry_herkunft_focus_in_event(GdkEventFocus *ev);
        void optionmenu_stand_deactivate();
        void on_entry_glaube_activate();
        gint on_entry_glaube_focus_out_event(GdkEventFocus *ev);
        gint on_entry_glaube_focus_in_event(GdkEventFocus *ev);
        void on_entry_spezialisierung_activate();
        gint on_entry_spezialisierung_focus_out_event(GdkEventFocus *ev);
        gint on_entry_spezialisierung_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_tage_activate();
        gint on_spinbutton_tage_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_tage_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gg_activate();
        gint on_spinbutton_gg_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gg_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_sg_activate();
        gint on_spinbutton_sg_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_sg_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gfp_activate();
        gint on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gfp_focus_in_event(GdkEventFocus *ev);
        void optionmenu_hand_deactivate();
        void on_entry_bezeichnung_activate();
        gint on_entry_bezeichnung_focus_out_event(GdkEventFocus *ev);
        gint on_entry_bezeichnung_focus_in_event(GdkEventFocus *ev);
        void on_entry_merkmale_activate();
        gint on_entry_merkmale_focus_out_event(GdkEventFocus *ev);
        gint on_entry_merkmale_focus_in_event(GdkEventFocus *ev);
        gint on_button_grundwerte_button_release_event(GdkEventButton *ev);
        void on_radiobutton_mann_toggled();
        void on_radiobutton_frau_toggled();
        void on_radiobutton_stadt_land_toggled();
        void on_abge_werte_setzen_clicked();
        void on_togglebutton_edit_werte_toggled();
};
#endif
