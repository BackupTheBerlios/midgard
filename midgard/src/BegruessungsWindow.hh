/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
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

// generated 2002/11/16 21:14:11 CET by thoma@Tiger.(none)
// using glademm V1.1.2a_cvs
//
// newer (non customized) versions of this file go to BegruessungsWindow.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _BEGRUESSUNGSWINDOW_HH
#  include "BegruessungsWindow_glade.hh"
#  define _BEGRUESSUNGSWINDOW_HH

class midgard_CG;

class BegruessungsWindow : public BegruessungsWindow_glade
{  
        midgard_CG* hauptfenster;

        void on_button_eingabe_clicked();
        void on_button_neu_clicked();
        void on_button_zufall_clicked();
        void on_button_load_clicked();
        void end();
   public:
        BegruessungsWindow(midgard_CG* h);
};
#endif
