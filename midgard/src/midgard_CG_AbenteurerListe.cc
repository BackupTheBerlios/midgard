// $Id: midgard_CG_AbenteurerListe.cc,v 1.3 2002/05/28 08:59:26 thoma Exp $
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

void midgard_CG::fill_AbenteurerListe()
{
  set_AbenteurerListe_Title();
  std::vector<cH_RowDataBase> datavec;
  for(std::vector<Abenteurer>::const_iterator i=Char.getList().begin();i!=Char.getList().end();++i)
   {
     if(i->getCWerte().Name_Abenteurer()!="")
        datavec.push_back(new Data_AbenteurerListe(*i));
   }
  AbenteurerListe->setDataVec(datavec);
}

void midgard_CG::on_AbenteurerListe_leaf(cH_RowDataBase d)
{
  const Data_AbenteurerListe *dt=dynamic_cast<const Data_AbenteurerListe*>(&*d);
  Char.set_Abenteurer(dt->getAbenteurer());
  set_title(getWerte().Name_Abenteurer());
}

/*
void midgard_CG::insert_into_CharList(Abenteurer &A)
{
  bool push_back=true;
  for(std::vector<Abenteurer>::iterator i=CharList.begin();i!=CharList.end();++i)
   {
     if(i->getCWerte().Name_Abenteurer()==A.getCWerte().Name_Abenteurer() &&
        i->getCWerte().Version() == A.getCWerte().Version() )
       {
         *i=A;
         push_back=false;
       }
   }
  if(push_back) CharList.push_back(A);
}
*/

void midgard_CG::set_AbenteurerListe_Title()
{
 std::vector<std::string> vs;
 vs.push_back("Name");
 vs.push_back("Typ");
 vs.push_back("Bezeichnung");
 vs.push_back("Spezies");
 vs.push_back("Spieler");
 vs.push_back("Version");
 AbenteurerListe->setTitles(vs);
}
