#include "MidgardBasicElement.hh"
#include "class_typen.hh"
#include "class_Grundwerte.hh"
#include "Fertigkeiten.hh"
#include "KiDo.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "Sprache.hh"
#include "Schrift.hh"
#include "class_kido.hh"
#include "class_zauber.hh"
#include "class_fertigkeiten.hh"
#include "class_sprache_schrift.hh"
#include "Ausnahmen.hh"
#include "SimpleTree.hh"

/*
cH_MidgardBasicElement::cache_t cH_MidgardBasicElement::cache;

cH_MidgardBasicElement::cH_MidgardBasicElement(const std::string& name)
{
 cH_MidgardBasicElement *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
   *this=cH_MidgardBasicElement(new MidgardBasicElement(name));
   cache.Register(name,*this);
  }
}
*/

void MidgardBasicElement::show_list_in_tree(
  const std::list<cH_MidgardBasicElement>& BasicList,
  SimpleTree *Tree,
  const Grundwerte& Werte, 
  const vector<H_Data_typen>& Typ, const Ausnahmen& ausnahmen,
  char variante, bool _bool_)
{
  if (BasicList.begin()==BasicList.end() ) return ;
  std::vector<cH_RowDataBase> datavec;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=BasicList.begin();i!=BasicList.end();++i)
   {
    switch((*BasicList.begin())->What())
     {
       case(FERTIGKEIT) : {cH_Fertigkeit f(*i);
         if(variante=='O')  
            datavec.push_back(new Data_fert(f->Name(),f->Erfolgswert(),f->Steigern(Typ,ausnahmen),f->Reduzieren(Typ,ausnahmen),f->Verlernen(Typ,ausnahmen)));
         if(variante=='N')  
            datavec.push_back(new Data_fert(f->Name(),f->Anfangswert(),f->Kosten(Typ,ausnahmen),f->Standard__(Typ,ausnahmen),f->Voraussetzung()));
         break; }
       case(WAFFEN)      : break;
       case(ZAUBER)      : {cH_Zauber z(*i);
          if (!_bool_ || (_bool_ &&  z->Spruchrolle())) 
           {int kosten=z->Kosten(Typ,ausnahmen);
            if(_bool_) kosten/=10; 
              datavec.push_back(new Data_zauber(z->Name(),z->Stufe(),z->Ursprung(),kosten,z->Standard__(Typ,ausnahmen)));   
           }
          break; }
       case(ZAUBERWERK)  : {cH_Zauberwerk z(*i); 
          if(variante=='O')  
              { if(_bool_) continue;
                datavec.push_back(new Data_zaubermittel(z->Stufe(),z->Name(),z->Art(),z->Kosten(Typ)));
              }
          if(variante=='N')
                datavec.push_back(new Data_zaubermittel(z->Stufe(),z->Name(),z->Art(),z->Kosten(Typ),z->Preis(),z->Zeitaufwand()));
          break; }
       case(KIDO)        : {cH_KiDo kd(*i);
               datavec.push_back(new Data_kido(kd->Hoho(),kd->Name(),kd->Stufe(),
                  kd->Ap(),kd->Kosten(Typ,ausnahmen),kd->Stil()));
          break; }
         case(SPRACHE)     : {cH_Sprache s(*i);
             if(variante=='O')
               datavec.push_back(new Data_sprache(s->Name(),s->Erfolgswert(),s->Steigern(Typ,ausnahmen),s->Reduzieren(Typ,ausnahmen),s->Verlernen(Typ,ausnahmen)));
             if(variante=='N')
               datavec.push_back(new Data_sprache(s->Name(),s->Urschrift(),0,s->Kosten(Typ,ausnahmen)));
          break; }
         case(SCHRIFT)     : {cH_Schrift s(*i);
               datavec.push_back(new Data_schrift(s->Name(),s->Art_der_Schrift(),s->Kosten(Typ,ausnahmen)));
          break; }
      }
   }
    Tree->setDataVec(datavec);
}

void MidgardBasicElement::move_element(std::list<cH_MidgardBasicElement>& von,std::list<cH_MidgardBasicElement>& nach,const std::string& name)
{
 for (std::list<cH_MidgardBasicElement>::iterator i=von.begin();i!= von.end();++i)
   if ((*i)->Name()==name) 
     { nach.splice(nach.begin(),von,i);break; }
}

bool MidgardBasicElement::ist_lernbar(const vector<H_Data_typen>& Typ,const map<std::string,std::string>& map_typ) const
{
  for (std::vector<H_Data_typen>::const_iterator i=Typ.begin();i!=Typ.end();++i)
    if (const_cast<map<std::string,std::string>& >(map_typ)[(*i)->Short()]!="") 
      return true;
  return false;
}

bool MidgardBasicElement::ist_gelernt(const std::list<cH_MidgardBasicElement>& L) const
{
 for (std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
   if((*i)->Name()==Name()) return true;
 return false;
}

        