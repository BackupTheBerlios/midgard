// generated 2002/4/14 11:37:35 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.8
//
// Please modify the corresponding derived classes in ./src/frame_drucken.hh and./src/frame_drucken.cc

#ifndef _FRAME_DRUCKEN_GLADE_HH
#  define _FRAME_DRUCKEN_GLADE_HH


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

#include <gtk--/frame.h>

class frame_drucken_glade : public Gtk::Frame
{  
protected:
        
        class Gtk::Frame *frame_drucken;
        
        frame_drucken_glade(GlademmData *_data);
        
        ~frame_drucken_glade();
};
#endif
