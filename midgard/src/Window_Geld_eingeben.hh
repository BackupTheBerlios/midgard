// $Id: Window_Geld_eingeben.hh,v 1.11 2001/05/30 15:08:16 thoma Exp $
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
