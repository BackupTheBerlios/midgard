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
#include "table_steigern.hh"
#include <Misc/itos.h>

void table_steigern::on_button_gfp_s_toggled()
{
 if(checkbutton_gfp->get_active())
  {
    spinbutton_gfp->set_value(hauptfenster->getWerte().GFP());
    spinbutton_gfp->show();
    gfp->hide();  
    spinbutton_gfp->grab_focus();
  }
 else
  {
    spinbutton_gfp->hide();
    gfp->set_text(itos(hauptfenster->getWerte().GFP()));
    gfp->show();  
  }
}

void table_steigern::on_spinbutton_gfp_activate()
{
 checkbutton_gfp->set_active(false);
 checkbutton_gfp->grab_focus();
// on_button_gfp_s_toggled();
 zeige_werte();
}

gint table_steigern::on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_gfp->update();
 hauptfenster->getWerte().setGFP(spinbutton_gfp->get_value_as_int());
 return false;
}

gint table_steigern::on_spinbutton_gfp_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_gfp->select_region(0,-1);
 return false;
}


//////////////////////////////////////////////////////////////////////////

void table_steigern::on_spinbutton_gold_activate()
{
 spinbutton_silber->grab_focus();
}

gint table_steigern::on_spinbutton_gold_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_gold->update();
 hauptfenster->getWerte().setGold(spinbutton_gold->get_value_as_int());
 return false;
}

gint table_steigern::on_spinbutton_gold_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_gold->select_region(0,-1);
 return false;
}

void table_steigern::on_spinbutton_silber_activate()
{
 spinbutton_kupfer->grab_focus();
}

gint table_steigern::on_spinbutton_silber_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_silber->update();
 hauptfenster->getWerte().setSilber(spinbutton_silber->get_value_as_int());
 return false;
}

gint table_steigern::on_spinbutton_silber_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_silber->select_region(0,-1);
 return false;
}

void table_steigern::on_spinbutton_kupfer_activate()
{
  button_gold_eingeben->grab_focus();
  button_gold_eingeben->set_active(false);
}

gint table_steigern::on_spinbutton_kupfer_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_kupfer->update();
 hauptfenster->getWerte().setKupfer(spinbutton_kupfer->get_value_as_int());
 return false;
}

gint table_steigern::on_spinbutton_kupfer_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_kupfer->select_region(0,-1);
 return false;
}

///////////////////////////////////////////////////////////////////////////

void table_steigern::on_spinbutton_aep_activate()
{
 spinbutton_kep->grab_focus();
}

gint table_steigern::on_spinbutton_aep_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_aep->update();
 hauptfenster->getWerte().setAEP(spinbutton_aep->get_value_as_int());
 return false;
}

gint table_steigern::on_spinbutton_aep_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_aep->select_region(0,-1);
 return false;
}

void table_steigern::on_spinbutton_kep_activate()
{
 spinbutton_zep->grab_focus();
}

gint table_steigern::on_spinbutton_kep_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_kep->update();
 hauptfenster->getWerte().setKEP(spinbutton_kep->get_value_as_int());
 return false;
}

gint table_steigern::on_spinbutton_kep_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_kep->select_region(0,-1);
 return false;
}

void table_steigern::on_spinbutton_zep_activate()
{
  button_EP->grab_focus();
  button_EP->set_active(false);  
}

gint table_steigern::on_spinbutton_zep_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_zep->update();
 hauptfenster->getWerte().setZEP(spinbutton_zep->get_value_as_int());
 return false;
}

gint table_steigern::on_spinbutton_zep_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_zep->select_region(0,-1);
 return false;
}

