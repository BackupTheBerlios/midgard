/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

// generated 2002/9/6 20:10:27 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// newer (non customized) versions of this file go to table_zufall.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_zufall.hh"
#include "midgard_CG.hh"
#include "Zufall.hh"
#include "KI.hh"
#include "Optionen.hh"
#include "Prototyp2.hh"
#include "Data_Prototyp.hh"
#include "Datenbank.hh"

void table_zufall::init(midgard_CG *h)
{
  hauptfenster=h;
  checkbutton_ange_fert->hide(); // nicht richtig implementiert
  fill_combos();
  fill_combo_steigern();
  fill_prototyp2_list();
  zeige_werte();
}

void table_zufall::fill_prototyp2_list()
{
  std::list<cH_Prototyp2> L=Datenbank.prototyp2;
  std::vector<cH_RowDataBase> datavec;
  for(std::list<cH_Prototyp2>::const_iterator i=L.begin();i!=L.end();++i)
   {
     for(std::vector<Prototyp2::st_protolisten>::const_iterator j=(*i)->LZauber().begin();j!=(*i)->LZauber().end();++j)
        datavec.push_back(new Data_Prototyp(*i,"Zauber",*j));
     for(std::vector<Prototyp2::st_protolisten>::const_iterator j=(*i)->LFertigkeiten().begin();j!=(*i)->LFertigkeiten().end();++j)
        datavec.push_back(new Data_Prototyp(*i,"Fertigkeiten",*j));
   }
  tree_prototyp->setDataVec(datavec);
}

void table_zufall::set_tree_prototyp_titels()
{
   std::vector<std::string> v;
   v.push_back("Prototyp");
   v.push_back("Art");
   v.push_back("Name");
   v.push_back("Faktor");
   tree_prototyp->setTitles(v);
}

void table_zufall::on_radiobutton_proto_spezialisieren_toggled()
{
 if(radiobutton_proto_spezialisieren->get_active())
  {
   frame_spezialist_typen->show();
   frame_verteilung_auf->hide();
/*
   frame_spezialist_typen->set_sensitive(true);
   frame_verteilung_auf->set_sensitive(false);
*/
  } 
}

void table_zufall::on_radiobutton_proto_verteilen_toggled()
{
 if(radiobutton_proto_verteilen->get_active())
  {
   frame_spezialist_typen->hide();
   frame_verteilung_auf->show();
//   frame_spezialist_typen->set_sensitive(false);
//   frame_verteilung_auf->set_sensitive(true);
  } 
}

void table_zufall::on_tree_prototyp_leaf_selected(cH_RowDataBase d)
{
}

