// generated 2001/2/2 10:59:38 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to gw_wuerfeln.cc_glade

// This file is for your program, I won't touch it again!

#include "midgard_CG.hh"
#include <strstream>
#include "zufall.h"

void midgard_CG::gw_wuerfeln()
{   
 get_spezies_constraint();
 werte.st = wuerfeln_best_of_two();
 werte.ge = wuerfeln_best_of_two();
 werte.ko = wuerfeln_best_of_two();
 werte.in = wuerfeln_best_of_two();
 werte.zt = wuerfeln_best_of_two();

 midgard_CG::zeige_werte(werte,"grund");
}

int midgard_CG::wuerfeln_best_of_two()
{
 Random random;
 int ran  = random.integer(1,100);
 int ran2 = random.integer(1,100);
 (ran > ran2) ? : ran=ran2;
 return ran;
}
