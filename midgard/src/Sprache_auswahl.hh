// generated 2001/3/7 7:55:50 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Sprache_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _SPRACHE_AUSWAHL_HH
#  include "Sprache_auswahl_glade.hh"
#  define _SPRACHE_AUSWAHL_HH
#include "glademm_support.hh"

class midgard_CG;

class Sprache_auswahl : public Sprache_auswahl_glade
{   
        midgard_CG* hauptfenster;        
        string modus;
        friend class Sprache_auswahl_glade;
        void on_clist_sp_sc_select_row(gint row, gint column, GdkEvent *event);
   public:
        Sprache_auswahl(midgard_CG* h, const string& mod);
};
#endif
