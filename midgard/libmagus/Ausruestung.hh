/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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
//#include "dtos1.h"

class AusruestungBaum;

class Ausruestung
{
     unsigned int anzahl;
     std::string name;
     double gewicht;
     std::string material,region;
     bool sichtbar;
     bool ruestung_ohne_gewicht;
     std::string beschreibung;

   public:
     Ausruestung() : anzahl(0), gewicht(0), sichtbar(false),ruestung_ohne_gewicht(false) {}

     Ausruestung(std::string n) 
       : anzahl(1), name(n), gewicht(0), sichtbar(true),ruestung_ohne_gewicht(false) {}
     Ausruestung(unsigned int a, std::string n,double g,std::string ma,std::string r,bool s,bool ru,const std::string b)
         :anzahl(a),name(n),gewicht(g),material(ma),region(r),sichtbar(s),ruestung_ohne_gewicht(ru),beschreibung(b) {}

     bool operator==(const Ausruestung& b) const
         {return name==b.name && material==b.material;}
     
     unsigned int Anzahl() const {return anzahl;}
     std::string SAnzahl() const;
     std::string Name() const {return name;}
     std::string Beschreibung() const {return beschreibung;}
     double Gewicht() const {return gewicht;}
     std::string SGewicht() const;
     std::string Region() const {return region;}
     std::string Material() const {return material;}
     bool Sichtbar() const {return sichtbar;}
     std::string SichtbarStr() const {if(sichtbar) return "*"; else return "";}
     void setSichtbar(bool s) {sichtbar=s;}
     bool RuestungOhneGewicht() const {return ruestung_ohne_gewicht;}

};

class AusruestungBaum
{
      std::list<AusruestungBaum> child;
      Ausruestung ausruestung;
      AusruestungBaum *parent;

   public:
      typedef std::list<AusruestungBaum>::const_iterator const_iterator;
      typedef std::list<AusruestungBaum>::iterator iterator;

      AusruestungBaum()  {}
      AusruestungBaum(const Ausruestung& a) 
         : ausruestung(a),parent(0) {}
      
      AusruestungBaum &push_back(const Ausruestung& a)
          { child.push_back(a); return child.back(); }

      const Ausruestung &getAusruestung() const {return ausruestung;}

      AusruestungBaum *getParent() const {return parent;}
      void setParent(AusruestungBaum *p) {parent=p;}

      const std::list<AusruestungBaum> &getChildren() const {return child;}
      std::list<AusruestungBaum> &getChildren() {return child;}

      void remove(const AusruestungBaum &A) {child.remove(A);}
         
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
