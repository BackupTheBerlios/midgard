#error hier geht's weiter

#include "config.h"
#include "Wizard.hh"

Wizard::esteps &operator++(Wizard::esteps &a)
{  
   a= Wizard::esteps(int(a)+1);
   if(a==Wizard::MAXSTEPS) a=Wizard::esteps(int(Wizard::MAXSTEPS)-1);
   return a;
}

void Wizard::next_step(esteps e)
{
  actual_step=++e;
  evaluate_step(actual_step);
}

void Wizard::restart()
{actual_step=START;
 evaluate_step(++actual_step);
}


void Wizard::evaluate_step(esteps step)
{
  assert(vecwiz.size()>(size_t)(step));
//  std::vector<cH_Typen> Typ=hauptfenster->getVTyp();
//cout <<"evaluate_step " <<step<<' '<<LERNSCHEMA_SEITE<<' '<<SPEZIALWAFFE<<' '<<SPEZIALGEBIET<<'\n';
//  if(step==LERNSCHEMA_SEITE) { next_step(LERNSCHEMA_SEITE); return;}

  if(step==SPEZIALWAFFE&&(!hauptfenster->getChar()->Typ1()->Spezialwaffe()&&!hauptfenster->getChar()->Typ2()->Spezialwaffe()))
   {
     next_step(SPEZIALWAFFE);
     return;
   }
  if(step==SPEZIALGEBIET&&(!hauptfenster->getChar()->Typ1()->Spezialgebiet()&&!hauptfenster->getChar()->Typ2()->Spezialgebiet()))
   {
     next_step(SPEZIALGEBIET);
     return;
   }
//  hauptfenster->notebook_main->set_current_page(vecwiz[step].page);
//  hauptfenster->set_wizard(vecwiz[step].text);
  hauptfenster->wizard_do_something(vecwiz[step].page,vecwiz[step].text);

}

