// $Id: Sprache_auswahl.hh,v 1.7 2001/05/15 22:21:41 thoma Exp $
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

// generated 2001/3/7 7:55:50 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Sprache_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _SPRACHE_AUSWAHL_HH
#  include "Sprache_auswahl_glade.hh"
#  define _SPRACHE_AUSWAHL_HH
#include "glademm_support.hh"

class midgard_CG;

class Sprache_auswahl : public Sprache_auswahl_glade
{   
        midgard_CG* hauptfenster;        
        string modus;
        friend class Sprache_auswahl_glade;
        void on_clist_sp_sc_select_row(gint row, gint column, GdkEvent *event);
   public:
        Sprache_auswahl(midgard_CG* h, const string& mod);
};
#endif
