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
#include "WindowInfo.hh"


void midgard_CG::spielleiter_export()
{
  string strinfo = "Datei 'spielleiter_export.txt' enth�lt nun die Daten des \n";
  strinfo +="Charakters im Format f�r Midgard Publikationen\n";
  manage (new WindowInfo(strinfo));
  ofstream fout("spielleiter_export.txt");
  fout << werte.name_charakter<<", "<<typ.l<<",   Grad "<<werte.grad<<"\n";
  fout << werte.stand<<", "<<werte.glaube<<" - ("<<werte.groesse<<"cm) - "
       << werte.alter<<" Jahre\n";
  fout << "\n";
  fout << "St "<<werte.st<<", Ge"<<werte.ge<<", Ko"<<werte.ko<<", In"<<werte.in
       << ", Zt"<<werte.zt<<", Au"<<werte.au<<", pA"<<werte.pa<<", Sb"<<werte.sb<<"\n";
  fout << werte.lp<<"LP, "<<werte.ap<<"AP - "<<werte.ruestung<<" - RW "
       << werte.rw<<", HGW "<<werte.hgw<<", B " << werte.b ;
  if (werte.bo_sc != 0 || werte.bo_ab != 0 || werte.bo_an != 0) fout <<" - ";
  if (werte.bo_sc != 0) fout << "SchB+"<<werte.bo_sc;
  if (werte.bo_sc != 0 || werte.bo_ab != 0 ) fout <<", ";
  if (werte.bo_ab != 0) fout << "AbB+"<<werte.bo_ab;
  if (werte.bo_an != 0) fout <<", AnB+" << werte.bo_sc;
  fout << "\n\n";
  fout << "Angriff: ";

 for (unsigned int i=0;i<vec_waffen.size();++i)
   {
    string wert = itos(vec_waffen[i].erfolgswert);
    for (unsigned int j=0; j<waffe_besitz.size();++j)
     {
      if (waffe_besitz[j].name==vec_waffen[i].name)
       {
         string waffenname ;
         waffenname = waffe_besitz[j].alias;
         fout <<waffenname ;
         if (waffe_besitz[j].av_bonus!=0 || waffe_besitz[j].sl_bonus!=0) fout <<"$^*$";
         int mag_schadensbonus = waffe_besitz[j].av_bonus;
         if (waffe_besitz[j].av_bonus==-5 && waffe_besitz[j].sl_bonus==-5) mag_schadensbonus = 0; 
         int anbo = werte.bo_an;
         if (midgard_CG::waffe_werte(waffe_besitz[j],werte,"Verteidigung")=="true")
            anbo = 0;
         int wert = vec_waffen[i].erfolgswert + anbo + mag_schadensbonus;
         fout << "+"<<wert << "(";
         string schaden=midgard_CG::waffe_werte(waffe_besitz[j],werte,"Schaden+mag_Bonus");
         fout << schaden << ")";
       }
      fout << ", ";
     }
   }

 fout <<" - Abwehr+"<<werte.abwehr_wert+werte.bo_ab <<", "
      <<"Resistenz+"<<werte.psyZR_wert+werte.bo_psy<<"/" 
                    <<werte.phsZR_wert+werte.bo_phs<<"/" 
                    <<werte.phkZR_wert+werte.bo_phk<<"\n\n" ;

 // angeborene Fertigkeiten
 for (unsigned int i=0;i<vec_an_fertigkeit.size();++i)
   {
    string wert = "+"+itos(vec_an_fertigkeit[i].erfolgswert);
    if (wert == "+0") wert = "";
    fout <<vec_an_fertigkeit[i].name << wert ;
    fout << ", ";
   }
 // Fertigkeiten
 for (unsigned int i=0;i<vec_fertigkeiten.size();++i)
   {
    string wert = "+"+itos(vec_fertigkeiten[i].erfolgswert);
    if (wert == "+0") wert = "";
    fout <<vec_fertigkeiten[i].name << wert ;
    if (i!=vec_fertigkeiten.size()-1) fout << ", ";
   }
 fout << " - ";
 for (unsigned int i=0; i<vec_sprachen.size();++i)
   {
      fout << vec_sprachen[i].name << " " << vec_sprachen[i].wert ;
      if (i!=vec_sprachen.size()-1) fout <<", ";
   }
  // Zauber
 if (zauber.size()!=0)
   {
     fout << "\n\n";
     fout << "Zaubern+"<<atoi(werte.zaubern_wert.c_str())+werte.bo_za<<": ";
     for (unsigned int i=0;i<zauber.size();++i)
      {
        fout << zauber[i].name ;
        if (i!=zauber.size()-1) fout << ", ";
      }
   }  
 fout << "\n";
}
