#include "midgard_CG.hh"
#include "class_SimpleTree.hh"


bool midgard_CG::MidgardBasicElement_leaf_alt(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();
 if(radiobutton_pp_eingeben->get_active()) 
  {
   spinbutton_pp_eingeben->set_value(MBE->Praxispunkte());
   spinbutton_pp_eingeben->show();
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
   { if (cH_Sprache(MBE)->Maxwert()==MBE->Erfolgswert() ) return false;
     MyList     = &list_Sprache; MyList_neu = &list_Sprache_neu;  }
 else if(MBE->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &list_Schrift; MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");

 //////////////////////////////////////////////////////////////////////////

 if (radiobutton_steigern->get_active() && MBE->Steigern(Typ,Database.ausnahmen))
    {
      if (!steigern_usp(MBE->Steigern(Typ,Database.ausnahmen),&MBE)) return false;
      if (MBE->What()==MidgardBasicElement::WAFFE &&
          MBE->Erfolgswert() >=  cH_Waffe(MBE)->Maxwert(Typ)) 
          { regnot("Maximal möglicher Erfolgswert erreicht");
            return false; }
      Werte.add_GFP(MBE->Steigern(Typ,Database.ausnahmen));
      for (std::list<cH_MidgardBasicElement>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i)->Name() == MBE->Name()) 
            (*i)->add_Erfolgswert(1); 
    }
 if (radiobutton_reduzieren->get_active() && MBE->Reduzieren(Typ,Database.ausnahmen))
    {
      if (steigern_bool) desteigern(MBE->Reduzieren(Typ,Database.ausnahmen));
      Werte.add_GFP(-MBE->Reduzieren(Typ,Database.ausnahmen));
      for (std::list<cH_MidgardBasicElement>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( (*i)->Name() == MBE->Name())  
            (*i)->add_Erfolgswert(-1); 
    }
 if (radiobutton_verlernen->get_active() && MBE->Verlernen(Typ,Database.ausnahmen))
    {
      guint verlernen = MBE->Verlernen(Typ,Database.ausnahmen);
      if( MBE->What()==MidgardBasicElement::ZAUBER && 
          togglebutton_spruchrolle->get_active() )    verlernen/=5  ;
      if (steigern_bool) desteigern(verlernen);
      Werte.add_GFP(-verlernen);
      MidgardBasicElement::move_element(*MyList,*MyList_neu,MBE->Name());
    }
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
 // Nicht alle Charakterklassen können Zauber auch mit Praxispunkten lernen
 if(MBE->What()==MidgardBasicElement::ZAUBER &&
     radiobutton_praxis->get_active() )
   {
     if(!Typ[0]->SpruecheMitPP() || !Typ[1]->SpruecheMitPP() )
        {
          regnot("Neue Zaubersprüche können von "+Typ[0]->Name(Werte.Geschlecht())
                  +" nicht durch Praxispunkte gelernt werden");
          return;
        }
      else if(MBE->Standard__(Typ,Database.ausnahmen)!="G")
        {
          regnot("Nur Grundzauber können von "+Typ[0]->Name(Werte.Geschlecht())
                  +" mit Praxispunkten gelernt werden");
          return;
        }
   }

 guint kosten=MBE->Kosten(Typ,Database.ausnahmen);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() ) kosten/=10;
 /////////////////////////////////////////////////////////////////////////
 
 if (!steigern_usp(kosten,&MBE)) return;
 Werte.add_GFP(kosten);

 // Lernen mit Spruchrolle: ///////////////////////////////////////////////
 if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_auto->get_active() )    Werte.add_GFP(kosten);
 else if( MBE->What()==MidgardBasicElement::ZAUBER &&
     togglebutton_spruchrolle->get_active() &&
     radio_spruchrolle_wuerfeln->get_active() )   
   {
     if(!spruchrolle_wuerfeln(MBE)) return;
     else Werte.add_GFP(kosten);
   } 
 /////////////////////////////////////////////////////////////////////////

 std::list<cH_MidgardBasicElement> *MyList,*MyList_neu;
 if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
   { 
     if(MBE->Name()=="Landeskunde") fillClistLand(MBE);
     if (MBE->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return;
     MyList     = &list_Fertigkeit; MyList_neu = &list_Fertigkeit_neu;
   }
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

//cout << MBE->What()<<' '<<MyList_neu->size()<<' '<<MyList->size()<<' '<<MBE->Name()<<'\n';
 if(MBE->What()!=MidgardBasicElement::ZAUBERWERK)
    MidgardBasicElement::move_element(*MyList_neu,*MyList,MBE->Name());
 else
    MidgardBasicElement::move_element(*MyList_neu,*MyList,MBE->Name(),cH_Zauberwerk(MBE)->Art());
//cout << MBE->What()<<' '<<MyList_neu->size()<<' '<<MyList->size()<<' '<<MBE->Name()<<'\n';
}


void midgard_CG::MidgardBasicElement_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe,const std::list<cH_MidgardBasicElement>& mbe2)
{
//  button_beruf_erfolgswert->set_sensitive(true); // falls Lernpunkte für Beruf nicht reichten
  if(mbe.begin()==mbe.end()) return;
/*
  if((*mbe.begin())->What()==MidgardBasicElement::BERUF)
   {
    list_Beruf=mbe;
    Database.ausnahmen.set_Beruf(list_Beruf);
    show_berufe();
//    button_beruf_erfolgswert->set_sensitive(true);
   }
*/
  if((*mbe.begin())->What()==MidgardBasicElement::FERTIGKEIT)
   {
    if(list_Fertigkeit.empty()) // wg. Fertigkeit durch Beruf
      list_Fertigkeit=mbe;
    else 
      list_Fertigkeit.splice(list_Fertigkeit.end(),const_cast<std::list<cH_MidgardBasicElement>& >(mbe));
    maxkido=0;  if (Typ[0]->Short()=="Kd") maxkido=2;
    int KD_tech=0;
    for(std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i)
      {
         cH_Fertigkeit f(*i);
         int bonus = f->AttributBonus(Werte);
         f->set_Erfolgswert( f->Erfolgswert() + bonus);     
         if (f->Name()=="KiDo") {kido_bool=true; show_gtk();}  
         if (f->Name()=="KiDo-Technik") { ++KD_tech;++maxkido;}
      }
    for (int j=0;j<KD_tech;++j)
      for(std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i)
       if (cH_Fertigkeit(*i)->Name()=="KiDo-Technik") {list_Fertigkeit.erase(i);break;}
    show_fertigkeiten();
    hbox_waffen->set_sensitive(true);
    table_waffen->set_sensitive(true);
   }
  if((*mbe.begin())->What()==MidgardBasicElement::WAFFE)
   {
    list_Waffen=mbe;
    list_WaffenGrund=mbe2;
    show_waffen();
    button_geld_waffen->set_sensitive(true);
    button_ruestung->set_sensitive(true);
         
    hbox_zauber->set_sensitive(true);
    table_magier_lernen->set_sensitive(true);
    hbox_kido->set_sensitive(true);
    table_kido_lernen->set_sensitive(true);
   }
  if((*mbe.begin())->What()==MidgardBasicElement::ZAUBER)
   {
    list_Zauber=mbe;
    angeborene_zauber();
    show_zauber();
   }
//cout << (*mbe.begin())->What()<<'\t'<<MidgardBasicElement::KIDO<<'\n';
  if((*mbe.begin())->What()==MidgardBasicElement::KIDO)
   {
    clist_kido->clear();
    list_Kido=mbe;
    show_kido();
   }
}

void midgard_CG::MidgardBasicElement_uebernehmen(const cH_MidgardBasicElement& mbe)
{
  if(mbe->What()==MidgardBasicElement::BERUF)
   {
    list_Beruf.clear(); // es kann nur einen Beruf geben 
    list_Beruf.push_back(mbe);
    Database.ausnahmen.set_Beruf(list_Beruf);
    show_berufe();
    hbox_fertigkeit->set_sensitive(true); 
    table_fertigkeit->set_sensitive(true);
   }
  if(mbe->What()==MidgardBasicElement::FERTIGKEIT)
   {
    list_Fertigkeit.push_back(mbe);
    show_fertigkeiten();
   }
  if(mbe->What()==MidgardBasicElement::SPRACHE)
   {
    list_Sprache.push_back(mbe);
   }
  if(mbe->What()==MidgardBasicElement::SCHRIFT)
   {
    list_Schrift.push_back(mbe);
    show_fertigkeiten();
   }
}
