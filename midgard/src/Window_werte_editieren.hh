// generated 2001/2/7 8:11:20 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to window_werte_editieren.hh_glade

// you might replace
//    class Foo : public Foo_glade { ... };
// by
//    typedef Foo_glade Foo;
// if you didn't make any modifications to the widget


class midgard_CG;
struct st_werte;

#ifndef _WINDOW_WERTE_EDITIEREN_HH
#  include "Window_werte_editieren_glade.hh"
#  define _WINDOW_WERTE_EDITIEREN_HH
#include <vector>

class Window_werte_editieren : public Window_werte_editieren_glade
{   
        
        friend class Window_werte_editieren_glade;
        void on_nwe_close_clicked();
        vector<string> vstand;

        midgard_CG* hauptfenster;
        public:
         Window_werte_editieren(midgard_CG* h,st_werte& werte);
            

};
#endif
