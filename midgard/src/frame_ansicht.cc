// generated 2002/4/23 21:23:31 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to frame_ansicht.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "frame_ansicht.hh"

#include<list>
#include "Optionen.hh"
#include "midgard_CG.hh"

void frame_ansicht::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}

void frame_ansicht::init()
{
 remove();
 if(!hauptfenster) assert(!"");
 if(!(hauptfenster->getOptionen())) assert(!"");
 Gtk::Table *table=manage(new Gtk::Table(0,0,false));  
 std::list<Midgard_Optionen::st_Ober> L=hauptfenster->getOptionen()->getOber();
 int count=0;
 for(std::list<Midgard_Optionen::st_Ober>::const_iterator i=L.begin();i!=L.end();++i)
  {
   Gtk::CheckButton *cb=manage(new Gtk::CheckButton(i->text,0,0.5));
   cb->set_active(i->active);
   cb->toggled.connect(SigC::bind(SigC::slot(this,&frame_ansicht::element_activate),cb,i->index));
   table->attach(*cb,0,1,count,count+1,GTK_FILL,0,0,0);
   ++count;
  }
 add(*table);
 show_all(); 
}



void frame_ansicht::element_activate(Gtk::CheckButton *cb,Midgard_Optionen::OberIndex index)
{
  hauptfenster->getOptionen()->Ober_setzen_from_menu(index,cb->get_active());
}   
