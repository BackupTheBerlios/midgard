// $Id: LaTeX_drucken_spielleiterbogen.cc,v 1.16 2002/09/21 18:00:13 thoma Exp $   
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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
#include "midgard_CG.hh"
#include "dtos1.h"
#include <Misc/itos.h>
#include "recodestream.h"

void LaTeX_drucken::Spielleiterbogen()
{
 const_cast<midgard_CG*>(hauptfenster)->Char.sort_gw(); // sortieren nach Gw
 std::string filename=get_latex_pathname(LaTeX_drucken::TeX_tmp)+get_latex_filename(LaTeX_drucken::TeX_Spielleiter);
 ofstream fout2((filename+".tex").c_str());
#ifdef __MINGW32__
 orecodestream fout(fout2);
#else
 ostream &fout=fout2;
#endif
 
 LaTeX_header(fout,false,false);           
 fout << "\\newcommand{\\n}{\\normalsize\\rule[-0.5ex]{0ex}{2.5ex}}\n";
 fout << "\\setlength{\\doublerulesep}{0.1mm}\n";
// fout << "\\fbox{\\parbox[t][22cm]{18cm}{ \n";
 fout << "\\vspace*{-2cm}\n\n";

 fout << "\\scalebox{0.97}{\\footnotesize\n";
 fout << "\\begin{tabular}{|||l|||\n";
 for(unsigned int i=0;i<hauptfenster->Char.getList().size();++i)
   fout << "c|"; // Anzahl der Spalten/Abenteurer
 fout << "||}\\hline\\hline\\hline\n";

 for(ewhat was=enamecharakter;was<eMAX; was=ewhat(int(was)+1))
   line(fout,was);

 fout << "\\end{tabular}\n";
 fout << "}\n"; //scalebox
// fout << "}}\n"; //fbox+parbox
 LaTeX_footer(fout);
 fout2.close();
 pdf_viewer(filename);
}

void LaTeX_drucken::line(ostream &fout,const ewhat &what)
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
     for_each(fout,what);
     fout << "\\\\\\hline\n";
   }
}

struct st_is{int e;std::string s;
      st_is(pair<int,bool> _e,std::string _s) : e(_e.first),s(_s){}
      st_is(int _e) : e(_e),s(itos(_e)) {}
   };
void LaTeX_drucken::for_each(ostream &fout,const ewhat& what)
{
 const Datenbank &Database=hauptfenster->getCDatabase();
 int maxlength=15;
 std::string cm="2.2cm";
 std::vector<st_is> V;
 for(std::list<VAbenteurer::st_abenteurer>::const_iterator i=hauptfenster->Char.getList().begin();i!=hauptfenster->Char.getList().end();++i)
  {
    const Grundwerte &W=i->abenteurer.getWerte();
    const Abenteurer &A=i->abenteurer;
    switch(what)
     {
       case enamespieler : fout << " & "<<LaTeX_scale(W.Name_Spieler(),maxlength,cm) ; break;
       case enamecharakter : fout << " & "<<LaTeX_scale(W.Name_Abenteurer(),maxlength,cm) ; break;
       case espez: fout << " & "<<LaTeX_scale(W.Spezies()->Name(),maxlength,cm); break; 
       case etyp: fout << " & "<<LaTeX_scale(i->abenteurer.STyp(),maxlength,cm); break; 
       case egrad: fout << " & "<<W.Grad()<<"/"<<W.GFP(); break; 
       case eherkunft: fout << " & "<<LaTeX_scale(W.Herkunft()->Name(),maxlength,cm); break; 
       case estand: fout << " & "<<LaTeX_scale(W.Stand(),maxlength,cm); break; 
       case egestalt: fout << " & "<<LaTeX_scale(W.Gestalt(),maxlength,cm); break; 
       case ekoerpergroesse: fout << " & "<<W.Groesse()<<" cm"; break; 
       case egewicht: fout << " & "<<W.Gewicht()<<" kg"; break; 
       case eBeruf: fout << " & "<<LaTeX_scale(i->abenteurer.Beruf(),maxlength,cm); break; 
       case eglaube: fout << " & "<<LaTeX_scale(W.Glaube(),maxlength,cm); break; 
       case est: V.push_back(st_is(W.St())); break;
       case egw: V.push_back(st_is(W.Gw())); break;
       case egs: V.push_back(st_is(W.Gs())); break;
       case eko: V.push_back(st_is(W.Ko())); break;
       case ein: V.push_back(st_is(W.In())); break;
       case ezt: V.push_back(st_is(W.Zt())); break;
       case eau: V.push_back(st_is(W.Au())); break;
       case epa: V.push_back(st_is(W.pA())); break;
       case ewk: V.push_back(st_is(W.Wk())); break;
       case esb: V.push_back(st_is(W.Sb())); break;
       case eb: {
           int b=hauptfenster->getChar().Erfolgswert("Laufen",hauptfenster->getCDatabase()).first;
           if(b==-99) b=0;
           else b-=2;
           int bs= W.B() + b;
           V.push_back(st_is(bs)); break;
          }
       case ezauber: V.push_back(st_is(W.Zaubern_wert())); break;
       case eabwehr:  V.push_back(st_is(W.Abwehr_wert())); break;
       case eres: fout << " & "<<W.Resistenzen_alle(hauptfenster->getChar().getVTyp()); break; 
       case esinnse: V.push_back(st_is(W.Sehen())); break;
       case esinnh: V.push_back(st_is(W.Hoeren())); break;
       case esinnr: V.push_back(st_is(W.Riechen())); break;
       case esinnsc: V.push_back(st_is(W.Schmecken())); break;
       case esinnt: V.push_back(st_is(W.Tasten())); break;
       case esinnss: V.push_back(st_is(W.SechsterSinn())); break;
       case eWahrnehmung:  V.push_back(st_is(A.Erfolgswert("Wahrnehmung",Database),A.SErfolgswert("Wahrnehmung",Database))); break;
       case eSpurenlesen: V.push_back(st_is(A.Erfolgswert("Spurenlesen",Database),A.SErfolgswert("Spurenlesen",Database))); break;
       case eFallen_entdecken: V.push_back(st_is(A.Erfolgswert("Fallen entdecken",Database),A.SErfolgswert("Fallen entdecken",Database))); break;
       case eSuchen: V.push_back(st_is(A.Erfolgswert("Suchen",Database),A.SErfolgswert("Suchen",Database))); break;
       case eMenschenkenntnis: V.push_back(st_is(A.Erfolgswert("Menschenkenntnis",Database),A.SErfolgswert("Menschenkenntnis",Database))); break;
       case eSagenkunde: V.push_back(st_is(A.Erfolgswert("Sagenkunde",Database),A.SErfolgswert("Sagenkunde",Database))); break;
       case eZauberkunde: V.push_back(st_is(A.Erfolgswert("Zauberkunde",Database),A.SErfolgswert("Zauberkunde",Database))); break;
       case eGassenwissen: V.push_back(st_is(A.Erfolgswert("Gassenwissen",Database),A.SErfolgswert("Gassenwissen",Database))); break;
       case eHimmelskunde: V.push_back(st_is(A.Erfolgswert("Himmelskunde",Database),A.SErfolgswert("Himmelskunde",Database))); break;
       case eSchaetzen: V.push_back(st_is(A.Erfolgswert("Schaetzen",Database),A.SErfolgswert("Schaetzen",Database))); break;
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


void LaTeX_drucken::list_for_each(ostream &fout,const std::list<MBEmlt>& L,const int &maxlength,const std::string& cm)
{
  fout << " & \\parbox{"<<cm<<"}{";
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();)
   {
     std::string s=(*i)->Name()+" (+"+itos((*i).Erfolgswert())+")";
     fout << LaTeX_scale(s,maxlength,cm);
     ++i;
     if(i!=L.end()) fout<<"\\newline ";
   }
  fout <<"}\n\t";
}

