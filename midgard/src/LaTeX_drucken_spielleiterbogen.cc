// $Id: LaTeX_drucken_spielleiterbogen.cc,v 1.14 2002/07/18 15:50:03 thoma Exp $   
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

 for(ewhat was=etyp;was<eMAX; was=ewhat(int(was)+1))
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
  fout << "\\n ";
  switch(what)
   {
     case enamespieler: fout << "Spieler"; break; 
     case enamecharakter: fout << "Figur"; break; 
     case espez: fout << "Spezies"; break; 
     case etyp: fout << "Typ"; break; 
     case egrad: fout << "Grad/GFP"; break; 
     case eherkunft: fout << "Herkunft"; break; 
     case estand: fout << "Stand"; break; 
     case egestalt: fout << "Gestalt"; break; 
     case ekoerpergroesse: fout << "Größe"; break; 
     case egewicht: fout << "Gewicht"; break; 
     case eBeruf: fout << "Beruf"; break; 
     case eglaube: fout << "Glaube"; break; 
     case est: fout << "St"; break; 
     case egw: fout << "Gw"; break; 
     case egs: fout << "Gs"; break; 
     case eko: fout << "Ko"; break; 
     case ein: fout << "In"; break; 
     case ezt: fout << "Zt"; break; 
     case eau: fout << "Au"; break; 
     case epa: fout << "pA"; break; 
     case ewk: fout << "Wk"; break; 
     case esb: fout << "Sb"; break; 
     case eb: fout << "B"; break; 
     case ezauber: fout << "Zaubern"; break; 
     case eabwehr: fout << "Abwehr"; break; 
     case eres: fout << "Resistenz"; break; 
     case esinnse: fout << "Sehen"; break; 
     case esinnh: fout << "Hören"; break; 
     case esinnr: fout << "Riechen"; break; 
     case esinnsc: fout << "Schmecken"; break; 
     case esinnt: fout << "Tasten"; break; 
     case esinnss: fout << "Sechster Sinn"; break; 
     case eWahrnehmung: fout << "Wahrnehmung"; break; 
     case eSpurenlesen: fout << "Spurenlesen"; break; 
     case eFallen_entdecken: fout << "Fallen entdecken"; break; 
     case eSuchen: fout << "Suchen"; break; 
     case eMenschenkenntnis: fout << "Menschenkenntnis"; break; 
     case eSagenkunde: fout << "Sagenkunde"; break; 
     case eZauberkunde: fout << "Zauberkunde"; break; 
     case eGassenwissen: fout << "Gassenwissen"; break; 
     case eHimmelskunde: fout << "Himmelskunde"; break; 
     case eSchaetzen: fout << "Schätzen"; break; 
     case eangFert: fout << "angeborene\\newline Fertigkeiten"; break; 
     case eWaffen: fout << "Waffen"; break;
     case eSprachen: fout << "Sprachen"; break; 
     case eSchriften: fout << "Schriften"; break; 
     default :break;
   }
  for_each(fout,what);
  fout << "\\\\\\hline\n";
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
/*
       case eb: {
        int b=hauptfenster->getChar().Erfolgswert("Laufen",hauptfenster->getCDatabase()).first-2;
        int bs=W.B()+b;
        V.push_back(st_is(b)); break;
          }
*/
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


void LaTeX_drucken::list_for_each(ostream &fout,const std::list<MidgardBasicElement_mutable>& L,const int &maxlength,const std::string& cm)
{
  fout << " & \\parbox{"<<cm<<"}{";
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L.begin();i!=L.end();)
   {
     std::string s=(*i)->Name()+" (+"+itos((*i).Erfolgswert())+")";
     fout << LaTeX_scale(s,maxlength,cm);
     ++i;
     if(i!=L.end()) fout<<"\\newline ";
   }
  fout <<"}\n\t";
}

