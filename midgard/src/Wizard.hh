// generated 2002/2/14 8:49:01 CET by thoma@Tiger.
// using glademm V0.6.2c_cvs
//
// newer (non customized) versions of this file go to Wizard_window.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WIZARD_HH
#  define _WIZARD_HH

class midgard_CG;
#include <vector>
#include <string>

class Wizard
{   
   public:
     enum esteps {START,SPEZIES,GRUNDWERTE,GESCHLECHT,TYP,STADTLAND,
                  ABGELEITETEWERTE,HERKUNFT,ANGEBORENEFERTIGKEITEN,
                  LERNPUNKTE,WAEHLEN,BERUF1,BERUF,
                  GELD,WAFFEN,RUESTUNG,SPEZIALWAFFE,SPEZIALGEBIET,
                  SPEICHERN,FERTIG,MAXSTEPS};
   private:
     struct st_wiz
     {  int page;
        std::string text,kurz;
        void (midgard_CG::*callback)();
        st_wiz(int p,std::string t,std::string k,void (midgard_CG::*c)() )
            : page(p),text(t),kurz(k),callback(c){}
     };

      midgard_CG* hauptfenster;
      esteps actual_step;
      std::vector<st_wiz> vecwiz;

      void fill_vecwiz();
      void evaluate_step(esteps step);

//      gint on_Wizard_window_delete_event(GdkEventAny* event);
     
        friend class Wizard_window_glade;
//        void on_button_wizard_weiter_clicked();
//        void on_button_wizard_skip_clicked();
//        void on_button_wizard_wiederholen_clicked();
//        void on_button_close_wizard_clicked();
//        void on_togglebutton_wizard_start_toggled();
   public: 
      Wizard(midgard_CG* h);
//      void next_step();
      void next_step(esteps e);
//      void same_step();
      void restart();  

      esteps ActualStep() const {return actual_step;}
        
};
#endif
