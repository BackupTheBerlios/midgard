#include "midgard_CG.hh"

bool midgard_CG::standard_one_G(const vector<std::string>& s)
{
 assert(s.size()==2);
 if (s[0] == "G" || s[1] =="G" ) return true;
 return false;
}

bool midgard_CG::standard_all_S(const vector<std::string>& s)
{
 assert(s.size()==2);
 if (s[0] == "S" && (s[1] =="S" || s[1]=="" )) return true;
 if (s[1] == "S" && (s[0] =="S" || s[0]=="" )) return true;
 return false;
}
     