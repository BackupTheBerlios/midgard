// $Id: LaTeX_zauber.cc,v 1.27 2001/10/02 07:25:01 thoma Exp $
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

void midgard_CG::LaTeX_zauber()
{
//  Zauber_get_Daten(vec_Zauber);
  std::string name = "midgard_tmp_myzauber.tex";
  ofstream fout(name.c_str());
  for (std::list<cH_Zauber>::const_iterator i=list_Zauber.begin();i!=list_Zauber.end();++i)
   {
     fout << (*i)->Name() << " & ";
//     fout << (*i)->Erfolgswert() <<" & ";
     int erf = get_erfolgswert_zaubern(Typ,Typ2,(*i)->Name());
     fout << erf <<" & ";
     fout << Gtk2TeX::string2TeX((*i)->Ap()) << " & ";
     fout << (*i)->Art() << " & ";
     fout << (*i)->Stufe() << " & ";
     fout << (*i)->Zauberdauer() << " & ";
     fout << (*i)->Reichweite() << " & ";
     fout << (*i)->Wirkungsziel() << " & ";
     fout << (*i)->Wirkungsbereich() << " & ";
     fout << (*i)->Wirkungsdauer() << " & ";
     fout << (*i)->Ursprung() << " & " ;
     fout << LaTeX_scale((*i)->Material(),20,"3cm") << " & " ;
     fout << (*i)->Agens() <<" " <<(*i)->Prozess() <<" "<<(*i)->Reagens() ;
     fout << "\\\\\n";
   }
}

void midgard_CG::LaTeX_zaubermittel()
{
  std::string name = "midgard_tmp_myzaubermittel.tex";
  ofstream fout(name.c_str());
  for (std::vector<H_Data_zaubermittel>::iterator i=vec_Zaubermittel.begin();
         i!=vec_Zaubermittel.end();++i)
   {
     std::string wert ;//= itos(*i->Wert());
     std::string art = (*i)->Art();
     if (wert=="0") wert ="";
     if (art=="AZ") art ="Alchimistisches Zaubermittel";
     if (art=="PZ") art ="Pflanzliches Zaubermittel";
     fout << wert <<" & ";
     fout << (*i)->Name()  <<" & ";
     fout << art   <<" & ";
     fout << (*i)->Stufe()   <<" & ";
     fout << (*i)->Zeitaufwand()  <<" & ";
     fout << (*i)->Kosten()   <<" & ";
   }
}


void midgard_CG::LaTeX_zauber_main(void)
{
  ofstream fout ("midgard_tmp_document_zauber.tex");
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
   fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(Werte.Name_Charakter(),25,"4.5cm") << "}\n";
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
  fout << "\\begin{tabular}{lcclccclcclp{3cm}l}\\hline\n";
  fout << " & Erfolgs- & &&&Zauber-&Reich-&\\multicolumn{1}{c}{Wirkungs-}&Wirkungs-&"
       <<"  Wirkungs-&\\multicolumn{1}{c}{Ur-}&\\multicolumn{1}{c}{Material}&\\multicolumn{1}{c}{Prozess}\\\\ \n";
  fout << "\\raisebox{1.5ex}[-1.5ex]{Zauberformel} & wert     & "
       << "\\raisebox{1.5ex}[-1.5ex]{AP} & \\multicolumn{1}{c}{\\raisebox{1.5ex}[-1.5ex]{Art}}"
       << " & \\raisebox{1.5ex}[-1.5ex]{Stufe} & -dauer & weite&\\multicolumn{1}{c}{ziel}&bereich&"
       << "dauer&\\multicolumn{1}{c}{sprung}\\\\\\hline\n";
  fout << "\\input{midgard_tmp_myzauber.tex}\n";
  fout << "\\end{tabular}\n";

 
  if (vec_Zaubermittel.size()!=0)
   {
     fout << "\\begin{tabular}{llllll}\\hline\n";
     fout << "Stufe&Name&Art&Stufe&\\scriptsize Zeitaufwand&Kosten\\\\\\hline\n";
     fout << "\\input{midgard_tmp_myzaubermittel.tex}\n";
     fout << "\\end{tabular}\n";
   }
  fout << "\\end{center}\n";
  fout << "\\end{document}\n\n";
}
