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
/*
   if(getCWerte().Name_Abenteurer()=="")
    {
      no_name();   
      return false;
    }
*/
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


void midgard_CG::xml_import(const std::string& datei)
{
   ifstream fi(datei.c_str());
   on_neuer_charakter_clicked();
   frame_steigern->set_sensitive(true);
   Char.xml_import_stream(fi,this);
   filename=datei;
   set_title(getWerte().Name_Abenteurer());
   load_for_mainpage(notebook_main->get_current_page_num());
//   if(getWerte().Stadt_Land()=="Stadt") table_grundwerte->radiobutton_stadt->set_active(true);
//   if(getWerte().Stadt_Land()=="Land")  table_grundwerte->radiobutton_land->set_active(true);
}

