#include "midgard_CG.hh"
#include "Berufe_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_berufe_wahl_clicked()
{
  berufe_clist->clear();
  manage(new Berufe_auswahl(this,typ,lernpunkte,werte));
}

void midgard_CG::show_berufe()
{
   berufe_clist->clear();
   Gtk::OStream os(berufe_clist);
   for(vector<st_ausgewaehlte_berufe>::iterator i=vec_beruf.begin();
         i!=vec_beruf.end();++i)
      {
         os << i->name<<"\t"<<i->vorteile<<"\t"<<i->erfolgswert<<"\n";
      }
   for (unsigned int i=0;i<berufe_clist->columns().size();++i)
      berufe_clist->set_column_auto_resize(i,true);
   berufe_clist->set_reorderable(true);

}

void midgard_CG::berufe_uebernehmen(vector<st_ausgewaehlte_berufe>& sab)
{
   vec_beruf = sab;
   midgard_CG::show_berufe();
}

void midgard_CG::on_beruf_erfolgswert_clicked()
{
 Random random;
 int erfahrungswert =  (lernpunkte.waffen + lernpunkte.fertigkeiten)/5.;
 int inbo=0;
 if (atoi(in->get_text().c_str()) >= 81 ) ++inbo ;
 if (atoi(in->get_text().c_str()) >= 96 ) ++inbo ;

 for(unsigned int  i=0; i<=vec_beruf.size();++i)
   {
    int ausbildungswert = random.integer(1,3)+6;
    if (i==0) vec_beruf[i].erfolgswert = ausbildungswert+erfahrungswert+inbo;
    else vec_beruf[i].erfolgswert = ausbildungswert+inbo;
   }
 midgard_CG::berufe_uebernehmen(vec_beruf);
}

