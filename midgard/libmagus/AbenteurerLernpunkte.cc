// $Id: AbenteurerLernpunkte.cc,v 1.1 2003/08/02 22:29:02 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#include "AbenteurerLernpunkte.hh"
#include "Abenteurer.hh"
#include <Misc/itos.h>
#include "Ausgabe.hh"

void AbenteurerLernpunkte::ruestung_auswaehlen(int wprozent)
	// on_button_ruestung_clicked(int wurf)
{
  std::string rue;
  if (a.Typ1()->Ruestung() == 1)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "TR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "TR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "LR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "LR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "LR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "LR" ;
   }
  if (a.Typ1()->Ruestung()== 2)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "TR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "LR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "LR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "KR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "KR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "KR" ;
   }
  if (a.Typ1()->Ruestung()== 3)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "TR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "LR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "KR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "KR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "KR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "PR" ;
   }
  if (a.Typ1()->Ruestung()== 4)
   {
      if ( 1 <= wprozent && wprozent  <= 10 ) rue = "OR" ;
      if (11 <= wprozent && wprozent  <= 20 ) rue = "OR" ;
      if (21 <= wprozent && wprozent  <= 30 ) rue = "OR" ;
      if (31 <= wprozent && wprozent  <= 60 ) rue = "TR" ;
      if (61 <= wprozent && wprozent  <= 80 ) rue = "TR" ;
      if (81 <= wprozent && wprozent  <= 95 ) rue = "LR" ;
      if (96 <= wprozent && wprozent  <= 100) rue = "LR" ;
   }
  if(a.Typ1()->Short()=="Fi") rue="KR";
  a.getWerte().setRuestung1(rue);
  Ausgabe(Ausgabe::Log, "Beim Auswürfeln der Rüstung wurde eine "+itos(wprozent)+" gewürfelt "
             "==> " + a.getWerte().Ruestung()->Long());
}

#if 0
void table_lernschema::beruf_gewuerfelt(int wurf)
{
  std::string kat=BKategorie.wuerfeln(wurf);
  Ausgabe(Ausgabe::ActionNeeded, kat);
}

void table_lernschema::on_beruf_tree_leaf_selected(Abenteurer &A, cH_Beruf b, const st_vorteil &v)
{
 try{
    cH_MidgardBasicElement cmbe(&*b);
    MBEmlt mbe(cmbe);
    a.List_Beruf().clear(); // es kann nur einen Beruf geben
    a.List_Beruf().push_back(mbe);

    bool zusatz = Beruf::Berufsfertigkeit(A,v);
    if(zusatz) 
     { cH_MidgardBasicElement cMBE(&*cH_Fertigkeit(v.name));
       MBEmlt MBE(cMBE);
       lernen_zusatz((*MBE)->ZusatzEnum(a.getVTyp()),MBE);
     }

    if (!BKategorie.kat_IV || (dt->getVorteil().kat==3 || dt->getVorteil().kat==4))
      {
      }
    else
      {
         BKategorie.kat_IV=false;
      }
 }catch(std::exception &e) {std::cerr << e.what()<<'\n';}
}

#endif
