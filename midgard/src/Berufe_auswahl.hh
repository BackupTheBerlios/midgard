// $Id: Berufe_auswahl.hh,v 1.10 2001/05/21 06:48:23 thoma Exp $
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

// generated 2001/2/12 13:50:00 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Berufe_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _BERUFE_AUSWAHL_HH
#  include "Berufe_auswahl_glade.hh"
#  define _BERUFE_AUSWAHL_HH

#include <vector>
class midgard_CG;
struct st_lernpunkte;
struct st_werte;
struct styp;

struct db_struct_beruf
{  int lernpunkte;    
   string beruf;      
   string stand;
   string voraussetzung;
   string vorteile;   
   db_struct_beruf(int l,const string &b, const string &s,
                  const string &v1,const string &v2 )
   : lernpunkte(l), beruf(b), stand(s), voraussetzung(v1), vorteile(v2)   
   {}
};   

class Berufe_auswahl : public Berufe_auswahl_glade
{   
        int maxpunkte;
        midgard_CG* hauptfenster;         
        friend class Berufe_auswahl_glade;
        vector<db_struct_beruf> beruf;
        void on_berufe_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_berufe_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_close_berufe_clicked();
        bool berufe_voraussetzung(const string& beruf, const st_werte& werte, const string& typz, const string& typ2z);
        bool btyp(const string& typ, const string& typz, const string& typ2z);
        string Beruf_vorteile(const string& beruf);
   public:
        Berufe_auswahl(midgard_CG* h,const styp& typ,const styp& typ_2, const st_lernpunkte& l, const st_werte& werte);
};
#endif
