// generated 2002/10/1 12:06:57 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/table_beschreibung.cc

#include "config.h"
#include "table_beschreibung.hh"
#include <gtk--/pixmap.h>
#include "../pixmaps/PrintChar-trans-50.xpm"
#include <gtk--/label.h>
#include <gtk--/box.h>
#include "../pixmaps/MAGUS_Logo_Small.xpm"
#include <gtk--/adjustment.h>
#include <gtk--/table.h>
#include <gtk--/viewport.h>
#include <gtk--/scrolledwindow.h>

table_beschreibung_glade::table_beschreibung_glade(GlademmData *_data
) : Gtk::Table(2, 2, false)
{  table_beschreibung = this;
   
   Gtk::Pixmap *pixmap147 = manage(new class Gtk::Pixmap(PrintChar_trans_50_xpm));
   Gtk::Label *label566 = manage(new class Gtk::Label("Beschreibung\n"
		"Drucken"));
   Gtk::HBox *hbox70 = manage(new class Gtk::HBox(false, 0));
   button_beschreibung_drucken = manage(new class Gtk::Button());
   
   Gtk::Pixmap *pixmap148 = manage(new class Gtk::Pixmap(MAGUS_Logo_Small_xpm));
   label_grafik = manage(new class Gtk::Label("Abbildung"));
   
   Gtk::HBox *hbox71 = manage(new class Gtk::HBox(false, 0));
   button_grafik = manage(new class Gtk::Button());
   
   Gtk::Label *label398 = manage(new class Gtk::Label("(Die Abenteurerbeschreibung darf s�mtliche LaTeX Befehle enthalten)"));
   Gtk::Label *label567 = manage(new class Gtk::Label("Breite des Bildes"));
   Gtk::Adjustment *spinbutton_pix_breite_adj = manage(new class Gtk::Adjustment(8, 3, 13, 1, 10, 10));
   spinbutton_pix_breite = manage(new class Gtk::SpinButton(*spinbutton_pix_breite_adj, 1, 0));
   
   Gtk::Label *label568 = manage(new class Gtk::Label("cm"));
   Gtk::Table *table135 = manage(new class Gtk::Table(2, 2, false));
   Gtk::Table *table134 = manage(new class Gtk::Table(2, 3, false));
   text_charakter_beschreibung = manage(new class Gtk::Text());
   
   Gtk::Viewport *viewport43 = manage(new class Gtk::Viewport());
   Gtk::ScrolledWindow *scrolledwindow80 = manage(new class Gtk::ScrolledWindow());
   pixmap147->set_alignment(0.5,0.5);
   pixmap147->set_padding(0,0);
   label566->set_alignment(0.5,0.5);
   label566->set_padding(0,0);
   label566->set_justify(GTK_JUSTIFY_CENTER);
   label566->set_line_wrap(false);
   hbox70->pack_start(*pixmap147, false, true, 0);
   hbox70->pack_start(*label566, false, false, 0);
   button_beschreibung_drucken->set_flags(GTK_CAN_FOCUS);
   button_beschreibung_drucken->set_relief(GTK_RELIEF_NORMAL);
   button_beschreibung_drucken->add(*hbox70);
   pixmap148->set_alignment(0.5,0.5);
   pixmap148->set_padding(0,0);
   label_grafik->set_alignment(0.5,0.5);
   label_grafik->set_padding(0,0);
   label_grafik->set_justify(GTK_JUSTIFY_CENTER);
   label_grafik->set_line_wrap(false);
   hbox71->pack_start(*pixmap148);
   hbox71->pack_start(*label_grafik, false, false, 0);
   button_grafik->set_flags(GTK_CAN_FOCUS);
   button_grafik->set_relief(GTK_RELIEF_NORMAL);
   button_grafik->add(*hbox71);
   label398->set_alignment(0,0.5);
   label398->set_padding(0,0);
   label398->set_justify(GTK_JUSTIFY_CENTER);
   label398->set_line_wrap(false);
   label567->set_alignment(0,0.5);
   label567->set_padding(0,0);
   label567->set_justify(GTK_JUSTIFY_CENTER);
   label567->set_line_wrap(false);
   spinbutton_pix_breite->set_flags(GTK_CAN_FOCUS);
   spinbutton_pix_breite->set_update_policy(GTK_UPDATE_ALWAYS);
   spinbutton_pix_breite->set_numeric(false);
   spinbutton_pix_breite->set_digits(0);
   spinbutton_pix_breite->set_wrap(false);
   spinbutton_pix_breite->set_snap_to_ticks(false);
   label568->set_alignment(0,0.5);
   label568->set_padding(0,0);
   label568->set_justify(GTK_JUSTIFY_CENTER);
   label568->set_line_wrap(false);
   table135->set_row_spacings(0);
   table135->set_col_spacings(0);
   table135->attach(*label567, 0, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table135->attach(*spinbutton_pix_breite, 0, 1, 1, 2, 0, 0, 0, 0);
   table135->attach(*label568, 1, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table134->set_row_spacings(0);
   table134->set_col_spacings(0);
   table134->attach(*button_beschreibung_drucken, 0, 1, 0, 1, 0, 0, 0, 0);
   table134->attach(*button_grafik, 1, 2, 0, 1, 0, 0, 0, 0);
   table134->attach(*label398, 0, 3, 1, 2, GTK_FILL, 0, 0, 0);
   table134->attach(*table135, 2, 3, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
   text_charakter_beschreibung->set_flags(GTK_CAN_FOCUS);
   text_charakter_beschreibung->set_editable(true);
   viewport43->set_shadow_type(GTK_SHADOW_NONE);
   viewport43->add(*text_charakter_beschreibung);
   scrolledwindow80->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
   scrolledwindow80->add(*viewport43);
   table_beschreibung->set_row_spacings(0);
   table_beschreibung->set_col_spacings(0);
   table_beschreibung->attach(*table134, 0, 1, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 6);
   table_beschreibung->attach(*scrolledwindow80, 0, 2, 1, 2, GTK_EXPAND|GTK_SHRINK|GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);
   pixmap147->show();
   label566->show();
   hbox70->show();
   button_beschreibung_drucken->show();
   pixmap148->show();
   label_grafik->show();
   hbox71->show();
   button_grafik->show();
   label398->show();
   label567->show();
   spinbutton_pix_breite->show();
   label568->show();
   table135->show();
   table134->show();
   text_charakter_beschreibung->show();
   viewport43->show();
   scrolledwindow80->show();
   table_beschreibung->show();
   button_beschreibung_drucken->clicked.connect(SigC::slot(static_cast<class table_beschreibung*>(this), &table_beschreibung::on_button_beschreibung_drucken_clicked));
   button_grafik->clicked.connect(SigC::slot(static_cast<class table_beschreibung*>(this), &table_beschreibung::on_button_grafik_clicked));
   spinbutton_pix_breite->focus_out_event.connect(SigC::slot(static_cast<class table_beschreibung*>(this), &table_beschreibung::on_spinbutton_pix_breite_focus_out_event));
   spinbutton_pix_breite->focus_in_event.connect(SigC::slot(static_cast<class table_beschreibung*>(this), &table_beschreibung::on_spinbutton_pix_breite_focus_in_event));
   text_charakter_beschreibung->focus_out_event.connect(SigC::slot(static_cast<class table_beschreibung*>(this), &table_beschreibung::on_text_charakter_beschreibung_focus_out_event));
}

table_beschreibung_glade::~table_beschreibung_glade()
{  
}
