// $Id: Window_herkunft.hh,v 1.15 2001/11/03 17:18:38 thoma Exp $
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

// generated 2001/3/7 10:18:12 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_herkunft.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_HERKUNFT_HH
#  include "Window_herkunft_glade.hh"
#  define _WINDOW_HERKUNFT_HH
#include "glademm_support.hh"

#include "Land.hh"
class midgard_CG;
class Window_herkunft : public Window_herkunft_glade
{   
        midgard_CG* hauptfenster;
        std::vector<cH_Land> L;

        friend class Window_herkunft_glade;
        void on_clist_herkunftsland_select_row(gint row, gint column, GdkEvent *event);
   public:
        Window_herkunft(midgard_CG* h);
};
#endif
