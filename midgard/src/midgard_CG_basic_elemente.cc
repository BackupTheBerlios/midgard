#include "midgard_CG.hh"

void midgard_CG::MidgardBasicElement_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe,const std::list<cH_MidgardBasicElement>& mbe2)
{
  button_beruf_erfolgswert->set_sensitive(true); // falls Lernpunkte für Beruf nicht reichten
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
    list_Beruf.push_back(mbe);
    Database.ausnahmen.set_Beruf(list_Beruf);
    show_berufe();
    hbox_fertigkeit->set_sensitive(true); 
    table_fertigkeit->set_sensitive(true);
   }
  if(mbe->What()==MidgardBasicElement::SPRACHE)
   {
    list_Sprache.push_back(mbe);
   }
  if(mbe->What()==MidgardBasicElement::SCHRIFT)
   {
    list_Schrift.push_back(mbe);
   }
}
