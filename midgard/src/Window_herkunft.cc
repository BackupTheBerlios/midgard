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

#include "config.h"
#include "Window_herkunft.hh"
#include <Gtk_OStream.h>

void Window_herkunft::on_clist_herkunftsland_select_row(gint row, gint column, GdkEvent *event)
{   
   cH_Land land=static_cast<Land*>(clist_herkunftsland->selection().begin()->get_data());
   hauptfenster->herkunft_uebernehmen(land);
   destroy();
}

Window_herkunft::Window_herkunft(midgard_CG* h,const Datenbank& Database)
: hauptfenster(h)
{
 Gtk::OStream os(clist_herkunftsland);
 for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
  {
   os << (*i)->Name()<<'\t'<<(*i)->Kontinent()<<'\n';
   os.flush((*i)->ref(),&HandleContent::unref);
  }   
}
