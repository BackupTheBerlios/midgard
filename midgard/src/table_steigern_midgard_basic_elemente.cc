/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
#include "Zauber.hh"
#include <Aux/itos.h>

bool table_steigern::MidgardBasicElement_leaf_alt(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 MidgardBasicElement_mutable &MBE = const_cast<MidgardBasicElement_mutable&>(dt->getMBE());
 if(togglebutton_praxispunkte->get_active() && radiobutton_pp_fertigkeit->get_active()) 
  {
   spinbutton_pp_eingeben->set_value(MBE.Praxispunkte());
   spinbutton_pp_eingeben->select_region(0,-1);
   spinbutton_pp_eingeben->show();
   spinbutton_pp_eingeben->grab_focus();
   return false;
  }

 ////////////////////////////////////////////////////////////////////////
 std::list<MidgardBasicElement_mutable> *MyList,*MyList_neu;
 if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
   { if (MBE->Name()=="KiDo" && kido_steigern_check(MBE.Erfolgswert())) return false;
     MyList     = &hauptfenster->getChar().List_Fertigkeit(); MyList_neu = &list_Fertigkeit_neu;   }
 else if(MBE->What()==MidgardBasicElement::WAFFE) 
   { MyList     = &hauptfenster->getChar().List_Waffen(); MyList_neu = &list_Waffen_neu;  }
 else if(MBE->What()==MidgardBasicElement::WAFFEGRUND) 
   { MyList     = &hauptfenster->getChar().List_WaffenGrund(); MyList_neu = &list_WaffenGrund_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBER) 
   { MyList     = &hauptfenster->getChar().List_Zauber(); MyList_neu = &list_Zauber_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBERWERK) 
   { MyList     = &hauptfenster->getChar().List_Zauberwerk(); MyList_neu = &list_Zauberwerk_neu;  }
 else if(MBE->What()==MidgardBasicElement::KIDO) 
   { MyList     = &hauptfenster->getChar().List_Kido(); MyList_neu = &list_Kido_neu;  }
 else if(MBE->What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &hauptfenster->getChar().List_Sprache(); MyList_neu = &list_Sprache_neu;  }
 else if(MBE->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &hauptfenster->getChar().List_Schrift(); MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");

 //////////////////////////////////////////////////////////////////////////

 if (radiobutton_steigern->get_active() && MBE.Steigern(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp()))
    {
      int stufen=1;
      int steigerkosten=MBE.Steigern(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp());
      if (!steigern_usp(steigerkosten,&MBE,stufen)) return false;
      if ( MBE.Erfolgswert() >= MBE->MaxErfolgswert(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp())) 
          { hauptfenster->set_status("Maximal möglicher Erfolgswert erreicht");
            return false; }
      hauptfenster->getChar().getWerte().addGFP(steigerkosten);
      for (std::list<MidgardBasicElement_mutable>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i)->Name() == MBE->Name()) 
            (*i).addErfolgswert(stufen); 
    }
 else if (radiobutton_reduzieren->get_active() && MBE.Reduzieren(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp()))
    {
      if (checkbutton_EP_Geld->get_active()) desteigern(MBE.Reduzieren(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp()));
      hauptfenster->getChar().getWerte().addGFP(-MBE.Reduzieren(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp()));
      for (std::list<MidgardBasicElement_mutable>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i)->Name() == MBE->Name())  
            (*i).addErfolgswert(-1); 
    }
 else if (radiobutton_verlernen->get_active() && MBE.Verlernen(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp()))
    {
      guint verlernen = MBE.Verlernen(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp());
      if( MBE->What()==MidgardBasicElement::ZAUBER && 
          togglebutton_spruchrolle->get_active() )    verlernen/=5  ;
      if (checkbutton_EP_Geld->get_active()) desteigern(verlernen);
      hauptfenster->getChar().getWerte().addGFP(-verlernen);
      MidgardBasicElement::move_element(*MyList,*MyList_neu,MBE);
    }
 else if (radiobutton_verlernen->get_active() && MBE->What()==MidgardBasicElement::WAFFE)
    {
      MidgardBasicElement::move_element(*MyList,*MyList_neu,MBE);
    }
 hauptfenster->undosave(MBE->Name()+" auf "+itos(MBE.Erfolgswert())+" gesteigert");
 return true;
}


void table_steigern::MidgardBasicElement_leaf_neu(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 MidgardBasicElement_mutable &MBE = const_cast<MidgardBasicElement_mutable&>(dt->getMBE());
 // Neue Dinge können nur durch Unterweisung gelernt werden
 // es sei denn es handelt sich um Zaubersprüche
 if(MBE->What()!=MidgardBasicElement::ZAUBER)
  { if (!radiobutton_unterweisung->get_active())
     { hauptfenster->set_status("Neue Fertigkeiten, Waffen, Sprachen und Schriften können nur durch 'Unterweisung' gelernt werden");
       return;
     }
  }
 else // ==> MBE->What()==MidgardBasicElement::ZAUBER
  {
/*
    if(radiobutton_selbst->get_active() )
      { hauptfenster->set_status("Neue Zauber können nicht durch 'Selbststudium' gelernt werden");
        return;
      }
*/
    // Nicht alle Abenteurerklassen können Zauber auch mit Praxispunkten lernen
    if(radiobutton_praxis->get_active() )
      { if(!hauptfenster->getCChar().CTyp1()->SpruecheMitPP() && !hauptfenster->getCChar().CTyp2()->SpruecheMitPP() )
           { hauptfenster->set_status("Neue Zaubersprüche können von "+hauptfenster->getCChar().CTyp1()->Name(hauptfenster->getCChar().getCWerte().Geschlecht())
                     +" nicht durch Praxispunkte gelernt werden");
             return;
           }
        else if(MBE->Standard__(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp())!="G")
           { hauptfenster->set_status("Nur Grundzauber können von "+hauptfenster->getCChar().CTyp1()->Name(hauptfenster->getCChar().getCWerte().Geschlecht())
                     +" mit Praxispunkten gelernt werden");
             return;
           }
      }
  }
 int kosten=MBE->Kosten(hauptfenster->getCChar().getCWerte(),hauptfenster->getCChar().getVTyp());

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() ) kosten/=10;
 /////////////////////////////////////////////////////////////////////////
 
 int dummy=1;
 if (!steigern_usp(kosten,&MBE,dummy)) return;
 hauptfenster->getChar().getWerte().addGFP(kosten);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_auto->get_active() )    hauptfenster->getChar().getWerte().addGFP(kosten);
 else if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_wuerfeln->get_active() )   
   {
     if(!spruchrolle_wuerfeln(MBE)) return;
     else hauptfenster->getChar().getWerte().addGFP(kosten);
   } 
 /////////////////////////////////////////////////////////////////////////

 std::list<MidgardBasicElement_mutable> *MyList,*MyList_neu;
 if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
   { if(MBE->ZusatzEnum(hauptfenster->getCChar().getVTyp()))
      {  
        neue_fert_tree->set_sensitive(false);
        MBE=MidgardBasicElement_mutable(new Fertigkeit(*cH_Fertigkeit(MBE)));
        fillClistZusatz(MBE);
        // Davor stellen, damit beim Kopieren dieses MBE in Verschoben wird.
        list_Fertigkeit_neu.push_front(MBE);
      }
     if (MBE->Name()=="KiDo" && kido_steigern_check(MBE.Erfolgswert())) return;
     MyList     = &hauptfenster->getChar().List_Fertigkeit(); MyList_neu = &list_Fertigkeit_neu;
   }
 else if(MBE->What()==MidgardBasicElement::WAFFE) 
   { MyList     = &hauptfenster->getChar().List_Waffen(); 
     MyList_neu = &list_Waffen_neu;  
//     if(cH_Waffe(MBE)->Art()=="Verteidigung") MBE.setErfolgswert(1);
//     else MBE.setErfolgswert(4);
   }
 else if(MBE->What()==MidgardBasicElement::WAFFEGRUND) 
   { MyList     = &hauptfenster->getChar().List_WaffenGrund(); MyList_neu = &list_WaffenGrund_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBER) 
  {
   { if(MBE->ZusatzEnum(hauptfenster->getCChar().getVTyp()))
      {  
        MBE=MidgardBasicElement_mutable(new Zauber(*cH_Zauber(MBE)));
        fillClistZusatz(MBE);
        // Davor stellen, damit beim Kopieren dieses MBE in Verschoben wird.
        list_Zauber_neu.push_front(MBE);
      }
   MyList     = &hauptfenster->getChar().List_Zauber(); MyList_neu = &list_Zauber_neu;  }
  }
 else if(MBE->What()==MidgardBasicElement::ZAUBERWERK) 
   { MyList     = &hauptfenster->getChar().List_Zauberwerk(); MyList_neu = &list_Zauberwerk_neu;  }
 else if(MBE->What()==MidgardBasicElement::KIDO) 
   { MyList     = &hauptfenster->getChar().List_Kido(); MyList_neu = &list_Kido_neu;  }
 else if(MBE->What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &hauptfenster->getChar().List_Sprache(); MyList_neu = &list_Sprache_neu;  }
 else if(MBE->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &hauptfenster->getChar().List_Schrift(); MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");


//cout << "Move "<<MyList_neu->size()<<' '<<MyList->size()<<'\n';

 MidgardBasicElement::move_element(*MyList_neu,*MyList,MBE);
 hauptfenster->undosave(MBE->Name()+" gelernt");

//cout << "Move "<<MyList_neu->size()<<' '<<MyList->size()<<'\n';
}


/*
void midgard_CG::MidgardBasicElement_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe,const std::list<cH_MidgardBasicElement>& mbe2)
{
  if(mbe.begin()==mbe.end()) return;
  if((*mbe.begin())->What()==MidgardBasicElement::WAFFEBESITZ)
   {
    hauptfenster->getCChar().CList_Waffen_besitz=mbe();
   }
//  else if((*mbe.begin())->What()==MidgardBasicElement::KIDO)
//   {
//    list_Kido=mbe;
//   }
  else assert(0);
  undosave(itos(mbe.size())+" "+(*mbe.begin())->What_str()+"n übernommen");
  show_gelerntes();
}
*/
