// $Id: LaTeX_drucken_ausruestung.cc,v 1.2 2002/05/20 20:44:09 thoma Exp $   
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

void LaTeX_drucken::on_ausruestung_druck(bool unsichtbar)
{
 std::string filename=get_latex_pathname(LaTeX_drucken::TeX_tmp)+get_latex_filename(LaTeX_drucken::TeX_Ausruestung);
 ofstream fout((filename+".tex").c_str());
 LaTeX_header(fout,false);           

 fout << "\\fbox{\\parbox[t][22cm]{18cm}{ \n";
 const AusruestungBaum besitz=hauptfenster->getCWerte().getCBesitz();
 for(AusruestungBaum::const_iterator i=besitz.begin();i!=besitz.end();++i)
  {
   if(i->getAusruestung().Sichtbar() || unsichtbar )
    {      
      std::string name=i->getAusruestung().Name();
      if (!i->getAusruestung().Material().empty()) name +=" ("+i->getAusruestung().Material()+")";
      if(i->getAusruestung().Sichtbar())  fout << name<<"\\\\\n" ;
      else                                fout <<"\\textcolor{mygray}{"<< name<<"}\\\\\n" ;
      ausruestung_druck(fout,unsichtbar,i->getChildren(),1);
     }
  }
 fout << "}}\n";
 LaTeX_footer(fout);
 fout.close();
 pdf_viewer(filename);
}


void LaTeX_drucken::ausruestung_druck(ostream &fout,bool unsichtbar,const std::list<AusruestungBaum> &AB,int deep)
{
 for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
  {
   if(i->getAusruestung().Sichtbar() || unsichtbar)
    {      
      std::string name=i->getAusruestung().Name();
      if (!i->getAusruestung().Material().empty() &&
           i->getAusruestung().Material()!="standard" ) 
         name +=" ("+i->getAusruestung().Material()+")";
      double fdeep = deep*0.5;
      fout << "\\hspace*{"+dtos1(fdeep)+"cm} ";
      if(i->getAusruestung().Sichtbar())  fout << name<<"\\\\\n" ;
      else                                 fout <<"\\textcolor{mygray}{"<< name<<"}\\\\\n" ;
      ausruestung_druck(fout,unsichtbar,i->getChildren(),deep+1);
     }
  }
}

