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
#include "Pflicht.hh"

Fertigkeiten_auswahl::Fertigkeiten_auswahl(midgard_CG* h,
     const midgard_CG::st_Database& dat,const vector<cH_Typen>& _Typ,
     Lernpunkte& _lernpunkte, const Grundwerte& _Werte,
     const std::list<cH_MidgardBasicElement>& _list_Sprache,
     const std::list<cH_MidgardBasicElement>& _list_Schrift)
: lernpunkte(_lernpunkte),Werte(_Werte),Typ(_Typ),Database(dat),
   list_Sprache(_list_Sprache),list_Schrift(_list_Schrift)
{
  hauptfenster=h;
  Fachwissen();
  Allgemeinwissen();
  Unge();
}

void Fertigkeiten_auswahl::Fachwissen()
{
  maxpunkte_F = lernpunkte.Fach();
  fach_lernpunkte->set_text(itos(maxpunkte_F));
  // Berufsvorteile
//  std::vector<string> vorteile=hauptfenster->Berufs_Vorteile();

  //Speziesspezifische Fertigkeit
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
     if(Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::LERNPUNKTE))
      {
        int erf=Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::ERFOLGSWERT);
        (*i)->set_Erfolgswert(erf);
        int v=0;
//        for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
//            if ((*j)==(*i)->Name()) v=1;
        Lernschema::st_index I(Typ[0]->Short(),"Fachkenntnisse",(*i)->Name());
//        (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I)-v);
        (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I)-v);
        list_Fert_spez.push_back(*i);       
      }
   }
  // Fachkenntnisse //////////////////////////////////////////////////////////////
  std::list<cH_MidgardBasicElement> LW=Database.lernschema.get_List("Fachkenntnisse",Typ);
  for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
   {
      if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
//      int v=0;
//      for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
//          if ((*j)==(*i)->Name()) v=1;
      Lernschema::st_index I(Typ[0]->Short(),"Fachkenntnisse",(*i)->Name());
//      (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I)-v);
      (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I));
      cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert0());
      list_Fert_Fach.push_back(*i);
   }
/*
  // andere Fertigkeiten
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
    bool fachkenntnis=false;
    for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Fert.begin();j!=list_Fert.end();++j)
       if((*j)->Name()==(*i)->Name()) { fachkenntnis=true; break; }
    bool spezieskenntnis=false;
    for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Fert_spez.begin();j!=list_Fert_spez.end();++j)
       if((*j)->Name()==(*i)->Name()) { spezieskenntnis=true; break; }
    
    if(!fachkenntnis && !spezieskenntnis)
     {
       cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert0());
       list_allg_Fert.push_back(*i);
     }
   }
*/
   list_Fert_spez.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
//   list_Fert.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
   Gtk::OStream os(fach_clist_auswahl);
//   fach_clist_auswahl->freeze();
   // Speziesspezifische Fertigkeiten
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_spez.begin();i!=list_Fert_spez.end();++i)
      { cH_Fertigkeit f(*i);
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ((f->Voraussetzungen(Werte) || Werte.Spezies()->Name()!="Mensch") &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name(),true))
         { os << f->Lernpunkte() <<"\t"<<f->Voraussetzung()<<"\t"<<f->Pflicht()<<"\t"<<f->Name()<<"\t"
               << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
            os.flush(&*i);
         }
      }
   if (list_Fert_spez.size()) os <<'\n';
   // Fachkenntnisse
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_Fach.begin();i!=list_Fert_Fach.end();++i)
      { cH_Fertigkeit f(*i);
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ((f->Voraussetzungen(Werte) || Werte.Spezies()->Name()!="Mensch") &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name(),true) &&
             hauptfenster->region_check(f->Region()) )
         { 
            Lernschema::st_index I(Typ[0]->Short(),"Fertigkeit",(*i)->Name());
            os << (*i)->Lernpunkte() <<"\t"<<f->Voraussetzung()<<"\t"
               << Database.lernschema.get_Pflicht_str(I) <<"\t"<<f->Name()<<"\t"
               << serfolgswert<<"\t"<<f->Attribut()<<"\t"
               <<f->Kosten(Typ,Database.ausnahmen)<<"\n";
            os.flush(&*i);
         }
      }
/*
   // andere Fertigkeiten ////////////////////////////////////////////////
   os <<"\n\n";   
   for(std::list<cH_MidgardBasicElement>::iterator i=list_allg_Fert.begin();i!=list_allg_Fert.end();++i)
      { cH_Fertigkeit f(*i);
        int v=0;
        for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
           if ((*j)==f->Name()) v=1;
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ( f->Voraussetzungen(Werte) && hauptfenster->region_check(f->Region()) &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name()))
         { os << f->Lernpunkte()-v<<"\t"<<f->Voraussetzung()<<"\t"<<""<<"\t"<<f->Name()<<"\t"
              << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
           os.flush(&*i);
         }
      }
*/
   for (unsigned int i=0;i<fach_clist_auswahl->columns().size();++i)
      fach_clist_auswahl->set_column_auto_resize(i,true);

   fach_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
//   fach_clist_auswahl->set_reorderable(true);
//   fach_clist_auswahl->thaw();
}

void Fertigkeiten_auswahl::Allgemeinwissen()
{
  maxpunkte_A = lernpunkte.Allgemein();
  allgemein_lernpunkte->set_text(itos(maxpunkte_A));

  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
/*
    bool fachkenntnis=false;
    for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Fert_Fach.begin();j!=list_Fert_Fach.end();++j)
       if((*j)->Name()==(*i)->Name()) { fachkenntnis=true; break; }
    bool spezieskenntnis=false;
    for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Fert_spez.begin();j!=list_Fert_spez.end();++j)
       if((*j)->Name()==(*i)->Name()) { spezieskenntnis=true; break; }
*/    
//    if(!fachkenntnis && !spezieskenntnis)
     if(cH_Fertigkeit(*i)->LernLand()!=99)
       {
        cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert());
        list_Fert_Allg.push_back(*i);
       }
   }
   list_Fert_Allg.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
   Gtk::OStream os(allgemein_clist_auswahl);
//   fach_clist_auswahl->freeze();
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_Allg.begin();i!=list_Fert_Allg.end();++i)
      { cH_Fertigkeit f(*i);
//        int v=0;
//        for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
//           if ((*j)==f->Name()) v=1;
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ( f->Voraussetzungen(Werte) && hauptfenster->region_check(f->Region()) &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name()))
         { os << f->Lernpunkte()<<f->Voraussetzung()<<"\t"<<""<<"\t"<<f->Name()<<"\t"
              << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
           os.flush(&*i);
         }
      }
   for (unsigned int i=0;i<allgemein_clist_auswahl->columns().size();++i)
      allgemein_clist_auswahl->set_column_auto_resize(i,true);

   allgemein_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
//   fach_clist_auswahl->set_reorderable(true);
//   fach_clist_auswahl->thaw();
}

void Fertigkeiten_auswahl::Unge()
{
  maxpunkte_U = lernpunkte.Unge();
  unge_lernpunkte->set_text(itos(maxpunkte_U));

  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
/*
    bool fachkenntnis=false;
    for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Fert_Fach.begin();j!=list_Fert_Fach.end();++j)
       if((*j)->Name()==(*i)->Name()) { fachkenntnis=true; break; }
    bool spezieskenntnis=false;
    for (std::list<cH_MidgardBasicElement>::const_iterator j=list_Fert_spez.begin();j!=list_Fert_spez.end();++j)
       if((*j)->Name()==(*i)->Name()) { spezieskenntnis=true; break; }
*/    
//    if(!fachkenntnis && !spezieskenntnis)
     if(cH_Fertigkeit(*i)->Lernpunkte()!=99)
       {
        cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert());
        list_Fert_Unge.push_back(*i);
       }
   }
   list_Fert_Unge.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
   Gtk::OStream os(unge_clist_auswahl);
//   fach_clist_auswahl->freeze();
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_Unge.begin();i!=list_Fert_Unge.end();++i)
      { cH_Fertigkeit f(*i);
//        int v=0;
//        for (std::vector<string>::const_iterator j=vorteile.begin();j!=vorteile.end();++j)
//           if ((*j)==f->Name()) v=1;
        std::string serfolgswert=itos(f->Erfolgswert());
        if (serfolgswert=="0") serfolgswert="";
        if ( f->Voraussetzungen(Werte) && hauptfenster->region_check(f->Region()) &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name()))
         { os << f->Lernpunkte()<<f->Voraussetzung()<<""<<"\t"<<f->Name()<<"\t"
              << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
           os.flush(&*i);
         }
      }
   for (unsigned int i=0;i<unge_clist_auswahl->columns().size();++i)
      unge_clist_auswahl->set_column_auto_resize(i,true);

   unge_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
//   fach_clist_auswahl->set_reorderable(true);
//   fach_clist_auswahl->thaw();
}




void Fertigkeiten_auswahl::on_close_fertigkeiten_clicked()
{
   std::list<cH_MidgardBasicElement> saf;
/*
   for (Gtk::CList::SelectionList::iterator i=fertigkeiten_clist_auswahl->selection().begin();
         i!=fertigkeiten_clist_auswahl->selection().end();++i)
     {  
      cH_MidgardBasicElement *ptr = static_cast<cH_MidgardBasicElement*>(i->get_data());
      if ((*ptr)->Name() != "Sprache" && (*ptr)->Name() != "Lesen/Schreiben" )
         saf.push_back(*ptr);
     }
*/
  hauptfenster->MidgardBasicElement_uebernehmen(saf);
  destroy();
}


void Fertigkeiten_auswahl::on_fach_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{
   if (maxpunkte_F < atoi(fach_clist_auswahl->get_text(row,0).c_str() ))
     {  fach_clist_auswahl->row(row).unselect(); }
   maxpunkte_F -= atoi(fach_clist_auswahl->get_text(row,0).c_str());
   fach_lernpunkte->set_text(itos(maxpunkte_F));
   // Sprache oder Schrift?
   std::string fert = fach_clist_auswahl->get_text(row,3);
   if (fert == "Sprache" || fert == "Lesen/Schreiben" )
     { SpracheSchrift(fert) ; }
}
void Fertigkeiten_auswahl::on_allgemein_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{
   if (maxpunkte_A < atoi(allgemein_clist_auswahl->get_text(row,0).c_str() ))
     {  allgemein_clist_auswahl->row(row).unselect(); }
   maxpunkte_A -= atoi(allgemein_clist_auswahl->get_text(row,0).c_str());
   allgemein_lernpunkte->set_text(itos(maxpunkte_A));
   // Sprache oder Schrift?
   std::string fert = allgemein_clist_auswahl->get_text(row,2);
   if (fert == "Sprache" || fert == "Lesen/Schreiben" )
     { SpracheSchrift(fert) ; }
}
void Fertigkeiten_auswahl::on_unge_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{
   if (maxpunkte_U < atoi(unge_clist_auswahl->get_text(row,0).c_str() ))
     {  unge_clist_auswahl->row(row).unselect(); }
   maxpunkte_U -= atoi(unge_clist_auswahl->get_text(row,0).c_str());
   unge_lernpunkte->set_text(itos(maxpunkte_U));
   // Sprache oder Schrift?
   std::string fert = unge_clist_auswahl->get_text(row,2);
   if (fert == "Sprache" || fert == "Lesen/Schreiben" )
     { SpracheSchrift(fert) ; }
}

void Fertigkeiten_auswahl::SpracheSchrift(const std::string& fert)
{
  if (fert == "Sprache") manage (new Sprache_auswahl(hauptfenster,Database,fert,list_Sprache));
  if (fert == "Lesen/Schreiben") manage (new Sprache_auswahl(hauptfenster,Database,fert,list_Sprache));
}

void Fertigkeiten_auswahl::on_fach_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{
   maxpunkte_F += atoi(fach_clist_auswahl->get_text(row,0).c_str());
   fach_lernpunkte->set_text(itos(maxpunkte_F));
}
void Fertigkeiten_auswahl::on_allgemein_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{
   maxpunkte_A += atoi(allgemein_clist_auswahl->get_text(row,0).c_str());
   allgemein_lernpunkte->set_text(itos(maxpunkte_A));
}
void Fertigkeiten_auswahl::on_unge_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event)
{
   maxpunkte_U += atoi(unge_clist_auswahl->get_text(row,0).c_str());
   unge_lernpunkte->set_text(itos(maxpunkte_U));
}

