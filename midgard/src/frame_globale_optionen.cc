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
#include <gtk--/separator.h>
#include <MVC_int_Widget.hh>
#include <MVC_bool_Widget.hh>



void frame_globale_optionen::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}


void frame_globale_optionen::init()
{
#if 1
      static bool ini=false;
      if(ini) return;
      ini=true;
#endif
 if(!hauptfenster) assert(!"");
 if(!(hauptfenster->getOptionen())) assert(!"");
 Gtk::Table *table=manage(new Gtk::Table(0,0,false));
 std::list<Midgard_Optionen::st_OptionenCheck> &L=hauptfenster->getOptionen()->getOptionenCheck();
 int count=0;
 for(std::list<Midgard_Optionen::st_OptionenCheck>::iterator i=L.begin();i!=L.end();++i)
  {
   MVC_bool_Widget *cb = manage(new MVC_bool_Widget(i->active,i->text));
   i->active.changed.connect(SigC::bind(SigC::slot(this,&frame_globale_optionen::element_activate_C),i->index));
   Gtk::Table *t=manage(new Gtk::Table(0,0,false));
   t->attach(*cb,0,1,0,1,GTK_FILL,0,0,0);

   if(i->wert!=hauptfenster->NOPAGE) 
    {
      int min=hauptfenster->PAGE_INFO;
      int max=hauptfenster->PAGE_ZUFALL;
      MVC_int_Widget *spin=manage(new MVC_int_Widget(i->wert, min, max));
      i->active.changed.connect(SigC::bind(SigC::slot(this,&frame_globale_optionen::element_show_or_hide),spin,&(i->wert)));
      t->attach(*spin,1,2,0,1,GTK_FILL,0,0,0);
    }
   else if(i->bild)
    {
      Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
      t->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
    }
   table->attach(*t,0,1,count,count+1,GTK_FILL,0,0,0);
   ++count;
  } 
 Gtk::HSeparator *hseparator = manage(new class Gtk::HSeparator());
 table->attach(*hseparator, 0, 1, count, count+1, GTK_FILL, 0, 0, 0);
 ++count;
 Gtk::Label *label = manage(new class Gtk::Label("Hausregeln"));
 table->attach(*label, 0, 1, count, count+1, 0, 0, 0, 0);
 ++count;
 std::list<Midgard_Optionen::st_Haus> &L2=hauptfenster->getOptionen()->getHausregeln();
 for(std::list<Midgard_Optionen::st_Haus>::iterator i=L2.begin();i!=L2.end();++i)
  {
   MVC_bool_Widget *cb = manage(new MVC_bool_Widget(i->active,i->text));
   i->active.changed.connect(SigC::bind(SigC::slot(this,&frame_globale_optionen::element_activate_H),i->index));

   Gtk::Table *t=manage(new Gtk::Table(0,0,false));
   t->attach(*cb,0,1,0,1,GTK_FILL,0,0,0);
   if(i->bild)
     {
        Gtk::Pixmap *_o=manage(new Gtk::Pixmap(i->bild));
        t->attach(*_o,1,2,0,1,GTK_FILL,0,0,0);
     }
   table->attach(*t,0,1,count,count+1,GTK_FILL,0,0,0);
   ++count;
  } 
 add(*table);
 show_all();
 
// if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::Notebook_start).active) // f�r 'hide'
// hauptfenster->getOptionen()->OptionenCheck_setzen_from_menu(Midgard_Optionen::Notebook_start,false);
}

void frame_globale_optionen::element_show_or_hide(gpointer gp,Gtk::Widget *widget,MVC<int> *wert)
{
cout <<"Wert: "<< *wert<<'\n';
  if(*static_cast<bool*>(gp)) widget->show();
  else { 
      widget->hide();
      *wert=-1;
   }
cout <<"Wert: "<< *wert<<'\n';
}


void frame_globale_optionen::element_activate_C(gpointer gp,Midgard_Optionen::OptionenCheckIndex index)
{
  hauptfenster->getOptionen()->OptionenCheck_setzen_from_menu(index);
  if(index==Midgard_Optionen::Original)
   {
    if(hauptfenster->getOptionen()->OptionenCheck(index).active)
       hauptfenster->getOptionen()->setAllHausregeln(false);
    init();
   }
}

void frame_globale_optionen::element_activate_H(gpointer gp,Midgard_Optionen::HausIndex index)
{
  hauptfenster->getOptionen()->Hausregeln_setzen_from_menu(index);
}
