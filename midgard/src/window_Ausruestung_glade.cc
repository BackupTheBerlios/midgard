// generated 2001/11/25 16:04:19 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/window_Ausruestung.cc

#include "config.h"
#include "window_Ausruestung.hh"
#include <gtk--/menu.h>
#include <gtk--/menuitem.h>
#include <gtk--/button.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/PrintChar-trans-50.xpm"
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/label.h>
#include <gtk--/viewport.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/table.h>

window_Ausruestung_glade::window_Ausruestung_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *window_Ausruestung = this;
   optionmenu_art = manage(new class Gtk::OptionMenu());
   optionmenu_typ = manage(new class Gtk::OptionMenu());
   
   Gtk::Toolbar *toolbar39 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH));
   Gtk::Button *button_druck = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar39->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Drucken", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(PrintChar_trans_50_xpm))->gtkobj()), 0, 0));
   Gtk::Button *button_close = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar39->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Schließen", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   clist_preisliste = manage(new class Gtk::CList(3));
   
   Gtk::Viewport *viewport22 = manage(new class Gtk::Viewport());
   Gtk::ScrolledWindow *scrolledwindow58 = manage(new class Gtk::ScrolledWindow());
   Gtk::Table *table78 = manage(new class Gtk::Table(3, 3, false));
   {   Gtk::Menu *_m(manage(new Gtk::Menu()));
      Gtk::MenuItem *_mi;
      _mi = manage(new Gtk::MenuItem("Art"));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)0);
      optionmenu_art->set_menu(*_m);
      optionmenu_art->set_history(0);
   }
   {   Gtk::Menu *_m(manage(new Gtk::Menu()));
      Gtk::MenuItem *_mi;
      _mi = manage(new Gtk::MenuItem("Typ"));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)0);
      optionmenu_typ->set_menu(*_m);
      optionmenu_typ->set_history(0);
   }
   toolbar39->set_space_size(5);
   toolbar39->set_tooltips(true);
   clist_preisliste->set_column_title(0, "Name");
   clist_preisliste->set_column_width(0, 80);
   clist_preisliste->set_column_title(1, "Preis");
   clist_preisliste->set_column_justification(1, GTK_JUSTIFY_RIGHT);
   clist_preisliste->set_column_width(1, 80);
   clist_preisliste->set_column_title(2, "Einheit");
   clist_preisliste->set_column_width(2, 80);
   clist_preisliste->column_titles_show();
   viewport22->add(*clist_preisliste);
   scrolledwindow58->set_policy(GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
   scrolledwindow58->add(*viewport22);
   table78->attach(*optionmenu_art, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table78->attach(*optionmenu_typ, 1, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table78->attach(*toolbar39, 2, 3, 0, 1, GTK_FILL, 0, 0, 0);
   table78->attach(*scrolledwindow58, 0, 3, 1, 2, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   window_Ausruestung->set_title("Ausrüstung");
   window_Ausruestung->add(*table78);
   optionmenu_art->show();
   optionmenu_typ->show();
   toolbar39->show();
   clist_preisliste->show();
   viewport22->show();
   scrolledwindow58->show();
   table78->show();
   window_Ausruestung->show();
   button_druck->clicked.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::on_button_druck_clicked));
   button_close->clicked.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::on_button_close_clicked));
   clist_preisliste->select_row.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::on_clist_preisliste_select_row));
}

window_Ausruestung_glade::~window_Ausruestung_glade()
{   
}
