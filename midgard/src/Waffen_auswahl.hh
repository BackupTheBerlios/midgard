// $Id: Waffen_auswahl.hh,v 1.28 2002/01/12 08:12:25 thoma Exp $
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

#include <list>
#include <vector>
//class midgard_CG;
#include "midgard_CG.hh"
class Grundwerte;
class cH_Waffe;
class cH_WaffeGrund;
class Typen;
#include "MidgardBasicElement.hh"


class Waffen_auswahl : public Waffen_auswahl_glade
{   
        int maxpunkte;
        std::list<cH_MidgardBasicElement> list_WaffenGrund;
        midgard_CG* hauptfenster;
        vector<cH_Typen> Typ; 
        friend class Waffen_auswahl_glade;
        std::list<cH_MidgardBasicElement> list_Waffen;
        void on_waffen_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_waffen_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_close_waffen_clicked();
  public:
        Waffen_auswahl(midgard_CG* h,const Datenbank& D, int lernpunkte, 
               const Grundwerte& Werte,const vector<cH_Typen>& Typ);
};
#endif
