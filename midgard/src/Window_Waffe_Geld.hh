// generated 2001/3/11 22:34:10 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Waffe_Geld.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_WAFFE_GELD_HH
#  include "Window_Waffe_Geld_glade.hh"
#  define _WINDOW_WAFFE_GELD_HH
#include <vector>

class midgard_CG;
struct st_werte;
struct st_ausgewaelte_waffen;

class Window_Waffe_Geld : public Window_Waffe_Geld_glade
{   
        
        midgard_CG* hauptfenster;        
        st_werte& werte;
        vector<st_ausgewaelte_waffen>& vec_waffen;
        friend class Window_Waffe_Geld_glade;
        void on_button_wuerfeln_clicked();
        void on_button_auswaehlen_clicked();
        void on_button_close_clicked();
        void Geld(int wurf);
        void Waffe(int wurf);
        void Waffe();
   public:
        Window_Waffe_Geld::Window_Waffe_Geld(midgard_CG* h, st_werte& w, vector<st_ausgewaelte_waffen>& wa);
        void Geld();
        void get_waffe(string waffe);
};
#endif
