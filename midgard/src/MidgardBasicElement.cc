#include "MidgardBasicElement.hh"
#include "class_typen.hh"
#include "Grundwerte.hh"
#include "Fertigkeiten.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "KiDo.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "Sprache.hh"
#include "Schrift.hh"
#include "class_kido.hh"
#include "class_zauber.hh"
#include "class_fertigkeiten.hh"
#include "class_sprache_schrift.hh"
#include "class_waffen.hh"
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
  const vector<H_Data_typen>& Typ, const Ausnahmen& ausnahmen,
  char variante, bool _bool_)
{
  if (BasicList.begin()==BasicList.end() ) {Tree->clear(); return ;}
  std::vector<cH_RowDataBase> datavec;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=BasicList.begin();i!=BasicList.end();++i)
   {
    switch((*BasicList.begin())->What())
     {
       case(FERTIGKEIT) : {cH_Fertigkeit f(*i);
         if(variante=='O')  
            datavec.push_back(new Data_fert(f->Name(),f->Erfolgswert(),f->Steigern(Typ,ausnahmen),f->Reduzieren(Typ,ausnahmen),f->Verlernen(Typ,ausnahmen)));
         if(variante=='N')  
            datavec.push_back(new Data_fert(f->Name(),f->Erfolgswert(),f->Kosten(Typ,ausnahmen),f->Standard__(Typ,ausnahmen),f->Voraussetzung()));
         break; }
       case(FERTIGKEIT_ANG)      : break;
       case(WAFFEGRUND)  : {cH_WaffeGrund w(*i);
         if(variante=='O')  
            datavec.push_back(new Data_grund(w->Name()));
         if(variante=='N')  
            datavec.push_back(new Data_grund(w->Name(),w->Kosten(Typ,ausnahmen)));
          break; }
       case(WAFFE)      : {cH_Waffe w(*i);
         if(variante=='O')  
            datavec.push_back(new Data_waffen(w->Name(),w->Erfolgswert(),w->Steigern(Typ,ausnahmen),w->Reduzieren(Typ,ausnahmen),w->Verlernen(Typ,ausnahmen)));
         if(variante=='N')  
            datavec.push_back(new Data_waffen(w->Name(),w->Erfolgswert(),w->Voraussetzung()));
          break; }
       case(ZAUBER)      : {cH_Zauber z(*i);
          if (!_bool_ || (_bool_ &&  z->Spruchrolle())) 
           {int kosten=z->Kosten(Typ,ausnahmen);
            if(_bool_) kosten/=10; 
              datavec.push_back(new Data_zauber(z->Name(),z->Stufe(),z->Ursprung(),kosten,z->Standard__(Typ,ausnahmen)));   
           }
          break; }
       case(ZAUBERWERK)  : {cH_Zauberwerk z(*i); 
          if(variante=='O')  
              { if(_bool_) continue;
                datavec.push_back(new Data_zaubermittel(z->Stufe(),z->Name(),z->Art(),z->Kosten(Typ,ausnahmen)));
              }
          if(variante=='N')
                datavec.push_back(new Data_zaubermittel(z->Stufe(),z->Name(),z->Art(),z->Kosten(Typ,ausnahmen),z->Preis(),z->Zeitaufwand()));
          break; }
       case(KIDO)        : {cH_KiDo kd(*i);
               datavec.push_back(new Data_kido(kd->Hoho(),kd->Name(),kd->Stufe(),
                  kd->Ap(),kd->Kosten(Typ,ausnahmen),kd->Stil()));
          break; }
         case(SPRACHE)     : {cH_Sprache s(*i);
             if(variante=='O')
               datavec.push_back(new Data_sprache(s->Name(),s->Erfolgswert(),s->Steigern(Typ,ausnahmen),s->Reduzieren(Typ,ausnahmen),s->Verlernen(Typ,ausnahmen)));
             if(variante=='N')
               datavec.push_back(new Data_sprache(s->Name(),s->Urschrift(),0,s->Kosten(Typ,ausnahmen)));
          break; }
         case(SCHRIFT)     : {cH_Schrift s(*i);
               datavec.push_back(new Data_schrift(s->Name(),s->Art_der_Schrift(),s->Kosten(Typ,ausnahmen)));
          break; }
      }
   }
    Tree->setDataVec(datavec);
}

void MidgardBasicElement::move_element(std::list<cH_MidgardBasicElement>& von,std::list<cH_MidgardBasicElement>& nach,const std::string& name)
{
 for (std::list<cH_MidgardBasicElement>::iterator i=von.begin();i!= von.end();++i)
   if ((*i)->Name()==name) 
     { nach.splice(nach.begin(),von,i);break; }
}

bool MidgardBasicElement::ist_lernbar(const vector<H_Data_typen>& Typ,const map<std::string,std::string>& map_typ) const
{
  for (std::vector<H_Data_typen>::const_iterator i=Typ.begin();i!=Typ.end();++i)
    if (const_cast<map<std::string,std::string>& >(map_typ)[(*i)->Short()]!="") 
      return true;
  return false;
}

bool MidgardBasicElement::ist_gelernt(const std::list<cH_MidgardBasicElement>& L) const
{
 for (std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
   if((*i)->Name()==Name()) return true;
 return false;
}

std::string MidgardBasicElement::Standard__(const vector<H_Data_typen>& Typ,const Ausnahmen& a) const
{
 vector<std::string> s = Standard(Typ,a);
 std::string s2=s[0];
 if(Typ[0]->Short()!="" && Typ[1]->Short()!="") s2+="/";
 if(Typ[1]->Short()!="") s2+=s[1];
 return s2;
}

vector<std::string> MidgardBasicElement::Standard(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const
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

double MidgardBasicElement::Standard_Faktor(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const
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
 return const_cast<std::map<int,int>& >(map_erfolgswert_kosten)[erfolgswert];
}

int MidgardBasicElement::Steigern(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const 
{ 
   return int(Standard_Faktor(Typ,ausnahmen)*get_Steigern_Kosten(Erfolgswert()+1));
}
int MidgardBasicElement::Reduzieren(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const 
{
   return int(Standard_Faktor(Typ,ausnahmen)*get_Steigern_Kosten(Erfolgswert()));
}
int MidgardBasicElement::Verlernen(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const
{
   if(Reduzieren(Typ,ausnahmen)==0)
      return Kosten(Typ,ausnahmen);
   else return 0;
}

