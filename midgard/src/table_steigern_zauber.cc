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
#include "table_steigern.hh"
#include "class_SimpleTree.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include <Aux/itos.h>

void table_steigern::on_zauber_laden_clicked()
{   
  list_Zauber_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getCDatabase().Zauber.begin();i!=hauptfenster->getCDatabase().Zauber.end();++i)
    { cH_Zauber z(*i);
      if (MidgardBasicElement_mutable(*i).ist_gelernt(hauptfenster->getCChar().CList_Zauber()) && (*i)->ZusatzEnum(hauptfenster->getCChar().getVTyp())==MidgardBasicElement::ZNone) continue ;
      if (z->Zauberart()=="Zaubersalz" && !togglebutton_zaubersalze->get_active())
         continue;
      if (z->Zauberart()=="Beschwörung" && !Region::isActive(hauptfenster->getCDatabase().Regionen,cH_Region("MdS")))
         continue;
      if (togglebutton_spruchrolle->get_active() && !z->Spruchrolle() ) continue;
      if ((*i)->ist_lernbar(hauptfenster->getCChar().getVTyp(),z->get_MapTyp()) || togglebutton_alle_zauber->get_active() )
      if (hauptfenster->region_check(z->Region()) && hauptfenster->nsc_check((*i)->NSC_only()))
        {
         if(togglebutton_spruchrolle->get_active()) z->setSpruchrolleFaktor(0.1);
         else z->setSpruchrolleFaktor(1);
         list_Zauber_neu.push_back(*i);            
        }
    }
  zauber_zeigen();
}

void table_steigern::zauber_zeigen()
{
// if (Typ[0]->Zaubern()=="n" && Typ[1]->Zaubern()=="n") return;
// if(!hauptfenster->getCChar().CTyp1()->is_mage() && !hauptfenster->getCChar().CTyp2()->is_mage() ) return;
 if(!hauptfenster->getCChar().is_mage()) return;
 zeige_werte();
 MidgardBasicElement::show_list_in_tree(list_Zauber_neu,neue_zauber_tree,hauptfenster);
 MidgardBasicElement::show_list_in_tree(hauptfenster->getCChar().CList_Zauber(),alte_zauber_tree,hauptfenster);
 zauberwerk_zeigen();
}

void table_steigern::on_leaf_selected_alte_zauber(cH_RowDataBase d)
{  
 if(MidgardBasicElement_leaf_alt(d))
  {
   zauber_zeigen();
  }
}


void table_steigern::on_leaf_selected_neue_zauber(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  zauber_zeigen();
}

void table_steigern::on_togglebutton_zaubersalze_toggled()
{
 on_zauber_laden_clicked();
}
void table_steigern::on_togglebutton_alle_zauber_toggled()
{
 on_zauber_laden_clicked();
}

void table_steigern::on_spruchrolle_toggled()
{
 on_zauber_laden_clicked();
}

bool table_steigern::spruchrolle_wuerfeln(const cH_MidgardBasicElement& z)
{
 cH_Zauber zauber(z);
 int erf_z = hauptfenster->getCWerte().Zaubern_wert() + hauptfenster->getCWerte().bo_Za() ;
 int xr=hauptfenster->random.integer(1,20);
 int iaus=0;
 
 if ((hauptfenster->getCChar().CTyp1()->Short()!="Ma" && hauptfenster->getCChar().CTyp2()->Short()!="Ma") && zauber->Art()=="A") 
    iaus=-2;

 // Für Magier:
 std::string standard="";
 if (hauptfenster->getCChar().CTyp1()->Short()=="Ma") standard=z->Standard(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())[0]; 
 if (hauptfenster->getCChar().CTyp2()->Short()=="Ma") standard=z->Standard(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())[1]; 
 if(standard!="") 
   {
    iaus = zauber->get_spezial_zauber_for_magier(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp(),standard); 
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
 hauptfenster->set_info(strinfo);
 if (x>=20) return true;
 else return false;
}


void table_steigern::on_alte_zauber_reorder()
{
  std::deque<guint> seq = alte_zauber_tree->get_seq();
  switch((Data_SimpleTree::Spalten_ZAUBER)seq[0]) {
      case Data_SimpleTree::NAMEn_Z  : hauptfenster->getChar().List_Zauber().sort(cH_Zauber::sort(cH_Zauber::sort::NAME)); ;break;
      case Data_SimpleTree::STUFEn_Z : hauptfenster->getChar().List_Zauber().sort(cH_Zauber::sort(cH_Zauber::sort::STUFE)); ;break;
      case Data_SimpleTree::URSPRUNGn_Z : hauptfenster->getChar().List_Zauber().sort(cH_Zauber::sort(cH_Zauber::sort::URSPRUNG)); ;break;
      default : hauptfenster->set_status("Sortieren nach diesem Parameter\n ist nicht möglich");
   }
}

///////////////////////////////////////////////////////////////////////////////
//Zauberwerk
///////////////////////////////////////////////////////////////////////////////

void table_steigern::on_alte_zaubermittel_reorder()
{
  std::deque<guint> seq = alte_zaubermittel_tree->get_seq();
  switch((Data_SimpleTree::Spalten_ZAUBERWERK)seq[0]) {
      case Data_SimpleTree::NAMEn_ZW  : hauptfenster->getChar().List_Zauberwerk().sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::NAME)) ;break;
      case Data_SimpleTree::STUFEn_ZW : hauptfenster->getChar().List_Zauberwerk().sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::STUFE)) ;break;
      case Data_SimpleTree::ARTn_ZW :   hauptfenster->getChar().List_Zauberwerk().sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::ART));break;
      default : hauptfenster->set_status("Sortieren nach diesem Parameter\n ist nicht möglich");
   }
}


void table_steigern::on_leaf_selected_alte_zauberwerk(cH_RowDataBase d)
{  
 MidgardBasicElement_leaf_alt(d);
 zauberwerk_zeigen();
}

void table_steigern::zauberwerk_zeigen()
{
 zauberwerk_laden();
 zeige_werte();
 MidgardBasicElement::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,hauptfenster);
 MidgardBasicElement::show_list_in_tree(hauptfenster->getCChar().CList_Zauberwerk()    ,alte_zaubermittel_tree,hauptfenster);
}

void table_steigern::on_leaf_selected_neue_zauberwerk(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  zauberwerk_zeigen();
}

void table_steigern::zauberwerk_laden()
{
 list_Zauberwerk_neu.clear();
 for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getCDatabase().Zauberwerk.begin();i!=hauptfenster->getCDatabase().Zauberwerk.end();++i)
  {
   cH_Zauberwerk z(*i);
   if (MidgardBasicElement_mutable(*i).ist_gelernt(hauptfenster->getCChar().CList_Zauberwerk())) continue ;
   if (((*i)->ist_lernbar(hauptfenster->getCChar().getVTyp(),z->get_MapTyp()) 
         && z->Voraussetzungen(hauptfenster->getCChar().CList_Zauber())
         && z->Voraussetzungen_Fertigkeit(hauptfenster->getCChar().CList_Fertigkeit())) 
         || togglebutton_alle_zauber->get_active() )
     if (hauptfenster->region_check(z->Region()) )
       list_Zauberwerk_neu.push_back(*i);
  }
}
