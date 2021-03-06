// $Id: WindowInfo.hh,v 1.48 2004/01/30 23:29:46 christof Exp $
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
//#include <sigc++/slot.h>
//#include <Gtk_OStream.h>
//#include <gtkmm/image.h>
//class midgard_CG;
//#include "Enums.hh"
#include <libmagus/Ausgabe.hh>

class WindowInfo : public WindowInfo_glade
{	void on_button_abbrechen_clicked();
        gint timeout();
        SigC::Connection des;

        void Flush();
        void on_button_erase_clicked();
        bool on_WindowInfo_delete_event(GdkEventAny *ev);
   public:
        WindowInfo();
        void AppendShow(const std::string& s,Ausgabe::Level l);
        void Show() { show();}
};
#endif
