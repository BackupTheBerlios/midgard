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
#include "dtos1.h"

class midgard_CG;
class AusruestungBaum;

class Ausruestung
{
     std::string name;
     double gewicht;
     std::string material,region;
     bool sichtbar;
     bool ruestung_ohne_gewicht;

   public:
     Ausruestung() : gewicht(0), sichtbar(false),ruestung_ohne_gewicht(false) {}

     Ausruestung(std::string n) 
       : name(n), gewicht(0), sichtbar(true),ruestung_ohne_gewicht(false) {}
     Ausruestung(std::string n,double g,std::string ma,std::string r,bool s,bool ru)
         :name(n),gewicht(g),material(ma),region(r),sichtbar(s),ruestung_ohne_gewicht(ru) {}

     bool operator==(const Ausruestung& b) const
         {return name==b.name && material==b.material;}
     
     std::string Name() const {return name;}
     double Gewicht() const {return gewicht;}
     std::string SGewicht() const { std::string gewicht;
                                    if(Gewicht()!=0) gewicht= dtos1(Gewicht())+" kg";
                                    return gewicht;
                                  }
     std::string Region() const {return region;}
     std::string Material() const {return material;}
     bool Sichtbar() const {return sichtbar;}
     std::string SichtbarStr() const {if(sichtbar) return "*"; else return "";}
     void setSichtbar(bool s) {sichtbar=s;}
     bool RuestungOhneGewicht() const {return ruestung_ohne_gewicht;}

/*
     static void save(const std::string &filename,midgard_CG *hauptfenster,
                      const std::string &art,const std::string &art2,
                      const std::string &name,const double &gewicht,
                      const double &preis,const std::string &einheit);
*/
};

class AusruestungBaum
{
      std::list<AusruestungBaum> child;
      Ausruestung ausruestung;
      // wieso ist das const ? wenn unten eine nicht const funktion existiert
      const AusruestungBaum *parent;

   public:
      typedef std::list<AusruestungBaum>::const_iterator const_iterator;
      typedef std::list<AusruestungBaum>::iterator iterator;

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
