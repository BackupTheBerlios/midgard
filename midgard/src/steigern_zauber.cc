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
#include "class_SimpleTree.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include <Aux/itos.h>

void midgard_CG::on_zauber_laden_clicked()
{   
  list_Zauber_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Zauber.begin();i!=Database.Zauber.end();++i)
    { cH_Zauber z(*i);
      if ((*i)->ist_gelernt(list_Zauber)) continue ;
      if (z->Zauberart()=="Zaubersalz" && !togglebutton_zaubersalze->get_active())
         continue;
      if (z->Zauberart()=="Beschwörung" && !Region::isActive(Database.Regionen,cH_Region("MdS")))
         continue;
      if (togglebutton_spruchrolle->get_active() && !z->Spruchrolle() ) continue;
      if ((*i)->ist_lernbar(Typ,z->get_MapTyp()) || togglebutton_alle_zauber->get_active() )
       if (region_check(z->Region()) )
        {
         if(togglebutton_spruchrolle->get_active()) z->setSpruchrolleFaktor(0.1);
         else z->setSpruchrolleFaktor(1);
         list_Zauber_neu.push_back(*i);            
        }
    }
  zauber_zeigen();
}

void midgard_CG::zauber_zeigen()
{
 if (Typ[0]->Zaubern()=="n" && Typ[1]->Zaubern()=="n") return;
 
 zeige_werte(Werte);
 steigern_aktivieren();
 MidgardBasicElement::show_list_in_tree(list_Zauber_neu,neue_zauber_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauber    ,alte_zauber_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk    ,alte_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::on_leaf_selected_alte_zauber(cH_RowDataBase d)
{  
 if(MidgardBasicElement_leaf_alt(d))
  {
   zauber_zeigen();
   zauberwerk_laden();
   zauberwerk_zeigen();
  }
}


void midgard_CG::on_leaf_selected_neue_zauber(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  zauber_zeigen();
  zauberwerk_laden();
  zauberwerk_zeigen();
}

void midgard_CG::on_togglebutton_zaubersalze_toggled()
{
 on_zauber_laden_clicked();
}
void midgard_CG::on_togglebutton_alle_zauber_toggled()
{
 on_zauber_laden_clicked();
}

/*
void midgard_CG::on_checkbutton_zaubermittel_toggled()
{
 zauberwerk_laden();
 zeige_werte(Werte);
#ifndef USE_XML 
 on_speichern_clicked();
#else
   steigern_aktivieren();
#endif
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk    ,alte_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
}
*/

void midgard_CG::on_spruchrolle_toggled()
{
 on_zauber_laden_clicked();
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
 InfoFenster->AppendShow(strinfo.c_str(),false);
 if (x>=20) return true;
 else return false;
}


void midgard_CG::on_alte_zauber_reorder()
{
  on_button_zauber_sort_clicked();
}

void midgard_CG::on_button_zauber_sort_clicked()
{
  std::deque<guint> seq = alte_zauber_tree->get_seq();
  switch((Data_SimpleTree::Spalten_ZAUBER)seq[0]) {
      case Data_SimpleTree::NAMEn_Z  : list_Zauber.sort(cH_Zauber::sort(cH_Zauber::sort::NAME)); ;break;
      case Data_SimpleTree::STUFEn_Z : list_Zauber.sort(cH_Zauber::sort(cH_Zauber::sort::STUFE)); ;break;
      case Data_SimpleTree::URSPRUNGn_Z : list_Zauber.sort(cH_Zauber::sort(cH_Zauber::sort::URSPRUNG)); ;break;
      default : InfoFenster->AppendShow("Sortieren nach diesem Parameter\n ist nicht möglich");
   }
}

///////////////////////////////////////////////////////////////////////////////
//Zauberwerk
///////////////////////////////////////////////////////////////////////////////

void midgard_CG::on_alte_zaubermittel_reorder()
{
  on_button_zaubermittel_sort_clicked();
}

void midgard_CG::on_button_zaubermittel_sort_clicked()
{
  std::deque<guint> seq = alte_zaubermittel_tree->get_seq();
  switch((Data_SimpleTree::Spalten_ZAUBERWERK)seq[0]) {
      case Data_SimpleTree::NAMEn_ZW  : list_Zauberwerk.sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::NAME)) ;break;
      case Data_SimpleTree::STUFEn_ZW : list_Zauberwerk.sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::STUFE)) ;break;
      case Data_SimpleTree::ARTn_ZW :   list_Zauberwerk.sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::ART));break;
      default : InfoFenster->AppendShow("Sortieren nach diesem Parameter\n ist nicht möglich");
   }
}


void midgard_CG::on_leaf_selected_alte_zauberwerk(cH_RowDataBase d)
{  
 MidgardBasicElement_leaf_alt(d);
 zauberwerk_zeigen();
}

void midgard_CG::zauberwerk_zeigen()
{
 zauberwerk_laden();
 zeige_werte(Werte);
#ifndef USE_XML 
 on_speichern_clicked();
#else
   steigern_aktivieren();
#endif 
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk    ,alte_zaubermittel_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::on_leaf_selected_neue_zauberwerk(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
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
         && z->Voraussetzungen(list_Zauber)
         && z->Voraussetzungen_Fertigkeit(list_Fertigkeit)) 
         || togglebutton_alle_zauber->get_active() )
     if (region_check(z->Region()) )
       list_Zauberwerk_neu.push_back(*i);
  }
}
