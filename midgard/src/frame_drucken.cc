// generated 2002/4/14 11:16:16 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to frame_drucken.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "frame_drucken.hh"

#include<list>
#include "Optionen.hh"
#include "midgard_CG.hh"
#include "xml_fileselection.hh"

void frame_drucken::set_Hauptfenster(midgard_CG *h)
{
  hauptfenster=h;
}


void frame_drucken::init()
{
  bool_changed=false;
  if(!hauptfenster) assert(!"");
  if(!(hauptfenster->getOptionen())) assert(!"");
  Gtk::Table *table=manage(new Gtk::Table(0,0,false));
  std::list<Midgard_Optionen::st_pdfViewer> L=hauptfenster->getOptionen()->getPDF();  
  Gtk::RadioButton::Group _RadioMGroup_pdfViewer;
  int count=0;
  for(std::list<Midgard_Optionen::st_pdfViewer>::const_iterator i=L.begin();i!=L.end();++i)
   {
     Gtk::RadioButton *rmi=manage(new class Gtk::RadioButton(_RadioMGroup_pdfViewer,i->text,0,0.5));
     rmi->set_active(i->active);
     rmi->toggled.connect(SigC::bind(SigC::slot(this,&frame_drucken::element_activate),rmi,i->index));
     table->attach(*rmi,0,1,count,count+1,GTK_FILL,0,0,0);
     if(i->index==Midgard_Optionen::anderer) 
      { Gtk::Button *b=manage(new class Gtk::Button("..."));
        b->clicked.connect(SigC::slot(this,&frame_drucken::on_button_pdf_viewer_clicked));
        table->attach(*b,1,2,count+1,count+2,GTK_FILL,0,0,0);
      }
     ++count;
   }
 entry=manage(new class Gtk::Entry());
 entry->changed.connect(SigC::slot(this,&frame_drucken::entry_changed));
 entry->set_text(hauptfenster->getOptionen()->Viewer());
 entry->focus_out_event.connect(SigC::slot(this,&frame_drucken::entry_focus_out));
 table->attach(*entry,0,1,count,count+1,GTK_FILL,0,0,0);
 table->show_all();
 add(*table);
}


void frame_drucken::element_activate(Gtk::RadioButton *rb,Midgard_Optionen::pdfViewerIndex index)
{
 if(rb->get_active())
  {
   hauptfenster->getOptionen()->pdfViewer_setzen_from_menu(index);       
   if(index==Midgard_Optionen::anderer) 
       hauptfenster->getOptionen()->setString(Midgard_Optionen::pdf_viewer,entry->get_text());
  }
}

void frame_drucken::entry_changed()
{
  bool_changed=true;
  hauptfenster->getOptionen()->pdfViewer_setzen_from_menu(Midgard_Optionen::anderer); 
  hauptfenster->getOptionen()->setString(Midgard_Optionen::pdf_viewer,entry->get_text());    
}

gint frame_drucken::entry_focus_out(GdkEventFocus *ev)
{
  if(bool_changed) init();
  return 0;
}

void frame_drucken::on_button_pdf_viewer_clicked()
{
#ifndef __MINGW32__
 manage
#else
 delete
#endif
 (new xml_fileselection(hauptfenster,xml_fileselection::pdfviewer));
}


void frame_drucken::pdf_viewer_selected(const std::string& dateiname)
{entry->set_text(dateiname);}
