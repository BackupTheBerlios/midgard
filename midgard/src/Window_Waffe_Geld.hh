// $Id: Window_Waffe_Geld.hh,v 1.29 2002/02/08 14:34:18 thoma Exp $
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

// generated 2001/3/11 22:34:10 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Waffe_Geld.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_WAFFE_GELD_HH
#  include "Window_Waffe_Geld_glade.hh"
#  define _WINDOW_WAFFE_GELD_HH
#include <list>
#include <vector>

#include "midgard_CG.hh"
class cH_MidgardBasicElement;
class Grundwerte;
class cH_Typen;

class Window_Waffe_Geld : public Window_Waffe_Geld_glade, public GeldFenster
{   
        friend class Window_waffe; 
        midgard_CG* hauptfenster;        
        Datenbank Database;
        Grundwerte& Werte;
        std::vector<cH_Typen> Typ;
        const std::list<cH_MidgardBasicElement>& list_Waffen;
        friend class Window_Waffe_Geld_glade;
        void on_button_geld_clicked();
        void on_button_waffe_clicked();
        void on_button_close_clicked();
        void Geld();
   public:
        Window_Waffe_Geld::Window_Waffe_Geld(midgard_CG* h, Grundwerte& w, 
            const vector<cH_Typen>& T, 
            const Datenbank& Database,
            const std::list<cH_MidgardBasicElement>& wa);
        void Geld_uebernehmen();
        void get_waffe(const vector<cH_MidgardBasicElement>& waffe);
};
#endif
