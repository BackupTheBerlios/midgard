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
#include "Sprache.hh"
#include "Zauber.hh"
#include <Misc/itos.h>

bool table_steigern::MidgardBasicElement_leaf_alt(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 MBEmlt &MBE = const_cast<MBEmlt&>(dt->getMBE());
 if(togglebutton_praxispunkte->get_active() && radiobutton_pp_fertigkeit->get_active()) 
  {
   spinbutton_pp_eingeben->set_value(MBE->Praxispunkte());
   spinbutton_pp_eingeben->select_region(0,-1);
   spinbutton_pp_eingeben->show();
   spinbutton_pp_eingeben->grab_focus();
   return false;
  }

 ////////////////////////////////////////////////////////////////////////
 std::list<MBEmlt> *MyList,*MyList_neu;
 if((*MBE)->What()==MidgardBasicElement::FERTIGKEIT) 
   { if ((*MBE)->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return false;
     MyList     = &hauptfenster->getChar()->List_Fertigkeit(); MyList_neu = &list_Fertigkeit_neu;   }
 else if((*MBE)->What()==MidgardBasicElement::WAFFE) 
   { MyList     = &hauptfenster->getChar()->List_Waffen(); MyList_neu = &list_Waffen_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::WAFFEGRUND) 
   { MyList     = &hauptfenster->getChar()->List_WaffenGrund(); MyList_neu = &list_WaffenGrund_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::ZAUBER) 
   { MyList     = &hauptfenster->getChar()->List_Zauber(); MyList_neu = &list_Zauber_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::ZAUBERWERK) 
   { MyList     = &hauptfenster->getChar()->List_Zauberwerk(); MyList_neu = &list_Zauberwerk_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::KIDO) 
   { MyList     = &hauptfenster->getChar()->List_Kido(); MyList_neu = &list_Kido_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &hauptfenster->getChar()->List_Sprache(); MyList_neu = &list_Sprache_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &hauptfenster->getChar()->List_Schrift(); MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");

 //////////////////////////////////////////////////////////////////////////
 std::string info;
 Abenteurer::e_wie_steigern wie=get_wie_steigern();
 Abenteurer::st_bool_steigern bool_steigern=get_bool_steigern();
 
 if (radiobutton_steigern->get_active() && MBE->Steigern(hauptfenster->getAben()))
    {
      bool ok=hauptfenster->getAben().steigere(MBE,info,wie,bool_steigern);
      hauptfenster->set_status(info);
      if(!ok) return false;

/*
      if ( MBE->Erfolgswert() >= (*MBE)->MaxErfolgswert(hauptfenster->getAben())) 
          { hauptfenster->set_status("Maximal möglicher Erfolgswert erreicht");
            return false; }
      if(radiobutton_unterweisung->get_active())
       {
         if( ((*MBE)->What()==MidgardBasicElement::FERTIGKEIT &&
              MBE->Erfolgswert() >= cH_Fertigkeit(MBE->getMBE())->MaxUnterweisung()) ||
             ((*MBE)->What()==MidgardBasicElement::SPRACHE &&
              MBE->Erfolgswert() >= cH_Fertigkeit("Sprache")->MaxUnterweisung()) ||
             ((*MBE)->What()==MidgardBasicElement::SCHRIFT &&
              MBE->Erfolgswert() >= cH_Fertigkeit("Schreiben")->MaxUnterweisung())
             )
          { hauptfenster->set_status("Weitere Steigerung des Erfolgswertes ist NICHT mit Unterweisung möglich.");
            return false; }
       }      
      int stufen=1;
      int steigerkosten=MBE->Steigern(hauptfenster->getAben());
      if (!steigern_usp(steigerkosten,&MBE,stufen)) return false;
      hauptfenster->getChar()->getWerte().addGFP(steigerkosten);
      for (std::list<MBEmlt>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i) == MBE) (*i).addErfolgswert(stufen) ; 
*/
    }
 else if (radiobutton_reduzieren->get_active() && MBE->Reduzieren(hauptfenster->getAben()))
    {
      hauptfenster->getAben().reduziere(MBE,wie,bool_steigern);
/*
      if (checkbutton_EP_Geld->get_active()) desteigern(MBE->Reduzieren(hauptfenster->getAben()));
      hauptfenster->getChar()->getWerte().addGFP(-MBE->Reduzieren(hauptfenster->getAben()));
      for (std::list<MBEmlt>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i) == MBE)  (*i).addErfolgswert(-1) ; 
*/
    }
 else if (radiobutton_verlernen->get_active() && MBE->Verlernen(hauptfenster->getAben()))
    {
      hauptfenster->getAben().verlerne(MBE,wie,bool_steigern);
/*
      guint verlernen = MBE->Verlernen(hauptfenster->getAben());
      if( (*MBE)->What()==MidgardBasicElement::ZAUBER && 
          togglebutton_spruchrolle->get_active() )    verlernen/=5  ;
      if (checkbutton_EP_Geld->get_active()) desteigern(verlernen);
      hauptfenster->getChar()->getWerte().addGFP(-verlernen);
*/
      Abenteurer::move_element(*MyList,*MyList_neu,MBE);
    }
 else if (radiobutton_verlernen->get_active() && (*MBE)->What()==MidgardBasicElement::WAFFE)
    {
      Abenteurer::move_element(*MyList,*MyList_neu,MBE);
    }
 hauptfenster->undosave((*MBE)->Name()+" auf "+itos(MBE->Erfolgswert())+" gesteigert");
 return true;
}

const Enums::e_wie_steigern table_steigern::get_wie_steigern()
{
 if     (radiobutton_unterweisung->get_active()) return Enums::eUnterweisung; 
 else if(radiobutton_selbst->get_active()) return Enums::eSelbststudium; 
 else if(radiobutton_praxis->get_active()) return Enums::ePraxis; 
 assert (!"never get here"); abort();
}

const Enums::st_bool_steigern table_steigern::get_bool_steigern()
{
 return Enums::st_bool_steigern(checkbutton_EP_Geld->get_active(),
         hauptfenster->getOptionen()->HausregelCheck(Midgard_Optionen::Gold).active,
         togglebutton_spruchrolle->get_active(),
         radio_spruchrolle_wuerfeln->get_active(),
         radiobutton_pp_hoch_wie_geht->get_active(),
         togglebutton_pp_verfallen->get_active(),
         togglebutton_pp_aep_fuellen->get_active(),
         togglebutton_neue_sprache_pp->get_active()
      );
}

void table_steigern::MidgardBasicElement_leaf_neu(const cH_RowDataBase &d)
{
// Abenteurer &A=hauptfenster->getAben();
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 MBEmlt &MBE = const_cast<MBEmlt&>(dt->getMBE());

 std::string info;
 bool ok=hauptfenster->getChar()->neu_lernen(MBE,info,get_wie_steigern(),get_bool_steigern());
 hauptfenster->set_status(info);
 if(!ok) return ;
 
#if 0
 if(((*MBE)->What()==MidgardBasicElement::FERTIGKEIT ||  (*MBE)->What()==MidgardBasicElement::WAFFE)
   && !(*MBE)->Voraussetzung(A,false))
  {
    hauptfenster->set_status("Erst muß "+(*MBE)->Voraussetzung()+" gelernt werden");
    return;
  }

 // Neue Dinge können nur durch Unterweisung gelernt werden
 // es sei denn es handelt sich um Zaubersprüche
 if((*MBE)->What()!=MidgardBasicElement::ZAUBER)
  { if (!radiobutton_unterweisung->get_active())
     { hauptfenster->set_status("Neue Fertigkeiten, Waffen, Sprachen und Schriften können nur durch 'Unterweisung' gelernt werden");
       return;
     }
  }
 else // ==> (*MBE)->What()==MidgardBasicElement::ZAUBER
  {
/*
    if(radiobutton_selbst->get_active() )
      { hauptfenster->set_status("Neue Zauber können nicht durch 'Selbststudium' gelernt werden");
        return;
      }
*/
    // Nicht alle Abenteurerklassen können Zauber auch mit Praxispunkten lernen
    if(radiobutton_praxis->get_active() )
      { if(!hauptfenster->getChar()->Typ1()->SpruecheMitPP() && !hauptfenster->getChar()->Typ2()->SpruecheMitPP() )
           { hauptfenster->set_status("Neue Zaubersprüche können von "+hauptfenster->getChar()->Typ1()->Name(hauptfenster->getChar()->getWerte().Geschlecht())
                     +" nicht durch Praxispunkte gelernt werden");
             return;
           }
        else if((*MBE)->Standard__(hauptfenster->getAben())!="G")
           { hauptfenster->set_status("Nur Grundzauber können von "+hauptfenster->getChar()->Typ1()->Name(hauptfenster->getChar()->getWerte().Geschlecht())
                     +" mit Praxispunkten gelernt werden");
             return;
           }
      }
  }
 int kosten=(*MBE)->Kosten(hauptfenster->getAben());

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( (*MBE)->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() ) kosten/=10;
 /////////////////////////////////////////////////////////////////////////
 // Lernern neuer Sprache mit PP: ///////////////////////////////////////
 bool neue_sprache_mit_pp=false;
 if((*MBE)->What()==MidgardBasicElement::SPRACHE &&
     togglebutton_neue_sprache_pp->get_active() )
   { neue_sprache_mit_pp=true;  kosten=40;}
 /////////////////////////////////////////////////////////////////////////
 
 int dummy=1;
 if(neue_sprache_mit_pp) 
   { set_lernzeit(kosten,Nichts);
     if((*MBE)->Grundfertigkeit(hauptfenster->getAben()))
          MBE->setErfolgswert(9);
     else MBE->setErfolgswert(7);
   }
 else if (!steigern_usp(kosten,&MBE,dummy)) return;


 hauptfenster->getChar()->getWerte().addGFP(kosten);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( (*MBE)->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_auto->get_active() )    hauptfenster->getChar()->getWerte().addGFP(kosten);
 else if( (*MBE)->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_wuerfeln->get_active() )   
   {
     std::string info;
     bool x=cH_Zauber(MBE->getMBE())->spruchrolle_wuerfeln(hauptfenster->getAben(),hauptfenster->random,info);
     hauptfenster->set_info(info);    
     if(!x) return;
     else hauptfenster->getChar()->getWerte().addGFP(kosten);
   } 
#endif
 /////////////////////////////////////////////////////////////////////////

 std::list<MBEmlt> *MyList,*MyList_neu;
 if((*MBE)->What()==MidgardBasicElement::FERTIGKEIT) 
   { if((*MBE)->ZusatzEnum(hauptfenster->getChar()->getVTyp()))
      {  
        neue_fert_tree->set_sensitive(false);
        MBE=MBEmlt(new Fertigkeit(*cH_Fertigkeit(MBE->getMBE())));
        fillClistZusatz(MBE);
        // Davor stellen, damit beim Kopieren dieses MBE Verschoben wird.
        list_Fertigkeit_neu.push_front(MBE);
      }
     if ((*MBE)->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return;
     MyList     = &hauptfenster->getChar()->List_Fertigkeit(); MyList_neu = &list_Fertigkeit_neu;
   }
 else if((*MBE)->What()==MidgardBasicElement::WAFFE) 
   { MyList     = &hauptfenster->getChar()->List_Waffen(); 
     MyList_neu = &list_Waffen_neu;  
   }
 else if((*MBE)->What()==MidgardBasicElement::WAFFEGRUND) 
   { MyList     = &hauptfenster->getChar()->List_WaffenGrund(); MyList_neu = &list_WaffenGrund_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::ZAUBER) 
  {
   { if((*MBE)->ZusatzEnum(hauptfenster->getChar()->getVTyp()))
      {  
        MBE=MBEmlt(new Zauber(*cH_Zauber(MBE->getMBE())));
        fillClistZusatz(MBE);
        // Davor stellen, damit beim Kopieren dieses MBE in Verschoben wird.
        list_Zauber_neu.push_front(MBE);
      }
   MyList     = &hauptfenster->getChar()->List_Zauber(); MyList_neu = &list_Zauber_neu;  }
  }
 else if((*MBE)->What()==MidgardBasicElement::ZAUBERWERK) 
   { MyList     = &hauptfenster->getChar()->List_Zauberwerk(); MyList_neu = &list_Zauberwerk_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::KIDO) 
   { MyList     = &hauptfenster->getChar()->List_Kido(); MyList_neu = &list_Kido_neu;  }
 else if((*MBE)->What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &hauptfenster->getChar()->List_Sprache(); MyList_neu = &list_Sprache_neu;  
     // eventuell höherer Erfolgswert weil die Sprache schon ungelernt beherrscht wird)
     int ungelernterErfolgswert=cH_Sprache(MBE->getMBE())->getHoeherenErfolgswert(hauptfenster->getChar()->List_Sprache(),hauptfenster->getCDatabase().Sprache);
     if (ungelernterErfolgswert) MBE->setErfolgswert(ungelernterErfolgswert);
     // bis hier
   }
 else if((*MBE)->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &hauptfenster->getChar()->List_Schrift(); MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");


//cout << "Move "<<MyList_neu->size()<<' '<<MyList->size()<<'\n';

 Abenteurer::move_element(*MyList_neu,*MyList,MBE);
 hauptfenster->undosave((*MBE)->Name()+" gelernt");

//cout << "Move "<<MyList_neu->size()<<' '<<MyList->size()<<'\n';
}

