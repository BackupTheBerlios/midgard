#ifndef CLASS_TYPEN_
#define CLASS_TYPEN_

#include<string>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>

class Typen : public HandleContent
{
   std::string typs;
   int typnr;
   std::string typl,typlw,typz;
   std::string zaubern,ausdauer,region;
   int stand,sb,ruestung,geld;
   mutable int opionmenu_nr;

public:
   Typen(const std::string& n);
   Typen() : typnr(0),stand(0),sb(0),ruestung(0),geld(0),opionmenu_nr(0){}
   
   int Nr() const {return opionmenu_nr;}
   void set_opionmenu_nr(int o) const {opionmenu_nr=o;}
   std::string Name(const std::string& geschlecht) const 
      {
//cout << "Geschlect im Typ = "<<geschlecht<<'\n';
if (geschlecht=="m") return typl; else return typlw;}
   std::string Short() const {return typs;}
   std::string Zaubern() const {return typz;}
   std::string Ausdauer() const {return ausdauer;}
   int Stand() const {return stand;}
   int Sb() const {return sb;}
   int Ruestung() const {return ruestung;}
   int Geld() const {return geld;}
   std::string Region() const {return region;}

   bool is_mage() const 
    { if(Zaubern()=="z" || Zaubern()=="j") return true; else return false; } 
};

class cH_Typen : public Handle<const Typen>    
{
    typedef CacheStatic<std::string,cH_Typen> cache_t;
    static cache_t cache;
    cH_Typen(Typen *s) : Handle<const Typen>(s) {};
    friend class std::map<std::string,cH_Typen>;
///    cH_Typen(){};
  public:
   cH_Typen() {*this=new Typen();}
   cH_Typen(const std::string& name);
};
 
class Typen_All
{
      std::vector<cH_Typen> list_All;
   public:
      Typen_All(Gtk::ProgressBar *progressbar);
      std::vector<cH_Typen> get_All() const {return list_All;}
};
  

#endif
