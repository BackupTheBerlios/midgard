
#ifndef _FRAME_ANSICHT_HH
#  include "frame_ansicht_glade.hh"
#  define _FRAME_ANSICHT_HH

class midgard_CG;
#include <libmagus/Magus_Optionen.hh>
//#include <gtkmm/checkbutton.h>

class frame_ansicht : public frame_ansicht_glade
{  
        midgard_CG *hauptfenster;
        void element_activate(gpointer gp, Magus_Optionen::OberIndex index);
public:
        
        frame_ansicht(GlademmData *_data) : frame_ansicht_glade(_data)
        {  
        }
        void init();
        void set_Hauptfenster(midgard_CG *h);
};
#endif
