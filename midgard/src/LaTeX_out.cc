#include "midgard_CG.hh"

void midgard_CG::on_latex_clicked()
{   
 system("cp "PACKAGE_DATA_DIR"document_eingabe.tex midgard_tmp_document_eingabe.tex");
 system("cp "PACKAGE_DATA_DIR"latexwertedef.tex midgard_tmp_latexwertedef.tex");

 ofstream fout("midgard_tmp_latexwerte.tex");
 fout << "\\sbox{\\typ}{\\footnotesize " << typ.l << "}\n";
 fout << "\\sbox{\\st}{"  <<werte.st << "}\n";
 fout << "\\sbox{\\gee}{" <<werte.ge << "}\n";
 fout << "\\sbox{\\ko}{"  <<werte.ko<< "}\n";
 fout << "\\sbox{\\inn}{" <<werte.in << "}\n";
 fout << "\\sbox{\\zt}{"  <<werte.zt << "}\n";
 fout << "\\sbox{\\au}{"  <<werte.au << "}\n";
 fout << "\\sbox{\\pa}{"  <<werte.pa << "}\n";
 fout << "\\sbox{\\sbb}{"  <<werte.sb << "}\n";
 int reaktionswert = werte.rw - atoi(midgard_CG::ruestung("RW").c_str());
 fout << "\\sbox{\\rw}{"  << werte.rw << "\\scriptsize ("<<reaktionswert<<")}\n";
 fout << "\\sbox{\\hgw}{"  <<werte.hgw << "}\n";
 int bewegungsweite = werte.b - atoi(midgard_CG::ruestung("B").c_str());
 fout << "\\sbox{\\bb}{"  <<werte.b << "\\scriptsize ("<<bewegungsweite<<")}\n";
 fout << "\\sbox{\\kaw}{"  <<werte.kaw << "}\n";
 fout << "\\sbox{\\wlw}{"  <<werte.wlw << "}\n";
 fout << "\\sbox{\\lpbasis}{"  <<werte.lpbasis << "}\n";
 fout << "\\sbox{\\lp}{"  <<werte.lp << "}\n";
 fout << "\\sbox{\\ap}{"  <<werte.ap << "}\n";
 fout << "\\sbox{\\boau}{"<<werte.bo_au<< "}\n";
 fout << "\\sbox{\\bosc}{"<<werte.bo_sc<< "}\n";
 fout << "\\sbox{\\boan}{"<<werte.bo_an<< "}\n";
 fout << "\\sbox{\\boab}{"<<werte.bo_ab<< "}\n";
 fout << "\\sbox{\\boza}{"<<werte.bo_za<< "}\n";
 fout << "\\sbox{\\bopsy}{"<<werte.bo_psy<< "}\n";
 fout << "\\sbox{\\bophs}{"<<werte.bo_phs<< "}\n";
 fout << "\\sbox{\\bophk}{"<<werte.bo_phk<< "}\n";
 fout << "\\sbox{\\bogi}{"<<werte.bo_gi<< "}\n";
 fout << "\\sbox{\\psy}{"<<werte.psyZR_wert<<"+"<<werte.bo_psy<<"}\n";
 fout << "\\sbox{\\phs}{"<<werte.phsZR_wert<<"+"<<werte.bo_phs<<"}\n";
 fout << "\\sbox{\\phk}{"<<werte.phkZR_wert<<"+"<<werte.bo_phk<<"}\n";
 fout << "\\sbox{\\gift}{"<<werte.gift_wert<<"+"<<werte.bo_gi<<"}\n";

 fout << "\\sbox{\\abwehr}{"<<werte.abwehr_wert<< "}\n";
 fout << "\\sbox{\\abwehrfinal}{"<<werte.abwehr_wert+werte.bo_ab<< "}\n";
 fout << "\\sbox{\\zauber}{"<<werte.zaubern_wert<< "}\n";
 fout << "\\sbox{\\alter}{"  <<werte.alter << "}\n";
 fout << "\\sbox{\\gestalt}{"  <<werte.gestalt << "}\n";
 fout << "\\sbox{\\gewicht}{"  <<werte.gewicht << "}\n";
 fout << "\\sbox{\\koerpergroesse}{"  <<werte.groesse << "}\n";
 fout << "\\sbox{\\grad}{"  <<werte.grad << "}\n";
 fout << "\\sbox{\\spezialisierung}{\\tiny "  <<werte.spezialisierung << "}\n";
 fout << "\\sbox{\\stand}{\\scriptsize "  <<werte.stand << "}\n";
 fout << "\\sbox{\\herkunft}{"  <<werte.herkunft << "}\n";
 fout << "\\sbox{\\glaube}{\\scriptsize "  <<werte.glaube << "}\n";
 fout << "\\sbox{\\namecharakter}{"  <<werte.name_charakter << "}\n";
 fout << "\\sbox{\\namespieler}{"  <<werte.name_spieler << "}\n";
 fout << "\\sbox{\\gfp}{\\tiny "  <<werte.gfp << "}\n";

 double geld = werte.gold + werte.silber/10. + werte.kupfer/100.;
 fout << "\\sbox{\\gold}{\\tiny "  << geld << "}\n";

 fout << "\\sbox{\\ruestung}{\\small "  <<werte.ruestung << "}\n";
 fout << "\\sbox{\\ruestunglp}{\\small "  <<midgard_CG::ruestung("LP") << "}\n";

 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 for (unsigned int i=0; i<vec_sprachen.size();++i)
   {
      string a = LaTeX_string(i);
      fout << "\\sbox{\\spra"<<a<<"}{\\scriptsize " << vec_sprachen[i].name <<"}\n";
      fout << "\\sbox{\\spraw"<<a<<"}{\\scriptsize "<< vec_sprachen[i].wert <<"}\n";
      fout << "\\sbox{\\schr"<<a<<"}{\\scriptsize "<< vec_sprachen[i].schrift <<"}\n";
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
 fout << "\\sbox{\\beruf}{" ;
 for(vector<st_ausgewaelte_berufe>::iterator i=vec_beruf.begin();
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
    fout <<"\\sbox{\\fert"<<a<<"}{\\scriptsize "  <<vec_an_fertigkeit[i].name << "}\t\t";
    fout << "\\sbox{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for (unsigned int i=0;i<vec_fertigkeiten.size();++i)
   {
    string a = LaTeX_string(count);
    count++;
    string wert = itos(vec_fertigkeiten[i].erfolgswert);
    if (wert == "0") wert = "";
    fout <<"\\sbox{\\fert"<<a<<"}{\\scriptsize "  <<vec_fertigkeiten[i].name << "}\t\t";
    fout << "\\sbox{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 /////////////////////////////////////////////////////////////////////////////
 // Waffen + Waffen/Besitz
 int  i_waffenlos = 4;
 for (unsigned int i=0;i<vec_waffen.size();++i)
   {
    count++;
    string a = LaTeX_string(count);
    string wert = itos(vec_waffen[i].erfolgswert);
    fout <<"\\sbox{\\fert"<<a<<"}{\\scriptsize "  <<vec_waffen[i].name << "}\t\t";
    fout << "\\sbox{\\wert"<<a<<"}{"  <<wert << "}\n";
    // waffenloser Kampf:
    if (vec_waffen[i].name=="waffenloser Kampf") 
         { i_waffenlos=atoi(wert.c_str());}
    for (unsigned int j=0; j<waffe_besitz.size();++j)
     {
      if (waffe_besitz[j]==vec_waffen[i].name)
       {
         string b = LaTeX_string(i);
         fout << "\\sbox{\\waffe"<<b<<"}{"<<waffe_besitz[j] << "}\n";
         int wert = vec_waffen[i].erfolgswert + werte.bo_an;
         fout << "\\sbox{\\waffeE"<<b<<"}{"<<wert << "}\n";
         string schaden=midgard_CG::waffe_werte(waffe_besitz[j],werte,"Schaden");
         fout << "\\sbox{\\waffeS"<<b<<"}{"<<schaden << "}\n";
         string anm = midgard_CG::waffe_werte(waffe_besitz[j],werte,"Angriffsrangmodifikation");
cout << "\\sbox{\\waffeA"<<b<<"}{"<<anm << "}\n";
         string abm = midgard_CG::waffe_werte(waffe_besitz[j],werte,"WM_Abwehr");
cout << "\\sbox{\\waffeV"<<b<<"}{"<<abm << "}\n";
       }
     }
   }
 // waffenloser Kampf:
 fout << "\\sbox{\\waffeEy"<<"}{"<<i_waffenlos+werte.bo_an << "}\n";
 string schaden=midgard_CG::waffe_werte("waffenloser Kampf",werte,"Schaden");
 fout << "\\sbox{\\waffeSy}{"<<schaden << "}\n";
 string anm = midgard_CG::waffe_werte("waffenloser Kampf",werte,"Angriffsrangmodifikation");
cout << "\\sbox{\\waffeAy}{"<<anm << "}\n";
 string abm = midgard_CG::waffe_werte("waffenloser Kampf",werte,"WM_Abwehr");
cout << "\\sbox{\\waffeVy}{"<<abm << "}\n";
 fout.close();
 system("latex midgard_tmp_document_eingabe.tex");
 system("dvips -t landscape midgard_tmp_document_eingabe.dvi");
 system("gv -seascape midgard_tmp_document_eingabe.ps &");

 // Zauber
 if (zauber.size()>0)
 {
    midgard_CG::LaTeX_zauber_main();
    midgard_CG::LaTeX_zauber();
    system("latex midgard_tmp_document_zauber.tex");
    system("dvips -t landscape midgard_tmp_document_zauber.dvi");
    system("gv -seascape midgard_tmp_document_zauber.ps &");
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