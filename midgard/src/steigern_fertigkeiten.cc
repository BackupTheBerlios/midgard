/*  Copyright (C) 2001 Malte Thoma
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
#include "Ausnahmen.hh"
#include "class_fertigkeiten.hh"
#include "Pflicht.hh"

void midgard_CG::on_fertigkeiten_laden_clicked()
{
  list_Fertigkeit_neu.clear();
  Fertigkeiten_All FA(laden_label);
  std::list<cH_MidgardBasicElement> list_tmp = FA.get_All();
  cH_Pflicht pflicht(Werte.Spezies(),Typ);
  for (std::list<cH_MidgardBasicElement>::const_iterator i=list_tmp.begin();i!=list_tmp.end();++i)
   { cH_Fertigkeit f(*i);
     if ((*i)->ist_gelernt(list_Fertigkeit)) continue ;
     if (f->Name()=="Sprache" || f->Name()=="Lesen/Schreiben") continue;
     if (pflicht->istVerboten(f->Name())) continue;
     if ((*i)->ist_lernbar(Typ,f->get_MapTyp()))
       if (region_check(f->Region()) )
        if (f->Voraussetzungen(Werte)) continue;
            list_Fertigkeit_neu.push_back(*i);
   }
 fertigkeiten_zeigen();
}

void midgard_CG::fertigkeiten_zeigen()
{
 zeige_werte(Werte);
 on_speichern_clicked();
 Ausnahmen ausnahmen(Werte,Typ,vec_Beruf);
 MidgardBasicElement::show_list_in_tree(list_Fertigkeit_neu,neue_fert_tree,Werte,Typ,ausnahmen,'N');
 MidgardBasicElement::show_list_in_tree(list_Fertigkeit    ,alte_fert_tree,Werte,Typ,ausnahmen,'O');
// show_alte_fertigkeiten();
// show_neue_fertigkeiten();
}


void midgard_CG::on_leaf_selected_alte_fert(cH_RowDataBase d)
{  
 const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);

 if (dt->Name()=="KiDo" && kido_steigern_check(dt->Erfolgswert())) return;
 if (radio_fert_steigern->get_active() && dt->Steigern())
    {
      // Steigern mit lernen
      if (!togglebutton_praxispunkte_fertigkeiten->get_active()) 
         {
            if (!steigern(dt->Steigern(),dt->Name())) return;
            Werte.add_GFP(dt->Steigern());
            for (std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!= list_Fertigkeit.end();++i )
               if ( cH_Fertigkeit(*i)->Name() == dt->Name()) cH_Fertigkeit(*i)->add_Erfolgswert(1); 
         }
      else  // Lernen mit Praxispunkten 
         {
            bool wuerfeln;
            if (radiobutton_praxis_wuerfeln_fertigkeiten->get_active()) wuerfeln = true;
            if (radiobutton_praxis_auto_fertigkeiten->get_active()) wuerfeln = false;
            int gelungen = praxispunkte_wuerfeln(dt->Name(),dt->Erfolgswert(),"Fertigkeit",wuerfeln);
            if (gelungen)
               {
                  Werte.add_GFP(dt->Steigern()/2);
                  for (std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!= list_Fertigkeit.end();++i )
                     if ( cH_Fertigkeit(*i)->Name() == dt->Name()) cH_Fertigkeit(*i)->add_Erfolgswert(1); 
               }
         }     
    }
   if (radio_fert_reduzieren->get_active() && dt->Reduzieren())
         {
            if (steigern_bool) desteigern(dt->Reduzieren());
            Werte.add_GFP(-dt->Reduzieren());
            for (std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!= list_Fertigkeit.end();++i )
               if ( cH_Fertigkeit(*i)->Name() == dt->Name()) cH_Fertigkeit(*i)->add_Erfolgswert(-1); 
         }
   if (radio_fert_verlernen->get_active() && dt->Verlernen())
         {
            if (steigern_bool) desteigern(dt->Verlernen());
            Werte.add_GFP(-dt->Verlernen());
            MidgardBasicElement::move_element(list_Fertigkeit,list_Fertigkeit_neu,dt->Name());
         }
   fertigkeiten_zeigen();
}

/*
void midgard_CG::get_srv_kosten(const cH_Fertigkeit& fertigkeit, int &steigern,int &reduzieren,int &verlernen) const
{
  exec sql begin declare section;
    int db_steigern=0, db_reduzieren=0, db_verlernen;
    char query[1024];
    char db_standard[5],db_standard2[5];
  exec sql end declare section;
  std::string squery;

  if (fertigkeit->Erfolgswert() != 0) // Fertigkeiten MIT Erfolgswert
     {
       squery = "SELECT coalesce(p"+itos(abs(fertigkeit->Erfolgswert()))
          +",0),coalesce(p"+itos(abs(fertigkeit->Erfolgswert()+1))+",0),fp,f."+Typ[0]->Short();
       if (Typ[1]->Short()!="") squery += ", "+Typ[1]->Short();
       squery +=" FROM steigern_fertigkeiten s, steigern_fertigkeiten_werte w, \
          fertigkeiten f WHERE s.name = '"+fertigkeit->Name()+"' AND w.name = s.wie \
             AND f.fertigkeit = '"+fertigkeit->Name()+"'";
     }
  else // Fertigkeiten OHNE Erfolgswert
     {
       squery = "SELECT fp,f."+Typ[0]->Short();
       if (Typ[1]->Short()!="") squery += ", "+Typ[1]->Short();
       squery  +=" FROM steigern_fertigkeiten s, fertigkeiten f \
          WHERE s.name = '"+fertigkeit->Name()+"' \
            AND f.fertigkeit = '"+fertigkeit->Name()+"'";
     }
  strncpy(query,squery.c_str(),sizeof(query));

  Transaction tr;
  exec sql prepare kosten_ein_ from :query ;  
  exec sql declare kosten_ein cursor for kosten_ein_ ;  
  exec sql open kosten_ein;
  if(Typ[1]->Short()!="")      
    {
      if (fertigkeit->Erfolgswert() != 0) // Fertigkeiten MIT Erfolgswert
         exec sql fetch kosten_ein into :db_reduzieren, 
             :db_steigern, :db_verlernen, :db_standard,:db_standard2;
      else // Fertigkeiten OHNE Erfolgswert
          exec sql fetch kosten_ein into :db_verlernen, :db_standard,:db_standard2;
    }
  else
    {
      if (fertigkeit->Erfolgswert() != 0) // Fertigkeiten MIT Erfolgswert
         exec sql fetch kosten_ein into :db_reduzieren, 
            :db_steigern, :db_verlernen, :db_standard;
      else // Fertigkeiten OHNE Erfolgswert
          exec sql fetch kosten_ein into :db_verlernen, :db_standard;
    }
  SQLerror::test(__FILELINE__);
  exec sql close kosten_ein;
  tr.close();

//  double fac = midgard_CG::get_standard_fertigkeit_(db_standard,db_standard2,name);
  double fac = fertigkeit->Standard_Faktor();
  steigern = (int)(db_steigern * fac);
  reduzieren=(int)(db_reduzieren * fac);
  if (db_reduzieren !=0) verlernen = 0 ;
  else  verlernen=(int)(db_verlernen *fac);
}
*/

void midgard_CG::on_button_fertigkeiten_sort_clicked()
{
  std::deque<guint> seq = alte_fert_tree->get_seq();
  switch((Data_fert::Spalten_A)seq[0]) {
      case Data_fert::NAMEa : list_Fertigkeit.sort(cH_Fertigkeit::sort(cH_Fertigkeit::sort::NAME)); ;break;
      case Data_fert::WERTa : list_Fertigkeit.sort(cH_Fertigkeit::sort(cH_Fertigkeit::sort::ERFOLGSWERT)); ;break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}


/*
void midgard_CG::show_neue_fertigkeiten()
{
 std::vector<cH_RowDataBase> datavec;
 for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit_neu.begin();i!=list_Fertigkeit_neu.end();++i)
  { cH_Fertigkeit f(*i);
// wieso dies??????? TESTEN!!!!!!!!!
   f->set_Erfolgswert(f->Anfangswert());   
   datavec.push_back(new Data_fert(f->Name(),f->Anfangswert(),
               f->Kosten(),f->Standard__(),f->Voraussetzung()));
  }
 neue_fert_tree->setDataVec(datavec);
}
*/
bool midgard_CG::kido_steigern_check(int wert)
{
  if (Werte.Grad()+10 > wert) return false;
  else
   { std::string strinfo ="KiDo darf nur auf maximal Grad+10 gesteigert werden.\n";
     manage (new WindowInfo(strinfo));
     return true;
   }
}


void midgard_CG::on_leaf_selected_neue_fert(cH_RowDataBase d)
{  const Data_fert *dt=dynamic_cast<const Data_fert*>(&*d);
  if (!steigern(dt->Lernkosten(),dt->Name())) return;
  Werte.add_GFP(dt->Lernkosten());
  MidgardBasicElement::move_element(list_Fertigkeit_neu,list_Fertigkeit,dt->Name());
  fertigkeiten_zeigen();

  if (dt->Name()=="KiDo") {kido_bool=true;show_gtk();
      std::string strinfo="Jetzt muß ein Stil unter 'Lernschema' -> 'KiDo' gewählt werden !!!";
      manage (new WindowInfo(strinfo,true)); }
  if (dt->Name()=="Wissen von der Magie") 
      {  doppelcharaktere();
         std::string strinfo ="Jetzt unter 'Grundwerte' die zweite Charkakterklasse wählen\n";
         strinfo += " und anschließend 'Fertigkeiten neu laden' klicken\n";
         manage (new WindowInfo(strinfo,true));
         // Resistenzboni für Zauberer setzten:
         Werte.set_magBoni(Werte.bo_Psy()+3,Werte.bo_Phs()+1,Werte.bo_Phk()+3);
         if (Werte.Zaubern_wert()==0) Werte.set_Zaubern_wert(10);
      }
}

void midgard_CG::on_radio_fert_steigern_toggled()
{
}



void midgard_CG::on_radio_fert_reduzieren_toggled()
{
   if (radio_fert_reduzieren->get_active())
      togglebutton_praxispunkte_fertigkeiten->set_active(false);
}

void midgard_CG::on_radio_fert_verlernen_toggled()
{
   if (radio_fert_verlernen->get_active())
      togglebutton_praxispunkte_fertigkeiten->set_active(false);
}

void midgard_CG::on_togglebutton_praxispunkte_fertigkeiten_toggled()
{
    if (togglebutton_praxispunkte_fertigkeiten->get_active())
      radio_fert_steigern->set_active(true);
}

void midgard_CG::on_radiobutton_praxis_wuerfeln_fertigkeiten_toggled()
{
}

void midgard_CG::on_radiobutton_praxis_auto_fertigkeiten_toggled()
{
}

/*
bool midgard_CG::Fertigkeiten_Voraussetzung(const std::string& fertigkeit)
{
  exec sql begin declare section;
   int db_st,db_ge,db_ko,db_in,db_zt,db_pa,db_au,db_sb,db_rw;
   char db_fertigkeit[30], db_fert[30];
  exec sql end declare section;
  strncpy(db_fertigkeit,fertigkeit.c_str(),sizeof(db_fertigkeit));

  exec sql select distinct coalesce(st,0), coalesce(ge,'0'),
   coalesce(ko,0),  coalesce("in",0), coalesce(zt,'0'),
   coalesce(au,0), coalesce(pa,'0'), 
   coalesce(sb,0), coalesce(rw,'0'), coalesce(fertigkeit,'')
   into :db_st,:db_ge,:db_ko,:db_in,:db_zt,:db_au,:db_pa,
         :db_sb,:db_rw,:db_fert
   from fertigkeiten_voraussetzung where name= :db_fertigkeit;
  SQLerror::test(__FILELINE__,100);
  if (sqlca.sqlcode) return true;
//  SQLerror::test(__FILELINE__);
    if ( db_st<=Werte.St() &&
         db_ge<=Werte.Ge() &&
         db_ko<=Werte.Ko() &&
         db_in<=Werte.In() &&
         db_zt<=Werte.Zt() &&
         db_au<=Werte.Au() &&
         db_pa<=Werte.pA() &&
         db_sb<=Werte.Sb() &&
         db_rw<=Werte.RW()
       )   
     return true;
  else return false ;
}
*/
