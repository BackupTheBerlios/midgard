// $Id: LernListen.cc,v 1.3 2002/09/08 17:42:30 thoma Exp $
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
#include "Sprache.hh"


std::list<MidgardBasicElement_mutable> LernListen::getMBEm(const VAbenteurer& A,eMBE was,
                        int erfolgswert,int lernpunkte,std::string lernart) const
{
   std::list<cH_MidgardBasicElement> V_;
   std::list<MidgardBasicElement_mutable> Vm;
   std::vector<Lernschema::st_index> VI;
   switch(was) {
      case MutterSprache: 
      case GastlandSprache: 
      case NachbarlandSprache: 
      case AlteSprache:
                            V_=D.Sprache; break;
      case lFach:           Vm=D.lernschema.get_List("Fachkenntnisse",A.getVTyp(),A.List_Fertigkeit());break;
      case lAllg: 
      case lUnge:           V_=D.Fertigkeit; break;
      case lWaff:           Vm=D.lernschema.get_List("Waffenfertigkeiten",A.getVTyp(),A.List_Waffen());break;
      case lZaub:           Vm=D.lernschema.get_List("Zauberkünste",A.getVTyp(),A.List_Waffen());break;
    }  
   std::list<MidgardBasicElement_mutable> V;
   if(!V_.empty())
    for(std::list<cH_MidgardBasicElement>::const_iterator i=V_.begin();i!=V_.end();++i)
     {
      bool erlaubt=false;
      if(was==MutterSprache || was==NachbarlandSprache)
       {
         if(cH_Sprache(*i)->Alte_Sprache()) continue;
         if(cH_Sprache(*i)->ist_erlaubt(A,was==NachbarlandSprache)) 
               erlaubt=true;
       }
      else if(was==AlteSprache)
         if(cH_Sprache(*i)->Alte_Sprache()) erlaubt=true;
         else continue;
      else erlaubt=true;
      MidgardBasicElement_mutable M(&**i);
      M.setLernArt(lernart+"_"+(*i)->Name());
      M.setErlaubt(erlaubt);
      M.setErfolgswert(erfolgswert);
      M.setLernpunkte(lernpunkte);
      V.push_back(M);
     }
   else if(!Vm.empty())
    for(std::list<MidgardBasicElement_mutable>::iterator i=Vm.begin();i!=Vm.end();++i)
     {
      if(was==lFach)
         VI=Lernschema::getIndex(A.getVTyp(),"Fachkenntnisse",(*i)->Name());
      if(was==lWaff)
         VI=Lernschema::getIndex(A.getVTyp(),"Waffenfertigkeiten",(*i)->Name());
      if(was==lZaub)
         VI=Lernschema::getIndex(A.getVTyp(),"Zauberkünste",(*i)->Name());
      int lp=D.lernschema.get_Lernpunkte(VI);
      i->setLernpunkte(lp);
      V.push_back(*i);
     }     
  return V;
}


std::vector<std::string> LernListen::getZusatz(eZusatz ez) const
{
   assert(ez==UeberlebenHeimat);
   std::vector<std::string> V;
   for(std::list<cH_MidgardBasicElement>::const_iterator i=D.Fertigkeit.begin();i!=D.Fertigkeit.end();++i)
    {
      if((*i)->Name().find("Überleben")!=std::string::npos)
         V.push_back((*i)->Name());
    }
   return V;
}



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

std::vector<pair<cH_Land,bool> > LernListen::getLand(const VAbenteurer& A) const
{
  std::vector<cH_Land> L=D.Laender;
  std::vector<pair<cH_Land,bool> > V;
  for (std::vector<cH_Land>::const_iterator i=L.begin();i!=L.end();++i)
   {
     V.push_back(pair<cH_Land,bool>(*i,(*i)->ist_erlaubt(A)));
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

