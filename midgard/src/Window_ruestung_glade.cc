// generated 2001/4/20 20:28:01 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_ruestung.cc

#include "config.h"
#include "Window_ruestung.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Armor-trans-50.xpm"
#include <gtk--/table.h>

Window_ruestung_glade::Window_ruestung_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_ruestung = this;
   clist_ruestung = manage(new class Gtk::CList(6));
   
   Gtk::ScrolledWindow *scrolledwindow36 = manage(new class Gtk::ScrolledWindow());
   Gtk::Pixmap *pixmap13 = manage(new class Gtk::Pixmap(Armor_trans_50_xpm));
   label_ruestung = manage(new class Gtk::Label("R�stung ausw�hlen"));
   
   Gtk::Table *table39 = manage(new class Gtk::Table(2, 3, false));
   clist_ruestung->set_column_title(0, "R�stung");
   clist_ruestung->set_column_width(0, 80);
   clist_ruestung->set_column_title(1, " ");
   clist_ruestung->set_column_width(1, 19);
   clist_ruestung->set_column_title(2, "LP\n"
		"Verlust");
   clist_ruestung->set_column_justification(2, GTK_JUSTIFY_CENTER);
   clist_ruestung->set_column_width(2, 80);
   clist_ruestung->set_column_title(3, "min.\n"
		"St�rke");
   clist_ruestung->set_column_justification(3, GTK_JUSTIFY_CENTER);
   clist_ruestung->set_column_width(3, 80);
   clist_ruestung->set_column_title(4, "RW\n"
		"Verlust");
   clist_ruestung->set_column_justification(4, GTK_JUSTIFY_CENTER);
   clist_ruestung->set_column_width(4, 80);
   clist_ruestung->set_column_title(5, "B\n"
		"Verlust");
   clist_ruestung->set_column_justification(5, GTK_JUSTIFY_CENTER);
   clist_ruestung->set_column_width(5, 80);
   clist_ruestung->column_titles_show();
   scrolledwindow36->set_usize(470, 195);
   scrolledwindow36->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow36->add(*clist_ruestung);
   pixmap13->set_alignment(0.5, 0.5);
   pixmap13->set_padding(0, 0);
   label_ruestung->set_alignment(0, 0.5);
   label_ruestung->set_padding(0, 0);
   table39->attach(*scrolledwindow36, 0, 3, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
   table39->attach(*pixmap13, 2, 3, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
   table39->attach(*label_ruestung, 0, 2, 0, 1, 0, 0, 3, 3);
   Window_ruestung->set_title("R�stung");
   Window_ruestung->add(*table39);
   clist_ruestung->show();
   scrolledwindow36->show();
   pixmap13->show();
   label_ruestung->show();
   table39->show();
   Window_ruestung->show();
   clist_ruestung->select_row.connect(SigC::slot(static_cast<class Window_ruestung*>(this), &Window_ruestung::on_clist_ruestung_select_row));
}

Window_ruestung_glade::~Window_ruestung_glade()
{   
}
