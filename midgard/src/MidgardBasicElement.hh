#ifndef MIDGARDBASICELEMENT
#define MIDGARDBASICELEMENT
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <string>
#include <vector>
#include <list>

class H_Data_typen;
class Grundwerte;
class Ausnahmen;
//class cH_Zauber;
class cH_MidgardBasicElement;

class MidgardBasicElement : public HandleContent
{
   public:
      enum MBEE {FERTIGKEITE,WAFFEN,ZAUBER,KIDO,SPRACHE,SCHRIFT} ;

      virtual std::string Name() const=0;
      virtual int Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const {return 0;}
      virtual std::string Region() const {return "";}
      virtual enum MBEE What() const=0;

      virtual bool operator == (const MidgardBasicElement& b) const 
         {return Name()==b.Name();}

      saveElementliste(const std::list<cH_MidgardBasicElement>& b);

};

class cH_MidgardBasicElement : public Handle<const MidgardBasicElement>
{
      typedef CacheStatic<std::string,cH_MidgardBasicElement> cache_t;
      static cache_t cache;
//      cH_MidgardBasicElement(MidgardBasicElement *s) : Handle<const MidgardBasicElement>(s) {};
      friend class std::map<std::string,cH_MidgardBasicElement>;
      cH_MidgardBasicElement(){}
   public:
//        cH_MidgardBasicElement(const std::string& name);
      cH_MidgardBasicElement(const MidgardBasicElement *r) 
            : Handle<const MidgardBasicElement>(r){}
//      bool operator== (const cH_MidgardBasicElement b) 
//         {return b==(*this);)

//      cH_MidgardBasicElement(const cH_Zauber *r) 
//            : Handle<const cH_Zauber>(r){}

//      const std::list<cH_MidgardBasicElement>& (cH_Zauber(std::string n));


      static void move_element(std::list<cH_MidgardBasicElement>& von,std::list<cH_MidgardBasicElement>& nach,const std::string& name)
         { for (std::list<cH_MidgardBasicElement>::iterator i=von.begin();i!= von.end();++i)
              if ((*i)->Name()==name)
           {nach.splice(nach.begin(),von,i);break;}
         }
};
   

#endif
