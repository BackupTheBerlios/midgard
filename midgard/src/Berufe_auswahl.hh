// $Id: Berufe_auswahl.hh,v 1.28 2002/01/12 08:12:24 thoma Exp $
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
//class midgard_CG;
#include "midgard_CG.hh"
//class H_Data_beruf;
class Grundwerte;
class Beruf_Data;
class Datenbank;

class Berufe_auswahl : public Berufe_auswahl_glade
{   
        midgard_CG* hauptfenster;         
        friend class Berufe_auswahl_glade;
        std::list<cH_MidgardBasicElement> list_beruf;
        std::list<cH_MidgardBasicElement> list_fert;
        vector<cH_Typen> Typ;
//        midgard_CG::st_Database Database;
        Datenbank Database;
        Grundwerte Werte;
        bool kat_I, kat_II, kat_III, kat_IV;
        int berufanzahl;

        void wuerfel();
        void gewuerfelt(int wurf);
        gint on_button_wuerfel_button_release_event(GdkEventButton *ev);
        void on_spinbutton_wurf_activate();
        void fill_list();
        void on_tree_unselect_row(gint row, gint column, GdkEvent *event);
        void on_close_berufe_clicked();
        void on_leaf_selected(cH_RowDataBase d);
        void einBeruf(const Beruf_Data &dt);
        void setTitles();
   public:
        Berufe_auswahl(midgard_CG* h,
                    const Datenbank& Database,
                    const vector<cH_Typen>& Typ, 
                    const Grundwerte& Werte,
                    std::list<cH_MidgardBasicElement>& list_fert);
};
#endif
