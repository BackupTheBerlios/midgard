
class grad_anstieg{

      int grad;
      int steigern_EP_prozent;
      int grad_basiswerte; 
      int grad_max_abwehr; 
      int grad_max_resistenz;
      int grad_max_zaubern;

   public:
      grad_anstieg() 
               : grad(1), steigern_EP_prozent(50), grad_basiswerte(1),
                 grad_max_abwehr(1), grad_max_resistenz(1), grad_max_zaubern(1) {}
      void clear() {*this=grad_anstieg();}

      int get_Steigern_EP_Prozent() const {return steigern_EP_prozent;}
      int get_Grad_Basiswerte() const {return grad_basiswerte;}
      int get_Grad_Abwehr() const {return grad_max_abwehr;}
      int get_Grad_Resistenz() const {return grad_max_resistenz;}
      int get_Grad_Zaubern() const {return grad_max_zaubern;}

      void get_max_werte();
      void set_Grad_Anstieg(int g,int p,int b) 
              { grad=g; steigern_EP_prozent=p; grad_basiswerte=b;
                get_max_werte(); }
      void set_Grad_Anstieg(int g) 
              { grad=g; get_max_werte(); }
      void set_Steigern_EP_Prozent(int i) {steigern_EP_prozent=i;}
      void set_Grad_Basiswerte(int i) {grad_basiswerte=i;}
};  
