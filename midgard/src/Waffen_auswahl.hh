// $Id: Waffen_auswahl.hh,v 1.12 2001/05/25 16:18:38 thoma Exp $
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

// generated 2001/2/10 15:13:17 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Waffen_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WAFFEN_AUSWAHL_HH
#  include "Waffen_auswahl_glade.hh"
#  define _WAFFEN_AUSWAHL_HH

#include <vector>
#include <map>
class midgard_CG;
struct st_lernpunkte;
struct st_werte;

struct db_struct_waffe
{  int lernpunkte; 
   string waffe;
   int erfolgswert;
   string grundkenntnisse;
   string zusatz;
   db_struct_waffe(int l,const string &f,int w, string g, string z)
   : lernpunkte(l), waffe(f), erfolgswert(w), grundkenntnisse(g),zusatz(z)
   {}
};


class Waffen_auswahl : public Waffen_auswahl_glade
{   
        int maxpunkte;
        map<string,string> waffen_grundkenntnisse;
        midgard_CG* hauptfenster;
        friend class Waffen_auswahl_glade;
        vector<db_struct_waffe> waffe;
        void on_waffen_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_waffen_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_close_waffen_clicked();
  public:
        Waffen_auswahl(midgard_CG* h,const string& typ,const string& typ_2, st_lernpunkte& l, const st_werte& werte);
};
#endif
