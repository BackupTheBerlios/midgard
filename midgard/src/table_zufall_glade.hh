// generated 2002/9/6 20:25:54 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/table_zufall.hh and./src/table_zufall.cc

#ifndef _TABLE_ZUFALL_GLADE_HH
#  define _TABLE_ZUFALL_GLADE_HH


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

class table_zufall_glade : public Gtk::Table
{  
protected:
        
        class Gtk::Table *table_zufall;
        
        table_zufall_glade(GlademmData *_data);
        
        ~table_zufall_glade();
};
#endif