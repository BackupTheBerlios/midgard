
#ifndef _WIZARD_HH
#  define _WIZARD_HH

namespace Wizard
{   enum esteps { Inaktiv, START, SPEZIES, GRUNDWERTE, GESCHLECHT, TYP, 
     		  STADTLAND, ABGELEITETEWERTE, LERNSCHEMA_SEITE, HERKUNFT,
                  UEBERLEBEN, ANGEBORENEFERTIGKEITEN, LERNPUNKTE, WAEHLEN,
                  BERUF1, BERUF, GELD, WAFFEN, RUESTUNG, AUSRUESTUNG,
                  SPEZIALWAFFE, SPEZIALGEBIET, NAMEN, SPEICHERN, FERTIG,
                  MAXSTEPS };

    void set(Model_ref<int> model,esteps was);
    void next_step(Model_ref<int> model);
};
#endif
