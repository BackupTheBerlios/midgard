// $Id: LernListen.hh,v 1.12 2005/04/23 14:24:15 christof Exp $
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

#ifndef _LERNLISTEN_HH
#  define _LERNLISTEN_HH

//#include "Datenbank.hh"
class VAbenteurer;
class H_WaffeBesitz;
class Abenteurer;
//class Beruf;
#include <string>
#include "Beruf.hh"
#include "Enums.hh"
#include "Spezies.hh"
#include "Ruestung.hh"
#include "Land.hh"

// könnte jetzt Namespace werden

namespace LernListen
{
//private:
      bool nsc_check(bool nsc_allowed,bool nsc_only);
      bool nsc_check(const Abenteurer &A,bool nsc_only);

//public:
      enum eMBE{MutterSprache,GastlandSprache,NachbarlandSprache,AlteSprache,
                lFach,lAllg,lUnge,lWaff,lZaub,lAngebFert};
//                sFert,sWaff,sZaub,sSpra,sSchr,sWGru,sZWerk};

//      LernListen() {}   

      bool region_check(const Abenteurer &A, const std::string& region);
      bool SpracheSchrift(const cH_MidgardBasicElement& MBE);                
      
      std::vector<cH_Spezies> getSpezies(bool nsc_allowed);
      std::vector<std::pair<cH_Typen,bool> > getTypen(const Abenteurer& A);
      std::vector<std::pair<cH_Typen,bool> > getTypen(const cH_Spezies &s);
      std::vector<std::pair<cH_Land,bool> > getHerkunft(const Abenteurer& A);
      std::vector<MidgardBasicElement::st_zusatz> getLandZusatz();
      std::vector<MidgardBasicElement::st_zusatz> getMBEZusatz(const Abenteurer& A,const MBEmlt& MBE);
      std::vector<MidgardBasicElement::st_zusatz> getUeberlebenZusatz(); 
      std::vector<MidgardBasicElement::st_zusatz> getWaffenZusatz(const std::list<MBEmlt>& WL); 
      std::vector<MidgardBasicElement::st_zusatz> getSprachenZusatz(const MBEmlt &MBE,const Abenteurer& Aben,bool nachbarland);
      std::vector<MidgardBasicElement::st_zusatz> getSchriftenZusatz(const MBEmlt &MBE,const Abenteurer& Aben);
      std::vector<std::string> getSpezialgebiet(const Abenteurer& A);
      std::list<MBEmlt> getBeruf(const Abenteurer& A);      
      std::vector<Beruf::st_vorteil> getBerufsVorteil(const MBEmlt& beruf,const BerufsKategorie &BKat,const Abenteurer& A);
      std::vector<cH_Ruestung> getRuestung(const Abenteurer& A);

      std::list<H_WaffeBesitz> getWaffenBesitz(const Abenteurer& Aben);

      std::list<MBEmlt> getMBEm(const Abenteurer& A,eMBE was, int erfolgswert=0,
                     int lernpunkte=0,std::string lernart="");

      std::list<MBEmlt> get_steigern_MBEm(const Abenteurer& A,MidgardBasicElement::MBEE was);
      // beschwörung ... ist das nicht eine Region?
      std::list<MBEmlt> get_steigern_Zauberliste(const Abenteurer& A,
            bool salz,bool beschwoerung, bool alle,bool spruchrolle);
      std::list<MBEmlt> get_steigern_ZauberWerkliste(const Abenteurer& A,
            bool alle);
      void shorten_for_GFP(std::list<MBEmlt> &L,const Abenteurer& A,const int gfp);
};


#endif
