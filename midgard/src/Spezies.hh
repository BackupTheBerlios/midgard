#ifndef _SPEZIES_HH
#  define _SPEZIES_HH

#include <gtk--/progressbar.h>
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <string>


class Spezies : public HandleContent
{
  std::string name;
  int nr;
  int st,gw,gs,ko,in,zt,sb,au,lpbasis,ap_grad,gift,m_abb,
       m_psy,m_phs,m_phk,alter, groesse_f,groesse_w, groesse_s, gestalt,
       b_f,b_s;

protected:   
  struct st_spez {std::string typen;int maxgrad;
         st_spez(std::string t,int m) : typen(t),maxgrad(m) {};
      };
private:
  std::vector<st_spez> vec_typen;

public:
   Spezies()
     :st(0),gw(0),gs(0),ko(0),in(0),zt(0),sb(0),au(0),
       lpbasis(0),ap_grad(0),gift(0),m_abb(0),
       m_psy(0),m_phs(0),m_phk(0),alter(0), 
       groesse_f(0),groesse_w(0), groesse_s(0),
       gestalt(0),b_f(0),b_s(0)  {}
   Spezies(const std::string& n); 

   std::string Name() const {return name;}
   int Nr() const {return nr;}
   int St() const {return st;}
   int Gw() const {return gw;}
   int Gs() const {return gs;}
   int Ko() const {return ko;}
   int In() const {return in;}
   int Zt() const {return zt;}
   int Sb() const {return sb;}
   int Au() const {return au;}
   int LPBasis() const {return lpbasis;}
   int AP_Grad() const {return ap_grad;}
   int Abb() const {return m_abb;}
   int Psy() const {return m_psy;}
   int Phs() const {return m_phs;}
   int Phk() const {return m_phk;}
   int Gift() const {return gift;}
   int Alter() const {return alter;}
   int Groesse_f() const {return groesse_f;}
   int Groesse_w() const {return groesse_w;}
   int Groesse_s() const {return groesse_s;}
   int Gestalt() const {return gestalt;}
   int B_f() const {return b_f;}
   int B_s() const {return b_s;}
//   std::vector<st_spez> get_Vec_Typen() const {return vec_typen;}
   bool Typ_erlaubt(std::string typ) const;
};

class cH_Spezies : public Handle<const Spezies>
{
    typedef CacheStatic<std::string,cH_Spezies> cache_t;
    static cache_t cache;
    cH_Spezies(Spezies *s) : Handle<const Spezies>(s) {};
    friend class std::map<std::string,cH_Spezies>; 
    cH_Spezies(){};
  public:
//   cH_Spezies() {*this=new Spezies();}
   cH_Spezies(const std::string& name);
};


class Spezies_All
{
      std::vector<cH_Spezies> list_All;
   public:
      Spezies_All(Gtk::ProgressBar *progressbar);
      std::vector<cH_Spezies> get_All() const {return list_All;}
};

#endif
