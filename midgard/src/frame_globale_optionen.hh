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

// generated 2002/4/14 21:33:05 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to frame_globale_optionen.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _FRAME_GLOBALE_OPTIONEN_HH
#  include "frame_globale_optionen_glade.hh"
#  define _FRAME_GLOBALE_OPTIONEN_HH

class midgard_CG;
#include "Magus_Optionen.hh"
#include <gtkmm/checkbutton.h>
#include <libmagus/Optionen.hh>

class frame_globale_optionen : public frame_globale_optionen_glade
{	midgard_CG *hauptfenster;

        void element_activate_C(gpointer gp,Magus_Optionen::OptionenCheckIndex index);
        void element_activate_H(gpointer gp,Optionen::HausIndex index);
        void element_show_or_hide(gpointer gp,Gtk::Widget *widget,Model<int> *wert);

        void on_spinbutton_notebookpage_changed(Magus_Optionen::OptionenCheckIndex index);
public:
        
        frame_globale_optionen(GlademmData *_data) : frame_globale_optionen_glade(_data)
        {  
        }
        void init();
        void set_Hauptfenster(midgard_CG *h);
};
#endif
