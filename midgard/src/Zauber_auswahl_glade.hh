// generated 2001/4/4 8:09:31 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Zauber_auswahl.hh and./src/Zauber_auswahl.cc

#ifndef _ZAUBER_AUSWAHL_GLADE_HH
#  define _ZAUBER_AUSWAHL_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/clist.h>
#include <gtk--/label.h>

class Zauber_auswahl_glade : public Gtk::Window
{   
protected:
        
        class Gtk::CList *zauber_clist_auswahl;
        class Gtk::Label *zauber_auswahl_lernpunkte;
        
        Zauber_auswahl_glade();
        
        ~Zauber_auswahl_glade();
};
#endif
