#ifndef _PRAXISPUNKTE_HH
#  define _PRAXISPUNKTE_HH
#include <string>
#include <map>
#include <gtk--/progressbar.h>
class cH_MidgardBasicElement;
class cH_Typen;
#include <vector>
class Grundwerte;

class Praxispunkte 
{
      struct st_map {int max_wert;int lernfaktor;
             st_map() : max_wert(0),lernfaktor(0) {}
             st_map(int m,int l) : max_wert(m),lernfaktor(l) {}
            };
      std::map<std::string,st_map> prax_map;
      
   public:
      Praxispunkte() {}
      Praxispunkte(Gtk::ProgressBar *progressbar);
private:
      bool wuerfeln(const cH_MidgardBasicElement& MBE, 
                                 const Grundwerte& Werte,
                                 const vector<cH_Typen>& Typ,
                                 bool wuerfeln);
};

#endif
