// generated 2002/9/30 8:41:20 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/Window_hilfe.hh and./src/Window_hilfe.cc

#ifndef _WINDOW_HILFE_GLADE_HH
#  define _WINDOW_HILFE_GLADE_HH


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

#include <gtk--/window.h>
#include <gtk--/text.h>

class Window_hilfe_glade : public Gtk::Window
{  
        
        GlademmData *_data;
protected:
        class Gtk::Text *text_hilfe;
        
        Window_hilfe_glade();
        
        ~Window_hilfe_glade();
};
#endif
