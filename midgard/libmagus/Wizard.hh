
#ifndef _WIZARD_HH
#  define _WIZARD_HH

#include <BaseObjects/Model.h>
class Abenteurer; // Alternative wäre, Wizard in Abenteurer reinzunehmen
			// genau wie Lernpunkte

struct Wizard
{   enum esteps { Inaktiv, START, SPEZIES, GRUNDWERTE, GESCHLECHT, TYP, 
     		  STADTLAND, ABGELEITETEWERTE, LERNSCHEMA_SEITE, HERKUNFT,
                  UEBERLEBEN, ANGEBORENEFERTIGKEITEN, LERNPUNKTE, WAEHLEN,
                  BERUF1, BERUF, GELD, WAFFEN, RUESTUNG, AUSRUESTUNG,
                  SPEZIALWAFFE, SPEZIALGEBIET, NAMEN, SPEICHERN, FERTIG,
                  MAXSTEPS };
    enum mode { Aus, Sensitive, Aktiv };
private:
    Model_copyable<esteps> act_step;
    Model_copyable<mode> act_mode;

public:
    // mimic a model
    operator Model_ref<esteps>() { return act_step; }
    esteps Value() const { return act_step; }
    operator esteps() { return act_step; }
    bool matches(const void *gp) const { return act_step.matches(gp); }
    
    bool aktiv() const { return act_step.Value()!=Inaktiv; }
    Model_ref<mode> getMode() { return act_mode; }
    mode getMode() const { return act_mode.Value(); }
    
    void set(esteps was);
    void next_step();
    
    bool can_skip(const Abenteurer &A);
    void set(esteps was,const Abenteurer &A);
    void next_step(const Abenteurer &A);
    void skip_if_possible(const Abenteurer &A);
    void done(esteps was,const Abenteurer &A);
    
    void restart(const Abenteurer &A) { set(START,A); }
};
#endif
