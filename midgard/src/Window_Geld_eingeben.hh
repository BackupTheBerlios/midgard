// $Id: Window_Geld_eingeben.hh,v 1.19 2001/10/21 21:21:55 thoma Exp $
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

class Grundwerte;
class Window_Waffe_Geld;
class midgard_CG;

class Window_Geld_eingeben : public Window_Geld_eingeben_glade
{   
        Grundwerte& Werte;
        bool back;
        Window_Waffe_Geld* oberfenster;
        midgard_CG* hauptfenster;
        friend class Window_Geld_eingeben_glade;
        void show_Geld();
        void on_button_close_clicked();
        void on_spinbutton_silber_activate();
        void on_spinbutton_kupfer_activate();
        void on_spinbutton_gold_activate();
   public:
        Window_Geld_eingeben(Window_Waffe_Geld* h,Grundwerte& w);
        Window_Geld_eingeben(midgard_CG* h,Grundwerte& w);
};
#endif
