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
//#include "Ausnahmen.hh"
#include "class_zauber.hh"
#include "Sprache.hh"
#include "Schrift.hh"


void midgard_CG::on_schrift_laden_clicked()
{   
   list_Schrift_neu.clear();
   for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Schrift.begin();i!=Database.Schrift.end();++i)
    { cH_Schrift s(*i);
      if((*i)->ist_gelernt(list_Schrift)) continue;
      if (region_check(s->Region()) )  
         if(s->kann_Sprache(list_Sprache))
            list_Schrift_neu.push_back(*i) ;
    }
   schriften_zeigen();
}

void midgard_CG::on_sprache_laden_clicked()
{   
   list_Sprache_neu.clear();
   for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Sprache.begin();i!=Database.Sprache.end();++i)
    { cH_Sprache s(*i);
      if((*i)->ist_gelernt(list_Sprache)) continue;
      if (region_check(s->Region()) )  
        {  s->set_Erfolgswert(1);
           list_Sprache_neu.push_back(*i) ;
        }
    }
   sprachen_zeigen();
   on_schrift_laden_clicked();
}   

void midgard_CG::schriften_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
//   Ausnahmen ausnahmen(Werte,Typ,vec_Beruf);
   MidgardBasicElement::show_list_in_tree(list_Schrift    ,alte_schrift_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Schrift_neu,neue_schrift_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::sprachen_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
//   Ausnahmen ausnahmen(Werte,Typ,vec_Beruf);
   MidgardBasicElement::show_list_in_tree(list_Sprache    ,alte_sprache_tree,Werte,Typ,Database.ausnahmen,'O');
   MidgardBasicElement::show_list_in_tree(list_Sprache_neu,neue_sprache_tree,Werte,Typ,Database.ausnahmen,'N');
}


void midgard_CG::on_leaf_selected_neue_sprache(cH_RowDataBase d)
{  
   const Data_sprache *dt=dynamic_cast<const Data_sprache*>(&*d);  
   if (!steigern(dt->Kosten(),"Sprache")) return;
   Werte.add_GFP(dt->Kosten());
   MidgardBasicElement::move_element(list_Sprache_neu,list_Sprache,dt->Name());
   sprachen_zeigen();
   on_schrift_laden_clicked();
}   
    
void midgard_CG::on_leaf_selected_alte_sprache(cH_RowDataBase d)
{  
   const Data_sprache *dt=dynamic_cast<const Data_sprache*>(&*d);  
   if (radio_sprache_steigern->get_active() && dt->Steigern())
    {
      if (!steigern(dt->Steigern(),"Sprache")) return;
      Werte.add_GFP(dt->Steigern());
      for (std::list<cH_MidgardBasicElement>::iterator i=list_Sprache.begin();i!= list_Sprache.end();++i)
         if ( cH_Sprache(*i)->Name() == dt->Name()) cH_Sprache(*i)->add_Erfolgswert(1);
    }
   if (radio_sprache_reduzieren->get_active() && dt->Reduzieren() )
    {
      if (steigern_bool) desteigern(dt->Reduzieren());
      Werte.add_GFP(-dt->Reduzieren());
      for (std::list<cH_MidgardBasicElement>::iterator i=list_Sprache.begin();i!= list_Sprache.end();++i)
         if ( cH_Sprache(*i)->Name() == dt->Name()) cH_Sprache(*i)->add_Erfolgswert(-1);
    }
   if (radio_sprache_verlernen->get_active() && dt->Verlernen() )
    {
      if (steigern_bool) desteigern(dt->Verlernen());
      Werte.add_GFP(-dt->Verlernen());
      MidgardBasicElement::move_element(list_Sprache,list_Sprache_neu,dt->Name());
    }
   on_sprache_laden_clicked();
}
    
void midgard_CG::on_radio_sprache_steigern_toggled()
{   
}   
    
void midgard_CG::on_radio_sprache_reduzieren_toggled()
{   
}   
    
void midgard_CG::on_radio_sprache_verlernen_toggled()
{   
}   

void midgard_CG::on_button_sprache_sort_clicked()
{
  std::deque<guint> seq = alte_sprache_tree->get_seq();
  switch((Data_sprache::Spalten_A)seq[0]) {
      case Data_sprache::NAMEa : list_Sprache.sort(cH_Sprache::sort(cH_Sprache::sort::NAME)); ;break;
      case Data_sprache::WERTa : list_Sprache.sort(cH_Sprache::sort(cH_Sprache::sort::ERFOLGSWERT)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}


void midgard_CG::on_leaf_selected_alte_schrift(cH_RowDataBase d)
{  
   const Data_schrift *dt=dynamic_cast<const Data_schrift*>(&*d);  
   if (steigern_bool) desteigern(dt->Kosten());
   Werte.add_GFP(-dt->Kosten());
   MidgardBasicElement::move_element(list_Schrift,list_Schrift_neu,dt->Name());
   on_sprache_laden_clicked();
}   
    
void midgard_CG::on_leaf_selected_neue_schrift(cH_RowDataBase d)
{  
   const Data_schrift *dt=dynamic_cast<const Data_schrift*>(&*d);  
   if (!steigern(dt->Kosten(),"Lesen/Schreiben")) return;
   Werte.add_GFP(dt->Kosten());
   MidgardBasicElement::move_element(list_Schrift_neu,list_Schrift,dt->Name());
   on_sprache_laden_clicked();
}   

