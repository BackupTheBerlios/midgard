// $Id: LaTeX_drucken.hh,v 1.2 2002/06/04 09:46:01 thoma Exp $
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

#ifndef _LATEXDRUCKEN_HH
#  define _LATEXDRUCKEN_HH

class midgard_CG;
class AusruestungBaum;
#include <iostream>
#include <string>
#include <list>
#include <fstream>

class LaTeX_drucken
{
    enum LaTeX_Filenames {TeX_MainWerte,TeX_MainDocument,TeX_Beschreibung,TeX_Ausruestung,TeX_Spielleiter};
    enum LaTeX_Pathnames {TeX_Install,TeX_tmp};
 private:
    const midgard_CG *hauptfenster;

    void LaTeX_write_values(ostream &fout,const std::string &install_latex_file);
    void LaTeX_write_empty_values(ostream &fout,const std::string &install_latex_file);
    std::string LaTeX_scale(const std::string& is, 
         unsigned int maxlength, const std::string& scale);
    std::string LaTeX_scalemag(const std::string& is, 
         unsigned int maxlength, const std::string& scale,
         const std::string& magisch,const std::string& reichweite);
    std::string LaTeX_string(int i);

    std::string get_latex_filename(const LaTeX_Filenames what);
    std::string get_latex_pathname(const LaTeX_Pathnames what);
    void LaTeX_newsavebox(ostream &fout);
    void LaTeX_footer(ostream &fout);
    void LaTeX_kopfzeile(ostream &fout,bool landscape,bool newdoc=true);
    void LaTeX_header(ostream &fout,bool landscape=true);
    void LaTeX_zauber_main(ostream &fout);
    void LaTeX_zaubermittel(ostream &fout);
    void LaTeX_zauber(ostream &fout);
    void LaTeX_kido(ostream &fout);
    void LaTeX_kido_main(ostream &fout);

    void ausruestung_druck(ostream &fout,bool unsichtbar,const std::list<AusruestungBaum> &AB,int deep);
    void pdf_viewer(const std::string& file);
    
    enum ewhat{SName,AName,Spezies,Typ,Grad,Herkunft,Stand,Gestalt,Groesse,
               Gewicht,Beruf,Glaube,Sprachen,Schriften,St,Gw,Gs,Ko,In,Zt,
               Au,pA,Wk,Sb,B,Resistenz,Sehen,Hoeren,Riechen,Schmecken,Tasten,
               SechsterSinn,Wahrnehmung,Spuren_lesen,Fallen_entdecken};
    void line(ofstream &fout,const ewhat &what);
    void for_each(ofstream &fout,const ewhat &what);
 public:
    LaTeX_drucken(const midgard_CG* h)
      : hauptfenster(h) {}

    void on_latex_clicked(bool values=true);
    void on_ausruestung_druck(bool unsichtbar);
    void latex_beschreibung_drucken();      
    void Spielleiterbogen();

};

#endif
