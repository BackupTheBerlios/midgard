// $Id: LaTeX_drucken_spielleiterbogen.cc,v 1.6 2002/06/06 08:12:23 thoma Exp $   
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
     case Grad: fout << "Grad"; break; 
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
     case Sprachen: fout << "Sprachen"; break; 
     case Schriften: fout << "Schriften"; break; 
   }
  for_each(fout,what);
  fout << "\\\\\\hline\n";
}

void LaTeX_drucken::for_each(ofstream &fout,const ewhat& what)
{
 const Datenbank Database=hauptfenster->getCDatabase();
 int maxlength=15;
 std::string cm="2.2cm";
 for(std::list<VAbenteurer::st_abenteurer>::const_iterator i=hauptfenster->Char.getList().begin();i!=hauptfenster->Char.getList().end();++i)
  {
    switch(what)
     {
       case SName : fout << " & "<<LaTeX_scale(i->abenteurer.getCWerte().Name_Spieler(),maxlength,cm) ; break;
       case AName : fout << " & "<<LaTeX_scale(i->abenteurer.getCWerte().Name_Abenteurer(),maxlength,cm) ; break;
       case Spezies: fout << " & "<<LaTeX_scale(i->abenteurer.getCWerte().Spezies()->Name(),maxlength,cm); break; 
       case Typ: fout << " & "<<LaTeX_scale(i->abenteurer.STyp(),maxlength,cm); break; 
       case Grad: fout << " & "<<i->abenteurer.getCWerte().Grad(); break; 
       case Herkunft: fout << " & "<<LaTeX_scale(i->abenteurer.getCWerte().Herkunft()->Name(),maxlength,cm); break; 
       case Stand: fout << " & "<<LaTeX_scale(i->abenteurer.getCWerte().Stand(),maxlength,cm); break; 
       case Gestalt: fout << " & "<<LaTeX_scale(i->abenteurer.getCWerte().Gestalt(),maxlength,cm); break; 
       case Groesse: fout << " & "<<i->abenteurer.getCWerte().Groesse()<<" cm"; break; 
       case Gewicht: fout << " & "<<i->abenteurer.getCWerte().Gewicht()<<" kg"; break; 
       case Beruf: fout << " & "<<LaTeX_scale(i->abenteurer.Beruf(),maxlength,cm); break; 
       case Glaube: fout << " & "<<LaTeX_scale(i->abenteurer.getCWerte().Glaube(),maxlength,cm); break; 
       case St: fout << " & "<<i->abenteurer.getCWerte().St();; break; 
       case Gw: fout << " & "<<i->abenteurer.getCWerte().Gw();; break; 
       case Gs: fout << " & "<<i->abenteurer.getCWerte().Gs();; break; 
       case Ko: fout << " & "<<i->abenteurer.getCWerte().Ko();; break; 
       case In: fout << " & "<<i->abenteurer.getCWerte().In();; break; 
       case Zt: fout << " & "<<i->abenteurer.getCWerte().Zt();; break; 
       case Au: fout << " & "<<i->abenteurer.getCWerte().Au();; break; 
       case pA: fout << " & "<<i->abenteurer.getCWerte().pA();; break; 
       case Wk: fout << " & "<<i->abenteurer.getCWerte().Wk();; break; 
       case Sb: fout << " & "<<i->abenteurer.getCWerte().Sb();; break; 
       case B: fout << " & "<<i->abenteurer.getCWerte().B();; break; 
       case Resistenz: fout << " & "<<i->abenteurer.getCWerte().Resistenzen_alle(hauptfenster->getCChar().getVTyp()); break; 
       case Sehen: fout << " & "<<i->abenteurer.getCWerte().Sehen(); break; 
       case Hoeren: fout << " & "<<i->abenteurer.getCWerte().Hoeren(); break; 
       case Riechen: fout << " & "<<i->abenteurer.getCWerte().Riechen(); break; 
       case Schmecken: fout << " & "<<i->abenteurer.getCWerte().Schmecken(); break; 
       case Tasten: fout << " & "<<i->abenteurer.getCWerte().Tasten(); break; 
       case SechsterSinn: fout << " & "<<i->abenteurer.getCWerte().SechsterSinn(); break; 
       case Wahrnehmung: fout << " & "<<i->abenteurer.SErfolgswert("Wahrnehmung",Database); break; 
       case Spurenlesen: fout << " & "<<i->abenteurer.SErfolgswert("Spurenlesen",Database); break; 
       case Fallen_entdecken: fout << " & "<<i->abenteurer.SErfolgswert("Fallen entdecken",Database); break; 
       case Suchen: fout << " & "<<i->abenteurer.SErfolgswert("Suchen",Database); break; 
       case Menschenkenntnis: fout << " & "<<i->abenteurer.SErfolgswert("Menschenkenntnis",Database); break;
       case Sagenkunde: fout << " & "<<i->abenteurer.SErfolgswert("Sagenkunde",Database); break;
       case Zauberkunde: fout << " & "<<i->abenteurer.SErfolgswert("Zauberkunde",Database); break;
       case Gassenwissen: fout << " & "<<i->abenteurer.SErfolgswert("Gassenwissen",Database); break;
       case Himmelskunde: fout << " & "<<i->abenteurer.SErfolgswert("Himmelskunde",Database); break;
       case Schaetzen: fout << " & "<<i->abenteurer.SErfolgswert("Schaetzen",Database); break;
       case angFert: list_for_each(fout,i->abenteurer.CList_Fertigkeit_ang(),maxlength,cm); break;
       case Sprachen: list_for_each(fout,i->abenteurer.CList_Sprache(),maxlength,cm); break;
       case Schriften: list_for_each(fout,i->abenteurer.CList_Schrift(),maxlength,cm); break;
     }
   }
}


void LaTeX_drucken::list_for_each(ofstream &fout,const std::list<cH_MidgardBasicElement>& L,const int &maxlength,const std::string& cm)
{
  fout << " & \\parbox{"<<cm<<"}{";
  for(std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();)
   {
     std::string s=(*i)->Name()+" (+"+itos((*i)->Erfolgswert())+")";
     fout << LaTeX_scale(s,maxlength,cm);
     ++i;
     if(i!=L.end()) fout<<"\\newline ";
   }
  fout <<"}\n\t";
}

