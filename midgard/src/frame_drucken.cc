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
#include "frame_drucken.hh"

#include<list>
#include "midgard_CG.hh"
#include "xml_fileselection.hh"
#include <Association.h>
#include <string_Entry.hh>

void frame_drucken::set_Hauptfenster(midgard_CG *h)
{
  hauptfenster=h;
}


void frame_drucken::init()
{
  bool_changed=false;
  assert(hauptfenster);
  Gtk::Table *table=Gtk::manage(new Gtk::Table(1,1,false));
  std::list<Magus_Optionen::st_pdfViewer> L=Programmoptionen->getPDF();  
  Gtk::RadioButton::Group _RadioMGroup_pdfViewer;
  int count=0;
  for(std::list<Magus_Optionen::st_pdfViewer>::const_iterator i=L.begin();i!=L.end();++i)
   {
     Gtk::RadioButton *rmi=Gtk::manage(new class Gtk::RadioButton(_RadioMGroup_pdfViewer,i->text));
     ManuProC::Association(*rmi).set_model(Programmoptionen->pdfViewerCheck(i->index).active);
//     rmi->signal_toggled().connect(SigC::bind(SigC::slot(*this,&frame_drucken::element_activate),rmi,i->index));
     table->attach(*rmi,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     if(i->index==Magus_Optionen::anderer) 
      { Gtk::Button *b=Gtk::manage(new class Gtk::Button("..."));
        b->signal_clicked().connect(SigC::slot(*this,&frame_drucken::on_button_pdf_viewer_clicked));
        table->attach(*b,1,2,count+1,count+2,Gtk::FILL,Gtk::AttachOptions(0),0,0);
      }
     ++count;
   }
 entry=Gtk::manage(new class string_Entry(Programmoptionen->getString(Magus_Optionen::pdf_viewer)));
// entry->signal_changed().connect(SigC::slot(*this,&frame_drucken::entry_changed));
// entry->set_text(Programmoptionen->Viewer());
// entry->signal_focus_out_event().connect(SigC::slot(*this,&frame_drucken::entry_focus_out));
 table->attach(*entry,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
 table->show_all();
 add(*table);
}

#if 0
void frame_drucken::element_activate(Gtk::RadioButton *rb,Magus_Optionen::pdfViewerIndex index)
{
 if(rb->get_active())
  {
   Programmoptionen->pdfViewer_setzen_from_menu(index);       
   if(index==Magus_Optionen::anderer) 
       Programmoptionen->setString(Magus_Optionen::pdf_viewer,entry->get_text());
  }
}
#endif

#if 0
void frame_drucken::entry_changed()
{
  bool_changed=true;
  Programmoptionen->pdfViewer_setzen_from_menu(Magus_Optionen::anderer); 
  Programmoptionen->setString(Magus_Optionen::pdf_viewer,entry->get_text());    
}

bool frame_drucken::entry_focus_out(GdkEventFocus *ev)
{
  if(bool_changed) init();
  return 0;
}
#endif

void frame_drucken::on_button_pdf_viewer_clicked()
{
 xml_fileselection::create(hauptfenster,xml_fileselection::pdfviewer);
}

#if 0
void frame_drucken::pdf_viewer_selected(const std::string& dateiname)
{entry->set_text(dateiname);}
#endif
