// generated 2002/4/14 21:33:05 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to frame_globale_optionen.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "frame_globale_optionen.hh"

#include<list>
#include "Optionen.hh"
#include "midgard_CG.hh"

void frame_globale_optionen::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}

void frame_globale_optionen::init()
{
 remove();
 if(!hauptfenster) assert(!"");
 if(!(hauptfenster->getOptionen())) assert(!"");
 Gtk::Table *table=manage(new Gtk::Table(0,0,false));
 std::list<Midgard_Optionen::st_OptionenCheck> L=hauptfenster->getOptionen()->getOptionenCheck();
 int count=0;
 for(std::list<Midgard_Optionen::st_OptionenCheck>::const_iterator i=L.begin();i!=L.end();++i)
  {
   Gtk::CheckButton *cb=manage(new Gtk::CheckButton(i->text,0,0.5));
   cb->set_active(i->active);
   cb->toggled.connect(SigC::bind(SigC::slot(this,&frame_globale_optionen::element_activate),cb,i->index));
   table->attach(*cb,0,1,count,count+1,GTK_FILL,0,0,0);
   ++count;
  } 
 table->show_all();
 add(*table);
}

void frame_globale_optionen::element_activate(Gtk::CheckButton *cb,Midgard_Optionen::OptionenCheckIndex index)
{
  hauptfenster->getOptionen()->OptionenCheck_setzen_from_menu(index,cb->get_active());
}


