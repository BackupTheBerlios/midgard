// generated 2001/4/21 10:07:39 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Zauber_auswahl.cc

#include "config.h"
#include "Zauber_auswahl.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Zauber-trans-50.xpm"
#include <gtk--/box.h>
#include <gtk--/button.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

Zauber_auswahl_glade::Zauber_auswahl_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Zauber_auswahl = this;
   zauber_clist_auswahl = manage(new class Gtk::CList(4));
   
   Gtk::ScrolledWindow *scrolledwindow4 = manage(new class Gtk::ScrolledWindow());
   Gtk::Label *label145 = manage(new class Gtk::Label("Lernpunkte"));
   zauber_auswahl_lernpunkte = manage(new class Gtk::Label("X"));
   
   Gtk::Pixmap *pixmap21 = manage(new class Gtk::Pixmap(Zauber_trans_50_xpm));
   Gtk::HBox *hbox10 = manage(new class Gtk::HBox(false, 0));
   Gtk::Toolbar *toolbar23 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button52 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar23->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table8 = manage(new class Gtk::Table(3, 2, false));
   zauber_clist_auswahl->set_column_title(0, "Lernpunkte");
   zauber_clist_auswahl->set_column_justification(0, GTK_JUSTIFY_RIGHT);
   zauber_clist_auswahl->set_column_width(0, 80);
   zauber_clist_auswahl->set_column_title(1, "Zauber");
   zauber_clist_auswahl->set_column_width(1, 80);
   zauber_clist_auswahl->set_column_title(2, "AP");
   zauber_clist_auswahl->set_column_width(2, 80);
   zauber_clist_auswahl->set_column_title(3, "FP");
   zauber_clist_auswahl->set_column_width(3, 80);
   zauber_clist_auswahl->column_titles_show();
   scrolledwindow4->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow4->add(*zauber_clist_auswahl);
   label145->set_alignment(0.5, 0.5);
   label145->set_padding(0, 0);
   zauber_auswahl_lernpunkte->set_alignment(0.5, 0.5);
   zauber_auswahl_lernpunkte->set_padding(11, 0);
   pixmap21->set_alignment(0.5, 0.5);
   pixmap21->set_padding(0, 0);
   hbox10->pack_start(*label145, false, false, 0);
   hbox10->pack_start(*zauber_auswahl_lernpunkte, false, false, 0);
   hbox10->pack_start(*pixmap21);
   toolbar23->set_border_width(5);
   toolbar23->set_space_size(5);
   toolbar23->set_tooltips(true);
   table8->attach(*scrolledwindow4, 0, 2, 0, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table8->attach(*hbox10, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
   table8->attach(*toolbar23, 1, 2, 2, 3, GTK_FILL, 0, 0, 0);
   Zauber_auswahl->set_usize(600, 400);
   Zauber_auswahl->set_title("Zauber");
   Zauber_auswahl->add(*table8);
   zauber_clist_auswahl->show();
   scrolledwindow4->show();
   label145->show();
   zauber_auswahl_lernpunkte->show();
   pixmap21->show();
   hbox10->show();
   toolbar23->show();
   table8->show();
   Zauber_auswahl->show();
   zauber_clist_auswahl->select_row.connect(SigC::slot(static_cast<class Zauber_auswahl*>(this), &Zauber_auswahl::on_zauber_clist_auswahl_select_row));
   zauber_clist_auswahl->unselect_row.connect(SigC::slot(static_cast<class Zauber_auswahl*>(this), &Zauber_auswahl::on_zauber_clist_auswahl_unselect_row));
   button52->clicked.connect(SigC::slot(static_cast<class Zauber_auswahl*>(this), &Zauber_auswahl::on_close_zauber_clicked));
}

Zauber_auswahl_glade::~Zauber_auswahl_glade()
{   
}
