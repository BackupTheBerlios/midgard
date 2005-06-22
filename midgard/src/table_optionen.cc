/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004-2005 Christof Petig
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
 ManuProC::Association(*entry_pdf).set_model(Programmoptionen->getString(Magus_Optionen::pdf_viewer));
 ManuProC::Association(*entry_html).set_model(Programmoptionen->getString(Magus_Optionen::html_viewer));
 ManuProC::Association(*entry_tmp_verz).set_model(Programmoptionen->getString(Magus_Optionen::tmppfad));
 ManuProC::Association(*entry_speicher_verz).set_model(Programmoptionen->getString(Magus_Optionen::speicherpfad));
 ManuProC::Association(*spinbutton_datei_history).set_model(Programmoptionen->DateiHistory());
 
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

void table_optionen::on_button_html_browser_clicked()
{WinFileReq::create(SigC::slot(*this,&table_optionen::html_browser_selected),
      Programmoptionen->getString(Magus_Optionen::html_viewer).Value(),
      "Programme (*.exe,*.bat)\0*.exe;*.bat\0",std::string(),
      "Welches Programm soll die HTML-Hilfe anzeigen?",true,
      hauptfenster);
}
void table_optionen::html_browser_selected(const std::string& dateiname)
{ Programmoptionen->getString(Magus_Optionen::html_viewer)=dateiname; }

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
      Programmoptionen->getString(Magus_Optionen::tmppfad).Value(),
      std::string(),std::string(),
      "In welchem Verzeichnis sollen Druckdateien erzeugt werden?",true,
      hauptfenster);
}
void table_optionen::tmp_selected(const std::string& dateiname)
{ Programmoptionen->getString(Magus_Optionen::tmppfad)=dateiname; }

void table_optionen::on_button_speicherplatz_clicked()
{WinFileReq::create(SigC::slot(*this,&table_optionen::speicherplatz_selected),
      Programmoptionen->getString(Magus_Optionen::speicherpfad).Value(),
      std::string(),std::string(),
      "In welchem Verzeichnis sollen die Abenteurer gespeichert werden?",true,
      hauptfenster);
}
void table_optionen::speicherplatz_selected(const std::string& dateiname)
{ Programmoptionen->getString(Magus_Optionen::speicherpfad)=dateiname; }
