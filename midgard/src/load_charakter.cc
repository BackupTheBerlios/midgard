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
#include <Aux/itos.h>

#include "TagStream.hh"
#include "WindowInfo.hh"
#include "xml_fileselection.hh"
//#include <SelectMatching.h>

#ifdef __MINGW__
std::string utf82iso(const std::string &s);
std::string iso2utf8(const std::string &s);
# define Latin2Screen(x) iso2utf8(x)
# define Internal2Latin(x) utf82iso(x)
#else
# define Latin2Screen(x) (x)
# define Internal2Latin(x) (x)
#endif

 
gint midgard_CG::on_laden_release_event(GdkEventButton *ev)
{
  xml_import_auswahl();
  return false;
}

void midgard_CG::xml_import_auswahl()
{
#ifndef __MINGW32__
  manage 
#else
  delete
#endif
  (new xml_fileselection(this,xml_fileselection::Load));
}

void midgard_CG::xml_import_history(const std::string datei)
{
 xml_import(datei);
}

void midgard_CG::xml_import(const std::string& datei)
{
//   int page=notebook_main->get_current_page_num();
   ifstream fi(datei.c_str());
   Char.push_back(Abenteurer());
   on_neuer_charakter_clicked();
   frame_steigern->set_sensitive(true);
   if(!(Char.xml_import_stream(fi,getDatabase(),getOptionen())))
     {
       set_info("Laden fehlgeschlagen");
       return;
     }
   Char.setFilename(datei);
   set_title(getWerte().Name_Abenteurer());
   notebook_main->set_page(PAGE_GRUNDWERTE);
//   load_for_mainpage(page);
   Char.safed();
   push_back_LDateien(datei);
}

