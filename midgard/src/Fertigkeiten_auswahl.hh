// $Id: Fertigkeiten_auswahl.hh,v 1.9 2001/05/15 22:21:41 thoma Exp $
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

// generated 2001/2/8 11:08:32 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Fertigkeiten_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _FERTIGKEITEN_AUSWAHL_HH
#  include "Fertigkeiten_auswahl_glade.hh"
#  define _FERTIGKEITEN_AUSWAHL_HH

#include <vector>
class midgard_CG;
struct st_lernpunkte;
struct st_werte;

struct db_struct_fertigkeiten
{  int lernpunkte; 
   string fertigkeiten; 
   int erfolgswert;
   string attribut;
   string pflicht;
   int fp;
   string voraussetzung;
   db_struct_fertigkeiten(int l,const string &f,int w,
                           const string &a, const string &p, int fp,
                           const string &v)
   : lernpunkte(l), fertigkeiten(f), erfolgswert(w), attribut(a), 
      pflicht(p), fp(fp), voraussetzung(v)
   {}
};

class Fertigkeiten_auswahl : public Fertigkeiten_auswahl_glade
{   
        int maxpunkte;        
        midgard_CG* hauptfenster;
        friend class Fertigkeiten_auswahl_glade;
        void on_close_fertigkeiten_clicked();
        vector<db_struct_fertigkeiten> fert;
        vector<db_struct_fertigkeiten> allg_fert;
        void on_fertigkeiten_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_fertigkeiten_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        bool Fertigkeiten_spezies_voraussetzung(const string& name,const string& spezies);
 public:
        Fertigkeiten_auswahl(midgard_CG* h,const string& typ,const string& typ_2, 
                 st_lernpunkte& l, const st_werte& werte);
};
#endif
