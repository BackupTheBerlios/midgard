/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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
      // wieso ist das const ? wenn unten eine nicht const funktion existiert
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
      // reicht der hier nicht? CP
      // AusruestungBaum *getParent() {return parent;}
      // dann könnte man :
      // const AusruestungBaum *getParent() const {return parent;}
      void setParent(AusruestungBaum *p) {parent=p;}

      const std::list<AusruestungBaum> &getChildren() const {return child;}
      std::list<AusruestungBaum> &getChildren() {return child;}

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
