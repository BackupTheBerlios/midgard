// $Id: Fertigkeiten_auswahl.hh,v 1.26 2001/11/12 09:20:36 thoma Exp $
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

#include <list>
#include <vector>
class cH_Fertigkeit;
#include "midgard_CG.hh"
class Typen;
class Grundwerte;
class H_Data_beruf;

class Fertigkeiten_auswahl : public Fertigkeiten_auswahl_glade
{   
        int maxpunkte;        
        midgard_CG* hauptfenster;
        midgard_CG::st_Database Database;

        friend class Fertigkeiten_auswahl_glade;
        void on_close_fertigkeiten_clicked();
        std::list<cH_MidgardBasicElement> list_Fert_spez;
        std::list<cH_MidgardBasicElement> list_Fert;
        std::list<cH_MidgardBasicElement> list_allg_Fert;
        void on_fertigkeiten_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_fertigkeiten_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
 public:
        Fertigkeiten_auswahl(midgard_CG* h,const midgard_CG::st_Database& Database,const vector<cH_Typen>& Typ,
                 int lernpunkte, const Grundwerte& Werte,const std::vector<H_Data_beruf>& vec_Beruf);
};
#endif
