// $Id: LaTeX_drucken_beschreibung.cc,v 1.3 2003/08/02 14:55:38 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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
#include <unistd.h>
#include <fstream>
#include <Misc/itos.h>
#include "recodestream.h"
#include "Windows_Linux.hh"
#include "Abenteurer.hh"

void LaTeX_drucken::latex_beschreibung_drucken(const Abenteurer &A)
{   
 std::string figwidth=itos(A.getWerte().BeschreibungPixSize())+"cm";
 std::string file=A.getWerte().BeschreibungPix();
 std::string filename=get_latex_pathname(TeX_tmp)+get_latex_filename(A,TeX_Beschreibung);
 std::ofstream fout2((filename+".tex").c_str());
 orecodestream fout(fout2);
 LaTeX_header(A,fout,false); 
 fout << "\\fbox{\\parbox[t][23cm]{18cm}{ \n";
 if(file!="")
  {
   fout << WinLux::normal_tilde;
//   fout << "\\IfFileExists{"+WinLux::recodePathForTeX(file)+"}";
   fout << WinLux::active_tilde;
   fout << "\n~\n"; //'~' damit 'wrapfig funktioniert
   fout << "\\begin{wrapfigure}{r}{"+figwidth+"}\n";
   fout << WinLux::normal_tilde;
   fout << "\\includegraphics[width="+figwidth+"]{"
   	+WinLux::recodePathForTeX(file)+"}\n";
   fout << WinLux::active_tilde;
   fout << "\\end{wrapfigure}\n";
  }
 fout << A.getWerte().Beschreibung()<<"\n";
 fout << "}}\n";
 LaTeX_footer(fout);
 fout2.close();
 pdf_viewer(filename);
}

