// $Id: Pflicht.hh,v 1.8 2002/01/15 09:58:17 christof Exp $               
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

#ifndef _PFLICHT_HH
#  define _PFLICHT_HH
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Typen.hh"
#include <gtk--/progressbar.h>
#ifdef USE_XML
#include "xml.h"
#endif

class Pflicht //: public HandleContent
{
      struct pf{std::string pflicht;std::string verboten; 
                int lernpunkte; int erfolgswert; std::string spielbeginn;
         pf(std::string p,std::string v,int l, int e, std::string s)
            :pflicht(p),verboten(v),lernpunkte(l),erfolgswert(e),spielbeginn(s){}
         bool operator<(const pf& b) {return pflicht<b.pflicht;}
         };
      map<std::string,list<pf> > pflicht_map;

#ifdef USE_XML
	typedef std::list<pf> list_pflicht_t;
	typedef std::map<std::string,list_pflicht_t> pflicht_nach_typ_t;
	static void SuchePflichtVerbot(const Tag *list,const string &name,
			pflicht_nach_typ_t &pflicht_nach_typ);
#endif
   public:
      Pflicht() {}
      Pflicht(Gtk::ProgressBar *progressbar);
      enum LE {LERNPUNKTE,ERFOLGSWERT};

      int istPflicht(const std::string& spezies,const vector<cH_Typen>& Typ,
                     const std::string& name,LE le) const ;
      bool istVerboten(const std::string& spezies,const vector<cH_Typen>& Typ,
                       const std::string& s,bool spielbeginn=false) const;
         
};

#endif
