#include "MidgardBasicElement.hh"
#include "class_typen.hh"


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

        