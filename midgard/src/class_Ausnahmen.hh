#ifndef _CLASS_AUSNAHMEN_HH
#  define _CLASS_AUSNAHMEN_HH


#include <Aux/Handles.h>
#include <vector.h>
#include <Aux/CacheStatic.h>
#include "class_typen.hh"

class Grundwerte;
class H_Data_beruf;
class Data_typen;

class Data_Ausnahmen : public HandleContent
{
   std::string name, art, standard;
   double fac;

public:
   Data_Ausnahmen(std::string nn, std::string aa, float ff, std::string ss)
         :name(nn), art(aa), standard(ss), fac(ff) {}

   std::string Name() const {return name;}
//   std::string Art() const {return art;}
   std::string Standard() const {return standard;}
   double Fac() const {return fac;}

};

class cH_Data_Ausnahmen : public Handle<const Data_Ausnahmen>    
{
protected:
 cH_Data_Ausnahmen() {}
public:
 cH_Data_Ausnahmen(Data_Ausnahmen *r) : Handle<const Data_Ausnahmen>(r){}
};

class Ausnahmen : public cH_Data_Ausnahmen
{
   struct st_index {std::string name; std::string version;
       bool operator == (const st_index& b) const 
           {return (name==b.name && version==b.version);}
       bool operator <  (const st_index& b) const 
            {return name < b.name || (name==b.name && version < b.version );}
   st_index(std::string n, std::string v):name(n),version(v){}
   st_index(){}
      };

   vector<cH_Data_Ausnahmen> vec_Ausnahmen;

   typedef CacheStatic<st_index,vector<cH_Data_Ausnahmen> > cache_t;
   static cache_t cache;


 public:
   Ausnahmen(const Grundwerte& Werte,const vector<H_Data_typen>& Typ, 
      std::vector<H_Data_beruf>& vec_Beruf);

   static void clear(){cache.clear();}

//   vector<cH_Data_Ausnahmen> get_Ausnahmen() const {return vec_Ausnahmen;}
   float Ausnahmen_float(const std::string& name);
   std::string  Ausnahmen_string(const std::string& name, const std::string& alt,const std::string& alt2);
};

#endif
