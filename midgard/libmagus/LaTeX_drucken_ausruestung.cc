// $Id: LaTeX_drucken_ausruestung.cc,v 1.3 2003/07/23 06:44:58 christof Exp $   
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

#include "LaTeX_drucken.hh"
#include "dtos1.h"
#include "itos.h"
#include "recodestream.h"
#include <TeX.h>
//#include <Gtk2TeX.h>
#include <Abenteurer.hh>
#include <fstream>

void LaTeX_drucken::on_ausruestung_druck(const Abenteurer &A,bool unsichtbar)
{
 std::string filename=get_latex_pathname(LaTeX_drucken::TeX_tmp)+get_latex_filename(A,LaTeX_drucken::TeX_Ausruestung);
 std::ofstream fout2((filename+".tex").c_str());
 orecodestream fout(fout2);
 LaTeX_header(A,fout,false);           

 std::string breite="18cm";
 std::string hbreitea="9cm";
 std::string hbreiteb="8.5cm";
 std::string aboxhoehe="26cm";

 fout <<"\\parbox{"+breite+"}{\\parbox{"+hbreitea+"}{";
 fout << "Normallast: "<<itos(A.getNormallast())<<"\\,kg\\qquad\n"
      << "Höchstlast: "<<itos(A.getHoechstlast())<<"\\,kg\\qquad\n"
      << "Schublast: " <<itos(A.getSchublast())<<"\\,kg\n\n";
 fout << "Belastung: "<<dtos1(A.getBelastung("Körper"))<<"\\,kg}\\hfill\n";
 fout <<"\\parbox{"+hbreiteb+"}{";
 {
  bool ew1=false; bool ew2=false;
  double ueberlast=A.getUeberlast();
  const Grundwerte &W=A.getWerte();
  cH_Ruestung R1=W.Ruestung(0);
  cH_Ruestung R2=W.Ruestung(1);
  int v1=R1->B_Verlust(ueberlast,W,ew1);
  int v2=R2->B_Verlust(ueberlast,W,ew2);
  if(ew1) 
    fout << "\\scriptsize Abzug auf Erfolgswürfe aufgrund von übermäßiger Belastung: --2 ("
               +R1->Name()+")\n\n";
  if(v1)
    fout << "\\scriptsize Abzug von der Bewegungsweite aufgrund übermäßiger Belastung: --"
         <<v1<<" $\\Rightarrow$ "<<(((W.B()-v1)<0)?0:(W.B()-v1))<<" ("+R1->Name()+")\n\n";
  if(ew2) 
    fout << "\\scriptsize Abzug auf Erfolgswürfe aufgrund von übermäßiger Belastung: --2 ("
               +R2->Name()+")\n\n";
  if(v2)
    fout << "\\scriptsize Abzug von der Bewegungsweite aufgrund übermäßiger Belastung: --"
         <<v2<<" $\\Rightarrow$ "<<(((W.B()-v2)<0)?0:(W.B()-v2))<<" ("+R2->Name()+")\n\n";
 }
 fout << "}}\n\n";

 fout << "%\\raggedright\n\\renewcommand{\\arraystretch}{1.0}\n"
      << "\\begin{longtable}{|lp{"+breite+"}|}\n\\hline\n";
 const AusruestungBaum besitz=A.getBesitz();
 for(AusruestungBaum::const_iterator i=besitz.begin();i!=besitz.end();++i)
  {
   if(i->getAusruestung().Sichtbar() || unsichtbar )
    {      
      fout << "\\multicolumn{2}{|l|}{\\bf ";
      std::string name=i->getAusruestung().Name();
      if (!i->getAusruestung().Material().empty()) name +=" ("+i->getAusruestung().Material()+")";
      if(i->getAusruestung().Sichtbar())  fout << TeX::string2TeX(name) ;
      else                                fout <<"\\textcolor{mygray}{"<< TeX::string2TeX(name)<<"}" ;
      double last=A.getBelastung(name);
      fout << " \\footnotesize ("<<dtos1(last)<<"\\,kg)";
      fout << "}\\\\\n"; // end of multicolumn and line
      ausruestung_druck(fout,unsichtbar,i->getChildren(),1);
     }
  }
 fout <<"\\hline\\end{longtable}\n";
 LaTeX_footer(fout);
 fout2.close();
 pdf_viewer(filename,true);
}


void LaTeX_drucken::ausruestung_druck(std::ostream &fout,bool unsichtbar,const std::list<AusruestungBaum> &AB,int deep)
{
 for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
  {
   if(i->getAusruestung().Sichtbar() || unsichtbar)
    {      
      std::string name=i->getAusruestung().Name();
      if (!i->getAusruestung().Material().empty() &&
           i->getAusruestung().Material()!="standard" ) 
         name +=" ("+i->getAusruestung().Material()+")";
      name = i->getAusruestung().SAnzahl() + name;
      fout <<"\\makebox[0.7cm]{\\raggedleft\\footnotesize "
         <<i->getAusruestung().SAnzahl()
         <<i->getAusruestung().SGewicht()+"}"; 
      double fdeep = deep*0.5;
      fout << "\\hspace*{"+dtos1(fdeep)+"cm} ";
      if(i->getAusruestung().Sichtbar())  fout << TeX::string2TeX(name)<<"\\\\\n" ;
      else                                 fout <<"\\textcolor{mygray}{"<< TeX::string2TeX(name)<<"}\\\\\n" ;
      ausruestung_druck(fout,unsichtbar,i->getChildren(),deep+1);
     }
  }
}

