// generated 2001/2/7 8:11:20 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to lernpunkte_editieren.hh_glade

// you might replace
//    class Foo : public Foo_glade { ... };
// by
//    typedef Foo_glade Foo;
// if you didn't make any modifications to the widget

class midgard_CG;
struct st_lernpunkte;

#ifndef _WINDOW_LERNPUNKTE_EDITIEREN_HH
#  include "Window_lernpunkte_editieren_glade.hh"
#  define _WINDOW_LERNPUNKTE_EDITIEREN_HH
class Window_lernpunkte_editieren : public Window_lernpunkte_editieren_glade
{   
        
        friend class Window_lernpunkte_editieren_glade;
        void on_close_clicked();
        midgard_CG* hauptfenster;
    public:
         Window_lernpunkte_editieren(midgard_CG* h, st_lernpunkte& l);

};
#endif
