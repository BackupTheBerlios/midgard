#include "midgard_CG.hh"
#include <Gtk2TeX.h>

void midgard_CG::LaTeX_kido()
{
  string name = "midgard_tmp_mykido.tex";
  ofstream fout(name.c_str());
  for (unsigned int i=0;i<vec_kido.size();++i)
   {
     string ap = itos(vec_kido[i].ap);
     if (ap=="0") ap="";
     string stufe=vec_kido[i].stufe;
     if (stufe=="Schüler") stufe="S";
     if (stufe=="Eingeweihter") stufe="E";
     if (stufe=="Meister") stufe="M";
     fout << ap << " & ";
     fout << vec_kido[i].hoho << " & ";
     fout << vec_kido[i].technik << " & ";
     fout << stufe << " & ";
     fout << Gtk2TeX::string2TeX(vec_kido[i].effekt) ;
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
//   fout << "\\input{./midgard_tmp_latexwertedef}\n";
   fout << "\\input{./midgard_tmp_latexwerte}\n";
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
