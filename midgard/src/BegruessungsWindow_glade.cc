// generated 2002/12/19 19:05:39 CET by christof@puck.petig-baender.de
// using glademm V1.1.3c
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- midgard.glade
// for gtk 2.0.9 and gtkmm 2.0.2
//
// Please modify the corresponding derived classes in ./src/BegruessungsWindow.cc

#include "config.h"
#include "BegruessungsWindow_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/image.h>
#include "../pixmaps/GnuHead-trans.xpm"
#include "../pixmaps/midgard_logo.xpm"
#include "../pixmaps/Tux-med.xpm"
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include "../pixmaps/EditChar-trans-50.xpm"
#include <gtkmm/button.h>
#include "../pixmaps/NewChar-trans-50.xpm"
#include "../pixmaps/ZF_G1-Char-32.xpm"
#include "../pixmaps/LoadChar-trans-50.xpm"
#include <gtkmm/separator.h>

BegruessungsWindow_glade::BegruessungsWindow_glade(
) : Gtk::Window(Gtk::WINDOW_POPUP)
{  
   
   Gtk::Window *BegruessungsWindow = this;
   _data = new GlademmData(get_accel_group());
   
   Glib::RefPtr<Gdk::Bitmap> _pixmap178_mask;
   Glib::RefPtr<Gdk::Pixmap> _pixmap178_pixmap = Gdk::Pixmap::create_from_xpm(get_default_colormap(), _pixmap178_mask, GnuHead_trans_xpm);
   Gtk::Image *pixmap178 = Gtk::manage(new class Gtk::Image(_pixmap178_pixmap, _pixmap178_mask));
   Glib::RefPtr<Gdk::Bitmap> _pixmap179_mask;
   Glib::RefPtr<Gdk::Pixmap> _pixmap179_pixmap = Gdk::Pixmap::create_from_xpm(get_default_colormap(), _pixmap179_mask, midgard_logo_xpm);
   Gtk::Image *pixmap179 = Gtk::manage(new class Gtk::Image(_pixmap179_pixmap, _pixmap179_mask));
   Glib::RefPtr<Gdk::Bitmap> _pixmap180_mask;
   Glib::RefPtr<Gdk::Pixmap> _pixmap180_pixmap = Gdk::Pixmap::create_from_xpm(get_default_colormap(), _pixmap180_mask, Tux_med_xpm);
   Gtk::Image *pixmap180 = Gtk::manage(new class Gtk::Image(_pixmap180_pixmap, _pixmap180_mask));
   Gtk::HBox *hbox100 = Gtk::manage(new class Gtk::HBox(false, 0));
   Gtk::Label *label641 = Gtk::manage(new class Gtk::Label("Einen neuen Abenteurer mit MAGUS erstellen."));
   Gtk::Label *label642 = Gtk::manage(new class Gtk::Label("Einen vorhandenen Abenteurer in MAGUS eingeben."));
   Gtk::Label *label643 = Gtk::manage(new class Gtk::Label("Einen Zufallsabenteurer (Grad 1) erstellen."));
   Gtk::Label *label644 = Gtk::manage(new class Gtk::Label("Einen Abenteurer aus einer Datei laden. "));
   Glib::RefPtr<Gdk::Bitmap> _pixmap182_mask;
   Glib::RefPtr<Gdk::Pixmap> _pixmap182_pixmap = Gdk::Pixmap::create_from_xpm(get_default_colormap(), _pixmap182_mask, EditChar_trans_50_xpm);
   Gtk::Image *pixmap182 = Gtk::manage(new class Gtk::Image(_pixmap182_pixmap, _pixmap182_mask));
   Gtk::Button *button_eingabe = Gtk::manage(new class Gtk::Button());
   Glib::RefPtr<Gdk::Bitmap> _pixmap181_mask;
   Glib::RefPtr<Gdk::Pixmap> _pixmap181_pixmap = Gdk::Pixmap::create_from_xpm(get_default_colormap(), _pixmap181_mask, NewChar_trans_50_xpm);
   Gtk::Image *pixmap181 = Gtk::manage(new class Gtk::Image(_pixmap181_pixmap, _pixmap181_mask));
   Gtk::Button *button_neu = Gtk::manage(new class Gtk::Button());
   Glib::RefPtr<Gdk::Bitmap> _pixmap186_mask;
   Glib::RefPtr<Gdk::Pixmap> _pixmap186_pixmap = Gdk::Pixmap::create_from_xpm(get_default_colormap(), _pixmap186_mask, ZF_G1_Char_32_xpm);
   Gtk::Image *pixmap186 = Gtk::manage(new class Gtk::Image(_pixmap186_pixmap, _pixmap186_mask));
   Gtk::Button *button_zufall = Gtk::manage(new class Gtk::Button());
   Glib::RefPtr<Gdk::Bitmap> _pixmap184_mask;
   Glib::RefPtr<Gdk::Pixmap> _pixmap184_pixmap = Gdk::Pixmap::create_from_xpm(get_default_colormap(), _pixmap184_mask, LoadChar_trans_50_xpm);
   Gtk::Image *pixmap184 = Gtk::manage(new class Gtk::Image(_pixmap184_pixmap, _pixmap184_mask));
   Gtk::Button *button_load = Gtk::manage(new class Gtk::Button());
   Gtk::Label *label645 = Gtk::manage(new class Gtk::Label("Dieses Fenster beim nächsten Start wieder anzeigen."));
   Gtk::HSeparator *hseparator23 = Gtk::manage(new class Gtk::HSeparator());
   Gtk::Label *label646 = Gtk::manage(new class Gtk::Label(""));
   Gtk::Label *label647 = Gtk::manage(new class Gtk::Label(""));
   Gtk::HSeparator *hseparator24 = Gtk::manage(new class Gtk::HSeparator());
   table_buttons = Gtk::manage(new class Gtk::Table(2, 2, false));
   
   Gtk::VBox *vbox67 = Gtk::manage(new class Gtk::VBox(false, 0));
   pixmap178->set_alignment(0.5,0.5);
   pixmap178->set_padding(0,0);
   pixmap179->set_alignment(0.5,0.5);
   pixmap179->set_padding(0,0);
   pixmap180->set_alignment(0.5,0.5);
   pixmap180->set_padding(0,0);
   hbox100->pack_start(*pixmap178, Gtk::PACK_SHRINK, 0);
   hbox100->pack_start(*pixmap179, Gtk::PACK_SHRINK, 0);
   hbox100->pack_start(*pixmap180, Gtk::PACK_SHRINK, 0);
   label641->set_alignment(0,0.5);
   label641->set_padding(0,0);
   label641->set_justify(Gtk::JUSTIFY_CENTER);
   label641->set_line_wrap(false);
   label641->set_use_markup(false);
   label642->set_alignment(0,0.5);
   label642->set_padding(0,0);
   label642->set_justify(Gtk::JUSTIFY_CENTER);
   label642->set_line_wrap(false);
   label642->set_use_markup(false);
   label643->set_alignment(0,0.5);
   label643->set_padding(0,0);
   label643->set_justify(Gtk::JUSTIFY_CENTER);
   label643->set_line_wrap(false);
   label643->set_use_markup(false);
   label644->set_alignment(0,0.5);
   label644->set_padding(0,0);
   label644->set_justify(Gtk::JUSTIFY_CENTER);
   label644->set_line_wrap(false);
   label644->set_use_markup(false);
   pixmap182->set_alignment(0.5,0.5);
   pixmap182->set_padding(0,0);
   button_eingabe->set_flags(Gtk::CAN_FOCUS);
   button_eingabe->set_relief(Gtk::RELIEF_NORMAL);
   button_eingabe->add(*pixmap182);
   pixmap181->set_alignment(0.5,0.5);
   pixmap181->set_padding(0,0);
   button_neu->set_flags(Gtk::CAN_FOCUS);
   button_neu->set_relief(Gtk::RELIEF_NORMAL);
   button_neu->add(*pixmap181);
   pixmap186->set_alignment(0.5,0.5);
   pixmap186->set_padding(0,0);
   button_zufall->set_flags(Gtk::CAN_FOCUS);
   button_zufall->set_relief(Gtk::RELIEF_NORMAL);
   button_zufall->add(*pixmap186);
   pixmap184->set_alignment(0.5,0.5);
   pixmap184->set_padding(0,0);
   button_load->set_flags(Gtk::CAN_FOCUS);
   button_load->set_relief(Gtk::RELIEF_NORMAL);
   button_load->add(*pixmap184);
   label645->set_alignment(0,0.5);
   label645->set_padding(0,0);
   label645->set_justify(Gtk::JUSTIFY_CENTER);
   label645->set_line_wrap(false);
   label645->set_use_markup(false);
   label646->set_alignment(0,0.5);
   label646->set_padding(0,0);
   label646->set_justify(Gtk::JUSTIFY_CENTER);
   label646->set_line_wrap(false);
   label646->set_use_markup(false);
   label647->set_alignment(0,0.5);
   label647->set_padding(0,0);
   label647->set_justify(Gtk::JUSTIFY_CENTER);
   label647->set_line_wrap(false);
   label647->set_use_markup(false);
   table_buttons->set_row_spacings(0);
   table_buttons->set_col_spacings(0);
   table_buttons->attach(*label641, 2, 3, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_buttons->attach(*label642, 2, 3, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_buttons->attach(*label643, 2, 3, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_buttons->attach(*label644, 2, 3, 4, 5, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_buttons->attach(*button_eingabe, 1, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_buttons->attach(*button_neu, 1, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_buttons->attach(*button_zufall, 1, 2, 3, 4, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_buttons->attach(*button_load, 1, 2, 4, 5, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
   table_buttons->attach(*label645, 2, 3, 6, 7, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_buttons->attach(*hseparator23, 0, 4, 5, 6, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 5);
   table_buttons->attach(*label646, 0, 1, 1, 2, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table_buttons->attach(*label647, 3, 4, 1, 2, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK, 0, 0);
   table_buttons->attach(*hseparator24, 0, 4, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 5);
   vbox67->pack_start(*hbox100, Gtk::PACK_SHRINK, 0);
   vbox67->pack_start(*table_buttons, Gtk::PACK_SHRINK, 0);
   BegruessungsWindow->set_title("MAGUS-Startfenster");
   BegruessungsWindow->set_modal(true);
   BegruessungsWindow->property_window_position().set_value(Gtk::WIN_POS_CENTER);
   BegruessungsWindow->set_resizable(true);
   BegruessungsWindow->add(*vbox67);
   pixmap178->show();
   pixmap179->show();
   pixmap180->show();
   hbox100->show();
   label641->show();
   label642->show();
   label643->show();
   label644->show();
   pixmap182->show();
   button_eingabe->show();
   pixmap181->show();
   button_neu->show();
   pixmap186->show();
   button_zufall->show();
   pixmap184->show();
   button_load->show();
   label645->show();
   hseparator23->show();
   label646->show();
   label647->show();
   hseparator24->show();
   table_buttons->show();
   vbox67->show();
   BegruessungsWindow->show();
   button_eingabe->signal_clicked().connect(SigC::slot(*this, &BegruessungsWindow_glade::on_button_eingabe_clicked));
   button_neu->signal_clicked().connect(SigC::slot(*this, &BegruessungsWindow_glade::on_button_neu_clicked));
   button_zufall->signal_clicked().connect(SigC::slot(*this, &BegruessungsWindow_glade::on_button_zufall_clicked));
   button_load->signal_clicked().connect(SigC::slot(*this, &BegruessungsWindow_glade::on_button_load_clicked));
}

BegruessungsWindow_glade::~BegruessungsWindow_glade()
{  delete _data;
}
