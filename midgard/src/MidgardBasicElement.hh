#ifndef MIDGARDBASICELEMENT
#define MIDGARDBASICELEMENT
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <string>
#include <vector>
#include <list>

class cH_Typen;
class Grundwerte;
class Ausnahmen;
class H_Data_beruf;
class cH_MidgardBasicElement;
class SimpleTree;



class MidgardBasicElement : public HandleContent
{
   protected:
      int kosten;
      int mutable erfolgswert,lernpunkte;
      int steigern_mit_EP; //1=KEP,2=ZEP,3=Beides
      std::map<std::string,std::string> map_typ;
      std::map<int,int> map_erfolgswert_kosten;
      void get_map_typ();
      void get_Steigern_Kosten_map();
      vector<std::string> Standard(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const; 
      int GrundKosten() const {  return kosten; }


   public:
      MidgardBasicElement() : kosten(0),erfolgswert(0),lernpunkte(0)
                              ,steigern_mit_EP(0) {}                              

      enum MBEE {BERUF,FERTIGKEIT,FERTIGKEIT_ANG,WAFFEGRUND,WAFFE,ZAUBER,
                  ZAUBERWERK,KIDO,SPRACHE,SCHRIFT} ;
      enum TREE {OLD,NEW};

      map<std::string,std::string> get_MapTyp() const {return map_typ;}
      
      void EP_steigern(const std::string fert);
      virtual std::string Name() const=0;
//      virtual int Erfolgswert(const vector<cH_Typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const {return 99;}
      int Lernpunkte() const {return lernpunkte;};
      void set_Lernpunkte(int l) const {lernpunkte=l;}
      int Erfolgswert() const {return erfolgswert;};
      void set_Erfolgswert(int e) const {erfolgswert=e;}
      void add_Erfolgswert(int e) const {erfolgswert+=e;}
      int Steigern_mit_EP() const {return steigern_mit_EP;}
      virtual std::string Region() const {return "";}
      virtual enum MBEE What() const=0;
      virtual std::string What_str() const=0; // zum speichern
      virtual std::string Stufe() const {return "";} 
      bool ist_lernbar(const vector<cH_Typen>& Typ,const map<std::string,std::string>& map_typ) const;
      bool ist_gelernt(const std::list<cH_MidgardBasicElement>& L) const;
      int get_Steigern_Kosten(int erfolgswert) const;
      std::string Standard__(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const;
      double Standard_Faktor(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const;
      int Kosten(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const 
         {return (int)(Standard_Faktor(Typ,ausnahmen)*GrundKosten());}
      int Steigern(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const; 
      int Reduzieren(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const;
      int Verlernen(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const; 
      bool standard_one_G(const vector<std::string>& s) const ;
      bool standard_all_S(const vector<std::string>& s) const ;
      bool operator == (const MidgardBasicElement& b) const 
         {return Name()==b.Name();}


      static void move_element(std::list<cH_MidgardBasicElement>& von,std::list<cH_MidgardBasicElement>& nach,const std::string& name);
      static void show_list_in_tree(
            const std::list<cH_MidgardBasicElement>& BasicList,
            SimpleTree *Tree, 
            const Grundwerte& Werte, const vector<cH_Typen>& Typ,
            const Ausnahmen& ausnahmen);
      static void saveElementliste(const std::list<cH_MidgardBasicElement>& b,
                                   const Grundwerte& Werte,
                                   const vector<cH_Typen>& Typ,
                                   const Ausnahmen& ausnahmen);

};

//MidgardBasicElement::TREE& operator++(MidgardBasicElement::TREE& t) {return t+1;}


class cH_MidgardBasicElement : public Handle<const MidgardBasicElement>
{
      typedef CacheStatic<std::string,cH_MidgardBasicElement> cache_t;
      static cache_t cache;
      friend class std::map<std::string,cH_MidgardBasicElement>;
      cH_MidgardBasicElement(){}
   public:
//      cH_MidgardBasicElement(){*this=new MidgardBasicElement();}
      cH_MidgardBasicElement(const MidgardBasicElement *r) 
            : Handle<const MidgardBasicElement>(r){}
//      bool operator== (const cH_MidgardBasicElement b) 
//         {return b==(*this);)

   class sort {
      public:
         enum esort {LERNPUNKTE,NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_MidgardBasicElement x,cH_MidgardBasicElement y) const
           { switch(es) {
               case(LERNPUNKTE) : return x->Lernpunkte() < y->Lernpunkte()  ;
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x->Erfolgswert() > y->Erfolgswert();
           }}
    };

};
   

#endif
