// $Id: Window_ruestung.hh,v 1.17 2001/11/04 07:22:20 thoma Exp $
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

// generated 2001/3/12 19:57:20 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_ruestung.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_RUESTUNG_HH
#  include "Window_ruestung_glade.hh"
#  define _WINDOW_RUESTUNG_HH

class midgard_CG;
class Grundwerte;
#include "midgard_CG.hh"

class Window_ruestung : public Window_ruestung_glade
{   
        Grundwerte& Werte;
        midgard_CG* hauptfenster;
//        midgard_CG::Database Database;
        friend class Window_ruestung_glade;
        void on_clist_ruestung_select_row(gint row, gint column, GdkEvent *event);
   public:
        Window_ruestung::Window_ruestung(Grundwerte& W, midgard_CG* h, const midgard_CG::st_Database& Database);
};
#endif
