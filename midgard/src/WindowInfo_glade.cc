// generated 2005/4/27 10:13:17 CEST by thoma@Tiger.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage --gtkmmversion 2.4.0 midgard.glade
// for gtk 2.6.2 and gtkmm 2.4.0
//
// Please modify the corresponding derived classes in ./src/WindowInfo.cc


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
#include "WindowInfo_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/image.h>

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/table.h>

WindowInfo_glade::WindowInfo_glade(
) : Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{  
   
   Gtk::Window *WindowInfo = this;
   gmm_data = new GlademmData(get_accel_group());
   
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
   table_schliessen = Gtk::manage(new class Gtk::Table(2, 2, true));
   LogWin = new class logwin();
   
   Gtk::ScrolledWindow *scrolledwindow88 = Gtk::manage(new class Gtk::ScrolledWindow());
   Gtk::Table *table133 = Gtk::manage(new class Gtk::Table(2, 2, false));
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
   table_schliessen->set_row_spacings(0);
   table_schliessen->set_col_spacings(10);
   table_schliessen->attach(*button_info_ok, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_schliessen->attach(*button_erase, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   scrolledwindow88->set_flags(Gtk::CAN_FOCUS);
   scrolledwindow88->set_shadow_type(Gtk::SHADOW_NONE);
   scrolledwindow88->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow88->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow88->add(*LogWin);
   table133->set_row_spacings(0);
   table133->set_col_spacings(0);
   table133->attach(*table_schliessen, 0, 1, 9, 10, Gtk::AttachOptions(), Gtk::AttachOptions(), 0, 0);
   table133->attach(*scrolledwindow88, 0, 1, 0, 9, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   WindowInfo->set_title("Info");
   WindowInfo->set_default_size(677,422);
   WindowInfo->set_modal(false);
   WindowInfo->property_window_position().set_value(Gtk::WIN_POS_NONE);
   WindowInfo->set_resizable(true);
   WindowInfo->property_destroy_with_parent().set_value(false);
   WindowInfo->add(*table133);
   pixmap144->show();
   label564->show();
   hbox68->show();
   button_info_ok->show();
   pixmap143->show();
   label563->show();
   hbox67->show();
   button_erase->show();
   table_schliessen->show();
   LogWin->show();
   scrolledwindow88->show();
   table133->show();
   button_info_ok->signal_clicked().connect(SigC::slot(*this, &WindowInfo_glade::on_button_abbrechen_clicked), false);
   button_erase->signal_clicked().connect(SigC::slot(*this, &WindowInfo_glade::on_button_erase_clicked), false);
   WindowInfo->signal_delete_event().connect(SigC::slot(*this, &WindowInfo_glade::on_WindowInfo_delete_event), false);
}

WindowInfo_glade::~WindowInfo_glade()
{  delete LogWin;
   delete gmm_data;
}
