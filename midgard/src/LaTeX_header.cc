// $Id: LaTeX_header.cc,v 1.24 2002/04/16 11:29:17 thoma Exp $
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
#ifndef __MINGW32__
#include <unistd.h>
#else
#include <windows.h>
#endif

std::string midgard_CG::get_latex_filename(const LaTeX_Filenames what)
{
  switch (what)
    {
      case TeX_MainDocument : return "midgard_document_eingabe";
      case TeX_MainWerte    : return "midgard_tmp_latexwerte";  
      case TeX_Beschreibung : return "midgard_tmp_beschreibung";
      case TeX_Ausruestung  : return "midgard_tmp_ausruestung";
    }
  abort(); // never get here
}

std::string midgard_CG::get_latex_pathname(const LaTeX_Pathnames what)
{
  switch (what)
    {
      case TeX_tmp : return "";
      case TeX_Install : return ""; //PACKAGE_DATA_DIR;
    }
  abort(); // never get here
}


std::string midgard_CG::system_comm(SystemComms what)
{
  switch (what)
   {
     case RM : return "rm ";
//     case CP : return "cp ";
   }
  abort(); //never get here
}


void midgard_CG::LaTeX_newsavebox(ostream &fout)
{
 fout << "\\usepackage{german}\n";
 fout << "\\usepackage[latin1]{inputenc}\n";
 fout << "\\newsavebox{\\ESchwert}    \n";
 fout << "\\newsavebox{\\Stichwaffe}  \n";
 fout << "\\newsavebox{\\ESchlagwaffe}\n";
 fout << "\\newsavebox{\\Spiesswaffe}\n";
 fout << "\\newsavebox{\\ZSchwert}\n";
 fout << "\\newsavebox{\\ZSchlagwaffe}\n";
 fout << "\\newsavebox{\\Stangenwaffe}   \n";
 fout << "\\newsavebox{\\Kettenwaffe}    \n";
 fout << "\\newsavebox{\\KampfohneWaffen}\n";
 fout << "\\newsavebox{\\Zauberstaebe}   \n";
 fout << "\\newsavebox{\\Wurfspiess}     \n";
 fout << "\\newsavebox{\\Stielwurfwaffe} \n";
 fout << "\\newsavebox{\\Wurfscheibe}    \n";
 fout << "\\newsavebox{\\Fesselwaffe}    \n";
 fout << "\\newsavebox{\\Armbrust}       \n";
 fout << "\\newsavebox{\\Bogen}          \n";
 fout << "\\newsavebox{\\Schleuder}\n";
 fout << "\\newsavebox{\\Schilde}\n";
 fout << "\\newsavebox{\\Parierwaffe}\n";
 fout << "\\newsavebox{\\Kampfstab}\n";
 fout << "\\newsavebox{\\Peitsche} \n";
 fout << "\\newsavebox{\\Garotte}  \n";
 fout << "\\newsavebox{\\Wurfmesser}\n";
 fout << "\\newsavebox{\\Blasrohr}  \n";
 fout << "\\newsavebox{\\Wurfpfeil} \n";
 fout << "\\newsavebox{\\Werfen}    \n";
}



void midgard_CG::LaTeX_kopfzeile(ostream &fout,bool landscape,bool newdoc)
{
 if(newdoc)
  {
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
  }
 fout << "\\begin{center}\n";
 std::string     drache="9.9cm", namensbox="7cm";
 if(!landscape) {drache="7cm" , namensbox="5cm";}
 fout << "\\IfFileExists{drache.png}{\\parbox{"+drache+"}{\\includegraphics[width="+drache+"]{drache.png}}}\n";
 fout << "{\\parbox{"+drache+"}{\\includegraphics[width="+drache+"]{"PACKAGE_DATA_DIR"drache.png}}}\n";
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
 fout <<"\\IfFileExists{dracher.png}{\\parbox{"+drache+"}{{\\includegraphics[width="+drache+"]{dracher.png}}}}\n";
 fout <<"{\\parbox{"+drache+"}{{\\includegraphics[width="+drache+"]{"PACKAGE_DATA_DIR"dracher.png}}}}\n";
 fout <<"\\vspace*{2ex}\n\n";
}

void midgard_CG::LaTeX_header(ostream &fout,bool landscape)
{
 if(landscape) fout << "\\documentclass[a4paper,10pt,landscape]{article}\n" ;
 else   fout << "\\documentclass[a4paper,10pt]{article}\n";

 fout << "\\usepackage{german}\n\\usepackage[latin2]{inputenc}\n";
 fout << "\\usepackage[pdftex]{graphicx}\n";
 fout << "\\usepackage{tabularx}\n";
 fout << "\\usepackage{times}\n";
 fout << "\\usepackage{color}\n";
 fout << "\\usepackage{wrapfig}\n";
 fout << "\\definecolor{mygray}{gray}{0.75}\n";
 

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
 LaTeX_kopfzeile(fout,landscape);
}

void midgard_CG::LaTeX_footer(ostream &fout)
{
  fout << "\\end{center}\n";
  fout << "\\end{document}\n\n";
}


void midgard_CG::pdf_viewer(const std::string& file)
{
#ifdef __MINGW32__
  const char * const subpath="\\texmf\\miktex\\bin";
  char buffer[1024];
  static char buffer2[10240];
  const char *e=getenv("PATH");
  if (!strstr(e,subpath))
  {  assert( getcwd(buffer, sizeof buffer) );
     assert( strlen(buffer)+strlen(subpath)<sizeof buffer);
     strcat(buffer,subpath);
     assert( 5+strlen(e)+1+strlen(buffer)<sizeof buffer2 );
     strcpy(buffer2,"PATH=");
     strcat(buffer2,e);
     strcat(buffer2,";");
     strcat(buffer2,buffer); // SearchPathA ?
     putenv(buffer2);
  }
  // GetTempPath ?
#define unlink(a) DeleteFileA(a)

#endif
  system(("pdflatex "+file+".tex").c_str());
  system((MOptionen->Viewer()+file+".pdf").c_str());

  unlink((file+".tex").c_str());
  unlink((file+".aux").c_str());
  unlink((file+".log").c_str());
  unlink((file+".pdf").c_str());
}
