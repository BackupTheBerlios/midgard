/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2006 Christof Petig
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

#ifndef X391DAD7B_45E2_439B_B050_3A22A87E18BA
#define X391DAD7B_45E2_439B_B050_3A22A87E18BA

#include "MagusDialog.hh"
#include <SimpleTree.hh>
#include <gtkmm/checkbutton.h>
#include <libmagus/MidgardBasicElement.hh>

// Ein Dialog zur Auswahl aus einer Liste
class DialogAuswahl : public MagusDialog
{ SimpleTree tree;
  cH_RowDataBase result;
  
  void clicked(cH_RowDataBase const& row,int idx,bool &handled);
public:
  DialogAuswahl(Gtk::Window *parent,int spalten=1,std::string const& text="");
  SimpleTree &get_tree() { return tree; }
  cH_RowDataBase run();
};

class DialogZusatz : public DialogAuswahl
{ Gtk::CheckButton cb;
  std::vector<cH_RowDataBase> alles;
  
  void einschraenkung_anwenden();
  static int spalten(MidgardBasicElement::eZusatz was);
  static std::string text(MidgardBasicElement::eZusatz was, MBEmlt MBE);
  static std::vector<std::string> titles(MidgardBasicElement::eZusatz was, MBEmlt MBE);
public:
  DialogZusatz(Gtk::Window *parent,MidgardBasicElement::eZusatz was,MBEmlt MBE);
  std::string run();
};

#endif
