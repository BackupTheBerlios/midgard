// generated 2003/2/25 21:37:35 CET by christof@puck.petig-baender.de
// using glademm V1.1.3e_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- midgard.glade
// for gtk 2.2.1 and gtkmm 2.2.0
//
// Please modify the corresponding derived classes in ./src/table_zufall.hh and./src/table_zufall.cc

#ifndef _TABLE_ZUFALL_GLADE_HH
#  define _TABLE_ZUFALL_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/table.h>
#include <gtkmm/tooltips.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/combo.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include "SimpleTree.hh"
#include "MyScale.hh"

class table_zufall_glade : public Gtk::Table
{  
protected:
        
        Gtk::Tooltips _tooltips;
        class Gtk::Table *table_zufall;
        class Gtk::CheckButton *checkbutton_spezies;
        class Gtk::CheckButton *checkbutton_herkunft;
        class Gtk::CheckButton *checkbutton_typ;
        class Gtk::CheckButton *checkbutton_ange_fert;
        class Gtk::Combo *combo_spezies;
        class Gtk::Combo *combo_typ;
        class Gtk::Combo *combo_herkunft;
        class Gtk::CheckButton *checkbutton_werte;
        class Gtk::CheckButton *checkbutton_st;
        class Gtk::CheckButton *checkbutton_gs;
        class Gtk::CheckButton *checkbutton_gw;
        class Gtk::CheckButton *checkbutton_ko;
        class Gtk::CheckButton *checkbutton_in;
        class Gtk::CheckButton *checkbutton_zt;
        class Gtk::CheckButton *checkbutton_au;
        class Gtk::CheckButton *checkbutton_pa;
        class Gtk::CheckButton *checkbutton_wk;
        class Gtk::CheckButton *checkbutton_sb;
        class Gtk::CheckButton *checkbutton_b;
        class Gtk::SpinButton *spinbutton_st;
        class Gtk::SpinButton *spinbutton_au;
        class Gtk::SpinButton *spinbutton_pa;
        class Gtk::SpinButton *spinbutton_wk;
        class Gtk::SpinButton *spinbutton_sb;
        class Gtk::SpinButton *spinbutton_b;
        class Gtk::SpinButton *spinbutton_gs;
        class Gtk::SpinButton *spinbutton_gw;
        class Gtk::SpinButton *spinbutton_ko;
        class Gtk::SpinButton *spinbutton_in;
        class Gtk::SpinButton *spinbutton_zt;
        class Gtk::Frame *frame_werte_vorgaben;
        class Gtk::Frame *frame_vorgaben;
        class Gtk::ToggleButton *togglebutton_vorgaben;
        class Gtk::Button *button_zufall_voll;
        class Gtk::RadioButton *radiobutton_proto_verteilen;
        class Gtk::RadioButton *radiobutton_proto_spezialisieren;
        class Gtk::SpinButton *spinbutton_ausnahme;
        class Gtk::SpinButton *spinbutton_standard;
        class Gtk::SpinButton *spinbutton_grund;
        class Gtk::Frame *frame_verteilung_auf;
        class SimpleTree *tree_prototyp;
        class Gtk::Frame *frame_spezialist_typen;
        class Gtk::SpinButton *spinbutton_zauberwerk;
        class MyScale *scale_fert;
        class MyScale *scale_waffen;
        class MyScale *scale_sprachen;
        class MyScale *scale_schriften;
        class Gtk::SpinButton *spinbutton_fertigkeit;
        class Gtk::SpinButton *spinbutton_waffen;
        class Gtk::SpinButton *spinbutton_waffen_grund;
        class Gtk::SpinButton *spinbutton_zauber;
        class Gtk::SpinButton *spinbutton_sprachen;
        class Gtk::SpinButton *spinbutton_schriften;
        class Gtk::Frame *frame_prototyp_mod;
        class Gtk::RadioButton *radiobutton_steigern_gfp;
        class Gtk::SpinButton *spinbutton_grad;
        class Gtk::SpinButton *spinbutton_gfp;
        class Gtk::RadioButton *radiobutton_steigern_grad;
        class Gtk::Combo *combo_prototyp;
        class Gtk::ToggleButton *togglebutton_prototyp;
        
        table_zufall_glade(GlademmData *_data);
        
        ~table_zufall_glade();
private:
        virtual void on_checkbutton_spezies_toggled() = 0;
        virtual void on_checkbutton_herkunft_toggled() = 0;
        virtual void on_checkbutton_typ_toggled() = 0;
        virtual void on_combo_spezies_activate() = 0;
        virtual bool on_combo_spezies_focus_out_event(GdkEventFocus *ev) = 0;
        virtual void on_combo_spezies_changed() = 0;
        virtual void on_combo_typ_activate() = 0;
        virtual bool on_combo_typ__focus_out_event(GdkEventFocus *ev) = 0;
        virtual void on_combo_typ__changed() = 0;
        virtual void on_checkbutton_werte_toggled() = 0;
        virtual void on_checkbutton_st_toggled() = 0;
        virtual void on_checkbutton_gs_toggled() = 0;
        virtual void on_checkbutton_gw_toggled() = 0;
        virtual void on_checkbutton_ko_toggled() = 0;
        virtual void on_checkbutton_in_toggled() = 0;
        virtual void on_checkbutton_zt_toggled() = 0;
        virtual void on_checkbutton_au_toggled() = 0;
        virtual void on_checkbutton_pa_toggled() = 0;
        virtual void on_checkbutton_wk_toggled() = 0;
        virtual void on_checkbutton_sb_toggled() = 0;
        virtual void on_checkbutton_b_toggled() = 0;
        virtual void on_togglebutton_vorgaben_toggled() = 0;
        virtual void on_button_zufall_voll_clicked() = 0;
        virtual void on_button_steigern_clicked() = 0;
        virtual void on_radiobutton_proto_verteilen_toggled() = 0;
        virtual void on_radiobutton_proto_spezialisieren_toggled() = 0;
        virtual void on_spinbutton_ausnahme_activate() = 0;
        virtual void on_spinbutton_standard_activate() = 0;
        virtual void on_spinbutton_grund_activate() = 0;
        virtual void on_tree_prototyp_leaf_selected(cH_RowDataBase leaf) = 0;
        virtual void on_spinbutton_zauberwerk_activate() = 0;
        virtual void on_button_check100_clicked() = 0;
        virtual void on_scale_fert_activate() = 0;
        virtual void on_scale_waffen_activate() = 0;
        virtual void on_scale_sprachen_activate() = 0;
        virtual void on_scale_schriften_activate() = 0;
        virtual void on_spinbutton_fertigkeit_activate() = 0;
        virtual void on_spinbutton_waffen_activate() = 0;
        virtual void on_spinbutton_waffen_grund_activate() = 0;
        virtual void on_spinbutton_zauber_activate() = 0;
        virtual void on_spinbutton_sprachen_activate() = 0;
        virtual void on_spinbutton_schriften_activate() = 0;
        virtual void on_radiobutton_steigern_gfp_toggled() = 0;
        virtual void on_radiobutton_steigern_grad_toggled() = 0;
        virtual void on_combo_prototyp_activate() = 0;
        virtual bool on_combo_prototyp_focus_out_event(GdkEventFocus *ev) = 0;
        virtual void on_combo_prototyp_changed() = 0;
        virtual void on_togglebutton_prototyp_toggled() = 0;
};
#endif
