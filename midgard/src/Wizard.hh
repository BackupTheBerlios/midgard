
#ifndef _WIZARD_HH
#  define _WIZARD_HH

class midgard_CG;
#include <vector>
#include <string>
#include <BaseObjects/Model.h>

class Wizard
{   
   public:
     enum esteps {START,SPEZIES,GRUNDWERTE,GESCHLECHT,TYP,STADTLAND,
                  ABGELEITETEWERTE,LERNSCHEMA_SEITE,
                  HERKUNFT,UEBERLEBEN,ANGEBORENEFERTIGKEITEN,
                  LERNPUNKTE,WAEHLEN,BERUF1,BERUF,
                  GELD,WAFFEN,RUESTUNG,AUSRUESTUNG,SPEZIALWAFFE,SPEZIALGEBIET,
                  NAMEN,
                  SPEICHERN,FERTIG,MAXSTEPS};
   private:
     struct st_wiz
     {  int page;
        std::string text;
        st_wiz(int p,std::string t)
            : page(p),text(t){}
     };

      midgard_CG* hauptfenster;
      static std::vector<st_wiz> vecwiz;

      static void fill_vecwiz();
      void evaluate_step(esteps step);

   public: 
      Wizard(midgard_CG* h);
      void next_step(esteps e);
      void restart();  

      // über dieses Model könnten z.B. Knöpfe blinken etc.
      Model<esteps> actual_step;
      Model<bool> active;
};
#endif
