/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
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
#include "table_steigern.hh"
#include <gtkmm/adjustment.h>
#include <Misc/itos.h>

bool table_steigern::vscale_value_changed(GdkEventButton *ev)
{ Window2Abenteurer();
  steigern_gtk();
  return false;
}

void table_steigern::steigern_gtk()
{ label_EP->set_text(itos(hauptfenster->getAben().fpanteil)+"%");
  label_Gold->set_text(itos(hauptfenster->getAben().goldanteil)+"%");
  if (33<=hauptfenster->getAben().fpanteil && hauptfenster->getAben().fpanteil<=67)
  { Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
    A->set_value(hauptfenster->getAben().fpanteil);
    vscale_EP_Gold->show();
  }
  else vscale_EP_Gold->hide();
}

void table_steigern::on_checkbutton_EP_Geld_toggled()
{  Window2Abenteurer();
}
 
#if 0
void table_steigern::on_togglebutton_pp_verfallen_toggled()
{
  if(togglebutton_pp_verfallen->get_active())
   togglebutton_pp_aep_fuellen->set_active(false);  
  Window2Abenteurer();
}

void table_steigern::on_togglebutton_pp_aep_fuellen_toggled()
{
  if(togglebutton_pp_aep_fuellen->get_active())
   togglebutton_pp_verfallen->set_active(false);  
  Window2Abenteurer();
}
#endif
