/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "config.h"
#include "table_ausruestung.hh"
#include "midgard_CG.hh"
#include <Gtk_OStream.h>
#include <Misc/EntryValueIntString.h>
#include <fstream>
#include <Misc/itos.h>
#include "dtos1.h"
#include <libmagus/Ausgabe.hh>

void table_ausruestung::init(midgard_CG *h)
{
   besitz=0;
   hauptfenster=h;
}

void table_ausruestung::refresh()
{  zeige_werte();
   ausruestung_laden();
   table_gruppe->hide();
   table_artikel->hide();      
   togglebutton_artikel_neu->set_active(false);
   togglebutton_gruppe_neu->set_active(false); 
//   togglebutton_gruppe_neu->hide();//
   label_normallast->set_text(itos(hauptfenster->getAben().getNormallast())+" kg");
   label_hoechstlast->set_text(itos(hauptfenster->getAben().getHoechstlast())+" kg");
   label_schublast->set_text(itos(hauptfenster->getAben().getSchublast())+" kg");
   fill_new_preise();
   fill_all_Combos_Art_Einheit_Region();
   fill_all_Combo_Art2();
}
   
   
void table_ausruestung::ausruestung_laden()
{
  sichtbarConnection=checkbutton_sichtbar->signal_toggled().connect(SigC::slot(*static_cast<class table_ausruestung*>(this), &table_ausruestung::on_checkbutton_sichtbar_toggled));
  showAusruestung();
}


void table_ausruestung::showAusruestung()
{
  hauptfenster->getAben().setStandardAusruestung();

  besitz=0;
  std::vector<std::string> title;

#if 0
  Ausruestung_tree->signal_drag_data_received().connect(SigC::slot(*this,&table_ausruestung::tree_drag_data_received));
  Ausruestung_tree->drag_dest_set ( Gtk::DEST_DEFAULT_ALL,
         target_table, n_targets - 1, /* no rootwin */
         static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE) );
#endif         
  
//  Gtk::TreeModelIterator r;
  AusruestungBaum &be=hauptfenster->getAben().getBesitz();
  for(AusruestungBaum::const_iterator i=be.begin();i!=be.end();++i)
   { Gtk::TreeModel::iterator iter = m_refStore->append();
     (*iter)[m_columns.name] = i->getAusruestung().Name();
     (*iter)[m_columns.material] = i->getAusruestung().Material();
     (*iter)[m_columns.gewicht] = i->getAusruestung().SGewicht();
     (*iter)[m_columns.sichtbar] = i->getAusruestung().Sichtbar();
     (*iter)[m_columns.region] = i->getAusruestung().Region();
     (*iter)[m_columns.ausruestung] = const_cast<AusruestungBaum*>(&*i);
     showChildren(iter->children(),i->getChildren());
   }

  Ausruestung_tree->expand_all();
  Ausruestung_tree->get_selection()->signal_changed().connect(SigC::slot(*static_cast<class table_ausruestung*>(this), &table_ausruestung::on_Ausruestung_tree_select_row));
//  Ausruestung_tree->signal_tree_unselect_row().connect(SigC::slot(*static_cast<class table_ausruestung*>(this), &table_ausruestung::on_Ausruestung_tree_unselect_row));
  button_ausruestung_loeschen->set_sensitive(false);
  label_gesamtlast->set_text(dtos1(hauptfenster->getAben().getBelastung("Körper"))+" kg");
}


void table_ausruestung::showChildren(Gtk::TreeModel::Children r,const std::list<AusruestungBaum> &AB)
{ // we should use a non const iterator - once available
  for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
   { Gtk::TreeModel::iterator iter = m_refStore->append(r);
     (*iter)[m_columns.name] = i->getAusruestung().Name();
     (*iter)[m_columns.material] = i->getAusruestung().Material();
     (*iter)[m_columns.gewicht] = i->getAusruestung().SGewicht();
     (*iter)[m_columns.sichtbar] = i->getAusruestung().Sichtbar();
     (*iter)[m_columns.region] = i->getAusruestung().Region();
     (*iter)[m_columns.ausruestung] = const_cast<AusruestungBaum*>(&*i);
     showChildren(iter->children(),i->getChildren());
   }  
}


bool table_ausruestung::tree_valid(const Glib::RefPtr<Gtk::TreeSelection> &selectionList)
{ Gtk::TreeIter i= selectionList->get_selected();
  if(i==m_refStore->children().end())
   {
      Ausgabe(Ausgabe::Debug,"Keine oder zuviel Zeile(n) gewählt");
      button_ausruestung_loeschen->set_sensitive(true);
      return false;
   }
  return true;
}

void table_ausruestung::on_Ausruestung_tree_select_row()
{ Gtk::TreeIter i= Ausruestung_tree->get_selection()->get_selected();
  if (i==m_refStore->children().end())
  {  button_ausruestung_loeschen->set_sensitive(false);
     besitz=0;
     return;
  }
//  Gtk::TreeModel::Selection selectionList = Ausruestung_tree->get_selection();
//  if(!tree_valid(selectionList)) return;
  AusruestungBaum *A=(*i)[m_columns.ausruestung];
  sichtbarConnection.disconnect();
  checkbutton_sichtbar->set_active(A->getAusruestung().Sichtbar());
  sichtbarConnection=checkbutton_sichtbar->signal_toggled().connect(SigC::slot(*static_cast<class table_ausruestung*>(this), &table_ausruestung::on_checkbutton_sichtbar_toggled));
  button_ausruestung_loeschen->set_sensitive(true);
  besitz=A;
}


void table_ausruestung::on_checkbutton_sichtbar_toggled()
{
  if(!besitz) return;
  const_cast<Ausruestung&>(besitz->getAusruestung()).setSichtbar(checkbutton_sichtbar->get_active());
  showAusruestung();
}


void table_ausruestung::on_ausruestung_loeschen_clicked()
{
  if(!besitz) return;
  AusruestungBaum *Parent = besitz->getParent();
  if(Parent)  Parent->remove(*besitz);  
  else Ausgabe(Ausgabe::Error,"Keine Herkunftsnode gesetzt");

/*
  Gtk::CTree_Helpers::Row parent = selectionList.begin()->get_parent();  
  for(Gtk::CTree_Helpers::Row::iterator i=parent.begin();i!=parent.end();++i)
   {
     Gtk::CTree_Helpers::Cell& cell = *i;   
std::cout <<"Cell: " <<cell.get_text()<<'\n';
//cout <<i->get_data()<<'\n';
//     if ((*i)->get_data() == A);// { parent.remove(i); break;}
   }
*/
  showAusruestung();
}

void table_ausruestung::on_checkbutton_ausruestung_geld_toggled()
{
}


void table_ausruestung::zeige_werte()
{
  label_golda->set_text(itos(hauptfenster->getAben().Gold()));
  label_silbera->set_text(itos(hauptfenster->getAben().Silber()));
  label_kupfera->set_text(itos(hauptfenster->getAben().Kupfer()));
}

void table_ausruestung::on_togglebutton_artikel_neu_toggled()
{
 if(togglebutton_artikel_neu->get_active())
  {
    togglebutton_gruppe_neu->set_active(false);
    table_artikel->show();
    entry_name->grab_focus();
  }
 else 
    table_artikel->hide();
}


void table_ausruestung::on_togglebutton_gruppe_neu_toggled()
{
 if(togglebutton_gruppe_neu->get_active())
  {
   togglebutton_artikel_neu->set_active(false);
   table_gruppe->show();
  }
 else 
  table_gruppe->hide();
}

void table_ausruestung::on_entry_art_activate()
{
  entry_art2->grab_focus();
}

void table_ausruestung::on_entry_art2_activate()
{
  button_art_speichern->grab_focus(); 
}

void table_ausruestung::on_button_art_speichern_clicked()
{
 std::string art  = entry_art->get_text();
 std::string art2 = entry_art2->get_text();
 newArt(art,art2);
 table_gruppe->hide();
}

void table_ausruestung::newArt(const std::string &art,const std::string art2)
{
  MNewArt[art].push_back(art2);
  togglebutton_gruppe_neu->set_active(false);
  fill_all_Combos_Art_Einheit_Region();
}


//Neueingeben eines Artikels:
void table_ausruestung::fill_all_Combos_Art_Einheit_Region()
{
  std::list<std::string> LArt;
  std::list<std::string> LEinheit;
  std::list<std::string> LRegion;
  std::list<cH_Preise> P=Datenbank.preise; 
  LRegion.push_back("Eigene Erweiterung");
  for(std::list<cH_Preise>::const_iterator i=P.begin();i!=P.end();++i)
   {
     LArt.push_back((*i)->Art());
     LEinheit.push_back((*i)->Einheit());
   }
  for(std::map<std::string,std::list<std::string> >::const_iterator i=MNewArt.begin();i!=MNewArt.end();++i)
     LArt.push_back(i->first);
  LArt.sort();
  LArt.unique();
  combo_art->set_popdown_strings(LArt);
  LEinheit.sort();
  LEinheit.unique();
  combo_einheit->set_popdown_strings(LEinheit);
}


bool table_ausruestung::fill_all_Combo_Art2()
{
  std::string art=combo_art->get_entry()->get_text();
  std::list<std::string> LArt2;
  std::list<cH_Preise> P=Datenbank.preise; 
  for(std::list<cH_Preise>::const_iterator i=P.begin();i!=P.end();++i)
   {
     if(art==(*i)->Art())
        LArt2.push_back((*i)->Art2());
   }
  std::list<std::string> S=MNewArt[art];
  for(std::list<std::string>::const_iterator i=S.begin();i!=S.end();++i)
      LArt2.push_back(*i);
  LArt2.unique();
  LArt2.sort();
  combo_art2->set_popdown_strings(LArt2);
  if(LArt2.empty()) return false;
  return true;
}

void table_ausruestung::on_combo_entry_artikel_art_changed()
{
  on_combo_entry_artikel_art_activate();
}

bool table_ausruestung::on_combo_entry_artikel_art_focus_out_event(GdkEventFocus *ev)
{
//  on_combo_entry_artikel_art_activate();
  return false;
}
void table_ausruestung::on_combo_entry_artikel_art_activate()
{
 if(fill_all_Combo_Art2())
   {
    combo_art2->set_sensitive(true);
    combo_art2->get_entry()->grab_focus();
   }
 else 
   {
    combo_art2->set_sensitive(false);
    entry_name->grab_focus();
   }
}

void table_ausruestung::on_combo_entry_art2_changed()
{
  on_combo_entry_art2_activate();
}
bool table_ausruestung::on_combo_entry_art2_focus_out_event(GdkEventFocus *ev)
{
//  on_combo_entry_art2_activate();
  return false;
}
void table_ausruestung::on_combo_entry_art2_activate()
{
 entry_name->grab_focus();
}

void table_ausruestung::on_entry_name_activate()
{
 spinbutton_gewicht->grab_focus();
}
void table_ausruestung::on_spinbutton_preis_activate()
{
  combo_einheit->get_entry()->grab_focus();
}
void table_ausruestung::on_combo_entry_einheit_activate()
{
//  combo_entry_region->grab_focus();
  button_artikel_speichern->grab_focus();
}

void table_ausruestung::on_combo_entry_einheit_changed()
{
 entry_beschreibung->grab_focus();
}

void table_ausruestung::on_entry_beschreibung_activate()
{
 button_artikel_speichern->grab_focus();
}


void table_ausruestung::on_combo_entry_region_activate()
{
  button_artikel_speichern->grab_focus();
}
void table_ausruestung::on_spinbutton_gewicht_activate()
{
 spinbutton_preis->grab_focus();
}



void table_ausruestung::on_button_artikel_speichern_clicked()
{
  save_new_arikel();
}

void table_ausruestung::save_new_arikel()
{
 std::string art = combo_art->get_entry()->get_text();
 std::string art2 = combo_art2->get_entry()->get_text();
 std::string name = entry_name->get_text();
 std::string einheit=combo_einheit->get_entry()->get_text();
 std::string beschreibung=entry_beschreibung->get_text();
 double preis = atof( spinbutton_preis->get_text().c_str());
 double gewicht = atof( spinbutton_gewicht->get_text().c_str());

  std::string region="EE";
  try{
  Preise::saveArtikel("",
                      art,art2,name,preis,einheit,gewicht,region,beschreibung);
#warning Anlegen von neuen Artikeln                      
//  Datenbank.preise.push_back(cH_Preise(name));
  fill_new_preise();
  }catch(std::exception &e) {Ausgabe(Ausgabe::Error,e.what());}
  ausruestung_laden();
// table_artikel->hide();
}

void table_ausruestung::on_button_ausruestung_druck()
{
  hauptfenster->on_auch_unsichtbares_drucken();
#warning B3
//  if (event->button==3) hauptfenster->on_nur_sichtbares_drucken();
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

table_ausruestung::ModelColumns::ModelColumns()
{  add(name); add(material); add(region);
   add(gewicht); add(sichtbar); add(ausruestung);
}
