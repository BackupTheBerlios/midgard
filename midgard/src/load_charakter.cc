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
#include <Misc/itos.h>
#include <Misc/TagStream.h>
#include "WindowInfo.hh"
#include "xml_fileselection.hh"
//#include <SelectMatching.h>
#include <libmagus/Ausgabe.hh>

void midgard_CG::on_laden()
{
  xml_import_auswahl();
}

void midgard_CG::xml_import_auswahl()
{
  (new xml_fileselection(this,xml_fileselection::Load));
}

void midgard_CG::xml_import_history(const std::string datei)
{
 xml_import(datei);
// load_for_mainpage(notebook_main->get_current_page());
}

void midgard_CG::xml_import(const std::string& datei)
{
   on_wizard_beenden_activate();
   std::ifstream fi(datei.c_str());
//   hmmm
//   table_grundwerte->combo_spezies->set_sensitive(false);
   VAbenteurer::iterator nab=AbenteurerAuswahl::Chars.push_back();
#if 0   
   // wieso ist der Char denn jetzt schon aktiv?
//   on_neuer_charakter_clicked();
   frame_steigern->set_sensitive(true);
#endif   
   if(!(nab->getAbenteurer().xml_import_stream(fi)))
     {
       Ausgabe(Ausgabe::Error,"Laden fehlgeschlagen");
       return;
     }
   nab->setFilename(datei);
   nab->saved();
   push_back_LDateien(datei);
   aktiver.setAbenteurer(nab);
}

