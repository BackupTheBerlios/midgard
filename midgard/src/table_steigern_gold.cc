/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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
#include <Misc/itos.h>

void table_steigern::clean_up()
{ LabelSpin_gfp->deaktivate();
  LabelSpin_silber->deaktivate();
  LabelSpin_kupfer->deaktivate();
  LabelSpin_gold->deaktivate();
  LabelSpin_aep->deaktivate();
  LabelSpin_kep->deaktivate();
  LabelSpin_zep->deaktivate();
}

enum { Button_edit=0, Button_add=1 };

void table_steigern::on_checkbutton_gfp()
{
 if(button_GFP->get_index()==Button_edit)
    LabelSpin_gfp->edit_new();
 else 
    LabelSpin_gfp->edit_add();
}

void table_steigern::on_LabelSpin_gfp_activate()
{
  hauptfenster->getAben().setGFP(LabelSpin_gfp->get_value());
  zeige_werte();
}

//////////////////////////////////////////////////////////////////////////

// vielleicht nur ein bool?
void table_steigern::show_goldeingabe(bool b,int do_edit)
{
     if     (do_edit) 
       { 
         LabelSpin_silber->edit_new();
         LabelSpin_kupfer->edit_new();
         LabelSpin_gold->edit_new();
       }
     else
       { 
         LabelSpin_silber->edit_add();
         LabelSpin_kupfer->edit_add();
         LabelSpin_gold->edit_add();
       }
}

void table_steigern::on_button_gold_eingeben()
{
 show_goldeingabe(true,button_gold->get_index()==Button_edit);
}


void table_steigern::on_LabelSpin_gold_activate()
{
 hauptfenster->getAben().setGold(LabelSpin_gold->get_value());
 LabelSpin_silber->grab_focus();
}

void table_steigern::on_LabelSpin_silber_activate()
{
 hauptfenster->getAben().setSilber(LabelSpin_silber->get_value());
 LabelSpin_kupfer->grab_focus();
}

void table_steigern::on_LabelSpin_kupfer_activate()
{
  hauptfenster->getAben().setKupfer(LabelSpin_kupfer->get_value());
}

///////////////////////////////////////////////////////////////////////////


void table_steigern::on_LabelSpin_aep_activate()
{
 hauptfenster->getAben().setAEP(LabelSpin_aep->get_value());
 LabelSpin_kep->grab_focus();
}

void table_steigern::on_LabelSpin_kep_activate()
{
 hauptfenster->getAben().setKEP(LabelSpin_kep->get_value());
 LabelSpin_zep->grab_focus();
}

void table_steigern::on_LabelSpin_zep_activate()
{
 hauptfenster->getAben().setZEP(LabelSpin_zep->get_value());
}

void table_steigern::on_button_EP_eingeben()
{ 
 show_EPeingabe(true,button_EP->get_index()==Button_edit);
}

void table_steigern::show_EPeingabe(bool b,int do_edit)
{
     if     (do_edit)
       { 
         LabelSpin_kep->edit_new();
         LabelSpin_zep->edit_new();
         LabelSpin_aep->edit_new();
       }
     else
       { 
         LabelSpin_kep->edit_add();
         LabelSpin_zep->edit_add();
         LabelSpin_aep->edit_add();
       }
}
