/*  libMagus: Library zum Verwalten von Midgard Abenteurern
 *  Copyright (C) 2003-2004 Christof Petig
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef _WIZARD_HH
#  define _WIZARD_HH

#include <BaseObjects/Model.h>
#include <Misc/compiler_ports.h>
class Abenteurer; // Alternative wäre, Wizard in Abenteurer reinzunehmen
			// genau wie Lernpunkte

struct Wizard
{   enum esteps { SPEZIES, GRUNDWERTE, GESCHLECHT, TYP, 
		  // 4
     		  STADTLAND, ABGELEITETEWERTE, LERNSCHEMA_SEITE, HERKUNFT,
     		  // 8
                  UEBERLEBEN, ANGEBORENEFERTIGKEITEN, LERNPUNKTE, WAEHLEN,
                  // 12
                  BERUF1, BERUF, GELD, WAFFEN, RUESTUNG, AUSRUESTUNG,
                  // 18
                  SPEZIALWAFFE, SPEZIALGEBIET, NAMEN, SPEICHERN, FERTIG,
                  // 23
                  ZWEITER_TYP, KIDO_STIL, MAXSTEPS, };

                  // bitte nicht mehr verwenden!
    __deprecated const static esteps Inaktiv=FERTIG;
    __deprecated const static esteps START=SPEZIES;
    enum mode { Aus, Hints, Sensitive, Aktiv };
private:
    Model_copyable<esteps> act_step;
    Model_copyable<mode> act_mode;

public:
    // mimic a model
    Wizard();
    
    operator Model_ref<esteps>() { return act_step; }
    operator Model_ref<mode>() { return act_mode; }
    esteps Value() const { return act_step; }
    operator esteps() { return act_step; }
    bool matches(const void *gp) const { return act_step.matches(gp); }
    
    bool aktiv() const { return act_step.Value()!=FERTIG; }
    Model_ref<mode> getMode() { return act_mode; }
    mode getMode() const { return act_mode.Value(); }
    
    void set(esteps was);
    void next_step();
    
    bool can_skip(const Abenteurer &A);
    void set(esteps was,const Abenteurer &A);
    void next_step(const Abenteurer &A);
    void skip_if_possible(const Abenteurer &A);
    void done(esteps was,const Abenteurer &A);
    
    void restart(const Abenteurer &A) { set(SPEZIES,A); }
};
#endif
