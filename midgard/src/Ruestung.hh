#ifndef RUESTUNGCLASS
#define RUESTUNGCLASS
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>


class Ruestung  : public HandleContent
{
   std::string name, longname, region; 
   int lp_verlust,min_staerke,rw_verlust,b_verlust,
      abwehr_bonus_verlust,angriffs_bonus_verlust;

  public:
//   Ruestung() {};
   Ruestung(const std::string& n);

   std::string Name() const   {return name; }
   std::string Long() const {return longname;}
   std::string Region() const {return region;}
   int LP_Verlust() const {return lp_verlust;}
   int Min_Staerke() const {return min_staerke;}
   int RW_Verlust() const {return rw_verlust;}
   int B_Verlust() const {return b_verlust;}
   int AbwehrBonus_Verlust(int abwehr_bonus) const;
   int AngriffsBonus_Verlust(int angriffs_bonus) const;
};

class cH_Ruestung : public Handle<const Ruestung>
{
    typedef CacheStatic<std::string,cH_Ruestung> cache_t;
    static cache_t cache;
    cH_Ruestung(Ruestung *s) : Handle<const Ruestung>(s) {};
    friend class std::map<std::string,cH_Ruestung>;
    cH_Ruestung() {}
  public:
//   cH_Ruestung() {*this=new Ruestung();}
   cH_Ruestung(const std::string& name);

};

class Ruestung_All
{
   std::vector<cH_Ruestung> list_All;
  public:
   Ruestung_All(Gtk::ProgressBar *progressbar);
   std::vector<cH_Ruestung> get_All() const {return list_All;}
};

#endif
