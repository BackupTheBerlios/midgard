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
#include "Sprache.hh"
#include "Schrift.hh"
#include "class_fertigkeiten.hh"

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
   MidgardBasicElement::show_list_in_tree(list_Schrift    ,alte_schrift_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Schrift_neu,neue_schrift_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::sprachen_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
   MidgardBasicElement::show_list_in_tree(list_Sprache    ,alte_sprache_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Sprache_neu,neue_sprache_tree,Werte,Typ,Database.ausnahmen);
}


void midgard_CG::on_leaf_selected_neue_sprache(cH_RowDataBase d)
{  
   const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);  
   cH_MidgardBasicElement MBE = dt->getMBE();
   if (!steigern(MBE->Kosten(Typ,Database.ausnahmen),&MBE)) return;
   Werte.add_GFP(MBE->Kosten(Typ,Database.ausnahmen));
   MidgardBasicElement::move_element(list_Sprache_neu,list_Sprache,MBE->Name());
   sprachen_zeigen();
   on_schrift_laden_clicked();
}   
    
void midgard_CG::on_leaf_selected_alte_sprache(cH_RowDataBase d)
{  
   const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);  
   cH_MidgardBasicElement MBE = dt->getMBE();
   if (radio_sprache_steigern->get_active() && MBE->Steigern(Typ,Database.ausnahmen))
    {
      for (std::list<cH_MidgardBasicElement>::iterator i=list_Sprache.begin();i!= list_Sprache.end();++i)
         if ( cH_Sprache(*i)->Name() == MBE->Name()) 
            if (cH_Sprache(*i)->Maxwert()==(*i)->Erfolgswert() ) return;
      if (!steigern(MBE->Steigern(Typ,Database.ausnahmen),&MBE)) return;
      Werte.add_GFP(MBE->Steigern(Typ,Database.ausnahmen));
      for (std::list<cH_MidgardBasicElement>::iterator i=list_Sprache.begin();i!= list_Sprache.end();++i)
         if ( cH_Sprache(*i)->Name() == MBE->Name()) cH_Sprache(*i)->add_Erfolgswert(1);
    }
   if (radio_sprache_reduzieren->get_active() && MBE->Reduzieren(Typ,Database.ausnahmen) )
    {
      if (steigern_bool) desteigern(MBE->Reduzieren(Typ,Database.ausnahmen));
      Werte.add_GFP(-MBE->Reduzieren(Typ,Database.ausnahmen));
      for (std::list<cH_MidgardBasicElement>::iterator i=list_Sprache.begin();i!= list_Sprache.end();++i)
         if ( cH_Sprache(*i)->Name() == MBE->Name()) cH_Sprache(*i)->add_Erfolgswert(-1);
    }
   if (radio_sprache_verlernen->get_active() && MBE->Verlernen(Typ,Database.ausnahmen) )
    {
      if (steigern_bool) desteigern(MBE->Verlernen(Typ,Database.ausnahmen));
      Werte.add_GFP(-MBE->Verlernen(Typ,Database.ausnahmen));
      MidgardBasicElement::move_element(list_Sprache,list_Sprache_neu,MBE->Name());
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
  switch((Data_fert::Spalten_SPA)seq[0]) {
      case Data_fert::NAMEa_SP : list_Sprache.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME)); ;break;
      case Data_fert::WERTa_SP : list_Sprache.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::ERFOLGSWERT)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}


void midgard_CG::on_leaf_selected_alte_schrift(cH_RowDataBase d)
{  
   const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);  
   cH_MidgardBasicElement MBE = dt->getMBE();
   if (steigern_bool) desteigern(MBE->Kosten(Typ,Database.ausnahmen));
   Werte.add_GFP(-MBE->Kosten(Typ,Database.ausnahmen));
   MidgardBasicElement::move_element(list_Schrift,list_Schrift_neu,MBE->Name());
   on_sprache_laden_clicked();
}   
    
void midgard_CG::on_leaf_selected_neue_schrift(cH_RowDataBase d)
{  
   const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);  
   cH_MidgardBasicElement MBE = dt->getMBE();
   if (!steigern(MBE->Kosten(Typ,Database.ausnahmen),&MBE)) return;
   Werte.add_GFP(MBE->Kosten(Typ,Database.ausnahmen));
   MidgardBasicElement::move_element(list_Schrift_neu,list_Schrift,MBE->Name());
   on_sprache_laden_clicked();
}   

