// $Id: table_lernschema_fertigkeiten.cc,v 1.36 2003/12/10 07:30:25 christof Exp $
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
#include <libmagus/Random.hh>
#include <libmagus/Ausgabe.hh>
#include <libmagus/Datenbank.hh>
#include "Wizard.hh"

void table_lernschema::on_button_angeborene_fertigkeit()
{
  hauptfenster->getChar().getWizard().done(Wizard::ANGEBORENEFERTIGKEITEN,hauptfenster->getAben());
  hauptfenster->getAben().setAngebFert();
  
  if (hauptfenster->getChar().proxies.werte_eingeben.Value()) on_angeborene_fertigkeit_right_clicked();
  else on_angeborene_fertigkeit_clicked() ;
  zeige_werte();
  show_gelerntes();

  button_lernpunkte->set_sensitive(true);
  togglebutton_lernpunkte_edit->set_sensitive(true);
  if(!hauptfenster->getAben().getOptionen().OptionenCheck(Optionen::NSC_only).active)
     button_angeborene_fert->set_sensitive(false);
}

void table_lernschema::on_angeborene_fertigkeit_clicked()
{
  int wurf = Random::integer(1,100);
//wurf = 100; /*debug*/
  int count100=0;
  while (wurf==100)
   {
     ++count100; 
     wurf = Random::integer(1,100);
   }
  if(count100>0) 
    { Ausgabe(Ausgabe::Log,itos(count100)+"x eine 100 gewürfelt, "+itos(count100)+" zusätzliche angeborende Fertigkeit nach Belieben wählen. Danach die 'Lernpunkte' auswürfeln.");
      on_angeborene_fertigkeit_right_clicked();      
    }
  Ausgabe(Ausgabe::Log,"Für die Angeborene Fertigkeit wurde eine "
              +itos(wurf)+" gewürfelt => "+AngebFert_gewuerfelt(wurf));
}


void table_lernschema::on_angeborene_fertigkeit_right_clicked()
{
  clean_lernschema_trees();
  tree_angeb_fert = manage(new MidgardBasicTree(MidgardBasicTree::ANGEBFERT));
  tree_angeb_fert->signal_leaf_selected().connect(SigC::slot(*static_cast<class table_lernschema*>(this), &table_lernschema::on_ang_fert_leaf_selected));
  std::list<cH_MidgardBasicElement> L=Datenbank.Fertigkeit_ang;
  list_Fertigkeit_ang_neu.clear();
  for(std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
    list_Fertigkeit_ang_neu.push_back(MBEmlt(*i));
  MidgardBasicTree::show_list_in_tree(list_Fertigkeit_ang_neu,tree_angeb_fert,&hauptfenster->getAben());

  scrolledwindow_lernen->show();
  tree_angeb_fert->show();
  scrolledwindow_lernen->add(*tree_angeb_fert);
}

void table_lernschema::on_ang_fert_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  MBEmlt MBE = dt->getMBE();
  cH_Fertigkeit_angeborene F(MBE->getMBE());

  hauptfenster->getAben().setAngebSinnFert(F->Min(),MBE);  
  list_Fertigkeit_ang_neu.remove(MBE);
  MidgardBasicTree::show_list_in_tree(list_Fertigkeit_ang_neu,tree_angeb_fert,&hauptfenster->getAben());
  show_gelerntes();
  zeige_werte();
}

std::string table_lernschema::AngebFert_gewuerfelt(int wurf)
{
  std::string name;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Fertigkeit_ang.begin();i!=Datenbank.Fertigkeit_ang.end();++i)
   {
     if (cH_Fertigkeit_angeborene(*i)->Min()<=wurf && wurf<=cH_Fertigkeit_angeborene(*i)->Max())
      {
         name=(*i)->Name();
         hauptfenster->getAben().setAngebSinnFert(wurf,MBEmlt(*i));  
         break;
      }
   }
 return name;
}

void table_lernschema::setFertigkeitenAusruestung()
{
  AusruestungBaum &koerper=hauptfenster->getAben().getBesitz();
  AusruestungBaum &rucksack=hauptfenster->getAben().getAusruestung_as_parent("Rucksack");
  for (std::list<MBEmlt>::const_iterator i=hauptfenster->getAben().List_Fertigkeit().begin();i!=hauptfenster->getAben().List_Fertigkeit().end();++i)
   {
     const std::vector<Fertigkeit::st_besitz> VB=cH_Fertigkeit((*i)->getMBE())->get_vec_Besitz();
     for(std::vector<Fertigkeit::st_besitz>::const_iterator j=VB.begin();j!=VB.end();++j)
      {
        int wurf=Random::integer(1,100);
        if(wurf>=j->min)
         {
           AusruestungBaum *A;
           if(j->position == Fertigkeit::Besitz)
            {
              A = &koerper.push_back(Ausruestung(j->name)); 
              A->setParent(&koerper);
            }
           else if(j->position == Fertigkeit::Rucksack)
            {
              A = &rucksack.push_back(Ausruestung(j->name));
              A->setParent(&rucksack); 
            }
         }
        InfoFensterAusruestung((*(*i))->Name(),j->name,wurf,j->min);
      }
   }
}

void table_lernschema::InfoFensterAusruestung(const std::string &fert_name,
               const std::string &gegen_name,int wurf,int noetig)
{
 std::string strinfo;
 strinfo="Für die Fertigkeit '"+fert_name+"' wurde für '"+gegen_name+
        "' eine "+itos(wurf)+" gewürfelt.\n";
 strinfo += "Nötig ist mindestens eine "+itos(noetig)+".\n";
 if(wurf>noetig) strinfo +="==> Das reicht.\n";
 else strinfo +="==> Das reicht NICHT.\n";
 Ausgabe(Ausgabe::Log,strinfo);
}
