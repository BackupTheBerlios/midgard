// $Id: LaTeX_charakter_beschreibung.cc,v 1.18 2001/12/17 14:53:58 thoma Exp $
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

void midgard_CG::latex_beschreibung_drucken()
{   
 ofstream fout("midgard_tmp_beschreibung.tex");
 LaTeX_header(fout,false); 
 fout << Werte.Beschreibung()<<"\n";
 LaTeX_footer(fout);
 fout.close();
 system("latex midgard_tmp_beschreibung.tex");
 system("dvips midgard_tmp_beschreibung.dvi");
 system("gv midgard_tmp_beschreibung.ps &");
}

