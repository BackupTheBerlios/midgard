// $Id: Fertigkeiten_auswahl.hh,v 1.31 2002/01/12 08:12:25 thoma Exp $
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
//#include "Grundwerte.hh"
#include "class_lernpunkte.hh"
#include <Datenbank.hh>

class Fertigkeiten_auswahl : public Fertigkeiten_auswahl_glade
{   
        int maxpunkte_F,maxpunkte_A,maxpunkte_U;        
        Lernpunkte lernpunkte;
        Grundwerte Werte;
        vector<cH_Typen> Typ;
        midgard_CG* hauptfenster;
        Datenbank Database;

        friend class Fertigkeiten_auswahl_glade;
        void on_close_fertigkeiten_clicked();
        std::list<cH_MidgardBasicElement> list_Fert_spez;
        std::list<cH_MidgardBasicElement> list_Fert_Fach;
        std::list<cH_MidgardBasicElement> list_Fert_Allg;
        std::list<cH_MidgardBasicElement> list_Fert_Unge;
//        std::list<cH_MidgardBasicElement> list_Zauberwerk;
//        std::list<cH_MidgardBasicElement> list_allg_Fert;
        const std::list<cH_MidgardBasicElement> *list_Sprache;
        std::list<cH_MidgardBasicElement> list_Schrift;
//        std::list<cH_MidgardBasicElement> list_Zauber;
        std::list<cH_MidgardBasicElement> list_Fertigkeit;
        void on_fach_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_fach_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_allgemein_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_allgemein_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_unge_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_unge_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void Fachwissen();
        void Allgemeinwissen();
        void Unge();
        bool SpracheSchrift(const std::string& fert,int wert=0,bool auswahl=false);
 public:
        Fertigkeiten_auswahl(midgard_CG* h,const Datenbank& Database,
                 const vector<cH_Typen>& Typ,
                 Lernpunkte& _lernpunkte, const Grundwerte& _Werte,
                 const std::list<cH_MidgardBasicElement> *_list_Sprache,
                 const std::list<cH_MidgardBasicElement>& _list_Schrift,
                 const std::list<cH_MidgardBasicElement>& _list_Fertigkeit);
};
#endif
