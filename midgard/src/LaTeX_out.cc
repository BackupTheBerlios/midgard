// $Id: LaTeX_out.cc,v 1.39 2001/10/07 08:05:31 thoma Exp $
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
#include <Aux/EmptyInt_4TeX.h>

gint midgard_CG::on_latex_release_event(GdkEventButton *ev)
{
  if (ev->button==1) on_latex_clicked();
//  if (ev->button==3) midgard_CG::spielleiter_export();
  return false;
}


void midgard_CG::on_latex_clicked(bool values=true)
{   
 if (!access("document_eingabe.tex",R_OK)) // Files im aktuellen Verzeichnis?
   {
    system("cp document_eingabe.tex midgard_tmp_document_eingabe.tex");
    system("cp latexwertedef.tex midgard_tmp_latexwertedef.tex");
   }
 else
   {
    system("cp "PACKAGE_DATA_DIR"document_eingabe.tex midgard_tmp_document_eingabe.tex");
    system("cp "PACKAGE_DATA_DIR"latexwertedef.tex midgard_tmp_latexwertedef.tex");
   }
 if (values) LaTeX_write_values();
 else LaTeX_write_empty_values();
 system("latex midgard_tmp_document_eingabe.tex");
 system("dvips -t landscape midgard_tmp_document_eingabe.dvi");
 system("gv -seascape midgard_tmp_document_eingabe.ps &");

 // Zauber
 if (list_Zauber.size()>0 || list_Zauberwerk.size()>0)
 {
    LaTeX_zauber_main();
    LaTeX_zauber();
    LaTeX_zaubermittel();
    system("latex midgard_tmp_document_zauber.tex");
    system("dvips -t landscape midgard_tmp_document_zauber.dvi");
    system("gv -seascape midgard_tmp_document_zauber.ps &");
 }

 // KiDo
 if (vec_Kido.size()>0)
 {
    midgard_CG::LaTeX_kido_main();
    midgard_CG::LaTeX_kido();
    system("latex midgard_tmp_document_kido.tex");
    system("dvips -t landscape midgard_tmp_document_kido.dvi");
    system("gv -seascape midgard_tmp_document_kido.ps &");
 }
}      

void midgard_CG::LaTeX_write_values()
{
 ofstream fout("midgard_tmp_latexwerte.tex");
 std::string styp = Typ[0]->Name();
 if (Typ[1]->Name()!="") styp += "/"+Typ[1]->Name();
 fout << "\\newcommand{\\typ}{"<< LaTeX_scale(styp,10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\st}{"  <<Werte.St() << "}\n";
 fout << "\\newcommand{\\gee}{" <<Werte.Ge() << "}\n";
 fout << "\\newcommand{\\ko}{"  <<Werte.Ko()<< "}\n";
 fout << "\\newcommand{\\inn}{" <<Werte.In() << "}\n";
 fout << "\\newcommand{\\zt}{"  <<Werte.Zt() << "}\n";
 fout << "\\newcommand{\\au}{"  <<Werte.Au() << "}\n";
 fout << "\\newcommand{\\pa}{"  <<Werte.pA() << "}\n";
 fout << "\\newcommand{\\sbb}{"  <<Werte.Sb() << "}\n";
 int reaktionswert = Werte.RW() - atoi(midgard_CG::ruestung("RW").c_str());
 fout << "\\newcommand{\\rw}{"  << Werte.RW() << "\\scriptsize ("<<reaktionswert<<")}\n";
 fout << "\\newcommand{\\hgw}{"  <<Werte.HGW() << "}\n";
 int bewegungsweite = Werte.B() - atoi(midgard_CG::ruestung("B").c_str());
 fout << "\\newcommand{\\bb}{"  <<Werte.B() << "\\scriptsize ("<<bewegungsweite<<")}\n";
 fout << "\\newcommand{\\kaw}{"  <<Werte.KAW() << "}\n";
 fout << "\\newcommand{\\wlw}{"  <<Werte.WLW() << "}\n";
 fout << "\\newcommand{\\lpbasis}{"  <<Werte.LPBasis() << "}\n";
 fout << "\\newcommand{\\lp}{"  <<Werte.LP() << "}\n";
 fout << "\\newcommand{\\ap}{"  <<Werte.AP() << "}\n";
 fout << "\\newcommand{\\boau}{"<<Werte.bo_Au()<< "}\n";
 fout << "\\newcommand{\\bosc}{"<<Werte.bo_Sc()<< "}\n";
 fout << "\\newcommand{\\boan}{"<<Werte.bo_An()<< "}\n";
 fout << "\\newcommand{\\boab}{"<<Werte.bo_Ab()<< "}\n";
 fout << "\\newcommand{\\boza}{"<<Werte.bo_Za()<< "}\n";
 fout << "\\newcommand{\\bopsy}{"<<Werte.bo_Psy()<< "}\n";
 fout << "\\newcommand{\\bophs}{"<<Werte.bo_Phs()<< "}\n";
 fout << "\\newcommand{\\bophk}{"<<Werte.bo_Phk()<< "}\n";
 fout << "\\newcommand{\\bogi}{"<<Werte.bo_Gift()<< "}\n";
 fout << "\\newcommand{\\psy}{"<<Werte.Resistenz()+Werte.bo_Psy()<<"}\n";
 fout << "\\newcommand{\\phs}{"<<Werte.Resistenz()+Werte.bo_Phs()<<"}\n";
 fout << "\\newcommand{\\phk}{"<<Werte.Resistenz()+Werte.bo_Phk()<<"}\n";
 fout << "\\newcommand{\\gift}{"<<3*Werte.LP()+Werte.bo_Gift()+ Spezies_constraint.Gift()<<"}\n";

 fout << "\\newcommand{\\abwehr}{"<<Werte.Abwehr_wert()<< "}\n";
 fout << "\\newcommand{\\abwehrfinal}{"<<Werte.Abwehr_wert()+Werte.bo_Ab()<< "}\n";
 int ohne_waffe=Werte.Abwehr_wert()+Werte.bo_Ab();
 std::string mit_waffe = midgard_CG::get_Verteidigungswaffe(ohne_waffe);
 if (atoi(mit_waffe.c_str())!=Werte.Abwehr_wert()+Werte.bo_Ab())
    fout << "\\newcommand{\\abwehrmitwaffe}{"<<mit_waffe<< "}\n";
 else 
    fout << "\\newcommand{\\abwehrmitwaffe}{""}\n";

 fout << "\\newcommand{\\zauber}{"<<EmptyInt_4TeX(Werte.Zaubern_wert())<< "}\n";
 fout << "\\newcommand{\\alter}{"  <<Werte.Alter() << "}\n";
 fout << "\\newcommand{\\gestalt}{"  <<LaTeX_scale(Werte.Gestalt(),5,"0.7cm") << "}\n";
 fout << "\\newcommand{\\gewicht}{"  <<Werte.Gewicht() << "\\,kg}\n";
 fout << "\\newcommand{\\koerpergroesse}{"  <<Werte.Groesse()/100. << "\\,m}\n";
 fout << "\\newcommand{\\grad}{"  <<Werte.Grad() << "}\n";
 fout << "\\newcommand{\\spezialisierung}{ "  <<LaTeX_scale(Werte.Spezialisierung(),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\stand}{"  <<LaTeX_scale(Werte.Stand(),10,"1.5cm") << "}\n";
 fout << "\\newcommand{\\herkunft}{"  <<LaTeX_scale(Werte.Herkunft(),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\glaube}{"  <<LaTeX_scale(Werte.Glaube(),10,"2.5cm") << "}\n";
 fout << "\\newcommand{\\namecharakter}{" << LaTeX_scale(Werte.Name_Charakter(),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\namespieler}{" << LaTeX_scale(Werte.Name_Spieler(),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\gfp}{\\tiny "  <<EmptyInt_4TeX(Werte.GFP()) << "}\n";
 fout << "\\newcommand{\\aep}{\\tiny "  <<EmptyInt_4TeX(Werte.AEP()) << "}\n";
 fout << "\\newcommand{\\kep}{\\tiny "  <<EmptyInt_4TeX(Werte.KEP()) << "}\n";
 fout << "\\newcommand{\\zep}{\\tiny "  <<EmptyInt_4TeX(Werte.ZEP()) << "}\n";

 double geld = Werte.Gold() + Werte.Silber()/10. + Werte.Kupfer()/100.;
 fout << "\\newcommand{\\gold}{\\tiny "  << geld << "}\n";

 fout << "\\newcommand{\\ruestung}{\\scriptsize "  <<Werte.Ruestung() << "}\n";
 fout << "\\newcommand{\\ruestunglp}{\\scriptsize "  <<midgard_CG::ruestung("LP") << "}\n";

 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 unsigned int sprachanz=0;
 unsigned int maxsprach=14;
// for (unsigned int i=0; i<vec_sprachen.size();++i)
 for(std::vector<H_Data_sprache>::const_iterator i=vec_Sprachen.begin();i!=vec_Sprachen.end();++i)
   {
      std::string a = LaTeX_string(sprachanz);
      ++sprachanz;
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << (*i)->Name() <<"}\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize "<< (*i)->Wert() <<"}\n";
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize "<< (*i)->Urschrift() <<"}\n";
   }
 for (unsigned int i=sprachanz; i<maxsprach;++i) // Bis zum Ende auffüllen
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize }\n";
   }


 /////////////////////////////////////////////////////////////////////////////
 // Grundfertigkeiten (Waffen)
 for (map<std::string,string>::const_iterator i=waffen_grundkenntnisse.begin();
         i!=waffen_grundkenntnisse.end();++i)
   {
      std::string sout = i->first;
      if (sout =="Bögen") sout = "Bogen";
      if (sout =="Wurfspieß") sout = "Wurfspiess";
      if (sout =="Spießwaffe") sout = "Spiesswaffe";
      if (sout =="waffenloser Kampf") sout = "waffenlos";
      fout << "\\sbox{\\"<<sout<<"}{\\tiny X}\n";
   }

 /////////////////////////////////////////////////////////////////////////////
 // Beruf
 fout << "\\newcommand{\\beruf}{" ;
 for(std::vector<H_Data_beruf>::const_iterator i=vec_Beruf.begin();
         i!=vec_Beruf.end();++i)
   {
     fout << (*i)->Name()<<" ("<<(*i)->Erfolgswert()<<")\t";
   }
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten & Waffen
 /////////////////////////////////////////////////////////////////////////////
 // angeborene Fertigkeiten
 int count=0;
 for(std::vector<H_Data_fert>::const_iterator i=vec_an_Fertigkeit.begin();i!=vec_an_Fertigkeit.end();++i) 
   {
    std::string a = LaTeX_string(count);
    count++;
    std::string wert = itos((*i)->Erfolgswert());
    if (wert == "0") wert = "";
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<(*i)->Name() << "}\t\t";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
//    fout << "\\newcommand{\\wert"<<a<<"}{"  <<(*i)->Empty_Erfolgswert() << "}\n";
   }
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for(std::list<H_Data_fert>::const_iterator i=vec_Fertigkeiten.begin();i!=vec_Fertigkeiten.end();++i) 
   {
    std::string a = LaTeX_string(count);
    count++;
    std::string wert = itos((*i)->Erfolgswert());
    if (wert == "0") wert = "";
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<(*i)->Name() << "}\t\t";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
//    fout << "\\newcommand{\\wert"<<a<<"}{"  <<(*i)->Empty_Erfolgswert() << "}\n";
   }
 std::string a = LaTeX_string(count);
 fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
 fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";

 /////////////////////////////////////////////////////////////////////////////
 // Waffen + Waffen/Besitz
 int  i_waffenlos = 4;
 unsigned int countwaffen=0;
// for (unsigned int i=0;i<vec_Waffen.size();++i)
// int jcount=0;
 for (std::vector<H_Data_waffen>::const_iterator i=vec_Waffen.begin();i!=vec_Waffen.end();++i)
   {
    count++;
    std::string a = LaTeX_string(count);
//std::cout << "latexstring = "<<a<<"\n";
    std::string wert = itos((*i)->Erfolgswert());
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<(*i)->Name() << "}\t\t";
    fout <<"\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
    // waffenloser Kampf:
    if ((*i)->Name()=="waffenloser Kampf") 
         { i_waffenlos=atoi(wert.c_str());}
//    for (unsigned int j=0; j<waffe_besitz.size();++j)
      for (std::vector<H_Data_waffen>::const_iterator j=vec_Waffen_besitz.begin();j!=vec_Waffen_besitz.end();++j)
     {
      if ((*j)->Name()==(*i)->Name())
       {
//         ++countwaffen;
         std::string b = LaTeX_string(countwaffen++);
//std::cout << (*j)->Name()<<"\t"<<(*i)->Name()<<"\t"<<"latexstring = "<<b<<"\n";
         std::string waffenname ;
         waffenname = (*j)->Alias();
         fout << "\\newcommand{\\waffe"<<b<<"}{ " ;
         if ((*j)->Magisch()!="") waffenname+="$^*$" ;
         fout <<LaTeX_scale(waffenname,15,"2.5cm",*j)<< "}\n";
         int mag_schadensbonus = (*j)->av_Bonus();
         int anbo = Werte.bo_An();
         int ang_mod = atoi(waffe_werte(*j,Werte,"WM_Angriff").c_str());
         if (midgard_CG::waffe_werte(*j,Werte,"Verteidigung")=="true")
            anbo = 0;
         int wert = (*i)->Erfolgswert() + anbo + mag_schadensbonus + ang_mod ;
         fout << "\\newcommand{\\waffeE"<<b<<"}{"<<wert << "}\n";
         std::string schaden=waffe_werte(*j,Werte,"Schaden+mag_Bonus");
         fout << "\\newcommand{\\waffeS"<<b<<"}{"<<schaden << "}\n";
         std::string anm = midgard_CG::waffe_werte(*j,Werte,"Angriffsrangmodifikation");
         fout << "\\newcommand{\\waffeA"<<b<<"}{"<<anm << "}\n";
         std::string abm = waffe_werte(*j,Werte,"WM_Abwehr");
         fout << "\\newcommand{\\waffeV"<<b<<"}{"<<abm << "}\n";
       }
     }
   }
 // waffenloser Kampf:
 fout << "\\newcommand{\\waffeEy"<<"}{"<<i_waffenlos+Werte.bo_An() << "}\n";
 std::string schaden=midgard_CG::waffe_werte(new Data_waffen("waffenloser Kampf","waffenloser Kampf","",0,0,""),Werte,"Schaden");
 fout << "\\newcommand{\\waffeSy}{"<<schaden << "}\n";
 std::string anm = midgard_CG::waffe_werte(new Data_waffen("waffenloser Kampf","waffenloser Kampf","",0,0,""),Werte,"Angriffsrangmodifikation");
 fout << "\\newcommand{\\waffeAy}{"<<anm << "}\n";
 std::string abm = midgard_CG::waffe_werte(new Data_waffen("waffenloser Kampf","waffenloser Kampf","",0,0,""),Werte,"WM_Abwehr");
 fout << "\\newcommand{\\waffeVy}{"<<abm << "}\n";

 // Fertigkeiten auffüllen
 unsigned int maxfert=36;
 for (unsigned int i=count+1; i<maxfert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";
   }
 // Waffen auffüllen
 unsigned int maxwaffen=6;
 for (unsigned int i=countwaffen; i<maxwaffen;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\waffe"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeE"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeS"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeA"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeV"<<a<<"}{\\scriptsize }\n";
   }
 fout.close();

}


void midgard_CG::LaTeX_write_empty_values()
{
 ofstream fout("midgard_tmp_latexwerte.tex");
 fout << "\\newcommand{\\typ}{}\n";
 fout << "\\newcommand{\\st}{}\n";
 fout << "\\newcommand{\\gee}{}\n";
 fout << "\\newcommand{\\ko}{}\n";
 fout << "\\newcommand{\\inn}{}\n";
 fout << "\\newcommand{\\zt}{}\n";
 fout << "\\newcommand{\\au}{}\n";
 fout << "\\newcommand{\\pa}{}\n";
 fout << "\\newcommand{\\sbb}{}\n";
 fout << "\\newcommand{\\rw}{}\n";
 fout << "\\newcommand{\\hgw}{}\n";
 fout << "\\newcommand{\\bb}{}\n";
 fout << "\\newcommand{\\kaw}{}\n";
 fout << "\\newcommand{\\wlw}{}\n";
 fout << "\\newcommand{\\lpbasis}{}\n";
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
 fout << "\\newcommand{\\psy}{}\n";
 fout << "\\newcommand{\\phs}{}\n";
 fout << "\\newcommand{\\phk}{}\n";
 fout << "\\newcommand{\\gift}{}\n";

 fout << "\\newcommand{\\abwehr}{}\n";
 fout << "\\newcommand{\\abwehrfinal}{}\n";
 fout << "\\newcommand{\\abwehrmitwaffe}{}\n";

 fout << "\\newcommand{\\zauber}{}\n";
 fout << "\\newcommand{\\alter}{}\n";
 fout << "\\newcommand{\\gestalt}{}\n";
 fout << "\\newcommand{\\gewicht}{}\n";
 fout << "\\newcommand{\\koerpergroesse}{}\n";
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
 unsigned int sprachanz=0;
 unsigned int maxsprach=14;
 for (unsigned int i=sprachanz; i<maxsprach;++i) // Bis zum Ende auffüllen
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
 unsigned int maxfert=36;
 for (unsigned int i=0; i<maxfert;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";
   }
 // Waffen auffüllen
 unsigned int maxwaffen=6;
 for (unsigned int i=0; i<maxwaffen;++i)
   {
      std::string a = LaTeX_string(i);
      fout << "\\newcommand{\\waffe"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeE"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeS"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeA"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeV"<<a<<"}{\\scriptsize }\n";
   }

 fout.close();

}



std::string midgard_CG::LaTeX_scale(const std::string& is, unsigned int maxlength, const std::string& scale, const H_Data_waffen& Waffe)
{
 std::string os;
 if (is.size() <= maxlength) os = is;
 else  os = "\\resizebox*{"+scale+"}{1.5ex}{"+is+"}" ;

 if (Waffe->Name()!="")
   {
     std::string l1=os,l2;
     if (Waffe->Magisch()==""||Waffe->Magisch()=="*") l2 = midgard_CG::waffe_werte(Waffe,Werte,"Fern");
     else  { if ((Waffe->Magisch()).size()<=25) l2 = "\\tiny "+Waffe->Magisch();
             else l2 = "\\resizebox*{"+scale+"}{1.5ex}{\\tiny "+Waffe->Magisch()+"}" ;
       }
     os = "\\parbox{2cm}{\\mbox{"+l1+"}" ;
     if (l2!="")  os += "\\tiny\\\\ \\mbox{"+l2+"}";
     os += "}";
   }
 return os;
}


std::string midgard_CG::LaTeX_string(int i)
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
   //Never get here
   return("0");
}
