// $Id: LaTeX_drucken_beschreibung.cc,v 1.5 2002/07/10 07:49:16 christof Exp $
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
#include <Misc/itos.h>
#include "recodestream.h"
#include "Windows_Linux.hh"

void LaTeX_drucken::latex_beschreibung_drucken()
{   
 std::string figwidth=itos(hauptfenster->getWerte().BeschreibungPixSize())+"cm";
 std::string file=hauptfenster->getWerte().BeschreibungPix();
 std::string filename=get_latex_pathname(TeX_tmp)+get_latex_filename(TeX_Beschreibung);
 ofstream fout2((filename+".tex").c_str());
#ifdef __MINGW32__
 orecodestream fout(fout2);
#else
 ostream &fout(fout2);
#endif 
 LaTeX_header(fout,false); 
 fout << "\\fbox{\\parbox[t][22cm]{18cm}{ \n";
 if(file!="")
  {
   fout << WinLux::normal_tilde;
   fout << "\\IfFileExists{"+WinLux::recodePathForTeX(file)+"}";
   fout << WinLux::active_tilde;
   fout << "{\n~\n"; //'~' damit 'wrapfig funktioniert
   fout << "\\begin{wrapfigure}{r}{"+figwidth+"}\n";
   fout << WinLux::normal_tilde;
   fout << "\\includegraphics[width="+figwidth+"]{"
   	+WinLux::recodePathForTeX(file)+"}\n";
   fout << WinLux::active_tilde;
   fout << "\\end{wrapfigure}}\n";
  }
 fout << hauptfenster->getWerte().Beschreibung()<<"\n";
 fout << "}}\n";
 LaTeX_footer(fout);
 fout2.close();
 pdf_viewer(filename);
}

