// $Id: LaTeX_out.cc,v 1.9 2001/04/19 11:45:35 christof Exp $
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

void midgard_CG::on_latex_clicked()
{   
 system("cp "PACKAGE_DATA_DIR"document_eingabe.tex midgard_tmp_document_eingabe.tex");
 system("cp "PACKAGE_DATA_DIR"latexwertedef.tex midgard_tmp_latexwertedef.tex");

 ofstream fout("midgard_tmp_latexwerte.tex");
 fout << "\\newcommand{\\typ}{\\footnotesize " << typ.l << "}\n";
 fout << "\\newcommand{\\st}{"  <<werte.st << "}\n";
 fout << "\\newcommand{\\gee}{" <<werte.ge << "}\n";
 fout << "\\newcommand{\\ko}{"  <<werte.ko<< "}\n";
 fout << "\\newcommand{\\inn}{" <<werte.in << "}\n";
 fout << "\\newcommand{\\zt}{"  <<werte.zt << "}\n";
 fout << "\\newcommand{\\au}{"  <<werte.au << "}\n";
 fout << "\\newcommand{\\pa}{"  <<werte.pa << "}\n";
 fout << "\\newcommand{\\sbb}{"  <<werte.sb << "}\n";
 int reaktionswert = werte.rw - atoi(midgard_CG::ruestung("RW").c_str());
 fout << "\\newcommand{\\rw}{"  << werte.rw << "\\scriptsize ("<<reaktionswert<<")}\n";
 fout << "\\newcommand{\\hgw}{"  <<werte.hgw << "}\n";
 int bewegungsweite = werte.b - atoi(midgard_CG::ruestung("B").c_str());
 fout << "\\newcommand{\\bb}{"  <<werte.b << "\\scriptsize ("<<bewegungsweite<<")}\n";
 fout << "\\newcommand{\\kaw}{"  <<werte.kaw << "}\n";
 fout << "\\newcommand{\\wlw}{"  <<werte.wlw << "}\n";
 fout << "\\newcommand{\\lpbasis}{"  <<werte.lpbasis << "}\n";
 fout << "\\newcommand{\\lp}{"  <<werte.lp << "}\n";
 fout << "\\newcommand{\\ap}{"  <<werte.ap << "}\n";
 fout << "\\newcommand{\\boau}{"<<werte.bo_au<< "}\n";
 fout << "\\newcommand{\\bosc}{"<<werte.bo_sc<< "}\n";
 fout << "\\newcommand{\\boan}{"<<werte.bo_an<< "}\n";
 fout << "\\newcommand{\\boab}{"<<werte.bo_ab<< "}\n";
 fout << "\\newcommand{\\boza}{"<<werte.bo_za<< "}\n";
 fout << "\\newcommand{\\bopsy}{"<<werte.bo_psy<< "}\n";
 fout << "\\newcommand{\\bophs}{"<<werte.bo_phs<< "}\n";
 fout << "\\newcommand{\\bophk}{"<<werte.bo_phk<< "}\n";
 fout << "\\newcommand{\\bogi}{"<<werte.bo_gi<< "}\n";
// fout << "\\newcommand{\\psy}{"<<werte.psyZR_wert<<"+"<<werte.bo_psy<<"}\n";
// fout << "\\newcommand{\\phs}{"<<werte.phsZR_wert<<"+"<<werte.bo_phs<<"}\n";
// fout << "\\newcommand{\\phk}{"<<werte.phkZR_wert<<"+"<<werte.bo_phk<<"}\n";
// fout << "\\newcommand{\\gift}{"<<werte.gift_wert<<"+"<<werte.bo_gi<<"}\n";
 fout << "\\newcommand{\\psy}{"<<werte.psyZR_wert+werte.bo_psy<<"}\n";
 fout << "\\newcommand{\\phs}{"<<werte.phsZR_wert+werte.bo_phs<<"}\n";
 fout << "\\newcommand{\\phk}{"<<werte.phkZR_wert+werte.bo_phk<<"}\n";
 fout << "\\newcommand{\\gift}{"<<werte.gift_wert+werte.bo_gi<<"}\n";

 fout << "\\newcommand{\\abwehr}{"<<werte.abwehr_wert<< "}\n";
 fout << "\\newcommand{\\abwehrfinal}{"<<werte.abwehr_wert+werte.bo_ab<< "}\n";
 int ohne_waffe=werte.abwehr_wert+werte.bo_ab;
 string mit_waffe = midgard_CG::get_Verteidigungswaffe(ohne_waffe);
 fout << "\\newcommand{\\abwehrmitwaffe}{"<<mit_waffe<< "}\n";
 

 fout << "\\newcommand{\\zauber}{"<<werte.zaubern_wert<< "}\n";
 fout << "\\newcommand{\\alter}{"  <<werte.alter << "}\n";
 fout << "\\newcommand{\\gestalt}{"  <<werte.gestalt << "}\n";
 fout << "\\newcommand{\\gewicht}{"  <<werte.gewicht << "}\n";
 fout << "\\newcommand{\\koerpergroesse}{"  <<werte.groesse << "}\n";
 fout << "\\newcommand{\\grad}{"  <<werte.grad << "}\n";
 fout << "\\newcommand{\\spezialisierung}{\\tiny "  <<werte.spezialisierung << "}\n";
 fout << "\\newcommand{\\stand}{\\scriptsize "  <<werte.stand << "}\n";
 fout << "\\newcommand{\\herkunft}{"  <<werte.herkunft << "}\n";
 fout << "\\newcommand{\\glaube}{\\scriptsize "  <<werte.glaube << "}\n";
 fout << "\\newcommand{\\namecharakter}{"  <<werte.name_charakter << "}\n";
 fout << "\\newcommand{\\namespieler}{"  <<werte.name_spieler << "}\n";
 fout << "\\newcommand{\\gfp}{\\tiny "  <<werte.gfp << "}\n";

 double geld = werte.gold + werte.silber/10. + werte.kupfer/100.;
 fout << "\\newcommand{\\gold}{\\tiny "  << geld << "}\n";

 fout << "\\newcommand{\\ruestung}{\\small "  <<werte.ruestung << "}\n";
 fout << "\\newcommand{\\ruestunglp}{\\small "  <<midgard_CG::ruestung("LP") << "}\n";

 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 unsigned int sprachanz=0;
 unsigned int maxsprach=14;
 for (unsigned int i=0; i<vec_sprachen.size();++i)
   {
      string a = LaTeX_string(i);
      ++sprachanz;
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << vec_sprachen[i].name <<"}\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize "<< vec_sprachen[i].wert <<"}\n";
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize "<< vec_sprachen[i].schrift <<"}\n";
   }
 for (unsigned int i=sprachanz; i<maxsprach;++i)
   {
      string a = LaTeX_string(i);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize }\n";
   }


 /////////////////////////////////////////////////////////////////////////////
 // Grundfertigkeiten (Waffen)
 for (map<string,string>::const_iterator i=waffen_grundkenntnisse.begin();
         i!=waffen_grundkenntnisse.end();++i)
   {
      string sout = i->first;
      if (sout =="Bögen") sout = "Bogen";
      if (sout =="Wurfspieß") sout = "Wurfspiess";
      if (sout =="Spießwaffe") sout = "Spiesswaffe";
      if (sout =="waffenloser Kampf") sout = "waffenlos";
      fout << "\\sbox{\\"<<sout<<"}{\\tiny X}\n";
   }

 /////////////////////////////////////////////////////////////////////////////
 // Beruf
 fout << "\\newcommand{\\beruf}{" ;
 for(vector<st_ausgewaehlte_berufe>::iterator i=vec_beruf.begin();
         i!=vec_beruf.end();++i)
   {
     fout << i->name<<" ("<<i->erfolgswert<<")\t";
   }
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten & Waffen
 /////////////////////////////////////////////////////////////////////////////
 // angeborene Fertigkeiten
 int count=0;
 for (unsigned int i=0;i<vec_an_fertigkeit.size();++i)
   {
    string a = LaTeX_string(count);
    count++;
    string wert = itos(vec_an_fertigkeit[i].erfolgswert);
    if (wert == "0") wert = "";
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<vec_an_fertigkeit[i].name << "}\t\t";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for (unsigned int i=0;i<vec_fertigkeiten.size();++i)
   {
    string a = LaTeX_string(count);
    count++;
    string wert = itos(vec_fertigkeiten[i].erfolgswert);
    if (wert == "0") wert = "";
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<vec_fertigkeiten[i].name << "}\t\t";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 string a = LaTeX_string(count);
 fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
 fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";

 /////////////////////////////////////////////////////////////////////////////
 // Waffen + Waffen/Besitz
 int  i_waffenlos = 4;
 unsigned int countwaffen=0;
 for (unsigned int i=0;i<vec_waffen.size();++i)
   {
    count++;
    string a = LaTeX_string(count);
    string wert = itos(vec_waffen[i].erfolgswert);
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<vec_waffen[i].name << "}\t\t";
    fout <<"\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
    // waffenloser Kampf:
    if (vec_waffen[i].name=="waffenloser Kampf") 
         { i_waffenlos=atoi(wert.c_str());}
    for (unsigned int j=0; j<waffe_besitz.size();++j)
     {
      if (waffe_besitz[j].name==vec_waffen[i].name)
       {
         ++countwaffen;
         string b = LaTeX_string(j);
         string waffenname ;
         waffenname = waffe_besitz[j].alias;
         fout << "\\newcommand{\\waffe"<<b<<"}{\\scriptsize "<<waffenname ;
         if (waffe_besitz[j].av_bonus!=0 || waffe_besitz[j].sl_bonus!=0) fout <<"$^*$";
         fout << "}\n";
         int mag_schadensbonus = waffe_besitz[j].av_bonus;
         if (waffe_besitz[j].av_bonus==-5 && waffe_besitz[j].sl_bonus==-5) mag_schadensbonus = 0; 
         int anbo = werte.bo_an;
         if (midgard_CG::waffe_werte(waffe_besitz[j],werte,"Verteidigung")=="true")
            anbo = 0;
         int wert = vec_waffen[i].erfolgswert + anbo + mag_schadensbonus;
         fout << "\\newcommand{\\waffeE"<<b<<"}{"<<wert << "}\n";
         string schaden=midgard_CG::waffe_werte(waffe_besitz[j],werte,"Schaden+mag_Bonus");
         fout << "\\newcommand{\\waffeS"<<b<<"}{"<<schaden << "}\n";
         string anm = midgard_CG::waffe_werte(waffe_besitz[j],werte,"Angriffsrangmodifikation");
         fout << "\\newcommand{\\waffeA"<<b<<"}{"<<anm << "}\n";
         string abm = midgard_CG::waffe_werte(waffe_besitz[j],werte,"WM_Abwehr");
         fout << "\\newcommand{\\waffeV"<<b<<"}{"<<abm << "}\n";
       }
     }
   }
 // waffenloser Kampf:
 fout << "\\newcommand{\\waffeEy"<<"}{"<<i_waffenlos+werte.bo_an << "}\n";
 string schaden=midgard_CG::waffe_werte(st_waffen_besitz("waffenloser Kampf","waffenloser Kampf","",0,0),werte,"Schaden");
 fout << "\\newcommand{\\waffeSy}{"<<schaden << "}\n";
 string anm = midgard_CG::waffe_werte(st_waffen_besitz("waffenloser Kampf","waffenloser Kampf","",0,0),werte,"Angriffsrangmodifikation");
 fout << "\\newcommand{\\waffeAy}{"<<anm << "}\n";
 string abm = midgard_CG::waffe_werte(st_waffen_besitz("waffenloser Kampf","waffenloser Kampf","",0,0),werte,"WM_Abwehr");
 fout << "\\newcommand{\\waffeVy}{"<<abm << "}\n";

 // Fertigkeiten auffüllen
 unsigned int maxfert=36;
 for (unsigned int i=count+1; i<maxfert;++i)
   {
      string a = LaTeX_string(i);
      fout << "\\newcommand{\\fert"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\wert"<<a<<"}{\\scriptsize }\n";
   }
 // Waffen auffüllen
 unsigned int maxwaffen=6;
 for (unsigned int i=countwaffen; i<maxwaffen;++i)
   {
      string a = LaTeX_string(i);
      fout << "\\newcommand{\\waffe"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeE"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeS"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeA"<<a<<"}{\\scriptsize }\n";
      fout << "\\newcommand{\\waffeV"<<a<<"}{\\scriptsize }\n";
   }
 fout.close();
 system("latex midgard_tmp_document_eingabe.tex");
 system("dvips -t landscape midgard_tmp_document_eingabe.dvi");
 system("gv -seascape midgard_tmp_document_eingabe.ps &");

 // Zauber
 if (zauber.size()>0 || vec_zaubermittel.size()>0)
 {
    midgard_CG::LaTeX_zauber_main();
    midgard_CG::LaTeX_zauber();
    midgard_CG::LaTeX_zaubermittel();
    system("latex midgard_tmp_document_zauber.tex");
    system("dvips -t landscape midgard_tmp_document_zauber.dvi");
    system("gv -seascape midgard_tmp_document_zauber.ps &");
 }

 // KiDo
 if (vec_kido.size()>0)
 {
    midgard_CG::LaTeX_kido_main();
    midgard_CG::LaTeX_kido();
    system("latex midgard_tmp_document_kido.tex");
    system("dvips -t landscape midgard_tmp_document_kido.dvi");
    system("gv -seascape midgard_tmp_document_kido.ps &");
 }
}      


string midgard_CG::LaTeX_string(int i)
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