/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2005 Christof Petig
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
#include <libmagus/Datenbank.hh>

void table_ausruestung::init(midgard_CG *h)
{
   besitz=0;
   hauptfenster=h;
  hauptfenster->getChar().signal_anderer_abenteurer().connect(SigC::slot(*this,&table_ausruestung::refresh));
  hauptfenster->getChar().proxies.undo_changed.connect(SigC::slot(*this,&table_ausruestung::refresh));
}

void table_ausruestung::refresh()
{  if (hauptfenster->get_current_page()!=midgard_CG::PAGE_AUSRUESTUNG) return;
   zeige_werte();
   showAusruestung();
//   togglebutton_gruppe_neu->hide();//
   label_normallast->set_text(itos(hauptfenster->getAben().getNormallast())+" kg");
   label_hoechstlast->set_text(itos(hauptfenster->getAben().getHoechstlast())+" kg");
   label_schublast->set_text(itos(hauptfenster->getAben().getSchublast())+" kg");
   // wenn sich die Regionen geändert haben ...
   fill_new_preise();
}

void table_ausruestung::redisplay(Gtk::TreeModel::Row const& r, AusruestungBaum const& a)
{
     r[m_columns.name] = a.getAusruestung().Name();
     r[m_columns.material] = a.getAusruestung().Material();
     r[m_columns.gewicht] = a.getAusruestung().SGewicht();
     r[m_columns.sichtbar] = a.getAusruestung().Sichtbar();
     r[m_columns.region] = a.getAusruestung().Region();
     r[m_columns.anzahl] = itos(a.getAusruestung().Anzahl());
}
   
void table_ausruestung::showAusruestung()
{
//  hauptfenster->getAben().setStandardAusruestung();

  besitz=0;
//  std::vector<std::string> title;

#if 0
  Ausruestung_tree->signal_drag_data_received().connect(SigC::slot(*this,&table_ausruestung::tree_drag_data_received));
  Ausruestung_tree->drag_dest_set ( Gtk::DEST_DEFAULT_ALL,
         target_table, n_targets - 1, /* no rootwin */
         static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE) );
#endif         
  
//  Gtk::TreeModelIterator r;
  m_refStore->clear();
  AusruestungBaum &be=hauptfenster->getAben().getBesitz();
  for(AusruestungBaum::const_iterator i=be.begin();i!=be.end();++i)
   { Gtk::TreeModel::iterator iter = m_refStore->append();
     redisplay(*iter,*i);
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
     redisplay(*iter,*i);
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
  if (!i)
  {  button_ausruestung_loeschen->set_sensitive(false);
     besitz=0;
  }
  else
  { button_ausruestung_loeschen->set_sensitive(true);
    besitz=&get_Var(m_refStore->get_path(i));
  }
}

void table_ausruestung::on_ausruestung_loeschen_clicked()
{
  if(!besitz) return;
  AusruestungBaum *Parent = besitz->getParent();
  if(Parent)  Parent->remove(*besitz);  
  else Ausgabe(Ausgabe::Error,"Keine Herkunftsnode gesetzt");
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
  showAusruestung();
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
   add(gewicht); add(sichtbar); add(anzahl);
}

AusruestungBaum &table_ausruestung::get_Var(Gtk::TreeModel::Path const& path)
{ bool is_end;
  AusruestungBaum::iterator bi=get_Iter(path,is_end);
  assert(!is_end);
  return *bi;
}

AusruestungBaum::iterator table_ausruestung::get_Iter(Gtk::TreeModel::Path const& path, bool& is_end)
{ AusruestungBaum &be=hauptfenster->getAben().getBesitz();
  AusruestungBaum::iterator bi=be.begin(),end=be.end();
  for (Gtk::TreeModel::Path::const_iterator i=path.begin();i!=path.end();)
  { assert(!*i || bi!=end);
    for (int cnt=*i;cnt>0 && bi!=end;--cnt) ++bi;
    ++i;
    if (i!=path.end())
    { assert(bi!=end);
      end=bi->end();
      bi=bi->begin();
    }
  }
  is_end=bi==end;
  return bi;
}

void table_ausruestung::cell_edited(const Glib::ustring &_path,
                  const Glib::ustring&new_text,unsigned idx)
{ Gtk::TreeModel::Path path=Gtk::TreeModel::Path(_path);
  AusruestungBaum &ausr=get_Var(path);
  switch(idx)
  { case sTitel: ausr.getAusruestung().Name(new_text); break;
    case sMaterial: ausr.getAusruestung().Material(new_text); break;
    case sAnzahl: ausr.getAusruestung().Anzahl(atoi(new_text.c_str())); break;
    default: assert(false);
  }
  redisplay(*m_refStore->get_iter(path),ausr);
}

void table_ausruestung::cell_edited_bool(const Glib::ustring &_path)
{ Gtk::TreeModel::Path path=Gtk::TreeModel::Path(_path);
  AusruestungBaum &ausr=get_Var(path);
  ausr.getAusruestung().Sichtbar(!ausr.getAusruestung().Sichtbar());
  redisplay(*m_refStore->get_iter(path),ausr);
}
