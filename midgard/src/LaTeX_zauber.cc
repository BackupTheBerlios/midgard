// $Id: LaTeX_zauber.cc,v 1.48 2002/04/22 07:48:53 christof Exp $
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
#include "Zauber.hh"
#include "Zauberwerk.hh"

#ifdef __MINGW32__
std::string utf82iso(const std::string &s);
#define LATIN(x) utf82iso(x)
#else
#define LATIN(x) (x)
#endif

void midgard_CG::LaTeX_zauber(ostream &fout)
{
  for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Zauber.begin();i!=list_Zauber.end();++i)
   {
     cH_Zauber z(*i);
     fout << LATIN(z->Name()) ;
     if(!z->Zusatz().empty()) fout << " ("<<LATIN(z->Zusatz())<<")";
     fout <<" & ";
     fout << z->Erfolgswert_Z(Typ,Werte) <<" & ";
     fout << Gtk2TeX::string2TeX(LATIN(z->Ap())) << " & ";
     fout << LATIN(z->Art()) << " & ";
     fout << z->Stufe() << " & ";
     fout << LATIN(z->Zauberdauer()) << " & ";
     fout << LATIN(z->Reichweite()) << " & ";
     fout << LATIN(z->Wirkungsziel()) << " & ";
     fout << LATIN(z->Wirkungsbereich()) << " & ";
     fout << LATIN(z->Wirkungsdauer()) << " & ";
     fout << LATIN(z->Ursprung()) << " & " ;
     fout << LaTeX_scale(LATIN(z->Material()),20,"3cm") << " & " ;
     fout << LATIN(z->Agens()) <<" " <<LATIN(z->Prozess()) <<" "<<LATIN(z->Reagens()) ;
     fout << "\\\\\n";
   }
}

void midgard_CG::LaTeX_zaubermittel(ostream &fout)
{
  for (std::list<cH_MidgardBasicElement>::iterator i=list_Zauberwerk.begin();i!=list_Zauberwerk.end();++i)
   {
     cH_Zauberwerk z(*i);
//     std::string wert ;//= itos((*i)->Wert());
//     fout << wert <<" & ";
     fout << LATIN(z->Name())  <<" & ";
     fout << LATIN(z->Art())   <<" & ";
     fout << z->Stufe()   <<" & ";
     fout << LATIN(z->Zeitaufwand())  <<" & ";
     fout << LATIN(z->Preis())   <<" \\\\\n ";
   }
}


void midgard_CG::LaTeX_zauber_main(ostream &fout)
{
  LaTeX_kopfzeile(fout,true,false);
  fout << "\\scriptsize\n";
  fout << "\\begin{tabular}{lcclccclcclp{3cm}l}\\hline\n";
  fout << " & Erfolgs- & &&&Zauber-&Reich-&\\multicolumn{1}{c}{Wirkungs-}&Wirkungs-&"
       <<"  Wirkungs-&\\multicolumn{1}{c}{Ur-}&\\multicolumn{1}{c}{Material}&\\multicolumn{1}{c}{Prozess}\\\\ \n";
  fout << "\\raisebox{1.5ex}[-1.5ex]{Zauberformel} & wert     & "
       << "\\raisebox{1.5ex}[-1.5ex]{AP} & \\multicolumn{1}{c}{\\raisebox{1.5ex}[-1.5ex]{Art}}"
       << " & \\raisebox{1.5ex}[-1.5ex]{Stufe} & -dauer & weite&\\multicolumn{1}{c}{ziel}&bereich&"
       << "dauer&\\multicolumn{1}{c}{sprung}\\\\\\hline\n";
  LaTeX_zauber(fout);
  fout << "\\end{tabular}\n";

 
  if (list_Zauberwerk.size()!=0)
   {
     fout << "\\begin{tabular}{lllll}\\hline\n";
     fout << "Name&Art&Stufe&\\scriptsize Zeitaufwand&Kosten\\\\\\hline\n";
     LaTeX_zaubermittel(fout);
     fout << "\\end{tabular}\n";
   }
  fout << "\\end{center}\n";
}
