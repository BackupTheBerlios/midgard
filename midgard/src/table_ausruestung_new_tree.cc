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

#include "table_ausruestung.hh"
#include "midgard_CG.hh"
#include "Data_NewPreis.hh"
//#include <Misc/itos.h>
//#include "dtos1.h"

pair<table_ausruestung::e_spalten,std::string> table_ausruestung::enum_from_string(const std::string &s)
{
  
  if(s=="Farbe") return pair<table_ausruestung::e_spalten,std::string>(Farbe,"Farbe");
  else if(s=="Material_K") return pair<table_ausruestung::e_spalten,std::string>(Material,"Material");
  else if(s=="Material_W") return pair<table_ausruestung::e_spalten,std::string>(Material,"Material");
  else if(s=="Stand") return pair<table_ausruestung::e_spalten,std::string>(Stand,"Stand");
  else return pair<table_ausruestung::e_spalten,std::string>(None,"???");
}

void table_ausruestung::fill_new_tree_titles(const std::map<e_spalten,std::string> &V)
{
 std::vector<string> preis_;
 preis_.push_back("Art");
 preis_.push_back("");
 preis_.push_back("Gegenstand");
 for(std::map<e_spalten,std::string>::const_iterator i=V.begin();i!=V.end();++i)
    preis_.push_back(i->second);
 preis_.push_back("Gewicht");
 preis_.push_back("Kosten");
 preise_tree_neu->setTitles(preis_);
} 

std::string table_ausruestung::spaltentitel(e_spalten e)
{
  if(e==Farbe) return  "Farbe";
  else if(e==Material)return  "Material";
  else if(e==Stand) return "Stand";
  return "???";
}


enum table_ausruestung::e_spalten &operator++(enum table_ausruestung::e_spalten &s)
{  return (enum table_ausruestung::e_spalten)(++(int&)s);
} 


void table_ausruestung::fill_new_preise()
{
  std::map<e_spalten,std::string> SpaltenMap;
  std::list<cH_Data_NewPreis> LNP;
  for(std::list<cH_Preise>::const_iterator i=hauptfenster->getDatabase().preise.begin();i!=hauptfenster->getDatabase().preise.end();++i)
   {
     LNP.push_back(new Data_NewPreis(*i));
   }
  for(e_spalten e=e_spalten(int(None)+1);e<Max;++e)
   {
     SpaltenMap[e]=spaltentitel(e);
     std::list<cH_Data_NewPreis> LNP2;
     for(std::list<cH_Data_NewPreis>::iterator j=LNP.begin();j!=LNP.end();++j)
      {
        std::map<std::string,std::vector<PreiseNewMod::st_preismod> > VM=cH_PreiseNewMod((*j)->Ware()->Art(),true)->VSpezifikation();
        if(VM.empty()) continue;
        std::map<e_spalten,std::vector<PreiseNewMod::st_preismod> > MS;
        for(std::map<std::string,std::vector<PreiseNewMod::st_preismod> >::const_iterator k=VM.begin();k!=VM.end();++k)
         {
           pair<e_spalten,std::string> spalte=enum_from_string(k->first);
           for(std::vector<PreiseNewMod::st_preismod>::const_iterator l=k->second.begin();l!=k->second.end();++l)
              MS[spalte.first].push_back(*l);
         }
        if(MS[e].empty()) continue;
        (*j)->getMod()[e]=*(MS[e].begin());

         std::vector<PreiseNewMod::st_preismod>::const_iterator b=MS[e].begin();
         for(std::vector<PreiseNewMod::st_preismod>::const_iterator k=++b;k!=MS[e].end();++k)
          {
           std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> M=(*j)->getMod();
           M[e]=*k;                       
           LNP2.push_back(new Data_NewPreis((*j)->Ware(),M));
          }
      }
     LNP.splice(LNP.end(),LNP2);
   }
  std::vector<cH_RowDataBase> datavec;
  for(std::list<cH_Data_NewPreis>::iterator j=LNP.begin();j!=LNP.end();++j)
   {
     datavec.push_back(&**j);
   }

  fill_new_tree_titles(SpaltenMap);
  preise_tree_neu->setDataVec(datavec);
}


void table_ausruestung::on_preise_tree_neu_leaf_selected(cH_RowDataBase d)
{
  const Data_NewPreis *dt=dynamic_cast<const Data_NewPreis*>(&*d);

cout << dt->Ware()->Name()<<'\t'<<dt->Ware()->Kosten()<<'\t'<<dt->Kosten()<<'\n';  

}
