// $Id: MagusDialog.cc,v 1.2 2003/09/02 06:22:47 christof Exp $
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

#include "config.h"
#include <gtkmm/main.h>
#include "midgard_CG.hh"
#include "Fertigkeiten.hh"
#include <gtkmm/button.h>
#include <gtkmm/table.h>   
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <Misc/itos.h>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#include "MagusDialog.hh"

#if 0
void MagusDialog::on_button_abbrechen_clicked()
{   delete this;
}

bool MagusDialog::on_WindowInfo_delete_event(GdkEventAny *ev)
{
// on_button_abbrechen_clicked();
 return false; // verhindert das zerstören des Objektes
}
#endif

MagusDialog::MagusDialog(Gtk::Window *w)
{ set_transient_for(w);
  show();
}

void MagusDialog::set_text(const std::string& s)
{  text->set_text(s);
}

int MagusDialog::run()
{  return Gtk::Dialog::run();
}
