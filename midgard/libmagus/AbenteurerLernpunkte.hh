// $Id: AbenteurerLernpunkte.hh,v 1.6 2003/11/24 16:21:42 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#ifndef _ABENTLERNSCHEMA_H
#  define _ABENTLERNSCHEMA_H

#include "Lernschema.hh"
#include "class_lernpunkte.hh" // or embed it here ...
#include "Beruf.hh"
//#include "AbenteurerLernpunkte.hh"
class Abenteurer;

class WaffeBesitzLernen
{
   int Ewaffe,Awaffe;
   bool magisch;

 public:
   WaffeBesitzLernen() :  Ewaffe(0),Awaffe(0),magisch(false) {}

   void set_EWaffe(int i)  {Ewaffe=i;}
   void set_AWaffe(int i)  {Awaffe=i;}
   void add_EWaffe(int i)  {Ewaffe+=i;}
   void add_AWaffe(int i)  {Awaffe+=i;}
   int EWaffe() const {return Ewaffe;}
   int AWaffe() const {return Awaffe;}

   void setMagisch(bool b) {magisch=b;}
   bool getMagisch() const {return magisch;}
};

class AbenteurerLernpunkte
{public:
//	enum GWR_Auswahl {ENone,EGeld1,EGeld2,EGeld3,EWaffen,ERuestung};
private:
	Lernpunkte lernpunkte; // noch zu vergebende Lernpunkte
	WaffeBesitzLernen waffebesitzlernen; // Punkte für Waffenauswahl
	int maxkido;
	BerufsKategorie BKategorie;
	std::vector<int> VGeldwurf;
	// AbenteurerLernpunkte::GWR_Auswahl gwr_auswahl; ??

	void lernschema_geld_wuerfeln(Abenteurer &a,const std::vector<int>& VGeldwurf);
   	void setFertigkeitenAusruestung(Abenteurer &a);
	static void InfoAusruestung(const std::string &fert_name,
               const std::string &gegen_name,int wurf,int noetig);

   public:
   	AbenteurerLernpunkte() : maxkido(), BKategorie() {}

   	void geld_wuerfeln(Abenteurer &a);
   	void ruestung_auswaehlen(Abenteurer &a,int wprozent);
   	
   	// Beruf
   	void beruf_gewuerfelt(Abenteurer &a,int wurf);
   	
   	// Fertigkeiten
   	std::string AngebFert_gewuerfelt(Abenteurer &a,int wurf);
   	
   	void on_button_ruestung_clicked(Abenteurer &a,int wurf);
   	void ausruestung_setzen(Abenteurer &a);
   	
   	int &MaxKido() { return maxkido; }
   	std::vector<int> &getVGeldwurf() { return VGeldwurf; }
   	Lernpunkte &getLernpunkte() { return lernpunkte; }
   	BerufsKategorie &getBKategorie() { return BKategorie; }
};

#endif
