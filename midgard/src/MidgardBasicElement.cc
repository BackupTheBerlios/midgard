/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
#include "class_SimpleTree.hh"
#include "SimpleTree.hh"
#include <Aux/itos.h>
#include "export_common.h"
#include "xml.h"
/*
cH_MidgardBasicElement::cache_t cH_MidgardBasicElement::cache;

cH_MidgardBasicElement::cH_MidgardBasicElement(const std::string& name)
{
 cH_MidgardBasicElement *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
   *this=cH_MidgardBasicElement(new MidgardBasicElement(name));
   cache.Register(name,*this);
  }
}
*/

void MidgardBasicElement::show_list_in_tree(
  const std::list<cH_MidgardBasicElement>& BasicList,
  SimpleTree *Tree,
  const Grundwerte& Werte, 
  const vector<cH_Typen>& Typ,bool clear_me)
{
  if (BasicList.begin()==BasicList.end() ) {Tree->clear(); return ;}
  std::vector<cH_RowDataBase> datavec;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=BasicList.begin();i!=BasicList.end();++i)
   {
      datavec.push_back(new Data_SimpleTree(*i,Typ,Werte));
   }
  Tree->setDataVec(datavec,clear_me);
}

void MidgardBasicElement::move_element(std::list<cH_MidgardBasicElement>& von,
                                       std::list<cH_MidgardBasicElement>& nach,
                                       const cH_MidgardBasicElement& MBE)
{
 for (std::list<cH_MidgardBasicElement>::iterator i=von.begin();i!= von.end();++i)
  {
   if((*i)->What()==ZAUBERWERK)
    {
      if ( (*i)->Name()==MBE->Name() && 
           cH_Zauberwerk(*i)->Art()==cH_Zauberwerk(MBE)->Art() && 
           (*i)->Stufe()==MBE->Stufe() ) 
        { nach.splice(nach.begin(),von,i);break; }
    }
   else
    {
      if ((*i)->Name()==MBE->Name()) 
        { nach.splice(nach.begin(),von,i);break; }
    }
  }
}

bool MidgardBasicElement::ist_lernbar(const vector<cH_Typen>& Typ,const map<std::string,std::string>& map_typ) const
{
  for (std::vector<cH_Typen>::const_iterator i=Typ.begin();i!=Typ.end();++i)
    if (const_cast<map<std::string,std::string>& >(map_typ)[(*i)->Short()]!="") 
      return true;
  return false;
}

bool MidgardBasicElement::ist_gelernt(const std::list<cH_MidgardBasicElement>& L) const
{
 for (std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
   {
     if((*i)->What()==ZAUBERWERK)
      {
        if((*i)->Name()==Name() &&
           cH_Zauberwerk(*i)->Art()==static_cast<const Zauberwerk*>(this)->Art() &&
           (*i)->Stufe()==Stufe())  return true ;
      }
     else 
      {  
     if((*i)->Name()==Name() && (*i)->Zusatz()==Zusatz()) return true;}
   }
 return false;
}

bool MidgardBasicElement::ist_gelernt(const std::list<std::string>& L) const
{
 for (std::list<std::string>::const_iterator i=L.begin();i!=L.end();++i)
   {
     if((*i)==Name()) return true;
   }
 return false;
}

std::string MidgardBasicElement::Standard__(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const
{
 vector<std::string> s = Standard(Werte,Typ);
 std::string s2=s[0];
 if(Typ[0]->Short()!="" && Typ[1]->Short()!="") s2+="/";
 if(Typ[1]->Short()!="") s2+=s[1];
 return s2;
}

vector<std::string> MidgardBasicElement::Standard(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const
{
 assert(Typ.size()==2);
 vector<std::string> s(2);
 for(map<std::string,std::string>::const_iterator i=map_typ.begin();i!=map_typ.end();++i)
   if(Typ[0]->Short()==i->first) {s[0]=i->second; break;}
 for(map<std::string,std::string>::const_iterator i=map_typ.begin();i!=map_typ.end();++i)
   if(Typ[1]->Short()==i->first) {s[1]=i->second; break;}

 s[0]=AusnahmenString(Werte,Typ[0],s[0]);
 s[1]=AusnahmenString(Werte,Typ[1],s[1]);

 return s;
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


double MidgardBasicElement::Standard_Faktor(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const
{
  double fac;
  if      (standard_one_G(Standard(Werte,Typ)) ) fac = 0.5;
  else if (standard_all_S(Standard(Werte,Typ)) ) fac = 1.0;
  else 
    { 
      fac = 2.0; 
      if (What()==ZAUBER || What()==ZAUBERWERK) fac=5.0;
    }
//cout <<Name()<<' ' <<"StandardFaktor = "<<fac<<"  Grundkosten= "<<GrundKosten()<<'\n';
  return fac;
}

bool MidgardBasicElement::standard_one_G(const vector<std::string>& s) const 
{
 assert(s.size()==2);
 if (s[0] == "G" || s[1] =="G" ) return true;
 return false;
}

bool MidgardBasicElement::standard_all_S(const vector<std::string>& s) const 
{
 assert(s.size()==2);
 if (s[0] == "S" && (s[1] =="S" || s[1]=="" )) return true;
 if (s[1] == "S" && (s[0] =="S" || s[0]=="" )) return true;
 return false;
}


int MidgardBasicElement::get_Steigern_Kosten(int erfolgswert) const
{
//cout << erfolgswert<<'\t'<<const_cast<std::map<int,int>& >(map_erfolgswert_kosten)[erfolgswert]<<'\t';
//cout << map_erfolgswert_kosten.size()<<'\n';
/*
for(std::map<int,int>::const_iterator i=map_erfolgswert_kosten.begin();i!=map_erfolgswert_kosten.end();++i)
{
cout << What()<<'\t'<<i->first<<'\t'<<i->second<<'\n';
}
*/
 return const_cast<std::map<int,int>& >(map_erfolgswert_kosten)[erfolgswert];
}

int MidgardBasicElement::Steigern(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const 
{ 
   int kosten=0;
   if(Erfolgswert()>0)
      kosten = get_Steigern_Kosten(Erfolgswert()+1);
   else 
      kosten = get_Steigern_Kosten(abs(Erfolgswert())-1);
   int back = int(Standard_Faktor(Werte,Typ)*kosten);
   return back;
}

int MidgardBasicElement::Reduzieren(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const 
{
   int kosten=0;
   if(Erfolgswert()>0)
      kosten = get_Steigern_Kosten(Erfolgswert());
   else 
      kosten = get_Steigern_Kosten(abs(Erfolgswert()));
   int back = int(Standard_Faktor(Werte,Typ)*kosten);
   return back;
}

int MidgardBasicElement::Verlernen(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const
{
//cout << "MidgardBasicElement::Verlernen "<<Name()<<' ' << Reduzieren(Typ,ausnahmen)<<'\n';
   if(Reduzieren(Werte,Typ)==0)
    {
        return Kosten(Werte,Typ);
    }      
   else return 0;
}


void MidgardBasicElement::get_map_typ()
{  
 const Tag *tag=this->tag;
 
 if(What()==SPRACHE) 
    tag=cH_Fertigkeit("Sprache")->tag;
 else if(What()==SCHRIFT)
    tag=cH_Fertigkeit("Schreiben")->tag;
 else if(What()==KIDO)
    tag=cH_Fertigkeit("KiDo")->tag;
 else assert(tag);

 if (tag)
 {  FOR_EACH_CONST_TAG(i,*tag)
    {  if (i->Type()=="Grund") map_typ[i->getAttr("Typ")]="G";
       else if (i->Type()=="Standard") map_typ[i->getAttr("Typ")]="S";
       else if (i->Type()=="Ausnahme") map_typ[i->getAttr("Typ")]="A";
    }
 }
}
 

void MidgardBasicElement::get_Steigern_Kosten_map()
{
 const Tag *tag=this->tag;
 const Tag *kosten=0;
 std::string steigern_wie=Name();
 
 if(What()==WAFFE) 
 {  assert(tag);
    typedef map<int,const Tag *> map_int_tag_t;
    static map_int_tag_t waffen_schwierigkeit;
    int schwierigkeit=tag->getIntAttr("Schwierigkeit");
    
    map_int_tag_t::const_iterator i=waffen_schwierigkeit.find(schwierigkeit);
    if (i==waffen_schwierigkeit.end())
    {  kosten=find_Tag("Waffen-Steigern","Kosten","Schwierigkeit",itos(schwierigkeit));
       waffen_schwierigkeit[schwierigkeit]=kosten;
    }
    else kosten=i->second;
 }
 else if(What()==SPRACHE) 
 { tag=cH_Fertigkeit("Sprache")->tag; steigern_wie="Sprache"; }
 else if(What()==SCHRIFT) 
 { tag=cH_Fertigkeit("Schreiben")->tag; steigern_wie="Schreiben"; }
 else assert(tag);

 if (!kosten)
 {  // steigern_wie herausfinden
    const Tag *steigern_wie_t=tag->find("steigern_wie");
    if (steigern_wie_t) steigern_wie=steigern_wie_t->getAttr("Fertigkeit");
    
    // Kosten f�r steigern_wie suchen: 
    // lokaler Cache, cH_Fertigkeit, dann SteigernKosten
    typedef map<std::string,const Tag *> map_string_tag_t;
    static map_string_tag_t steigern_kosten;

    try
    {  if (steigern_wie==Name()) steigern_wie_t=this->tag;
       else
       {  // zuerst in lokalen Cache (schneller)
          map_string_tag_t::const_iterator i=steigern_kosten.find(steigern_wie);
          if (i!=steigern_kosten.end()) kosten=i->second;
          // Fertigkeit suchen, wenn nicht gefunden wirft es NotFound
          else
             steigern_wie_t=cH_Fertigkeit(steigern_wie)->tag;
       }
          
       if (!kosten)
       {  if (steigern_wie_t)
             kosten=steigern_wie_t->find("Kosten");
          else cerr << "!steigern_wie_t: " << Name() << ',' << What() << '\n';
       }
    } 
    catch (const NotFound &e) // keine Fertigkeit
    {  kosten=find_Tag("SteigernKosten","Kosten","Fertigkeit",steigern_wie);
       steigern_kosten[steigern_wie]=kosten;
    }
 }
 if (!kosten) 
 { cerr << "keine Kosten f�r '" << steigern_wie << "' gefunden\n";
   return;
 }
 for (int i=1;i<=22;++i)
    map_erfolgswert_kosten[i]=kosten->getIntAttr("Wert"+itos(i),0/*??*/);
}

void MidgardBasicElement::saveElementliste(IF_XML(ostream &datei,)
			   const std::list<cH_MidgardBasicElement>& b,
                           const Grundwerte& Werte,
                           const vector<cH_Typen>& Typ)
{
  if(b.size()==0) return;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=b.begin();i!=b.end();++i)
   {
      // oder <Beruf Wert=12>Arzt</Beruf> ?
      std::string type=(*i)->What_str();
      if (type.find('.')!=string::npos)
         type.replace(type.find('.'),1,"-");
      datei << "    <" << type;
      write_string_attrib(datei, "Bezeichnung", (*i)->Name());
      write_int_attrib(datei, "Wert", (*i)->Erfolgswert());
//      write_string_attrib(datei, "Region", (*i)->Region());
      write_int_attrib(datei, "Praxispunkte", (*i)->Praxispunkte());

      if ((*i)->What()==ZAUBERWERK)
      {  
        write_string_attrib(datei, "Art", cH_Zauberwerk(*i)->Art());
        write_string_attrib(datei, "Stufe", cH_Zauberwerk(*i)->Stufe());
      }
      if ((*i)->ZusatzEnum(Typ))
         write_string_attrib(datei, "Zusatz", (*i)->Zusatz());
      datei << "/>\n";
   }
}

  //////////////////////////////////////////////////////////////////////
  //Steigern von Fertigkeiten  
void MidgardBasicElement::EP_steigern(const std::string fert)
{
// const Tag *tag=find_Tag("Fertigkeiten","Fertigkeit","Name",fert);
 const Tag *steigern=0;
 
 if (tag)
    // Fertigkeit gefunden
    steigern=tag->find("EP-Typ");
 else 
    // globale Liste: Ausdauer, Waffen, Zauber
  {
    steigern=find_Tag("verwendbareEP","EP-Typ","Fertigkeit",fert);
#warning Christof: Das funktioniert nicht :-(
cout << "\n\n\nverwendbareEP "<<fert<<' '<<steigern<<'\n';
  }

 int back=0;
 if (steigern)
 {  if (steigern->getBoolAttr("KEP")) back+=1;
    if (steigern->getBoolAttr("ZEP")) back+=2;
 }
 steigern_mit_EP=back;
}

MidgardBasicElement::MidgardBasicElement(const MidgardBasicElement &M)
       : name(M.name), region(M.region),kosten(M.kosten), 
         praxispunkte(M.praxispunkte),erfolgswert(M.erfolgswert),
         lernpunkte(M.lernpunkte), enum_zusatz(M.enum_zusatz),
         Vzusatz(M.Vzusatz),
         steigern_mit_EP(M.steigern_mit_EP),
         map_typ(M.map_typ),map_erfolgswert_kosten(M.map_erfolgswert_kosten)
{
cout << M.name << " copied\n";
}
