
class grad_anstieg{

      int steigern_EP_prozent;
      int grad_basiswerte; 
      int grad_abwehr; 
      int grad_resistenz;

   public:
//      grad_anstieg(int p,int b,int a,int r) 
//               : steigern_EP_prozent(p), grad_basiswerte(b),
//                 grad_abwehr(a), grad_resistenz(r) {}
      grad_anstieg() 
               : steigern_EP_prozent(1), grad_basiswerte(1),
                 grad_abwehr(1), grad_resistenz(1) {}

      int get_Steigern_EP_Prozent() const {return steigern_EP_prozent;}
      int get_Grad_Basiswerte() const {return grad_basiswerte;}
      int get_Grad_Abwehr() const {return grad_abwehr;}
      int get_Grad_Resistenz() const {return grad_resistenz;}

      void set_Grad_Anstieg(int p,int b,int a,int r) 
              { steigern_EP_prozent=p, grad_basiswerte=b,
                 grad_abwehr=a, grad_resistenz=r; }
      void set_Steigern_EP_Prozent(int i) {steigern_EP_prozent=i;}
      void set_Grad_Basiswerte(int i) {grad_basiswerte=i;}
      void set_Grad_Abwehr(int i) {grad_abwehr=i;}
      void set_Grad_Resistenz(int i) {grad_resistenz=i;}
};  
