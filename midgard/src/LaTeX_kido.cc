// $Id: LaTeX_kido.cc,v 1.40 2002/04/22 07:48:53 christof Exp $
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
#include "KiDo.hh"
#include <Aux/itos.h>

#ifdef __MINGW32__
std::string utf82iso(const std::string &s);
#define LATIN(x) utf82iso(x)
#else
#define LATIN(x) (x)
#endif

void midgard_CG::LaTeX_kido(ostream &fout)
{
  for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Kido.begin();i!=list_Kido.end();++i)
   {
     cH_KiDo kd(*i);
     std::string ap = itos(kd->Ap());
     if (ap=="0") ap="";
     std::string stufe=kd->Stufe();
     if (stufe=="Schüler") stufe="S";
     if (stufe=="Eingeweihter") stufe="E";
     if (stufe=="Meister") stufe="M";
     fout << ap << " & ";
     fout << LATIN(kd->HoHo()) << " & ";
     fout << LATIN(kd->Deutsch()) << " & ";
     fout << stufe << " & ";
     fout << Gtk2TeX::string2TeX(LATIN(kd->Effekt())) ;
     fout << "\\\\\n";
   }
}


void midgard_CG::LaTeX_kido_main(ostream &fout)
{
  LaTeX_kopfzeile(fout,true,false);
  fout << "\\begin{tabular}{rllcp{17cm}}\n";
  fout << "\\multicolumn{5}{l}{\\large\\bf Erfolgswert KiDo: "
         <<KiDo::get_erfolgswert_kido(list_Fertigkeit)+Werte.bo_Za()<<"}\\\\\\hline\n";
  fout << " AP & HoHo & Technik & Stufe & Effekt \\\\\\hline \n";

  LaTeX_kido(fout);
  fout << "\\end{tabular}\n";
  fout << "\\end{center}\n";
}
