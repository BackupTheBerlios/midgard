// generated 2001/3/25 9:24:56 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_mag_bonus.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_MAG_BONUS_HH
#  include "Window_mag_bonus_glade.hh"
#  define _WINDOW_MAG_BONUS_HH
#include "glademm_support.hh"
#include "Window_Waffenbesitz.hh"

struct st_waffen_besitz;
class Window_Waffenbesitz;

class Window_mag_bonus : public Window_mag_bonus_glade
{   
        Window_Waffenbesitz* hauptfenster;
        st_waffen_besitz& waffe_besitz;        
        friend class Window_mag_bonus_glade;
        void on_button_close_clicked();
   public:
        Window_mag_bonus::Window_mag_bonus(Window_Waffenbesitz* h, st_waffen_besitz& wa);
};
#endif
