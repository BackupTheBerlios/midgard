
#include "config.h"
#include "frame_icons.hh"

#include "midgard_CG.hh"
#include <bool_CheckButton.hh>
#include <libmagus/Magus_Optionen.hh>

void frame_icons::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}

void frame_icons::init() 
{
 assert(hauptfenster);
 Gtk::Table *table=manage(new Gtk::Table(1,1,false));
 std::list<Magus_Optionen::st_Icon> &L=Programmoptionen->getIcon();
 int count=0;
 for(std::list<Magus_Optionen::st_Icon>::iterator i=L.begin();i!=L.end();++i)
  {
    bool_CheckButton *cb = Gtk::manage(new bool_CheckButton(i->active,i->text));
//    i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_icons::element_activate),i->index));
    table->attach(*cb,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    ++count;
  }
 table->show_all();
 add(*table);
}

#if 0
void frame_icons::element_activate(gpointer gp,Magus_Optionen::IconIndex index)
{
  Programmoptionen->Icon_setzen_from_menu(index);
}
#endif
