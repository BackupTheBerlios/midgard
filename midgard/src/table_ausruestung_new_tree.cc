/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2005 Christof Petig
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
#include <Misc/mystring.h>
#include <libmagus/Datenbank.hh>
#include <libmagus/Ausgabe.hh>
#include <libmagus/LernListen.hh>

double Data_NewPreis::CalKosten() const
{      
  double k=kosten;
  for(std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod>::const_iterator i=M.begin();i!=M.end();++i)
    k*=i->second.preis_faktor;
  return k;
}


std::pair<table_ausruestung::e_spalten,std::string> table_ausruestung::enum_from_string(const std::string &s)
{
  
  if(s=="Farbe") return std::pair<table_ausruestung::e_spalten,std::string>(Farbe,"Farbe");
  else if(s=="Material_K") return std::pair<table_ausruestung::e_spalten,std::string>(Material,"Material");
  else if(s=="Material_W") return std::pair<table_ausruestung::e_spalten,std::string>(Material,"Material");
  else if(s=="Stand") return std::pair<table_ausruestung::e_spalten,std::string>(Stand,"Stand");
  else return std::pair<table_ausruestung::e_spalten,std::string>(None,"???");
}

void table_ausruestung::fill_new_tree_titles(const std::map<e_spalten,std::string> &V)
{
 std::vector<std::string> preis_;
 preis_.push_back("Art");
 preis_.push_back("");
 preis_.push_back("Gegenstand");
 for(std::map<e_spalten,std::string>::const_iterator i=V.begin();i!=V.end();++i)
    preis_.push_back(i->second);
 preis_.push_back("Gewicht");
 preis_.push_back("Kosten");
 preis_.push_back("Beschreibung");
 preis_.push_back("Region");
 preise_tree_neu->setTitles(preis_);
} 

std::string table_ausruestung::spaltentitel(e_spalten e)
{
  if(e==Farbe) return  "Farbe";
  else if(e==Material)return  "Material";
  else if(e==Stand) return "Stand";
  return "???";
}


enum table_ausruestung::e_spalten operator++(enum table_ausruestung::e_spalten &s)
{  return (enum table_ausruestung::e_spalten)(++(int&)s);
} 


void table_ausruestung::fill_new_preise()
{
  std::map<e_spalten,std::string> SpaltenMap;
  std::list<cH_Data_NewPreis> LNP;
  std::list<cH_Preise>::const_iterator e=Datenbank.preise.end();
//cout << "F I L L \n";
  for(std::list<cH_Preise>::const_iterator i=Datenbank.preise.begin();i!=e;++i)
   {
     if((*i)->Unverkauflich() && !togglebutton_unverkauflich->get_active()) continue;
     if(LernListen::region_check(hauptfenster->getAben(),(*i)->Region()))
         LNP.push_back(new Data_NewPreis(*i));
   }
//cout << "F I L L 2\t"<<LNP.size()<<'\n';
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
           std::pair<e_spalten,std::string> spalte=enum_from_string(k->first);
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
  datavec.reserve(2000);
  for(std::list<cH_Data_NewPreis>::iterator j=LNP.begin();j!=LNP.end();++j)
     datavec.push_back(&**j);
//cout <<SpaltenMap.size()<<'\t'<< LNP.size()<<'\t'<<datavec.size()<<'\n';
  fill_new_tree_titles(SpaltenMap);
  preise_tree_neu->setDataVec(datavec);
}


bool table_ausruestung::genug_geld(const std::string &_E_,const int kosten) const
{
  enum eeinheit{GS,SS,KS};
  eeinheit einheit;
  if     (_E_=="GS") einheit=GS;
  else if(_E_=="SS") einheit=SS;
  else if(_E_=="KS") einheit=KS;
     
  Grundwerte &W=hauptfenster->getAben();
  int vermoegen=W.Kupfer()+10*W.Silber()+100*W.Gold();

  {int k=kosten;
   if(einheit==GS)      k *= 100;
   else if(einheit==SS) k *= 10;
   if(k>vermoegen) { Ausgabe(Ausgabe::Error,"Nicht genug Gold"); 
                         return false; }
  }
gewechselt:
  switch (einheit) {
     case GS: {
        if(W.Gold() >= kosten) {W.addGold(-kosten); return true;}

        int sk=kosten-W.Gold();
        if(W.Silber() >= 10*sk) {W.setGold(0); W.addSilber(-10*sk); 
                                  return true;}
         
        int kk=kosten-W.Gold()-10*W.Silber();
        if(W.Kupfer()>=100*kk) {W.setGold(0); W.setSilber(0);
                                 W.addKupfer(-100*kk);return true;}
      }
     case SS: {
        if(W.Silber() >= kosten) {W.addSilber(-kosten); return true;}
        
        int kk=kosten-W.Silber();
        if(W.Kupfer() >= 10*kk) {W.setSilber(0);W.addKupfer(-10*kk);
                                 return true;}

        W.addSilber(10);
        W.addGold(-1);
        goto gewechselt;                
      }
     case KS: {
        if(W.Kupfer() >= kosten) {W.addKupfer(-kosten); return true;}
        if(W.Silber()) {W.addKupfer(10); W.addSilber(-1);}
        W.addKupfer(100);
        W.addGold(-1);
        goto gewechselt;                
      }
   }
  Ausgabe(Ausgabe::Error,"Nicht genug Geld");
  return false;
}

#warning Preis abziehen, wenn Anzahl verändert wird

void table_ausruestung::on_preise_tree_neu_leaf_selected(cH_RowDataBase d)
{ const Data_NewPreis *dt=dynamic_cast<const Data_NewPreis*>(&*d);
  preise_tree_neu->get_selection()->unselect_all();
  if(checkbutton_ausruestung_geld->get_active())
   { if(!genug_geld(dt->Ware()->Einheit(),dt->Kosten())) 
     { // Nachricht?
       return;
     }
   }
  
  if(!besitz && dt->Ware()->Art()!="Neu")
   { // einfach _oben_ auswählen
     Gtk::TreeViewColumn *col=0;
     Gtk::TreePath parent;
     int cellx,celly;
     if (Ausruestung_tree->get_path_at_pos(0,0,parent,col,cellx,celly))
     { Ausruestung_tree->get_selection()->select(parent);
     }
   }
  hauptfenster->getChar()->begin_undo();
  std::string material;
  std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> M=dt->getMod();
  for(std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod>::const_iterator i=M.begin();i!=M.end();++i)
     material += i->second.spezifikation + ", ";
  ManuProC::remove_last_from(material,", ");
  bool sichtbar=true;
  if (besitz) sichtbar=besitz->getAusruestung().Sichtbar();
  Ausruestung A(1,dt->Ware()->Name(),dt->Ware()->Gewicht(),material,dt->Ware()->Region(),
      sichtbar,dt->Ware()->Ruestung(),dt->Ware()->Beschreibung());
  
  if(besitz)
   { bool isend;
     assert(Ausruestung_tree->get_selection()->count_selected_rows());
     Gtk::TreePath parent=*Ausruestung_tree->get_selection()->get_selected_rows().begin();
     Gtk::TreeModel::iterator piter=Ausruestung_tree->get_model()->get_iter(parent);
     AusruestungBaum &neues=get_Iter(parent,isend)->push_back(A);
     assert(!isend);
//     besitz->push_back(A);
     Gtk::TreeModel::iterator iter = m_refStore->append(piter->children());
     redisplay(*iter,neues);
     Ausruestung_tree->expand_to_path(Ausruestung_tree->get_model()->get_path(*iter));
     Ausruestung_tree->scroll_to_row(Ausruestung_tree->get_model()->get_path(*iter));
   }
  else 
   { AusruestungBaum &neues=hauptfenster->getAben().getBesitz().push_back(A);
     Gtk::TreeModel::iterator iter = m_refStore->append();
     redisplay(*iter,neues);
     Ausruestung_tree->scroll_to_row(Ausruestung_tree->get_model()->get_path(*iter));
   }
  hauptfenster->getChar()->name_undo("Ausrüstung "+dt->Ware()->Name()+" hinzugefügt");
//  showAusruestung();
}


void table_ausruestung::on_togglebutton_unverkauflich_toggled()
{
  fill_new_preise();
}
