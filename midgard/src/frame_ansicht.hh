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


#ifndef _FRAME_ANSICHT_HH
#  include "frame_ansicht_glade.hh"
#  define _FRAME_ANSICHT_HH

class midgard_CG;
#include <libmagus/Magus_Optionen.hh>
//#include <gtkmm/checkbutton.h>

class frame_ansicht : public frame_ansicht_glade
{  
        midgard_CG *hauptfenster;
        void element_activate(gpointer gp, Magus_Optionen::OberIndex index);
public:
        
        frame_ansicht(GlademmData *_data) : frame_ansicht_glade(_data)
        {  
        }
        void init();
        void set_Hauptfenster(midgard_CG *h);
};
#endif
