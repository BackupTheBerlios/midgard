#ifndef CLASS_AUSRUESTUNG
#define CLASS_AUSRUESTUNG

#include <string>
#include <map>
#include <list>

class AusruestungBaum;

class Ausruestung
{
     std::string name, material;
     bool sichtbar;

   public:
     Ausruestung() : sichtbar(false) {}

     Ausruestung(std::string n) 
       : name(n), sichtbar(true) {}
     Ausruestung(std::string n,std::string ma,bool s)
         :name(n),material(ma),sichtbar(s) {}

//     bool operator==(const Ausruestung& b) const
//         {return name==b.name && material==b.material;}
     
     std::string Name() const {return name;}
     std::string Material() const {return material;}
     bool Sichtbar() const {return sichtbar;}
     std::string SichtbarStr() const {if(sichtbar) return "*"; else return "";}

     void setSichtbar(bool s) {sichtbar=s;}
};

class AusruestungBaum
{
      std::list<AusruestungBaum> child;
      Ausruestung ausruestung;

      typedef list<AusruestungBaum>::const_iterator const_iterator;

   public:
      AusruestungBaum()  {}
      AusruestungBaum(const Ausruestung& a): ausruestung(a) {}
      
      AusruestungBaum &push_back(const Ausruestung& a)
          { child.push_back(a); return child.back(); }

      Ausruestung getAusruestung() const {return ausruestung;}
      const std::list<AusruestungBaum> &getChildren() const {return child;}

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
