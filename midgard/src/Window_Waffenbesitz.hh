// $Id: Window_Waffenbesitz.hh,v 1.8 2001/05/15 18:58:05 thoma Exp $
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
#include "Window_mag_bonus.hh"

class midgard_CG;
struct st_ausgewaehlte_waffen;
struct st_werte;
struct st_waffen_besitz;

class Window_Waffenbesitz : public Window_Waffenbesitz_glade
{   
        midgard_CG* hauptfenster;
        vector<st_ausgewaehlte_waffen>& vec_waffen;
        vector<st_waffen_besitz>& waffe_besitz;
        st_werte& werte;
        bool mag_bonus_bool;
        int memwaffe;
        friend class Window_Waffenbesitz_glade;
        void on_clist_waffe_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_waffe_neu_select_row(gint row, gint column, GdkEvent *event);
        void show_alte_waffen();
        void show_neue_waffen();
        void on_button_close_clicked();
        void on_checkbutton_mag_waffenbonus_toggled();
   public:
        Window_Waffenbesitz(midgard_CG* h,vector<st_ausgewaehlte_waffen>& vw,vector<st_waffen_besitz>& wb,st_werte& we);
        void mag_boni_uebernehmen(st_waffen_besitz& wa);
};
#endif

