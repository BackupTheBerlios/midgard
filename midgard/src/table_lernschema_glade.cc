// generated 2002/6/18 8:33:10 CEST by thoma@Tiger.(none)
// using glademm V1.1.0b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.9
//
// Please modify the corresponding derived classes in ./src/table_lernschema.cc

#include "config.h"
#include "table_lernschema.hh"
#include <gtk--/pixmap.h>
#include "../pixmaps/right_arr-exp3.xpm"
#include <gtk--/button.h>
#include "../pixmaps/left_arr-exp3.xpm"
#include <gtk--/adjustment.h>
#include "../pixmaps/Fert_Reiten-32.xpm"
#include "../pixmaps/Skills-trans-50.xpm"
#include "../pixmaps/Fert_Laufen-32.xpm"
#include <gtk--/box.h>
#include <gtk--/frame.h>
#include "../pixmaps/Fert_Lesen-32.xpm"
#include "../pixmaps/Angeb_Tast-32.xpm"
#include <gtk--/entry.h>
#include "../pixmaps/KiDo-trans-50.xpm"
#include <gtk--/label.h>
#include "../pixmaps/Weapon-trans-50.xpm"
#include "../pixmaps/Claymore-50.xpm"
#include "../pixmaps/Zauber-trans-50.xpm"
#include "../pixmaps/Regio_Arkanum-50.xpm"
#include <gtk--/table.h>
#include <gtk--/viewport.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/paned.h>
#include "../pixmaps/Angeb_Sicht-32.xpm"
#include "../pixmaps/Angeb_Ohr-32.xpm"
#include "../pixmaps/Angeb_Richtung-32.xpm"
#include "../pixmaps/Angeb_Reflex-32.xpm"
#include "../pixmaps/Angeb_Nase-32.xpm"
#include "../pixmaps/CountrChar-trans-50.xpm"
#include "../pixmaps/Dice-2W6-trans-50.xpm"
#include "../pixmaps/Edit-trans-50.xpm"
#include "../pixmaps/Job-trans-50.xpm"
#include "../pixmaps/Money-50.xpm"
#include "../pixmaps/Dice_Armor-trans-50.xpm"
#include <gtk--/toolbar.h>
#include "../pixmaps/Gross_dfr3_pre.xpm"

table_lernschema_glade::table_lernschema_glade(GlademmData *_data
) : Gtk::Table(4, 2, false)
{  table_lernschema = this;
   
   Gtk::Pixmap *pixmap70 = manage(new class Gtk::Pixmap(right_arr_exp3_xpm));
   Gtk::Button *button_waffe_trans = manage(new class Gtk::Button());
   Gtk::Pixmap *pixmap71 = manage(new class Gtk::Pixmap(left_arr_exp3_xpm));
   Gtk::Button *button_fach_trans = manage(new class Gtk::Button());
   Gtk::Adjustment *spinbutton_fach_adj = manage(new class Gtk::Adjustment(1, 0, 95, 1, 10, 10));
   spinbutton_fach = manage(new class Gtk::SpinButton(*spinbutton_fach_adj, 1, 0));
   
   Gtk::Pixmap *pixmap120 = manage(new class Gtk::Pixmap(Fert_Reiten_32_xpm));
   Gtk::Pixmap *pixmap118 = manage(new class Gtk::Pixmap(Skills_trans_50_xpm));
   Gtk::Pixmap *pixmap119 = manage(new class Gtk::Pixmap(Fert_Laufen_32_xpm));
   Gtk::HBox *hbox60 = manage(new class Gtk::HBox(false, 0));
   Gtk::RadioButton::Group _RadioBGroup_LernListe;
   button_fachkenntnisse = manage(new class Gtk::RadioButton(_RadioBGroup_LernListe));
   
   Gtk::VBox *vbox33 = manage(new class Gtk::VBox(false, 0));
   Gtk::Frame *frame25 = manage(new class Gtk::Frame("Fachkenntnisse"));
   Gtk::Adjustment *spinbutton_allgemein_adj = manage(new class Gtk::Adjustment(1, 0, 95, 1, 10, 10));
   spinbutton_allgemein = manage(new class Gtk::SpinButton(*spinbutton_allgemein_adj, 1, 0));
   
   Gtk::Pixmap *pixmap116 = manage(new class Gtk::Pixmap(Skills_trans_50_xpm));
   Gtk::Pixmap *pixmap149 = manage(new class Gtk::Pixmap(Fert_Lesen_32_xpm));
   Gtk::HBox *hbox59 = manage(new class Gtk::HBox(false, 0));
   button_allgemeinwissen = manage(new class Gtk::RadioButton(_RadioBGroup_LernListe));
   
   Gtk::VBox *vbox34 = manage(new class Gtk::VBox(false, 0));
   Gtk::Frame *frame26 = manage(new class Gtk::Frame("Allgemeinwissen"));
   Gtk::Adjustment *spinbutton_unge_adj = manage(new class Gtk::Adjustment(1, 0, 95, 1, 10, 10));
   spinbutton_unge = manage(new class Gtk::SpinButton(*spinbutton_unge_adj, 1, 0));
   
   Gtk::Pixmap *pixmap121 = manage(new class Gtk::Pixmap(Angeb_Tast_32_xpm));
   Gtk::Pixmap *pixmap114 = manage(new class Gtk::Pixmap(Fert_Laufen_32_xpm));
   Gtk::HBox *hbox50 = manage(new class Gtk::HBox(false, 0));
   button_untyp_fertigkeiten = manage(new class Gtk::RadioButton(_RadioBGroup_LernListe));
   
   Gtk::VBox *vbox35 = manage(new class Gtk::VBox(false, 0));
   Gtk::Frame *frame80 = manage(new class Gtk::Frame("Ungew�hnl. Fertigk."));
   combo_kido_stil = manage(new class Gtk::Combo());
   
   Gtk::Pixmap *pixmap102 = manage(new class Gtk::Pixmap(KiDo_trans_50_xpm));
   Gtk::Label *label540 = manage(new class Gtk::Label("KiDo Techniken\n"
		"ausw�hlen"));
   Gtk::HBox *hbox54 = manage(new class Gtk::HBox(false, 0));
   button_kido_auswahl = manage(new class Gtk::RadioButton(_RadioBGroup_LernListe));
   
   Gtk::VBox *vbox45 = manage(new class Gtk::VBox(false, 0));
   frame_KiDo_lernschema = manage(new class Gtk::Frame("KiDo"));
   
   Gtk::Adjustment *spinbutton_waffen_adj = manage(new class Gtk::Adjustment(1, 0, 95, 1, 10, 10));
   spinbutton_waffen = manage(new class Gtk::SpinButton(*spinbutton_waffen_adj, 1, 0));
   
   Gtk::Pixmap *pixmap100 = manage(new class Gtk::Pixmap(Weapon_trans_50_xpm));
   Gtk::Pixmap *pixmap107 = manage(new class Gtk::Pixmap(Claymore_50_xpm));
   Gtk::HBox *hbox52 = manage(new class Gtk::HBox(false, 0));
   button_waffen = manage(new class Gtk::RadioButton(_RadioBGroup_LernListe));
   
   Gtk::VBox *vbox36 = manage(new class Gtk::VBox(false, 0));
   Gtk::Frame *frame27 = manage(new class Gtk::Frame("Waffen"));
   Gtk::Adjustment *spinbutton_zauber_adj = manage(new class Gtk::Adjustment(1, 0, 95, 1, 10, 10));
   spinbutton_zauber = manage(new class Gtk::SpinButton(*spinbutton_zauber_adj, 1, 0));
   
   Gtk::Pixmap *pixmap101 = manage(new class Gtk::Pixmap(Zauber_trans_50_xpm));
   Gtk::Pixmap *pixmap123 = manage(new class Gtk::Pixmap(Regio_Arkanum_50_xpm));
   Gtk::HBox *hbox53 = manage(new class Gtk::HBox(false, 0));
   button_zauber = manage(new class Gtk::RadioButton(_RadioBGroup_LernListe));
   
   Gtk::VBox *vbox37 = manage(new class Gtk::VBox(false, 0));
   Gtk::Frame *frame28 = manage(new class Gtk::Frame("Zauber"));
   combo_magier_spezialgebiet = manage(new class Gtk::Combo());
   
   Gtk::Table *table96 = manage(new class Gtk::Table(2, 7, false));
   frame_lernpunkte = manage(new class Gtk::Frame("Lernpunkte f�r"));
   
   Gtk::Table *table117 = manage(new class Gtk::Table(1, 1, false));
   Gtk::Label *label544 = manage(new class Gtk::Label("Gelernt"));
   tree_gelerntes = new class MidgardBasicTree(MidgardBasicTree::GELERNTES);
   
   Gtk::Viewport *viewport35 = manage(new class Gtk::Viewport());
   Gtk::ScrolledWindow *scrolledwindow73 = manage(new class Gtk::ScrolledWindow());
   Gtk::Table *table122 = manage(new class Gtk::Table(2, 1, false));
   viewport_lernen = manage(new class Gtk::Viewport());
   scrolledwindow_lernen = manage(new class Gtk::ScrolledWindow());
   Tree_Lernschema_Zusatz = new class MidgardBasicTree(MidgardBasicTree::LERNSCHEMAZUSATZ);
   
   Gtk::Viewport *viewport39 = manage(new class Gtk::Viewport());
   Gtk::ScrolledWindow *scrolledwindow77 = manage(new class Gtk::ScrolledWindow());
   frame_lernschema_zusatz = manage(new class Gtk::Frame("Titel"));
   label_lernschma_titel = manage(new class Gtk::Label("label547"));
   
   Gtk::Table *table123 = manage(new class Gtk::Table(2, 2, false));
   Gtk::HPaned *hpaned6 = manage(new class Gtk::HPaned());
   Gtk::Pixmap *pixmap99 = manage(new class Gtk::Pixmap(Angeb_Sicht_32_xpm));
   Gtk::Pixmap *pixmap105 = manage(new class Gtk::Pixmap(Angeb_Tast_32_xpm));
   Gtk::Pixmap *pixmap96 = manage(new class Gtk::Pixmap(Angeb_Ohr_32_xpm));
   Gtk::Pixmap *pixmap98 = manage(new class Gtk::Pixmap(Angeb_Richtung_32_xpm));
   Gtk::Pixmap *pixmap97 = manage(new class Gtk::Pixmap(Angeb_Reflex_32_xpm));
   Gtk::Pixmap *pixmap95 = manage(new class Gtk::Pixmap(Angeb_Nase_32_xpm));
   Gtk::HBox *table119 = manage(new class Gtk::HBox(false, 0));
   Gtk::Label *label537 = manage(new class Gtk::Label("angeborene Fertigkeiten"));
   Gtk::VBox *vbox62 = manage(new class Gtk::VBox(false, 0));
   button_angeborene_fert = manage(new class Gtk::Button());
   
   Gtk::Label *label557 = manage(new class Gtk::Label("%Wurf f�r\n"
		"Beruf eingeben"));
   Gtk::Label *label558 = manage(new class Gtk::Label("%"));
   Gtk::Adjustment *spinbutton_beruf_adj = manage(new class Gtk::Adjustment(1, 1, 100, 1, 10, 10));
   spinbutton_beruf = manage(new class Gtk::SpinButton(*spinbutton_beruf_adj, 1, 0));
   table_berufsprozent = manage(new class Gtk::Table(2, 2, false));
   
   Gtk::Label *label542 = manage(new class Gtk::Label("Berufsnamen eingeben"));
   entry_berufsname = manage(new class Gtk::Entry());
   vbox_berufsname = manage(new class Gtk::VBox(false, 0));
   
   Gtk::VBox *vbox49 = manage(new class Gtk::VBox(false, 0));
   label_gwr = manage(new class Gtk::Label("%Wurf\n"
		"eingeben"));
   
   Gtk::Adjustment *spinbutton_waffen_lernschema_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_waffen_lernschema = manage(new class Gtk::SpinButton(*spinbutton_waffen_lernschema_adj, 1, 0));
   table_waffen_lernschema_eingabe = manage(new class Gtk::Table(2, 1, false));
   
   Gtk::Toolbar *toolbar3 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH));
   button_herkunft = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar3->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Herkunft", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(CountrChar_trans_50_xpm))->gtkobj()), 0, 0));
   toolbar3->tools().push_back(Gtk::Toolbar_Helpers::WidgetElem(*button_angeborene_fert));
   toolbar3->tools().push_back(Gtk::Toolbar_Helpers::Space());
   button_lernpunkte = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar3->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Lernpunkte", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Dice_2W6_trans_50_xpm))->gtkobj()), 0, 0));
   togglebutton_lernpunkte_edit = Gtk::wrap((GtkToggleButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar3->gtkobj()), GTK_TOOLBAR_CHILD_TOGGLEBUTTON, 0, "Lernpunkte", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Edit_trans_50_xpm))->gtkobj()), 0, 0));
   toolbar3->tools().push_back(Gtk::Toolbar_Helpers::Space());
   button_beruf = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar3->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Beruf", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Job_trans_50_xpm))->gtkobj()), 0, 0));
   toolbar3->tools().push_back(Gtk::Toolbar_Helpers::WidgetElem(*vbox49));
   toolbar3->tools().push_back(Gtk::Toolbar_Helpers::Space());
   button_lernschema_geld = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar3->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Geld", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Money_50_xpm))->gtkobj()), 0, 0));
   button_lernschema_waffen = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar3->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Waffen", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Weapon_trans_50_xpm))->gtkobj()), 0, 0));
   toolbar3->tools().push_back(Gtk::Toolbar_Helpers::WidgetElem(*table_waffen_lernschema_eingabe));
   button_ruestung = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar3->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "R�stung", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Dice_Armor_trans_50_xpm))->gtkobj()), 0, 0));
   handlebox_lernschema = manage(new class Gtk::HandleBox());
   fertig_typ = manage(new class Gtk::Label("label280"));
   
   Gtk::Frame *frame59 = manage(new class Gtk::Frame("Abenteurertyp"));
   label_ruestung_lernschema = manage(new class Gtk::Label("label553"));
   
   Gtk::Frame *frame101 = manage(new class Gtk::Frame("R�stungsklasse"));
   Gtk::Pixmap *pixmap122 = manage(new class Gtk::Pixmap(Weapon_trans_50_xpm));
   Gtk::Label *label545 = manage(new class Gtk::Label("Spezialwaffe\n"
		"ausw�hlen"));
   Gtk::HBox *hbox61 = manage(new class Gtk::HBox(false, 0));
   togglebutton_spezialwaffe = manage(new class Gtk::ToggleButton());
   label_herkunft_lernschema = manage(new class Gtk::Label("label553"));
   
   Gtk::Frame *frame102 = manage(new class Gtk::Frame("Herkunft"));
   Gtk::Table *table131 = manage(new class Gtk::Table(1, 4, false));
   Gtk::Label *label565 = manage(new class Gtk::Label("zu teure Fertigkeiten zeigen"));
   togglebutton_teure_anzeigen = manage(new class Gtk::CheckButton());
   
   Gtk::Label *label562 = manage(new class Gtk::Label("Gelernte Fertigkeiten zeigen"));
   togglebutton_gelernte_anzeigen = manage(new class Gtk::CheckButton());
   
   Gtk::Pixmap *pixmap145 = manage(new class Gtk::Pixmap(Angeb_Sicht_32_xpm));
   Gtk::Table *table132 = manage(new class Gtk::Table(2, 2, false));
   Gtk::Frame *frame103 = manage(new class Gtk::Frame("Optionen"));
   eventbox_zusatz = manage(new class Gtk::EventBox());
   table_lernschema_121 = manage(new class Gtk::Table(1, 4, false));
   pixmap_dfr3 = manage(new class Gtk::Pixmap(Gross_dfr3_pre_xpm));
   
   Gtk::Viewport *viewport36 = manage(new class Gtk::Viewport());
   scrolledwindow_dfr3 = manage(new class Gtk::ScrolledWindow());
   pixmap70->set_alignment(0.5, 0.5);
   pixmap70->set_padding(0, 0);
   button_waffe_trans->set_flags(GTK_CAN_FOCUS);
   button_waffe_trans->set_relief(GTK_RELIEF_NONE);
   button_waffe_trans->add(*pixmap70);
   pixmap71->set_alignment(0.5, 0.5);
   pixmap71->set_padding(0, 0);
   button_fach_trans->set_flags(GTK_CAN_FOCUS);
   button_fach_trans->set_relief(GTK_RELIEF_NONE);
   button_fach_trans->add(*pixmap71);
   spinbutton_fach->set_editable(true);
   pixmap120->set_alignment(0.5, 0.5);
   pixmap120->set_padding(0, 0);
   pixmap118->set_alignment(0.5, 0.5);
   pixmap118->set_padding(0, 0);
   pixmap119->set_alignment(0.5, 0.5);
   pixmap119->set_padding(0, 0);
   hbox60->pack_start(*pixmap120);
   hbox60->pack_start(*pixmap118);
   hbox60->pack_start(*pixmap119);
   button_fachkenntnisse->set_mode(false);
   button_fachkenntnisse->set_active(true);
   button_fachkenntnisse->add(*hbox60);
   vbox33->pack_start(*spinbutton_fach, false, false, 0);
   vbox33->pack_start(*button_fachkenntnisse, true, false, 0);
   frame25->set_label_align(0, 0);
   frame25->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame25->add(*vbox33);
   spinbutton_allgemein->set_editable(true);
   pixmap116->set_alignment(0.5, 0.5);
   pixmap116->set_padding(0, 0);
   pixmap149->set_alignment(0.5, 0.5);
   pixmap149->set_padding(0, 0);
   hbox59->pack_start(*pixmap116);
   hbox59->pack_start(*pixmap149);
   button_allgemeinwissen->set_mode(false);
   button_allgemeinwissen->add(*hbox59);
   vbox34->pack_start(*spinbutton_allgemein, false, false, 0);
   vbox34->pack_start(*button_allgemeinwissen, true, false, 0);
   frame26->set_label_align(0, 0);
   frame26->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame26->add(*vbox34);
   spinbutton_unge->set_editable(true);
   pixmap121->set_alignment(0.5, 0.5);
   pixmap121->set_padding(0, 0);
   pixmap114->set_alignment(0.5, 0.5);
   pixmap114->set_padding(0, 0);
   hbox50->pack_start(*pixmap121);
   hbox50->pack_start(*pixmap114);
   button_untyp_fertigkeiten->set_mode(false);
   button_untyp_fertigkeiten->add(*hbox50);
   vbox35->pack_start(*spinbutton_unge, false, false, 0);
   vbox35->pack_end(*button_untyp_fertigkeiten, true, false, 0);
   frame80->set_label_align(0, 0);
   frame80->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame80->add(*vbox35);
   combo_kido_stil->get_entry()->set_editable(true);
   {  
      
      const char * const items[] = { "", 0 };
      combo_kido_stil->set_popdown_strings(items);
   }
   combo_kido_stil->get_entry()->set_editable(true);
   pixmap102->set_alignment(0.5, 0.5);
   pixmap102->set_padding(0, 0);
   label540->set_alignment(0.5, 0.5);
   label540->set_padding(0, 0);
   hbox54->pack_start(*pixmap102, false, true, 0);
   hbox54->pack_start(*label540, false, false, 0);
   button_kido_auswahl->set_mode(false);
   button_kido_auswahl->add(*hbox54);
   vbox45->pack_start(*combo_kido_stil, false, false, 0);
   vbox45->pack_start(*button_kido_auswahl, false, false, 0);
   frame_KiDo_lernschema->set_label_align(0, 0);
   frame_KiDo_lernschema->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame_KiDo_lernschema->add(*vbox45);
   spinbutton_waffen->set_editable(true);
   pixmap100->set_alignment(0.5, 0.5);
   pixmap100->set_padding(0, 0);
   pixmap107->set_alignment(0.5, 0.5);
   pixmap107->set_padding(0, 0);
   hbox52->pack_start(*pixmap100);
   hbox52->pack_start(*pixmap107);
   button_waffen->set_mode(false);
   button_waffen->add(*hbox52);
   vbox36->pack_start(*spinbutton_waffen, false, false, 0);
   vbox36->pack_start(*button_waffen, true, false, 0);
   frame27->set_label_align(0, 0);
   frame27->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame27->add(*vbox36);
   spinbutton_zauber->set_editable(true);
   pixmap101->set_alignment(0.5, 0.5);
   pixmap101->set_padding(0, 0);
   pixmap123->set_alignment(0.5, 0.5);
   pixmap123->set_padding(0, 0);
   hbox53->pack_start(*pixmap101);
   hbox53->pack_start(*pixmap123);
   button_zauber->set_mode(false);
   button_zauber->add(*hbox53);
   vbox37->pack_start(*spinbutton_zauber, false, false, 0);
   vbox37->pack_start(*button_zauber, true, false, 0);
   frame28->set_label_align(0, 0);
   frame28->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame28->add(*vbox37);
   combo_magier_spezialgebiet->get_entry()->set_editable(true);
   {  
      
      const char * const items[] = { "", 0 };
      combo_magier_spezialgebiet->set_popdown_strings(items);
   }
   combo_magier_spezialgebiet->get_entry()->set_editable(true);
   table96->attach(*button_waffe_trans, 3, 5, 1, 2, GTK_FILL, 0, 0, 0);
   table96->attach(*button_fach_trans, 0, 3, 1, 2, GTK_FILL, 0, 0, 0);
   table96->attach(*frame25, 0, 1, 0, 1, GTK_FILL, GTK_EXPAND, 0, 0);
   table96->attach(*frame26, 1, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table96->attach(*frame80, 2, 4, 0, 1, 0, 0, 0, 0);
   table96->attach(*frame_KiDo_lernschema, 6, 7, 0, 1, 0, 0, 0, 0);
   table96->attach(*frame27, 4, 5, 0, 1, 0, 0, 0, 0);
   table96->attach(*frame28, 5, 6, 0, 1, 0, 0, 0, 0);
   table96->attach(*combo_magier_spezialgebiet, 5, 6, 1, 2, 0, 0, 0, 0);
   frame_lernpunkte->set_label_align(0, 0);
   frame_lernpunkte->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame_lernpunkte->add(*table96);
   table117->attach(*frame_lernpunkte, 0, 1, 0, 1, 0, GTK_EXPAND|GTK_FILL, 0, 0);
   label544->set_alignment(0, 0.5);
   label544->set_padding(0, 0);
   viewport35->set_shadow_type(GTK_SHADOW_NONE);
   viewport35->add(*tree_gelerntes);
   scrolledwindow73->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow73->add(*viewport35);
   table122->attach(*label544, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table122->attach(*scrolledwindow73, 0, 1, 1, 2, GTK_EXPAND|GTK_SHRINK|GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);
   viewport_lernen->set_shadow_type(GTK_SHADOW_NONE);
   scrolledwindow_lernen->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow_lernen->add(*viewport_lernen);
   Tree_Lernschema_Zusatz->set_events(GDK_LEAVE_NOTIFY_MASK);
   viewport39->set_shadow_type(GTK_SHADOW_NONE);
   viewport39->add(*Tree_Lernschema_Zusatz);
   scrolledwindow77->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow77->add(*viewport39);
   frame_lernschema_zusatz->set_label_align(0, 0);
   frame_lernschema_zusatz->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame_lernschema_zusatz->add(*scrolledwindow77);
   label_lernschma_titel->set_alignment(0, 0.5);
   label_lernschma_titel->set_padding(0, 0);
   table123->attach(*scrolledwindow_lernen, 0, 1, 1, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table123->attach(*frame_lernschema_zusatz, 1, 2, 0, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table123->attach(*label_lernschma_titel, 0, 1, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);
   hpaned6->set_handle_size(10);
   hpaned6->set_gutter_size(6);
   hpaned6->set_position(243);
   hpaned6->pack1(*table122, true, true);
   hpaned6->pack2(*table123, true, true);
   pixmap99->set_alignment(0.5, 0.5);
   pixmap99->set_padding(0, 0);
   pixmap105->set_alignment(0.5, 0.5);
   pixmap105->set_padding(0, 0);
   pixmap96->set_alignment(0.5, 0.5);
   pixmap96->set_padding(0, 0);
   pixmap98->set_alignment(0.5, 0.5);
   pixmap98->set_padding(0, 0);
   pixmap97->set_alignment(0.5, 0.5);
   pixmap97->set_padding(0, 0);
   pixmap95->set_alignment(0.5, 0.5);
   pixmap95->set_padding(0, 0);
   table119->pack_start(*pixmap99);
   table119->pack_start(*pixmap105);
   table119->pack_start(*pixmap96);
   table119->pack_start(*pixmap98);
   table119->pack_start(*pixmap97);
   table119->pack_start(*pixmap95);
   label537->set_alignment(0.5, 0.5);
   label537->set_padding(0, 0);
   vbox62->pack_start(*table119);
   vbox62->pack_start(*label537);
   _tooltips.set_tip(*button_angeborene_fert, "Linke Maustaste: W�rfeln                          Rechte Maustaste: Ausw�hlen (Abbruch dann mit 'Lernpunkte')", "");
   button_angeborene_fert->add(*vbox62);
   _tooltips.set_tip(*button_lernpunkte, "Lernpunkte w�rfeln", "");
   _tooltips.set_tip(*togglebutton_lernpunkte_edit, "Lernpunkte editieren und/oder %Wurf f�r Berufswahl eingeben.", "");
   _tooltips.set_tip(*button_beruf, "Linke Maustaste: Auswahl aus Originalliste. Rechte Maustaste: Berufsnamen selber eingeben.", "");
   label557->set_alignment(0, 0.5);
   label557->set_padding(0, 0);
   label558->set_alignment(0, 0.5);
   label558->set_padding(0, 0);
   _tooltips.set_tip(*spinbutton_beruf, "%Wurf f�r den Beruf eingeben", "");
   spinbutton_beruf->set_editable(true);
   table_berufsprozent->attach(*label557, 0, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table_berufsprozent->attach(*label558, 1, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table_berufsprozent->attach(*spinbutton_beruf, 0, 1, 1, 2, GTK_FILL, 0, 0, 0);
   label542->set_alignment(0, 0.5);
   label542->set_padding(0, 0);
   label542->set_justify(GTK_JUSTIFY_LEFT);
   entry_berufsname->set_editable(true);
   vbox_berufsname->pack_start(*label542, false, false, 0);
   vbox_berufsname->pack_start(*entry_berufsname, false, false, 0);
   vbox49->pack_start(*table_berufsprozent);
   vbox49->pack_start(*vbox_berufsname);
   _tooltips.set_tip(*button_lernschema_geld, "Linke Maustaste: Geld w�rfeln             Rechte Maustaste: Geld eingeben", "");
   _tooltips.set_tip(*button_lernschema_waffen, "Linke Maustaste: Waffen ausw�rfeln            Rechte Maustaste: Waffen aussuchen", "");
   label_gwr->set_alignment(0, 0.5);
   label_gwr->set_padding(0, 0);
   spinbutton_waffen_lernschema->set_editable(true);
   table_waffen_lernschema_eingabe->attach(*label_gwr, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table_waffen_lernschema_eingabe->attach(*spinbutton_waffen_lernschema, 0, 1, 1, 2, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   _tooltips.set_tip(*button_ruestung, "Linke Maustaste: R�stung w�rfeln                                 Rechte Maustaste: R�stung aussuchen", "");
   toolbar3->set_space_size(5);
   toolbar3->set_tooltips(true);
   toolbar3->set_space_style(GTK_TOOLBAR_SPACE_EMPTY);
   handlebox_lernschema->add(*toolbar3);
   fertig_typ->set_alignment(0.5, 0.5);
   fertig_typ->set_padding(5, 5);
   frame59->set_label_align(0, 0);
   frame59->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame59->add(*fertig_typ);
   label_ruestung_lernschema->set_alignment(0.5, 0.5);
   label_ruestung_lernschema->set_padding(0, 0);
   frame101->set_label_align(0, 0);
   frame101->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame101->add(*label_ruestung_lernschema);
   pixmap122->set_alignment(0.5, 0.5);
   pixmap122->set_padding(0, 0);
   label545->set_alignment(0.5, 0.5);
   label545->set_padding(0, 0);
   hbox61->pack_start(*pixmap122);
   hbox61->pack_start(*label545, false, false, 0);
   togglebutton_spezialwaffe->set_flags(GTK_CAN_FOCUS);
   _tooltips.set_tip(*togglebutton_spezialwaffe, "Nach dem Dr�cken dieses Knopfes kann eine Spezialwaffe gew�hlt werden. Entweder eine Nahkampfwaffe die 1 LP gekostet hat, oder eine Fernkampfwaffe, die h�chstens 2 LP gekostet hat.", "");
   togglebutton_spezialwaffe->add(*hbox61);
   label_herkunft_lernschema->set_alignment(0.5, 0.5);
   label_herkunft_lernschema->set_padding(0, 0);
   frame102->set_label_align(0, 0);
   frame102->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame102->add(*label_herkunft_lernschema);
   table131->attach(*frame59, 0, 1, 0, 1, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table131->attach(*frame101, 2, 3, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
   table131->attach(*togglebutton_spezialwaffe, 3, 4, 0, 1, GTK_FILL, 0, 0, 0);
   table131->attach(*frame102, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
   label565->set_alignment(0, 0.5);
   label565->set_padding(0, 0);
   togglebutton_teure_anzeigen->set_flags(GTK_CAN_FOCUS);
   togglebutton_teure_anzeigen->add(*label565);
   label562->set_alignment(7.45058e-09, 0.5);
   label562->set_padding(0, 0);
   togglebutton_gelernte_anzeigen->set_flags(GTK_CAN_FOCUS);
   togglebutton_gelernte_anzeigen->add(*label562);
   pixmap145->set_alignment(0.5, 0.5);
   pixmap145->set_padding(0, 0);
   table132->attach(*togglebutton_teure_anzeigen, 1, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table132->attach(*togglebutton_gelernte_anzeigen, 1, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table132->attach(*pixmap145, 0, 1, 0, 2, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
   frame103->set_label_align(0, 0);
   frame103->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame103->add(*table132);
   eventbox_zusatz->set_events(GDK_LEAVE_NOTIFY_MASK);
   table_lernschema_121->attach(*table131, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table_lernschema_121->attach(*frame103, 2, 3, 0, 1, GTK_FILL, 0, 0, 0);
   table_lernschema_121->attach(*eventbox_zusatz, 3, 4, 0, 1, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
   pixmap_dfr3->set_usize(300,-1);
   pixmap_dfr3->set_alignment(0.5, 0.5);
   pixmap_dfr3->set_padding(0, 0);
   viewport36->set_usize(309,-1);
   viewport36->set_shadow_type(GTK_SHADOW_NONE);
   viewport36->add(*pixmap_dfr3);
   scrolledwindow_dfr3->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow_dfr3->add(*viewport36);
   table_lernschema->attach(*table117, 0, 1, 1, 2, GTK_FILL, 0, 0, 0);
   table_lernschema->attach(*hpaned6, 0, 1, 3, 4, GTK_EXPAND|GTK_SHRINK|GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);
   table_lernschema->attach(*handlebox_lernschema, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
   table_lernschema->attach(*table_lernschema_121, 0, 1, 2, 3, GTK_SHRINK|GTK_FILL, GTK_SHRINK|GTK_FILL, 0, 0);
   table_lernschema->attach(*scrolledwindow_dfr3, 1, 2, 0, 4, GTK_SHRINK|GTK_FILL, GTK_SHRINK|GTK_FILL, 0, 0);
   pixmap70->show();
   button_waffe_trans->show();
   pixmap71->show();
   button_fach_trans->show();
   spinbutton_fach->show();
   pixmap120->show();
   pixmap118->show();
   pixmap119->show();
   hbox60->show();
   button_fachkenntnisse->show();
   vbox33->show();
   frame25->show();
   spinbutton_allgemein->show();
   pixmap116->show();
   pixmap149->show();
   hbox59->show();
   button_allgemeinwissen->show();
   vbox34->show();
   frame26->show();
   spinbutton_unge->show();
   pixmap121->show();
   pixmap114->show();
   hbox50->show();
   button_untyp_fertigkeiten->show();
   vbox35->show();
   frame80->show();
   combo_kido_stil->show();
   pixmap102->show();
   label540->show();
   hbox54->show();
   button_kido_auswahl->show();
   vbox45->show();
   frame_KiDo_lernschema->show();
   spinbutton_waffen->show();
   pixmap100->show();
   pixmap107->show();
   hbox52->show();
   button_waffen->show();
   vbox36->show();
   frame27->show();
   spinbutton_zauber->show();
   pixmap101->show();
   pixmap123->show();
   hbox53->show();
   button_zauber->show();
   vbox37->show();
   frame28->show();
   combo_magier_spezialgebiet->show();
   table96->show();
   frame_lernpunkte->show();
   table117->show();
   label544->show();
   tree_gelerntes->show();
   viewport35->show();
   scrolledwindow73->show();
   table122->show();
   viewport_lernen->show();
   scrolledwindow_lernen->show();
   Tree_Lernschema_Zusatz->show();
   viewport39->show();
   scrolledwindow77->show();
   frame_lernschema_zusatz->show();
   label_lernschma_titel->show();
   table123->show();
   hpaned6->show();
   pixmap99->show();
   pixmap105->show();
   pixmap96->show();
   pixmap98->show();
   pixmap97->show();
   pixmap95->show();
   table119->show();
   label537->show();
   vbox62->show();
   button_angeborene_fert->show();
   label557->show();
   label558->show();
   spinbutton_beruf->show();
   table_berufsprozent->show();
   label542->show();
   entry_berufsname->show();
   vbox_berufsname->show();
   vbox49->show();
   label_gwr->show();
   spinbutton_waffen_lernschema->show();
   toolbar3->show();
   handlebox_lernschema->show();
   fertig_typ->show();
   frame59->show();
   label_ruestung_lernschema->show();
   frame101->show();
   pixmap122->show();
   label545->show();
   hbox61->show();
   togglebutton_spezialwaffe->show();
   label_herkunft_lernschema->show();
   frame102->show();
   table131->show();
   label565->show();
   togglebutton_teure_anzeigen->show();
   label562->show();
   togglebutton_gelernte_anzeigen->show();
   pixmap145->show();
   table132->show();
   frame103->show();
   eventbox_zusatz->show();
   table_lernschema_121->show();
   pixmap_dfr3->show();
   viewport36->show();
   scrolledwindow_dfr3->show();
   table_lernschema->show();
   button_waffe_trans->clicked.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_button_waffe_trans_clicked));
   button_fach_trans->clicked.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_button_fach_trans_clicked));
   spinbutton_fach->activate.connect_after(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_fach_activate));
   spinbutton_fach->focus_out_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_fach_focus_out_event));
   spinbutton_fach->focus_in_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_fach_focus_in_event));
   button_fachkenntnisse->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_lernliste_wahl_toggled));
   spinbutton_allgemein->activate.connect_after(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_allgemein_activate));
   spinbutton_allgemein->focus_out_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_allgemein_focus_out_event));
   spinbutton_allgemein->focus_in_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_allgemein_focus_in_event));
   button_allgemeinwissen->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_lernliste_wahl_toggled));
   spinbutton_unge->activate.connect_after(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_unge_activate));
   spinbutton_unge->focus_out_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_unge_focus_out_event));
   spinbutton_unge->focus_in_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_unge_focus_in_event));
   button_untyp_fertigkeiten->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_lernliste_wahl_toggled));
   combo_kido_stil->get_entry()->activate.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_combo_kido_stil_activate));
   combo_kido_stil->get_entry()->focus_out_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_combo_kido_stil_focus_out_event));
   button_kido_auswahl->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_kido_wahl_clicked));
   spinbutton_waffen->activate.connect_after(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_waffen_activate));
   spinbutton_waffen->focus_out_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_waffen_focus_out_event));
   spinbutton_waffen->focus_in_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_waffen_focus_in_event));
   button_waffen->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_lernliste_wahl_toggled));
   button_waffen->clicked.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_button_waffen_clicked));
   spinbutton_zauber->activate.connect_after(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_zaubern_activate));
   spinbutton_zauber->focus_out_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_zaubern_focus_out_event));
   spinbutton_zauber->focus_in_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_zaubern_focus_in_event));
   button_zauber->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_lernliste_wahl_toggled));
   combo_magier_spezialgebiet->get_entry()->activate.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_combo_magier_spezialgebiet_activate));
   combo_magier_spezialgebiet->get_entry()->focus_out_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_combo_magier_spezialgebiet_focus_out_event));
   tree_gelerntes->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_tree_gelerntes_leaf_selected));
   button_herkunft->clicked.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_herkunftsland_clicked));
   button_angeborene_fert->button_release_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_angeborene_fertigkeit_button_release_event));
   button_lernpunkte->clicked.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_lernpunkte_wuerfeln_clicked));
   togglebutton_lernpunkte_edit->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_togglebutton_lernpunkte_edit_toggled));
   button_beruf->button_release_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_button_beruf_release_event));
   spinbutton_beruf->activate.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_beruf_activate));
   spinbutton_beruf->focus_in_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_beruf_focus_in));
   entry_berufsname->activate.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_entry_berufsname_activate));
   button_lernschema_geld->button_release_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_button_lernschema_geld_button_release_event));
   button_lernschema_waffen->button_release_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_button_lernschema_waffen_button_release_event));
   spinbutton_waffen_lernschema->activate.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_waffen_lernschema_activate));
   spinbutton_waffen_lernschema->focus_in_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_spinbutton_waffen_lernschema_focus_in_event));
   button_ruestung->button_release_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_button_ruestung_button_release_event));
   togglebutton_teure_anzeigen->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_togglebutton_teure_anzeigen_toggled));
   togglebutton_gelernte_anzeigen->toggled.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_togglebutton_gelernte_anzeigen_toggled));
   eventbox_zusatz->leave_notify_event.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_eventbox_zusatz_leave_notify_event));
}

table_lernschema_glade::~table_lernschema_glade()
{  delete tree_gelerntes;
   delete Tree_Lernschema_Zusatz;
}
