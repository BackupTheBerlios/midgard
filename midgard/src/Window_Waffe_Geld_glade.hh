// generated 2001/4/3 9:39:19 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_Waffe_Geld.hh and./src/Window_Waffe_Geld.cc

#ifndef _WINDOW_WAFFE_GELD_GLADE_HH
#  define _WINDOW_WAFFE_GELD_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/radiobutton.h>
#include <gtk--/label.h>
#include <gtk--/clist.h>

class Window_Waffe_Geld_glade : public Gtk::Window
{   
protected:
        
        class Gtk::RadioButton *radio_geld;
        class Gtk::RadioButton *radio_waffe;
        class Gtk::Label *label_waffen_geld;
        class Gtk::Label *gold;
        class Gtk::Label *silber;
        class Gtk::Label *kupfer;
        class Gtk::CList *clist_gewaehlte_waffen;
        
        Window_Waffe_Geld_glade();
        
        ~Window_Waffe_Geld_glade();
};
#endif
