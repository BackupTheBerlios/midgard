// $Id: LaTeX_charakter_beschreibung.cc,v 1.25 2002/03/13 09:32:35 thoma Exp $
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
#include <unistd.h>
#include <fstream>
#include <Aux/itos.h>


void midgard_CG::latex_beschreibung_drucken()
{   
 std::string figwidth=itos(Werte.BeschreibungPixSize())+"cm";
 std::string file=Werte.BeschreibungPix();
 ofstream fout("midgard_tmp_beschreibung.tex");
 LaTeX_header(fout,false); 
 fout << "\\fbox{\\parbox[t][22cm]{18cm}{ \n";
 if(file!="")
  {
   fout << "\\IfFileExists{"+file+"}{\n~\n"; //'~' damit 'wrapfig funktioniert
   fout << "\\begin{wrapfigure}{r}{"+figwidth+"}\n";
   fout << "\\includegraphics[width="+figwidth+"]{"+file+"}\n";
   fout << "\\end{wrapfigure}}\n";
  }
 fout << Werte.Beschreibung()<<"\n";
 fout << "}}\n";
 LaTeX_footer(fout);
 fout.close();
 pdf_viewer("midgard_tmp_beschreibung");
}

