// $Id: WindowInfo.hh,v 1.25 2002/03/02 16:24:38 thoma Exp $
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

// generated 2001/2/27 13:32:15 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to WindowInfo.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOWINFO_HH
#  include "WindowInfo_glade.hh"
#  define _WINDOWINFO_HH
#include "glademm_support.hh"
#include <sigc++/slot.h>
#include <Gtk_OStream.h>

class midgard_CG;
class cH_MidgardBasicElement;
//#include "MidgardBasicElement.hh"

class WindowInfo : public WindowInfo_glade
{   
   public:
        enum emodus {None,Autoclean,ZaubernLernen};
   private:
        friend class WindowInfo_glade;
        void on_button_info_ok_clicked();
        void on_button_bestaetigen_clicked();
        gint timeout();
        SigC::Connection des;
        bool autoclean;

        Gtk::OStream *mystream;
        void bestaetigen(bool b);
        void Flush();
        void on_button_erase_clicked();
        emodus Modus;
        midgard_CG* hauptfenster;
        cH_MidgardBasicElement *MBE;
   public:
        WindowInfo(midgard_CG* h);
        void AppendShow(const std::string& s,emodus modus,cH_MidgardBasicElement MBE);
        void AppendShow(int i,emodus modus,cH_MidgardBasicElement MBE);
        void AppendShow(const std::string& s, emodus modus=Autoclean);
        void AppendShow(int i, emodus modus=Autoclean);
        void Show() {show();}
};
#endif
