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
  optionmenu_art->get_menu()->deactivate.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::opt_art));
  fill_optionmenu_typ();
  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::opt_typ));
}



void window_Ausruestung::on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event)
{
}

void window_Ausruestung::fill_preisliste()
{
  cH_PreiseMod *art=static_cast<cH_PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  PreiseMod::st_vec *modi=static_cast<PreiseMod::st_vec*>(optionmenu_typ->get_menu()->get_active()->get_user_data());
  Gtk::OStream os(clist_preisliste);
  for(std::list<cH_Preise>::const_iterator i=Database.preise.begin();i!=Database.preise.end();++i)
   {
     if((*art)->Art()==(*i)->Art())
      os << (*i)->Name() 
         << (*i)->Kosten()
         << (*i)->Einheit()
         <<'\n';
   }  
}


void window_Ausruestung::opt_art()
{
  fill_optionmenu_typ();
  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::opt_typ));
}

void window_Ausruestung::fill_optionmenu_art()
{
  Gtk::OStream os(optionmenu_art);
  for(std::list<cH_PreiseMod>::iterator i=Database.preisemod.begin();i!=Database.preisemod.end();++i)
   {
     os << (*i)->Art();
     os.flush((gpointer)&*i);
   }  
}


void window_Ausruestung::opt_typ()
{
  fill_preisliste();
}

void window_Ausruestung::fill_optionmenu_typ()
{
  cH_PreiseMod *art=static_cast<cH_PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  Gtk::OStream os(optionmenu_typ);
  for(vector<PreiseMod::st_vec>::const_iterator i=(*art)->getVec().begin();i!=(*art)->getVec().end();++i)
   {
     os << i->typ;
     os.flush((gpointer)&*i);
   }  
}


void window_Ausruestung::on_button_druck_clicked()
{
}


void window_Ausruestung::on_button_close_clicked()
{   
  destroy();
}
