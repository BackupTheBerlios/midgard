#ifndef MIDGARDBASICELEMENT
#define MIDGARDBASICELEMENT
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <string>
#include <vector>
class H_Data_typen;
class Grundwerte;
class Ausnahmen;
//class cH_Zauber;

class MidgardBasicElement : public HandleContent
{
   public:

      virtual std::string Name() const=0;
      virtual int Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const=0;
      virtual std::string Region() const=0; //const {return "";}
      virtual std::string What() const=0;

};

class cH_MidgardBasicElement : public Handle<const MidgardBasicElement>
{
      typedef CacheStatic<std::string,cH_MidgardBasicElement> cache_t;
      static cache_t cache;
      cH_MidgardBasicElement(MidgardBasicElement *s) : Handle<const MidgardBasicElement>(s) {};
      friend class std::map<std::string,cH_MidgardBasicElement>;
      cH_MidgardBasicElement(){}
   public:
//        cH_MidgardBasicElement(const std::string& name);
//      cH_MidgardBasicElement(const MidgardBasicElement *r) 
//            : Handle<const MidgardBasicElement>(r){}

//      cH_MidgardBasicElement(const cH_Zauber *r) 
//            : Handle<const cH_Zauber>(r){}

//      const std::list<cH_MidgardBasicElement>& (cH_Zauber(std::string n));
};

#endif
