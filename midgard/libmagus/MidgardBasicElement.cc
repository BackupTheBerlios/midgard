/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Grundwerte.hh"
#include "Fertigkeiten.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "KiDo.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "Sprache.hh"
#include "Schrift.hh"
//#include "class_SimpleTree.hh"
//#include "SimpleTree.hh"
#include <Misc/itos.h>
//#include "xml.h"
#include "Datenbank.hh"
#include "Abenteurer.hh"
#include <Misc/germanstring.h>
#include <memory>
#include "NotFound.h"
#include "Ausgabe.hh"

bool H_MidgardBasicElement_mutable::sort::operator() (H_MidgardBasicElement_mutable x,H_MidgardBasicElement_mutable y) const
{ switch(es) {
               case(LERNPUNKTEPFLICHT) : return x->Pflicht() > y->Pflicht() ||
                  (x->Pflicht() == y->Pflicht()  &&  x->Lernpunkte() < y->Lernpunkte() ) ;
               case(NAME) : return germanstring((*x)->Name()) < germanstring((*y)->Name())  ;
               case(ERFOLGSWERT): return x->Erfolgswert() > y->Erfolgswert();
               
           }abort();
}

bool MidgardBasicElement::Voraussetzung(const Abenteurer& A,bool anzeigen) const
{Ausgabe(Ausgabe::Error,"ERROR in Voraussetzung");return false;}

std::string MidgardBasicElement::RegionString() const
{
  std::vector<cH_Region> V=Datenbank.Regionen;
  std::string s=Regionen_All::getRegionfromAbk(V,region)->Name();
  if(!RegionZusatz().empty()) s+=" ("+RegionZusatz()+")";
  return s;
}

bool MidgardBasicElement::ist_lernbar(const std::vector<cH_Typen>& Typ,const std::map<std::string,std::string>& map_typ) const
{
  for (std::vector<cH_Typen>::const_iterator i=Typ.begin();i!=Typ.end();++i)
    if (const_cast<std::map<std::string,std::string>& >(map_typ)[(*i)->Short()]!="") 
      return true;
  return false;
}

bool MidgardBasicElement_mutable::ist_gelernt(const std::list<MBEmlt>& L) const
{
 for (std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
     if(**i==*this) return true;
 return false;
}

bool MidgardBasicElement::ist_gelernt(const std::list<std::string>& L) const
{
 for (std::list<std::string>::const_iterator i=L.begin();i!=L.end();++i)
   {
//cout <<"Ist gelernt? " << (*i)<<'\t'<<Name()<<'\n';
     if((*i)==Name()) return true;
     if(Name()=="Muttersprache" && 
         (*i).find("_Muttersprache")!=std::string::npos) return true;
     if(Name()=="Gastlandsprache" && 
         (*i).find("_Gastlandsprache")!=std::string::npos) return true;
   }
 return false;
}

std::string MidgardBasicElement::Standard__(const Abenteurer &A) const
{
 std::vector<std::string> s = Standard(A);
 std::string s2=s[0];
 if(A.Typ1()->Short()!="" && A.Typ2()->Short()!="") s2+="/";
 if(A.Typ2()->Short()!="") s2+=s[1];
 return s2;
}

std::vector<std::string> MidgardBasicElement::Standard(const Abenteurer &A) const
{
 assert(A.getVTyp().size()==2);
 std::vector<std::string> s(2);
 for(std::map<std::string,std::string>::const_iterator i=map_typ.begin();i!=map_typ.end();++i)
   if(A.Typ1()->Short()==i->first) {s[0]=i->second; break;}
 for(std::map<std::string,std::string>::const_iterator i=map_typ.begin();i!=map_typ.end();++i)
   if(A.Typ2()->Short()==i->first) {s[1]=i->second; break;}

 s[0]=AusnahmenString(A,A.Typ1(),s[0]);
 s[1]=AusnahmenString(A,A.Typ2(),s[1]);

 return s;
}

bool MidgardBasicElement::Grundfertigkeit(const Abenteurer &A) const
{
  if      (standard_one_G(Standard(A)) ) return true;
  return false;
}

bool MidgardBasicElement::Standardfertigkeit(const Abenteurer &A) const
{
  if (standard_all_S(Standard(A)) ) return true;
  return false;
}


std::string MidgardBasicElement::AusnahmenString(const Grundwerte &Werte,const cH_Typen& Typ,const std::string s) const
{
  if(Region()=="") return s;
  for(std::vector<st_ausnahmen>::const_iterator i=VAusnahmen.begin();i!=VAusnahmen.end();++i)
   {
     if( (i->herkunft==""|| i->herkunft==Werte.Herkunft()->Name()) &&
         (i->spezies ==""|| i->spezies ==Werte.Spezies()->Name())  &&
         (i->stand   ==""|| i->stand==Werte.Stand())  &&
         (i->typ     ==""|| i->typ==Typ->Short() ))
      {
       return i->standard;
      }
   }
  return s;
}


double MidgardBasicElement::Standard_Faktor(const Abenteurer &A) const
{
  double fac;
  if      (standard_one_G(Standard(A)) ) fac = 0.5;
  else if (standard_all_S(Standard(A)) ) fac = 1.0;
  else 
    { 
      fac = 2.0; 
      if (What()==ZAUBER || What()==ZAUBERWERK) fac=5.0;
    }
//cout <<Name()<<' ' <<"StandardFaktor = "<<fac<<"  Grundkosten= "<<GrundKosten()<<'\n';
  return fac;
}

bool MidgardBasicElement::standard_one_G(const std::vector<std::string>& s) const 
{
 assert(s.size()==2);
 if (s[0] == "G" || s[1] =="G" ) return true;
 return false;
}

bool MidgardBasicElement::standard_all_S(const std::vector<std::string>& s) const 
{
 assert(s.size()==2);
 if (s[0] == "S" && (s[1] =="S" || s[1]=="" )) return true;
 if (s[1] == "S" && (s[0] =="S" || s[0]=="" )) return true;
 return false;
}


int MidgardBasicElement::get_Steigern_Kosten(int erfolgswert) const
{
 return const_cast<std::map<int,int>& >(map_erfolgswert_kosten)[erfolgswert];
}

int MidgardBasicElement_mutable::Steigern(const Abenteurer &A) const 
{ 
   int kosten=0;
   if(Erfolgswert()>0)
      kosten = (*this)->get_Steigern_Kosten(Erfolgswert()+1);
   else 
      kosten = (*this)->get_Steigern_Kosten(abs(Erfolgswert())-1);
   int back = int((*this)->Standard_Faktor(A)*kosten);
   return back;
}

int MidgardBasicElement_mutable::Reduzieren(const Abenteurer &A) const 
{
   int kosten=0;
   if(Erfolgswert()>0)
      kosten = (*this)->get_Steigern_Kosten(Erfolgswert());
   else 
      kosten = (*this)->get_Steigern_Kosten(abs(Erfolgswert()));
   int back = int((*this)->Standard_Faktor(A)*kosten);
   return back;
}

int MidgardBasicElement_mutable::Verlernen(const Abenteurer &A) const
{
//cout << "MidgardBasicElement::Verlernen "<<Name()<<' ' << Reduzieren(Typ,ausnahmen)<<'\n';
   if(Reduzieren(A)==0)
    {
        return (*this)->Kosten(A);
    }      
   else return 0;
}


void MidgardBasicElement::get_map_typ(const Tag &t)
{  FOR_EACH_CONST_TAG(i,t)
    {  if (i->Type()=="Grund") map_typ[i->getAttr("Typ")]="G";
       else if (i->Type()=="Standard") map_typ[i->getAttr("Typ")]="S";
       else if (i->Type()=="Ausnahme") map_typ[i->getAttr("Typ")]="A";
    }
}
 
void MidgardBasicElement::get_map_typ()
{
 static std::auto_ptr<cH_Fertigkeit> sprache,schrift,kido;

 if(What()==SPRACHE)
 {  if (!sprache.get()) sprache.reset(new cH_Fertigkeit("Sprache"));
    map_typ=(*sprache)->map_typ;
 }
 else if(What()==SCHRIFT)
 {  if (!schrift.get()) schrift.reset(new cH_Fertigkeit("Schreiben"));
    map_typ=(*schrift)->map_typ;
 }
 else if(What()==KIDO)
 {  if (!kido.get()) kido.reset(new cH_Fertigkeit("KiDo"));
    map_typ=(*kido)->map_typ;
 }
 else assert(!"get_map_typ mit merkw�rdigem Typ");
}
 

const std::map<int,int> &MidgardBasicElement::get_Steigern_Kosten_map()
{
 if(What()==WAFFE) 
 {  int schwierigkeit=dynamic_cast<Waffe&>(*this).Schwierigkeit();
    map_erfolgswert_kosten=waffen_steigern_nach_schwierigkeit[schwierigkeit];
 }
 else if(What()==SPRACHE) 
 { map_erfolgswert_kosten=cH_Fertigkeit("Sprache")->map_erfolgswert_kosten; }
 else if(What()==SCHRIFT) 
 { map_erfolgswert_kosten=cH_Fertigkeit("Schreiben")->map_erfolgswert_kosten; }
 else assert(!"get here");
 
 return map_erfolgswert_kosten;
}

void MidgardBasicElement::load_steigern_kosten(const Tag &t)
{   std::map<int,int> &m=sonstige_steigern_kosten[t.getAttr("Fertigkeit")];
    for (int i=1;i<=22;++i)
       m[i]=t.getIntAttr("Wert"+itos(i),0);
}

void MidgardBasicElement::load_waffen_steigern_nach_schwierigkeit(const Tag &t)
{   std::map<int,int> &m=waffen_steigern_nach_schwierigkeit[t.getIntAttr("Schwierigkeit")];
    for (int i=1;i<=22;++i)
       m[i]=t.getIntAttr("Wert"+itos(i),0);
}

void MidgardBasicElement::get_Steigern_Kosten_map(const Tag &t)
{const Tag *kosten=t.find("Kosten");

 if (!kosten) 
 {  // steigern_wie herausfinden
    std::string steigern_wie;
    const Tag *steigern_wie_t=t.find("steigern_wie");
    if (steigern_wie_t) steigern_wie=steigern_wie_t->getAttr("Fertigkeit");
    else
    {  Ausgabe(Ausgabe::Warning,"keine Kosten für '"+Name()+"' gefunden");
       return;
    }
    
    // Kosten für steigern_wie suchen: 
    try
    {  if (steigern_wie=="-" || steigern_wie.empty()) return;
       else
       {  std::map<std::string,std::map<int,int> >::const_iterator i=
       		sonstige_steigern_kosten.find(steigern_wie);
       	  if (i!=sonstige_steigern_kosten.end())
       	  {  map_erfolgswert_kosten=i->second;
       	     return;
       	  }

          map_erfolgswert_kosten=cH_Fertigkeit(steigern_wie)->map_erfolgswert_kosten;
          return;
       }
    } 
    catch (const NotFound &e) // keine Fertigkeit
    {  Ausgabe(Ausgabe::Warning,"keine Kosten für '"+Name()+"/"+steigern_wie+"' gefunden");
       return;
    }
 }
 else 
    for (int i=1;i<=22;++i)
       map_erfolgswert_kosten[i]=kosten->getIntAttr("Wert"+itos(i),0);
}

void MidgardBasicElement::saveElementliste(Tag &datei,
			   const std::list<MBEmlt>& b,
                           const Grundwerte& Werte,
                           const std::vector<cH_Typen>& Typ)
{
  if(b.size()==0) return;
  for (std::list<MBEmlt>::const_iterator i=b.begin();i!=b.end();++i)
   {
      // oder <Beruf Wert=12>Arzt</Beruf> ?
      std::string type=(*(*i))->What_str();
      if (type.find('.')!=std::string::npos)
         type.replace(type.find('.'),1,"-");
      Tag &t=datei.push_back(Tag(type));
      t.setAttr("Bezeichnung", (*(*i))->Name());
      t.setIntAttr_nn("Wert", (*i)->Erfolgswert());
      t.setIntAttr_nn("Praxispunkte", (*i)->Praxispunkte());

      if ((*(*i))->What()==ZAUBERWERK)
      {  
        t.setAttr("Art", cH_Zauberwerk((*i)->getMBE())->Art());
        t.setAttr("Stufe", cH_Zauberwerk((*i)->getMBE())->Stufe());
      }
      if ((*(*i))->ZusatzEnum(Typ))
         t.setAttr("Zusatz", (*i)->Zusatz());
   }
}

  //////////////////////////////////////////////////////////////////////
  //Steigern von Fertigkeiten  
  
std::map<std::string,MidgardBasicElement::EP_t> MidgardBasicElement::verwendbareEP;

void MidgardBasicElement::EP_steigern(const std::string &fert,EP_t e)
{  verwendbareEP[fert]=e;
}

MidgardBasicElement::EP_t MidgardBasicElement::EP_steigern(const std::string &fert)
{  std::map<std::string,EP_t>::const_iterator i=verwendbareEP.find(fert);
   if (i!=verwendbareEP.end()) { steigern_mit_EP=i->second; return steigern_mit_EP; }
   try
   {  cH_Fertigkeit f=cH_Fertigkeit(fert);
      steigern_mit_EP=f->Steigern_mit_EP();
      return steigern_mit_EP;
   } catch (const NotFound &f)
   {  Ausgabe(Ausgabe::Warning, "EP_steigern: Fertigkeit "+fert+" (noch) unbekannt");
      return Nicht;
   }
}

MidgardBasicElement::EP_t MidgardBasicElement::EP_steigern_load(const Tag &t)
{ EP_t res=Nicht;
  const Tag *steigern=t.find("EP-Typ");
  if (steigern)
  {  if (steigern->getBoolAttr("KEP")) res|=KEP;
     if (steigern->getBoolAttr("ZEP")) res|=ZEP;
  }
  return res;
}

std::string MidgardBasicElement_mutable::Pflicht_str() const
{
  if (Pflicht()) return "X";
  else return "";
}

int MidgardBasicElement::FErfolgswert(const Abenteurer &abenteurer,const MBEmlt &mbem) const
{  return 0;
}

int MidgardBasicElement::Kosten(const Abenteurer &A) const 
{return (int)(Standard_Faktor(A)*GrundKosten());}

void operator|=(MidgardBasicElement::EP_t &a, MidgardBasicElement::EP_t b)
{  (int&)a|=int(b);
}

bool operator&(MidgardBasicElement::EP_t a, MidgardBasicElement::EP_t b)
{  return int(a)&int(b);
}

std::map<int,std::map<int,int> > MidgardBasicElement::waffen_steigern_nach_schwierigkeit;
std::map<std::string,std::map<int,int> > MidgardBasicElement::sonstige_steigern_kosten;
