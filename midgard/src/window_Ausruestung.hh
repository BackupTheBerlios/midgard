// generated 2001/11/25 15:17:30 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// newer (non customized) versions of this file go to window_Ausruestung.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_AUSRUESTUNG_HH
#  include "window_Ausruestung_glade.hh"
#  define _WINDOW_AUSRUESTUNG_HH
#include "glademm_support.hh"

#include "midgard_CG.hh"

class window_Ausruestung : public window_Ausruestung_glade
{   
        midgard_CG::st_Database Database;
        
        friend class window_Ausruestung_glade;
        void fill_optionmenu_art();
        void fill_optionmenu_typ();
        void on_button_close_clicked();
        void on_button_druck_clicked();
   public:
        window_Ausruestung(const midgard_CG::st_Database& dat);
};
#endif
