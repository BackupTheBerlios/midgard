// generated 2001/2/27 10:54:49 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_charakter_beschreibung.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_CHARAKTER_BESCHREIBUNG_HH
#  include "Window_charakter_beschreibung_glade.hh"
#  define _WINDOW_CHARAKTER_BESCHREIBUNG_HH
#include "glademm_support.hh"

class midgard_CG;

class Window_charakter_beschreibung : public Window_charakter_beschreibung_glade
{   
        
        friend class Window_charakter_beschreibung_glade;
        void on_charakter_beschreibung_uebernehmen_clicked();
        void on_charakter_beschreibung_drucken_clicked();
        void on_charakter_beschreibung_abbrechen_clicked();
        midgard_CG* hauptfenster;
   public:
        Window_charakter_beschreibung(midgard_CG* h,string s);
};
#endif
