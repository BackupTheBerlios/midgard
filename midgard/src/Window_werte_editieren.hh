// $Id: Window_werte_editieren.hh,v 1.24 2001/12/31 16:06:34 thoma Exp $
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

// generated 2001/2/7 8:11:20 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to window_werte_editieren.hh_glade

// you might replace
//    class Foo : public Foo_glade { ... };
// by
//    typedef Foo_glade Foo;
// if you didn't make any modifications to the widget


class midgard_CG;
class Grundwerte;

#ifndef _WINDOW_WERTE_EDITIEREN_HH
#  include "Window_werte_editieren_glade.hh"
#  define _WINDOW_WERTE_EDITIEREN_HH
#include <vector>

class Window_werte_editieren : public Window_werte_editieren_glade
{   
        friend class Window_werte_editieren_glade;
        void st_activate();
        void gw_activate();
        void gs_activate();
        void ko_activate();
        void in_activate();
        void zt_activate();
        void bzt_activate();
        void au_activate();
        void pa_activate();
        void sb_activate();
        void wk_activate();
        void re_activate();
        void b_activate();
        void lp_activate();
        void ap_activate();
        void bau_activate();
        void grad_activate();
        void alter_activate();
        void on_spinbutton_steigertage_activate();
        void gewicht_activate();
        void groesse_activate();
        void gestalt_activate();
        void spezial_activate();
        void her_activate();
        void glau_activate();
        void ns_activate();
        void nc_activate();
        void sc_activate();
        void an_activate();
        void ab_activate();
        void psy_activate();
        void phs_activate();
        void phk_activate();
        void wza_activate();
        void wab_activate();
        void gfp_activate();
        void gg_activate();
        void sg_activate();
        void vers_activate();
        void on_nwe_close_clicked();
        std::vector<string> vstand, vhand;
        Grundwerte& Werte;
        midgard_CG* hauptfenster;
        public:
         Window_werte_editieren(midgard_CG* h,Grundwerte& w);
};
#endif
