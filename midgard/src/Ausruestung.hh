#ifndef CLASS_AUSRUESTUNG
#define CLASS_AUSRUESTUNG

#include <string>
#include <map>
#include <list>

class AusruestungBaum;

class Ausruestung
{
     std::string name, material;
//     AusruestungBaum *parent;
     bool sichtbar;

   public:
     Ausruestung() : sichtbar(false) {}
/*
     Ausruestung(std::string n,AusruestungBaum *p) 
       : name(n),parent(p), sichtbar(true) {}
     Ausruestung(std::string n,std::string ma,AusruestungBaum *p,
            std::string wo,bool s)
         :name(n), material(ma),parent(p),wobinich(wo),sichtbar(s) {}
*/
     Ausruestung(std::string n) 
       : name(n), sichtbar(true) {}
     Ausruestung(std::string n,std::string ma,bool s)
         :name(n),material(ma),sichtbar(s) {}

//     bool operator==(const Ausruestung& b) const
//         {return name==b.name && material==b.material;}
     
     std::string Name() const {return name;}
     std::string Material() const {return material;}
//     std::string Modi() const {return modi;}
//     std::string WoBinIch() const {return wobinich;}
//     AusruestungBaum Parent() const {return parent;}
     bool Sichtbar() const {return sichtbar;}

     void setSichtbar(bool s) {sichtbar=s;}
};

class AusruestungBaum
{
      std::list<AusruestungBaum> child;
      Ausruestung ausruestung;

      typedef list<AusruestungBaum>::const_iterator const_iterator;
//      typedef list<AusruestungBaum>::iterator iterator;

   public:
      AusruestungBaum()  {}
      AusruestungBaum(const Ausruestung& a): ausruestung(a) {}
      
      AusruestungBaum &push_back(const Ausruestung& a)
          { child.push_back(a); return child.back(); }

      Ausruestung getAusruestung() const {return ausruestung;}
      std::list<AusruestungBaum> getChildren() const {return child;}

//      void Rein(const Ausruestung& a) { ausmap[a.WoBinIch()].push_back(a); }
//      void Raus(const Ausruestung& a) { ausmap[a.WoBinIch()].remove(a); }

      bool empty() const
          {  return child.empty(); }
      size_t size() const
          {  return child.size(); }
      const_iterator begin() const
          {  return child.begin(); }
      const_iterator end() const
          {  return child.end(); }
};

#endif
