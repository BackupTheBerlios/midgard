// generated 2001/2/11 14:16:06 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Zauber_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget


#ifndef _ZAUBER_AUSWAHL_HH
#  include "Zauber_auswahl_glade.hh"
#  define _ZAUBER_AUSWAHL_HH

#include <vector>
class midgard_CG;
struct st_lernpunkte;

struct db_struct_zauber
{  int lernpunkte;    
   string zauber;      
   string ap;
   int kosten;
   db_struct_zauber(int l,const string &f, const string &a, int k)
   : lernpunkte(l), zauber(f), ap(a), kosten(k)   
   {}
};   


class Zauber_auswahl : public Zauber_auswahl_glade
{   
        int maxpunkte;
        midgard_CG* hauptfenster;
        friend class Zauber_auswahl_glade;
        vector<db_struct_zauber> zauber;
        void on_zauber_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_zauber_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
        void on_close_zauber_clicked();
  public:
        Zauber_auswahl(midgard_CG* h,const string& typ, st_lernpunkte& l);

};
#endif
