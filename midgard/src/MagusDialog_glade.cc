// generated 2003/12/16 0:10:52 CET by christof@puck.petig-baender.de
// using glademm V2.0.0c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage midgard.glade
// for gtk 2.2.4 and gtkmm 2.2.8
//
// Please modify the corresponding derived classes in ./src/MagusDialog.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
#include "MagusDialog_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/image.h>

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/buttonbox.h>

MagusDialog_glade::MagusDialog_glade(
)
{  
   
   Gtk::Dialog *MagusDialog = this;
   gmm_data = new GlademmData(get_accel_group());
   
   Gtk::Image *image11 = Gtk::manage(new class Gtk::Image(MagusImage("Nein-32.xpm")));
   text_no = Gtk::manage(new class Gtk::Label("Nein"));
   
   Gtk::HBox *hbox105 = Gtk::manage(new class Gtk::HBox(false, 0));
   Gtk::Button *cancelbutton1 = Gtk::manage(new class Gtk::Button());
   Gtk::Image *image10 = Gtk::manage(new class Gtk::Image(MagusImage("Excl-32.xpm")));
   text_yes = Gtk::manage(new class Gtk::Label("Ja"));
   
   Gtk::HBox *hbox104 = Gtk::manage(new class Gtk::HBox(false, 0));
   Gtk::Button *okbutton1 = Gtk::manage(new class Gtk::Button());
   Gtk::Image *pixmap144 = Gtk::manage(new class Gtk::Image(MagusImage("Yellow-Dice-trans-50.xpm")));
   Gtk::Label *label564 = Gtk::manage(new class Gtk::Label("Fenster\n"
		"schließen"));
   Gtk::HBox *hbox68 = Gtk::manage(new class Gtk::HBox(false, 0));
   Gtk::Button *button12 = Gtk::manage(new class Gtk::Button());
   text = Gtk::manage(new class Gtk::Label("label699"));
   image11->set_alignment(0.5,0.5);
   image11->set_padding(0,0);
   text_no->set_alignment(0.5,0.5);
   text_no->set_padding(0,0);
   text_no->set_justify(Gtk::JUSTIFY_CENTER);
   text_no->set_line_wrap(false);
   text_no->set_use_markup(false);
   text_no->set_selectable(false);
   hbox105->pack_start(*image11);
   hbox105->pack_start(*text_no);
   cancelbutton1->set_flags(Gtk::CAN_FOCUS);
   cancelbutton1->set_relief(Gtk::RELIEF_NORMAL);
   cancelbutton1->add(*hbox105);
   image10->set_alignment(0.5,0.5);
   image10->set_padding(0,0);
   text_yes->set_alignment(0.5,0.5);
   text_yes->set_padding(0,0);
   text_yes->set_justify(Gtk::JUSTIFY_CENTER);
   text_yes->set_line_wrap(false);
   text_yes->set_use_markup(false);
   text_yes->set_selectable(false);
   hbox104->pack_start(*image10);
   hbox104->pack_start(*text_yes);
   okbutton1->set_flags(Gtk::CAN_FOCUS);
   okbutton1->set_relief(Gtk::RELIEF_NORMAL);
   okbutton1->add(*hbox104);
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
   button12->set_flags(Gtk::CAN_FOCUS);
   button12->set_relief(Gtk::RELIEF_NORMAL);
   button12->add(*hbox68);
   MagusDialog->get_action_area()->property_layout_style().set_value(Gtk::BUTTONBOX_END);
   text->set_flags(Gtk::CAN_FOCUS);
   text->set_alignment(0.5,0.5);
   text->set_padding(0,0);
   text->set_justify(Gtk::JUSTIFY_CENTER);
   text->set_line_wrap(true);
   text->set_use_markup(false);
   text->set_selectable(true);
   MagusDialog->get_vbox()->set_homogeneous(false);
   MagusDialog->get_vbox()->set_spacing(0);
   MagusDialog->get_vbox()->pack_start(*text);
   MagusDialog->set_title("Frage");
   MagusDialog->set_default_size(677,422);
   MagusDialog->set_modal(true);
   MagusDialog->property_window_position().set_value(Gtk::WIN_POS_CENTER);
   MagusDialog->set_resizable(true);
   MagusDialog->property_destroy_with_parent().set_value(false);
   MagusDialog->set_has_separator(false);
   MagusDialog->add_action_widget(*cancelbutton1, -6);
   MagusDialog->add_action_widget(*okbutton1, -5);
   MagusDialog->add_action_widget(*button12, -7);
   image11->show();
   text_no->show();
   hbox105->show();
   cancelbutton1->show();
   image10->show();
   text_yes->show();
   hbox104->show();
   okbutton1->show();
   pixmap144->show();
   label564->show();
   hbox68->show();
   button12->show();
   text->show();
   MagusDialog->show();
   MagusDialog->signal_delete_event().connect(SigC::slot(*this, &MagusDialog_glade::on_WindowInfo_delete_event));
}

MagusDialog_glade::~MagusDialog_glade()
{  delete gmm_data;
}
