class Data_spezies : public HandleContent
{
  int st,ge,ko,in,zt,sb,au,lpbasis,ap_grad,gift,m_abb,
       m_psy,m_phs,m_phk,alter, groesse_f,groesse_w, groesse_s, gestalt,
       b_f,b_s;

public:
   Data_spezies()
   :st(0),ge(0),ko(0),in(0),zt(0),sb(0),au(0),
       lpbasis(0),ap_grad(0),gift(0),m_abb(0),
       m_psy(0),m_phs(0),m_phk(0),alter(0), 
       groesse_f(0),groesse_w(0), groesse_s(0),
       gestalt(0),b_f(0),b_s(0)  {}
   Data_spezies(int _st,int _ge,int _ko,int _in,int _zt,int _sb,int _au,    
   int _lpbasis,int _ap_grad,int _gift,int _m_abb, int _m_psy,int _m_phs, int _m_phk, 
   int _alter,int _groesse_f,int _groesse_w,int _groesse_s,int _gestalt,   
   int _b_f,int _b_s)
   :st(_st),ge(_ge),ko(_ko),in(_in),zt(_zt),sb(_sb),au(_au),
       lpbasis(_lpbasis),ap_grad(_ap_grad),gift(_gift),m_abb(_m_abb),
       m_psy(_m_psy),m_phs(_m_phs),m_phk(_m_phk),alter(_alter), 
       groesse_f(_groesse_f),groesse_w(_groesse_w), groesse_s(_groesse_s),
       gestalt(_gestalt),b_f(_b_f),b_s(_b_s)  {}

   int St() const {return st;}
   int Ge() const {return ge;}
   int Ko() const {return ko;}
   int In() const {return in;}
   int Zt() const {return zt;}
   int Sb() const {return sb;}
   int Au() const {return au;}
   int LPBasis() const {return lpbasis;}
   int AP_Grad() const {return ap_grad;}
   int m_Abb() const {return m_abb;}
   int m_Psy() const {return m_psy;}
   int m_Phs() const {return m_phs;}
   int m_Phk() const {return m_phk;}
   int Gift() const {return gift;}
   int Alter() const {return alter;}
   int Groesse_f() const {return groesse_f;}
   int Groesse_w() const {return groesse_w;}
   int Groesse_s() const {return groesse_s;}
   int Gestalt() const {return gestalt;}
   int B_f() const {return b_f;}
   int B_s() const {return b_s;}

};
/*
class cH_Spezies : public const_Handle<Data_spezies>
{
protected:
 cH_Spezies() {}
public:
 cH_Spezies(Data_spezies *r) : const_Handle<Data_spezies>(r){}
};
*/
