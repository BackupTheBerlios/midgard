// generated 2002/8/26 14:40:04 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// newer (non customized) versions of this file go to frame_icons.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _FRAME_ICONS_HH
#  include "frame_icons_glade.hh"
#  define _FRAME_ICONS_HH

class midgard_CG;
#include <libmagus/Magus_Optionen.hh>
#include <gtkmm/radiobutton.h>

class frame_icons : public frame_icons_glade
{  
        
        midgard_CG *hauptfenster;

//        void element_activate(Gtk::RadioButton *rb,Magus_Optionen::IconIndex index);
        void element_activate(gpointer gp,Magus_Optionen::IconIndex index);
        
public:
        
        frame_icons(GlademmData *_data) : frame_icons_glade(_data) {}
        void init();
        void set_Hauptfenster(midgard_CG *h);
};
#endif
