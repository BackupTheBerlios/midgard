// $Id: LaTeX_drucken_spielleiterbogen.cc,v 1.3 2002/06/04 13:56:11 thoma Exp $   
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

void LaTeX_drucken::Spielleiterbogen()
{
 std::string filename=get_latex_pathname(LaTeX_drucken::TeX_tmp)+get_latex_filename(LaTeX_drucken::TeX_Spielleiter);
 ofstream fout((filename+".tex").c_str());
 LaTeX_header(fout,false);           
 fout << "\\newcommand{\\n}{\\normalsize\\rule[-0.5ex]{0ex}{2.5ex}}\n";
 fout << "\\setlength{\\doublerulesep}{0.1mm}\n";
 fout << "\\fbox{\\parbox[t][22cm]{18cm}{ \n";

 fout << "\\scalebox{0.97}{\n";
 fout << "\\begin{tabular}{|||l|||\n";
 for(unsigned int i=0;i<hauptfenster->Char.getList().size();++i)
   fout << "c|"; // Anzahl der Spalten/Abenteurer
 fout << "||}\\hline\\hline\\hline\n";

 fout << "\\n Spieler "; for_each(fout,SName); fout << "\\\\\\hline\n";
 fout << "\\n Figur "; for_each(fout,AName); fout << "\\\\\\hline\n";
 fout << "\\n Spezies "; for_each(fout,Spezies); fout << "\\\\\\hline\n";
 fout << "\\n Typ "; for_each(fout,Typ); fout << "\\\\\\hline\n";
 fout << "\\n Grad "; for_each(fout,Grad); fout << "\\\\\\hline\n";
 fout << "\\n Herkunft "; for_each(fout,Herkunft); fout << "\\\\\\hline\n";
 fout << "\\n Stand "; for_each(fout,Stand); fout << "\\\\\\hline\n";
 fout << "\\n Gestalt "; for_each(fout,Gestalt); fout << "\\\\\\hline\n";
 fout << "\\n Grösse "; for_each(fout,Groesse); fout << "\\\\\\hline\n";
 fout << "\\n Gewicht "; for_each(fout,Gewicht); fout << "\\\\\\hline\n";
 fout << "\\n Beruf "; for_each(fout,Beruf); fout << "\\\\\\hline\n";
 fout << "\\n Glaube "; for_each(fout,Glaube); fout << "\\\\\\hline\n";
 fout << "\\n  St "; for_each(fout,St); fout << "\\\\\\hline\n";
 fout << "\\n  Gw "; for_each(fout,Gw); fout << "\\\\\\hline\n";
 fout << "\\n  Gs "; for_each(fout,Gs); fout << "\\\\\\hline\n";
 fout << "\\n  Ko "; for_each(fout,Ko); fout << "\\\\\\hline\n";
 fout << "\\n  In "; for_each(fout,In); fout << "\\\\\\hline\n";
 fout << "\\n  Zt "; for_each(fout,Zt); fout << "\\\\\\hline\n";
 fout << "\\n  Au "; for_each(fout,Au); fout << "\\\\\\hline\n";
 fout << "\\n  pA "; for_each(fout,pA); fout << "\\\\\\hline\n";
 fout << "\\n  Wk "; for_each(fout,Wk); fout << "\\\\\\hline\n";
 fout << "\\n  Sb "; for_each(fout,Sb); fout << "\\\\\\hline\n";
 fout << "\\n  B "; for_each(fout,B); fout << "\\\\\\hline\n";
 fout << "\\n  Resistenzen"; for_each(fout,Resistenz); fout << "\\\\\\hline\n";
 fout << "\\n  Sehen "; for_each(fout,Sehen); fout << "\\\\\\hline\n";
 fout << "\\n  Hören "; for_each(fout,Hoeren); fout << "\\\\\\hline\n";
 fout << "\\n  Riechen "; for_each(fout,Riechen); fout << "\\\\\\hline\n";
 fout << "\\n  Schmecken "; for_each(fout,Schmecken); fout << "\\\\\\hline\n";
 fout << "\\n  Tasten "; for_each(fout,Tasten); fout << "\\\\\\hline\n";
 fout << "\\n  Sechster Sinn "; for_each(fout,SechsterSinn); fout << "\\\\\\hline\n";
 fout << "\\n  Wahrnehmung "; for_each(fout,Wahrnehmung); fout << "\\\\\\hline\n";
 fout << "\\n  Spurenlesen "; for_each(fout,Spurenlesen); fout << "\\\\\\hline\n";
 fout << "\\n  Fallen entdecken "; for_each(fout,Fallen_entdecken); fout << "\\\\\\hline\n";
// fout << "\\n   "; for_each(fout,); fout << "\\\\\\hline\n";
// fout << "\\n   "; for_each(fout,); fout << "\\\\\\hline\n";
// fout << "\\n   "; for_each(fout,); fout << "\\\\\\hline\n";
 

 fout << "\\end{tabular}\n";
 fout << "}\n"; //scalebox
 fout << "}}\n";
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
     case Sprachen: fout << "Sprachen"; break; 
     case Schriften: fout << "Schriften"; break; 
//     case : fout << ""; break; 
//     case : fout << ""; break; 
   }
  for_each(fout,what);
  fout << "\\\\\\hline\n";
}

void LaTeX_drucken::for_each(ofstream &fout,const ewhat& what)
{
 const Datenbank Database=hauptfenster->getCDatabase();
 int maxlength=10;
 std::string cm="2cm";
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
       case Wahrnehmung: fout << " & "<<i->abenteurer.Erfolgswert("Wahrnehmung",Database); break; 
       case Spurenlesen: fout << " & "<<i->abenteurer.Erfolgswert("Spurenlesen",Database); break; 
       case Fallen_entdecken: fout << " & "<<i->abenteurer.SErfolgswert("Fallen entdecken",Database); break; 
       case Sprachen: fout << "Sprachen"; break; 
       case Schriften: fout << "Schriften"; break; 
     }
  }
}

