// $Id: Window_waffe.hh,v 1.28 2002/05/02 05:14:53 thoma Exp $
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

// generated 2001/3/12 22:18:09 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_waffe.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_WAFFE_HH
#  include "Window_waffe_glade.hh"
#  define _WINDOW_WAFFE_HH

#include <vector>
#include <list>
//class Window_Waffe_Geld;
class cH_MidgardBasicElement;
class Grundwerte; 
class cH_Typen;
class midgard_CG;
#include "midgard_CG.hh"

class Window_waffe : public Window_waffe_glade
{   
        Datenbank Database;
        int wurf;
        const std::list<cH_MidgardBasicElement>& list_Waffen;        
        Grundwerte& Werte;
        std::vector<cH_Typen> Typ;
//        Window_Waffe_Geld* oberfenster;
        midgard_CG* hauptfenster;
        friend class Window_waffe_glade;
        void on_clist_waffe_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_waffe_unselect_row(gint row, gint column, GdkEvent *event);
        void wuerfeln();
//        void get_art(std::string& aartE,std::string& aartS,std::string& aartW,std::string&Z,std::string& aartA);
        void magische_Waffe();
        void on_button_close_clicked();
   public:
        Window_waffe::Window_waffe(int we,
                                    midgard_CG* h,Grundwerte& W,
                                    const vector<cH_Typen>& T,
                                    const Datenbank& Database,
                                    const std::list<cH_MidgardBasicElement>& wa);
};
#endif
