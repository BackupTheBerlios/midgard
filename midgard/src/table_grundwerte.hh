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
#include <Model.h>
#include <Misc/UniqueValue.h>


class table_grundwerte : public table_grundwerte_glade
{  
        
        friend class table_grundwerte_glade;
        friend class midgard_CG;
        friend class Zufall;
        friend class table_zufall;
        friend class BegruessungsWindow;
        midgard_CG *hauptfenster;

        bool block_changed;
        Model<bool> edit_werte;
public:
        
        table_grundwerte(GlademmData *_data) 
            : table_grundwerte_glade(_data), hauptfenster(0),
              block_changed(false),edit_werte(false),label(0) {}
        void init(midgard_CG *hauptfenster);
        void fill_typauswahl();  
        void fill_typauswahl_2();
        void neuer_charakter();
        void doppelcharaktere();

        static const UniqueValue::value_t trace_channel;

private:
        std::vector<std::string> Vstand, Vhand;

        void grundwerte_wuerfeln();
        void Eigenschaften_variante(int i);
        void check_350(const std::vector<int>& a = std::vector<int>());
        void gw_wuerfeln_2x();
        int  constraint_gw(int constraint);
        int  constraint_aw(int constraint);
        int  wuerfeln_best_of_two();
        void midgard_check_werte100();

        void edit_sensitive(bool b);
        
        void fill_typauswahl_fill(int typ_1_2);
        void fill_spezies();
        void typauswahl_button();  
        void typauswahl_2_button();
        void spezieswahl_button();
        void zeige_werte(bool typ2_hide=true);

        // Für Variante 2 + 3
        enum e_eigen{est,egw,egs,eko,ein,ezt,eMAX};
//        friend e_eigen &operator++(e_eigen &s);
	friend class spezies_mod_comp;
        struct st_eigen{e_eigen eigenschaft;std::string lang;std::string kurz;
        		int spezies_mod; 
               st_eigen(e_eigen e,std::string l,std::string k,int spezies_m=0)  
                   : eigenschaft(e),lang(l),kurz(k),spezies_mod(spezies_m){}
               bool operator==(const e_eigen& b) const 
                           {return eigenschaft== b;}
                    };
        std::vector<st_eigen>::const_iterator actual_eigen;
        
        Gtk::Label *label;
        std::vector<st_eigen> Veigenschaften;
        void set_Grundwerte(e_eigen eigenschaft,int wert);
        void Schwachpunkt_wuerfeln();

        // Für Variante 2
        int actual_wurf;
        void gw_variante_2();
        void gw_variante_2_next();
        void on_button_variante_2_clicked(Gtk::Button *button,e_eigen eigenschaft);

        // Für Variante 3
        void gw_variante_3();
        void gw_variante_3_next();
        void on_button_variante_3_clicked(Gtk::Button *button,int wert);
        
        
        // Ab hier die automatischen Methoden von glade erzeugt        
   private:
        void on_combo_spezies_changed();
        void on_combo_spezies_activate();
        bool on_combo_spezies_focus_out_event(GdkEventFocus *ev);
        void on_combo_typ__changed();
        void on_combo_typ_activate();
        void on_combo_typ2__changed();
        void on_combo_typ2_activate();
        bool on_combo_typ__focus_out_event(GdkEventFocus *ev);
        bool on_combo_typ2_focus_out_event(GdkEventFocus *ev);
        void on_combo_stand_activate();
        bool on_combo_stand_focus_out_event(GdkEventFocus *ev);
        void on_combo_hand_activate();
        bool on_combo_hand_focus_out_event(GdkEventFocus *ev);
        void on_button_grda1setzen_clicked();
        void on_spinbutton_b_activate();
        bool on_spinbutton_b_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_b_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_au_activate();
        bool on_spinbutton_au_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_au_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_pa_activate();
        bool on_spinbutton_pa_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_pa_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_sb_activate();
        bool on_spinbutton_sb_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_sb_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_wk_activate();
        bool on_spinbutton_wk_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_wk_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_st_activate();
        bool on_spinbutton_st_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_st_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gs_activate();
        bool on_spinbutton_gs_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_gs_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gw_activate();
        bool on_spinbutton_gw_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_gw_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_ko_activate();
        bool on_spinbutton_ko_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_ko_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_in_activate();
        bool on_spinbutton_in_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_in_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_zt_activate();
        bool on_spinbutton_zt_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_zt_focus_in_event(GdkEventFocus *ev);
        void on_entry_nameC_activate();
        bool on_entry_nameC_focus_out_event(GdkEventFocus *ev);
        bool on_entry_nameC_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_ap_activate();
        bool on_spinbutton_ap_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_ap_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_lp_activate();
        bool on_spinbutton_lp_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_lp_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_grad_activate();
        bool on_spinbutton_grad_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_grad_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_alter_activate();
        bool on_spinbutton_alter_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_alter_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_Cgewicht_activate();
        bool on_spinbutton_Cgewicht_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_Cgewicht_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_groesse_activate();
        bool on_spinbutton_groesse_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_groesse_focus_in_event(GdkEventFocus *ev);
        void on_entry_nameS_activate();
        bool on_entry_nameS_focus_out_event(GdkEventFocus *ev);
        bool on_entry_nameS_focus_in_event(GdkEventFocus *ev);
        void on_entry_version_activate();
        bool on_entry_version_focus_out_event(GdkEventFocus *ev);
        bool on_entry_version_focus_in_event(GdkEventFocus *ev);
        void on_entry_herkunft_activate();
        bool on_entry_herkunft_focus_out_event(GdkEventFocus *ev);
        bool on_entry_herkunft_focus_in_event(GdkEventFocus *ev);
        void on_entry_glaube_activate();
        bool on_entry_glaube_focus_out_event(GdkEventFocus *ev);
        bool on_entry_glaube_focus_in_event(GdkEventFocus *ev);
        void on_entry_spezialisierung_activate();
        bool on_entry_spezialisierung_focus_out_event(GdkEventFocus *ev);
        bool on_entry_spezialisierung_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_tage_activate();
        bool on_spinbutton_tage_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_tage_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gg_activate();
        bool on_spinbutton_gg_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_gg_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_sg_activate();
        bool on_spinbutton_sg_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_sg_focus_in_event(GdkEventFocus *ev);
        void on_spinbutton_gfp_activate();
        bool on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev);
        bool on_spinbutton_gfp_focus_in_event(GdkEventFocus *ev);
        void on_entry_bezeichnung_activate();
        bool on_entry_bezeichnung_focus_out_event(GdkEventFocus *ev);
        bool on_entry_bezeichnung_focus_in_event(GdkEventFocus *ev);
        void on_entry_merkmale_activate();
        bool on_entry_merkmale_focus_out_event(GdkEventFocus *ev);
        bool on_entry_merkmale_focus_in_event(GdkEventFocus *ev);
        bool on_button_grundwerte_button_release_event(GdkEventButton *ev);
        void on_radiobutton_mann_toggled();
        void on_radiobutton_frau_toggled();
        void on_radiobutton_stadt_land_toggled();
        void on_abge_werte_setzen_clicked();
        void on_togglebutton_edit_werte_toggled();
};
#endif
