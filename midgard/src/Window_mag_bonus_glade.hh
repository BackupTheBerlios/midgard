// generated 2001/5/15 23:18:16 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/HELP/midgard/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/Window_mag_bonus.hh and./src/Window_mag_bonus.cc

#ifndef _WINDOW_MAG_BONUS_GLADE_HH
#  define _WINDOW_MAG_BONUS_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/tooltips.h>
#include <gtk--/spinbutton.h>
#include <gtk--/label.h>
#include <gtk--/entry.h>

class Window_mag_bonus_glade : public Gtk::Window
{   
        
        Gtk::Tooltips _tooltips;
protected:
        class Gtk::SpinButton *spinbutton_av_bonus;
        class Gtk::SpinButton *spinbutton_sl_bonus;
        class Gtk::Label *label_waffe;
        class Gtk::Label *label_SL_bonus;
        class Gtk::Label *label_av_bonus;
        class Gtk::Entry *entry_magisch;
        
        Window_mag_bonus_glade();
        
        ~Window_mag_bonus_glade();
};
#endif
