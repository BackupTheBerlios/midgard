
#include "config.h"
#include "frame_drucken.hh"

#include<list>
#include "midgard_CG.hh"
#include "xml_fileselection.hh"

void frame_drucken::set_Hauptfenster(midgard_CG *h)
{
  hauptfenster=h;
}


void frame_drucken::init()
{
  bool_changed=false;
  assert(hauptfenster);
  Gtk::Table *table=Gtk::manage(new Gtk::Table(1,1,false));
  std::list<Magus_Optionen::st_pdfViewer> L=Programmoptionen.getPDF();  
  Gtk::RadioButton::Group _RadioMGroup_pdfViewer;
  int count=0;
  for(std::list<Magus_Optionen::st_pdfViewer>::const_iterator i=L.begin();i!=L.end();++i)
   {
     Gtk::RadioButton *rmi=Gtk::manage(new class Gtk::RadioButton(_RadioMGroup_pdfViewer,i->text));
     rmi->set_active(i->active);
     rmi->signal_toggled().connect(SigC::bind(SigC::slot(*this,&frame_drucken::element_activate),rmi,i->index));
     table->attach(*rmi,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     if(i->index==Magus_Optionen::anderer) 
      { Gtk::Button *b=Gtk::manage(new class Gtk::Button("..."));
        b->signal_clicked().connect(SigC::slot(*this,&frame_drucken::on_button_pdf_viewer_clicked));
        table->attach(*b,1,2,count+1,count+2,Gtk::FILL,Gtk::AttachOptions(0),0,0);
      }
     ++count;
   }
 entry=Gtk::manage(new class Gtk::Entry());
 entry->signal_changed().connect(SigC::slot(*this,&frame_drucken::entry_changed));
 entry->set_text(Programmoptionen.Viewer());
 entry->signal_focus_out_event().connect(SigC::slot(*this,&frame_drucken::entry_focus_out));
 table->attach(*entry,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
 table->show_all();
 add(*table);
}


void frame_drucken::element_activate(Gtk::RadioButton *rb,Magus_Optionen::pdfViewerIndex index)
{
 if(rb->get_active())
  {
   Programmoptionen.pdfViewer_setzen_from_menu(index);       
   if(index==Magus_Optionen::anderer) 
       Programmoptionen.setString(Magus_Optionen::pdf_viewer,entry->get_text());
  }
}

void frame_drucken::entry_changed()
{
  bool_changed=true;
  Programmoptionen.pdfViewer_setzen_from_menu(Magus_Optionen::anderer); 
  Programmoptionen.setString(Magus_Optionen::pdf_viewer,entry->get_text());    
}

bool frame_drucken::entry_focus_out(GdkEventFocus *ev)
{
  if(bool_changed) init();
  return 0;
}

void frame_drucken::on_button_pdf_viewer_clicked()
{
 (new xml_fileselection(hauptfenster,xml_fileselection::pdfviewer));
}


void frame_drucken::pdf_viewer_selected(const std::string& dateiname)
{entry->set_text(dateiname);}
