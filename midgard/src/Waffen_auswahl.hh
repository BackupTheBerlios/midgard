// generated 2001/2/10 15:13:17 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Waffen_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WAFFEN_AUSWAHL_HH
#  include "Waffen_auswahl_glade.hh"
#  define _WAFFEN_AUSWAHL_HH

#include <vector>
#include <map>
class midgard_CG;
struct st_lernpunkte;

struct db_struct_waffe
{  int lernpunkte; 
   string waffe;
   int erfolgswert;
   string grundkenntnisse;
   string zusatz;
   db_struct_waffe(int l,const string &f,int w, string g, string z)
   : lernpunkte(l), waffe(f), erfolgswert(w), grundkenntnisse(g),zusatz(z)
   {}
};


class Waffen_auswahl : public Waffen_auswahl_glade
{   
        int maxpunkte;
        map<string,string> waffen_grundkenntnisse;
        midgard_CG* hauptfenster;
        friend class Waffen_auswahl_glade;
        vector<db_struct_waffe> waffe;
        void on_waffen_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_waffen_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_close_waffen_clicked();
  public:
        Waffen_auswahl(midgard_CG* h,const string& typ, st_lernpunkte& l);
};
#endif
