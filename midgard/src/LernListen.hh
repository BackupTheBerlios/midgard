// $Id: LernListen.hh,v 1.1 2002/05/14 07:26:14 thoma Exp $
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

class LernListen
{
     std::list<cH_MidgardBasicElement> list_Beruf;
     std::list<cH_MidgardBasicElement> list_Fertigkeit_ang;
     std::list<cH_MidgardBasicElement> list_Fertigkeit;
     std::list<cH_MidgardBasicElement> list_Fertigkeit_universal;
     std::list<cH_MidgardBasicElement> list_WaffenGrund;
     std::list<cH_MidgardBasicElement> list_Waffen;
     std::list<cH_MidgardBasicElement> list_Waffen_besitz;
     std::list<cH_MidgardBasicElement> list_Zauber;
     std::list<cH_MidgardBasicElement> list_Zauberwerk;
     std::list<cH_MidgardBasicElement> list_Kido;
     std::list<cH_MidgardBasicElement> list_Sprache;
     std::list<cH_MidgardBasicElement> list_Schrift;
   public:
     std::list<cH_MidgardBasicElement> getBeruf() {return list_Beruf;}
     std::list<cH_MidgardBasicElement> getFertigkeit_ang() {return list_Fertigkeit_ang;}
     std::list<cH_MidgardBasicElement> getFertigkeit() {return list_Fertigkeit;}
     std::list<cH_MidgardBasicElement> getFertigkeit_universal() {return list_Fertigkeit_universal;}
     std::list<cH_MidgardBasicElement> getWaffenGrund() {return list_WaffenGrund;}
     std::list<cH_MidgardBasicElement> getWaffen() {return list_Waffen;}
     std::list<cH_MidgardBasicElement> getWaffen_besitz() {return list_Waffen_besitz;}
     std::list<cH_MidgardBasicElement> getZauber() {return list_Zauber;}
     std::list<cH_MidgardBasicElement> getZauberwerk() {return list_Zauberwerk;}
     std::list<cH_MidgardBasicElement> getKido() {return list_Kido;}
     std::list<cH_MidgardBasicElement> getSprache() {return list_Sprache;}
     std::list<cH_MidgardBasicElement> getSchrift() {return list_Schrift;}
};


#endif
