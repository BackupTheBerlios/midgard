
#ifndef _WIZARD_HH
#  define _WIZARD_HH

#include <BaseObjects/Model.h>

struct Wizard
{   enum esteps { Inaktiv, START, SPEZIES, GRUNDWERTE, GESCHLECHT, TYP, 
     		  STADTLAND, ABGELEITETEWERTE, LERNSCHEMA_SEITE, HERKUNFT,
                  UEBERLEBEN, ANGEBORENEFERTIGKEITEN, LERNPUNKTE, WAEHLEN,
                  BERUF1, BERUF, GELD, WAFFEN, RUESTUNG, AUSRUESTUNG,
                  SPEZIALWAFFE, SPEZIALGEBIET, NAMEN, SPEICHERN, FERTIG,
                  MAXSTEPS };
private:
    Model_copyable<esteps> act_step;

public:
    // mimic a model
    operator Model_ref<esteps>() { return act_step; }
    esteps Value() const { return act_step; }
    operator esteps() { return act_step; }
    bool matches(const void *gp) const { return act_step.matches(gp); }
    
    void set(esteps was);
    void next_step();
    void done(esteps was);
};
#endif
