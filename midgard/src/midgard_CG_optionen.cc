// $Id: midgard_CG_optionen.cc,v 1.24 2001/08/13 20:08:24 thoma Exp $
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
bool Escharbool=false;
bool Rawindrabool=false;
bool KanThaiPanbool=false;
bool Nahuatlanbool=false;
bool Waelandbool=false;
bool Albabool=false;
bool HDbool=false;
bool BRbool=false;
bool Gildenbriefbool=false;
bool Kuestenstaatenbool=false;

void midgard_CG::on_checkbutton_original_toggled()
{
  if (checkbutton_original->get_active()) Originalbool=true;
  else Originalbool=false;

  if(Originalbool) 
    { checkbutton_alle_zauber->set_sensitive(false); 
      checkbutton_HD->set_sensitive(false);
      checkbutton_BR->set_sensitive(false);
      checkbutton_Gildenbrief->set_sensitive(false);
    }      
  else 
    { checkbutton_alle_zauber->set_sensitive(true); 
      checkbutton_HD->set_sensitive(true);
      checkbutton_BR->set_sensitive(true);
      checkbutton_Gildenbrief->set_sensitive(true);
    }      
}


void midgard_CG::on_checkbutton_info_fenster_toggled()
{   
  if (checkbutton_info_fenster->get_active()) Infobool=true;
  else Infobool=false;
}

void midgard_CG::on_checkbutton_Eschar_toggled()
{   
  if (checkbutton_Eschar->get_active()) Escharbool=true;
  else Escharbool=false;
  if (Escharbool)
     midgard_CG::regnot("Der Derwisch hat leider noch kein Lernschema :-( ");
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_HD_toggled()
{   
  if (checkbutton_HD->get_active()) HDbool=true;
  else HDbool=false;
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_BR_toggled()
{   
  if (checkbutton_BR->get_active()) BRbool=true;
  else BRbool=false;
  midgard_CG::fill_typauswahl();
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_Kuestenstaaten_toggled()
{   
  if (checkbutton_Kuestenstaaten->get_active()) Kuestenstaatenbool=true;
  else Kuestenstaatenbool=false;
  midgard_CG::regnot("Region noch nicht publiziert");
//  midgard_CG::fill_typauswahl();
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_Gildenbrief_toggled()
{   
  if (checkbutton_Gildenbrief->get_active()) Gildenbriefbool=true;
  else Gildenbriefbool=false;
  midgard_CG::regnot("nicht implementiert");
//  midgard_CG::fill_typauswahl();
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_Rawindra_toggled()
{   
  if (checkbutton_Rawindra->get_active()) Rawindrabool=true;
  else Rawindrabool=false;
//  midgard_CG::regnot("Region noch in Arbeit: Fabian Wagner,\n Fabian.Wagner@01019freenet.de");
  midgard_CG::fill_typauswahl();
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_KanThaiPan_toggled()
{   
  if (checkbutton_KanThaiPan->get_active()) KanThaiPanbool=true;
  else KanThaiPanbool=false;
  midgard_CG::fill_typauswahl();
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_Nahuatlan_toggled()
{   
  if (checkbutton_Nahuatlan->get_active()) Nahuatlanbool=true;
  else Nahuatlanbool=false;
  midgard_CG::regnot("Region noch in Arbeit: Nils Richter,\n anarion@uni-muenster.de");
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_Waeland_toggled()
{   
  if (checkbutton_Waeland->get_active()) Waelandbool=true;
  else Waelandbool=false;
  midgard_CG::regnot("Region noch in Arbeit: Stefan Brutscher,\n   midgard-site@t-online.de");
  clear_Ausnahmen();
}

void midgard_CG::on_checkbutton_Alba_toggled()
{   
  if (checkbutton_Alba->get_active()) Albabool=true;
  else Albabool=false;
  clear_Ausnahmen();
}

void midgard_CG::regnot(std::string sadd)
{
  manage(new WindowInfo(sadd));
}
