// $Id: Zauber_auswahl.hh,v 1.16 2001/06/12 09:31:06 thoma Exp $
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

// generated 2001/2/11 14:16:06 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Zauber_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget


#ifndef _ZAUBER_AUSWAHL_HH
#  include "Zauber_auswahl_glade.hh"
#  define _ZAUBER_AUSWAHL_HH

#include <vector>
class midgard_CG;
struct st_lernpunkte;
struct st_werte;
struct styp;

struct db_struct_zauber
{  int lernpunkte;    
   string zauber;      
   string ap;
   int kosten;
   db_struct_zauber(int l,const string &f, const string &a, int k)
   : lernpunkte(l), zauber(f), ap(a), kosten(k)   
   {}
};   


class Zauber_auswahl : public Zauber_auswahl_glade
{   
        int maxpunkte;
        midgard_CG* hauptfenster;
        friend class Zauber_auswahl_glade;
        vector<db_struct_zauber> zauber;
        void on_zauber_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_zauber_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_close_zauber_clicked();
  public:
        Zauber_auswahl(midgard_CG* h,const st_werte& werte, const styp& typ, const styp& typ_2, st_lernpunkte& l);

};
#endif
