// $Id: customize_toolbars.h,v 1.6 2003/09/01 06:47:58 christof Exp $
/*  Midgard Roleplaying Character Generator
 *  Copyright (C) 2001-2002 Christof Petig
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

#ifndef CUSTOMIZE_TOOLBARS_H
#define CUSTOMIZE_TOOLBARS_H
#include <gtkmm/widget.h>

namespace Gtk
{  void CustomizeToolbars(Gtk::Widget *w, bool show_icons, bool show_text, bool tab_text);
bool rec_hide(Gtk::Widget *w);
}

#endif
