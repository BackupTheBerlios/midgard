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

void table_ausruestung::init(midgard_CG *h)
{
   besitz=0;
   hauptfenster=h;
   zeige_werte();
   ausruestung_laden();
   table_gruppe->hide();
   table_artikel->hide();      
   togglebutton_artikel_neu->set_active(false);
   togglebutton_gruppe_neu->set_active(false); 
//   togglebutton_gruppe_neu->hide();//
   label_normallast->set_text(itos(h->getAben().getNormallast())+" kg");
   label_hoechstlast->set_text(itos(h->getAben().getHoechstlast())+" kg");
   label_schublast->set_text(itos(h->getAben().getSchublast())+" kg");
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
  title.push_back("Titel");
  title.push_back("Material");
  title.push_back("Gewicht");
  title.push_back("Sichtbar");
  title.push_back("Region");
  scrolledwindow_ausruestung->remove();
  Ausruestung_tree=manage(new Gtk::CTree(title));

  Ausruestung_tree->signal_drag_data_received().connect(SigC::slot(*this,&table_ausruestung::tree_drag_data_received));
  Ausruestung_tree->drag_dest_set ( Gtk::DEST_DEFAULT_ALL,
         target_table, n_targets - 1, /* no rootwin */
         static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE) );
  
  Gtk::CTree_Helpers::RowList::iterator r;
  AusruestungBaum &be=hauptfenster->getChar()->getBesitz();
  for(AusruestungBaum::const_iterator i=be.begin();i!=be.end();++i)
   {
     std::vector <std::string> v;
     v.push_back(i->getAusruestung().Name());
     v.push_back(i->getAusruestung().Material());
     v.push_back(i->getAusruestung().SGewicht());
     v.push_back(i->getAusruestung().SichtbarStr());
     v.push_back(i->getAusruestung().Region());
     Ausruestung_tree->rows().push_back(Gtk::CTree_Helpers::Element(v));
     r=--(Ausruestung_tree->rows().end());
     r->set_data(gpointer(&*i));
//cout << "show "<<v[0]<<'\t'<<&*i<<'\t'<<i->getAusruestung().Name()<<'\n';
     showChildren(r,i->getChildren());
   }

  r->expand_recursive();
  Ausruestung_tree->show(); 
  Ausruestung_tree->signal_tree_select_row().connect(SigC::slot(*static_cast<class table_ausruestung*>(this), &table_ausruestung::on_Ausruestung_tree_select_row));
  Ausruestung_tree->signal_tree_unselect_row().connect(SigC::slot(*static_cast<class table_ausruestung*>(this), &table_ausruestung::on_Ausruestung_tree_unselect_row));
  for (unsigned int i=0;i<Ausruestung_tree->columns().size();++i)
         Ausruestung_tree->set_column_auto_resize(i,true);
            
  scrolledwindow_ausruestung->add(*Ausruestung_tree);
  button_ausruestung_loeschen->set_sensitive(false);
  label_gesamtlast->set_text(dtos1(hauptfenster->getAben().getBelastung())+" kg");
}


void table_ausruestung::showChildren(Gtk::CTree_Helpers::RowList::iterator r,const std::list<AusruestungBaum> &AB)
{
  Gtk::CTree_Helpers::RowList::iterator n;
  for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
   {
     std::vector <std::string> v;
     v.push_back(i->getAusruestung().Name());
     v.push_back(i->getAusruestung().Material());
     v.push_back(i->getAusruestung().SGewicht());
     v.push_back(i->getAusruestung().SichtbarStr());
     v.push_back(i->getAusruestung().Region());
     r->subtree().push_back(Gtk::CTree_Helpers::Element(v));
     n=--(r->subtree().end());
     n->set_data(gpointer(&*i));
     showChildren(n,i->getChildren());
   }  
}



bool table_ausruestung::tree_valid(Gtk::CTree_Helpers::SelectionList &selectionList)
{
  if(selectionList.empty())
   {
      std::cout<< "Keine Zeile gewählt\n";
      button_ausruestung_loeschen->set_sensitive(true);
      return false;
   }
  if(selectionList.size()>1)
   {
      std::cout<< "Zuviele Zeilen gewählt\n";
      button_ausruestung_loeschen->set_sensitive(true);
      return false;
   }
  return true;
}

void table_ausruestung::on_Ausruestung_tree_unselect_row(Gtk::CTree::Row row,gint column)
{
  button_ausruestung_loeschen->set_sensitive(false);
  besitz=0;
}

void table_ausruestung::on_Ausruestung_tree_select_row(Gtk::CTree::Row row,gint column)
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;
  AusruestungBaum *A=static_cast<AusruestungBaum*>(selectionList.begin()->get_data());
  sichtbarConnection.signal_di().connect();
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
  else std::cerr << "Keine Herkunftsnode gesetzt\n";

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
  label_golda->set_text(itos(hauptfenster->getWerte().Gold()));
  label_silbera->set_text(itos(hauptfenster->getWerte().Silber()));
  label_kupfera->set_text(itos(hauptfenster->getWerte().Kupfer()));
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
  std::list<cH_Preise> P=hauptfenster->getCDatabase().preise; 
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
  std::list<cH_Preise> P=hauptfenster->getCDatabase().preise; 
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
 double preis = atof( spinbutton_preis->get_text().c_str());
 double gewicht = atof( spinbutton_gewicht->get_text().c_str());

  std::string region="EE";
  try{
  Preise::saveArtikel("",hauptfenster,
                      art,art2,name,preis,einheit,gewicht,region);
  hauptfenster->getDatabase().preise.push_back(cH_Preise(name));
  fill_new_preise();
  }catch(std::exception &e) {std::cerr << e.what()<<'\n';}
  ausruestung_laden();
// table_artikel->hide();
}

bool table_ausruestung::on_button_ausruestung_druck_release_event(GdkEventButton *event)
{
  if (event->button==1) hauptfenster->on_auch_unsichtbares_drucken();
  if (event->button==3) hauptfenster->on_nur_sichtbares_drucken();
  return false;
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
