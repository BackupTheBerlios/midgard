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
 Random random;
// Grundwerte: best of two
 for(int i=0;i<5;++i)
   {
    int ran  = random.integer(1,100);
    int ran2 = random.integer(1,100);
    (ran > ran2) ? : ran=ran2;
    if (i==0) werte.st=ran;
    if (i==1) werte.ge=ran;
    if (i==2) werte.ko=ran; 
    if (i==3) werte.in=ran; 
    if (i==4) werte.zt=ran; 
   }
 midgard_CG::zeige_werte(werte,"grund");
}


