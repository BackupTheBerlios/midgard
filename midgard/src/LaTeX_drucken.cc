// $Id: LaTeX_drucken.cc,v 1.39 2002/07/03 08:11:19 thoma Exp $
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
#ifdef __MINGW32__ // recode path name for TeX with slashes
         for (std::string::iterator i=result.begin();i!=result.end();++i)
            if (*i=='\\') *i='/';
#endif
         return result;
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
 std::string styp;
 if(hauptfenster->getWerte().Bezeichnung().size())
  {  styp=hauptfenster->getWerte().Bezeichnung()+" ("+hauptfenster->getChar().Typ1()->Short();
     if(hauptfenster->getChar().Typ2()->Short().size()) styp +="/"+hauptfenster->getChar().Typ2()->Short();
     styp+=")";
  }
 else 
  { styp = hauptfenster->getChar().Typ1()->Name(hauptfenster->getWerte().Geschlecht());
    if (hauptfenster->getChar().Typ2()->Name(hauptfenster->getWerte().Geschlecht())!="") 
      styp += "/"+hauptfenster->getChar().Typ2()->Name(hauptfenster->getWerte().Geschlecht());
  }
 fout << "\\newcommand{\\typ}{"<< LaTeX_scale(styp,10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\st}{"  <<hauptfenster->getWerte().St() << "}\n";
 fout << "\\newcommand{\\gs}{" <<hauptfenster->getWerte().Gs() << "}\n";
 fout << "\\newcommand{\\gw}{"  << hauptfenster->getWerte().Gw()<<hauptfenster->getWerte().Ruestung_RW_Verlust()<<"}\n";
 fout << "\\newcommand{\\ko}{"  <<hauptfenster->getWerte().Ko()<< "}\n";
 fout << "\\newcommand{\\inn}{" <<hauptfenster->getWerte().In() << "}\n";
 fout << "\\newcommand{\\zt}{"  <<hauptfenster->getWerte().Zt() << "}\n";
 fout << "\\newcommand{\\au}{"  <<hauptfenster->getWerte().Au() << "}\n";
 fout << "\\newcommand{\\pa}{"  <<hauptfenster->getWerte().pA() << "}\n";
 fout << "\\newcommand{\\sbb}{"  <<hauptfenster->getWerte().Sb() << "}\n";
 fout << "\\newcommand{\\wk}{"  <<hauptfenster->getWerte().Wk() << "}\n";
 fout << "\\newcommand{\\rw}{ X }\n";
 fout << "\\newcommand{\\hgw}{ X }\n";
 fout << "\\newcommand{\\bb}{"  <<hauptfenster->getWerte().B()<<hauptfenster->getWerte().Ruestung_B_Verlust()<<"}\n";
// fout << "\n";
 fout << "\\newcommand{\\kaw}{"  <<hauptfenster->getWerte().KAW() << "}\n";
 fout << "\\newcommand{\\geistesblitz}{"  <<hauptfenster->getWerte().Geistesblitz() << "}\n";
 fout << "\\newcommand{\\ggn}{"  <<hauptfenster->getWerte().GG() << "}\n";
 fout << "\\newcommand{\\sg}{"  <<hauptfenster->getWerte().SG() << "}\n";
 fout << "\\newcommand{\\lp}{"  <<hauptfenster->getWerte().LP() << "}\n";
 fout << "\\newcommand{\\ap}{"  <<hauptfenster->getWerte().AP() << "}\n";
 fout << "\\newcommand{\\boau}{"<<hauptfenster->getWerte().bo_Au()<< "}\n";
 fout << "\\newcommand{\\bosc}{"<<hauptfenster->getWerte().bo_Sc()<< "}\n";
 fout << "\\newcommand{\\boan}{"<<hauptfenster->getWerte().bo_An()<< "}\n";
 fout << "\\newcommand{\\boab}{"<<hauptfenster->getWerte().bo_Ab()<< "}\n";
 fout << "\\newcommand{\\boza}{"<<hauptfenster->getWerte().bo_Za()<< "}\n";
 fout << "\\newcommand{\\bopsy}{"<<hauptfenster->getWerte().bo_Psy(hauptfenster->getChar().getVTyp())<< "}\n";
 fout << "\\newcommand{\\bophs}{"<<hauptfenster->getWerte().bo_Phs(hauptfenster->getChar().getVTyp())<< "}\n";
 fout << "\\newcommand{\\bophk}{"<<hauptfenster->getWerte().bo_Phk(hauptfenster->getChar().getVTyp())<< "}\n";

 // Sinne
 fout << "\\newcommand{\\sinnse}{"<<hauptfenster->getWerte().Sehen()<< "}\n";
 fout << "\\newcommand{\\sinnh}{"<<hauptfenster->getWerte().Hoeren()<< "}\n";
 fout << "\\newcommand{\\sinnr}{"<<hauptfenster->getWerte().Riechen()<< "}\n";
 fout << "\\newcommand{\\sinnsc}{"<<hauptfenster->getWerte().Schmecken()<< "}\n";
 fout << "\\newcommand{\\sinnt}{"<<hauptfenster->getWerte().Tasten()<< "}\n";
 fout << "\\newcommand{\\sinnss}{"<<hauptfenster->getWerte().SechsterSinn()<< "}\n";
 
 fout << "\\newcommand{\\hand}{"<<hauptfenster->getWerte().Hand()<< "}\n";

// fout << "\\newcommand{\\bogi}{ X }\n";
 fout << "\\newcommand{\\res}{"<<hauptfenster->getWerte().Resistenz()<<"}\n";
 fout << "\\newcommand{\\psy}{"<<hauptfenster->getWerte().Resistenz()+hauptfenster->getWerte().bo_Psy(hauptfenster->getChar().getVTyp())<<"}\n";
 fout << "\\newcommand{\\ppresistenz}{"<<EmptyInt_4TeX(hauptfenster->getWerte().ResistenzPP())<<"}\n";
 fout << "\\newcommand{\\phs}{"<<hauptfenster->getWerte().Resistenz()+hauptfenster->getWerte().bo_Phs(hauptfenster->getChar().getVTyp())<<"}\n";
 fout << "\\newcommand{\\phk}{"<<hauptfenster->getWerte().Resistenz()+hauptfenster->getWerte().bo_Phk(hauptfenster->getChar().getVTyp())<<"}\n";
// fout << "\\newcommand{\\gift}{"<<3*hauptfenster->getWerte().LP()+hauptfenster->getWerte().bo_Gift()+ Spezies_constraint.Gift()<<"}\n";
 fout << "\\newcommand{\\gift}{"<<hauptfenster->getWerte().Gift()<<"}\n";

 fout << "\\newcommand{\\raufen}{"<<hauptfenster->getWerte().Raufen()<< "}\n";
 fout << "\\newcommand{\\abwehr}{"<<hauptfenster->getWerte().Abwehr_wert()<< "}\n";
 fout << "\\newcommand{\\ppabwehr}{"<<EmptyInt_4TeX(hauptfenster->getWerte().AbwehrPP())<< "}\n";
 int ohne_waffe=hauptfenster->getWerte().Abwehr_wert()+hauptfenster->getWerte().bo_Ab();
 std::string abwehr_verlust_string = hauptfenster->getWerte().Ruestung_Abwehr_Verlust(hauptfenster->getChar().List_Fertigkeit());
 fout << "\\newcommand{\\abwehrfinal}{"<<ohne_waffe<<abwehr_verlust_string<<"}\n";

 std::string mit_waffe = Waffe::get_Verteidigungswaffe(ohne_waffe,hauptfenster->getChar().List_Waffen(),hauptfenster->getChar().List_Waffen_besitz(),hauptfenster->getChar().getVTyp(),hauptfenster->getWerte());
 fout << "\\newcommand{\\abwehrmitwaffe}{"<<mit_waffe<<abwehr_verlust_string<<"}\n";

 fout << "\\newcommand{\\zauber}{"<<EmptyInt_4TeX(hauptfenster->getWerte().Zaubern_wert())<< "}\n";
 fout << "\\newcommand{\\ppzauber}{"<<EmptyInt_4TeX(hauptfenster->getWerte().ZaubernPP())<< "}\n";
 fout << "\\newcommand{\\alter}{"  <<hauptfenster->getWerte().Alter() << "}\n";
 fout << "\\newcommand{\\gestalt}{"  <<LaTeX_scale(hauptfenster->getWerte().Gestalt(),5,"0.7cm") << "}\n";
 fout << "\\newcommand{\\gewicht}{"  <<hauptfenster->getWerte().Gewicht() << "\\,kg}\n";
 fout << "\\newcommand{\\koerpergroesse}{"  <<hauptfenster->getWerte().Groesse()/100. << "\\,m}\n";
 fout << "\\newcommand{\\koerpergroessebez}{"  <<hauptfenster->getWerte().GroesseBez() << "}\n";
 fout << "\\newcommand{\\grad}{"  <<hauptfenster->getWerte().Grad() << "}\n";
 fout << "\\newcommand{\\spezialisierung}{ "  <<LaTeX_scale(hauptfenster->getWerte().Spezialisierung(),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\stand}{"  <<LaTeX_scale(hauptfenster->getWerte().Stand(),10,"1.5cm") << "}\n";
 fout << "\\newcommand{\\herkunft}{"  <<LaTeX_scale(hauptfenster->getWerte().Herkunft()->Name(),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\glaube}{"  <<LaTeX_scale(hauptfenster->getWerte().Glaube(),10,"2.5cm") << "}\n";
 fout << "\\newcommand{\\namecharakter}{" << LaTeX_scale(hauptfenster->getWerte().Name_Abenteurer(),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\namespieler}{" << LaTeX_scale(hauptfenster->getWerte().Name_Spieler(),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\gfp}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getWerte().GFP()) << "}\n";
 fout << "\\newcommand{\\aep}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getWerte().KEP()) << "}\n";
 fout << "\\newcommand{\\kep}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getWerte().ZEP()) << "}\n";
 fout << "\\newcommand{\\zep}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getWerte().AEP()) << "}\n";

 double geld = hauptfenster->getWerte().Gold() + hauptfenster->getWerte().Silber()/10. + hauptfenster->getWerte().Kupfer()/100.;
 fout << "\\newcommand{\\gold}{\\tiny "  << geld << "}\n";

 fout << "\\newcommand{\\ruestung}{\\scriptsize "  <<hauptfenster->getWerte().Ruestung()->Name() << "}\n";
 fout << "\\newcommand{\\ruestunglp}{\\scriptsize "  <<hauptfenster->getWerte().Ruestung()->LP_Verlust() << "}\n";
 fout << "\\newcommand{\\ruestungb}{\\scriptsize "  <<hauptfenster->getWerte().Ruestung(1)->Name() << "}\n";
 fout << "\\newcommand{\\ruestunglpb}{\\scriptsize "  <<hauptfenster->getWerte().Ruestung(1)->LP_Verlust() << "}\n";

 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 unsigned int sprachanz=0;
 unsigned int maxsprach=23;
 std::list<MidgardBasicElement_mutable> verwandteSprachen;
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Sprache().begin();i!=hauptfenster->getChar().List_Sprache().end();++i)
   {  cH_Sprache s(*i);
      std::list<MidgardBasicElement_mutable> tmplist=s->VerwandteSprachen((*i).Erfolgswert(),hauptfenster->getChar().List_Sprache(),hauptfenster->getCDatabase().Sprache);
      verwandteSprachen.splice(verwandteSprachen.end(),tmplist);
//geht nicht!!!      verwandteSprachen.splice(verwandteSprachen.end(),s->VerwandteSprachen(hauptfenster->getChar().List_Sprache,hauptfenster->Database()().Sprache));
      std::string a = LaTeX_string(sprachanz++);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << LaTeX_scale(s->Name(),20,"2.6cm") <<"}\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize +"<< (*i).Erfolgswert() <<"}\n";
      vector<pair<std::string,int> > vs=s->SchriftWert(hauptfenster->getChar().List_Schrift());
      std::string ss;
      for(vector<pair<std::string,int> >::const_iterator j=vs.begin();j!=vs.end();)
       {
         ss+= j->first + "(+"+itos(j->second)+")";
         if(++j!=vs.end())  ss+=", ";
       }
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize "<< LaTeX_scale(ss,20,"2.6cm") <<"}\n";
   }
 verwandteSprachen=Sprache::cleanVerwandteSprachen(verwandteSprachen);
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=verwandteSprachen.begin();i!=verwandteSprachen.end();++i)
   { cH_Sprache s(*i);
     if(i->ist_gelernt(hauptfenster->getChar().List_Sprache())) continue;
     std::string a = LaTeX_string(sprachanz++);
     fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << LaTeX_scale(s->Name(),20,"2.6cm") <<"}\n";
     fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize (+"<< (*i).Erfolgswert() <<")}\n";
     fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize "<< LaTeX_scale("",20,"2.6cm") <<"}\n";
   }
 for (unsigned int i=sprachanz; i<maxsprach;++i) // Bis zum Ende auffüllen
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schrw"<<a<<"}{\\scriptsize }\n";
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
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Beruf().begin();
         i!=hauptfenster->getChar().List_Beruf().end();++i)
   {
     fout << (*i)->Name(); //<<" ("<<(*i).Erfolgswert()<<")\t";
   }
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // weitere Merkmale
 fout << "\\newcommand{\\merkmale}{" ;
 if(hauptfenster->getWerte().Spezies()->Name()!="Mensch")  fout << hauptfenster->getWerte().Spezies()->Name()<<" "; 
 fout << hauptfenster->getWerte().Merkmale();
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten & Waffen
 /////////////////////////////////////////////////////////////////////////////
 // angeborene Fertigkeiten
 int count=0;
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Fertigkeit_ang().begin();i!=hauptfenster->getChar().List_Fertigkeit_ang().end();++i) 
   {cH_Fertigkeit_angeborene f(*i);
    std::string a = LaTeX_string(count);
    count++;
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<f->Name() << "}   ";
    // Praxispunkte
    std::string pp = itos((*i).Praxispunkte());
    if (pp == "0") pp = "";
    fout << "\\newcommand{\\praxis"<<a<<"}{"  << pp << "}   ";
    // Erfolgswert
    std::string wert = itos(f->FErfolgswert(hauptfenster->getChar().getAbenteurer(),*i));
    if (wert == "0") wert = "";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Fertigkeit().begin();i!=hauptfenster->getChar().List_Fertigkeit().end();++i) 
   {cH_Fertigkeit f(*i);
    std::string a = LaTeX_string(count);
    count++;
    std::string wert = itos((*i).Erfolgswert());
    if (wert == "0") wert = "";
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  
      <<LaTeX_scale(f->Name()+" "+i->Zusatz(),33,"4cm") << "}\t\t";
    // Praxispunkte
    std::string pp = itos((*i).Praxispunkte());
    if (pp == "0") pp = "";
    fout << "\\newcommand{\\praxis"<<a<<"}{"  << pp << "}   ";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 std::string a = LaTeX_string(count);
 fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
 fout << "\\newcommand{\\praxis"<<a<<"}{\\scriptsize }\n";
 fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";

 /////////////////////////////////////////////////////////////////////////////
 // Waffen + Waffen/Besitz
 unsigned int countwaffen=0;
 std::string angriffsverlust_string = hauptfenster->getWerte().Ruestung_Angriff_Verlust(hauptfenster->getChar().List_Fertigkeit());
 std::list<WaffeBesitz> WBesitz=hauptfenster->getChar().List_Waffen_besitz();
 for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getChar().List_Waffen().begin();i!=hauptfenster->getChar().List_Waffen().end();++i)
   {cH_Waffe w(*i);
    count++;
    std::string a = LaTeX_string(count);
//std::cout << "latexstring = "<<a<<"\n";
    std::string wert = itos((*i).Erfolgswert());
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<w->Name() << "}\t\t";
    // Praxispunkte
    std::string pp = itos((*i).Praxispunkte());
    if (pp == "0") pp = "";
    fout << "\\newcommand{\\praxis"<<a<<"}{"  << pp << "}   ";
    fout <<"\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
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
      if (WB.Waffe()->Name()==w->Name())
       {
         std::string b = LaTeX_string(countwaffen++);
//std::cout << (*j)->Name()<<"\t"<<w->Name()<<"\t"<<"latexstring = "<<b<<"\n";
         std::string waffenname ;
         waffenname = WB.AliasName();
         fout << "\\newcommand{\\waffe"<<b<<"}{ " ;
         if (WB.Magisch()!="" || 
             WB.av_Bonus()!=0 || WB.sl_Bonus()!=0) waffenname+="$^*$ "+WB.Bonus() ;
         fout <<LaTeX_scalemag(waffenname,20,"3cm",WB.Magisch(),WB.Waffe()->Reichweite())<< "}\n";
         
         // Erfolgswert für einen Verteidigungswaffen
         if (WB.Waffe()->Verteidigung())
          {
           int wert = (*i).Erfolgswert() + WB.av_Bonus() + WB.Waffe()->WM_Angriff(WB->Name()) ;
           fout << "\\newcommand{\\waffeE"<<b<<"}{"<<itos(wert)<<"}\n";
          }
         // Erfolgswert für Angriffswaffen
         else 
          {
//           int wert = (*i).Erfolgswert() + hauptfenster->getWerte().bo_An() + WB.av_Bonus() + WB.Waffe()->WM_Angriff(WB->Name()) ;
           int wert = (*i).Erfolgswert() + hauptfenster->getWerte().bo_An() + WB.av_Bonus() + WB.Waffe()->WM_Angriff(waffenname) ;
           // Angriffsbonus subtrahieren, wenn schwere Rüstung getragen wird:
           fout << "\\newcommand{\\waffeE"<<b<<"}{"<<wert<<angriffsverlust_string<<"}\n";
          }
         std::string schaden=WB.Schaden(hauptfenster->getWerte(),waffenname,true);
         fout << "\\newcommand{\\waffeS"<<b<<"}{"<<schaden << "}\n";
         std::string anm = WB.Waffe()->Waffenrang();
         fout << "\\newcommand{\\waffeA"<<b<<"}{"<<anm << "}\n";
         std::string abm = WB.Waffe()->WM_Abwehr();
         fout << "\\newcommand{\\waffeV"<<b<<"}{"<<abm << "}\n";
       }
     }
   }
 /////////////////////////////////////////////////////////////////////////
 // Universelle Fertigkeiten

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

 // Fertigkeiten auffüllen
 unsigned int maxfert=40;
 for (unsigned int i=count+1; i<maxfert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\praxis"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";
   }
 // Waffen auffüllen
 unsigned int maxwaffen=9;
 for (unsigned int i=countwaffen; i<maxwaffen;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\waffe"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeE"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeS"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeA"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeV"<<a<<"}{\\scriptsize }\n";
   }
 // Universelle Fertigkeiten auffüllen
 unsigned int maxunifert=48;
 for (unsigned int i=countunifert; i<maxunifert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\uni"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\uniw"<<a<<"}{\\scriptsize }\n";
   }
#ifdef __MINGW32__ // LaTeX needs / instead of '\\'
 std::string recoded_install_latex_file=install_latex_file;
 for (std::string::iterator i=recoded_install_latex_file.begin();i!=recoded_install_latex_file.end();++i)
            if (*i=='\\') *i='/';
 fout << "\\input{"+recoded_install_latex_file+"}\n";
#else
 fout << "\\input{"+install_latex_file+"}\n";
#endif 
// fout.close();
}


void LaTeX_drucken::LaTeX_write_empty_values(ostream &fout,const std::string &install_latex_file)
{
 fout << "\\documentclass[11pt,a4paper,landscape]{article}\n";
// fout << "\\newcommand{\\installpath}{"<<get_latex_pathname(TeX_Install)<< "}\n";
 LaTeX_newsavebox(fout);
 fout << "\\newcommand{\\typ}{}\n";
 fout << "\\newcommand{\\merkmale}{}" ;
 fout << "\\newcommand{\\hand}{""}\n";
 fout << "\\newcommand{\\st}{}\n";
 fout << "\\newcommand{\\gw}{}\n";
 fout << "\\newcommand{\\gs}{}\n";
 fout << "\\newcommand{\\ko}{}\n";
 fout << "\\newcommand{\\inn}{}\n";
 fout << "\\newcommand{\\zt}{}\n";
 fout << "\\newcommand{\\au}{}\n";
 fout << "\\newcommand{\\pa}{}\n";
 fout << "\\newcommand{\\sbb}{}\n";
 fout << "\\newcommand{\\wk}{}\n";
 fout << "\\newcommand{\\rw}{}\n";
// fout << "\\newcommand{\\hgw}{}\n";
 fout << "\\newcommand{\\bb}{}\n";
 fout << "\\newcommand{\\geistesblitz}{}\n";
 fout << "\\newcommand{\\kaw}{}\n";
 fout << "\\newcommand{\\wlw}{}\n";
 fout << "\\newcommand{\\sg}{}\n";
 fout << "\\newcommand{\\ggn}{}\n";
 fout << "\\newcommand{\\lp}{}\n";
 fout << "\\newcommand{\\ap}{}\n";
 fout << "\\newcommand{\\boau}{}\n";
 fout << "\\newcommand{\\bosc}{}\n";
 fout << "\\newcommand{\\boan}{}\n";
 fout << "\\newcommand{\\boab}{}\n";
 fout << "\\newcommand{\\boza}{}\n";
 fout << "\\newcommand{\\bopsy}{}\n";
 fout << "\\newcommand{\\bophs}{}\n";
 fout << "\\newcommand{\\bophk}{}\n";
 fout << "\\newcommand{\\bogi}{}\n";
 fout << "\\newcommand{\\res}{}\n";
 fout << "\\newcommand{\\psy}{}\n";
 fout << "\\newcommand{\\phs}{}\n";
 fout << "\\newcommand{\\phk}{}\n";
 fout << "\\newcommand{\\gift}{}\n";

 fout << "\\newcommand{\\abwehr}{}\n";
 fout << "\\newcommand{\\abwehrfinal}{}\n";
 fout << "\\newcommand{\\abwehrmitwaffe}{}\n";

 fout << "\\newcommand{\\ppresistenz}{}\n";
 fout << "\\newcommand{\\ppabwehr}{}\n";
 fout << "\\newcommand{\\ppzauber}{}\n";

 fout << "\\newcommand{\\zauber}{}\n";
 fout << "\\newcommand{\\alter}{}\n";
 fout << "\\newcommand{\\gestalt}{}\n";
 fout << "\\newcommand{\\gewicht}{}\n";
 fout << "\\newcommand{\\koerpergroesse}{}\n";
 fout << "\\newcommand{\\koerpergroessebez}{}\n";
 fout << "\\newcommand{\\grad}{}\n";
 fout << "\\newcommand{\\spezialisierung}{}\n";
 fout << "\\newcommand{\\stand}{}\n";
 fout << "\\newcommand{\\herkunft}{}\n";
 fout << "\\newcommand{\\glaube}{}\n";
 fout << "\\newcommand{\\namecharakter}{}\n";
 fout << "\\newcommand{\\namespieler}{}\n";
 fout << "\\newcommand{\\gfp}{}\n";
 fout << "\\newcommand{\\aep}{}\n";
 fout << "\\newcommand{\\kep}{}\n";
 fout << "\\newcommand{\\zep}{}\n";

 fout << "\\newcommand{\\gold}{}\n";

 fout << "\\newcommand{\\ruestung}{}\n";
 fout << "\\newcommand{\\ruestunglp}{}\n";

 fout << "\\newcommand{\\raufen}{}\n";
 // Sinne
 // Sinne
 fout << "\\newcommand{\\sinnse}{}\n";
 fout << "\\newcommand{\\sinnh}{}\n";
 fout << "\\newcommand{\\sinnr}{}\n";
 fout << "\\newcommand{\\sinnsc}{}\n";
 fout << "\\newcommand{\\sinnt}{}\n";
 fout << "\\newcommand{\\sinnss}{}\n";
 

 unsigned int maxsprach=23;
 for (unsigned int i=0; i<maxsprach;++i) // Bis zum Ende auffüllen
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\spra"<<a<<"}{}\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{}\n";
      fout << "\\newcommand{\\schr"<<a<<"}{}\n";
   }
 fout << "\\newcommand{\\beruf}{}\n" ;
 fout << "\\newcommand{\\waffeEy"<<"}{}\n";
 fout << "\\newcommand{\\waffeSy}{}\n";
 fout << "\\newcommand{\\waffeAy}{}\n";
 fout << "\\newcommand{\\waffeVy}{}\n";
 // Fertigkeiten auffüllen
 unsigned int maxfert=40;
 for (unsigned int i=0; i<maxfert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\fert"<<a<<"}{}\n";
      fout << "\\newcommand{\\praxis"<<a<<"}{}   ";
      fout << "\\newcommand{\\wert"<<a<<"}{}\n";
   }
 // Waffen auffüllen
 unsigned int maxwaffen=8;
 for (unsigned int i=0; i<maxwaffen;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\waffe"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeE"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeS"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeA"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeV"<<a<<"}{\\scriptsize }\n";
   }
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


 unsigned int maxunifert=48;
 for (unsigned int i=countunifert; i<maxunifert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\uni"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\uniw"<<a<<"}{\\scriptsize }\n";
   }
#ifdef __MINGW32__ // LaTeX needs / instead of '\\'
 std::string recoded_install_latex_file=install_latex_file;
 for (std::string::iterator i=recoded_install_latex_file.begin();i!=recoded_install_latex_file.end();++i)
            if (*i=='\\') *i='/';
 fout << "\\input{"+recoded_install_latex_file+"}\n";
#else
 fout << "\\input{"+install_latex_file+"}\n";
#endif 
// fout.close();
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
