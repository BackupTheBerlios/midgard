// $Id: WindowInfo.hh,v 1.45 2003/01/23 15:28:25 thoma Exp $
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

#ifndef _WINDOWINFO_HH
#  include "WindowInfo_glade.hh"
#  define _WINDOWINFO_HH
#include <sigc++/slot.h>
#include <Gtk_OStream.h>
#include <gtkmm/image.h>


class midgard_CG;
#include "MidgardBasicElement.hh"
#include "table_steigern.hh"
#include "Enums.hh"

class WindowInfo : public WindowInfo_glade
{   
   public:
        enum emodus {None,Autoclean/*,ZaubernLernen*//*,PraxisPunkteMBE*/,
                     /*PraxisPunkteAnderes,*/Exit_ohne_speichern,Elf_doppel,
                     LernenMitSpruchrolle};
   private:
        friend class WindowInfo_glade;
        void on_button_abbrechen_clicked();
        void on_button_bestaetigen_clicked();
        void on_button_status_toggled();
        gint timeout();
        SigC::Connection des;
        bool autoclean;

        Gtk::OStream *mystream,*myLogstream;
        void bestaetigen(bool b);
        void Flush(int anzahl);
        void on_button_erase_clicked();
        bool on_WindowInfo_delete_event(GdkEventAny *ev);
        void auswahl(int anz);
        Gtk::Button *WindowInfo::auswahl_button(Gtk::Image *p,Gtk::Label *l,int connect);
        void on_button_auswahl_clicked(int connect);
        emodus Modus;
        midgard_CG* hauptfenster;
        MBEmlt *MBE;
        Enums::e_was_steigern was;
        int bonus_spruchrolle;
   public:
        WindowInfo(midgard_CG* h);
        void AppendShow(const std::string& s,emodus modus, Enums::e_was_steigern was,int anzahl);
        void AppendShow(const std::string& s,emodus modus, MBEmlt *MBE,int anzahl=0);
        void AppendShow(const std::string& s,emodus modus=Autoclean,int anzahl=0);
        void AppendShowLog(const std::string& s);
        void Show() {bestaetigen(false); show();}
        void show_pic(bool b);
};
#endif
