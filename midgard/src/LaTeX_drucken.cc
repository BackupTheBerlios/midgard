// $Id: LaTeX_drucken.cc,v 1.42 2002/07/08 14:52:23 christof Exp $
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

#include <unistd.h>
#include <Misc/EmptyInt_4TeX.h>
#include "Sprache.hh"
#include "Waffe.hh"
#include "Fertigkeiten_angeboren.hh"
#include "LaTeX_drucken.hh"
#include <fstream>
#include "midgard_CG.hh"
#include "Fertigkeiten.hh"
#include "KiDo.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include <Gtk2TeX.h>
#include "recodestream.h"
#include "Windows_Linux.hh"

static std::string defFileName(const std::string &s)
{  std::string res;
   for (std::string::const_iterator i=s.begin();i!=s.end();++i)
      if (('0' <= *i && *i <= '9') || ('A' <= *i && *i <= 'Z')
      	|| ('a' <= *i && *i <= 'z') || *i=='_')
      	 res+=*i;
   return res;
}

std::string LaTeX_drucken::get_latex_filename(const LaTeX_Filenames what)
{
  std::string name=hauptfenster->getWerte().Name_Abenteurer();
  std::string version=hauptfenster->getWerte().Version();
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
      case TeX_tmp : return hauptfenster->getOptionen()->getString(Midgard_Optionen::tmppfad);
      case TeX_Install : 
      {  std::string result=hauptfenster->with_path("MAGUS-Logo-grey2.png",true);
         return WinLux::recodePathForTeX(result);
      }
    }
  abort(); // never get here
}


void LaTeX_drucken::on_latex_clicked(bool values=true)
{   
// std::string installfile=get_latex_pathname(TeX_Install)+get_latex_filename(TeX_MainDocument);
 std::string installfile=hauptfenster->with_path(get_latex_filename(TeX_MainDocument)+".tex");
 std::string filename=get_latex_pathname(TeX_tmp)+get_latex_filename(TeX_MainWerte);
 
cout <<"LaTeX: "<< filename<<'\n';
 {
 ofstream fout((filename+".tex").c_str());
#ifdef __MINGW32__
 orecodestream rfout(fout);
#else
 ostream &rfout=fout;
#endif
 if (values) LaTeX_write_values(rfout,installfile);
 else LaTeX_write_empty_values(rfout,installfile);

 if (hauptfenster->getChar().List_Zauber().size()>0 || hauptfenster->getChar().List_Zauberwerk().size()>0)  // Zauber
  {
    LaTeX_zauber_main(rfout);
  }
 if (hauptfenster->getChar().List_Kido().size()>0) // KiDo
  {
    LaTeX_kido_main(rfout);
  }
 rfout << "\\end{document}\n";
 rfout.flush();
 fout.close();
 }
 pdf_viewer(filename);
}      

void LaTeX_drucken::LaTeX_write_values(ostream &fout,const std::string &install_latex_file)
{
 fout << "\\documentclass[11pt,a4paper,landscape]{article}\n";
// fout << "\\newcommand{\\installpath}{"<<get_latex_pathname(TeX_Install)<< "}\n";
 LaTeX_newsavebox(fout);

 write_grundwerte(fout);
 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 {
 std::vector<st_sprachen_schrift> L;
 std::list<MidgardBasicElement_mutable> verwandteSprachen;
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Sprache().begin();i!=hauptfenster->getChar().List_Sprache().end();++i)
   {  //cH_Sprache s(*i);
      std::list<MidgardBasicElement_mutable> tmplist=cH_Sprache(*i)->VerwandteSprachen((*i).Erfolgswert(),hauptfenster->getChar().List_Sprache(),hauptfenster->getCDatabase().Sprache);
      verwandteSprachen.splice(verwandteSprachen.end(),tmplist);
      vector<pair<std::string,int> > vs=cH_Sprache(*i)->SchriftWert(hauptfenster->getChar().List_Schrift());
      L.push_back(st_sprachen_schrift(*i,vs));
   }
 verwandteSprachen=Sprache::cleanVerwandteSprachen(verwandteSprachen);
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=verwandteSprachen.begin();i!=verwandteSprachen.end();++i)
   { //cH_Sprache s(*i);
     if(i->ist_gelernt(hauptfenster->getChar().List_Sprache())) continue;
     L.push_back(st_sprachen_schrift(*i));
   }
 write_sprachen(fout,L);
 }
 /////////////////////////////////////////////////////////////////////////////
 // Grundfertigkeiten (Waffen)
 for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_WaffenGrund().begin();i!=hauptfenster->getChar().List_WaffenGrund().end();++i)
   {
      std::string sout = (*i)->Name();
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
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Beruf().begin();i!=hauptfenster->getChar().List_Beruf().end();++i)
     fout << (*i)->Name(); 
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // weitere Merkmale
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten & Waffen
 /////////////////////////////////////////////////////////////////////////////
 // angeborene Fertigkeiten
 std::list<MidgardBasicElement_mutable> L;
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Fertigkeit_ang().begin();i!=hauptfenster->getChar().List_Fertigkeit_ang().end();++i) 
     L.push_back(*i);
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Fertigkeit().begin();i!=hauptfenster->getChar().List_Fertigkeit().end();++i) 
    L.push_back(*i);
// Leerzeile ???
 /////////////////////////////////////////////////////////////////////////////
 // Waffen + Waffen/Besitz
 std::string angriffsverlust_string = hauptfenster->getWerte().Ruestung_Angriff_Verlust(hauptfenster->getChar().List_Fertigkeit());
 std::list<WaffeBesitz> WBesitz=hauptfenster->getChar().List_Waffen_besitz();
 std::list<WaffeBesitz> WB_druck;
 for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Waffen().begin();i!=hauptfenster->getChar().List_Waffen().end();++i)
   {
    L.push_back(*i);
    cH_Waffe w(*i);
    // waffenloser Kampf:
    if (w->Name()=="waffenloser Kampf" || w->Name()=="Faustkampf") 
     {
      WaffeBesitz W(w,w->Name(),0,0,"","");
      W.setErfolgswert(i->Erfolgswert());
      WBesitz.push_back(W);
     }
    for (std::list<WaffeBesitz>::const_iterator j=WBesitz.begin();j!=WBesitz.end();++j)
     {
      WaffeBesitz WB=*j;
      WB.setErfolgswert(i->Erfolgswert());
      if (WB.Waffe()->Name()==w->Name())  WB_druck.push_back(WB)  ;
     }
   }
 write_waffenbesitz(fout,WB_druck);
 write_fertigkeiten(fout,L);
 write_universelle(fout);

 fout << "\\input{"+WinLux::recodePathForTeX(install_latex_file)+"}\n";
}


void LaTeX_drucken::LaTeX_write_empty_values(ostream &fout,const std::string &install_latex_file)
{
 fout << "\\documentclass[11pt,a4paper,landscape]{article}\n";
// fout << "\\newcommand{\\installpath}{"<<get_latex_pathname(TeX_Install)<< "}\n";
 LaTeX_newsavebox(fout);
 write_grundwerte(fout,true);
 
 std::vector<st_sprachen_schrift> L;
 write_sprachen(fout,L);
 fout << "\\newcommand{\\beruf}{}\n" ;
 std::list<MidgardBasicElement_mutable> F;
 write_fertigkeiten(fout,F);
 std::list<WaffeBesitz> B;
 write_waffenbesitz(fout,B);
 write_universelle(fout);
/*
 // Universelle Fertigkeiten
 std::list<cH_MidgardBasicElement> UF;
 const std::list<cH_MidgardBasicElement> LF=hauptfenster->getCDatabase().Fertigkeit;
 for(std::list<cH_MidgardBasicElement>::const_iterator i=LF.begin();i!=LF.end();++i)
  {
    cH_Fertigkeit f(*i);
    if(f->Ungelernt()!=-99)
       UF.push_back(*i);
  }
 cH_MidgardBasicElement werfen(&*cH_Waffe("Werfen")); 
 UF.push_back(werfen);
 UF.sort(MidgardBasicElement_mutable::sort(MidgardBasicElement_mutable::sort::NAME));
 int countunifert=0;
 for(std::list<cH_MidgardBasicElement>::iterator i=UF.begin();i!=UF.end();++i)
  {
    std::string a = LaTeX_string(countunifert++);
    std::string name = (*i)->Name();
    std::string wert;
    if       ((*i)->What()==MidgardBasicElement::FERTIGKEIT) 
      { cH_Fertigkeit f(*i);
        wert = "+"+itos(f->Ungelernt());
        if(name=="Geheimmechanismen öffnen") name = "Geheimmech. öffnen";
        if(name=="Landeskunde (Heimat)") name = "Landeskunde";
      }
    else if  ((*i)->What()==MidgardBasicElement::WAFFE)    
      { cH_Waffe      f(*i);
        wert = "+4";
      }
//    f->set_Erfolgswert(f->Ungelernt());
    fout <<"\\newcommand{\\uni"<<a<<"}{\\tiny "<<name<< "}\t\t";
    fout << "\\newcommand{\\uniw"<<a<<"}{("<<wert << ")}\n";
  } 


// unsigned int maxunifert=48;
 for (unsigned int i=countunifert; i<maxunifert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\uni"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\uniw"<<a<<"}{\\scriptsize }\n";
   }
*/
 fout << "\\input{"+WinLux::recodePathForTeX(install_latex_file)+"}\n";
// fout.close();
}



void LaTeX_drucken::write_grundwerte(ostream &fout,bool empty=false)
{
 for(ewhat was=etyp;was<eMAX; was=ewhat(int(was)+1))
  {
   std::string sfout = "\\newcommand{\\";
   switch (was) {
     case etyp  : sfout += "typ}{"; break ;
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
     case egeld : sfout += "gold}{"; break ;
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
    const Grundwerte &W=hauptfenster->getWerte();
    switch(was) {
     case etyp  : {
        std::string styp;
        if(W.Bezeichnung().size())
          {  styp=W.Bezeichnung()+" ("+hauptfenster->getChar().Typ1()->Short();
             if(hauptfenster->getChar().Typ2()->Short().size()) styp +="/"+hauptfenster->getChar().Typ2()->Short();
             styp+=")";
          }
        else 
          { styp = hauptfenster->getChar().Typ1()->Name(W.Geschlecht());
            if (hauptfenster->getChar().Typ2()->Name(W.Geschlecht())!="") 
               styp += "/"+hauptfenster->getChar().Typ2()->Name(W.Geschlecht());
          }
        sfout += LaTeX_scale(styp,10,"2.2cm") ; 
        break;
      }      
     case emerk : { if(W.Spezies()->Name()!="Mensch") sfout += W.Spezies()->Name() + " ";
           sfout +=W.Merkmale(); 
         }
     case est   : sfout += itos(W.St()); break ;
     case egs   : sfout += itos(W.Gs()); break ;
     case egw   : sfout += itos(W.Gw()) + W.Ruestung_RW_Verlust(); break ;
     case eko   : sfout += itos(W.Ko()); break ;
     case ein   : sfout += itos(W.In()); break ;
     case ezt   : sfout += itos(W.Zt()); break ;
     case eau   : sfout += itos(W.Au()); break ;
     case epa   : sfout += itos(W.pA()); break ;
     case esb   : sfout += itos(W.Sb()); break ;
     case ewk   : sfout += itos(W.Wk()); break ;
     case eb    : sfout += itos(W.B()) + W.Ruestung_B_Verlust(); break ;
     case ekaw  : sfout += itos(W.KAW()); break ;
     case egsb  : sfout += itos(W.Geistesblitz()); break ;
     case egn   : sfout += itos(W.GG()); break ;
     case esg   : sfout += itos(W.SG()); break ;
     case elp   : sfout += itos(W.LP()); break ;
     case eap   : sfout += itos(W.AP()); break ;
     case eboau : sfout += itos(W.bo_Au()); break ;
     case ebosc : sfout += itos(W.bo_Sc()); break ;
     case eboan : sfout += itos(W.bo_An()); break ;
     case eboab : sfout += itos(W.bo_Ab()); break ;
     case eboza : sfout += itos(W.bo_Za()); break ;
     case ebopsy: sfout += itos(W.bo_Psy(hauptfenster->getChar().getVTyp())); break ;
     case ebophs: sfout += itos(W.bo_Phs(hauptfenster->getChar().getVTyp())); break ;
     case ebophk: sfout += itos(W.bo_Phk(hauptfenster->getChar().getVTyp())); break ;
     case eres  : sfout += itos(W.Resistenz()); break ;
     case epsy  : sfout += itos(W.Resistenz()+W.bo_Psy(hauptfenster->getChar().getVTyp())); break ;
     case ephs  : sfout += itos(W.Resistenz()+W.bo_Phs(hauptfenster->getChar().getVTyp())); break ; 
     case ephk  : sfout += itos(W.Resistenz()+W.bo_Phk(hauptfenster->getChar().getVTyp())); break ;
     case egift : sfout += itos(W.Gift()); break ;
     case eabwehr:sfout += itos(W.Abwehr_wert()); break ;
     case eabwehrfinal:
     case eabwehrmitwaffe:
      { if(was==eabwehrfinal)    sfout += itos(W.Abwehr_wert()+W.bo_Ab());
        if(was==eabwehrmitwaffe) sfout += Waffe::get_Verteidigungswaffe(W.Abwehr_wert()+W.bo_Ab(),hauptfenster->getChar().List_Waffen(),hauptfenster->getChar().List_Waffen_besitz(),hauptfenster->getChar().getVTyp(),W);
        sfout += W.Ruestung_Abwehr_Verlust(hauptfenster->getChar().List_Fertigkeit());
        break;
      }
     case eppresistenz:sfout += EmptyInt_4TeX(hauptfenster->getWerte().ResistenzPP()); break ;
     case eppabwehr:sfout += EmptyInt_4TeX(hauptfenster->getWerte().AbwehrPP()); break ;
     case eppzauber:sfout += EmptyInt_4TeX(hauptfenster->getWerte().ZaubernPP()); break ;
     case ezauber:sfout += EmptyInt_4TeX(W.Zaubern_wert()); break ;
     case ehand:sfout += W.Hand(); break ;
     case eraufen:sfout += itos(W.Raufen()); break ;
     case ealter:sfout += itos(W.Alter()); break ;
     case egewicht:sfout += itos(W.Gewicht())+ "\\,kg"; break ;
     case egestalt:sfout += LaTeX_scale(W.Gestalt(),5,"0.7cm"); break ;
     case ekoerpergroesse:sfout += LaTeX_scale(dtos(W.Groesse()/100.)+ "\\,m " + W.GroesseBez(),7,"0.8cm"); break ;
     case egrad:sfout += itos(W.Grad()); break ;
     case espezialisierung:sfout += LaTeX_scale(W.Spezialisierung(),10,"2.2cm") ; break ;
     case estand:sfout += LaTeX_scale(W.Stand(),10,"1.5cm"); break ;
     case eherkunft:sfout += LaTeX_scale(W.Herkunft()->Name(),10,"2.2cm"); break ;
     case eglaube:sfout += LaTeX_scale(W.Glaube(),10,"2.5cm"); break ;
     case enamecharakter:sfout += LaTeX_scale(W.Name_Abenteurer(),25,"4.5cm"); break ;
     case enamespieler : sfout += LaTeX_scale(W.Name_Spieler(),25,"4.5cm"); break ;
     case egfp : sfout += EmptyInt_4TeX(W.GFP()); break ;
     case eaep : sfout += EmptyInt_4TeX(W.AEP()); break ;
     case ekep : sfout += EmptyInt_4TeX(W.KEP()); break ;
     case ezep : sfout += EmptyInt_4TeX(W.ZEP()); break ;
     case egeld : sfout += "\\tiny " + dtos(W.Gold()+W.Silber()/10.+W.Kupfer()/100.); break ;
     case eruestung : sfout += W.Ruestung()->Name(); break ;
     case eruestunglp : sfout += itos(W.Ruestung()->LP_Verlust()); break ;
     case eruestungb : sfout += W.Ruestung(1)->Name(); break ;
     case eruestunglpb : sfout += itos(W.Ruestung(1)->LP_Verlust()); break ;
     case esinnse : sfout += itos(W.Sehen()     ); break ;
     case esinnh  : sfout += itos(W.Hoeren()    ); break ;
     case esinnr  : sfout += itos(W.Riechen()   ); break ;
     case esinnsc : sfout += itos(W.Schmecken() ); break ;
     case esinnt  : sfout += itos(W.Tasten()    ); break ;
     case esinnss : sfout += itos(W.SechsterSinn()); break ;
     default : sfout += "XXX"; break;
    }
   }
  if(sfout.find("XXX")==std::string::npos)
     fout << sfout<< "}\n";
 }
}


void LaTeX_drucken::write_sprachen(ostream &fout,const std::vector<st_sprachen_schrift>& L)
{
  unsigned int sprachanz=0;
  for(std::vector<st_sprachen_schrift>::const_iterator i=L.begin();i!=L.end();++i)
   {
      std::string a = LaTeX_string(sprachanz++);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << LaTeX_scale(i->sprache->Name(),20,"2.6cm") <<"}\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize +"<< i->sprache.Erfolgswert() <<"}\n";
      std::string ss;
      for(vector<pair<std::string,int> >::const_iterator j=i->vs.begin();j!=i->vs.end();)
       {
         ss+= j->first + "(+"+itos(j->second)+")";
         if(++j!=i->vs.end())  ss+=", ";
       }
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize "<< LaTeX_scale(ss,20,"2.6cm") <<"}\n";
   }
 for (unsigned int i=sprachanz; i<maxsprach;++i) // Bis zum Ende auffüllen
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schrw"<<a<<"}{\\scriptsize }\n";
   }
}

void LaTeX_drucken::write_fertigkeiten(ostream &fout,const std::list<MidgardBasicElement_mutable>& L)
{
  unsigned int count=0;
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L.begin();i!=L.end();++i)
   {
     std::string a = LaTeX_string(count++);
     fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "
         <<LaTeX_scale((*i)->Name()+" "+i->Zusatz(),33,"4cm") << "}   ";
     fout << "\\newcommand{\\praxis"<<a<<"}{"  << itos0((*i).Praxispunkte()) << "}   ";
     std::string wert;
     if((*i)->What()==MidgardBasicElement::FERTIGKEIT)
       wert=itos0(cH_Fertigkeit(*i)->FErfolgswert(hauptfenster->getChar().getAbenteurer(),*i));
     else if((*i)->What()==MidgardBasicElement::FERTIGKEIT_ANG)
       wert=itos0(cH_Fertigkeit_angeborene(*i)->FErfolgswert(hauptfenster->getChar().getAbenteurer(),*i));
     else if((*i)->What()==MidgardBasicElement::WAFFE)
       wert=itos0(i->Erfolgswert());
     fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert<< "}\n";
   }
 for (unsigned int i=count; i<maxfert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\praxis"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";
   }
}

void LaTeX_drucken::write_waffenbesitz(ostream &fout,const std::list<WaffeBesitz>& L)
{
  std::string angriffsverlust = hauptfenster->getWerte().Ruestung_Angriff_Verlust(hauptfenster->getChar().List_Fertigkeit());
  unsigned int count=0;
  for(std::list<WaffeBesitz>::const_iterator i=L.begin();i!=L.end();++i)
   {
     std::string b = LaTeX_string(count++);
     std::string waffenname = i->AliasName();
     fout << "\\newcommand{\\waffe"<<b<<"}{ " ;
     if (i->Magisch()!="" || i->av_Bonus()!=0 || i->sl_Bonus()!=0) 
         waffenname+="$^*$ "+i->Bonus() ;
     fout <<LaTeX_scalemag(waffenname,20,"3cm",i->Magisch(),i->Waffe()->Reichweite())<< "}\n";
     if (i->Waffe()->Verteidigung()) // Erfolgswert für einen Verteidigungswaffen
      {
        int wert = i->Erfolgswert()+i->av_Bonus()+i->Waffe()->WM_Angriff((*i)->Name());
        fout << "\\newcommand{\\waffeE"<<b<<"}{"<<itos(wert)<<"}\n";
      }
     else  // Erfolgswert für Angriffswaffen
      {
        int wert = i->Erfolgswert()+hauptfenster->getWerte().bo_An()+i->av_Bonus()+i->Waffe()->WM_Angriff(waffenname);
        // Angriffsbonus subtrahieren, wenn schwere Rüstung getragen wird:
        fout << "\\newcommand{\\waffeE"<<b<<"}{"<<wert<<angriffsverlust<<"}\n";
      }
     std::string schaden=i->Schaden(hauptfenster->getWerte(),waffenname,true);
     fout << "\\newcommand{\\waffeS"<<b<<"}{"<<schaden << "}\n";
     std::string anm = i->Waffe()->Waffenrang();
     fout << "\\newcommand{\\waffeA"<<b<<"}{"<<anm << "}\n";
     std::string abm = i->Waffe()->WM_Abwehr();
     fout << "\\newcommand{\\waffeV"<<b<<"}{"<<abm << "}\n";
   }
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


void LaTeX_drucken::write_universelle(ostream &fout)
{
 std::list<Abenteurer::st_universell> UF=hauptfenster->getChar().List_Universell(hauptfenster->getCDatabase());
 int countunifert=0;
 for(std::list<Abenteurer::st_universell>::iterator i=UF.begin();i!=UF.end();++i)
  {
    std::string a = LaTeX_string(countunifert);
    std::string name = i->mbe->Name();
    std::string wert;
    int iwert= i->mbe.Erfolgswert();
    if   (iwert>=0) wert = "+"+itos(iwert);
    else            wert = "--"+itos(abs(iwert));
    
    if     (name=="Geheimmechanismen öffnen") name = "Geheimmech. öffnen";
    else if(name=="Landeskunde (Heimat)") name = "Landeskunde ("+hauptfenster->getWerte().Herkunft()->Name()+")";

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
  if (magisch==""||magisch=="*") l2 = reichweite ;
  else  { if (magisch.size()<=25) l2 = "\\tiny "+magisch;
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
   //Never get here
   return("0");
}

void LaTeX_drucken::LaTeX_newsavebox(ostream &fout)
{
 fout << "\\newcommand{\\installpath}{"<<get_latex_pathname(TeX_Install)<< "}\n";
 fout << "\\usepackage{german}\n";
 fout << "\\usepackage[latin1]{inputenc}\n";
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
}


void LaTeX_drucken::LaTeX_kopfzeile(ostream &fout,bool landscape,bool newdoc)
{
 if(newdoc)
  {
    if(landscape)
     {
       fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(hauptfenster->getWerte().Name_Abenteurer(),25,"4.5cm") << "}\n";
       fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(hauptfenster->getWerte().Name_Spieler(),25,"4.5cm") << "}\n";
     }
    else
     {
       fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(hauptfenster->getWerte().Name_Abenteurer(),20,"4.cm") << "}\n";
       fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(hauptfenster->getWerte().Name_Spieler(),20,"4.cm") << "}\n";
     }
  }
 std::string     drache="9.9cm", namensbox="7cm";
 if(!landscape) {drache="7cm" , namensbox="5cm";}
 fout << "\\IfFileExists{drache.png}{\\parbox{"+drache+"}{\\includegraphics[width="+drache+"]{drache.png}}}\n";
 fout << "{\\parbox{"+drache+"}{\\includegraphics[width="+drache+"]{"PACKAGE_DATA_DIR"drache.png}}}\n";
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
 fout <<"\\IfFileExists{drache.png}{\\parbox{"+drache+"}{\\reflectbox{\\includegraphics[width="+drache+"]{drache.png}}}}\n";
 fout <<"{\\parbox{"+drache+"}{\\reflectbox{\\includegraphics[width="+drache+"]{"PACKAGE_DATA_DIR"drache.png}}}}\n";
 fout <<"\\vspace*{2ex}\n\n";
}

void LaTeX_drucken::LaTeX_header(ostream &fout,bool landscape,bool kopfzeile)
{
 if(landscape) fout << "\\documentclass[a4paper,10pt,landscape]{article}\n" ;
 else   fout << "\\documentclass[a4paper,10pt]{article}\n";

 fout << "\\usepackage{german}\n\\usepackage[latin2]{inputenc}\n";
 fout << "\\usepackage[pdftex]{graphicx}\n";
 fout << "\\usepackage{tabularx}\n";
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
   fout << "\\setlength{\\textheight}{26.0cm}\n";
   fout << "\\setlength{\\textwidth}{19.5cm}   \n";
   fout << "\\setlength{\\arraycolsep}{0.1cm} \n";
   fout << "\\setlength{\\evensidemargin}{-1.5cm}\n";
   fout << "\\setlength{\\oddsidemargin}{-1.5cm} \n";
   fout << "\\setlength{\\topmargin}{-0.4cm}    \n";
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
 fout << "\\begin{document}\n";
 fout << "\\begin{center}\n";
 if(kopfzeile)
    LaTeX_kopfzeile(fout,landscape);
}
 
void LaTeX_drucken::LaTeX_footer(ostream &fout)
{
  fout << "\\end{center}\n";
  fout << "\\end{document}\n\n";
}
 
void LaTeX_drucken::pdf_viewer(const std::string& file)
{
  char currentwd[10240];
  *currentwd=0;
  getcwd(currentwd,sizeof currentwd);
  
#ifdef __MINGW32__
  const char * const subpath="\\texmf\\miktex\\bin";
  static std::string newpath;
  const char *e=getenv("PATH");
  if (!e) e="";
  if (!strstr(e,subpath))
  {  newpath="PATH="+hauptfenster->BinaryVerzeichnis()
  	+subpath+std::string(1,WinLux::psep)+ e;
     putenv((char*)(newpath.c_str()));
  }
  // GetTempPath ?
#define unlink(a) _unlink(a)

#endif

  std::string file2=file;
  // LaTeX always writes to current dir first, so we change dir

  if (file.rfind(WinLux::dirsep)!=std::string::npos)
  {  chdir((file.substr(0,file.rfind(WinLux::dirsep))).c_str());
     file2=file.substr(file.rfind(WinLux::dirsep)+1);
  }

// oder batchmode?
  system(("pdflatex --interaction scrollmode "+file2+".tex").c_str());
  system((hauptfenster->getOptionen()->Viewer()+" \""+file2+".pdf\" "
#ifndef __MINGW32__  
						  		"&"
#endif  		
  								).c_str());

//  unlink((file+".tex").c_str());
  unlink((file2+".aux").c_str());
  unlink((file2+".log").c_str());
//  unlink((pfile+".pdf").c_str());
  chdir(currentwd);
}

///////////////////////////////////////////////////////////////

void LaTeX_drucken::LaTeX_zauber(ostream &fout)
{
  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Zauber().begin();i!=hauptfenster->getChar().List_Zauber().end();++i)
   {
     cH_Zauber z(*i);
     fout << z->Name() ;
     if(!(*i).Zusatz().empty()) fout << " ("<<(*i).Zusatz()<<")";
     fout <<" & ";
     fout << z->Erfolgswert_Z(hauptfenster->getChar().getVTyp(),hauptfenster->getWerte()) <<" & ";
     fout << Gtk2TeX::string2TeX(z->Ap()) << " & ";
     fout << Gtk2TeX::string2TeX(z->Art())<< " & ";
     fout << Gtk2TeX::string2TeX(z->Stufe()) << " & ";
     fout << Gtk2TeX::string2TeX(z->Zauberdauer()) << " & ";
     fout << Gtk2TeX::string2TeX(z->Reichweite()) << " & ";
     fout << Gtk2TeX::string2TeX(z->Wirkungsziel()) << " & ";
     fout << Gtk2TeX::string2TeX(z->Wirkungsbereich()) << " & ";
     fout << Gtk2TeX::string2TeX(z->Wirkungsdauer()) << " & ";
     fout << Gtk2TeX::string2TeX(z->Ursprung()) << " & " ;
     fout << LaTeX_scale(Gtk2TeX::string2TeX(z->Material()),20,"3cm") << " & " ;
     fout << z->Agens(hauptfenster->getChar().getVTyp()) <<" " <<z->Prozess() <<" "<<z->Reagens() ;
     fout << "\\\\\n";
   }
}

void LaTeX_drucken::LaTeX_zaubermittel(ostream &fout)
{
  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Zauberwerk().begin();i!=hauptfenster->getChar().List_Zauberwerk().end();++i)
   {
     cH_Zauberwerk z(*i);
//     std::string wert ;//= itos((*i)->Wert());
//     fout << wert <<" & ";
     fout << z->Name()  <<" & ";
     fout << z->Art()   <<" & ";
     fout << z->Stufe()   <<" & ";
     fout << z->Zeitaufwand()  <<" & ";
     fout << z->Preis()   <<" \\\\\n ";
   }
}


void LaTeX_drucken::LaTeX_zauber_main(ostream &fout)
{
  fout << "\\begin{center}\n";
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

 
  if (hauptfenster->getChar().List_Zauberwerk().size()!=0)
   {
     fout << "\\begin{tabular}{lllll}\\hline\n";
     fout << "Name&Art&Stufe&\\scriptsize Zeitaufwand&Kosten\\\\\\hline\n";
     LaTeX_zaubermittel(fout);
     fout << "\\end{tabular}\n";
   }
  fout << "\\end{center}\n";
}


/////////////////////////////////////////////////////////////////

void LaTeX_drucken::LaTeX_kido(ostream &fout)
{
  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Kido().begin();i!=hauptfenster->getChar().List_Kido().end();++i)
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


void LaTeX_drucken::LaTeX_kido_main(ostream &fout)
{
  fout << "\\end{center}\n";
  LaTeX_kopfzeile(fout,true,false);
  fout << "\\begin{tabular}{rllcp{17cm}}\n";
  fout << "\\multicolumn{5}{l}{\\large\\bf Erfolgswert KiDo: "
         <<KiDo::get_erfolgswert_kido(hauptfenster->getChar().List_Fertigkeit())+hauptfenster->getWerte().bo_Za()<<"}\\\\\\hline\n";
  fout << " AP & HoHo & Technik & Stufe & Effekt \\\\\\hline \n";

  LaTeX_kido(fout);
  fout << "\\end{tabular}\n";
  fout << "\\end{center}\n";
}
