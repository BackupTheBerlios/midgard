// generated 2001/11/25 15:17:30 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// newer (non customized) versions of this file go to midgard_CG.cc_new

// This file is for your program, I won't touch it again!

#include "midgard_CG.hh"
#include <Gtk_OStream.h>
#include <Aux/EntryValueIntString.h>

class Data_Preis : public RowDataBase
{
     std::string art, typ, eigenschaft;
     int kosten;
     PreiseMod::st_payload preismod;
  public:
     Data_Preis(std::string a, std::string t, PreiseMod::st_payload p)
      : art(a),typ(t),preismod(p) {}
      
     enum spalten {ART,TYP,EIGENSCHAFT,KOSTEN,EINHEIT};
     
     virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const 
      {
        switch(spalten(seqnr)) {
           case ART: return cH_EntryValueIntString(art);
           case TYP: return cH_EntryValueIntString(typ);
           case EIGENSCHAFT: return cH_EntryValueIntString(preismod.name);
           case KOSTEN: return cH_EntryValueIntString(preismod.faktor);
           case EINHEIT: return cH_EntryValueIntString(preismod.einheit);
         }
        return cH_EntryValueIntString();
      }

   std::string Art() const {return art;}
   std::string Typ() const {return typ;}
   PreiseMod::st_payload Preismod() const {return preismod;}
};
class cH_Data_Preis : public Handle<const Data_Preis>
{
public:
 cH_Data_Preis(Data_Preis *r) : Handle<const Data_Preis>(r) {}
};


void midgard_CG::ausruestung_laden()
{
  sichtbarConnection=checkbutton_sichtbar->toggled.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_checkbutton_sichtbar_toggled));
  std::vector<cH_RowDataBase> datavec;
  for(std::list<cH_PreiseMod>::iterator i=Database.preisemod.begin();i!=Database.preisemod.end();++i)
   {
     datavec.push_back(new Data_Preis((*i)->Art(),(*i)->Typ(),(*i)->Payload()));
   }
  preise_tree->setDataVec(datavec);
  showAusruestung();
}

void midgard_CG::on_preise_leaf_selected(cH_RowDataBase d)
{
 static std::string art;
 const Data_Preis *dt=dynamic_cast<const Data_Preis*>(&*d);
//cout << dt->Art()<<' '<<dt->Typ()<<' '<<dt->Preismod().name<<'\n';
 std::string memart=art;
 art=dt->Art();
 if(art!=memart) modimap.clear();
 modimap[pair<std::string,std::string>(dt->Art(),dt->Typ())]=dt->Preismod();
 show_modi();
}

void midgard_CG::show_modi()
{
  viewport_modi->remove();
  Gtk::Table *table_modi = manage(new Gtk::Table(0,0,false));
  Gtk::Label *l=manage (new Gtk::Label("Kosten"));
  l->set_alignment(0, 0.5);
  l->show();
  table_modi->attach(*l,1,2,0,1,GTK_FILL,0,0,0);
  int row=1;
  for (std::map<pair<std::string,std::string>,PreiseMod::st_payload>::const_iterator i=modimap.begin();i!=modimap.end();++i)
   {
     Gtk::Label *l=manage (new Gtk::Label(i->second.name));
     l->set_alignment(0, 0.5);
     l->show();
     table_modi->attach(*l,0,1,row,row+1,GTK_FILL,0,0,0);
     Gtk::Label *l2=manage (new Gtk::Label("x "+dtos(i->second.faktor)));
     l2->set_alignment(0, 0.5);
     l2->show();
//cout << i->second.name<<' '<<i->second.faktor<<'\n';
     table_modi->attach(*l2,1,2,row,row+1,GTK_FILL,0,0,0);
     ++row;
   }
  table_modi->set_col_spacings(5);
  viewport_modi->add(*table_modi);
  table_modi->show();
  fill_preisliste();
}

void midgard_CG::on_button_modi_clicked()
{
  modimap.clear();
  show_modi();
}



void midgard_CG::showAusruestung()
{
  if(besitz.empty()) 
    { AusruestungBaum *Koerper = &besitz.push_back(Ausruestung("K�rper"));
      Koerper->setParent(&besitz);
      AusruestungBaum *Rucksack=&Koerper->push_back(Ausruestung("Rucksack","Leder",true));
      Rucksack->setParent(Koerper);
    }
  std::vector<std::string> title;
  title.push_back("Titel");
  title.push_back("Material");
  title.push_back("Sichtbar");
  Ausruestung_tree=manage(new Gtk::CTree(title));
  Gtk::CTree_Helpers::RowList::iterator r;
  for(AusruestungBaum::const_iterator i=besitz.begin();i!=besitz.end();++i)
   {
     std::vector <string> v;
     v.push_back(i->getAusruestung().Name());
     v.push_back(i->getAusruestung().Material());
     v.push_back(i->getAusruestung().SichtbarStr());
     Ausruestung_tree->rows().push_back(Gtk::CTree_Helpers::Element(v));
     r=--(Ausruestung_tree->rows().end());
     r->set_data(gpointer(&*i));
     showChildren(r,i->getChildren());
   }

/*
  for(Gtk::CTree_Helpers::RowList::const_iterator i=Ausruestung_tree->rows().begin();
         i!=Ausruestung_tree->rows().end();++i)
   {
     cout << i->get_data() << '\n';
     AusruestungBaum &A=*static_cast<AusruestungBaum*>(i->get_data());
     cout << '\t'<<A.getAusruestung().Name();
     cout << '\t'<<A.getChildren().size();
     for(Gtk::CTree_Helpers::RowList::const_iterator j=i->subtree().begin();
            j!=i->subtree().end();++j)
      {
        cout << j->get_data() << '\n';
        AusruestungBaum &A=*static_cast<AusruestungBaum*>(j->get_data());
        cout << '\t'<<A.getAusruestung().Name();
        cout << '\t'<<A.getChildren().size();
      }
   }
*/
  r->expand_recursive();
  Ausruestung_tree->show(); 
  Ausruestung_tree->tree_select_row.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_Ausruestung_tree_select_row));
  Ausruestung_tree->tree_unselect_row.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_Ausruestung_tree_unselect_row));
  for (unsigned int i=0;i<Ausruestung_tree->columns().size();++i)
         Ausruestung_tree->set_column_auto_resize(i,true);
            
  viewport_ausruestung->remove();
  viewport_ausruestung->add(*Ausruestung_tree);
  button_ausruestung_loeschen->set_sensitive(false);
}

void midgard_CG::showChildren(Gtk::CTree_Helpers::RowList::iterator r,const list<AusruestungBaum> &AB)
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


bool midgard_CG::tree_valid(Gtk::CTree_Helpers::SelectionList &selectionList)
{
  if(selectionList.empty())
   {
      cout<< "Keine Zeile gew�hlt\n";
      button_ausruestung_loeschen->set_sensitive(true);
      return false;
   }
  if(selectionList.size()>1)
   {
      cout<< "Zuviele Zeilen gew�hlt\n";
      button_ausruestung_loeschen->set_sensitive(true);
      return false;
   }
  return true;
}

void midgard_CG::on_Ausruestung_tree_unselect_row(Gtk::CTree::Row row,gint column)
{
  button_ausruestung_loeschen->set_sensitive(false);
}

void midgard_CG::on_Ausruestung_tree_select_row(Gtk::CTree::Row row,gint column)
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;
  AusruestungBaum &A=*static_cast<AusruestungBaum*>(selectionList.begin()->get_data());
  sichtbarConnection.disconnect();
  checkbutton_sichtbar->set_active(A.getAusruestung().Sichtbar());
  sichtbarConnection=checkbutton_sichtbar->toggled.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::on_checkbutton_sichtbar_toggled));
  button_ausruestung_loeschen->set_sensitive(true);
}

void midgard_CG::on_checkbutton_sichtbar_toggled()
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;

  AusruestungBaum &A=*static_cast<AusruestungBaum*>(selectionList.begin()->get_data());
  const_cast<Ausruestung&>(A.getAusruestung()).setSichtbar(checkbutton_sichtbar->get_active());
  showAusruestung();
}


void midgard_CG::on_ausruestung_loeschen_clicked()
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


void midgard_CG::on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event)
{
  Gtk::CTree_Helpers::SelectionList selectionList = Ausruestung_tree->selection();
  if(!tree_valid(selectionList)) return;
  AusruestungBaum &A=*static_cast<AusruestungBaum*>(selectionList.begin()->get_data());

  std::string name   =clist_preisliste->get_text(row,0);
  std::string kosten =clist_preisliste->get_text(row,1);
  std::string einheit=clist_preisliste->get_text(row,2);

  int g=0,s=0,k=0;
  if(einheit=="GS") g=atoi(kosten.c_str());
  if(einheit=="SS") s=atoi(kosten.c_str());
  if(einheit=="KS") k=atoi(kosten.c_str());
  Werte.add_Gold(-g);
  Werte.add_Silber(-s);
  Werte.add_Kupfer(-k);
  Geld_uebernehmen();

 std::string bez;
 for (std::map<pair<std::string,std::string>,PreiseMod::st_payload>::const_iterator i=modimap.begin();i!=modimap.end();)
   {
     bez += i->second.name;
     if(++i!=modimap.end()) bez+=", ";
   }

 AusruestungBaum &B=A.push_back(Ausruestung(name,bez,checkbutton_sichtbar->get_active()));
 B.setParent(&A);

 showAusruestung();
}


void midgard_CG::fill_preisliste()
{
 clist_preisliste->clear();
 if(modimap.empty()) return;
 double fak=1;  
 for (std::map<pair<std::string,std::string>,PreiseMod::st_payload>::const_iterator i=modimap.begin();i!=modimap.end();++i)
   {
    fak *= i->second.faktor;
   }
 Gtk::OStream os(clist_preisliste);
 for(std::list<cH_Preise>::const_iterator i=Database.preise.begin();i!=Database.preise.end();++i)
   {
//     if(dt->Art()==(*i)->Art())
    if(modimap.begin()->first.first==(*i)->Art())
      os << (*i)->Name() <<'\t'
         << (*i)->Kosten() * fak <<'\t'
         << (*i)->Einheit()
         <<'\n';
   }  
  for (unsigned int i=0;i<clist_preisliste->columns().size();++i)
       clist_preisliste->set_column_auto_resize(i,true);
}


void midgard_CG::on_button_ausruestung_druck_clicked()
{
 ofstream fout("midgard_tmp_ausruestung.tex");
 LaTeX_header(fout,false);           

 for(AusruestungBaum::const_iterator i=besitz.begin();i!=besitz.end();++i)
  {
   std::string name=i->getAusruestung().Name()+" ("+i->getAusruestung().Material()+")";
   fout << name<<'\n';
   ausruestung_druck(fout,i->getChildren(),0);
  }

 LaTeX_footer(fout);
 fout.close();
 system("latex midgard_tmp_ausruestung.tex");    
 system("dvips midgard_tmp_ausruestung.dvi");
 system("gv midgard_tmp_ausruestung.ps &");  
}


void midgard_CG::ausruestung_druck(ofstream &fout,const list<AusruestungBaum> &AB,int deep)
{
 for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
  {
   std::string name=i->getAusruestung().Name()+" ("+i->getAusruestung().Material()+")";
   fout << name<<'\n';
   ausruestung_druck(fout,i->getChildren(),deep);
  }
}
