#ifndef MIDGARDBASIC
#define MIDGARDBASIC
#include <Aux/Handles.h>
#include <string>

class MidgardBasic : public HandleContent
{
      virtual std::string Name() const=0;
      virtual std::string Wert() const=0;
      virtual std::string Region() const {return "";}
      virtual std::string What() const=0;
};

class cH_MidgardBasic : public Handle<const MidgardBasic>
{
   public:
      cH_MidgardBasic(const MidgardBasic *r) 
            : Handle<const MidgardBasic>(r){}
};

#endif