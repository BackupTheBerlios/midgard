#include "midgard_CG.hh"

bool midgard_CG::region_check(string region)
{
//cout << "region = "<<"\t"<<region<<"\n";
  if (region=="") return true;  

  if (region=="K" && KanThaiPanbool) return true;
  if (region=="A" && Albabool)       return true;
  if (region=="R" && Rawindrabool)     return true;
//  if (region=="W" && Waelandbool)    return true;
  if (region=="E" && Escharbool)     return true;
//  if (region=="N" && Nahuatlanbool)  return true;

  else return false;

}
