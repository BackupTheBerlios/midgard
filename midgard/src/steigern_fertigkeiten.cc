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
#include "class_SimpleTree.hh"
#include <Gtk_OStream.h>
#include "Fertigkeiten.hh"
#include "Waffe.hh"       


void midgard_CG::on_fertigkeiten_laden_clicked()
{
  list_Fertigkeit_neu.clear();
  for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   { cH_Fertigkeit f(*i);
     if ((*i)->ist_gelernt(list_Fertigkeit) && cH_Fertigkeit(*i)->ZusatzEnum(Typ)==MidgardBasicElement::ZNone) continue ;
     if (f->Name()=="Sprache" || f->Name()=="Schreiben" || f->Name()=="KiDo-Technik") continue;
//     if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name())) continue;
     if(Werte.Spezies()->istVerboten(*i)) continue;
     if (f->Name()=="Zaubern" && Typ[0]->is_mage() || f->Name()=="Zaubern" && Typ[1]->is_mage() ) continue;
     if ((*i)->ist_lernbar(Typ,f->get_MapTyp()))
       if (region_check(f->Region()) )
        if (f->Voraussetzungen(Werte)) 
         {
            f->set_Erfolgswert(f->Anfangswert());
            list_Fertigkeit_neu.push_back(*i);
//Kopie            list_Fertigkeit_neu.push_back(new Fertigkeit(*f));
         }
   }
 fertigkeiten_zeigen();
}

void midgard_CG::fertigkeiten_zeigen()
{
 zeige_werte(Werte);
 MidgardBasicElement::show_list_in_tree(list_Fertigkeit_neu,neue_fert_tree,Werte,Typ,Database.ausnahmen);
 MidgardBasicElement::show_list_in_tree(list_Fertigkeit    ,alte_fert_tree,Werte,Typ,Database.ausnahmen);
}


void midgard_CG::on_leaf_selected_alte_fert(cH_RowDataBase d)
{  
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_Fertigkeit F(cH_Fertigkeit(dt->getMBE()));
 if( radiobutton_unterweisung->get_active() && 
     F->Erfolgswert() >= F->MaxUnterweisung())
   {
     regnot("Weitere Steigerung des Erfolgswertes ist NICHT mit Unterweisung möglich.");
     return ;
   }
 if (MidgardBasicElement_leaf_alt(d))
    fertigkeiten_zeigen();
}

void midgard_CG::on_alte_fert_reorder()
{
  std::deque<guint> seq = alte_fert_tree->get_seq();
  switch((Data_SimpleTree::Spalten_LONG_ALT)seq[0]) {
      case Data_SimpleTree::NAMEa : list_Fertigkeit.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME)); ;break;
      case Data_SimpleTree::WERTa : list_Fertigkeit.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::ERFOLGSWERT)); ;break;
      default : InfoFenster->AppendShow("Sortieren nach diesem Parameter\n ist nicht möglich");
   }
}


bool midgard_CG::kido_steigern_check(int wert)
{
  if (Werte.Grad()+10 > wert) return false;
  else
   { InfoFenster->AppendShow("KiDo darf nur auf maximal Grad+10 gesteigert werden.\n");
     return true;
   }
}


void midgard_CG::on_leaf_selected_neue_fert(cH_RowDataBase d)
{  
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  cH_MidgardBasicElement MBE = dt->getMBE();
  if (MBE->Name()=="KiDo") 
    { kido_bool=true;show_gtk();
      optionmenu_KiDo_Stile->set_sensitive(true);
      button_kido_auswahl->set_sensitive(false);
      InfoFenster->AppendShow("Jetzt muß ein Stil unter 'Lernschema' -> 'KiDo' gewählt werden !!!",WindowInfo::None);
      MidgardBasicElement_leaf_neu(d);      
      lernschema_sensitive(true);
    }
  else if (MBE->Name()=="Zaubern") 
    {  
     InfoFenster->AppendShow("Sicher?\nDiese Entscheidung kann nicht Rückgängig gemacht werden.",WindowInfo::ZaubernLernen,MBE);
    }
  else 
     MidgardBasicElement_leaf_neu(d);
  fertigkeiten_zeigen();
}

void midgard_CG::kaempfer_lernt_zaubern(const cH_MidgardBasicElement MBE)
{
   doppelcharaktere();
   InfoFenster->AppendShow("Jetzt unter 'Grundwerte' die zweite Charkakterklasse wählen\n",WindowInfo::None);
   // Resistenzboni für Zauberer setzten:
//         Werte.set_magBoni(Werte.bo_Psy()+3,Werte.bo_Phs()+1,Werte.bo_Phk()+3);
   if (Werte.Zaubern_wert()==2) Werte.setZaubern_wert(10);
//   cH_MidgardBasicElement MBE=new Fertigkeit(*cH_Fertigkeit("Zaubern"));
   MidgardBasicElement::move_element(list_Fertigkeit,list_Fertigkeit_neu,MBE);
  fertigkeiten_zeigen();
}


void midgard_CG::fillClistLand(const cH_MidgardBasicElement &MBE)
{
  clist_landauswahl->clear();
  Gtk::OStream os(clist_landauswahl);

  switch (MBE->ZusatzEnum(Typ))
   {
     case MidgardBasicElement::ZLand :
      {        
        clist_landauswahl->set_column_title(0, "Land auswählen");
        for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
         {
            os <<(*i)->Name()<<'\n';
            os.flush(MBE->ref(),&HandleContent::unref);
          }
        break;
      }
     case MidgardBasicElement::ZWaffe :
      {      
        clist_landauswahl->set_column_title(0, "Waffe auswählen");
        for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
         {
           if (cH_Waffe(*i)->Art()=="Schußwaffe" || cH_Waffe(*i)->Art()=="Wurfwaffe")
            {
              os <<(*i)->Name()<<'\n';
              os.flush(MBE->ref(),&HandleContent::unref);
            }
         }
        break;
      }
     case MidgardBasicElement::ZTabelle : 
      {
        clist_landauswahl->set_column_title(0, MBE->Name()+" auswählen");
        std::vector<std::string> VZ=MBE->VZusatz();
        for (std::vector<std::string>::const_iterator i=VZ.begin();i!=VZ.end();++i)
           {
             os << *i <<'\n';
             os.flush(MBE->ref(),&HandleContent::unref);
           }
        break; 
       }

     case MidgardBasicElement::ZHerkunft :
      {
        assert("Never get here\n");
      }
     case MidgardBasicElement::ZNone :
      {
        assert("Never get here\n");
      }
   }
  scrolledwindow_landauswahl->show();
}

void midgard_CG::on_clist_landauswahl_select_row(gint row, gint column, GdkEvent *event)
{
  std::string zusatz = clist_landauswahl->get_text(row,0);
  MidgardBasicElement *MBE=static_cast<MidgardBasicElement*>(clist_landauswahl->selection().begin()->get_data());
  MBE->setZusatz(zusatz);
  // Erhöter Erfolgswert für Landeskunde Heimat:
  if(zusatz==Werte.Herkunft()->Name()) MBE->set_Erfolgswert(9);
  scrolledwindow_landauswahl->hide();
  on_fertigkeiten_laden_clicked();
  neue_fert_tree->set_sensitive(true);
}

