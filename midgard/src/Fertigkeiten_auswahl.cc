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
     const std::list<cH_MidgardBasicElement> *_list_Sprache,
     const std::list<cH_MidgardBasicElement> &_list_Schrift,
     const std::list<cH_MidgardBasicElement> &_list_Fertigkeit)
: lernpunkte(_lernpunkte),Werte(_Werte),Typ(_Typ),Database(dat),
   list_Sprache(_list_Sprache),list_Schrift(_list_Schrift),
   list_Fertigkeit(_list_Fertigkeit)
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
  //Speziesspezifische Fertigkeit
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
     if(Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::LERNPUNKTE))
      {
        int erf=Database.pflicht.istPflicht(Werte.Spezies()->Name(),Typ,(*i)->Name(),Pflicht::ERFOLGSWERT);
        (*i)->set_Erfolgswert(erf);
        Lernschema::st_index I(Typ[0]->Short(),"Fachkenntnisse",(*i)->Name());
        (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I));
        list_Fert_spez.push_back(*i);       
      }
   }
  // Fachkenntnisse //////////////////////////////////////////////////////////////
  std::list<cH_MidgardBasicElement> LW=Database.lernschema.get_List("Fachkenntnisse",Typ);
  for(std::list<cH_MidgardBasicElement>::const_iterator i=LW.begin();i!=LW.end();++i)
   {
      if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
      Lernschema::st_index I(Typ[0]->Short(),"Fachkenntnisse",(*i)->Name());
      (*i)->set_Lernpunkte(Database.lernschema.get_Lernpunkte(I));
      cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert0());
      list_Fert_Fach.push_back(*i);
   }

   list_Fert_spez.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
   list_Fert_Fach.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::LERNPUNKTE));
   Gtk::OStream os(fach_clist_auswahl);
   // Speziesspezifische Fertigkeiten
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_spez.begin();i!=list_Fert_spez.end();++i)
      { cH_Fertigkeit f(*i);
        std::string serfolgswert=itos(f->FErfolgswert(Werte));
        if (serfolgswert=="0") serfolgswert="";
        if ((f->Voraussetzungen(Werte) || Werte.Spezies()->Name()!="Mensch") &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name(),true))
         { os << f->Lernpunkte() <<"\t"<<f->Voraussetzung()<<"\t"<<f->Pflicht()<<"\t"<<f->Name()<<"\t"
               << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
            os.flush(f->ref());
         }
      }
   if (list_Fert_spez.size()) os <<'\n';
   // Fachkenntnisse
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_Fach.begin();i!=list_Fert_Fach.end();++i)
      { cH_Fertigkeit f(*i);
        std::string serfolgswert=itos(f->FErfolgswert(Werte));
        if (serfolgswert=="0") serfolgswert="";
        if ((f->Voraussetzungen(Werte) || Werte.Spezies()->Name()!="Mensch") &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name(),true) &&
             hauptfenster->region_check(f->Region()) )
         { 
            Lernschema::st_index I(Typ[0]->Short(),"Fachkenntnisse",(*i)->Name());
            os << (*i)->Lernpunkte() <<"\t"<<f->Voraussetzung()<<"\t"
               << Database.lernschema.get_Pflicht_str(I) <<"\t"<<f->Name()<<"\t"
               << serfolgswert<<"\t"<<f->Attribut()<<"\t"
               <<f->Kosten(Typ,Database.ausnahmen)<<"\n";
//            os.flush(&*i);
            os.flush(f->ref());
         }
      }
   for (unsigned int i=0;i<fach_clist_auswahl->columns().size();++i)
      fach_clist_auswahl->set_column_auto_resize(i,true);
   fach_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
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
     if(cH_Fertigkeit(*i)->LernLand() >= maxpunkte_A && Werte.Stadt_Land()=="Land")
       {
        cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert());
        list_Fert_Allg.push_back(*i);
       }
     if(cH_Fertigkeit(*i)->LernStadt() >= maxpunkte_A && Werte.Stadt_Land()=="Stadt")
       {
        cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert());
        list_Fert_Allg.push_back(*i);
       }
   }
   if(true)
      list_Fert_Allg.sort(cH_Fertigkeit::sort(cH_Fertigkeit::sort::LERN_L));
   if(false)
      list_Fert_Allg.sort(cH_Fertigkeit::sort(cH_Fertigkeit::sort::LERN_S));
   Gtk::OStream os(allgemein_clist_auswahl);
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_Allg.begin();i!=list_Fert_Allg.end();++i)
      { cH_Fertigkeit f(*i);
        int lernpunkte=0;
        if(true) lernpunkte=f->LernLand();
        if(false) lernpunkte=f->LernStadt();
        std::string serfolgswert=itos(f->FErfolgswert(Werte));
        if (serfolgswert=="0") serfolgswert="";
        if(lernpunkte <= maxpunkte_A)
          if ( f->Voraussetzungen(Werte) && hauptfenster->region_check(f->Region()) &&
             !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name()))
            { os << lernpunkte<<'\t'<<f->Voraussetzung()<<"\t"<<f->Name()<<"\t"
                << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
//              os.flush(&*i);
              os.flush(f->ref());
            }
      }
   for (unsigned int i=0;i<allgemein_clist_auswahl->columns().size();++i)
      allgemein_clist_auswahl->set_column_auto_resize(i,true);
   allgemein_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
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
       {
        cH_Fertigkeit(*i)->set_Erfolgswert(cH_Fertigkeit(*i)->Anfangswert());
        list_Fert_Unge.push_back(*i);
       }
   }
   list_Fert_Unge.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
   Gtk::OStream os(unge_clist_auswahl);
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fert_Unge.begin();i!=list_Fert_Unge.end();++i)
      { cH_Fertigkeit f(*i);
        std::string serfolgswert=itos(f->FErfolgswert(Werte));
        if (serfolgswert=="0") serfolgswert="";
        if(f->Lernpunkte() <= maxpunkte_U)
          if ( f->Voraussetzungen(Werte) && hauptfenster->region_check(f->Region()) &&
               !Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,f->Name()))
           { os << f->Lernpunkte()<<'\t'<<f->Voraussetzung()<<"\t"<<f->Name()<<"\t"
                << serfolgswert<<"\t"<<f->Attribut()<<"\t"<<f->Kosten(Typ,Database.ausnahmen)<<"\n";
//             os.flush(&*i);
             os.flush(f->ref());
           }
      }
   for (unsigned int i=0;i<unge_clist_auswahl->columns().size();++i)
      unge_clist_auswahl->set_column_auto_resize(i,true);

   unge_clist_auswahl->set_selection_mode(GTK_SELECTION_MULTIPLE);
}




void Fertigkeiten_auswahl::on_close_fertigkeiten_clicked()
{
   std::list<cH_MidgardBasicElement> saf;
   for (Gtk::CList::SelectionList::iterator i=fach_clist_auswahl->selection().begin();i!=fach_clist_auswahl->selection().end();++i)
     {  
      cH_MidgardBasicElement ptr = static_cast<MidgardBasicElement*>(i->get_data());
      if(!SpracheSchrift(ptr->Name()))
         saf.push_back(ptr);
     }
   for (Gtk::CList::SelectionList::iterator i=allgemein_clist_auswahl->selection().begin();i!=allgemein_clist_auswahl->selection().end();++i)
     {  
      cH_MidgardBasicElement ptr = static_cast<MidgardBasicElement*>(i->get_data());
      if(!SpracheSchrift((ptr)->Name()))
         saf.push_back(ptr);
     }
   for (Gtk::CList::SelectionList::iterator i=unge_clist_auswahl->selection().begin();i!=unge_clist_auswahl->selection().end();++i)
     {  
      cH_MidgardBasicElement ptr = static_cast<MidgardBasicElement*>(i->get_data());
      if(!SpracheSchrift((ptr)->Name()))
         saf.push_back(ptr);
     }
  hauptfenster->MidgardBasicElement_uebernehmen(saf);
  destroy();
}


void Fertigkeiten_auswahl::on_fach_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{
   if (maxpunkte_F < atoi(fach_clist_auswahl->get_text(row,0).c_str() ))
     {  fach_clist_auswahl->row(row).unselect(); }
   maxpunkte_F -= atoi(fach_clist_auswahl->get_text(row,0).c_str());
   fach_lernpunkte->set_text(itos(maxpunkte_F));
   SpracheSchrift(fach_clist_auswahl->get_text(row,3),atoi(fach_clist_auswahl->get_text(row,4).c_str()),true);
}
void Fertigkeiten_auswahl::on_allgemein_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{
   if (maxpunkte_A < atoi(allgemein_clist_auswahl->get_text(row,0).c_str() ))
     {  allgemein_clist_auswahl->row(row).unselect(); }
   maxpunkte_A -= atoi(allgemein_clist_auswahl->get_text(row,0).c_str());
   allgemein_lernpunkte->set_text(itos(maxpunkte_A));
   SpracheSchrift(allgemein_clist_auswahl->get_text(row,2),atoi(allgemein_clist_auswahl->get_text(row,3).c_str()),true) ;
}
void Fertigkeiten_auswahl::on_unge_clist_auswahl_select_row(gint row, gint column, GdkEvent *event)
{
   if (maxpunkte_U < atoi(unge_clist_auswahl->get_text(row,0).c_str() ))
     {  unge_clist_auswahl->row(row).unselect(); }
   maxpunkte_U -= atoi(unge_clist_auswahl->get_text(row,0).c_str());
   unge_lernpunkte->set_text(itos(maxpunkte_U));
   SpracheSchrift(unge_clist_auswahl->get_text(row,2),atoi(unge_clist_auswahl->get_text(row,3).c_str()),true) ;
}

bool Fertigkeiten_auswahl::SpracheSchrift(const std::string& fert,int wert,bool auswahl)
{
 bool launch=false;
 Sprache_auswahl::modus mod;

 if(fert=="Landeskunde" || fert=="Landeskunde (Heimat)")
    { launch=true;  mod=Sprache_auswahl::LAND; }
 else if(fert=="Schreiben: Muttersprache(+12)" ||
         fert=="Schreiben: Muttersprache(+9)" ||        
         fert=="Schreiben: Muttersprache(+4)" ||
         fert=="Schreiben: Alte Sprache(+12)" ||
         fert=="Schreiben" )
    { launch=true;  mod=Sprache_auswahl::SCHRIFT; }
 else if(fert=="Muttersprache" ||
         fert=="Gastlandsprache" ||
         fert=="Sprechen: Sprache(+4)" ||
         fert=="Sprechen: Sprache(+9)" ||
         fert=="Sprechen: Sprache(+12)")
    { launch=true;  mod=Sprache_auswahl::NEUESPRACHE; }
 else if(fert=="Sprechen: Alte Sprache")
    { launch=true;  mod=Sprache_auswahl::ALTESPRACHE; }

 if(auswahl && launch)
     manage (new Sprache_auswahl(hauptfenster,Database,mod,wert,
                                 list_Sprache,list_Schrift,list_Fertigkeit));
 return launch;
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

