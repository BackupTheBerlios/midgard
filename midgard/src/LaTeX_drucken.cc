// $Id: LaTeX_drucken.cc,v 1.22 2002/06/24 10:51:30 christof Exp $
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

#ifdef __MINGW32__
std::string utf82iso(const std::string &s);
#define LATIN(x) utf82iso(x)
#else
#define LATIN(x) (x)
#endif


std::string LaTeX_drucken::get_latex_filename(const LaTeX_Filenames what)
{
  std::string name=hauptfenster->getCWerte().Name_Abenteurer();
  std::string version=hauptfenster->getCWerte().Version();
  std::string nv="_"+name+"__"+version+"_";
  
  while(true) // alle nicht von der shell interpretierbare Zeichen ersetzen
   {
    string::size_type s=nv.find_first_of(" '");
    if(s!=string::npos) nv.replace(s,1,"_");
    else break;
   }
  
  switch (what)
    {
      case TeX_MainDocument : return "midgard_document_eingabe";
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
      case TeX_tmp : return "";//MOptionen->getString(Midgard_Optionen::tmppfad);
      case TeX_Install : return ""; //PACKAGE_DATA_DIR;
    }
  abort(); // never get here
}


void LaTeX_drucken::on_latex_clicked(bool values=true)
{   
 std::string installfile=get_latex_pathname(TeX_Install)+get_latex_filename(TeX_MainDocument);
 std::string filename=get_latex_pathname(TeX_tmp)+get_latex_filename(TeX_MainWerte);
 
/*
 if (!access("document_eingabe4.tex",R_OK)) // Files im aktuellen Verzeichnis?
    system("cp document_eingabe4.tex midgard_tmp_document_eingabe.tex");
 else
    system("cp "PACKAGE_DATA_DIR"document_eingabe4.tex midgard_tmp_document_eingabe.tex");
*/

 ofstream fout((filename+".tex").c_str());
 if (values) LaTeX_write_values(fout,installfile);
 else LaTeX_write_empty_values(fout,installfile);

 if (hauptfenster->getCChar().CList_Zauber().size()>0 || hauptfenster->getCChar().CList_Zauberwerk().size()>0)  // Zauber
  {
    LaTeX_zauber_main(fout);
  }
 if (hauptfenster->getCChar().CList_Kido().size()>0) // KiDo
  {
    LaTeX_kido_main(fout);
  }
 fout << "\\end{document}\n";
 fout.close();
 pdf_viewer(filename);
}      

void LaTeX_drucken::LaTeX_write_values(ostream &fout,const std::string &install_latex_file)
{
 fout << "\\documentclass[11pt,a4paper,landscape]{article}\n";
 LaTeX_newsavebox(fout);
 std::string styp;
 if(hauptfenster->getCWerte().Bezeichnung().size())
  {  styp=hauptfenster->getCWerte().Bezeichnung()+" ("+hauptfenster->getCChar().CTyp1()->Short();
     if(hauptfenster->getCChar().CTyp2()->Short().size()) styp +="/"+hauptfenster->getCChar().CTyp2()->Short();
     styp+=")";
  }
 else 
  { styp = hauptfenster->getCChar().CTyp1()->Name(hauptfenster->getCWerte().Geschlecht());
    if (hauptfenster->getCChar().CTyp2()->Name(hauptfenster->getCWerte().Geschlecht())!="") 
      styp += "/"+hauptfenster->getCChar().CTyp2()->Name(hauptfenster->getCWerte().Geschlecht());
  }
 fout << "\\newcommand{\\typ}{"<< LaTeX_scale(LATIN(styp),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\st}{"  <<hauptfenster->getCWerte().St() << "}\n";
 fout << "\\newcommand{\\gs}{" <<hauptfenster->getCWerte().Gs() << "}\n";
 fout << "\\newcommand{\\gw}{"  << hauptfenster->getCWerte().Gw()<<hauptfenster->getCWerte().Ruestung_RW_Verlust()<<"}\n";
 fout << "\\newcommand{\\ko}{"  <<hauptfenster->getCWerte().Ko()<< "}\n";
 fout << "\\newcommand{\\inn}{" <<hauptfenster->getCWerte().In() << "}\n";
 fout << "\\newcommand{\\zt}{"  <<hauptfenster->getCWerte().Zt() << "}\n";
 fout << "\\newcommand{\\au}{"  <<hauptfenster->getCWerte().Au() << "}\n";
 fout << "\\newcommand{\\pa}{"  <<hauptfenster->getCWerte().pA() << "}\n";
 fout << "\\newcommand{\\sbb}{"  <<hauptfenster->getCWerte().Sb() << "}\n";
 fout << "\\newcommand{\\wk}{"  <<hauptfenster->getCWerte().Wk() << "}\n";
 fout << "\\newcommand{\\rw}{ X }\n";
 fout << "\\newcommand{\\hgw}{ X }\n";
 fout << "\\newcommand{\\bb}{"  <<hauptfenster->getCWerte().B()<<hauptfenster->getCWerte().Ruestung_B_Verlust()<<"}\n";
 fout << "}\n";
 fout << "\\newcommand{\\kaw}{"  <<hauptfenster->getCWerte().KAW() << "}\n";
 fout << "\\newcommand{\\geistesblitz}{"  <<hauptfenster->getCWerte().Geistesblitz() << "}\n";
 fout << "\\newcommand{\\ggn}{"  <<hauptfenster->getCWerte().GG() << "}\n";
 fout << "\\newcommand{\\sg}{"  <<hauptfenster->getCWerte().SG() << "}\n";
 fout << "\\newcommand{\\lp}{"  <<hauptfenster->getCWerte().LP() << "}\n";
 fout << "\\newcommand{\\ap}{"  <<hauptfenster->getCWerte().AP() << "}\n";
 fout << "\\newcommand{\\boau}{"<<hauptfenster->getCWerte().bo_Au()<< "}\n";
 fout << "\\newcommand{\\bosc}{"<<hauptfenster->getCWerte().bo_Sc()<< "}\n";
 fout << "\\newcommand{\\boan}{"<<hauptfenster->getCWerte().bo_An()<< "}\n";
 fout << "\\newcommand{\\boab}{"<<hauptfenster->getCWerte().bo_Ab()<< "}\n";
 fout << "\\newcommand{\\boza}{"<<hauptfenster->getCWerte().bo_Za()<< "}\n";
 fout << "\\newcommand{\\bopsy}{"<<hauptfenster->getCWerte().bo_Psy(hauptfenster->getCChar().getVTyp())<< "}\n";
 fout << "\\newcommand{\\bophs}{"<<hauptfenster->getCWerte().bo_Phs(hauptfenster->getCChar().getVTyp())<< "}\n";
 fout << "\\newcommand{\\bophk}{"<<hauptfenster->getCWerte().bo_Phk(hauptfenster->getCChar().getVTyp())<< "}\n";

 // Sinne
 fout << "\\newcommand{\\sinnse}{"<<hauptfenster->getCWerte().Sehen()<< "}\n";
 fout << "\\newcommand{\\sinnh}{"<<hauptfenster->getCWerte().Hoeren()<< "}\n";
 fout << "\\newcommand{\\sinnr}{"<<hauptfenster->getCWerte().Riechen()<< "}\n";
 fout << "\\newcommand{\\sinnsc}{"<<hauptfenster->getCWerte().Schmecken()<< "}\n";
 fout << "\\newcommand{\\sinnt}{"<<hauptfenster->getCWerte().Tasten()<< "}\n";
 fout << "\\newcommand{\\sinnss}{"<<hauptfenster->getCWerte().SechsterSinn()<< "}\n";
 
 fout << "\\newcommand{\\hand}{"<<LATIN(hauptfenster->getCWerte().Hand())<< "}\n";

// fout << "\\newcommand{\\bogi}{ X }\n";
 fout << "\\newcommand{\\res}{"<<hauptfenster->getCWerte().Resistenz()<<"}\n";
 fout << "\\newcommand{\\psy}{"<<hauptfenster->getCWerte().Resistenz()+hauptfenster->getCWerte().bo_Psy(hauptfenster->getCChar().getVTyp())<<"}\n";
 fout << "\\newcommand{\\ppresistenz}{"<<EmptyInt_4TeX(hauptfenster->getCWerte().ResistenzPP())<<"}\n";
 fout << "\\newcommand{\\phs}{"<<hauptfenster->getCWerte().Resistenz()+hauptfenster->getCWerte().bo_Phs(hauptfenster->getCChar().getVTyp())<<"}\n";
 fout << "\\newcommand{\\phk}{"<<hauptfenster->getCWerte().Resistenz()+hauptfenster->getCWerte().bo_Phk(hauptfenster->getCChar().getVTyp())<<"}\n";
// fout << "\\newcommand{\\gift}{"<<3*hauptfenster->getCWerte().LP()+hauptfenster->getCWerte().bo_Gift()+ Spezies_constraint.Gift()<<"}\n";
 fout << "\\newcommand{\\gift}{"<<hauptfenster->getCWerte().Gift()<<"}\n";

 fout << "\\newcommand{\\raufen}{"<<hauptfenster->getCWerte().Raufen()<< "}\n";
 fout << "\\newcommand{\\abwehr}{"<<hauptfenster->getCWerte().Abwehr_wert()<< "}\n";
 fout << "\\newcommand{\\ppabwehr}{"<<EmptyInt_4TeX(hauptfenster->getCWerte().AbwehrPP())<< "}\n";
 int ohne_waffe=hauptfenster->getCWerte().Abwehr_wert()+hauptfenster->getCWerte().bo_Ab();
 std::string abwehr_verlust_string = hauptfenster->getCWerte().Ruestung_Abwehr_Verlust(hauptfenster->getCChar().CList_Fertigkeit());
 fout << "\\newcommand{\\abwehrfinal}{"<<ohne_waffe<<abwehr_verlust_string<<"}\n";

 std::string mit_waffe = Waffe::get_Verteidigungswaffe(ohne_waffe,hauptfenster->getCChar().CList_Waffen(),hauptfenster->getCChar().CList_Waffen_besitz(),hauptfenster->getCChar().getVTyp(),hauptfenster->getCWerte());
 fout << "\\newcommand{\\abwehrmitwaffe}{"<<mit_waffe<<abwehr_verlust_string<<"}\n";

 fout << "\\newcommand{\\zauber}{"<<EmptyInt_4TeX(hauptfenster->getCWerte().Zaubern_wert())<< "}\n";
 fout << "\\newcommand{\\ppzauber}{"<<EmptyInt_4TeX(hauptfenster->getCWerte().ZaubernPP())<< "}\n";
 fout << "\\newcommand{\\alter}{"  <<hauptfenster->getCWerte().Alter() << "}\n";
 fout << "\\newcommand{\\gestalt}{"  <<LaTeX_scale(LATIN(hauptfenster->getCWerte().Gestalt()),5,"0.7cm") << "}\n";
 fout << "\\newcommand{\\gewicht}{"  <<hauptfenster->getCWerte().Gewicht() << "\\,kg}\n";
 fout << "\\newcommand{\\koerpergroesse}{"  <<hauptfenster->getCWerte().Groesse()/100. << "\\,m}\n";
 fout << "\\newcommand{\\koerpergroessebez}{"  <<LATIN(hauptfenster->getCWerte().GroesseBez()) << "}\n";
 fout << "\\newcommand{\\grad}{"  <<hauptfenster->getCWerte().Grad() << "}\n";
 fout << "\\newcommand{\\spezialisierung}{ "  <<LaTeX_scale(LATIN(hauptfenster->getCWerte().Spezialisierung()),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\stand}{"  <<LaTeX_scale(hauptfenster->getCWerte().Stand(),10,"1.5cm") << "}\n";
 fout << "\\newcommand{\\herkunft}{"  <<LaTeX_scale(LATIN(hauptfenster->getCWerte().Herkunft()->Name()),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\glaube}{"  <<LaTeX_scale(LATIN(hauptfenster->getCWerte().Glaube()),10,"2.5cm") << "}\n";
 fout << "\\newcommand{\\namecharakter}{" << LaTeX_scale(LATIN(hauptfenster->getCWerte().Name_Abenteurer()),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\namespieler}{" << LaTeX_scale(LATIN(hauptfenster->getCWerte().Name_Spieler()),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\gfp}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getCWerte().GFP()) << "}\n";
 fout << "\\newcommand{\\aep}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getCWerte().KEP()) << "}\n";
 fout << "\\newcommand{\\kep}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getCWerte().ZEP()) << "}\n";
 fout << "\\newcommand{\\zep}{\\tiny "  <<EmptyInt_4TeX(hauptfenster->getCWerte().AEP()) << "}\n";

 double geld = hauptfenster->getCWerte().Gold() + hauptfenster->getCWerte().Silber()/10. + hauptfenster->getCWerte().Kupfer()/100.;
 fout << "\\newcommand{\\gold}{\\tiny "  << geld << "}\n";

 fout << "\\newcommand{\\ruestung}{\\scriptsize "  <<LATIN(hauptfenster->getCWerte().Ruestung()->Name()) << "}\n";
 fout << "\\newcommand{\\ruestunglp}{\\scriptsize "  <<hauptfenster->getCWerte().Ruestung()->LP_Verlust() << "}\n";
 fout << "\\newcommand{\\ruestungb}{\\scriptsize "  <<LATIN(hauptfenster->getCWerte().Ruestung(1)->Name()) << "}\n";
 fout << "\\newcommand{\\ruestunglpb}{\\scriptsize "  <<hauptfenster->getCWerte().Ruestung(1)->LP_Verlust() << "}\n";

 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 unsigned int sprachanz=0;
 unsigned int maxsprach=23;
 std::list<MidgardBasicElement_mutable> verwandteSprachen;
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Sprache().begin();i!=hauptfenster->getCChar().CList_Sprache().end();++i)
   {  cH_Sprache s(*i);
      std::list<MidgardBasicElement_mutable> tmplist=s->VerwandteSprachen((*i).Erfolgswert(),hauptfenster->getCChar().CList_Sprache(),hauptfenster->getCDatabase().Sprache);
      verwandteSprachen.splice(verwandteSprachen.end(),tmplist);
//geht nicht!!!      verwandteSprachen.splice(verwandteSprachen.end(),s->VerwandteSprachen(hauptfenster->getCChar().CList_Sprache,hauptfenster->Database()().Sprache));
      std::string a = LaTeX_string(sprachanz++);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << LaTeX_scale(LATIN(s->Name()),20,"2.6cm") <<"}\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize +"<< (*i).Erfolgswert() <<"}\n";
      vector<pair<std::string,int> > vs=s->SchriftWert(hauptfenster->getCChar().CList_Schrift());
      std::string ss;
      for(vector<pair<std::string,int> >::const_iterator j=vs.begin();j!=vs.end();)
       {
         ss+= j->first + "(+"+itos(j->second)+")";
         if(++j!=vs.end())  ss+=", ";
       }
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize "<< LaTeX_scale(LATIN(ss),20,"2.6cm") <<"}\n";
   }
 verwandteSprachen=Sprache::cleanVerwandteSprachen(verwandteSprachen);
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=verwandteSprachen.begin();i!=verwandteSprachen.end();++i)
   { cH_Sprache s(*i);
     if(i->ist_gelernt(hauptfenster->getCChar().CList_Sprache())) continue;
     std::string a = LaTeX_string(sprachanz++);
     fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << LaTeX_scale(LATIN(s->Name()),20,"2.6cm") <<"}\n";
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
 for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_WaffenGrund().begin();i!=hauptfenster->getCChar().CList_WaffenGrund().end();++i)
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
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Beruf().begin();
         i!=hauptfenster->getCChar().CList_Beruf().end();++i)
   {
     fout << LATIN((*i)->Name()); //<<" ("<<(*i).Erfolgswert()<<")\t";
   }
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // weitere Merkmale
 fout << "\\newcommand{\\merkmale}{" ;
 if(hauptfenster->getCWerte().Spezies()->Name()!="Mensch")  fout << LATIN(hauptfenster->getCWerte().Spezies()->Name())<<" "; 
 fout << LATIN(hauptfenster->getCWerte().Merkmale());
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten & Waffen
 /////////////////////////////////////////////////////////////////////////////
 // angeborene Fertigkeiten
 int count=0;
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Fertigkeit_ang().begin();i!=hauptfenster->getCChar().CList_Fertigkeit_ang().end();++i) 
   {cH_Fertigkeit_angeborene f(*i);
    std::string a = LaTeX_string(count);
    count++;
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<LATIN(f->Name()) << "}   ";
    // Praxispunkte
    std::string pp = itos((*i).Praxispunkte());
    if (pp == "0") pp = "";
    fout << "\\newcommand{\\praxis"<<a<<"}{"  << pp << "}   ";
    // Erfolgswert
    std::string wert = itos(f->FErfolgswert(hauptfenster->getCChar().getAbenteurer(),*i));
    if (wert == "0") wert = "";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Fertigkeit().begin();i!=hauptfenster->getCChar().CList_Fertigkeit().end();++i) 
   {cH_Fertigkeit f(*i);
    std::string a = LaTeX_string(count);
    count++;
    std::string wert = itos((*i).Erfolgswert());
    if (wert == "0") wert = "";
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  
      <<LATIN(LaTeX_scale(f->Name()+" "+i->Zusatz(),33,"4cm")) << "}\t\t";
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
//WL int  i_waffenlos = 4;
 unsigned int countwaffen=0;
 std::string angriffsverlust_string = hauptfenster->getCWerte().Ruestung_Angriff_Verlust(hauptfenster->getCChar().CList_Fertigkeit());
 for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Waffen().begin();i!=hauptfenster->getCChar().CList_Waffen().end();++i)
   {cH_Waffe w(*i);
    count++;
    std::string a = LaTeX_string(count);
//std::cout << "latexstring = "<<a<<"\n";
    std::string wert = itos((*i).Erfolgswert());
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<LATIN(w->Name()) << "}\t\t";
    // Praxispunkte
    std::string pp = itos((*i).Praxispunkte());
    if (pp == "0") pp = "";
    fout << "\\newcommand{\\praxis"<<a<<"}{"  << pp << "}   ";
    fout <<"\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
    // waffenloser Kampf:
//WL    if (w->Name()=="waffenloser Kampf") 
//WL         { i_waffenlos=atoi(wert.c_str());}
      for (std::list<WaffeBesitz>::const_iterator j=hauptfenster->getCChar().CList_Waffen_besitz().begin();j!=hauptfenster->getCChar().CList_Waffen_besitz().end();++j)
     {
      WaffeBesitz WB=*j;
      if (WB.Waffe()->Name()==w->Name())
       {
         std::string b = LaTeX_string(countwaffen++);
//std::cout << (*j)->Name()<<"\t"<<w->Name()<<"\t"<<"latexstring = "<<b<<"\n";
         std::string waffenname ;
         waffenname = WB.AliasName();
         fout << "\\newcommand{\\waffe"<<b<<"}{ " ;
         if (WB.Magisch()!="" || 
             WB.av_Bonus()!=0 || WB.sl_Bonus()!=0) waffenname+="$^*$ "+WB.Bonus() ;
         fout <<LaTeX_scalemag(LATIN(waffenname),20,"3cm",WB.Magisch(),WB.Waffe()->Reichweite())<< "}\n";
         
         // Erfolgswert für einen Verteidigungswaffen
         if (WB.Waffe()->Verteidigung())
          {
           int wert = (*i).Erfolgswert() + WB.av_Bonus() + WB.Waffe()->WM_Angriff(WB->Name()) ;
           fout << "\\newcommand{\\waffeE"<<b<<"}{"<<itos(wert)<<"}\n";
          }
         // Erfolgswert für Angriffswaffen
         else 
          {
           int wert = (*i).Erfolgswert() + hauptfenster->getCWerte().bo_An() + WB.av_Bonus() + WB.Waffe()->WM_Angriff(WB->Name()) ;
           // Angriffsbonus subtrahieren, wenn schwere Rüstung getragen wird:
           fout << "\\newcommand{\\waffeE"<<b<<"}{"<<wert<<angriffsverlust_string<<"}\n";
          }
         std::string schaden=WB.Schaden(hauptfenster->getCWerte(),WB->Name(),true);
         fout << "\\newcommand{\\waffeS"<<b<<"}{"<<schaden << "}\n";
         std::string anm = WB.Waffe()->Waffenrang();
         fout << "\\newcommand{\\waffeA"<<b<<"}{"<<anm << "}\n";
         std::string abm = WB.Waffe()->WM_Abwehr();
         fout << "\\newcommand{\\waffeV"<<b<<"}{"<<abm << "}\n";
       }
     }
   }
 // waffenloser Kampf:
/*
 WaffeBesitz waffenlos(cH_Waffe("waffenloser Kampf"));
 
 fout << "\\newcommand{\\waffeEy"<<"}{"<<i_waffenlos+hauptfenster->getCWerte().bo_An() << "}\n";
 std::string schaden= waffenlos.Schaden(hauptfenster->getCWerte(), waffenlos->Name(),true);
 fout << "\\newcommand{\\waffeSy}{"<<schaden << "}\n";
 std::string anm = waffenlos.Waffe()->Waffenrang();
 fout << "\\newcommand{\\waffeAy}{"<<anm << "}\n";
 std::string abm = waffenlos.Waffe()->WM_Abwehr();
 fout << "\\newcommand{\\waffeVy}{"<<abm << "}\n";
*/
 /////////////////////////////////////////////////////////////////////////
 // Universelle Fertigkeiten

 std::list<Abenteurer::st_universell> UF=hauptfenster->getCChar().CList_Universell(hauptfenster->getCDatabase());
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
    else if(name=="Landeskunde (Heimat)") name = "Landeskunde ("+hauptfenster->getCWerte().Herkunft()->Name()+")";

    if (!i->gelernt)
     {
       ++countunifert;
       fout <<"\\newcommand{\\uni"<<a<<"}{"<<LATIN(name)<< "}\t\t";
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
 fout << "\\input{"+install_latex_file+"}\n";
// fout.close();
}


void LaTeX_drucken::LaTeX_write_empty_values(ostream &fout,const std::string &install_latex_file)
{
 fout << "\\documentclass[11pt,a4paper,landscape]{article}\n";
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
    fout <<"\\newcommand{\\uni"<<a<<"}{\\tiny "<<LATIN(name)<< "}\t\t";
    fout << "\\newcommand{\\uniw"<<a<<"}{("<<wert << ")}\n";
  } 


 unsigned int maxunifert=48;
 for (unsigned int i=countunifert; i<maxunifert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\uni"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\uniw"<<a<<"}{\\scriptsize }\n";
   }
 fout << "\\input{"+install_latex_file+"}\n";
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
{
    if(i==0) return("a");
    if(i==1) return("b");
    if(i==2) return("c");
    if(i==3) return("d");
    if(i==4) return("e");
    if(i==5) return("f");
    if(i==6) return("g");
    if(i==7) return("h");
    if(i==8) return("i");
    if(i==9) return("j");
    if(i==10) return("k");
    if(i==11) return("l");
    if(i==12) return("m");
    if(i==13) return("n");
    if(i==14) return("o");
    if(i==15) return("p");
    if(i==16) return("q");
    if(i==17) return("r");
    if(i==18) return("s");
    if(i==19) return("t");
    if(i==20) return("u");
    if(i==21) return("v");
    if(i==22) return("w");
    if(i==23) return("x");
    if(i==24) return("y");
    if(i==25) return("z");
    if(i==26) return("aa");
    if(i==27) return("ab");
    if(i==28) return("ac");
    if(i==29) return("ad");
    if(i==30) return("ae");
    if(i==31) return("af");
    if(i==32) return("ag");
    if(i==33) return("ah");
    if(i==34) return("ai");
    if(i==35) return("aj");
    if(i==36) return("ak");
    if(i==37) return("al");
    if(i==38) return("am");
    if(i==39) return("an");
    if(i==40) return("ao");
    if(i==41) return("ap");
    if(i==42) return("aq");
    if(i==43) return("ar");
    if(i==44) return("as");
    if(i==45) return("at");
    if(i==46) return("au");
    if(i==47) return("av");
   //Never get here
   return("0");
}

void LaTeX_drucken::LaTeX_newsavebox(ostream &fout)
{
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
       fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(hauptfenster->getCWerte().Name_Abenteurer(),25,"4.5cm") << "}\n";
       fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(hauptfenster->getCWerte().Name_Spieler(),25,"4.5cm") << "}\n";
     }
    else
     {
       fout << "\\newcommand{\\namecharakter}{"  <<LaTeX_scale(hauptfenster->getCWerte().Name_Abenteurer(),20,"4.cm") << "}\n";
       fout << "\\newcommand{\\namespieler}{"  <<LaTeX_scale(hauptfenster->getCWerte().Name_Spieler(),20,"4.cm") << "}\n";
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
#ifdef __MINGW32__
  const char * const subpath="\\texmf\\miktex\\bin";
  char buffer[1024];
  static char buffer2[10240];
  const char *e=getenv("PATH");
  if (!strstr(e,subpath))
  {  assert( getcwd(buffer, sizeof buffer) );
     assert( strlen(buffer)+strlen(subpath)<sizeof buffer);
     strcat(buffer,subpath);
     assert( 5+strlen(e)+1+strlen(buffer)<sizeof buffer2 );
     strcpy(buffer2,"PATH=");
     strcat(buffer2,e);
     strcat(buffer2,";");
     strcat(buffer2,buffer); // SearchPathA ?
     putenv(buffer2);
  }
  // GetTempPath ?
#define unlink(a) _unlink(a)

#endif

  system(("pdflatex --interaction scrollmode "+file+".tex").c_str());
  system((hauptfenster->getOptionen()->Viewer()+" "+file+".pdf &").c_str());

//  unlink((file+".tex").c_str());
  unlink((file+".aux").c_str());
  unlink((file+".log").c_str());
//  unlink((file+".pdf").c_str());
}

///////////////////////////////////////////////////////////////

void LaTeX_drucken::LaTeX_zauber(ostream &fout)
{
  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Zauber().begin();i!=hauptfenster->getCChar().CList_Zauber().end();++i)
   {
     cH_Zauber z(*i);
     fout << LATIN(z->Name()) ;
     if(!(*i).Zusatz().empty()) fout << " ("<<LATIN((*i).Zusatz())<<")";
     fout <<" & ";
     fout << z->Erfolgswert_Z(hauptfenster->getCChar().getVTyp(),hauptfenster->getCWerte()) <<" & ";
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
     fout << LATIN(z->Agens(hauptfenster->getCChar().getVTyp())) <<" " <<LATIN(z->Prozess()) <<" "<<LATIN(z->Reagens()) ;
     fout << "\\\\\n";
   }
}

void LaTeX_drucken::LaTeX_zaubermittel(ostream &fout)
{
  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Zauberwerk().begin();i!=hauptfenster->getCChar().CList_Zauberwerk().end();++i)
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


void LaTeX_drucken::LaTeX_zauber_main(ostream &fout)
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

 
  if (hauptfenster->getCChar().CList_Zauberwerk().size()!=0)
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
  for (std::list<MidgardBasicElement_mutable>::const_iterator i=hauptfenster->getCChar().CList_Kido().begin();i!=hauptfenster->getCChar().CList_Kido().end();++i)
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


void LaTeX_drucken::LaTeX_kido_main(ostream &fout)
{
  LaTeX_kopfzeile(fout,true,false);
  fout << "\\begin{tabular}{rllcp{17cm}}\n";
  fout << "\\multicolumn{5}{l}{\\large\\bf Erfolgswert KiDo: "
         <<KiDo::get_erfolgswert_kido(hauptfenster->getCChar().CList_Fertigkeit())+hauptfenster->getCWerte().bo_Za()<<"}\\\\\\hline\n";
  fout << " AP & HoHo & Technik & Stufe & Effekt \\\\\\hline \n";

  LaTeX_kido(fout);
  fout << "\\end{tabular}\n";
  fout << "\\end{center}\n";
}
