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
#include <fstream>
#include "Waffe.hh"
#include "xml_fileselection.hh"
#include <Misc/itos.h>
#include <libmagus/Ausgabe.hh>

void midgard_CG::on_speichern()
{
  save_existing_filename();
  //else                xml_export_auswahl();
}

void midgard_CG::xml_export_auswahl()
{ 
   if(Char->Name_Abenteurer().empty())
    { Ausgabe(Ausgabe::ActionNeeded,"Der Abenteurer braucht noch einen Namen"); 
      notebook_main->set_current_page(PAGE_GRUNDWERTE);
      table_grundwerte->NamenEingeben();
      return;}
 (new xml_fileselection(this,xml_fileselection::Save/*"Abenteurer speichern"*/));
}

void midgard_CG::save_existing_filename()
{
  if(!Char.getFilename().empty()) xml_export(Char.getFilename());
  else                            xml_export_auswahl();
}


void midgard_CG::xml_export(const std::string& dateiname)
{  
   if(Char->Name_Abenteurer().empty())
    { Ausgabe(Ausgabe::ActionNeeded,"Der Abenteurer braucht noch einen Namen"); 
      notebook_main->set_current_page(PAGE_GRUNDWERTE);
      table_grundwerte->NamenEingeben();
      return;}
   Char.setFilename(dateiname);
   frame_steigern->set_sensitive(true);

   std::ofstream datei(dateiname.c_str());
   if (!datei.good())
   { 
      Ausgabe(Ausgabe::Error,"Ich kann die Datei '"+dateiname+"' nicht beschreiben");
      return;
   }
  Char->speicherstream(datei);
  Char.saved();   
  push_back_LDateien(dateiname);
  if(notebook_main->get_current_page() == PAGE_NEWS)
      load_for_mainpage(PAGE_NEWS);
}

