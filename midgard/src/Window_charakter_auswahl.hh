// $Id: Window_charakter_auswahl.hh,v 1.17 2002/01/19 14:28:11 christof Exp $
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

#ifndef _WINDOW_CHARAKTER_AUSWAHL_HH
#  include "Window_charakter_auswahl_glade.hh"
#  define _WINDOW_CHARAKTER_AUSWAHL_HH
#include "glademm_support.hh"

class midgard_CG;

class Window_charakter_auswahl : public Window_charakter_auswahl_glade
{   
        
        friend class Window_charakter_auswahl_glade;
        void on_clist_charakter_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_auswahl_abbruch_clicked();
        void charakter_loeschen(const std::string& name, const std::string& version);
        void Window_charakter_auswahl::show_charakter();
        midgard_CG* hauptfenster;
   public:
        Window_charakter_auswahl(midgard_CG* h);
};
#endif
