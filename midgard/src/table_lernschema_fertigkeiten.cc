// $Id: table_lernschema_fertigkeiten.cc,v 1.6 2002/06/20 19:06:18 thoma Exp $
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
//#include "Fertigkeiten_auswahl.hh"
#include <Gtk_OStream.h>
//#include "Window_angeb_fert.hh"
#include "Fertigkeiten.hh"
#include "Fertigkeiten_angeboren.hh"
#include <Aux/itos.h>
#include "class_SimpleTree.hh"
#include "midgard_CG.hh"

gint table_lernschema::on_angeborene_fertigkeit_button_release_event(GdkEventButton *event)
{
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::ANGEBORENEFERTIGKEITEN);
  hauptfenster->getChar().List_Fertigkeit_ang().clear();
  hauptfenster->getChar().List_Fertigkeit_ang()=hauptfenster->getCWerte().Spezies()->getAngFertigkeiten();
  hauptfenster->getChar().List_Zauber()=hauptfenster->getWerte().Spezies()->getZauber();
  hauptfenster->getWerte().resetSinne();
  checkAngeboreneSinne();
  
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
    { hauptfenster->set_info(itos(count100)+"x eine 100 gewürfelt, "+itos(count100)+" zusätzliche angeborende Fertigkeit nach Belieben wählen. Danach die 'Lernpunkte' auswürfeln.");
      on_angeborene_fertigkeit_right_clicked();      
    }
  hauptfenster->set_status("Für die Angeborene Fertigkeit wurde eine "
              +itos(wurf)+" gewürfelt => "+AngebFert_gewuerfelt(wurf));
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

//  scrolledwindow_beruf->hide();
  scrolledwindow_lernen->show();
//  scrolledwindow_ange_fert->show();
  tree_angeb_fert->show();
  viewport_lernen->add(*tree_angeb_fert);
}

void table_lernschema::on_ang_fert_leaf_selected(cH_RowDataBase d)
{
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  MidgardBasicElement_mutable MBE = dt->getMBE();
  cH_Fertigkeit_angeborene F(MBE);
  if(!AngebSinn(F->Min(),MBE.Erfolgswert()))
    MidgardBasicElement::move_element(list_Fertigkeit_ang_neu,hauptfenster->getChar().List_Fertigkeit_ang(),MBE);
  else list_Fertigkeit_ang_neu.remove(MBE);
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
         if(!AngebSinn(wurf,MidgardBasicElement_mutable(*i).Erfolgswert()))
            hauptfenster->getChar().List_Fertigkeit_ang().push_back(*i);
         break;
      }
   }
 return name;
}

bool table_lernschema::AngebSinn(int wurf,int wert)
{
  if     ( 1<=wurf && wurf<= 2) hauptfenster->getWerte().setSinnCheck("Sehen",wert);    
  else if( 3<=wurf && wurf<= 4) hauptfenster->getWerte().setSinnCheck("Hören",wert);    
  else if( 5<=wurf && wurf<= 6) hauptfenster->getWerte().setSinnCheck("Riechen",wert);  
  else if( 7<=wurf && wurf<= 8) hauptfenster->getWerte().setSinnCheck("Schmecken",wert);
  else if( 9<=wurf && wurf<=10) hauptfenster->getWerte().setSinnCheck("Tasten",wert);
  else if(11<=wurf && wurf<=20) hauptfenster->getWerte().setSinn("Sehen",wert);    
  else if(21<=wurf && wurf<=30) hauptfenster->getWerte().setSinn("Hören",wert);    
  else if(31<=wurf && wurf<=40) hauptfenster->getWerte().setSinn("Riechen",wert);  
  else if(41<=wurf && wurf<=50) hauptfenster->getWerte().setSinn("Schmecken",wert);
  else if(51<=wurf && wurf<=60) hauptfenster->getWerte().setSinn("Tasten",wert);
  else if(61<=wurf && wurf<=65) hauptfenster->getWerte().setSinn("Sechster Sinn",wert);
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


void table_lernschema::checkAngeboreneSinne()
{
  std::list<pair<std::string,int> > L=hauptfenster->getCWerte().Spezies()->getSinne();
  for(std::list<pair<std::string,int> >::const_iterator i=L.begin();i!=L.end();++i)
     hauptfenster->getWerte().setSinn(i->first,i->second);
}
