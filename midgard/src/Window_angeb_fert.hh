// $Id: Window_angeb_fert.hh,v 1.17 2001/06/30 20:30:06 thoma Exp $
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

// generated 2001/3/27 8:26:31 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_angeb_fert.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_ANGEB_FERT_HH
#  include "Window_angeb_fert_glade.hh"
#  define _WINDOW_ANGEB_FERT_HH
#include "glademm_support.hh"

#include <vector>
class midgard_CG;
class H_Data_fert;
class Grundwerte;

class Window_angeb_fert : public Window_angeb_fert_glade
{   

         struct st_af{int min;int max;std::string name;int wert;
            st_af(int mi,int ma,std::string n,int w):min(mi),max(ma),name(n),wert(w){}};
        
        midgard_CG* hauptfenster;
        std::vector<H_Data_fert>& vec_an_Fertigkeit;
        const Grundwerte& Werte;
        int wurf;
        std::vector<st_af> af;
        friend class Window_angeb_fert_glade;
        void on_clist_ang_fert_alt_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_ang_fert_neu_select_row(gint row, gint column, GdkEvent *event);
        void on_button_close_clicked();
        void show_alte_afert();
        void load_af();
        void show_neue_afert();
        void gewuerfelt();
   public:
        Window_angeb_fert::Window_angeb_fert(midgard_CG* h, std::vector<H_Data_fert>& vaf,
               const Grundwerte& W,int wurf);
};
#endif
