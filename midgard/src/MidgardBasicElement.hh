#ifndef MIDGARDBASICELEMENT
#define MIDGARDBASICELEMENT
#include <Aux/Handles.h>
#include <string>
#include <vector>
class H_Data_typen;
class Grundwerte;
class Ausnahmen;

class MidgardBasicElement : public HandleContent
{
      virtual std::string Name() const=0;
      virtual int Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const=0;
      virtual std::string Region() const=0; //const {return "";}
      virtual std::string What() const=0;
};

class cH_MidgardBasicElement : public Handle<const MidgardBasicElement>
{
   public:
      cH_MidgardBasicElement(const MidgardBasicElement *r) 
            : Handle<const MidgardBasicElement>(r){}
};

#endif
