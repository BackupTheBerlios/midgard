// generated 2002/9/27 8:04:02 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/table_zufall.cc

#include "config.h"
#include "table_zufall.hh"
#include <gtk--/entry.h>
#include <gtk--/adjustment.h>
#include <gtk--/table.h>
#include <gtk--/button.h>
#include <gtk--/frame.h>
#include <gtk--/box.h>
#include <gtk--/eventbox.h>
#include <gtk--/label.h>

table_zufall_glade::table_zufall_glade(GlademmData *_data
) : Gtk::Table(3, 3, false)
{  table_zufall = this;
   checkbutton_spezies = manage(new class Gtk::CheckButton("Spezies", 0, 0.5));
   checkbutton_herkunft = manage(new class Gtk::CheckButton("Herkunft", 0, 0.5));
   checkbutton_typ = manage(new class Gtk::CheckButton("Typ", 0, 0.5));
   checkbutton_ange_fert = manage(new class Gtk::CheckButton("angeb. Fert.", 0, 0.5));
   combo_spezies = manage(new class Gtk::Combo());
   combo_typ = manage(new class Gtk::Combo());
   combo_herkunft = manage(new class Gtk::Combo());
   checkbutton_werte = manage(new class Gtk::CheckButton("Werte", 0, 0.5));
   checkbutton_st = manage(new class Gtk::CheckButton("St", 0, 0.5));
   checkbutton_gs = manage(new class Gtk::CheckButton("Gs", 0, 0.5));
   checkbutton_gw = manage(new class Gtk::CheckButton("Gw", 0, 0.5));
   checkbutton_ko = manage(new class Gtk::CheckButton("Ko", 0, 0.5));
   checkbutton_in = manage(new class Gtk::CheckButton("In", 0, 0.5));
   checkbutton_zt = manage(new class Gtk::CheckButton("Zt", 0, 0.5));
   checkbutton_au = manage(new class Gtk::CheckButton("Au", 0, 0.5));
   checkbutton_pa = manage(new class Gtk::CheckButton("pA", 0, 0.5));
   checkbutton_wk = manage(new class Gtk::CheckButton("Wk", 0, 0.5));
   checkbutton_sb = manage(new class Gtk::CheckButton("Sb", 0, 0.5));
   checkbutton_b = manage(new class Gtk::CheckButton("B", 0, 0.5));
   
   Gtk::Adjustment *spinbutton_st_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_st = manage(new class Gtk::SpinButton(*spinbutton_st_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_au_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_au = manage(new class Gtk::SpinButton(*spinbutton_au_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_pa_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_pa = manage(new class Gtk::SpinButton(*spinbutton_pa_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_wk_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_wk = manage(new class Gtk::SpinButton(*spinbutton_wk_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_sb_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_sb = manage(new class Gtk::SpinButton(*spinbutton_sb_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_b_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_b = manage(new class Gtk::SpinButton(*spinbutton_b_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_gs_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_gs = manage(new class Gtk::SpinButton(*spinbutton_gs_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_gw_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_gw = manage(new class Gtk::SpinButton(*spinbutton_gw_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_ko_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_ko = manage(new class Gtk::SpinButton(*spinbutton_ko_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_in_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_in = manage(new class Gtk::SpinButton(*spinbutton_in_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_zt_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_zt = manage(new class Gtk::SpinButton(*spinbutton_zt_adj, 1, 0));
   
   Gtk::Table *table168 = manage(new class Gtk::Table(6, 4, false));
   frame_werte_vorgaben = manage(new class Gtk::Frame());
   
   Gtk::Table *table166 = manage(new class Gtk::Table(6, 2, false));
   frame_vorgaben = manage(new class Gtk::Frame("Vorgaben"));
   togglebutton_vorgaben = manage(new class Gtk::ToggleButton("Vorgaben\n"
		"machen"));
   
   Gtk::Button *button_zufall_voll = manage(new class Gtk::Button("Zufallsabenteurer \n"
		"Grad 1 erzeugen"));
   Gtk::Table *table170 = manage(new class Gtk::Table(2, 2, false));
   Gtk::Frame *frame110 = manage(new class Gtk::Frame("Abenteurer erzeugen"));
   Gtk::Button *button_steigern = manage(new class Gtk::Button("Steigern"));
   combo_prototyp = manage(new class Gtk::Combo());
   togglebutton_prototyp = manage(new class Gtk::ToggleButton("Modifizieren"));
   
   Gtk::HBox *hbox91 = manage(new class Gtk::HBox(false, 0));
   Gtk::Frame *frame112 = manage(new class Gtk::Frame("Prototyp"));
   Gtk::RadioButton::Group _RadioBGroup_zufall_steigern;
   radiobutton_steigern_gfp = manage(new class Gtk::RadioButton(_RadioBGroup_zufall_steigern, "GFP", 0, 0.5));
   
   Gtk::Adjustment *spinbutton_grad_adj = manage(new class Gtk::Adjustment(1, 0, 15, 1, 10, 10));
   spinbutton_grad = manage(new class Gtk::SpinButton(*spinbutton_grad_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_gfp_adj = manage(new class Gtk::Adjustment(1, 0, 1e+07, 1, 10, 10));
   spinbutton_gfp = manage(new class Gtk::SpinButton(*spinbutton_gfp_adj, 1, 0));
   radiobutton_steigern_grad = manage(new class Gtk::RadioButton(_RadioBGroup_zufall_steigern, "Grad", 0, 0.5));
   
   Gtk::Table *table169 = manage(new class Gtk::Table(2, 2, false));
   Gtk::EventBox *eventbox22 = manage(new class Gtk::EventBox());
   Gtk::Frame *frame113 = manage(new class Gtk::Frame());
   Gtk::Adjustment *spinbutton_fertigkeit_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_fertigkeit = manage(new class Gtk::SpinButton(*spinbutton_fertigkeit_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_waffen_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_waffen = manage(new class Gtk::SpinButton(*spinbutton_waffen_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_waffen_grund_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_waffen_grund = manage(new class Gtk::SpinButton(*spinbutton_waffen_grund_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_zauber_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_zauber = manage(new class Gtk::SpinButton(*spinbutton_zauber_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_zauberwerk_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_zauberwerk = manage(new class Gtk::SpinButton(*spinbutton_zauberwerk_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_sprachen_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_sprachen = manage(new class Gtk::SpinButton(*spinbutton_sprachen_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_schriften_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_schriften = manage(new class Gtk::SpinButton(*spinbutton_schriften_adj, 1, 0));
   
   Gtk::Label *label612 = manage(new class Gtk::Label("Fertig-\n"
		"keiten"));
   Gtk::Label *label613 = manage(new class Gtk::Label("Waffen"));
   Gtk::Label *label614 = manage(new class Gtk::Label("Waffen-\n"
		"Grund."));
   Gtk::Label *label615 = manage(new class Gtk::Label("Zauber"));
   Gtk::Label *label616 = manage(new class Gtk::Label("Zauber-\n"
		"werk"));
   Gtk::Label *label617 = manage(new class Gtk::Label("Sprachen"));
   Gtk::Label *label618 = manage(new class Gtk::Label("Schriften"));
   Gtk::Label *label609 = manage(new class Gtk::Label("Spezialist (steigern)"));
   Gtk::Label *label610 = manage(new class Gtk::Label("Gebildeter (neu lernen)"));
   label_spez_fert = manage(new class Gtk::Label("50%"));
   label_allg_fert = manage(new class Gtk::Label("50%"));
   
   Gtk::Adjustment *vscale_spezallg_fert_adj = manage(new class Gtk::Adjustment(50, 0, 100, 1, 1, 0));
   vscale_spezallg_fert = manage(new class Gtk::VScale(*vscale_spezallg_fert_adj));
   label_spez_waff = manage(new class Gtk::Label("50%"));
   label_spez_spra = manage(new class Gtk::Label("50%"));
   label_spez_schr = manage(new class Gtk::Label("50%"));
   label_allg_waff = manage(new class Gtk::Label("50%"));
   label_allg_spra = manage(new class Gtk::Label("50%"));
   label_allg_schr = manage(new class Gtk::Label("50%"));
   
   Gtk::Adjustment *vscale_spezallg_waff_adj = manage(new class Gtk::Adjustment(50, 0, 100, 1, 1, 0));
   vscale_spezallg_waff = manage(new class Gtk::VScale(*vscale_spezallg_waff_adj));
   
   Gtk::Adjustment *vscale_spezallg_spra_adj = manage(new class Gtk::Adjustment(50, 0, 100, 1, 1, 0));
   vscale_spezallg_spra = manage(new class Gtk::VScale(*vscale_spezallg_spra_adj));
   
   Gtk::Adjustment *vscale_spezallg_schr_adj = manage(new class Gtk::Adjustment(50, 0, 100, 1, 1, 0));
   vscale_spezallg_schr = manage(new class Gtk::VScale(*vscale_spezallg_schr_adj));
   
   Gtk::Button *button_check100 = manage(new class Gtk::Button("Eingestellte Werte\n"
		"�bernehmen und testen"));
   Gtk::Table *table172 = manage(new class Gtk::Table(5, 8, false));
   Gtk::EventBox *eventbox21 = manage(new class Gtk::EventBox());
   frame_prototyp_mod = manage(new class Gtk::Frame());
   
   Gtk::Table *table165 = manage(new class Gtk::Table(3, 3, false));
   Gtk::Frame *frame111 = manage(new class Gtk::Frame("Abenteurer steigern"));
   checkbutton_spezies->set_flags(GTK_CAN_FOCUS);
   checkbutton_spezies->set_mode(true);
   checkbutton_spezies->set_active(false);
   checkbutton_herkunft->set_flags(GTK_CAN_FOCUS);
   checkbutton_herkunft->set_mode(true);
   checkbutton_herkunft->set_active(false);
   checkbutton_typ->set_flags(GTK_CAN_FOCUS);
   checkbutton_typ->set_mode(true);
   checkbutton_typ->set_active(false);
   checkbutton_ange_fert->set_flags(GTK_CAN_FOCUS);
   checkbutton_ange_fert->set_mode(true);
   checkbutton_ange_fert->set_active(false);
   combo_spezies->get_entry()->set_flags(GTK_CAN_FOCUS);
   combo_spezies->get_entry()->set_visibility(true);
   combo_spezies->get_entry()->set_editable(true);
   combo_spezies->get_entry()->set_text("");
   combo_spezies->set_sensitive(false);
   combo_spezies->set_case_sensitive(false);
   combo_spezies->set_use_arrows(true);
   combo_spezies->set_use_arrows_always(false);
   {  
      
      const char * const items[] = { "", 0 };
      combo_spezies->set_popdown_strings(items);
   }
   combo_spezies->get_entry()->set_text("");
   combo_typ->get_entry()->set_flags(GTK_CAN_FOCUS);
   combo_typ->get_entry()->set_visibility(true);
   combo_typ->get_entry()->set_editable(true);
   combo_typ->get_entry()->set_text("");
   combo_typ->set_sensitive(false);
   combo_typ->set_case_sensitive(false);
   combo_typ->set_use_arrows(true);
   combo_typ->set_use_arrows_always(false);
   {  
      
      const char * const items[] = { "", 0 };
      combo_typ->set_popdown_strings(items);
   }
   combo_typ->get_entry()->set_text("");
   combo_herkunft->get_entry()->set_flags(GTK_CAN_FOCUS);
   combo_herkunft->get_entry()->set_visibility(true);
   combo_herkunft->get_entry()->set_editable(true);
   combo_herkunft->get_entry()->set_text("");
   combo_herkunft->set_sensitive(false);
   combo_herkunft->set_case_sensitive(false);
   combo_herkunft->set_use_arrows(true);
   combo_herkunft->set_use_arrows_always(false);
   {  
      
      const char * const items[] = { "", 0 };
      combo_herkunft->set_popdown_strings(items);
   }
   combo_herkunft->get_entry()->set_text("");
   checkbutton_werte->set_flags(GTK_CAN_FOCUS);
   checkbutton_werte->set_mode(true);
   checkbutton_werte->set_active(false);
   checkbutton_st->set_flags(GTK_CAN_FOCUS);
   checkbutton_st->set_mode(true);
   checkbutton_st->set_active(false);
   checkbutton_gs->set_flags(GTK_CAN_FOCUS);
   checkbutton_gs->set_mode(true);
   checkbutton_gs->set_active(false);
   checkbutton_gw->set_flags(GTK_CAN_FOCUS);
   checkbutton_gw->set_mode(true);
   checkbutton_gw->set_active(false);
   checkbutton_ko->set_flags(GTK_CAN_FOCUS);
   checkbutton_ko->set_mode(true);
   checkbutton_ko->set_active(false);
   checkbutton_in->set_flags(GTK_CAN_FOCUS);
   checkbutton_in->set_mode(true);
   checkbutton_in->set_active(false);
   checkbutton_zt->set_flags(GTK_CAN_FOCUS);
   checkbutton_zt->set_mode(true);
   checkbutton_zt->set_active(false);
   checkbutton_au->set_flags(GTK_CAN_FOCUS);
   checkbutton_au->set_mode(true);
   checkbutton_au->set_active(false);
   checkbutton_pa->set_flags(GTK_CAN_FOCUS);
   checkbutton_pa->set_mode(true);
   checkbutton_pa->set_active(false);
   checkbutton_wk->set_flags(GTK_CAN_FOCUS);
   checkbutton_wk->set_mode(true);
   checkbutton_wk->set_active(false);
   checkbutton_sb->set_flags(GTK_CAN_FOCUS);
   checkbutton_sb->set_mode(true);
   checkbutton_sb->set_active(false);
   checkbutton_b->set_flags(GTK_CAN_FOCUS);
   checkbutton_b->set_mode(true);
   checkbutton_b->set_active(false);
   spinbutton_st->set_sensitive(false);
   spinbutton_st->set_flags(GTK_CAN_FOCUS);
   spinbutton_st->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_st->set_numeric(false);
   spinbutton_st->set_digits(0);
   spinbutton_st->set_wrap(false);
   spinbutton_st->set_snap_to_ticks(false);
   spinbutton_au->set_sensitive(false);
   spinbutton_au->set_flags(GTK_CAN_FOCUS);
   spinbutton_au->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_au->set_numeric(false);
   spinbutton_au->set_digits(0);
   spinbutton_au->set_wrap(false);
   spinbutton_au->set_snap_to_ticks(false);
   spinbutton_pa->set_sensitive(false);
   spinbutton_pa->set_flags(GTK_CAN_FOCUS);
   spinbutton_pa->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_pa->set_numeric(false);
   spinbutton_pa->set_digits(0);
   spinbutton_pa->set_wrap(false);
   spinbutton_pa->set_snap_to_ticks(false);
   spinbutton_wk->set_sensitive(false);
   spinbutton_wk->set_flags(GTK_CAN_FOCUS);
   spinbutton_wk->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_wk->set_numeric(false);
   spinbutton_wk->set_digits(0);
   spinbutton_wk->set_wrap(false);
   spinbutton_wk->set_snap_to_ticks(false);
   spinbutton_sb->set_sensitive(false);
   spinbutton_sb->set_flags(GTK_CAN_FOCUS);
   spinbutton_sb->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_sb->set_numeric(false);
   spinbutton_sb->set_digits(0);
   spinbutton_sb->set_wrap(false);
   spinbutton_sb->set_snap_to_ticks(false);
   spinbutton_b->set_sensitive(false);
   spinbutton_b->set_flags(GTK_CAN_FOCUS);
   spinbutton_b->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_b->set_numeric(false);
   spinbutton_b->set_digits(0);
   spinbutton_b->set_wrap(false);
   spinbutton_b->set_snap_to_ticks(false);
   spinbutton_gs->set_sensitive(false);
   spinbutton_gs->set_flags(GTK_CAN_FOCUS);
   spinbutton_gs->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_gs->set_numeric(false);
   spinbutton_gs->set_digits(0);
   spinbutton_gs->set_wrap(false);
   spinbutton_gs->set_snap_to_ticks(false);
   spinbutton_gw->set_sensitive(false);
   spinbutton_gw->set_flags(GTK_CAN_FOCUS);
   spinbutton_gw->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_gw->set_numeric(false);
   spinbutton_gw->set_digits(0);
   spinbutton_gw->set_wrap(false);
   spinbutton_gw->set_snap_to_ticks(false);
   spinbutton_ko->set_sensitive(false);
   spinbutton_ko->set_flags(GTK_CAN_FOCUS);
   spinbutton_ko->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_ko->set_numeric(false);
   spinbutton_ko->set_digits(0);
   spinbutton_ko->set_wrap(false);
   spinbutton_ko->set_snap_to_ticks(false);
   spinbutton_in->set_sensitive(false);
   spinbutton_in->set_flags(GTK_CAN_FOCUS);
   spinbutton_in->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_in->set_numeric(false);
   spinbutton_in->set_digits(0);
   spinbutton_in->set_wrap(false);
   spinbutton_in->set_snap_to_ticks(false);
   spinbutton_zt->set_sensitive(false);
   spinbutton_zt->set_flags(GTK_CAN_FOCUS);
   spinbutton_zt->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_zt->set_numeric(false);
   spinbutton_zt->set_digits(0);
   spinbutton_zt->set_wrap(false);
   spinbutton_zt->set_snap_to_ticks(false);
   table168->set_row_spacings(0);
   table168->set_col_spacings(0);
   table168->attach(*checkbutton_st, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_gs, 0, 1, 1, 2, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_gw, 0, 1, 2, 3, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_ko, 0, 1, 3, 4, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_in, 0, 1, 4, 5, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_zt, 0, 1, 5, 6, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_au, 2, 3, 0, 1, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_pa, 2, 3, 1, 2, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_wk, 2, 3, 2, 3, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_sb, 2, 3, 3, 4, GTK_FILL, 0, 0, 0);
   table168->attach(*checkbutton_b, 2, 3, 4, 5, GTK_FILL, 0, 0, 0);
   table168->attach(*spinbutton_st, 1, 2, 0, 1, 0, 0, 0, 0);
   table168->attach(*spinbutton_au, 3, 4, 0, 1, 0, 0, 0, 0);
   table168->attach(*spinbutton_pa, 3, 4, 1, 2, 0, 0, 0, 0);
   table168->attach(*spinbutton_wk, 3, 4, 2, 3, 0, 0, 0, 0);
   table168->attach(*spinbutton_sb, 3, 4, 3, 4, 0, 0, 0, 0);
   table168->attach(*spinbutton_b, 3, 4, 4, 5, 0, 0, 0, 0);
   table168->attach(*spinbutton_gs, 1, 2, 1, 2, 0, 0, 0, 0);
   table168->attach(*spinbutton_gw, 1, 2, 2, 3, 0, 0, 0, 0);
   table168->attach(*spinbutton_ko, 1, 2, 3, 4, 0, 0, 0, 0);
   table168->attach(*spinbutton_in, 1, 2, 4, 5, 0, 0, 0, 0);
   table168->attach(*spinbutton_zt, 1, 2, 5, 6, 0, 0, 0, 0);
   frame_werte_vorgaben->set_shadow_type(GTK_SHADOW_NONE);
   frame_werte_vorgaben->set_label_align(0,0);
   frame_werte_vorgaben->add(*table168);
   table166->set_row_spacings(0);
   table166->set_col_spacings(0);
   table166->attach(*checkbutton_spezies, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table166->attach(*checkbutton_herkunft, 0, 1, 2, 3, GTK_FILL, 0, 0, 0);
   table166->attach(*checkbutton_typ, 0, 1, 1, 2, GTK_FILL, 0, 0, 0);
   table166->attach(*checkbutton_ange_fert, 0, 1, 3, 4, GTK_FILL, 0, 0, 0);
   table166->attach(*combo_spezies, 1, 2, 0, 1, 0, 0, 0, 0);
   table166->attach(*combo_typ, 1, 2, 1, 2, 0, 0, 0, 0);
   table166->attach(*combo_herkunft, 1, 2, 2, 3, 0, 0, 0, 0);
   table166->attach(*checkbutton_werte, 0, 1, 4, 5, GTK_FILL, 0, 0, 0);
   table166->attach(*frame_werte_vorgaben, 0, 2, 5, 6, GTK_SHRINK|GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);
   frame_vorgaben->set_shadow_type(GTK_SHADOW_IN);
   frame_vorgaben->set_label_align(0,0);
   frame_vorgaben->add(*table166);
   togglebutton_vorgaben->set_flags(GTK_CAN_FOCUS);
   togglebutton_vorgaben->set_relief(GTK_RELIEF_NORMAL);
   togglebutton_vorgaben->set_active(false);
   button_zufall_voll->set_flags(GTK_CAN_FOCUS);
   button_zufall_voll->set_relief(GTK_RELIEF_NORMAL);
   table170->set_row_spacings(0);
   table170->set_col_spacings(0);
   table170->attach(*frame_vorgaben, 0, 2, 1, 2, GTK_EXPAND|GTK_SHRINK|GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);
   table170->attach(*togglebutton_vorgaben, 1, 2, 0, 1, GTK_EXPAND|GTK_SHRINK, GTK_SHRINK, 0, 0);
   table170->attach(*button_zufall_voll, 0, 1, 0, 1, GTK_EXPAND|GTK_SHRINK, GTK_SHRINK, 0, 0);
   frame110->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame110->set_label_align(0,0);
   frame110->add(*table170);
   button_steigern->set_flags(GTK_CAN_FOCUS);
   button_steigern->set_relief(GTK_RELIEF_NORMAL);
   combo_prototyp->get_entry()->set_flags(GTK_CAN_FOCUS);
   combo_prototyp->get_entry()->set_visibility(true);
   combo_prototyp->get_entry()->set_editable(true);
   combo_prototyp->get_entry()->set_text("");
   combo_prototyp->set_case_sensitive(false);
   combo_prototyp->set_use_arrows(true);
   combo_prototyp->set_use_arrows_always(false);
   {  
      
      const char * const items[] = { "", 0 };
      combo_prototyp->set_popdown_strings(items);
   }
   combo_prototyp->get_entry()->set_text("");
   togglebutton_prototyp->set_flags(GTK_CAN_FOCUS);
   togglebutton_prototyp->set_relief(GTK_RELIEF_NORMAL);
   togglebutton_prototyp->set_active(false);
   hbox91->pack_start(*combo_prototyp);
   hbox91->pack_start(*togglebutton_prototyp, false, false, 0);
   frame112->set_shadow_type(GTK_SHADOW_IN);
   frame112->set_label_align(0,0);
   frame112->add(*hbox91);
   radiobutton_steigern_gfp->set_flags(GTK_CAN_FOCUS);
   radiobutton_steigern_gfp->set_mode(true);
   radiobutton_steigern_gfp->set_active(false);
   spinbutton_grad->set_flags(GTK_CAN_FOCUS);
   spinbutton_grad->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_grad->set_numeric(false);
   spinbutton_grad->set_digits(0);
   spinbutton_grad->set_wrap(false);
   spinbutton_grad->set_snap_to_ticks(false);
   spinbutton_gfp->set_sensitive(false);
   spinbutton_gfp->set_flags(GTK_CAN_FOCUS);
   spinbutton_gfp->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_gfp->set_numeric(false);
   spinbutton_gfp->set_digits(0);
   spinbutton_gfp->set_wrap(false);
   spinbutton_gfp->set_snap_to_ticks(false);
   radiobutton_steigern_grad->set_flags(GTK_CAN_FOCUS);
   radiobutton_steigern_grad->set_mode(true);
   radiobutton_steigern_grad->set_active(true);
   table169->set_row_spacings(0);
   table169->set_col_spacings(0);
   table169->attach(*radiobutton_steigern_gfp, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table169->attach(*spinbutton_grad, 1, 2, 1, 2, 0, 0, 0, 0);
   table169->attach(*spinbutton_gfp, 1, 2, 0, 1, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table169->attach(*radiobutton_steigern_grad, 0, 1, 1, 2, GTK_FILL, 0, 0, 0);
   _tooltips.set_tip(*eventbox22, "'GFP': Vorgabe wieviel f�r GFP der Abenteurer lernen soll. 'Grad': Vorgabe in welchem Grad sich der Abenteurer nach dem Steigern befinden soll.", "");
   eventbox22->add(*table169);
   frame113->set_shadow_type(GTK_SHADOW_IN);
   frame113->set_label_align(0,0);
   frame113->add(*eventbox22);
   spinbutton_fertigkeit->set_flags(GTK_CAN_FOCUS);
   spinbutton_fertigkeit->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_fertigkeit->set_numeric(false);
   spinbutton_fertigkeit->set_digits(0);
   spinbutton_fertigkeit->set_wrap(false);
   spinbutton_fertigkeit->set_snap_to_ticks(false);
   spinbutton_waffen->set_flags(GTK_CAN_FOCUS);
   spinbutton_waffen->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_waffen->set_numeric(false);
   spinbutton_waffen->set_digits(0);
   spinbutton_waffen->set_wrap(false);
   spinbutton_waffen->set_snap_to_ticks(false);
   spinbutton_waffen_grund->set_flags(GTK_CAN_FOCUS);
   spinbutton_waffen_grund->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_waffen_grund->set_numeric(false);
   spinbutton_waffen_grund->set_digits(0);
   spinbutton_waffen_grund->set_wrap(false);
   spinbutton_waffen_grund->set_snap_to_ticks(false);
   spinbutton_zauber->set_flags(GTK_CAN_FOCUS);
   spinbutton_zauber->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_zauber->set_numeric(false);
   spinbutton_zauber->set_digits(0);
   spinbutton_zauber->set_wrap(false);
   spinbutton_zauber->set_snap_to_ticks(false);
   spinbutton_zauberwerk->set_flags(GTK_CAN_FOCUS);
   spinbutton_zauberwerk->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_zauberwerk->set_numeric(false);
   spinbutton_zauberwerk->set_digits(0);
   spinbutton_zauberwerk->set_wrap(false);
   spinbutton_zauberwerk->set_snap_to_ticks(false);
   spinbutton_sprachen->set_flags(GTK_CAN_FOCUS);
   spinbutton_sprachen->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_sprachen->set_numeric(false);
   spinbutton_sprachen->set_digits(0);
   spinbutton_sprachen->set_wrap(false);
   spinbutton_sprachen->set_snap_to_ticks(false);
   spinbutton_schriften->set_flags(GTK_CAN_FOCUS);
   spinbutton_schriften->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_schriften->set_numeric(false);
   spinbutton_schriften->set_digits(0);
   spinbutton_schriften->set_wrap(false);
   spinbutton_schriften->set_snap_to_ticks(false);
   label612->set_alignment(0,0.5);
   label612->set_padding(0,0);
   label612->set_justify(GTK_JUSTIFY_LEFT);
   label612->set_line_wrap(false);
   label613->set_alignment(0,0.5);
   label613->set_padding(0,0);
   label613->set_justify(GTK_JUSTIFY_CENTER);
   label613->set_line_wrap(false);
   label614->set_alignment(0,0.5);
   label614->set_padding(0,0);
   label614->set_justify(GTK_JUSTIFY_CENTER);
   label614->set_line_wrap(false);
   label615->set_alignment(0,0.5);
   label615->set_padding(0,0);
   label615->set_justify(GTK_JUSTIFY_CENTER);
   label615->set_line_wrap(false);
   label616->set_alignment(0,0);
   label616->set_padding(0,0);
   label616->set_justify(GTK_JUSTIFY_LEFT);
   label616->set_line_wrap(false);
   label617->set_alignment(0,0.5);
   label617->set_padding(0,0);
   label617->set_justify(GTK_JUSTIFY_CENTER);
   label617->set_line_wrap(false);
   label618->set_alignment(0,0.5);
   label618->set_padding(0,0);
   label618->set_justify(GTK_JUSTIFY_CENTER);
   label618->set_line_wrap(false);
   label609->set_alignment(1,0.5);
   label609->set_padding(0,0);
   label609->set_justify(GTK_JUSTIFY_CENTER);
   label609->set_line_wrap(false);
   label610->set_alignment(0.999999,0.5);
   label610->set_padding(0,0);
   label610->set_justify(GTK_JUSTIFY_CENTER);
   label610->set_line_wrap(false);
   label_spez_fert->set_alignment(0.5,0.5);
   label_spez_fert->set_padding(0,0);
   label_spez_fert->set_justify(GTK_JUSTIFY_CENTER);
   label_spez_fert->set_line_wrap(false);
   label_allg_fert->set_alignment(0.5,0.5);
   label_allg_fert->set_padding(0,0);
   label_allg_fert->set_justify(GTK_JUSTIFY_CENTER);
   label_allg_fert->set_line_wrap(false);
   vscale_spezallg_fert->set_flags(GTK_CAN_FOCUS);
   vscale_spezallg_fert->set_digits(0);
   vscale_spezallg_fert->set_draw_value(false);
   vscale_spezallg_fert->set_value_pos(GTK_POS_RIGHT);
   label_spez_waff->set_alignment(0.5,0.5);
   label_spez_waff->set_padding(0,0);
   label_spez_waff->set_justify(GTK_JUSTIFY_CENTER);
   label_spez_waff->set_line_wrap(false);
   label_spez_spra->set_alignment(0.5,0.5);
   label_spez_spra->set_padding(0,0);
   label_spez_spra->set_justify(GTK_JUSTIFY_CENTER);
   label_spez_spra->set_line_wrap(false);
   label_spez_schr->set_alignment(0.5,0.5);
   label_spez_schr->set_padding(0,0);
   label_spez_schr->set_justify(GTK_JUSTIFY_CENTER);
   label_spez_schr->set_line_wrap(false);
   label_allg_waff->set_alignment(0.5,0.5);
   label_allg_waff->set_padding(0,0);
   label_allg_waff->set_justify(GTK_JUSTIFY_CENTER);
   label_allg_waff->set_line_wrap(false);
   label_allg_spra->set_alignment(0.5,0.5);
   label_allg_spra->set_padding(0,0);
   label_allg_spra->set_justify(GTK_JUSTIFY_CENTER);
   label_allg_spra->set_line_wrap(false);
   label_allg_schr->set_alignment(0.5,0.5);
   label_allg_schr->set_padding(0,0);
   label_allg_schr->set_justify(GTK_JUSTIFY_CENTER);
   label_allg_schr->set_line_wrap(false);
   vscale_spezallg_waff->set_flags(GTK_CAN_FOCUS);
   vscale_spezallg_waff->set_digits(0);
   vscale_spezallg_waff->set_draw_value(false);
   vscale_spezallg_waff->set_value_pos(GTK_POS_RIGHT);
   vscale_spezallg_spra->set_flags(GTK_CAN_FOCUS);
   vscale_spezallg_spra->set_digits(0);
   vscale_spezallg_spra->set_draw_value(false);
   vscale_spezallg_spra->set_value_pos(GTK_POS_RIGHT);
   vscale_spezallg_schr->set_flags(GTK_CAN_FOCUS);
   vscale_spezallg_schr->set_digits(0);
   vscale_spezallg_schr->set_draw_value(false);
   vscale_spezallg_schr->set_value_pos(GTK_POS_RIGHT);
   button_check100->set_flags(GTK_CAN_FOCUS);
   button_check100->set_relief(GTK_RELIEF_NORMAL);
   table172->set_row_spacings(0);
   table172->set_col_spacings(0);
   table172->attach(*spinbutton_fertigkeit, 1, 2, 1, 2, GTK_SHRINK, GTK_SHRINK, 0, 0);
   table172->attach(*spinbutton_waffen, 2, 3, 1, 2, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table172->attach(*spinbutton_waffen_grund, 3, 4, 1, 2, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table172->attach(*spinbutton_zauber, 4, 5, 1, 2, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table172->attach(*spinbutton_zauberwerk, 5, 6, 1, 2, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table172->attach(*spinbutton_sprachen, 6, 7, 1, 2, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table172->attach(*spinbutton_schriften, 7, 8, 1, 2, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table172->attach(*label612, 1, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table172->attach(*label613, 2, 3, 0, 1, GTK_FILL, 0, 0, 0);
   table172->attach(*label614, 3, 4, 0, 1, GTK_FILL, 0, 0, 0);
   table172->attach(*label615, 4, 5, 0, 1, GTK_FILL, 0, 0, 0);
   table172->attach(*label616, 5, 6, 0, 1, GTK_FILL, 0, 0, 0);
   table172->attach(*label617, 6, 7, 0, 1, GTK_FILL, 0, 0, 0);
   table172->attach(*label618, 7, 8, 0, 1, GTK_FILL, 0, 0, 0);
   table172->attach(*label609, 0, 1, 2, 3, GTK_FILL, 0, 0, 0);
   table172->attach(*label610, 0, 1, 4, 5, GTK_FILL, 0, 0, 0);
   table172->attach(*label_spez_fert, 1, 2, 2, 3, GTK_FILL, 0, 0, 0);
   table172->attach(*label_allg_fert, 1, 2, 4, 5, GTK_FILL, 0, 0, 0);
   table172->attach(*vscale_spezallg_fert, 1, 2, 3, 4, 0, GTK_EXPAND|GTK_FILL, 0, 0);
   table172->attach(*label_spez_waff, 2, 3, 2, 3, GTK_FILL, 0, 0, 0);
   table172->attach(*label_spez_spra, 6, 7, 2, 3, GTK_FILL, 0, 0, 0);
   table172->attach(*label_spez_schr, 7, 8, 2, 3, GTK_FILL, 0, 0, 0);
   table172->attach(*label_allg_waff, 2, 3, 4, 5, GTK_FILL, 0, 0, 0);
   table172->attach(*label_allg_spra, 6, 7, 4, 5, GTK_FILL, 0, 0, 0);
   table172->attach(*label_allg_schr, 7, 8, 4, 5, GTK_FILL, 0, 0, 0);
   table172->attach(*vscale_spezallg_waff, 2, 3, 3, 4, GTK_FILL, GTK_FILL, 0, 0);
   table172->attach(*vscale_spezallg_spra, 6, 7, 3, 4, GTK_FILL, GTK_FILL, 0, 0);
   table172->attach(*vscale_spezallg_schr, 7, 8, 3, 4, GTK_FILL, GTK_FILL, 0, 0);
   table172->attach(*button_check100, 0, 1, 0, 2, GTK_SHRINK|GTK_FILL, GTK_SHRINK, 0, 0);
   _tooltips.set_tip(*eventbox21, "Verteilung der GFP auf unterschiedliche Bereiche. Ein 'Spezialist' steigert seine bereits gelernten Fertigkeiten, ein 'Gebildeter' lernt bevorzugt neue Fertigkeiten.", "");
   eventbox21->add(*table172);
   frame_prototyp_mod->set_shadow_type(GTK_SHADOW_IN);
   frame_prototyp_mod->set_label_align(0,0);
   frame_prototyp_mod->add(*eventbox21);
   table165->set_row_spacings(0);
   table165->set_col_spacings(0);
   table165->attach(*button_steigern, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table165->attach(*frame112, 1, 2, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);
   table165->attach(*frame113, 2, 3, 0, 2, GTK_SHRINK, GTK_SHRINK, 0, 0);
   table165->attach(*frame_prototyp_mod, 0, 3, 2, 3, GTK_SHRINK|GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);
   frame111->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame111->set_label_align(0,0);
   frame111->add(*table165);
   table_zufall->set_row_spacings(0);
   table_zufall->set_col_spacings(0);
   table_zufall->attach(*frame110, 0, 1, 0, 1, GTK_SHRINK, GTK_SHRINK|GTK_FILL, 0, 0);
   table_zufall->attach(*frame111, 1, 2, 0, 1, GTK_SHRINK, GTK_SHRINK|GTK_FILL, 0, 0);
   checkbutton_spezies->show();
   checkbutton_herkunft->show();
   checkbutton_typ->show();
   checkbutton_ange_fert->show();
   combo_spezies->show();
   combo_typ->show();
   combo_herkunft->show();
   checkbutton_werte->show();
   checkbutton_st->show();
   checkbutton_gs->show();
   checkbutton_gw->show();
   checkbutton_ko->show();
   checkbutton_in->show();
   checkbutton_zt->show();
   checkbutton_au->show();
   checkbutton_pa->show();
   checkbutton_wk->show();
   checkbutton_sb->show();
   checkbutton_b->show();
   spinbutton_st->show();
   spinbutton_au->show();
   spinbutton_pa->show();
   spinbutton_wk->show();
   spinbutton_sb->show();
   spinbutton_b->show();
   spinbutton_gs->show();
   spinbutton_gw->show();
   spinbutton_ko->show();
   spinbutton_in->show();
   spinbutton_zt->show();
   table168->show();
   table166->show();
   togglebutton_vorgaben->show();
   button_zufall_voll->show();
   table170->show();
   frame110->show();
   button_steigern->show();
   combo_prototyp->show();
   togglebutton_prototyp->show();
   hbox91->show();
   frame112->show();
   radiobutton_steigern_gfp->show();
   spinbutton_grad->show();
   spinbutton_gfp->show();
   radiobutton_steigern_grad->show();
   table169->show();
   eventbox22->show();
   frame113->show();
   spinbutton_fertigkeit->show();
   spinbutton_waffen->show();
   spinbutton_waffen_grund->show();
   spinbutton_zauber->show();
   spinbutton_zauberwerk->show();
   spinbutton_sprachen->show();
   spinbutton_schriften->show();
   label612->show();
   label613->show();
   label614->show();
   label615->show();
   label616->show();
   label617->show();
   label618->show();
   label609->show();
   label610->show();
   label_spez_fert->show();
   label_allg_fert->show();
   vscale_spezallg_fert->show();
   label_spez_waff->show();
   label_spez_spra->show();
   label_spez_schr->show();
   label_allg_waff->show();
   label_allg_spra->show();
   label_allg_schr->show();
   vscale_spezallg_waff->show();
   vscale_spezallg_spra->show();
   vscale_spezallg_schr->show();
   button_check100->show();
   table172->show();
   eventbox21->show();
   table165->show();
   frame111->show();
   table_zufall->show();
   checkbutton_spezies->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_spezies_toggled));
   checkbutton_herkunft->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_herkunft_toggled));
   checkbutton_typ->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_typ_toggled));
   combo_spezies->get_entry()->activate.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_spezies_activate));
   combo_spezies->get_entry()->focus_out_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_spezies_focus_out_event));
   combo_spezies->get_entry()->changed.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_spezies_changed));
   combo_typ->get_entry()->activate.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_typ_activate));
   combo_typ->get_entry()->focus_out_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_typ__focus_out_event));
   combo_typ->get_entry()->changed.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_typ__changed));
   combo_herkunft->get_entry()->activate.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_typ_activate));
   combo_herkunft->get_entry()->focus_out_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_typ__focus_out_event));
   combo_herkunft->get_entry()->changed.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_typ__changed));
   checkbutton_werte->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_werte_toggled));
   checkbutton_st->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_st_toggled));
   checkbutton_gs->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_gs_toggled));
   checkbutton_gw->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_gw_toggled));
   checkbutton_ko->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_ko_toggled));
   checkbutton_in->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_in_toggled));
   checkbutton_zt->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_zt_toggled));
   checkbutton_au->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_au_toggled));
   checkbutton_pa->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_pa_toggled));
   checkbutton_wk->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_wk_toggled));
   checkbutton_sb->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_sb_toggled));
   checkbutton_b->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_checkbutton_b_toggled));
   togglebutton_vorgaben->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_togglebutton_vorgaben_toggled));
   button_zufall_voll->clicked.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_button_zufall_voll_clicked));
   button_steigern->clicked.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_button_steigern_clicked));
   combo_prototyp->get_entry()->activate.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_prototyp_activate));
   combo_prototyp->get_entry()->focus_out_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_prototyp_focus_out_event));
   combo_prototyp->get_entry()->changed.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_combo_prototyp_changed));
   togglebutton_prototyp->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_togglebutton_prototyp_toggled));
   radiobutton_steigern_gfp->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_radiobutton_steigern_gfp_toggled));
   radiobutton_steigern_grad->toggled.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_radiobutton_steigern_grad_toggled));
   vscale_spezallg_fert->button_release_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_vscale_spezallg_fert_button_release_event));
   vscale_spezallg_waff->button_release_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_vscale_spezallg_waff_button_release_event));
   vscale_spezallg_spra->button_release_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_vscale_spezallg_spra_button_release_event));
   vscale_spezallg_schr->button_release_event.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_vscale_spezallg_schr_button_release_event));
   button_check100->clicked.connect(SigC::slot(static_cast<class table_zufall*>(this), &table_zufall::on_button_check100_clicked));
}

table_zufall_glade::~table_zufall_glade()
{  
}
