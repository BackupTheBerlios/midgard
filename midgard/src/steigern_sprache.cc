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
#include "class_SimpleTree.hh"

void midgard_CG::on_schrift_laden_clicked()
{   
   list_Schrift_neu.clear();
   for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Schrift.begin();i!=Database.Schrift.end();++i)
    { cH_Schrift s(*i);
      if((*i)->ist_gelernt(list_Schrift)) continue;
      if (region_check(s->Region()) )  
         if(s->kann_Sprache(list_Sprache))
           { s->set_Erfolgswert(cH_Fertigkeit("Schreiben")->Anfangswert());
             list_Schrift_neu.push_back(*i) ;
           }
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
        {  s->set_Erfolgswert(cH_Fertigkeit("Sprache")->Anfangswert());
           list_Sprache_neu.push_back(*i) ;
        }
    }
   sprachen_zeigen();
   on_schrift_laden_clicked();
}   

void midgard_CG::schriften_zeigen()
{
   zeige_werte(Werte);
#ifndef USE_XML   
   on_speichern_clicked();
#endif
   MidgardBasicElement::show_list_in_tree(list_Schrift    ,alte_schrift_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Schrift_neu,neue_schrift_tree,Werte,Typ,Database.ausnahmen);
}

void midgard_CG::sprachen_zeigen()
{
   zeige_werte(Werte);
#ifndef USE_XML   
   on_speichern_clicked();
#endif   
   MidgardBasicElement::show_list_in_tree(list_Sprache    ,alte_sprache_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Sprache_neu,neue_sprache_tree,Werte,Typ,Database.ausnahmen);
}


void midgard_CG::on_leaf_selected_neue_sprache(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  sprachen_zeigen();
  on_schrift_laden_clicked();
}
    
void midgard_CG::on_leaf_selected_alte_sprache(cH_RowDataBase d)
{  
  if(MidgardBasicElement_leaf_alt(d))
   {
     neue_schrift_wegen_sprache();
     on_sprache_laden_clicked();
   }
}
    
void midgard_CG::on_alte_sprache_reorder()
{
   on_button_sprache_sort_clicked();
}

void midgard_CG::on_button_sprache_sort_clicked()
{
  std::deque<guint> seq = alte_sprache_tree->get_seq();
  switch((Data_SimpleTree::Spalten_LONG_ALT)seq[0]) {
      case Data_SimpleTree::NAMEa : list_Sprache.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME)); ;break;
      case Data_SimpleTree::WERTa : list_Sprache.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::ERFOLGSWERT)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}


void midgard_CG::on_leaf_selected_alte_schrift(cH_RowDataBase d)
{  
  if(MidgardBasicElement_leaf_alt(d))
   {
     neue_schrift_wegen_sprache();
     on_sprache_laden_clicked();
   }
}   
    
void midgard_CG::on_leaf_selected_neue_schrift(cH_RowDataBase d)
{  
  MidgardBasicElement_leaf_neu(d);
  on_sprache_laden_clicked();
}   



void midgard_CG::neue_schrift_wegen_sprache()
{
  // Alle gelernten Sprachen testen
  for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Sprache.begin();i!=list_Sprache.end();++i)
   {
     if((*i)->Erfolgswert()<10) continue;
     // welche Schriften gehören zu dieser Sprache?
     std::vector<std::string> VS=cH_Sprache(*i)->Schrift();
     for(std::vector<std::string>::const_iterator j=VS.begin();j!=VS.end();++j)
      {
        cH_Schrift s(*j);
        if(s->ist_gelernt(list_Schrift)) continue;
//        std::list<cH_MidgardBasicElement> gS=s->gleicheSchrift(list_Schrift);
        std::list<cH_MidgardBasicElement> gS=s->gleicheSchrift(Database.Schrift);
        for(std::list<cH_MidgardBasicElement>::const_iterator k=gS.begin();k!=gS.end();++k)
         {
           if(s->Name()!=(*k)->Name()) continue;
           int e=andereSprache_gleicheSchriftart(s->Art_der_Schrift());
           if(e>=12) 
            {
              (*k)->set_Erfolgswert(8);   
              list_Schrift.push_back(*k); 
            }
         }
      }
   }  
}

int midgard_CG::andereSprache_gleicheSchriftart(std::string art)
{
  int e=0;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Schrift.begin();i!=list_Schrift.end();++i)
   {
     if (cH_Schrift(*i)->Art_der_Schrift()==art)
        if( (*i)->Erfolgswert() > e ) 
           e = (*i)->Erfolgswert();
   }
  return e;
}
