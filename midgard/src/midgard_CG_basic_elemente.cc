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

#include "midgard_CG.hh"
#include "class_SimpleTree.hh"
#include "Fertigkeiten.hh"
#include "Zauber.hh"
#include <Aux/itos.h>

bool midgard_CG::MidgardBasicElement_leaf_alt(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();
 if(togglebutton_praxispunkte->get_active()) 
  {
   spinbutton_pp_eingeben->set_value(MBE->Praxispunkte());
   spinbutton_pp_eingeben->show();
   spinbutton_pp_eingeben->grab_focus();
   return false;
  }

 ////////////////////////////////////////////////////////////////////////
 std::list<cH_MidgardBasicElement> *MyList,*MyList_neu;
 if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
   { if (MBE->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return false;
     MyList     = &list_Fertigkeit; MyList_neu = &list_Fertigkeit_neu;   }
 else if(MBE->What()==MidgardBasicElement::WAFFE) 
   { MyList     = &list_Waffen; MyList_neu = &list_Waffen_neu;  }
 else if(MBE->What()==MidgardBasicElement::WAFFEGRUND) 
   { MyList     = &list_WaffenGrund; MyList_neu = &list_WaffenGrund_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBER) 
   { MyList     = &list_Zauber; MyList_neu = &list_Zauber_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBERWERK) 
   { MyList     = &list_Zauberwerk; MyList_neu = &list_Zauberwerk_neu;  }
 else if(MBE->What()==MidgardBasicElement::KIDO) 
   { MyList     = &list_Kido; MyList_neu = &list_Kido_neu;  }
 else if(MBE->What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &list_Sprache; MyList_neu = &list_Sprache_neu;  }
 else if(MBE->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &list_Schrift; MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");

 //////////////////////////////////////////////////////////////////////////

 if (radiobutton_steigern->get_active() && MBE->Steigern(Werte,Typ))
    {
      if (!steigern_usp(MBE->Steigern(Werte,Typ),&MBE)) return false;
      if ( MBE->Erfolgswert() >= MBE->MaxErfolgswert(Werte,Typ)) 
          { regnot("Maximal möglicher Erfolgswert erreicht");
            return false; }
      Werte.addGFP(MBE->Steigern(Werte,Typ));
      for (std::list<cH_MidgardBasicElement>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i)->Name() == MBE->Name()) 
            (*i)->addErfolgswert(1); 
    }
 else if (radiobutton_reduzieren->get_active() && MBE->Reduzieren(Werte,Typ))
    {
      if (checkbutton_EP_Geld->get_active()) desteigern(MBE->Reduzieren(Werte,Typ));
      Werte.addGFP(-MBE->Reduzieren(Werte,Typ));
      for (std::list<cH_MidgardBasicElement>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i)->Name() == MBE->Name())  
            (*i)->addErfolgswert(-1); 
    }
 else if (radiobutton_verlernen->get_active() && MBE->Verlernen(Werte,Typ))
    {
      guint verlernen = MBE->Verlernen(Werte,Typ);
      if( MBE->What()==MidgardBasicElement::ZAUBER && 
          togglebutton_spruchrolle->get_active() )    verlernen/=5  ;
      if (checkbutton_EP_Geld->get_active()) desteigern(verlernen);
      Werte.addGFP(-verlernen);
      MidgardBasicElement::move_element(*MyList,*MyList_neu,MBE);
    }
 else if (radiobutton_verlernen->get_active() && MBE->What()==MidgardBasicElement::WAFFE)
    {
      MidgardBasicElement::move_element(*MyList,*MyList_neu,MBE);
    }
 undosave(MBE->Name()+" auf "+itos(MBE->Erfolgswert())+" gesteigert");
 return true;
}


void midgard_CG::MidgardBasicElement_leaf_neu(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();
 // Neue Dinge können nur durch Unterweisung gelernt werden
 // es sei denn es handelt sich um Zaubersprüche
 if(!radiobutton_unterweisung->get_active() &&  
    MBE->What()==MidgardBasicElement::ZAUBER )
  {
    regnot("Neue Fertigkeiten können nur durch 'Unterweisung' gelernt werden");
    return;
  }
 // Nicht alle Abenteurerklassen können Zauber auch mit Praxispunkten lernen
 if(MBE->What()==MidgardBasicElement::ZAUBER &&
     radiobutton_praxis->get_active() )
   {
     if(!Typ[0]->SpruecheMitPP() || !Typ[1]->SpruecheMitPP() )
        {
          regnot("Neue Zaubersprüche können von "+Typ[0]->Name(Werte.Geschlecht())
                  +" nicht durch Praxispunkte gelernt werden");
          return;
        }
      else if(MBE->Standard__(Werte,Typ)!="G")
        {
          regnot("Nur Grundzauber können von "+Typ[0]->Name(Werte.Geschlecht())
                  +" mit Praxispunkten gelernt werden");
          return;
        }
   }

 guint kosten=MBE->Kosten(Werte,Typ);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() ) kosten/=10;
 /////////////////////////////////////////////////////////////////////////
 
 if (!steigern_usp(kosten,&MBE)) return;
 Werte.addGFP(kosten);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_auto->get_active() )    Werte.addGFP(kosten);
 else if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_wuerfeln->get_active() )   
   {
     if(!spruchrolle_wuerfeln(MBE)) return;
     else Werte.addGFP(kosten);
   } 
 /////////////////////////////////////////////////////////////////////////

 std::list<cH_MidgardBasicElement> *MyList,*MyList_neu;
 if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
   { if(MBE->ZusatzEnum(Typ))
      {  
        neue_fert_tree->set_sensitive(false);
        MBE=new Fertigkeit(*cH_Fertigkeit(MBE));
        fillClistLand(MBE);
        // Davor stellen, damit beim Kopieren dieses MBE in Verschoben wird.
        list_Fertigkeit_neu.push_front(MBE);
      }
     if (MBE->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return;
     MyList     = &list_Fertigkeit; MyList_neu = &list_Fertigkeit_neu;
   }
 else if(MBE->What()==MidgardBasicElement::WAFFE) 
   { MyList     = &list_Waffen; MyList_neu = &list_Waffen_neu;  }
 else if(MBE->What()==MidgardBasicElement::WAFFEGRUND) 
   { MyList     = &list_WaffenGrund; MyList_neu = &list_WaffenGrund_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBER) 
  {
   { if(MBE->ZusatzEnum(Typ))
      {  
        MBE=new Zauber(*cH_Zauber(MBE));
        fillClistLand(MBE);
        // Davor stellen, damit beim Kopieren dieses MBE in Verschoben wird.
        list_Zauber_neu.push_front(MBE);
      }
   MyList     = &list_Zauber; MyList_neu = &list_Zauber_neu;  }
  }
 else if(MBE->What()==MidgardBasicElement::ZAUBERWERK) 
   { MyList     = &list_Zauberwerk; MyList_neu = &list_Zauberwerk_neu;  }
 else if(MBE->What()==MidgardBasicElement::KIDO) 
   { MyList     = &list_Kido; MyList_neu = &list_Kido_neu;  }
 else if(MBE->What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &list_Sprache; MyList_neu = &list_Sprache_neu;  }
 else if(MBE->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &list_Schrift; MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");

//cout << "Move "<<MyList_neu->size()<<' '<<MyList->size()<<'\n';
 MidgardBasicElement::move_element(*MyList_neu,*MyList,MBE);
 undosave(MBE->Name()+" gelernt");

//cout << "Move "<<MyList_neu->size()<<' '<<MyList->size()<<'\n';
}


void midgard_CG::MidgardBasicElement_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe,const std::list<cH_MidgardBasicElement>& mbe2)
{
  if(mbe.begin()==mbe.end()) return;
  if((*mbe.begin())->What()==MidgardBasicElement::WAFFEBESITZ)
   {
    list_Waffen_besitz=mbe;
   }
  else if((*mbe.begin())->What()==MidgardBasicElement::KIDO)
   {
    list_Kido=mbe;
   }
  else assert(0);
  undosave(itos(mbe.size())+" "+(*mbe.begin())->What_str()+"n übernommen");
  show_gelerntes();
}

