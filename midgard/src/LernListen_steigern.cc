// $Id: LernListen_steigern.cc,v 1.1 2002/09/16 12:01:13 thoma Exp $
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
//#include "midgard_CG.hh"
#include "Abenteurer.hh"
//#include "Sprache.hh"
//#include "Schrift.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"

std::list<MidgardBasicElement_mutable> LernListen::get_steigern_MBEm(const Abenteurer& A,eMBE was,bool nsc_allowed) const
{
  std::list<cH_MidgardBasicElement> V_;
  switch(was) {
     case sFert: V_=D.Fertigkeit; break;
     case sWaff: V_=D.Waffe; break;
     case sZaub: V_=D.Zauber; break;
     case sSpra: V_=D.Sprache; break;
     case sSchr: V_=D.Schrift; break;
     case sWGru: V_=D.WaffeGrund; break;
     case sZWerk:V_=D.Zauberwerk; break; 
     default : assert(!"never get here\n");
   }
  std::list<MidgardBasicElement_mutable> V;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=V_.begin();i!=V_.end();++i)
   {
     if ((*i)->Name()=="Sprache" || (*i)->Name()=="Schreiben" || (*i)->Name()=="KiDo-Technik") continue;
     if(A.getWerte().Spezies()->istVerboten(*i)) continue;
     if ((*i)->Name()=="Zaubern" && A.is_mage() ) continue;
     if (!(*i)->ist_lernbar(A.getVTyp(),(*i)->get_MapTyp())) continue;
     if (!region_check((*i)->Region()) ) continue;
     if (!nsc_check(nsc_allowed,(*i)->NSC_only())) continue;
     MidgardBasicElement_mutable MBEm(*i);
     switch(was) {
       case sFert: { const cH_Fertigkeit f(*i);
          if (MidgardBasicElement_mutable(*i).ist_gelernt(A.List_Fertigkeit()) && 
              (*i)->ZusatzEnum(A.getVTyp())==MidgardBasicElement::ZNone) continue ;
          if (!f->Voraussetzung(A)) continue;
          MBEm.setErfolgswert(f->Anfangswert());
          break;
         }
       case sZaub: { 
          if (MidgardBasicElement_mutable(*i).ist_gelernt(A.List_Zauber()) && 
              (*i)->ZusatzEnum(A.getVTyp())==MidgardBasicElement::ZNone) continue ;
          break;
         }
       case sZWerk: { 
          if (MidgardBasicElement_mutable(*i).ist_gelernt(A.List_Zauberwerk()) && 
              (*i)->ZusatzEnum(A.getVTyp())==MidgardBasicElement::ZNone) continue ;
          break;
         }
       default : assert(!"never get here\n");
      }
     V.push_back(MBEm);
   }
  return V;
}

std::list<MidgardBasicElement_mutable> LernListen::get_steigern_Zauberliste(const Abenteurer& A,
      bool salz,bool beschwoerung,bool nsc, bool alle,bool spruchrolle) const
{
  std::list<MidgardBasicElement_mutable> L_=get_steigern_MBEm(A,sZaub,nsc);
  std::list<MidgardBasicElement_mutable> L;
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L_.begin();i!=L_.end();++i)
   {
     cH_Zauber z(*i);
     if (z->Spruchrolle()) z->setSpruchrolleFaktor(0.1);
     else z->setSpruchrolleFaktor(1);
     if(alle) L.push_back(*i);
     else
      {
        if (z->Zauberart()=="Zaubersalz"   && !salz ) continue;
        if (z->Zauberart()=="Beschwörung"  && !beschwoerung) continue;
        if (z->Spruchrolle()               && !spruchrolle) continue;
        L.push_back(*i);
      }
   }
 return L;
}

std::list<MidgardBasicElement_mutable> LernListen::get_steigern_ZauberWerkliste(const Abenteurer& A,
      bool nsc, bool alle) const
{
  std::list<MidgardBasicElement_mutable> L_=get_steigern_MBEm(A,sZWerk,nsc);
  std::list<MidgardBasicElement_mutable> L;
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L_.begin();i!=L_.end();++i)
   { const cH_Zauberwerk z(*i);
     if(alle) L.push_back(*i); 
     else
      {  if (!z->Voraussetzungen(A.List_Zauber())) continue;
         if (!z->Voraussetzungen_Fertigkeit(A.List_Fertigkeit())) continue;
         L.push_back(*i); 
      }
   }
 return L;
}
