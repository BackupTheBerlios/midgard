#include "midgard_CG.hh"

string midgard_CG::get_erfolgswert_zaubern(const styp& typ,const string& name)
{
   double fac = midgard_CG::get_standard_zauber(typ.s,name);
   int ifac;
   if (fac == 0.5) ifac = 0; else ifac=-2;

   int ispez=0;
   if (typ.s=="Ma") ispez = midgard_CG::get_spezial_zauber(typ.s,name);

   string erf = itos (atoi(werte.zaubern_wert.c_str())
                            +werte.bo_za + ifac + ispez) ;
   return(erf);
}
