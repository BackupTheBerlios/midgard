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
//#include "Ausnahmen.hh"
//#include "class_zauber.hh"
#include "class_fertigkeiten.hh"
#include "zufall.h"

void midgard_CG::on_zauber_laden_clicked()
{   
  list_Zauber_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Zauber.begin();i!=Database.Zauber.end();++i)
    { cH_Zauber z(*i);
      if ((*i)->ist_gelernt(list_Zauber)) continue ;
      if (z->Zauberart()=="Zaubersalz" && !checkbutton_zaubersalze->get_active())
         continue;
      if (z->Zauberart()=="Beschwörung" && !checkbutton_beschwoerungen->get_active())
         continue;
      if ((*i)->ist_lernbar(Typ,z->get_MapTyp()) || checkbutton_alle_zauber->get_active() )
       if (region_check(z->Region()) )
         list_Zauber_neu.push_back(*i);            
    }
  zauber_zeigen();
}

void midgard_CG::zauber_zeigen()
{
 if (Typ[0]->Zaubern()=="n" && Typ[1]->Zaubern()=="n") return;
 
 zeige_werte(Werte);
 on_speichern_clicked();
 MidgardBasicElement::show_list_in_tree(list_Zauber_neu,neue_zauber_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauber    ,alte_zauber_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk    ,alte_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::on_leaf_selected_alte_zauber(cH_RowDataBase d)
{  
   const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);
   cH_MidgardBasicElement MBE = dt->getMBE();
   int kosten = MBE->Kosten(Typ,Database.ausnahmen);
   if(spruchrolle->get_active()) kosten/=5;
   if (steigern_bool) desteigern(kosten);
   Werte.add_GFP(-kosten);
   MidgardBasicElement::move_element(list_Zauber,list_Zauber_neu,MBE->Name());
   zauber_zeigen();
   zauberwerk_laden();
   zauberwerk_zeigen();
}


void midgard_CG::on_leaf_selected_neue_zauber(cH_RowDataBase d)
{  
  const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  int kosten = MBE->Kosten(Typ,Database.ausnahmen);
  if(spruchrolle->get_active()) kosten/=10;
  
  if (!steigern(kosten,&MBE)) return;
  if (radio_spruchrolle_auto->get_active() && spruchrolle->get_active())
   {
     Werte.add_GFP(2*kosten);
     MidgardBasicElement::move_element(list_Zauber_neu,list_Zauber,MBE->Name());
   }
  else if (radio_spruchrolle_wuerfeln->get_active() && spruchrolle->get_active())
   {
      int gelungen = spruchrolle_wuerfeln(MBE);
      if (gelungen != 0)
        {
         MidgardBasicElement::move_element(list_Zauber_neu,list_Zauber,MBE->Name());
         Werte.add_GFP(2*kosten);
        }
      Werte.add_GFP(kosten);
   }
  else // normales lernen ohne Spruchrolle
   {
     Werte.add_GFP(MBE->Kosten(Typ,Database.ausnahmen));
     MidgardBasicElement::move_element(list_Zauber_neu,list_Zauber,MBE->Name());
   }
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
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk    ,alte_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
}
void midgard_CG::on_checkbutton_zaubermittel_toggled()
{
 zauberwerk_laden();
 zeige_werte(Werte);
 on_speichern_clicked();
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk    ,alte_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::on_spruchrolle_toggled()
{
/*
 if (spruchrolle->get_active() ) 
   { 
      Zauber::set_Spruchrolle(list_Zauber,true);
      Zauber::set_Spruchrolle(list_Zauber_neu,true);
   }
 else 
   { 
      Zauber::set_Spruchrolle(list_Zauber,false);
      Zauber::set_Spruchrolle(list_Zauber_neu,false);
   }
 MidgardBasicElement::show_list_in_tree(list_Zauber_neu,neue_zauber_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauber    ,alte_zauber_tree,Werte,Typ,Database.ausnahmen);
*/
}

bool midgard_CG::spruchrolle_wuerfeln(const cH_MidgardBasicElement& z)
{
 cH_Zauber zauber(z);
 Random random;
 int erf_z = Werte.Zaubern_wert() + Werte.bo_Za() ;
 int xr=random.integer(1,20);
 int iaus=0;
 
 if ((Typ[0]->Short()!="Ma" && Typ[1]->Short()!="Ma") && zauber->Art()=="A") 
    iaus=-2;

 // Für Magier:
 std::string standard="";
 if (Typ[0]->Short()=="Ma") standard=z->Standard(Typ,Database.ausnahmen)[0]; 
 if (Typ[1]->Short()=="Ma") standard=z->Standard(Typ,Database.ausnahmen)[1]; 
 if(standard!="") 
   {
    iaus = zauber->get_spezial_zauber_for_magier(Werte,standard); //iaus = 2 ?
    if (!iaus)
     { if (zauber->Art()=="S")  iaus=+1;
       if (zauber->Art()=="A")  iaus=-1;  }
   }
 
 int x = xr-zauber->iStufe();
 x += iaus;
 x += erf_z;
 std::string strinfo = "Lernversuch von Spruchrolle:
 gewürfelt  Spruchstufe  Ausnahme/Spezial Erfolgswert  Gesamtergebnis\n     "
      +itos(xr)+"            -"+itos(zauber->iStufe())+"               "
      +itos(iaus)+"             "+itos(erf_z)+"       =       "+ itos(x)+"\n";
 manage (new WindowInfo(strinfo.c_str(),true));
 if (x>=20) return true;
 else return false;
}



void midgard_CG::on_button_zauber_sort_clicked()
{
  std::deque<guint> seq = alte_zauber_tree->get_seq();
  switch((Data_fert::Spalten_ZA)seq[0]) {
      case Data_fert::NAMEa_Z  : list_Zauber.sort(cH_Zauber::sort(cH_Zauber::sort::NAME)); ;break;
      case Data_fert::STUFEa_Z : list_Zauber.sort(cH_Zauber::sort(cH_Zauber::sort::STUFE)); ;break;
      case Data_fert::URSPRUNGa_Z : list_Zauber.sort(cH_Zauber::sort(cH_Zauber::sort::URSPRUNG)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}

///////////////////////////////////////////////////////////////////////////////
//Zauberwerk
///////////////////////////////////////////////////////////////////////////////

void midgard_CG::on_button_zaubermittel_sort_clicked()
{
  std::deque<guint> seq = alte_zaubermittel_tree->get_seq();
  switch((Data_fert::Spalten_ZWA)seq[0]) {
      case Data_fert::NAMEa_ZW  : list_Zauberwerk.sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::NAME)) ;break;
      case Data_fert::STUFEa_ZW : list_Zauberwerk.sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::STUFE)) ;break;
      case Data_fert::ARTa_ZW :   list_Zauberwerk.sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::ART));break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}


void midgard_CG::on_leaf_selected_alte_zauberwerk(cH_RowDataBase d)
{  
 const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();
 if (steigern_bool) desteigern(MBE->Kosten(Typ,Database.ausnahmen));
 Werte.add_GFP(-MBE->Kosten(Typ,Database.ausnahmen));
 MidgardBasicElement::move_element(list_Zauberwerk,list_Zauberwerk_neu,MBE->Name());
 zauberwerk_zeigen();
}

void midgard_CG::zauberwerk_zeigen()
{
 zauberwerk_laden();
 zeige_werte(Werte);
 on_speichern_clicked();
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk    ,alte_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::on_leaf_selected_neue_zauberwerk(cH_RowDataBase d)
{  
  const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if (!steigern(MBE->Kosten(Typ,Database.ausnahmen),&MBE)) return;
  Werte.add_GFP(MBE->Kosten(Typ,Database.ausnahmen));  
  MidgardBasicElement::move_element(list_Zauberwerk_neu,list_Zauberwerk,MBE->Name());
  zauberwerk_zeigen();
}

void midgard_CG::zauberwerk_laden()
{
 list_Zauberwerk_neu.clear();
 for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Zauberwerk.begin();i!=Database.Zauberwerk.end();++i)
  {
   cH_Zauberwerk z(*i);
   if ((*i)->ist_gelernt(list_Zauberwerk)) continue ;
   if (((*i)->ist_lernbar(Typ,z->get_MapTyp()) 
         && z->Voraussetzungen(list_Zauber)) 
         || checkbutton_alle_zauber->get_active() )
    if (region_check(z->Region()) )
      list_Zauberwerk_neu.push_back(*i);
  }
}
