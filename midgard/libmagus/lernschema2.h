// $Id: lernschema2.h,v 1.1 2003/07/29 06:16:44 christof Exp $               
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

#ifndef _LERNSCHEMA2_H
#  define _LERNSCHEMA2_H

#include "Lernschema.hh"
#include "Zufall.hh"

class Lernschema2
{	Lernpunkte lernpunkte;
	WaffeBesitzLernen waffebesitzlernen;
	int maxkido;
	BerufsKategorie BKategorie;
	enum GWR_Auswahl {ENone,EGeld1,EGeld2,EGeld3,EWaffen,ERuestung};
	std::vector<int> VGeldwurf;

   public:
   	void geld_wuerfeln();
   	static void ruestung_auswaehlen(Abenteurer &A, int wprozent);
   	ausruestung_setzen();
   	
   	// Beruf
   	void beruf_gewuerfelt(int wurf);
   	
   	// Fertigkeiten
   	std::string AngebFert_gewuerfelt(int wurf);
};

#endif
