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
#include <Misc/itos.h>
#include "dtos1.h"

class Data_NewPreis : public RowDataBase
{
      cH_Preise ware;
      double kosten;
      std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> M;
  public:
     Data_NewPreis(const cH_Preise P) : ware(P),kosten(P->Kosten()) {}
     Data_NewPreis(const cH_Preise P,const std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> &m) 
         : ware(P),kosten(P->Kosten()),M(m) 
         {
           for(std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod>::const_iterator i=M.begin();i!=M.end();++i)
                kosten*=i->second.preis_faktor;
         }
      
     enum spalten {ART,ART2,NAME,V_STAND,V_MATERIAL,V_FARBE,GEWICHT,KOSTEN};
     
     virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const 
      {
        std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> M_=
            const_cast<std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod>&>(M);
        switch(spalten(seqnr)) {
           case ART: return cH_EntryValueIntString(ware->Art());
           case ART2: return cH_EntryValueIntString(ware->Art2());
           case NAME: return cH_EntryValueIntString(ware->Name());
           case GEWICHT: return cH_EntryValueIntString(ware->Gewicht());
           case V_STAND: return cH_EntryValueIntString(M_[table_ausruestung::Stand].spezifikation);
           case V_MATERIAL: return cH_EntryValueIntString(M_[table_ausruestung::Material].spezifikation);
           case V_FARBE: return cH_EntryValueIntString(M_[table_ausruestung::Farbe].spezifikation);
           case KOSTEN: return cH_EntryValueIntString(dtos(kosten)+" "+ware->Einheit());
         }
        return cH_EntryValueIntString();
      }
   cH_Preise Ware() const {return ware;}
   double Kosten() const {return kosten;}
   std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> 
         getMod() const {return M;}
//   std::string Spezifikation() const {return spezifikation;}
//   std::string Varaiante() const {return variante;}

};
class cH_Data_NewPreis : public Handle<const Data_NewPreis>
{
public:
 cH_Data_NewPreis(Data_NewPreis *r) : Handle<const Data_NewPreis>(r) {}
};


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
 preis_.push_back("Kostenfaktor");
 preise_tree_neu->setTitles(preis_);
} 



enum table_ausruestung::e_spalten &operator++(enum table_ausruestung::e_spalten &s)
{  return (enum table_ausruestung::e_spalten)(++(int&)s);
} 


void table_ausruestung::fill_new_preise()
{
  std::vector<cH_RowDataBase> datavec;
  std::map<e_spalten,std::string> SpaltenMap;
  for(std::list<cH_Preise>::const_iterator i=hauptfenster->getDatabase().preise.begin();i!=hauptfenster->getDatabase().preise.end();++i)
   {
     std::map<std::string,std::vector<PreiseNewMod::st_preismod> > VM=cH_PreiseNewMod((*i)->Art(),true)->VSpezifikation();
     if(VM.empty()) 
       { datavec.push_back(new Data_NewPreis(*i));
         continue;
       }
     std::map<e_spalten,vector<PreiseNewMod::st_preismod> > MS;
     for(std::map<std::string,std::vector<PreiseNewMod::st_preismod> >::const_iterator j=VM.begin();j!=VM.end();++j)     
      {
        pair<e_spalten,std::string> spalte=enum_from_string(j->first);
        SpaltenMap[spalte.first]=spalte.second;
        for(std::vector<PreiseNewMod::st_preismod>::const_iterator k=j->second.begin();k!=j->second.end();++k)
           MS[spalte.first].push_back(*k);
      }

    std::vector<std::map<e_spalten,PreiseNewMod::st_preismod> > X;

    // Iteratoren für die einzelnen Spalten
    typedef  pair<std::vector<PreiseNewMod::st_preismod>::iterator,
                  std::vector<PreiseNewMod::st_preismod>::iterator> 
                        beg_end_t;
    std::map<e_spalten,beg_end_t> VCI;
    for(std::map<e_spalten,std::vector<PreiseNewMod::st_preismod> >::iterator j=MS.begin();j!=MS.end();++j)
       VCI[j->first]=beg_end_t(j->second.begin(),j->second.end());
reloop:
    std::map<e_spalten,PreiseNewMod::st_preismod> Y;
    for(e_spalten e=Farbe;e<=Stand;++e)
       if(VCI[e].first!=VCI[e].second) Y[e] = *(VCI[e].first) ;
    X.push_back(Y); 

    for(std::map<e_spalten,beg_end_t>::iterator k=VCI.begin();k!=VCI.end();++k)
     {
      if(k->second.first!=k->second.second)
         ++(k->second.first);
      if(k->second.first!=k->second.second)
         goto reloop;
     }

    for(std::vector<std::map<e_spalten,PreiseNewMod::st_preismod> >::const_iterator j=X.begin();j!=X.end();++j)
        datavec.push_back(new Data_NewPreis(*i,*j));
   }
  fill_new_tree_titles(SpaltenMap);
  preise_tree_neu->setDataVec(datavec);
}

/*
std::map<e_spalten,int> VI;

PreiseNewMod::st_preismod next_element_for(const table_ausruestung::e_spalten &spalte,
      std::map<table_ausruestung::e_spalten,std::vector<PreiseNewMod::st_preismod> > M)
{
  return M[spalte][VI[spalte]];
}
*/

void table_ausruestung::on_preise_tree_neu_leaf_selected(cH_RowDataBase d)
{
  const Data_NewPreis *dt=dynamic_cast<const Data_NewPreis*>(&*d);

cout << dt->Ware()->Name()<<'\t'<<dt->Ware()->Kosten()<<'\t'<<dt->Kosten()<<'\n';  

}
