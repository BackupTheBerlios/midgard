// generated 2002/9/6 20:25:52 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/table_steigern.hh and./src/table_steigern.cc

#ifndef _TABLE_STEIGERN_GLADE_HH
#  define _TABLE_STEIGERN_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtk--/accelgroup.h>

class GlademmData
{  
        
        Gtk::AccelGroup *accgrp;
public:
        
        GlademmData(Gtk::AccelGroup *ag) : accgrp(ag)
        {  
        }
        
        Gtk::AccelGroup * getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtk--/table.h>
#include <gtk--/tooltips.h>
#include <gtk--/label.h>
#include <gtk--/frame.h>
#include <gtk--/checkbutton.h>
#include <gtk--/spinbutton.h>
#include <gtk--/scale.h>
#include <gtk--/button.h>
#include <gtk--/radiobutton.h>
#include <gtk--/togglebutton.h>
#include <gtk--/box.h>
#include <gtk--/handlebox.h>
#include "MidgardBasicTree.hh"
#include <gtk--/scrolledwindow.h>
#include <gtk--/pixmap.h>
#include <gtk--/clist.h>
#include <gtk--/entry.h>
#include "SimpleTree.hh"
#include <gtk--/notebook.h>

class table_steigern_glade : public Gtk::Table
{  
protected:
        
        Gtk::Tooltips _tooltips;
        class Gtk::Table *table_steigern;
        class Gtk::Label *label_s_grad;
        class Gtk::Label *label_s_resistenz;
        class Gtk::Label *label_s_zaubern;
        class Gtk::Label *label_s_abwehr;
        class Gtk::Label *label_alter;
        class Gtk::Label *label_s_ap;
        class Gtk::Label *label_steigertage;
        class Gtk::Label *steigern_typ;
        class Gtk::Label *label_steigern_spezies;
        class Gtk::Label *label_pp_abwehr;
        class Gtk::Label *label_pp_zaubern;
        class Gtk::Frame *frame_pp_zaubern;
        class Gtk::Label *label_pp_resistenz;
        class Gtk::Label *label_pp_spezial;
        class Gtk::Frame *frame_pp_spezial;
        class Gtk::CheckButton *button_gold_eingeben;
        class Gtk::SpinButton *spinbutton_aep;
        class Gtk::Label *label_aep;
        class Gtk::SpinButton *spinbutton_kep;
        class Gtk::Label *label_kep;
        class Gtk::SpinButton *spinbutton_zep;
        class Gtk::Label *label_zep;
        class Gtk::SpinButton *spinbutton_gold;
        class Gtk::Label *label_gold;
        class Gtk::SpinButton *spinbutton_silber;
        class Gtk::Label *label_silber;
        class Gtk::SpinButton *spinbutton_kupfer;
        class Gtk::Label *label_kupfer;
        class Gtk::SpinButton *spinbutton_gfp;
        class Gtk::Label *gfp;
        class Gtk::CheckButton *checkbutton_EP_Geld;
        class Gtk::CheckButton *checkbutton_gfp;
        class Gtk::CheckButton *button_EP;
        class Gtk::Label *label_EP;
        class Gtk::Label *label_Gold;
        class Gtk::VScale *vscale_EP_Gold;
        class Gtk::Label *label_grad_GFP;
        class Gtk::Label *label_ausdauer_GFP;
        class Gtk::Label *label_abwehr_GFP;
        class Gtk::Label *label_zauber_GFP;
        class Gtk::Button *button_grad_zaubern;
        class Gtk::SpinButton *spinbutton_eigenschaften_grad_anstieg;
        class Gtk::Label *label_resistenz_GFP;
        class Gtk::Table *table_gradsteigern_lang;
        class Gtk::RadioButton *radiobutton_pp_hoch_wie_geht;
        class Gtk::RadioButton *radiobutton_pp_1stufe;
        class Gtk::ToggleButton *togglebutton_pp_verfallen;
        class Gtk::ToggleButton *togglebutton_pp_aep_fuellen;
        class Gtk::Table *table_pp_einstellungen;
        class Gtk::RadioButton *radiobutton_praxis;
        class Gtk::RadioButton *radiobutton_unterweisung;
        class Gtk::RadioButton *radiobutton_selbst;
        class Gtk::Frame *frame_lernen_mit;
        class Gtk::RadioButton *radio_spruchrolle_wuerfeln;
        class Gtk::RadioButton *radio_spruchrolle_auto;
        class Gtk::ToggleButton *togglebutton_spruchrolle;
        class Gtk::ToggleButton *togglebutton_alle_zauber;
        class Gtk::ToggleButton *togglebutton_zaubersalze;
        class Gtk::Frame *frame_zauber_zusatz;
        class Gtk::RadioButton *radiobutton_reduzieren;
        class Gtk::RadioButton *radiobutton_verlernen;
        class Gtk::RadioButton *radiobutton_steigern;
        class Gtk::Frame *frame_fertigkeit;
        class Gtk::SpinButton *spinbutton_pp_eingeben;
        class Gtk::ToggleButton *togglebutton_praxispunkte;
        class Gtk::RadioButton *radiobutton_pp_fertigkeit;
        class Gtk::RadioButton *radiobutton_pp_abwehr;
        class Gtk::RadioButton *radiobutton_pp_zauber;
        class Gtk::RadioButton *radiobutton_pp_spezial;
        class Gtk::RadioButton *radiobutton_pp_resistenz;
        class Gtk::VBox *vbox_praxispunkte;
        class Gtk::Frame *frame_praxispunkte;
        class Gtk::HandleBox *handlebox_steigern;
        class Gtk::Table *table_handlebox1;
        class MidgardBasicTree *tree_steigern_zusatz;
        class Gtk::ScrolledWindow *scrolledwindow_landauswahl;
        class MidgardBasicTree *alte_fert_tree;
        class MidgardBasicTree *neue_fert_tree;
        class Gtk::Label *label_ns_fertigkeiten;
        class Gtk::Pixmap *pixmap_ns_fertig;
        class MidgardBasicTree *alte_waffen_tree;
        class MidgardBasicTree *neue_waffen_tree;
        class MidgardBasicTree *alte_grund_tree;
        class MidgardBasicTree *neue_grund_tree;
        class Gtk::Label *label_nw_waffen;
        class Gtk::Pixmap *pixmap_ns_waffen;
        class MidgardBasicTree *alte_zauber_tree;
        class MidgardBasicTree *neue_zauber_tree;
        class MidgardBasicTree *alte_zaubermittel_tree;
        class MidgardBasicTree *neue_zaubermittel_tree;
        class Gtk::Table *table_magier_steigern;
        class Gtk::Label *label_ns_zauber;
        class Gtk::Pixmap *pixmap_ns_zauber;
        class MidgardBasicTree *alte_kido_tree;
        class MidgardBasicTree *neue_kido_tree;
        class Gtk::Pixmap *pixmap_kurai;
        class Gtk::Table *table_kido_steigern;
        class Gtk::Label *label_ns_kido;
        class Gtk::Pixmap *pixmap_ns_kido;
        class MidgardBasicTree *alte_sprache_tree;
        class Gtk::ToggleButton *togglebutton_neue_sprache_pp;
        class MidgardBasicTree *neue_sprache_tree;
        class MidgardBasicTree *alte_schrift_tree;
        class MidgardBasicTree *neue_schrift_tree;
        class Gtk::Label *label_ns_sprache;
        class Gtk::Pixmap *pixmap_ns_sprache;
        class Gtk::Label *label_ruestung_1;
        class Gtk::CheckButton *button_ruestung_1;
        class Gtk::Label *label_ruestung_2;
        class Gtk::CheckButton *button_ruestung_2;
        class Gtk::CList *clist_ruestung;
        class Gtk::Label *label_av_bonus;
        class Gtk::Label *label_sl_bonus;
        class Gtk::SpinButton *spinbutton_av_bonus;
        class Gtk::SpinButton *spinbutton_sl_bonus;
        class Gtk::Entry *entry_magisch;
        class Gtk::Table *table_magbonus;
        class Gtk::CheckButton *checkbutton_mag_waffenbonus;
        class SimpleTree *waffenbesitz_alt_tree;
        class SimpleTree *waffenbesitz_neu_tree;
        class Gtk::Label *label_ns_besitz;
        class Gtk::Pixmap *pixmap_ns_besitz;
        class Gtk::Notebook *notebook_lernen;
        
        table_steigern_glade(GlademmData *_data);
        
        ~table_steigern_glade();
};
#endif
