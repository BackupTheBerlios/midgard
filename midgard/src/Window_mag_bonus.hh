// $Id: Window_mag_bonus.hh,v 1.8 2001/05/25 10:22:38 thoma Exp $
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
