// generated 2002/4/23 21:23:31 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to frame_ansicht.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _FRAME_ANSICHT_HH
#  include "frame_ansicht_glade.hh"
#  define _FRAME_ANSICHT_HH

class midgard_CG;
#include "Optionen.hh"
#include <gtk--/checkbutton.h>


class frame_ansicht : public frame_ansicht_glade
{  
        
        friend class frame_ansicht_glade;
        midgard_CG *hauptfenster;
        void element_activate(gpointer gp, Midgard_Optionen::OberIndex index);
public:
        
        frame_ansicht(GlademmData *_data) : frame_ansicht_glade(_data)
        {  
        }
        void init();
        void set_Hauptfenster(midgard_CG *h);
                
};
#endif
