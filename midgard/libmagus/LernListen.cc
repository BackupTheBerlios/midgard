// $Id: LernListen.cc,v 1.8 2003/11/10 14:20:09 thoma Exp $
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

#include "LernListen.hh"
#include "Abenteurer.hh"
#include "Sprache.hh"
#include "Schrift.hh"
#include "Beruf.hh"


std::list<MBEmlt> LernListen::getMBEm(const Abenteurer& A,eMBE was,
                        int erfolgswert,int lernpunkte,std::string lernart) const
{
   std::list<cH_MidgardBasicElement> V_;
   std::list<MBEmlt> Vm;
   std::vector<Lernschema::st_index> VI;
   switch(was) {
      case MutterSprache: 
      case GastlandSprache: 
      case NachbarlandSprache: 
      case AlteSprache:
                            V_=Datenbank.Sprache; break;
      case lFach:           Vm=Datenbank.lernschema.get_List("Fachkenntnisse",A.getVTyp(),A.List_Fertigkeit());break;
      case lAllg: 
      case lUnge:           V_=Datenbank.Fertigkeit; break;
      case lWaff:           Vm=Datenbank.lernschema.get_List("Waffenfertigkeiten",A.getVTyp(),A.List_Waffen());break;
      case lZaub:           Vm=Datenbank.lernschema.get_List("Zauberkünste",A.getVTyp(),A.List_Waffen());break;
      case lAngebFert:      V_=Datenbank.Fertigkeit_ang; break;
      default : assert(!"never get here\n");
    }  
   std::list<MBEmlt> V;
   if(!V_.empty())
   {
    // Waffen hinzunehmen:
    if(was==lAllg)
      {std::list<cH_MidgardBasicElement> v=Waffe::getAllgemeinwissen(Datenbank.Waffe);
       V_.splice(V_.end(),v);
      }
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
      MBEmlt M(&**i);
      M->setLernArt(lernart+"_"+(*i)->Name());
      M->setErlaubt(erlaubt);

      int lp=0;
      if(was==lUnge) lp = cH_Fertigkeit(*i)->LernUnge();
      else if (was==lAllg)
       {
         if     (A.Stadt_Land()==Enums::Land  ) lp=(*i)->LernLand();
         else if(A.Stadt_Land()==Enums::Stadt ) lp=(*i)->LernStadt();
         if((*i)->What()==MidgardBasicElement::FERTIGKEIT) 
            cH_Fertigkeit(*i)->get_region_lp(lp,A);
       }
      M->setLernpunkte(lp);
      
      if(was==lUnge || was==lAllg)
       {
         if     ((*i)->Name()=="Muttersprache")
            Sprache::setErfolgswertMuttersprache(M,A.In(),cH_Fertigkeit(*i)->AttributBonus(A));
         else if((*i)->Name()=="Gastlandsprache")
            Sprache::setErfolgswertGastlandsprache(M,A.In());
         else if((*i)->What()==MidgardBasicElement::FERTIGKEIT) 
            M->setErfolgswert((*i)->Anfangswert()+cH_Fertigkeit(*i)->AttributBonus(A));
         else if((*i)->What()==MidgardBasicElement::WAFFE) 
            M->setErfolgswert(4);
       }
      else if(was==lAngebFert) M->setErfolgswert((*i)->Anfangswert());
      else M->setErfolgswert(erfolgswert);
      if(!region_check(A,(*i)->Region())) continue;
      if(A.Spezies()->istVerbotenSpielbegin(*i)) continue;
      V.push_back(M);
     }
    }
   else if(!Vm.empty())
   {
    for(std::list<MBEmlt>::iterator i=Vm.begin();i!=Vm.end();++i)
     {
      if(was==lFach)
       {
         VI=Lernschema::getIndex(A.getVTyp(),"Fachkenntnisse",(*(*i))->Name());
         (*i)->setErfolgswert(cH_Fertigkeit((*i)->getMBE())->Anfangswert0()+cH_Fertigkeit((*i)->getMBE())->AttributBonus(A));
         (*i)->setPflicht(Datenbank.lernschema.get_Pflicht(VI));
//cout << (*i)->Name()<<"  ?: "<<i->Erfolgswert()<<'\t'<<i->Pflicht()<<'\n';
       }
      if(was==lWaff)
         VI=Lernschema::getIndex(A.getVTyp(),"Waffenfertigkeiten",(*(*i))->Name());
      if(was==lZaub)
         VI=Lernschema::getIndex(A.getVTyp(),"Zauberkünste",(*(*i))->Name());
      int lp=Datenbank.lernschema.get_Lernpunkte(VI);
      (*i)->setLernpunkte(lp);
      if((*(*i))->What()==MidgardBasicElement::WAFFE)
         if (!region_check(A,cH_Waffe((*i)->getMBE())->Region((*(*i))->Name()))) continue;
      else if(!region_check(A,(*(*i))->Region())) continue;
//cout << (*i)->Name()<<"Region: "<<region_check((*i)->Region())<<' '<<i->Lernpunkte()<<' '<<i->Erfolgswert()<<'\n';
      if(A.Spezies()->istVerbotenSpielbegin((*i)->getMBE())) continue;
      V.push_back(*i);
     }     
   }
//  else assert(!"never get here\n");
  return V;
}




std::vector<cH_Spezies> LernListen::getSpezies(bool nsc_allowed) const
{
 std::vector<cH_Spezies> V,S=Datenbank.Spezies;
 for(std::vector<cH_Spezies>::const_iterator i=S.begin();i!=S.end();++i)                                   
   {
     if (!nsc_check(nsc_allowed,(*i)->NSC_only())) continue;
     V.push_back(*i);
   }
 return V;
}

std::vector<std::pair<cH_Typen,bool> > LernListen::getTypen(const Abenteurer &A) const 
 //W,const cH_Spezies &S,bool nsc_allowed) const
{
  const std::vector<cH_Typen> &T=Datenbank.Typen;
  std::vector<std::pair<cH_Typen,bool> > V;
  for(std::vector<cH_Typen>::const_iterator i=T.begin();i!=T.end();++i)
   {
//cout << (*i)->Typl()<<'\t'<<S->Typ_erlaubt((*i)->Short())<<' '
//<<region_check((*i)->Region())<<' '<<nsc_check(nsc_allowed,(*i)->NSC_only())
//<<'\n';
     if (A.Spezies()->Typ_erlaubt((*i)->Short()))
      if (region_check(A,(*i)->Region()) && nsc_check(A,(*i)->NSC_only()))
       {
         if((*i)->Mindestwerte(A))
            V.push_back(std::pair<cH_Typen,bool>(*i,true));
         else 
            V.push_back(std::pair<cH_Typen,bool>(*i,false));
       }
   }
  return V;
}



std::vector<std::pair<cH_Land,bool> > LernListen::getHerkunft(const Abenteurer& A) const
{
  std::vector<cH_Land> L=Datenbank.Laender;
  std::vector<std::pair<cH_Land,bool> > V;
  for (std::vector<cH_Land>::const_iterator i=L.begin();i!=L.end();++i)
   {
     V.push_back(std::pair<cH_Land,bool>(*i,(*i)->ist_erlaubt(A)));
   }
  return V;
}

std::vector<MidgardBasicElement::st_zusatz> LernListen::getLandZusatz() const
{
  std::vector<MidgardBasicElement::st_zusatz> B;
  std::vector<cH_Land> L=Datenbank.Laender;
  for(std::vector<cH_Land>::const_iterator i=L.begin();i!=L.end();++i)
   {
     B.push_back(MidgardBasicElement::st_zusatz((*i)->Name()));
   }
  return B;
}


std::vector<MidgardBasicElement::st_zusatz> LernListen::getMBEZusatz(const Abenteurer &A, const MBEmlt& MBE) const
{
  std::vector<MidgardBasicElement::st_zusatz> B;
  std::vector<MidgardBasicElement::st_zusatz> V=(*MBE)->VZusatz();
  for (std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=V.begin();i!=V.end();++i)
   {
     MidgardBasicElement::st_zusatz z=*i;
     z.long_region=Regionen_All::getRegionfromAbk(Datenbank.Regionen,i->region)->Name()+" "+i->region_zusatz;
     if(region_check(A,i->region)) B.push_back(z);
   }
  return B;
}

std::vector<MidgardBasicElement::st_zusatz> LernListen::getUeberlebenZusatz() const
{
   std::vector<MidgardBasicElement::st_zusatz> B;
   for(std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Fertigkeit.begin();i!=Datenbank.Fertigkeit.end();++i)
    {
      if((*i)->Name().find("Überleben")!=std::string::npos)
         B.push_back(MidgardBasicElement::st_zusatz((*i)->Name()));
    }
   return B;
}

std::vector<MidgardBasicElement::st_zusatz> LernListen::getWaffenZusatz(const std::list<MBEmlt> &WL)
{
   std::vector<MidgardBasicElement::st_zusatz> B;
   for(std::list<MBEmlt>::const_iterator i=WL.begin();i!=WL.end();++i)
    {
      if (cH_Waffe((*i)->getMBE())->Art()=="Schußwaffe" || cH_Waffe((*i)->getMBE())->Art()=="Wurfwaffe")
        B.push_back(MidgardBasicElement::st_zusatz((*(*i))->Name()));
    }
  return B;
}

std::vector<MidgardBasicElement::st_zusatz> LernListen::getSprachenZusatz(const MBEmlt &MBE,const Abenteurer& Aben,bool nachbarland) const
{
  std::vector<MidgardBasicElement::st_zusatz> B;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Sprache.begin();i!=Datenbank.Sprache.end();++i)
   {
     if(MBEmlt(&**i)->ist_gelernt(Aben.List_Sprache())) continue;

     bool erlaubt=true;
     if((*MBE)->Name()=="Muttersprache" || (*MBE)->Name()=="Gastlandsprache")
      {
        if(cH_Sprache(*i)->Alte_Sprache()) continue;                  
        if((*MBE)->Name()=="Muttersprache") // muß im Heimatland gesprochen werden
          if(!cH_Sprache(*i)->ist_erlaubt(Aben))
             erlaubt=false;
      }
     else if((*MBE)->Name()=="Sprechen: Alte Sprache" && !cH_Sprache(*i)->Alte_Sprache())
         continue;
     else if(nachbarland && !cH_Sprache(*i)->ist_erlaubt(Aben,nachbarland))
         erlaubt=false;
     B.push_back(MidgardBasicElement::st_zusatz((*i)->Name(),erlaubt));
   }
 return B;
}

std::vector<MidgardBasicElement::st_zusatz> LernListen::getSchriftenZusatz(const MBEmlt &MBE,const Abenteurer& Aben) const
{
  std::vector<MidgardBasicElement::st_zusatz> B;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Schrift.begin();i!=Datenbank.Schrift.end();++i)
   {
     if(MBEmlt(&**i)->ist_gelernt(Aben.List_Schrift())) continue;
     if(!cH_Schrift(*i)->kann_Sprache(Aben.List_Sprache())) continue;
     bool erlaubt=true;
     if( (*MBE)->Name().find("Muttersprache") != std::string::npos)
       if(!cH_Schrift(*i)->Mutterschrift(Aben)) erlaubt=false;
     else if ( (*MBE)->Name().find("Alte Sprache") != std::string::npos)
       if(!cH_Sprache((*i)->Name())->Alte_Sprache()) continue;
     B.push_back(MidgardBasicElement::st_zusatz((*i)->Name(),erlaubt));
   }
  return B;
}

std::vector<cH_Ruestung> LernListen::getRuestung(const Abenteurer &A) const
{
  std::vector<cH_Ruestung> V;
  for(std::vector<cH_Ruestung>::const_iterator i=Datenbank.Ruestung.begin();i!=Datenbank.Ruestung.end();++i)
   {  cH_Ruestung r(*i);
      if (region_check(A,r->Region()))  V.push_back(*i);
   }
  return V;
}


bool LernListen::region_check(const Abenteurer &A, const std::string& region)
{
  if (region.empty()) return true;
  else if (region=="EE") return true; // eigene Erweiterungen
  return A.getRegion(cH_Region::getRegionfromAbk(region));
}

bool LernListen::nsc_check(bool nsc_allowd,bool nsc_only)
{
  if (nsc_only && !nsc_allowd) return false;
  return true;
}

bool LernListen::nsc_check(const Abenteurer &A,bool nsc_only)
{  if (!nsc_only) return true;
   return A.getOptionen().OptionenCheck(Optionen::NSC_only).active;
}

bool LernListen::SpracheSchrift(const cH_MidgardBasicElement& MBE)
{
 bool back=false;  
 std::string fert=MBE->Name();

 if(fert=="Schreiben: Muttersprache(+12)" ||
         fert=="Schreiben: Muttersprache(+9)" ||
         fert=="Schreiben: Muttersprache(+4)" ||
         fert=="Schreiben: Alte Sprache(+12)" ||
         fert=="Schreiben: Alte Sprache(+4)" ||
         fert=="Schreiben" )
    { back=true;   }   
 else if(fert=="Muttersprache")
    { back=true; }  
 else if(fert=="Gastlandsprache" ||
         fert=="Sprechen: Sprache(+4)" ||
         fert=="Sprechen: Sprache(+9)" ||
         fert=="Sprechen: Sprache(+12)") 
    { back=true;  }  
 else if(fert=="Sprechen: Alte Sprache")
    { back=true; }  
 return back;  
}

std::list<H_WaffeBesitz> LernListen::getWaffenBesitz(const Abenteurer& Aben) const
{
  std::list<cH_MidgardBasicElement> V=Datenbank.Waffe;
  std::list<H_WaffeBesitz> L;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=V.begin();i!=V.end();++i)
   {
     if(Aben.Spezies()->istVerbotenSpielbegin(*i)) continue;
     const cH_Waffe w(*i);
     if (w->Grundkenntnis() == "Kampf ohne Waffen") continue;
     if (w->Grundkenntnis() == "Werfen") continue;
     if (!MBEmlt(&*w)->ist_gelernt(Aben.List_Waffen())) continue;
     L.push_back(new WaffeBesitz(w,w->Name(),0,0,"","")); 
     for(std::list<Waffe::st_alias>::const_iterator j=cH_Waffe(w)->Alias().begin();j!=cH_Waffe(w)->Alias().end();++j)
      {
        if(j->st>Aben.St()) continue;
        if(region_check(Aben,j->region))
           L.push_back(new WaffeBesitz(w,j->name,0,0,"",j->region)); 
      }
   }
 return L;
}

std::vector<std::string> LernListen::getSpezialgebiet(const Abenteurer& A) const
{
  std::vector<std::string> L;
  for(std::vector<cH_Spezialgebiet>::const_iterator i=Datenbank.Spezialgebiet.begin();i!=Datenbank.Spezialgebiet.end();++i) 
   {
    if((*i)->Typ() != A.Typ1()->Short() && 
       (*i)->Typ() != A.Typ2()->Short() ) continue;
    L.push_back((*i)->Name());
   }
  return L;
}


std::list<MBEmlt> LernListen::getBeruf(const Abenteurer& A) const
{
  std::list<MBEmlt> L;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Beruf.begin();i!=Datenbank.Beruf.end();++i)
   {
     if(A.Spezies()->istVerbotenSpielbegin(*i)) continue;
     cH_Beruf b(*i);
     if ( !b->Typ(A.getVTyp()) || !b->Stand(A.Stand()) ) continue;
     if(!b->Stadt() && A.Stadt_Land()==Enums::Stadt) continue;
     if(!b->Land()  && A.Stadt_Land()==Enums::Land) continue;
     L.push_back(*i);
   }
 L.sort(MBEmlt::sort(MBEmlt::sort::NAME));
 return L;
}

std::vector<Beruf::st_vorteil> LernListen::getBerufsVorteil(const MBEmlt& beruf,const BerufsKategorie &BKat,const Abenteurer& A) const
{
  cH_Beruf b(beruf->getMBE());
  std::vector<Beruf::st_vorteil> fert=b->Vorteile();
  std::vector<Beruf::st_vorteil> F;
  for(std::vector<Beruf::st_vorteil>::iterator j=fert.begin();j!=fert.end();++j)
   {
     if(j->name=="Schmecken+10") j->kat=1;
     else j->kat=cH_Fertigkeit(j->name)->Berufskategorie();
     if( (j->kat==1 && BKat.kat_I)   || (j->kat==2 && BKat.kat_II) ||
         (j->kat==3 && BKat.kat_III) || (j->kat==4 && BKat.kat_IV ) )
        {
          if(j->name!="Schmecken+10" && 
             MBEmlt(&*cH_Fertigkeit(j->name))->ist_gelernt(A.List_Fertigkeit()))
                j->gelernt=true;
          else if(j->name=="Schreiben: Muttersprache(+12)") j->gelernt=true;
          F.push_back(*j);
//datavec.push_back(new Beruf_Data(kat,(*i)->Name(),j->name,j->wert,gelerntes));
        }
    }
  return F;  
}

