// $Id: Sprache_auswahl.hh,v 1.26 2002/02/10 16:17:31 thoma Exp $
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

#include "midgard_CG.hh"

class Sprache_auswahl : public Sprache_auswahl_glade
{   
   public:
        enum modus {SPRACHE,MUTTERSPRACHE,NEUESPRACHE,ALTESPRACHE,SCHRIFT,
                    LAND,HEIMATLAND,GEHEIMZEICHEN};
   private:
        modus mod;
        midgard_CG* hauptfenster;        
        const Grundwerte Werte;
        friend class Sprache_auswahl_glade;
        void on_clist_sp_sc_select_row(gint row, gint column, GdkEvent *event);
        const cH_MidgardBasicElement *MBE;
        int wert;
   public:
        Sprache_auswahl(midgard_CG* h, const Datenbank& Database,
             const Grundwerte& Werte, const cH_MidgardBasicElement& MBE,
             modus mod,int wert,
             const std::list<cH_MidgardBasicElement> &Sp,
             const std::list<cH_MidgardBasicElement> &Sc,
             const std::list<cH_MidgardBasicElement> &L);
};
#endif
