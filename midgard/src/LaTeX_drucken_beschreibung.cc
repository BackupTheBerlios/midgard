// $Id: LaTeX_drucken_beschreibung.cc,v 1.1 2002/05/14 07:26:14 thoma Exp $
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
#include <unistd.h>
//#include <fstream>
#include <Aux/itos.h>


void LaTeX_drucken::latex_beschreibung_drucken()
{   
 std::string figwidth=itos(hauptfenster->getCWerte().BeschreibungPixSize())+"cm";
 std::string file=hauptfenster->getCWerte().BeschreibungPix();
 std::string filename=get_latex_pathname(TeX_tmp)+get_latex_filename(TeX_Beschreibung);
 ofstream fout((filename+".tex").c_str());
 LaTeX_header(fout,false); 
 fout << "\\fbox{\\parbox[t][22cm]{18cm}{ \n";
 if(file!="")
  {
   fout << "\\IfFileExists{"+file+"}{\n~\n"; //'~' damit 'wrapfig funktioniert
   fout << "\\begin{wrapfigure}{r}{"+figwidth+"}\n";
   fout << "\\includegraphics[width="+figwidth+"]{"+file+"}\n";
   fout << "\\end{wrapfigure}}\n";
  }
 fout << hauptfenster->getCWerte().Beschreibung()<<"\n";
 fout << "}}\n";
 LaTeX_footer(fout);
 fout.close();
 pdf_viewer(filename);
}

