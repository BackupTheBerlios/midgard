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

// generated 2001/3/14 8:34:43 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Waffenbesitz.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_Waffenbesitz.hh"
#include "midgard_CG.hh"
//#include <Aux/Transaction.h>
//#include <Aux/SQLerror.h>
//#include <Gtk_OStream.h>
//exec sql include sqlca;
#include "Typen.hh"


void Window_Waffenbesitz::on_leaf_selected_alt(cH_RowDataBase d)
{  
  const Data_waffenbesitz *dt=dynamic_cast<const Data_waffenbesitz*>(&*d);
  selected_weapon=&(dt->get_Waffe()); //WARNING
  cH_WaffeBesitz WB(*selected_weapon);


  if(!checkbutton_mag_waffenbonus->get_active()) 
    MidgardBasicElement::move_element(Waffe_Besitz,Waffe_Besitz_neu,cH_WaffeBesitz(dt->get_Waffe())->Name());
//    move_waffe(Waffe_Besitz,Waffe_Besitz_neu,dt->get_Waffe()->Name());
  else 
   {
     table_magbonus->show();
     if (WB->Waffe()->Art()=="Verteidigung")
       { label_av_bonus->set_text("Abwehrbonus");
         label_SL_bonus->set_text("LP-Schutz");  
       }
     else
       { label_av_bonus->set_text("Angriffsbonus");
         label_SL_bonus->set_text("Schadensbonus");
       }
     label_waffe->set_text(WB->Name());
     spinbutton_av_bonus->set_value(WB->av_Bonus());
     spinbutton_sl_bonus->set_value(WB->sl_Bonus());
     entry_magisch->set_text(WB->Magisch());
     spinbutton_av_bonus->grab_focus();
    }
//  hauptfenster->on_speichern_clicked();
  zeige_waffen();

//  show_alte_waffen();   
//  show_neue_waffen();   
}

void Window_Waffenbesitz::on_spinbutton_av_bonus_activate()
{ 
 spinbutton_sl_bonus->grab_focus();
}

void Window_Waffenbesitz::on_spinbutton_sl_bonus_activate()
{
 entry_magisch->grab_focus();
}

void Window_Waffenbesitz::on_entry_magisch_activate()
{
  gtk_spin_button_update(spinbutton_av_bonus->gtkobj());
  gtk_spin_button_update(spinbutton_sl_bonus->gtkobj());

//  cH_Data_waffenbesitz dt(waffenbesitz_alt_tree->getSelectedRowDataBase_as<cH_Data_waffenbesitz>());

//cout << Waffe_Besitz.size()<<'\n';
  for (std::list<cH_MidgardBasicElement>::iterator i=Waffe_Besitz.begin();i!=Waffe_Besitz.end();++i)
   { 
//     if ((*i)==dt)
     if ((*i)==*selected_weapon)
      {
        cH_WaffeBesitz WB(*i);
        WB->set_av_Bonus(spinbutton_av_bonus->get_value_as_int());
        WB->set_sl_Bonus(spinbutton_sl_bonus->get_value_as_int());
        WB->set_Magisch(entry_magisch->get_text());
      }
   }  
  table_magbonus->hide();
  zeige_waffen();
}


void Window_Waffenbesitz::on_leaf_selected_neu(cH_RowDataBase d)
{  
  const Data_waffenbesitz *dt=dynamic_cast<const Data_waffenbesitz*>(&*d);
//  move_waffe(Waffe_Besitz_neu,Waffe_Besitz,dt->get_Waffe()->Name());
   MidgardBasicElement::move_element(Waffe_Besitz_neu,Waffe_Besitz,dt->get_Waffe()->Name());
  zeige_waffen();
}

/*
void Window_Waffenbesitz::move_waffe(std::list<cH_MidgardBasicElement>& von,std::list<cH_MidgardBasicElement>& nach,std::string name)
{
  for (std::list<cH_MidgardBasicElement>::iterator i=von.begin();i!= von.end();++i)
    if ((*i)->Name()==name) 
       {nach.splice(nach.begin(),von,i);break;}
  zeige_waffen();
}
*/

Window_Waffenbesitz::Window_Waffenbesitz(midgard_CG* h,
      const midgard_CG::st_Database& _Database,
      const std::list<cH_MidgardBasicElement>& vw,
      std::list<cH_MidgardBasicElement>& wb,Grundwerte& We,
      const vector<cH_Typen>& T )
: Database(_Database), list_Waffen(vw), Waffe_Besitz(wb), Werte(We),Typ(T)
{
  table_magbonus->hide();
  hauptfenster=h;

  std::vector<string> alte_waffen;
  alte_waffen.push_back("Name");
  alte_waffen.push_back("Schaden");
  alte_waffen.push_back("Region");
  alte_waffen.push_back("mag.Bonus");
  alte_waffen.push_back("Beschreibung");
  waffenbesitz_alt_tree->setTitles(alte_waffen);
  waffenbesitz_neu_tree->setTitles(alte_waffen);

  lade_waffen();
  zeige_waffen();   
}

void Window_Waffenbesitz::on_button_close_clicked()
{
   hauptfenster->waffe_besitz_uebernehmen(Waffe_Besitz);
   destroy();
}

void Window_Waffenbesitz::zeige_waffen()
{
  hauptfenster->on_speichern_clicked();
  show_alte_waffen();
  show_neue_waffen();
}

void  Window_Waffenbesitz::show_alte_waffen()
{
  std::vector<cH_RowDataBase> datavec;
//cout <<"Alte größe = " <<Waffe_Besitz.size()<<'\n';

  for (std::list<cH_MidgardBasicElement>::const_iterator i=Waffe_Besitz.begin();i!=Waffe_Besitz.end();++i)
     datavec.push_back(new Data_waffenbesitz(*i,Werte));
  waffenbesitz_alt_tree->setDataVec(datavec);
}

void  Window_Waffenbesitz::show_neue_waffen()
{
  std::vector<cH_RowDataBase> datavec;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Waffe_Besitz_neu.begin();i!=Waffe_Besitz_neu.end();++i)
     if (hauptfenster->region_check(cH_WaffeBesitz(*i)->Waffe()->Region(cH_WaffeBesitz(*i)->Name())))
        datavec.push_back(new Data_waffenbesitz(*i,Werte));
  waffenbesitz_neu_tree->setDataVec(datavec);
}

void Window_Waffenbesitz::on_button_neuladen_clicked()
{
 lade_waffen();
 zeige_waffen();
}

void  Window_Waffenbesitz::lade_waffen()
{
  Waffe_Besitz_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Waffe.begin();i!=Database.Waffe.end();++i)
   {
     cH_Waffe w(*i);
     if (w->Name() == "waffenloser Kampf") continue;
      if ((*i)->ist_gelernt(list_Waffen))
       {
        Waffe_Besitz_neu.push_back(new WaffeBesitz(w,w->Name(),"",0,0,""));
        for (list<Waffe::st_alias>::const_iterator j=cH_Waffe(w)->Alias().begin();j!=cH_Waffe(w)->Alias().end();++j)
         {
          Waffe_Besitz_neu.push_back(new WaffeBesitz(w,(*j).name,"",0,0,""));
         }
       }
   }
/*
  exec sql begin declare section;
   char db_waffe[50];
   char db_name[50] ;
   char db_version[50] ;
  exec sql end declare section;
  strncpy(db_name,(Werte.Name_Charakter()).c_str(),sizeof(db_name));
  strncpy(db_version,(Werte.Version()).c_str(),sizeof(db_version));

  exec sql declare ein cursor for 
     SELECT distinct w.name from waffen w, charaktere_fertigkeiten c 
     where w.name = c.fertigkeit and c.charakter_name = :db_name
     and c.version = :db_version
     and w.name not in 
     (select fertigkeit from charaktere_fertigkeiten 
      where charakter_name = :db_name and version = :db_version
      and art = 'Besitz_W' and magisch = '');
  Transaction tr;
  exec sql open ein;
  SQLerror::test(__FILELINE__);
  while(true)
   {
     exec sql fetch ein into :db_waffe;
     SQLerror::test(__FILELINE__,100);
     if (sqlca.sqlcode) break;
     cH_MidgardBasicElement waffe(new Waffe(db_waffe));
     if (waffe->Name()!="waffenloser Kampf" )
      {
       Waffe_Besitz_neu.push_back(new WaffeBesitz(waffe,waffe->Name(),"",0,0,""));
       for (list<Waffe::st_alias>::const_iterator j=cH_Waffe(waffe)->Alias().begin();j!=cH_Waffe(waffe)->Alias().end();++j)
        {
         Waffe_Besitz_neu.push_back(new WaffeBesitz(waffe,(*j).name,"",0,0,""));
        }
      }
   }
  exec sql close ein;
  tr.close();
*/
}

void Window_Waffenbesitz::on_checkbutton_mag_waffenbonus_toggled()
{
}


void Window_Waffenbesitz::on_button_sort_clicked()
{
  std::deque<guint> seq = waffenbesitz_alt_tree->get_seq();
  switch((Data_waffenbesitz::SPALTEN_A)seq[0]) {
      case Data_waffenbesitz::MAGBONUS : Waffe_Besitz.sort(WaffenBesitz_sort_magbonus()) ;break;
      case Data_waffenbesitz::NAME_A   : Waffe_Besitz.sort(WaffenBesitz_sort_name()); break;
      default : manage(new WindowInfo("Sortieren nach diesem Parameter\n ist nicht möglich"));
   }
}
