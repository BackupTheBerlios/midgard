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
  const vector<cH_Typen>& Typ, const Ausnahmen& ausnahmen)
{
  if (BasicList.begin()==BasicList.end() ) {Tree->clear(); return ;}
  std::vector<cH_RowDataBase> datavec;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=BasicList.begin();i!=BasicList.end();++i)
   {
      datavec.push_back(new Data_SimpleTree(*i,Typ,ausnahmen,Werte));
   }
  Tree->setDataVec(datavec);
}

void MidgardBasicElement::move_element(std::list<cH_MidgardBasicElement>& von,
                                       std::list<cH_MidgardBasicElement>& nach,
                                       const std::string& name,
                                       const std::string& art)
{
 for (std::list<cH_MidgardBasicElement>::iterator i=von.begin();i!= von.end();++i)
  {
   if((*i)->What()==ZAUBERWERK)
    {
//cout << (*i)->Name()<<' '<<name <<' '<< cH_Zauberwerk(*i)->Art()<<' '<<art<<'\n';
      if ((*i)->Name()==name && cH_Zauberwerk(*i)->Art()==art) 
        { nach.splice(nach.begin(),von,i);break; }
    }
   else
    {
      if ((*i)->Name()==name) 
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
//cout << (*i)->Name()<<' '<<Name()<<'\n';
     if((*i)->Name()==Name()) return true;
   }
 return false;
}

std::string MidgardBasicElement::Standard__(const vector<cH_Typen>& Typ,const Ausnahmen& a) const
{
 vector<std::string> s = Standard(Typ,a);
 std::string s2=s[0];
 if(Typ[0]->Short()!="" && Typ[1]->Short()!="") s2+="/";
 if(Typ[1]->Short()!="") s2+=s[1];
 return s2;
}

vector<std::string> MidgardBasicElement::Standard(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const
{
 assert(Typ.size()==2);
 vector<std::string> s(2);
 for(map<std::string,std::string>::const_iterator i=map_typ.begin();i!=map_typ.end();++i)
   if(Typ[0]->Short()==i->first) {s[0]=i->second; break;}
 for(map<std::string,std::string>::const_iterator i=map_typ.begin();i!=map_typ.end();++i)
   if(Typ[1]->Short()==i->first) {s[1]=i->second; break;}
 ausnahmen.Ausnahmen_string(Name(),s);
 return s;
}

double MidgardBasicElement::Standard_Faktor(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const
{
  double fac = ausnahmen.Ausnahmen_float(Name());
  if (fac!=0) return fac;
  if      (standard_one_G(Standard(Typ,ausnahmen)) ) fac = 0.5;
  else if (standard_all_S(Standard(Typ,ausnahmen)) ) fac = 1.0;
  else { 
      fac = 2.0; 
      if (What()==ZAUBER || What()==ZAUBERWERK) fac=5.0;
    }
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
//for(std::map<int,int>::const_iterator i=map_erfolgswert_kosten.begin();i!=map_erfolgswert_kosten.end();++i)
//{
//cout << What()<<'\t'<<i->first<<'\t'<<i->second<<'\n';
//}
 return const_cast<std::map<int,int>& >(map_erfolgswert_kosten)[erfolgswert];
}

int MidgardBasicElement::Steigern(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const 
{ 
   int kosten=0;
   if(Erfolgswert()>0)
      kosten = get_Steigern_Kosten(Erfolgswert()+1);
   else 
      kosten = get_Steigern_Kosten(abs(Erfolgswert())-1);
   int back = int(Standard_Faktor(Typ,ausnahmen)*kosten);
   return back;
}
int MidgardBasicElement::Reduzieren(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const 
{
   int kosten=0;
   if(Erfolgswert()>0)
      kosten = get_Steigern_Kosten(Erfolgswert());
   else 
      kosten = get_Steigern_Kosten(abs(Erfolgswert()));
   int back = int(Standard_Faktor(Typ,ausnahmen)*kosten);
   return back;
}
int MidgardBasicElement::Verlernen(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const
{
//cout << "MidgardBasicElement::Verlernen "<<Name()<<' ' << Reduzieren(Typ,ausnahmen)<<'\n';
   if(Reduzieren(Typ,ausnahmen)==0)
    {
        return Kosten(Typ,ausnahmen);
    }      
   else return 0;
}

