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
#include "WindowInfo.hh"
#include "class_Ausnahmen.hh"
#include "class_zauber.hh"
#include "zufall.h"

void midgard_CG::on_zauber_laden_clicked()
{   
  list_Zauber_neu.clear();
  Zauber_All ZA;
  std::list<cH_Zauber> list_tmp=ZA.get_All();
  for (std::list<cH_Zauber>::const_iterator i=list_tmp.begin();i!=list_tmp.end();++i)
    {
      if ((*i)->ist_gelernt(list_Zauber)) continue ;
      if ((*i)->Zauberart()=="Zaubersalz" && !checkbutton_zaubersalze->get_active())
         continue;
      if ((*i)->Zauberart()=="Beschwörung" && !checkbutton_beschwoerungen->get_active())
         continue;
      if ((*i)->ist_lernbar(Typ) || checkbutton_alle_zauber->get_active() )
       if (region_check((*i)->Region()) )
         list_Zauber_neu.push_back(*i);            
    }
  zauber_zeigen();
}

void midgard_CG::zauber_zeigen()
{
 if (Typ[0]->Zaubern()=="n" && Typ[1]->Zaubern()=="n") return;
 zeige_werte(Werte);
 on_speichern_clicked();
 show_alte_zauber();
 show_neue_zauber();
 show_altes_zauberwerk();
 show_neues_zauberwerk();
}



void midgard_CG::show_alte_zauber()
{
   std::vector<cH_RowDataBase> datavec;
   for (std::list<cH_Zauber>::const_iterator i=list_Zauber.begin(); i!=list_Zauber.end();++i)
    {
      int kosten = (*i)->Kosten(Typ,Ausnahmen(Werte,Typ,vec_Beruf));
      if (spruchrolle->get_active()) kosten /= 10;
      if ( !spruchrolle->get_active()  || 
           (spruchrolle->get_active()  && (*i)->Spruchrolle()) )      
        datavec.push_back(new Data_zauber((*i)->Name(),(*i)->Stufe(),(*i)->Ursprung(),kosten,(*i)->Standard__(Typ,Ausnahmen(Werte,Typ,vec_Beruf))));
    }
   alte_zauber_tree->setDataVec(datavec);
}

void midgard_CG::show_neue_zauber()
{
   std::vector<cH_RowDataBase> datavec;
   for (std::list<cH_Zauber>::const_iterator i=list_Zauber_neu.begin(); i!=list_Zauber_neu.end();++i)
    {
      int kosten = (*i)->Kosten(Typ,Ausnahmen(Werte,Typ,vec_Beruf));
      if (spruchrolle->get_active()) kosten /= 10;
      if ( !spruchrolle->get_active()  || 
           (spruchrolle->get_active()  && (*i)->Spruchrolle()) )      
        datavec.push_back(new Data_zauber((*i)->Name(),(*i)->Stufe(),(*i)->Ursprung(),kosten,(*i)->Standard__(Typ,Ausnahmen(Werte,Typ,vec_Beruf))));
    }
   neue_zauber_tree->setDataVec(datavec);
}



void midgard_CG::on_leaf_selected_alte_zauber(cH_RowDataBase d)
{  
   const Data_zauber *dt=dynamic_cast<const Data_zauber*>(&*d);
   if (steigern_bool) desteigern(dt->Kosten());
   Werte.add_GFP(-dt->Kosten());
   move_zauber(list_Zauber,list_Zauber_neu,dt->Name());
}


void midgard_CG::on_leaf_selected_neue_zauber(cH_RowDataBase d)
{  
  const Data_zauber *dt=dynamic_cast<const Data_zauber*>(&*d);
  if (!steigern(dt->Kosten(),"Zauber")) return;
  if (radio_spruchrolle_auto->get_active() && spruchrolle->get_active())
   {
     Werte.add_GFP(2*dt->Kosten());
     move_zauber(list_Zauber_neu,list_Zauber,dt->Name());
   }
  else if (radio_spruchrolle_wuerfeln->get_active() && spruchrolle->get_active())
   {
      int gelungen = spruchrolle_wuerfeln(dt->Name());
      if (gelungen != 0)
        {
         move_zauber(list_Zauber_neu,list_Zauber,dt->Name());
         Werte.add_GFP(dt->Kosten());
        }
      Werte.add_GFP(dt->Kosten());
   }
  else // normales lernen ohne Spruchrolle
   {
     Werte.add_GFP(dt->Kosten());
     move_zauber(list_Zauber_neu,list_Zauber,dt->Name());
   }
}

void midgard_CG::move_zauber(std::list<cH_Zauber>& von,std::list<cH_Zauber>& nach,const std::string& name)
{
 for (std::list<cH_Zauber>::iterator i=von.begin();i!= von.end();++i) 
     if ((*i)->Name()==name) 
       {nach.splice(nach.begin(),von,i);break;}
   zauber_zeigen();
   zauberwerk_laden();
   zauberwerk_zeigen();
}

void midgard_CG::on_checkbutton_zaubersalze_toggled()
{
 on_zauber_laden_clicked();
}
void midgard_CG::on_checkbutton_beschwoerungen_toggled()
{
 on_zauber_laden_clicked();
}
void midgard_CG::on_checkbutton_alle_zauber_toggled()
{
 on_zauber_laden_clicked();
 show_neues_zauberwerk();
}
void midgard_CG::on_checkbutton_zaubermittel_toggled()
{
 zauberwerk_laden();
 zeige_werte(Werte);
 on_speichern_clicked();
 show_neues_zauberwerk();
 show_altes_zauberwerk();
}

void midgard_CG::on_spruchrolle_toggled()
{
 midgard_CG::show_alte_zauber();
 midgard_CG::show_neue_zauber();
}

int midgard_CG::spruchrolle_wuerfeln(std::string name)
{
 cH_Zauber zauber(name);

 Random random;
 int erf_z = Werte.Zaubern_wert() + Werte.bo_Za() ;
 int xr=random.integer(1,20);
 int iaus=0;
 
 if (Typ[0]->Short() != "Ma" && Typ[1]->Short() != "Ma") if (zauber->Art()=="A")  iaus=-2;
 else if (Typ[0]->Short() == "Ma" || Typ[1]->Short() == "Ma" ) 
   {
    iaus = zauber->get_spezial_zauber_for_magier(Werte); //iaus = 2 ?
    if (!iaus)
     {
       if (zauber->Art()=="S")  iaus=+1;
       if (zauber->Art()=="A")  iaus=-1;
     }
   }
 else abort();

 
 int x = xr-zauber->iStufe();
 x += iaus;
 x += erf_z;
 std::string strinfo = "Lernversuch von Spruchrolle:
 gewürfelt  Spruchstufe  Ausnahme/Spezial Erfolgswert  Gesamtergebnis\n     "
      +itos(xr)+"            -"+itos(zauber->iStufe())+"               "
      +itos(iaus)+"             "+itos(erf_z)+"       =       "+ itos(x)+"\n";
 manage (new WindowInfo(strinfo.c_str(),true));
 if (x>=20) return(1);
 else return(0);
}



void midgard_CG::on_button_zauber_sort_clicked()
{
  std::deque<guint> seq = alte_zauber_tree->get_seq();
  switch((Data_zauber::Spalten_A)seq[0]) {
      case Data_zauber::NAMEa  : list_Zauber.sort(Zauber_sort_name()); ;break;
      case Data_zauber::STUFEa : list_Zauber.sort(Zauber_sort_stufe()); ;break;
      case Data_zauber::URSPRUNGa : list_Zauber.sort(Zauber_sort_ursprung()); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}

///////////////////////////////////////////////////////////////////////////////
//Zauberwerk
///////////////////////////////////////////////////////////////////////////////

void midgard_CG::on_button_zaubermittel_sort_clicked()
{
  std::deque<guint> seq = alte_zaubermittel_tree->get_seq();
  switch((Data_zaubermittel::Spalten_A)seq[0]) {
      case Data_zaubermittel::NAMEa  : list_Zauberwerk.sort(Zauberwerk_sort_name()) ;break;
      case Data_zaubermittel::STUFEa : list_Zauberwerk.sort(Zauberwerk_sort_stufe()) ;break;
      case Data_zaubermittel::ARTa :   list_Zauberwerk.sort(Zauberwerk_sort_art());break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}



void midgard_CG::move_zauberwerk(std::list<cH_Zauberwerk>& von,std::list<cH_Zauberwerk>& nach,const std::string& name)
{
 for (std::list<cH_Zauberwerk>::iterator i=von.begin();i!= von.end();++i) 
     if ((*i)->Name()==name) 
       {nach.splice(nach.begin(),von,i);break;}
 zauberwerk_laden();
 zauberwerk_zeigen();
}

void midgard_CG::on_leaf_selected_alte_zauberwerk(cH_RowDataBase d)
{  
  const Data_zaubermittel *dt=dynamic_cast<const Data_zaubermittel*>(&*d);
  if (steigern_bool) desteigern(dt->Kosten());
  Werte.add_GFP(-dt->Kosten());
  move_zauberwerk(list_Zauberwerk,list_Zauberwerk_neu,dt->Name());
}

void midgard_CG::zauberwerk_zeigen()
{
 zeige_werte(Werte);
 on_speichern_clicked();
 zauberwerk_laden();
 show_altes_zauberwerk();
 show_neues_zauberwerk();
}

void midgard_CG::on_leaf_selected_neue_zauberwerk(cH_RowDataBase d)
{  
  const Data_zaubermittel *dt=dynamic_cast<const Data_zaubermittel*>(&*d);
  if (!steigern(dt->Kosten(),"Zauber")) return;
  Werte.add_GFP(dt->Kosten());  
  move_zauberwerk(list_Zauberwerk_neu,list_Zauberwerk,dt->Name());
}

void midgard_CG::show_altes_zauberwerk()
{
   std::vector<cH_RowDataBase> datavec;
   if (!checkbutton_zaubermittel->get_active()) return ;
   for (std::list<cH_Zauberwerk>::iterator i=list_Zauberwerk.begin(); 
         i!=list_Zauberwerk.end();++i)
   datavec.push_back(new Data_zaubermittel((*i)->Stufe(),(*i)->Name(),(*i)->Art(),(*i)->Kosten(Typ)));
   alte_zaubermittel_tree->setDataVec(datavec);
}


void midgard_CG::show_neues_zauberwerk()
{
 std::vector<cH_RowDataBase> datavec;
 for (std::list<cH_Zauberwerk>::iterator i=list_Zauberwerk_neu.begin(); 
         i!=list_Zauberwerk_neu.end();++i)
 datavec.push_back(new Data_zaubermittel((*i)->Stufe(),(*i)->Name(),(*i)->Art(),(*i)->Kosten(Typ),(*i)->Preis(),(*i)->Zeitaufwand()));
 neue_zaubermittel_tree->setDataVec(datavec);
}

void midgard_CG::zauberwerk_laden()
{
 list_Zauberwerk_neu.clear();
 Zauberwerk_All ZWA;
 std::list<cH_Zauberwerk> list_tmp=ZWA.get_All();
 for (std::list<cH_Zauberwerk>::const_iterator i=list_tmp.begin();i!=list_tmp.end();++i)
  {
   if ((*i)->ist_gelernt(list_Zauberwerk)) continue ;
   if (((*i)->ist_lernbar(Typ) 
         && Zauberwerk::zauberwerk_voraussetzung((*i)->Name(),Werte)) 
         || checkbutton_alle_zauber->get_active() )
    if (region_check((*i)->Region()) )
      list_Zauberwerk_neu.push_back(*i);
  }
}
