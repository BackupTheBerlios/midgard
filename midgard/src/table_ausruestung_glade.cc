// generated 2006/8/14 13:10:55 CEST by christof@vesta.petig-baender.de
// using glademm V2.12.1
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage --gtkmmversion 2.4.0 midgard.glade
// for gtk 2.10.1 and gtkmm 2.4.0
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
#include <sigc++/bind.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //
#include "table_ausruestung_glade.hh"
#include <gtkmm/image.h>

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3

#include <gtkmm/toolbutton.h>
#else //
#include <gtkmm/button.h>
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#include <gtkmm/separatortoolitem.h>
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#include <gtkmm/expander.h>
#else //
#include <gtkmm/handlebox.h>
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#include <gtkmm/toolitem.h>
#endif //
#include <gtkmm/separator.h>
#include <gtkmm/table.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
#include <gtkmm/toolbar.h>
#include <gtkmm/treeview.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/paned.h>
#include <gtkmm/eventbox.h>

table_ausruestung_glade::table_ausruestung_glade(GlademmData *gmm_data
) : Gtk::Table(2, 2, false)
{  table_ausruestung = this;
   
   Gtk::Image *button_ausruestung_druck_img = Gtk::manage(new class Gtk::Image(MagusImage("PrintChar-trans-50.xpm")));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   Gtk::ToolButton *button_ausruestung_druck = Gtk::manage(new class Gtk::ToolButton(*button_ausruestung_druck_img, "Drucken"));
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   Gtk::SeparatorToolItem *separatortoolitem6 = Gtk::manage(new class Gtk::SeparatorToolItem());
#endif //
   Gtk::Image *togglebutton_gruppe_neu_img = Gtk::manage(new class Gtk::Image(MagusImage("New_Art-50.xpm")));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   togglebutton_gruppe_neu = Gtk::manage(new class Gtk::ToggleToolButton(*togglebutton_gruppe_neu_img, "Neue Art"));
#endif //
   
   Gtk::Image *togglebutton_artikel_neu_img = Gtk::manage(new class Gtk::Image(MagusImage("New_Art-50.xpm")));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   togglebutton_artikel_neu = Gtk::manage(new class Gtk::ToggleToolButton(*togglebutton_artikel_neu_img, "Neuer Artikel"));
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   
   Gtk::SeparatorToolItem *separatortoolitem7 = Gtk::manage(new class Gtk::SeparatorToolItem());
#endif //
   Gtk::Image *button_ausruestung_loeschen_img = Gtk::manage(new class Gtk::Image(MagusImage("Trash-32.xpm")));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   button_ausruestung_loeschen = Gtk::manage(new class Gtk::ToolButton(*button_ausruestung_loeschen_img, "Löschen"));
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   
   Gtk::SeparatorToolItem *separatortoolitem8 = Gtk::manage(new class Gtk::SeparatorToolItem());
#endif //
   Gtk::Image *checkbutton_ausruestung_geld_img = Gtk::manage(new class Gtk::Image(MagusImage("Money-50.xpm")));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   checkbutton_ausruestung_geld = Gtk::manage(new class Gtk::ToggleToolButton(*checkbutton_ausruestung_geld_img, "Mit Geld\n"
		"ausrüsten"));
#endif //
   
   Gtk::Image *togglebutton_unverkauflich_img = Gtk::manage(new class Gtk::Image(MagusImage("Angeb_Sicht-32.xpm")));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   togglebutton_unverkauflich = Gtk::manage(new class Gtk::ToggleToolButton(*togglebutton_unverkauflich_img, "Unverkäufliches\n"
		"anzeigen"));
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   
   Gtk::SeparatorToolItem *separatortoolitem9 = Gtk::manage(new class Gtk::SeparatorToolItem());
#endif //
   label_golda = Gtk::manage(new class Gtk::Label("0"));
   
   Gtk::Label *label675 = Gtk::manage(new class Gtk::Label("Gold"));
   Gtk::Frame *frame81 = Gtk::manage(new class Gtk::Frame());
   label_silbera = Gtk::manage(new class Gtk::Label("0"));
   
   Gtk::Label *label676 = Gtk::manage(new class Gtk::Label("Silber"));
   Gtk::Frame *frame82 = Gtk::manage(new class Gtk::Frame());
   label_kupfera = Gtk::manage(new class Gtk::Label("0"));
   
   Gtk::Label *label677 = Gtk::manage(new class Gtk::Label("Kupfer"));
   Gtk::Frame *frame83 = Gtk::manage(new class Gtk::Frame());
   Gtk::HBox *hbox106 = Gtk::manage(new class Gtk::HBox(false, 0));
   label_geld = Gtk::manage(new class Gtk::Label("Geld"));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   
   Gtk::Expander *expander1 = Gtk::manage(new class Gtk::Expander());
#else //
   Gtk::HandleBox *expander1 = Gtk::manage(new class Gtk::HandleBox());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   Gtk::ToolItem *toolitem19 = Gtk::manage(new class Gtk::ToolItem());
#endif //
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
   Gtk::Frame *frame117 = Gtk::manage(new class Gtk::Frame());
   label_last = Gtk::manage(new class Gtk::Label("Last"));
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   
   Gtk::Expander *expander2 = Gtk::manage(new class Gtk::Expander());
#else //
   Gtk::HandleBox *expander2 = Gtk::manage(new class Gtk::HandleBox());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   Gtk::ToolItem *toolitem24 = Gtk::manage(new class Gtk::ToolItem());
#endif //
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
   combo_art = Gtk::manage(new class Gtk::Combo());
   combo_art2 = Gtk::manage(new class Gtk::Combo());
   
   Gtk::Image *pixmap188 = Gtk::manage(new class Gtk::Image(MagusImage("SaveChar-trans-50.xpm")));
   Gtk::Label *label650 = Gtk::manage(new class Gtk::Label("Artikel\n"
		"speichern"));
   Gtk::HBox *hbox102 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_artikel_speichern = Gtk::manage(new class Gtk::Button());
   entry_beschreibung = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label689 = Gtk::manage(new class Gtk::Label("Beschreibung des Artikels (optional)"));
   Gtk::Frame *frame120 = Gtk::manage(new class Gtk::Frame());
   table_artikel = Gtk::manage(new class Gtk::Table(2, 2, false));
   
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
   scrolledwindow_ausruestung = Gtk::manage(new class Gtk::ScrolledWindow());
   
   Gtk::Table *table93 = Gtk::manage(new class Gtk::Table(2, 2, false));
   preise_tree_neu = new class SimpleTree(9);
   
   Gtk::ScrolledWindow *scrolledwindow66 = Gtk::manage(new class Gtk::ScrolledWindow());
   Gtk::Table *table94 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::VPaned *vpaned11 = Gtk::manage(new class Gtk::VPaned());
   Gtk::EventBox *eventbox25 = Gtk::manage(new class Gtk::EventBox());
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*button_ausruestung_druck);
#else //
   
   
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::ButtonElem("Drucken", *button_ausruestung_druck_img, Gtk::Toolbar_Helpers::Callback0()));
   Gtk::Button *button_ausruestung_druck = static_cast<Gtk::Button *>(toolbar39->tools().back().get_widget());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*separatortoolitem6);
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Space());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*togglebutton_gruppe_neu);
#else //
   
   
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::ToggleElem("Neue Art", *togglebutton_gruppe_neu_img, Gtk::Toolbar_Helpers::Callback0()));
   togglebutton_gruppe_neu = static_cast<Gtk::ToggleButton *>(toolbar39->tools().back().get_widget());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*togglebutton_artikel_neu);
#else //
   
   
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::ToggleElem("Neuer Artikel", *togglebutton_artikel_neu_img, Gtk::Toolbar_Helpers::Callback0()));
   togglebutton_artikel_neu = static_cast<Gtk::ToggleButton *>(toolbar39->tools().back().get_widget());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*separatortoolitem7);
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Space());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*button_ausruestung_loeschen);
#else //
   
   
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::ButtonElem("Löschen", *button_ausruestung_loeschen_img, Gtk::Toolbar_Helpers::Callback0()));
   button_ausruestung_loeschen = static_cast<Gtk::Button *>(toolbar39->tools().back().get_widget());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*separatortoolitem8);
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Space());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*checkbutton_ausruestung_geld);
#else //
   
   
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::ToggleElem("Mit Geld\n"
		"ausrüsten", *checkbutton_ausruestung_geld_img, Gtk::Toolbar_Helpers::Callback0()));
   checkbutton_ausruestung_geld = static_cast<Gtk::ToggleButton *>(toolbar39->tools().back().get_widget());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*togglebutton_unverkauflich);
#else //
   
   
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::ToggleElem("Unverkäufliches\n"
		"anzeigen", *togglebutton_unverkauflich_img, Gtk::Toolbar_Helpers::Callback0()));
   togglebutton_unverkauflich = static_cast<Gtk::ToggleButton *>(toolbar39->tools().back().get_widget());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*separatortoolitem9);
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Space());
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*toolitem19);
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Element(*expander1));
   
   Gtk::Widget *toolitem19 = toolbar39->tools().back().get_widget();
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->append(*toolitem24);
#else //
   toolbar39->tools().push_back(Gtk::Toolbar_Helpers::Element(*expander2));
   
   Gtk::Widget *toolitem24 = toolbar39->tools().back().get_widget();
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   _tooltips.set_tip(*button_ausruestung_druck, "Drucken (alles)", "");
   button_ausruestung_druck->set_homogeneous(true);
   button_ausruestung_druck->set_expand(false);
   button_ausruestung_druck->set_tooltip(_tooltips, "Drucken (alles)");
#endif //
   button_ausruestung_druck_img->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem6->set_homogeneous(false);
   separatortoolitem6->set_expand(false);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   _tooltips.set_tip(*togglebutton_gruppe_neu, "neue Kategorie hinzufügen", "");
   togglebutton_gruppe_neu->set_homogeneous(true);
   togglebutton_gruppe_neu->set_expand(false);
   togglebutton_gruppe_neu->set_tooltip(_tooltips, "neue Kategorie hinzufügen");
#endif //
   togglebutton_gruppe_neu_img->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   _tooltips.set_tip(*togglebutton_artikel_neu, "neuer Gegenstand", "");
   togglebutton_artikel_neu->set_homogeneous(true);
   togglebutton_artikel_neu->set_expand(false);
   togglebutton_artikel_neu->set_tooltip(_tooltips, "neuer Gegenstand");
#endif //
   togglebutton_artikel_neu_img->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem7->set_homogeneous(false);
   separatortoolitem7->set_expand(false);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   _tooltips.set_tip(*button_ausruestung_loeschen, "löschen", "");
   button_ausruestung_loeschen->set_homogeneous(false);
   button_ausruestung_loeschen->set_expand(false);
   button_ausruestung_loeschen->set_tooltip(_tooltips, "löschen");
#endif //
   button_ausruestung_loeschen_img->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem8->set_homogeneous(false);
   separatortoolitem8->set_expand(false);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   _tooltips.set_tip(*checkbutton_ausruestung_geld, "Geld verbrauchen", "");
   checkbutton_ausruestung_geld->set_homogeneous(false);
   checkbutton_ausruestung_geld->set_expand(false);
   checkbutton_ausruestung_geld->set_tooltip(_tooltips, "Geld verbrauchen");
#endif //
   checkbutton_ausruestung_geld_img->show();
   checkbutton_ausruestung_geld->set_active(true);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   _tooltips.set_tip(*togglebutton_unverkauflich, "unverkäufliches anbieten", "");
   togglebutton_unverkauflich->set_homogeneous(true);
   togglebutton_unverkauflich->set_expand(false);
   togglebutton_unverkauflich->set_tooltip(_tooltips, "unverkäufliches anbieten");
#endif //
   togglebutton_unverkauflich_img->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem9->set_homogeneous(false);
   separatortoolitem9->set_expand(false);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
#endif //
   label_golda->set_justify(Gtk::JUSTIFY_CENTER);
   label_golda->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_golda->set_width_chars(-1);
   label675->set_justify(Gtk::JUSTIFY_LEFT);
   label675->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label675->set_width_chars(-1);
   frame81->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame81->set_label_align(0,0.5);
   frame81->add(*label_golda);
   frame81->set_label_widget(*label675);
   label_silbera->set_justify(Gtk::JUSTIFY_CENTER);
   label_silbera->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_silbera->set_width_chars(-1);
   label676->set_justify(Gtk::JUSTIFY_LEFT);
   label676->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label676->set_width_chars(-1);
   frame82->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame82->set_label_align(0,0.5);
   frame82->add(*label_silbera);
   frame82->set_label_widget(*label676);
   label_kupfera->set_justify(Gtk::JUSTIFY_CENTER);
   label_kupfera->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_kupfera->set_width_chars(-1);
   label677->set_justify(Gtk::JUSTIFY_LEFT);
   label677->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label677->set_width_chars(-1);
   frame83->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame83->set_label_align(0,0.5);
   frame83->add(*label_kupfera);
   frame83->set_label_widget(*label677);
   hbox106->pack_start(*frame81);
   hbox106->pack_start(*frame82);
   hbox106->pack_start(*frame83);
   label_geld->set_justify(Gtk::JUSTIFY_LEFT);
   label_geld->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_geld->set_width_chars(-1);
   expander1->set_flags(Gtk::CAN_FOCUS);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   expander1->set_spacing(0);
#endif //
   expander1->add(*hbox106);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   expander1->set_label_widget(*label_geld);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolitem19->set_homogeneous(false);
   toolitem19->set_expand(false);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolitem19->add(*expander1);
#endif //
   label_gesamtlast->set_alignment(0,0.5);
   label_gesamtlast->set_justify(Gtk::JUSTIFY_CENTER);
   label_gesamtlast->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_gesamtlast->set_width_chars(-1);
   label629->set_alignment(0,0.5);
   label629->set_padding(2,0);
   label629->set_justify(Gtk::JUSTIFY_CENTER);
   label629->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label629->set_width_chars(-1);
   label630->set_alignment(0,0.5);
   label630->set_padding(2,0);
   label630->set_justify(Gtk::JUSTIFY_CENTER);
   label630->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label630->set_width_chars(-1);
   label->set_alignment(0,0.5);
   label->set_padding(2,0);
   label->set_justify(Gtk::JUSTIFY_CENTER);
   label->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label->set_width_chars(-1);
   label632->set_alignment(0,0.5);
   label632->set_padding(2,0);
   label632->set_justify(Gtk::JUSTIFY_CENTER);
   label632->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label632->set_width_chars(-1);
   label_normallast->set_alignment(1,0.5);
   label_normallast->set_justify(Gtk::JUSTIFY_CENTER);
   label_normallast->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_normallast->set_width_chars(-1);
   label_hoechstlast->set_alignment(1,0.5);
   label_hoechstlast->set_justify(Gtk::JUSTIFY_CENTER);
   label_hoechstlast->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_hoechstlast->set_width_chars(-1);
   label_schublast->set_alignment(1,0.5);
   label_schublast->set_justify(Gtk::JUSTIFY_CENTER);
   label_schublast->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_schublast->set_width_chars(-1);
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
   frame117->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame117->set_label_align(0,0.5);
   frame117->add(*table178);
   label_last->set_justify(Gtk::JUSTIFY_LEFT);
   label_last->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label_last->set_width_chars(-1);
   expander2->set_flags(Gtk::CAN_FOCUS);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   expander2->set_spacing(0);
#endif //
   expander2->add(*frame117);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   expander2->set_label_widget(*label_last);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolitem24->set_homogeneous(false);
   toolitem24->set_expand(false);
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolitem24->add(*expander2);
#endif //
   toolbar39->set_toolbar_style(Gtk::TOOLBAR_BOTH);
   toolbar39->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolbar39->set_show_arrow(false);
#endif //
   label506->set_alignment(0,0.5);
   label506->set_justify(Gtk::JUSTIFY_CENTER);
   label506->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label506->set_width_chars(-1);
   label507->set_alignment(0,0.5);
   label507->set_justify(Gtk::JUSTIFY_CENTER);
   label507->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label507->set_width_chars(-1);
   label508->set_alignment(0,0.5);
   label508->set_justify(Gtk::JUSTIFY_CENTER);
   label508->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label508->set_width_chars(-1);
   label511->set_alignment(0,0.5);
   label511->set_justify(Gtk::JUSTIFY_CENTER);
   label511->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label511->set_width_chars(-1);
   label527->set_alignment(0,0.5);
   label527->set_justify(Gtk::JUSTIFY_CENTER);
   label527->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label527->set_width_chars(-1);
   entry_name->set_flags(Gtk::CAN_FOCUS);
   entry_name->set_max_length(0);
   entry_name->set_text("");
   entry_name->set_width_chars(10);
   label509->set_alignment(0,0.5);
   label509->set_justify(Gtk::JUSTIFY_CENTER);
   label509->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label509->set_width_chars(-1);
   label649->set_alignment(0,0.5);
   label649->set_justify(Gtk::JUSTIFY_CENTER);
   label649->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label649->set_width_chars(-1);
   combo_region->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_region->get_entry()->set_editable(false);
   combo_region->get_entry()->set_max_length(0);
   combo_region->get_entry()->set_text("");
   combo_region->get_entry()->set_width_chars(10);
   combo_region->set_sensitive(false);
   {  
      
      const char * const items[] = { "", "", 0 };
      combo_region->set_popdown_strings(items);
   }
   combo_region->get_entry()->set_text("");
   combo_einheit->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_einheit->get_entry()->set_editable(false);
   combo_einheit->get_entry()->set_max_length(0);
   combo_einheit->get_entry()->set_text("");
   combo_einheit->get_entry()->set_width_chars(10);
   {  
      
      const char * const items[] = { "", "", "", "", 0 };
      combo_einheit->set_popdown_strings(items);
   }
   combo_einheit->get_entry()->set_text("");
   spinbutton_preis->set_flags(Gtk::CAN_FOCUS);
   spinbutton_preis->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbutton_preis->set_digits(1);
   spinbutton_gewicht->set_flags(Gtk::CAN_FOCUS);
   spinbutton_gewicht->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbutton_gewicht->set_digits(2);
   combo_art->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_art->get_entry()->set_editable(false);
   combo_art->get_entry()->set_max_length(0);
   combo_art->get_entry()->set_text("");
   combo_art->get_entry()->set_width_chars(10);
   {  
      
      const char * const items[] = { "", "", 0 };
      combo_art->set_popdown_strings(items);
   }
   combo_art->get_entry()->set_text("");
   combo_art2->get_entry()->set_flags(Gtk::CAN_FOCUS);
   combo_art2->get_entry()->set_editable(false);
   combo_art2->get_entry()->set_max_length(0);
   combo_art2->get_entry()->set_text("");
   combo_art2->get_entry()->set_width_chars(10);
   {  
      
      const char * const items[] = { "", 0 };
      combo_art2->set_popdown_strings(items);
   }
   combo_art2->get_entry()->set_text("");
   label650->set_justify(Gtk::JUSTIFY_CENTER);
   label650->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label650->set_width_chars(-1);
   hbox102->pack_start(*pixmap188);
   hbox102->pack_start(*label650, Gtk::PACK_SHRINK, 0);
   button_artikel_speichern->set_flags(Gtk::CAN_FOCUS);
   _tooltips.set_tip(*button_artikel_speichern, "Gegenstand anlegen", "");
   button_artikel_speichern->set_relief(Gtk::RELIEF_NORMAL);
   button_artikel_speichern->add(*hbox102);
   entry_beschreibung->set_flags(Gtk::CAN_FOCUS);
   entry_beschreibung->set_max_length(0);
   entry_beschreibung->set_text("");
   label689->set_justify(Gtk::JUSTIFY_LEFT);
   label689->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label689->set_width_chars(-1);
   frame120->set_shadow_type(Gtk::SHADOW_NONE);
   frame120->set_label_align(0,0.5);
   frame120->add(*entry_beschreibung);
   frame120->set_label_widget(*label689);
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
   table_artikel->attach(*combo_art, 0, 1, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*combo_art2, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_artikel->attach(*button_artikel_speichern, 7, 8, 0, 3, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_artikel->attach(*frame120, 0, 7, 2, 3, Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 0);
   label503->set_alignment(0,0.5);
   label503->set_justify(Gtk::JUSTIFY_CENTER);
   label503->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label503->set_width_chars(-1);
   label504->set_alignment(0,0.5);
   label504->set_justify(Gtk::JUSTIFY_CENTER);
   label504->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label504->set_width_chars(-1);
   entry_art->set_flags(Gtk::CAN_FOCUS);
   entry_art->set_max_length(0);
   entry_art->set_text("");
   entry_art2->set_flags(Gtk::CAN_FOCUS);
   entry_art2->set_max_length(0);
   entry_art2->set_text("");
   entry_art2->set_width_chars(16);
   label651->set_justify(Gtk::JUSTIFY_CENTER);
   label651->set_ellipsize(Pango::ELLIPSIZE_NONE);
   label651->set_width_chars(-1);
   hbox103->pack_start(*pixmap189);
   hbox103->pack_start(*label651, Gtk::PACK_SHRINK, 0);
   button_art_speichern->set_flags(Gtk::CAN_FOCUS);
   _tooltips.set_tip(*button_art_speichern, "Kategorie anlegen", "");
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
   table81->attach(*table_gruppe, 0, 1, 1, 2, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 0, 0);
   handlebox7->set_shadow_type(Gtk::SHADOW_OUT);
   handlebox7->set_handle_position(Gtk::POS_LEFT);
   handlebox7->set_snap_edge(Gtk::POS_TOP);
   handlebox7->add(*table81);
   scrolledwindow_ausruestung->set_shadow_type(Gtk::SHADOW_NONE);
   scrolledwindow_ausruestung->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow_ausruestung->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   table93->set_row_spacings(0);
   table93->set_col_spacings(0);
   table93->attach(*scrolledwindow_ausruestung, 0, 1, 0, 3, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   scrolledwindow66->set_shadow_type(Gtk::SHADOW_NONE);
   scrolledwindow66->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow66->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow66->add(*preise_tree_neu);
   table94->set_row_spacings(0);
   table94->set_col_spacings(0);
   table94->attach(*scrolledwindow66, 0, 1, 0, 1, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   vpaned11->set_position(264);
   vpaned11->pack1(*table93, Gtk::SHRINK);
   vpaned11->pack2(*table94, Gtk::EXPAND|Gtk::SHRINK);
   _tooltips.set_tip(*eventbox25, "Artikel unten anwählen um ihn zu kaufen, dann mit der Maus oben umordnen", "");
   eventbox25->add(*vpaned11);
   table_ausruestung->set_row_spacings(0);
   table_ausruestung->set_col_spacings(0);
   table_ausruestung->attach(*handlebox7, 0, 2, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
   table_ausruestung->attach(*eventbox25, 0, 2, 1, 2, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   button_ausruestung_druck->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem6->show();
#endif //
   togglebutton_gruppe_neu->show();
   togglebutton_artikel_neu->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem7->show();
#endif //
   button_ausruestung_loeschen->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem8->show();
#endif //
   checkbutton_ausruestung_geld->show();
   togglebutton_unverkauflich->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   separatortoolitem9->show();
#endif //
   label_golda->show();
   label675->show();
   frame81->show();
   label_silbera->show();
   label676->show();
   frame82->show();
   label_kupfera->show();
   label677->show();
   frame83->show();
   hbox106->show();
   label_geld->show();
   expander1->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolitem19->show();
#endif //
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
   frame117->show();
   label_last->show();
   expander2->show();
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>=3
   toolitem24->show();
#endif //
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
   combo_art->show();
   combo_art2->show();
   pixmap188->show();
   label650->show();
   hbox102->show();
   button_artikel_speichern->show();
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
   scrolledwindow_ausruestung->show();
   table93->show();
   preise_tree_neu->show();
   scrolledwindow66->show();
   table94->show();
   vpaned11->show();
   eventbox25->show();
   table_ausruestung->show();
   button_ausruestung_druck->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_button_ausruestung_druck), false);
   togglebutton_gruppe_neu->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_togglebutton_gruppe_neu_toggled), false);
   togglebutton_artikel_neu->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_togglebutton_artikel_neu_toggled), false);
   button_ausruestung_loeschen->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_ausruestung_loeschen_clicked), false);
   checkbutton_ausruestung_geld->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_checkbutton_ausruestung_geld_toggled), false);
   togglebutton_unverkauflich->signal_toggled().connect(SigC::slot(*this, &table_ausruestung_glade::on_togglebutton_unverkauflich_toggled), false);
   entry_name->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_entry_name_activate), false);
   combo_region->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_region_activate), false);
   combo_einheit->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_einheit_activate), false);
   combo_einheit->get_entry()->signal_changed().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_einheit_changed), false);
   spinbutton_preis->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_spinbutton_preis_activate), true);
   spinbutton_gewicht->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_spinbutton_gewicht_activate), true);
   combo_art->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_artikel_art_activate), false);
   combo_art->get_entry()->signal_focus_out_event().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_artikel_art_focus_out_event), false);
   combo_art->get_entry()->signal_changed().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_artikel_art_changed), false);
   combo_art2->get_entry()->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_art2_activate), false);
   combo_art2->get_entry()->signal_focus_out_event().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_art2_focus_out_event), false);
   combo_art2->get_entry()->signal_changed().connect(SigC::slot(*this, &table_ausruestung_glade::on_combo_entry_art2_changed), false);
   button_artikel_speichern->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_button_artikel_speichern_clicked), false);
   entry_art->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_entry_art_activate), false);
   entry_art2->signal_activate().connect(SigC::slot(*this, &table_ausruestung_glade::on_entry_art2_activate), false);
   button_art_speichern->signal_clicked().connect(SigC::slot(*this, &table_ausruestung_glade::on_button_art_speichern_clicked), false);
   preise_tree_neu->signal_leaf_selected().connect(SigC::slot(*this, &table_ausruestung_glade::on_preise_tree_neu_leaf_selected));
}

table_ausruestung_glade::~table_ausruestung_glade()
{  delete preise_tree_neu;
}
