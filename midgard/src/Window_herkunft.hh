// generated 2001/3/7 10:18:12 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_herkunft.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_HERKUNFT_HH
#  include "Window_herkunft_glade.hh"
#  define _WINDOW_HERKUNFT_HH
#include "glademm_support.hh"

class midgard_CG;
class Window_herkunft : public Window_herkunft_glade
{   
        midgard_CG* hauptfenster;
        
        friend class Window_herkunft_glade;
        void on_clist_herkunftsland_select_row(gint row, gint column, GdkEvent *event);
   public:
        Window_herkunft(midgard_CG* h);
};
#endif
