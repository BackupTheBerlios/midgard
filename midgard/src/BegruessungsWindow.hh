// generated 2002/11/16 21:14:11 CET by thoma@Tiger.(none)
// using glademm V1.1.2a_cvs
//
// newer (non customized) versions of this file go to BegruessungsWindow.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _BEGRUESSUNGSWINDOW_HH
#  include "BegruessungsWindow_glade.hh"
#  define _BEGRUESSUNGSWINDOW_HH

class midgard_CG;

class BegruessungsWindow : public BegruessungsWindow_glade
{  
        
        friend class BegruessungsWindow_glade;
        midgard_CG* hauptfenster;


        void on_button_eingabe_clicked();
        void on_button_neu_clicked();
        void on_button_zufall_clicked();
        void on_button_load_clicked();
        void end();
   public:
        BegruessungsWindow(midgard_CG* h);
};
#endif
