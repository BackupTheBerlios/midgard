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

#include "class_SimpleTree_LernschemaZusatz.hh"
#include "midgard_CG.hh"

void midgard_CG::lernen_zusatz(enum_lernschema_zusatz was)
{
  std::vector<cH_RowDataBase> datavec;
  switch(was)
   {
     case LZHERKUNFT:
      {
       lernen_zusatz_titel(was);
       for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
         datavec.push_back(new Data_Herkunft(*i));
       Tree_Lernschema_Zusatz->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_herkunft_leaf_selected));
       break;
      }
   }
 Tree_Lernschema_Zusatz->setDataVec(datavec);
 frame_lernschema_zusatz->show();
}

void midgard_CG::lernen_zusatz_titel(enum_lernschema_zusatz was)
{
  std::vector<std::string> vs;
  switch(was)
   {
     case LZHERKUNFT:
      {
       frame_lernschema_zusatz->set_label("Herkunftsland wählen");
       vs.push_back("Land");
       vs.push_back("Koninent");
       vs.push_back("Sprache(n)");
      }
   }
 Tree_Lernschema_Zusatz->setTitles(vs);
}


void midgard_CG::on_herkunft_leaf_selected(cH_RowDataBase d)
{
  const Data_Herkunft *dt=dynamic_cast<const Data_Herkunft*>(&*d);
  if(wizard) 
   { wizard->next_step();
   }
  Werte.setHerkunft(dt->getLand());
  frame_lernschema_zusatz->hide();
  zeige_werte(Werte);  
  button_angeborene_fert->set_sensitive(true);
}

