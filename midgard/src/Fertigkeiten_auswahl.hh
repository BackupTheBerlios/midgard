// generated 2001/2/8 11:08:32 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to Fertigkeiten_auswahl.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _FERTIGKEITEN_AUSWAHL_HH
#  include "Fertigkeiten_auswahl_glade.hh"
#  define _FERTIGKEITEN_AUSWAHL_HH

#include <vector>
class midgard_CG;
struct st_lernpunkte;

struct db_struct_fertigkeiten
{  int lernpunkte; 
   string fertigkeiten; 
   int erfolgswert;
   string attribut;
   string pflicht;
   int fp;
   string voraussetzung;
   db_struct_fertigkeiten(int l,const string &f,int w,
                           const string &a, const string &p, int fp,
                           const string &v)
   : lernpunkte(l), fertigkeiten(f), erfolgswert(w), attribut(a), 
      pflicht(p), fp(fp), voraussetzung(v)
   {}
};

class Fertigkeiten_auswahl : public Fertigkeiten_auswahl_glade
{   
        int maxpunkte;        
        midgard_CG* hauptfenster;
        friend class Fertigkeiten_auswahl_glade;
        void on_close_fertigkeiten_clicked();
        vector<db_struct_fertigkeiten> fert;
        vector<db_struct_fertigkeiten> allg_fert;
        void on_fertigkeiten_clist_auswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_fertigkeiten_clist_auswahl_unselect_row(gint row, gint column, GdkEvent *event);
 public:
        Fertigkeiten_auswahl(midgard_CG* h,const string& typ, 
                 st_lernpunkte& l);
};
#endif
