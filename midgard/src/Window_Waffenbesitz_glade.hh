// generated 2001/5/15 23:18:16 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/HELP/midgard/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/Window_Waffenbesitz.hh and./src/Window_Waffenbesitz.cc

#ifndef _WINDOW_WAFFENBESITZ_GLADE_HH
#  define _WINDOW_WAFFENBESITZ_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/tooltips.h>
#include <gtk--/clist.h>
#include <gtk--/checkbutton.h>

class Window_Waffenbesitz_glade : public Gtk::Window
{   
        
        Gtk::Tooltips _tooltips;
protected:
        class Gtk::CList *clist_waffe_alt;
        class Gtk::CList *clist_waffe_neu;
        class Gtk::CheckButton *checkbutton_mag_waffenbonus;
        
        Window_Waffenbesitz_glade();
        
        ~Window_Waffenbesitz_glade();
};
#endif
