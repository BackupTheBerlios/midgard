// generated 2002/4/30 10:12:00 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to KiDo_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _KIDO_AUSWAHL_HH
#  include "KiDo_auswahl_glade.hh"
#  define _KIDO_AUSWAHL_HH
class KiDo_auswahl : public KiDo_auswahl_glade
{  
        
        friend class KiDo_auswahl_glade;
        void on_clist_kido_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_kido_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_button_close_clicked();
};
#endif
