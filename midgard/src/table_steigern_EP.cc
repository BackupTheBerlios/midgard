/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
#include <gtk--/adjustment.h>
#include <Misc/itos.h>

gint table_steigern::vscale_value_changed(GdkEventButton *ev)
{
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  int Av=(int)A->get_value();
  hauptfenster->getWerte().set_Steigern_EP_Prozent(100-Av);
  steigern_gtk();
  return false;
}

void table_steigern::steigern_gtk()
{
  label_EP->set_text(itos(hauptfenster->getWerte().get_Steigern_EP_Prozent())+"%");
  label_Gold->set_text(itos(100-hauptfenster->getWerte().get_Steigern_EP_Prozent())+"%");
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  A->set_value(100-hauptfenster->getWerte().get_Steigern_EP_Prozent());
  if (steigern_mit_EP_bool) checkbutton_EP_Geld->set_active(true);
  else                      checkbutton_EP_Geld->set_active(false);
}

void table_steigern::on_checkbutton_EP_Geld_toggled()
{
   if (checkbutton_EP_Geld->get_active()) 
      { steigern_mit_EP_bool=true;
      }
   else 
      { steigern_mit_EP_bool=false;
      }
}

/*
void table_steigern::on_button_EP_toggled()
{
 show_EPeingabe(button_EP->get_active());  
 spinbutton_aep->grab_focus();
}
*/

gint table_steigern::on_button_EP_eingeben_button_release_event(GdkEventButton *ev)
{ 
 if(ev->button==3) button_EP->set_active(!button_EP->get_active());
 show_EPeingabe(button_EP->get_active(),ev->button);
 return false;
}


void table_steigern::show_EPeingabe(bool b,int button)
{
  LabelSpin_aep->set_value(hauptfenster->getWerte().AEP());
  LabelSpin_kep->set_value(hauptfenster->getWerte().KEP());
  LabelSpin_zep->set_value(hauptfenster->getWerte().ZEP());
  if(b)
   {   
     if     (button == 1)
       { 
         LabelSpin_kep->edit_new();
         LabelSpin_zep->edit_new();
         LabelSpin_aep->edit_new();
       }
     else if(button == 3)
       { 
         LabelSpin_kep->edit_add();
         LabelSpin_zep->edit_add();
         LabelSpin_aep->edit_add();
       }
   }
  else
   {  
      LabelSpin_aep->deaktivate();
      LabelSpin_kep->deaktivate();
      LabelSpin_zep->deaktivate();
   }             

/*
  if(b)
   {
     spinbutton_aep->set_value(hauptfenster->getWerte().AEP());
     spinbutton_kep->set_value(hauptfenster->getWerte().KEP());
     spinbutton_zep->set_value(hauptfenster->getWerte().ZEP());
     spinbutton_aep->show();
     spinbutton_kep->show();
     spinbutton_zep->show();
     label_aep->hide();
     label_kep->hide();
     label_zep->hide();
   }
  else
   {
     spinbutton_aep->hide();
     spinbutton_kep->hide();
     spinbutton_zep->hide();
     label_aep->set_text(itos(hauptfenster->getWerte().AEP()));
     label_kep->set_text(itos(hauptfenster->getWerte().KEP()));
     label_zep->set_text(itos(hauptfenster->getWerte().ZEP()));
     label_aep->show();
     label_kep->show();
     label_zep->show();
   }
*/
}
 

void table_steigern::on_togglebutton_pp_verfallen_toggled()
{
  if(togglebutton_pp_verfallen->get_active())
   togglebutton_pp_aep_fuellen->set_active(false);  
}

void table_steigern::on_togglebutton_pp_aep_fuellen_toggled()
{
  if(togglebutton_pp_aep_fuellen->get_active())
   togglebutton_pp_verfallen->set_active(false);  
}

        