// $Id: midgard_CG_optionen.cc,v 1.29 2002/01/12 08:12:25 thoma Exp $
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


bool Originalbool=true;
bool Infobool=true;

void midgard_CG::on_checkbutton_original_menu()
{
//  checkbutton_original->set_active(menu_original->get_active());
  if (menu_original->get_active()) Originalbool=true;
  else Originalbool=false;

  if(Originalbool) 
    { checkbutton_alle_zauber->set_sensitive(false); 
    }      
  else 
    { checkbutton_alle_zauber->set_sensitive(true); 
    }      

//  on_checkbutton_original_toggled();
}

/*
void midgard_CG::on_checkbutton_original_toggled()
{
  if (checkbutton_original->get_active()) Originalbool=true;
  else Originalbool=false;
  menu_original->set_active(Originalbool);

  if(Originalbool) 
    { checkbutton_alle_zauber->set_sensitive(false); 
    }      
  else 
    { checkbutton_alle_zauber->set_sensitive(true); 
    }      
// menu_init();
}
*/

void midgard_CG::on_checkbutton_info_fenster_menu()
{
  if (menu_info->get_active()) Infobool=true;
  else Infobool=false;
  menu_info->set_active(Infobool);
//  checkbutton_info_fenster->set_active(menu_info->get_active());
//  on_checkbutton_info_fenster_toggled();
}
/*
void midgard_CG::on_checkbutton_info_fenster_toggled()
{   
  if (checkbutton_info_fenster->get_active()) Infobool=true;
  else Infobool=false;
  menu_info->set_active(Infobool);
}
*/
void midgard_CG::on_checkbutton_Regionen_menu(Gtk::CheckMenuItem *menu_item,cH_Region region)
{
 if(menu_item->get_active()) region->setActive(true);
 else region->setActive(false);
}



void midgard_CG::regnot(std::string sadd)
{
  manage(new WindowInfo(sadd));
}
