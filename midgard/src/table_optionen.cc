
#include "config.h"
#include "table_optionen.hh"
#include "midgard_CG.hh"
#include "xml_fileselection.hh"

void table_optionen::init()
{
 entry_html->set_text(hauptfenster->getOptionen()->getString(Magus_Optionen::html_viewer));
 entry_tmp_verz->set_text(hauptfenster->getOptionen()->getString(Magus_Optionen::tmppfad));
 entry_speicher_verz->set_text(hauptfenster->getOptionen()->getString(Magus_Optionen::speicherpfad));
 spinbutton_datei_history->set_value(hauptfenster->getOptionen()->DateiHistory());
 
 frame_drucken->init();
 frame_globale_optionen->init();
 frame_ansicht->init();
 frame_icons->init();
}


void table_optionen::set_Hauptfenster(midgard_CG *h) 
{
  hauptfenster=h;
  frame_drucken->set_Hauptfenster(h);
  frame_globale_optionen->set_Hauptfenster(h);
  frame_ansicht->set_Hauptfenster(h);
  frame_icons->set_Hauptfenster(h);
}



void table_optionen::on_entry_html_changed()
{  
 hauptfenster->getOptionen()->setString(Magus_Optionen::html_viewer,
      entry_html->get_text());
}

void table_optionen::on_entry_tmp_verz_changed()
{  
 hauptfenster->getOptionen()->setString(Magus_Optionen::tmppfad,
      entry_tmp_verz->get_text());
}

void table_optionen::on_entry_speicher_verz_changed()
{  
 hauptfenster->getOptionen()->setString(Magus_Optionen::speicherpfad,
      entry_speicher_verz->get_text());
}

void table_optionen::on_spinbutton_datei_history_changed()
{
  spinbutton_datei_history->update();
  hauptfenster->getOptionen()->setDateiHistory(
      spinbutton_datei_history->get_value_as_int());
}


void table_optionen::on_button_html_browser_clicked()
{
 (new xml_fileselection(hauptfenster,xml_fileselection::html));
}
void table_optionen::html_browser_selected(const std::string& dateiname)
{entry_html->set_text(dateiname);}

void table_optionen::on_button_tmp_clicked()
{
 (new xml_fileselection(hauptfenster,xml_fileselection::temp));
}
void table_optionen::tmp_selected(const std::string& dateiname)
{entry_tmp_verz->set_text(dateiname);}

void table_optionen::on_button_speicherplatz_clicked()
{
 (new xml_fileselection(hauptfenster,xml_fileselection::speichern));
}
void table_optionen::speicherplatz_selected(const std::string& dateiname)
{entry_speicher_verz->set_text(dateiname);}

