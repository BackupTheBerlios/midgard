// generated 2004/5/10 13:57:50 CEST by christof@puck.petig-baender.de
// using glademm V2.6.0_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage --gtkmmversion 2.4.0 midgard.glade
// for gtk 2.4.0 and gtkmm 2.4.0
//
// Please modify the corresponding derived classes in ./src/table_ausruestung.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
#include <gtkmmconfig.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //
#include "table_ausruestung_glade.hh"
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/treeview.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/image.h>

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/handlebox.h>
#include <gtkmm/separator.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/paned.h>

table_ausruestung_glade::table_ausruestung_glade(GlademmData *gmm_data
) : Gtk::Table(2, 2, false)
{  table_ausruestung = this;
   
   Gtk::Button *button_ausruestung_druck = Gtk::manage(new class Gtk::Button("Drucken"));
   Gtk::Label *separatortoolitem6 = Gtk::manage(new class Gtk::Label("GtkSeparatorToolItem separatortoolitem6"));
   togglebutton_gruppe_neu = Gtk::manage(new class Gtk::ToggleButton("Neue Art"));
   togglebutton_artikel_neu = Gtk::manage(new class Gtk::ToggleButton("Neuer Artikel"));
   
   Gtk::Toolbar *toolbar39 = Gtk::manage(new class Gtk::Toolbar());
   Gtk::Label *label506 = Gtk::manage(new class Gtk::Label("Gegenstand"));
   Gtk::Label *label507 = Gtk::manage(new class Gtk::Label("Preis"));
   Gtk::Label *label508 = Gtk::manage(new class Gtk::Label("Einheit"));
   Gtk::Label *label511 = Gtk::manage(new class Gtk::Label("Art"));
   Gtk::Label *label527 = Gtk::manage(new class Gtk::Label("Art2"));
   entry_name = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label509 = Gtk::manage(new class Gtk::Label("Gew. (kg)"));
   Gtk::Label *label649 = Gtk::manage(new class Gtk::Label("Region"));
   combo_region = Gtk::manage(new class Gtk::Combo());
   combo_einheit = Gtk::manage(new class Gtk::Combo());
   
   Gtk::Adjustment *spinbutton_preis_adj = Gtk::manage(new class Gtk::Adjustment(1, 0, 100000, 1, 10, 10));
   spinbutton_preis = Gtk::manage(new class Gtk::SpinButton(*spinbutton_preis_adj, 1, 1));
   
   Gtk::Adjustment *spinbutton_gewicht_adj = Gtk::manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_gewicht = Gtk::manage(new class Gtk::SpinButton(*spinbutton_gewicht_adj, 1, 2));
   
   Gtk::Image *pixmap188 = Gtk::manage(new class Gtk::Image(MagusImage("SaveChar-trans-50.xpm")));
   Gtk::Label *label650 = Gtk::manage(new class Gtk::Label("Artikel\n"
		"speichern"));
   Gtk::HBox *hbox102 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_artikel_speichern = Gtk::manage(new class Gtk::Button());
   combo_art = Gtk::manage(new class Gtk::Combo());
   combo_art2 = Gtk::manage(new class Gtk::Combo());
   table_artikel = Gtk::manage(new class Gtk::Table(2, 2, false));
   entry_beschreibung = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label689 = Gtk::manage(new class Gtk::Label("Beschreibung des Artikels (optional)"));
   Gtk::Frame *frame120 = Gtk::manage(new class Gtk::Frame());
   Gtk::Label *label503 = Gtk::manage(new class Gtk::Label("Art"));
   Gtk::Label *label504 = Gtk::manage(new class Gtk::Label("Art2"));
   entry_art = Gtk::manage(new class Gtk::Entry());
   entry_art2 = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Image *pixmap189 = Gtk::manage(new class Gtk::Image(MagusImage("SaveChar-trans-50.xpm")));
   Gtk::Label *label651 = Gtk::manage(new class Gtk::Label("Art\n"
		"speichern"));
   Gtk::HBox *hbox103 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_art_speichern = Gtk::manage(new class Gtk::Button());
   table_gruppe = Gtk::manage(new class Gtk::Table(2, 2, false));
   
   Gtk::Table *table81 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::HandleBox *handlebox7 = Gtk::manage(new class Gtk::HandleBox());
   Gtk::Image *pixmap69 = Gtk::manage(new class Gtk::Image(MagusImage("Trash-32.xpm")));
   Gtk::Label *label475 = Gtk::manage(new class Gtk::Label("Löschen"));
   Gtk::HBox *hbox35 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_ausruestung_loeschen = Gtk::manage(new class Gtk::Button());
   
   Gtk::Image *pixmap89 = Gtk::manage(new class Gtk::Image(MagusImage("sichtbar.xpm")));
   checkbutton_sichtbar = Gtk::manage(new class Gtk::CheckButton());
   
   Gtk::Table *table105 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::Label *label623 = Gtk::manage(new class Gtk::Label("Zunächst oben auswählen, wo der neue Gegenstand eingefügt werden soll,\n"
		"anschließend unten den neuen Gegenstand auswählen."));
   scrolledwindow_ausruestung = Gtk::manage(new class Gtk::ScrolledWindow());
   label_gesamtlast = Gtk::manage(new class Gtk::Label("kg"));
   
   Gtk::Label *label629 = Gtk::manage(new class Gtk::Label("Gesamtlast:"));
   Gtk::Label *label630 = Gtk::manage(new class Gtk::Label("Normallast:"));
   Gtk::Label *label = Gtk::manage(new class Gtk::Label("Höchstlast:"));
   Gtk::Label *label632 = Gtk::manage(new class Gtk::Label("Schublast:"));
   label_normallast = Gtk::manage(new class Gtk::Label("kg"));
   label_hoechstlast = Gtk::manage(new class Gtk::Label("kg"));
   label_schublast = Gtk::manage(new class Gtk::Label("kg"));
   
   Gtk::HSeparator *hseparator22 = Gtk::manage(new class Gtk::HSeparator());
   Gtk::Table *table178 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::Label *label674 = Gtk::manage(new class Gtk::Label("Belastbarkeit"));
   Gtk::Frame *frame117 = Gtk::manage(new class Gtk::Frame());
   Gtk::Table *table93 = Gtk::manage(new class Gtk::Table(2, 2, false));
   preise_tree_neu = new class SimpleTree(9);
   
   Gtk::ScrolledWindow *scrolledwindow66 = Gtk::manage(new class Gtk::ScrolledWindow());
   Gtk::Image *pixmap83 = Gtk::manage(new class Gtk::Image(MagusImage("Money-50.xpm")));
   Gtk::Label *label526 = Gtk::manage(new class Gtk::Label("Mit Geld\n"
		"ausrüsten"));
   Gtk::HBox *hbox46 = Gtk::manage(new class Gtk::HBox(false, 0));
   checkbutton_ausruestung_geld = Gtk::manage(new class Gtk::CheckButton());
   label_golda = Gtk::manage(new class Gtk::Label("0"));
   
   Gtk::Label *label675 = Gtk::manage(new class Gtk::Label("Gold"));
   Gtk::Frame *frame81 = Gtk::manage(new class Gtk::Frame());
   label_silbera = Gtk::manage(new class Gtk::Label("0"));
   
   Gtk::Label *label676 = Gtk::manage(new class Gtk::Label("Silber"));
   Gtk::Frame *frame82 = Gtk::manage(new class Gtk::Frame());
   label_kupfera = Gtk::manage(new class Gtk::Label("0"));
   
   Gtk::Label *label677 = Gtk::manage(new class Gtk::Label("Kupfer"));
   Gtk::Frame *frame83 = Gtk::manage(new class Gtk::Frame());
   Gtk::Image *pixmap177 = Gtk::manage(new class Gtk::Image(MagusImage("Angeb_Sicht-32.xpm")));
   Gtk::Label *label637 = Gtk::manage(new class Gtk::Label("Unverkäufliches\n"
		"anzeigen"));
   Gtk::HBox *hbox96 = Gtk::manage(new class Gtk::HBox(false, 0));
   togglebutton_unverkauflich = Gtk::manage(new class Gtk::ToggleButton());
   
   Gtk::Adjustment *spinbutton_anzahl_adj = Gtk::manage(new class Gtk::Adjustment(1, 0, 1000, 1, 10, 10));
   spinbutton_anzahl = Gtk::manage(new class Gtk::SpinButton(*spinbutton_anzahl_adj, 1, 0));
   
   Gtk::Label *label688 = Gtk::manage(new class Gtk::Label("Anzahl"));
   Gtk::Frame *frame119 = Gtk::manage(new class Gtk::Frame());
   Gtk::Table *table92 = Gtk::manage(new class Gtk::Table(2, 2, true));
   Gtk::Table *table94 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::VPaned *vpaned11 = Gtk::manage(new class Gtk::VPaned());
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
   {  Gtk::ToolItem *item = Gtk::manage(new Gtk::ToolItem);
      item->add(*button_ausruestung_druck);
      toolbar39->append(*item);
   }
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Element(*button_ausruestung_druck));
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
   {  
      
      Gtk::ToolItem *item = Gtk::manage(new Gtk::ToolItem);
      item->add(*separatortoolitem6);
      toolbar39->append(*item);
   }
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Element(*separatortoolitem6));
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
   {  
      
      Gtk::ToolItem *item = Gtk::manage(new Gtk::ToolItem);
      item->add(*togglebutton_gruppe_neu);
      toolbar39->append(*item);
   }
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Element(*togglebutton_gruppe_neu));
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
   {  
      
      Gtk::ToolItem *item = Gtk::manage(new Gtk::ToolItem);
      item->add(*togglebutton_artikel_neu);
      toolbar39->append(*item);
   }
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Element(*togglebutton_artikel_neu));
#endif //
   _tooltips.set_tip(*button_ausruestung_druck, "Drucken (alles)", "");
   togglebutton_gruppe_neu->set_active(false);
   togglebutton_artikel_neu->set_active(false);
   toolbar39->set_tooltips(true);
   toolbar39->set_toolbar_style(Gtk::TOOLBAR_BOTH);
   toolbar39->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
   label506->set_alignment(0,0.5);
   label506->set_padding(0,0);
   label506->set_justify(Gtk::JUSTIFY_CENTER);
   label506->set_line_wrap(false);
   label506->set_use_markup(false);
   label506->set_selectable(false);
   label507->set_alignment(0,0.5);
   label507->set_padding(0,0);
   label507->set_justify(Gtk::JUSTIFY_CENTER);
   label507->set_line_wrap(false);
   label507->set_use_markup(false);
   label507->set_selectable(false);
   label508->set_alignment(0,0.5);
   label508->set_padding(0,0);
   label508->set_justify(Gtk::JUSTIFY_CENTER);
   label508->set_line_wrap(false);
   label508->set_use_markup(false);
   label508->set_selectable(false);
   label511->set_alignment(0,0.5);
   label511->set_padding(0,0);
   label511->set_justify(Gtk::JUSTIFY_CENTER);
   label511->set_line_wrap(false);
   label511->set_use_markup(false);
   label511->set_selectable(false);
   label527->set_alignment(0,0.5);
   label527->set_padding(0,0);
   label527->set_justify(Gtk::JUSTIFY_CENTER);
   label527->set_line_wrap(false);
   label527->set_use_markup(false);
   label527->set_selectable(false);
   entry_name->set_flags(Gtk::CAN_FOCUS);
   entry_name->set_visibility(true);
   entry_name->set_editable(true);
   entry_name->set_max_length(0);
   entry_name->set_text("");
   entry_name->set_has_frame(true);
   entry_name->set_activates_default(false);
   label509->set_alignment(0,0.5);
   label509->set_padding(0,0);
   label509->set_justify(Gtk::JUSTIFY_CENTER);
   label509->set_line_wrap(false);
   label509->set_use_markup(false);
   label509->set_selectable(false);
   label649->set_alignment(0,0.5);
   label649->set_padding(0,0);
   label649->set_justify(Gtk::JUSTIFY_CENTER);
   label649->set_line_wrap(false);
   label649->set_use_markup(false);
   label649->set_selectable(false);
   combo_region->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_region->get_entry()->set_visibility(true);
   combo_region->get_entry()->set_editable(false);
   combo_region->get_entry()->set_max_length(0);
   combo_region->get_entry()->set_text("");
   combo_region->get_entry()->set_has_frame(true);
   combo_region->get_entry()->set_activates_default(false);
   combo_region->set_sensitive(false);
   combo_region->set_case_sensitive(false);
   {  
      
      const char * const items[] = { "", "", 0 };
      combo_region->set_popdown_strings(items);
   }
   combo_region->get_entry()->set_text("");
   combo_einheit->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_einheit->get_entry()->set_visibility(true);
   combo_einheit->get_entry()->set_editable(false);
   combo_einheit->get_entry()->set_max_length(0);
   combo_einheit->get_entry()->set_text("");
   combo_einheit->get_entry()->set_has_frame(true);
   combo_einheit->get_entry()->set_activates_default(false);
   combo_einheit->set_case_sensitive(false);
   {  
      
      const char * const items[] = { "", "", "", "", 0 };
      combo_einheit->set_popdown_strings(items);
   }
   combo_einheit->get_entry()->set_text("");
   spinbutton_preis->set_flags(Gtk::CAN_FOCUS);
   spinbutton_preis->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbutton_preis->set_numeric(false);
   spinbutton_preis->set_digits(1);
   spinbutton_preis->set_wrap(false);
   spinbutton_gewicht->set_flags(Gtk::CAN_FOCUS);
   spinbutton_gewicht->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbutton_gewicht->set_numeric(false);
   spinbutton_gewicht->set_digits(2);
   spinbutton_gewicht->set_wrap(false);
   pixmap188->set_alignment(0.5,0.5);
   pixmap188->set_padding(0,0);
   label650->set_alignment(0.5,0.5);
   label650->set_padding(0,0);
   label650->set_justify(Gtk::JUSTIFY_CENTER);
   label650->set_line_wrap(false);
   label650->set_use_markup(false);
   label650->set_selectable(false);
   hbox102->pack_start(*pixmap188);
   hbox102->pack_start(*label650, Gtk::PACK_SHRINK, 0);
   button_artikel_speichern->set_flags(Gtk::CAN_FOCUS);
   button_artikel_speichern->set_relief(Gtk::RELIEF_NORMAL);
   button_artikel_speichern->add(*hbox102);
   combo_art->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_art->get_entry()->set_visibility(true);
   combo_art->get_entry()->set_editable(false);
   combo_art->get_entry()->set_max_length(0);
   combo_art->get_entry()->set_text("");
   combo_art->get_entry()->set_has_frame(true);
   combo_art->get_entry()->set_activates_default(false);
   combo_art->set_case_sensitive(false);
   {  
      
      const char * const items[] = { "", "", 0 };
      combo_art->set_popdown_strings(items);
   }
   combo_art->get_entry()->set_text("");
   combo_art2->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_art2->get_entry()->set_visibility(true);
   combo_art2->get_entry()->set_editable(false);
   combo_art2->get_entry()->set_max_length(0);
   combo_art2->get_entry()->set_text("");
   combo_art2->get_entry()->set_has_frame(true);
   combo_art2->get_entry()->set_activates_default(false);
   combo_art2->set_case_sensitive(false);
   {  
      
      const char * const items[] = { "", 0 };
      combo_art2->set_popdown_strings(items);
   }
   combo_art2->get_entry()->set_text("");
   table_artikel->set_row_spacings(0);
   table_artikel->set_col_spacings(0);
   table_artikel->attach(*label506, 2, 3, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*label507, 4, 5, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*label508, 5, 6, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*label511, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*label527, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*entry_name, 2, 3, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*label509, 3, 4, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*label649, 6, 7, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*combo_region, 6, 7, 1, 2, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_artikel->attach(*combo_einheit, 5, 6, 1, 2, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_artikel->attach(*spinbutton_preis, 4, 5, 1, 2, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_artikel->attach(*spinbutton_gewicht, 3, 4, 1, 2, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_artikel->attach(*button_artikel_speichern, 7, 8, 0, 2, Gtk::EXPAND|Gtk::SHRINK, Gtk::SHRINK|Gtk::FILL, 0, 0);
   table_artikel->attach(*combo_art, 0, 1, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*combo_art2, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   entry_beschreibung->set_flags(Gtk::CAN_FOCUS);
   entry_beschreibung->set_visibility(true);
   entry_beschreibung->set_editable(true);
   entry_beschreibung->set_max_length(0);
   entry_beschreibung->set_text("");
   entry_beschreibung->set_has_frame(true);
   entry_beschreibung->set_activates_default(false);
   label689->set_alignment(0.5,0.5);
   label689->set_padding(0,0);
   label689->set_justify(Gtk::JUSTIFY_LEFT);
   label689->set_line_wrap(false);
   label689->set_use_markup(false);
   label689->set_selectable(false);
   frame120->set_shadow_type(Gtk::SHADOW_NONE);
   frame120->set_label_align(0,0.5);
   frame120->add(*entry_beschreibung);
   frame120->set_label_widget(*label689);
   label503->set_alignment(0,0.5);
   label503->set_padding(0,0);
   label503->set_justify(Gtk::JUSTIFY_CENTER);
   label503->set_line_wrap(false);
   label503->set_use_markup(false);
   label503->set_selectable(false);
   label504->set_alignment(0,0.5);
   label504->set_padding(0,0);
   label504->set_justify(Gtk::JUSTIFY_CENTER);
   label504->set_line_wrap(false);
   label504->set_use_markup(false);
   label504->set_selectable(false);
   entry_art->set_flags(Gtk::CAN_FOCUS);
   entry_art->set_visibility(true);
   entry_art->set_editable(true);
   entry_art->set_max_length(0);
   entry_art->set_text("");
   entry_art->set_has_frame(true);
   entry_art->set_activates_default(false);
   entry_art2->set_flags(Gtk::CAN_FOCUS);
   entry_art2->set_visibility(true);
   entry_art2->set_editable(true);
   entry_art2->set_max_length(0);
   entry_art2->set_text("");
   entry_art2->set_has_frame(true);
   entry_art2->set_activates_default(false);
   pixmap189->set_alignment(0.5,0.5);
   pixmap189->set_padding(0,0);
   label651->set_alignment(0.5,0.5);
   label651->set_padding(0,0);
   label651->set_justify(Gtk::JUSTIFY_CENTER);
   label651->set_line_wrap(false);
   label651->set_use_markup(false);
   label651->set_selectable(false);
   hbox103->pack_start(*pixmap189);
   hbox103->pack_start(*label651, Gtk::PACK_SHRINK, 0);
   button_art_speichern->set_flags(Gtk::CAN_FOCUS);
   button_art_speichern->set_relief(Gtk::RELIEF_NORMAL);
   button_art_speichern->add(*hbox103);
   table_gruppe->set_row_spacings(0);
   table_gruppe->set_col_spacings(0);
   table_gruppe->attach(*label503, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_gruppe->attach(*label504, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_gruppe->attach(*entry_art, 0, 1, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_gruppe->attach(*entry_art2, 1, 2, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_gruppe->attach(*button_art_speichern, 2, 3, 0, 2, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table81->set_row_spacings(0);
   table81->set_col_spacings(0);
   table81->attach(*toolbar39, 0, 1, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 5, 5);
   table81->attach(*table_artikel, 0, 1, 2, 3, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 0, 0);
   table81->attach(*frame120, 0, 1, 3, 4, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 0, 0);
   table81->attach(*table_gruppe, 0, 1, 1, 2, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 0, 0);
   handlebox7->set_shadow_type(Gtk::SHADOW_OUT);
   handlebox7->set_handle_position(Gtk::POS_LEFT);
   handlebox7->set_snap_edge(Gtk::POS_TOP);
   handlebox7->add(*table81);
   pixmap69->set_alignment(0.5,0.5);
   pixmap69->set_padding(0,0);
   label475->set_alignment(0.5,0.5);
   label475->set_padding(0,0);
   label475->set_justify(Gtk::JUSTIFY_CENTER);
   label475->set_line_wrap(false);
   label475->set_use_markup(false);
   label475->set_selectable(false);
   hbox35->pack_start(*pixmap69);
   hbox35->pack_start(*label475, Gtk::PACK_SHRINK, 0);
   button_ausruestung_loeschen->set_flags(Gtk::CAN_FOCUS);
   button_ausruestung_loeschen->set_relief(Gtk::RELIEF_NORMAL);
   button_ausruestung_loeschen->add(*hbox35);
   pixmap89->set_alignment(0.5,0.5);
   pixmap89->set_padding(0,0);
   checkbutton_sichtbar->set_flags(Gtk::CAN_FOCUS);
   checkbutton_sichtbar->set_relief(Gtk::RELIEF_NORMAL);
   checkbutton_sichtbar->set_mode(false);
   checkbutton_sichtbar->set_active(false);
   checkbutton_sichtbar->add(*pixmap89);
   table105->set_row_spacings(0);
   table105->set_col_spacings(0);
   table105->attach(*button_ausruestung_loeschen, 0, 1, 2, 3, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 0, 0);
   table105->attach(*checkbutton_sichtbar, 0, 1, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 0, 0);
   label623->set_alignment(0,7.45058e-09);
   label623->set_padding(0,0);
   label623->set_justify(Gtk::JUSTIFY_LEFT);
   label623->set_line_wrap(false);
   label623->set_use_markup(false);
   label623->set_selectable(false);
   scrolledwindow_ausruestung->set_shadow_type(Gtk::SHADOW_NONE);
   scrolledwindow_ausruestung->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow_ausruestung->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   label_gesamtlast->set_alignment(0,0.5);
   label_gesamtlast->set_padding(0,0);
   label_gesamtlast->set_justify(Gtk::JUSTIFY_CENTER);
   label_gesamtlast->set_line_wrap(false);
   label_gesamtlast->set_use_markup(false);
   label_gesamtlast->set_selectable(false);
   label629->set_alignment(0,0.5);
   label629->set_padding(2,0);
   label629->set_justify(Gtk::JUSTIFY_CENTER);
   label629->set_line_wrap(false);
   label629->set_use_markup(false);
   label629->set_selectable(false);
   label630->set_alignment(0,0.5);
   label630->set_padding(2,0);
   label630->set_justify(Gtk::JUSTIFY_CENTER);
   label630->set_line_wrap(false);
   label630->set_use_markup(false);
   label630->set_selectable(false);
   label->set_alignment(0,0.5);
   label->set_padding(2,0);
   label->set_justify(Gtk::JUSTIFY_CENTER);
   label->set_line_wrap(false);
   label->set_use_markup(false);
   label->set_selectable(false);
   label632->set_alignment(0,0.5);
   label632->set_padding(2,0);
   label632->set_justify(Gtk::JUSTIFY_CENTER);
   label632->set_line_wrap(false);
   label632->set_use_markup(false);
   label632->set_selectable(false);
   label_normallast->set_alignment(1,0.5);
   label_normallast->set_padding(0,0);
   label_normallast->set_justify(Gtk::JUSTIFY_CENTER);
   label_normallast->set_line_wrap(false);
   label_normallast->set_use_markup(false);
   label_normallast->set_selectable(false);
   label_hoechstlast->set_alignment(1,0.5);
   label_hoechstlast->set_padding(0,0);
   label_hoechstlast->set_justify(Gtk::JUSTIFY_CENTER);
   label_hoechstlast->set_line_wrap(false);
   label_hoechstlast->set_use_markup(false);
   label_hoechstlast->set_selectable(false);
   label_schublast->set_alignment(1,0.5);
   label_schublast->set_padding(0,0);
   label_schublast->set_justify(Gtk::JUSTIFY_CENTER);
   label_schublast->set_line_wrap(false);
   label_schublast->set_use_markup(false);
   label_schublast->set_selectable(false);
   table178->set_row_spacings(0);
   table178->set_col_spacings(2);
   table178->attach(*label_gesamtlast, 1, 2, 4, 5, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*label629, 0, 1, 4, 5, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*label630, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*label, 0, 1, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*label632, 0, 1, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*label_normallast, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*label_hoechstlast, 1, 2, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*label_schublast, 1, 2, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table178->attach(*hseparator22, 0, 2, 3, 4, Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 0);
   label674->set_alignment(0.5,0.5);
   label674->set_padding(0,0);
   label674->set_justify(Gtk::JUSTIFY_LEFT);
   label674->set_line_wrap(false);
   label674->set_use_markup(false);
   label674->set_selectable(false);
   frame117->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame117->set_label_align(0,0.5);
   frame117->add(*table178);
   frame117->set_label_widget(*label674);
   table93->set_row_spacings(0);
   table93->set_col_spacings(0);
   table93->attach(*table105, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table93->attach(*label623, 1, 3, 1, 2, Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   table93->attach(*scrolledwindow_ausruestung, 0, 1, 0, 3, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   table93->attach(*frame117, 1, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   scrolledwindow66->set_shadow_type(Gtk::SHADOW_NONE);
   scrolledwindow66->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow66->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow66->add(*preise_tree_neu);
   pixmap83->set_alignment(0.5,0.5);
   pixmap83->set_padding(0,0);
   label526->set_alignment(0.5,0.5);
   label526->set_padding(0,0);
   label526->set_justify(Gtk::JUSTIFY_CENTER);
   label526->set_line_wrap(false);
   label526->set_use_markup(false);
   label526->set_selectable(false);
   hbox46->pack_start(*pixmap83, Gtk::PACK_SHRINK, 0);
   hbox46->pack_start(*label526, Gtk::PACK_SHRINK, 0);
   checkbutton_ausruestung_geld->set_flags(Gtk::CAN_FOCUS);
   checkbutton_ausruestung_geld->set_relief(Gtk::RELIEF_NORMAL);
   checkbutton_ausruestung_geld->set_mode(false);
   checkbutton_ausruestung_geld->set_active(true);
   checkbutton_ausruestung_geld->add(*hbox46);
   label_golda->set_alignment(0.5,0.5);
   label_golda->set_padding(0,0);
   label_golda->set_justify(Gtk::JUSTIFY_CENTER);
   label_golda->set_line_wrap(false);
   label_golda->set_use_markup(false);
   label_golda->set_selectable(false);
   label675->set_alignment(0.5,0.5);
   label675->set_padding(0,0);
   label675->set_justify(Gtk::JUSTIFY_LEFT);
   label675->set_line_wrap(false);
   label675->set_use_markup(false);
   label675->set_selectable(false);
   frame81->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame81->set_label_align(0,0.5);
   frame81->add(*label_golda);
   frame81->set_label_widget(*label675);
   label_silbera->set_alignment(0.5,0.5);
   label_silbera->set_padding(0,0);
   label_silbera->set_justify(Gtk::JUSTIFY_CENTER);
   label_silbera->set_line_wrap(false);
   label_silbera->set_use_markup(false);
   label_silbera->set_selectable(false);
   label676->set_alignment(0.5,0.5);
   label676->set_padding(0,0);
   label676->set_justify(Gtk::JUSTIFY_LEFT);
   label676->set_line_wrap(false);
   label676->set_use_markup(false);
   label676->set_selectable(false);
   frame82->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame82->set_label_align(0,0.5);
   frame82->add(*label_silbera);
   frame82->set_label_widget(*label676);
   label_kupfera->set_alignment(0.5,0.5);
   label_kupfera->set_padding(0,0);
   label_kupfera->set_justify(Gtk::JUSTIFY_CENTER);
   label_kupfera->set_line_wrap(false);
   label_kupfera->set_use_markup(false);
   label_kupfera->set_selectable(false);
   label677->set_alignment(0.5,0.5);
   label677->set_padding(0,0);
   label677->set_justify(Gtk::JUSTIFY_LEFT);
   label677->set_line_wrap(false);
   label677->set_use_markup(false);
   label677->set_selectable(false);
   frame83->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame83->set_label_align(0,0.5);
   frame83->add(*label_kupfera);
   frame83->set_label_widget(*label677);
   pixmap177->set_alignment(0.5,0.5);
   pixmap177->set_padding(0,0);
   label637->set_alignment(0.5,0.5);
   label637->set_padding(0,0);
   label637->set_justify(Gtk::JUSTIFY_CENTER);
   label637->set_line_wrap(false);
   label637->set_use_markup(false);
   label637->set_selectable(false);
   hbox96->pack_start(*pixmap177);
   hbox96->pack_start(*label637, Gtk::PACK_SHRINK, 0);
   togglebutton_unverkauflich->set_flags(Gtk::CAN_FOCUS);
   togglebutton_unverkauflich->set_relief(Gtk::RELIEF_NORMAL);
   togglebutton_unverkauflich->set_active(false);
   togglebutton_unverkauflich->add(*hbox96);
   spinbutton_anzahl->set_flags(Gtk::CAN_FOCUS);
   spinbutton_anzahl->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbutton_anzahl->set_numeric(false);
   spinbutton_anzahl->set_digits(0);
   spinbutton_anzahl->set_wrap(false);
   label688->set_alignment(0.5,0.5);
   label688->set_padding(0,0);
   label688->set_justify(Gtk::JUSTIFY_LEFT);
   label688->set_line_wrap(false);
   label688->set_use_markup(false);
   label688->set_selectable(false);
   frame119->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame119->set_label_align(0,0.5);
   frame119->add(*spinbutton_anzahl);
   frame119->set_label_widget(*label688);
   table92->set_row_spacings(0);
   table92->set_col_spacings(0);
   table92->attach(*checkbutton_ausruestung_geld, 0, 3, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table92->attach(*frame81, 0, 1, 3, 4, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   table92->attach(*frame82, 1, 2, 3, 4, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
   table92->attach(*frame83, 2, 3, 3, 4, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
   table92->attach(*togglebutton_unverkauflich, 0, 3, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table92->attach(*frame119, 0, 1, 0, 1, Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 0);
   table94->set_row_spacings(0);
   table94->set_col_spacings(0);
   table94->attach(*scrolledwindow66, 0, 1, 0, 3, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   table94->attach(*table92, 1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   vpaned11->set_position(264);
   vpaned11->pack1(*table93, Gtk::SHRINK);
   vpaned11->pack2(*table94, Gtk::EXPAND|Gtk::SHRINK);
   table_ausruestung->set_row_spacings(0);
   table_ausruestung->set_col_spacings(0);
   table_ausruestung->attach(*handlebox7, 0, 2, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
   table_ausruestung->attach(*vpaned11, 0, 2, 1, 2, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   button_ausruestung_druck->show();
   separatortoolitem6->show();
   togglebutton_gruppe_neu->show();
   togglebutton_artikel_neu->show();
   toolbar39->show();
   label506->show();
   label507->show();
   label508->show();
   label511->show();
   label527->show();
   entry_name->show();
   label509->show();
   label649->show();
   combo_region->show();
   combo_einheit->show();
   spinbutton_preis->show();
   spinbutton_gewicht->show();
   pixmap188->show();
   label650->show();
   hbox102->show();
   button_artikel_speichern->show();
   combo_art->show();
   combo_art2->show();
   entry_beschreibung->show();
   label689->show();
   frame120->show();
   label503->show();
   label504->show();
   entry_art->show();
   entry_art2->show();
   pixmap189->show();
   label651->show();
   hbox103->show();
   button_art_speichern->show();
   table81->show();
   handlebox7->show();
   pixmap69->show();
   label475->show();
   hbox35->show();
   button_ausruestung_loeschen->show();
   pixmap89->show();
   checkbutton_sichtbar->show();
   table105->show();
   label623->show();
   scrolledwindow_ausruestung->show();
   label_gesamtlast->show();
   label629->show();
   label630->show();
   label->show();
   label632->show();
   label_normallast->show();
   label_hoechstlast->show();
   label_schublast->show();
   hseparator22->show();
   table178->show();
   label674->show();
   frame117->show();
   table93->show();
   preise_tree_neu->show();
   scrolledwindow66->show();
   pixmap83->show();
   label526->show();
   hbox46->show();
   checkbutton_ausruestung_geld->show();
   label_golda->show();
   label675->show();
   frame81->show();
   label_silbera->show();
   label676->show();
   frame82->show();
   label_kupfera->show();
   label677->show();
   frame83->show();
   pixmap177->show();
   label637->show();
   hbox96->show();
   togglebutton_unverkauflich->show();
   spinbutton_anzahl->show();
   label688->show();
   frame119->show();
   table92->show();
   table94->show();
   vpaned11->show();
   table_ausruestung->show();
   button_ausruestung_druck->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_button_ausruestung_druck), false);
   togglebutton_gruppe_neu->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_togglebutton_gruppe_neu_toggled), false);
   togglebutton_artikel_neu->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_togglebutton_artikel_neu_toggled), false);
   entry_name->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_entry_name_activate), false);
   combo_region->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_region_activate), false);
   combo_einheit->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_einheit_activate), false);
   combo_einheit->get_entry()->signal_changed().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_einheit_changed), false);
   spinbutton_preis->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_spinbutton_preis_activate), false);
   spinbutton_gewicht->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_spinbutton_gewicht_activate), false);
   button_artikel_speichern->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_button_artikel_speichern_clicked), false);
   combo_art->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_artikel_art_activate), false);
   combo_art->get_entry()->signal_focus_out_event().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_artikel_art_focus_out_event), false);
   combo_art->get_entry()->signal_changed().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_artikel_art_changed), false);
   combo_art2->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_art2_activate), false);
   combo_art2->get_entry()->signal_focus_out_event().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_art2_focus_out_event), false);
   combo_art2->get_entry()->signal_changed().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_art2_changed), false);
   entry_art->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_entry_art_activate), false);
   entry_art2->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_entry_art2_activate), false);
   button_art_speichern->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_button_art_speichern_clicked), false);
   button_ausruestung_loeschen->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_ausruestung_loeschen_clicked), false);
   preise_tree_neu->signal_leaf_selected().connect(SigC::slot(*this, &table_ausruestung_glade::on_preise_tree_neu_leaf_selected), false);
   preise_tree_neu->signal_drag_data_get().connect(SigC::slot(*this, &table_ausruestung_glade::on_preise_tree_neu_drag_data_get), false);
   checkbutton_ausruestung_geld->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_checkbutton_ausruestung_geld_toggled), false);
   togglebutton_unverkauflich->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_togglebutton_unverkauflich_toggled), false);
}

table_ausruestung_glade::~table_ausruestung_glade()
{  delete preise_tree_neu;
}
