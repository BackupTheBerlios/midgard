// generated 2001/11/25 15:17:30 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// newer (non customized) versions of this file go to window_Ausruestung.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "window_Ausruestung.hh"
#include <Gtk_OStream.h>


window_Ausruestung::window_Ausruestung(const midgard_CG::st_Database& dat)
: Database(dat)
{
  fill_optionmenu_art();
}

void window_Ausruestung::fill_optionmenu_art()
{
  Gtk::OStream os_art(optionmenu_art);
//  Gtk::OStream os_art(optionmenu_typ);
/*
  for(std::list<cH_PreiseMod>::iterator i=Database.PreiseMod.begin();i!=Database.PreiseMod.end();++i)
   {
     os << (*i)->Art()
   }  
*/
}


void window_Ausruestung::on_button_druck_clicked()
{
}


void window_Ausruestung::on_button_close_clicked()
{   
  destroy();
}
