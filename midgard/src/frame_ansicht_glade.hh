// generated 2002/4/24 9:39:20 CEST by christof@puck.petig-baender.de
// using glademm V0.6.4b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- midgard.glade
// for gtk 2.0.2 and gtkmm 1.2.8
//
// Please modify the corresponding derived classes in ./src/frame_ansicht.hh and./src/frame_ansicht.cc

#ifndef _FRAME_ANSICHT_GLADE_HH
#  define _FRAME_ANSICHT_GLADE_HH


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

class frame_ansicht_glade : public Gtk::Frame
{  
protected:
        
        class Gtk::Frame *frame_ansicht;
        
        frame_ansicht_glade(GlademmData *_data);
        
        ~frame_ansicht_glade();
};
#endif