// generated 2001/2/28 7:47:05 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_charakter_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_CHARAKTER_AUSWAHL_HH
#  include "Window_charakter_auswahl_glade.hh"
#  define _WINDOW_CHARAKTER_AUSWAHL_HH
#include "glademm_support.hh"

class midgard_CG;

class Window_charakter_auswahl : public Window_charakter_auswahl_glade
{   
        
        friend class Window_charakter_auswahl_glade;
        void on_clist_charakter_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_auswahl_abbruch_clicked();
        void charakter_loeschen(const string& name, const string& version);
        void Window_charakter_auswahl::show_charakter();
        midgard_CG* hauptfenster;
   public:
        Window_charakter_auswahl(midgard_CG* h);
};
#endif
