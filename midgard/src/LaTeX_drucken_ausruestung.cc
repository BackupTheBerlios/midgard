// $Id: LaTeX_drucken_ausruestung.cc,v 1.13 2002/11/05 07:24:19 thoma Exp $   
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
#include "midgard_CG.hh"
#include "dtos1.h"
#include "itos.h"
#include "recodestream.h"

void LaTeX_drucken::on_ausruestung_druck(bool unsichtbar)
{
 std::string filename=get_latex_pathname(LaTeX_drucken::TeX_tmp)+get_latex_filename(LaTeX_drucken::TeX_Ausruestung);
 std::ofstream fout2((filename+".tex").c_str());
#ifdef __MINGW32__
 orecodestream fout(fout2);
#else
 std::ostream &fout=fout2;
#endif
 LaTeX_header(fout,false);           

 std::string breite="18cm";
 std::string hbreitea="9cm";
 std::string hbreiteb="8cm";
 std::string aboxhoehe="26cm";

 const Abenteurer &A=hauptfenster->getAben();
 fout <<"\\parbox{"+hbreitea+"}{";
 fout << "Normallast: "<<itos(A.getNormallast())<<"\\,kg\\qquad\n"
      << "Höchstlast: "<<itos(A.getHoechstlast())<<"\\,kg\\qquad\n"
      << "Schublast: " <<itos(A.getSchublast())<<"\\,kg\n\n";
 fout << "Belastung: "<<dtos1(A.getBelastung())<<"\\,kg}\\hfill\n";
 fout <<"\\parbox{"+hbreiteb+"}{";
 {
  bool ew=false;
  double ueberlast=A.getUeberlast();
  int B=hauptfenster->getWerte().B();
  int v=hauptfenster->getWerte().Ruestung(0)->B_Verlust(ueberlast,B,ew);
cout << "XXXXXXXXXXXXX\t"<<ueberlast<<'\t'<<B<<'\t'<<ew<<'\t'<<v<<'\n';
  if(ew) 
    fout << "\\scriptsize Abzug auf Erfolgswürfe aufgrund von übermäßiger Belastung: --2\n\n";
  if(v)
    fout << "\\scriptsize Abzug auf die Bewegungsweite aufgrund übermäßiger Belastung: --"<<B<<"\n";
 }
 fout << "}\n\n";

 fout << "\\fbox{\\parbox[t]["+aboxhoehe+"]{"+breite+"}{ \n";
 const AusruestungBaum besitz=hauptfenster->getChar()->getBesitz();
 for(AusruestungBaum::const_iterator i=besitz.begin();i!=besitz.end();++i)
  {
   if(i->getAusruestung().Sichtbar() || unsichtbar )
    {      
      std::string name=i->getAusruestung().Name();
      if (!i->getAusruestung().Material().empty()) name +=" ("+i->getAusruestung().Material()+")";
      fout <<"\\hspace{0.7cm}";
      if(i->getAusruestung().Sichtbar())  fout << name<<"\\\\\n" ;
      else                                fout <<"\\textcolor{mygray}{"<< name<<"}\\\\\n" ;
      ausruestung_druck(fout,unsichtbar,i->getChildren(),1);
     }
  }
 fout << "}}\n";
 LaTeX_footer(fout);
 fout2.close();
 pdf_viewer(filename);
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

      fout <<"\\makebox[0.7cm]{\\raggedleft\\footnotesize "+i->getAusruestung().SGewicht()+"}"; 
      double fdeep = deep*0.5;
      fout << "\\hspace*{"+dtos1(fdeep)+"cm} ";
      if(i->getAusruestung().Sichtbar())  fout << name<<"\\\\\n" ;
      else                                 fout <<"\\textcolor{mygray}{"<< name<<"}\\\\\n" ;
      ausruestung_druck(fout,unsichtbar,i->getChildren(),deep+1);
     }
  }
}

