/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "Sprache.hh"
#include "Fertigkeiten_angeboren.hh"
#include "Waffe.hh"
#include <fstream>
#include "Zauber.hh"
#include <Misc/itos.h>
#include <Misc/recodestream.h>
#include <Misc/mystring.h>
#include "Ausgabe.hh"
#include "Abenteurer.hh"
#include "Datenbank.hh"
#include "spielleiter_export.hh"
#include "Zauberwerk.hh"

static void spielleiter_export_save_zauber(const Abenteurer &Char, std::ostream& fout, bool full);
static void spielleiter_export_save_ausruestung(const Abenteurer &A, std::ostream &fout);

void spielleiter_export_save(const Abenteurer &Char,const std::string& dateiname,bool full)
{
  std::ofstream fout2(dateiname.c_str());
  orecodestream fout(fout2);
  const Grundwerte &W=Char;
  fout << W.Name_Abenteurer()<<", "
      <<Char.Typ1()->Name(W.Geschlecht())
      <<"               Gr "<<W.Grad()<<"\n";
  fout << W.Stand()<<", "
       <<W.Glaube()<<" - "
       <<W.GroesseBez() <<" ("
       <<W.Groesse()<<"cm), "
       <<W.Gestalt()<<" - "
       << W.Alter()<<" Jahre\n";
  fout << "\n";
  if(full)
  {  fout <<  W.Gewicht()+ "kg, "<<W.Hand()<<'\n'
          <<  W.Herkunft()->Name()<<", "<<W.Spezialisierung()<<'\n'
          <<  "Göttliche Gnade: "<<W.GG()<<", Schicksalsgunst: "<<W.SG()<<'\n'
          <<  "GFP: "<<W.GFP()<<", AEP: "<<W.AEP()<<", KEP: "<<W.KEP()<<", ZEP:"<<W.ZEP()<<'\n';
  }
                                             
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
  if (full)
   {
     if     (W.bo_Au()>0) boni+="AuB+"+itos(W.bo_Au())+", ";
     else if(W.bo_Au()<0) boni+="AuB" +itos(W.bo_Au())+", ";
     if     (W.bo_Za()>0) boni+="ZauB+"+itos(W.bo_Za())+", ";
     else if(W.bo_Za()<0) boni+="ZauB" +itos(W.bo_Za())+", ";
     if     (W.bo_Psy()>0) boni+="GeistB+"+itos(W.bo_Psy())+", ";
     else if(W.bo_Psy()<0) boni+="GeistB" +itos(W.bo_Psy())+", ";
     if     (W.bo_Phs()>0) boni+="KörperB+"+itos(W.bo_Phs())+", ";
     else if(W.bo_Phs()<0) boni+="KörperB" +itos(W.bo_Phs())+", ";
     if     (W.bo_Phk()>0) boni+="UmgebungB+"+itos(W.bo_Phk())+", ";
     else if(W.bo_Phk()<0) boni+="UmgebungB" +itos(W.bo_Phk())+", ";
   }
  ManuProC::remove_last_from(boni,", ");
  if(!boni.empty()) fout <<" - "<<boni<<'\n';

  std::string angriff;
  for(std::list<MBEmlt>::const_iterator i=Char.List_Waffen().begin();i!=Char.List_Waffen().end();++i)
   {
    cH_Waffe w((*i)->getMBE());
    std::string name = (*(*i))->Name();
    int anbo = Char.bo_An();
    if (w->Verteidigung())
        anbo = 0;
    int wert = (*i)->Erfolgswert() + anbo;
    std::string schaden;
    bool besitz=false;
    {WaffeBesitz WB(w,w->Name(),0,0,"","");
    schaden= "$"+WB.Schaden(Char,w->Name())+"$";
    }
    for(std::list<H_WaffeBesitz>::const_iterator j=Char.List_Waffen_besitz().begin();j!=Char.List_Waffen_besitz().end();++j)
     {
       H_WaffeBesitz WB=*j;
       if (WB->Waffe()->Name()==w->Name())
        {
          besitz=true;
          name = WB->AliasName();
//LaTeX          if (WB->av_Bonus()!=0 || WB->sl_Bonus()!=0) name +="$^*$";
          if (WB->av_Bonus()!=0 || WB->sl_Bonus()!=0) name +="*";
          wert += WB->av_Bonus() + WB->Waffe()->WM_Angriff((**j)->Name());
          schaden=WB->Schaden(Char,(*WB)->Name());
        }
      }
    angriff += name+"+"+itos(wert)+" ("+schaden+"), ";
   }
  ManuProC::remove_last_from(angriff,",");
  if(!angriff.empty()) 
    { 
     fout << "\n\n";
     fout << "Angriff: ";
     fout <<angriff; 
    }
  fout << "; Raufen+"<<W.Raufen()<<" ("<<W.RaufenSchaden()<<")"; 
  fout <<" - Abwehr+"<<W.Abwehr_wert()+W.bo_Ab() <<", "
       <<"Resistenz+"<<W.Resistenz()+W.bo_Psy()<<"/" 
                     <<W.Resistenz()+W.bo_Phs()<<"/" 
                     <<W.Resistenz()+W.bo_Phk()<<"\n" ;

 // angeborene Fertigkeiten
 std::string fert;
 for(std::list<MBEmlt>::const_iterator i=Char.List_Fertigkeit_ang().begin();i!=Char.List_Fertigkeit_ang().end();++i)
   {//cH_Fertigkeit_angeborene f(i->getMBE());
    std::string wert = "+"+itos((*i)->Erfolgswert());
    if (wert == "+0") wert = "";
    fert+=(*(*i))->Name()+wert+", ";
   }
 // Fertigkeiten
 for(std::list<MBEmlt>::const_iterator i=Char.List_Fertigkeit().begin();i!=Char.List_Fertigkeit().end();++i)
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
 std::list<MBEmlt> vsinne=Char.Sinne() ;
 for (std::list<MBEmlt>::const_iterator i=vsinne.begin();i!=vsinne.end();++i)
  {
      sinne += (*(*i))->Name()+"+"+itos((*i)->Erfolgswert())+", ";
  }
 ManuProC::remove_last_from(sinne,",");
 fout << sinne<<"\n";

 std::string sprache;
 for (std::list<MBEmlt>::const_iterator i=Char.List_Sprache().begin();i!=Char.List_Sprache().end();++i)
   {
      sprache += (*(*i))->Name()+"+"+itos((*i)->Erfolgswert())+", ";
   }
 std::list<MBEmlt> verwandteSprachen=Sprache::getVerwandteSprachen(Char.List_Sprache(),Datenbank.Sprache);
 for (std::list<MBEmlt>::const_iterator i=verwandteSprachen.begin();i!=verwandteSprachen.end();++i)
   {
      sprache += (*(*i))->Name()+"+("+itos((*i)->Erfolgswert())+"), ";
   }
 ManuProC::remove_last_from(sprache,",");
 fout << "Sprechen: "<<sprache<<"\n";

 // Schreiben
 std::string schreiben;
 for (std::list<MBEmlt>::const_iterator i=Char.List_Schrift().begin();i!=Char.List_Schrift().end();++i)
   {
      schreiben += (*(*i))->Name()+"+"+itos((*i)->Erfolgswert())+", ";
   }
 ManuProC::remove_last_from(schreiben,",");
 fout << "Schreiben: "<<schreiben<<"\n\n";

 // WaffenGrundfertigkeiten:
 if(full)
  {
    std::string waffengrund;
    for(std::list<MBEmlt>::const_iterator i=Char.List_WaffenGrund().begin();i!=Char.List_WaffenGrund().end();++i)
     { waffengrund+=(*(*i))->Name()+", ";
     }
    ManuProC::remove_last_from(waffengrund,",");
    fout << "Waffen Grundkenntnisse: "<<waffengrund<<"\n\n";
  }  

 // Zauber
 if (Char.List_Zauber().size()!=0)
    spielleiter_export_save_zauber(Char,fout,full);

 if(full)
  {
    spielleiter_export_save_ausruestung(Char,fout);
    fout <<"Geld: "<<W.Gold()<<" GS, "<<W.Silber()<<" SS, "<<W.Kupfer()<<" KS\n\n";
  }

 fout << W.Beschreibung()<<'\n';
  if(!full)  Ausgabe(Ausgabe::Log,"Datei '"+dateiname+"' enthält nun die Daten des "
                       "Abenteurers im Format für Midgard Publikationen");
  else Ausgabe(Ausgabe::Log,"Datei '"+dateiname+"' enthält nun die kompletten Daten des "
                   "Abenteurers");
}

static void spielleiter_export_save_zauber(const Abenteurer &Char, std::ostream& fout,bool full)
{
//  Grundwerte &W=Char;
  std::map<int,std::list<MBEmlt> > ZL;
  for (std::list<MBEmlt>::const_iterator i=Char.List_Zauber().begin();i!=Char.List_Zauber().end();++i)
     ZL[cH_Zauber((*i)->getMBE())->Erfolgswert_Z(Char)].push_back(*i);

  for(std::map<int,std::list<MBEmlt> >::const_iterator i=ZL.begin();i!=ZL.end();++i)
   {
     std::string z;
     z+="Zaubern+"+itos(i->first)+": ";
     for (std::list<MBEmlt>::const_iterator j=i->second.begin();j!=i->second.end();++j)
        z += (*(*j))->Name()+", ";
     ManuProC::remove_last_from(z,",");
     fout << z<<"\n";
   }
  fout << "\n";

// Zaubermittel
  if(full)
   {
     std::map<std::string,std::list<MBEmlt> > ZM;
     for (std::list<MBEmlt>::const_iterator i=Char.List_Zauberwerk().begin();i!=Char.List_Zauberwerk().end();++i)
        ZM[cH_Zauberwerk((*i)->getMBE())->Art()].push_back(*i);

     for(std::map<std::string,std::list<MBEmlt> >::const_iterator i=ZM.begin();i!=ZM.end();++i)
      {
        std::string z=i->first+": ";
        if(i->first.empty()) z="Zauberwerk: ";
        for (std::list<MBEmlt>::const_iterator j=i->second.begin();j!=i->second.end();++j)
           z += (*(*j))->Name()+", ";
        ManuProC::remove_last_from(z,",");
        fout << z<<"\n";
      }
     fout << "\n";
   }
}

static void spielleiter_export_save_ausruestung(const Abenteurer &A, std::ostream &fout)
{
   std::string w="Waffenbesitz: ";
   for (std::list<H_WaffeBesitz>::const_iterator i=A.List_Waffen_besitz().begin();i!=A.List_Waffen_besitz().end();++i)
    {
      w+= (*i)->AliasName();
      if ((*i)->Magisch()!="" || (*i)->av_Bonus()!=0 || (*i)->sl_Bonus()!=0)
           w+="* "+(*i)->Bonus() ;
      w+= (*i)->Waffe()->Text();
      w+=" ("+(*i)->Schaden(A,(*i)->AliasName())+")";  
//      std::string ws = (*i)->Schaden(A,(*i)->AliasName());
      w+=", ";
    }
    ManuProC::remove_last_from(w,",");
    fout << w<<"\n\n";
}

