#include "midgard_CG.hh"

bool midgard_CG::region_check(string region)
{
//cout << "region = "<<"\t"<<region<<"\n";
  if (region=="") return true;  

  if (region=="K" && KanThaiPanbool) return true;
  if (region=="A" && Albabool)       return true;

  else return false;

}
