// $Id: midgard_CG_AbenteurerListe.cc,v 1.10 2002/12/13 18:35:22 christof Exp $
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
#include "class_AbenteurerListe.hh"
#include <algorithm>

void midgard_CG::fill_AbenteurerListe()
{
  set_AbenteurerListe_Title();
  std::vector<cH_RowDataBase> datavec;
  for(std::list<VAbenteurer::st_abenteurer>::iterator i=Char.getList().begin();i!=Char.getList().end();++i)
   {
//     if(i->abenteurer.getWerte().Name_Abenteurer()!="")
        datavec.push_back(new Data_AbenteurerListe(i));
   }
  AbenteurerListe->setDataVec(datavec);
}

void midgard_CG::on_AbenteurerListe_leaf(cH_RowDataBase d)
{
  const Data_AbenteurerListe *dt=dynamic_cast<const Data_AbenteurerListe*>(&*d);
  if(togglebutton_delete_abenteurer_aus_liste->get_active())
   {
     std::list<VAbenteurer::st_abenteurer>::iterator A=dt->getAbenteurer();
     bool neuer_zeiger=false;
     if(Char.getAbenteurer()==A->abenteurer) neuer_zeiger=true;
     Char.getList().erase(A);
     if(neuer_zeiger) 
      { if(Char.empty()) Char.push_back(); 
        else Char.setAbenteurer(--(Char.getList().end()));
      }
     togglebutton_delete_abenteurer_aus_liste->set_active(false);
     load_for_mainpage(PAGE_NEWS);
   }
  else
   {
     Char.setAbenteurer(dt->getAbenteurer());
     set_title(getWerte().Name_Abenteurer());
     AbenteurerListe->get_selection()->unselect_all();
   }
}

void midgard_CG::on_togglebutton_delete_abenteurer_aus_liste_toggled()
{
  
}

void midgard_CG::set_AbenteurerListe_Title()
{
 std::vector<std::string> vs;
 vs.push_back("Name");
 vs.push_back("Gespeichert");
 vs.push_back("Typ");
 vs.push_back("Bezeichnung");
 vs.push_back("Spezies");
 vs.push_back("Spieler");
 vs.push_back("Version");
 AbenteurerListe->setTitles(vs);
}
