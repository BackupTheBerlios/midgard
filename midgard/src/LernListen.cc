// $Id: LernListen.cc,v 1.1 2002/09/07 07:17:26 thoma Exp $
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

#include "LernListen.hh"
#include "midgard_CG.hh"

std::vector<cH_Spezies> LernListen::getSpezies(bool nsc_allowed) const
{
 std::vector<cH_Spezies> V,S=D.Spezies;
 for(std::vector<cH_Spezies>::const_iterator i=S.begin();i!=S.end();++i)                                   
   {
     if (!nsc_check(nsc_allowed,(*i)->NSC_only())) continue;
     V.push_back(*i);
   }
 return V;
}


std::vector<pair<cH_Typen,bool> > LernListen::getTypen(const VAbenteurer& A,bool nsc_allowed) const
{
  std::vector<cH_Typen> T=D.Typen;
  std::vector<pair<cH_Typen,bool> > V;
  for(std::vector<cH_Typen>::const_iterator i=T.begin();i!=T.end();++i)
   {
     if (A.getWerte().Spezies()->Name()=="Mensch" || A.getWerte().Spezies()->Typ_erlaubt((*i)->Short()))
      if (region_check((*i)->Region()) && nsc_check(nsc_allowed,(*i)->NSC_only()))       
       {
         if((*i)->Mindestwerte(A.getWerte()))
            V.push_back(pair<cH_Typen,bool>(*i,true));
         else 
            V.push_back(pair<cH_Typen,bool>(*i,false));
       }
   }
  return V;
}

bool LernListen::region_check(const std::string& region) const
{
  if (region=="") return true;
  for(std::vector<cH_Region>::const_iterator i=D.Regionen.begin();i!=D.Regionen.end();++i)
   {
     if( (region==(*i)->Abkuerzung() || region==(*i)->Name() ) &&
         (*i)->Active()) return true;
   }
  return false;
}

bool LernListen::nsc_check(bool nsc_allowd,bool nsc_only) const
{
  if (nsc_only && !nsc_allowd) return false;
  return true;
}

//!Mh->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active