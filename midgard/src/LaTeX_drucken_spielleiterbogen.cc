// $Id: LaTeX_drucken_spielleiterbogen.cc,v 1.9 2002/06/19 07:53:37 thoma Exp $   
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
#include <Aux/itos.h>

void LaTeX_drucken::Spielleiterbogen()
{
 const_cast<midgard_CG*>(hauptfenster)->Char.sort_gw(); // sortieren nach Gw
 std::string filename=get_latex_pathname(LaTeX_drucken::TeX_tmp)+get_latex_filename(LaTeX_drucken::TeX_Spielleiter);
 ofstream fout((filename+".tex").c_str());
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

 line(fout,SName);
 line(fout,AName);
 line(fout,Spezies);
 line(fout,Typ);
 line(fout,Grad);
 line(fout,Herkunft);
 line(fout,Stand);
 line(fout,Gestalt);
 line(fout,Groesse);
 line(fout,Gewicht);
 line(fout,Beruf);
 line(fout,Glaube);
 line(fout,St);
 line(fout,Gw);
 line(fout,Gs);
 line(fout,Ko);
 line(fout,In);
 line(fout,Zt);
 line(fout,Au);
 line(fout,pA);
 line(fout,Wk);
 line(fout,Sb);
 line(fout,B);
 line(fout,Abwehr);
 line(fout,Zaubern);
 line(fout,Resistenz);
 line(fout,Sehen);
 line(fout,Hoeren);
 line(fout,Riechen);
 line(fout,Schmecken);
 line(fout,Tasten);
 line(fout,SechsterSinn);
 line(fout,Wahrnehmung);
 line(fout,Spurenlesen);
 line(fout,Fallen_entdecken);
 line(fout,Suchen);
 line(fout,Menschenkenntnis);
 line(fout,Sagenkunde);
 line(fout,Zauberkunde);
 line(fout,Gassenwissen);
 line(fout,Himmelskunde);
 line(fout,Schaetzen);
 line(fout,angFert);
 line(fout,Waffen);
 line(fout,Sprachen);
 line(fout,Schriften);

 fout << "\\end{tabular}\n";
 fout << "}\n"; //scalebox
// fout << "}}\n"; //fbox+parbox
 LaTeX_footer(fout);
 fout.close();
 pdf_viewer(filename);
}

void LaTeX_drucken::line(ofstream &fout,const ewhat &what)
{
  fout << "\\n ";
  switch(what)
   {
     case SName: fout << "Spieler"; break; 
     case AName: fout << "Figur"; break; 
     case Spezies: fout << "Spezies"; break; 
     case Typ: fout << "Typ"; break; 
     case Grad: fout << "Grad/GFP"; break; 
     case Herkunft: fout << "Herkunft"; break; 
     case Stand: fout << "Stand"; break; 
     case Gestalt: fout << "Gestalt"; break; 
     case Groesse: fout << "Groesse"; break; 
     case Gewicht: fout << "Gewicht"; break; 
     case Beruf: fout << "Beruf"; break; 
     case Glaube: fout << "Glaube"; break; 
     case St: fout << "St"; break; 
     case Gw: fout << "Gw"; break; 
     case Gs: fout << "Gs"; break; 
     case Ko: fout << "Ko"; break; 
     case In: fout << "In"; break; 
     case Zt: fout << "Zt"; break; 
     case Au: fout << "Au"; break; 
     case pA: fout << "pA"; break; 
     case Wk: fout << "Wk"; break; 
     case Sb: fout << "Sb"; break; 
     case B: fout << "B"; break; 
     case Zaubern: fout << "Zaubern"; break; 
     case Abwehr: fout << "Abwehr"; break; 
     case Resistenz: fout << "Resistenz"; break; 
     case Sehen: fout << "Sehen"; break; 
     case Hoeren: fout << "Hoeren"; break; 
     case Riechen: fout << "Riechen"; break; 
     case Schmecken: fout << "Schmecken"; break; 
     case Tasten: fout << "Tasten"; break; 
     case SechsterSinn: fout << "Sechster Sinn"; break; 
     case Wahrnehmung: fout << "Wahrnehmung"; break; 
     case Spurenlesen: fout << "Spurenlesen"; break; 
     case Fallen_entdecken: fout << "Fallen entdecken"; break; 
     case Suchen: fout << "Suchen"; break; 
     case Menschenkenntnis: fout << "Menschenkenntnis"; break; 
     case Sagenkunde: fout << "Sagenkunde"; break; 
     case Zauberkunde: fout << "Zauberkunde"; break; 
     case Gassenwissen: fout << "Gassenwissen"; break; 
     case Himmelskunde: fout << "Himmelskunde"; break; 
     case Schaetzen: fout << "Schätzen"; break; 
     case angFert: fout << "angeborne\\newline Fertigkeiten"; break; 
     case Waffen: fout << "Waffen"; break;
     case Sprachen: fout << "Sprachen"; break; 
     case Schriften: fout << "Schriften"; break; 
   }
  for_each(fout,what);
  fout << "\\\\\\hline\n";
}

struct st_is{int e;std::string s;
      st_is(pair<int,bool> _e,std::string _s) : e(_e.first),s(_s){}
      st_is(int _e) : e(_e),s(itos(_e)) {}
   };
void LaTeX_drucken::for_each(ofstream &fout,const ewhat& what)
{
 const Datenbank &Database=hauptfenster->getCDatabase();
 int maxlength=15;
 std::string cm="2.2cm";
 std::vector<st_is> V;
 for(std::list<VAbenteurer::st_abenteurer>::const_iterator i=hauptfenster->Char.getList().begin();i!=hauptfenster->Char.getList().end();++i)
  {
    const Grundwerte &W=i->abenteurer.getCWerte();
    const Abenteurer &A=i->abenteurer;
    switch(what)
     {
       case SName : fout << " & "<<LaTeX_scale(W.Name_Spieler(),maxlength,cm) ; break;
       case AName : fout << " & "<<LaTeX_scale(W.Name_Abenteurer(),maxlength,cm) ; break;
       case Spezies: fout << " & "<<LaTeX_scale(W.Spezies()->Name(),maxlength,cm); break; 
       case Typ: fout << " & "<<LaTeX_scale(i->abenteurer.STyp(),maxlength,cm); break; 
       case Grad: fout << " & "<<W.Grad()<<"/"<<W.GFP(); break; 
       case Herkunft: fout << " & "<<LaTeX_scale(W.Herkunft()->Name(),maxlength,cm); break; 
       case Stand: fout << " & "<<LaTeX_scale(W.Stand(),maxlength,cm); break; 
       case Gestalt: fout << " & "<<LaTeX_scale(W.Gestalt(),maxlength,cm); break; 
       case Groesse: fout << " & "<<W.Groesse()<<" cm"; break; 
       case Gewicht: fout << " & "<<W.Gewicht()<<" kg"; break; 
       case Beruf: fout << " & "<<LaTeX_scale(i->abenteurer.Beruf(),maxlength,cm); break; 
       case Glaube: fout << " & "<<LaTeX_scale(W.Glaube(),maxlength,cm); break; 
       case St: V.push_back(st_is(W.St())); break;
       case Gw: V.push_back(st_is(W.Gw())); break;
       case Gs: V.push_back(st_is(W.Gs())); break;
       case Ko: V.push_back(st_is(W.Ko())); break;
       case In: V.push_back(st_is(W.In())); break;
       case Zt: V.push_back(st_is(W.Zt())); break;
       case Au: V.push_back(st_is(W.Au())); break;
       case pA: V.push_back(st_is(W.pA())); break;
       case Wk: V.push_back(st_is(W.Wk())); break;
       case Sb: V.push_back(st_is(W.Sb())); break;
       case B:  V.push_back(st_is(W.B())); break;
       case Zaubern: V.push_back(st_is(W.Zaubern_wert())); break;
       case Abwehr:  V.push_back(st_is(W.Abwehr_wert())); break;
       case Resistenz: fout << " & "<<W.Resistenzen_alle(hauptfenster->getCChar().getVTyp()); break; 
       case Sehen: V.push_back(st_is(W.Sehen())); break;
       case Hoeren: V.push_back(st_is(W.Hoeren())); break;
       case Riechen: V.push_back(st_is(W.Riechen())); break;
       case Schmecken: V.push_back(st_is(W.Schmecken())); break;
       case Tasten: V.push_back(st_is(W.Tasten())); break;
       case SechsterSinn: V.push_back(st_is(W.SechsterSinn())); break;
       case Wahrnehmung:  V.push_back(st_is(A.Erfolgswert("Wahrnehmung",Database),A.SErfolgswert("Wahrnehmung",Database))); break;
       case Spurenlesen: V.push_back(st_is(A.Erfolgswert("Spurenlesen",Database),A.SErfolgswert("Spurenlesen",Database))); break;
       case Fallen_entdecken: V.push_back(st_is(A.Erfolgswert("Fallen entdecken",Database),A.SErfolgswert("Fallen entdecken",Database))); break;
       case Suchen: V.push_back(st_is(A.Erfolgswert("Suchen",Database),A.SErfolgswert("Suchen",Database))); break;
       case Menschenkenntnis: V.push_back(st_is(A.Erfolgswert("Menschenkenntnis",Database),A.SErfolgswert("Menschenkenntnis",Database))); break;
       case Sagenkunde: V.push_back(st_is(A.Erfolgswert("Sagenkunde",Database),A.SErfolgswert("Sagenkunde",Database))); break;
       case Zauberkunde: V.push_back(st_is(A.Erfolgswert("Zauberkunde",Database),A.SErfolgswert("Zauberkunde",Database))); break;
       case Gassenwissen: V.push_back(st_is(A.Erfolgswert("Gassenwissen",Database),A.SErfolgswert("Gassenwissen",Database))); break;
       case Himmelskunde: V.push_back(st_is(A.Erfolgswert("Himmelskunde",Database),A.SErfolgswert("Himmelskunde",Database))); break;
       case Schaetzen: V.push_back(st_is(A.Erfolgswert("Schaetzen",Database),A.SErfolgswert("Schaetzen",Database))); break;
       case angFert: list_for_each(fout,A.CList_Fertigkeit_ang(),maxlength,cm); break;
       case Waffen: list_for_each(fout,A.CList_Waffen(),maxlength,cm); break;
       case Sprachen: list_for_each(fout,A.CList_Sprache(),maxlength,cm); break;
       case Schriften: list_for_each(fout,A.CList_Schrift(),maxlength,cm); break;
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


void LaTeX_drucken::list_for_each(ofstream &fout,const std::list<MidgardBasicElement_mutable>& L,const int &maxlength,const std::string& cm)
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

