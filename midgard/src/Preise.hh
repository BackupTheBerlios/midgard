#ifndef PREISECLASS
#define PREISECLASS
#include <gtk--/progressbar.h>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include<string>
#include<vector>
#include<list>

class Preise : public HandleContent
{
   std::string name,einheit,art;
   float kosten;

   void get_Preise();
 public:
   Preise(const std::string& n)
     :name(n) {get_Preise();}

 std::string Art() const {  return art; }
 std::string Name()  const {  return name; }
 float Kosten() const { return kosten ; }
 std::string Einheit()  const {  return einheit; }
};




class cH_Preise : public Handle<const Preise>
{
    typedef CacheStatic<std::string,cH_Preise> cache_t;
    static cache_t cache;
    cH_Preise(Preise *s) : Handle<const Preise>(s) {};
    friend class std::map<std::string,cH_Preise>;
    cH_Preise(){};
 public:
    cH_Preise(const std::string& name);

 class sort {
      public:
         enum esort {NAME,ART};
      private: 
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Preise x,cH_Preise y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(ART)   : return x->Art() < y->Art() ;
           }}
    };
};

class Preise_All
{
   std::list<cH_Preise> list_All;
  public:
   Preise_All(Gtk::ProgressBar *progressbar);
   std::list<cH_Preise> get_All() const {return list_All;}
};

///////////////////////////////////

class PreiseMod : public HandleContent
{
 public: 
   struct st_vec{std::string name; std::string einheit;
                 float faktor; int min;
          st_vec() : faktor(0),min(0){}
          st_vec(std::string n, std::string e,
                 float f, int m) 
             : name(n), einheit(e), faktor(f), min(m) {}
          };
 private:
   std::string art;
   vector<st_vec> vec;
   std::map<std::string,vector<st_vec> > map_mod;

   void get_PreiseMod();
 public:
   PreiseMod(const std::string& a)
     :art(a) {get_PreiseMod();}

 std::string Art() const {  return art; }
// vector<st_vec> getVec() const {return vec_mod;}
 std::map<std::string,vector<st_vec> > getMap() const {return map_mod;}
 
};




class cH_PreiseMod : public Handle<const PreiseMod>
{
    typedef CacheStatic<std::string,cH_PreiseMod> cache_t;
    static cache_t cache;
    cH_PreiseMod(PreiseMod *s) : Handle<const PreiseMod>(s) {};
    friend class std::map<std::string,cH_PreiseMod>;
    cH_PreiseMod(){};
 public:
    cH_PreiseMod(const std::string& name);

};

class PreiseMod_All
{
   std::list<cH_PreiseMod> list_All;
  public:
   PreiseMod_All(Gtk::ProgressBar *progressbar);
   std::list<cH_PreiseMod> get_All() const {return list_All;}
};



#endif
