#include "midgard_CG.hh"

void midgard_CG::sprache_uebernehmen(string s,int wert)
{
   vec_sprachen.push_back(st_sprachen(s,wert,""));
   midgard_CG::sprachen_schrift();
}

void midgard_CG::schrift_uebernehmen(string s, string t)
{
   vec_schriften.push_back(st_schriften(s,t));
   midgard_CG::sprachen_schrift();
}
