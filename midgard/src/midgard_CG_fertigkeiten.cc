// $Id: midgard_CG_fertigkeiten.cc,v 1.49 2002/02/06 10:23:51 thoma Exp $
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
#include "Fertigkeiten_auswahl.hh"
#include <Gtk_OStream.h>
#include "Window_angeb_fert.hh"
#include "Fertigkeiten.hh"
#include "Fertigkeiten_angeboren.hh"
#include <Aux/itos.h>

void midgard_CG::on_allgemein_fertigkeiten_wahl_clicked()
{   
  show_lernschema(MidgardBasicElement::FERTIGKEIT,"Allg");
}
void midgard_CG::on_untyp_fertigkeiten_wahl_clicked()
{   
  show_lernschema(MidgardBasicElement::FERTIGKEIT,"Unge");
}
void midgard_CG::on_fach_fertigkeiten_wahl_clicked()
{   
//  list_Fertigkeit.clear();
//  list_Sprache.clear();
//  list_Schrift.clear();
  show_lernschema(MidgardBasicElement::FERTIGKEIT,"Fach");

  list_Fertigkeit.clear();
  list_Sprache.clear();
  list_Schrift.clear();
//  manage(new Fertigkeiten_auswahl(this,Database,Typ,lernpunkte,
//      Werte,&list_Sprache,list_Schrift,list_Fertigkeit));
}

/*
void midgard_CG::show_fertigkeiten()
{
   fertigkeiten_clist->clear();
   Gtk::OStream os(fertigkeiten_clist);
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit_ang.begin();
         i!=list_Fertigkeit_ang.end();++i)
      { cH_Fertigkeit_angeborene f(*i);
         os << f->Name();
         if (f->FErfolgswert(Werte)!=0) os <<"\t" <<f->FErfolgswert(Werte);
         os << "\n";
      }
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i)
      { cH_Fertigkeit f(*i);
         os << f->Name()<<" "<<f->Zusatz();
         if (f->FErfolgswert(Werte)!=0) os <<"\t" <<f->FErfolgswert(Werte);
         os << "\n";
      }
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Sprache.begin();i!=list_Sprache.end();++i)
      { 
         os << (*i)->Name() <<'\t'<<(*i)->Erfolgswert()<<'\n';
      }
   for(std::list<cH_MidgardBasicElement>::iterator i=list_Schrift.begin();i!=list_Schrift.end();++i)
      { 
         os << (*i)->Name() <<'\t'<<(*i)->Erfolgswert()<<'\n';
      }
   for (unsigned int i=0;i<fertigkeiten_clist->columns().size();++i)
      fertigkeiten_clist->set_column_auto_resize(i,true);
   fertigkeiten_clist->set_reorderable(true);

   show_sinne();
}
*/

gint midgard_CG::on_angeborene_fertigkeit_button_release_event(GdkEventButton *event)
{
  list_Fertigkeit_ang.clear();
  Werte.resetSinne();
  if (Werte.Spezies()->Name()=="Zwerg" || Werte.Spezies()->Name()=="Elf") 
      list_Fertigkeit_ang.push_back(&*cH_Fertigkeit_angeborene("Nachtsicht"/*,0*/));
  if (event->button==1) on_angeborene_fertigkeit_clicked() ;
  if (event->button==3) on_angeborene_fertigkeit_right_clicked() ;
//  button_fertigkeiten->set_sensitive(true);
  return false;
}

void midgard_CG::on_angeborene_fertigkeit_clicked()
{
  int wurf = random.integer(1,100);
//wurf = 100; /*debug*/
  while (wurf==100)
   {
      manage (new Window_angeb_fert(this,Database,list_Fertigkeit_ang,Werte,wurf));
      wurf = random.integer(1,100);
   }
  manage (new Window_angeb_fert(this,Database,list_Fertigkeit_ang,Werte,wurf));
  std::string stinfo="Für die Angeborene Fertigkeit\n wurde eine ";stinfo+=itos(wurf);stinfo+=" gewürfelt.\n";
  manage(new WindowInfo(stinfo));
//  show_fertigkeiten();
  show_gelerntes();
}


void midgard_CG::on_angeborene_fertigkeit_right_clicked()
{
  Werte.resetSinne();
  manage (new Window_angeb_fert(this,Database,list_Fertigkeit_ang,Werte,-1));
  show_gelerntes();
//  show_fertigkeiten();
}


void midgard_CG::universal_Fertigkeiten()
{
  list_Fertigkeit_universal.clear();
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
//     if((*i)->ist_gelernt(list_Fertigkeit)) continue ;
     if(cH_Fertigkeit(*i)->Voraussetzungen(Werte) && cH_Fertigkeit(*i)->Ungelernt()!=-1)
       list_Fertigkeit_universal.push_back(*i);
   }
}


void midgard_CG::show_sinne()
{
   clist_sinne->clear();
   Gtk::OStream os(clist_sinne);
   std::map<std::string,int> Sinnmap=Werte.Sinne();
   for(std::map<std::string,int>::const_iterator i=Sinnmap.begin();i!=Sinnmap.end();++i)
      { 
         os << i->first<<'\t'<<i->second<<'\n';
      }
   for (unsigned int i=0;i<clist_sinne->columns().size();++i)
      clist_sinne->set_column_auto_resize(i,true);
   clist_sinne->set_reorderable(true);
}



void midgard_CG::angeborene_fertigkeiten()
{
 if (Werte.Spezies()->Name()=="Zwerg" ||
     Werte.Spezies()->Name()=="Waldgnom" ||
     Werte.Spezies()->Name()=="Berggnom")
   {
     cH_MidgardBasicElement fert_an(&*cH_Fertigkeit_angeborene("Robustheit"));
     cH_Fertigkeit_angeborene(fert_an)->set_Erfolgswert(9);
     list_Fertigkeit_ang.push_back(fert_an);
   }
}
