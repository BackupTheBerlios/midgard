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

void frame_globale_optionen::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}

void frame_globale_optionen::set_values()
{
//  hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::Notebook_start).spin
//      ->set_value(hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::Notebook_start).wert);
}


void frame_globale_optionen::init()
{
#if 1
      static bool ini=false;
      if(ini) return;
      ini=true;
#endif
/*
 remove();
*/
 if(!hauptfenster) assert(!"");
 if(!(hauptfenster->getOptionen())) assert(!"");
 Gtk::Table *table=manage(new Gtk::Table(0,0,false));
 std::list<Midgard_Optionen::st_OptionenCheck> &L=hauptfenster->getOptionen()->getOptionenCheck();
 int count=0;
 for(std::list<Midgard_Optionen::st_OptionenCheck>::iterator i=L.begin();i!=L.end();++i)
  {
/*
   Gtk::CheckButton *cb=manage(new Gtk::CheckButton(i->text,0,0.5));
   cb->set_active(i->active);
   cb->toggled.connect(SigC::bind(SigC::slot(this,&frame_globale_optionen::element_activate_C),cb,i->index));
*/
   i->checkbutton = manage(new MVC_bool_Widget(i->active,i->text));
   i->active.changed.connect(SigC::bind(SigC::slot(this,&frame_globale_optionen::element_activate_C),i->index));
   Gtk::Table *t=manage(new Gtk::Table(0,0,false));
//   t->attach(*cb,0,1,0,1,GTK_FILL,0,0,0);
   t->attach(*i->checkbutton,0,1,0,1,GTK_FILL,0,0,0);
   if(i->wert!=-1) 
    {
cout << "A: "<<i->spin<<'\n';
      int min=hauptfenster->PAGE_INFO;
      int max=hauptfenster->PAGE_ZUFALL-1;
//      Gtk::Adjustment *spa = manage(new class Gtk::Adjustment(i->wert, min+1, max+1, 1, 10, 10)); 
cout << "B: "<<i->spin<<'\n';
//      i->spin= manage(new class Gtk::SpinButton(*spa, 1, 0));
        i->spin= manage(new MVC_int_Widget(i->wert, min, max));
cout << "C: "<<i->spin<<'\n';

//      i->spin->set_value(i->wert);
//      i->spin->changed.connect(SigC::bind(SigC::slot(static_cast<class frame_globale_optionen*>(this), &frame_globale_optionen::on_spinbutton_notebookpage_changed),i->index));
      t->attach(*i->spin,1,2,0,1,GTK_FILL,0,0,0);
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
 std::list<Midgard_Optionen::st_Haus> L2=hauptfenster->getOptionen()->getHausregeln();
 for(std::list<Midgard_Optionen::st_Haus>::const_iterator i=L2.begin();i!=L2.end();++i)
  {
   Gtk::CheckButton *cb=manage(new Gtk::CheckButton(i->text,0,0.5));
   
   if(hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::Original).active)
    {
      cb->set_sensitive(false);
      cb->set_active(i->active);
    }
   else
      cb->set_active(i->active);
   cb->toggled.connect(SigC::bind(SigC::slot(this,&frame_globale_optionen::element_activate_H),cb,i->index));
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
 
// if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::Notebook_start).active) // für 'hide'
// hauptfenster->getOptionen()->OptionenCheck_setzen_from_menu(Midgard_Optionen::Notebook_start,false);
}

void frame_globale_optionen::on_spinbutton_notebookpage_changed(Midgard_Optionen::OptionenCheckIndex index)
{
/*
  Midgard_Optionen::st_OptionenCheck S=hauptfenster->getOptionen()->OptionenCheck(index);
  if(!S.spin) {cerr << "Spinbutten nicht definiert\n"; return;}
  S.spin->update();
  int wert = S.spin->get_value_as_int();
  hauptfenster->getOptionen()->OptionenCheck(index,wert);
*/
}


void frame_globale_optionen::element_activate_C(gpointer gp,Midgard_Optionen::OptionenCheckIndex index)
{
  hauptfenster->getOptionen()->OptionenCheck_setzen_from_menu(index);
  if(index==Midgard_Optionen::Original)
   {
    hauptfenster->getOptionen()->setAllHausregeln(false);
    init();
   }
}

/*
void frame_globale_optionen::element_activate_C(Gtk::CheckButton *cb,Midgard_Optionen::OptionenCheckIndex index)
{
  hauptfenster->getOptionen()->OptionenCheck_setzen_from_menu(index,cb->get_active());
  if(index==Midgard_Optionen::Original)
   {
    hauptfenster->getOptionen()->setAllHausregeln(false);
    init();
   }
}
*/

void frame_globale_optionen::element_activate_H(Gtk::CheckButton *cb,Midgard_Optionen::HausIndex index)
{
  hauptfenster->getOptionen()->Hausregeln_setzen_from_menu(index,cb->get_active());
}
