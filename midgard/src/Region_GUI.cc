/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

//#include <libmagus/Region.hh>
#include "Region_GUI.hh"

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

Glib::RefPtr<Gdk::Pixbuf> RegionenPic_enum::PicModel(epic typ,bool tiny)
{  std::string name="pinguin.xpm";
   if      (typ==Eschar)     name="Eschar-trans-50.xpm";
   else if (typ==KanThaiPan) name="KiDo-trans-50.xpm";
   else if (typ==DFR)        name="Regio-DFR-4-50.xpm";
   else if (typ==Rawindra)   name="Regio_Rawindra-50.xpm";
   else if (typ==Alba)       name="Regio_Alba-50.xpm";
   else if (typ==Waeland)    name="Regio_Waeland-50.xpm";
   else if (typ==Nahuatlan)  name="Regio_Nahuatlan-50.xpm";
   else if (typ==Arkanum)    name="Regio_Arkanum-50.xpm";
   else if (typ==Gildenbrief)name="Regio_Gilde-50.xpm";
   else if (typ==HD)         name="Regio_H_u_D-50.xpm";
   else if (typ==HD_finster) name="Regio_H_u_D_F-50.xpm";
   else if (typ==Tipps_und_Tricks)  name="TuT_50.xpm";
   else if (typ==Abenteuer)  name="Abwehr-50.xpm";

   Glib::RefPtr<Gdk::Pixbuf> res=MagusImage(name);
   if (tiny && !res.is_null() && res->get_height()>26)
      res=res->scale_simple(int(res->get_width()*26.0/res->get_height()+.5),
      				26,Gdk::INTERP_BILINEAR);
   return res;
}

Gtk::Image *RegionenPic_enum::Pic(epic typ,bool tiny)
{  return manage(new Gtk::Image(PicModel(typ,tiny)));
}

