// generated 2005/4/27 10:13:16 CEST by thoma@Tiger.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage --gtkmmversion 2.4.0 midgard.glade
// for gtk 2.6.2 and gtkmm 2.4.0
//
// Please modify the corresponding derived classes in ./src/frame_globale_optionen.cc


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
#include "frame_globale_optionen_glade.hh"
#include <gtkmm/label.h>

frame_globale_optionen_glade::frame_globale_optionen_glade(GlademmData *gmm_data
)
{  frame_globale_optionen = this;
   
   Gtk::Label *label678 = Gtk::manage(new class Gtk::Label("Globale Optionen"));
   label678->set_alignment(0.5,0.5);
   label678->set_padding(0,0);
   label678->set_justify(Gtk::JUSTIFY_LEFT);
   label678->set_line_wrap(false);
   label678->set_use_markup(false);
   label678->set_selectable(false);
   frame_globale_optionen->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame_globale_optionen->set_label_align(0,0.5);
   frame_globale_optionen->set_label_widget(*label678);
   label678->show();
   frame_globale_optionen->show();
}

frame_globale_optionen_glade::~frame_globale_optionen_glade()
{  
}
