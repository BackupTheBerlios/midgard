// generated 2001/4/10 8:12:37 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_Geld_eingeben.cc

#include "config.h"
#include "Window_Geld_eingeben.hh"
#include <gtk--/label.h>
#include <gtk--/adjustment.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Money-50.xpm"
#include <gtk--/button.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>

Window_Geld_eingeben_glade::Window_Geld_eingeben_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_Geld_eingeben = this;
   Gtk::Label *label293 = manage(new class Gtk::Label("Geldbetrag eingeben"));
   Gtk::Label *label294 = manage(new class Gtk::Label("Gold"));
   Gtk::Label *label295 = manage(new class Gtk::Label("Silber"));
   Gtk::Label *label296 = manage(new class Gtk::Label("Kupfer"));
   Gtk::Adjustment *spinbutton_gold_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_gold = manage(new class Gtk::SpinButton(*spinbutton_gold_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_silber_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_silber = manage(new class Gtk::SpinButton(*spinbutton_silber_adj, 1, 0));
   
   Gtk::Adjustment *spinbutton_kupfer_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   spinbutton_kupfer = manage(new class Gtk::SpinButton(*spinbutton_kupfer_adj, 1, 0));
   
   Gtk::Pixmap *pixmap12 = manage(new class Gtk::Pixmap(Money_50_xpm));
   Gtk::Toolbar *toolbar28 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button57 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar28->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table38 = manage(new class Gtk::Table(5, 2, false));
   label293->set_alignment(0, 0.5);
   label293->set_padding(0, 0);
   label294->set_alignment(0, 0.5);
   label294->set_padding(0, 0);
   label295->set_alignment(0, 0.5);
   label295->set_padding(0, 0);
   label296->set_alignment(0, 0.5);
   label296->set_padding(0, 0);
   spinbutton_gold->set_editable(true);
   spinbutton_gold->set_numeric(true);
   spinbutton_silber->set_editable(true);
   spinbutton_silber->set_numeric(true);
   spinbutton_kupfer->set_editable(true);
   spinbutton_kupfer->set_numeric(true);
   pixmap12->set_alignment(0.5, 0.5);
   pixmap12->set_padding(0, 0);
   toolbar28->set_border_width(5);
   toolbar28->set_space_size(5);
   toolbar28->set_tooltips(true);
   table38->attach(*label293, 0, 2, 0, 1, 0, 0, 5, 5);
   table38->attach(*label294, 0, 1, 1, 2, GTK_FILL, 0, 3, 0);
   table38->attach(*label295, 0, 1, 2, 3, GTK_FILL, 0, 3, 0);
   table38->attach(*label296, 0, 1, 3, 4, GTK_FILL, 0, 3, 0);
   table38->attach(*spinbutton_gold, 1, 2, 1, 2, GTK_EXPAND, 0, 0, 0);
   table38->attach(*spinbutton_silber, 1, 2, 2, 3, GTK_EXPAND, 0, 0, 0);
   table38->attach(*spinbutton_kupfer, 1, 2, 3, 4, GTK_EXPAND, 0, 0, 0);
   table38->attach(*pixmap12, 0, 1, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
   table38->attach(*toolbar28, 1, 2, 4, 5, GTK_FILL, 0, 0, 0);
   Window_Geld_eingeben->set_title("Geld");
   Window_Geld_eingeben->add(*table38);
   label293->show();
   label294->show();
   label295->show();
   label296->show();
   spinbutton_gold->show();
   spinbutton_silber->show();
   spinbutton_kupfer->show();
   pixmap12->show();
   toolbar28->show();
   table38->show();
   Window_Geld_eingeben->show();
   button57->clicked.connect(SigC::slot(static_cast<class Window_Geld_eingeben*>(this), &Window_Geld_eingeben::on_button_close_clicked));
}

Window_Geld_eingeben_glade::~Window_Geld_eingeben_glade()
{   
}
