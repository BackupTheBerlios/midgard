// generated 2001/4/17 21:01:04 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Berufe_auswahl.cc

#include "config.h"
#include "Berufe_auswahl.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/box.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Job-trans-50.xpm"
#include <gtk--/button.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

Berufe_auswahl_glade::Berufe_auswahl_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Berufe_auswahl = this;
   berufe_clist_auswahl = manage(new class Gtk::CList(4));
   
   Gtk::ScrolledWindow *scrolledwindow5 = manage(new class Gtk::ScrolledWindow());
   Gtk::Label *label158 = manage(new class Gtk::Label("Lernpunkte"));
   beruf_auswahl_lernpunkte = manage(new class Gtk::Label("X"));
   
   Gtk::HBox *hbox11 = manage(new class Gtk::HBox(false, 0));
   Gtk::Pixmap *pixmap20 = manage(new class Gtk::Pixmap(Job_trans_50_xpm));
   Gtk::Toolbar *toolbar24 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button53 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar24->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table9 = manage(new class Gtk::Table(3, 3, false));
   berufe_clist_auswahl->set_column_title(0, "Lern-\n"
		"punkte");
   berufe_clist_auswahl->set_column_justification(0, GTK_JUSTIFY_RIGHT);
   berufe_clist_auswahl->set_column_width(0, 80);
   berufe_clist_auswahl->set_column_title(1, "Voraus-\n"
		"setzung");
   berufe_clist_auswahl->set_column_width(1, 80);
   berufe_clist_auswahl->set_column_title(2, "Beruf");
   berufe_clist_auswahl->set_column_width(2, 80);
   berufe_clist_auswahl->set_column_title(3, "Vorteile");
   berufe_clist_auswahl->set_column_width(3, 80);
   berufe_clist_auswahl->column_titles_show();
   scrolledwindow5->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow5->add(*berufe_clist_auswahl);
   label158->set_alignment(0.5, 0.5);
   label158->set_padding(0, 0);
   beruf_auswahl_lernpunkte->set_alignment(0.5, 0.5);
   beruf_auswahl_lernpunkte->set_padding(11, 0);
   hbox11->pack_start(*label158, false, false, 0);
   hbox11->pack_start(*beruf_auswahl_lernpunkte, false, false, 0);
   pixmap20->set_alignment(0.5, 0.5);
   pixmap20->set_padding(0, 0);
   toolbar24->set_border_width(5);
   toolbar24->set_space_size(5);
   toolbar24->set_tooltips(true);
   table9->attach(*scrolledwindow5, 0, 3, 0, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table9->attach(*hbox11, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
   table9->attach(*pixmap20, 1, 2, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
   table9->attach(*toolbar24, 2, 3, 2, 3, GTK_FILL, 0, 0, 0);
   Berufe_auswahl->set_usize(600, 400);
   Berufe_auswahl->set_title("Berufe");
   Berufe_auswahl->add(*table9);
   berufe_clist_auswahl->show();
   scrolledwindow5->show();
   label158->show();
   beruf_auswahl_lernpunkte->show();
   hbox11->show();
   pixmap20->show();
   toolbar24->show();
   table9->show();
   Berufe_auswahl->show();
   berufe_clist_auswahl->select_row.connect(SigC::slot(static_cast<class Berufe_auswahl*>(this), &Berufe_auswahl::on_berufe_clist_auswahl_select_row));
   berufe_clist_auswahl->unselect_row.connect(SigC::slot(static_cast<class Berufe_auswahl*>(this), &Berufe_auswahl::on_berufe_clist_auswahl_unselect_row));
   button53->clicked.connect(SigC::slot(static_cast<class Berufe_auswahl*>(this), &Berufe_auswahl::on_close_berufe_clicked));
}

Berufe_auswahl_glade::~Berufe_auswahl_glade()
{   
}
