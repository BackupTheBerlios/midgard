// generated 2002/4/16 8:33:14 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.8
//
// Please modify the corresponding derived classes in ./src/table_optionen.cc

#include "config.h"
#include "table_optionen.hh"
#include <gtk--/label.h>
#include <gtk--/table.h>

table_optionen_glade::table_optionen_glade(GlademmData *_data
) : Gtk::Table(1, 1, false)
{  table_optionen = this;
   frame_globale_optionen = manage(new class frame_globale_optionen(_data));
   frame_drucken = manage(new class frame_drucken(_data));
   
   Gtk::Label *label578 = manage(new class Gtk::Label("HTML-Browser (f�r Hilfe)"));
   entry_html = manage(new class Gtk::Entry());
   
   Gtk::Label *label576 = manage(new class Gtk::Label("Tempor�res Verzeichnis"));
   Gtk::Label *label577 = manage(new class Gtk::Label("speichern"));
   entry_tmp_verz = manage(new class Gtk::Entry());
   entry_speicher_verz = manage(new class Gtk::Entry());
   
   Gtk::Label *label575 = manage(new class Gtk::Label("Pfade"));
   Gtk::Table *table147 = manage(new class Gtk::Table(4, 2, false));
   Gtk::Table *table146 = manage(new class Gtk::Table(3, 3, false));
   label578->set_alignment(0, 0.5);
   label578->set_padding(0, 0);
   entry_html->set_editable(true);
   entry_html->set_text("mozilla ");
   label576->set_alignment(0, 0.5);
   label576->set_padding(0, 0);
   label577->set_alignment(0, 0.5);
   label577->set_padding(0, 0);
   entry_tmp_verz->set_editable(true);
   entry_tmp_verz->set_text("$TEMP");
   entry_speicher_verz->set_editable(true);
   entry_speicher_verz->set_text("$HOME/magus");
   label575->set_alignment(0.5, 0.5);
   label575->set_padding(0, 0);
   label575->set_justify(GTK_JUSTIFY_LEFT);
   table147->attach(*label578, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table147->attach(*entry_html, 1, 2, 0, 1, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table147->attach(*label576, 0, 1, 2, 3, GTK_FILL, 0, 0, 0);
   table147->attach(*label577, 0, 1, 3, 4, GTK_FILL, 0, 0, 0);
   table147->attach(*entry_tmp_verz, 1, 2, 2, 3, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table147->attach(*entry_speicher_verz, 1, 2, 3, 4, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table147->attach(*label575, 0, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table146->attach(*frame_globale_optionen, 0, 1, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table146->attach(*frame_drucken, 1, 2, 0, 1, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
   table146->attach(*table147, 0, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
   table_optionen->attach(*table146, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
   label578->show();
   entry_html->show();
   label576->show();
   label577->show();
   entry_tmp_verz->show();
   entry_speicher_verz->show();
   label575->show();
   table147->show();
   table146->show();
   table_optionen->show();
   entry_html->changed.connect(SigC::slot(static_cast<class table_optionen*>(this), &table_optionen::on_entry_html_changed));
   entry_tmp_verz->changed.connect(SigC::slot(static_cast<class table_optionen*>(this), &table_optionen::on_entry_tmp_verz_changed));
   entry_speicher_verz->changed.connect(SigC::slot(static_cast<class table_optionen*>(this), &table_optionen::on_entry_speicher_verz_changed));
}

table_optionen_glade::~table_optionen_glade()
{  
}
