// $Id: midgard_CG_fertigkeiten.cc,v 1.66 2002/04/30 08:25:04 thoma Exp $
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
//#include "Fertigkeiten_auswahl.hh"
#include <Gtk_OStream.h>
//#include "Window_angeb_fert.hh"
#include "Fertigkeiten.hh"
#include "Fertigkeiten_angeboren.hh"
#include <Aux/itos.h>
#include "class_SimpleTree.hh"

gint midgard_CG::on_angeborene_fertigkeit_button_release_event(GdkEventButton *event)
{
  if(wizard) wizard->next_step(Wizard::ANGEBORENEFERTIGKEITEN);
  list_Fertigkeit_ang.clear();
  list_Fertigkeit_ang=Werte.Spezies()->getAngFertigkeiten();
  list_Zauber=Werte.Spezies()->getZauber();
  Werte.resetSinne();
  checkAngeboreneSinne();
  
  if (event->button==1) on_angeborene_fertigkeit_clicked() ;
  if (event->button==3) on_angeborene_fertigkeit_right_clicked() ;
  zeige_werte();
  show_gelerntes();

  button_lernpunkte->set_sensitive(true);
  togglebutton_lernpunkte_edit->set_sensitive(true);
  button_angeborene_fert->set_sensitive(false);

  return false;
}

void midgard_CG::on_angeborene_fertigkeit_clicked()
{
  int wurf = random.integer(1,100);
//wurf = 100; /*debug*/
  int count100=0;
  while (wurf==100)
   {
     ++count100; 
     wurf = random.integer(1,100);
   }
  if(count100>0) 
    { set_info(itos(count100)+"x eine 100 gewürfelt, "+itos(count100)+" zusätzliche angeborende Fertigkeit nach Belieben wählen.");
      on_angeborene_fertigkeit_right_clicked();      
    }
  set_status("Für die Angeborene Fertigkeit wurde eine "
              +itos(wurf)+" gewürfelt => "+AngebFert_gewuerfelt(wurf));
}


void midgard_CG::on_angeborene_fertigkeit_right_clicked()
{
  clean_lernschema_trees();
  tree_angeb_fert = manage(new MidgardBasicTree(MidgardBasicTree::ANGEBFERT));
  tree_angeb_fert->leaf_selected.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_ang_fert_leaf_selected));
  list_Fertigkeit_ang_neu=Database.Fertigkeit_ang;
  MidgardBasicElement::show_list_in_tree(list_Fertigkeit_ang_neu,tree_angeb_fert,this);

//  scrolledwindow_beruf->hide();
  scrolledwindow_lernen->show();
//  scrolledwindow_ange_fert->show();
  tree_angeb_fert->show();
  viewport_lernen->add(*tree_angeb_fert);
}

void midgard_CG::on_ang_fert_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  cH_Fertigkeit_angeborene F(MBE);
  if(!AngebSinn(F->Min(),MBE->Erfolgswert()))
    MidgardBasicElement::move_element(list_Fertigkeit_ang_neu,list_Fertigkeit_ang,MBE);
  else list_Fertigkeit_ang_neu.remove(MBE);
  MidgardBasicElement::show_list_in_tree(list_Fertigkeit_ang_neu,tree_angeb_fert,this);
  show_gelerntes();
  zeige_werte();
}

std::string midgard_CG::AngebFert_gewuerfelt(int wurf)
{
  std::string name;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit_ang.begin();i!=Database.Fertigkeit_ang.end();++i)
   {
     if (cH_Fertigkeit_angeborene(*i)->Min()<=wurf && wurf<=cH_Fertigkeit_angeborene(*i)->Max())
      {
         name=(*i)->Name();
         if(!AngebSinn(wurf,(*i)->Erfolgswert()))
            list_Fertigkeit_ang.push_back(*i);
         break;
      }
   }
 return name;
}

bool midgard_CG::AngebSinn(int wurf,int wert)
{
  if     ( 1<=wurf && wurf<= 2) Werte.setSinnCheck("Sehen",wert);    
  else if( 3<=wurf && wurf<= 4) Werte.setSinnCheck("Hören",wert);    
  else if( 5<=wurf && wurf<= 6) Werte.setSinnCheck("Riechen",wert);  
  else if( 7<=wurf && wurf<= 8) Werte.setSinnCheck("Schmecken",wert);
  else if( 9<=wurf && wurf<=10) Werte.setSinnCheck("Tasten",wert);
  else if(11<=wurf && wurf<=20) Werte.setSinn("Sehen",wert);    
  else if(21<=wurf && wurf<=30) Werte.setSinn("Hören",wert);    
  else if(31<=wurf && wurf<=40) Werte.setSinn("Riechen",wert);  
  else if(41<=wurf && wurf<=50) Werte.setSinn("Schmecken",wert);
  else if(51<=wurf && wurf<=60) Werte.setSinn("Tasten",wert);
  else if(61<=wurf && wurf<=65) Werte.setSinn("Sechster Sinn",wert);
  else return false;
/*
cout << "Sehen = "<<Werte.Sinne()["Sehen"]<<'\n';
cout << "Hören = "<<Werte.Sinne()["Hören"]<<'\n';
cout << "Riechen = "<<Werte.Sinne()["Riechen"]<<'\n';
cout << "Schmecken = "<<Werte.Sinne()["Schmecken"]<<'\n';
cout << "Tasten = "<<Werte.Sinne()["Tasten"]<<'\n';
cout << "Sechster Sinn = "<<Werte.Sinne()["Sechster Sinn"]<<'\n';
*/
  return true;
}





void midgard_CG::universal_Fertigkeiten()
{
  list_Fertigkeit_universal.clear();
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
//     if((*i)->ist_gelernt(list_Fertigkeit)) continue ;
     if(cH_Fertigkeit(*i)->Voraussetzungen(Werte) && cH_Fertigkeit(*i)->Ungelernt()!=-1)
       list_Fertigkeit_universal.push_back(*i);
   }
}

void midgard_CG::checkAngeboreneSinne()
{
  std::list<pair<std::string,int> > L=Werte.Spezies()->getSinne();
  for(std::list<pair<std::string,int> >::const_iterator i=L.begin();i!=L.end();++i)
     Werte.setSinn(i->first,i->second);
}
