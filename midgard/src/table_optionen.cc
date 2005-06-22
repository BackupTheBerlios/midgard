/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "config.h"
#include "table_optionen.hh"
#include "midgard_CG.hh"
#include <WinFileReq.hh>
#include <libmagus/Magus_Optionen.hh>
#include <Association.h>

void table_optionen::init()
{
#warning besser als MVC realisieren
 ManuProC::Association(*entry_pdf).set_model(Programmoptionen->getString(Magus_Optionen::pdf_viewer));
 entry_html->set_text(Programmoptionen->getString(Magus_Optionen::html_viewer).Value());
 entry_tmp_verz->set_text(Programmoptionen->getString(Magus_Optionen::tmppfad).Value());
 entry_speicher_verz->set_text(Programmoptionen->getString(Magus_Optionen::speicherpfad).Value());
 spinbutton_datei_history->set_value(Programmoptionen->DateiHistory());
 
 frame_globale_optionen->init();
 frame_ansicht->init();
 frame_icons->init();
}


void table_optionen::set_Hauptfenster(midgard_CG *h) 
{
  hauptfenster=h;
  frame_globale_optionen->set_Hauptfenster(h);
  frame_ansicht->set_Hauptfenster(h);
  frame_icons->set_Hauptfenster(h);
}



void table_optionen::on_entry_html_changed()
{  
 Programmoptionen->setString(Magus_Optionen::html_viewer,
      entry_html->get_text());
}

void table_optionen::on_entry_tmp_verz_changed()
{  
 Programmoptionen->setString(Magus_Optionen::tmppfad,
      entry_tmp_verz->get_text());
}

void table_optionen::on_entry_speicher_verz_changed()
{  
 Programmoptionen->setString(Magus_Optionen::speicherpfad,
      entry_speicher_verz->get_text());
}

void table_optionen::on_spinbutton_datei_history_changed()
{
  spinbutton_datei_history->update();
  Programmoptionen->setDateiHistory(
      spinbutton_datei_history->get_value_as_int());
}


void table_optionen::on_button_html_browser_clicked()
{WinFileReq::create(SigC::slot(*this,&table_optionen::html_browser_selected),
      entry_html->get_text(),"Programme (*.exe,*.bat)\0*.exe;*.bat\0",std::string(),
      "Welches Programm soll die HTML-Hilfe anzeigen?",true,
      hauptfenster);
}
void table_optionen::html_browser_selected(const std::string& dateiname)
{entry_html->set_text(dateiname);}

void table_optionen::on_button_pdf_browser_clicked()
{WinFileReq::create(SigC::slot(*this,&table_optionen::pdf_viewer_selected),
      Programmoptionen->getString(Magus_Optionen::pdf_viewer).Value(),
      "Programme (*.exe,*.bat)\0*.exe;*.bat\0",std::string(),
      "Welches Programm soll die PDF-Dokumente anzeigen?",true,
      hauptfenster);
}
void table_optionen::pdf_viewer_selected(const std::string& dateiname)
{ Programmoptionen->getString(Magus_Optionen::pdf_viewer)=dateiname; }

void table_optionen::on_button_tmp_clicked()
{WinFileReq::create(SigC::slot(*this,&table_optionen::tmp_selected),
      entry_tmp_verz->get_text(),std::string(),std::string(),
      "In welchem Verzeichnis sollen Druckdateien erzeugt werden?",true,
      hauptfenster);
}
void table_optionen::tmp_selected(const std::string& dateiname)
{entry_tmp_verz->set_text(dateiname);}

void table_optionen::on_button_speicherplatz_clicked()
{WinFileReq::create(SigC::slot(*this,&table_optionen::speicherplatz_selected),
      entry_speicher_verz->get_text(),std::string(),std::string(),
      "In welchem Verzeichnis sollen die Abenteurer gespeichert werden?",true,
      hauptfenster);
}
void table_optionen::speicherplatz_selected(const std::string& dateiname)
{entry_speicher_verz->set_text(dateiname);}

