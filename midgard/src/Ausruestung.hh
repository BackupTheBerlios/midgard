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

     bool operator==(const Ausruestung& b) const
         {return name==b.name && material==b.material;}
     
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
      const AusruestungBaum *parent;

      typedef list<AusruestungBaum>::const_iterator const_iterator;
      typedef list<AusruestungBaum>::iterator iterator;




   public:
      AusruestungBaum()  {}
      AusruestungBaum(const Ausruestung& a) 
         : ausruestung(a),parent(0) {}
      
      AusruestungBaum &push_back(const Ausruestung& a)
          { child.push_back(a); return child.back(); }

      const Ausruestung &getAusruestung() const {return ausruestung;}
      AusruestungBaum *getParent() const {return const_cast<AusruestungBaum*>(parent);}
      void setParent(AusruestungBaum *p) {parent=p;}
      const std::list<AusruestungBaum> &getChildren() const {return child;}

      void remove(const AusruestungBaum &A) {child.remove(A);}
         
//         { for (std::list<AusruestungBaum>::iterator i=child.begin();i!=child.end();++i)
//            if( *i==A ) {child.remove(*i);break;}
//         }
      bool empty() const
          {  return child.empty(); }
      void clear() 
          {  return child.clear(); }
      size_t size() const
          {  return child.size(); }
      const_iterator begin() const
          {  return child.begin(); }
      const_iterator end() const
          {  return child.end(); }
      iterator begin() 
          {  return child.begin(); }
      iterator end() 
          {  return child.end(); }
     bool operator==(const AusruestungBaum& b) const
         {return getAusruestung()==b.getAusruestung();}


};

#endif
