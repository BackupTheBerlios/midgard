#include "midgard_CG.hh"
#include "Waffen_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_waffen_wahl_clicked()
{
  waffen_clist->clear();
  manage(new Waffen_auswahl(this,typ.s,lernpunkte));
}

void midgard_CG::show_waffen()
{
   waffen_clist->clear();
   Gtk::OStream os(waffen_clist);
   for(vector<st_ausgewaelte_waffen>::iterator i=vec_waffen.begin();
         i!=vec_waffen.end();++i)
      {
         os << i->name<<"\t"<<i->erfolgswert<<"\n";
      }
   for (unsigned int i=0;i<waffen_clist->columns().size();++i)
      waffen_clist->set_column_auto_resize(i,true);
   waffen_clist->set_reorderable(true);

}

void midgard_CG::waffen_uebernehmen(vector<st_ausgewaelte_waffen>& saw, map<string,string> wg)
{
   vec_waffen = saw;
   waffen_grundkenntnisse = wg;
   midgard_CG::show_waffen();
}

void midgard_CG::on_waffen_clist_select_row(gint row, gint column, GdkEvent *event)
{   
 /* Funktion für Spezialwaffe */
 if (typ.z=="n" || typ.s == "Ord")
   {
    static int oldrow = -1;
    ++++vec_waffen[row].erfolgswert;    
    if(oldrow!=-1) ----vec_waffen[oldrow].erfolgswert;    
    oldrow=row;
    werte.spezialisierung = waffen_clist->get_text(row,0);
    midgard_CG::waffen_uebernehmen(vec_waffen,waffen_grundkenntnisse);
   }
}

