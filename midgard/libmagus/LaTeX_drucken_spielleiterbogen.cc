// $Id: LaTeX_drucken_spielleiterbogen.cc,v 1.8 2004/12/21 08:17:45 thoma Exp $   
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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


#include "LaTeX_drucken.hh"
#include "dtos1.h"
#include <Misc/itos.h>
#include <Misc/recodestream.h>
#include "VAbenteurer.hh"
#include <fstream>
#include <TeX.h>

void LaTeX_drucken::Spielleiterbogen(VAbenteurer &VA)
{
 VA.sort_gw(); // sortieren nach Gw
 std::string filename=get_latex_pathname(LaTeX_drucken::TeX_tmp)+get_latex_filename(Abenteurer(),LaTeX_drucken::TeX_Spielleiter);
 std::ofstream fout2((filename+".tex").c_str());
 orecodestream fout(fout2);
 
 LaTeX_header(Abenteurer(),fout,false,false);
 LaTeX_header_doc(Abenteurer(),fout,false,false);
 fout << "\\newcommand{\\n}{\\normalsize\\rule[-0.5ex]{0ex}{2.5ex}}\n";
 fout << "\\setlength{\\doublerulesep}{0.1mm}\n";
// fout << "\\fbox{\\parbox[t][22cm]{18cm}{ \n";
 fout << "\\vspace*{-0cm}\n\n";

 fout << "\\scriptsize\n";
 fout << "\\begin{longtable}{|||l|||\n";
 for(unsigned int i=0;i<VA.getList().size();++i)
   fout << "c|"; // Anzahl der Spalten/Abenteurer
 fout << "||}\\hline\\hline\\hline\n";

 for(ewhat was=enamecharakter;was<eMAX; was=ewhat(int(was)+1))
   line(VA,fout,was);

 fout << "\\end{longtable}\n";
// fout << "}\n"; //scalebox
// fout << "}}\n"; //fbox+parbox
 LaTeX_footer(fout);
 fout2.close();
 pdf_viewer(filename,true);
}

void LaTeX_drucken::line(const VAbenteurer &VA,std::ostream &fout,const ewhat &what)
{
  std::string S;
  switch(what)
   {
     case enamespieler: S="Spieler"; break; 
     case enamecharakter: S="Figur"; break; 
     case espez: S="Spezies"; break; 
     case etyp: S="Typ"; break; 
     case egrad: S="Grad/GFP"; break; 
     case eherkunft: S="Herkunft"; break; 
     case estand: S="Stand"; break; 
     case egestalt: S="Gestalt"; break; 
     case ekoerpergroesse: S="Größe"; break; 
     case egewicht: S="Gewicht"; break; 
     case eBeruf: S="Beruf"; break; 
     case eglaube: S="Glaube"; break; 
     case est: S="St"; break; 
     case egw: S="Gw"; break; 
     case egs: S="Gs"; break; 
     case eko: S="Ko"; break; 
     case ein: S="In"; break; 
     case ezt: S="Zt"; break; 
     case eau: S="Au"; break; 
     case epa: S="pA"; break; 
     case ewk: S="Wk"; break; 
     case esb: S="Sb"; break; 
     case eb: S="B"; break; 
     case ezauber: S="Zaubern"; break; 
     case eabwehr: S="Abwehr"; break; 
     case eres: S="Resistenz"; break; 
     case esinnse: S="Sehen"; break; 
     case esinnh: S="Hören"; break; 
     case esinnr: S="Riechen"; break; 
     case esinnsc: S="Schmecken"; break; 
     case esinnt: S="Tasten"; break; 
     case esinnss: S="Sechster Sinn"; break; 
     case eWahrnehmung: S="Wahrnehmung"; break; 
     case eSpurenlesen: S="Spurenlesen"; break; 
     case eFallen_entdecken: S="Fallen entdecken"; break; 
     case eSuchen: S="Suchen"; break; 
     case eMenschenkenntnis: S="Menschenkenntnis"; break; 
     case eSagenkunde: S="Sagenkunde"; break; 
     case eZauberkunde: S="Zauberkunde"; break; 
     case eGassenwissen: S="Gassenwissen"; break; 
     case eHimmelskunde: S="Himmelskunde"; break; 
     case eSchaetzen: S="Schätzen"; break; 
     case eangFert: S="angeborene\\newline Fertigkeiten"; break; 
     case eWaffen: S="Waffen"; break;
     case eSprachen: S="Sprachen"; break; 
     case eSchriften: S="Schriften"; break; 
     default :break;
   }
  if(S!="")
   {
     fout << "\\n "<<S;
     for_each(VA,fout,what);
     fout << "\\\\\\hline\n";
   }
}

struct st_is{int e;std::string s;
      st_is(std::pair<int,bool> _e,std::string _s) : e(_e.first),s(_s){}
      st_is(int _e) : e(_e),s(itos(_e)) {}
   };
void LaTeX_drucken::for_each(const VAbenteurer &VA,std::ostream &fout,const ewhat& what)
{
 int maxlength=15;
 std::string cm="2.2cm";
 std::vector<st_is> V;
 for(VAbenteurer::const_iterator i=VA.getList().begin();i!=VA.getList().end();++i)
  {
    const Abenteurer &A=i->getAbenteurer();
    switch(what)
     {
       case enamespieler : fout << " & "<<TeX::scale(A.Name_Spieler(),maxlength,cm) ; break;
       case enamecharakter : fout << " & "<<TeX::scale(A.Name_Abenteurer(),maxlength,cm) ; break;
       case espez: fout << " & "<<TeX::scale(A.Spezies()->Name(),maxlength,cm); break; 
       case etyp: fout << " & "<<TeX::scale(A.STyp(),maxlength,cm); break; 
       case egrad: fout << " & "<<A.Grad()<<"/"<<A.GFP(); break; 
       case eherkunft: fout << " & "<<TeX::scale(A.Herkunft()->Name(),maxlength,cm); break; 
       case estand: fout << " & "<<TeX::scale(A.Stand(),maxlength,cm); break; 
       case egestalt: fout << " & "<<TeX::scale(A.Gestalt(),maxlength,cm); break; 
       case ekoerpergroesse: fout << " & "<<A.Groesse()<<" cm"; break; 
       case egewicht: fout << " & "<<A.Gewicht()<<" kg"; break; 
       case eBeruf: fout << " & "<<TeX::scale(A.Beruf(),maxlength,cm); break; 
       case eglaube: fout << " & "<<TeX::scale(A.Glaube(),maxlength,cm); break; 
       case est: V.push_back(st_is(A.St())); break;
       case egw: V.push_back(st_is(A.Gw())); break;
       case egs: V.push_back(st_is(A.Gs())); break;
       case eko: V.push_back(st_is(A.Ko())); break;
       case ein: V.push_back(st_is(A.In())); break;
       case ezt: V.push_back(st_is(A.Zt())); break;
       case eau: V.push_back(st_is(A.Au())); break;
       case epa: V.push_back(st_is(A.pA())); break;
       case ewk: V.push_back(st_is(A.Wk())); break;
       case esb: V.push_back(st_is(A.Sb())); break;
       case eb: {
           int b=A.Erfolgswert("Laufen").first;
           if(b==-99) b=0;
           else b-=2;
           int bs= A.B() + b;
           V.push_back(st_is(bs)); break;
          }
       case ezauber: V.push_back(st_is(A.Zaubern_wert())); break;
       case eabwehr:  V.push_back(st_is(A.Abwehr_wert())); break;
       case eres: fout << " & "<<A.Resistenzen_alle(); break; 
       case esinnse: V.push_back(st_is(A.Sehen())); break;
       case esinnh: V.push_back(st_is(A.Hoeren())); break;
       case esinnr: V.push_back(st_is(A.Riechen())); break;
       case esinnsc: V.push_back(st_is(A.Schmecken())); break;
       case esinnt: V.push_back(st_is(A.Tasten())); break;
       case esinnss: V.push_back(st_is(A.SechsterSinn())); break;
       case eWahrnehmung:  V.push_back(st_is(A.Erfolgswert("Wahrnehmung"),A.SErfolgswert("Wahrnehmung"))); break;
       case eSpurenlesen: V.push_back(st_is(A.Erfolgswert("Spurenlesen"),A.SErfolgswert("Spurenlesen"))); break;
       case eFallen_entdecken: V.push_back(st_is(A.Erfolgswert("Fallen entdecken"),A.SErfolgswert("Fallen entdecken"))); break;
       case eSuchen: V.push_back(st_is(A.Erfolgswert("Suchen"),A.SErfolgswert("Suchen"))); break;
       case eMenschenkenntnis: V.push_back(st_is(A.Erfolgswert("Menschenkenntnis"),A.SErfolgswert("Menschenkenntnis"))); break;
       case eSagenkunde: V.push_back(st_is(A.Erfolgswert("Sagenkunde"),A.SErfolgswert("Sagenkunde"))); break;
       case eZauberkunde: V.push_back(st_is(A.Erfolgswert("Zauberkunde"),A.SErfolgswert("Zauberkunde"))); break;
       case eGassenwissen: V.push_back(st_is(A.Erfolgswert("Gassenwissen"),A.SErfolgswert("Gassenwissen"))); break;
       case eHimmelskunde: V.push_back(st_is(A.Erfolgswert("Himmelskunde"),A.SErfolgswert("Himmelskunde"))); break;
       case eSchaetzen: V.push_back(st_is(A.Erfolgswert("Schaetzen"),A.SErfolgswert("Schaetzen"))); break;
       case eangFert: list_for_each(fout,A.List_Fertigkeit_ang(),maxlength,cm); break;
       case eWaffen: list_for_each(fout,A.List_Waffen(),maxlength,cm); break;
       case eSprachen: list_for_each(fout,A.List_Sprache(),maxlength,cm); break;
       case eSchriften: list_for_each(fout,A.List_Schrift(),maxlength,cm); break;
       default: break;
     }
   }
 int max=-1;
 int min=99;
 for(std::vector<st_is>::iterator i=V.begin();i!=V.end();++i)
  {  if(i->e>max)  max=i->e  ;
     if(i->e<min)  min=i->e  ; }
 for(std::vector<st_is>::const_iterator i=V.begin();i!=V.end();++i)
  {
    fout << " & ";
    if(i->e==max && max!=min) fout << "\\bf ";
    fout <<i->s; 
  }
}


void LaTeX_drucken::list_for_each(std::ostream &fout,const std::list<MBEmlt>& L,const int &maxlength,const std::string& cm)
{
  fout << " & \\parbox{"<<cm<<"}{";
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();)
   {
     std::string s=(*(*i))->Name()+" (+"+itos((*i)->Erfolgswert())+")";
     fout << TeX::scale(s,maxlength,cm);
     ++i;
     if(i!=L.end()) fout<<"\\newline ";
   }
  fout <<"}\n\t";
}

