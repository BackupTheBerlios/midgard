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


gint midgard_CG::on_speichern_release_event(GdkEventButton *ev)
{
  if (ev->button==1)  save_existing_filename();
  else                xml_export_auswahl();
  return false;
}

void midgard_CG::xml_export_auswahl()
{ 
#ifndef __MINGW32__ 
 manage 
#else
 delete
#endif
 (new xml_fileselection(this,xml_fileselection::Save/*"Abenteurer speichern"*/));
}

void midgard_CG::save_existing_filename()
{
  if(!Char.getFilename().empty()) xml_export(Char.getFilename());
  else                            xml_export_auswahl();
}


void midgard_CG::xml_export(const std::string& dateiname)
{  
   if(Char.getWerte().Name_Abenteurer().empty())
    { set_status("Der Abenteurer braucht noch einen Namen"); 
      notebook_main->set_page(PAGE_GRUNDWERTE);
      table_grundwerte->togglebutton_edit_werte->set_active(true);
      table_grundwerte->entry_nameC->grab_focus();
      return;}
   Char.setFilename(dateiname);
   frame_steigern->set_sensitive(true);

   ofstream datei(dateiname.c_str());
   if (!datei.good())
   { 
      set_info("Ich kann die Datei '"+dateiname+"' nicht beschreiben");
      return;
   }
  Char.speicherstream(datei,getCDatabase(),getCOptionen());
  Char.safed();   
  push_back_LDateien(dateiname);
  if(notebook_main->get_current_page_num() == PAGE_NEWS)
      load_for_mainpage(PAGE_NEWS);
}

