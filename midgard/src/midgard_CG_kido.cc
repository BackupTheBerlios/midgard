#include "midgard_CG.hh"
#include "KiDo_auswahl.hh"
#include <Gtk_OStream.h>


void midgard_CG::on_kido_wahl_clicked()
{
   if (werte.spezialisierung!="Sanfte Techniken" && 
       werte.spezialisierung!="Harte Techniken" &&
       werte.spezialisierung!="Gemischte Techniken")
    {
      string strinfo="Erst eine Technik wählen\n";
      manage(new WindowInfo(strinfo));
      return;
    }
   int maxkido=0;
   if (typ.s=="Kd") maxkido = 5;
   if (typ.s=="Ny") maxkido = 3;
   manage(new KiDo_auswahl(this,maxkido,werte));
}

void midgard_CG::show_kido()
{
   clist_kido->clear();
   Gtk::OStream os(clist_kido);
   for (vector<st_kido>::const_iterator i=vec_kido.begin();i!=vec_kido.end();++i)
    {
      os << i->hoho<<"\t"<<i->technik<<"\t"<<"\t"<<i->ap<<"\t"<<i->fp<<"\n";
    }
   for (unsigned int i=0;i<clist_kido->columns().size();++i)
      clist_kido->set_column_auto_resize(i,true);
}

void midgard_CG::kido_uebernehmen(vector<string>& technik)
{
   clist_kido->clear();
   for (vector<string>::const_iterator i=technik.begin();i!=technik.end();++i)
      vec_kido.push_back(st_kido((*i),"","","",0,0,""));
   get_kido(vec_kido);
   midgard_CG::show_kido();
}

void midgard_CG::stil_optionmenue()
{
  static bool block=false;
  if (block==true) return;
  int ityp = int(optionmenu_KiDo_Stile->get_menu()->get_active()->get_user_data());
  if (ityp==optionmenu_KiDo_Stile::sanft) werte.spezialisierung="Sanfte Techniken";
  if (ityp==optionmenu_KiDo_Stile::hart) werte.spezialisierung="Harte Techniken";
  if (ityp==optionmenu_KiDo_Stile::gemischt) werte.spezialisierung="Gemischte Techniken";
}
