
#include "config.h"
#include "frame_ansicht.hh"

#include<list>
#include "Optionen.hh"
#include "midgard_CG.hh"
#include <bool_CheckButton.hh>


void frame_ansicht::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}

/*
static void wert_changed(gpointer gp)
{ 
  std::cout << "OPTIONEN: WC: "<<  *(bool*)(gp)<<'\n';
} 
*/

void frame_ansicht::init()
{
 if(!hauptfenster) assert(!"");
 if(!(hauptfenster->getOptionen())) assert(!"");
 Gtk::Table *table=manage(new Gtk::Table(1,1,false));  
 std::list<Magus_Optionen::st_Ober> &L=hauptfenster->getOptionen()->getOber();
 int count=0;
 for(std::list<Magus_Optionen::st_Ober>::iterator i=L.begin();i!=L.end();++i)
  {
   if(!i->show) continue;
   bool_CheckButton *cb = manage(new bool_CheckButton(i->active,i->text));
   i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_ansicht::element_activate),i->index));
//i->active.signal_changed().connect(SigC::slot(&wert_changed));
   table->attach(*cb,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   ++count;
  }
 add(*table);
 show_all(); 
}

void frame_ansicht::element_activate(gpointer gp,Magus_Optionen::OberIndex index)
{
  hauptfenster->getOptionen()->Ober_setzen_from_menu(index);
}   
