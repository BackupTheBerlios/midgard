// generated 2001/5/25 13:55:39 CEST by christof@puck.(none)
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_Waffe_Geld.cc

#include "config.h"
#include "Window_Waffe_Geld.hh"
#include <gtk--/separator.h>
#include <gtk--/label.h>
#include <gtk--/table.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Money-50.xpm"
#include <gtk--/button.h>
#include "../pixmaps/Dice-W100-trans-50.xpm"
#include "../pixmaps/Edit-trans-50.xpm"
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include "../pixmaps/Weapon-trans-50.xpm"
#include <gtk--/scrolledwindow.h>
#include "../pixmaps/Select-trans-50.xpm"

Window_Waffe_Geld_glade::Window_Waffe_Geld_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_Waffe_Geld = this;
   Gtk::RadioButton::Group _RadioBGroup_geld_waffen;
   radio_geld = manage(new class Gtk::RadioButton(_RadioBGroup_geld_waffen, "Geld"));
   radio_waffe = manage(new class Gtk::RadioButton(_RadioBGroup_geld_waffen, "Waffe"));
   label_waffen_geld = manage(new class Gtk::Label("6x f�r Waffen oder Geld w�rfeln"));
   
   Gtk::VSeparator *vseparator17 = manage(new class Gtk::VSeparator());
   Gtk::Label *label289 = manage(new class Gtk::Label("Kupfer"));
   Gtk::Label *label287 = manage(new class Gtk::Label("Gold"));
   Gtk::Label *label288 = manage(new class Gtk::Label("Silber"));
   gold = manage(new class Gtk::Label("0"));
   silber = manage(new class Gtk::Label("0"));
   kupfer = manage(new class Gtk::Label("0"));
   
   Gtk::Table *table37 = manage(new class Gtk::Table(3, 2, false));
   Gtk::Pixmap *pixmap10 = manage(new class Gtk::Pixmap(Money_50_xpm));
   Gtk::Toolbar *toolbar11 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH));
   Gtk::Button *button35 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar11->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "W�rfeln", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Dice_W100_trans_50_xpm))->gtkobj()), 0, 0));
   Gtk::Button *button36 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar11->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Ausw�hlen", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Edit_trans_50_xpm))->gtkobj()), 0, 0));
   toolbar11->tools().push_back(Gtk::Toolbar_Helpers::Space());
   
   Gtk::Button *button37 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar11->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "Schlie�en", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Pixmap *pixmap11 = manage(new class Gtk::Pixmap(Weapon_trans_50_xpm));
   Gtk::HSeparator *hseparator15 = manage(new class Gtk::HSeparator());
   clist_gewaehlte_waffen = manage(new class Gtk::CList(1));
   
   Gtk::ScrolledWindow *scrolledwindow35 = manage(new class Gtk::ScrolledWindow());
   Gtk::Pixmap *pixmap47 = manage(new class Gtk::Pixmap(Select_trans_50_xpm));
   Gtk::Table *table36 = manage(new class Gtk::Table(7, 5, false));
   label_waffen_geld->set_alignment(0, 0.5);
   label_waffen_geld->set_padding(0, 0);
   label289->set_alignment(0, 0.5);
   label289->set_padding(0, 0);
   label287->set_alignment(0, 0.5);
   label287->set_padding(0, 0);
   label288->set_alignment(0, 0.5);
   label288->set_padding(0, 0);
   gold->set_alignment(0, 0.5);
   gold->set_padding(0, 0);
   silber->set_alignment(0, 0.5);
   silber->set_padding(0, 0);
   kupfer->set_alignment(0, 0.5);
   kupfer->set_padding(0, 0);
   table37->attach(*label289, 0, 1, 2, 3, GTK_EXPAND|GTK_FILL, 0, 3, 0);
   table37->attach(*label287, 0, 1, 0, 1, GTK_EXPAND|GTK_FILL, 0, 3, 0);
   table37->attach(*label288, 0, 1, 1, 2, GTK_EXPAND|GTK_FILL, 0, 3, 0);
   table37->attach(*gold, 1, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table37->attach(*silber, 1, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table37->attach(*kupfer, 1, 2, 2, 3, GTK_FILL, 0, 0, 0);
   pixmap10->set_alignment(0.5, 0.5);
   pixmap10->set_padding(0, 0);
   toolbar11->set_space_size(10);
   toolbar11->set_tooltips(true);
   pixmap11->set_alignment(0.5, 0.5);
   pixmap11->set_padding(0, 0);
   clist_gewaehlte_waffen->set_column_title(0, "label286");
   clist_gewaehlte_waffen->set_column_width(0, 80);
   scrolledwindow35->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow35->add(*clist_gewaehlte_waffen);
   pixmap47->set_alignment(0.5, 0.5);
   pixmap47->set_padding(0, 0);
   table36->attach(*radio_geld, 1, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table36->attach(*radio_waffe, 1, 2, 2, 3, GTK_FILL, 0, 0, 0);
   table36->attach(*label_waffen_geld, 1, 5, 0, 1, GTK_FILL, 0, 6, 5);
   table36->attach(*vseparator17, 2, 3, 1, 3, GTK_FILL, GTK_FILL, 0, 0);
   table36->attach(*table37, 1, 2, 4, 5, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table36->attach(*pixmap10, 3, 4, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
   table36->attach(*toolbar11, 3, 5, 1, 3, GTK_FILL, 0, 0, 0);
   table36->attach(*pixmap11, 4, 5, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
   table36->attach(*hseparator15, 0, 5, 3, 4, GTK_FILL, GTK_FILL, 0, 5);
   table36->attach(*scrolledwindow35, 0, 5, 5, 6, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table36->attach(*pixmap47, 0, 1, 1, 3, GTK_FILL, GTK_FILL, 0, 0);
   Window_Waffe_Geld->set_title("Waffen & Geld");
   Window_Waffe_Geld->add(*table36);
   radio_geld->show();
   radio_waffe->show();
   label_waffen_geld->show();
   vseparator17->show();
   label289->show();
   label287->show();
   label288->show();
   gold->show();
   silber->show();
   kupfer->show();
   table37->show();
   pixmap10->show();
   toolbar11->show();
   pixmap11->show();
   hseparator15->show();
   clist_gewaehlte_waffen->show();
   scrolledwindow35->show();
   pixmap47->show();
   table36->show();
   Window_Waffe_Geld->show();
   button35->clicked.connect(SigC::slot(static_cast<class Window_Waffe_Geld*>(this), &Window_Waffe_Geld::on_button_wuerfeln_clicked));
   button36->clicked.connect(SigC::slot(static_cast<class Window_Waffe_Geld*>(this), &Window_Waffe_Geld::on_button_auswaehlen_clicked));
   button37->clicked.connect(SigC::slot(static_cast<class Window_Waffe_Geld*>(this), &Window_Waffe_Geld::on_button_close_clicked));
}

Window_Waffe_Geld_glade::~Window_Waffe_Geld_glade()
{   
}
