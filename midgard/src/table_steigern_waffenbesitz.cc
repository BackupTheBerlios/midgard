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
#include "table_steigern.hh"
#include <Gtk_OStream.h>
#include <Aux/itos.h>
#include "Data_waffenbesitz.hh"

void table_steigern::on_leaf_waffenbesitz_selected_alt(cH_RowDataBase d)
{  
  const Data_waffenbesitz *dt=dynamic_cast<const Data_waffenbesitz*>(&*d);
  WaffeBesitz WB(dt->get_Waffe());
cout << WB->Name()<<'\t'<<WB.AliasName()<<'\n';

  if(!checkbutton_mag_waffenbonus->get_active()) 
   {
    const MidgardBasicElement *MBE = &static_cast<const MidgardBasicElement&>(*WB);
    for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Waffen_besitz().begin();
         i!=hauptfenster->getChar().List_Waffen_besitz().end();++i)
     {
       if(*i==MBE)
         {
            hauptfenster->getChar().List_Waffen_besitz().remove(*i);
            break;
         }
     }
    show_alte_waffen();
//    zeige_waffen();
   }
  else 
   {
     table_magbonus->show();
     if (WB.Waffe()->Art()=="Verteidigung")
       { label_av_bonus->set_text("Abwehrbonus");
         label_sl_bonus->set_text("LP-Schutz");  
       }
     else
       { label_av_bonus->set_text("Angriffsbonus");
         label_sl_bonus->set_text("Schadensbonus");
       }
//     label_waffe->set_text(WB->Name());
     spinbutton_av_bonus->set_value(WB.av_Bonus());
     spinbutton_sl_bonus->set_value(WB.sl_Bonus());
     entry_magisch->set_text(WB.Magisch());
     spinbutton_av_bonus->grab_focus();
     spinbutton_av_bonus->select_region(0,-1);
    }
}

void table_steigern::on_spinbutton_av_bonus_activate()
{ spinbutton_sl_bonus->grab_focus(); spinbutton_sl_bonus->select_region(0,-1);}
void table_steigern::on_spinbutton_sl_bonus_activate()
{ entry_magisch->grab_focus(); entry_magisch->select_region(0,-1);}

void table_steigern::on_entry_magisch_activate()
{
  spinbutton_av_bonus->update();
  spinbutton_sl_bonus->update();

  try{
     cH_Data_waffenbesitz dt(waffenbesitz_alt_tree->getSelectedRowDataBase_as<cH_Data_waffenbesitz>());
     WaffeBesitz WB = dt->get_Waffe();

     std::list<MidgardBasicElement_mutable> &L=hauptfenster->getChar().List_Waffen_besitz();
     for(std::list<MidgardBasicElement_mutable>::iterator i=L.begin();i!=L.end();++i)
      {
       if((*i)->Name()==WB->Name())
        {
          WB.set_av_Bonus(spinbutton_av_bonus->get_value_as_int());
          WB.set_sl_Bonus(spinbutton_sl_bonus->get_value_as_int());
          WB.set_Magisch(entry_magisch->get_text());
          break;
        }
      }

     table_magbonus->hide();
  } catch(std::exception &e) {cerr<<e.what()<<'\n';
   hauptfenster->set_status("Keine Waffe selektiert");
     };
//  zeige_waffen();
  show_alte_waffen();
}


void table_steigern::on_leaf_waffenbesitz_selected_neu(cH_RowDataBase d)
{  
  const Data_waffenbesitz *dt=dynamic_cast<const Data_waffenbesitz*>(&*d);
//  cH_MidgardBasicElement MBE=new WaffeBesitz(*cH_WaffeBesitz(dt->get_Waffe()));
//  MidgardBasicElement_mutable MBE=dt->get_Waffe();
  WaffeBesitz MBE=dt->get_Waffe();

cout << MBE->Name()<<'\t'<<MBE.AliasName()<<'\n';
  hauptfenster->getChar().List_Waffen_besitz().push_back(MBE);
//  zeige_waffen();
  show_alte_waffen();
}

void table_steigern::init_waffenbesitz()
{
  table_magbonus->hide();

  std::vector<string> alte_waffen;
  alte_waffen.push_back("Name");
  alte_waffen.push_back("Schaden");
  alte_waffen.push_back("Region");
  alte_waffen.push_back("mag.Bonus");
  alte_waffen.push_back("Beschreibung");
  waffenbesitz_alt_tree->setTitles(alte_waffen);
  waffenbesitz_neu_tree->setTitles(alte_waffen);

  lade_waffenbesitz();
  show_alte_waffen();
}

void  table_steigern::show_alte_waffen()
{
  std::vector<cH_RowDataBase> datavec;
//cout <<"Alte größe = " <<Waffe_Besitz.size()<<'\n';

  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Waffen_besitz().begin();i!=hauptfenster->getChar().List_Waffen_besitz().end();++i)
     datavec.push_back(new Data_waffenbesitz(*i,hauptfenster));
  waffenbesitz_alt_tree->setDataVec(datavec);
}

void  table_steigern::lade_waffenbesitz()
{
  std::list<WaffeBesitz> Waffe_Besitz_neu;
  const std::list<cH_MidgardBasicElement> L=hauptfenster->getCDatabase().Waffe;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
   {
     cH_Waffe w(*i);
     if (w->Grundkenntnis() == "Kampf ohne Waffen") continue;
      if (MidgardBasicElement_mutable(*i).ist_gelernt(hauptfenster->getCChar().CList_Waffen()))
       {
//        MidgardBasicElement_mutable W(new WaffeBesitz(w,0,w->Name(),0,0,""));
        WaffeBesitz W(w,0,w->Name(),0,0,"");
        Waffe_Besitz_neu.push_back(W);
        for (list<Waffe::st_alias>::const_iterator j=cH_Waffe(w)->Alias().begin();j!=cH_Waffe(w)->Alias().end();++j)
         {
           WaffeBesitz W(w,0,(*j).name,0,0,"");
cout << W->Name()<<'\t'<<(*j).name<<'\t'<<W.AliasName()<<'\n';
           if(hauptfenster->region_check(j->region))
                 Waffe_Besitz_neu.push_back(W);
         }
       }
   }
  std::vector<cH_RowDataBase> datavec;
  for (std::list<WaffeBesitz>::const_iterator i=Waffe_Besitz_neu.begin();i!=Waffe_Besitz_neu.end();++i)
        datavec.push_back(new Data_waffenbesitz(*i,hauptfenster));
  waffenbesitz_neu_tree->setDataVec(datavec);
}

void table_steigern::on_checkbutton_mag_waffenbonus_toggled()
{
  if(!checkbutton_mag_waffenbonus->get_active())
     on_entry_magisch_activate();
}

void table_steigern::on_alte_waffenbesitz_reorder()
{
  std::deque<guint> seq = waffenbesitz_alt_tree->get_seq();
  switch((Data_waffenbesitz::SPALTEN_A)seq[0]) {
      case Data_waffenbesitz::MAGBONUS : hauptfenster->getChar().List_Waffen_besitz().sort(WaffenBesitz_sort_magbonus()) ;break;
      case Data_waffenbesitz::NAME_A   : hauptfenster->getChar().List_Waffen_besitz().sort(WaffenBesitz_sort_name()); break;
      default : hauptfenster->set_status("Sortieren nach diesem Parameter\n ist nicht möglich");
   }
}
