// $Id: table_lernschema_fertigkeiten.cc,v 1.12 2002/09/12 15:01:14 thoma Exp $
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

#include "table_lernschema.hh"
#include <Gtk_OStream.h>
#include "Fertigkeiten.hh"
#include "Fertigkeiten_angeboren.hh"
#include <Misc/itos.h>
#include "class_SimpleTree.hh"
#include "midgard_CG.hh"

gint table_lernschema::on_angeborene_fertigkeit_button_release_event(GdkEventButton *event)
{
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::ANGEBORENEFERTIGKEITEN);
  hauptfenster->getChar()->setAngebFert();
  
  if (event->button==1) on_angeborene_fertigkeit_clicked() ;
  if (event->button==3) on_angeborene_fertigkeit_right_clicked() ;
  zeige_werte();
  show_gelerntes();

  button_lernpunkte->set_sensitive(true);
  togglebutton_lernpunkte_edit->set_sensitive(true);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
     button_angeborene_fert->set_sensitive(false);
  return false;
}

void table_lernschema::on_angeborene_fertigkeit_clicked()
{
  int wurf = hauptfenster->random.integer(1,100);
//wurf = 100; /*debug*/
  int count100=0;
  while (wurf==100)
   {
     ++count100; 
     wurf = hauptfenster->random.integer(1,100);
   }
  if(count100>0) 
    { hauptfenster->set_info(itos(count100)+"x eine 100 gew�rfelt, "+itos(count100)+" zus�tzliche angeborende Fertigkeit nach Belieben w�hlen. Danach die 'Lernpunkte' ausw�rfeln.");
      on_angeborene_fertigkeit_right_clicked();      
    }
  hauptfenster->set_status("F�r die Angeborene Fertigkeit wurde eine "
              +itos(wurf)+" gew�rfelt => "+AngebFert_gewuerfelt(wurf));
}


void table_lernschema::on_angeborene_fertigkeit_right_clicked()
{
  clean_lernschema_trees();
  tree_angeb_fert = manage(new MidgardBasicTree(MidgardBasicTree::ANGEBFERT));
  tree_angeb_fert->leaf_selected.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::on_ang_fert_leaf_selected));
  std::list<cH_MidgardBasicElement> L=hauptfenster->getDatabase().Fertigkeit_ang;
  list_Fertigkeit_ang_neu.clear();
  for(std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
    list_Fertigkeit_ang_neu.push_back(MidgardBasicElement_mutable(*i));
  MidgardBasicElement::show_list_in_tree(list_Fertigkeit_ang_neu,tree_angeb_fert,hauptfenster);

  scrolledwindow_lernen->show();
  tree_angeb_fert->show();
  viewport_lernen->add(*tree_angeb_fert);
}

void table_lernschema::on_ang_fert_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  MidgardBasicElement_mutable MBE = dt->getMBE();
  cH_Fertigkeit_angeborene F(MBE);
//  if(!LernListen::AngebSinnFert(hauptfenster->getChar(),F->Min(),MBE.Erfolgswert()))
//    MidgardBasicElement::move_element(list_Fertigkeit_ang_neu,hauptfenster->getChar().List_Fertigkeit_ang(),MBE);

  hauptfenster->getChar()->setAngebSinnFert(F->Min(),MBE);  
  list_Fertigkeit_ang_neu.remove(MBE);
  MidgardBasicElement::show_list_in_tree(list_Fertigkeit_ang_neu,tree_angeb_fert,hauptfenster);
  show_gelerntes();
  zeige_werte();
}

std::string table_lernschema::AngebFert_gewuerfelt(int wurf)
{
  std::string name;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=hauptfenster->getDatabase().Fertigkeit_ang.begin();i!=hauptfenster->getDatabase().Fertigkeit_ang.end();++i)
   {
     if (cH_Fertigkeit_angeborene(*i)->Min()<=wurf && wurf<=cH_Fertigkeit_angeborene(*i)->Max())
      {
         name=(*i)->Name();
         hauptfenster->getChar()->setAngebSinnFert(wurf,MidgardBasicElement_mutable(*i));  
         break;
      }
   }
 return name;
}

void table_lernschema::setFertigkeitenAusruestung(AusruestungBaum &Rucksack)
{
  AusruestungBaum &besitz=hauptfenster->getChar().getBesitz();
  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Fertigkeit().begin();i!=hauptfenster->getChar().List_Fertigkeit().end();++i)
   {
     const std::vector<Fertigkeit::st_besitz> VB=cH_Fertigkeit(*i)->get_vec_Besitz();
     for(std::vector<Fertigkeit::st_besitz>::const_iterator j=VB.begin();j!=VB.end();++j)
      {
        int wurf=hauptfenster->random.integer(1,100);
        if(wurf>=j->min)
         {
           AusruestungBaum *A;
           if(j->position == Fertigkeit::Besitz)
            {
              A = &besitz.push_back(Ausruestung(j->name)); 
              A->setParent(&besitz);
            }
           else if(j->position == Fertigkeit::Rucksack)
            {
              A = &Rucksack.push_back(Ausruestung(j->name));
              A->setParent(&Rucksack); 
            }
         }
        InfoFensterAusruestung((*i)->Name(),j->name,wurf,j->min);
      }
   }
}

void table_lernschema::InfoFensterAusruestung(const std::string &fert_name,
               const std::string &gegen_name,int wurf,int noetig)
{
 std::string strinfo;
 strinfo="F�r die Fertigkeit '"+fert_name+"' wurde f�r '"+gegen_name+
        "' eine "+itos(wurf)+" gew�rfelt.\n";
 strinfo += "N�tig ist mindestens eine "+itos(noetig+1)+".\n";
 if(wurf>noetig) strinfo +="==> Das reicht.\n";
 else strinfo +="==> Das reicht NICHT.\n";
 hauptfenster->InfoFenster->AppendShow(strinfo,WindowInfo::None);
}
