// generated 2001/5/25 13:55:39 CEST by christof@puck.(none)
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_Geld_eingeben.hh and./src/Window_Geld_eingeben.cc

#ifndef _WINDOW_GELD_EINGEBEN_GLADE_HH
#  define _WINDOW_GELD_EINGEBEN_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/spinbutton.h>

class Window_Geld_eingeben_glade : public Gtk::Window
{   
protected:
        
        class Gtk::SpinButton *spinbutton_gold;
        class Gtk::SpinButton *spinbutton_silber;
        class Gtk::SpinButton *spinbutton_kupfer;
        
        Window_Geld_eingeben_glade();
        
        ~Window_Geld_eingeben_glade();
};
#endif
