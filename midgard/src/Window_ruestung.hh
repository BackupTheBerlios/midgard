// generated 2001/3/12 19:57:20 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_ruestung.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_RUESTUNG_HH
#  include "Window_ruestung_glade.hh"
#  define _WINDOW_RUESTUNG_HH

struct st_werte;
class midgard_CG;

class Window_ruestung : public Window_ruestung_glade
{   
        st_werte& werte;        
        midgard_CG* hauptfenster;
        friend class Window_ruestung_glade;
        void on_clist_ruestung_select_row(gint row, gint column, GdkEvent *event);
   public:
        Window_ruestung::Window_ruestung(st_werte& w,midgard_CG* h);
};
#endif
