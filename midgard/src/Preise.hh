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
   double kosten,gewicht;

   void get_Preise();
 public:
   Preise(const std::string& n)
     :name(n) {get_Preise();}

 std::string Art() const {  return art; }
 std::string Name()  const {  return name; }
 double Kosten() const { return kosten ; }
 double Gewicht() const { return gewicht ; }
 std::string Einheit()  const {  return einheit; }

 static void saveArtikel(std::string art,std::string name,double preis, std::string einheit,double gewicht);
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
   struct st_payload{std::string name; double faktor;
          st_payload() : faktor(0) {}
          st_payload(std::string n, double f) 
             : name(n), faktor(f) {}
          };
 private:
   std::string art,typ;
   int nr;
   st_payload payload;
   void get_PreiseMod();
 public:
   PreiseMod(const std::string& a,const std::string& t,const int& n)
     :art(a),typ(t),nr(n) {get_PreiseMod();}

 std::string Art() const {  return art; }
 std::string Typ() const {  return typ; }
 int Nr() const {  return nr; }
 st_payload Payload() const {return payload;}

// static saveGruppe(std::string art,int typ, std::string eigenschaft);
};

class cH_PreiseMod : public Handle<const PreiseMod>
{
   struct st_index{std::string art; std::string typ;int nr;
          st_index() :nr(0) {}
          st_index(std::string a,std::string t,int n) : art(a),typ(t),nr(n) {}
          bool operator<(const st_index& b) const
            {return art<b.art || (art==b.art && typ<b.typ)
                    ||(art==b.art &&typ==b.typ&&nr<b.nr) ;}          
         };

    typedef CacheStatic<st_index,cH_PreiseMod> cache_t;
    static cache_t cache;
    cH_PreiseMod(PreiseMod *s) : Handle<const PreiseMod>(s) {};
    friend class std::map<st_index,cH_PreiseMod>;
    cH_PreiseMod(){};
 public:
    cH_PreiseMod(const std::string& art,const std::string typ,const int &nr);
};

class PreiseMod_All
{
   std::list<cH_PreiseMod> list_All;
  public:
   PreiseMod_All(Gtk::ProgressBar *progressbar);
   std::list<cH_PreiseMod> get_All() const {return list_All;}
};



#endif
