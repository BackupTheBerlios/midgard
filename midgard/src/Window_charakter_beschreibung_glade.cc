// generated 2001/4/30 17:29:58 CEST by thoma@tiger.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/Window_charakter_beschreibung.cc

#include "config.h"
#include "Window_charakter_beschreibung.hh"
#include <gtk--/scrolledwindow.h>
#include <gtk--/button.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/DescrChar-trans-50.xpm"
#include "../pixmaps/PrintChar-trans-50.xpm"
#include "../pixmaps/Schliessen1-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

Window_charakter_beschreibung_glade::Window_charakter_beschreibung_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_charakter_beschreibung = this;
   text_charakter_beschreibung = manage(new class Gtk::Text());
   
   Gtk::ScrolledWindow *scrolledwindow12 = manage(new class Gtk::ScrolledWindow());
   Gtk::Toolbar *toolbar12 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_TEXT));
   Gtk::Button *button38 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar12->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "‹bernehmen", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(DescrChar_trans_50_xpm))->gtkobj()), 0, 0));
   Gtk::Button *button39 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar12->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "‹bernehmen und Drucken", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(PrintChar_trans_50_xpm))->gtkobj()), 0, 0));
   toolbar12->tools().push_back(Gtk::Toolbar_Helpers::Space());
   
   Gtk::Button *button40 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar12->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Abbrechen", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Schliessen1_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table23 = manage(new class Gtk::Table(2, 4, false));
   text_charakter_beschreibung->set_usize(734, 340);
   text_charakter_beschreibung->set_editable(true);
   text_charakter_beschreibung->set_word_wrap(false);
   text_charakter_beschreibung->set_point(0);
   scrolledwindow12->set_policy(GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
   scrolledwindow12->add(*text_charakter_beschreibung);
   toolbar12->set_space_size(10);
   toolbar12->set_tooltips(true);
   table23->attach(*scrolledwindow12, 0, 4, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table23->attach(*toolbar12, 0, 4, 1, 2, 0, 0, 0, 5);
   Window_charakter_beschreibung->set_title("Charakter Beschreibung");
   Window_charakter_beschreibung->add(*table23);
   text_charakter_beschreibung->show();
   scrolledwindow12->show();
   toolbar12->show();
   table23->show();
   Window_charakter_beschreibung->show();
   button38->clicked.connect(SigC::slot(static_cast<class Window_charakter_beschreibung*>(this), &Window_charakter_beschreibung::on_charakter_beschreibung_uebernehmen_clicked));
   button39->clicked.connect(SigC::slot(static_cast<class Window_charakter_beschreibung*>(this), &Window_charakter_beschreibung::on_charakter_beschreibung_drucken_clicked));
   button40->clicked.connect(SigC::slot(static_cast<class Window_charakter_beschreibung*>(this), &Window_charakter_beschreibung::on_charakter_beschreibung_abbrechen_clicked));
}

Window_charakter_beschreibung_glade::~Window_charakter_beschreibung_glade()
{   
}
