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


Berufe_auswahl::Berufe_auswahl(midgard_CG* h,  
  const midgard_CG::st_Database& Database,
  const vector<cH_Typen>& Typ,
  int lernpunkte, const Grundwerte& Werte)
{
  hauptfenster=h;
  maxpunkte = lernpunkte;
  beruf_auswahl_lernpunkte->set_text(itos(maxpunkte));

  Gtk::OStream os(berufe_clist_auswahl);
  berufe_clist_auswahl->freeze();
  
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Beruf.begin();i!=Database.Beruf.end();++i)
   {
     cH_Beruf b(*i);
     (*i)->set_Lernpunkte(b->Lernpunkte());
//     if(!b->Voraussetzungen(Werte,Typ)) continue;
      if (hauptfenster->region_check(b->Region()))
        if(b->Lernpunkte()<=maxpunkte)
           list_beruf.push_back(*i);
   }
  list_beruf.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
  for(std::list<cH_MidgardBasicElement>::iterator i=list_beruf.begin();i!=list_beruf.end();++i)
     {
      cH_Beruf b(*i);
       {
         os << b->Lernpunkte()<<"\t"<<(*i)->Name()<<"\t"<<b->get_Vorteile()<<"\n";
         os.flush(&*i);
       }
     }
  for (unsigned int i=0;i<berufe_clist_auswahl->columns().size();++i)
    berufe_clist_auswahl->set_column_auto_resize(i,true);

  berufe_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
  berufe_clist_auswahl->set_reorderable(true);
  berufe_clist_auswahl->thaw();
}

void Berufe_auswahl::on_berufe_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{   
   if (maxpunkte < atoi(berufe_clist_auswahl->get_text(row,0).c_str() ))
      {
         berufe_clist_auswahl->row(row).unselect();
      }
   maxpunkte -= atoi(berufe_clist_auswahl->get_text(row,0).c_str());
   beruf_auswahl_lernpunkte->set_text(itos(maxpunkte));
}

void Berufe_auswahl::on_berufe_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{   
   maxpunkte += atoi(berufe_clist_auswahl->get_text(row,0).c_str());
   beruf_auswahl_lernpunkte->set_text(itos(maxpunkte));
}

void Berufe_auswahl::on_close_berufe_clicked()
{   
   std::list<cH_MidgardBasicElement> sab;
   for (Gtk::CList::SelectionList::iterator i=berufe_clist_auswahl->selection().begin();
         i!=berufe_clist_auswahl->selection().end();++i)
     {  
      cH_MidgardBasicElement *ptr = static_cast<cH_MidgardBasicElement*>(i->get_data());
         // ptr=&fert[i->get_row_num()];
//       sab.push_back(new Data_beruf((*ptr)->Name(),(*ptr)->Vorteile(),0));
      sab.push_back(*ptr);
     }
//  hauptfenster->berufe_uebernehmen(sab);
  hauptfenster->MidgardBasicElement_uebernehmen(sab);
  destroy();

}

/*
bool Berufe_auswahl::berufe_voraussetzung(const std::string& beruf, const Grundwerte& Werte, const std::string& typz, const std::string& typ2z)
{
  exec sql begin declare section;
   int db_st,db_ge,db_ko,db_in,db_zt,db_pa,db_au,db_sb;
   char db_geschlecht[5];
   char db_typ[5];
   char db_region[10];
   char db_beruf[30];
  exec sql end declare section;
  strncpy(db_beruf,beruf.c_str(),sizeof(db_beruf));

  exec sql select coalesce(st,'0'), coalesce(ge,'0'),
   coalesce(ko,'0'),  coalesce("in",'0'), coalesce(zt,'0'),
   coalesce(typ,'0'), coalesce(pa,'0'), coalesce(au,'0'), coalesce(sb,'0'),
   coalesce(geschlecht,''), coalesce(region,'')
   into :db_st,:db_ge,:db_ko,:db_in,:db_zt,:db_typ,:db_pa,:db_au,
      :db_sb,:db_geschlecht,:db_region
   from berufe_voraussetzung where beruf= :db_beruf limit 1;
  SQLerror::test(__FILELINE__);
//std::cout << beruf<<"\t->"<<db_typ<<"<-\t";
  std::string geschlecht = db_geschlecht;
//std::cout << "->"<<geschlecht<<"<- ->"<<Werte.Geschlecht()<<"<-\n";
  if (   db_st<=Werte.St() &&
         db_ge<=Werte.Ge() &&
         db_ko<=Werte.Ko() &&
         db_in<=Werte.In() &&
         db_zt<=Werte.Zt() &&
         db_pa<=Werte.pA() &&
         db_au<=Werte.Au() &&
         db_sb<=Werte.Sb() &&
         (geschlecht==Werte.Geschlecht() || geschlecht == "") &&
         Berufe_auswahl::btyp(db_typ,typz,typ2z) &&
         hauptfenster->region_check(db_region)
     )   
   return true;
  else return false ;
}
*/

bool Berufe_auswahl::btyp(const std::string& typ, const std::string& typz, const std::string& typ2z)
{
//std::cout <<"\t"<<typz<<"\t";
 if (typ2z!="") return true; // Doppelklassencharakter 
 bool r;
 if       (typ=="z" && typz=="z") r=true;
 else if  (typ=="k" && typz=="n") r=true; 
 else if  (typ=="k" && typz=="j") r=true; 
 else if  (typ=="0") r=true;
 else r = false;
//std::cout << r<<"\n";
 return r;
}
/*
std::string Berufe_auswahl::Beruf_vorteile(const std::string& beruf)
{
  exec sql begin declare section;
   char db_beruf[30];
   char db_vorteile[30][30];
  exec sql end declare section;
  strncpy(db_beruf,beruf.c_str(),sizeof(db_beruf));
  exec sql select coalesce(vorteil,'') into :db_vorteile from berufe_vorteile
      where beruf = :db_beruf;
  SQLerror::test(__FILELINE__,100);
  std::string vorteile;
  for (int i=0;i<sqlca.sqlerrd[2];++i)  
   {
     vorteile += db_vorteile[i];
     if (i!=sqlca.sqlerrd[2]-1) vorteile += ", ";
   }
//std::cout << db_beruf<<"\t"<<vorteile<<"\n";
  return vorteile;
}
*/
