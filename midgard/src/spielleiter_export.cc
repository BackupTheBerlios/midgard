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

#include "midgard_CG.hh"
#include "Sprache.hh"
#include "Fertigkeiten_angeboren.hh"
#include "Waffe.hh"
#include <fstream>
#include "Zauber.hh"
#include <Aux/itos.h>
#include "xml_fileselection.hh"


void midgard_CG::spielleiter_export()
{
 manage (new xml_fileselection(this,xml_fileselection::Export));
}


void midgard_CG::spielleiter_export_save(const std::string& dateiname)
{
  std::string strinfo = "Datei '"+dateiname+"' enthält nun die Daten des \n";
  strinfo +="Abenteurers im Format für Midgard Publikationen\n";
  InfoFenster->AppendShow(strinfo);
  ofstream fout(dateiname.c_str());
  fout << Werte.Name_Abenteurer()<<", "
      <<Typ[0]->Name(Werte.Geschlecht())<<",   Grad "<<Werte.Grad()<<"\n";
  fout << Werte.Stand()<<", "<<Werte.Glaube()<<" - ("<<Werte.Groesse()<<"cm) - "
       << Werte.Alter()<<" Jahre\n";
  fout << "\n";
  fout << "St "<<Werte.St()<<", Ge"<<Werte.Gw()<<", Gs"<<Werte.Gs()<<", Ko"<<Werte.Ko()<<", In"<<Werte.In()
       << ", Zt"<<Werte.Zt()<<", Au"<<Werte.Au()<<", pA"<<Werte.pA()<<", Sb"<<Werte.Sb()<<"\n";
  fout << Werte.LP()<<"LP, "<<Werte.AP()<<"AP - "<<Werte.Ruestung()->Name()<<" - RW "
       <<", HGW "<<", B " << Werte.B() ;
  if (Werte.bo_Sc() != 0 || Werte.bo_Ab() != 0 || Werte.bo_An() != 0) fout <<" - ";
  if (Werte.bo_Sc() != 0) fout << "SchB+"<<Werte.bo_Sc();
  if (Werte.bo_Sc() != 0 || Werte.bo_Ab() != 0 ) fout <<", ";
  if (Werte.bo_Ab() != 0) fout << "AbB+"<<Werte.bo_Ab();
  if (Werte.bo_An() != 0) fout <<", AnB+" << Werte.bo_Sc();
  fout << "\n\n";
  fout << "Angriff: ";

  for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
   {cH_Waffe w(*i);
    std::string wert = itos(w->Erfolgswert());
    for(std::list<cH_MidgardBasicElement>::const_iterator j=list_Waffen_besitz.begin();j!=list_Waffen_besitz.end();++j)
     {
      cH_WaffeBesitz WB(*j);
      if (WB->Waffe()->Name()==w->Name())
       {
         std::string waffenname ;
         waffenname = WB->Name();
         fout <<waffenname ;
         if (WB->av_Bonus()!=0 || WB->sl_Bonus()!=0) fout <<"$^*$";
         int mag_schadensbonus = WB->av_Bonus();
         int ang_mod = WB->Waffe()->WM_Angriff((*j)->Name());
//         if (WB->av_Bonus()==-5 && WB->sl_Bonus()==-5) mag_schadensbonus = 0; 
         int anbo = Werte.bo_An();
         if (WB->Waffe()->Verteidigung())
            anbo = 0;
         int wert = w->Erfolgswert() + anbo + mag_schadensbonus + ang_mod;
         fout << "+"<<wert << "(";
         std::string schaden=WB->Schaden(Werte,WB->Name());
         fout << schaden << ")";
       }
      fout << ", ";
     }
   }

 fout <<" - Abwehr+"<<Werte.Abwehr_wert()+Werte.bo_Ab() <<", "
      <<"Resistenz+"<<Werte.Resistenz()+Werte.bo_Psy(Typ)<<"/" 
                    <<Werte.Resistenz()+Werte.bo_Phs(Typ)<<"/" 
                    <<Werte.Resistenz()+Werte.bo_Phk(Typ)<<"\n\n" ;

 // angeborene Fertigkeiten
 for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit_ang.begin();i!=list_Fertigkeit_ang.end();++i)
   {cH_Fertigkeit_angeborene f(*i);
    std::string wert = "+"+itos(f->Erfolgswert());
    if (wert == "+0") wert = "";
    fout <<f->Name() << wert ;
    fout << ", ";
   }
 // Fertigkeiten
 for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i)
   { cH_Fertigkeit f(*i);
    std::string wert = "+"+itos(f->Erfolgswert());
    if (wert == "+0") wert = "";
    fout <<f->Name() << wert ;
//    if (i!=vec_fertigkeiten.size()-1) fout << ", ";
    if (i != list_Fertigkeit.end()) fout << ", ";
   }
 fout << " - ";
 for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Sprache.begin();i!=list_Sprache.end();++i)
   {
      fout << cH_Sprache(*i)->Name() << " " << cH_Sprache(*i)->Erfolgswert() ;
      if (i!=list_Sprache.end()) fout <<", ";
   }
  // Zauber
 if (list_Zauber.size()!=0)
   {
     fout << "\n\n";
     fout << "Zaubern+"<<Werte.Zaubern_wert()+Werte.bo_Za()<<": ";
     for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Zauber.begin();i!=list_Zauber.end();)
      {
        cH_Zauber z(*i);      
        fout << z->Name() ;
//        if (i!=zauber.size()-1) fout << ", ";
        if (i!=list_Zauber.end()) fout << ", ";
        ++i;
      }
   }  
 fout << "\n";
}
