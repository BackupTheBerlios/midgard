// $Id: Region_GUI.hh,v 1.2 2003/07/16 07:11:36 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002-2003 Christof Petig
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

#ifndef REGION_GUI_HH
#define REGION_GUI_HH
//#include <libmagus/Region.hh>
#include <gtkmm/image.h>
//#include "Optionen.hh"

class RegionenPic
{
 public:
   enum epic {None, Rawindra,KanThaiPan,Alba,Eschar,Gildenbrief,HD,Waeland,
              Nahuatlan,Arkanum,DFR,Meister_der_Sphaeren,Tipps_und_Tricks,
              Abenteuer,HD_finster,Kuestenstaaten,Ikengabecken};
   __deprecated static Gtk::Image* Pic(epic e,bool tiny=false) ;
   static Glib::RefPtr<Gdk::Pixbuf> PicModel(epic e,bool tiny=false) ;
};

// class Regionen_GUI
//   mutable Model<Glib::RefPtr<Gdk::Pixbuf> > region_pix;
//   mutable Model<Glib::RefPtr<Gdk::Pixbuf> > region_pix_small;
#endif
