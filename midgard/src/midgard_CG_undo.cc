// $Id: midgard_CG_undo.cc,v 1.6 2002/04/23 20:18:10 thoma Exp $
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

void midgard_CG::undosave(std::string s)
{
  modify_bool=true;
  strstream ss;
  speicherstream(ss);
  ss<<char(0);
  MidgardUndo.push_back(s,ss.str());
  ss.freeze();
}

void midgard_CG::show_undo_tree()
{
  std::vector<Midgard_Undo::st_undo> V=MidgardUndo.get_V();
  std::vector<cH_RowDataBase> datavec;
  for(std::vector<Midgard_Undo::st_undo>::const_iterator i=V.begin();i!=V.end();++i)
     datavec.push_back(new Data_Undo(*i));
  undo_tree->setDataVec(datavec);
}

void midgard_CG::on_undo_leaf_selected(cH_RowDataBase d)
{
  const Data_Undo *dt=dynamic_cast<const Data_Undo*>(&*d);
  strstream s;
  s<<MidgardUndo.get(dt->getIndex())<<char(0);
//  xml_import(MidgardUndo.get(dt->getIndex()));
  xml_import_stream(s);
  s.freeze();
}

void midgard_CG::on_button_redo_clicked()
{
  strstream s;
  s<<MidgardUndo.get_next()<<char(0);
  xml_import_stream(s);
  s.freeze();
//  xml_import(MidgardUndo.get_next());
}


void midgard_CG::on_button_undo_clicked()
{
  strstream s;
  s<<MidgardUndo.get_last()<<char(0);
  xml_import_stream(s);
  s.freeze();
//  xml_import(MidgardUndo.get_last());
}

