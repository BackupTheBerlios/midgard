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

// generated 2001/2/10 15:15:14 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Waffen_auswahl.cc_new

// This file is for your program, I won't touch it again!

#include "Berufe_auswahl.hh"
#include "midgard_CG.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include "zufall.h"

Berufe_auswahl::Berufe_auswahl(midgard_CG* h,  
  const midgard_CG::st_Database& _Database,
  const vector<cH_Typen>& _Typ,
  const Grundwerte& _Werte)
:  Typ(_Typ),Database(_Database),  Werte(_Werte)
{
  hauptfenster=h;
}

void Berufe_auswahl::on_button_wuerfel_clicked()
{
 Random random;
 int wurf=random.integer(1,100);
 label_wuerfel->set_text("Würfelergebnis: "+itos(wurf));
 std::string kat;
 bool kat_I=false, kat_II=false, kat_III=false, kat_IV=false;
 if(wurf<=20) kat="Kein(e) Beruf/Fertigkeit wählbar";
 if(21<=wurf&&wurf<=50)
  { kat="Eine Fertigkeit aus der Kategorie I wählbar"; 
    kat_I=true; }
 if(51<=wurf&&wurf<=80)
  { kat="Eine Fertigkeit aus der Kategorie I oder II wählbar"; 
    kat_I=true; 
    kat_II=true;}
 if(81<=wurf&&wurf<=95)
  { kat="Ein Fertigkeit aus der Kategorie I,II oder III wählbar"; 
    kat_I=true; 
    kat_II=true;
    kat_III=true;}
 if(81<=wurf&&wurf<=95)
  { kat="Ein Fertigkeit aus der Kategorie III oder IV \n oder zwei aus den Kategorien I und II wählbar"; 
    kat_I=true; 
    kat_II=true;
    kat_III=true;
    kat_IV=true; }

 label_kategorie->set_text(kat);
 fill_list();
}

void Berufe_auswahl::fill_list()
{
  Gtk::OStream os(berufe_clist_auswahl);
  berufe_clist_auswahl->freeze();
  
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Beruf.begin();i!=Database.Beruf.end();++i)
   {
     cH_Beruf b(*i);
     if (hauptfenster->region_check(b->Region()))
         list_beruf.push_back(*i);
   }
  list_beruf.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
  for(std::list<cH_MidgardBasicElement>::iterator i=list_beruf.begin();i!=list_beruf.end();++i)
     {
      std::vector<string> fert=cH_Beruf(*i)->Vorteile();
      for(std::vector<string>::const_iterator j=fert.begin();j!=fert.end();++j)
       {
         int kat;
         if(*j=="Schmecken+10") kat=1;
         else kat=cH_Fertigkeit(*j)->Berufskategorie();
         os << kat <<"\t"<<(*i)->Name()<<'\t'<< *j<<"\n";
       }
     }
  for (unsigned int i=0;i<berufe_clist_auswahl->columns().size();++i)
    berufe_clist_auswahl->set_column_auto_resize(i,true);

//  berufe_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
//  berufe_clist_auswahl->set_reorderable(true);
  berufe_clist_auswahl->thaw();
}


void Berufe_auswahl::on_berufe_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{   
// << static_cast<MidgardBasicElement*>(berufe_clist_auswahl->get_user_data())->Name() <<'\n';
//         berufe_clist_auswahl->row(row).unselect();

//  std::string beruf= static_cast<MidgardBasicElement*>(berufe_clist_auswahl->get_user_data())->Name();
  std::string beruf=berufe_clist_auswahl->get_text(row,1);
  std::string fert=berufe_clist_auswahl->get_text(row,2);
  std::list<cH_MidgardBasicElement> saf;
//  sab.push_back(cH_MidgardBasicElement(new Beruf(beruf)));  
  saf.push_back(cH_MidgardBasicElement(new Fertigkeit(fert)));  
  cH_MidgardBasicElement mbe(new Beruf(beruf));
  hauptfenster->MidgardBasicElement_uebernehmen(mbe);
  hauptfenster->MidgardBasicElement_uebernehmen(saf);
  destroy();
}

void Berufe_auswahl::on_berufe_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{   
}

void Berufe_auswahl::on_close_berufe_clicked(void)
{
}

