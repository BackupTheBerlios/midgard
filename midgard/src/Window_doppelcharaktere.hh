// generated 2001/5/14 14:50:20 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to Window_doppelcharaktere.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_DOPPELCHARAKTERE_HH
#  include "Window_doppelcharaktere_glade.hh"
#  define _WINDOW_DOPPELCHARAKTERE_HH
#include "glademm_support.hh"
class midgard_CG;

class Window_doppelcharaktere : public Window_doppelcharaktere_glade
{   
        midgard_CG *hauptfenster;        
        friend class Window_doppelcharaktere_glade;
        void on_doppelklasse_button_nein_clicked();
        void on_doppelklasse_button_ja_clicked();
   public :
        Window_doppelcharaktere::Window_doppelcharaktere(midgard_CG* h);
};
#endif
