// generated 2001/4/3 21:37:34 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
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
#include "glademm_support.hh"

#include <vector>
class midgard_CG;



class KiDo_auswahl : public KiDo_auswahl_glade
{   
        
        midgard_CG* hauptfenster;
        int maxkido;
        friend class KiDo_auswahl_glade;
        void on_clist_kido_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_kido_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_button_close_clicked();
   public:
        KiDo_auswahl(midgard_CG* h, int m);
};
#endif
