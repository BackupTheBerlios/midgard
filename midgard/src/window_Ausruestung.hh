/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

// generated 2001/11/25 15:17:30 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// newer (non customized) versions of this file go to window_Ausruestung.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_AUSRUESTUNG_HH
#  include "window_Ausruestung_glade.hh"
#  define _WINDOW_AUSRUESTUNG_HH
#include "glademm_support.hh"

#include "midgard_CG.hh"

class window_Ausruestung : public window_Ausruestung_glade
{   
        Datenbank Database;
        
        friend class window_Ausruestung_glade;
        void fill_preisliste();
        void fill_optionmenu_art();
        void fill_optionmenu_typ();
        void opt_art();
        void opt_typ();
        void on_button_close_clicked();
        void on_button_druck_clicked();
        void on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event); 
   public:
        window_Ausruestung(const Datenbank& dat);
};
#endif
