#include "midgard_CG.hh"

int midgard_CG::attribut_check(string at)
{
   int b=0;

   if (at=="St" && werte.st>=81) ++b;
   if (at=="St" && werte.st>=96) ++b;
   if (at=="Ge" && werte.ge>=81) ++b;
   if (at=="Ge" && werte.ge>=96) ++b;
   if (at=="Ko" && werte.ko>=81) ++b;
   if (at=="Ko" && werte.ko>=96) ++b;
   if (at=="In" && werte.in>=81) ++b;
   if (at=="In" && werte.in>=96) ++b;
   if (at=="Zt" && werte.zt>=81) ++b;
   if (at=="Zt" && werte.zt>=96) ++b;
   if (at=="RW" && werte.rw>=81) ++b;
   if (at=="RW" && werte.rw>=96) ++b;
   if (at=="Sb" && werte.sb>=81) ++b;
   if (at=="Sb" && werte.sb>=96) ++b;
   if (at=="pA" && werte.pa>=81) ++b;
   if (at=="pA" && werte.pa>=96) ++b;
 return b;
}
