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
#include "zufall.h"
#include "WaffeGrund.hh"
#include "class_waffen.hh"
#include "Pflicht.hh"


void midgard_CG::on_waffen_laden_clicked()
{
 list_Waffen_neu.clear();
// cH_Pflicht pflicht(Werte.Spezies(),Typ);
 for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Waffe.begin();i!=Database.Waffe.end();++i)
   { cH_Waffe w(*i);
     if (w->ist_gelernt(list_Waffen)) continue ;
     if (Database.pflicht.istVerboten(Werte.Spezies(),Typ,w->Name())) continue;
     if (w->Grundkenntnis_vorhanden(list_WaffenGrund))
       if (w->ist_lernbar(Typ,w->get_MapTyp()))
         if (region_check(w->Region(w->Name())) )
           if (w->SG_Voraussetzung(Werte))
             {
              if(w->Art()=="Verteidigung") w->set_Erfolgswert(1);
              else w->set_Erfolgswert(4);
              list_Waffen_neu.push_back(*i);
             }
   }

/*
   exec sql begin declare section;
      char db_waffe[50];
      char query[1024];
   exec sql end declare section;
   std::string squery = "SELECT w.name FROM  waffen w, \
   charaktere_fertigkeiten c WHERE  w.grundkenntnisse = c.fertigkeit \
   AND c.charakter_name = '"+Werte.Name_Charakter()+"' AND w.name NOT IN \
   (SELECT fertigkeit FROM charaktere_fertigkeiten WHERE art = 'Waffe' \
   AND charakter_name = '"+Werte.Name_Charakter()+
   "' AND version = '"+Werte.Version()+"') \
   AND w.name  not in (select verboten from pflicht_lernen where typ='"+
   Werte.Spezies()+"' and verboten is not null) AND  grundkenntnisse not in \
    (select verboten from pflicht_lernen where typ='"+Werte.Spezies()+
   "' and verboten is not null)";
   strncpy(query,squery.c_str(),sizeof(query));
   Transaction tr;
   exec sql prepare wa_ein_ from :query;
   exec sql declare wa_ein cursor for wa_ein_;
   exec sql open wa_ein;
   SQLerror::test(__FILELINE__);
   while(true)
      {
         exec sql fetch wa_ein into :db_waffe;
         SQLerror::test(__FILELINE__,100);
         if (sqlca.sqlcode) break;
         cH_Waffe waffe(db_waffe,Typ);
         if (waffe->Art()=="Verteidigung") waffe->set_Erfolgswert(1);
         else waffe->set_Erfolgswert(4);
         if  (waffe->SG_Voraussetzung(Werte)&&region_check(waffe->Region(waffe->Name())))
           list_Waffen_neu.push_back(waffe);
      }
   exec sql close wa_ein;
   tr.close();
*/
  on_waffengrund_laden_clicked();
  waffen_zeigen();
}


void midgard_CG::waffen_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
//   Ausnahmen ausnahmen(Werte,Typ,vec_Beruf);
   MidgardBasicElement::show_list_in_tree(list_WaffenGrund_neu,neue_grund_tree,Werte,Typ,Database.ausnahmen,'N');
   MidgardBasicElement::show_list_in_tree(list_WaffenGrund    ,alte_grund_tree,Werte,Typ,Database.ausnahmen,'O');
   MidgardBasicElement::show_list_in_tree(list_Waffen_neu,neue_waffen_tree,Werte,Typ,Database.ausnahmen,'N');
   MidgardBasicElement::show_list_in_tree(list_Waffen    ,alte_waffen_tree,Werte,Typ,Database.ausnahmen,'O');
}



void midgard_CG::on_leaf_selected_neue_grund(cH_RowDataBase d)
{  
  const Data_grund *dt=dynamic_cast<const Data_grund*>(&*d);
  if (!steigern(dt->Kosten(),"Waffen")) return;
  Werte.add_GFP(dt->Kosten());
  MidgardBasicElement::move_element(list_WaffenGrund_neu,list_WaffenGrund,dt->Name());
//  waffen_zeigen();
  on_waffen_laden_clicked();
}


void midgard_CG::on_waffengrund_laden_clicked()
{
  list_WaffenGrund_neu.clear();
  cH_Pflicht pflicht(Werte.Spezies(),Typ);
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.WaffeGrund.begin();i!=Database.WaffeGrund.end();++i)
   { cH_WaffeGrund w(*i);
     if ((*i)->ist_gelernt(list_WaffenGrund)) continue ;
     if (pflicht->istVerboten(w->Name())) continue;
     if (region_check(w->Region()) )
      list_WaffenGrund_neu.push_back(*i);
   }
}

void midgard_CG::on_leaf_selected_neue_waffen(cH_RowDataBase d)
{  const Data_waffen *dt=dynamic_cast<const Data_waffen*>(&*d);
  MidgardBasicElement::move_element(list_Waffen_neu,list_Waffen,dt->Name());
  waffen_zeigen();
}
 
void midgard_CG::on_leaf_selected_alte_grund(cH_RowDataBase d)
{  
  std::string strinfo="WARNUNG: Beim verlernen von Grundkenntnissen werden weder die\n";
  strinfo +="GFP angepaßt, noch die bereits gelernten Waffen, die zu dieser\n";
  strinfo +="Grundkenntnis gehöhren, verlernt\n";
  WindowInfo(strinfo,true);
 const Data_grund *dt=dynamic_cast<const Data_grund*>(&*d);
 if (radiobutton_grundkenntnisse_verlernen->get_active())
   {
     radiobutton_grundkenntnisse_verlernen->set_active(false);
     MidgardBasicElement::move_element(list_WaffenGrund,list_WaffenGrund_neu,dt->Name());
     waffen_zeigen();
   }
}

void midgard_CG::on_leaf_selected_alte_waffen(cH_RowDataBase d)
{  
   const Data_waffen *dt=dynamic_cast<const Data_waffen*>(&*d);
   if (radio_waffen_steigern->get_active())
      {
       if (!steigern(dt->Steigern(),"Waffen")) return;
       if (!togglebutton_praxispunkte_waffen->get_active()) // normal Lernen
        {
          if (dt->Erfolgswert() >=  cH_Waffe(dt->Name())->Maxwert(Typ)) 
            {  
               std::string strinfo = "Maximal möglicher Erfolgswert erreicht\n";
               manage (new WindowInfo(strinfo));
               return ;
            }          
          Werte.add_GFP(dt->Steigern());
          if (dt->Steigern() != 0)
          for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
               if (cH_Waffe(*i)->Name()==dt->Name()) 
                  { cH_Waffe(*i)->add_Erfolgswert(1); break;}
        }
       else // steigern mit Praxispunkten
        {
          bool wuerfeln;
          if (radiobutton_praxis_auto_waffen->get_active())     wuerfeln = false;
          if (radiobutton_praxis_wuerfeln_waffen->get_active()) wuerfeln = true;

          std::string art="Waffe";
          int gelungen = praxispunkte_wuerfeln(dt->Name(),dt->Erfolgswert(),art,wuerfeln);
          if (gelungen)
            {
              Werte.add_GFP(dt->Steigern());
              if (dt->Steigern() != 0)
              for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
                  if (cH_Waffe(*i)->Name()==dt->Name()) cH_Waffe(*i)->add_Erfolgswert(1);
            }
        }
      }
   if (radio_waffen_reduzieren->get_active())
      {
        if (steigern_bool) desteigern(dt->Reduzieren());
        Werte.add_GFP(-dt->Reduzieren());
        if (dt->Reduzieren() != 0)
        for (std::list<cH_MidgardBasicElement>::iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
              if (cH_Waffe(*i)->Name()==dt->Name()) cH_Waffe(*i)->add_Erfolgswert(-1);  
      }
   waffen_zeigen();
}

void midgard_CG::on_radio_waffen_steigern_toggled()
{   
}

void midgard_CG::on_radio_waffen_reduzieren_toggled()
{   
   if (radio_waffen_reduzieren->get_active())
      togglebutton_praxispunkte_waffen->set_active(false);
}

void midgard_CG::on_togglebutton_praxispunkte_waffen_toggled()
{   
   if (togglebutton_praxispunkte_waffen->get_active()) 
      radio_waffen_steigern->set_active(true);
}

void midgard_CG::on_radiobutton_praxis_wuerfeln_waffen_toggled()
{   
}

void midgard_CG::on_radiobutton_praxis_auto_waffen_toggled()
{   
}

void midgard_CG::on_button_waffen_sort_clicked()
{
  std::deque<guint> seq = alte_waffen_tree->get_seq();
  switch((Data_waffen::Spalten_A)seq[0]) {
      case Data_waffen::WERTa : list_Waffen.sort(cH_Waffe::sort(cH_Waffe::sort::ERFOLGSWERT)); ;break;
      case Data_waffen::NAMEa : list_Waffen.sort(cH_Waffe::sort(cH_Waffe::sort::NAME)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}
