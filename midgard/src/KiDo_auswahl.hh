// $Id: KiDo_auswahl.hh,v 1.16 2001/06/12 09:31:05 thoma Exp $
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

// generated 2001/4/3 21:37:34 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to KiDo_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _KIDO_AUSWAHL_HH
#  include "KiDo_auswahl_glade.hh"
#  define _KIDO_AUSWAHL_HH
#include "glademm_support.hh"

#include <vector>
class midgard_CG;
struct st_werte;
struct st_kido_{string name_orig;string name;int ap;int fp;
      st_kido_(string n, string n2, int a, int f)
      : name_orig(n),name(n2),ap(a),fp(f) {}};

class KiDo_auswahl : public KiDo_auswahl_glade
{   
        
        vector<st_kido_> kido_technik;
        midgard_CG* hauptfenster;
        int maxkido;
        friend class KiDo_auswahl_glade;
        void on_clist_kido_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_clist_kido_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_button_close_clicked();
   public:
        KiDo_auswahl(midgard_CG* h, int m,const st_werte& werte);
};
#endif
