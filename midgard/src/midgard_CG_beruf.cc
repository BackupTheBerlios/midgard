// $Id: midgard_CG_beruf.cc,v 1.45 2002/02/06 13:53:56 thoma Exp $
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

#include "midgard_CG.hh"
#include "Berufe_auswahl.hh"
#include <Gtk_OStream.h>
#ifndef USE_XML
#include <Aux/SQLerror.h>
#endif


gint midgard_CG::on_button_beruf_release_event(GdkEventButton *ev)
{
  if (ev->button==1) 
   {
     manage(new Berufe_auswahl(this,Database,Typ,Werte,list_Fertigkeit));
   }
  if (ev->button==3) 
   {
     table_berufsname->show();
     entry_berufsname->grab_focus();
   }
  return false;
}

void midgard_CG::on_entry_berufsname_activate()
{
  cH_MidgardBasicElement beruf(&*cH_Beruf(entry_berufsname->get_text(),true));
  MidgardBasicElement_uebernehmen(beruf);
  table_berufsname->hide();
}


