// generated 2001/4/20 20:28:01 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_hilfe.cc

#include "config.h"
#include "Window_hilfe.hh"
#include <gtk--/scrolledwindow.h>
#include <gtk--/button.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

Window_hilfe_glade::Window_hilfe_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_hilfe = this;
   text_hilfe = manage(new class Gtk::Text());
   
   Gtk::ScrolledWindow *scrolledwindow25 = manage(new class Gtk::ScrolledWindow());
   Gtk::Toolbar *toolbar27 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button56 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar27->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table35 = manage(new class Gtk::Table(2, 4, false));
   text_hilfe->set_usize(700, 348);
   text_hilfe->set_editable(false);
   text_hilfe->set_word_wrap(false);
   text_hilfe->set_point(0);
   scrolledwindow25->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow25->add(*text_hilfe);
   toolbar27->set_border_width(5);
   toolbar27->set_space_size(5);
   toolbar27->set_tooltips(true);
   table35->attach(*scrolledwindow25, 0, 4, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table35->attach(*toolbar27, 3, 4, 1, 2, 0, 0, 0, 0);
   Window_hilfe->set_title("Hilfe");
   Window_hilfe->add(*table35);
   text_hilfe->show();
   scrolledwindow25->show();
   toolbar27->show();
   table35->show();
   Window_hilfe->show();
   button56->clicked.connect(SigC::slot(static_cast<class Window_hilfe*>(this), &Window_hilfe::on_button_hilfe_schliessen_clicked));
}

Window_hilfe_glade::~Window_hilfe_glade()
{   
}
