// generated 2001/4/20 20:28:00 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Berufe_auswahl.hh and./src/Berufe_auswahl.cc

#ifndef _BERUFE_AUSWAHL_GLADE_HH
#  define _BERUFE_AUSWAHL_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/clist.h>
#include <gtk--/label.h>

class Berufe_auswahl_glade : public Gtk::Window
{   
protected:
        
        class Gtk::CList *berufe_clist_auswahl;
        class Gtk::Label *beruf_auswahl_lernpunkte;
        
        Berufe_auswahl_glade();
        
        ~Berufe_auswahl_glade();
};
#endif
