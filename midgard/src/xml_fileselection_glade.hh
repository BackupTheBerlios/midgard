// generated 2002/8/26 14:40:04 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/xml_fileselection.hh and./src/xml_fileselection.cc

#ifndef _XML_FILESELECTION_GLADE_HH
#  define _XML_FILESELECTION_GLADE_HH


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

#include <gtk--/fileselection.h>

class xml_fileselection_glade : public Gtk::FileSelection
{  
        
        GlademmData *_data;
protected:
        
        xml_fileselection_glade();
        
        ~xml_fileselection_glade();
};
#endif
