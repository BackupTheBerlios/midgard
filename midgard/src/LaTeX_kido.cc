// $Id: LaTeX_kido.cc,v 1.18 2001/06/27 11:24:35 thoma Exp $
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

#include "midgard_CG.hh"
#include <Gtk2TeX.h>

void midgard_CG::LaTeX_kido()
{
  std::string name = "midgard_tmp_mykido.tex";
  ofstream fout(name.c_str());
//  for (unsigned int i=0;i<vec_kido.size();++i)
  for (std::vector<H_Data_kido>::const_iterator i=vec_Kido.begin();i!=vec_Kido.end();++i)
   {
     std::string ap = itos((*i)->Ap());
     if (ap=="0") ap="";
     std::string stufe=(*i)->Stufe();
     if (stufe=="Sch�ler") stufe="S";
     if (stufe=="Eingeweihter") stufe="E";
     if (stufe=="Meister") stufe="M";
     fout << ap << " & ";
     fout << (*i)->Hoho() << " & ";
     fout << (*i)->Name() << " & ";
     fout << stufe << " & ";
     fout << Gtk2TeX::string2TeX((*i)->Effekt()) ;
     fout << "\\\\\n";
   }
}


void midgard_CG::LaTeX_kido_main(void)
{
  ofstream fout ("midgard_tmp_document_kido.tex");
  fout << "\\documentclass[a4paper,10pt,landscape]{article}\n";
  fout << "\\usepackage{german}\n\\usepackage[latin2]{inputenc}\n";
   fout << "\\usepackage[final]{epsfig}\n";
   fout << "\\usepackage{tabularx}\n";
   fout << "\\usepackage{times}\n";

  fout << "\\setlength{\\textheight}{20.0cm}\n";
  fout << "\\setlength{\\textwidth}{28cm}\n";
  fout << "\\setlength{\\oddsidemargin}{-2.0cm}\n";
  fout << "\\setlength{\\evensidemargin}{-2.0cm}\n";
  fout << "\\setlength{\\topmargin}{-3.0cm}\n\n\n";
   fout << "\\newcommand{\\LI}{\\setlength{\\arrayrulewidth}{0.4mm}}\n";
   fout << "\\newcommand{\\li}{\\setlength{\\arrayrulewidth}{0.2mm}}\n";
   fout << "\\setlength{\\doublerulesep}{0mm}\n";
  fout << "\\begin{document}\n";
   fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(werte.name_charakter,25,"4.5cm") << "}\n";
   fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(werte.name_spieler,25,"4.5cm") << "}\n";
   fout << "\\begin{center}\n";
   fout << "\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file="PACKAGE_DATA_DIR"drache.ps}}\n";
   fout << "\\parbox[][][c]{7cm}{\n";
   fout << "\\LI\n";
   fout << "\\begin{tabularx}{7.0cm}{|c|X|}\\hline\n";
   fout << "\\makebox[1.1cm]{Figur}&\\namecharakter\\\\\\hline\n";
   fout << "\\end{tabularx}\n\n";
   fout <<"\\vspace{2mm}\\li\n";
   fout <<"\\begin{tabularx}{7.0cm}{|c|X|}\\hline\n";
   fout <<"\\makebox[1.1cm]{Spieler}&\\namespieler\\\\\\hline\n";
   fout <<"\\end{tabularx}\n}\n";
   fout <<"\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file="PACKAGE_DATA_DIR"dracher.ps}}\n";
   fout <<"\\vspace*{2ex}\n";
  fout << "\\begin{tabular}{rllcp{17cm}}\n";
  fout << "\\multicolumn{5}{l}{\\large\\bf Erfolgswert KiDo: "
         <<get_erfolgswert_kido()+werte.bo_za<<"}\\\\\\hline\n";
  fout << " AP & HoHo & Technik & Stufe & Effekt \\\\\\hline \n";
  fout << "\\input{midgard_tmp_mykido.tex}\n";
  fout << "\\end{tabular}\n";
  fout << "\\end{center}\n";
  fout << "\\end{document}\n\n";
}
