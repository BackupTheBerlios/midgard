// generated 2001/8/15 8:35:09 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to Window_Erfahrungspunkte.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_ERFAHRUNGSPUNKTE_HH
#  include "Window_Erfahrungspunkte_glade.hh"
#  define _WINDOW_ERFAHRUNGSPUNKTE_HH
#include "glademm_support.hh"

class Grundwerte;
class midgard_CG;


class Window_Erfahrungspunkte : public Window_Erfahrungspunkte_glade
{   

        Grundwerte& Werte;
        midgard_CG *hauptfenster; 
        
        friend class Window_Erfahrungspunkte_glade;
        void on_button_close_clicked();
        void on_spinbutton_AEP_activate();
        void on_spinbutton_KEP_activate();
        void on_spinbutton_ZEP_activate();
   public:
        Window_Erfahrungspunkte(midgard_CG* h,Grundwerte& w);
};
#endif
