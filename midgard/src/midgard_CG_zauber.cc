#include "midgard_CG.hh"
#include "Zauber_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_zauber_wahl_clicked()
{
  zauber_clist->clear();
  manage(new Zauber_auswahl(this,typ.s,lernpunkte));
}

void midgard_CG::show_zauber()
{
   zauber_clist->clear();
   midgard_CG::Zauber_get_daten(zauber);
   Gtk::OStream os(zauber_clist);
   for(vector<st_zauber>::iterator i=zauber.begin();
         i!=zauber.end();++i)
      {
         os << i->name<<"\t"<<i->erfolgswert<<"\n";
      }
   for (unsigned int i=0;i<zauber_clist->columns().size();++i)
      zauber_clist->set_column_auto_resize(i,true);
   zauber_clist->set_reorderable(true);
}

void midgard_CG::zauber_uebernehmen(vector<st_ausgewaehlte_zauber>& saz)
{
   zauber.clear();
   vec_zauber = saz;
   for(vector<st_ausgewaehlte_zauber>::iterator i=vec_zauber.begin();
         i!=vec_zauber.end();++i)
      {
         string erf = midgard_CG::get_erfolgswert_zaubern(typ,i->name);
         zauber.push_back(st_zauber(i->ap,i->name,erf,"0","0","0","0","0","0","0","0","0","0","0","0","0",0));
      }
   midgard_CG::show_zauber();
}

