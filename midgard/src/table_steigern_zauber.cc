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
#include <Misc/itos.h>
#include "LernListen.hh"
#include <libmagus/Ausgabe.hh>
#include <libmagus/Random.hh>
#include <libmagus/LernListen.hh>

void table_steigern::on_zauber_laden_clicked()
{ if (notebook_lernen->get_current_page()!=PAGE_ZAUBER) return;
 try{
  list_Zauber_neu=LernListen::get_steigern_Zauberliste(hauptfenster->getAben(),togglebutton_zaubersalze->get_active(),
  					   LernListen::region_check(hauptfenster->getAben(),"MdS"),
                                           togglebutton_alle_zauber->get_active(),
                                           hauptfenster->getAben().wie_steigern==Grundwerte::ws_Spruchrolle);
 }catch(std::exception &e) {Ausgabe(Ausgabe::Error,e.what());}
  zauber_zeigen();
}

void table_steigern::zauber_zeigen()
{
 if(!hauptfenster->getAben().is_mage()) return;
 zeige_werte();
 MidgardBasicTree::show_list_in_tree(list_Zauber_neu,neue_zauber_tree,hauptfenster->getChar().actualIterator());
 MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Zauber(),alte_zauber_tree,hauptfenster->getChar().actualIterator());
 zauberwerk_zeigen();
}

void table_steigern::on_leaf_selected_alte_zauber(cH_RowDataBase d)
{  
 if(MidgardBasicElement_leaf_alt(d))
   zauber_zeigen();
}


void table_steigern::on_leaf_selected_neue_zauber(cH_RowDataBase d)
{ if(hauptfenster->getAben().wie_steigern==Grundwerte::ws_Spruchrolle
     && hauptfenster->getAben().wie_steigern_variante==Grundwerte::wsv_SpruchrolleRoll)
   { // 2* würfeln???
     wuerfel_lesen_von_zauberschrift();
     return;
   }   
  MidgardBasicElement_leaf_neu(d);
//  zauber_zeigen();
}

void table_steigern::wuerfel_lesen_von_zauberschrift()
{
  int x= Random::W20();
  int e=hauptfenster->getAben().Erfolgswert("Lesen von Zauberschrift").first;
  int bonus;
  if(x+e >= 20) bonus=+4;
  else          bonus=-4;
  Ausgabe(Ausgabe::ActionNeeded,"EW:Lesen von Zauberschrift => "+itos(x)+"+"+itos(e)+"="+itos(x+e)
   +"\n    => Bonus= "+itos(bonus)+"\nSoll versucht werden den Zauberspruch zu lernen?");
#warning dialog
#if 0  
  hauptfenster->InfoFenster->AppendShow("EW:Lesen von Zauberschrift => "+itos(x)+"+"+itos(e)+"="+itos(x+e)
   +"\n    => Bonus= "+itos(bonus)+"\nSoll versucht werden den Zauberspruch zu lernen?"
   ,WindowInfo::LernenMitSpruchrolle,bonus);
#endif   
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


#include <locale.h>

void table_steigern::on_alte_zauber_reorder()
{
//cout << "Locale :"<< localeconv() <<'\n';
  std::deque<guint> seq = alte_zauber_tree->get_seq();
  switch((Data_SimpleTree::Spalten_ZAUBER)seq[0]) {
      case Data_SimpleTree::NAMEn_Z  : hauptfenster->getAben().List_Zauber().sort(cH_Zauber::sort(cH_Zauber::sort::NAME)); ;break;
      case Data_SimpleTree::STUFEn_Z : hauptfenster->getAben().List_Zauber().sort(cH_Zauber::sort(cH_Zauber::sort::STUFE)); ;break;
      case Data_SimpleTree::URSPRUNGn_Z : hauptfenster->getAben().List_Zauber().sort(cH_Zauber::sort(cH_Zauber::sort::URSPRUNG)); ;break;
      default : Ausgabe(Ausgabe::Error,"Sortieren nach diesem Parameter ist nicht möglich");
   }
}

///////////////////////////////////////////////////////////////////////////////
//Zauberwerk
///////////////////////////////////////////////////////////////////////////////

void table_steigern::on_alte_zaubermittel_reorder()
{
  std::deque<guint> seq = alte_zaubermittel_tree->get_seq();
  switch((Data_SimpleTree::Spalten_ZAUBERWERK)seq[0]) {
      case Data_SimpleTree::NAMEn_ZW  : hauptfenster->getAben().List_Zauberwerk().sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::NAME)) ;break;
      case Data_SimpleTree::STUFEn_ZW : hauptfenster->getAben().List_Zauberwerk().sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::STUFE)) ;break;
      case Data_SimpleTree::ARTn_ZW :   hauptfenster->getAben().List_Zauberwerk().sort(cH_Zauberwerk::sort(cH_Zauberwerk::sort::ART));break;
      default : Ausgabe(Ausgabe::Error,"Sortieren nach diesem Parameter ist nicht möglich");
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
 MidgardBasicTree::show_list_in_tree(list_Zauberwerk_neu,neue_zaubermittel_tree,hauptfenster->getChar().actualIterator());
 MidgardBasicTree::show_list_in_tree(hauptfenster->getAben().List_Zauberwerk()    ,alte_zaubermittel_tree,hauptfenster->getChar().actualIterator());
}

void table_steigern::on_leaf_selected_neue_zauberwerk(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
//  zauberwerk_zeigen();
}

void table_steigern::zauberwerk_laden()
{
 list_Zauberwerk_neu=LernListen::get_steigern_ZauberWerkliste(hauptfenster->getAben(),
                                                      togglebutton_alle_zauber->get_active());
}
