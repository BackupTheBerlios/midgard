#ifndef _PFLICHT_HH
#  define _PFLICHT_HH
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Typen.hh"
#include <gtk--/progressbar.h>


class Pflicht //: public HandleContent
{
      struct pf{std::string pflicht;std::string verboten; 
                int lernpunkte; int erfolgswert; std::string spielbeginn;
         pf(std::string p,std::string v,int l, int e, std::string s)
            :pflicht(p),verboten(v),lernpunkte(l),erfolgswert(e),spielbeginn(s){}
         bool operator<(const pf& b) {return pflicht<b.pflicht;}
         };
      map<std::string,list<pf> > pflicht_map;
      
   public:
      Pflicht() {}
      Pflicht(Gtk::ProgressBar *progressbar);
      enum LE {LERNPUNKTE,ERFOLGSWERT};

      int istPflicht(const std::string& spezies,const vector<cH_Typen>& Typ,
                     const std::string& s,LE le) const ;
      bool istVerboten(const std::string& spezies,const vector<cH_Typen>& Typ,
                       const std::string& s,bool spielbeginn=false) const;
         
};

#endif
