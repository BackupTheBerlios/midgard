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
#include <Misc/itos.h>
#include "xml_fileselection.hh"
#include "recodestream.h"
#include <Misc/mystring.h>

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
  std::string strinfo = "Datei '"+dateiname+"' enth�lt nun die Daten des ";
  strinfo +="Abenteurers im Format f�r Midgard Publikationen\n";
  set_status(strinfo); 
  ofstream fout2(dateiname.c_str());
#ifdef __MINGW32__
  orecodestream fout(fout2);
#else
  ostream &fout=fout2;
#endif
  Grundwerte W=Char->getWerte();
  fout << W.Name_Abenteurer()<<", "
      <<Char->Typ1()->Name(W.Geschlecht())
      <<"               Gr "<<W.Grad()<<"\n";
  fout << W.Stand()<<", "
       <<W.Glaube()<<" - "
       <<W.GroesseBez() <<" ("
       <<W.Groesse()<<"cm), "
       <<W.Gestalt()<<" - "
       << W.Alter()<<" Jahre\n";
  fout << "\n";
  fout <<"St " <<W.St()
       <<", Gs "<<W.Gs()
       <<", Gw "<<W.Gw()
       <<", Ko "<<W.Ko()
       <<", In "<<W.In()
       <<", Zt "<<W.Zt()<<'\n'
       <<"Au "<<W.Au()
       <<", pA "<<W.pA()
       <<", Wk "<<W.Wk()
       <<", Sb "<<W.Sb()<<"\n";
  fout <<W.LP()<<" LP, "
       <<W.AP()<<" AP - "
       <<W.Ruestung()->Name()<<" - "
       << "B " << W.B() ;
  std::string boni;
  if     (W.bo_Sc()>0) boni+="SchB+"+itos(W.bo_Sc())+", ";
  else if(W.bo_Sc()<0) boni+="SchB" +itos(W.bo_Sc())+", ";
  if     (W.bo_Ab()>0) boni+="AbB+"+itos(W.bo_Ab())+", ";
  else if(W.bo_Ab()<0) boni+="AbB" +itos(W.bo_Ab())+", ";
  if     (W.bo_An()>0) boni+="AnB+"+itos(W.bo_An())+", ";
  else if(W.bo_An()<0) boni+="AnB" +itos(W.bo_An())+", ";
  ManuProC::remove_last_from(boni,",");
//  std::string::size_type st=boni.find_last_of(",");
//  if(st!=std::string::npos) boni.erase(st,1);
  if(!boni.empty()) fout <<" - "<<boni<<'\n';

  std::string angriff;
  for(std::list<MBEmlt>::const_iterator i=Char->List_Waffen().begin();i!=Char->List_Waffen().end();++i)
   {
    cH_Waffe w((*i)->getMBE());
    std::string name = (*(*i))->Name();
    int anbo = Char->getWerte().bo_An();
    if (w->Verteidigung())
        anbo = 0;
    int wert = (*i)->Erfolgswert() + anbo;
    std::string schaden;
    bool besitz=false;
    {WaffeBesitz WB(w,w->Name(),0,0,"","");
    schaden= WB.Schaden(getWerte(),w->Name(),true);
    }
    for(std::list<WaffeBesitz>::const_iterator j=Char->List_Waffen_besitz().begin();j!=Char->List_Waffen_besitz().end();++j)
     {
       WaffeBesitz WB=*j;
       if (WB.Waffe()->Name()==w->Name())
        {
          besitz=true;
          name = WB.AliasName();
          if (WB.av_Bonus()!=0 || WB.sl_Bonus()!=0) name +="$^*$";
          wert += WB.av_Bonus() + WB.Waffe()->WM_Angriff((*j)->Name());
          schaden=WB.Schaden(Char->getWerte(),WB->Name());
        }
      }
    angriff += name+"+"+itos(wert)+" ("+schaden+"), ";
   }
  ManuProC::remove_last_from(angriff,",");
//  std::string::size_type st2=angriff.find_last_of(",");
//  if(st2!=std::string::npos) angriff.erase(st2,2);
  if(!angriff.empty()) 
    { 
     fout << "\n\n";
     fout << "Angriff: ";
     fout <<angriff; 
    }
  fout << "; Raufen+"<<W.Raufen()<<" ("<<W.RaufenSchaden()<<")"; 
  fout <<" - Abwehr+"<<W.Abwehr_wert()+W.bo_Ab() <<", "
       <<"Resistenz+"<<W.Resistenz()+W.bo_Psy(Char->getVTyp())<<"/" 
                     <<W.Resistenz()+W.bo_Phs(Char->getVTyp())<<"/" 
                     <<W.Resistenz()+W.bo_Phk(Char->getVTyp())<<"\n" ;

 // angeborene Fertigkeiten
 std::string fert;
 for(std::list<MBEmlt>::const_iterator i=Char->List_Fertigkeit_ang().begin();i!=Char->List_Fertigkeit_ang().end();++i)
   {//cH_Fertigkeit_angeborene f(i->getMBE());
    std::string wert = "+"+itos((*i)->Erfolgswert());
    if (wert == "+0") wert = "";
    fert+=(*(*i))->Name()+wert+", ";
   }
 // Fertigkeiten
 for(std::list<MBEmlt>::const_iterator i=Char->List_Fertigkeit().begin();i!=Char->List_Fertigkeit().end();++i)
   { //cH_Fertigkeit f((*i)->getMBE());
    std::string wert = "+"+itos((*i)->Erfolgswert());
    if (wert == "+0") wert = "";
    fert+=(*(*i))->Name()+wert+", " ;
   }
 ManuProC::remove_last_from(fert,",");
// std::string::size_type st3=fert.find_last_of(",");
// if(st3!=std::string::npos) fert.erase(st3,2);
 fout << fert << "\n";

 std::string sinne;
 std::list<MBEmlt> vsinne=getWerte().Sinne() ;
 for (std::list<MBEmlt>::const_iterator i=vsinne.begin();i!=vsinne.end();++i)
  {
      sinne += (*(*i))->Name()+"+"+itos((*i)->Erfolgswert())+", ";
  }
 ManuProC::remove_last_from(sinne,",");
 fout << sinne<<"\n";

 std::string sprache;
 for (std::list<MBEmlt>::const_iterator i=Char->List_Sprache().begin();i!=Char->List_Sprache().end();++i)
   {
      sprache += (*(*i))->Name()+"+"+itos((*i)->Erfolgswert())+", ";
   }
 std::list<MBEmlt> verwandteSprachen=Sprache::getVerwandteSprachen(getChar()->List_Sprache(),getCDatabase().Sprache);
 for (std::list<MBEmlt>::const_iterator i=verwandteSprachen.begin();i!=verwandteSprachen.end();++i)
   {
      sprache += (*(*i))->Name()+"+("+itos((*i)->Erfolgswert())+"), ";
   }
 ManuProC::remove_last_from(sprache,",");
// std::string::size_type st4=sprache.find_last_of(",");
// if(st4!=std::string::npos) sprache.erase(st4,2);
 fout << "Sprechen: "<<sprache<<"\n";

 // Schreiben
 std::string schreiben;
 for (std::list<MBEmlt>::const_iterator i=Char->List_Schrift().begin();i!=Char->List_Schrift().end();++i)
   {
      schreiben += (*(*i))->Name()+"+"+itos((*i)->Erfolgswert())+", ";
   }
 ManuProC::remove_last_from(schreiben,",");
 fout << "Schreiben: "<<schreiben<<"\n\n";


 // Zauber
 if (Char->List_Zauber().size()!=0)
   {
     std::string zauber;
     zauber+="Zaubern+"+itos(W.Zaubern_wert()+Char->getWerte().bo_Za())+": ";
     for (std::list<MBEmlt>::const_iterator i=Char->List_Zauber().begin();i!=Char->List_Zauber().end();++i)
        zauber += (*(*i))->Name()+", ";
     ManuProC::remove_last_from(zauber,",");
//     std::string::size_type st=zauber.find_last_of(",");
//     if(st!=std::string::npos) zauber.erase(st,1);
     fout << zauber<<"\n\n";
   }  
 fout << W.Beschreibung()<<'\n';
}
