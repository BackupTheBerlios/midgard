// $Id: AbenteurerLernpunkte.hh,v 1.1 2003/08/02 22:29:02 christof Exp $               
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
#include "AbenteurerLernpunkte.hh"
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
{	Lernpunkte lernpunkte; // noch zu vergebende Lernpunkte
	WaffeBesitzLernen waffebesitzlernen; // Punkte für Waffenauswahl
	int maxkido;
	BerufsKategorie BKategorie;
	enum GWR_Auswahl {ENone,EGeld1,EGeld2,EGeld3,EWaffen,ERuestung};
	std::vector<int> VGeldwurf;
	Abenteurer &a;

   public:
   	AbenteurerLernpunkte(Abenteurer &_a) 
   		: maxkido(), BKategorie(), a(_a) {}

   	void geld_wuerfeln();
   	void ruestung_auswaehlen(int wprozent);
   	
   	// Beruf
   	void beruf_gewuerfelt(int wurf);
   	
   	// Fertigkeiten
   	std::string AngebFert_gewuerfelt(int wurf);
   	
   	void on_button_ruestung_clicked(int wurf);
   	void ausruestung_setzen();
};

#endif
