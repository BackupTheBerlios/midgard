// $Id: LaTeX_zauber.cc,v 1.36 2002/01/29 10:45:28 thoma Exp $
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
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include <fstream>

void midgard_CG::LaTeX_zauber()
{
//  Zauber_get_Daten(vec_Zauber);
  std::string name = "midgard_tmp_myzauber.tex";
  ofstream fout(name.c_str());
  for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Zauber.begin();i!=list_Zauber.end();++i)
   {
     cH_Zauber z(*i);
     fout << z->Name() << " & ";
     fout << z->Erfolgswert_Z(Typ,Werte,Database.ausnahmen) <<" & ";
     fout << Gtk2TeX::string2TeX(z->Ap()) << " & ";
     fout << z->Art() << " & ";
     fout << z->Stufe() << " & ";
     fout << z->Zauberdauer() << " & ";
     fout << z->Reichweite() << " & ";
     fout << z->Wirkungsziel() << " & ";
     fout << z->Wirkungsbereich() << " & ";
     fout << z->Wirkungsdauer() << " & ";
     fout << z->Ursprung() << " & " ;
     fout << LaTeX_scale(z->Material(),20,"3cm") << " & " ;
     fout << z->Agens() <<" " <<z->Prozess() <<" "<<z->Reagens() ;
     fout << "\\\\\n";
   }
}

void midgard_CG::LaTeX_zaubermittel()
{
  std::string name = "midgard_tmp_myzaubermittel.tex";
  ofstream fout(name.c_str());
  for (std::list<cH_MidgardBasicElement>::iterator i=list_Zauberwerk.begin();i!=list_Zauberwerk.end();++i)
   {
     cH_Zauberwerk z(*i);
//     std::string wert ;//= itos((*i)->Wert());
//     fout << wert <<" & ";
     fout << z->Name()  <<" & ";
     fout << z->Art()   <<" & ";
     fout << z->Stufe()   <<" & ";
     fout << z->Zeitaufwand()  <<" & ";
     fout << z->Preis()   <<" \\\\\n ";
   }
}


void midgard_CG::LaTeX_zauber_main(void)
{
  ofstream fout ("midgard_tmp_document_zauber.tex");
  LaTeX_header(fout);
/*
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
   fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(Werte.Name_Abenteurer(),25,"4.5cm") << "}\n";
   fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(Werte.Name_Spieler(),25,"4.5cm") << "}\n";
   fout << "\\begin{center}\n";
   fout << "\\IfFileExists{drache.ps}{\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file=drache.ps}}}\n";
   fout << "{\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file="PACKAGE_DATA_DIR"drache.ps}}}\n";
   fout << "\\parbox[][][c]{7cm}{\n";
   fout << "\\LI\n";
   fout << "\\begin{tabularx}{7.0cm}{|c|X|}\\hline\n";
   fout << "\\makebox[1.1cm]{Figur}&\\namecharakter\\\\\\hline\n";
   fout << "\\end{tabularx}\n\n";
   fout <<"\\vspace{2mm}\\li\n";
   fout <<"\\begin{tabularx}{7.0cm}{|c|X|}\\hline\n";
   fout <<"\\makebox[1.1cm]{Spieler}&\\namespieler\\\\\\hline\n";
   fout <<"\\end{tabularx}\n}\n";
   fout <<"\\IfFileExists{dracher.ps}{\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file=dracher.ps}}}\n";
   fout <<"{\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file="PACKAGE_DATA_DIR"dracher.ps}}}\n";
   fout <<"\\vspace*{2ex}\n";
*/
  fout << "\\begin{tabular}{lcclccclcclp{3cm}l}\\hline\n";
  fout << " & Erfolgs- & &&&Zauber-&Reich-&\\multicolumn{1}{c}{Wirkungs-}&Wirkungs-&"
       <<"  Wirkungs-&\\multicolumn{1}{c}{Ur-}&\\multicolumn{1}{c}{Material}&\\multicolumn{1}{c}{Prozess}\\\\ \n";
  fout << "\\raisebox{1.5ex}[-1.5ex]{Zauberformel} & wert     & "
       << "\\raisebox{1.5ex}[-1.5ex]{AP} & \\multicolumn{1}{c}{\\raisebox{1.5ex}[-1.5ex]{Art}}"
       << " & \\raisebox{1.5ex}[-1.5ex]{Stufe} & -dauer & weite&\\multicolumn{1}{c}{ziel}&bereich&"
       << "dauer&\\multicolumn{1}{c}{sprung}\\\\\\hline\n";
  fout << "\\input{midgard_tmp_myzauber.tex}\n";
  fout << "\\end{tabular}\n";

 
  if (list_Zauberwerk.size()!=0)
   {
     fout << "\\begin{tabular}{lllll}\\hline\n";
     fout << "Name&Art&Stufe&\\scriptsize Zeitaufwand&Kosten\\\\\\hline\n";
     fout << "\\input{midgard_tmp_myzaubermittel.tex}\n";
     fout << "\\end{tabular}\n";
   }
  LaTeX_footer(fout);
//  fout << "\\end{center}\n";
//  fout << "\\end{document}\n\n";
}
