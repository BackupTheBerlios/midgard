// generated 2003/4/23 14:25:54 CEST by christof@puck.petig-baender.de
// using glademm V1.1.3g_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage midgard.glade
// for gtk 2.2.1 and gtkmm 2.2.1
//
// Please modify the corresponding derived classes in ./src/WindowInfo.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
#include "WindowInfo_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/image.h>

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

#include <gtkmm/label.h>
#include <gtkmm/box.h>

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

#include <gtkmm/table.h>

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

WindowInfo_glade::WindowInfo_glade(
) : Gtk::Window(Gtk::WINDOW_POPUP)
{  
   
   Gtk::Window *WindowInfo = this;
   gmm_data = new GlademmData(get_accel_group());
   LogWin = new class logwin();
   
   Gtk::Image *pixmap_ja = Gtk::manage(new class Gtk::Image(MagusImage("Excl-32.xpm")));
   Gtk::Label *label570 = Gtk::manage(new class Gtk::Label("Ja"));
   Gtk::HBox *hbox73 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_bestaetigen = Gtk::manage(new class Gtk::Button());
   
   Gtk::Image *pixmap_nein = Gtk::manage(new class Gtk::Image(MagusImage("Nein-32.xpm")));
   Gtk::Label *label569 = Gtk::manage(new class Gtk::Label("Nein"));
   Gtk::HBox *hbox72 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_abbrechen = Gtk::manage(new class Gtk::Button());
   table_bestaetigen = Gtk::manage(new class Gtk::Table(2, 2, true));
   
   Gtk::Image *pixmap144 = Gtk::manage(new class Gtk::Image(MagusImage("Yellow-Dice-trans-50.xpm")));
   Gtk::Label *label564 = Gtk::manage(new class Gtk::Label("Fenster\n"
		"schließen"));
   Gtk::HBox *hbox68 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_info_ok = Gtk::manage(new class Gtk::Button());
   
   Gtk::Image *pixmap143 = Gtk::manage(new class Gtk::Image(MagusImage("Clear-32.xpm")));
   Gtk::Label *label563 = Gtk::manage(new class Gtk::Label("Textfeld\n"
		"löschen"));
   Gtk::HBox *hbox67 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_erase = Gtk::manage(new class Gtk::Button());
   
   Gtk::Image *pixmap187 = Gtk::manage(new class Gtk::Image(MagusImage("Angeb_Sicht-32.xpm")));
   Gtk::Label *label648 = Gtk::manage(new class Gtk::Label("Status"));
   Gtk::HBox *hbox101 = Gtk::manage(new class Gtk::HBox(false, 0));
   button_status = Gtk::manage(new class Gtk::ToggleButton());
   table_schliessen = Gtk::manage(new class Gtk::Table(2, 2, true));
   frame_auswahl = Gtk::manage(new class Gtk::Frame());
   
   Gtk::Table *table125 = Gtk::manage(new class Gtk::Table(2, 2, false));
   LogWin_Status = new class logwin();
   scrolledwindow_status = Gtk::manage(new class Gtk::ScrolledWindow());
   pixmap_arkanum = Gtk::manage(new class Gtk::Image(MagusImage("Gross_ark_pre.xpm")));
   
   Gtk::Table *table133 = Gtk::manage(new class Gtk::Table(2, 2, false));
   pixmap_ja->set_alignment(0.5,0.5);
   pixmap_ja->set_padding(0,0);
   label570->set_alignment(0.5,0.5);
   label570->set_padding(0,0);
   label570->set_justify(Gtk::JUSTIFY_CENTER);
   label570->set_line_wrap(false);
   label570->set_use_markup(false);
   label570->set_selectable(false);
   hbox73->pack_start(*pixmap_ja);
   hbox73->pack_start(*label570);
   button_bestaetigen->set_flags(Gtk::CAN_FOCUS);
   button_bestaetigen->set_relief(Gtk::RELIEF_NORMAL);
   button_bestaetigen->add(*hbox73);
   pixmap_nein->set_alignment(0.5,0.5);
   pixmap_nein->set_padding(0,0);
   label569->set_alignment(0.5,0.5);
   label569->set_padding(0,0);
   label569->set_justify(Gtk::JUSTIFY_CENTER);
   label569->set_line_wrap(false);
   label569->set_use_markup(false);
   label569->set_selectable(false);
   hbox72->pack_start(*pixmap_nein);
   hbox72->pack_start(*label569);
   button_abbrechen->set_flags(Gtk::CAN_FOCUS);
   button_abbrechen->set_relief(Gtk::RELIEF_NORMAL);
   button_abbrechen->add(*hbox72);
   table_bestaetigen->set_row_spacings(0);
   table_bestaetigen->set_col_spacings(10);
   table_bestaetigen->attach(*button_bestaetigen, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_bestaetigen->attach(*button_abbrechen, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   pixmap144->set_alignment(0.5,0.5);
   pixmap144->set_padding(0,0);
   label564->set_alignment(0.5,0.5);
   label564->set_padding(0,0);
   label564->set_justify(Gtk::JUSTIFY_CENTER);
   label564->set_line_wrap(false);
   label564->set_use_markup(false);
   label564->set_selectable(false);
   hbox68->pack_start(*pixmap144);
   hbox68->pack_start(*label564, Gtk::PACK_SHRINK, 0);
   button_info_ok->set_flags(Gtk::CAN_FOCUS);
   button_info_ok->set_relief(Gtk::RELIEF_NORMAL);
   button_info_ok->add(*hbox68);
   pixmap143->set_alignment(0.5,0.5);
   pixmap143->set_padding(0,0);
   label563->set_alignment(0.5,0.5);
   label563->set_padding(0,0);
   label563->set_justify(Gtk::JUSTIFY_CENTER);
   label563->set_line_wrap(false);
   label563->set_use_markup(false);
   label563->set_selectable(false);
   hbox67->pack_start(*pixmap143);
   hbox67->pack_start(*label563, Gtk::PACK_SHRINK, 0);
   button_erase->set_flags(Gtk::CAN_FOCUS);
   button_erase->set_relief(Gtk::RELIEF_NORMAL);
   button_erase->add(*hbox67);
   pixmap187->set_alignment(0.5,0.5);
   pixmap187->set_padding(0,0);
   label648->set_alignment(0.5,0.5);
   label648->set_padding(0,0);
   label648->set_justify(Gtk::JUSTIFY_CENTER);
   label648->set_line_wrap(false);
   label648->set_use_markup(false);
   label648->set_selectable(false);
   hbox101->pack_start(*pixmap187);
   hbox101->pack_start(*label648, Gtk::PACK_SHRINK, 0);
   button_status->set_flags(Gtk::CAN_FOCUS);
   button_status->set_relief(Gtk::RELIEF_NORMAL);
   button_status->set_active(false);
   button_status->add(*hbox101);
   table_schliessen->set_row_spacings(0);
   table_schliessen->set_col_spacings(10);
   table_schliessen->attach(*button_info_ok, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_schliessen->attach(*button_erase, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_schliessen->attach(*button_status, 2, 3, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   frame_auswahl->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame_auswahl->set_label_align(0,0.5);
   table125->set_row_spacings(0);
   table125->set_col_spacings(0);
   table125->attach(*table_bestaetigen, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);
   table125->attach(*table_schliessen, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
   table125->attach(*frame_auswahl, 0, 1, 2, 3, Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   scrolledwindow_status->set_shadow_type(Gtk::SHADOW_NONE);
   scrolledwindow_status->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow_status->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow_status->add(*LogWin_Status);
   pixmap_arkanum->set_alignment(0.5,0.5);
   pixmap_arkanum->set_padding(0,0);
   table133->set_row_spacings(0);
   table133->set_col_spacings(0);
   table133->attach(*LogWin, 0, 1, 0, 9, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   table133->attach(*table125, 0, 1, 9, 10, Gtk::AttachOptions(), Gtk::AttachOptions(), 0, 0);
   table133->attach(*scrolledwindow_status, 0, 1, 10, 11, Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 0);
   table133->attach(*pixmap_arkanum, 1, 2, 0, 11, Gtk::AttachOptions(), Gtk::AttachOptions(), 0, 0);
   WindowInfo->set_title("Info");
   WindowInfo->set_default_size(677,422);
   WindowInfo->set_modal(false);
   WindowInfo->property_window_position().set_value(Gtk::WIN_POS_CENTER);
   WindowInfo->set_resizable(true);
   WindowInfo->property_destroy_with_parent().set_value(false);
   WindowInfo->add(*table133);
   LogWin->show();
   pixmap_ja->show();
   label570->show();
   hbox73->show();
   button_bestaetigen->show();
   pixmap_nein->show();
   label569->show();
   hbox72->show();
   button_abbrechen->show();
   table_bestaetigen->show();
   pixmap144->show();
   label564->show();
   hbox68->show();
   button_info_ok->show();
   pixmap143->show();
   label563->show();
   hbox67->show();
   button_erase->show();
   pixmap187->show();
   label648->show();
   hbox101->show();
   button_status->show();
   table_schliessen->show();
   frame_auswahl->show();
   table125->show();
   LogWin_Status->show();
   scrolledwindow_status->show();
   pixmap_arkanum->show();
   table133->show();
   button_bestaetigen->signal_clicked().connect(SigC::slot(*this, &WindowInfo_glade::on_button_bestaetigen_clicked));
   button_abbrechen->signal_clicked().connect(SigC::slot(*this, &WindowInfo_glade::on_button_abbrechen_clicked));
   button_info_ok->signal_clicked().connect(SigC::slot(*this, &WindowInfo_glade::on_button_abbrechen_clicked));
   button_erase->signal_clicked().connect(SigC::slot(*this, &WindowInfo_glade::on_button_erase_clicked));
   button_status->signal_toggled().connect(SigC::slot(*this, &WindowInfo_glade::on_button_status_toggled));
   WindowInfo->signal_delete_event().connect(SigC::slot(*this, &WindowInfo_glade::on_WindowInfo_delete_event));
}

WindowInfo_glade::~WindowInfo_glade()
{  delete LogWin;
   delete LogWin_Status;
   delete gmm_data;
}
