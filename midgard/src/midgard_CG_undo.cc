// $Id: midgard_CG_undo.cc,v 1.17 2003/04/29 07:33:56 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.  
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "midgard_CG.hh"
#include "Abenteurer.hh"
#include <sstream>

void midgard_CG::undosave(std::string s)
{
  Char.modified();
//  modify_bool=true;
  std::stringstream ss;
  Char->speicherstream(ss,getCDatabase(),getCOptionen());
  MidgardUndo.push_back(s,ss.str());
}

void midgard_CG::show_undo_tree()
{
  const std::vector<Midgard_Undo::st_undo> &V=MidgardUndo.get_V();
  std::vector<cH_RowDataBase> datavec;
  for(std::vector<Midgard_Undo::st_undo>::const_iterator i=V.begin();i!=V.end();++i)
     datavec.push_back(new Data_Undo(*i));
  undo_tree->setDataVec(datavec);
}

void midgard_CG::on_undo_leaf_selected(cH_RowDataBase d)
{
  const Data_Undo *dt=dynamic_cast<const Data_Undo*>(&*d);
  std::stringstream s;
  s<<MidgardUndo.get(dt->getIndex());
  Char->xml_import_stream(s,getDatabase(),getOptionen(),this);
  set_status("Alten Zustand wieder hergestellt");
  undo_tree->get_selection()->unselect_all();
}

void midgard_CG::on_button_redo_clicked()
{
  std::stringstream s;
  s<<MidgardUndo.get_next();
  Char->xml_import_stream(s,getDatabase(),getOptionen(),this);
  load_for_mainpage(notebook_main->get_current_page());
}


void midgard_CG::on_button_undo_clicked()
{
  std::stringstream s;
  s<<MidgardUndo.get_last();
  Char->xml_import_stream(s,getDatabase(),getOptionen(),this);
  load_for_mainpage(notebook_main->get_current_page());
}

static void PosCalc(GtkMenu *menu,gint *x,gint *y,gboolean *push_in,gpointer user_data)
{  (*y)+=4;
   (*push_in)=true;
}

void midgard_CG::on_undo_secondpressed(int mbutton)
{  if (MidgardUndo.get_V().size()!=undo_tree->getModel().getDataVec().size()) 
      show_undo_tree();
   if (undo_menu) delete undo_menu;
   undo_menu=new Gtk::Menu();
   const SimpleTreeModel::datavec_t &vec=undo_tree->getModel().getDataVec();
   Midgard_Undo::const_iterator i=MidgardUndo.current_iter();
   if (i==MidgardUndo.end()) return;
   for (unsigned count=0; count<10; --i,++count)
   {  assert(i->count<vec.size());
      Gtk::MenuItem *mi=manage(new Gtk::MenuItem(i->text));
      undo_menu->add(*mi);
      mi->show();
      mi->signal_activate().connect(SigC::bind(SigC::slot(*this,
      		&midgard_CG::on_undo_leaf_selected),vec[i->count]));
      if (i==MidgardUndo.begin()) break;
   }
   gtk_menu_popup(undo_menu->gobj(),0,0,&PosCalc,0,0,0);
}

void midgard_CG::on_redo_secondpressed(int mbutton)
{  if (MidgardUndo.get_V().size()!=undo_tree->getModel().getDataVec().size()) 
      show_undo_tree();
   if (undo_menu) delete undo_menu;
   undo_menu=new Gtk::Menu();
   const SimpleTreeModel::datavec_t &vec=undo_tree->getModel().getDataVec();
   Midgard_Undo::const_iterator i=MidgardUndo.current_iter();
   if (i==MidgardUndo.end()) return;
   if (++i==MidgardUndo.end()) return;
   for (unsigned count=0; count<10; ++i,++count)
   {  if (i==MidgardUndo.end()) break;
      assert(i->count<vec.size());
      Gtk::MenuItem *mi=manage(new Gtk::MenuItem(i->text));
      undo_menu->add(*mi);
      mi->show();
      mi->signal_activate().connect(SigC::bind(SigC::slot(*this,
      		&midgard_CG::on_undo_leaf_selected),vec[i->count]));
   }
   gtk_menu_popup(undo_menu->gobj(),0,0,&PosCalc,0,0,0);
}

