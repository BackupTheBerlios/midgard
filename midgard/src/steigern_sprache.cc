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
#include "Ausnahmen.hh"
#include "class_zauber.hh"
#include "Sprache.hh"
#include "Schrift.hh"


void midgard_CG::on_sprache_laden_clicked()
{   
   list_Schrift_neu.clear();
   Schriften_All SA(laden_label);
   std::list<cH_MidgardBasicElement> list_tmp = SA.get_All();
   for (std::list<cH_MidgardBasicElement>::const_iterator i=list_tmp.begin();i!=list_tmp.end();++i)
    { cH_Schrift s(*i);
      if((*i)->ist_gelernt(list_Schrift)) continue;
      if (region_check(s->Region()) )  list_Schrift_neu.push_back(*i) ;
    }

   list_Sprache_neu.clear();
   Sprachen_All SPA(laden_label);
   std::list<cH_MidgardBasicElement> list_tmp2 = SPA.get_All();
   for (std::list<cH_MidgardBasicElement>::const_iterator i=list_tmp2.begin();i!=list_tmp2.end();++i)
    { cH_Sprache s(*i);
      if((*i)->ist_gelernt(list_Sprache)) continue;
      if (region_check(s->Region()) )  list_Sprache_neu.push_back(*i) ;
    }

   schriften_zeigen();
   sprachen_zeigen();
}   

void midgard_CG::schriften_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
   Ausnahmen ausnahmen(Werte,Typ,vec_Beruf);
   MidgardBasicElement::show_list_in_tree(list_Schrift    ,alte_schrift_tree,Werte,Typ,ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Schrift_neu,neue_schrift_tree,Werte,Typ,ausnahmen);
}

void midgard_CG::sprachen_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
   Ausnahmen ausnahmen(Werte,Typ,vec_Beruf);
   MidgardBasicElement::show_list_in_tree(list_Sprache    ,alte_sprache_tree,Werte,Typ,ausnahmen,'O');
   MidgardBasicElement::show_list_in_tree(list_Sprache_neu,neue_sprache_tree,Werte,Typ,ausnahmen,'N');
}


void midgard_CG::on_leaf_selected_neue_sprache(cH_RowDataBase d)
{  
   const Data_sprache *dt=dynamic_cast<const Data_sprache*>(&*d);  
   if (!steigern(dt->Kosten(),"Sprache")) return;
   Werte.add_GFP(dt->Kosten());
   MidgardBasicElement::move_element(list_Sprache_neu,list_Sprache,dt->Name());
   on_sprache_laden_clicked();
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

/*
void midgard_CG::show_alte_sprachen()
{
   std::vector<cH_RowDataBase> datavec;
   cH_Fertigkeit sprache("Sprache",Typ,Ausnahmen(Werte,Typ,vec_Beruf));
//   double fac = midgard_CG::get_standard_fertigkeit(Typ[0]->Short(),Typ[1]->Short(),"Sprache");
   for (std::vector<H_Data_sprache>::const_iterator i=vec_Sprachen.begin();i!=vec_Sprachen.end();++i)
      {
         exec sql begin declare section;
            int db_max_erfolgswert;
            char db_alter_erfolgswert[10];
            char db_neuer_erfolgswert[10];
            char db_sprache[50];
            char query[256];
            int db_steigern, db_reduzieren, db_verlernen;
         exec sql end declare section;
         strncpy(db_sprache,((*i)->Name()).c_str(),sizeof(db_sprache));
         exec sql select distinct max_wert into :db_max_erfolgswert 
               from sprachen where name = :db_sprache;


         std::string ae = "p";  ae += itos((*i)->Wert());
         std::string ne = "p";  ne += itos((*i)->Wert()+1);
         strncpy(db_neuer_erfolgswert, ne.c_str(), sizeof(db_neuer_erfolgswert));
         strncpy(db_alter_erfolgswert, ae.c_str(), sizeof(db_alter_erfolgswert));

         snprintf(query,sizeof(query),"SELECT \
         coalesce(%s,0), coalesce(%s,0) 
         FROM steigern_fertigkeiten_werte \
         WHERE name = 'Sprache'",
         db_alter_erfolgswert,db_neuer_erfolgswert);

         Transaction tr;
         exec sql prepare s_ein_ from :query;
         exec sql declare s_ein cursor for s_ein_;
         exec sql open s_ein;
         exec sql fetch s_ein into :db_reduzieren, :db_steigern ;
         SQLerror::test(__FILELINE__);
         exec sql close s_ein;
         tr.close();
         
         exec sql select distinct fp into :db_verlernen from sprachen where name = :db_sprache ;
         SQLerror::test(__FILELINE__);
         if (db_reduzieren !=0) db_verlernen = 0 ;
         if (db_max_erfolgswert==(*i)->Wert()) db_steigern=0;
         double fac=sprache->Standard_Faktor();
         datavec.push_back(new Data_sprache((*i)->Name(),(*i)->Wert(),
            db_steigern*fac,db_reduzieren*fac,db_verlernen * fac));
      }
   alte_sprache_tree->setDataVec(datavec);
}
*/
/*
void midgard_CG::show_neue_sprachen()
{
  std::vector<cH_RowDataBase> datavec;
  exec sql begin declare section;
   char db_name[50], db_urschrift[50];
   int db_fp;
   char db_cname[50],db_version[50];
  exec sql end declare section;
  strncpy(db_cname,(Werte.Name_Charakter()).c_str(),sizeof(db_cname));
  strncpy(db_version,(Werte.Version()).c_str(),sizeof(db_version));   
  Transaction tr; 
 exec sql declare ein cursor for
   SELECT DISTINCT name, fp, schrift from sprachen
   WHERE  name NOT IN (SELECT fertigkeit FROM charaktere_fertigkeiten
   WHERE art = 'Sprache' 
   AND charakter_name = :db_cname AND version = :db_version) order by name;
  SQLerror::test(__FILELINE__);
 exec sql open ein;
// double fac = midgard_CG::get_standard_fertigkeit(Typ[0]->Short(),Typ[1]->Short(),"Sprache");
 cH_Fertigkeit sprache("Sprache",Typ,Ausnahmen(Werte,Typ,vec_Beruf));
  while (true)
   {
      exec sql fetch ein into :db_name, :db_fp, :db_urschrift;
      SQLerror::test(__FILELINE__,100);  
      if (sqlca.sqlcode) break;
      datavec.push_back(new Data_sprache(db_name,db_urschrift,0,db_fp*sprache->Standard_Faktor()));
   }
 exec sql close ein;
 tr.close();
 neue_sprache_tree->setDataVec(datavec);
}
*/

/*
void midgard_CG::show_alte_schriften()
{
  std::vector<cH_RowDataBase> datavec;
  exec sql begin declare section;
   char db_typ[20], db_name[20];
   int db_kosten;
  exec sql end declare section;
//  double fac = midgard_CG::get_standard_fertigkeit(Typ[0]->Short(),Typ[1]->Short(),"Lesen/Schreiben");
  cH_Fertigkeit schrift("Lesen/Schreiben",Typ,Ausnahmen(Werte,Typ,vec_Beruf));
  for (std::vector<H_Data_schrift>::const_iterator i=vec_Schriften.begin();
      i!=vec_Schriften.end();++i)
   {
      strncpy(db_name,((*i)->Urschrift()).c_str(),sizeof(db_name));
      exec sql select typ, kosten into :db_typ, :db_kosten 
                           from schrift where name = :db_name;
      datavec.push_back(new Data_schrift((*i)->Urschrift(),db_typ,db_kosten*schrift->Standard_Faktor()));
   }
  alte_schrift_tree->setDataVec(datavec);
}

void midgard_CG::show_neue_schriften()
{
  std::vector<cH_RowDataBase> datavec;
  exec sql begin declare section;
   char db_name[50];
   int db_fp;
   char db_typ[30],db_cname[50],db_version[50];
  exec sql end declare section;
  strncpy(db_cname,(Werte.Name_Charakter()).c_str(),sizeof(db_cname));
  strncpy(db_version,(Werte.Version()).c_str(),sizeof(db_version));   
  Transaction tr; 
 exec sql declare ein2 cursor for
   SELECT DISTINCT name, kosten, typ from schrift   
   WHERE  name NOT IN (SELECT fertigkeit FROM charaktere_fertigkeiten
   WHERE art = 'Urschrift' 
   AND charakter_name = :db_cname AND version = :db_version) order by name, typ;
  SQLerror::test(__FILELINE__);
 exec sql open ein2;
// double fac = midgard_CG::get_standard_fertigkeit(Typ[0]->Short(),Typ[1]->Short(),"Lesen/Schreiben");
 cH_Fertigkeit schrift("Lesen/Schreiben",Typ,Ausnahmen(Werte,Typ,vec_Beruf));
 while (true)
   {
      exec sql fetch ein2 into :db_name, :db_fp, :db_typ;
      SQLerror::test(__FILELINE__,100);  
      if (sqlca.sqlcode) break;
//      os << db_fp*fac <<"\t"<<db_name<<"\t"<<db_typ <<"\n";
      datavec.push_back(new Data_schrift(db_name,db_typ,db_fp*schrift->Standard_Faktor()));
   }
 exec sql close ein2;
 tr.close();
 neue_schrift_tree->setDataVec(datavec);
}
*/