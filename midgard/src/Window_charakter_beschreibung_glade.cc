// generated 2001/3/14 22:01:10 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_charakter_beschreibung.cc

#include "config.h"
#include "Window_charakter_beschreibung.hh"
#include <gtk--/scrolledwindow.h>
#include <gtk--/table.h>

Window_charakter_beschreibung_glade::Window_charakter_beschreibung_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_charakter_beschreibung = this;
   text_charakter_beschreibung = manage(new class Gtk::Text());
   
   Gtk::ScrolledWindow *scrolledwindow12 = manage(new class Gtk::ScrolledWindow());
   charakter_beschreibung_uebernehmen = manage(new class Gtk::Button("‹bernehmen"));
   charakter_beschreibung_abbrechen = manage(new class Gtk::Button("Abbrechen"));
   charakter_beschreibung_drucken = manage(new class Gtk::Button("‹bernehmen \n"
		"und Drucken"));
   
   Gtk::Table *table23 = manage(new class Gtk::Table(2, 4, false));
   text_charakter_beschreibung->set_usize(734, 340);
   text_charakter_beschreibung->set_editable(true);
   text_charakter_beschreibung->set_word_wrap(false);
   text_charakter_beschreibung->set_point(0);
   scrolledwindow12->set_policy(GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
   scrolledwindow12->add(*text_charakter_beschreibung);
   table23->attach(*scrolledwindow12, 0, 4, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table23->attach(*charakter_beschreibung_uebernehmen, 1, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table23->attach(*charakter_beschreibung_abbrechen, 3, 4, 1, 2, GTK_FILL, 0, 0, 0);
   table23->attach(*charakter_beschreibung_drucken, 2, 3, 1, 2, GTK_FILL, 0, 0, 0);
   Window_charakter_beschreibung->set_title("Charakter Beschreibung");
   Window_charakter_beschreibung->add(*table23);
   text_charakter_beschreibung->show();
   scrolledwindow12->show();
   charakter_beschreibung_uebernehmen->show();
   charakter_beschreibung_abbrechen->show();
   charakter_beschreibung_drucken->show();
   table23->show();
   Window_charakter_beschreibung->show();
   charakter_beschreibung_uebernehmen->clicked.connect(SigC::slot(static_cast<class Window_charakter_beschreibung*>(this), &Window_charakter_beschreibung::on_charakter_beschreibung_uebernehmen_clicked));
   charakter_beschreibung_abbrechen->clicked.connect(SigC::slot(static_cast<class Window_charakter_beschreibung*>(this), &Window_charakter_beschreibung::on_charakter_beschreibung_abbrechen_clicked));
   charakter_beschreibung_drucken->clicked.connect(SigC::slot(static_cast<class Window_charakter_beschreibung*>(this), &Window_charakter_beschreibung::on_charakter_beschreibung_drucken_clicked));
}

Window_charakter_beschreibung_glade::~Window_charakter_beschreibung_glade()
{   
}
