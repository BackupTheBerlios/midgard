// generated 2001/4/17 19:55:39 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/KiDo_auswahl.cc

#include "config.h"
#include "KiDo_auswahl.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/viewport.h>
#include <gtk--/button.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

KiDo_auswahl_glade::KiDo_auswahl_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *KiDo_auswahl = this;
   clist_kido_auswahl = manage(new class Gtk::CList(4));
   
   Gtk::ScrolledWindow *scrolledwindow48 = manage(new class Gtk::ScrolledWindow());
   Gtk::Viewport *viewport1 = manage(new class Gtk::Viewport());
   Gtk::ScrolledWindow *scrolledwindow47 = manage(new class Gtk::ScrolledWindow());
   label_kido_techniken = manage(new class Gtk::Label("Noch x Techniken ausw�hlen"));
   
   Gtk::Toolbar *toolbar26 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button55 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar26->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table52 = manage(new class Gtk::Table(2, 3, false));
   clist_kido_auswahl->set_column_title(0, "HoHo");
   clist_kido_auswahl->set_column_width(0, 80);
   clist_kido_auswahl->set_column_title(1, "Technik");
   clist_kido_auswahl->set_column_width(1, 80);
   clist_kido_auswahl->set_column_title(2, "AP");
   clist_kido_auswahl->set_column_justification(2, GTK_JUSTIFY_CENTER);
   clist_kido_auswahl->set_column_width(2, 80);
   clist_kido_auswahl->set_column_title(3, "FP");
   clist_kido_auswahl->set_column_justification(3, GTK_JUSTIFY_RIGHT);
   clist_kido_auswahl->set_column_width(3, 80);
   clist_kido_auswahl->column_titles_show();
   scrolledwindow48->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow48->add(*clist_kido_auswahl);
   viewport1->add(*scrolledwindow48);
   scrolledwindow47->set_usize(375, 440);
   scrolledwindow47->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow47->add(*viewport1);
   label_kido_techniken->set_alignment(0, 0.5);
   label_kido_techniken->set_padding(0, 0);
   toolbar26->set_border_width(5);
   toolbar26->set_space_size(5);
   toolbar26->set_tooltips(true);
   table52->attach(*scrolledwindow47, 0, 3, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table52->attach(*label_kido_techniken, 0, 1, 1, 2, GTK_FILL, 0, 0, 0);
   table52->attach(*toolbar26, 2, 3, 1, 2, 0, 0, 0, 0);
   KiDo_auswahl->set_title("KiDo");
   KiDo_auswahl->add(*table52);
   clist_kido_auswahl->show();
   scrolledwindow48->show();
   viewport1->show();
   scrolledwindow47->show();
   label_kido_techniken->show();
   toolbar26->show();
   table52->show();
   KiDo_auswahl->show();
   clist_kido_auswahl->select_row.connect(SigC::slot(static_cast<class KiDo_auswahl*>(this), &KiDo_auswahl::on_clist_kido_auswahl_select_row));
   clist_kido_auswahl->unselect_row.connect(SigC::slot(static_cast<class KiDo_auswahl*>(this), &KiDo_auswahl::on_clist_kido_auswahl_unselect_row));
   button55->clicked.connect(SigC::slot(static_cast<class KiDo_auswahl*>(this), &KiDo_auswahl::on_button_close_clicked));
}

KiDo_auswahl_glade::~KiDo_auswahl_glade()
{   
}
