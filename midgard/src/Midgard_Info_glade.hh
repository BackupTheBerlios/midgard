// generated 2002/1/26 16:39:10 CET by thoma@Tiger.
// using glademm V0.6.2c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/Midgard_Info.hh and./src/Midgard_Info.cc

#ifndef _MIDGARD_INFO_GLADE_HH
#  define _MIDGARD_INFO_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/label.h>
#include <gtk--/toolbar.h>
#include <gtk--/frame.h>
#include <gtk--/progressbar.h>

class Midgard_Info_glade : public Gtk::Window
{   
protected:
        
        class Gtk::Label *versionsnummer;
        class Gtk::Toolbar *toolbar_close;
        class Gtk::Frame *frame_regionen;
        class Gtk::ProgressBar *progressbar_laender;
        class Gtk::ProgressBar *progressbar_ruestung;
        class Gtk::ProgressBar *progressbar_ang_Fert;
        class Gtk::ProgressBar *progressbar_fertigkeiten;
        class Gtk::ProgressBar *progressbar_grundkenntnisse;
        class Gtk::ProgressBar *progressbar_lernschema;
        class Gtk::ProgressBar *progressbar_beruf;
        class Gtk::ProgressBar *progressbar_regionen;
        class Gtk::ProgressBar *progressbar_ausnahmen;
        class Gtk::ProgressBar *progressbar_spezies;
        class Gtk::ProgressBar *progressbar_typen;
        class Gtk::ProgressBar *progressbar_grad;
        class Gtk::ProgressBar *progressbar_spezial;
        class Gtk::ProgressBar *progressbar_preise;
        class Gtk::ProgressBar *progressbar_pflicht;
        class Gtk::ProgressBar *progressbar_schrift;
        class Gtk::ProgressBar *progressbar_sprache;
        class Gtk::ProgressBar *progressbar_kido;
        class Gtk::ProgressBar *progressbar_zauberwerk;
        class Gtk::ProgressBar *progressbar_zauber;
        class Gtk::ProgressBar *progressbar_aliaswaffen;
        class Gtk::ProgressBar *progressbar_waffen;
        class Gtk::Frame *frame_datenbank;
        
        Midgard_Info_glade();
        
        ~Midgard_Info_glade();
};
#endif
