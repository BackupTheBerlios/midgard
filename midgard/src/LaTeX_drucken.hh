// $Id: LaTeX_drucken.hh,v 1.21 2003/07/01 09:35:55 thoma Exp $
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
//class cH_MidgardBasicElement;
#include "MidgardBasicElement.hh"
#include "Waffe.hh"
#include "Sprache.hh"
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
    enum ewhat{enamecharakter,enamespieler,egrad,etyp,espez,
               emagusversion,
               espezialisierung,estand,eherkunft,eglaube,
               egfp,eaep,ekep,ezep,egold,esilber,ekupfer,eruestung,eruestunglp,
               eruestungb,eruestunglpb,espezies,
               emerk,est,
               egs,egw,eko,ein,ezt,eau,epa,esb,ewk,eb,ekaw,egsb,egn,esg,
               elp,eap,eboau,ebosc,eboan,eboab,eboza,ebopsy,ebophs,ebophk,
               eres,epsy,ephs,ephk,egift,eabwehr,eabwehrfinal,eabwehrmitwaffe,
               eppresistenz,eppabwehr,eppzauber,ezauber,ehand,eraufen,
               ealter,egewicht,egestalt,ekoerpergroesse,
               esinnse,esinnh,esinnr,esinnsc,esinnt,esinnss,
         eWahrnehmung,eSpurenlesen,eFallen_entdecken,eSuchen,eMenschenkenntnis,
         eSagenkunde,eZauberkunde,eGassenwissen,eHimmelskunde,eSchaetzen,eangFert,
         eWaffen,eSprachen,eSchriften,eBeruf,eMAX};
    static const unsigned int maxsprach=23;
    static const unsigned int maxfert=40;
    static const unsigned int maxwaffen=12;
    static const unsigned int maxunifert=48;
   
    const midgard_CG *hauptfenster;
    bool bool_sprach,bool_fert,bool_waffen;

    void LaTeX_write_values(std::ostream &fout,const std::string &install_latex_file);
    void LaTeX_write_empty_values(std::ostream &fout,const std::string &install_latex_file);
    void write_grundwerte(std::ostream &fout,bool empty=false);
    void write_sprachen(std::ostream &fout,const std::vector<Sprache_und_Schrift>& L,bool longlist=false);
    void write_fertigkeiten(std::ostream &fout,const std::list<MBEmlt>& L,bool longlist=false);
    void write_waffenbesitz(std::ostream &fout,const std::list<H_WaffeBesitz>& L,bool longlist=false);
    void write_universelle(std::ostream &fout);
    void write_long_list(std::ostream &fout,const std::vector<Sprache_und_Schrift> &S,
                         const std::list<MBEmlt> &F,
                         const std::list<H_WaffeBesitz> &WB_druck);

    std::string LaTeX_scale(const std::string& is, 
         unsigned int maxlength, const std::string& scale);
    std::string LaTeX_scalemag(const std::string& is, 
         unsigned int maxlength, const std::string& scale,
         const std::string& magisch,const std::string& reichweite);
    std::string LaTeX_string(int i);

    std::string get_latex_filename(const LaTeX_Filenames what);
    std::string get_latex_pathname(const LaTeX_Pathnames what);
    void LaTeX_newsavebox(std::ostream &fout);
    void LaTeX_footer(std::ostream &fout);
    void LaTeX_kopfzeile(std::ostream &fout,bool landscape,bool newdoc=true);
    void LaTeX_header(std::ostream &fout,bool landscape=true,bool kopfzeile=true);
    void LaTeX_zauber_main(std::ostream &fout);
    void LaTeX_zaubermittel(std::ostream &fout);
    void LaTeX_zauber(std::ostream &fout);
    void LaTeX_kido(std::ostream &fout);
    void LaTeX_kido_main(std::ostream &fout);

    void ausruestung_druck(std::ostream &fout,bool unsichtbar,const std::list<AusruestungBaum> &AB,int deep);
    void pdf_viewer(const std::string& file,const bool tex_two_times=false);
    
    void line(std::ostream &fout,const ewhat &what);
    void for_each(std::ostream &fout,const ewhat &what);
    void list_for_each(std::ostream &fout,const std::list<MBEmlt>& L,const int &maxlength,const std::string& cm);
 public:
    LaTeX_drucken(const midgard_CG* h)
      : hauptfenster(h),bool_sprach(false),bool_fert(false),bool_waffen(false)
       {}

    void on_latex_clicked(bool values=true);
    void on_ausruestung_druck(bool unsichtbar);
    void latex_beschreibung_drucken();      
    void Spielleiterbogen();

};

#endif
