// generated 2001/4/17 19:55:39 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Waffen_auswahl.cc

#include "config.h"
#include "Waffen_auswahl.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Weapon-trans-50.xpm"
#include <gtk--/box.h>
#include <gtk--/button.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

Waffen_auswahl_glade::Waffen_auswahl_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Waffen_auswahl = this;
   waffen_clist_auswahl = manage(new class Gtk::CList(5));
   
   Gtk::ScrolledWindow *scrolledwindow3 = manage(new class Gtk::ScrolledWindow());
   Gtk::Label *label138 = manage(new class Gtk::Label("Lernpunkte"));
   waffen_auswahl_lernpunkte = manage(new class Gtk::Label("X"));
   
   Gtk::Pixmap *pixmap22 = manage(new class Gtk::Pixmap(Weapon_trans_50_xpm));
   Gtk::HBox *hbox9 = manage(new class Gtk::HBox(false, 0));
   Gtk::Toolbar *toolbar22 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button51 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar22->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table7 = manage(new class Gtk::Table(3, 2, false));
   waffen_clist_auswahl->set_column_title(0, "Lernpunkte");
   waffen_clist_auswahl->set_column_width(0, 80);
   waffen_clist_auswahl->set_column_title(1, "Voraussetzung");
   waffen_clist_auswahl->set_column_justification(1, GTK_JUSTIFY_RIGHT);
   waffen_clist_auswahl->set_column_width(1, 80);
   waffen_clist_auswahl->set_column_title(2, "Waffe");
   waffen_clist_auswahl->set_column_width(2, 80);
   waffen_clist_auswahl->set_column_title(3, "Erfolgswert");
   waffen_clist_auswahl->set_column_justification(3, GTK_JUSTIFY_RIGHT);
   waffen_clist_auswahl->set_column_width(3, 80);
   waffen_clist_auswahl->set_column_title(4, "Grundkenntnisse ");
   waffen_clist_auswahl->set_column_justification(4, GTK_JUSTIFY_RIGHT);
   waffen_clist_auswahl->set_column_width(4, 80);
   waffen_clist_auswahl->column_titles_show();
   scrolledwindow3->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow3->add(*waffen_clist_auswahl);
   label138->set_alignment(0.5, 0.5);
   label138->set_padding(0, 0);
   waffen_auswahl_lernpunkte->set_alignment(0.5, 0.5);
   waffen_auswahl_lernpunkte->set_padding(11, 0);
   pixmap22->set_alignment(0.5, 0.5);
   pixmap22->set_padding(0, 0);
   hbox9->pack_start(*label138, false, false, 0);
   hbox9->pack_start(*waffen_auswahl_lernpunkte, false, false, 0);
   hbox9->pack_start(*pixmap22);
   toolbar22->set_border_width(5);
   toolbar22->set_space_size(5);
   toolbar22->set_tooltips(true);
   table7->attach(*scrolledwindow3, 0, 2, 0, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table7->attach(*hbox9, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
   table7->attach(*toolbar22, 1, 2, 2, 3, GTK_FILL, 0, 0, 0);
   Waffen_auswahl->set_usize(600, 400);
   Waffen_auswahl->set_title("Waffen");
   Waffen_auswahl->add(*table7);
   waffen_clist_auswahl->show();
   scrolledwindow3->show();
   label138->show();
   waffen_auswahl_lernpunkte->show();
   pixmap22->show();
   hbox9->show();
   toolbar22->show();
   table7->show();
   Waffen_auswahl->show();
   waffen_clist_auswahl->select_row.connect(SigC::slot(static_cast<class Waffen_auswahl*>(this), &Waffen_auswahl::on_waffen_clist_auswahl_select_row));
   waffen_clist_auswahl->unselect_row.connect(SigC::slot(static_cast<class Waffen_auswahl*>(this), &Waffen_auswahl::on_waffen_clist_auswahl_unselect_row));
   button51->clicked.connect(SigC::slot(static_cast<class Waffen_auswahl*>(this), &Waffen_auswahl::on_close_waffen_clicked));
}

Waffen_auswahl_glade::~Waffen_auswahl_glade()
{   
}
