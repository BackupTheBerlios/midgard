// generated 2002/4/16 8:33:14 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_optionen.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_optionen.hh"
#include "midgard_CG.hh"

void table_optionen::init()
{
 entry_html->set_text(hauptfenster->getOptionen()->getString(Midgard_Optionen::html_viewer));
 entry_tmp_verz->set_text(hauptfenster->getOptionen()->getString(Midgard_Optionen::tmppfad));
 entry_speicher_verz->set_text(hauptfenster->getOptionen()->getString(Midgard_Optionen::speicherpfad));
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
 hauptfenster->getOptionen()->setString(Midgard_Optionen::html_viewer,
      entry_html->get_text());
}

void table_optionen::on_entry_tmp_verz_changed()
{  
 hauptfenster->getOptionen()->setString(Midgard_Optionen::tmppfad,
      entry_tmp_verz->get_text());
}

void table_optionen::on_entry_speicher_verz_changed()
{  
 hauptfenster->getOptionen()->setString(Midgard_Optionen::speicherpfad,
      entry_speicher_verz->get_text());
}

void table_optionen::on_spinbutton_datei_history_changed()
{
  spinbutton_datei_history->update();
  hauptfenster->getOptionen()->setDateiHistory(
      spinbutton_datei_history->get_value_as_int());
}
