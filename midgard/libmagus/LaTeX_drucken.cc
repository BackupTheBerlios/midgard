// $Id: LaTeX_drucken.cc,v 1.24 2004/10/27 10:42:11 christof Exp $
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

#include <config.h>
#include <unistd.h>
#include <Misc/EmptyInt_4TeX.h>
#include "Fertigkeiten_angeboren.hh"
#include "LaTeX_drucken.hh"
#include <fstream>
#include "Fertigkeiten.hh"
#include "KiDo.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include <TeX.h>
#include <Misc/recodestream.h>
#include "Windows_Linux.hh"
#include "Abenteurer.hh"
#include "Magus_Optionen.hh"
#include "magus_paths.h"
#include "Ausgabe.hh"
#include "Datenbank.hh"
#include "WaffeGrund.hh"
// to redefine VERSION
#include <config.h>
#include <Misc/TraceNV.h>
#include <magustrace.h>

static std::string defFileName(const std::string &s)
{  std::string res;
   for (std::string::const_iterator i=s.begin();i!=s.end();++i)
      if (('0' <= *i && *i <= '9') || ('A' <= *i && *i <= 'Z')
      	|| ('a' <= *i && *i <= 'z') || *i=='_')
      	 res+=*i;
   return res;
}

std::string LaTeX_drucken::get_latex_filename(const Abenteurer &A, const LaTeX_Filenames what)
{
  std::string name=A.Name_Abenteurer();
  std::string version=A.Version();
  std::string nv="_"+defFileName(name)+"__"+defFileName(version)+"_";
  
  switch (what)
    {
      case TeX_MainDocument : return "magus_document_eingabe";
      case TeX_MainWerte    : return "magus"+nv+"latexwerte";  
      case TeX_Beschreibung : return "magus"+nv+"beschreibung";
      case TeX_Ausruestung  : return "magus"+nv+"ausruestung"; 
      case TeX_Spielleiter  : return "magus_spielleiter"; 
    }
  abort(); // never get here
}
 
std::string LaTeX_drucken::get_latex_pathname(const LaTeX_Pathnames what)
{
  switch (what)
    {
      case TeX_tmp : return Programmoptionen->getString(Magus_Optionen::tmppfad);
      case TeX_Install : 
      {  std::string result=magus_paths::with_path("MAGUS-Logo-grey2.png",true);
         return WinLux::recodePathForTeX(result);
      }
    }
  abort(); // never get here
}

#if 1
void LaTeX_drucken::Ausdrucken(const Abenteurer &A,bool values)
{   
// std::string installfile=get_latex_pathname(TeX_Install)+get_latex_filename(TeX_MainDocument);
 std::string installfile=magus_paths::with_path(get_latex_filename(A,TeX_MainDocument)+".tex");
 std::string filename=get_latex_pathname(TeX_tmp)+get_latex_filename(A,TeX_MainWerte);
 
//cout <<"LaTeX: "<< filename<<'\n';
 {
 std::ofstream fout((filename+".tex").c_str());
 orecodestream rfout(fout);
 if (values) LaTeX_write_values(A,rfout,installfile);
 else LaTeX_write_empty_values(rfout,installfile);

 if (!A.List_Zauber().empty() || !A.List_Zauberwerk().empty())  // Zauber
  {
    LaTeX_zauber_main(A,rfout);
  }
 if (!A.List_Kido().empty()) // KiDo
  {
    LaTeX_kido_main(A,rfout);
  }
 rfout << "\\end{document}\n";
 rfout.flush();
 fout.close();
 }
 pdf_viewer(filename);
}
#endif

void LaTeX_drucken::LaTeX_write_values(const Abenteurer &A, std::ostream &fout,const std::string &install_latex_file)
{
 fout << "\\documentclass[11pt,a4paper,landscape]{article}\n";
// fout << "\\newcommand{\\installpath}{"<<get_latex_pathname(TeX_Install)<< "}\n";
 LaTeX_newsavebox(A,fout);

 write_grundwerte(A,fout);
 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 std::vector<Sprache_und_Schrift> S;
 for(std::list<MBEmlt>::const_iterator i=A.List_Sprache().begin();i!=A.List_Sprache().end();++i)
   {  
      Sprache_und_Schrift sus=cH_Sprache((*i)->getMBE())->SchriftWert((*i)->Erfolgswert(),true,A.List_Schrift());
      S.push_back(sus);
   }
 std::list<MBEmlt> verwandteSprachen=Sprache::getVerwandteSprachen(A.List_Sprache(),Datenbank.Sprache);
 for(std::list<MBEmlt>::const_iterator i=verwandteSprachen.begin();i!=verwandteSprachen.end();++i)
   { //cH_Sprache s(*i);
     if((*i)->ist_gelernt(A.List_Sprache()) ) 
      { 
        // der ungelernte Erfolgswert ist besser als der gelernte
        if((*i)->Erfolgswert() > A.Erfolgswert((*(*i))->Name()).first)
           Sprache_und_Schrift::ungelernte_ist_besser(S,(*(*i))->Name(),(*i)->Erfolgswert());
        continue;
      }
     S.push_back(Sprache_und_Schrift(*i,false));
   }
 write_sprachen(fout,S);
 if(S.size()>maxsprach) bool_sprach=true;
 /////////////////////////////////////////////////////////////////////////////
 // Grundfertigkeiten (Waffen)
 for (std::list<MBEmlt>::const_iterator i=A.List_WaffenGrund().begin();i!=A.List_WaffenGrund().end();++i)
   {
      std::string sout = (*(*i))->Name();
      if (sout =="Bögen") sout = "Bogen";
      if (sout =="Wurfspieß") sout = "Wurfspiess";
      if (sout =="Spießwaffe") sout = "Spiesswaffe";
      if (sout =="Kampf ohne Waffen") sout = "KampfohneWaffen";
      if (sout =="Zauberstäbe") sout = "Zauberstaebe";
      fout << "\\sbox{\\"<<sout<<"}{\\tiny X}\n";
   }

 /////////////////////////////////////////////////////////////////////////////
 // Beruf
 fout << "\\newcommand{\\beruf}{" ;
 std::string beruf;
 for(std::list<MBEmlt>::const_iterator i=A.List_Beruf().begin();i!=A.List_Beruf().end();++i)
     beruf += (*(*i))->Name(); 
 fout << LaTeX_scale(beruf,10,"1.5cm") <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // weitere Merkmale
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten & Waffen
 /////////////////////////////////////////////////////////////////////////////
 // angeborene Fertigkeiten
 std::list<MBEmlt> F;
 for(std::list<MBEmlt>::const_iterator i=A.List_Fertigkeit_ang().begin();i!=A.List_Fertigkeit_ang().end();++i) 
     F.push_back(*i);
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for(std::list<MBEmlt>::const_iterator i=A.List_Fertigkeit().begin();i!=A.List_Fertigkeit().end();++i) 
    F.push_back(*i);
// Leerzeile ???
 /////////////////////////////////////////////////////////////////////////////
 // Waffen + Waffen/Besitz
 std::string angriffsverlust_string = A.Ruestung_Angriff_Verlust(A.List_Fertigkeit());
 std::list<H_WaffeBesitz> WBesitz=A.List_Waffen_besitz();
 std::list<H_WaffeBesitz> WB_druck;
 for (std::list<MBEmlt>::const_iterator i=A.List_Waffen().begin();i!=A.List_Waffen().end();++i)
   {
    F.push_back(*i);
    cH_Waffe w((*i)->getMBE());
    // waffenloser Kampf:
    if (w->Name()=="waffenloser Kampf" || w->Name()=="Faustkampf") 
     {
      H_WaffeBesitz W=new WaffeBesitz(w,w->Name(),0,0,"","");
      W->setErfolgswert((*i)->Erfolgswert());
      WBesitz.push_back(W);
     }
    for (std::list<H_WaffeBesitz>::const_iterator j=WBesitz.begin();j!=WBesitz.end();++j)
     {
      H_WaffeBesitz WB=*j;
      if (WB->Waffe()->Name()==w->Name())  
       {
         WB->setErfolgswert((*i)->Erfolgswert());
         WB_druck.push_back(WB)  ;
       }
     }
   }
 write_waffenbesitz(A,fout,WB_druck);
 write_fertigkeiten(A,fout,F);
 write_universelle(A,fout);
 if(F.size()>maxfert) bool_fert=true;
 if(WB_druck.size()>maxwaffen) bool_waffen=true;

 fout << WinLux::normal_tilde;
 fout << "\\input{"+WinLux::recodePathForTeX(install_latex_file)+"}\n";
 fout << WinLux::active_tilde;

 if(bool_sprach || bool_fert || bool_waffen) write_long_list(A,fout,S,F,WB_druck);
}


void LaTeX_drucken::LaTeX_write_empty_values(std::ostream &fout,const std::string &install_latex_file)
{
 fout << "\\documentclass[11pt,a4paper,landscape]{article}\n";
// fout << "\\newcommand{\\installpath}{"<<get_latex_pathname(TeX_Install)<< "}\n";
 LaTeX_newsavebox(Abenteurer(),fout);
 write_grundwerte(Abenteurer(),fout,true);
 
 std::vector<Sprache_und_Schrift> L;
 write_sprachen(fout,L);
 fout << "\\newcommand{\\beruf}{}\n" ;
 std::list<MBEmlt> F;
 write_fertigkeiten(Abenteurer(),fout,F);
 std::list<H_WaffeBesitz> B;
 write_waffenbesitz(Abenteurer(),fout,B);
 write_universelle(Abenteurer(),fout);

 fout << WinLux::normal_tilde;
 fout << "\\input{"+WinLux::recodePathForTeX(install_latex_file)+"}\n";
 fout << WinLux::active_tilde;
}

void LaTeX_drucken::write_grundwerte(const Abenteurer &A,std::ostream &fout,bool empty)
{
 for(ewhat was=enamecharakter;was<eMAX; was=ewhat(int(was)+1))
  {
   std::string sfout = "\\newcommand{\\";
   switch (was) {
     case etyp  : sfout += "typ}{"; break ;
     case emagusversion  : sfout += "magusversion}{"; break ;
     case e_last_saved_time : sfout += "lastsavedat}{"; break ;
     case espezies : sfout += "spezies}{"; break ;
     case emerk : sfout += "merkmale}{"; break ;
     case est   : sfout += "st }{"; break ;
     case egs   : sfout += "gs }{"; break ;
     case egw   : sfout += "gw }{"; break ;
     case eko   : sfout += "ko }{"; break ;
     case ein   : sfout += "inn }{"; break ;
     case ezt   : sfout += "zt }{"; break ;
     case eau   : sfout += "au }{"; break ;
     case epa   : sfout += "pa }{"; break ;
     case esb   : sfout += "sbb }{"; break ;
     case ewk   : sfout += "wk }{"; break ;
     case eb    : sfout += "bb }{"; break ;
     case ekaw  : sfout += "kaw }{"; break ;
     case egsb  : sfout += "geistesblitz }{"; break ;
     case egn   : sfout += "ggn}{"; break ;
     case esg   : sfout += "sg }{"; break ;
     case elp   : sfout += "lp }{"; break ;
     case eap   : sfout += "ap }{"; break ;
     case eboau : sfout += "boau}{"; break ;
     case ebosc : sfout += "bosc}{"; break ;
     case eboan : sfout += "boan}{"; break ;
     case eboab : sfout += "boab}{"; break ;
     case eboza : sfout += "boza}{"; break ;
     case ebopsy: sfout += "bopsy}{"; break ;
     case ebophs: sfout += "bophs}{"; break ;
     case ebophk: sfout += "bophk}{"; break ;
     case eres  : sfout += "res}{"; break ;
     case epsy  : sfout += "psy}{"; break ;
     case ephs  : sfout += "phs}{"; break ;
     case ephk  : sfout += "phk}{"; break ;
     case egift : sfout += "gift}{"; break ;
     case eabwehr:sfout += "abwehr}{"; break ;
     case eabwehrfinal:sfout += "abwehrfinal}{"; break ;
     case eabwehrmitwaffe:sfout += "abwehrmitwaffe}{"; break ;
     case eppresistenz:sfout += "ppresistenz}{"; break ;
     case eppabwehr:sfout += "ppabwehr}{"; break ;
     case eppzauber:sfout += "ppzauber}{"; break ;
     case ezauber:sfout += "zauber}{"; break ;
     case ehand:sfout += "hand}{"; break ;
     case eraufen:sfout += "raufen}{"; break ;
     case ealter:sfout += "alter}{"; break ;
     case egewicht:sfout += "gewicht}{"; break ;
     case egestalt:sfout += "gestalt}{"; break ;
     case ekoerpergroesse:sfout += "koerpergroesse}{"; break ;
     case egrad:sfout += "grad}{"; break ;
     case espezialisierung:sfout += "spezialisierung}{"; break ;
     case estand:sfout += "stand}{"; break ;
     case eherkunft:sfout += "herkunft}{"; break ;
     case eglaube:sfout += "glaube}{"; break ;
     case enamecharakter:sfout += "namecharakter}{"; break ;
     case enamespieler : sfout += "namespieler}{"; break ;
     case egfp : sfout += "gfp}{"; break ;
     case eaep : sfout += "aep}{"; break ;
     case ekep : sfout += "kep}{"; break ;
     case ezep : sfout += "zep}{"; break ;
     case egold : sfout += "gold}{"; break ;
     case esilber : sfout += "silber}{"; break ;
     case ekupfer : sfout += "kupfer}{"; break ;
     case eruestung : sfout += "ruestung}{"; break ;
     case eruestunglp : sfout += "ruestunglp}{"; break ;
     case eruestungb : sfout += "ruestungb}{"; break ;
     case eruestunglpb : sfout += "ruestunglpb}{"; break ;
     case esinnse : sfout += "sinnse}{"; break ;
     case esinnh  : sfout += "sinnh}{"; break ;
     case esinnr  : sfout += "sinnr}{"; break ;
     case esinnsc : sfout += "sinnsc}{"; break ;
     case esinnt  : sfout += "sinnt}{"; break ;
     case esinnss : sfout += "sinnss}{"; break ;
     default : sfout  += "XXX"; break;
   }
  if(!empty)
   {
    const Grundwerte &W=A;
    switch(was) {
     case etyp  : {
        std::string styp;
        if(!W.Bezeichnung().empty())
          {  styp=W.Bezeichnung()+" ("+A.Typ1()->Short();
             if(!A.Typ2()->Short().empty()) styp +="/"+A.Typ2()->Short();
             styp+=")";
          }
        else 
          { styp = A.Typ1()->Name(W.Geschlecht());
            if (A.Typ2()->Name(W.Geschlecht())!="") 
               styp += "/"+A.Typ2()->Name(W.Geschlecht());
          }
        sfout += LaTeX_scale(styp,10,"2.2cm") ; 
        break;
      }      
     case emagusversion : sfout += VERSION; break;
     case e_last_saved_time : sfout += A.LastSavedAt(); break;
     case espezies : sfout += LaTeX_scale(W.Spezies()->Name(),10,"2cm") ; break;
     case emerk :    sfout +=W.Merkmale(); break;
     case est   : sfout += itos(W.St()); break ;
     case egs   : sfout += itos(W.Gs()); break ;
     case egw   : sfout += itos(W.Gw()) + W.Ruestung_RW_Verlust(); break ;
     case eko   : sfout += itos(W.Ko()); break ;
     case ein   : sfout += itos(W.In()); break ;
     case ezt   : sfout += itos(W.Zt()); break ;
     case eau   : { int ia=A.Erfolgswert("Athletik").first;
         ia/=3;
         std::string sa; if(ia>0) sa="^{+"+itos(ia)+"}"  ;
         sfout += LaTeX_scale("$"+itos(W.Au())+sa+"$",8,"0.9cm"); break ;
      }
     case epa   : sfout += itos(W.pA()); break ;
     case esb   : sfout += itos(W.Sb()); break ;
     case ewk   : sfout += itos(W.Wk()); break ;
     case eb    : {
        int b=A.Erfolgswert("Laufen").first-2; 
        std::string bs;  if(b>0) bs="^{+"+itos(b)+"}"  ;
        sfout += LaTeX_scale("$"+itos(W.B())+A.Ruestung_B_Verlust(false)+bs+"$",8,"0.9cm"); break ;
      }
     case ekaw  : sfout += itos(W.KAW()); break ;
     case egsb  : sfout += itos(W.Geistesblitz()); break ;
     case egn   : sfout += itos(W.GG()); break ;
     case esg   : sfout += itos(W.SG()); break ;
     case elp   : sfout += itos(W.LP()); break ;
     case eap   : sfout += itos(W.AP()); break ;
     case eboau : sfout += itos0p(W.bo_Au(),0,true); break ;
     case ebosc : sfout += itos0p(W.bo_Sc(),0,true); break ;
     case eboan : sfout += itos0p(W.bo_An(),0,true); break ;
     case eboab : sfout += itos0p(W.bo_Ab(),0,true); break ;
     case eboza : sfout += itos0p(W.bo_Za(),0,true); break ;
     case ebopsy: sfout += itos0p(W.bo_Psy(),0,true); break ;
     case ebophs: sfout += itos0p(W.bo_Phs(),0,true); break ;
     case ebophk: sfout += itos0p(W.bo_Phk(),0,true); break ;
     case eres  : sfout += itos0p(W.Resistenz(),0,true); break ;
     case epsy  : sfout += itos0p(W.Resistenz()+W.bo_Psy(),0,true); break ;
     case ephs  : sfout += itos0p(W.Resistenz()+W.bo_Phs(),0,true); break ; 
     case ephk  : sfout += itos0p(W.Resistenz()+W.bo_Phk(),0,true); break ;
     case egift : sfout += itos(W.Gift()); break ;
     case eabwehr:sfout += itos0p(W.Abwehr_wert(),0,true); break ;
     case eabwehrfinal:
     case eabwehrmitwaffe:
      { if(was==eabwehrfinal)    sfout += itos0p(W.Abwehr_wert()+W.bo_Ab(),-1,true);
        if(was==eabwehrmitwaffe) sfout += TeX::string2TeX(
            Waffe::get_Verteidigungswaffe(W.Abwehr_wert()+W.bo_Ab(),
               A.List_Waffen(),A.List_Waffen_besitz(),A));
        sfout += W.Ruestung_Abwehr_Verlust(A.List_Fertigkeit());
        break;
      }
     case eppresistenz:sfout += EmptyInt_4TeX(A.ResistenzPP()); break ;
     case eppabwehr:sfout += EmptyInt_4TeX(A.AbwehrPP()); break ;
     case eppzauber: 
          if(A.ZauberSpruecheMitPP())              sfout += EmptyInt_4TeX(A.ZaubernPP()); 
          else if(A.ZaubernPP() || A.SpezialPP() ) sfout += itos(A.ZaubernPP())+"/"+itos(A.SpezialPP()); 
          break ;
     case ezauber:sfout += itos0p(W.Zaubern_wert(),0,true); break ;
     case ehand:sfout += LaTeX_scale(W.Hand(),7,"1.2cm"); break ;
     case eraufen:sfout += itos(W.Raufen()); break ;
     case ealter:sfout += itos(W.Alter()); break ;
     case egewicht:sfout += itos(W.Gewicht())+ "\\,kg"; break ;
     case egestalt:sfout += LaTeX_scale(W.Gestalt(),5,"0.7cm"); break ;
     case ekoerpergroesse:sfout += LaTeX_scale(dtos(W.Groesse()/100.)+ "\\,m~\\scriptsize(" + W.GroesseBez()+")",8,"0.9cm"); break ;
     case egrad:sfout += itos(W.Grad()); break ;
     case espezialisierung:sfout += LaTeX_scale(W.Spezialisierung(),10,"2.2cm") ; break ;
     case estand:sfout += LaTeX_scale(W.Stand(),10,"1.5cm"); break ;
     case eherkunft:sfout += LaTeX_scale(W.Herkunft()->Name(),10,"2.2cm"); break ;
     case eglaube:sfout += LaTeX_scale(W.Glaube(),10,"2.5cm"); break ;
     case enamecharakter:sfout += LaTeX_scale(W.Name_Abenteurer(),25,"4.5cm"); break ;
     case enamespieler : sfout += LaTeX_scale(W.Name_Spieler(),25,"4.5cm"); break ;
     case egfp : sfout += EmptyInt_4TeX(W.GFP(),10); break ;
     case eaep : sfout += EmptyInt_4TeX(W.AEP(),10); break ;
     case ekep : sfout += EmptyInt_4TeX(W.KEP(),10); break ;
     case ezep : sfout += EmptyInt_4TeX(W.ZEP(),10); break ;
/*
     case egold   : sfout += "\\tiny " + itos0p(W.Gold()); break ;
     case esilber : sfout += "\\tiny " + itos0p(W.Silber()); break ;
     case ekupfer : sfout += "\\tiny " + itos0p(W.Kupfer()); break ;
*/
     case egold   : sfout += EmptyInt_4TeX(W.Gold(),10); break ;
     case esilber : sfout += EmptyInt_4TeX(W.Silber(),10); break ;
     case ekupfer : sfout += EmptyInt_4TeX(W.Kupfer(),10); break ;
     case eruestung : sfout += W.Ruestung()->Name(); break ;
     case eruestunglp : sfout += itos(W.Ruestung()->LP_Verlust()); break ;
     case eruestungb : sfout += W.Ruestung(1)->Name(); break ;
     case eruestunglpb : sfout += itos(W.Ruestung(1)->LP_Verlust()); break ;
     case esinnse : sfout += itos0p(W.Sehen(),0,true     ); break ;
     case esinnh  : sfout += itos0p(W.Hoeren(),0,true    ); break ;
     case esinnr  : sfout += itos0p(W.Riechen(),0,true   ); break ;
     case esinnsc : sfout += itos0p(W.Schmecken(),0,true ); break ;
     case esinnt  : sfout += itos0p(W.Tasten(),0,true    ); break ;
     case esinnss : sfout += itos0p(W.SechsterSinn(),-1,true); break ;
     default : sfout += "XXX"; break;
    }
   }
  if(sfout.find("XXX")==std::string::npos)
     fout << sfout<< "}\n";
 }
}


void LaTeX_drucken::write_sprachen(std::ostream &fout,const std::vector<Sprache_und_Schrift>& L,bool longlist)
{
  unsigned int sprachanz=0;
  for(std::vector<Sprache_und_Schrift>::const_iterator i=L.begin();i!=L.end();++i)
   {
      std::string a = LaTeX_string(sprachanz++);
      if(a=="0") break;
      if(!longlist) fout << "\\newcommand{\\spra"<<a<<"}";
      fout << "{\\scriptsize " << LaTeX_scale((*(i->getSprache()))->Name(),20,"2.6cm") <<"}\n";

      if(!longlist) fout << "\\newcommand{\\spraw"<<a<<"}";
      else fout << " & ";
      fout << "{\\scriptsize " << i->getErfolgswert() <<"}\n";

      std::string ss;
      for(std::vector<Sprache_und_Schrift::st_sus>::const_iterator j=i->getSchriften().begin();j!=i->getSchriften().end();)
       {
         ss+= j->/*schrift*/buchstaben + "$\\;$+"+itos(j->wert);
         if(++j!=i->getSchriften().end())  ss+=", ";
       }
      if(!longlist) fout << "\\newcommand{\\schr"<<a<<"}";
      else fout << " & ";
      fout <<"{\\scriptsize "<< LaTeX_scale(ss,20,"2.6cm") <<"}";
      if(longlist) fout << "\\\\";
      fout << "\n";
   }
 if(!longlist)
  for (unsigned int i=sprachanz; i<maxsprach;++i) // Bis zum Ende auffüllen
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schrw"<<a<<"}{\\scriptsize }\n";
   }
}

void LaTeX_drucken::write_fertigkeiten(const Abenteurer &A,std::ostream &fout,const std::list<MBEmlt>& L,bool longlist)
{
  unsigned int count=0;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
   {
     std::string a = LaTeX_string(count++);
     if(a=="0") break;
     if(!longlist) fout <<"\\newcommand{\\fert"<<a<<"}";
     fout << "{\\scriptsize " <<LaTeX_scale((*(*i))->Name()+" "+(*i)->Zusatz(),33,"4cm") << "}";

     if(!longlist) fout << "\\newcommand{\\praxis"<<a<<"}";
     else fout << " & ";
     if((*i)->What()==MidgardBasicElement::FERTIGKEIT_ANG)
          fout <<"{--}";
     else fout <<"{"<< itos0p((*i)->Praxispunkte()) << "}";

     std::string wert;
     if((*(*i))->What()==MidgardBasicElement::FERTIGKEIT)
       wert=itos0p(cH_Fertigkeit((*i)->getMBE())->FErfolgswert(A,*i),0,true);
     else if((*(*i))->What()==MidgardBasicElement::FERTIGKEIT_ANG)
       wert=itos0p(cH_Fertigkeit_angeborene((*i)->getMBE())->FErfolgswert(A,*i),0,true);
     else if((*(*i))->What()==MidgardBasicElement::WAFFE)
       wert=itos0p((*i)->Erfolgswert(),0,true);
     if(!longlist) fout << "\\newcommand{\\wert"<<a<<"}";
     else fout << " & ";
     fout << "{"  <<wert<< "}";
     if(longlist) fout << "\\\\";
     fout << "\n";
   }
 if(!longlist)
 for (unsigned int i=count; i<maxfert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\praxis"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";
   }
}

struct st_WB{std::string name;std::string wert;std::string schaden;
                    std::string rang;std::string modi;
              st_WB(std::string n,std::string w,std::string s,
                                  std::string r,std::string m)
                    : name(n),wert(w),schaden(s),rang(r),modi(m) {}};

void LaTeX_drucken::write_waffenbesitz(const Abenteurer &A, std::ostream &fout,const std::list<H_WaffeBesitz>& L,bool longlist)
{
  std::string angriffsverlust = A.Ruestung_Angriff_Verlust(A.List_Fertigkeit());
  std::vector<st_WB> VWB;
  VWB.push_back(st_WB("Raufen",itos(A.Raufen()),
                      A.RaufenSchaden(),"",""));
  for(std::list<H_WaffeBesitz>::const_iterator i=L.begin();i!=L.end();++i)
   {
     std::string waffenname = (*i)->AliasName();
     if ((*i)->Magisch()!="" || (*i)->av_Bonus()!=0 || (*i)->sl_Bonus()!=0) 
         waffenname+="$^*$ "+(*i)->Bonus() ;
     std::string swert;

     if ((*i)->Waffe()->Verteidigung()) // Erfolgswert für Verteidigungswaffen
      {
        int wert = (*i)->Erfolgswert()+(*i)->av_Bonus()+(*i)->Waffe()->WM_Angriff((*i)->AliasName());
        swert=itos(wert);
      }
     else  // Erfolgswert für Angriffswaffen
      {
        int wert = (*i)->Erfolgswert()+A.bo_An()+(*i)->av_Bonus()+(*i)->Waffe()->WM_Angriff((*i)->AliasName());
        // Angriffsbonus subtrahieren, wenn schwere Rüstung getragen wird:
        swert = itos(wert)+angriffsverlust;
      }
     std::string schaden=(*i)->Schaden(A,(*i)->AliasName());
     std::string anm = (*i)->Waffe()->Waffenrang();
     std::string abm = (*i)->Waffe()->WM_Abwehr();
     std::string text=(*i)->Waffe()->Text();
     
     bool grund_ist_gelernt = false;
     if( !(*i)->Waffe()->ZweiteGrundkenntnis().empty() )
        grund_ist_gelernt=MBEmlt(&*cH_WaffeGrund((*i)->Waffe()->ZweiteGrundkenntnis()))
           ->ist_gelernt(A.List_WaffenGrund());
                    
     if(text.find("Einhändig")!=std::string::npos)
      { if(!(*i)->Waffe()->Min_St_Einhand(A)) text="";
        if(!grund_ist_gelernt) text="";
      }
                                             
     VWB.push_back(st_WB(LaTeX_scalemag(waffenname,25,"3cm",(*i)->Magisch(),
            TeX::string2TeX((*i)->Waffe()->Reichweite()+" "+(*i)->Waffe()->Text())),
            swert,schaden,anm,abm));
   }
 unsigned int count=0;
 for(std::vector<st_WB>::const_iterator i=VWB.begin();i!=VWB.end();++i)
  {
    std::string b = LaTeX_string(count++);
    if(b=="0") break;
    if(!longlist) fout << "\\newcommand{\\waffeE"<<b<<"}";
    else fout << " & ";
    fout << "{+"<<TeX::string2TeX(i->wert)<<"}\n";
     if(!longlist) fout << "\\newcommand{\\waffeA"<<b<<"}";
     else fout << " & ";
     fout << "{"<<TeX::string2TeX(i->rang) << "}";
     if(longlist) fout << "\\\\\\cline{2-3}";
     fout << "\n";

     if(!longlist) fout << "\\newcommand{\\waffe"<<b<<"}{ " ;
     else fout << "\\raisebox{1.5ex}[-1.5ex]{\\makebox[2cm][l]{ ";
     fout << i->name <<"}\n";
     if(!longlist) fout << "\\newcommand{\\waffeS"<<b<<"}";
     else fout << "} & ";
     fout << "{"<<TeX::string2TeX(i->schaden) << "}\n";
     if(!longlist) fout << "\\newcommand{\\waffeV"<<b<<"}";
     else fout << " & ";
     fout << "{"<<TeX::string2TeX(i->modi) << "}";
     if(longlist) fout << "\\\\\\hline\\hline";
     fout << "\n";
  }
 if(!longlist)
  for (unsigned int i=count; i<maxwaffen;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\waffe"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeE"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeS"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeA"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeV"<<a<<"}{\\scriptsize }\n";
   }
}


void LaTeX_drucken::write_universelle(const Abenteurer &A,std::ostream &fout)
{
 std::list<Abenteurer::st_universell> UF=A.List_Universell();
 int countunifert=0;
 for(std::list<Abenteurer::st_universell>::iterator i=UF.begin();i!=UF.end();++i)
  {
    std::string a = LaTeX_string(countunifert);
    if(a=="0") break;
    std::string name = (*i->mbe)->Name();
    std::string wert;
    int iwert= i->mbe->Erfolgswert();
    if   (iwert>=0) wert = "+"+itos(iwert);
    else            wert = "--"+itos(abs(iwert));
    
    if     (name=="Geheimmechanismen öffnen") name = "Geheimmech. öffnen";
    else if(name=="Landeskunde (Heimat)") name = "Landeskunde ("+A.Herkunft()->Name()+")";

    if (!i->gelernt)
     {
       ++countunifert;
       fout <<"\\newcommand{\\uni"<<a<<"}{"<<name<< "}\t\t";
       if (i->voraussetzung)
          fout << "\\newcommand{\\uniw"<<a<<"}{("<<wert << ")}\n";
       else
          fout << "\\newcommand{\\uniw"<<a<<"}{$^*\\!$("<<wert << ")}\n";
     }
  } 

 // Universelle Fertigkeiten auffüllen
 for (unsigned int i=countunifert; i<maxunifert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\uni"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\uniw"<<a<<"}{\\scriptsize }\n";
   }

}


void LaTeX_drucken::write_long_list(const Abenteurer &A,std::ostream &fout,const std::vector<Sprache_und_Schrift>& S,
                     const std::list<MBEmlt> &F,
                     const std::list<H_WaffeBesitz> &WB_druck)
{
  fout << "\n\n\\newpage\n\n";
//  fout << "\\catcode`\\~=12\n"; // omitting this kills the printing on Windows - latex bug?
  fout << "\\begin{sideways}\n";
//  fout << "\\rotatebox{90}{\n";
  fout << "\\fbox{\n";
  fout << "\\begin{minipage}[t][\\textwidth]{19cm}\n";

  // Fertigkeiten & Waffen
  fout << "\\parbox{7cm}{\n"
          "\\setlength{\\tabcolsep}{0.4em}\n"
          "\\footnotesize"
          "\\begin{tabular}[t]{|p{4cm}|c|r|}\\hline\n"
          "\\multicolumn{3}{|c|}{\\small angeborene und erlernte}\\\\\n"
          "\\multicolumn{3}{|c|}{\\small Fähigkeiten und Waffenfertigkeiten}\\\\[1ex]\n"
          "\\normalsize Fertigkeit&{$\\!$\\normalsize PP$\\!$}&{$\\!\\!$\\normalsize EW$\\!\\!$}\\\\\\hline\\hline\n";
  write_fertigkeiten(A,fout,F,true);
  fout << "\\hline\n\\end{tabular}}\n";

  // Sprache & Schrift
  fout << "\\parbox{9cm}{\n"
          "\\setlength{\\tabcolsep}{0.5em}\n"
          "\\scriptsize\n"
          "\\begin{tabular}{|p{2.6cm}|c|p{2.6cm}|}\n"
          "\\hline\n"
          "Sprache&Wert&Schrift\\\\\\hline\\hline\n";
  write_sprachen(fout,S,true);
  fout << "\\hline\n\\end{tabular}\n\n";

  // Waffenbesitz
  fout << "\\bigskip\n"
          "\\setlength{\\tabcolsep}{0.3em}\n"
          "\\begin{tabular}[t]{||p{3.1cm}|c|c||}\\hline\\hline\n"
          "\\raisebox{-1ex}[2ex][0ex]{\\LARGE Waffe}&\\normalsize Erfolgswert&\\footnotesize Waffenrang\\\\\\cline{2-3}\n"
          "\\raisebox{-0.2ex}[1ex][0.2ex]{\\footnotesize (Reichweite)}&\\normalsize\\raisebox{-0.2ex}[1ex][0.2ex]{Schaden}&\\footnotesize Abwehrmod.\\\\\\hline\\hline\\hline\n";
  write_waffenbesitz(A,fout,WB_druck,true);
  fout << "\\hline\n\\end{tabular}}\n";

  fout <<"\\vfill\\hfill\n";
  fout <<"\\parbox{1.5cm}{\\usebox{\\LogoBoxKlein}}";
  fout << "\\end{minipage}\n";
  fout << "}\n";
  fout << "\\end{sideways}\n";
}

std::string LaTeX_drucken::LaTeX_scale(const std::string& is, 
      unsigned int maxlength, const std::string& scale)
{
 std::string os;
 if (is.size() <= maxlength) os = is;
 else  os = "\\resizebox*{"+scale+"}{1.5ex}{"+is+"}" ;
 return os;
}

std::string LaTeX_drucken::LaTeX_scalemag(const std::string& is, 
      unsigned int maxlength, const std::string& scale,
       const std::string& magisch,const std::string& reichweite)
{
 std::string os;
 if (is.size() <= maxlength) os = is;
 else  os = "\\resizebox*{"+scale+"}{1.5ex}{"+is+"}" ;
  std::string l1=os,l2;
  if (magisch==""||magisch=="*") 
   {
     if(reichweite.size()<=25) l2 = "{\\tiny "+reichweite+"}";
     else l2 = "\\resizebox*{"+scale+"}{1.5ex}{\\tiny "+reichweite+"}" ;
   }
  else  
    { if (magisch.size()<=25) l2 = "\\tiny "+magisch;
      else l2 = "\\resizebox*{"+scale+"}{1.5ex}{\\tiny "+magisch+"}" ;
    }
  os = "\\parbox{2cm}{\\mbox{"+l1+"}" ;
  if (l2!="")  os += "\\tiny\\\\ \\mbox{"+l2+"}";
  os += "}";
 return os;
}


std::string LaTeX_drucken::LaTeX_string(int i)
{  if (i<26) return std::string(1,char('a'+i));
   if (i<52) return "a"+std::string(1,char('a'+i-26));
   if (i<78) return "b"+std::string(1,char('a'+i-52));
   //Never get here
   return("0");
}

void LaTeX_drucken::LaTeX_Bildboxen(std::ostream &fout,const std::string &file,const double width_of_abenteurer_cm)
{
 fout << "\\newsavebox{\\DrachenBox}\n";
 fout << "\\newsavebox{\\SmallDrachenBox}\n";
 fout << "\\newsavebox{\\LogoBox}\n";
 fout << "\\newsavebox{\\LogoBoxKlein}\n";
 fout << "\\newsavebox{\\SaebelBox}\n";
 fout << "\\newsavebox{\\GeldBox}\n";
 fout << "\\newsavebox{\\LetterFeatherBox}\n";
 fout << "\\newsavebox{\\WurfbeilBox}\n";
 fout << "\\newsavebox{\\AbenBox}\n";

 fout << WinLux::normal_tilde;
 fout << "\\sbox{\\DrachenBox}{\\includegraphics[width=9.9cm]{"<<WinLux::recodePathForTeX(magus_paths::with_path("drache.png"))<<"}}\n";
 fout << "\\sbox{\\SmallDrachenBox}{\\includegraphics[width=6.5cm]{"<<WinLux::recodePathForTeX(magus_paths::with_path("drache.png"))<<"}}\n";
 fout << "\\sbox{\\LogoBox}{\\includegraphics[width=2.5cm]{"<< WinLux::recodePathForTeX(magus_paths::with_path("MAGUS-Logo-grey2.png"))<<"}}\n";
 fout << "\\sbox{\\LogoBoxKlein}{\\includegraphics[width=1.5cm]{"<< WinLux::recodePathForTeX(magus_paths::with_path("MAGUS-Logo-grey2.png"))<<"}}\n";
 fout << "\\sbox{\\SaebelBox}{\\includegraphics[height=0.7cm]{"<< WinLux::recodePathForTeX(magus_paths::with_path("saebel.png"))<<"}}\n";
 fout << "\\sbox{\\GeldBox}{\\includegraphics[height=0.9cm]{"<< WinLux::recodePathForTeX(magus_paths::with_path("Money-gray.png"))<<"}}\n";
 fout << "\\sbox{\\LetterFeatherBox}{\\includegraphics[width=2.5cm]{"<< WinLux::recodePathForTeX(magus_paths::with_path("Letter-Feather-grey.png"))<<"}}\n";
 fout << "\\sbox{\\WurfbeilBox}{\\includegraphics[width=3.5cm]{"<< WinLux::recodePathForTeX(magus_paths::with_path("wurfbeil.png"))<<"}}\n";


 // Ab jetzt geht es um das Bild des Abenteurers ////////////////////////////
// std::string figwidth=itos(hauptfenster->getWerte().BeschreibungPixSize())+"cm";
// std::string file=hauptfenster->getWerte().BeschreibungPix();
 fout << "\\sbox{\\AbenBox}{\\includegraphics[width="+dtos(width_of_abenteurer_cm)+"cm]";
 if(!file.empty())  fout << "{"+WinLux::recodePathForTeX(file)+"}}\n";
 else               fout << "{"<< WinLux::recodePathForTeX(magus_paths::with_path("MAGUS-Logo-grey2.png"))<<"}}\n";
    
 ////////////////////////////////////////////////////////////////////////////
 fout << WinLux::active_tilde; 
}

void LaTeX_drucken::LaTeX_newsavebox(const Abenteurer &A,std::ostream &fout)
{
// fout << WinLux::normal_tilde;
// fout << "\\newcommand{\\installpath}{"<<get_latex_pathname(TeX_Install)<< "}\n";
// fout << WinLux::active_tilde; 
 fout << "\\usepackage{german}\n";
 fout << "\\usepackage[latin1]{inputenc}\n";
 fout << "\\usepackage[pdftex]{graphicx}\n";
#ifdef __MINGW32__ 
 fout << "\\DeclareGraphicsRule{.PNG}{png}{.PNG}{}\n"
 	"\\DeclareGraphicsRule{.JPG}{jpg}{.JPG}{}\n"
 	"\\DeclareGraphicsRule{.PDF}{pdf}{.PDF}{}\n";
 	// tif?
#endif 
 fout << "\\newsavebox{\\Einhandschwert}    \n";
 fout << "\\newsavebox{\\Stichwaffe}  \n";
 fout << "\\newsavebox{\\Einhandschlagwaffe}\n";
 fout << "\\newsavebox{\\Spiesswaffe}\n";
 fout << "\\newsavebox{\\Zweihandschwert}\n";
 fout << "\\newsavebox{\\Zweihandschlagwaffe}\n";
 fout << "\\newsavebox{\\Stangenwaffe}   \n";
 fout << "\\newsavebox{\\Kettenwaffe}    \n";
 fout << "\\newsavebox{\\KampfohneWaffen}\n";
 fout << "\\newsavebox{\\Zauberstaebe}   \n";
 fout << "\\newsavebox{\\Wurfspiess}     \n";
 fout << "\\newsavebox{\\Stielwurfwaffe} \n";
 fout << "\\newsavebox{\\Wurfscheibe}    \n";
 fout << "\\newsavebox{\\Fesselwaffe}    \n";
 fout << "\\newsavebox{\\Armbrust}       \n";
 fout << "\\newsavebox{\\Bogen}          \n";
 fout << "\\newsavebox{\\Schleuder}\n";
 fout << "\\newsavebox{\\Schild}\n";
 fout << "\\newsavebox{\\Parierwaffe}\n";
 fout << "\\newsavebox{\\Kampfstab}\n"; 
 fout << "\\newsavebox{\\Peitsche} \n"; 
 fout << "\\newsavebox{\\Garotte}  \n"; 
 fout << "\\newsavebox{\\Wurfmesser}\n";
 fout << "\\newsavebox{\\Blasrohr}  \n";
 fout << "\\newsavebox{\\Wurfpfeil} \n";
 fout << "\\newsavebox{\\Werfen}    \n";
 LaTeX_Bildboxen(fout,A.BeschreibungPix(),2.5);
}


void LaTeX_drucken::LaTeX_kopfzeile(const Abenteurer &A,std::ostream &fout,bool landscape,bool newdoc)
{
 if(newdoc)
  {
    if(landscape)
     {
       fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(A.Name_Abenteurer(),25,"4.5cm") << "}\n";
       fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(A.Name_Spieler(),25,"4.5cm") << "}\n";
     }
    else
     {
       fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(A.Name_Abenteurer(),20,"4.cm") << "}\n";
       fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(A.Name_Spieler(),20,"4.cm") << "}\n";
     }
  }
 std::string     drache="9.9cm", namensbox="7cm";
 if(!landscape) {drache="6.5cm" , namensbox="5cm";}
// fout << WinLux::normal_tilde;
 if(landscape)  fout << "\\parbox{"+drache+"}{\\usebox{\\DrachenBox}}\n";
 else           fout << "\\parbox{"+drache+"}{\\usebox{\\SmallDrachenBox}}\n";
// fout << WinLux::active_tilde; 
 fout << "\\parbox[][][c]{"+namensbox+"}{\n";
 if(!landscape) fout << "\\scriptsize\n";
 fout << "\\LI\n";
 fout << "\\begin{tabularx}{"+namensbox+"}{|c|X|}\\hline\n";
 fout << "\\makebox[1.1cm]{Figur}&\\namecharakter\\\\\\hline\n";
 fout << "\\end{tabularx}\n\n";
 if(landscape)  fout <<"\\vspace{2mm}\\li\n";
 else           fout <<"\\vspace{0.5mm}\\li\n";
 fout <<"\\begin{tabularx}{"+namensbox+"}{|c|X|}\\hline\n";
 fout <<"\\makebox[1.1cm]{Spieler}&\\namespieler\\\\\\hline\n";
 fout <<"\\end{tabularx}\n}\n";
// fout << WinLux::normal_tilde;
 if(landscape)  fout << "\\parbox{"+drache+"}{\\usebox{\\DrachenBox}}\n";
 else           fout << "\\parbox{"+drache+"}{\\usebox{\\SmallDrachenBox}}\n";
// fout << WinLux::active_tilde;
 fout <<"\\vspace*{2ex}\n\n";
}

void LaTeX_drucken::LaTeX_header(const Abenteurer &A,std::ostream &fout,bool landscape,bool kopfzeile)
{
 if(landscape) fout << "\\documentclass[a4paper,10pt,landscape]{article}\n" ;
 else   fout << "\\documentclass[a4paper,10pt]{article}\n";

 fout << "\\usepackage{german}\n\\usepackage[latin1]{inputenc}\n";
 fout << "\\usepackage[pdftex]{graphicx}\n";
 fout << "\\usepackage{tabularx}\n";
 fout << "\\usepackage{longtable}\n";
 fout << "\\usepackage{times}\n";
 fout << "\\usepackage{color}\n";
 fout << "\\usepackage{wrapfig}\n";
 fout << "\\definecolor{mygray}{gray}{0.75}\n";

 if(landscape)
  {
   fout << "\\setlength{\\textheight}{20.0cm}\n";
   fout << "\\setlength{\\textwidth}{28cm}\n";
   fout << "\\setlength{\\oddsidemargin}{-2.0cm}\n";
   fout << "\\setlength{\\evensidemargin}{-2.0cm}\n";
   fout << "\\setlength{\\topmargin}{-3.0cm}\n\n\n";
  }
 else
  {
   fout << "\\setlength{\\textheight}{27.0cm}\n";
   fout << "\\setlength{\\textwidth}{18.5cm}   \n";
   fout << "\\setlength{\\arraycolsep}{0.1cm} \n";
   fout << "\\setlength{\\evensidemargin}{-1.cm}\n";
   fout << "\\setlength{\\oddsidemargin}{-1.cm} \n";
   fout << "\\setlength{\\topmargin}{-3.0cm}    \n";
   fout << "\\setlength{\\parindent}{0em}       \n";
   fout << "\\renewcommand {\\arraystretch}{1.3}\n\n";

   fout << "\%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
   fout << "\%% Listenumgebungen\n";
   fout << "\%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
   fout << "\\newenvironment{punkte}{\n";
   fout << "\\begin{list}{$\\bullet$}\n";
   fout << "{\n";
   fout << "\\setlength{\\labelwidth}{0.5cm}\n";
   fout << "\\setlength{\\leftmargin}{1.cm} \n";
   fout << "\\setlength{\\labelsep}{0.5cm}  \n";
   fout << "\\setlength{\\rightmargin}{0.5cm}\n";
   fout << "\\setlength{\\parsep}{0.1ex plus0.1ex minus0.1ex} \n";
   fout << "\\setlength{\\itemsep}{0.1ex plus0.1ex minus0.1ex}\n";
   fout << "}}\n";
   fout << "{\n";
   fout << "\\end{list}\n";
   fout << "}\n";


   fout << "\\newenvironment{punkte2}{\n";
   fout << "\\begin{list}{$\\star$}\n";   
   fout << "{\n";
   fout << "\\setlength{\\labelwidth}{0.5cm}\n";
   fout << "\\setlength{\\leftmargin}{1.cm} \n";
   fout << "\\setlength{\\labelsep}{0.5cm}  \n";
   fout << "\\setlength{\\rightmargin}{0.5cm}\n";
   fout << "\\setlength{\\parsep}{0.0ex plus0.1ex minus0.1ex} \n";
   fout << "\\setlength{\\itemsep}{0.0ex plus0.1ex minus0.1ex}\n";
   fout << "}}\n";
   fout << "{\n"; 
   fout << "\\end{list}\n";
   fout << "}\n";
  }
 fout << "\\newcommand{\\LI}{\\setlength{\\arrayrulewidth}{0.4mm}}\n";
 fout << "\\newcommand{\\li}{\\setlength{\\arrayrulewidth}{0.2mm}}\n";
 fout << "\\setlength{\\doublerulesep}{0mm}\n";
 fout << "\\pagestyle{empty}\n";
}

void LaTeX_drucken::LaTeX_header_doc(const Abenteurer &a,std::ostream &fout,bool landscape,bool kopfzeile)
{
 fout << "\\begin{document}\n";
 if(kopfzeile)
   {  
     fout << "\\begin{center}\n";
     LaTeX_kopfzeile(a,fout,landscape);
     fout << "\\end{center}\n";
    }
}
 
void LaTeX_drucken::LaTeX_footer(std::ostream &fout)
{
  fout << "\\end{document}\n\n";
}
 
void LaTeX_drucken::pdf_viewer(const std::string& file,const bool tex_two_times)
{ ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,file,tex_two_times);
  char currentwd[10240];
  *currentwd=0;
  getcwd(currentwd,sizeof currentwd);
  
  std::string pdflatex="pdflatex";
  
#ifdef __MINGW32__ // oder direkt mit Pfad aufrufen?
  static std::string TEXMF;
  if (TEXMF.empty()) 
  { TEXMF="TEXMF="+magus_paths::BinaryVerzeichnis()+"\\texmf";
    putenv(TEXMF.c_str());
  }
  ManuProC::Trace(LibMagus::trace_channel,"",NV("TEXMF",getenv("TEXMF")));
  pdflatex="\""+magus_paths::BinaryVerzeichnis()+"\\"+pdflatex+"\"";
#define unlink(a) _unlink(a)
#endif

  // LaTeX always writes to current dir first, so we change dir
  std::string file2=file;
  std::string::size_type lastslash=file.rfind(WinLux::dirsep);

  if (lastslash!=std::string::npos)
  {  ManuProC::Trace(LibMagus::trace_channel,"chdir",file.substr(0,lastslash));
     chdir((file.substr(0,lastslash)).c_str());
     file2=file.substr(lastslash+1);
  }

// oder batchmode?
//2x wg. longtable
  std::string cmd=pdflatex+" --interaction scrollmode "+file2+".tex";
  ManuProC::Trace(LibMagus::trace_channel,"system",cmd);
  system(cmd.c_str());
  ManuProC::Trace(LibMagus::trace_channel,"system",cmd);
  system(cmd.c_str());

  std::string pdfcommand=Programmoptionen->Viewer()+" "+file2+".pdf";
  Ausgabe(Ausgabe::Debug,pdfcommand);
//  const_cast<midgard_CG*>(hauptfenster)->set_status(pdfcommand,false);
  ManuProC::Trace(LibMagus::trace_channel,"CreateProcess",pdfcommand);
  if (!WinLux::CreateProcess(pdfcommand))
     Ausgabe(Ausgabe::Error,pdfcommand+" startet nicht");

//  unlink((file+".tex").c_str());
  unlink((file2+".aux").c_str());
  unlink((file2+".log").c_str());
//  unlink((pfile+".pdf").c_str());
  ManuProC::Trace(LibMagus::trace_channel,"chdir",currentwd);
  chdir(currentwd);
}

///////////////////////////////////////////////////////////////

void LaTeX_drucken::LaTeX_zauber(const Abenteurer &A,std::ostream &fout)
{
  for (std::list<MBEmlt>::const_iterator i=A.List_Zauber().begin();i!=A.List_Zauber().end();++i)
   {
     cH_Zauber z((*i)->getMBE());
     fout << z->Name() ;
     if(!(*i)->Zusatz().empty()) fout << " ("<<(*i)->Zusatz()<<")";
     fout <<" & ";
     fout << z->Erfolgswert_Z(A) <<" & ";
     fout << TeX::string2TeX(z->Ap()) << " & ";
     fout << TeX::string2TeX(z->Art())<< " & ";
     fout << TeX::string2TeX(z->Stufe()) << " & ";
     fout << TeX::string2TeX(z->Zauberdauer()) << " & ";
     fout << TeX::string2TeX(z->Reichweite()) << " & ";
     fout << TeX::string2TeX(z->Wirkungsziel()) << " & ";
     fout << TeX::string2TeX(z->Wirkungsbereich()) << " & ";
     fout << TeX::string2TeX(z->Wirkungsdauer()) << " & ";
     fout << TeX::string2TeX(z->Ursprung()) << " & " ;
     fout << LaTeX_scale(TeX::string2TeX(z->Material()),20,"3cm") << " & " ;
     fout << z->Agens(A.getVTyp()) <<" " <<z->Prozess() <<" "<<z->Reagens() ;
     fout << "\\\\\n";
     if(A.getOptionen().OptionenCheck(Optionen::ZauberBeschreibungDrucken).active
         && !z->Beschreibung().empty() )
       fout <<"\\multicolumn{13}{p{27cm}}{"
         "\\parbox{0.49cm}{~}\\parbox{26.5cm}{"
         "\\renewcommand{\\baselinestretch}{0.5}\\it\\tiny "<<TeX::string2TeX(z->Beschreibung())
         << "}}\\\\\n";
   }
}

void LaTeX_drucken::LaTeX_zaubermittel(const Abenteurer &A,std::ostream &fout)
{
  for (std::list<MBEmlt>::const_iterator i=A.List_Zauberwerk().begin();i!=A.List_Zauberwerk().end();++i)
   {
     cH_Zauberwerk z((*i)->getMBE());
//     std::string wert ;//= itos((*i)->Wert());
//     fout << wert <<" & ";
     fout << z->Name()  <<" & ";
     fout << z->Art()   <<" & ";
     fout << z->Stufe()   <<" & ";
     fout << z->Zeitaufwand()  <<" & ";
     fout << z->Preis()   <<" \\\\\n ";
   }
}


void LaTeX_drucken::LaTeX_zauber_main(const Abenteurer &A,std::ostream &fout)
{
  fout << "\\begin{center}\n";
//  LaTeX_kopfzeile(fout,true,false);
  fout << "\\scriptsize\n";
  fout << "\\begin{longtable}{lcclccclcclp{3cm}l}\n";
  fout <<"\\multicolumn{13}{c}{";
  LaTeX_kopfzeile(A,fout,true,false);
  fout << "}\\\\\n";
  fout << " & Erfolgs- & &&&Zauber-&Reich-&\\multicolumn{1}{c}{Wirkungs-}&Wirkungs-&"
       <<"  Wirkungs-&\\multicolumn{1}{c}{Ur-}&\\multicolumn{1}{c}{Material}&\\multicolumn{1}{c}{Prozess}\\\\ \n";
  fout << "\\raisebox{1.5ex}[-1.5ex]{Zauberformel} & wert     & "
       << "\\raisebox{1.5ex}[-1.5ex]{AP} & \\multicolumn{1}{c}{\\raisebox{1.5ex}[-1.5ex]{Art}}"
       << " & \\raisebox{1.5ex}[-1.5ex]{Stufe} & -dauer & weite&\\multicolumn{1}{c}{ziel}&bereich&"
       << "dauer&\\multicolumn{1}{c}{sprung}\\\\\\hline\n";
  fout << "\\endhead\n";
  LaTeX_zauber(A,fout);
  fout << "\\end{longtable}\n";

 
  if (!A.List_Zauberwerk().empty())
   {
     fout << "\\begin{tabular}{lllll}\\hline\n";
     fout << "Name&Art&Stufe&\\scriptsize Zeitaufwand&Kosten\\\\\\hline\n";
     LaTeX_zaubermittel(A,fout);
     fout << "\\end{tabular}\n";
   }
  fout << "\\end{center}\n";
}


/////////////////////////////////////////////////////////////////

void LaTeX_drucken::LaTeX_kido(const Abenteurer &A,std::ostream &fout)
{
  for (std::list<MBEmlt>::const_iterator i=A.List_Kido().begin();i!=A.List_Kido().end();++i)
   {
     cH_KiDo kd((*i)->getMBE());
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
     fout << TeX::string2TeX(kd->Effekt()) ;
     fout << "\\\\\n";
   }
}


void LaTeX_drucken::LaTeX_kido_main(const Abenteurer &A,std::ostream &fout)
{
//  fout << "\\end{center}\n";
  LaTeX_kopfzeile(A,fout,true,false);
  fout << "\\begin{tabular}{rllcp{17cm}}\n";
  fout << "\\multicolumn{5}{l}{\\large\\bf Erfolgswert KiDo: "
         <<KiDo::get_erfolgswert_kido(A.List_Fertigkeit())+A.bo_Za()<<"}\\\\\\hline\n";
  fout << " AP & HoHo & Technik & Stufe & Effekt \\\\\\hline \n";

  LaTeX_kido(A,fout);
  fout << "\\end{tabular}\n";
//  fout << "\\end{center}\n";
}

void LaTeX_drucken::Ausdrucken() { Ausdrucken(Abenteurer(),false); }
