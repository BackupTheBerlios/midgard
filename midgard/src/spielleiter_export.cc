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
#include "WindowInfo.hh"


void midgard_CG::spielleiter_export()
{
  std::string strinfo = "Datei 'spielleiter_export.txt' enthält nun die Daten des \n";
  strinfo +="Charakters im Format für Midgard Publikationen\n";
  manage (new WindowInfo(strinfo));
  ofstream fout("spielleiter_export.txt");
  fout << Werte.Name_Charakter()<<", "<<Typ.Name()<<",   Grad "<<Werte.Grad()<<"\n";
  fout << Werte.Stand()<<", "<<Werte.Glaube()<<" - ("<<Werte.Groesse()<<"cm) - "
       << Werte.Alter()<<" Jahre\n";
  fout << "\n";
  fout << "St "<<Werte.St()<<", Ge"<<Werte.Ge()<<", Ko"<<Werte.Ko()<<", In"<<Werte.In()
       << ", Zt"<<Werte.Zt()<<", Au"<<Werte.Au()<<", pA"<<Werte.pA()<<", Sb"<<Werte.Sb()<<"\n";
  fout << Werte.LP()<<"LP, "<<Werte.AP()<<"AP - "<<Werte.Ruestung()<<" - RW "
       << Werte.RW()<<", HGW "<<Werte.HGW()<<", B " << Werte.B() ;
  if (Werte.bo_Sc() != 0 || Werte.bo_Ab() != 0 || Werte.bo_An() != 0) fout <<" - ";
  if (Werte.bo_Sc() != 0) fout << "SchB+"<<Werte.bo_Sc();
  if (Werte.bo_Sc() != 0 || Werte.bo_Ab() != 0 ) fout <<", ";
  if (Werte.bo_Ab() != 0) fout << "AbB+"<<Werte.bo_Ab();
  if (Werte.bo_An() != 0) fout <<", AnB+" << Werte.bo_Sc();
  fout << "\n\n";
  fout << "Angriff: ";

// for (unsigned int i=0;i<vec_waffen.size();++i)
  for(std::vector<H_Data_waffen>::const_iterator i=vec_Waffen.begin();i!=vec_Waffen.end();++i)
   {
    std::string wert = itos((*i)->Erfolgswert());
//    for (unsigned int j=0; j<waffe_besitz.size();++j)
    for(std::vector<H_Data_waffen>::const_iterator j=vec_Waffen_besitz.begin();j!=vec_Waffen_besitz.end();++j)
     {
      if ((*j)->Name()==(*i)->Name())
       {
         std::string waffenname ;
         waffenname = (*j)->Alias();
         fout <<waffenname ;
         if ((*j)->av_Bonus()!=0 || (*j)->sl_Bonus()!=0) fout <<"$^*$";
         int mag_schadensbonus = (*j)->av_Bonus();
         int ang_mod = atoi(waffe_werte(*j,Werte,"WM_Angriff").c_str());
         if ((*j)->av_Bonus()==-5 && (*j)->sl_Bonus()==-5) mag_schadensbonus = 0; 
         int anbo = Werte.bo_An();
//         if (midgard_CG::waffe_werte(waffe_besitz[j],Werte,"Verteidigung")=="true")
         if (midgard_CG::waffe_werte(*j,Werte,"Verteidigung")=="true")
            anbo = 0;
         int wert = (*i)->Erfolgswert() + anbo + mag_schadensbonus + ang_mod;
         fout << "+"<<wert << "(";
//         std::string schaden=midgard_CG::waffe_werte(waffe_besitz[j],Werte,"Schaden+mag_Bonus");
         std::string schaden=midgard_CG::waffe_werte(*j,Werte,"Schaden+mag_Bonus");
         fout << schaden << ")";
       }
      fout << ", ";
     }
   }

 fout <<" - Abwehr+"<<Werte.Abwehr_wert()+Werte.bo_Ab() <<", "
      <<"Resistenz+"<<Werte.Resistenz()+Werte.bo_Psy()<<"/" 
                    <<Werte.Resistenz()+Werte.bo_Phs()<<"/" 
                    <<Werte.Resistenz()+Werte.bo_Phk()<<"\n\n" ;

 // angeborene Fertigkeiten
// for (unsigned int i=0;i<vec_an_fertigkeit.size();++i)
 for(std::vector<H_Data_fert>::const_iterator i=vec_an_Fertigkeit.begin();i!=vec_an_Fertigkeit.end();++i)
   {
    std::string wert = "+"+itos((*i)->Erfolgswert());
    if (wert == "+0") wert = "";
    fout <<(*i)->Name() << wert ;
    fout << ", ";
   }
 // Fertigkeiten
 for(std::vector<H_Data_fert>::const_iterator i=vec_Fertigkeiten.begin();i!=vec_Fertigkeiten.end();++i)
// for (unsigned int i=0;i<vec_fertigkeiten.size();++i)
   {
    std::string wert = "+"+itos((*i)->Erfolgswert());
    if (wert == "+0") wert = "";
    fout <<(*i)->Name() << wert ;
//    if (i!=vec_fertigkeiten.size()-1) fout << ", ";
    if (i != vec_Fertigkeiten.end()) fout << ", ";
   }
 fout << " - ";
// for (unsigned int i=0; i<vec_sprachen.size();++i)
 for (std::vector<H_Data_sprache>::const_iterator i=vec_Sprachen.begin();i!=vec_Sprachen.end();++i)
   {
      fout << (*i)->Name() << " " << (*i)->Wert() ;
      if (i!=vec_Sprachen.end()) fout <<", ";
   }
  // Zauber
 if (vec_Zauber.size()!=0)
   {
     fout << "\n\n";
     fout << "Zaubern+"<<atoi((Werte.Zaubern_wert()).c_str())+Werte.bo_Za()<<": ";
     for (std::vector<H_Data_zauber>::const_iterator i=vec_Zauber.begin();i!=vec_Zauber.end();)
      {
        fout << (*i)->Name() ;
//        if (i!=zauber.size()-1) fout << ", ";
        if (i!=vec_Zauber.end()) fout << ", ";
        ++i;
      }
   }  
 fout << "\n";
}
