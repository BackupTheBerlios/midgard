/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002-2003 Christof Petig
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

#include "KiDo.hh"
#include <cstring>
#include <Misc/itos.h>
#include <Misc/Tag.h>
#include "NotFound.h"
#include "Ausgabe.hh"

KiDo_Stile::KiDo_Stile()
{
  // Muß mit Optionmenu in glade übereinstimmen
  Vkido.clear();
  Vkido.push_back("TECHNIK");
  Vkido.push_back("Sanfte Techniken");
  Vkido.push_back("Harte Techniken");
  Vkido.push_back("Gemischte Techniken");
}

bool KiDo_Stile::ist_gelernt(std::string s)
{
  std::vector<std::string>::iterator i=find(Vkido.begin(),Vkido.end(),s);
  if(i==Vkido.end()) return false;
  return true;
}

bool KiDo_Stile::ist_sanft(std::string s)
{
 if(s==Vkido[1]) return true;
 return false;
}

bool KiDo_Stile::ist_hart(std::string s)
{
 if(s==Vkido[2]) return true;
 return false;
}

bool KiDo_Stile::ist_gemischt(std::string s)
{
 if(s==Vkido[3]) return true;
 return false;
}



cH_KiDo::cache_t cH_KiDo::cache;

cH_KiDo::cH_KiDo(const std::string& name ,bool create)
{
 cH_KiDo *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "KiDo '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("KiDo"); 
     t2.setAttr("Name",name);
     t2.setAttr("Übersetzung","?");
     t2.setAttr("Stil","?");
     *this=new KiDo(t2);
  }
  else throw NotFound(name);
  }
}

void KiDo::get_KiDo(const Tag &t)
{
  deutsch = t.getAttr("Übersetzung");
  stufe = t.getAttr("Stufe");
  stil=t.getAttr("Stil");
  kosten=t.getIntAttr("Lernkosten");
  ap=t.getIntAttr("AP");
  effekt=t.Value();  
}


int KiDo::get_erfolgswert_kido(const std::list<MBEmlt>& L)
{
 for (std::list<MBEmlt>::const_iterator i= L.begin();i!=L.end();++i)
   if ((*(*i))->Name() == "KiDo") return (*i)->Erfolgswert();
 abort();
}   

std::map<std::string,int> KiDo::maxkidostil(const std::list<MBEmlt>& list_Kido)
{
  std::map<std::string,int> MK;
  for (std::list<MBEmlt>::const_iterator i=list_Kido.begin();i!=list_Kido.end();++i)
     MK[cH_KiDo((*i)->getMBE())->Stufe()]++;
  return MK;
}

static MidgardBasicElement::EP_t KiDo_EP=MidgardBasicElement::EP_t_undefined;

KiDo::KiDo(const Tag &t)
     : MidgardBasicElement(t.getAttr("Name")) 
{  get_KiDo(t); get_map_typ();
   if (KiDo_EP==EP_t_undefined) KiDo_EP=EP_steigern("KiDo");
   else EP_steigern(KiDo_EP);
}

cH_KiDo cH_KiDo::load(const Tag &t,bool &is_new)
{  cH_KiDo *res=cache.lookup(t.getAttr("Name"));
   assert(!res);
   {  cH_KiDo r2=new KiDo(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void KiDo_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  bool is_new=false;
   cH_KiDo z=cH_KiDo::load(t,is_new);
   // das &* dient dazu um aus einem cH_KiDo ein cH_MBE zu machen
   if (is_new) list.push_back(&*z);
}

bool cH_KiDo::sort::operator() (MBEmlt _x,MBEmlt _y) const
{ 
   cH_KiDo x(_x->getMBE());
   cH_KiDo y(_y->getMBE());
   switch(es) {
      default:
      case(HOHO) : return x->HoHo() < y->HoHo()  ;
      case(NAME) : return x->Deutsch() < y->Deutsch()  ;
      case(STUFE): return x->Stufe() < y->Stufe();
      case(AP)   : return x->Ap() < y->Ap() ;
      case(STIL) : return x->Stil() < y->Stil() ;
   }
}
