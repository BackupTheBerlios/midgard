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

#ifdef __MINGW32__
std::string utf82iso(const std::string &s);
#define LATIN(x) utf82iso(x)
#else
#define LATIN(x) (x)
#endif

void midgard_CG::on_exportieren_activate()
{
#ifndef __MINGW32__
 manage 
#else
 delete
#endif
	 (new xml_fileselection(this,xml_fileselection::Export));
}

void midgard_CG::spielleiter_export_save(const std::string& dateiname)
{
  std::string strinfo = "Datei '"+dateiname+"' enthält nun die Daten des \n";
  strinfo +="Abenteurers im Format für Midgard Publikationen\n";
  InfoFenster->AppendShow(strinfo);
  ofstream fout(dateiname.c_str());
  fout << LATIN(Char.getCWerte().Name_Abenteurer())<<", "
      <<LATIN(Char.CTyp1()->Name(Char.getCWerte().Geschlecht()))<<",   Grad "<<Char.getCWerte().Grad()<<"\n";
  fout << LATIN(Char.getCWerte().Stand())<<", "<<LATIN(Char.getCWerte().Glaube())<<" - ("<<Char.getCWerte().Groesse()<<"cm) - "
       << Char.getCWerte().Alter()<<" Jahre\n";
  fout << "\n";
  fout << "St "<<Char.getCWerte().St()
       <<", Gw"<<Char.getCWerte().Gw()
       <<", Gs"<<Char.getCWerte().Gs()
       <<", Ko"<<Char.getCWerte().Ko()
       <<", In"<<Char.getCWerte().In()
       <<", Zt"<<Char.getCWerte().Zt()
       <<", Au"<<Char.getCWerte().Au()
       <<", pA"<<Char.getCWerte().pA()
       <<", Wk"<<Char.getCWerte().Wk()
       <<", Sb"<<Char.getCWerte().Sb()<<"\n";
  fout <<Char.getCWerte().LP()<<"LP, "
       <<Char.getCWerte().AP()<<"AP - "
       <<LATIN(Char.getCWerte().Ruestung()->Name())<<" -  "
       << ", B " << Char.getCWerte().B() ;
  if (Char.getCWerte().bo_Sc() != 0 || Char.getCWerte().bo_Ab() != 0 || Char.getCWerte().bo_An() != 0) fout <<" - ";
  if (Char.getCWerte().bo_Sc() != 0) fout << "SchB+"<<Char.getCWerte().bo_Sc();
  if (Char.getCWerte().bo_Sc() != 0 || Char.getCWerte().bo_Ab() != 0 ) fout <<", ";
  if (Char.getCWerte().bo_Ab() != 0) fout << "AbB+"<<Char.getCWerte().bo_Ab();
  if (Char.getCWerte().bo_An() != 0) fout <<", AnB+" << Char.getCWerte().bo_Sc();
  fout << "\n\n";
  fout << "Angriff: ";

  for(std::list<cH_MidgardBasicElement>::const_iterator i=Char.CList_Waffen().begin();i!=Char.CList_Waffen().end();++i)
   {cH_Waffe w(*i);
    std::string wert = itos(w->Erfolgswert());
    for(std::list<cH_MidgardBasicElement>::const_iterator j=Char.CList_Waffen_besitz().begin();j!=Char.CList_Waffen_besitz().end();++j)
     {
      cH_WaffeBesitz WB(*j);
      if (WB->Waffe()->Name()==w->Name())
       {
         std::string waffenname ;
         waffenname = WB->Name();
         fout <<LATIN(waffenname) ;
         if (WB->av_Bonus()!=0 || WB->sl_Bonus()!=0) fout <<"$^*$";
         int mag_schadensbonus = WB->av_Bonus();
         int ang_mod = WB->Waffe()->WM_Angriff((*j)->Name());
//         if (WB->av_Bonus()==-5 && WB->sl_Bonus()==-5) mag_schadensbonus = 0; 
         int anbo = Char.getCWerte().bo_An();
         if (WB->Waffe()->Verteidigung())
            anbo = 0;
         int wert = w->Erfolgswert() + anbo + mag_schadensbonus + ang_mod;
         fout << "+"<<wert << "(";
         std::string schaden=WB->Schaden(Char.getCWerte(),WB->Name());
         fout << schaden << ")";
       }
      fout << ", ";
     }
   }

 fout <<" - Abwehr+"<<Char.getCWerte().Abwehr_wert()+Char.getCWerte().bo_Ab() <<", "
      <<"Resistenz+"<<Char.getCWerte().Resistenz()+Char.getCWerte().bo_Psy(Char.getVTyp())<<"/" 
                    <<Char.getCWerte().Resistenz()+Char.getCWerte().bo_Phs(Char.getVTyp())<<"/" 
                    <<Char.getCWerte().Resistenz()+Char.getCWerte().bo_Phk(Char.getVTyp())<<"\n\n" ;

 // angeborene Fertigkeiten
 for(std::list<cH_MidgardBasicElement>::const_iterator i=Char.CList_Fertigkeit_ang().begin();i!=Char.CList_Fertigkeit_ang().end();++i)
   {cH_Fertigkeit_angeborene f(*i);
    std::string wert = "+"+itos(f->Erfolgswert());
    if (wert == "+0") wert = "";
    fout <<LATIN(f->Name()) << wert ;
    fout << ", ";
   }
 // Fertigkeiten
 for(std::list<cH_MidgardBasicElement>::const_iterator i=Char.CList_Fertigkeit().begin();i!=Char.CList_Fertigkeit().end();++i)
   { cH_Fertigkeit f(*i);
    std::string wert = "+"+itos(f->Erfolgswert());
    if (wert == "+0") wert = "";
    fout <<LATIN(f->Name()) << wert ;
//    if (i!=vec_fertigkeiten.size()-1) fout << ", ";
    if (i != Char.CList_Fertigkeit().end()) fout << ", ";
   }
 fout << " - ";
 for (std::list<cH_MidgardBasicElement>::const_iterator i=Char.CList_Sprache().begin();i!=Char.CList_Sprache().end();++i)
   {
      fout << LATIN(cH_Sprache(*i)->Name()) << " " << cH_Sprache(*i)->Erfolgswert() ;
      if (i!=Char.CList_Sprache().end()) fout <<", ";
   }
  // Zauber
 if (Char.CList_Zauber().size()!=0)
   {
     fout << "\n\n";
     fout << "Zaubern+"<<Char.getCWerte().Zaubern_wert()+Char.getCWerte().bo_Za()<<": ";
     for (std::list<cH_MidgardBasicElement>::const_iterator i=Char.CList_Zauber().begin();i!=Char.CList_Zauber().end();)
      {
        cH_Zauber z(*i);      
        fout << LATIN(z->Name()) ;
//        if (i!=zauber.size()-1) fout << ", ";
        if (i!=Char.CList_Zauber().end()) fout << ", ";
        ++i;
      }
   }  
 fout << "\n";
}
