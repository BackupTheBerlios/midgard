// generated 2001/4/21 10:07:39 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.4
//
// Please modify the corresponding derived classes in ./src/Window_Waffenbesitz.cc

#include "config.h"
#include "Window_Waffenbesitz.hh"
#include <gtk--/label.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/button.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/box.h>
#include "../pixmaps/Weapon-trans-50.xpm"
#include <gtk--/table.h>

Window_Waffenbesitz_glade::Window_Waffenbesitz_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Window_Waffenbesitz = this;
   clist_waffe_alt = manage(new class Gtk::CList(3));
   
   Gtk::ScrolledWindow *scrolledwindow38 = manage(new class Gtk::ScrolledWindow());
   clist_waffe_neu = manage(new class Gtk::CList(3));
   
   Gtk::ScrolledWindow *scrolledwindow39 = manage(new class Gtk::ScrolledWindow());
   Gtk::Label *label315 = manage(new class Gtk::Label("Besitz"));
   Gtk::Label *label316 = manage(new class Gtk::Label("Erwerb"));
   Gtk::Toolbar *toolbar29 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button58 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar29->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::HBox *hbox18 = manage(new class Gtk::HBox(false, 0));
   checkbutton_mag_waffenbonus = manage(new class Gtk::CheckButton("mag.Bonus angeben"));
   
   Gtk::HBox *hbox19 = manage(new class Gtk::HBox(false, 0));
   Gtk::Pixmap *pixmap9 = manage(new class Gtk::Pixmap(Weapon_trans_50_xpm));
   Gtk::Table *table43 = manage(new class Gtk::Table(3, 3, false));
   clist_waffe_alt->set_column_title(0, "Waffe");
   clist_waffe_alt->set_column_width(0, 80);
   clist_waffe_alt->set_column_title(1, "Schaden");
   clist_waffe_alt->set_column_width(1, 80);
   clist_waffe_alt->set_column_title(2, "mag.Bonus");
   clist_waffe_alt->set_column_width(2, 80);
   clist_waffe_alt->column_titles_show();
   scrolledwindow38->set_usize(266, 150);
   scrolledwindow38->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow38->add(*clist_waffe_alt);
   clist_waffe_neu->set_column_title(0, "Waffe");
   clist_waffe_neu->set_column_width(0, 80);
   clist_waffe_neu->set_column_title(1, "Schaden");
   clist_waffe_neu->set_column_width(1, 80);
   clist_waffe_neu->set_column_title(2, "Region");
   clist_waffe_neu->set_column_width(2, 80);
   clist_waffe_neu->column_titles_show();
   scrolledwindow39->set_usize(270, 150);
   scrolledwindow39->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow39->add(*clist_waffe_neu);
   label315->set_alignment(0, 0.5);
   label315->set_padding(0, 0);
   label316->set_alignment(0, 0.5);
   label316->set_padding(0, 0);
   toolbar29->set_border_width(5);
   toolbar29->set_space_size(5);
   toolbar29->set_tooltips(true);
   hbox18->pack_start(*toolbar29, false, false, 0);
   _tooltips.set_tip(*checkbutton_mag_waffenbonus, "Nach dem aktivieren: Waffe w�hlen", "");
   hbox19->pack_start(*checkbutton_mag_waffenbonus, false, false, 0);
   pixmap9->set_alignment(0.5, 0.5);
   pixmap9->set_padding(0, 0);
   table43->attach(*scrolledwindow38, 0, 1, 1, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table43->attach(*scrolledwindow39, 2, 3, 1, 2, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
   table43->attach(*label315, 0, 1, 0, 1, 0, 0, 0, 3);
   table43->attach(*label316, 2, 3, 0, 1, GTK_EXPAND, 0, 0, 3);
   table43->attach(*hbox18, 2, 3, 2, 3, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 3);
   table43->attach(*hbox19, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
   table43->attach(*pixmap9, 1, 2, 0, 1, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
   Window_Waffenbesitz->set_title("Waffenbesitz");
   Window_Waffenbesitz->set_policy(false, true, true);
   Window_Waffenbesitz->add(*table43);
   clist_waffe_alt->show();
   scrolledwindow38->show();
   clist_waffe_neu->show();
   scrolledwindow39->show();
   label315->show();
   label316->show();
   toolbar29->show();
   hbox18->show();
   checkbutton_mag_waffenbonus->show();
   hbox19->show();
   pixmap9->show();
   table43->show();
   Window_Waffenbesitz->show();
   clist_waffe_alt->select_row.connect(SigC::slot(static_cast<class Window_Waffenbesitz*>(this), &Window_Waffenbesitz::on_clist_waffe_alt_select_row));
   clist_waffe_neu->select_row.connect(SigC::slot(static_cast<class Window_Waffenbesitz*>(this), &Window_Waffenbesitz::on_clist_waffe_neu_select_row));
   button58->clicked.connect(SigC::slot(static_cast<class Window_Waffenbesitz*>(this), &Window_Waffenbesitz::on_button_close_clicked));
   checkbutton_mag_waffenbonus->toggled.connect(SigC::slot(static_cast<class Window_Waffenbesitz*>(this), &Window_Waffenbesitz::on_checkbutton_mag_waffenbonus_toggled));
}

Window_Waffenbesitz_glade::~Window_Waffenbesitz_glade()
{   
}
