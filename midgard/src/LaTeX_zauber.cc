#include "midgard_CG.hh"
#include <Gtk2TeX.h>

void midgard_CG::LaTeX_zauber()
{
  string name = "midgard_tmp_myzauber.tex";
  ofstream fout(name.c_str());
  for (unsigned int i=0;i<zauber.size();++i)
   {
     fout << zauber[i].name << " & ";
     fout << zauber[i].erfolgswert <<" & ";
     fout << Gtk2TeX::string2TeX(zauber[i].ap) << " & ";
     fout << zauber[i].art << " & ";
     fout << zauber[i].stufe << " & ";
     fout << zauber[i].zauberdauer << " & ";
     fout << zauber[i].reichweite << " & ";
     fout << zauber[i].wirkungsziel << " & ";
     fout << zauber[i].wirkungsbereich << " & ";
     fout << zauber[i].wirkungsdauer << " & ";
     fout << zauber[i].ursprung << " & " ;
     fout << zauber[i].material << " & " ;
     fout << zauber[i].agens <<" " <<zauber[i].prozess <<" "<<zauber[i].reagens ;
     fout << "\\\\\n";
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
   fout << "\\input{./midgard_tmp_latexwertedef}\n";
   fout << "\\input{./midgard_tmp_latexwerte}\n";
   fout << "\\begin{center}\n";
   fout << "\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file="PACKAGE_DATA_DIR"drache.ps}}\n";
   fout << "\\parbox[][][c]{7cm}{\n";
   fout << "\\LI\n";
   fout << "\\begin{tabularx}{7.0cm}{|c|X|}\\hline\n";
   fout << "\\makebox[1.1cm]{Figur}&\\usebox{\\namecharakter}\\\\\\hline\n";
   fout << "\\end{tabularx}\n\n";
   fout <<"\\vspace{2mm}\\li\n";
   fout <<"\\begin{tabularx}{7.0cm}{|c|X|}\\hline\n";
   fout <<"\\makebox[1.1cm]{Spieler}&\\usebox{\\namespieler}\\\\\\hline\n";
   fout <<"\\end{tabularx}\n}\n";
   fout <<"\\parbox{10cm}{\\epsfig{width=10cm,angle=0,file="PACKAGE_DATA_DIR"dracher.ps}}\n";
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
  fout << "\\end{center}\n";
  fout << "\\end{document}\n\n";
}
