#include "midgard_CG.hh"
#include "zufall.h"
#include "Fertigkeiten_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_fertigkeiten_wahl_clicked()
{   
//  manage(new Fertigkeiten_auswahl(this,typ.s,werte,lernpunkte,vec_beruf));
  manage(new Fertigkeiten_auswahl(this,typ.s,lernpunkte));
}

void midgard_CG::show_fertigkeiten()
{
   fertigkeiten_clist->clear();
   Gtk::OStream os(fertigkeiten_clist);
   for(vector<st_ausgewaehlte_fertigkeiten>::iterator i=vec_fertigkeiten.begin();
         i!=vec_fertigkeiten.end();++i)
      {
         os << i->name<<"\t"<<i->erfolgswert<<"\n";
      }
   for(vector<st_angeborene_fertigkeit>::iterator i=vec_an_fertigkeit.begin();
         i!=vec_an_fertigkeit.end();++i)
      {
         os << i->name<<"\t"<<i->erfolgswert<<"\n";
      }
   for (unsigned int i=0;i<fertigkeiten_clist->columns().size();++i)
      fertigkeiten_clist->set_column_auto_resize(i,true);
   fertigkeiten_clist->set_reorderable(true);
}

void midgard_CG::fertigkeiten_uebernehmen(vector<st_ausgewaehlte_fertigkeiten>& saf)
{
   vec_fertigkeiten = saf;

   for(vector<st_ausgewaehlte_fertigkeiten>::iterator i=vec_fertigkeiten.begin();
         i!=vec_fertigkeiten.end();++i)
      {
         int bonus = midgard_CG::attribut_check(i->attribut);
         i->erfolgswert += bonus;
      }
    midgard_CG::show_fertigkeiten();
}

void midgard_CG::on_angeborene_fertigekeit_clicked()
{
 vec_an_fertigkeit.clear();
 Random random;
 int wert = random.integer(1,100);
//wert =97; /*debug*/
// cout << "Für die Angeborene Fertigkeit wurde eine "<<wert<<" gewürfelt.\n";
 string stinfo="Für die Angeborene Fertigkeit\n wurde eine ";stinfo+=itos(wert);stinfo+=" gewürfelt.\n";
 manage(new WindowInfo(stinfo));
 while ( wert >= 85)
   {
      if (86<=wert && wert<=87) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Beidhändigkeit",0));
      if (88<=wert && wert<=89) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Berserkergang",0));
      if (90<=wert && wert<=91) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Richtungssinn",12));
      if (92<=wert && wert<=93) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Gefahr spüren",1));
      if (94<=wert && wert<=95) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Horchen",5));
      if (96<=wert && wert<=97) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Nachtsicht",0));
      if (98<=wert && wert<=99) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Wachgabe",0));
      if (98<=wert && wert<=99) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("Wachgabe",0));
      if (wert == 100) vec_an_fertigkeit.push_back(st_angeborene_fertigkeit("AUSWAHL",0));
      if (wert == 100) {wert = random.integer(1,100); break;}
      wert = 0;
   }
  midgard_CG::show_fertigkeiten();
}

