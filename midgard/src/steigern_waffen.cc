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
#include "WaffeGrund.hh"
#include "class_SimpleTree.hh"
#include "Pflicht.hh"


void midgard_CG::on_waffen_laden_clicked()
{
 list_Waffen_neu.clear();
 for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Waffe.begin();i!=Database.Waffe.end();++i)
   { cH_Waffe w(*i);
     if (w->ist_gelernt(list_Waffen)) continue ;
     if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,w->Name())) continue;
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
  on_waffengrund_laden_clicked();
  waffen_zeigen();
}


void midgard_CG::waffen_zeigen()
{
   zeige_werte(Werte);
   on_speichern_clicked();
   MidgardBasicElement::show_list_in_tree(list_WaffenGrund_neu,neue_grund_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_WaffenGrund    ,alte_grund_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Waffen_neu,neue_waffen_tree,Werte,Typ,Database.ausnahmen);
   MidgardBasicElement::show_list_in_tree(list_Waffen    ,alte_waffen_tree,Werte,Typ,Database.ausnahmen);
}



void midgard_CG::on_leaf_selected_neue_grund(cH_RowDataBase d)
{  
//  const Data_grund *dt=dynamic_cast<const Data_grund*>(&*d);
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if (!steigern_usp(MBE->Kosten(Typ,Database.ausnahmen),&MBE)) return;
  Werte.add_GFP(MBE->Kosten(Typ,Database.ausnahmen));
  MidgardBasicElement::move_element(list_WaffenGrund_neu,list_WaffenGrund,MBE->Name());
  on_waffen_laden_clicked();
}


void midgard_CG::on_waffengrund_laden_clicked()
{
  list_WaffenGrund_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.WaffeGrund.begin();i!=Database.WaffeGrund.end();++i)
   { cH_WaffeGrund w(*i);
     if ((*i)->ist_gelernt(list_WaffenGrund)) continue ;
     if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,w->Name())) continue;
     if((*i)->ist_lernbar(Typ,(*i)->get_MapTyp()))
        if (region_check(w->Region()) )
         list_WaffenGrund_neu.push_back(*i);
   }
}

void midgard_CG::on_leaf_selected_neue_waffen(cH_RowDataBase d)
{  
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  MidgardBasicElement::move_element(list_Waffen_neu,list_Waffen,dt->getMBE()->Name());
  waffen_zeigen();
}
 
void midgard_CG::on_leaf_selected_alte_grund(cH_RowDataBase d)
{  
  std::string strinfo="WARNUNG: Beim verlernen von Grundkenntnissen werden weder die\n";
  strinfo +="GFP angepaßt, noch die bereits gelernten Waffen, die zu dieser\n";
  strinfo +="Grundkenntnis gehöhren, verlernt\n";
  WindowInfo(strinfo,true);
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();
 if (radiobutton_verlernen->get_active())
   {
//     radiobutton_grundkenntnisse_verlernen->set_active(false);
     MidgardBasicElement::move_element(list_WaffenGrund,list_WaffenGrund_neu,MBE->Name());
     waffen_zeigen();
   }
}

void midgard_CG::on_leaf_selected_alte_waffen(cH_RowDataBase d)
{  
   const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
   cH_MidgardBasicElement MBE = dt->getMBE();
   if (radiobutton_steigern->get_active())
      {
       if (!steigern_usp(MBE->Steigern(Typ,Database.ausnahmen),&MBE)) return;
//       if (!togglebutton_praxispunkte_waffen->get_active()) // normal Lernen
//        {
          if (MBE->Erfolgswert() >=  cH_Waffe(MBE)->Maxwert(Typ)) 
            {  
               std::string strinfo = "Maximal möglicher Erfolgswert erreicht\n";
               manage (new WindowInfo(strinfo));
               return ;
            }          
          Werte.add_GFP(MBE->Steigern(Typ,Database.ausnahmen));
          if (MBE->Steigern(Typ,Database.ausnahmen) != 0)
          for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
               if (cH_Waffe(*i)->Name()==MBE->Name()) 
                  { cH_Waffe(*i)->add_Erfolgswert(1); break;}
/*
        }
       else // steigern mit Praxispunkten
        {
          bool wuerfeln;
          if (radiobutton_praxis_auto_waffen->get_active())     wuerfeln = false;
          if (radiobutton_praxis_wuerfeln_waffen->get_active()) wuerfeln = true;

          std::string art="Waffe";
//          int gelungen = praxispunkte_wuerfeln(MBE->Name(),MBE->Erfolgswert(),art,wuerfeln);
          bool gelungen = Database.praxispunkte.wuerfeln(MBE,Werte,Typ,wuerfeln);
          if (gelungen)
            {
              Werte.add_GFP(MBE->Steigern(Typ,Database.ausnahmen));
              if (MBE->Steigern(Typ,Database.ausnahmen) != 0)
              for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
                  if ((*i)->Name()==MBE->Name()) (*i)->add_Erfolgswert(1);
            }
        }
*/
      }
   if (radiobutton_reduzieren->get_active())
      {
        if (steigern_bool) desteigern(MBE->Reduzieren(Typ,Database.ausnahmen));
        Werte.add_GFP(-MBE->Reduzieren(Typ,Database.ausnahmen));
        if (MBE->Reduzieren(Typ,Database.ausnahmen) != 0)
        for (std::list<cH_MidgardBasicElement>::iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
              if (cH_Waffe(*i)->Name()==MBE->Name()) (*i)->add_Erfolgswert(-1);  
      }
   if (radiobutton_verlernen->get_active())
      {
         manage(new WindowInfo("Nicht implementiert"));
      }
   waffen_zeigen();
}

/*
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
*/

void midgard_CG::on_button_waffen_sort_clicked()
{
  std::deque<guint> seq = alte_waffen_tree->get_seq();
  switch((Data_SimpleTree::Spalten_WA)seq[0]) {
      case Data_SimpleTree::WERTa_W : list_Waffen.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::ERFOLGSWERT)); ;break;
      case Data_SimpleTree::NAMEa_W : list_Waffen.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}
