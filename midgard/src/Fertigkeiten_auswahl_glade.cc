// $Id: Fertigkeiten_auswahl_glade.cc,v 1.15 2001/04/19 13:29:11 thoma Exp $
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

// generated 2001/4/19 8:46:44 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Fertigkeiten_auswahl.cc

#include "config.h"
#include "Fertigkeiten_auswahl.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Skills-trans-50.xpm"
#include <gtk--/box.h>
#include <gtk--/button.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

Fertigkeiten_auswahl_glade::Fertigkeiten_auswahl_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Fertigkeiten_auswahl = this;
   fertigkeiten_clist_auswahl = manage(new class Gtk::CList(7));
   
   Gtk::ScrolledWindow *scrolledwindow2 = manage(new class Gtk::ScrolledWindow());
   Gtk::Label *label130 = manage(new class Gtk::Label("Lernpunkte"));
   fert_auswahl_lernpunkte = manage(new class Gtk::Label("X"));
   
   Gtk::Pixmap *pixmap23 = manage(new class Gtk::Pixmap(Skills_trans_50_xpm));
   Gtk::HBox *hbox8 = manage(new class Gtk::HBox(false, 0));
   Gtk::Toolbar *toolbar21 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button50 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar21->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table6 = manage(new class Gtk::Table(3, 3, false));
   fertigkeiten_clist_auswahl->set_column_title(0, "Lernpunkte");
   fertigkeiten_clist_auswahl->set_column_justification(0, GTK_JUSTIFY_RIGHT);
   fertigkeiten_clist_auswahl->set_column_width(0, 80);
   fertigkeiten_clist_auswahl->set_column_title(1, "Vorraussetzung");
   fertigkeiten_clist_auswahl->set_column_width(1, 80);
   fertigkeiten_clist_auswahl->set_column_title(2, "Pflicht");
   fertigkeiten_clist_auswahl->set_column_justification(2, GTK_JUSTIFY_RIGHT);
   fertigkeiten_clist_auswahl->set_column_width(2, 80);
   fertigkeiten_clist_auswahl->set_column_title(3, "Fertigkeit");
   fertigkeiten_clist_auswahl->set_column_width(3, 80);
   fertigkeiten_clist_auswahl->set_column_title(4, "Erfolgswert");
   fertigkeiten_clist_auswahl->set_column_justification(4, GTK_JUSTIFY_RIGHT);
   fertigkeiten_clist_auswahl->set_column_width(4, 80);
   fertigkeiten_clist_auswahl->set_column_title(5, "Eigenschaft");
   fertigkeiten_clist_auswahl->set_column_width(5, 80);
   fertigkeiten_clist_auswahl->set_column_title(6, "FP");
   fertigkeiten_clist_auswahl->set_column_width(6, 80);
   fertigkeiten_clist_auswahl->column_titles_show();
   scrolledwindow2->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow2->add(*fertigkeiten_clist_auswahl);
   label130->set_alignment(0.5, 0.5);
   label130->set_padding(0, 0);
   fert_auswahl_lernpunkte->set_alignment(0.5, 0.5);
   fert_auswahl_lernpunkte->set_padding(11, 0);
   pixmap23->set_alignment(0.5, 0.5);
   pixmap23->set_padding(0, 0);
   hbox8->pack_start(*label130, false, false, 0);
   hbox8->pack_start(*fert_auswahl_lernpunkte, false, false, 0);
   hbox8->pack_start(*pixmap23);
   toolbar21->set_border_width(5);
   toolbar21->set_space_size(5);
   toolbar21->set_tooltips(true);
   table6->attach(*scrolledwindow2, 0, 3, 0, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table6->attach(*hbox8, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
   table6->attach(*toolbar21, 2, 3, 2, 3, GTK_FILL, 0, 0, 0);
   Fertigkeiten_auswahl->set_usize(600, 400);
   Fertigkeiten_auswahl->set_title("Fertigkeiten");
   Fertigkeiten_auswahl->add(*table6);
   fertigkeiten_clist_auswahl->show();
   scrolledwindow2->show();
   label130->show();
   fert_auswahl_lernpunkte->show();
   pixmap23->show();
   hbox8->show();
   toolbar21->show();
   table6->show();
   Fertigkeiten_auswahl->show();
   fertigkeiten_clist_auswahl->select_row.connect(SigC::slot(static_cast<class Fertigkeiten_auswahl*>(this), &Fertigkeiten_auswahl::on_fertigkeiten_clist_auswahl_select_row));
   fertigkeiten_clist_auswahl->unselect_row.connect(SigC::slot(static_cast<class Fertigkeiten_auswahl*>(this), &Fertigkeiten_auswahl::on_fertigkeiten_clist_auswahl_unselect_row));
   button50->clicked.connect(SigC::slot(static_cast<class Fertigkeiten_auswahl*>(this), &Fertigkeiten_auswahl::on_close_fertigkeiten_clicked));
}

Fertigkeiten_auswahl_glade::~Fertigkeiten_auswahl_glade()
{   
}
