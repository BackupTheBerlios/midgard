#ifndef _PRAXISPUNKTE_HH
#  define _PRAXISPUNKTE_HH
#include <string>
#include <map>
#include <gtk--/progressbar.h>


class Praxispunkte 
{
      struct st_map {int max_wert;int lernfaktor;
             st_map(int m,intl) : max_wert(m),lernfaktor(l) {}
            };
      std::map prax_map<std::string,st_map>;
      
   public:
      Praxispunkte() {}
      Praxispunkte(Gtk::ProgressBar *progressbar);

};

#endif
