// $Id: Window_waffe.hh,v 1.6 2001/04/19 13:29:11 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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
        void Window_waffe::magische_Waffe();
   public:
        Window_waffe::Window_waffe(int we,midgard_CG* h, 
                                    Window_Waffe_Geld* o,st_werte& w,
                                    vector<st_ausgewaehlte_waffen>& wa);
        Window_waffe::Window_waffe(int we,midgard_CG* h, 
                                    st_werte& w,
                                    vector<st_ausgewaehlte_waffen>& wa);
};
#endif
