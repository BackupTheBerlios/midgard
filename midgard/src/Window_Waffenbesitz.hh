// generated 2001/3/14 8:34:43 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Waffenbesitz.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_WAFFENBESITZ_HH
#  include "Window_Waffenbesitz_glade.hh"
#  define _WINDOW_WAFFENBESITZ_HH

#include <vector>
#include <string>

class midgard_CG;
struct st_ausgewaelte_waffen;
struct st_werte;

class Window_Waffenbesitz : public Window_Waffenbesitz_glade
{   
        midgard_CG* hauptfenster;
        vector<st_ausgewaelte_waffen>& vec_waffen;
        vector<string>& waffe_besitz;
        st_werte& werte;
        friend class Window_Waffenbesitz_glade;
        void on_clist_waffe_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_waffe_neu_select_row(gint row, gint column, GdkEvent *event);
        void show_alte_waffen();
        void show_neue_waffen();
        void on_button_close_clicked();
   public:
        Window_Waffenbesitz(midgard_CG* h,vector<st_ausgewaelte_waffen>& vw,vector<string>& wb,st_werte& we);
};
#endif
