// $Id: LaTeX_kido.cc,v 1.36 2002/02/24 12:59:19 thoma Exp $
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
#include <fstream>
#include <Aux/itos.h>

void midgard_CG::LaTeX_kido()
{
  std::string name = "midgard_tmp_mykido.tex";
  ofstream fout(name.c_str());
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
     fout << kd->HoHo() << " & ";
     fout << kd->Deutsch() << " & ";
     fout << stufe << " & ";
     fout << Gtk2TeX::string2TeX(kd->Effekt()) ;
     fout << "\\\\\n";
   }
}


void midgard_CG::LaTeX_kido_main(void)
{
  ofstream fout ("midgard_tmp_document_kido.tex");
  LaTeX_kopfzeile(fout,true,false);
  fout << "\\begin{tabular}{rllcp{17cm}}\n";
  fout << "\\multicolumn{5}{l}{\\large\\bf Erfolgswert KiDo: "
         <<KiDo::get_erfolgswert_kido(list_Fertigkeit)+Werte.bo_Za()<<"}\\\\\\hline\n";
  fout << " AP & HoHo & Technik & Stufe & Effekt \\\\\\hline \n";
  fout << "\\input{midgard_tmp_mykido.tex}\n";
  fout << "\\end{tabular}\n";
//  LaTeX_footer(fout);
}
