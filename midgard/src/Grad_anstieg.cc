/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002      Christof Petig 
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

#include "Grad_anstieg.hh"
#include "xml.h"
#include "ProgressBar.h"
#include <Misc/itos.h>

Grad_anstieg::Grad_anstieg(Gtk::ProgressBar *progressbar)
//: steigern_EP_prozent(50), grad_basiswerte(1)
{
 const Tag *Gradanstieg=xml_data->find("Gradanstieg");
 if (Gradanstieg)
 {  Tag::const_iterator b=Gradanstieg->begin(),e=Gradanstieg->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*Gradanstieg,b,e,"Grad")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       const Tag *Kosten=i->find("Kosten");
       map_grad[i->getIntAttr("Grad")]=
       	st_grad(i->getIntAttr("Abwehr"),Kosten->getIntAttr("Abwehr"),
       		i->getIntAttr("Resistenz"),Kosten->getIntAttr("Resistenz"),
       		i->getIntAttr("Zaubern"),Kosten->getIntAttr("Zaubern"),
       		i->getIntAttr("GFP"), i->getIntAttr("Schicksalsgunst"),
       		Kosten->getIntAttr("Ausdauer",i->getIntAttr("AP_Kosten")));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
 fill_kosten_maps();
}

void Grad_anstieg::fill_kosten_maps()
{
  for(std::map<int,st_grad>::const_iterator i=map_grad.begin();i!=map_grad.end();++i)
   {
     map_Abwehr_kosten[i->second.abwehr]=i->second.abwehr_kosten;
     map_Resistenz_kosten[i->second.resistenz]=i->second.resistenz_kosten;
     map_Zaubern_kosten[i->second.zaubern]=i->second.zaubern_kosten;
   }
}

int Grad_anstieg::get_AP_Kosten(int grad)  const
{
  int x=0; 
  while(x==0)   x = map_grad[grad--].ap_kosten;
  return x;
}

int Grad_anstieg::get_MaxAbwehr(int grad)   const
{
  int x=0; 
  while(x==0)   x = map_grad[grad--].abwehr;
  return x;
}

int Grad_anstieg::get_Abwehr_Kosten(int erfolgswert) const
{
  return map_Abwehr_kosten[erfolgswert]; 
}

int Grad_anstieg::get_MaxZauber(int grad)  const
{
  int x=0; 
  while(x==0)   x = map_grad[grad--].zaubern;
  return x;
}

int Grad_anstieg::get_Zauber_Kosten(int erfolgswert)  const
{
  return map_Zaubern_kosten[erfolgswert]; 
}

int Grad_anstieg::get_MaxResistenz(int grad)  const
{
  int x=0; 
  while(x==0)   x = map_grad[grad--].resistenz;
  return x;
}

int Grad_anstieg::get_Resistenz_Kosten(int erfolgswert)   const
{
  return map_Resistenz_kosten[erfolgswert]; 
}

int Grad_anstieg::get_Schicksalsgunst(int grad)   const
{
  return map_grad[grad].schicksalsgunst;
}

int Grad_anstieg::get_Grad(int gfp) const
{
 if(gfp<0)gfp=0;
 map<int,st_grad>::const_reverse_iterator e=map_grad.rend();
 for(map<int,st_grad>::const_reverse_iterator i=map_grad.rbegin();i!=e;++i)
   { 
//cout<<gfp<<'\t'<< i->second.gfp<<'\t'<<i->first<<'\n';
    if( i->second.gfp <= gfp) 
       return i->first;
   }
 assert(0);
}

std::string Grad_anstieg::getGFP_for_str(ewas ew,const Grundwerte& Werte) const
{
 int back=getGFP_for(ew,Werte);
 if(ew==Grad_fehlt)
  {
   if(back==0)  return "erreicht";
   else return "Noch "+itos(back)+" GFP";;
  }
 else
  {
   if(back==0) return "";
   else return itos(back)+" GFP";
  }
}

int Grad_anstieg::getGFP_for(ewas ew,const Grundwerte& Werte) const
{
  int wert, maxwert, kosten;
  int maxgrad=get_Grad(Werte.GFP());
  switch(ew) {
    case Grad_    :  return map_grad[Werte.Grad()].gfp ;
    case Grad_fehlt : 
                    if(maxgrad>Werte.Grad()) return 0;
                    else return map_grad[Werte.Grad()+1].gfp-Werte.GFP();      
    case Abwehr   : maxwert=get_MaxAbwehr(Werte.Grad()); 
                    wert=Werte.Abwehr_wert();
                    kosten = map_Abwehr_kosten[Werte.Abwehr_wert()+1];
                    break;
    case Zaubern  : maxwert=get_MaxZauber(Werte.Grad()); 
                    wert=Werte.Zaubern_wert();
                    kosten = map_Zaubern_kosten[Werte.Zaubern_wert()+1];
                    break;
    case Resistenz: maxwert=get_MaxResistenz(Werte.Grad()); 
                    wert=Werte.Resistenz();
                    kosten = map_Resistenz_kosten[Werte.Resistenz()+1];
                    break;
    case Ausdauer : maxwert=999; 
                    wert=Werte.AP();
                    kosten=map_grad[Werte.Grad()].ap_kosten;
                    break;
   }
   if(maxwert<=wert) return 0;
   else return kosten;
}


int Grad_anstieg::getGFP(int grad) const
{
 return map_grad[grad].gfp;
}

