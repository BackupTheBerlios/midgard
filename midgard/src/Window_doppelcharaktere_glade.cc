// generated 2001/5/14 14:50:20 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/Window_doppelcharaktere.cc

#include "config.h"
#include "Window_doppelcharaktere.hh"
#include <gtk--/button.h>
#include <gtk--/label.h>
#include <gtk--/table.h>

Window_doppelcharaktere_glade::Window_doppelcharaktere_glade(
) : Gtk::Window(GTK_WINDOW_POPUP)
{   
   
   Gtk::Window *Window_doppelcharaktere = this;
   Gtk::Button *button63 = manage(new class Gtk::Button("Nein"));
   Gtk::Label *label397 = manage(new class Gtk::Label("Soll dieser Elf ein Doppelklassencharakter sein?"));
   Gtk::Button *doppelklasse_button_ja = manage(new class Gtk::Button("Ja"));
   Gtk::Table *table64 = manage(new class Gtk::Table(2, 2, false));
   button63->set_usize(40, -1);
   label397->set_alignment(0, 0.5);
   label397->set_padding(0, 0);
   doppelklasse_button_ja->set_usize(40, -1);
   table64->attach(*button63, 1, 2, 1, 2, 0, 0, 0, 0);
   table64->attach(*label397, 0, 2, 0, 1, GTK_FILL, 0, 5, 5);
   table64->attach(*doppelklasse_button_ja, 0, 1, 1, 2, 0, 0, 0, 10);
   Window_doppelcharaktere->set_title("Doppelklasse ?");
   Window_doppelcharaktere->add(*table64);
   button63->show();
   label397->show();
   doppelklasse_button_ja->show();
   table64->show();
   Window_doppelcharaktere->show();
   button63->clicked.connect(SigC::slot(static_cast<class Window_doppelcharaktere*>(this), &Window_doppelcharaktere::on_doppelklasse_button_nein_clicked));
   doppelklasse_button_ja->clicked.connect(SigC::slot(static_cast<class Window_doppelcharaktere*>(this), &Window_doppelcharaktere::on_doppelklasse_button_ja_clicked));
}

Window_doppelcharaktere_glade::~Window_doppelcharaktere_glade()
{   
}
