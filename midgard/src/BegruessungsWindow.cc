/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
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


#include "config.h"
#include "BegruessungsWindow.hh"
#include "midgard_CG.hh"
#include "bool_CheckButton.hh"
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

BegruessungsWindow::BegruessungsWindow(midgard_CG* h) 
 : hauptfenster(h) 
{
  Gtk::Image *p= manage(new class Gtk::Image(MagusImage("KillChar-32.xpm")));
  bool_CheckButton *W = Gtk::manage(new bool_CheckButton(Programmoptionen->OberCheck(Magus_Optionen::BegruessungsFenster).active,*p));
  W->set_mode(false);
  W->show_all();
  table_buttons->attach(*W, 1, 2, 6, 7, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
}




void BegruessungsWindow::on_button_eingabe_clicked()
{  // ProgrammOptionen: Eingabe aktiv ...
   hauptfenster->NamenEingeben();
   end();
}

void BegruessungsWindow::on_button_neu_clicked()
{  
  end();
}

void BegruessungsWindow::on_button_zufall_clicked()
{  
//   hauptfenster->notebook_main->set_page(PAGE_ZUFALL);
#warning mit libmagus realisieren
//   hauptfenster->table_zufall->init(hauptfenster);
//   hauptfenster->table_zufall->on_button_zufall_voll_clicked();
   end();
}

void BegruessungsWindow::on_button_load_clicked()
{  
   hauptfenster->xml_import_auswahl();
   end();
}

/*
void BegruessungsWindow::on_togglebutton_never_again_toggled()
{  
  Programmoptionen->setOber("Automatisches Öffnen des Begrüssungsfensters",togglebutton_never_again->get_active());
}
*/

void BegruessungsWindow::end()
{
  delete this;
}

