// generated 2001/5/3 22:45:19 CEST by thoma@linux.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// /home/thoma/petig/cvs/christof/glade--/src/glade-- midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
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
