// generated 2001/11/25 15:17:30 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// newer (non customized) versions of this file go to midgard_CG.cc_new

// This file is for your program, I won't touch it again!

#include "midgard_CG.hh"
#include <Gtk_OStream.h>
#include <Aux/EntryValueIntString.h>

#include "Ausruestung.hh"

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


class Data_Ausruestung : public RowDataBase
{
     vector<std::string> V;
  public:
     Data_Ausruestung(vector<std::string> v) : V(v) {V.resize(10);}
     
     virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const 
      {
        switch(seqnr) {
           case 1 : return cH_EntryValueIntString(V[0]);
           case 2 : return cH_EntryValueIntString(V[1]);
           case 3 : return cH_EntryValueIntString(V[2]);
           case 4 : return cH_EntryValueIntString(V[3]);
           case 5 : return cH_EntryValueIntString(V[4]);
           case 6 : return cH_EntryValueIntString(V[5]);
           case 7 : return cH_EntryValueIntString(V[6]);
           case 8 : return cH_EntryValueIntString(V[7]);
           case 9 : return cH_EntryValueIntString(V[8]);
           case 10: return cH_EntryValueIntString(V[9]);
         }
        return cH_EntryValueIntString();
      }

   std::string getLast()
      {
        for(vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
          if((*i)!="") return *i;
        return "";         
      }
};
class cH_Data_Ausruestung : public Handle<const Data_Ausruestung>
{
public:
 cH_Data_Ausruestung(Data_Ausruestung *r) : Handle<const Data_Ausruestung>(r) {}
};
 


void midgard_CG::ausruestung_laden()
{
//  fill_optionmenu_art();
//  opt_art();
  std::vector<cH_RowDataBase> datavec;
  for(std::list<cH_PreiseMod>::iterator i=Database.preisemod.begin();i!=Database.preisemod.end();++i)
   {
     datavec.push_back(new Data_Preis((*i)->Art(),(*i)->Typ(),(*i)->Payload()));
   }
  preise_tree->setDataVec(datavec);
}

void midgard_CG::on_preise_leaf_selected(cH_RowDataBase d)
{
 static std::string art;
 const Data_Preis *dt=dynamic_cast<const Data_Preis*>(&*d);
cout << dt->Art()<<' '<<dt->Typ()<<' '<<dt->Preismod().name<<'\n';
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

void midgard_CG::on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event)
{
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

 AusruestungFull AF;

 bool sichtbar=true;
 std::string position;
 AF.Rein(Ausruestung(name,bez,position,sichtbar));

 name += " "+bez;
  
cout << name<<'\n';
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

void midgard_CG::opt_art()
{
//  fill_optionmenu_typ();
}
void midgard_CG::fill_optionmenu_art()
{
/*
  {Gtk::OStream os(optionmenu_art);
  for(std::list<cH_PreiseMod>::iterator i=Database.preisemod.begin();i!=Database.preisemod.end();++i)
   {
     os << (*i)->Art();
     os.flush((gpointer)&*i);
   }  
  }
  optionmenu_art->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_art));
  optionmenu_art->show();
*/
}


void midgard_CG::opt_typ()
{
//  fill_optionmenu_eigenschaft();
}
void midgard_CG::fill_optionmenu_typ()
{
/*
  cH_PreiseMod *art=static_cast<cH_PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  {Gtk::OStream os(optionmenu_typ);
   for(std::map<std::string,vector<PreiseMod::st_vec> >::const_iterator i=(*art)->getMap().begin();i!=(*art)->getMap().end();++i)
    {
      os << i->first<<'\n';
      os.flush((gpointer)&(i->first));
    }  
  }
  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_typ));
  optionmenu_typ->show();
*/
}

void midgard_CG::opt_eigenschaft()
{
//  fill_preisliste();
}
void midgard_CG::fill_optionmenu_eigenschaft()
{
/*
  {Gtk::OStream os(optionmenu_eigenschaft);
  cH_PreiseMod *art=static_cast<cH_PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  std::string *typ=static_cast<std::string*>(optionmenu_typ->get_menu()->get_active()->get_user_data());

  for(std::vector<PreiseMod::st_vec>::const_iterator i=(*art)->getMap()[*typ].begin();i!=(*art)->getMap()[*typ].end();++i)
   {
     
//     if(i->typ==*typ)
//      {
cout <<"->"<< i->name<<"<-\n";
//       os << i->name<<'\n';
//       os.flush((gpointer)&*i);
//      }
   }  
  }
  optionmenu_eigenschaft->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::opt_eigenschaft));
  optionmenu_eigenschaft->show();
*/
}


void midgard_CG::on_button_ausruestung_druck_clicked()
{
}


