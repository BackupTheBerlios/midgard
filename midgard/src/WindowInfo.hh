// generated 2001/2/27 13:32:15 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to WindowInfo.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOWINFO_HH
#  include "WindowInfo_glade.hh"
#  define _WINDOWINFO_HH
#include "glademm_support.hh"
#include <sigc++/slot.h>

class WindowInfo : public WindowInfo_glade
{   
        
        friend class WindowInfo_glade;
        void on_button_info_ok_clicked();
        gint timeout();
        SigC::Connection des;
   public:
        WindowInfo(const string& s);
};
#endif
