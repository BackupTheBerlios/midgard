/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include <Ausnahmen.hh>
#include <midgard_CG.hh>
//#include <gtk--/progressbar.h>
#include "ProgressBar.h"

Ausnahmen::Ausnahmen(Gtk::ProgressBar *progressbar)
{
 const Tag *Fertigkeiten=xml_data->find("Fertigkeiten");
 if (Fertigkeiten)
 {  Tag::const_iterator b=Fertigkeiten->begin(),e=Fertigkeiten->end();
    double size=(e-b)*2;
    FOR_EACH_CONST_TAG_OF_5(i,*Fertigkeiten,b,e,"Fertigkeit")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       FOR_EACH_CONST_TAG_OF(j,*i,"regionaleBesonderheit")
       {  st_index1 index(j->getAttr("Typ"),j->getAttr("Herkunft"),
       			j->getAttr("Spezies"),j->getAttr("Beruf"),j->getAttr("Stand"));
          Data_Ausnahmen DA(i->getAttr("Name"),"f",j->getAttr("Standard"));
       }
    }
 }
 const Tag *Zauber=xml_data->find("Zauber");
 if (Zauber)
 {  Tag::const_iterator b=Zauber->begin(),e=Zauber->end();
    double size=(e-b)*2;
    FOR_EACH_CONST_TAG_OF_5(i,*Zauber,b,e,"Spruch")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size+.5);
       FOR_EACH_CONST_TAG_OF(j,*i,"regionaleBesonderheit")
       {  st_index1 index(j->getAttr("Typ"),j->getAttr("Herkunft"),
       			j->getAttr("Spezies"),j->getAttr("Beruf"),j->getAttr("Stand"));
          Data_Ausnahmen DA(i->getAttr("Name"),"z",j->getAttr("Standard"));
       }
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}

double Ausnahmen::Ausnahmen_float(const std::string& name) const
{
  assert(Typ.size()==2);
  for(std::map<st_index1,Data_Ausnahmen>::const_iterator i=map_ausnahmen.begin();i!=map_ausnahmen.end();++i)
   {
     if (i->second.Name()!=name) continue;
     if (i->first.typ == Typ[0]->Short() || (Typ[1]->Short()!= "" && i->first.typ == Typ[1]->Short()))
      {
        if ( (i->first.spezies  !="" && i->first.spezies  == Werte.Spezies()->Name() ) || 
             (i->first.herkunft !="" && i->first.herkunft == Werte.Herkunft()->Name() )) 
          return i->second.Fac();
      }
     if (i->first.stand != "" && i->first.stand==Werte.Stand() )
          return i->second.Fac();
     if (i->first.herkunft != "" && i->first.herkunft==Werte.Herkunft()->Name() )
          return i->second.Fac();
     for(std::list<cH_MidgardBasicElement>::const_iterator j=list_Beruf.begin();j!=list_Beruf.end();++j)
      if(i->first.beruf==(*j)->Name())  return i->second.Fac() ;
   }
 return 0;
}

void Ausnahmen::Ausnahmen_string(const std::string& name, 
                vector<std::string>& standard) const
{
  assert(Typ.size()==2);
  assert(standard.size()==2);
  for(std::map<st_index1,Data_Ausnahmen>::const_iterator i=map_ausnahmen.begin();i!=map_ausnahmen.end();++i)
   {
     if (i->second.Name()!=name) continue;
     if (i->first.typ == Typ[0]->Short() || (Typ[1]->Short()!= "" && i->first.typ == Typ[1]->Short()))
      {
        if ( (i->first.spezies  !="" && i->first.spezies  == Werte.Spezies()->Name() ) || 
             (i->first.herkunft !="" && i->first.herkunft == Werte.Herkunft()->Name() )) 
          i->second.Standard(standard);
      }
     if (i->first.stand != "" && i->first.stand==Werte.Stand() )
          i->second.Standard(standard);
     if (i->first.herkunft != "" && i->first.herkunft==Werte.Herkunft()->Name() )
          i->second.Standard(standard);
     for(std::list<cH_MidgardBasicElement>::const_iterator j=list_Beruf.begin();j!=list_Beruf.end();++j)
      if(i->first.beruf==(*j)->Name())  i->second.Standard(standard);
   }
}

double Data_Ausnahmen::Fac() const
{
  double fac;
  if (standard == "G" )                       fac = 0.5;
  else if (standard == "S" )                  fac = 1.0;
  else if (standard == "A" && Art()=="f" )    fac = 2.0;
  else if (standard == "A" && Art()=="z" )    fac = 5.0;
  else abort();
  return fac;
}

