// $Id: ProgressBar.cc,v 1.2 2002/01/30 16:17:07 christof Exp $
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
#include <gtk--/main.h>
#include <gtk--/progressbar.h>

void ProgressBar::set_percentage(Gtk::ProgressBar *progressbar, double value)
{
#if 1
   static const int steps=5;
   static int old_val;
   int new_val=int(value*steps);
   if (old_val!=new_val)
   {  progressbar->set_percentage(new_val/(double)steps);
      while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
      old_val=new_val;
   }
#else
   progressbar->set_percentage((i-b)/size);
   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
#endif
}
