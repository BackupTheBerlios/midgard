// generated 2001/3/12 10:16:00 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Geld_eingeben.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_GELD_EINGEBEN_HH
#  include "Window_Geld_eingeben_glade.hh"
#  define _WINDOW_GELD_EINGEBEN_HH

struct st_werte;
class Window_Waffe_Geld;
class midgard_CG;

class Window_Geld_eingeben : public Window_Geld_eingeben_glade
{   
        st_werte& werte;
        bool back;
        Window_Waffe_Geld* oberfenster;
        friend class Window_Geld_eingeben_glade;
        void on_button_close_clicked();
   public:
        Window_Geld_eingeben::Window_Geld_eingeben(Window_Waffe_Geld* h,st_werte& w);
        Window_Geld_eingeben::Window_Geld_eingeben(midgard_CG* h,st_werte& w);
};
#endif
