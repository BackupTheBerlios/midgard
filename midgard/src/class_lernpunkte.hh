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

#ifndef _LERNPUNKTE_HH
#  define _LERNPUNKTE_HH



class Lernpunkte {

 int fach, waffen, allgemein, unge, zauber;
 bool schreiben_pflicht_allg, schreiben_pflicht_fach;

public:
   Lernpunkte():fach(0),waffen(0),allgemein(0),unge(0),zauber(0),
   schreiben_pflicht_allg(false),schreiben_pflicht_fach(false){}
   Lernpunkte(int f, int w, int a,int u, int z)
      :fach(f),waffen(w),allgemein(a),unge(0),zauber(z),
      schreiben_pflicht_allg(false),schreiben_pflicht_fach(false){}

   void clear() {fach=0;waffen=0;allgemein=0;unge=0;zauber=0;}

   int Fach() const {return fach;}
   int Waffen() const {return waffen;}
   int Allgemein() const {return allgemein;}
   int Unge() const {return unge;}
   int Zauber() const { return zauber;}

   void setFach(int i) {fach =i;}
   void setWaffen(int i) {waffen =i;}
   void setAllgemein(int i) {allgemein =i;}
   void setUnge(int i) {unge =i;}
   void setZauber(int i) {zauber =i;}

   void addFach(int i) {fach +=i;}
   void addWaffen(int i) {waffen +=i;}
   void addAllgemein(int i) {allgemein +=i;}
   void addUnge(int i) {unge +=i;}
   void addZauber(int i) {zauber +=i;}

   bool get_schreiben_pflicht_allg() const {return schreiben_pflicht_allg;}
   bool get_schreiben_pflicht_fach() const {return schreiben_pflicht_fach;}

   void set_schreiben_pflicht_allg(bool b) {schreiben_pflicht_allg=b;}
   void set_schreiben_pflicht_fach(bool b) {schreiben_pflicht_fach=b;}

   int Summe() const {return fach+waffen+allgemein+unge+zauber;}   
   
};


#endif
