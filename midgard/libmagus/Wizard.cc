
#include "config.h"
#include "Wizard.hh"
#include <Misc/inbetween.h>
#include "Abenteurer.hh"

void Wizard::set(esteps was)
{  act_step=was;
}

void Wizard::next_step()
{  if (in(act_step.Value(),Inaktiv,FERTIG)) return;
   act_step=esteps(int(act_step.Value())+1);
}

bool Wizard::can_skip(const Abenteurer &A)
{  switch (act_step.Value())
   {  case SPEZIALWAFFE:
   	 return !A.Typ1()->Spezialwaffe() && !A.Typ2()->Spezialwaffe();
      case SPEZIALGEBIET:
         return !A.Typ1()->Spezialgebiet() && !A.Typ2()->Spezialgebiet();
      case START:
      case LERNSCHEMA_SEITE:
         return true;
      case SPEZIES:
         return A.Spezies()->Name()!="Mensch" || A.St()>1 || A.Gw()>1;
      case GRUNDWERTE:
         return A.St()>1 || A.Gw()>1 || A.Gs()>1 || A.Ko()>1 || A.In()>1;
      case GESCHLECHT:
         return A.Geschlecht()!=Enums::Mann || A.Typ1()->Valid();
      case TYP:
         return A.Typ1()->Valid();
      case STADTLAND: // !=Enums::Stadt
      case ABGELEITETEWERTE:
         return A.Sb()>1 || A.Au()>1 || A.pA()>1;
      case HERKUNFT:
         return !!A.Herkunft();
#warning ...
      default:
         return false;
   }
}

void Wizard::set(esteps was,const Abenteurer &A)
{  set(was);
   skip_if_possible(A);
}

void Wizard::next_step(const Abenteurer &A)
{  next_step();
   skip_if_possible(A);
}

void Wizard::done(esteps was,const Abenteurer &A)
{  if (act_step.Value()==Inaktiv) return;
   // schauen ob das sinnvoll war - reicht das schon?
   if (was<act_step.Value()) set(was);
   else next_step();
   skip_if_possible(A);
}

void Wizard::skip_if_possible(const Abenteurer &A)
{  while (can_skip(A)) next_step();
}

