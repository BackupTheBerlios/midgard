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
#include <gtkmm/separator.h>
#include <int_SpinButton.hh>
#include <bool_CheckButton.hh>



void frame_globale_optionen::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}


void frame_globale_optionen::init()
{
 if(!hauptfenster) assert(!"");
 if(!(hauptfenster->getOptionen())) assert(!"");
 Gtk::Table *table=manage(new Gtk::Table(1,1,false));
 std::list<Magus_Optionen::st_OptionenCheck> &L=hauptfenster->getOptionen()->getOptionenCheck();
 int count=0;
 for(std::list<Magus_Optionen::st_OptionenCheck>::iterator i=L.begin();i!=L.end();++i)
  {
   bool_CheckButton *cb = manage(new bool_CheckButton(i->active,i->text));
   i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_globale_optionen::element_activate_C),i->index));
   Gtk::Table *t=manage(new Gtk::Table(1,1,false));
   t->attach(*cb,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   if(i->wert!=hauptfenster->NOPAGE) 
    {
      int min=hauptfenster->PAGE_INFO;
      int max=hauptfenster->PAGE_ZUFALL;
      int_SpinButton *spin=Gtk::manage(new int_SpinButton(i->wert, min, max));
      i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_globale_optionen::element_show_or_hide),spin,&(i->wert)));
      t->attach(*spin,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    }
   else if(i->bild)
    {
      Gtk::Image *_o=Gtk::manage(new Gtk::Image(i->bild));
      t->attach(*_o,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    }
   table->attach(*t,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   ++count;
  } 
 Gtk::HSeparator *hseparator = manage(new class Gtk::HSeparator());
 table->attach(*hseparator, 0, 1, count, count+1, Gtk::FILL, Gtk::AttachOptions(0), 0, 0);
 ++count;
 Gtk::Label *label = manage(new class Gtk::Label("Hausregeln"));
 table->attach(*label, 0, 1, count, count+1, Gtk::AttachOptions(0), Gtk::AttachOptions(0), 0, 0);
 ++count;
 std::list<Magus_Optionen::st_Haus> &L2=hauptfenster->getOptionen()->getHausregeln();
 for(std::list<Magus_Optionen::st_Haus>::iterator i=L2.begin();i!=L2.end();++i)
  {
   bool_CheckButton *cb = manage(new bool_CheckButton(i->active,i->text));
   i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_globale_optionen::element_activate_H),i->index));

   Gtk::Table *t=manage(new Gtk::Table(1,1,false));
   t->attach(*cb,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   if(i->bild)
     {
        Gtk::Image *_o=manage(new Gtk::Image(i->bild));
        t->attach(*_o,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     }
   table->attach(*t,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   ++count;
  } 
 add(*table);
 show_all();
}

void frame_globale_optionen::element_show_or_hide(gpointer gp,Gtk::Widget *widget,Model<int> *wert)
{
  if(*static_cast<bool*>(gp)) widget->show();
  else { 
      widget->hide();
      *wert=-1;
   }
}


void frame_globale_optionen::element_activate_C(gpointer gp,Magus_Optionen::OptionenCheckIndex index)
{
  hauptfenster->getOptionen()->OptionenCheck_setzen_from_menu(index);
  if(index==Magus_Optionen::Original)
   {
    if(hauptfenster->getOptionen()->OptionenCheck(index).active)
       hauptfenster->getOptionen()->setAllHausregeln(false);
   }
}

void frame_globale_optionen::element_activate_H(gpointer gp,Magus_Optionen::HausIndex index)
{
  hauptfenster->getOptionen()->Hausregeln_setzen_from_menu(index);
}
