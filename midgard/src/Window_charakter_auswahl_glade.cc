// generated 2001/4/29 19:11:59 CEST by thoma@linux.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.3
//
// Please modify the corresponding derived classes in ./src/Window_charakter_auswahl.cc

#include "config.h"
#include "Window_charakter_auswahl.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/LoadChar-trans-50.xpm"
#include <gtk--/button.h>
#include "../pixmaps/Schliessen1-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/box.h>

Window_charakter_auswahl_glade::Window_charakter_auswahl_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_charakter_auswahl = this;
   Gtk::Label *label251 = manage(new class Gtk::Label("In der Datenbank vorhandene Charaktere"));
   clist_charakter_auswahl = manage(new class Gtk::CList(2));
   
   Gtk::ScrolledWindow *scrolledwindow13 = manage(new class Gtk::ScrolledWindow());
   checkbutton_loeschen = manage(new class Gtk::CheckButton("Charakter l�schen"));
   
   Gtk::Pixmap *pixmap19 = manage(new class Gtk::Pixmap(LoadChar_trans_50_xpm));
   Gtk::Toolbar *toolbar25 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button54 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar25->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Schliessen1_50_xpm))->gtkobj()), 0, 0));
   Gtk::HBox *hbox16 = manage(new class Gtk::HBox(false, 0));
   Gtk::VBox *vbox5 = manage(new class Gtk::VBox(false, 0));
   label251->set_alignment(0.5, 0.5);
   label251->set_padding(30, 0);
   clist_charakter_auswahl->set_column_title(0, "Name");
   clist_charakter_auswahl->set_column_width(0, 80);
   clist_charakter_auswahl->set_column_title(1, "Version");
   clist_charakter_auswahl->set_column_width(1, 80);
   clist_charakter_auswahl->column_titles_show();
   scrolledwindow13->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow13->add(*clist_charakter_auswahl);
   pixmap19->set_alignment(0.5, 0.5);
   pixmap19->set_padding(0, 0);
   toolbar25->set_border_width(5);
   toolbar25->set_space_size(5);
   toolbar25->set_tooltips(true);
   hbox16->pack_start(*checkbutton_loeschen, false, false, 3);
   hbox16->pack_start(*pixmap19);
   hbox16->pack_start(*toolbar25, false, false, 0);
   vbox5->pack_start(*label251, false, false, 0);
   vbox5->pack_start(*scrolledwindow13);
   vbox5->pack_start(*hbox16, false, true, 0);
   Window_charakter_auswahl->set_usize(-1, 260);
   Window_charakter_auswahl->grab_focus();
   Window_charakter_auswahl->set_title("Charakter auswahl");
   Window_charakter_auswahl->add(*vbox5);
   label251->show();
   clist_charakter_auswahl->show();
   scrolledwindow13->show();
   checkbutton_loeschen->show();
   pixmap19->show();
   toolbar25->show();
   hbox16->show();
   vbox5->show();
   Window_charakter_auswahl->show();
   clist_charakter_auswahl->select_row.connect(SigC::slot(static_cast<class Window_charakter_auswahl*>(this), &Window_charakter_auswahl::on_clist_charakter_auswahl_select_row));
   button54->clicked.connect(SigC::slot(static_cast<class Window_charakter_auswahl*>(this), &Window_charakter_auswahl::on_auswahl_abbruch_clicked));
}

Window_charakter_auswahl_glade::~Window_charakter_auswahl_glade()
{   
}
