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

// generated 2001/2/8 11:08:32 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Fertigkeiten_auswahl.cc_new

// This file is for your program, I won't touch it again!

#include "Fertigkeiten_auswahl.hh"
#include "midgard_CG.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include "Sprache_auswahl.hh"
//#include "Ausnahmen.hh"
#include "Pflicht.hh"

Fertigkeiten_auswahl::Fertigkeiten_auswahl(midgard_CG* h,const midgard_CG::st_Database& dat,const vector<cH_Typen>& Typ,
     int lernpunkte, const Grundwerte& Werte,const std::vector<H_Data_beruf>& vec_Beruf)
: Database(dat)
{
  hauptfenster=h;
  maxpunkte = lernpunkte;
  fert_auswahl_lernpunkte->set_text(itos(maxpunkte));
  // Berufsvorteile
  std::vector<string> vorteile=hauptfenster->Berufs_Vorteile();

  // Lernschema //////////////////////////////////////////////////////////////
  std::list<cH_MidgardBasicElement> LW=Database.lernschema.get_List("Fertigkeit",Typ);
cout << LW.size()<<'\n';
  for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
   {
      if (!Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
      cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert0());
      list_Fert.push_back(*i);
   }
  //Speziesspezifische Fertigkeit und andere Fertigkeiten
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
     if(Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::LERNPUNKTE))
      {
        int erf=Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::ERFOLGSWERT);
        cH_Fertigkeit(*i)->set_Erfolgswert(erf);
        list_Fert_spez.push_back(*i);       
      }
     else //andere Fertigkeiten
      {
        for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Fert.begin();j!=list_Fert.end();++j)
         {
           if((*j)->Name()==(*i)->Name()) continue;
           cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert0());
           list_allg_Fert.push_back(*i);
         }
      }
   }
cout << list_allg_Fert.size()<<'\t'<<list_Fert.size()<<'\n';

   Gtk::OStream os(fertigkeiten_clist_auswahl);
   fertigkeiten_clist_auswahl->freeze();
   // Speziesspezifische Fertigkeiten
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_spez.begin();i!=list_Fert_spez.end();++i)
      { cH_Fertigkeit f(*i);
        int v=0;
        for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
            if ((*j)==f->Name()) v=1;
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ((f->Voraussetzungen(Werte) || Werte.Spezies()->Name()!="Mensch") &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name(),true))
         { os << f->Lernpunkte()-v <<"\t"<<f->Voraussetzung()<<"\t"<<f->Pflicht()<<"\t"<<f->Name()<<"\t"
               << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
            os.flush(&*i);
         }
      }
   // Lernschema
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert.begin();i!=list_Fert.end();++i)
      { cH_Fertigkeit f(*i);
        int v=0;
        for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
            if ((*j)==f->Name()) v=1;
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ((f->Voraussetzungen(Werte) || Werte.Spezies()->Name()!="Mensch") &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name(),true))
         { 
            Lernschema::st_index I(Typ[0]->Short(),"Fertigkeit",f->Name());
            os << Database.lernschema.get_Lernpunkte(I)-v <<"\t"<<f->Voraussetzung()<<"\t*\t"<<f->Name()<<"\t"
               << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
            os.flush(&*i);
         }
      }
   // andere Fertigkeiten ////////////////////////////////////////////////
   os <<"\n\n";   
   for(std::list<cH_MidgardBasicElement>::iterator i=list_allg_Fert.begin();i!=list_allg_Fert.end();++i)
      { cH_Fertigkeit f(*i);
        int v=0;
        for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
           if ((*j)==f->Name()) v=1;
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ( f->Voraussetzungen(Werte) && 
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name()))
         { os << f->Lernpunkte()-v<<"\t"<<f->Voraussetzung()<<"\t"<<""<<"\t"<<f->Name()<<"\t"
              << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
           os.flush(&*i);
         }
      }

   for (unsigned int i=0;i<fertigkeiten_clist_auswahl->columns().size();++i)
      fertigkeiten_clist_auswahl->set_column_auto_resize(i,true);

   fertigkeiten_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
   fertigkeiten_clist_auswahl->set_reorderable(true);
   fertigkeiten_clist_auswahl->thaw();
}

void Fertigkeiten_auswahl::on_close_fertigkeiten_clicked()
{
   std::list<cH_MidgardBasicElement> saf;
   for (Gtk::CList::SelectionList::iterator i=fertigkeiten_clist_auswahl->selection().begin();
         i!=fertigkeiten_clist_auswahl->selection().end();++i)
     {  
      cH_MidgardBasicElement *ptr = static_cast<cH_MidgardBasicElement*>(i->get_data());
      saf.push_back(*ptr);
     }
  hauptfenster->MidgardBasicElement_uebernehmen(saf);
  destroy();
}


void Fertigkeiten_auswahl::on_fertigkeiten_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{
   if (maxpunkte < atoi(fertigkeiten_clist_auswahl->get_text(row,0).c_str() ))
      {
         fertigkeiten_clist_auswahl->row(row).unselect();
      }
   maxpunkte -= atoi(fertigkeiten_clist_auswahl->get_text(row,0).c_str());
   fert_auswahl_lernpunkte->set_text(itos(maxpunkte));
   // Sprache oder Schrift?
   std::string fert = fertigkeiten_clist_auswahl->get_text(row,3);
   if (fert == "Sprache" || fert == "Lesen/Schreiben" )
    {
      if (maxpunkte >=  atoi(fertigkeiten_clist_auswahl->get_text(row,0).c_str() ))
         manage (new Sprache_auswahl(hauptfenster,Database,fert));
    }
}

void Fertigkeiten_auswahl::on_fertigkeiten_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{
   maxpunkte += atoi(fertigkeiten_clist_auswahl->get_text(row,0).c_str());
   fert_auswahl_lernpunkte->set_text(itos(maxpunkte));
}

