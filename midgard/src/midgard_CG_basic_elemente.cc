#include "midgard_CG.hh"
#include "class_SimpleTree.hh"


void midgard_CG::MidgardBasicElement_leaf_alt(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();
 if(radiobutton_pp_eingeben->get_active()) 
  {
   spinbutton_pp_eingeben->set_value(MBE->Praxispunkte());
   spinbutton_pp_eingeben->show();
   return;
  }

 std::list<cH_MidgardBasicElement> *MyList,*MyList_neu;
 if(MBE->What()==MidgardBasicElement::FERTIGKEIT) 
   { if (MBE->Name()=="KiDo" && kido_steigern_check(MBE->Erfolgswert())) return;
     MyList     = &list_Fertigkeit; MyList_neu = &list_Fertigkeit_neu;   }
 else if(MBE->What()==MidgardBasicElement::WAFFE) 
   { MyList     = &list_Waffen; MyList_neu = &list_Waffen_neu;  }
 else if(MBE->What()==MidgardBasicElement::WAFFEGRUND) 
   { MyList     = &list_WaffenGrund; MyList_neu = &list_WaffenGrund_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBER) 
   { MyList     = &list_Zauber; MyList_neu = &list_Zauber_neu;  }
 else if(MBE->What()==MidgardBasicElement::ZAUBERWERK) 
   { MyList     = &list_Zauberwerk; MyList_neu = &list_Zauberwerk_neu;  }
 else if(MBE->What()==MidgardBasicElement::SPRACHE) 
   { if (cH_Sprache(MBE)->Maxwert()==MBE->Erfolgswert() ) return;
     MyList     = &list_Sprache; MyList_neu = &list_Sprache_neu;  }
 else if(MBE->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &list_Schrift; MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");

 if (radiobutton_steigern->get_active() && MBE->Steigern(Typ,Database.ausnahmen))
    {
      if (!steigern_usp(MBE->Steigern(Typ,Database.ausnahmen),&MBE)) return;
      Werte.add_GFP(MBE->Steigern(Typ,Database.ausnahmen));
      for (std::list<cH_MidgardBasicElement>::iterator i=(*MyList).begin();i!= (*MyList).end();++i )
         if ( cH_Fertigkeit(*i)->Name() == MBE->Name()) 
           cH_Fertigkeit(*i)->add_Erfolgswert(1); 
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
      if (steigern_bool) desteigern(MBE->Verlernen(Typ,Database.ausnahmen));
      Werte.add_GFP(-MBE->Verlernen(Typ,Database.ausnahmen));
      MidgardBasicElement::move_element(*MyList,*MyList_neu,MBE->Name());
    }
}


void midgard_CG::MidgardBasicElement_leaf_neu(const cH_RowDataBase &d)
{
 const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
 cH_MidgardBasicElement MBE = dt->getMBE();

 if (!steigern_usp(MBE->Kosten(Typ,Database.ausnahmen),&MBE)) return;
 Werte.add_GFP(MBE->Kosten(Typ,Database.ausnahmen));

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
 else if(MBE->What()==MidgardBasicElement::SPRACHE) 
   { MyList     = &list_Sprache; MyList_neu = &list_Sprache_neu;  }
 else if(MBE->What()==MidgardBasicElement::SCHRIFT) 
   { MyList     = &list_Schrift; MyList_neu = &list_Schrift_neu;  }
 else assert(!"Fehler (alt) in midgard_CG_basic_elemente.cc");

 MidgardBasicElement::move_element(*MyList_neu,*MyList,MBE->Name());
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
