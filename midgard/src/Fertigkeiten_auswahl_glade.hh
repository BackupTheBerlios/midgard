// generated 2001/4/17 19:55:39 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Fertigkeiten_auswahl.hh and./src/Fertigkeiten_auswahl.cc

#ifndef _FERTIGKEITEN_AUSWAHL_GLADE_HH
#  define _FERTIGKEITEN_AUSWAHL_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/clist.h>
#include <gtk--/label.h>

class Fertigkeiten_auswahl_glade : public Gtk::Window
{   
protected:
        
        class Gtk::CList *fertigkeiten_clist_auswahl;
        class Gtk::Label *fert_auswahl_lernpunkte;
        
        Fertigkeiten_auswahl_glade();
        
        ~Fertigkeiten_auswahl_glade();
};
#endif
