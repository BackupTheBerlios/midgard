// generated 2001/3/12 22:18:09 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_waffe.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_WAFFE_HH
#  include "Window_waffe_glade.hh"
#  define _WINDOW_WAFFE_HH

#include <vector>
class midgard_CG;
class Window_Waffe_Geld;
struct st_werte; 
struct st_ausgewaehlte_waffen;

class Window_waffe : public Window_waffe_glade
{   
        int wurf;
        vector<st_ausgewaehlte_waffen>& vec_waffen;        
        st_werte& werte;
        midgard_CG* hauptfenster;
        Window_Waffe_Geld* oberfenster;
        friend class Window_waffe_glade;
        void on_clist_waffe_select_row(gint row, gint column, GdkEvent *event);
        void wuerfeln();
        void aussuchen();
        void get_art(string& aartE,string& aartS,string& aartW,string&Z,string& aartA);
   public:
        Window_waffe::Window_waffe(int we,midgard_CG* h, 
                                    Window_Waffe_Geld* o,st_werte& w,
                                    vector<st_ausgewaehlte_waffen>& wa);
        Window_waffe::Window_waffe(int we,midgard_CG* h, 
                                    st_werte& w,
                                    vector<st_ausgewaehlte_waffen>& wa);
};
#endif
