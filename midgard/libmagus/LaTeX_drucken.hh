// $Id: LaTeX_drucken.hh,v 1.7 2004/08/30 13:17:56 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003-2004 Christof Petig
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

//class cH_MidgardBasicElement;
#include "MidgardBasicElement.hh"
#include "Waffe.hh"
#include "Sprache.hh"
class AusruestungBaum;
class VAbenteurer;
#include <iostream>
#include <string>
#include <list>
//#include <fstream>

// Abenteurer als Argument oder als Member Variable?

class LaTeX_drucken
{
    enum LaTeX_Filenames {TeX_MainWerte,TeX_MainDocument,TeX_Beschreibung,TeX_Ausruestung,TeX_Spielleiter};
    enum LaTeX_Pathnames {TeX_Install,TeX_tmp};
 private:
    enum ewhat{enamecharakter,enamespieler,egrad,etyp,espez,
               emagusversion,e_last_saved_time,
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
   
    bool bool_sprach,bool_fert,bool_waffen;

    void LaTeX_write_values(const Abenteurer &A,std::ostream &fout,const std::string &install_latex_file);
    void LaTeX_write_empty_values(std::ostream &fout,const std::string &install_latex_file); //const
    void write_grundwerte(const Abenteurer&,std::ostream &fout,bool empty=false);
    void write_sprachen(std::ostream &fout,const std::vector<Sprache_und_Schrift>& L,bool longlist=false);
    void write_fertigkeiten(const Abenteurer &A,std::ostream &fout,const std::list<MBEmlt>& L,bool longlist=false);
    void write_waffenbesitz(const Abenteurer &A,std::ostream &fout,const std::list<H_WaffeBesitz>& L,bool longlist=false);
    void write_universelle(const Abenteurer &A,std::ostream &fout);
    void write_long_list(const Abenteurer &A,std::ostream &fout,const std::vector<Sprache_und_Schrift> &S,
                         const std::list<MBEmlt> &F,
                         const std::list<H_WaffeBesitz> &WB_druck);

    static std::string LaTeX_scale(const std::string& is, 
         unsigned int maxlength, const std::string& scale);
    static std::string LaTeX_scalemag(const std::string& is, 
         unsigned int maxlength, const std::string& scale,
         const std::string& magisch,const std::string& reichweite);
    static std::string LaTeX_string(int i);

    static std::string get_latex_filename(const Abenteurer &A,const LaTeX_Filenames what);
    static std::string get_latex_pathname(const LaTeX_Pathnames what);
    void LaTeX_Drachenbox(std::ostream &fout);
    static void LaTeX_newsavebox(const Abenteurer &A,std::ostream &fout);
    static void LaTeX_footer(std::ostream &fout);
    static void LaTeX_kopfzeile(const Abenteurer &A,std::ostream &fout,bool landscape,bool newdoc=true);
    void LaTeX_header(const Abenteurer &A,std::ostream &fout,bool landscape=true,bool kopfzeile=true);
    void LaTeX_zauber_main(const Abenteurer &A,std::ostream &fout);
    void LaTeX_zaubermittel(const Abenteurer &A,std::ostream &fout);
    void LaTeX_zauber(const Abenteurer &A,std::ostream &fout);
    static void LaTeX_kido(const Abenteurer &A,std::ostream &fout);
    static void LaTeX_kido_main(const Abenteurer &A,std::ostream &fout);

    void ausruestung_druck(std::ostream &fout,bool unsichtbar,const std::list<AusruestungBaum> &AB,int deep);
    static void pdf_viewer(const std::string& file,const bool tex_two_times=false);
    
    void line(const VAbenteurer &VA,std::ostream &fout,const ewhat &what);
    void for_each(const VAbenteurer &VA,std::ostream &fout,const ewhat &what);
    void list_for_each(std::ostream &fout,const std::list<MBEmlt>& L,const int &maxlength,const std::string& cm);
    static void LaTeX_Bildboxen(std::ostream &fout,const std::string &file,const double width_of_abenteurer_cm);
    void LaTeX_header_doc(const Abenteurer &a,std::ostream &fout,bool landscape=true,bool kopfzeile=true);
 public:
    LaTeX_drucken()
      : bool_sprach(),bool_fert(),bool_waffen()
       {}

    void Ausdrucken(const Abenteurer &A,bool values=true);
    void Ausdrucken();
    void on_ausruestung_druck(const Abenteurer &a,bool unsichtbar);
    void latex_beschreibung_drucken(const Abenteurer &a);      
    void Spielleiterbogen(VAbenteurer &a); // nicht const wegen sort_gw()

};

#endif
