// generated 2001/3/9 7:14:20 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_hilfe.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_HILFE_HH
#  include "Window_hilfe_glade.hh"
#  define _WINDOW_HILFE_HH
class Window_hilfe : public Window_hilfe_glade
{   
        
        friend class Window_hilfe_glade;
        void on_button_hilfe_schliessen_clicked();
        string hilfetext();
   public:
        Window_hilfe();
};
#endif
