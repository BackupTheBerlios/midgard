// $Id: LaTeX_out.cc,v 1.106 2002/03/04 18:25:33 thoma Exp $
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
#include "Sprache.hh"
#include "Waffe.hh"
#include <fstream>
#include "Fertigkeiten_angeboren.hh"

gint midgard_CG::on_latex_release_event(GdkEventButton *ev)
{
  if (ev->button==1) on_latex_clicked();
//  if (ev->button==3) midgard_CG::spielleiter_export();
  return false;
}


void midgard_CG::on_latex_clicked(bool values=true)
{   
 system("rm midgard_tmp_myzauber.tex midgard_tmp_mykido.tex");
 if (!access("document_eingabe4.tex",R_OK)) // Files im aktuellen Verzeichnis?
    system("cp document_eingabe4.tex midgard_tmp_document_eingabe.tex");
 else
    system("cp "PACKAGE_DATA_DIR"document_eingabe4.tex midgard_tmp_document_eingabe.tex");

 if (values) LaTeX_write_values();
 else LaTeX_write_empty_values();

 if (list_Zauber.size()>0 || list_Zauberwerk.size()>0)  // Zauber
  {
    LaTeX_zauber_main();
    LaTeX_zauber();
    LaTeX_zaubermittel();
  }
 if (list_Kido.size()>0) // KiDo
  {
    LaTeX_kido_main();
    LaTeX_kido();
  }

 system("pdflatex midgard_tmp_document_eingabe.tex");
 if(pdfViewerCheck(gv).active)
    system("gv midgard_tmp_document_eingabe.pdf &");
 else if (pdfViewerCheck(acroread).active)
    system("acroread midgard_tmp_document_eingabe.pdf &");
}      

void midgard_CG::LaTeX_write_values()
{
 ofstream fout("midgard_tmp_latexwerte.tex");
 std::string styp = Typ[0]->Name(Werte.Geschlecht());
 if (Typ[1]->Name(Werte.Geschlecht())!="") 
      styp += "/"+Typ[1]->Name(Werte.Geschlecht());
 fout << "\\newcommand{\\typ}{"<< LaTeX_scale(styp,10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\st}{"  <<Werte.St() << "}\n";
 fout << "\\newcommand{\\gs}{" <<Werte.Gs() << "}\n";
 fout << "\\newcommand{\\gw}{"  << Werte.Gw() ;
  if( Werte.Ruestung()->RW_Verlust() )
    fout << "\\scriptsize ("<<Werte.Gw()-Werte.Ruestung()->RW_Verlust()<<")";
 fout << "}\n";
 fout << "\\newcommand{\\ko}{"  <<Werte.Ko()<< "}\n";
 fout << "\\newcommand{\\inn}{" <<Werte.In() << "}\n";
 fout << "\\newcommand{\\zt}{"  <<Werte.Zt() << "}\n";
 fout << "\\newcommand{\\au}{"  <<Werte.Au() << "}\n";
 fout << "\\newcommand{\\pa}{"  <<Werte.pA() << "}\n";
 fout << "\\newcommand{\\sbb}{"  <<Werte.Sb() << "}\n";
 fout << "\\newcommand{\\wk}{"  <<Werte.Wk() << "}\n";
 fout << "\\newcommand{\\rw}{ X }\n";
 fout << "\\newcommand{\\hgw}{ X }\n";
 fout << "\\newcommand{\\bb}{"  <<Werte.B() ;
 if(Werte.Ruestung()->B_Verlust())
   fout << "\\scriptsize ("<<Werte.B() - Werte.Ruestung()->B_Verlust()<<")";
 fout << "}\n";
 fout << "\\newcommand{\\kaw}{"  <<Werte.KAW() << "}\n";
 fout << "\\newcommand{\\geistesblitz}{"  <<Werte.Geistesblitz() << "}\n";
 fout << "\\newcommand{\\ggn}{"  <<Werte.GG() << "}\n";
 fout << "\\newcommand{\\sg}{"  <<Werte.SG() << "}\n";
 fout << "\\newcommand{\\lp}{"  <<Werte.LP() << "}\n";
 fout << "\\newcommand{\\ap}{"  <<Werte.AP() << "}\n";
 fout << "\\newcommand{\\boau}{"<<Werte.bo_Au()<< "}\n";
 fout << "\\newcommand{\\bosc}{"<<Werte.bo_Sc()<< "}\n";
 fout << "\\newcommand{\\boan}{"<<Werte.bo_An()<< "}\n";
 fout << "\\newcommand{\\boab}{"<<Werte.bo_Ab()<< "}\n";
 fout << "\\newcommand{\\boza}{"<<Werte.bo_Za()<< "}\n";
 fout << "\\newcommand{\\bopsy}{"<<Werte.bo_Psy(Typ)<< "}\n";
 fout << "\\newcommand{\\bophs}{"<<Werte.bo_Phs(Typ)<< "}\n";
 fout << "\\newcommand{\\bophk}{"<<Werte.bo_Phk(Typ)<< "}\n";

 // Sinne
 fout << "\\newcommand{\\sinnse}{"<<Werte.Sehen()<< "}\n";
 fout << "\\newcommand{\\sinnh}{"<<Werte.Hoeren()<< "}\n";
 fout << "\\newcommand{\\sinnr}{"<<Werte.Riechen()<< "}\n";
 fout << "\\newcommand{\\sinnsc}{"<<Werte.Schmecken()<< "}\n";
 fout << "\\newcommand{\\sinnt}{"<<Werte.Tasten()<< "}\n";
 fout << "\\newcommand{\\sinnss}{"<<Werte.SechsterSinn()<< "}\n";
 
 fout << "\\newcommand{\\hand}{"<<Werte.Hand()<< "}\n";



// fout << "\\newcommand{\\bogi}{ X }\n";
 fout << "\\newcommand{\\res}{"<<Werte.Resistenz()<<"}\n";
 fout << "\\newcommand{\\psy}{"<<Werte.Resistenz()+Werte.bo_Psy(Typ)<<"}\n";
 fout << "\\newcommand{\\ppresistenz}{"<<EmptyInt_4TeX(Werte.ResistenzPP())<<"}\n";
 fout << "\\newcommand{\\phs}{"<<Werte.Resistenz()+Werte.bo_Phs(Typ)<<"}\n";
 fout << "\\newcommand{\\phk}{"<<Werte.Resistenz()+Werte.bo_Phk(Typ)<<"}\n";
// fout << "\\newcommand{\\gift}{"<<3*Werte.LP()+Werte.bo_Gift()+ Spezies_constraint.Gift()<<"}\n";
 fout << "\\newcommand{\\gift}{"<<Werte.Gift()<<"}\n";

 fout << "\\newcommand{\\raufen}{"<<Werte.Raufen()<< "}\n";
 fout << "\\newcommand{\\abwehr}{"<<Werte.Abwehr_wert()<< "}\n";
 fout << "\\newcommand{\\ppabwehr}{"<<EmptyInt_4TeX(Werte.AbwehrPP())<< "}\n";
 int ohne_waffe=Werte.Abwehr_wert()+Werte.bo_Ab();
 int abwehr_verlust = Werte.Ruestung()->AbwehrBonus_Verlust(Werte.bo_Ab());
 if(!cH_Fertigkeit("Kampf in Vollrüstung")->ist_gelernt(list_Fertigkeit) &&
      Werte.Ruestung()->VollRuestungsAbzug()!=0)
   abwehr_verlust += abs(Werte.Ruestung()->VollRuestungsAbzug());
 std::string abwehr_verlust_string;
 if(abwehr_verlust) abwehr_verlust_string="--"+itos(abs(abwehr_verlust)); 
 fout << "\\newcommand{\\abwehrfinal}{"<<ohne_waffe<<abwehr_verlust_string<<"}\n";

 std::string mit_waffe = Waffe::get_Verteidigungswaffe(ohne_waffe,list_Waffen,list_Waffen_besitz,Typ,Werte);
 fout << "\\newcommand{\\abwehrmitwaffe}{"<<mit_waffe<<abwehr_verlust_string<<"}\n";

 fout << "\\newcommand{\\zauber}{"<<EmptyInt_4TeX(Werte.Zaubern_wert())<< "}\n";
 fout << "\\newcommand{\\ppzauber}{"<<EmptyInt_4TeX(Werte.ZaubernPP())<< "}\n";
 fout << "\\newcommand{\\alter}{"  <<Werte.Alter() << "}\n";
 fout << "\\newcommand{\\gestalt}{"  <<LaTeX_scale(Werte.Gestalt(),5,"0.7cm") << "}\n";
 fout << "\\newcommand{\\gewicht}{"  <<Werte.Gewicht() << "\\,kg}\n";
 fout << "\\newcommand{\\koerpergroesse}{"  <<Werte.Groesse()/100. << "\\,m}\n";
 fout << "\\newcommand{\\koerpergroessebez}{"  <<Werte.GroesseBez() << "}\n";
 fout << "\\newcommand{\\grad}{"  <<Werte.Grad() << "}\n";
 fout << "\\newcommand{\\spezialisierung}{ "  <<LaTeX_scale(Werte.Spezialisierung(),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\stand}{"  <<LaTeX_scale(Werte.Stand(),10,"1.5cm") << "}\n";
 fout << "\\newcommand{\\herkunft}{"  <<LaTeX_scale(Werte.Herkunft()->Name(),10,"2.2cm") << "}\n";
 fout << "\\newcommand{\\glaube}{"  <<LaTeX_scale(Werte.Glaube(),10,"2.5cm") << "}\n";
 fout << "\\newcommand{\\namecharakter}{" << LaTeX_scale(Werte.Name_Abenteurer(),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\namespieler}{" << LaTeX_scale(Werte.Name_Spieler(),25,"4.5cm") << "}\n";
 fout << "\\newcommand{\\gfp}{\\tiny "  <<EmptyInt_4TeX(Werte.GFP()) << "}\n";
 fout << "\\newcommand{\\aep}{\\tiny "  <<EmptyInt_4TeX(Werte.KEP()) << "}\n";
 fout << "\\newcommand{\\kep}{\\tiny "  <<EmptyInt_4TeX(Werte.ZEP()) << "}\n";
 fout << "\\newcommand{\\zep}{\\tiny "  <<EmptyInt_4TeX(Werte.AEP()) << "}\n";

 double geld = Werte.Gold() + Werte.Silber()/10. + Werte.Kupfer()/100.;
 fout << "\\newcommand{\\gold}{\\tiny "  << geld << "}\n";

 fout << "\\newcommand{\\ruestung}{\\scriptsize "  <<Werte.Ruestung()->Name() << "}\n";
// fout << "\\newcommand{\\ruestunglp}{\\scriptsize "  <<midgard_CG::ruestung("LP") << "}\n";
 fout << "\\newcommand{\\ruestunglp}{\\scriptsize "  <<Werte.Ruestung()->LP_Verlust() << "}\n";

 /////////////////////////////////////////////////////////////////////////////
 // Sprachen und Schriften
 unsigned int sprachanz=0;
 unsigned int maxsprach=23;
 std::list<cH_MidgardBasicElement> verwandteSprachen;
 for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Sprache.begin();i!=list_Sprache.end();++i)
   {  cH_Sprache s(*i);
      std::list<cH_MidgardBasicElement> tmplist=s->VerwandteSprachen(list_Sprache,Database.Sprache);
      verwandteSprachen.splice(verwandteSprachen.end(),tmplist);
//geht nicht!!!      verwandteSprachen.splice(verwandteSprachen.end(),s->VerwandteSprachen(list_Sprache,Database.Sprache));
      std::string a = LaTeX_string(sprachanz++);
      fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << LaTeX_scale(s->Name(),20,"2.6cm") <<"}\n";
      fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize +"<< s->Erfolgswert() <<"}\n";
      vector<pair<std::string,int> > vs=s->SchriftWert(list_Schrift);
      std::string ss;
      for(vector<pair<std::string,int> >::const_iterator j=vs.begin();j!=vs.end();)
       {
         ss+= j->first + "(+"+itos(j->second)+")";
         if(++j!=vs.end())  ss+=", ";
       }
      fout << "\\newcommand{\\schr"<<a<<"}{\\scriptsize "<< LaTeX_scale(ss,20,"2.6cm") <<"}\n";
   }
 verwandteSprachen=Sprache::cleanVerwandteSprachen(verwandteSprachen);
 for(std::list<cH_MidgardBasicElement>::const_iterator i=verwandteSprachen.begin();i!=verwandteSprachen.end();++i)
   { cH_Sprache s(*i);
     if(s->ist_gelernt(list_Sprache)) continue;
     std::string a = LaTeX_string(sprachanz++);
     fout << "\\newcommand{\\spra"<<a<<"}{\\scriptsize " << LaTeX_scale(s->Name(),20,"2.6cm") <<"}\n";
     fout << "\\newcommand{\\spraw"<<a<<"}{\\scriptsize (+"<< s->Erfolgswert() <<")}\n";
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
 for (std::list<cH_MidgardBasicElement>::const_iterator i=list_WaffenGrund.begin();i!=list_WaffenGrund.end();++i)
   {
      std::string sout = (*i)->Name();
      if (sout =="Bögen") sout = "Bogen";
      if (sout =="Wurfspieß") sout = "Wurfspiess";
      if (sout =="Spießwaffe") sout = "Spiesswaffe";
      if (sout =="Kampf ohne Waffen") sout = "KampfohneWaffen";
      fout << "\\sbox{\\"<<sout<<"}{\\tiny X}\n";
   }

 /////////////////////////////////////////////////////////////////////////////
 // Beruf
 fout << "\\newcommand{\\beruf}{" ;
 for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Beruf.begin();
         i!=list_Beruf.end();++i)
   {
     fout << (*i)->Name(); //<<" ("<<(*i)->Erfolgswert()<<")\t";
   }
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // weitere Merkmale
 fout << "\\newcommand{\\merkmale}{" ;
 if(Werte.Spezies()->Name()!="Mensch") 
     fout << Werte.Spezies()->Name(); 
 fout <<"}\n";
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten & Waffen
 /////////////////////////////////////////////////////////////////////////////
 // angeborene Fertigkeiten
 int count=0;
 for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit_ang.begin();i!=list_Fertigkeit_ang.end();++i) 
   {cH_Fertigkeit_angeborene f(*i);
    std::string a = LaTeX_string(count);
    count++;
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<f->Name() << "}   ";
    // Praxispunkte
    std::string pp = itos(f->Praxispunkte());
    if (pp == "0") pp = "";
    fout << "\\newcommand{\\praxis"<<a<<"}{"  << pp << "}   ";
    // Erfolgswert
    std::string wert = itos(f->FErfolgswert(Werte));
    if (wert == "0") wert = "";
    fout << "\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
   }
 /////////////////////////////////////////////////////////////////////////////
 // Fertigkeiten
 for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i) 
   {cH_Fertigkeit f(*i);
    std::string a = LaTeX_string(count);
    count++;
    std::string wert = itos(f->Erfolgswert());
    if (wert == "0") wert = "";
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<f->Name()<<
      ' '<<f->Zusatz() << "}\t\t";
    // Praxispunkte
    std::string pp = itos(f->Praxispunkte());
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
 int  i_waffenlos = 4;
 unsigned int countwaffen=0;
 int angriffsverlust = abs(Werte.Ruestung()->AngriffsBonus_Verlust(Werte.bo_An()));
 // Abzug, wenn in Vollrüstung gekämpft wird, obwohl die
 // entsprechende Fertigkeit nicht beherrscht wird.
 if(!cH_Fertigkeit("Kampf in Vollrüstung")->ist_gelernt(list_Fertigkeit))
       angriffsverlust += Werte.Ruestung()->VollRuestungsAbzug();
 std::string angriffsverlust_string;
 if (angriffsverlust) angriffsverlust_string="--"+itos(angriffsverlust);            
 for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen.begin();i!=list_Waffen.end();++i)
   {cH_Waffe w(*i);
    count++;
    std::string a = LaTeX_string(count);
//std::cout << "latexstring = "<<a<<"\n";
    std::string wert = itos(w->Erfolgswert());
    fout <<"\\newcommand{\\fert"<<a<<"}{\\scriptsize "  <<w->Name() << "}\t\t";
    // Praxispunkte
    std::string pp = itos(w->Praxispunkte());
    if (pp == "0") pp = "";
    fout << "\\newcommand{\\praxis"<<a<<"}{"  << pp << "}   ";
    fout <<"\\newcommand{\\wert"<<a<<"}{"  <<wert << "}\n";
    // waffenloser Kampf:
    if (w->Name()=="waffenloser Kampf") 
         { i_waffenlos=atoi(wert.c_str());}
      for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Waffen_besitz.begin();j!=list_Waffen_besitz.end();++j)
     {
      cH_WaffeBesitz WB(*j);
      if (WB->Waffe()->Name()==w->Name())
       {
         std::string b = LaTeX_string(countwaffen++);
//std::cout << (*j)->Name()<<"\t"<<w->Name()<<"\t"<<"latexstring = "<<b<<"\n";
         std::string waffenname ;
         waffenname = WB->Name();
         fout << "\\newcommand{\\waffe"<<b<<"}{ " ;
         if (WB->Magisch()!="" || 
            (WB->av_Bonus()!=0 && WB->sl_Bonus()!=0)) waffenname+="$^*$ "+WB->Bonus() ;
         fout <<LaTeX_scalemag(waffenname,20,"3cm",WB->Magisch(),WB->Waffe()->Reichweite())<< "}\n";
         
         // Erfolgswert für einen Verteidigungswaffen
         if (WB->Waffe()->Verteidigung())
          {
           int wert = (*i)->Erfolgswert() + WB->av_Bonus() + WB->Waffe()->WM_Angriff(WB->Name()) ;
           fout << "\\newcommand{\\waffeE"<<b<<"}{"<<itos(wert)<<"}\n";
          }
         // Erfolgswert für Angriffswaffen
         else 
          {
           int wert = (*i)->Erfolgswert() + Werte.bo_An() + WB->av_Bonus() + WB->Waffe()->WM_Angriff(WB->Name()) ;
           // Angriffsbonus subtrahieren, wenn schwere Rüstung getragen wird:
           fout << "\\newcommand{\\waffeE"<<b<<"}{"<<wert<<angriffsverlust_string<<"}\n";
          }
         std::string schaden=WB->Schaden(Werte,WB->Name());
         fout << "\\newcommand{\\waffeS"<<b<<"}{"<<schaden << "}\n";
         std::string anm = WB->Waffe()->Waffenrang();
         fout << "\\newcommand{\\waffeA"<<b<<"}{"<<anm << "}\n";
         std::string abm = WB->Waffe()->WM_Abwehr();
         fout << "\\newcommand{\\waffeV"<<b<<"}{"<<abm << "}\n";
       }
     }
   }
 // waffenloser Kampf:
 cH_MidgardBasicElement waffenlos(new WaffeBesitz(cH_Waffe("waffenloser Kampf"),"waffenloser Kampf","",0,0,""));
 fout << "\\newcommand{\\waffeEy"<<"}{"<<i_waffenlos+Werte.bo_An() << "}\n";
 std::string schaden= cH_WaffeBesitz(waffenlos)->Schaden(Werte, waffenlos->Name());
 fout << "\\newcommand{\\waffeSy}{"<<schaden << "}\n";
 std::string anm = cH_WaffeBesitz(waffenlos)->Waffe()->Waffenrang();
 fout << "\\newcommand{\\waffeAy}{"<<anm << "}\n";
 std::string abm = cH_WaffeBesitz(waffenlos)->Waffe()->WM_Abwehr();
 fout << "\\newcommand{\\waffeVy}{"<<abm << "}\n";
 /////////////////////////////////////////////////////////////////////////
 // Universelle Fertigkeiten
 std::list<cH_MidgardBasicElement> UF;
 for(std::list<cH_MidgardBasicElement>::iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
  {
    cH_Fertigkeit f(*i);
    if(f->Ungelernt()!=-99)
       UF.push_back(*i);
  }
 cH_MidgardBasicElement werfen(&*cH_Waffe("Werfen")); 
 UF.push_back(werfen);
 UF.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
 int countunifert=0;
 for(std::list<cH_MidgardBasicElement>::iterator i=UF.begin();i!=UF.end();++i)
  {
    std::string a = LaTeX_string(countunifert);
    std::string name = (*i)->Name();
    std::string wert;
    bool voraussetzung=true;
    if ((*i)->What()==MidgardBasicElement::FERTIGKEIT) 
      { cH_Fertigkeit f(*i);
        int iwert = f->Ungelernt();
        if (!f->Voraussetzungen(Werte)) {iwert-=2; voraussetzung=false;}
        if   (iwert>=0) wert = "+"+itos(iwert);
        else            wert = "--"+itos(abs(iwert));

        if(name=="Geheimmechanismen öffnen") name = "Geheimmech. öffnen";
        if(name=="Landeskunde (Heimat)") name = "Landeskunde ("+Werte.Herkunft()->Name()+")";
      }
    else if ((*i)->What()==MidgardBasicElement::WAFFE)    
      { cH_Waffe f(*i);
        int iwert = 4+Werte.bo_An();
        if (!f->SG_Voraussetzung(Werte)) {iwert=0; voraussetzung=false;}
        if   (iwert>=0) wert = "+"+itos(iwert);
        else            wert = "--"+itos(abs(iwert));
      }

    if ((*i)->ist_gelernt(list_Fertigkeit) || (*i)->ist_gelernt(list_Waffen))
     {
//       fout <<"\\newcommand{\\uni"<<a<<"}{("<<name<< "}\t\t";
//       fout << "\\newcommand{\\uniw"<<a<<"}{"  <<wert << ")}\n";
     }
    else
     {
       ++countunifert;
       fout <<"\\newcommand{\\uni"<<a<<"}{"<<name<< "}\t\t";
       if (voraussetzung)
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
 unsigned int maxwaffen=8;
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
 fout.close();

}


void midgard_CG::LaTeX_write_empty_values()
{
 ofstream fout("midgard_tmp_latexwerte.tex");
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
 for(std::list<cH_MidgardBasicElement>::iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
  {
    cH_Fertigkeit f(*i);
    if(f->Ungelernt()!=-99)
       UF.push_back(*i);
  }
 cH_MidgardBasicElement werfen(&*cH_Waffe("Werfen")); 
 UF.push_back(werfen);
 UF.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
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
 fout.close();
}



std::string midgard_CG::LaTeX_scale(const std::string& is, 
      unsigned int maxlength, const std::string& scale)
{
 std::string os;
 if (is.size() <= maxlength) os = is;
 else  os = "\\resizebox*{"+scale+"}{1.5ex}{"+is+"}" ;
 return os;
}

std::string midgard_CG::LaTeX_scalemag(const std::string& is, 
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
