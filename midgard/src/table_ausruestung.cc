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
//#include "WindowInfo.hh"
#include <Gtk_OStream.h>
#include <Misc/EntryValueIntString.h>
#include <fstream>
#include <Misc/itos.h>
#include "dtos1.h"

class Data_Preis : public RowDataBase
{
     std::string art,art2, typ, eigenschaft;
     int kosten;
     PreiseMod::st_payload preismod;
  public:
     Data_Preis(std::string a, std::string a2, std::string t, PreiseMod::st_payload p)
      : art(a),art2(a2),typ(t),preismod(p) {}
      
     enum spalten {ART,ART2,TYP,EIGENSCHAFT,KOSTEN};
     
     virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const 
      {
        switch(spalten(seqnr)) {
           case ART: return cH_EntryValueIntString(art);
           case ART2: return cH_EntryValueIntString(art2);
           case TYP: return cH_EntryValueIntString(typ);
           case EIGENSCHAFT: return cH_EntryValueIntString(preismod.name);
           case KOSTEN: return cH_EntryValueIntString(preismod.faktor);
         }
        return cH_EntryValueIntString();
      }

   std::string Art() const {return art;}
   std::string Art2() const {return art2;}
   std::string Typ() const {return typ;}
   PreiseMod::st_payload Preismod() const {return preismod;}
};
class cH_Data_Preis : public Handle<const Data_Preis>
{
public:
 cH_Data_Preis(Data_Preis *r) : Handle<const Data_Preis>(r) {}
};



void table_ausruestung::init(midgard_CG *h)
{
   hauptfenster=h;
   zeige_werte();
   ausruestung_laden();
   table_gruppe->hide();
   table_artikel->hide();      
   togglebutton_gruppe_neu->hide(); // nicht implementiert
   set_tree_titles();
   fill_new_preise();
}
   
void table_ausruestung::set_tree_titles()
{
 std::vector<string> preis;
 preis.push_back("Art");
 preis.push_back("");
 preis.push_back("Kategorie");
 preis.push_back("Eigenschaft");
 preis.push_back("Kostenfaktor");
 preise_tree->setTitles(preis);
}


   

void table_ausruestung::ausruestung_laden()
{
  sichtbarConnection=checkbutton_sichtbar->toggled.connect(SigC::slot(static_cast<class table_ausruestung*>(this), &table_ausruestung::on_checkbutton_sichtbar_toggled));
  std::vector<cH_RowDataBase> datavec;
  for(std::list<cH_PreiseMod>::const_iterator i=hauptfenster->getDatabase().preisemod.begin();i!=hauptfenster->getDatabase().preisemod.end();++i)
   {
     datavec.push_back(new Data_Preis((*i)->Art(),(*i)->Art2(),(*i)->Typ(),(*i)->Payload()));
   }
  preise_tree->setDataVec(datavec);
  showAusruestung();
}

void table_ausruestung::on_preise_leaf_selected(cH_RowDataBase d)
{
 static std::string art,art2;
 const Data_Preis *dt=dynamic_cast<const Data_Preis*>(&*d);
//cout << dt->Art()<<' '<<dt->Typ()<<' '<<dt->Preismod().name<<'\n';
 std::string memart=art;
 std::string memart2=art2;
 art=dt->Art();
 art2=dt->Art2();
 if(art!=memart || art2!=memart2) modimap.clear();
 modimap[st_modimap_index(dt->Art(),dt->Art2(),dt->Typ())]=dt->Preismod();
 show_modi();
 entry_artikel_art->set_text(art);
 entry_artikel_art2->set_text(art2);
}

void table_ausruestung::show_modi()
{
  viewport_modi->remove();
  Gtk::Table *table_modi = manage(new Gtk::Table(0,0,false));
  Gtk::Label *l=manage (new Gtk::Label("Kosten"));
  l->set_alignment(0, 0.5);
  l->show();
  table_modi->attach(*l,1,2,0,1,GTK_FILL|GTK_SHRINK,GTK_FILL|GTK_SHRINK,0,0);
  int row=1;
  for (std::map<st_modimap_index,PreiseMod::st_payload>::const_iterator i=modimap.begin();i!=modimap.end();++i)
   {
     Gtk::Label *l=manage (new Gtk::Label(i->second.name));
     l->set_alignment(0, 0.5);
     l->show();
     table_modi->attach(*l,0,1,row,row+1,GTK_FILL|GTK_SHRINK,GTK_FILL|GTK_SHRINK,0,0);
     Gtk::Label *l2=manage (new Gtk::Label("x "+dtos1(i->second.faktor)));
     l2->set_alignment(0, 0.5);
     l2->show();
//cout << i->second.name<<' '<<i->second.faktor<<'\n';
     table_modi->attach(*l2,1,2,row,row+1,GTK_FILL|GTK_SHRINK,GTK_FILL|GTK_SHRINK,0,0);
     ++row;
   }
  table_modi->set_col_spacings(5);
  viewport_modi->add(*table_modi);
  table_modi->show();
  fill_preisliste();
}

void table_ausruestung::on_button_modi_clicked()
{
  modimap.clear();
  show_modi();
}

void table_ausruestung::showAusruestung()
{
  if(hauptfenster->getChar()->getBesitz().empty())
      setStandardAusruestung(hauptfenster->getChar()->getBesitz());
  std::vector<std::string> title;
  title.push_back("Titel");
  title.push_back("Material");
  title.push_back("Sichtbar");
  Ausruestung_tree=manage(new Gtk::CTree(title));

  Ausruestung_tree->drag_data_received.connect(slot(this,&(table_ausruestung::tree_drag_data_received)));
  Ausruestung_tree->drag_dest_set ( GTK_DEST_DEFAULT_ALL,
         target_table, n_targets - 1, /* no rootwin */
         static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE) );
  
  Gtk::CTree_Helpers::RowList::iterator r;
  AusruestungBaum besitz=hauptfenster->getChar()->getBesitz();
  for(AusruestungBaum::const_iterator i=besitz.begin();i!=besitz.end();++i)
   {
     std::vector <string> v;
     v.push_back(i->getAusruestung().Name());
     v.push_back(i->getAusruestung().Material());
     v.push_back(i->getAusruestung().SichtbarStr());
     Ausruestung_tree->rows().push_back(Gtk::CTree_Helpers::Element(v));
     r=--(Ausruestung_tree->rows().end());
     r->set_data(gpointer(&*i));
//cout << "show "<<i->getChildren().getAusruestung().Name()<<'\n';
     showChildren(r,i->getChildren());
   }

/*
  for(Gtk::CTree_Helpers::RowList::const_iterator i=Ausruestung_tree->rows().begin();
         i!=Ausruestung_tree->rows().end();++i)
   {
     cout << i->get_data() << '\n';
     AusruestungBaum &A=*static_cast<AusruestungBaum*>(i->get_data());
     cout << '\t'<<"I am: "<<A.getAusruestung().Name();
     cout << '\t'<<"Child Size= "<<A.getChildren().size();
     for(Gtk::CTree_Helpers::RowList::const_iterator j=i->subtree().begin();
            j!=i->subtree().end();++j)
      {
        cout << j->get_data() << '\n';
        AusruestungBaum &A=*static_cast<AusruestungBaum*>(j->get_data());
        cout << '\t'<<"I am: "<<A.getAusruestung().Name();
        cout << '\t'<<"Child Size= "<<A.getChildren().size()<<'\n';
      }
   }
*/

  r->expand_recursive();
  Ausruestung_tree->show(); 
  Ausruestung_tree->tree_select_row.connect(SigC::slot(static_cast<class table_ausruestung*>(this), &table_ausruestung::on_Ausruestung_tree_select_row));
  Ausruestung_tree->tree_unselect_row.connect(SigC::slot(static_cast<class table_ausruestung*>(this), &table_ausruestung::on_Ausruestung_tree_unselect_row));
  for (unsigned int i=0;i<Ausruestung_tree->columns().size();++i)
         Ausruestung_tree->set_column_auto_resize(i,true);
            
  viewport_ausruestung->remove();
  viewport_ausruestung->add(*Ausruestung_tree);
  button_ausruestung_loeschen->set_sensitive(false);
}


void table_ausruestung::showChildren(Gtk::CTree_Helpers::RowList::iterator r,const list<AusruestungBaum> &AB)
{
  Gtk::CTree_Helpers::RowList::iterator n;
  for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
   {
     std::vector <string> v;
     v.push_back(i->getAusruestung().Name());
     v.push_back(i->getAusruestung().Material());
     v.push_back(i->getAusruestung().SichtbarStr());
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
      cout<< "Keine Zeile gewählt\n";
      button_ausruestung_loeschen->set_sensitive(true);
      return false;
   }
  if(selectionList.size()>1)
   {
      cout<< "Zuviele Zeilen gewählt\n";
      button_ausruestung_loeschen->set_sensitive(true);
      return false;
   }
  return true;
}

void table_ausruestung::on_Ausruestung_tree_unselect_row(Gtk::CTree::Row row,gint column)
{
  button_ausruestung_loeschen->set_sensitive(false);
}

void table_ausruestung::on_Ausruestung_tree_select_row(Gtk::CTree::Row row,gint column)
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;
  AusruestungBaum &A=*static_cast<AusruestungBaum*>(selectionList.begin()->get_data());
  sichtbarConnection.disconnect();
  checkbutton_sichtbar->set_active(A.getAusruestung().Sichtbar());
  sichtbarConnection=checkbutton_sichtbar->toggled.connect(SigC::slot(static_cast<class table_ausruestung*>(this), &table_ausruestung::on_checkbutton_sichtbar_toggled));
  button_ausruestung_loeschen->set_sensitive(true);
}

void table_ausruestung::on_checkbutton_sichtbar_toggled()
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;

  AusruestungBaum &A=*static_cast<AusruestungBaum*>(selectionList.begin()->get_data());
  const_cast<Ausruestung&>(A.getAusruestung()).setSichtbar(checkbutton_sichtbar->get_active());
  showAusruestung();
}


void table_ausruestung::on_ausruestung_loeschen_clicked()
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;
  AusruestungBaum &A=*static_cast<AusruestungBaum*>(selectionList.begin()->get_data());
  AusruestungBaum *Parent = A.getParent();
  if(Parent)  Parent->remove(A);  
  else cerr << "Keine Herkunftsnode gesetzt\n";

/*
  Gtk::CTree_Helpers::Row parent = selectionList.begin()->get_parent();  
  for(Gtk::CTree_Helpers::Row::iterator i=parent.begin();i!=parent.end();++i)
   {
     Gtk::CTree_Helpers::Cell& cell = *i;   
cout <<"Cell: " <<cell.get_text()<<'\n';
//cout <<i->get_data()<<'\n';
//     if ((*i)->get_data() == A);// { parent.remove(i); break;}
   }
*/
  showAusruestung();
}

void table_ausruestung::on_checkbutton_ausruestung_geld_toggled()
{
}

void table_ausruestung::on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event)
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;
  AusruestungBaum &A=*static_cast<AusruestungBaum*>(selectionList.begin()->get_data());

  std::string name   =clist_preisliste->get_text(row,0);
  std::string kosten =clist_preisliste->get_text(row,1);
  std::string einheit=clist_preisliste->get_text(row,2);

  if(checkbutton_ausruestung_geld->get_active())
   {
     int g=0,s=0,k=0;
     if(einheit=="GS") g=atoi(kosten.c_str());
     if(einheit=="SS") s=atoi(kosten.c_str());
     if(einheit=="KS") k=atoi(kosten.c_str());
     hauptfenster->getWerte().addGold(-g);
     hauptfenster->getWerte().addSilber(-s);
     hauptfenster->getWerte().addKupfer(-k);
     zeige_werte();
   }
 std::string bez;
 for (std::map<st_modimap_index,PreiseMod::st_payload>::const_iterator i=modimap.begin();i!=modimap.end();)
   {
     bez += i->second.name;
     if(++i!=modimap.end()) bez+=", ";
   }

 AusruestungBaum &B=A.push_back(Ausruestung(name,bez,checkbutton_sichtbar->get_active()));
 B.setParent(&A);

 clist_preisliste->unselect_all();
 showAusruestung();
}

void table_ausruestung::zeige_werte()
{
  label_golda->set_text(itos(hauptfenster->getWerte().Gold()));
  label_silbera->set_text(itos(hauptfenster->getWerte().Silber()));
  label_kupfera->set_text(itos(hauptfenster->getWerte().Kupfer()));
}


void table_ausruestung::fill_preisliste()
{
 clist_preisliste->clear();
 if(modimap.empty()) return;
 double fak=1;  
 for (std::map<st_modimap_index,PreiseMod::st_payload>::const_iterator i=modimap.begin();i!=modimap.end();++i)
   {
    fak *= i->second.faktor;
   }
// Klassenvariable wg. drag&drop// std::vector<st_ausruestung> vec_aus;
 vec_aus.clear();
 for(std::list<cH_Preise>::const_iterator i=hauptfenster->getDatabase().preise.begin();i!=hauptfenster->getDatabase().preise.end();++i)
   {
    if(modimap.begin()->first.art==(*i)->Art() && modimap.begin()->first.art2==(*i)->Art2())
     vec_aus.push_back(st_ausruestung((*i)->Name(),(*i)->Kosten() * fak,(*i)->Einheit(),(*i)->Gewicht()));
   }  
 sort(vec_aus.begin(),vec_aus.end());
 Gtk::OStream os(clist_preisliste);
 for(std::vector<st_ausruestung>::const_iterator i=vec_aus.begin();i!=vec_aus.end();++i)
   {
      os << i->name <<'\t'
         << i->kosten  <<'\t'
         << i->einheit <<'\t'
         << i->gewicht <<'\n';
       os.flush(gpointer(&*i));
   }
  for (unsigned int i=0;i<clist_preisliste->columns().size();++i)
       clist_preisliste->set_column_auto_resize(i,true);
}

AusruestungBaum &table_ausruestung::setStandardAusruestung(AusruestungBaum &besitz)
{
  AusruestungBaum *Koerper = &besitz.push_back(Ausruestung("Körper"));
  Koerper->setParent(&besitz);
  AusruestungBaum *Hose=&Koerper->push_back(Ausruestung("Hose"));
  Hose->setParent(Koerper);
  AusruestungBaum *Hemd=&Koerper->push_back(Ausruestung("Hemd"));
  Hemd->setParent(Koerper);
  AusruestungBaum *Guertel=&Koerper->push_back(Ausruestung("Gürtel"));
  Guertel->setParent(Koerper);
  AusruestungBaum *Schuhe=&Koerper->push_back(Ausruestung("Schuhe"));
  Schuhe->setParent(Koerper);
  AusruestungBaum *Rucksack=&Koerper->push_back(Ausruestung("Rucksack","Leder",true));
  Rucksack->setParent(Koerper);
  AusruestungBaum *Decke=&Rucksack->push_back(Ausruestung("Decke","warm",false));
  Decke->setParent(Rucksack);
  AusruestungBaum *Lederbeutel=&Rucksack->push_back(Ausruestung("Lederbeutel"));
  Lederbeutel->setParent(Guertel);
  AusruestungBaum *Geld=&Rucksack->push_back(Ausruestung("Geld","",false));
  Geld->setParent(Lederbeutel);

  return *Rucksack;
//  setFertigkeitenAusruestung(Rucksack);
}


////////////////////////////////////////////////////////////////////////
//Neueingeben
//von hier 
void table_ausruestung::on_togglebutton_artikel_neu_toggled()
{
 if(togglebutton_artikel_neu->get_active())
  {
    table_artikel->show();
    entry_name->grab_focus();
  }
 else 
    table_artikel->hide();
}
void table_ausruestung::on_togglebutton_gruppe_neu_toggled()
{
 if(togglebutton_gruppe_neu->get_active())
  table_gruppe->show();
 else 
  table_gruppe->hide();
}
void table_ausruestung::on_entry_art_activate()
{
  entry_typ->grab_focus();
}
void table_ausruestung::on_entry_typ_activate()
{
  entry_eigenschaft->grab_focus();
}
void table_ausruestung::on_entry_eigenschaft_activate()
{
 std::string art = entry_art->get_text();
 std::string typ = entry_typ->get_text();
 std::string eigenschaft = entry_eigenschaft->get_text();
 table_gruppe->hide();
}
// bis hier ist es nicht implementiert


//Neueingeben eines Artikels:
void table_ausruestung::on_entry_artikel_art_activate()
{
 entry_artikel_art2->grab_focus();
}
void table_ausruestung::on_entry_artikel_art2_activate()
{
 entry_name->grab_focus();
}
void table_ausruestung::on_entry_name_activate()
{
 spinbutton_preis->grab_focus();
}
void table_ausruestung::on_spinbutton_preis_activate()
{
 optionmenu_einheit->grab_focus();
}
void table_ausruestung::on_optionmenu_einheit_deactivate()
{
 spinbutton_gewicht->grab_focus();
}
void table_ausruestung::on_spinbutton_gewicht_activate()
{
 std::string art = entry_artikel_art->get_text();
 std::string art2 = entry_artikel_art2->get_text();
 std::string name = entry_name->get_text();
 std::string einheit;
 int ieinheit = int(optionmenu_einheit->get_menu()->get_active()->get_user_data()); 
 if(ieinheit==optionmenu_einheit::GS) einheit="GS";
 if(ieinheit==optionmenu_einheit::SS) einheit="SS";
 if(ieinheit==optionmenu_einheit::KS) einheit="KS";
 double preis = atof( spinbutton_preis->get_text().c_str());
 double gewicht = atof( spinbutton_gewicht->get_text().c_str());

  Preise::saveArtikel(art,art2,name,preis,einheit,gewicht);
  hauptfenster->getDatabase().preise.push_back(cH_Preise(name));
  ausruestung_laden();
// table_artikel->hide();
}

gint table_ausruestung::on_button_ausruestung_druck_release_event(GdkEventButton *event)
{
  if (event->button==1) hauptfenster->on_auch_unsichtbares_drucken();
  if (event->button==3) hauptfenster->on_nur_sichtbares_drucken();
  return false;
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
