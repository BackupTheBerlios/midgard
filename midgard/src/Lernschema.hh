#ifndef _LERNSCHEMA_HH
#  define _LERNSCHEMA_HH
#include <gtk--/progressbar.h>
#include <map>
#include "MidgardBasicElement.hh"


class Lernschema 
{
   public:
      struct st_index {std::string typ; std::string art; std::string fertigkeit;
             st_index()  {};
             st_index(std::string t, std::string a, std::string f) 
               : typ(t),art(a),fertigkeit(f) {}
             bool operator==(const st_index& b) const
               {return art==b.art && typ==b.typ && fertigkeit==b.fertigkeit;}
             bool operator<(const st_index& b) const
               { return  art <b.art || 
                        (art==b.art && typ <b.typ) ||
                        (art==b.art && typ==b.typ && fertigkeit<b.fertigkeit);}
         };
   private:
      struct st_wert  {bool pflicht;int erfolgswert;
                       std::string attribut; int lernpunkte;
                       std::string p_element; std::string s_element;
             st_wert(): pflicht(false),erfolgswert(0),lernpunkte(-1){}
             st_wert (bool p,int e, std::string a, int l,
                      std::string pe, std::string se)
                      : pflicht(p),erfolgswert(e),
                        attribut(a),lernpunkte(l),p_element(pe),
                        s_element(se) {}
         };

      std::map<st_index,st_wert> lern_map;

      bool get_Pflicht(const st_index& I) const 
            {return const_cast<std::map<st_index,st_wert>&>(lern_map)[I].pflicht;}
   public:
      Lernschema() {};
      Lernschema(Gtk::ProgressBar *progressbar);

      std::string get_Pflicht_str(const st_index& I) const 
            {if (get_Pflicht(I)) return "*";else return "";}
      int get_Lernpunkte(const st_index& I) const 
            {return const_cast<std::map<st_index,st_wert>&>(lern_map)[I].lernpunkte;}
      std::string get_Attribut(const st_index& I) const 
            {return const_cast<std::map<st_index,st_wert>&>(lern_map)[I].attribut;}
      std::list<cH_MidgardBasicElement> get_List(const std::string& art, 
                                       const vector<cH_Typen>& _Typ) const;
};

#endif
