// $Id: MagusDialog.hh,v 1.6 2004/12/21 08:32:29 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#ifndef _MAGUSDIALOG_HH
#  include "MagusDialog_glade.hh"
#  define _MAGUSDIALOG_HH
#include <gtkmm/window.h>
#include <Misc/bitmask.h>

class MagusDialog : public MagusDialog_glade
{  
        bool on_WindowInfo_delete_event(GdkEventAny *ev);
   public:
        enum style_bits { b_Nein, b_Ja, b_Close };
        MagusDialog(Gtk::Window *w);
        void set_text(const std::string& s);
        void set_yes_no(const std::string& y,const std::string& n);
        int run();
        void set_style(const bitmask<style_bits> &st);
        // remember: get_vbox is also possible
};
#endif
