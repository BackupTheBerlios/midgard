// generated 2001/11/25 15:17:30 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// newer (non customized) versions of this file go to midgard_CG.cc_new

// This file is for your program, I won't touch it again!

#include "midgard_CG.hh"
#include <Gtk_OStream.h>


void midgard_CG::ausruestung_laden()
{
  fill_optionmenu_art();
  optionmenu_art->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_art));
//  fill_optionmenu_typ();
//  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_typ));
//  fill_optionmenu_eigenschaft();
//  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_eigenschaft));
  optionmenu_art->show();
//  optionmenu_typ->show();
}



void midgard_CG::on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event)
{
}

void midgard_CG::fill_preisliste()
{
  clist_preisliste->clear();
  cH_PreiseMod *art=static_cast<cH_PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
//  PreiseMod::st_vec *modi=static_cast<PreiseMod::st_vec*>(optionmenu_typ->get_menu()->get_active()->get_user_data());
  Gtk::OStream os(clist_preisliste);
  for(std::list<cH_Preise>::const_iterator i=Database.preise.begin();i!=Database.preise.end();++i)
   {
     if((*art)->Art()==(*i)->Art())
      os << (*i)->Name() <<'\t'
         << (*i)->Kosten()<<'\t'
         << (*i)->Einheit()
         <<'\n';
   }  
  for (unsigned int i=0;i<clist_preisliste->columns().size();++i)
       clist_preisliste->set_column_auto_resize(i,true);
           
}

void midgard_CG::opt_art()
{
  fill_optionmenu_typ();
  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_typ));
  optionmenu_typ->show();
}

void midgard_CG::fill_optionmenu_art()
{
  Gtk::OStream os(optionmenu_art);
  for(std::list<cH_PreiseMod>::iterator i=Database.preisemod.begin();i!=Database.preisemod.end();++i)
   {
     os << (*i)->Art();
     os.flush((gpointer)&*i);
   }  
}


void midgard_CG::opt_typ()
{
  fill_optionmenu_eigenschaft();
  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_eigenschaft));
  optionmenu_eigenschaft->show();
//  fill_preisliste();
}

void midgard_CG::fill_optionmenu_typ()
{
  cH_PreiseMod *art=static_cast<cH_PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  Gtk::OStream os(optionmenu_typ);
  std::list<std::string> L;
  if((*art)->getVec().size()>1)
  for(vector<PreiseMod::st_vec>::const_iterator i=(*art)->getVec().begin();i!=(*art)->getVec().end();++i)
   {
     L.push_back(i->typ);
   }  
  L.sort();
  L.unique();
  for(std::list<std::string>::const_iterator i=L.begin();i!=L.end();++i)
   {
     os << (*i)<<'\n';
     os.flush((gpointer)&*i);
   }  
}


void midgard_CG::opt_eigenschaft()
{
  fill_preisliste();
}

void midgard_CG::fill_optionmenu_eigenschaft()
{
  Gtk::OStream os(optionmenu_eigenschaft);
  cH_PreiseMod *art=static_cast<cH_PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  std::string *typ=static_cast<std::string*>(optionmenu_typ->get_menu()->get_active()->get_user_data());
  for(vector<PreiseMod::st_vec>::const_iterator i=(*art)->getVec().begin();i!=(*art)->getVec().end();++i)
   {
     if(i->typ==*typ)
cout <<"->"<< i->name<<"<-\n";
//     os << i->name<<'\n';
//     os.flush((gpointer)&*i);
   }  
}


void midgard_CG::on_button_ausruestung_druck_clicked()
{
}


