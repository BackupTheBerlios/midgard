// generated 2003/12/8 8:43:15 CET by christof@puck.petig-baender.de
// using glademm V2.0.0c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- --image-provider=MagusImage midgard.glade
// for gtk 2.2.4 and gtkmm 2.2.8
//
// Please modify the corresponding derived classes in ./src/table_optionen.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
#include "table_optionen_glade.hh"
#include "frame_globale_optionen.hh"
#include "frame_ansicht.hh"
#include <gtkmm/label.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/button.h>
#include <gtkmm/table.h>
#include "frame_drucken.hh"
#include "frame_icons.hh"

table_optionen_glade::table_optionen_glade(GlademmData *gmm_data
) : Gtk::Table(2, 2, false)
{  table_optionen = this;
   frame_globale_optionen = Gtk::manage(new class frame_globale_optionen(gmm_data));
   frame_ansicht = Gtk::manage(new class frame_ansicht(gmm_data));
   
   Gtk::Label *label578 = Gtk::manage(new class Gtk::Label("HTML-Browser (für Hilfe)"));
   Gtk::Label *label576 = Gtk::manage(new class Gtk::Label("Temporäres Verzeichnis"));
   Gtk::Label *label577 = Gtk::manage(new class Gtk::Label("Speichern"));
   Gtk::Label *label575 = Gtk::manage(new class Gtk::Label("Pfade"));
   entry_html = Gtk::manage(new class Gtk::Entry());
   entry_tmp_verz = Gtk::manage(new class Gtk::Entry());
   entry_speicher_verz = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label599 = Gtk::manage(new class Gtk::Label("Anzahl der Dateien in der History"));
   Gtk::Adjustment *spinbutton_datei_history_adj = Gtk::manage(new class Gtk::Adjustment(1, 0, 9, 1, 10, 10));
   spinbutton_datei_history = Gtk::manage(new class Gtk::SpinButton(*spinbutton_datei_history_adj, 1, 0));
   
   Gtk::Button *button_html_browser = Gtk::manage(new class Gtk::Button("..."));
   Gtk::Button *button_tmp = Gtk::manage(new class Gtk::Button("..."));
   Gtk::Button *button_speicherplatz = Gtk::manage(new class Gtk::Button("..."));
   Gtk::Table *table147 = Gtk::manage(new class Gtk::Table(2, 2, false));
   frame_drucken = Gtk::manage(new class frame_drucken(gmm_data));
   frame_icons = Gtk::manage(new class frame_icons(gmm_data));
   
   Gtk::Table *table146 = Gtk::manage(new class Gtk::Table(2, 2, false));
   label578->set_alignment(0,0.5);
   label578->set_padding(0,0);
   label578->set_justify(Gtk::JUSTIFY_CENTER);
   label578->set_line_wrap(false);
   label578->set_use_markup(false);
   label578->set_selectable(false);
   label578->set_mnemonic_widget(*entry_html);
   label576->set_alignment(0,0.5);
   label576->set_padding(0,0);
   label576->set_justify(Gtk::JUSTIFY_CENTER);
   label576->set_line_wrap(false);
   label576->set_use_markup(false);
   label576->set_selectable(false);
   label576->set_mnemonic_widget(*entry_tmp_verz);
   label577->set_alignment(0,0.5);
   label577->set_padding(0,0);
   label577->set_justify(Gtk::JUSTIFY_CENTER);
   label577->set_line_wrap(false);
   label577->set_use_markup(false);
   label577->set_selectable(false);
   label575->set_alignment(0.5,0.5);
   label575->set_padding(0,0);
   label575->set_justify(Gtk::JUSTIFY_LEFT);
   label575->set_line_wrap(false);
   label575->set_use_markup(false);
   label575->set_selectable(false);
   entry_html->set_flags(Gtk::CAN_FOCUS);
   entry_html->set_visibility(true);
   entry_html->set_editable(true);
   entry_html->set_max_length(0);
   entry_html->set_text("mozilla ");
   entry_html->set_has_frame(true);
   entry_html->set_activates_default(false);
   entry_tmp_verz->set_flags(Gtk::CAN_FOCUS);
   entry_tmp_verz->set_visibility(true);
   entry_tmp_verz->set_editable(true);
   entry_tmp_verz->set_max_length(0);
   entry_tmp_verz->set_text("$TEMP");
   entry_tmp_verz->set_has_frame(true);
   entry_tmp_verz->set_activates_default(false);
   entry_speicher_verz->set_flags(Gtk::CAN_FOCUS);
   entry_speicher_verz->set_visibility(true);
   entry_speicher_verz->set_editable(true);
   entry_speicher_verz->set_max_length(0);
   entry_speicher_verz->set_text("~/magus");
   entry_speicher_verz->set_has_frame(true);
   entry_speicher_verz->set_activates_default(false);
   label599->set_alignment(0,0.5);
   label599->set_padding(0,0);
   label599->set_justify(Gtk::JUSTIFY_LEFT);
   label599->set_line_wrap(false);
   label599->set_use_markup(false);
   label599->set_selectable(false);
   spinbutton_datei_history->set_flags(Gtk::CAN_FOCUS);
   spinbutton_datei_history->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbutton_datei_history->set_numeric(false);
   spinbutton_datei_history->set_digits(0);
   spinbutton_datei_history->set_wrap(false);
   button_html_browser->set_flags(Gtk::CAN_FOCUS);
   button_html_browser->set_relief(Gtk::RELIEF_NORMAL);
   button_tmp->set_flags(Gtk::CAN_FOCUS);
   button_tmp->set_relief(Gtk::RELIEF_NORMAL);
   button_speicherplatz->set_flags(Gtk::CAN_FOCUS);
   button_speicherplatz->set_relief(Gtk::RELIEF_NORMAL);
   table147->set_row_spacings(0);
   table147->set_col_spacings(3);
   table147->attach(*label578, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*label576, 0, 1, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*label577, 0, 1, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*label575, 0, 2, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*entry_html, 1, 2, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*entry_tmp_verz, 1, 2, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*entry_speicher_verz, 1, 2, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*label599, 0, 1, 4, 5, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*spinbutton_datei_history, 1, 2, 4, 5, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*button_html_browser, 2, 3, 0, 1, Gtk::AttachOptions(), Gtk::AttachOptions(), 0, 0);
   table147->attach(*button_tmp, 2, 3, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table147->attach(*button_speicherplatz, 2, 3, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table146->set_row_spacings(0);
   table146->set_col_spacings(0);
   table146->attach(*frame_globale_optionen, 0, 1, 0, 1, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, 0, 0);
   table146->attach(*frame_ansicht, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
   table146->attach(*table147, 0, 2, 1, 2, Gtk::FILL, Gtk::FILL, 0, 3);
   table146->attach(*frame_drucken, 3, 4, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::FILL, 0, 0);
   table146->attach(*frame_icons, 2, 3, 0, 1, Gtk::EXPAND|Gtk::SHRINK|Gtk::FILL, Gtk::FILL, 0, 0);
   table_optionen->set_row_spacings(0);
   table_optionen->set_col_spacings(0);
   table_optionen->attach(*table146, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
   label578->show();
   label576->show();
   label577->show();
   label575->show();
   entry_html->show();
   entry_tmp_verz->show();
   entry_speicher_verz->show();
   label599->show();
   spinbutton_datei_history->show();
   button_html_browser->show();
   button_tmp->show();
   button_speicherplatz->show();
   table147->show();
   table146->show();
   table_optionen->show();
   entry_html->signal_changed().connect(SigC::slot(*this, &table_optionen_glade::on_entry_html_changed));
   entry_tmp_verz->signal_changed().connect(SigC::slot(*this, &table_optionen_glade::on_entry_tmp_verz_changed));
   entry_speicher_verz->signal_changed().connect(SigC::slot(*this, &table_optionen_glade::on_entry_speicher_verz_changed));
   spinbutton_datei_history->signal_changed().connect(SigC::slot(*this, &table_optionen_glade::on_spinbutton_datei_history_changed));
   button_html_browser->signal_clicked().connect(SigC::slot(*this, &table_optionen_glade::on_button_html_browser_clicked));
   button_tmp->signal_clicked().connect(SigC::slot(*this, &table_optionen_glade::on_button_tmp_clicked));
   button_speicherplatz->signal_clicked().connect(SigC::slot(*this, &table_optionen_glade::on_button_speicherplatz_clicked));
}

table_optionen_glade::~table_optionen_glade()
{  
}
