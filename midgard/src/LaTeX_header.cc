// $Id: LaTeX_header.cc,v 1.5 2002/01/29 10:45:28 thoma Exp $
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

void midgard_CG::LaTeX_header(ostream &fout,bool landscape)
{
 if(landscape) fout << "\\documentclass[a4paper,10pt,landscape]{article}\n" ;
 else   fout << "\\documentclass[a4paper,10pt]{article}\n";

 fout << "\\usepackage{german}\n\\usepackage[latin2]{inputenc}\n";
 fout << "\\usepackage[final]{epsfig}\n";
 fout << "\\usepackage{tabularx}\n";
 fout << "\\usepackage{times}\n";
 fout << "\\usepackage{pstricks}\n";
 fout << "\\newrgbcolor{mygray}{0.75 0.75 0.75}\n";

 if(landscape)
  {
   fout << "\\setlength{\\textheight}{20.0cm}\n";
   fout << "\\setlength{\\textwidth}{28cm}\n";
   fout << "\\setlength{\\oddsidemargin}{-2.0cm}\n";
   fout << "\\setlength{\\evensidemargin}{-2.0cm}\n";
   fout << "\\setlength{\\topmargin}{-3.0cm}\n\n\n";
  }
 else
  {
   fout << "\\setlength{\\textheight}{26.0cm}\n";
   fout << "\\setlength{\\textwidth}{19.5cm}   \n";
   fout << "\\setlength{\\arraycolsep}{0.1cm} \n";
   fout << "\\setlength{\\evensidemargin}{-1.5cm}\n";
   fout << "\\setlength{\\oddsidemargin}{-1.5cm} \n";
   fout << "\\setlength{\\topmargin}{-0.4cm}    \n";
   fout << "\\setlength{\\parindent}{0em}       \n";
   fout << "\\renewcommand {\\arraystretch}{1.3}\n\n";

   fout << "\%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
   fout << "\%% Listenumgebungen\n";
   fout << "\%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
   fout << "\\newenvironment{punkte}{\n";
   fout << "\\begin{list}{$\\bullet$}\n";
   fout << "{\n";
   fout << "\\setlength{\\labelwidth}{0.5cm}\n";
   fout << "\\setlength{\\leftmargin}{1.cm} \n";
   fout << "\\setlength{\\labelsep}{0.5cm}  \n"; 
   fout << "\\setlength{\\rightmargin}{0.5cm}\n";
   fout << "\\setlength{\\parsep}{0.1ex plus0.1ex minus0.1ex} \n";
   fout << "\\setlength{\\itemsep}{0.1ex plus0.1ex minus0.1ex}\n";
   fout << "}}\n";
   fout << "{\n";
   fout << "\\end{list}\n";
   fout << "}\n";

   fout << "\\newenvironment{punkte2}{\n";
   fout << "\\begin{list}{$\\star$}\n";
   fout << "{\n";
   fout << "\\setlength{\\labelwidth}{0.5cm}\n";
   fout << "\\setlength{\\leftmargin}{1.cm} \n";
   fout << "\\setlength{\\labelsep}{0.5cm}  \n"; 
   fout << "\\setlength{\\rightmargin}{0.5cm}\n";
   fout << "\\setlength{\\parsep}{0.0ex plus0.1ex minus0.1ex} \n";
   fout << "\\setlength{\\itemsep}{0.0ex plus0.1ex minus0.1ex}\n";
   fout << "}}\n";
   fout << "{\n";
   fout << "\\end{list}\n";
   fout << "}\n";
  }
 fout << "\\newcommand{\\LI}{\\setlength{\\arrayrulewidth}{0.4mm}}\n";
 fout << "\\newcommand{\\li}{\\setlength{\\arrayrulewidth}{0.2mm}}\n";
 fout << "\\setlength{\\doublerulesep}{0mm}\n";
 fout << "\\begin{document}\n";
 if(landscape)
  {
    fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(Werte.Name_Abenteurer(),25,"4.5cm") << "}\n";
    fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(Werte.Name_Spieler(),25,"4.5cm") << "}\n";
  }
 else
  {
    fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(Werte.Name_Abenteurer(),20,"4.cm") << "}\n";
    fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(Werte.Name_Spieler(),20,"4.cm") << "}\n";
  }
 fout << "\\begin{center}\n";
 std::string     drache="10cm", namensbox="7cm";
 if(!landscape) {drache="7cm" , namensbox="5cm";}
 fout << "\\IfFileExists{drache.ps}{\\parbox{"+drache+"}{\\epsfig{width="+drache+",angle=0,file=drache.ps}}}\n";
 fout << "{\\parbox{"+drache+"}{\\epsfig{width="+drache+",angle=0,file="PACKAGE_DATA_DIR"drache.ps}}}\n";
 fout << "\\parbox[][][c]{"+namensbox+"}{\n";
 if(!landscape) fout << "\\scriptsize\n";
 fout << "\\LI\n";
 fout << "\\begin{tabularx}{"+namensbox+"}{|c|X|}\\hline\n";
 fout << "\\makebox[1.1cm]{Figur}&\\namecharakter\\\\\\hline\n";
 fout << "\\end{tabularx}\n\n";
 if(landscape)  fout <<"\\vspace{2mm}\\li\n";
 else           fout <<"\\vspace{0.5mm}\\li\n";
 fout <<"\\begin{tabularx}{"+namensbox+"}{|c|X|}\\hline\n";
 fout <<"\\makebox[1.1cm]{Spieler}&\\namespieler\\\\\\hline\n";
 fout <<"\\end{tabularx}\n}\n";
 fout <<"\\IfFileExists{dracher.ps}{\\parbox{"+drache+"}{\\epsfig{width="+drache+",angle=0,file=dracher.ps}}}\n";
 fout <<"{\\parbox{"+drache+"}{\\epsfig{width="+drache+",angle=0,file="PACKAGE_DATA_DIR"dracher.ps}}}\n";
 fout <<"\\vspace*{2ex}\n\n";
}

void midgard_CG::LaTeX_footer(ostream &fout)
{
  fout << "\\end{center}\n";
  fout << "\\end{document}\n\n";
}
