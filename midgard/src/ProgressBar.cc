// $Id: ProgressBar.cc,v 1.5 2002/12/18 17:58:00 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2002 Christof Petig
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

#include "ProgressBar.h"
#include <gtkmm/main.h>
#include <gtkmm/progressbar.h>

void ProgressBar::set_percentage(Gtk::ProgressBar *progressbar, double value)
{
#if 0 // no longer needed
   static const int steps=10;
   static int old_val;
   int new_val=int(value*steps);
   if (old_val!=new_val)
   {  progressbar->set_percentage(new_val/(double)steps);
      while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
      old_val=new_val;
   }
#else
   progressbar->set_fraction(value);
   // needed for 2.0?
   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
#endif
}
