/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
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

#include "table_steigern.hh"
#include "midgard_CG.hh"
#include "class_SimpleTree.hh"
#include "Fertigkeiten.hh"
#include "Sprache.hh"
#include "Zauber.hh"
#include <Misc/itos.h>
#include <libmagus/Ausgabe.hh>
#include <libmagus/Datenbank.hh>

enum { Button_Steigern, Button_Verlernen, Button_PP_eingeben };

bool table_steigern::MidgardBasicElement_leaf_alt(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 MBEmlt &MBE = const_cast<MBEmlt&>(dt->getMBE());
 if (button_was_tun->get_index()==Button_PP_eingeben
     || (togglebutton_praxispunkte->get_active()
     && radiobutton_pp_fertigkeit->get_active())) 
  {
   spinbutton_pp_eingeben->set_value(MBE->Praxispunkte());
   spinbutton_pp_eingeben->select_region(0,-1);
   spinbutton_pp_eingeben->show();
   spinbutton_pp_eingeben->grab_focus();
   return false;
  }

 ////////////////////////////////////////////////////////////////////////
 AbenteurerAuswahl::LocalUndoRememberer undo(hauptfenster->getChar().actualIterator());

 if((*MBE).What()==MidgardBasicElement::FERTIGKEIT 
    && (*MBE)->Name()=="KiDo" 
    && kido_steigern_check(MBE->Erfolgswert())) 
   return false;

 //////////////////////////////////////////////////////////////////////////
// Abenteurer::e_wie_steigern wie=get_wie_steigern();
// Abenteurer::st_bool_steigern bool_steigern=get_bool_steigern();
 
 if (!hauptfenster->getAben().reduzieren && MBE->Steigern(hauptfenster->getAben()))
    { bool result=false;
      getKnownTree((*MBE).What())->getModel().about_to_change(d);
      if (hauptfenster->getAben().Steigern(MBE)) result=true;
      getKnownTree((*MBE).What())->getModel().has_changed(d);
      if (result) 
      { refresh_gesteigert();
        undo.finish((*MBE)->What_str()+" "+(*MBE)->Name()+" auf "+itos(MBE->Erfolgswert())+" gesteigert");
      }
      return result;
    }
 else if (hauptfenster->getAben().reduzieren)
    { bool result=false;
      getKnownTree((*MBE).What())->getModel().remove_line(d);
      bool verlernt=false;
      if (hauptfenster->getAben().ReduzierenVerlernen(MBE,verlernt)) 
        result=true;
      if (result && verlernt) 
      { std::list<MBEmlt> *MyList=&hauptfenster->getAben().getList((*MBE).What()),
               *MyList_neu=&getLearnList((*MBE).What());
        Abenteurer::move_element(*MyList,*MyList_neu,MBE);
        getLearnTree((*MBE).What())->getModel().append_line(d);
      }
      else getKnownTree((*MBE).What())->getModel().append_line(d);
      
      if (result) 
      { refresh_gesteigert();
        undo.finish((*MBE)->What_str()+" "+(*MBE)->Name()+" auf "+itos(MBE->Erfolgswert())+" verlernt");
      }
      return result;
    }
 return false;
}

void table_steigern::lernen_von_spruchrolle_fragen(const int bonus)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*(neue_zauber_tree->getSelectedRowDataBase()));
 MBEmlt &MBE = const_cast<MBEmlt&>(dt->getMBE()); 
 neu_lernen(MBE,bonus);
}

void table_steigern::MidgardBasicElement_leaf_neu(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 MBEmlt &MBE = const_cast<MBEmlt&>(dt->getMBE());
 if (neu_lernen(MBE))
 { if (/* (*MBE).What()!=MidgardBasicElement::FERTIGKEIT 
       || */ !(*MBE)->ZusatzEnum(hauptfenster->getAben().getVTyp()))
     getLearnTree((*MBE).What())->getModel().remove_line(d);
#warning ist das das richtige Element?
   getKnownTree((*MBE).What())->getModel().append_line(d);
   refresh_gesteigert();
 }
}

bool table_steigern::neu_lernen(MBEmlt &MBE,const int bonus)
{
 bool ok=hauptfenster->getAben().neu_lernen(MBE,bonus);
 if(!ok) return false;
//ab hier neuer code:
 hauptfenster->getChar().undosave((*MBE)->What_str()+" "+(*MBE)->Name()+" gelernt");
 std::list<MBEmlt> &liste=getLearnList((*MBE).What());
 Abenteurer &A=hauptfenster->getAben();
 if ((*MBE).What()==MidgardBasicElement::FERTIGKEIT
         || (*MBE).What()==MidgardBasicElement::ZAUBER)
   { if((*MBE)->ZusatzEnum(A.getVTyp()))
      {
//        neue_fert_tree->set_sensitive(false);
        MBE=MBEmlt(&*cH_Fertigkeit(MBE->getMBE()));
        fillClistZusatz(MBE);
        // Davor stellen, damit beim Kopieren dieses MBE Verschoben wird.   
        liste.push_front(MBE);
      }
   }
 A.move_neues_element(MBE,&liste);
 return true;
} 

std::list<MBEmlt> &table_steigern::getLearnList(MidgardBasicElement::MBEE was)
{ switch (was)
  { case MidgardBasicElement::FERTIGKEIT: return list_Fertigkeit_neu;
    case MidgardBasicElement::WAFFE: return list_Waffen_neu;
    case MidgardBasicElement::WAFFEGRUND: return list_WaffenGrund_neu;
    case MidgardBasicElement::ZAUBER: return list_Zauber_neu;
    case MidgardBasicElement::ZAUBERWERK: return list_Zauberwerk_neu;
    case MidgardBasicElement::KIDO: return list_Kido_neu;
    case MidgardBasicElement::SPRACHE: return list_Sprache_neu;
    case MidgardBasicElement::SCHRIFT: return list_Schrift_neu;
    default: assert(!"getLearnList: invalid arg");
  }
  abort();
}

MidgardBasicTree *table_steigern::getKnownTree(MidgardBasicElement::MBEE was)
{ switch (was)
  { case MidgardBasicElement::FERTIGKEIT: return alte_fert_tree;
    case MidgardBasicElement::WAFFEGRUND: return alte_grund_tree;
    case MidgardBasicElement::WAFFE: return alte_waffen_tree;
    case MidgardBasicElement::ZAUBER: return alte_zauber_tree;
    case MidgardBasicElement::ZAUBERWERK: return alte_zaubermittel_tree;
    case MidgardBasicElement::KIDO: return alte_kido_tree;
    case MidgardBasicElement::SPRACHE: return alte_sprache_tree;
    case MidgardBasicElement::SCHRIFT: return alte_schrift_tree;
    default: assert(!"getKnownTree: invalid arg");
    // WAFFEBESITZ: waffenbesitz_alt_tree
  }
  abort();
}

MidgardBasicTree *table_steigern::getLearnTree(MidgardBasicElement::MBEE was)
{ switch (was)
  { case MidgardBasicElement::FERTIGKEIT: return neue_fert_tree;
    case MidgardBasicElement::WAFFEGRUND: return neue_grund_tree;
    case MidgardBasicElement::WAFFE: return neue_waffen_tree;
    case MidgardBasicElement::ZAUBER: return neue_zauber_tree;
    case MidgardBasicElement::ZAUBERWERK: return neue_zaubermittel_tree;
    case MidgardBasicElement::KIDO: return neue_kido_tree;
    case MidgardBasicElement::SPRACHE: return neue_sprache_tree;
    case MidgardBasicElement::SCHRIFT: return neue_schrift_tree;
    default: assert(!"getLearnTree: invalid arg");
    // WAFFEBESITZ: waffenbesitz_neu_tree
  }
  abort();
}
