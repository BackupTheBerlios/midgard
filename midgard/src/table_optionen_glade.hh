// generated 2002/10/1 12:06:57 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/table_optionen.hh and./src/table_optionen.cc

#ifndef _TABLE_OPTIONEN_GLADE_HH
#  define _TABLE_OPTIONEN_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtk--/accelgroup.h>

class GlademmData
{  
        
        Gtk::AccelGroup *accgrp;
public:
        
        GlademmData(Gtk::AccelGroup *ag) : accgrp(ag)
        {  
        }
        
        Gtk::AccelGroup * getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtk--/table.h>
#include "frame_globale_optionen.hh"
#include "frame_ansicht.hh"
#include <gtk--/entry.h>
#include <gtk--/spinbutton.h>
#include "frame_drucken.hh"
#include "frame_icons.hh"

class table_optionen_glade : public Gtk::Table
{  
protected:
        
        class Gtk::Table *table_optionen;
        class frame_globale_optionen *frame_globale_optionen;
        class frame_ansicht *frame_ansicht;
        class Gtk::Entry *entry_html;
        class Gtk::Entry *entry_tmp_verz;
        class Gtk::Entry *entry_speicher_verz;
        class Gtk::SpinButton *spinbutton_datei_history;
        class frame_drucken *frame_drucken;
        class frame_icons *frame_icons;
        
        table_optionen_glade(GlademmData *_data);
        
        ~table_optionen_glade();
};
#endif
