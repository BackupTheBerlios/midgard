// generated 2002/4/14 21:33:05 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to frame_globale_optionen.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _FRAME_GLOBALE_OPTIONEN_HH
#  include "frame_globale_optionen_glade.hh"
#  define _FRAME_GLOBALE_OPTIONEN_HH

class midgard_CG;
#include "Optionen.hh"
#include <gtk--/checkbutton.h>


class frame_globale_optionen : public frame_globale_optionen_glade
{  
        
        friend class frame_globale_optionen_glade;
        midgard_CG *hauptfenster;
        void element_activate(Gtk::CheckButton *cb,Midgard_Optionen::OptionenCheckIndex index);         

public:
        
        frame_globale_optionen(GlademmData *_data) : frame_globale_optionen_glade(_data)
        {  
        }
        void init();
        void set_Hauptfenster(midgard_CG *h);
              
};
#endif
