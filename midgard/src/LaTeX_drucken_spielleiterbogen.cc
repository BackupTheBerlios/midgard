// $Id: LaTeX_drucken_spielleiterbogen.cc,v 1.1 2002/06/04 09:46:01 thoma Exp $   
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
 fout << "\\begin{tabular}{|||c|||\n";
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
// fout << "\\n  "; for_each(fout,); fout << "\\\\\\hline\n";
// fout << "\\n  "; for_each(fout,); fout << "\\\\\\hline\n";
 

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
     
   }
  for_each(fout,what);
  fout << "\\\\\\hline\n";
}

void LaTeX_drucken::for_each(ofstream &fout,const ewhat& what)
{
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
     }
  }
}

