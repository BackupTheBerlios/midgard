// $Id: LernListen.hh,v 1.14 2002/09/21 18:00:13 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "Datenbank.hh"

class midgard_CG;
class VAbenteurer;
class WaffeBesitz;
#include "Beruf.hh"
#include "Enums.hh"

class LernListen
{
      const Datenbank D;
  public:
      enum eMBE{MutterSprache,GastlandSprache,NachbarlandSprache,AlteSprache,
                lFach,lAllg,lUnge,lWaff,lZaub,lAngebFert,
                sFert,sWaff,sZaub,sSpra,sSchr,sWGru,sZWerk};

      LernListen(const Datenbank& d) : D(d){}   
      LernListen() {}   

      bool nsc_check(bool nsc_allowed,bool nsc_only) const ;
      bool region_check(const std::string& region) const;

      static bool SpracheSchrift(const cH_MidgardBasicElement& MBE);                
      
      std::vector<cH_Spezies> getSpezies(bool nsc_allowed) const ;
      std::vector<pair<cH_Typen,bool> > getTypen(const VAbenteurer& A,bool nsc_allowed) const ;
      std::vector<pair<cH_Land,bool> > getHerkunft(const VAbenteurer& A) const;
      std::vector<MidgardBasicElement::st_zusatz> getLandZusatz() const;
      std::vector<MidgardBasicElement::st_zusatz> getMBEZusatz(const MBEmlt& MBE) const;
      std::vector<MidgardBasicElement::st_zusatz> getUeberlebenZusatz() const; 
      static std::vector<MidgardBasicElement::st_zusatz> getWaffenZusatz(const std::list<MBEmlt>& WL); 
      std::vector<MidgardBasicElement::st_zusatz> getSprachenZusatz(const MBEmlt &MBE,const VAbenteurer& Aben,bool nachbarland) const;
      std::vector<MidgardBasicElement::st_zusatz> getSchriftenZusatz(const MBEmlt &MBE,const VAbenteurer& Aben) const;
      std::vector<std::string> getSpezialgebiet(const VAbenteurer& A) const;
      std::list<MBEmlt> getBeruf(const VAbenteurer& A) const;      
      std::vector<Beruf::st_vorteil> getBerufsVorteil(const MBEmlt& beruf,const BerufsKategorie &BKat,const VAbenteurer& A) const;

      std::list<WaffeBesitz> getWaffenBesitz(const VAbenteurer& Aben) const;      

      std::list<MBEmlt> getMBEm(const VAbenteurer& A,eMBE was, int erfolgswert=0,
                     int lernpunkte=0,std::string lernart="") const;


      std::list<MBEmlt> get_steigern_MBEm(const Abenteurer& A,eMBE was,bool nsc_allowed) const;
      std::list<MBEmlt> get_steigern_Zauberliste(const Abenteurer& A,
            bool salz,bool beschwoerung,bool nsc, bool alle,bool spruchrolle) const;
      std::list<MBEmlt> get_steigern_ZauberWerkliste(const Abenteurer& A,
            bool nsc, bool alle) const;
      void shorten_for_GFP(std::list<MBEmlt> &L,const Abenteurer& A,int gfp) const;

};


#endif
