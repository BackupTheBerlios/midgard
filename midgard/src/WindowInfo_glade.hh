// generated 2002/4/8 13:13:23 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.8
//
// Please modify the corresponding derived classes in ./src/WindowInfo.hh and./src/WindowInfo.cc

#ifndef _WINDOWINFO_GLADE_HH
#  define _WINDOWINFO_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/button.h>
#include <gtk--/table.h>
#include "logwin.hh"

class WindowInfo_glade : public Gtk::Window
{  
protected:
        
        class Gtk::Button *button_bestaetigen;
        class Gtk::Button *button_abbrechen;
        class Gtk::Table *table_bestaetigen;
        class Gtk::Button *button_info_ok;
        class Gtk::Table *table_schliessen;
        class logwin *LogWin;
        
        WindowInfo_glade();
        
        ~WindowInfo_glade();
};
#endif
