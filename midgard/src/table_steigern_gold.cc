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

void table_steigern::on_checkbutton_gfp()
{
// if(ev->button==3) checkbutton_gfp->set_active(!checkbutton_gfp->get_active()); 
 if(checkbutton_gfp->get_active())
  {
    LabelSpin_gfp->edit_new();
    //else if(ev->button == 3) LabelSpin_gfp->edit_add();
  }
 else  LabelSpin_gfp->deaktivate();
// return false;
}

void table_steigern::on_LabelSpin_gfp_activate()
{
  hauptfenster->getChar()->setGFP(LabelSpin_gfp->get_value());
  checkbutton_gfp->set_active(false);
  checkbutton_gfp->grab_focus();
  zeige_werte();
}

//////////////////////////////////////////////////////////////////////////

void table_steigern::on_button_gold_eingeben()
{
 // if(ev->button==3) button_gold_eingeben->set_active(!button_gold_eingeben->get_active()); 
 show_goldeingabe(button_gold_eingeben->get_active(),1);
}


void table_steigern::on_LabelSpin_gold_activate()
{
 hauptfenster->getChar()->setGold(LabelSpin_gold->get_value());
 LabelSpin_silber->grab_focus();
}

/*
bool table_steigern::on_spinbutton_gold_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_gold->update();
 hauptfenster->getChar()->setGold(spinbutton_gold->get_value());
 return false;
}

bool table_steigern::on_spinbutton_gold_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_gold->select_region(0,-1);
 return false;
}
*/
void table_steigern::on_LabelSpin_silber_activate()
{
 hauptfenster->getChar()->setSilber(LabelSpin_silber->get_value());
 LabelSpin_kupfer->grab_focus();
}
/*
bool table_steigern::on_spinbutton_silber_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_silber->update();
 hauptfenster->getChar()->setSilber(spinbutton_silber->get_value_as_int());
 return false;
}

bool table_steigern::on_spinbutton_silber_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_silber->select_region(0,-1);
 return false;
}
*/

void table_steigern::on_LabelSpin_kupfer_activate()
{
  hauptfenster->getChar()->setKupfer(LabelSpin_kupfer->get_value());
  button_gold_eingeben->grab_focus();
  button_gold_eingeben->set_active(false);
}

/*
bool table_steigern::on_spinbutton_kupfer_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_kupfer->update();
 hauptfenster->getChar()->setKupfer(spinbutton_kupfer->get_value_as_int());
 return false;
}

bool table_steigern::on_spinbutton_kupfer_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_kupfer->select_region(0,-1);
 return false;
}
*/
///////////////////////////////////////////////////////////////////////////


void table_steigern::on_LabelSpin_aep_activate()
{
 hauptfenster->getChar()->setAEP(LabelSpin_aep->get_value());
 LabelSpin_kep->grab_focus();
}
/*
bool table_steigern::on_spinbutton_aep_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_aep->update();
 hauptfenster->getChar()->setAEP(spinbutton_aep->get_value_as_int());
 return false;
}

bool table_steigern::on_spinbutton_aep_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_aep->select_region(0,-1);
 return false;
}
*/
void table_steigern::on_LabelSpin_kep_activate()
{
 hauptfenster->getChar()->setKEP(LabelSpin_kep->get_value());
 LabelSpin_zep->grab_focus();
}

/*
bool table_steigern::on_spinbutton_kep_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_kep->update();
 hauptfenster->getChar()->setKEP(spinbutton_kep->get_value_as_int());
 return false;
}

bool table_steigern::on_spinbutton_kep_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_kep->select_region(0,-1);
 return false;
}
*/
void table_steigern::on_LabelSpin_zep_activate()
{
 hauptfenster->getChar()->setZEP(LabelSpin_zep->get_value());
 button_EP->grab_focus();
 button_EP->set_active(false);  
}
/*
bool table_steigern::on_spinbutton_zep_focus_out_event(GdkEventFocus *ev)
{
 spinbutton_zep->update();
 hauptfenster->getChar()->setZEP(spinbutton_zep->get_value_as_int());
 return false;
}

bool table_steigern::on_spinbutton_zep_focus_in_event(GdkEventFocus *ev)
{
 spinbutton_zep->select_region(0,-1);
 return false;
}
*/
