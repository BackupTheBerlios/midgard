// generated 2005/6/21 10:12:53 CEST by christof@vesta.petig-baender.de
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage --gtkmmversion 2.4.0 midgard.glade
// for gtk 2.6.8 and gtkmm 2.4.0
//
// Please modify the corresponding derived classes in ./src/frame_icons.cc


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
#include "frame_icons_glade.hh"
#include <gtkmm/label.h>

frame_icons_glade::frame_icons_glade(GlademmData *gmm_data
)
{  frame_icons = this;
   
   Gtk::Label *label681 = Gtk::manage(new class Gtk::Label("Thema"));
   label681->set_alignment(0.5,0.5);
   label681->set_padding(0,0);
   label681->set_justify(Gtk::JUSTIFY_LEFT);
   label681->set_line_wrap(false);
   label681->set_use_markup(false);
   label681->set_selectable(false);
   frame_icons->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame_icons->set_label_align(0,0.5);
   frame_icons->set_label_widget(*label681);
   label681->show();
   frame_icons->show();
}

frame_icons_glade::~frame_icons_glade()
{  
}
